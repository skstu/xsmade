#include "config.h"

static wxui::IWxui *gpsWxui = nullptr;
static std::atomic_bool gbWxuiStatus = false;
namespace {
enum class ResponseCode : int {
  Ok = 0x0000,
  SystemError = -0x1100,
  ProcessAlreadyRunning = -0x1110,
  BrwAlreadyRunning = -0x2100,
  FfxAlreadyRunning = -0x3100,
};

static std::map<ResponseCode, std::string> ResponseCodeString = {
    {ResponseCode::Ok, "Ok"},
    {ResponseCode::SystemError, "SystemError"},
    {ResponseCode::ProcessAlreadyRunning, "ProcessAlreadyRunning"},
    {ResponseCode::BrwAlreadyRunning, "BrwAlreadyRunning"},
    {ResponseCode::FfxAlreadyRunning, "FfxAlreadyRunning"},
};

class Response {
public:
  Response(const RequestType &reqType) : reqtype_(reqType) {
  }
  void *operator new(size_t) = delete;
  void operator delete(void *) = delete;
  Response(const Response &) = delete;
  Response &operator=(const Response &) = delete;
  std::string ToJson() const {
    std::string result;
    rapidjson::Document doc(rapidjson::Type::kObjectType);
    doc.AddMember(
        rapidjson::Value().SetString("request_type", doc.GetAllocator()).Move(),
        rapidjson::Value()
            .SetString(
                fmt::format("{:X}", static_cast<unsigned long long>(reqtype_))
                    .c_str(),
                doc.GetAllocator())
            .Move(),
        doc.GetAllocator());
    doc.AddMember(
        rapidjson::Value()
            .SetString("response_code", doc.GetAllocator())
            .Move(),
        rapidjson::Value().SetInt(static_cast<int>(response_code_)).Move(),
        doc.GetAllocator());
    doc.AddMember(
        rapidjson::Value().SetString("message", doc.GetAllocator()).Move(),
        rapidjson::Value()
            .SetString(ResponseCodeString[response_code_].c_str(),
                       doc.GetAllocator())
            .Move(),
        doc.GetAllocator());
    doc.AddMember(
        rapidjson::Value().SetString("result", doc.GetAllocator()).Move(),
        rapidjson::Value().SetString(result.c_str(), doc.GetAllocator()).Move(),
        doc.GetAllocator());
    result = Json::toString(doc);
    return result;
  }
  void SetResponseCode(const ResponseCode &code) {
    response_code_ = code;
  }
  void SetResult(const rapidjson::Document &resultDoc) {
    result = "{}";
    do {
      if (!resultDoc.IsObject() && !resultDoc.IsArray())
        break;
      if (resultDoc.IsObject())
        if (resultDoc.ObjectEmpty())
          break;
      if (resultDoc.IsArray())
        if (resultDoc.Empty())
          break;
      result = Json::toString(resultDoc);
    } while (0);
  }

private:
  std::string result;
  ResponseCode response_code_ = ResponseCode::SystemError;
  const RequestType reqtype_;
  ~Response() {
  }
};
} // namespace

Server::Server() {
  Init();
}

Server::~Server() {
  UnInit();
}
void Server::Release() const {
  delete this;
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
    if (Config::ConfigGet()->GetSettings().developer.enable) {
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
void Server::Stop() {
  do {
    if (!open_.load())
      break;
    if (gpsWxui) {
      gpsWxui->Stop();
      wxui::IWxui::Destroy(&gpsWxui);
      gpsWxui = nullptr;
    }
    open_.store(false);
    server_->stop();
    for (auto &t : threads_)
      t.join();
    threads_.clear();
  } while (0);
}
void Server::Process() {
  do { //!@ plugin - ffx
    if (gbWxuiStatus)
      break;
    if (!gpsWxui)
      break;
    gpsWxui->Stop();
    wxui::IWxui::Destroy(&gpsWxui);
  } while (0);
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

  case RequestType::FFX_START_SCREEN_RECORDING: {
#if 0
    Components::Component *pComp = Components::Get()->GetComp(u"ffx");
    if (!pComp)
      break;

    ffx::FFXArgs ffxArgs(ffx::tfFFXArgs{
        {0, {"-y", ""}},
        {1, {"-f", "gdigrab"}},
        {2, {"-video_size", "640x480"}},
        {3, {"-offset_x", "0"}},
        {4, {"-offset_y", "0"}},
        {5, {"-framerate", "15"}},
        {6, {"-i", "desktop"}},
        {7, {"-t", "30"}},
        {8, {"-r", "20"}},
        {9, {"-vcodec", "libx264"}},
        {10, {"-s", "640x480"}},
        {11, {"-b:v", "10000"}},
        {12, {"-crf", "24"}},
        {13, {"-pix_fmt", "yuv420p"}},
        {14, {"-preset:v", "veryfast"}},
        {15, {"-tune:v", "zerolatency"}},
        {16, {"-xs-outfile", "test_yuv420p_x264.mp4"}},
    });

    /*
"args": {
        "-video_size": "640x480",
        "-offset_x": "0",
        "-offset_y": "0",
        "-framerate": "15",
        "-vcodec": "libx264",
        "-s": "640x480",
        "-xs-out": "screen_recording_x264_test.mp4"
    }
*/
    rapidjson::Document doc;
    do {
      if (doc.Parse(body.data(), body.size()).HasParseError())
        break;
      if (!doc.HasMember("args") || !doc["args"].IsObject())
        break;
      if (doc["args"].ObjectEmpty())
        break;
      for (auto it = doc["args"].MemberBegin(); it != doc["args"].MemberEnd();
           ++it) {
        do {
          if (!it->value.IsString() || !it->name.IsString())
            break;
          ffxArgs.Push(it->name.GetString(), it->value.GetString());
        } while (0);
      }
    } while (0);

    pComp->Create(ffxArgs.GetArgs(), false);
#endif
  } break;
  case RequestType::FFX_STOP_SCREEN_RECORDING: {
#if 0
    Components::Component *pComp = Components::Get()->GetComp(u"ffx");
    if (!pComp)
      break;
    pComp->Destroy();
#endif
  } break;
  case RequestType::PLUGIN_FFXUI_OPEN: {
    bool success = false;
    do {
      if (gbWxuiStatus.load())
        break;
      if (!gpsWxui) {
        gpsWxui = wxui::IWxui::Create(
            (Config::ConfigGet()->PathGet().plugins_dir + "/wxui.dll").c_str());
      }
      if (!gpsWxui)
        break;
      gpsWxui->ConfigGet()->SetResourceDir(
          (Config::ConfigGet()->PathGet().resources_dir + "/ffxui/").c_str());
      gpsWxui->ConfigGet()->SetFrameType(wxui::FrameType::SHAPEFRAME);
      gpsWxui->ConfigGet()->RegisterSystemExitCb(
          [](void *route) { gbWxuiStatus.store(false); }, this);
      gpsWxui->ConfigGet()->RegisterRecordingStartCb(
          [](const wxui::IRecordingArgs *args, void *route) {
            std::string size =
                fmt::format("{}x{}", args->GetCX(), args->GetCY());
#if defined(DEBUG)
            std::string outfile = fmt::format(
                R"(C:\Users\k34ub\AppData\Roaming\MarsProjects\userdata\{}.mp4)",
                stl::Time::TimeStamp<std::chrono::microseconds>());
#else
            std::string outfile = fmt::format(
                "{}/{}.mp4",
                Config::ConfigGet()->PathGet().chromium_user_data_dir,
                stl::Time::TimeStamp<std::chrono::microseconds>());
#endif
            ffx::FFXArgs ffxArgs(ffx::tfFFXArgs{
                {0, {"-y", ""}},
                {1, {"-f", "gdigrab"}},
                {2, {"-video_size", size}},
                {3, {"-offset_x", std::to_string(args->GetX())}},
                {4, {"-offset_y", std::to_string(args->GetY())}},
                {5, {"-framerate", "15"}},
                {6, {"-i", "desktop"}},
                {7, {"-t", "102400"}},
                {8, {"-r", "20"}},
                {9, {"-vcodec", "libx264"}},
                {10, {"-s", size}},
                {11, {"-b:v", "10000"}},
                {12, {"-crf", "24"}},
                {13, {"-pix_fmt", "yuv420p"}},
                {14, {"-preset:v", "veryfast"}},
                {15, {"-tune:v", "zerolatency"}},
                {16, {"-xs-outfile", stl::Path::Mormalize(outfile)}},
            });

            IComponent *pComp = Components::Get()->GetComp(u"ffmpeg");
            if (pComp) {
              pComp->Start(ffxArgs.GetArgs(), false);
            }
          },
          this);
      gpsWxui->ConfigGet()->RegisterRecordingStopCb(
          [](void *route) {
            IComponent *pComp = Components::Get()->GetComp(u"ffmpeg");
            if (pComp) {
              pComp->Stop();
            }
          },
          this);
      gpsWxui->Start();
      gbWxuiStatus.store(true);
    } while (0);
    auto ss = 0;
  } break;
  case RequestType::PLUGIN_FFXUI_CLOSE: {
    if (!gpsWxui)
      break;
    gpsWxui->Stop();
    wxui::IWxui::Destroy(&gpsWxui);
    gpsWxui = nullptr;
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

  Config::ConfigGet()->RouteConfigureInit(port_);
  server_->listen("127.0.0.1", port_);
}
