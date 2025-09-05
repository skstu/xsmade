#include "config.h"
#if 0
namespace {
static void ConfigWebglDevice(const int &platform_key,
                              const chromium::xsiumio::IFpsdb *fpsdb,
                              chromium::xsiumio::IXSiumio &model,
                              const bool &interference = false) {
  auto f_webgl_device = fpsdb->webgl.source.find(platform_key);
  do {
    if (f_webgl_device == fpsdb->webgl.source.end())
      break;
    if (f_webgl_device->second.empty())
      break;
    const auto &dev =
        f_webgl_device->second[stl::Random::GetRandomValue<size_t>(
            0, f_webgl_device->second.size() - 1)];
    model.fps.webgl.getParameter = dev.getParameter;
    model.fps.webgl.contextAttributes = dev.contextAttributes;
    model.fps.webgl.shaderPrecisionFormat = dev.shaderPrecisionFormat;
    model.fps.webgl.contextAttributes.enable = true;
    model.fps.webgl.shaderPrecisionFormat.enable = true;
  } while (0);
}
static void ConfigVoice(const int &platform_key,
                        const chromium::xsiumio::IFpsdb *fpsdb,
                        chromium::xsiumio::IXSiumio &model) {
  auto voice = fpsdb->voice;
  do {
    std::mt19937_64 rng(model.timestamp);
    std::shuffle(voice.begin(), voice.end(), rng);
    size_t get_count = stl::Random::GetRandomValue<int>(5, 20);
    model.fps.voice.datas.clear();
    for (size_t i = 0; i < get_count; ++i) {
      if (i >= voice.size())
        break;
      chromium::xsiumio::IXSiumio::Fingerprint::Voice::Data data;
      data.lang = voice[i].lang;
      data.name = voice[i].name;
      model.fps.voice.datas.emplace_back(data);
    }
  } while (0);
}
static void ConfigFont(const int &platform_key,
                       const chromium::xsiumio::IFpsdb *fpsdb,
                       chromium::xsiumio::IXSiumio &model) {
  auto f_font = fpsdb->font.find(platform_key);
  do {
    if (f_font == fpsdb->font.end())
      break;
    std::mt19937_64 rng(model.timestamp);
    model.fps.font.allowlist.clear();
    std::vector<std::string> fonts = f_font->second.family;
    const size_t total = fonts.size();
    size_t remove_count =
        stl::Random::GetRandomValue<int>(1, static_cast<int>(total / 2) - 1);
    std::shuffle(fonts.begin(), fonts.end(), rng);
    remove_count = std::min(remove_count, fonts.size());
    for (size_t i = 0; i < remove_count; ++i) {
      fonts.erase(fonts.begin());
    }
    for (const auto &fontFamily : fonts) {
      model.fps.font.allowlist.emplace(fontFamily);
    }
  } while (0);
}
static void ConfigScreen(const int &platform_key,
                         const chromium::xsiumio::IFpsdb *fpsdb,
                         chromium::xsiumio::IXSiumio &model) {
  auto f_screen = fpsdb->screen.source.find(platform_key);
  do {
    if (f_screen == fpsdb->screen.source.end())
      break;
    if (f_screen->second.empty())
      break;
    auto screen_info = f_screen->second[stl::Random::GetRandomValue<size_t>(
        0, f_screen->second.size() - 1)];
    model.fps.screen = screen_info;
    model.fps.screen.enable = true;
  } while (0);
}

static void ConfigBrowser(const int &platform_key,
                          const chromium::xsiumio::IFpsdb *fpsdb,
                          chromium::xsiumio::IXSiumio &model) {
  auto f_browser = fpsdb->browsers.find(platform_key);
  do {
    if (f_browser == fpsdb->browsers.end())
      break;
    if (f_browser->second.empty())
      break;
    const auto &brw = f_browser->second[stl::Random::GetRandomValue<size_t>(
        0, f_browser->second.size() - 1)];
    model.fps.userAgent = brw.userAgent;
    model.fps.userAgentMetadata = brw.userAgentMetadata;
    model.fps.userAgentMetadata.enable = true;
  } while (0);
}
} // namespace
ModelLevel2::ModelLevel2() {
}
ModelLevel2::~ModelLevel2() {
}
void ModelLevel2::Release() const {
  delete this;
}
const char *ModelLevel2::GetModelIdentify() const {
  return "Model-Level-2";
}
bool ModelLevel2::GetModel(chromium::xsiumio::IXSiumio &model) {
  bool result = false;
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    const int platform_key = 0;

    // bool use_cache = model_result_.load() && !model_cache_.empty();
    // if (use_cache) {
    //   model << model_cache_;
    //   result = true;
    // }

    // Output(model);
    // if (use_cache)
    //   break;

    auto f_platform = fpsdb_.platform.source.find(platform_key);
    if (f_platform == fpsdb_.platform.source.end())
      break;
    model.fps.platform = f_platform->second;
    model.timestamp = stl::Time::TimeStamp<std::chrono::microseconds>();
    model.identify = model.timestamp;
    model.fps.do_not_track = stl::Random::GetRandomBool();

    auto f_hardwareConcurrency =
        fpsdb_.hardwareConcurrency.source.find(platform_key);
    if (f_hardwareConcurrency != fpsdb_.hardwareConcurrency.source.end()) {
      model.fps.hardwareConcurrency =
          f_hardwareConcurrency->second[stl::Random::GetRandomValue<size_t>(
              0, f_hardwareConcurrency->second.size() - 1)];
    }

    auto f_deviceMemory = fpsdb_.deviceMemory.source.find(platform_key);
    if (f_deviceMemory != fpsdb_.deviceMemory.source.end()) {
      model.fps.deviceMemory =
          f_deviceMemory->second[stl::Random::GetRandomValue<size_t>(
              0, f_deviceMemory->second.size() - 1)];
    }

    model.fps.rtt = stl::Random::GetRandomValue<uint32_t>(20, 200);
    model.fps.disk.quota = stl::Random::GetRandomValue<uint64_t>(
        50000000000, 2000000000000); // 50GB~2TB
    model.fps.disk.usage = stl::Random::GetRandomValue<uint64_t>(
        5000000000, 1000000000000); // 5GB~1TB

    model.fps.canvas.hash.random = false;
    /*model.fps.canvas.hash.base =
        fpsdb_.hash_canvas.base[stl::Random::GetRandomValue<double>(
            0, fpsdb_.hash_canvas.base.size() - 1)];*/
    model.fps.canvas.hash.base =
        stl::Random::GetRandomValue<unsigned int>(1001, 888888);

    model.fps.webgl.hash.base =
        fpsdb_.hash_webgl.base[stl::Random::GetRandomValue<size_t>(
            0, fpsdb_.hash_webgl.base.size() - 1)];
    model.fps.audio.hash.base =
        fpsdb_.hash_audio.base[stl::Random::GetRandomValue<size_t>(
            0, fpsdb_.hash_audio.base.size() - 1)];
    model.fps.webgl.hash.base =
        fpsdb_.hash_webgl.base[stl::Random::GetRandomValue<size_t>(
            0, fpsdb_.hash_webgl.base.size() - 1)];
    model.fps.v8.hash.base =
        stl::Time::TimeStamp<std::chrono::microseconds>() * 1.0;
    model.fps.math.hash.base = stl::Random::GetRandomValue<double>(1e-6, 1e-8);

    //ConfigLanguages(platform_key, &fpsdb_, model);
    // ConfigBrowser(platform_key, &fpsdb_, model);
    ConfigWebglDevice(platform_key, &fpsdb_, model, true);
    ConfigScreen(platform_key, &fpsdb_, model);
    ConfigFont(platform_key, &fpsdb_, model);
    ConfigVoice(platform_key, &fpsdb_, model);

    result = true;
  } while (0);
  return result;
}

bool ModelLevel2::GetProxyInfo(chromium::xsiumio::IXSiumio &,std::string &chromiumProxyUrl,
                               std::string &curlProxyUrl,
                               const bool &useCache) {
  bool result = false;
  std::lock_guard<std::mutex> lock(*mtx_);
  do {
    if (!useCache)
      break;
    if (proxys_.empty())
      break;
    break;
    const size_t total = proxys_.size();
    size_t index = stl::Random::GetRandomValue<size_t>(0, total - 1);
    chromiumProxyUrl = proxys_[index];
    std::string tmp(chromiumProxyUrl);
    auto f_socks5 = tmp.find("socks5://");
    auto f_http = tmp.find("http://");
    if (f_socks5 != std::string::npos) {
      curlProxyUrl = tmp.replace(f_socks5, strlen("socks5://"), "http://");
    } else if (chromiumProxyUrl.find("http://") != std::string::npos) {
      curlProxyUrl = chromiumProxyUrl;
      chromiumProxyUrl = tmp.replace(f_http, strlen("http://"), "socks5://");
    } else {
      break;
    }
    result = true;
  } while (0);

  do {
    if (result)
      break;
    std::ostringstream oss;
    oss << "4412679-3737a568-US-session-"
        << stl::Random::GetRandomValue<int>(100000000, 999999999);
    const std::string username = oss.str();
    const std::string password = "3871a960";
    // const std::string host = "gate-hk.kkoip.com";
    const std::string host = "162.128.174.76";
    const int port = 16586;
    const std::string proxy_string =
        username + ":" + password + "@" + host + ":" + std::to_string(port);
#if CURLCC_USE_SOCKS5
    curlProxyUrl = "socks5h://" + proxy_string;
#else
    curlProxyUrl = "http://" + proxy_string;
#endif
    chromiumProxyUrl = "socks5://" + proxy_string;
    result = true;
  } while (0);
#if ENABLE_DEVELOP_MODE
  std::cout << chromiumProxyUrl << std::endl;
#endif
  return result;
}
#endif