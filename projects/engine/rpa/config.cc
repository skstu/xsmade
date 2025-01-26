#include "brwcfg.h"
Config::Config() {
}
Config::~Config() {
}
bool Config::EnableDevTools(void) const {
  return true;
}
bool Config::EnableShowBadFlagsSecurityWarnings(void) const {
  return true;
}
bool Config::EnableSessionCrashedBubbleViewShow(void) const {
  return true;
}
bool Config::EnableLockFirstTabPage(void) const {
  return false;
}
bool Config::EnableProductLogo(void) const {
  return false;
}

///////////////////////////////////////////////////////////////////////
static Config *__gspConfig = nullptr;
Config *Config::Create() {
  if (!__gspConfig)
    __gspConfig = new Config();
  return __gspConfig;
}
void Config::Destroy() {
  SK_DELETE_PTR(__gspConfig);
}
