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

    configures_dir_ = current_dir_ + "/" +
                      Conv::u16_to_u8(chromium::project_dirname_configures);
    stl::Directory::Create(configures_dir_);
    stl::Directory::Create(
        current_dir_ + "/" +
        Conv::u16_to_u8(chromium::project_dirname_extensions));
    stl::Directory::Create(current_dir_ + "/" +
                           Conv::u16_to_u8(chromium::project_dirname_route));
    stl::Directory::Create(current_dir_ + "/" +
                           Conv::u16_to_u8(chromium::project_dirname_cache));
    stl::Directory::Create(current_dir_ + "/" +
                           Conv::u16_to_u8(chromium::project_dirname_tmp));
    configure_path_ = configures_dir_ + "/" +
                      Conv::u16_to_u8(chromium::project_filename_configure);
    settings_path_ = configures_dir_ + "/settings.xml";
    do {
      std::string buf = stl::File::ReadFile(settings_path_);
      if (buf.empty())
        break;
      settings_ = new ISettings(buf);
    } while (0);
    do {
      std::string tmp = current_dir_ + "/browser/chromium";
      if (!stl::Directory::Exists(tmp))
        break;
      std::map<std::string, std::string> dirs, files;
      stl::Directory::Enum(tmp, dirs, files, false);
      if (dirs.empty())
        break;
      for (const auto &dir : dirs) {
        std::string chrome_process = dir.second + "/Chromium.exe";
        if (!stl::File::Exists(chrome_process))
          continue;
        chromium_startup_process_[dir.first] = chrome_process;
      }
    } while (0);

  } while (0);
}

void Config::UnInit() {
}

const std::string &Config::GetCurrentDir() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return current_dir_;
}

std::string Config::GetChromiumProcess(const std::string &version) const {
  std::string result;
  std::lock_guard<std::mutex> lock(*mtx_);
  do {
    if (chromium_startup_process_.empty())
      break;
    if (version.empty()) {
      result = chromium_startup_process_.begin()->second;
    } else {
      auto it = chromium_startup_process_.find(version);
      if (it != chromium_startup_process_.end()) {
        result = it->second;
      } else {
        result = chromium_startup_process_.begin()
                     ->second; // Default to the first one if not found
      }
    }
  } while (0);
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