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
#if ENABLE_DEVELOPER_DEBUG
    port_ = 65535;
#else
    port_ = xs_sys_get_free_port();
#endif
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
    brws_.iterate_clear([&](const auto &key, const auto &brw, bool &itclear) {
      if (0 == xs_sys_process_has_exit(brw->GetPid())) {
        client_notifys_.push(Config::CreateBrwCloseNotifyPak(key));
        brw->Release();
        itclear = true;
      }
    });
  } while (0);
  do {
    if (client_notifys_.empty())
      break;
    const unsigned int notify_port =
        Config::ConfigGet()->RouteConfigureGetClientPort();
    if (notify_port <= 0)
      break;
    auto msgs = client_notifys_.pops();
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

    brws_.iterate([&](const std::string &key, const Browser *brw) {
      rapidjson::Value brwObj(rapidjson::Type::kObjectType);
      brwObj.AddMember(
          rapidjson::Value().SetString("pid", resDoc.GetAllocator()).Move(),
          rapidjson::Value().SetInt64(brw->GetPid()).Move(),
          resDoc.GetAllocator());
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
#if ENABLE_DEVELOPER_LOGGER
    LOG_INFO("brwOpenBody:({})", body.empty() ? "empty body!" : body);
#endif
    Browser *brw = new Browser(body);
    if (brws_.search(brw->GetKey())) {
      code = -1002;
      message = "The target is already running";
      brw->Release();
      break;
    }
    bool result = brw->Open();
#if ENABLE_DEVELOPER_LOGGER
    LOG_INFO("create brw {} key({})", result ? "success" : "failed",
             result ? brw->GetKey() : "null");
#endif
    if (result) {
      brws_.push(brw->GetKey(), brw);
    } else {
      brw->Close();
      brw->Release();
    }
    code = result ? 0 : -1001;
    message = result ? "ok" : "Invalid request data";
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
    auto found = brws_.search(
        key, [](const std::string &key, const auto &brw) { brw->Close(); });
    auto pop = brws_.pop(key);
    if (pop) {
      (*pop)->Release();
    }
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
    stl::Directory::EnumU8(Config::ConfigGet()->PathGet().chromium_dir, dirs,
                           files, false);
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

  Config::ConfigGet()->RouteConfigureInit(port_);
  server_->listen("127.0.0.1", port_);
}
