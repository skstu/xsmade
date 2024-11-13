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
          if (0 != xs_sys_process_has_exit(pid)) {
            itclear = true;
          }
        });
  } while (0);
}
void Server::OnRequest(const RequestType &reqType, const std::string &body,
                       std::string &res) {
  /*
      "code": 0,
    "message": "ok",
    "browser_id": 19264,
  */
  int code = -1;
  std::string message;
  long long brwpid = 0;

  switch (reqType) {
  case RequestType::SERVER_OPEN: {

  } break;
  case RequestType::SERVER_CLOSE: {

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
      std::string node;
      node.append("--proxy-server=")
          .append(Config::ConfigGet()->ConfigureGet().proxy_.addr)
          .append(
              std::to_string(Config::ConfigGet()->ConfigureGet().proxy_.port));
      brw_startup_args.emplace_back(node);
    } while (0);

    do { //!@ startup url
      if (Config::ConfigGet()->ConfigureGet().worker_.url.empty())
        break;
      std::string node;
      node.append(Config::ConfigGet()->ConfigureGet().worker_.url);
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
      // stl::Directory::Create(user_data);
      node.append("--user-data-dir=").append(user_data);
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
      std::string chromium_dir =
          Config::ConfigGet()->WorkProjectsPath() + "/chromium/";
      std::map<std::string, std::string> dirs, files;
      stl::Directory::EnumU8(chromium_dir, dirs, files, false);
      if (dirs.empty())
        break;
      final_brw_prog_fname = chromium_dir + dirs.begin()->first + "/chrome.app";
      if (!Config::ConfigGet()->ConfigureGet().worker_.brwver.empty()) {
        auto found =
            dirs.find(Config::ConfigGet()->ConfigureGet().worker_.brwver);
        if (found == dirs.end())
          break;
        final_brw_prog_fname = chromium_dir + found->first + "/chrome.app";
      }
      auto sss = 0;
      is_open_ready = true;
    } while (0);

    if (!final_brw_prog_fname.empty()) {
      // brw_startup_args
      std::vector<const char *> args;
      for (const auto &node : brw_startup_args)
        args.emplace_back(node.c_str());
      long long pid = 0;
      int status = xs_sys_process_spawn(
          (final_brw_prog_fname + "/Contents/MacOS/chromium").c_str(), &args[0],
          &pid);
      if (status != 0)
        break;
      online_brws_.push(final_brw_key, pid);
      code = 0;
      message = "ok";
    }

  } break;
  case RequestType::BROWSER_CLOSE: {

  } break;
  case RequestType::BROWSER_GET: {

  } break;
  default:
    break;
  }

  do {
    rapidjson::Document resDoc(rapidjson::Type::kObjectType);
    resDoc.AddMember(
        rapidjson::Value().SetString("code", resDoc.GetAllocator()).Move(),
        rapidjson::Value().SetInt(code).Move(), resDoc.GetAllocator());
    resDoc.AddMember(
        rapidjson::Value().SetString("message", resDoc.GetAllocator()).Move(),
        rapidjson::Value()
            .SetString(message.c_str(), resDoc.GetAllocator())
            .Move(),
        resDoc.GetAllocator());
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
    doc.AddMember(
        rapidjson::Value().SetString("server_port", doc.GetAllocator()).Move(),
        rapidjson::Value().SetUint(port_).Move(), doc.GetAllocator());

    stl::File::WriteFile(route_path, Json::toString(doc));
  } while (0);
#if _DEBUG
  server_->listen("127.0.0.1", 65535);
#else
  server_->listen("127.0.0.1", 65535);
  // server_->listen("127.0.0.1", port_);
#endif
}
