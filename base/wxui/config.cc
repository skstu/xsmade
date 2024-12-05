#include "wxui.h"

Config::Config() {
  Init();
}
Config::~Config() {
  UnInit();
}
void Config::Init() {
  do {
    wxInitAllImageHandlers();
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
void Config::SetResourceDir(const char *dir) {
  std::lock_guard<std::mutex> lock{*mtx_};
  resource_dir_ = dir ? dir : "";
  do {
    if (resource_dir_.empty())
      break;
    std::map<std::string, std::string> files, dirs;
    stl::Directory::EnumU8(resource_dir_, dirs, files, false);
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
void Config::RegisterRecordingStartCb(tfRecordingStartCb cb, void *route) {
  std::lock_guard<std::mutex> lock{*mtx_};
  recording_start_cb_ = cb;
  recording_start_cb_route_ = route;
}
void Config::RegisterRecordingStopCb(tfRecordingStopCb cb, void *route) {
  std::lock_guard<std::mutex> lock{*mtx_};
  recording_stop_cb_ = cb;
  recording_stop_cb_route_ = route;
}
void Config::OnRecordingStart(const IRecordingArgs *args) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (recording_start_cb_) {
    recording_start_cb_(args, recording_start_cb_route_);
  }
}
void Config::OnRecordingStop() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (recording_stop_cb_) {
    recording_stop_cb_(recording_stop_cb_route_);
  }
}
void Config::RegisterSystemExitCb(tfSystemExitCb cb, void *route) {
  std::lock_guard<std::mutex> lock{*mtx_};
  system_exit_cb_ = cb;
  system_exit_cb_route_ = route;
}
void Config::OnSystemExit() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (system_exit_cb_) {
    system_exit_cb_(system_exit_cb_route_);
  }
}
std::map<CommandTool, wxString> gpCommandToolTipMap = {
    {CommandTool::TOOL_SCALING_UP, wxT("比例缩放(大)")},
    {CommandTool::TOOL_SCALING_DOWN, wxT("比例缩放(小)")},
    {CommandTool::TOOL_RECORDING_START, wxT("开始录屏")},
    {CommandTool::TOOL_RECORDING_STOP, wxT("正在录制...")},
    {CommandTool::TOOL_SCREENSHOT, wxT("截屏")},
    {CommandTool::TOOL_SYSTEM_CLOSE, wxT("退出")},
    {CommandTool::TOOL_SETTINGS, wxT("设置")},
    {CommandTool::TOOL_WINDOW, wxT("选定区域")},
};
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