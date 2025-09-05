#include "config.h"

Comps::Comps() {
  Init();
}
Comps::~Comps() {
  UnInit();
}
void Comps::Release() const {
  delete this;
}
void Comps::Init() {
  do { // libcurlcc
    std::string target_component_path;
    target_component_path =
        Config::CreateOrGet()->GetProjectComponentsDir() + "/libcurlcc.dll";
    if (!stl::File::Exists(target_component_path))
      break;
    auto pcmp = curl::ICurl::Create(target_component_path.c_str());
    if (!pcmp)
      break;
    comps_.emplace(CompKey::kCurl, pcmp);
  } while (0);
  do { // libicucc
    std::string target_component_path;
    target_component_path =
        Config::CreateOrGet()->GetProjectComponentsDir() + "/libicucc.dll";
    if (!stl::File::Exists(target_component_path))
      break;
    auto pcmp = IIcucc::Create(target_component_path.c_str());
    if (!pcmp)
      break;
    comps_.emplace(CompKey::kIcu, pcmp);
  } while (0);
}
void Comps::UnInit() {
}
bool Comps::Start() {
  do {
    if (open_.load())
      break;
    for (auto &[key, comp] : comps_) {
      comp->Start();
    }
    open_.store(true);
  } while (0);
  return open_.load();
}
void Comps::Stop() {
  do {
    if (!open_.load())
      break;
    for (auto &[key, comp] : comps_) {
      comp->Stop();
    }
    open_.store(false);
  } while (0);
}
/////////////////////////////////////////////////////////////////////
Comps *__gpsComps = nullptr;
Comps *Comps::CreateOrGet() {
  if (!__gpsComps)
    __gpsComps = new Comps();
  return __gpsComps;
}
void Comps::Destroy() {
  if (__gpsComps) {
    delete __gpsComps;
    __gpsComps = nullptr;
  }
}
