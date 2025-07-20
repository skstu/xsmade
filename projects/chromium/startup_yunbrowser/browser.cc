#include "config.h"

Browser::Browser() {
  Init();
}
Browser::~Browser() {
  UnInit();
}
void Browser::Init() {
  // Initialization code for the browser can go here
}
void Browser::UnInit() {
  // Cleanup code for the browser can go here
}
bool Browser::CreateChromium(IRequest &req) {
  bool result = false;
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    if (req.GetConfigure().id) {
      req.SetErrorCode(ErrorCode::InvalidBrowserID);
      break;
    }
    std::string cfg_data;
    req.GetConfigure() >> cfg_data;
    if (cfg_data.empty()) {
      req.SetErrorCode(ErrorCode::InvalidConfigureData);
      break;
    }
    const std::string chromium_runtime_dir =
        Config::CreateOrGet()->GetChromiumRuntimeDirectory(
            req.GetConfigure().id);
    const std::string cfgdata_path =
        chromium_runtime_dir + "/" + chromium::cfg::project_dirname_configures +
        "/" + chromium::cfg::project_filename_configure;
    stl::Directory::Create(chromium_runtime_dir);
    stl::File::WriteFile(cfgdata_path, cfg_data);
    stl::File::WriteFile(Config::CreateOrGet()->GetChromiumRoutingCfgfilePath(),
                         cfgdata_path);
    IChromium *chrome = new IChromium();
    if (!chrome->Open()) {
      req.SetErrorCode(ErrorCode::BrwProcessOpenFailed);
      chrome->Release();
      break;
    }

    req.SetErrorCode(ErrorCode::Success);
    result = true;
  } while (0);
  return result;
}
void Browser::DestroyChromium(IRequest &req) {
  std::lock_guard<std::mutex> lck(*mtx_);
}
//////////////////////////////////////////////////////////////
static Browser *__gpBrowser = nullptr;
Browser *Browser::CreateOrGet() {
  if (!__gpBrowser) {
    __gpBrowser = new Browser();
  }
  return __gpBrowser;
}
void Browser::Destroy() {
  if (__gpBrowser) {
    delete __gpBrowser;
    __gpBrowser = nullptr;
  }
}