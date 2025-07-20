#include "brwcfg.h"
/////////////////////////////////////////////////////////////////
Config::Config() {
  Init();
}
Config::~Config() {
  UnInit();
}
void Config::Init() {
  xs_buffer_t *dllpath = nullptr;
  do {
    static int static_dummy_variable;
    xs_sys_get_dll_path(&dllpath, &static_dummy_variable);
    if (!dllpath)
      break;
    std::string u8Dllpath(dllpath->buffer, dllpath->len);
    {
      std::u16string parent = Conv::u8_to_u16(u8Dllpath);
      std::u16string parent_path, filename, extension;

      stl::Path::ParsePathname(parent, parent_path, filename, extension,
                               path_.module_name);
    }
    path_.components_dir =
        stl::Path::PathnameToPath(Conv::u8_to_u16(u8Dllpath));
    path_.root = stl::Path::Parent(
        stl::Path::PathnameToPath(Conv::u8_to_u16(u8Dllpath)));
    path_.temp_dir = path_.root + u"/" + chromium::project_dirname_tmp;
    path_.chromium_envpath_route_path =
        path_.temp_dir + u"/" + chromium::project_filename_tmpcfgpath;

    path_.configure_path = path_.root + u"/" +
                           chromium::project_dirname_configures + u"/" +
                           chromium::project_filename_configure;
    path_.settings_path = path_.root + u"/" +
                          chromium::project_dirname_configures +
                          u"/settings.xml";
#if defined(__OSLINUX__)
    path_.libuvpp_path = path_.components_dir + u"/libuvpp.so";
#elif defined(__OSWIN__)
    path_.libuvpp_path = path_.components_dir + u"/libuvpp.dll";
#endif

    do {
      if (!stl::File::Exists(path_.chromium_envpath_route_path))
        break;
      std::string cfgPath =
          stl::File::ReadFile(path_.chromium_envpath_route_path);
      stl::File::Remove(path_.chromium_envpath_route_path);
      if (!stl::File::Exists(cfgPath))
        break;
      path_.configure_path = Conv::u8_to_u16(cfgPath);
    } while (0);
    configure_ =
        new chromium::IConfigure(stl::File::ReadFile(path_.configure_path));
    settings_ = new ISettings(stl::File::ReadFile(path_.settings_path));
    path_.logs_dir = path_.root + u"/logs";
    stl::Directory::Create(path_.logs_dir);
    path_.chromium_cache_dir =
        path_.root + u"/" + chromium::project_dirname_cache;
    std::string hexPolicyIdString = fmt::format("{:x}", configure_->policy.id);
    path_.chromium_userdata_dir =
        path_.chromium_cache_dir + u"/" + Conv::u8_to_u16(hexPolicyIdString);
    path_.chromium_userenv_dir =
        path_.chromium_userdata_dir + u"/" + chromium::project_dirname_chromium;
    stl::Directory::Create(Conv::u16_to_ws(path_.chromium_userenv_dir));
    path_.configure_cache_dir = path_.chromium_userenv_dir + u"/" +
                                chromium::project_dirname_configures;
    stl::Directory::Create(path_.configure_cache_dir);
    path_.configure_cache_path =
        path_.configure_cache_dir + u"/" + chromium::project_filename_configure;
    if (!stl::File::Exists(path_.configure_cache_path)) {
      stl::File::WriteFile(path_.configure_cache_path,
                           configure_->Serialization());
    }
  } while (0);
  xs_sys_free_buffer(&dllpath);
}
void Config::UnInit() {
  SK_DELETE_PTR(settings_);
  SK_DELETE_PTR(configure_);
}
const Config::Path &Config::GetPath() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return path_;
}
const ISettings &Config::GetSettings() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return *settings_;
}
const chromium::IConfigure &Config::GetConfigure() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return *configure_;
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