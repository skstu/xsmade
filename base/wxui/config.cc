#include "wxui.h"

Config::Config() {
  Init();
}
Config::~Config() {
  UnInit();
}
void Config::Init() {
  wxInitAllImageHandlers();
  do {
    std::string current = System::GetCurrentProcessPath();
    std::map<std::string, std::string> files, dirs;
    stl::Directory::EnumU8(current + "/res/images", dirs, files, false);
    if (files.empty())
      break;
    for (const auto &file : files) {
      wxImage *img = nullptr;
      if (!wxComm::LoadImg(file.second, &img))
        continue;
      imgres_.emplace(stl::String::Lower(file.first), img);
    }
  } while (0);
}
void Config::UnInit() {
  for (auto &it : imgres_)
    SK_DELETE_PTR(it.second);
  imgres_.clear();
}
void Config::SetFrameType(const FrameType &type) {
  std::lock_guard<std::mutex> lock{*mtx_};
  type_ = type;
}
const FrameType &Config::GetFrameType() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return type_;
}
ITheme *Config::CreateTheme() {
  Theme *result = nullptr;
  std::lock_guard<std::mutex> lock{*mtx_};
  result = new Theme();
  themes_.emplace_back(result);
  return dynamic_cast<ITheme *>(result);
}
const Theme *Config::GetTheme(const wxui::tfThemeIdentify &identify) const {
  const Theme *result = nullptr;
  std::lock_guard<std::mutex> lock{*mtx_};
  for (const auto &t : themes_) {
    if (t->Identify() == identify) {
      result = t;
      break;
    }
  }
  return result;
}
wxImage *Config::GetResImage(const std::string &imgName) const {
  wxImage *result = nullptr;
  std::lock_guard<std::mutex> lock{*mtx_};
  do {
    auto found = imgres_.find(stl::String::Lower(imgName));
    if (found == imgres_.end())
      break;
    result = found->second;
  } while (0);
  return result;
}
//////////////////////////////////////////////////////////
static Config *__gpConfig = nullptr;
Config *Config::Get() {
  if (!__gpConfig)
    __gpConfig = new Config();
  return __gpConfig;
}
void Config::Destroy() {
  if (__gpConfig) {
    delete __gpConfig;
    __gpConfig = nullptr;
  }
}