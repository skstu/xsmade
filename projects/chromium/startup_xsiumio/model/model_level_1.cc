#include "config.h"
#if 0
namespace {
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
    //model.fps.screen.enable = true;
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
// 合理扰动区间结构体
struct ShaderPrecisionRange {
  int min, max;
};
// float类型主流区间
constexpr ShaderPrecisionRange kRangeMinF = {120, 127};
constexpr ShaderPrecisionRange kRangeMaxF = {127, 255};
constexpr ShaderPrecisionRange kPrecisionF = {10, 23};
// int类型主流区间
constexpr ShaderPrecisionRange kRangeMinI = {120, 127};
constexpr ShaderPrecisionRange kRangeMaxI = {127, 255};
constexpr ShaderPrecisionRange kPrecisionI = {0, 8};

// 扰动函数（支持特殊值采样）
template <typename T>
T SampleWithSpecials(T value, const ShaderPrecisionRange &range,
                     const std::vector<T> &specials, double special_prob = 0.1,
                     int delta = 2) {
  if (!specials.empty() &&
      stl::Random::GetRandomValue<double>(0, 1) < special_prob) {
    return specials[stl::Random::GetRandomValue<size_t>(0,
                                                        specials.size() - 1)];
  }
  int v = value + stl::Random::GetRandomValue<int>(-delta, delta);
  if (v < range.min)
    v = range.min;
  if (v > range.max)
    v = range.max;
  return static_cast<T>(v);
}

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

    if (!interference)
      break;
    // 其它WebGL参数扰动（保持原有逻辑）
    do {
      const std::vector<std::string> &s33902 = {"1,1", "16384,16384",
                                                "32767,32767"};
      const std::vector<std::string> &s33901 = {"1024", "2048", "4096", "8192",
                                                "16384"};
      const std::vector<std::string> &s3413 = {"0", "8"};
      const std::vector<std::string> &s3412 = {"0", "8"};
      const std::vector<std::string> &s3414 = {"16", "24", "32"};
      const std::vector<std::string> &s3411 = {"8"};
      const std::vector<std::string> &s34047 = {"8", "16", "32"};
      const std::vector<std::string> &s35661 = {"128", "256", "512"};
      const std::vector<std::string> &s34076 = {"8", "16", "32", "64", "16384"};
      const std::vector<std::string> &s36349 = {"1024", "2048", "4096", "8192",
                                                "16384"};
      const std::vector<std::string> &s34024 = {"1024", "2048", "4096", "8192",
                                                "16384"};
      const std::vector<std::string> &s34930 = {"8", "16", "32"};
      const std::vector<std::string> &s3379 = {"16", "32", "64", "128",
                                               "16384"};
      const std::vector<std::string> &s36348 = {"128", "256", "512"};
      const std::vector<std::string> &s34921 = {"8", "16", "32"};
      const std::vector<std::string> &s35660 = {"8", "16", "32"};
      const std::vector<std::string> &s36347 = {"128", "256", "512", "4096"};
      const std::vector<std::string> &s3386 = {"16384,16384", "32767,32767"};
      const std::vector<std::string> &s3410 = {"8"};
      const std::vector<std::string> &s3415 = {"0", "1"};

      model.fps.webgl.getParameter[3386] =
          s3386[stl::Random::GetRandomValue<size_t>(0, s3386.size() - 1)];
      model.fps.webgl.getParameter[34930] =
          s34930[stl::Random::GetRandomValue<size_t>(0, s34930.size() - 1)];
      model.fps.webgl.getParameter[33902] =
          s33902[stl::Random::GetRandomValue<size_t>(0, s33902.size() - 1)];
      model.fps.webgl.getParameter[33901] =
          s33901[stl::Random::GetRandomValue<size_t>(0, s33901.size() - 1)];
      model.fps.webgl.getParameter[3413] =
          s3413[stl::Random::GetRandomValue<size_t>(0, s3413.size() - 1)];
      model.fps.webgl.getParameter[3412] =
          s3412[stl::Random::GetRandomValue<size_t>(0, s3412.size() - 1)];
      model.fps.webgl.getParameter[3414] =
          s3414[stl::Random::GetRandomValue<size_t>(0, s3414.size() - 1)];
      model.fps.webgl.getParameter[3411] =
          s3411[stl::Random::GetRandomValue<size_t>(0, s3411.size() - 1)];
      model.fps.webgl.getParameter[34047] =
          s34047[stl::Random::GetRandomValue<size_t>(0, s34047.size() - 1)];
      model.fps.webgl.getParameter[35661] =
          s35661[stl::Random::GetRandomValue<size_t>(0, s35661.size() - 1)];
      model.fps.webgl.getParameter[34076] =
          s34076[stl::Random::GetRandomValue<size_t>(0, s34076.size() - 1)];
      model.fps.webgl.getParameter[36349] =
          s36349[stl::Random::GetRandomValue<size_t>(0, s36349.size() - 1)];
      model.fps.webgl.getParameter[34024] =
          s34024[stl::Random::GetRandomValue<size_t>(0, s34024.size() - 1)];
      model.fps.webgl.getParameter[3379] =
          s3379[stl::Random::GetRandomValue<size_t>(0, s3379.size() - 1)];
      model.fps.webgl.getParameter[36348] =
          s36348[stl::Random::GetRandomValue<size_t>(0, s36348.size() - 1)];
      model.fps.webgl.getParameter[34921] =
          s34921[stl::Random::GetRandomValue<size_t>(0, s34921.size() - 1)];
      model.fps.webgl.getParameter[35660] =
          s35660[stl::Random::GetRandomValue<size_t>(0, s35660.size() - 1)];
      model.fps.webgl.getParameter[36347] =
          s36347[stl::Random::GetRandomValue<size_t>(0, s36347.size() - 1)];
      model.fps.webgl.getParameter[3410] =
          s3410[stl::Random::GetRandomValue<size_t>(0, s3410.size() - 1)];
      model.fps.webgl.getParameter[3415] =
          s3415[stl::Random::GetRandomValue<size_t>(0, s3415.size() - 1)];

      model.fps.webgl.contextAttributes.alpha = stl::Random::GetRandomBool();
      model.fps.webgl.contextAttributes.antialias =
          stl::Random::GetRandomBool();
      model.fps.webgl.contextAttributes.depth = stl::Random::GetRandomBool();
      model.fps.webgl.contextAttributes.desynchronized = false;
      model.fps.webgl.contextAttributes.failIfMajorPerformanceCaveat =
          stl::Random::GetRandomBool();
      const std::vector<std::string> powerPreferences = {
          "default", "high-performance", "low-power"};
      // model.fps.webgl.contextAttributes.powerPreference =
      //     powerPreferences[stl::Random::GetRandomValue<size_t>(
      //         0, powerPreferences.size() - 1)];
      model.fps.webgl.contextAttributes.powerPreference = "default";
      model.fps.webgl.contextAttributes.premultipliedAlpha =
          stl::Random::GetRandomBool();
      model.fps.webgl.contextAttributes.preserveDrawingBuffer =
          stl::Random::GetRandomBool();
      model.fps.webgl.contextAttributes.stencil = stl::Random::GetRandomBool();
      model.fps.webgl.contextAttributes.xrCompatible =
          stl::Random::GetRandomBool();

      // float/int类型扰动（支持特殊值采样）
      auto &spf = model.fps.webgl.shaderPrecisionFormat;
      const std::vector<int> specialsF = {120, 127, 128, 255};
      // const std::vector<int> specialsI = {16, 24, 30, 31, 32, 127, 128, 255};
      const std::vector<int> specialsI = {30, 31, 32, 127, 128, 255};
      double special_prob = 0.88; // 约12%概率采样特殊值

#define PERTURB_F(v, r) SampleWithSpecials((v), (r), specialsF, special_prob, 3)
#define PERTURB_I(v, r) SampleWithSpecials((v), (r), specialsI, special_prob, 2)

      spf._8B30._8DF0.rangeMin =
          PERTURB_F(spf._8B30._8DF0.rangeMin, kRangeMinF);
      spf._8B30._8DF0.rangeMax =
          PERTURB_F(spf._8B30._8DF0.rangeMax, kRangeMaxF);
      spf._8B30._8DF0.precision =
          PERTURB_F(spf._8B30._8DF0.precision, kPrecisionF);
      spf._8B30._8DF1.rangeMin =
          PERTURB_F(spf._8B30._8DF1.rangeMin, kRangeMinF);
      spf._8B30._8DF1.rangeMax =
          PERTURB_F(spf._8B30._8DF1.rangeMax, kRangeMaxF);
      spf._8B30._8DF1.precision =
          PERTURB_F(spf._8B30._8DF1.precision, kPrecisionF);
      spf._8B30._8DF2.rangeMin =
          PERTURB_F(spf._8B30._8DF2.rangeMin, kRangeMinF);
      spf._8B30._8DF2.rangeMax =
          PERTURB_F(spf._8B30._8DF2.rangeMax, kRangeMaxF);
      spf._8B30._8DF2.precision =
          PERTURB_F(spf._8B30._8DF2.precision, kPrecisionF);
      spf._8B30._8DF3.rangeMin =
          PERTURB_F(spf._8B30._8DF3.rangeMin, kRangeMinF);
      spf._8B30._8DF3.rangeMax =
          PERTURB_F(spf._8B30._8DF3.rangeMax, kRangeMaxF);
      spf._8B30._8DF3.precision =
          PERTURB_F(spf._8B30._8DF3.precision, kPrecisionF);
      spf._8B30._8DF4.rangeMin =
          PERTURB_F(spf._8B30._8DF4.rangeMin, kRangeMinF);
      spf._8B30._8DF4.rangeMax =
          PERTURB_F(spf._8B30._8DF4.rangeMax, kRangeMaxF);
      spf._8B30._8DF4.precision =
          PERTURB_F(spf._8B30._8DF4.precision, kPrecisionF);
      spf._8B30._8DF5.rangeMin =
          PERTURB_F(spf._8B30._8DF5.rangeMin, kRangeMinF);
      spf._8B30._8DF5.rangeMax =
          PERTURB_F(spf._8B30._8DF5.rangeMax, kRangeMaxF);
      spf._8B30._8DF5.precision =
          PERTURB_F(spf._8B30._8DF5.precision, kPrecisionF);

      spf._8B31._8DF0.rangeMin =
          PERTURB_I(spf._8B31._8DF0.rangeMin, kRangeMinI);
      spf._8B31._8DF0.rangeMax =
          PERTURB_I(spf._8B31._8DF0.rangeMax, kRangeMaxI);
      spf._8B31._8DF0.precision =
          PERTURB_I(spf._8B31._8DF0.precision, kPrecisionI);
      spf._8B31._8DF1.rangeMin =
          PERTURB_I(spf._8B31._8DF1.rangeMin, kRangeMinI);
      spf._8B31._8DF1.rangeMax =
          PERTURB_I(spf._8B31._8DF1.rangeMax, kRangeMaxI);
      spf._8B31._8DF1.precision =
          PERTURB_I(spf._8B31._8DF1.precision, kPrecisionI);
      spf._8B31._8DF2.rangeMin =
          PERTURB_I(spf._8B31._8DF2.rangeMin, kRangeMinI);
      spf._8B31._8DF2.rangeMax =
          PERTURB_I(spf._8B31._8DF2.rangeMax, kRangeMaxI);
      spf._8B31._8DF2.precision =
          PERTURB_I(spf._8B31._8DF2.precision, kPrecisionI);
      spf._8B31._8DF3.rangeMin =
          PERTURB_I(spf._8B31._8DF3.rangeMin, kRangeMinI);
      spf._8B31._8DF3.rangeMax =
          PERTURB_I(spf._8B31._8DF3.rangeMax, kRangeMaxI);
      spf._8B31._8DF3.precision =
          PERTURB_I(spf._8B31._8DF3.precision, kPrecisionI);
      spf._8B31._8DF4.rangeMin =
          PERTURB_I(spf._8B31._8DF4.rangeMin, kRangeMinI);
      spf._8B31._8DF4.rangeMax =
          PERTURB_I(spf._8B31._8DF4.rangeMax, kRangeMaxI);
      spf._8B31._8DF4.precision =
          PERTURB_I(spf._8B31._8DF4.precision, kPrecisionI);
      spf._8B31._8DF5.rangeMin =
          PERTURB_I(spf._8B31._8DF5.rangeMin, kRangeMinI);
      spf._8B31._8DF5.rangeMax =
          PERTURB_I(spf._8B31._8DF5.rangeMax, kRangeMaxI);
      spf._8B31._8DF5.precision =
          PERTURB_I(spf._8B31._8DF5.precision, kPrecisionI);

#undef PERTURB_F
#undef PERTURB_I
    } while (0);

    // model.fps.webgl.enable = true;
    model.fps.webgl.contextAttributes.enable = true;
    model.fps.webgl.shaderPrecisionFormat.enable = true;
  } while (0);
}
} // namespace
ModelLevel1::ModelLevel1() {
}
ModelLevel1::~ModelLevel1() {
}
void ModelLevel1::Release() const {
  delete this;
}
const char *ModelLevel1::GetModelIdentify() const {
  return "Model-Level-1";
}
bool ModelLevel1::GetModel(chromium::xsiumio::IXSiumio &model) {
  bool result = false;
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    const int platform_key = 0;

    bool use_cache = model_result_.load() && !model_cache_.empty();
    if (use_cache) {
      model << model_cache_;
      result = true;
    }

    Output(model);
    if (use_cache)
      break;

    signal_proxy_use_count_.store(signal_proxy_use_count_.load() + 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(
        stl::Random::GetRandomValue<int>(1000, 5000))); //
    auto f_platform = fpsdb_.platform.source.find(platform_key);
    if (f_platform == fpsdb_.platform.source.end())
      break;
    model.startup.enable_cleanup_udd = true;
    model.fps.platform = f_platform->second;
    model.timestamp = stl::Time::TimeStamp<std::chrono::microseconds>();
    model.identify = model.timestamp;

    model.fps.do_not_track = "1";
    if (stl::Random::GetRandomBool()) {
      model.fps.do_not_track = "null";
    }

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

    model.fps.rtt = 0; // stl::Random::GetRandomValue<uint32_t>(20, 200);
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

    model.fps.webgl.hash.random = false;
    model.fps.webgl.hash.base =
        fpsdb_.hash_webgl.base[stl::Random::GetRandomValue<size_t>(
            0, fpsdb_.hash_webgl.base.size() - 1)];

    model.fps.audio.hash.random = false;
    model.fps.audio.hash.base =
        fpsdb_.hash_audio.base[stl::Random::GetRandomValue<size_t>(
            0, fpsdb_.hash_audio.base.size() - 1)];

    model.fps.webgl.hash.random = false;
    model.fps.webgl.hash.base =
        fpsdb_.hash_webgl.base[stl::Random::GetRandomValue<size_t>(
            0, fpsdb_.hash_webgl.base.size() - 1)];

    model.fps.v8.hash.random = false;
    model.fps.v8.hash.base =
        stl::Time::TimeStamp<std::chrono::microseconds>() * 1.0;

    model.fps.math.hash.random = false;
    model.fps.math.hash.base = stl::Random::GetRandomValue<double>(1e-6, 1e-8);

    //ConfigLanguages(platform_key, &fpsdb_, model);
    //ConfigBrowser(platform_key, &fpsdb_, model);
    ConfigWebglDevice(platform_key, &fpsdb_, model, true);
    ConfigScreen(platform_key, &fpsdb_, model);
    ConfigFont(platform_key, &fpsdb_, model);
    ConfigVoice(platform_key, &fpsdb_, model);
#if 0
    std::string output_webgl = fmt::format(
        "'{},{},{}','{},{},{}','{},{},{}','{},{},{}','{},{},{}','{},{},{}','{},"
        "{},{}','{},{},{}','{},{},{}','{},{},{}','{},{},{}','{},{},{}'",
        model.fps.webgl.shaderPrecisionFormat._8B30._8DF0.rangeMin,
        model.fps.webgl.shaderPrecisionFormat._8B30._8DF0.rangeMax,
        model.fps.webgl.shaderPrecisionFormat._8B30._8DF0.precision,
        model.fps.webgl.shaderPrecisionFormat._8B30._8DF1.rangeMin,
        model.fps.webgl.shaderPrecisionFormat._8B30._8DF1.rangeMax,
        model.fps.webgl.shaderPrecisionFormat._8B30._8DF1.precision,
        model.fps.webgl.shaderPrecisionFormat._8B30._8DF2.rangeMin,
        model.fps.webgl.shaderPrecisionFormat._8B30._8DF2.rangeMax,
        model.fps.webgl.shaderPrecisionFormat._8B30._8DF2.precision,
        model.fps.webgl.shaderPrecisionFormat._8B30._8DF3.rangeMin,
        model.fps.webgl.shaderPrecisionFormat._8B30._8DF3.rangeMax,
        model.fps.webgl.shaderPrecisionFormat._8B30._8DF3.precision,
        model.fps.webgl.shaderPrecisionFormat._8B30._8DF4.rangeMin,
        model.fps.webgl.shaderPrecisionFormat._8B30._8DF4.rangeMax,
        model.fps.webgl.shaderPrecisionFormat._8B30._8DF4.precision,
        model.fps.webgl.shaderPrecisionFormat._8B30._8DF5.rangeMin,
        model.fps.webgl.shaderPrecisionFormat._8B30._8DF5.rangeMax,
        model.fps.webgl.shaderPrecisionFormat._8B30._8DF5.precision,
        model.fps.webgl.shaderPrecisionFormat._8B31._8DF0.rangeMin,
        model.fps.webgl.shaderPrecisionFormat._8B31._8DF0.rangeMax,
        model.fps.webgl.shaderPrecisionFormat._8B31._8DF0.precision,
        model.fps.webgl.shaderPrecisionFormat._8B31._8DF1.rangeMin,
        model.fps.webgl.shaderPrecisionFormat._8B31._8DF1.rangeMax,
        model.fps.webgl.shaderPrecisionFormat._8B31._8DF1.precision,
        model.fps.webgl.shaderPrecisionFormat._8B31._8DF2.rangeMin,
        model.fps.webgl.shaderPrecisionFormat._8B31._8DF2.rangeMax,
        model.fps.webgl.shaderPrecisionFormat._8B31._8DF2.precision,
        model.fps.webgl.shaderPrecisionFormat._8B31._8DF3.rangeMin,
        model.fps.webgl.shaderPrecisionFormat._8B31._8DF3.rangeMax,
        model.fps.webgl.shaderPrecisionFormat._8B31._8DF3.precision,
        model.fps.webgl.shaderPrecisionFormat._8B31._8DF4.rangeMin,
        model.fps.webgl.shaderPrecisionFormat._8B31._8DF4.rangeMax,
        model.fps.webgl.shaderPrecisionFormat._8B31._8DF4.precision,
        model.fps.webgl.shaderPrecisionFormat._8B31._8DF5.rangeMin,
        model.fps.webgl.shaderPrecisionFormat._8B31._8DF5.rangeMax,
        model.fps.webgl.shaderPrecisionFormat._8B31._8DF5.precision);
    std::cout << "WebGL Shader Precision Format: " << output_webgl << std::endl;
#endif
#if 0
    model.fps.canvas.enable = stl::Random::GetRandomBool();
    model.fps.webgl.enable = stl::Random::GetRandomBool();
    model.fps.audio.enable = stl::Random::GetRandomBool();
    model.fps.v8.enable = stl::Random::GetRandomBool();
    model.fps.math.enable = stl::Random::GetRandomBool();
    model.fps.font.enable = stl::Random::GetRandomBool();
    model.fps.screen.enable = stl::Random::GetRandomBool();
    model.fps.voice.enable = stl::Random::GetRandomBool();
    if (stl::Random::GetRandomBool()) {
      model.fps.languages.clear();
      model.fps.acceptLanguage.clear();
    }
    if (stl::Random::GetRandomBool()) {
      model.fps.hardwareConcurrency = 0;
      model.fps.deviceMemory = 0;
    }
#endif
    result = true;
  } while (0);
  return result;
}
bool ModelLevel1::GetProxyInfo(chromium::xsiumio::IXSiumio &,std::string &chromiumProxyUrl,
                               std::string &curlProxyUrl,
                               const bool &useCache) {
  bool result = false;
  std::lock_guard<std::mutex> lock(*mtx_);
  do {
    if (!useCache)
      break;
    if (proxys_.empty())
      break;
    const size_t total = proxys_.size();
    size_t index = stl::Random::GetRandomValue<size_t>(0, total - 1);
    chromiumProxyUrl = proxys_[index];
    std::string tmp(chromiumProxyUrl);
    auto f_socks5 = tmp.find("socks5://");
    if (f_socks5 != std::string::npos) {
      curlProxyUrl = tmp.replace(f_socks5, strlen("socks5://"), "http://");
    } else if (chromiumProxyUrl.find("http://") != std::string::npos) {
      curlProxyUrl = chromiumProxyUrl;
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
    const std::string host = "gate-hk.kkoip.com";
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