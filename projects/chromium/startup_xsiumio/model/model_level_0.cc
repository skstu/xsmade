#include "config.h"
ModelLevel0::ModelLevel0() {
}
ModelLevel0::~ModelLevel0() {
}
void ModelLevel0::Release() const {
  delete this;
}
const char *ModelLevel0::GetModelIdentify() const {
  std::lock_guard<std::mutex> lck(*mtx_);
  return "Model-Level-0";
}
const ModeType &ModelLevel0::GetModeType() const {
  std::lock_guard<std::mutex> lck(*mtx_);
  return mode_type_;
}
bool ModelLevel0::GenModel(const chromium::xsiumio::IXSiumio &input) {
  bool result = false;
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    const int platform_key = 0;
    auto f_platform = fpsdb_.platform.source.find(platform_key);
    if (f_platform == fpsdb_.platform.source.end())
      break;
    xscfg_ = input;
    xs_process_id_t parent_pid = 0;
    xs_sys_process_getpid(&parent_pid);
    xscfg_.startup.startup_pid =
        static_cast<decltype(xscfg_.startup.startup_pid)>(parent_pid);

    xscfg_.fps.platform = f_platform->second;

    if (xscfg_.seed <= 0)
      xscfg_.seed = stl::Time::GoogleTimestamp();

    xscfg_.fps.do_not_track = true;

    auto f_hardwareConcurrency =
        fpsdb_.hardwareConcurrency.source.find(platform_key);
    if (xscfg_.fps.hardwareConcurrency > 0 &&
        f_hardwareConcurrency != fpsdb_.hardwareConcurrency.source.end()) {
      xscfg_.fps.hardwareConcurrency =
          f_hardwareConcurrency->second[stl::Random::GetRandomValue<size_t>(
              0, f_hardwareConcurrency->second.size() - 1)];
    }

    auto f_deviceMemory = fpsdb_.deviceMemory.source.find(platform_key);
    if (xscfg_.fps.deviceMemory > 0 &&
        f_deviceMemory != fpsdb_.deviceMemory.source.end()) {
      xscfg_.fps.deviceMemory =
          f_deviceMemory->second[stl::Random::GetRandomValue<size_t>(
              0, f_deviceMemory->second.size() - 1)];
    }

    if (xscfg_.fps.rtt > 0) {
      xscfg_.fps.rtt = stl::Random::GetRandomValue<uint32_t>(20, 300);
    }
    xscfg_.fps.disk.quota = stl::Random::GetRandomValue<uint64_t>(
        50000000000, 2000000000000); // 50GB~2TB
    xscfg_.fps.disk.usage = stl::Random::GetRandomValue<uint64_t>(
        5000000000, 1000000000000); // 5GB~1TB

    xscfg_.fps.canvas.hash.random = false;
    xscfg_.fps.canvas.hash.base =
        stl::Random::GetRandomValue<unsigned int>(6666666, 888888);

    xscfg_.fps.webgl.hash.random = false;
    xscfg_.fps.webgl.hash.base =
        fpsdb_.hash_webgl.base[stl::Random::GetRandomValue<size_t>(
            0, fpsdb_.hash_webgl.base.size() - 1)];

    xscfg_.fps.audio.hash.random = false;
    xscfg_.fps.audio.hash.base =
        fpsdb_.hash_audio.base[stl::Random::GetRandomValue<size_t>(
            0, fpsdb_.hash_audio.base.size() - 1)];

    xscfg_.fps.webgl.hash.random = false;
    xscfg_.fps.webgl.hash.base =
        fpsdb_.hash_webgl.base[stl::Random::GetRandomValue<size_t>(
            0, fpsdb_.hash_webgl.base.size() - 1)];

    xscfg_.fps.v8.hash.random = false;
    xscfg_.fps.v8.hash.base =
        stl::Time::TimeStamp<std::chrono::microseconds>() * 1.0;

    xscfg_.fps.math.hash.random = false;
    xscfg_.fps.math.hash.base = stl::Random::GetRandomValue<double>(1e-6, 1e-8);
    do { //!@ select browser
      auto f_browser = fpsdb_.browsers.find(platform_key);
      if (f_browser == fpsdb_.browsers.end())
        break;
      if (f_browser->second.empty())
        break;
      const auto &brw = f_browser->second[stl::Random::GetRandomValue<size_t>(
          0, f_browser->second.size() - 1)];
      xscfg_.fps.product = brw.product;
      xscfg_.fps.userAgent = brw.userAgent;
      xscfg_.fps.userAgentMetadata = brw.userAgentMetadata;
      xscfg_.fps.userAgentMetadata.enable = true;
    } while (0);

    do { //!@ select device
      auto f_webgl_device = fpsdb_.webgl.source.find(platform_key);
      if (f_webgl_device == fpsdb_.webgl.source.end())
        break;
      if (f_webgl_device->second.empty())
        break;
      const auto &dev =
          f_webgl_device->second[stl::Random::GetRandomValue<size_t>(
              0, f_webgl_device->second.size() - 1)];
      xscfg_.fps.webgl.getParameter = dev.getParameter;
      xscfg_.fps.webgl.contextAttributes = dev.contextAttributes;
      xscfg_.fps.webgl.shaderPrecisionFormat = dev.shaderPrecisionFormat;
      xscfg_.fps.webgl.contextAttributes.enable = true;
      xscfg_.fps.webgl.shaderPrecisionFormat.enable = true;
    } while (0);

    // SettingBridgeProxy();
    Super();
    if (!model_result_.load()) {
      SaveXSCfg();
    }
    result = true;
  } while (0);
  return result;
}
