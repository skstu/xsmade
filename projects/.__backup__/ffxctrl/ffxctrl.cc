#include "config.h"

FFXCtrl::FFXCtrl() {
}

FFXCtrl::~FFXCtrl() {
}

bool FFXCtrl::Start() {
  do {
    if (open_.load())
      break;

    open_.store(true);
    std::vector<std::string> v;
    threads_.emplace_back([this]() { MainProc(); });
  } while (0);
  return open_.load();
}
void FFXCtrl::Stop() {
  do {
    if (!open_.load())
      break;
    open_.store(false);
    for (auto &t : threads_)
      t.join();
    threads_.clear();
  } while (0);
}
void FFXCtrl::MainProc() {
  do {
    wxDISABLE_DEBUG_SUPPORT();
    // wxApp::CheckBuildOptions(WX_BUILD_OPTIONS_SIGNATURE, "program");
    // wxLog::AddTraceMask(wxTRACE_Messages);
    // wxLogMessage("wxWidgets initialization started.");
    wxInitializer wxinit;
    if (!wxinit.IsOk())
      break;
    auto inst = wxApp::GetInstance();
    App *app = wxDynamicCast(inst, App);
    int rc = wxEntry(NULL);
    // config_->OnSystemExit(rc);
  } while (0);
}
/////////////////////////////////////////////////////////////////////
static FFXCtrl *__gpsFFXCtrl = nullptr;
FFXCtrl *FFXCtrl::Create() {
  if (!__gpsFFXCtrl)
    __gpsFFXCtrl = new FFXCtrl();
  return __gpsFFXCtrl;
}
void FFXCtrl::Destroy() {
  if (__gpsFFXCtrl) {
    delete __gpsFFXCtrl;
    __gpsFFXCtrl = nullptr;
  }
}

#ifdef __cplusplus
extern "C" {
#endif
SHARED_API void *interface_init(void *data, unsigned long len) {
  auto ffxctrl = FFXCtrl::Create();
  do {
    if (!data || len <= 0)
      break;

  } while (0);
  return reinterpret_cast<void *>(dynamic_cast<IFFXCtrl *>(ffxctrl));
}
SHARED_API void interface_uninit() {
  FFXCtrl::Destroy();
}
#ifdef __cplusplus
}
#endif