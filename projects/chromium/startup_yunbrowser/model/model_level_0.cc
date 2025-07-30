#include "config.h"

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

    model.fps.hardwareConcurrency = 0;
    
    if (stl::Random::GetRandomBool()) {
      model.fps.deviceMemory = 0;
    }

    model.fps.rtt = stl::Random::GetRandomValue<uint32_t>(50, 300);
    model.fps.disk.enable = stl::Random::GetRandomBool();
    model.fps.disk.quota =
        stl::Random::GetRandomValue<uint64_t>(1000000000, 5000000000);
    model.fps.disk.usage =
        stl::Random::GetRandomValue<uint64_t>(100000000, 500000000);

    model.fps.canvas.enable = stl::Random::GetRandomBool();
    model.fps.canvas.hash.random = false;
    model.fps.canvas.hash.base =
        fpsdb->hash_canvas.base[stl::Random::GetRandomValue<size_t>(
            0, fpsdb->hash_canvas.base.size() - 1)];
    model.fps.webgl.hash.random = false;
    model.fps.webgl.hash.base =
        fpsdb->hash_webgl.base[stl::Random::GetRandomValue<size_t>(
            0, fpsdb->hash_webgl.base.size() - 1)];

    model.fps.audio.enable = stl::Random::GetRandomBool();
    model.fps.audio.hash.random = false;
    model.fps.audio.hash.base =
        fpsdb->hash_audio.base[stl::Random::GetRandomValue<size_t>(
            0, fpsdb->hash_audio.base.size() - 1)];

    model.fps.font.enable = stl::Random::GetRandomBool();
    model.fps.font.hash.random = false;

    result = true;
  } while (0);
  return result;
}
