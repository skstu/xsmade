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
    // if (req.GetConfigure().GetID() < 0 || req.GetConfigure().GetID() >= 0xFF) {
    //   req.SetErrorCode(ErrorCode::InvalidBrowserID);
    //   break;
    // }
    // std::string cfg_data;
    // req.GetConfigure() >> cfg_data;
    // const std::string user_data_default_dir =
    //     req.GetConfigure().GetUserDataDir() + "/Chromium";
    // stl::Directory::Create(user_data_default_dir);
    // auto path = req.GetConfigure().GetTmpDir() + "/" +
    //             chromium::project_filename_tmpcfgpath;
    // if (!stl::File::WriteFile(
    //         path, req.GetConfigure().GetEnvironmentConfigurePath()) ||
    //     !stl::File::WriteFile(user_data_default_dir + "/" +
    //                               chromium::project_filename_configure,
    //                           cfg_data)) {
    //   req.SetErrorCode(ErrorCode::CreateBrowserEnvFailed);
    //   break;
    // }
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