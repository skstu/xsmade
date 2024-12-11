#include "brwcfg.h"

Config::Config() {
}
Config::~Config() {
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