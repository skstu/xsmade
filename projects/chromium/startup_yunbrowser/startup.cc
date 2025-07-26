#include "config.h"
static std::mutex __mtx__;
Startup::Startup(const RunMode &mode) : mode_(mode) {
  Init();
}
Startup::~Startup() {
  UnInit();
}
void Startup::Init() {
  do {
    std::string current_path = Config::CreateOrGet()->GetCurrentDir();
#if _DEBUG
    std::string target_component_path =
        current_path + "/components/libcurlcc.dll";
#else
    std::string target_component_path = current_path + "/libcurlcc.dll";
#endif
    if (!stl::File::Exists(target_component_path))
      break;
    pComponentCurl_ = curl::ICurl::Create(target_component_path.c_str());
    server_ = new Server();
    model_ = dynamic_cast<IModel *>(new Model());
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
void Startup::GenerateDynamicProxyInfo(std::string &curl,
                                       std::string &chromium) const {
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
void Startup::Configure() {
  const bool is_clean_udd = true;
  do {
#if _DEBUG
    const std::string project_path = Config::CreateOrGet()->GetCurrentDir() +
                                     "\\browser\\chromium\\138.0.7204.158\\";
#else
    const std::string project_path = Config::CreateOrGet()->GetCurrentDir();
#endif
    const std::string xsiumio_path =
        project_path + "\\" + chromium::xsiumio::kObjectKey + ".json";
    const std::string chromium_user_data_dir = project_path + "\\.cache\\1";
    std::string xsiumio_buffer;
    if (!stl::File::Exists(xsiumio_path))
      break;
    xsiumio_buffer = stl::File::ReadFile(xsiumio_path);
    rapidjson::Document doc;
    if (doc.Parse(xsiumio_buffer.c_str(), xsiumio_buffer.size())
            .HasParseError())
      break;
    if (!doc.HasMember(chromium::xsiumio::kObjectKey) ||
        !doc[chromium::xsiumio::kObjectKey].IsObject())
      break;
    xsiumio << doc[chromium::xsiumio::kObjectKey];
    { //!@ develop configure
      std::string curl_proxy_string;
      GenerateDynamicProxyInfo(curl_proxy_string,
                               xsiumio.proxy.credentials_url);
      LOG_INFO("Chromium using proxy: %s",
               xsiumio.proxy.credentials_url.c_str());
      std::cout << "Chromium using proxy: " << xsiumio.proxy.credentials_url
                << std::endl;
      do {
        ConfigDynamicInfo(xsiumio.proxy_info_request_url, curl_proxy_string);
        if (is_clean_udd) {
          try {
            stl::Directory::RemoveAll(chromium_user_data_dir);
          } catch (const std::exception &e) {
            std::cout << "Error removing directory: " << e.what() << std::endl;
            LOG_WARN("Error removing directory: %s", e.what());
          }
        }
        stl::Directory::Create(chromium_user_data_dir);
        stl::File::WriteFile(project_path + "/" +
                                 chromium::yunlogin::kFilenameUdd,
                             chromium_user_data_dir);
        xsiumio.webrtcIPHandling.public_ip = xsiumio.myipyunlogincom.Ip;
        xsiumio.fps.timezone.id = xsiumio.myipyunlogincom.LocalTime;

        LOG_INFO("Public IP: %s", xsiumio.webrtcIPHandling.public_ip.c_str());
        LOG_INFO("Timezone ID: %s", xsiumio.fps.timezone.id.c_str());
        std::cout << "Public IP: " << xsiumio.webrtcIPHandling.public_ip
                  << std::endl;
        std::cout << "Timezone ID: " << xsiumio.fps.timezone.id << std::endl;

        //!@ configure xsiumio fps
        const std::vector<int> cpu_cores = {2,  4,  6,  8,  12, 16, 20,
                                            24, 28, 32, 36, 48, 64, 96};
        const std::vector<unsigned long long> mem_sizes_g = {
            2, 4, 6, 8, 12, 16, 24, 32, 48, 64, 96, 128, 192, 256};
        xsiumio.fps.hardwareConcurrency =
            cpu_cores[stl::Random::GetRandomValue<int>(0, 13)];
        xsiumio.fps.deviceMemory =
            cpu_cores[stl::Random::GetRandomValue<int>(0, 13)];
        xsiumio.fps.canvas.hash.random = false;
        xsiumio.fps.canvas.hash.base =
            stl::Random::GetRandomValue<double>(0.00001, 0.00999);
        xsiumio.fps.webgl.hash.random = false;
        xsiumio.fps.webgl.hash.base =
            stl::Random::GetRandomValue<double>(0.00001, 100.00001);
        xsiumio.fps.audio.hash.random = false;
        xsiumio.fps.audio.hash.base =
            stl::Random::GetRandomValue<double>(0.00001, 100.00001);
        xsiumio.fps.webgl.hash.random = false;
        xsiumio.fps.webgl.hash.base =
            stl::Random::GetRandomValue<double>(0.00001, 100.00001);
        for (auto &param : xsiumio.fps.webgl.getParameter) {
          switch (param.first) {
          case 3379:
          case 34024:
          case 34076:
          case 34047:
          case 34921:
          case 34930:
          case 35660:
          case 35661:
          case 36347:
          case 36348:
          case 36349:
          case 3410:
          case 3411:
          case 3412:
          case 3413:
          case 3414: {
            long current = strtol(param.second.c_str(), nullptr, 10);
            if (current <= 2)
              continue;
            {
              current = stl::Random::GetRandomValue<long>(
                  static_cast<long>(current / 2), current);
              param.second = std::to_string(current);
            }
          } break;
          default:
            break;
          } /// switch
        }
        xsiumio.fps.font.hash.random = false;
        xsiumio.fps.font.hash.base = 1.0f;
        std::set<std::string> font_allowlist = {"arial",
                                                "bahnschrift",
                                                "calibri",
                                                "cambria",
                                                "cambria math",
                                                "candara",
                                                "comic sans ms",
                                                "consolas",
                                                "constantia",
                                                "corbel",
                                                "courier new",
                                                "ebrima",
                                                "franklin gothic",
                                                "gabriola",
                                                "gadugi",
                                                "georgia",
                                                "impact",
                                                "javanese text",
                                                "lucida console",
                                                "lucida sans unicode",
                                                "malgun gothic",
                                                "marlett",
                                                "microsoft himalaya",
                                                "microsoft jhenghei",
                                                "microsoft jhenghei ui",
                                                "microsoft new tai lue",
                                                "microsoft phagspa",
                                                "microsoft sans serif",
                                                "microsoft tai le",
                                                "microsoft yahei",
                                                "microsoft yi baiti",
                                                "mingliu-extb",
                                                "mingliu_hkscs-extb",
                                                "mongolian baiti",
                                                "ms gothic",
                                                "ms pgothic",
                                                "ms ui gothic",
                                                "mv boli",
                                                "myanmar text",
                                                "palatino linotype",
                                                "pmingliu-extb",
                                                "segoe print",
                                                "segoe script",
                                                "segoe ui",
                                                "segoe ui emoji",
                                                "segoe ui symbol",
                                                "simsun",
                                                "simsun-extb",
                                                "sitka small",
                                                "sylfaen",
                                                "symbol",
                                                "trebuchet ms",
                                                "verdana",
                                                "webdings",
                                                "yu gothic",
                                                "Arial",
                                                "Verdana",
                                                "Tahoma",
                                                "Times New Roman",
                                                "Courier New",
                                                "Georgia",
                                                "Impact",
                                                "Comic Sans MS",
                                                "Lucida Console"};

        {
          std::uint64_t seed =
              stl::Time::TimeStamp<std::chrono::microseconds>();
          std::vector<std::string> fonts(font_allowlist.begin(),
                                         font_allowlist.end());
          std::mt19937_64 rng(seed);
          std::uniform_int_distribution<int> dist_count(5, 20);
          size_t remove_count = static_cast<size_t>(dist_count(rng));
          std::shuffle(fonts.begin(), fonts.end(), rng);
          remove_count = std::min(remove_count, fonts.size());
          for (size_t i = 0; i < remove_count; ++i) {
            font_allowlist.erase(fonts[i]);
          }
          xsiumio.fps.font.allowlist.clear();
          for (const auto &font : font_allowlist) {
            xsiumio.fps.font.allowlist.emplace(font);
          }
        }

      } while (0);
    }

    chromium::yunlogin::IConfigure cfgdat("");
    xsiumio.timestamp = stl::Time::TimeStamp<std::chrono::microseconds>();
    xsiumio.identify = xsiumio.timestamp;
    std::string output, cfgdatBuffer, cfgdatBufferEncrypted;
    rapidjson::Document docOutput(rapidjson::Type::kObjectType);
    xsiumio >> docOutput;
    output = Json::toString(docOutput);
    cfgdat << output;
    cfgdat >> cfgdatBuffer;
    cfgdatBufferEncrypted = chromium::yunlogin::AESEncrypt(cfgdatBuffer);
#if _DEBUG
    stl::File::WriteFile(chromium_user_data_dir + "/cfgdat.json", cfgdatBuffer);
    stl::File::WriteFile(chromium_user_data_dir + "/" +
                             chromium::yunlogin::kFilenameConfig,
                         cfgdatBufferEncrypted);
#else
    stl::File::WriteFile(chromium_user_data_dir + "/" +
                             chromium::yunlogin::kFilenameConfig,
                         cfgdatBufferEncrypted);
#endif
  } while (0);
}
bool Startup::OpenChrome() {
  bool result = false;
  do {
    switch (mode_) {
    case RunMode::kReleaseModel:
      ConfigureRelease();
      break;
    default:
      Configure();
    }

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
        if (mode_ == RunMode::kReleaseModel) {
          // Load release model
          model_->LoadModelParts();
        }
      } while (0);

      do {
        std::unique_lock<std::mutex> lck(__mtx__, std::defer_lock);
        lck.lock();
        if (chromium_main_pid_.load() == 0) {
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
                                const std::string &proxyString) {
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
      xsiumio.myipyunlogincom << doc;
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
        xsiumio.myipyunlogincom.Ip = doc["query"].GetString();
      }
      if (doc.HasMember("timezone") && doc["timezone"].IsString()) {
        xsiumio.myipyunlogincom.LocalTime = doc["timezone"].GetString();
      }
      if (doc.HasMember("city") && doc["city"].IsString()) {
        xsiumio.myipyunlogincom.City = doc["city"].GetString();
        xsiumio.myipyunlogincom.CityEn = xsiumio.myipyunlogincom.City;
      }
      if (doc.HasMember("country") && doc["country"].IsString()) {
        xsiumio.myipyunlogincom.Country = doc["country"].GetString();
        xsiumio.myipyunlogincom.CountryEnglish =
            xsiumio.myipyunlogincom.Country;
      }
      if (doc.HasMember("countryCode") && doc["countryCode"].IsString()) {
        xsiumio.myipyunlogincom.CountryCode = doc["countryCode"].GetString();
      }
      if (doc.HasMember("isp") && doc["isp"].IsString()) {
        xsiumio.myipyunlogincom.ISP = doc["isp"].GetString();
      }
      if (doc.HasMember("lat") && doc["lat"].IsNumber()) {
        xsiumio.myipyunlogincom.Latitude =
            std::to_string(doc["lat"].GetDouble());
      }
      if (doc.HasMember("lon") && doc["lon"].IsNumber()) {
        xsiumio.myipyunlogincom.Longitude =
            std::to_string(doc["lon"].GetDouble());
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
        xsiumio.myipyunlogincom.Ip = doc["ip"].GetString();
      }
      if (doc.HasMember("timezone") && doc["timezone"].IsString()) {
        xsiumio.myipyunlogincom.LocalTime = doc["timezone"].GetString();
      }
      if (doc.HasMember("city") && doc["city"].IsString()) {
        xsiumio.myipyunlogincom.City = doc["city"].GetString();
        xsiumio.myipyunlogincom.CityEn = xsiumio.myipyunlogincom.City;
      }
      if (doc.HasMember("country") && doc["country"].IsString()) {
        xsiumio.myipyunlogincom.Country = doc["country"].GetString();
        xsiumio.myipyunlogincom.CountryEnglish =
            xsiumio.myipyunlogincom.Country;
      }
      if (doc.HasMember("loc") && doc["loc"].IsString()) {
        std::string loc = doc["loc"].GetString();
        std::vector<std::string> locParts = stl::String::StringSplit(loc, ",");
        if (locParts.size() == 2) {
          xsiumio.myipyunlogincom.Latitude = locParts[0];
          xsiumio.myipyunlogincom.Longitude = locParts[1];
        }
      }
    } else {
      LOG_ERROR("Unknown URL for dynamic info: {}", url.c_str());
      std::cout << "Unknown URL for dynamic info: " << url << std::endl;
      break;
    }
  } while (0);

  if (result) {
    xsiumio.webrtcIPHandling.public_ip = xsiumio.myipyunlogincom.Ip;
    xsiumio.fps.timezone.id = xsiumio.myipyunlogincom.LocalTime;
  }
  LOG_INFO("Request dynamic data {}", result ? "success" : "failed");
  std::cout << "Request dynamic data " << (result ? "success" : "failed")
            << std::endl;
  return result;
}
void Startup::NotifyRequestResult(const std::string &body) {
  std::unique_lock<std::mutex> lck(__mtx__, std::defer_lock);
  lck.lock();
  int result = 0;
  do {
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