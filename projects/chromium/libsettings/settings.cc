#include "settings.h"
/////////////////////////////////////////////////////////////////
Settings::Settings() {
  Init();
}
Settings::~Settings() {
  UnInit();
}
void Settings::Release() const {
  delete this;
}
void Settings::Init() {
}
void Settings::UnInit() {
}
bool Settings::operator<<(const std::string &xmlData) {
  bool result = false;
  std::lock_guard<std::mutex> lock(*mtx_);
  do {
    if (xmlData.empty())
      break;
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError xmlErr = doc.Parse(xmlData.c_str(), xmlData.size());
    if (xmlErr != tinyxml2::XML_SUCCESS)
      break;

    tinyxml2::XMLNode *node_settings = doc.FirstChildElement("settings");
    if (!node_settings)
      break;

    result = true;
  } while (0);
  return result;
}
//////////////////////////////////////////////////////////////////////////////////////////
static Settings *__gpsConfig = nullptr;
Settings *Settings::GetOrCreate() {
  if (!__gpsConfig)
    __gpsConfig = new Settings();
  return __gpsConfig;
}
void Settings::Destroy() {
  if (__gpsConfig)
    __gpsConfig->Release();
  __gpsConfig = nullptr;
}

extern "C" {
SHARED_API void *interface_init(void *data, unsigned long len) {
  auto p = Settings::GetOrCreate();
  if (data && len > 0) {
    *p << std::string((const char *)data, len);
  }
  return reinterpret_cast<void *>(
      dynamic_cast<IXSiumioSettings *>(Settings::GetOrCreate()));
}
SHARED_API void interface_uninit(void) {
  Settings::Destroy();
}
} // extern "C"