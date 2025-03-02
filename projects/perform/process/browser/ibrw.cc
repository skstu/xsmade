#include <perform.h>

static std::string browser_configure_cache;

IBrowserInterfaceServer::IBrowserInterfaceServer() {
  Init();
}

IBrowserInterfaceServer::~IBrowserInterfaceServer() {
  UnInit();
}
void IBrowserInterfaceServer::Release() const {
  delete this;
}
void IBrowserInterfaceServer::Init() {
  config_ = new BrowserConfig();
  server_ = new httplib::Server();
}
void IBrowserInterfaceServer::UnInit() {
  SK_DELETE_PTR(server_);
  SK_DELETE_PTR(config_);
}
bool IBrowserInterfaceServer::Start() {
  do {
    if (open_.load() || !server_)
      break;
    if (config_->IsDevMode()) {
      port_ = 65535;
    } else {
      port_ = xs_sys_get_free_port();
    }
    if (port_ <= 0)
      break;
    open_.store(true);
    threads_.emplace_back([this]() { Listen(); });
    server_->wait_until_ready();
  } while (0);
  return open_.load();
}
void IBrowserInterfaceServer::Stop() {
  do {
    if (!open_.load())
      break;
    if (gpsWxui) {
      gpsWxui->Stop();
      // wxui::IWxui::Destroy(&gpsWxui);
      gpsWxui = nullptr;
    }
    open_.store(false);
    server_->stop();
    for (auto &t : threads_)
      t.join();
    threads_.clear();
  } while (0);
}
void IBrowserInterfaceServer::Process() {
  do { // get browser request response.
    std::map<std::u16string, std::u16string> brwUserdataDirs, brwUserdataFiles,
        repDirs, repFiles;
    if (!stl::Directory::Exists(config_->PathGet().chromium_user_data_dir))
      break;
    stl::Directory::Enum(config_->PathGet().chromium_user_data_dir,
                         brwUserdataDirs, brwUserdataFiles, false);
    for (const auto &userdatadir : brwUserdataDirs) {
      const auto key = userdatadir.first;
      repDirs.clear();
      repFiles.clear();
      stl::Directory::Enum(config_->GetXSCacheRouteRepsDir(key), repDirs,
                           repFiles, false);

      for (const auto &f : repFiles) {
        do {
          std::string fBuffer = stl::File::ReadFile(f.second);
          if (fBuffer.empty())
            break;
          client_notifys_.push(std::make_tuple<std::string, std::string>(
              "/browser/cookies",
              BrowserConfig::CreateBrwCookiesNotifyPak(key, fBuffer)));
        } while (0);
        stl::File::Remove(f.second);
      }
    }
  } while (0);
  do { //!@ plugin - ffx
    if (gbWxuiStatus)
      break;
    if (!gpsWxui)
      break;
    gpsWxui->Stop();
    // wxui::IWxui::Destroy(&gpsWxui);
  } while (0);
  do {
    brws_.iterate_clear(
        [&](const std::string &key, const auto &brw, bool &itclear) {
          if (0 == xs_sys_process_has_exit(brw->GetPid())) {
            client_notifys_.push(std::make_tuple<std::string, std::string>(
                "/close",
                BrowserConfig::CreateBrwCloseNotifyPak(Conv::u8_to_u16(key))));
            brw->Release();
            itclear = true;
          }
        });
  } while (0);
  do {
    const unsigned int notify_port = config_->RouteConfigureGetClientPort();
    if (notify_port <= 0)
      break;
    if (client_notifys_.empty())
      break;
    auto msgs = client_notifys_.pops();
    for (const auto &msg : msgs) {
      std::string path = std::get<0>(msg);
      std::string content = std::get<1>(msg);

      httplib::Client cli("127.0.0.1", notify_port);
      httplib::Headers heads = {{"content-type", "application/json"}};
      auto postRes = cli.Post(path, heads, content.data(), content.size(),
                              "application/json");
      if (!postRes || postRes->status != 200) {
        LOG_ERROR("POST({}) FAIL", path);
      } else {
        LOG_INFO("POST({}) CONTENT({})", path, content);
      }
    }
  } while (0);
}
IConfig *IBrowserInterfaceServer::ConfigGet() const {
  return dynamic_cast<IConfig *>(config_);
}

void IBrowserInterfaceServer::Listen() {
  server_->Post("/server/open", [this](const httplib::Request &req,
                                       httplib::Response &res) {
    std::string repRes;
    OnRequest(RequestType::SERVER_OPEN, req.body, repRes);
    LOG_INFO("REQ({}) BODY({}) RES({})", "/server/open", req.body, repRes);
    res.set_content(repRes.empty() ? "{}" : repRes,
                    "application/json; charset=utf-8");
  });
  server_->Post("/server/close", [this](const httplib::Request &req,
                                        httplib::Response &res) {
    std::string repRes;
    OnRequest(RequestType::SERVER_CLOSE, req.body, repRes);
    LOG_INFO("REQ({}) BODY({}) RES({})", "/server/close", req.body, repRes);
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
  server_->Post("/browser/open", [this](const httplib::Request &req,
                                        httplib::Response &res) {
    browser_configure_cache = req.body;
    std::string repRes;
    OnRequest(RequestType::BROWSER_OPEN, req.body, repRes);
    LOG_INFO("REQ({}) BODY({}) RES({})", "/browser/open", req.body, repRes);
    res.set_content(repRes.empty() ? "{}" : repRes,
                    "application/json; charset=utf-8");
  });
  server_->Post("/browser/close", [this](const httplib::Request &req,
                                         httplib::Response &res) {
    std::string repRes;
    OnRequest(RequestType::BROWSER_CLOSE, req.body, repRes);
    LOG_INFO("REQ({}) BODY({})", "/browser/close", req.body, repRes);
    res.set_content(repRes.empty() ? "{}" : repRes,
                    "application/json; charset=utf-8");
  });
  server_->Post("/browser/activate", [this](const httplib::Request &req,
                                            httplib::Response &res) {
    std::string repRes;
    OnRequest(RequestType::BROWSER_ACTIVATE, req.body, repRes);
    LOG_INFO("REQ({}) BODY({})", "/browser/activate", req.body, repRes);
    res.set_content(repRes.empty() ? "{}" : repRes,
                    "application/json; charset=utf-8");
  });
  server_->Post("/browser/get", [this](const httplib::Request &req,
                                       httplib::Response &res) {
    std::string repRes;
    OnRequest(RequestType::BROWSER_GET, req.body, repRes);
    LOG_INFO("REQ({}) BODY({}) RES({})", "/browser/get", req.body, repRes);
    res.set_content(repRes.empty() ? "{}" : repRes,
                    "application/json; charset=utf-8");
  });

  server_->Post("/browser/get_cache",
                [this](const httplib::Request &req, httplib::Response &res) {
                  std::string repRes;
                  OnRequest(RequestType::BROWSER_GET_CACHE, req.body, repRes);
                  LOG_INFO("REQ({}) BODY({}) RES({})", "/browser/get_cache",
                           req.body, repRes);

                  repRes = browser_configure_cache;
                  res.set_content(repRes.empty() ? "{}" : repRes,
                                  "application/json; charset=utf-8");
                });

  server_->Post("/browser/get_cookies",
                [this](const httplib::Request &req, httplib::Response &res) {
                  std::string repRes;
                  OnRequest(RequestType::BROWSER_COOKIES_GET, req.body, repRes);
                  LOG_INFO("REQ({}) BODY({}) RES({})", "/browser/get_cookies",
                           req.body, repRes);
                  res.set_content(repRes.empty() ? "{}" : repRes,
                                  "application/json; charset=utf-8");
                });
  server_->Post("/browser/set_cookies",
                [this](const httplib::Request &req, httplib::Response &res) {
                  std::string repRes;
                  OnRequest(RequestType::BROWSER_COOKIES_SET, req.body, repRes);
                  LOG_INFO("REQ({}) BODY({}) RES({})", "/browser/set_cookies",
                           req.body, repRes);
                  res.set_content(repRes.empty() ? "{}" : repRes,
                                  "application/json; charset=utf-8");
                });
  server_->Post("/browser/del_cookies",
                [this](const httplib::Request &req, httplib::Response &res) {
                  std::string repRes;
                  OnRequest(RequestType::BROWSER_COOKIES_DEL, req.body, repRes);
                  LOG_INFO("REQ({}) BODY({}) RES({})", "/browser/del_cookies",
                           req.body, repRes);
                  res.set_content(repRes.empty() ? "{}" : repRes,
                                  "application/json; charset=utf-8");
                });
  server_->Post("/system/device", [this](const httplib::Request &req,
                                         httplib::Response &res) {
    std::string repRes;
    OnRequest(RequestType::SYSTEM_DEVICE, req.body, repRes);
    LOG_INFO("REQ({}) BODY({}) RES({})", "/system/device", req.body, repRes);
    res.set_content(repRes.empty() ? "{}" : repRes,
                    "application/json; charset=utf-8");
  });
  server_->Post("/ffx/start_screen_recording",
                [this](const httplib::Request &req, httplib::Response &res) {
                  std::string repRes;
                  OnRequest(RequestType::FFX_START_SCREEN_RECORDING, req.body,
                            repRes);
                  res.set_content(repRes.empty() ? "{}" : repRes,
                                  "application/json; charset=utf-8");
                });
  server_->Post("/ffx/stop_screen_recording",
                [this](const httplib::Request &req, httplib::Response &res) {
                  std::string repRes;
                  OnRequest(RequestType::FFX_STOP_SCREEN_RECORDING, req.body,
                            repRes);
                  res.set_content(repRes.empty() ? "{}" : repRes,
                                  "application/json; charset=utf-8");
                });
  server_->Post("/plugin/ffxui/open",
                [this](const httplib::Request &req, httplib::Response &res) {
                  std::string repRes;
                  OnRequest(RequestType::PLUGIN_FFXUI_OPEN, req.body, repRes);
                  res.set_content(repRes.empty() ? "{}" : repRes,
                                  "application/json; charset=utf-8");
                });
  server_->Post("/plugin/ffxui/close",
                [this](const httplib::Request &req, httplib::Response &res) {
                  std::string repRes;
                  OnRequest(RequestType::PLUGIN_FFXUI_CLOSE, req.body, repRes);
                  res.set_content(repRes.empty() ? "{}" : repRes,
                                  "application/json; charset=utf-8");
                });
  server_->Post("/", [](const httplib::Request &req, httplib::Response &res) {

  });

  config_->RouteConfigureInit(port_);
  server_->listen("127.0.0.1", port_);
}
