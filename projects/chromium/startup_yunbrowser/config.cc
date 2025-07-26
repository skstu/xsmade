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

    project_model_parts_dir_ = current_dir_ + "/model_parts";
    stl::Directory::Create(project_model_parts_dir_);

    project_model_dir_ = current_dir_ + "/model";
    stl::Directory::Create(project_model_dir_);
#if _DEBUG
    chromium_process_path_ =
        current_dir_ + "/browser/chromium/138.0.7204.158/YunBrowser.exe";
#else
    chromium_process_path_ = current_dir_ + "/YunBrowser.exe";
#endif
  } while (0);
}

void Config::UnInit() {
  LOG_UNINIT;
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