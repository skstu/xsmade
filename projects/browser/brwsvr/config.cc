#include "server.h"
Config::Config() {
  Init();
}
Config::~Config() {
  UnInit();
}
void Config::Init() {
  path_.init();
  default_configure_ = new brwcfg::IConfigure(
      stl::File::ReadFile(Conv::u16_to_u8(path_.configure_path)));
  std::string settings_buffer =
      stl::File::ReadFile(Conv::u16_to_u8(path_.settings_path));
  settings_ = new brwcfg::ISettings(settings_buffer);
  do {
    std::map<std::u16string, std::u16string> dirs, files;
    stl::Directory::Enum(path_.chromium_dir, dirs, files, false);
    for (const auto &node : dirs) {
      if (!stl::File::Exists(node.second + u"/fanbrowser.exe"))
        continue;
      chromes_[Conv::u16_to_u8(node.first)] = node.second + u"/fanbrowser.exe";
    }
  } while (0);
}
void Config::UnInit() {
  SK_DELETE_PTR(default_configure_);
  SK_DELETE_PTR(settings_);
}
const brwcfg::ISettings &Config::GetSettings(void) const {
  std::lock_guard<std::mutex> lck(*mtx_);
  return *settings_;
}
const brwcfg::IConfigure &Config::GetDefaultConfigure(void) const {
  std::lock_guard<std::mutex> lck(*mtx_);
  return *default_configure_;
}
const Config::Path &Config::GetPath(void) const {
  std::lock_guard<std::mutex> lck(*mtx_);
  return path_;
}
bool Config::CreateBrowserEnv(const browser_id_t &brwid,
                              const std::string &buffer) const {
  bool result = false;
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    if (buffer.empty())
      break;
    const std::string hexPolicyIdString = fmt::format("{:x}", brwid);
    // C:\Users\k34ub\source\skstu\xsmade\bin\cache\90fa4b4b8d7ac982\mpUserEnv\configures
    const std::u16string cfgDir = path_.cache_dir + u"/" +
                                  Conv::u8_to_u16(hexPolicyIdString) +
                                  u"/mpUserEnv/configures";
    stl::Directory::Create(cfgDir);
    const std::u16string cfgPath = cfgDir + u"/configure.json";
    stl::File::WriteFile(cfgPath, buffer);
    const std::u16string cfgPathRoutePath =
        path_.temp_dir + u"/configure_path.route";
    stl::File::Remove(cfgPathRoutePath);
    stl::File::WriteFile(cfgPathRoutePath, Conv::u16_to_u8(cfgPath));

    result = true;
  } while (0);

  return result;
}
std::u16string Config::GetChromiumUserDataDir(const browser_id_t &brwid) const {
  std::u16string result;
  std::lock_guard<std::mutex> lck(*mtx_);
  std::string hexPolicyIdString = fmt::format("{:x}", brwid);
  result = path_.cache_dir + u"/" + Conv::u8_to_u16(hexPolicyIdString);
  stl::Directory::Create(result);
  return result;
}
std::u16string Config::GetChromiumUserEnvDir(const browser_id_t &brwid) const {
  std::u16string result;
  std::lock_guard<std::mutex> lck(*mtx_);
  std::string hexPolicyIdString = fmt::format("{:x}", brwid);
  result = path_.cache_dir + u"/" + Conv::u8_to_u16(hexPolicyIdString) +
           u"/mpUserEnv";
  stl::Directory::Create(result);
  return result;
}
std::u16string Config::GetChrome(const std::string &brwver) const {
  std::u16string result;
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    if (chromes_.empty())
      break;
    auto it = chromes_.find(brwver);
    if (it == chromes_.end()) {
      result = chromes_.begin()->second;
      break;
    }
    result = it->second;
  } while (0);
  return result;
}
//////////////////////////////////////////////////////////////////////////////////////////

void Config::Path::init(void) {
  xs_buffer_t *tmppath = nullptr;
#if defined(__OSWIN__)
  static int static_dummy_variable;
  xs_sys_get_dll_path(&tmppath, &static_dummy_variable);
#elif defined(__OSLINUX__)
  static auto sfn = []() {};
  xs_sys_get_dll_path(&tmppath, (void *)&sfn);
#endif
  current_dir = Conv::u8_to_u16(std::string(tmppath->buffer, tmppath->len));
  std::u16string module_name;
  {
    std::u16string parent_path, filename, extension;
    stl::Path::ParsePathname(current_dir, parent_path, filename, extension,
                             module_name);
  }
  xs_sys_free((void **)&tmppath);
  current_dir = stl::Path::Parent(current_dir);
  root_dir = stl::Path::Parent(current_dir);
#if defined(__OSLINUX__)
  libuvpp_path = stl::Path::Absolute(root_dir + u"/components/libuvpp.so");
#else
  libuvpp_path = stl::Path::Absolute(root_dir + u"/components/libuvpp.dll");
#endif
  settings_path = stl::Path::Absolute(root_dir + u"/configures/settings.xml");
  configure_path =
      stl::Path::Absolute(root_dir + u"/configures/configure.json");
  temp_dir = stl::Path::Absolute(root_dir + u"/temp");
  browser_dir = stl::Path::Absolute(root_dir + u"/browser");
  chromium_dir = stl::Path::Absolute(browser_dir + u"/chromium");
  cache_dir = stl::Path::Absolute(root_dir + u"/cache");
  logs_path = stl::Path::Absolute(root_dir + u"/logs");
  stl::Directory::Create(temp_dir);
  stl::Directory::Create(logs_path);
  logs_path = stl::Path::Absolute(logs_path + u"/" + module_name + u".log");
}
//////////////////////////////////////////////////////////////////////////////////////////
static Config *__gpsConfig = nullptr;
Config *Config::GetOrCreate() {
  if (!__gpsConfig)
    __gpsConfig = new Config();
  return __gpsConfig;
}
void Config::Destroy() {
  SK_DELETE_PTR(__gpsConfig);
}