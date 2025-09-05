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
  stl::File::WriteFile(Config::CreateOrGet()->GetGenConfigPath(), xscfgBuffer);
}
bool IModel::Ready() const {
  std::lock_guard<std::mutex> lck(*mtx_);
  return ready_.load();
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
void IModel::SettingBridgeProxy() {
  std::string proxy_url;
  do {
    if (!xscfg_.proxy.enable)
      break;
    if (xscfg_.proxy.dynamic) {
      proxy_url = GetUserDynamicProxyString();
      if (proxy_url.empty())
        break;
      xscfg_.proxy.credentials_url = "socks5://" + proxy_url;
      xscfg_.proxy.curl_credentials_url = "http://" + proxy_url;
    } else if (!xscfg_.proxy.credentials_url.empty() &&
               xscfg_.proxy.curl_credentials_url.empty()) {

      auto f_socks5h = xscfg_.proxy.credentials_url.find("socks5h://");
      auto f_socks5 = xscfg_.proxy.credentials_url.find("socks5://");
      std::string tmp(xscfg_.proxy.credentials_url);
      if (f_socks5 != std::string::npos) {
        xscfg_.proxy.curl_credentials_url =
            tmp.replace(f_socks5, strlen("http://"), "http://");
      } else if (f_socks5h != std::string::npos) {
        xscfg_.proxy.curl_credentials_url =
            tmp.replace(f_socks5h, strlen("http://"), "http://");
      }
    }
  } while (0);

  do {
    if (!xscfg_.proxy.enable)
      break;
    if (!xscfg_.bridge.enable)
      break;
    if (proxy_url.empty())
      break;
    bool f_host_resolver_rules = false;
    bool f_proxy_bypass_list = false;
    for (const auto &arg : xscfg_.startup.args) {
      if (arg.find("host-resolver-rules") != std::string::npos) {
        f_host_resolver_rules = true;
      }
      if (arg.find("proxy-bypass-list") != std::string::npos) {
        f_proxy_bypass_list = true;
      }
    }
    if (!f_host_resolver_rules) {
      xscfg_.startup.args.emplace_back(
          "--host-resolver-rules=MAP * ~NOTFOUND , EXCLUDE localhost");
    }
    if (!f_proxy_bypass_list) {
      xscfg_.startup.args.emplace_back("--proxy-bypass-list=<-loopback>");
    }
    xscfg_.bridge.proxy_pass = proxy_url;
    std::string tmp;
    xscfg_.bridge >> tmp;
    bridge_startup_args_ = OpenSSL::Base64Encode(tmp, false);
  } while (0);
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