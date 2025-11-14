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
bool ModelLevel0::GenModel(chromium::xsiumio::IXSiumio &input) {
  bool result = false;
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    if (model_result_.load() && xscfg_.policy.reuse) {
      auto f = Config::CreateOrGet()->GetGenConfigPath();
      auto fb = stl::File::ReadFile(f);
      if (!fb.empty()) {
        std::cout << "Reuse existing config" << std::endl;
        input << fb;
        result = true;
        break;
      }
    }

    xscfg_ = input;

    InitPlatform();
    SelectBrowser();
    EnableGpu();
    UseAngleSwiftshader();
    InitFpsUtil();
    InitFpsHash();
    InitCdmRegistry();
    InitFont();
    InitATI();
    InitVoiceAndLanguages();

    Super();
    // SaveXSCfg();
    input = xscfg_;
    result = true;
  } while (0);
  return result;
}
