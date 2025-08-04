#include "config.h"

namespace {
static void SwitchPlatform(const int &platform_key,
                           const chromium::xsiumio::IFpsdb *fpsdb,
                           chromium::xsiumio::IXSiumio &model) {
  do {
    auto f_userAgentMetadata =
        fpsdb->userAgentMetadata.source.find(platform_key);
    if (f_userAgentMetadata == fpsdb->userAgentMetadata.source.end())
      break;
    if (f_userAgentMetadata->second.empty())
      break;
    auto userAgentMetadata =
        f_userAgentMetadata->second[stl::Random::GetRandomValue<size_t>(
            0, f_userAgentMetadata->second.size() - 1)];
    model.fps.userAgentMetadata.full_version = userAgentMetadata.full_version;
    model.fps.userAgentMetadata.platform = userAgentMetadata.platform;
    model.fps.userAgentMetadata.platform_version =
        userAgentMetadata.platform_version;
    model.fps.userAgentMetadata.architecture = userAgentMetadata.architecture;
    model.fps.userAgentMetadata.model = userAgentMetadata.model;
    model.fps.userAgentMetadata.mobile = userAgentMetadata.mobile;
    model.fps.userAgentMetadata.bitness = userAgentMetadata.bitness;
    model.fps.userAgentMetadata.wow64 = userAgentMetadata.wow64;
    model.fps.userAgentMetadata.form_factors.clear();
    for (const auto &item : userAgentMetadata.form_factors) {
      if (item.empty())
        continue;
      model.fps.userAgentMetadata.form_factors.emplace_back(item);
    }
  } while (0);
}
static void SwitchWebglDevice(const int &platform_key,
                              const chromium::xsiumio::IFpsdb *fpsdb,
                              chromium::xsiumio::IXSiumio &model) {
  auto f_webgl_device = fpsdb->webgl.devices.find(platform_key);
  do {
    if (f_webgl_device == fpsdb->webgl.devices.end())
      break;
    if (f_webgl_device->second.empty())
      break;
    auto webgl_device =
        f_webgl_device->second[stl::Random::GetRandomValue<size_t>(
            0, f_webgl_device->second.size() - 1)];

    model.fps.webgl.getParameter.clear();
    for (const auto &item : webgl_device.getParameter.source) {
      model.fps.webgl.getParameter[item.first] = item.second;
    }
#if 0
    model.fps.webgl.contextAttributes.alpha = stl::Random::GetRandomBool();
    model.fps.webgl.contextAttributes.depth = stl::Random::GetRandomBool();
    model.fps.webgl.contextAttributes.stencil = stl::Random::GetRandomBool();
    model.fps.webgl.contextAttributes.antialias = stl::Random::GetRandomBool();
    model.fps.webgl.contextAttributes.premultipliedAlpha =
        stl::Random::GetRandomBool();
    model.fps.webgl.contextAttributes.preserveDrawingBuffer =
        stl::Random::GetRandomBool();
    model.fps.webgl.contextAttributes.failIfMajorPerformanceCaveat =
        stl::Random::GetRandomBool();
    const std::vector<std::string> powerPreferences = {
        "default", "high-performance", "low-power"};
    model.fps.webgl.contextAttributes.powerPreference =
        powerPreferences[stl::Random::GetRandomValue<size_t>(
            0, powerPreferences.size() - 1)];
    model.fps.webgl.contextAttributes.xrCompatible =
        stl::Random::GetRandomBool();
#endif

    model.fps.webgl.contextAttributes.alpha =
        webgl_device.contextAttributes.alpha;
    model.fps.webgl.contextAttributes.depth =
        webgl_device.contextAttributes.depth;
    model.fps.webgl.contextAttributes.stencil =
        webgl_device.contextAttributes.stencil;
    model.fps.webgl.contextAttributes.antialias =
        webgl_device.contextAttributes.antialias;
    model.fps.webgl.contextAttributes.premultipliedAlpha =
        webgl_device.contextAttributes.premultipliedAlpha;
    model.fps.webgl.contextAttributes.preserveDrawingBuffer =
        webgl_device.contextAttributes.preserveDrawingBuffer;
    model.fps.webgl.contextAttributes.failIfMajorPerformanceCaveat =
        webgl_device.contextAttributes.failIfMajorPerformanceCaveat;
    model.fps.webgl.contextAttributes.powerPreference =
        webgl_device.contextAttributes.powerPreference;
    model.fps.webgl.contextAttributes.xrCompatible =
        webgl_device.contextAttributes.xrCompatible;

    model.fps.webgl.shaderPrecisionFormat._8B30._8DF0.rangeMin =
        webgl_device.shaderPrecisionFormat._8B30._8DF0.rangeMin;
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF0.rangeMax =
        webgl_device.shaderPrecisionFormat._8B30._8DF0.rangeMax;
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF0.precision =
        webgl_device.shaderPrecisionFormat._8B30._8DF0.precision;
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF1.rangeMin =
        webgl_device.shaderPrecisionFormat._8B30._8DF1.rangeMin;
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF1.rangeMax =
        webgl_device.shaderPrecisionFormat._8B30._8DF1.rangeMax;
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF1.precision =
        webgl_device.shaderPrecisionFormat._8B30._8DF1.precision;
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF2.rangeMin =
        webgl_device.shaderPrecisionFormat._8B30._8DF2.rangeMin;
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF2.rangeMax =
        webgl_device.shaderPrecisionFormat._8B30._8DF2.rangeMax;
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF2.precision =
        webgl_device.shaderPrecisionFormat._8B30._8DF2.precision;
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF3.rangeMin =
        webgl_device.shaderPrecisionFormat._8B30._8DF3.rangeMin;
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF3.rangeMax =
        webgl_device.shaderPrecisionFormat._8B30._8DF3.rangeMax;
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF3.precision =
        webgl_device.shaderPrecisionFormat._8B30._8DF3.precision;
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF4.rangeMin =
        webgl_device.shaderPrecisionFormat._8B30._8DF4.rangeMin;
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF4.rangeMax =
        webgl_device.shaderPrecisionFormat._8B30._8DF4.rangeMax;
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF4.precision =
        webgl_device.shaderPrecisionFormat._8B30._8DF4.precision;
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF5.rangeMin =
        webgl_device.shaderPrecisionFormat._8B30._8DF5.rangeMin;
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF5.rangeMax =
        webgl_device.shaderPrecisionFormat._8B30._8DF5.rangeMax;
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF5.precision =
        webgl_device.shaderPrecisionFormat._8B30._8DF5.precision;

    model.fps.webgl.shaderPrecisionFormat._8B31._8DF0.rangeMin =
        webgl_device.shaderPrecisionFormat._8B31._8DF0.rangeMin;
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF0.rangeMax =
        webgl_device.shaderPrecisionFormat._8B31._8DF0.rangeMax;
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF0.precision =
        webgl_device.shaderPrecisionFormat._8B31._8DF0.precision;
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF1.rangeMin =
        webgl_device.shaderPrecisionFormat._8B31._8DF1.rangeMin;
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF1.rangeMax =
        webgl_device.shaderPrecisionFormat._8B31._8DF1.rangeMax;
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF1.precision =
        webgl_device.shaderPrecisionFormat._8B31._8DF1.precision;
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF2.rangeMin =
        webgl_device.shaderPrecisionFormat._8B31._8DF2.rangeMin;
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF2.rangeMax =
        webgl_device.shaderPrecisionFormat._8B31._8DF2.rangeMax;
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF2.precision =
        webgl_device.shaderPrecisionFormat._8B31._8DF2.precision;
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF3.rangeMin =
        webgl_device.shaderPrecisionFormat._8B31._8DF3.rangeMin;
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF3.rangeMax =
        webgl_device.shaderPrecisionFormat._8B31._8DF3.rangeMax;
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF3.precision =
        webgl_device.shaderPrecisionFormat._8B31._8DF3.precision;
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF4.rangeMin =
        webgl_device.shaderPrecisionFormat._8B31._8DF4.rangeMin;
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF4.rangeMax =
        webgl_device.shaderPrecisionFormat._8B31._8DF4.rangeMax;
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF4.precision =
        webgl_device.shaderPrecisionFormat._8B31._8DF4.precision;
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF5.rangeMin =
        webgl_device.shaderPrecisionFormat._8B31._8DF5.rangeMin;
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF5.rangeMax =
        webgl_device.shaderPrecisionFormat._8B31._8DF5.rangeMax;
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF5.precision =
        webgl_device.shaderPrecisionFormat._8B31._8DF5.precision;
  } while (0);
}

} // namespace

ModelLevel0::ModelLevel0() {
}
ModelLevel0::~ModelLevel0() {
}
void ModelLevel0::Release() const {
  delete this;
}
const char *ModelLevel0::GetModelIdentify() const {
  return "Model-Level-0";
}
bool ModelLevel0::GetModel(chromium::xsiumio::IXSiumio &model) const {
  bool result = false;
  std::lock_guard<std::mutex> lck(*mtx_);
  const auto *fpsdb = Startup::GetOrCreate()->GetFpsdb();
  do {
    if (!fpsdb)
      break;
    const int platform_key = 0;
    std::mt19937_64 model_rng(model.timestamp);
    // Not.A/Brand --136
#if 0
[
            [
                "Chromium",
                "136"
            ],
            [
                "Google Chrome",
                "136"
            ],
            [
                "Not.A/Brand",
                "99"
            ]
        ],
        [
            [
                "Chromium",
                "136.0.7103.114"
            ],
            [
                "Google Chrome",
                "136.0.7103.114"
            ],
            [
                "Not.A/Brand",
                "99.0.0.0"
            ]
        ]
#endif
    // Not;A=Brand --139
#if 0
[
        "x86",
        "64",
        [
            [
                "Not;A=Brand",
                "8"
            ],
            [
                "Chromium",
                "139"
            ],
            [
                "Google Chrome",
                "139"
            ]
        ],
        [
            [
                "Not;A=Brand",
                "8.0.0.0"
            ],
            [
                "Chromium",
                "139.0.7248.0"
            ],
            [
                "Google Chrome",
                "139.0.7248.0"
            ]
        ],
        "0",
        "",
        "Windows",
        "10.0.0"
    ]
#endif
    model.timestamp = stl::Time::TimeStamp<std::chrono::microseconds>();
    model.identify = model.timestamp;

    auto f_hardwareConcurrency =
        fpsdb->hardwareConcurrency.source.find(platform_key);
    if (f_hardwareConcurrency != fpsdb->hardwareConcurrency.source.end()) {
      model.fps.hardwareConcurrency =
          f_hardwareConcurrency->second[stl::Random::GetRandomValue<size_t>(
              0, f_hardwareConcurrency->second.size() - 1)];
    }

    auto f_deviceMemory = fpsdb->deviceMemory.source.find(platform_key);
    if (f_deviceMemory != fpsdb->deviceMemory.source.end()) {
      model.fps.deviceMemory =
          f_deviceMemory->second[stl::Random::GetRandomValue<size_t>(
              0, f_deviceMemory->second.size() - 1)];
    }

    model.fps.rtt = stl::Random::GetRandomValue<uint32_t>(50, 300);
    model.fps.disk.quota =
        stl::Random::GetRandomValue<uint64_t>(1000000000, 5000000000);
    model.fps.disk.usage =
        stl::Random::GetRandomValue<uint64_t>(100000000, 500000000);

    model.fps.canvas.hash.random = false;
    model.fps.canvas.hash.base =
        fpsdb->hash_canvas.base[stl::Random::GetRandomValue<size_t>(
            0, fpsdb->hash_canvas.base.size() - 1)];

    model.fps.webgl.hash.random = false;
    model.fps.webgl.hash.base =
        fpsdb->hash_webgl.base[stl::Random::GetRandomValue<size_t>(
            0, fpsdb->hash_webgl.base.size() - 1)];

    SwitchPlatform(platform_key, fpsdb, model);

    SwitchWebglDevice(platform_key, fpsdb, model);

    model.fps.audio.hash.random = false;
    model.fps.audio.hash.base =
        fpsdb->hash_audio.base[stl::Random::GetRandomValue<size_t>(
            0, fpsdb->hash_audio.base.size() - 1)];

    auto f_screen = fpsdb->screen.source.find(platform_key);
    if (f_screen != fpsdb->screen.source.end()) {
      auto screen_info = f_screen->second[stl::Random::GetRandomValue<size_t>(
          0, f_screen->second.size() - 1)];

      model.fps.screen.devicePixelRatio = screen_info.devicePixelRatio;
      model.fps.screen.width = screen_info.width;
      model.fps.screen.height = screen_info.height;
      model.fps.screen.colorDepth = screen_info.colorDepth;
      model.fps.screen.pixelDepth = screen_info.pixelDepth;
      model.fps.screen.availLeft = screen_info.availLeft;
      model.fps.screen.availTop = screen_info.availTop;
      model.fps.screen.availHeight =
          screen_info.availHeight * model.fps.screen.devicePixelRatio;
      model.fps.screen.availWidth =
          screen_info.availWidth * model.fps.screen.devicePixelRatio;
      model.fps.screen.dpi.x = screen_info.dpi.x;
      model.fps.screen.dpi.y = screen_info.dpi.y;
    }

    auto f_font = fpsdb->font.find(platform_key);
    if (f_font != fpsdb->font.end()) {
      model.fps.font.allowlist.clear();

      std::vector<std::string> fonts = f_font->second.family;
      const size_t total = fonts.size();
      size_t remove_count =
          stl::Random::GetRandomValue<int>(1, static_cast<int>(total / 2) - 1);
      std::shuffle(fonts.begin(), fonts.end(), model_rng);
      remove_count = std::min(remove_count, fonts.size());
      for (size_t i = 0; i < remove_count; ++i) {
        fonts.erase(fonts.begin());
      }
      for (const auto &fontFamily : fonts) {
        model.fps.font.allowlist.emplace(fontFamily);
      }
    }

    { //!@ Voice
      auto voice = fpsdb->voice;
      std::shuffle(voice.begin(), voice.end(), model_rng);
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
    }

    result = true;
  } while (0);
  return result;
}
