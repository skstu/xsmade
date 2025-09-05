#include "config.h"

Config::Config() {
  Init();
}

Config::~Config() {
  UnInit();
}

void Config::Init() {
  do {
    char *current_path = nullptr;
    size_t current_path_size = 0;
    xs_sys_process_getpath(&current_path, &current_path_size);
    current_dir_.append(current_path, current_path_size);
    xs_sys_free((void **)&current_path);

    project_logs_dir_ = current_dir_ + "/logs";
    stl::Directory::Create(project_logs_dir_);
    LOG_INIT(Conv::u8_to_u16(project_logs_dir_) + u"/main.log");

    project_tmp_dir_ = current_dir_ + "/tmp";
    stl::Directory::Create(project_tmp_dir_);

    project_route_dir_ = current_dir_ + "/route";
    stl::Directory::Create(project_route_dir_);

    project_model_parts_dir_ = current_dir_ + "/model_parts";
    stl::Directory::Create(project_model_parts_dir_);

    project_model_dir_ = current_dir_ + "/model";
    stl::Directory::Create(project_model_dir_);

    project_configures_dir_ = current_dir_ + "/configures";
    stl::Directory::Create(project_configures_dir_);

    project_components_path_ = current_dir_ + "/components";
    stl::Directory::Create(project_components_path_);

    project_settings_dir_ = current_dir_ + "/settings";
    stl::Directory::Create(project_settings_dir_);

    project_cache_dir_ = current_dir_ + "/cache";
    chromium_process_path_ = current_dir_ + "/browser/chromium/" +
                             GetChromiumVersion() + "/" +
                             GetChromiumProcessName();
    project_root_dir_ = current_dir_;

    project_bridge_process_name_ = "XSiumioBridge.exe";
    project_bridge_process_path_ =
        project_components_path_ + "/" + project_bridge_process_name_;

    project_xscfg_path_ =
        project_configures_dir_ + "/" + chromium::xsiumio::kObjectKey + ".json";

    project_gen_configure_path_ =
        project_route_dir_ + "/" + chromium::xsiumio::kObjectKey + ".json";
    stl::Directory::Create(project_cache_dir_);
  } while (0);
}

void Config::UnInit() {
  LOG_UNINIT;
}
const std::string &Config::GetGenConfigPath() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return project_gen_configure_path_;
}
const std::string &Config::GetBridgeProcessName() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return project_bridge_process_name_;
}
const std::string &Config::GetBridgeProcessPath() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return project_bridge_process_path_;
}
std::string Config::GetChromiumProcessName() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return std::string(chromium::xsiumio::kObjectKey) + ".exe";
}
std::string Config::GetChromiumVersion() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return "138.0.7204.158";
}
const std::string &Config::GetProjectXSCfgPath() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return project_xscfg_path_;
}
const std::string &Config::GetProjectRootDir() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return project_root_dir_;
}
const std::string &Config::GetCurrentDir() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return current_dir_;
}
const std::string &Config::GetProjectLogsDir() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return project_logs_dir_;
}
const std::string &Config::GetProjectTmpDir() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return project_tmp_dir_;
}
const std::string &Config::GetChromiumProcessPath() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return chromium_process_path_;
}
const std::string &Config::GetProjectModelPartsDir() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return project_model_parts_dir_;
}
const std::string &Config::GetProjectModelDir() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return project_model_dir_;
}
const std::string &Config::GetProjectRouteDir() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return project_route_dir_;
}
const std::string &Config::GetProjectCacheDir() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return project_cache_dir_;
}
const std::string &Config::GetProjectConfiguresDir() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return project_configures_dir_;
}
const std::string &Config::GetProjectComponentsDir() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return project_components_path_;
}
const std::string &Config::GetProjectSettingsDir() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return project_settings_dir_;
}
std::string Config::GetChromiumUserDataDir(
    const chromium::xsiumio::tfIdentifyType &brwid) const {
  std::string result;
  std::lock_guard<std::mutex> lock(*mtx_);
  if (brwid <= 0) {
    result = project_cache_dir_ + "/" +
             chromium::xsiumio::kProjectDirnameDefaultUserData;
  } else {
    std::ostringstream ss;
    ss << std::setw(16) << std::setfill('0') << std::hex << brwid;
    std::string hexStr = ss.str();
    result = project_cache_dir_ + "/" + hexStr;
  }
  return result;
}
////////////////////////////////////////////////////////////////////////////
static Config *__gpConfig = nullptr;
Config *Config::CreateOrGet() {
  if (!__gpConfig) {
    __gpConfig = new Config();
  }
  return __gpConfig;
}
void Config::Destroy() {
  if (__gpConfig) {
    delete __gpConfig;
    __gpConfig = nullptr;
  }
}
bool Config::DevelopMode() {
  bool result = false;
  if (__gpConfig && __gpConfig->settings_) {
    result = __gpConfig->settings_->enable_devmode;
  }
  return result;
}