#include "config.h"

Config::Config() {
  Init();
}

Config::~Config() {
  UnInit();
}

void Config::Init() {
  do {
    current_process_path_.clear();
    char *path = nullptr;
    size_t path_size = 0;
    xs_sys_process_getpath(&path, &path_size);
    current_process_path_.append(path, path_size);
    xs_sys_free((void **)&path);
    current_process_path_ = stl::Path::PathnameToPath(current_process_path_);
  } while (0);

  do {
    work_projects_path_.clear();
    char *appdata = nullptr;
    size_t appdata_path_len = 0;
    xs_sys_get_appdata_path(&appdata, &appdata_path_len);
    work_projects_path_.append(appdata, appdata_path_len);
    xs_sys_free((void **)&appdata);
    work_projects_path_.append("/WorkProjects");
  } while (0);
}

void Config::UnInit() {
}
const std::string &Config::CurrentProcessPath() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return current_process_path_;
}
const std::string &Config::WorkProjectsPath() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return work_projects_path_;
}
////////////////////////////////////////////////////////////////////////////
static Config *__gpConfig = nullptr;
Config *Config::ConfigGet() {
  if (!__gpConfig)
    __gpConfig = new Config();
  return __gpConfig;
}
