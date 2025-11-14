#include "config.h"
namespace {
static std::string GetUserDynamicProxyString() {
  std::ostringstream oss;
  oss << "4412679-3737a568-US-session-"
      << stl::Random::GetRandomValue<int>(100000000, 999999999);
  const std::string username = oss.str();
  const std::string password = "3871a960";
  const std::string host = "gate-hk.kkoip.com";
  const int port = 16586;
  return username + ":" + password + "@" + host + ":" + std::to_string(port);
}

static std::string
GetUserDynamicProxyStringXuZhou(const unsigned int &timeout = 10) {
  // socks5h://windows-zone-windows-session-666666-sessTime-120:111111@pr-na.ipidea.io:2336
  std::ostringstream oss;
  oss << "windows-zone-windows-session-"
      << stl::Random::GetRandomValue<int>(666666, 999999) << "-sessTime-"
      << __min(timeout, 120);
  const std::string username = oss.str();
  const std::string password = "111111";
  const std::string host = "pr-na.ipidea.io";
  const int port = 2333; // 2336
  return username + ":" + password + "@" + host + ":" + std::to_string(port);
}
} // namespace
struct StaticProxyInfo {
  std::string host;
  int port;
  std::string username;
  std::string password;
};

static bool GetStaticProxyInfo(std::vector<std::string> &out) {
  bool result = false;
  static const std::vector<StaticProxyInfo> proxys = {
      {"38.213.69.199", 5206, "rgj6rwy4gcc7", "hdqc5wjnw4fn"},
      {"38.213.69.231", 5206, "hgj6rwy4p7fx", "cner2w7ccm7d"},
      {"38.213.69.187", 5206, "ugj6rwy4p9ge", "tiepyjkstxqs"},
      {"38.213.69.52", 5206, "bgj6rwy4pqhs", "mrdhhepu374p"},
      {"38.213.69.96", 5206, "dgj6rwuah9rb", "jrypy55eiqj5"},
  };

  for (const auto &it : proxys) {
    auto outProxyUrls = "socks5://" + it.username + ":" + it.password + "@" +
                        it.host + ":" + std::to_string(it.port);
    out.emplace_back(outProxyUrls);
  }

#if 0
38.213.69.199:5206:rgj6rwy4gcc7:hdqc5wjnw4fn
38.213.69.231:5206:hgj6rwy4p7fx:cner2w7ccm7d
38.213.69.187:5206:ugj6rwy4p9ge:tiepyjkstxqs
38.213.69.52:5206:bgj6rwy4pqhs:mrdhhepu374p
38.213.69.96:5206:dgj6rwuah9rb:jrypy55eiqj5
#endif

  result = false;
  return result;
}

IModel::IModel() {
  Init();
}
IModel::~IModel() {
  UnInit();
}
void IModel::Init() {
  LoadXSCfg();
}
void IModel::UnInit() {
}
void IModel::LoadXSCfg() {
  do {
    std::string xscfgBuffer =
        stl::File::ReadFile(Config::CreateOrGet()->GetProjectXSCfgPath());
    if (xscfgBuffer.empty()) {
      std::cout << "Not found xscfg" << std::endl;
      break;
    }
    xscfg_ << xscfgBuffer;
  } while (0);
}
void IModel::SaveXSCfg() {
  std::string xscfgBuffer;
  xscfg_ >> xscfgBuffer;
  stl::File::WriteFile(Config::CreateOrGet()->GetProjectXSCfgPath(),
                       xscfgBuffer);
}
void IModel::GenRouteConfigure(chromium::xsiumio::IXSiumio &cfg) const {
  std::lock_guard<std::mutex> lck(*mtx_);
  cfg.Super([](const std::string &hashSource) {
    return OpenSSL::HMAC_SHA256(hashSource, "Martell", true);
  });
  std::string xscfgBuffer;
  cfg >> xscfgBuffer;
  stl::File::WriteFile(Config::CreateOrGet()->GetGenConfigPath(), xscfgBuffer);
}
bool IModel::Ready() const {
  std::lock_guard<std::mutex> lck(*mtx_);
  return ready_.load();
}
std::string IModel::GetDynamicProxyUrl() const {
  std::string result;
  do {
    if (!xscfg_.policy.dynamic_proxy)
      break;
    switch (xscfg_.policy.dynamic_proxy_type) {
    case 0: { //!@ User/Client US
      result = GetUserDynamicProxyString();
    } break;
    case 1: { //!@ IPID
      result = GetUserDynamicProxyStringXuZhou(
          xscfg_.policy.dynamic_proxy_session_timeout > 0
              ? xscfg_.policy.dynamic_proxy_session_timeout
              : 10);
    } break;
    default:
      break;
    }
  } while (0);
  return result;
}
std::string IModel::GetProxyStringForCurl() const {
  std::string result;
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    if (!xscfg_.proxy.enable)
      break;
    if (xscfg_.bridge.enable && !xscfg_.bridge.proxy_pass.empty()) {
      result = xscfg_.bridge.proxy_pass;
    } else if (!xscfg_.proxy.url.empty()) {
      result = xscfg_.proxy.url;
    }
    if (result.empty())
      break;
    auto f_socks5h = result.find("socks5h://");
    auto f_socks5 = result.find("socks5://");
    if (f_socks5 != std::string::npos)
      result.replace(f_socks5, strlen("socks5://"), "http://");
    else if (f_socks5h != std::string::npos)
      result.replace(f_socks5h, strlen("socks5h://"), "http://");
  } while (0);
  return result;
}
static void SettingBridgeProxyStartupArgs(chromium::xsiumio::IXSiumio &cfg) {
  for (auto it = cfg.startup.args.begin(); it != cfg.startup.args.end();) {
    if (it->find("host-resolver-rules") != std::string::npos ||
        it->find("proxy-bypass-list") != std::string::npos) {
      it = cfg.startup.args.erase(it);
    } else {
      ++it;
    }
  }
  if (cfg.bridge.enable && cfg.proxy.enable) {
    /* "--host-resolver-rules=MAP * ~NOTFOUND , EXCLUDE 127.0.0.1",
         "--proxy-bypass-list=<-loopback>",*/
    cfg.startup.args.emplace_back(
        "--host-resolver-rules=MAP * ~NOTFOUND , EXCLUDE 127.0.0.1");
    cfg.startup.args.emplace_back("--proxy-bypass-list=<-loopback>");
  }
}
void IModel::SettingBridgeProxy(chromium::xsiumio::IXSiumio &cfg) {
  std::lock_guard<std::mutex> lck(*mtx_);
  SettingBridgeProxyStartupArgs(cfg);
  if (!cfg.proxy.enable) {
    cfg.bridge.enable = false;
    cfg.bridge.proxy_pass.clear();
    cfg.proxy.url.clear();
  }

  do {
    if (!cfg.bridge.enable)
      break;
    cfg.bridge.proxy_pass.clear();
    if (!cfg.policy.enable)
      break;
    if (!cfg.policy.dynamic_proxy)
      break;
    cfg.bridge.proxy_pass = "socks5h://" + GetDynamicProxyUrl();
  } while (0);

  if (cfg.bridge.enable) {
    bridge_startup_args_ = cfg.bridge.GetCmdlineString();
  }
  if (cfg.bridge.enable && cfg.proxy.enable) {
    cfg.proxy.url = "http://127.0.0.1:55668";
  }
  xscfg_ = cfg;
}
void IModel::FinishModelParts() {
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    if (model_parts_updated_.load())
      break;
    if (model_ress_.empty())
      break;
    chromium::Packet packet;
    chromium::tfRoutePak buffer;
    packet.made(model_ress_, buffer);
    if (buffer.empty())
      break;
    stl::File::WriteFile(
        Config::CreateOrGet()->GetProjectModelDir() + "/model.bin", buffer);
    model_parts_updated_.store(true);
  } while (0);
}

bool IModel::LoadModelParts() {
  bool result = false;
  std::lock_guard<std::mutex> lck(*mtx_);
  bool fpsdb_loaded = false;
  do {
    if (!stl::Directory::Exists(Config::CreateOrGet()->GetProjectModelDir()))
      break;
    if (!stl::File::Exists(Config::CreateOrGet()->GetProjectModelDir() +
                           "/model.bin"))
      break;
    chromium::tfRoutePak buffer = stl::File::ReadFile(
        Config::CreateOrGet()->GetProjectModelDir() + "/model.bin");
    if (buffer.empty())
      break;
    std::set<std::string> proxys_tmp;
    chromium::Packet packet;
    if (!packet.unmade(buffer, model_ress_)) {
      LOG_ERROR("Failed to decode model parts.");
      break;
    }
#if _DEBUG
    std::set<double> canvas_base_s;
    std::set<std::string> webgl_getparameter_37445_37446_s;
#endif
    for (const auto &it : model_ress_) {
      do {
        std::string part_buffer = stl::String::WemadeDecode(it.second);
        if (part_buffer.empty())
          break;
        if (it.first == static_cast<chromium::tfRouteIndex>(ModelKey::kFpsdb)) {
          fpsdb_ << part_buffer;
          fpsdb_loaded = true;
          continue;
        }
        if (it.first <
            static_cast<chromium::tfRouteIndex>(ModelKey::kModelPartsBegin))
          continue;
        rapidjson::Document doc;
        if (doc.Parse(part_buffer.data(), part_buffer.size()).HasParseError())
          continue;
        if (!doc.HasMember(chromium::xsiumio::kObjectKey) ||
            !doc[chromium::xsiumio::kObjectKey].IsObject())
          continue;

        do {
          if (!doc[chromium::xsiumio::kObjectKey].HasMember("proxy"))
            break;
          if (!doc[chromium::xsiumio::kObjectKey]["proxy"].IsObject())
            break;
          if (!doc[chromium::xsiumio::kObjectKey]["proxy"].HasMember(
                  "credentials_url"))
            break;
          if (!doc[chromium::xsiumio::kObjectKey]["proxy"]["credentials_url"]
                   .IsString())
            break;
          const std::string credentials_url =
              doc[chromium::xsiumio::kObjectKey]["proxy"]["credentials_url"]
                  .GetString();
          proxys_tmp.emplace(credentials_url);
        } while (0);

        do {
          chromium::xsiumio::IXSiumio node;
          node << doc[chromium::xsiumio::kObjectKey];
#if _DEBUG
          if (node.fps.canvas.hash.base > 1.0) {
            canvas_base_s.emplace(node.fps.canvas.hash.base);
          }
          if (!node.fps.webgl.getParameter[37445].empty() &&
              !node.fps.webgl.getParameter[37446].empty()) {
            webgl_getparameter_37445_37446_s.emplace(
                node.fps.webgl.getParameter[37445] + "," +
                node.fps.webgl.getParameter[37446]);
          }
#endif
          if (node.identify <= 0)
            break;
          xsiumios_.emplace(node.identify, node);
        } while (0);
        auto ss = 0;
      } while (0);
    }
#if _DEBUG
    std::string tmpout;
    for (const auto &canvas_base : canvas_base_s) {
      if (canvas_base <= 0)
        continue;
      tmpout += fmt::format("{:.6f},", canvas_base);
    }
    stl::File::WriteFile(
        Config::CreateOrGet()->GetCurrentDir() + "/canvas_base.txt", tmpout);

    std::string webgl_getparameter_37445_37446_out;
    for (const auto &param : webgl_getparameter_37445_37446_s) {
      webgl_getparameter_37445_37446_out += fmt::format("{},", param);
    }
    stl::File::WriteFile(Config::CreateOrGet()->GetCurrentDir() +
                             "/webgl_getparameter_37445_37446.txt",
                         webgl_getparameter_37445_37446_out);
#endif

    std::vector<std::string> tmpStaticProxys;
    if (GetStaticProxyInfo(tmpStaticProxys) && !tmpStaticProxys.empty()) {
      proxys_ = tmpStaticProxys;
    } else {
      for (const auto &proxy : proxys_tmp) {
        if (proxy.empty())
          continue;
        proxys_.emplace_back(proxy);
      }
    }

    result = true;
  } while (0);
#if ENABLE_DEVELOP_MODE
  const std::string log =
      fmt::format("webglDevs({}) brws({})", fpsdb_.webgl.source[0].size(),
                  fpsdb_.browsers[0].size());
  std::cout << log << std::endl;
#else
  const std::string log = fmt::format(
      "{} xs={} p={} plm={} brw={} scn={} dev={} ch={} wh={} ah={} fps={} ",
      GetModelIdentify(), xsiumios_.size(), proxys_.size(),
      fpsdb_.platform.source.size(), fpsdb_.browsers.size(),
      fpsdb_.screen.source.size(), fpsdb_.webgl.source.size(),
      fpsdb_.hash_canvas.base.size(), fpsdb_.hash_webgl.base.size(),
      fpsdb_.hash_audio.base.size(), fpsdb_loaded ? 1 : 0);
  LOG_INFO("{}", log);
  std::cout << log << std::endl;
#endif
  ready_.store(true);
  return result;
}
void IModel::Super() {
  xscfg_.Super([](const std::string &hashSource) {
    return OpenSSL::HMAC_SHA256(hashSource, "Martell", true);
  });
}
void IModel::SetModelResult(const bool &result) {
  std::lock_guard<std::mutex> lock(*mtx_);
  model_result_ = result;
}
bool IModel::GetModelResult() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return model_result_.load();
}
void IModel::SetModelCache(const std::string &cache) {
  std::lock_guard<std::mutex> lock(*mtx_);
  model_cache_ = cache;

  size_t pos = model_ress_.size();
  model_ress_.emplace(static_cast<chromium::tfRouteIndex>(pos),
                      stl::String::WemadeEncode(cache));
  model_parts_updated_.store(false);
}
void IModel::Output(const chromium::xsiumio::IXSiumio &model) const {
}

const std::string &IModel::GetBridgeStartupArgs() const {
  std::lock_guard<std::mutex> lck(*mtx_);
  return bridge_startup_args_;
}
const chromium::xsiumio::IXSiumio &IModel::GetXSCfg() const {
  std::lock_guard<std::mutex> lck(*mtx_);
  return xscfg_;
}
bool IModel::LaunchBrowser(const chromium::xsiumio::tfIdentifyType &) {
  return false;
}
bool IModel::ShutdownBrowser(const chromium::xsiumio::tfIdentifyType &) {
  return false;
}