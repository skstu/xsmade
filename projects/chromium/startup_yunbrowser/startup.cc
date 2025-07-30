#include "config.h"
static std::mutex __mtx__;
Startup::Startup(const RunMode &mode) : mode_(mode) {
  Init();
}
Startup::~Startup() {
  UnInit();
}
chromium::xsiumio::IFpsdb *Startup::GetFpsdb() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return fpsdb_;
}
void Startup::Init() {
  do {
    std::string current_path = Config::CreateOrGet()->GetCurrentDir();
    std::string target_component_path, target_fpsdb_path;
    target_fpsdb_path = current_path + "/fpsdb.json";
    fpsdb_ = new chromium::xsiumio::IFpsdb();
    if (stl::File::Exists(target_fpsdb_path)) {
      *fpsdb_ << stl::File::ReadFile(target_fpsdb_path);
    }
#if _DEBUG
    target_component_path = current_path + "/components/libcurlcc.dll";
#else
    target_component_path = current_path + "/libcurlcc.dll";
#endif
    if (stl::File::Exists(target_component_path)) {
      pComponentCurl_ = curl::ICurl::Create(target_component_path.c_str());
    }
    server_ = new Server();
    switch (mode_) {
    case RunMode::kModelLevel0: {
      model_ = dynamic_cast<IModel *>(new ModelLevel0());
    } break;
    case RunMode::kModelLevel1: {
      model_ = dynamic_cast<IModel *>(new ModelLevel1());
    } break;
    case RunMode::kModelLevel2: {
      model_ = dynamic_cast<IModel *>(new ModelLevel2());
    } break;
    case RunMode::kModelLevel3: {
      model_ = dynamic_cast<IModel *>(new ModelLevel3());
    } break;
    default:
      break;
    }
    std::cout << "Use model: " << model_->GetModelIdentify() << std::endl;
    LOG_INFO("Use model: {}", model_->GetModelIdentify());
    ready_.store(true);
  } while (0);
}
void Startup::UnInit() {
  if (server_) {
    server_->Stop();
  }
  SK_DELETE_PTR(server_);
  curl::ICurl::Destroy(&pComponentCurl_);
  if (model_)
    model_->Release();
  if (fpsdb_)
    fpsdb_->Release();
  ready_.store(false);
}
std::time_t Startup::GetChromiumStartTime() const {
  std::time_t result = 0;
  std::unique_lock<std::mutex> lck(__mtx__, std::defer_lock);
  lck.lock();
  result = chromium_start_time_;
  lck.unlock();
  return result;
}
void Startup::ChromiumClose() {
  std::unique_lock<std::mutex> lck(__mtx__, std::defer_lock);
  lck.lock();
  if (chromium_main_pid_.load() != 0) {
    xs_process_id_t pid = 0;
    // xs_sys_process_kill(chromium_main_pid_.load(), 0);
    xs_sys_process_kill_name("YunBrowser.exe", &pid);
    chromium_main_pid_.store(0);
  }
  chromium_start_time_ = 0;
  lck.unlock();
}
void Startup::GenerateDynamicProxyInfo(std::string &chromium,
                                       std::string &curl) const {
  int session_id = stl::Random::GetRandomValue<int>(100000000, 999999999);
  std::ostringstream oss;
  oss << "4412679-3737a568-US-session-" << session_id;
  const std::string username = oss.str();
  const std::string password = "3871a960";
  const std::string host = "gate-hk.kkoip.com";
  const int port = 16586;
  const std::string proxy_string =
      username + ":" + password + "@" + host + ":" + std::to_string(port);
  curl = "socks5h://" + proxy_string;
  chromium = "socks5://" + proxy_string;
}
void Startup::ConfigureBegin() {
  do {
#if _DEBUG
    const std::string xsiumio_path =
        Config::CreateOrGet()->GetProjectCacheDir() + "/../" +
        chromium::xsiumio::kObjectKey + ".json";
#else
    const std::string xsiumio_path = Config::CreateOrGet()->GetCurrentDir() +
                                     "\\" + chromium::xsiumio::kObjectKey +
                                     ".json";
#endif
    std::string xsiumio_buffer;
    xsiumio << stl::File::ReadFile(xsiumio_path);
    std::string udd_path =
        stl::Path::Normal(Config::CreateOrGet()->GetProjectCacheDir() + "/udd");
    Config::CreateOrGet()->SetChromiumUserDataDir(udd_path);
    if (xsiumio.startup.enable_cleanup_udd) {
      try {
        stl::Directory::RemoveAll(udd_path);
      } catch (const std::exception &e) {
        std::cout << "Error removing directory: " << e.what() << std::endl;
        LOG_WARN("Error removing directory: %s", e.what());
      }
    }
    stl::Directory::Create(udd_path);
#if _DEBUG
    stl::File::WriteFile(Config::CreateOrGet()->GetProjectCacheDir() + "/../" +
                             chromium::yunlogin::kFilenameUdd,
                         udd_path);
#else
    stl::File::WriteFile(Config::CreateOrGet()->GetCurrentDir() + "/" +
                             chromium::yunlogin::kFilenameUdd,
                         udd_path);
#endif
  } while (0);
}
void Startup::ConfigureEnd() {
  do {
    std::string chromium_proxy_string, curl_proxy_string;
    GenerateDynamicProxyInfo(chromium_proxy_string, curl_proxy_string);
    LOG_INFO("Proxy: {}", chromium_proxy_string);
    ConfigDynamicInfo(R"(http://ip-api.com/json)", curl_proxy_string, xsiumio);
    xsiumio.proxy.credentials_url = chromium_proxy_string;
    chromium::yunlogin::IConfigure cfgdat("");
    std::cout << "Use model id " << xsiumio.identify << std::endl;
    LOG_INFO("Use model id {}", xsiumio.identify);

    std::string xsiumioBuffer, cfgdatBuffer, cfgdatBufferEncrypted;
    rapidjson::Document docOutput(rapidjson::Type::kObjectType);
    xsiumio >> docOutput;
    xsiumioBuffer = Json::toString(docOutput);

    auto fp_xsiumbuf = cache_.search(curl_proxy_string);
    if (fp_xsiumbuf) {
      xsiumioBuffer = *fp_xsiumbuf;
      std::cout << "Using cached xsiumio buffer for proxy: "
                << curl_proxy_string << std::endl;
    } else {
      cache_.push(curl_proxy_string, xsiumioBuffer);
    }

    cfgdat << xsiumioBuffer;
    cfgdat >> cfgdatBuffer;
    cfgdatBufferEncrypted = chromium::yunlogin::AESEncrypt(cfgdatBuffer);
#if _DEBUG
    stl::File::WriteFile(Config::CreateOrGet()->GetChromiumUserDataDir() +
                             "/cfgdat.json",
                         cfgdatBuffer);
    // stl::File::WriteFile(Config::CreateOrGet()->GetChromiumUserDataDir() +
    //                          "/xsiumio.json",
    //                      xsiumioBuffer);
    stl::File::WriteFile(Config::CreateOrGet()->GetChromiumUserDataDir() + "/" +
                             chromium::yunlogin::kFilenameConfig,
                         cfgdatBufferEncrypted);
#else
    stl::File::WriteFile(Config::CreateOrGet()->GetChromiumUserDataDir() + "/" +
                             chromium::yunlogin::kFilenameConfig,
                         cfgdatBufferEncrypted);
#endif
    LOG_INFO("{}---\n{}", xsiumio.identify, xsiumioBuffer);
  } while (0);
}
bool Startup::OpenChrome() {
  bool result = false;
  do {
    const std::string strCurrentPath = Config::CreateOrGet()->GetCurrentDir();
    const std::string strChromeExe =
        Config::CreateOrGet()->GetChromiumProcessPath();
    xs_process_id_t pid = 0;
    if (xs_sys_process_spawn(strChromeExe.c_str(), nullptr, nullptr, 1, &pid))
      break;
    chromium_main_pid_.store(pid);
    chromium_start_time_ = stl::Time::TimeStamp<std::chrono::seconds>();
    result = true;
  } while (0);
  return result;
}
void Startup::Run() {
  std::thread([this]() {
    bool needStop = true;
    do {
      do { //!@ Server
        if (pComponentCurl_)
          pComponentCurl_->Start();
        if (server_->IsOpen())
          break;
        if (!server_->Start())
          break;
        needStop = false;
      } while (0);

      do { //!@ release mode load models
        if (!model_->Ready()) {
          model_->LoadModelParts();
          model_->GenModel();
        }
      } while (0);

      do {
        std::unique_lock<std::mutex> lck(__mtx__, std::defer_lock);
        lck.lock();
        if (chromium_main_pid_.load() == 0) {
          ConfigureBegin();
          model_->GetModel(xsiumio);
          ConfigureEnd();
          OpenChrome();
        }
        lck.unlock();

      } while (0);
      if (needStop)
        break;

      time_t start_time = GetChromiumStartTime();
      if ((start_time > 0) &&
          (stl::Time::TimeStamp<std::chrono::seconds>() - start_time >=
           chromium_timeout_)) {
        const std::string log_message =
            "Chromium process has not started within the timeout period.";
        std::cout << "[" << stl::Time::GetLogTimeCN() << "] " << log_message
                  << std::endl;
        LOG_INFO("{}", log_message);
        ChromiumClose();
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } while (1);
  }).join();
  if (pComponentCurl_)
    pComponentCurl_->Stop();
}
bool Startup::ConfigDynamicInfo(const std::string &url,
                                const std::string &proxyString,
                                chromium::xsiumio::IXSiumio &out) const {
  bool result = false;
  std::string dynamic_info;
  LOG_INFO("ConfigDynamicInfo: url={}, proxyString={}", url, proxyString);
  std::cout << "ConfigDynamicInfo: url=" << url
            << ", proxyString=" << proxyString << std::endl;
  do {
    if (url.empty())
      break;
    if (!pComponentCurl_)
      break;
    auto pCurl = dynamic_cast<curl::ICurl *>(pComponentCurl_);
    if (!pCurl)
      break;
    auto reqArray = pCurl->CreateRequestArray();
    auto reqMyip = pCurl->CreateRequest();
    reqMyip->SetUrl(url.c_str());
    reqMyip->SetProxyString(proxyString.c_str());
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

    if (url.find("myip.yunlogin.com") != std::string::npos) {

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

  if (result) {
    out.webrtcIPHandling.public_ip = out.dynFpsInfo.ipinfo.ip;
    out.fps.timezone.id = out.dynFpsInfo.ipinfo.timezone;
  }

  LOG_INFO("Request dynamic data {} ,ip {},timezone_id {}",
           result ? "success" : "failed", out.dynFpsInfo.ipinfo.ip,
           out.fps.timezone.id);
  std::cout << "Request dynamic data " << (result ? "success" : "failed")
            << ", ip: " << out.dynFpsInfo.ipinfo.ip
            << ", timezone_id: " << out.fps.timezone.id << std::endl;
  return result;
}
void Startup::NotifyRequestResult(const std::string &body) {
  std::unique_lock<std::mutex> lck(__mtx__, std::defer_lock);
  lck.lock();
  int result = 0;
  do {
    if (mode_ == RunMode::kModelLevel1)
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
    if (!result)
      break;
    std::string mode_filename =
        std::to_string(stl::Time::TimeStamp<std::chrono::microseconds>()) +
        ".mode";
    std::string mode_data;
    rapidjson::Document modeDoc(rapidjson::Type::kObjectType);
    xsiumio >> modeDoc;
    mode_data = Json::toString(modeDoc);
    stl::File::WriteFile(Config::CreateOrGet()->GetProjectModelPartsDir() +
                             "/" + mode_filename,
                         mode_data);
  } while (0);
  lck.unlock();
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