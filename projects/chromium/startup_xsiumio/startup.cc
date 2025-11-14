#include "config.h"
Startup::Startup(const RunMode &mode) : mode_(mode) {
  Init();
}
Startup::~Startup() {
  UnInit();
}
void Startup::Init() {
  do {
    switch (mode_) {
    case RunMode::kModeService: {
      model_ = dynamic_cast<IModel *>(new ModelLevel0());
    } break;
    case RunMode::kModelLevel0: {
      model_ = dynamic_cast<IModel *>(new ModelLevel0());
    } break;
    // case RunMode::kModelLevel1: {
    //   model_ = dynamic_cast<IModel *>(new ModelLevel1());
    // } break;
    // case RunMode::kModelLevel2: {
    //   model_ = dynamic_cast<IModel *>(new ModelLevel2());
    // } break;
    // case RunMode::kModelLevel3: {
    //   model_ = dynamic_cast<IModel *>(new ModelLevel3());
    // } break;
    default:
      break;
    }
  } while (0);
}
void Startup::UnInit() {
  if (model_)
    model_->Release();
  Comps::Destroy();
}
void Startup::Request(chromium::IRequest *req) {
  std::lock_guard<std::mutex> lck(*mtx_);
  requests_.push(req);
}
void Startup::Run() {
  Client::CreateOrGet()->Start();
  Server::CreateOrGet();
  std::thread([this]() {
    bool needStop = true;
    std::time_t curr_time = stl::Time::TimeStamp<std::chrono::seconds>();
    std::time_t next_time = curr_time;
    std::time_t prev_time = next_time;
    std::time_t prev_time_chromium_check = 0;
    const std::time_t time_chromium_check_interval = 3;        // 3 seconds
    const std::time_t chromium_running_timeout_ms = 1000 * 60; // 1 minutes
    std::time_t chromium_startup_time_ms = 0;
    do {
      curr_time = stl::Time::TimeStamp<std::chrono::seconds>();

      do { //!@ Server
        if (Server::CreateOrGet()->Ready())
          break;
        if (!Server::CreateOrGet()->Start())
          break;
        if (model_)
          model_->LoadModelParts();
        Comps::CreateOrGet()->Start();
        std::unique_lock<std::mutex> lck(*mtx_, std::defer_lock);
        lck.lock();
        ready_.store(true);
        lck.unlock();
        needStop = false;
      } while (0);

      do {
        if (RunMode::kModeService == mode_)
          break;
        next_time = stl::Time::TimeStamp<std::chrono::seconds>();
        if (next_time - prev_time >= 10) {
          model_->FinishModelParts();
          prev_time = next_time;
        }
      } while (0);

      do {
        if (RunMode::kModeService == mode_)
          break;
        if (chromium_startup_time_ms > 0) {
          if (stl::Time::TimeStamp<std::chrono::milliseconds>() -
                  chromium_startup_time_ms >=
              chromium_running_timeout_ms) {
            model_->SetModelResult(false);
            Browser::CreateOrGet()->ClearChromium();
          }
        }
        if (Browser::CreateOrGet()->IsIdle()) {
          chromium_startup_time_ms =
              stl::Time::TimeStamp<std::chrono::milliseconds>();
          Browser::CreateOrGet()->SetStatus(BrowserStatus::kStarting);
          // model_->GenModel();
          // Browser::CreateOrGet()->CreateChromium(model_->GetXSCfg());
          std::string cfgBuffer = stl::File::ReadFile(
              Config::CreateOrGet()->GetProjectConfiguresDir() + "/" +
              chromium::xsiumio::kObjectKey + ".json");
          chromium::IRequest *reqObj = new chromium::IRequest(cfgBuffer);
          Startup::GetOrCreate()->Request(reqObj);
        }
      } while (0);

      do {
        // if (RunMode::kModeService != mode_)
        //   break;
        if (!Server::CreateOrGet()->Ready())
          break;
        if (requests_.empty())
          break;
        auto reqs = requests_.pops();
        for (auto &req : reqs) {
          std::unique_lock<std::mutex> lck(*mtx_, std::defer_lock);
          lck.lock();
          do {
            if (!ready_.load()) {
              req->SetErrorCode(chromium::ErrorCode::ServiceNotReady);
              break;
            }
            switch (req->GetRequestType()) {
            case chromium::xsiumio::RequestType::kCreateBrowser: {
              chromium::xsiumio::IXSiumio &cfg = req->GetConfig();
              model_->SettingBridgeProxy(cfg);
              xs_process_id_t bridgePid = 0;
              if (cfg.bridge.enable) {
                std::vector<const char *> startup_args{
                    model_->GetBridgeStartupArgs().c_str(), nullptr};
                xs_sys_process_spawn(
                    Config::CreateOrGet()->GetBridgeProcessPath().c_str(),
                    &startup_args[0], nullptr, 1, &bridgePid);
              }
              if (!ConfigDynamicInfo(cfg.dynFpsUrl.empty()
                                         ? "https://myip.ipipv.com"
                                         : cfg.dynFpsUrl,
                                     model_->GetProxyStringForCurl(), cfg)) {
                Browser::CreateOrGet()->SetStatus(BrowserStatus::kIdle);
                break;
              }
              model_->GenModel(cfg);

              if (first_run_.load() || !cfg.policy.reuse ||
                  !model_->GetModelResult()) {
                model_->GenRouteConfigure(cfg);
              }
              IChromium *chromium = Browser::CreateOrGet()->CreateChromium(req);
              if (bridgePid > 0 && chromium) {
                chromium->SetBridgePid(bridgePid);
              }
            } break;
            case chromium::xsiumio::RequestType::kDestroyBrowser: {
              Browser::CreateOrGet()->DestroyChromium(req);
            } break;
            case chromium::xsiumio::RequestType::kResetBrowser: {
              Browser::CreateOrGet()->ResetChromium(req);
            } break;
            case chromium::xsiumio::RequestType::kChromiumInit: {
              Browser::CreateOrGet()->CreateChromiumResult(req);
            } break;
            case chromium::xsiumio::RequestType::kServiceAsyncNotify: {
              auto xx = 0;
            } break;
            default:
              break;
            }
          } while (0);
          lck.unlock();
          Client::Packet resPak;
          req->SetRequestType(
              chromium::xsiumio::RequestType::kServiceAsyncNotify);
          resPak.target_port = req->GetConfig().server.port;
          resPak.target_host = req->GetConfig().server.host;
          resPak.body = req->GetResponse();
          Client::CreateOrGet()->Post(resPak);
          req->Release();
        }
      } while (0);

      do {
        if (RunMode::kModeService != mode_)
          break;
        if (!Server::CreateOrGet()->Ready())
          break;
        if (prev_time_chromium_check <= 0) {
          prev_time_chromium_check = curr_time;
          break;
        }
        if (curr_time - prev_time_chromium_check < time_chromium_check_interval)
          break;
        prev_time_chromium_check = curr_time;

        Browser::CreateOrGet()->CheckChromium([this](IChromium *chromium) {
          bool result = true;
          do {
            if (0 == xs_sys_process_already_exists(chromium->GetPid()))
              break;
            result = false;
          } while (0);
          return result;
        });
      } while (0);

      if (needStop)
        break;

      //       time_t start_time = GetChromiumStartTime();
      //       if ((start_time > 0) &&
      //           (stl::Time::TimeStamp<std::chrono::seconds>() - start_time >=
      //            kChromiumTimeout)) {
      // #if _DEBUG
      //         const std::string log_message =
      //             "Chromium process has not started within the timeout
      //             period.";
      //         std::cout << "[" << stl::Time::GetLogTimeCN() << "] " <<
      //         log_message
      //                   << std::endl;
      //         LOG_INFO("{}", log_message);
      // #endif
      //         ChromiumClose();
      //       }
      if (first_run_.load()) {
        first_run_.store(false);
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } while (1);
  }).join();
  Client::CreateOrGet()->Stop();
  Server::CreateOrGet()->Stop();
  Client::Destroy();
  Server::Destroy();
}
bool Startup::Ready() const {
  return ready_.load();
}
bool Startup::ConfigDynamicInfo(const std::string &url,
                                const std::string &proxyString,
                                chromium::xsiumio::IXSiumio &out) const {
  bool result = false;
  std::string dynamic_info;
#if 1 //_DEBUG
  LOG_INFO("ConfigDynamicInfo: {}", proxyString);
  std::cout << "ConfigDynamicInfo: "
            << (proxyString.empty() ? "localhost" : proxyString) << std::endl;
#endif

  do {
    if (url.empty())
      break;
    auto pCurl =
        Comps::CreateOrGet()->GetComp<curl::ICurl>(Comps::CompKey::kCurl);
    if (!pCurl)
      break;
    if (!pCurl) {
      LOG_ERROR("Failed to cast ICurl component.");
      std::cout << "Failed to cast ICurl component." << std::endl;
      break;
    }
    auto reqArray = pCurl->CreateRequestArray();
    auto reqMyip = pCurl->CreateRequest();
    reqMyip->SetUrl(url.c_str());
    if (!proxyString.empty()) {
      reqMyip->SetProxyString(
          proxyString.c_str(),
          proxyString.find("@") != std::string::npos ? true : false);
    }
    reqArray->Push(reqMyip);
    curl::ICurl::IRequestArray *resArrsy = pCurl->Perform(reqArray);
    for (size_t i = 0; i < resArrsy->Total(); ++i) {
      curl::ICurl::IRequest *req = resArrsy->Next(i);
      if (!req)
        continue;
      if (req->GetResponseCode()) {
        int code = req->GetResponseCode();
        LOG_ERROR("Request failed with code: {}", code);
        std::cout << "Request failed with code: " << code << std::endl;
        continue;
      }
      char *response = nullptr;
      size_t response_size = 0;
      req->GetResponse(&response, &response_size);
      dynamic_info.clear();
      dynamic_info.append(response, response_size);
      pCurl->Free((void **)&response);
      result = true;
      break;
    }
    if (resArrsy)
      resArrsy->Release();
  } while (0);

  do {
    if (!result)
      break;
    rapidjson::Document doc;
    if (doc.Parse(dynamic_info.data(), dynamic_info.size()).HasParseError())
      break;
    if (!doc.IsObject())
      break;

    if (url.find("myip.ipccr.com") != std::string::npos ||
        url.find("myip.ipipv.com") != std::string::npos) {
      /*
{
  "Continent": "",
  "ContinentEn": "",
  "Country": "美国",
  "CountryEnglish": "United States of America",
  "CountryCode": "US",
  "Province": "加利福尼亚",
  "ProvinceEn": "California",
  "City": "Santa Clara",
  "CityEn": "Santa Clara",
  "District": "",
  "AreaCode": "",
  "ISP": "",
  "Longitude": "-121.955490",
  "Latitude": "37.354111",
  "LocalTime": "America/Los_Angeles",
  "Elevation": "0.000000",
  "WeatherStation": "",
  "ZipCode": "95052",
  "CityCode": "",
  "Asn": "",
  "Ip": "43.135.180.117",
  "db": "ip2location"
}
*/
      if (doc.HasMember("Ip") && doc["Ip"].IsString()) {
        out.dynFpsInfo.ipinfo.ip = doc["Ip"].GetString();
      }
      if (doc.HasMember("LocalTime") && doc["LocalTime"].IsString()) {
        out.dynFpsInfo.ipinfo.timezone = doc["LocalTime"].GetString();
      }
      if (doc.HasMember("CityEn") && doc["CityEn"].IsString()) {
        out.dynFpsInfo.ipinfo.city = doc["CityEn"].GetString();
      }
      if (doc.HasMember("CountryEnglish") && doc["CountryEnglish"].IsString()) {
        out.dynFpsInfo.ipinfo.country = doc["CountryEnglish"].GetString();
      }
      if (doc.HasMember("ProvinceEn") && doc["ProvinceEn"].IsString()) {
        out.dynFpsInfo.ipinfo.region = doc["ProvinceEn"].GetString();
      }
      if (doc.HasMember("Longitude") && doc["Longitude"].IsNumber()) {
        out.dynFpsInfo.ipinfo.lon =
            std::to_string(doc["Longitude"].GetDouble());
      }
      if (doc.HasMember("Latitude") && doc["Latitude"].IsNumber()) {
        out.dynFpsInfo.ipinfo.lat = std::to_string(doc["Latitude"].GetDouble());
      }
    } else if (url.find("ip-api.com/") != std::string::npos) {
      /*
{
  "status": "success",
  "country": "China",
  "countryCode": "CN",
  "region": "ZJ",
  "regionName": "Zhejiang",
  "city": "Hangzhou",
  "zip": "",
  "lat": 30.2943,
  "lon": 120.1663,
  "timezone": "Asia/Shanghai",
  "isp": "Chinanet",
  "org": "",
  "as": "AS4134 CHINANET-BACKBONE",
  "query": "125.118.223.0"
}
      */
      if (doc.HasMember("query") && doc["query"].IsString()) {
        out.dynFpsInfo.ipinfo.ip = doc["query"].GetString();
      }
      if (doc.HasMember("timezone") && doc["timezone"].IsString()) {
        out.dynFpsInfo.ipinfo.timezone = doc["timezone"].GetString();
      }
      if (doc.HasMember("city") && doc["city"].IsString()) {
        out.dynFpsInfo.ipinfo.city = doc["city"].GetString();
      }
      if (doc.HasMember("country") && doc["country"].IsString()) {
        out.dynFpsInfo.ipinfo.country = doc["country"].GetString();
      }
      if (doc.HasMember("isp") && doc["isp"].IsString()) {
        out.dynFpsInfo.ipinfo.isp = doc["isp"].GetString();
      }
      if (doc.HasMember("lat") && doc["lat"].IsNumber()) {
        out.dynFpsInfo.ipinfo.lat = std::to_string(doc["lat"].GetDouble());
      }
      if (doc.HasMember("lon") && doc["lon"].IsNumber()) {
        out.dynFpsInfo.ipinfo.lon = std::to_string(doc["lon"].GetDouble());
      }
      if (doc.HasMember("region") && doc["region"].IsString()) {
        out.dynFpsInfo.ipinfo.region = doc["region"].GetString();
      }
    } else if (url.find("ipinfo.io") != std::string::npos) {
      /*
{
  "ip": "125.118.223.0",
  "city": "Hangzhou",
  "region": "Zhejiang",
  "country": "CN",
  "loc": "30.2936,120.1614",
  "org": "AS4134 CHINANET-BACKBONE",
  "postal": "310000",
  "timezone": "Asia/Shanghai",
  "readme": "https://ipinfo.io/missingauth"
}
*/
      if (doc.HasMember("ip") && doc["ip"].IsString()) {
        out.dynFpsInfo.ipinfo.ip = doc["ip"].GetString();
      }
      if (doc.HasMember("timezone") && doc["timezone"].IsString()) {
        out.dynFpsInfo.ipinfo.timezone = doc["timezone"].GetString();
      }
      if (doc.HasMember("city") && doc["city"].IsString()) {
        out.dynFpsInfo.ipinfo.city = doc["city"].GetString();
      }
      if (doc.HasMember("country") && doc["country"].IsString()) {
        out.dynFpsInfo.ipinfo.country = doc["country"].GetString();
      }
      if (doc.HasMember("loc") && doc["loc"].IsString()) {
        std::string loc = doc["loc"].GetString();
        std::vector<std::string> locParts = stl::String::StringSplit(loc, ",");
        if (locParts.size() == 2) {
          out.dynFpsInfo.ipinfo.lat = locParts[0];
          out.dynFpsInfo.ipinfo.lon = locParts[1];
        }
      }
    } else {
      LOG_ERROR("Unknown URL for dynamic info: {}", url.c_str());
      std::cout << "Unknown URL for dynamic info: " << url << std::endl;
      break;
    }
  } while (0);

  out.webrtcIPHandling.public_ip = out.dynFpsInfo.ipinfo.ip;

#if _DEBUG
  const std::string log =
      fmt::format("DynFpsInfo: tz={}, ip={}", out.dynFpsInfo.ipinfo.timezone,
                  out.dynFpsInfo.ipinfo.ip);
  LOG_INFO("{}", log);
  std::cout << log << std::endl;
#endif
  return result;
}
void Startup::NotifyRequestResult(const std::string &body) {
  int result = 0;
  do {
    if (!model_)
      break;
    rapidjson::Document doc;
    if (doc.Parse(body.data(), body.size()).HasParseError())
      break;
    if (doc.IsObject()) {
      if (doc.HasMember("result") && doc["result"].IsInt()) {
        result = doc["result"].GetInt();
      }
    } else if (doc.IsArray()) {
      if (doc.Size() > 0 && doc[0].IsObject()) {
        if (doc[0].HasMember("result") && doc[0]["result"].IsInt()) {
          result = doc[0]["result"].GetInt();
        }
      }
    }
    model_->SetModelResult(result);
#if ENABLE_DEVELOP_MODE3
    std::cout << "NotifyRequestResult: result = " << result << std::endl;
#endif
    if (!result)
      break;
    // std::string mode_filename =
    //     std::to_string(stl::Time::TimeStamp<std::chrono::microseconds>()) +
    //     ".mode";
    // rapidjson::Document modeDoc(rapidjson::Type::kObjectType);
    // xsiumio >> modeDoc;
    // std::string buffer = Json::toString(modeDoc);
    // stl::File::WriteFile(Config::CreateOrGet()->GetProjectModelPartsDir() +
    //                          "/" + mode_filename,
    //                      buffer);
    // model_->SetModelCache(buffer);

    auto sss = 0;
  } while (0);
  Browser::CreateOrGet()->ClearChromium();
}
/////////////////////////////////////////////////////////////////////
Startup *__gpsStartup = nullptr;
Startup *Startup::GetOrCreate(const RunMode &mode) {
  if (!__gpsStartup)
    __gpsStartup = new Startup(mode);
  return __gpsStartup;
}
void Startup::Destroy() {
  if (__gpsStartup) {
    delete __gpsStartup;
    __gpsStartup = nullptr;
  }
}