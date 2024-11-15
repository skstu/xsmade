#include "config.h"

Server::Server() {
  Init();
}

Server::~Server() {
  UnInit();
}
void Server::Init() {
  server_ = new httplib::Server();
}
void Server::UnInit() {
  if (server_) {
    delete server_;
    server_ = nullptr;
  }
}
bool Server::Start() {
  do {
    if (open_.load() || !server_)
      break;
    port_ = xs_sys_get_free_port();
    if (port_ <= 0)
      break;
    open_.store(true);
    threads_.emplace_back([this]() { Listen(); });
    server_->wait_until_ready();
  } while (0);
  return open_.load();
}
void Server::Stop() {
  do {
    if (!open_.load())
      break;
    open_.store(false);
    server_->stop();
    for (auto &t : threads_)
      t.join();
    threads_.clear();
  } while (0);
}
void Server::Process() {
  do {
    online_brws_.iterate_clear(
        [&](const auto &key, const long long &pid, bool &itclear) {
          if (0 == xs_sys_process_has_exit(pid)) {
            client_notifys_.push(Config::CreateBrwCloseNotifyPak(key));
            itclear = true;
          }
        });
  } while (0);
  do {
    unsigned int notify_port = Config::ConfigGet()->GetClientLocalPort();
    if (notify_port <= 0)
      break;
    auto msgs = client_notifys_.pops();
    if (msgs.empty())
      break;
    for (const auto &msg : msgs) {
      httplib::Client cli("127.0.0.1", notify_port);
      httplib::Headers heads = {{"content-type", "application/json"}};
      auto view = msg.c_str();
      cli.Post("/close", heads, msg.data(), msg.size(), "application/json");
    }
  } while (0);
}
void Server::OnRequest(const RequestType &reqType, const std::string &body,
                       std::string &res) {
  int code = -1;
  std::string message;
  long long brwpid = 0;
  rapidjson::Document resDoc(rapidjson::Type::kObjectType);
  rapidjson::Value resultObj(rapidjson::Type::kObjectType);

  switch (reqType) {
  case RequestType::SERVER_OPEN: { //!@ 初始化请求
    rapidjson::Value onlines(rapidjson::kArrayType);

    online_brws_.iterate([&](const std::string &key, const long long &pid) {
      rapidjson::Value brwObj(rapidjson::Type::kObjectType);
      brwObj.AddMember(
          rapidjson::Value().SetString("pid", resDoc.GetAllocator()).Move(),
          rapidjson::Value().SetInt64(pid).Move(), resDoc.GetAllocator());
      brwObj.AddMember(
          rapidjson::Value().SetString("key", resDoc.GetAllocator()).Move(),
          rapidjson::Value()
              .SetString(key.c_str(), resDoc.GetAllocator())
              .Move(),
          resDoc.GetAllocator());
      onlines.PushBack(brwObj, resDoc.GetAllocator());
    });
    resultObj.AddMember(
        rapidjson::Value().SetString("brwonline", resDoc.GetAllocator()),
        onlines, resDoc.GetAllocator());
  } break;
  case RequestType::SERVER_CLOSE: {
    std::exit(3762);
  } break;
  case RequestType::BROWSER_OPEN: {
    rapidjson::Document doc;
    if (doc.Parse(body.data(), body.size()).HasParseError() ||
        doc.ObjectEmpty()) {
      code = -1001;
      message = "Invalid request data";
      break;
    }

    bool is_open_ready = false;
    std::string final_brw_prog_fname;
    std::string final_brw_key = "root";

    Config::ConfigGet()->ConfigureSet(body);

    stl::Directory::Create(Config::ConfigGet()->WorkProjectsPath());
    stl::File::WriteFile(Config::ConfigGet()->WorkProjectsPath() +
                             "/brwccfg.json",
                         Config::ConfigGet()->ConfigureGet().source_);
    std::vector<std::string> brw_startup_args;
    do { //!@ proxy
      if (!Config::ConfigGet()->ConfigureGet().proxy_.valid())
        break;
      std::string node =
          fmt::format("--proxy-server={}:{}",
                      Config::ConfigGet()->ConfigureGet().proxy_.addr,
                      Config::ConfigGet()->ConfigureGet().proxy_.port);
      brw_startup_args.emplace_back(node);
    } while (0);

    do { //!@ startup url
      if (Config::ConfigGet()->ConfigureGet().worker_.url.empty())
        break;
      std::string node = fmt::format(
          "--xs-openurl={}", Config::ConfigGet()->ConfigureGet().worker_.url);
      brw_startup_args.emplace_back(node);
    } while (0);

    do { //!@ userAgent
      if (Config::ConfigGet()
              ->ConfigureGet()
              .fp_.f_.vs_.navigator_.userAgent.empty())
        break;
      std::string node = fmt::format(
          R"(--user-agent="{}")",
          Config::ConfigGet()->ConfigureGet().fp_.f_.vs_.navigator_.userAgent);
      brw_startup_args.emplace_back(node);
    } while (0);
    do { //!@ user-data-dir
      std::string node;
      std::string user_data =
          Config::ConfigGet()->WorkProjectsPath() + "/userdata/cache/root/";
      if (!Config::ConfigGet()->ConfigureGet().rule_.key.empty()) {
        user_data =
            Config::ConfigGet()->WorkProjectsPath() + "/userdata/cache/";
        user_data.append(Config::ConfigGet()->ConfigureGet().rule_.key)
            .append("/");
        final_brw_key = Config::ConfigGet()->ConfigureGet().rule_.key;
      }
      node = fmt::format("--user-data-dir={}", user_data);
      brw_startup_args.emplace_back(node);
    } while (0);

    if (online_brws_.search(final_brw_key)) {
      code = -1002;
      message = "The target is already running";
      break;
    }
    do { //!@ user-data-dir
      brw_startup_args.emplace_back("--no-first-run");
      // if (!url_.empty()) {
      //	process_startup_cmdline_.append(url_).append(L" ");
      // }
      brw_startup_args.emplace_back("--disable-sync");
      brw_startup_args.emplace_back("--disable-gaia-services");
      brw_startup_args.emplace_back("--disable-account-consistency");
      brw_startup_args.emplace_back(
          "--disable-features=ChromeSignin,AccountConsistency");
      brw_startup_args.emplace_back("--disable-background-mode");
      brw_startup_args.emplace_back("--no-default-browser-check");
    } while (0);

    do { //!@
      //!@ 浏览器目录
      std::string chromium_dir = Config::ConfigGet()->ChromiumPath();
      std::map<std::string, std::string> dirs, files;
      stl::Directory::EnumU8(chromium_dir, dirs, files, false);
      if (dirs.empty())
        break;
#if defined(__OSMAC__)
      final_brw_prog_fname = chromium_dir + dirs.begin()->first + "/chrome.app";
      if (!Config::ConfigGet()->ConfigureGet().worker_.brwver.empty()) {
        auto found =
            dirs.find(Config::ConfigGet()->ConfigureGet().worker_.brwver);
        if (found == dirs.end())
          break;
        final_brw_prog_fname =
            chromium_dir + found->first + "/chrome.app/Contents/MacOS/chromium";
      }
#elif defined(__OSWIN__)
      final_brw_prog_fname = chromium_dir + dirs.begin()->first + "/chrome.exe";
      if (!Config::ConfigGet()->ConfigureGet().worker_.brwver.empty()) {
        auto found =
            dirs.find(Config::ConfigGet()->ConfigureGet().worker_.brwver);
        if (found == dirs.end())
          break;
        final_brw_prog_fname = chromium_dir + found->first + "/chrome.exe";
      }
#endif
      is_open_ready = true;
    } while (0);

    if (!final_brw_prog_fname.empty()) {
      // brw_startup_args
      std::vector<const char *> args;
      for (const auto &node : brw_startup_args)
        args.emplace_back(node.c_str());
      args.emplace_back(nullptr);
      long long pid = 0;
      int status =
          xs_sys_process_spawn(final_brw_prog_fname.c_str(), &args[0], &pid);
      if (status != 0)
        break;
      online_brws_.push(final_brw_key, pid);
      code = 0;
      message = "ok";
    }

  } break;
  case RequestType::BROWSER_CLOSE: {
    rapidjson::Document doc;
    if (doc.Parse(body.data(), body.size()).HasParseError())
      break;
    if (!doc.HasMember("rule") || !doc["rule"].IsObject())
      break;
    if (!doc["rule"].HasMember("key") || !doc["rule"]["key"].IsString())
      break;
    const std::string key = doc["rule"]["key"].GetString();
    auto found = online_brws_.search(
        key, [](const std::string &key, const long long &pid) {
          xs_sys_process_kill(pid);
        });
    online_brws_.pop(key);
    if (found) {
      code = 0;
      message = "ok";
      client_notifys_.push(Config::CreateBrwCloseNotifyPak(key));
    } else {
      code = -1003;
      message = "not found";
    }
  } break;
  case RequestType::BROWSER_GET: {
    rapidjson::Value brwObjs(rapidjson::Type::kArrayType);
    std::map<std::string, std::string> dirs, files;
    stl::Directory::EnumU8(Config::ConfigGet()->ChromiumPath(), dirs, files,
                           false);
    for (const auto &node : dirs) {
      brwObjs.PushBack(rapidjson::Value()
                           .SetString(node.first.c_str(), resDoc.GetAllocator())
                           .Move(),
                       resDoc.GetAllocator());
    }
    resultObj.AddMember(
        rapidjson::Value()
            .SetString("chromium_versions", resDoc.GetAllocator())
            .Move(),
        brwObjs, resDoc.GetAllocator());
    code = 0;
    message = "ok";
  } break;
  default:
    break;
  }

  do {
    resDoc.AddMember(
        rapidjson::Value().SetString("code", resDoc.GetAllocator()).Move(),
        rapidjson::Value().SetInt(code).Move(), resDoc.GetAllocator());
    resDoc.AddMember(
        rapidjson::Value().SetString("message", resDoc.GetAllocator()).Move(),
        rapidjson::Value()
            .SetString(message.c_str(), resDoc.GetAllocator())
            .Move(),
        resDoc.GetAllocator());
    resDoc.AddMember(
        rapidjson::Value().SetString("result", resDoc.GetAllocator()).Move(),
        resultObj, resDoc.GetAllocator());
    res = Json::toString(resDoc);
  } while (0);
}
void Server::Listen() {
  server_->Post("/server/open",
                [this](const httplib::Request &req, httplib::Response &res) {
                  std::string repRes;
                  OnRequest(RequestType::SERVER_OPEN, req.body, repRes);
                  res.set_content(repRes.empty() ? "{}" : repRes,
                                  "application/json; charset=utf-8");
                });
  server_->Post("/server/close",
                [this](const httplib::Request &req, httplib::Response &res) {
                  std::string repRes;
                  OnRequest(RequestType::SERVER_CLOSE, req.body, repRes);
                  res.set_content(repRes.empty() ? "{}" : repRes,
                                  "application/json; charset=utf-8");
                });
  server_->Post("/browser/down",
                [this](const httplib::Request &req, httplib::Response &res) {
                  std::string repRes;
                  // OnRequest(RequestType::BROWSER_OPEN, req.body, repRes);
                  res.set_content(repRes.empty() ? "{}" : repRes,
                                  "application/json; charset=utf-8");
                });
  server_->Post("/browser/open",
                [this](const httplib::Request &req, httplib::Response &res) {
                  std::string repRes;
                  OnRequest(RequestType::BROWSER_OPEN, req.body, repRes);
                  res.set_content(repRes.empty() ? "{}" : repRes,
                                  "application/json; charset=utf-8");
                });
  server_->Post("/browser/close",
                [this](const httplib::Request &req, httplib::Response &res) {
                  std::string repRes;
                  OnRequest(RequestType::BROWSER_CLOSE, req.body, repRes);
                  res.set_content(repRes.empty() ? "{}" : repRes,
                                  "application/json; charset=utf-8");
                });
  server_->Post("/browser/get",
                [this](const httplib::Request &req, httplib::Response &res) {
                  std::string repRes;
                  OnRequest(RequestType::BROWSER_GET, req.body, repRes);
                  res.set_content(repRes.empty() ? "{}" : repRes,
                                  "application/json; charset=utf-8");
                });
  server_->Post("/", [](const httplib::Request &req, httplib::Response &res) {

  });

  do {
    std::string route_path =
        Config::ConfigGet()->CurrentProcessPath() + "/route.json";

    rapidjson::Document doc;
    std::string route_buffer = stl::File::ReadFile(route_path);
    if (doc.Parse(route_buffer.data(), route_buffer.size()).HasParseError()) {
      stl::File::Remove(route_path);
      stl::File::Create(route_path);
      stl::File::WriteFile(route_path, "{}");
      doc.Parse("{}");
    }
    if (doc.HasMember("server_port"))
      doc.RemoveMember("server_port");
    if (!doc.HasMember("client_port")) {
      doc.AddMember(rapidjson::Value()
                        .SetString("client_port", doc.GetAllocator())
                        .Move(),
                    rapidjson::Value().SetUint(0).Move(), doc.GetAllocator());
    }
    doc.AddMember(
        rapidjson::Value().SetString("server_port", doc.GetAllocator()).Move(),
        rapidjson::Value().SetUint(port_).Move(), doc.GetAllocator());

    stl::File::WriteFile(route_path, Json::toString(doc));
  } while (0);
#if ENABLE_DEVELOPER_DEBUG
  server_->listen("127.0.0.1", 65535);
#else
  server_->listen("127.0.0.1", port_);
#endif
}
