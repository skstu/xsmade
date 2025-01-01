#include <perform.h>

void IBrowserInterfaceServer::OnRequest(const RequestType &reqType,
                                        const std::string &body,
                                        std::string &res) {
  Response repObj(reqType);
  rapidjson::Document resDoc(rapidjson::Type::kObjectType);

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
    resDoc.AddMember(
        rapidjson::Value().SetString("brwonline", resDoc.GetAllocator()),
        onlines, resDoc.GetAllocator());
    repObj.SetResponseCode(ResponseCode::Ok);
    repObj.SetResult(resDoc);
  } break;
  case RequestType::SERVER_CLOSE: {
    std::exit(3762);
  } break;
  case RequestType::BROWSER_OPEN: {
    Browser *brw = new Browser(body);
    auto exist = brws_.search(brw->GetKey());
    if (exist) {
      rapidjson::Value brwObj(rapidjson::Type::kObjectType);
      brwObj.AddMember(
          rapidjson::Value().SetString("pid", resDoc.GetAllocator()).Move(),
          rapidjson::Value().SetInt64((*exist)->GetPid()).Move(),
          resDoc.GetAllocator());
      brwObj.AddMember(
          rapidjson::Value().SetString("key", resDoc.GetAllocator()).Move(),
          rapidjson::Value()
              .SetString((*exist)->GetKey().c_str(), resDoc.GetAllocator())
              .Move(),
          resDoc.GetAllocator());
      resDoc.AddMember(
          rapidjson::Value().SetString("brw", resDoc.GetAllocator()), brwObj,
          resDoc.GetAllocator());
      repObj.SetResponseCode(ResponseCode::BrwAlreadyRunning);
      brw->Release();
      break;
    }
    bool result = brw->Open();
    if (result) {
      brws_.push(brw->GetKey(), brw);

      rapidjson::Value brwObj(rapidjson::Type::kObjectType);
      brwObj.AddMember(
          rapidjson::Value().SetString("pid", resDoc.GetAllocator()).Move(),
          rapidjson::Value().SetInt64(brw->GetPid()).Move(),
          resDoc.GetAllocator());
      brwObj.AddMember(
          rapidjson::Value().SetString("key", resDoc.GetAllocator()).Move(),
          rapidjson::Value()
              .SetString(brw->GetKey().c_str(), resDoc.GetAllocator())
              .Move(),
          resDoc.GetAllocator());
      resDoc.AddMember(
          rapidjson::Value().SetString("brw", resDoc.GetAllocator()), brwObj,
          resDoc.GetAllocator());
      repObj.SetResponseCode(ResponseCode::Ok);
    } else {
      repObj.SetResponseCode(ResponseCode::BrwCreateError);
      brw->Close();
      brw->Release();
    }
  } break;
  case RequestType::BROWSER_CLOSE: {
    std::string key;
    do {
      rapidjson::Document doc;
      if (doc.Parse(body.data(), body.size()).HasParseError())
        break;
      if (!doc.HasMember("rule") || !doc["rule"].IsObject())
        break;
      if (!doc["rule"].HasMember("key") || !doc["rule"]["key"].IsString())
        break;
      key = doc["rule"]["key"].GetString();
    } while (0);

    if (key.empty()) {
      repObj.SetResponseCode(ResponseCode::BrwKeyError);
      break;
    }
    rapidjson::Value brwObj(rapidjson::Type::kObjectType);
    auto found =
        brws_.search(key, [&](const std::string &key, const auto &brw) {
          brw->Close();
          brwObj.AddMember(
              rapidjson::Value().SetString("pid", resDoc.GetAllocator()).Move(),
              rapidjson::Value().SetInt64(brw->GetPid()).Move(),
              resDoc.GetAllocator());
          brwObj.AddMember(
              rapidjson::Value().SetString("key", resDoc.GetAllocator()).Move(),
              rapidjson::Value()
                  .SetString(brw->GetKey().c_str(), resDoc.GetAllocator())
                  .Move(),
              resDoc.GetAllocator());
        });
    auto pop = brws_.pop(key);
    if (pop) {
      (*pop)->Release();
    }
    if (found) {
      resDoc.AddMember(
          rapidjson::Value().SetString("brw", resDoc.GetAllocator()), brwObj,
          resDoc.GetAllocator());
      repObj.SetResponseCode(ResponseCode::Ok);
      client_notifys_.push(std::make_tuple<std::string, std::string>(
          "/close",
          BrowserConfig::CreateBrwCloseNotifyPak(Utfpp::u8_to_u16(key))));
    } else {
      repObj.SetResponseCode(ResponseCode::BrwNotfound);
    }
  } break;
  case RequestType::BROWSER_GET: {
    rapidjson::Value brwObjs(rapidjson::Type::kArrayType);
    std::map<std::u16string, std::u16string> dirs, files;
    stl::Directory::EnumU16(config_->PathGet().chromium_dir, dirs, files,
                            false);
    for (const auto &node : dirs) {
      brwObjs.PushBack(rapidjson::Value()
                           .SetString(Utfpp::u16_to_u8(node.first).c_str(),
                                      resDoc.GetAllocator())
                           .Move(),
                       resDoc.GetAllocator());
    }
    resDoc.AddMember(rapidjson::Value()
                         .SetString("chromium_versions", resDoc.GetAllocator())
                         .Move(),
                     brwObjs, resDoc.GetAllocator());
    repObj.SetResponseCode(ResponseCode::Ok);
  } break;
  case RequestType::BROWSER_COOKIES_DEL:
  case RequestType::BROWSER_COOKIES_SET:
  case RequestType::BROWSER_COOKIES_GET: {
    Configure cfg(body);
    std::string key = cfg.rule_.key;
    bool verfiy = false;
    do {
      if (key.empty())
        break;
      if (cfg.cookies_.sequence <= 0)
        break;
      if (cfg.cookies_.action.empty())
        break;
      if (cfg.cookies_.type.empty())
        break;
      verfiy = true;
    } while (0);
    if (!verfiy) {
      repObj.SetResponseCode(ResponseCode::BrwCookieReqError);
      break;
    }
    std::string cookies_reqData = cfg.cookies_.GetCookiesRequest();
    std::u16string path =
        config_->GetXSCacheRouteReqsDir(Utfpp::u8_to_u16(key)) + u"/" +
        Utfpp::u8_to_u16(std::to_string(cfg.cookies_.sequence));
    stl::File::WriteFile(path, cookies_reqData);
    repObj.SetResponseCode(ResponseCode::Done);
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
#if 0
    bool success = false;
    do {
      if (gbWxuiStatus.load())
        break;
      if (!gpsWxui) {
        gpsWxui = wxui::IWxui::Create(
            (Utfpp::u16_to_u8(config_->PathGet().plugins_dir) + "/wxui.dll")
                .c_str());
      }
      if (!gpsWxui)
        break;
      gpsWxui->ConfigGet()->SetResourceDir(
          (Utfpp::u16_to_u8(config_->PathGet().resources_dir) + "/ffxui/")
              .c_str());
      gpsWxui->ConfigGet()->SetFrameType(wxui::FrameType::SHAPEFRAME);
      gpsWxui->ConfigGet()->RegisterSystemExitCb(
          [](void *route) { gbWxuiStatus.store(false); }, this);
      gpsWxui->ConfigGet()->RegisterRecordingStartCb(
          [](const wxui::IRecordingArgs *args, void *route) {
            IBrowserInterfaceServer *__this =
                reinterpret_cast<IBrowserInterfaceServer *>(route);
            std::string size =
                fmt::format("{}x{}", args->GetCX(), args->GetCY());
#if defined(DEBUG)
            std::string outfile = fmt::format(
                R"(C:\Users\k34ub\AppData\Roaming\MarsProjects\userdata\{}.mp4)",
                stl::Time::TimeStamp<std::chrono::microseconds>());
#else
            std::string outfile = fmt::format(
                "{}/{}.mp4",
                Utfpp::u16_to_u8(
                    __this->config_->PathGet().chromium_user_data_dir),
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
                {16, {"-xs-outfile", stl::Path::Normalize(outfile)}},
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
#endif
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

  repObj.SetReqBody(body);
  repObj.SetResult(resDoc);
  res = repObj.GetResult();
}
