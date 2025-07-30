#include "config.h"

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
bool ModelLevel2::GetModel(chromium::xsiumio::IXSiumio &model) const {
  bool result = false;
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    if (model_.canvas.empty() || model_.webgl.empty() || model_.audio.empty() ||
        model_.font.empty() || model_.cpu_cores.empty() ||
        model_.device_memory.empty()) {
      break;
    }
    model.timestamp = stl::Time::TimeStamp<std::chrono::microseconds>();
    model.identify = model.timestamp;
    model.fps.rtt = stl::Random::GetRandomValue<uint32_t>(100, 500);
    model.fps.disk.quota =
        stl::Random::GetRandomValue<uint64_t>(1000000000, 5000000000);
    model.fps.disk.usage =
        stl::Random::GetRandomValue<uint64_t>(100000000, 500000000);
    model.fps.hardwareConcurrency =
        model_.cpu_cores[stl::Random::GetRandomValue<int>(
            0, model_.cpu_cores.size() - 1)];
    model.fps.deviceMemory =
        model_.device_memory[stl::Random::GetRandomValue<int>(
            0, model_.device_memory.size() - 1)];

    model.fps.canvas.hash.random = false;
    uint32_t canvas_base = stl::Random::GetRandomValue<int>(
        0, static_cast<uint32_t>(model_.canvas.size() - 1));
    model.fps.canvas.hash.base = model_.canvas[canvas_base].hash.base;

    model.fps.webgl.hash.random = false;
    uint32_t webgl_base = stl::Random::GetRandomValue<int>(
        0, static_cast<uint32_t>(model_.webgl.size() - 1));
    model.fps.webgl.hash.base = model_.webgl[webgl_base].hash.base;

    model.fps.audio.hash.random = false;
    uint32_t audio_base = stl::Random::GetRandomValue<int>(
        0, static_cast<uint32_t>(model_.audio.size() - 1));
    model.fps.audio.hash.base = model_.audio[audio_base].hash.base;

    model.fps.font.hash.random = false;
    uint32_t font_base = stl::Random::GetRandomValue<int>(
        0, static_cast<uint32_t>(model_.font.size() - 1));
    model.fps.font.hash.base = model_.font[font_base].hash.base;

    model.fps.font.allowlist.clear();
    for (const auto &fontFamily : model_.font[font_base].allowlist) {
      model.fps.font.allowlist.emplace(fontFamily);
    }
    result = true;
  } while (0);
  return result;
}