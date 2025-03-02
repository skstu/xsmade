#include "ui.h"

using namespace ui;

IWxui::IWxui() {
  Init();
}
IWxui::~IWxui() {
  UnInit();
}
void IWxui::Init() {
}
void IWxui::UnInit() {
}
bool IWxui::Start() {
  do {
    if (open_.load())
      break;
    open_.store(true);
    threads_.emplace_back([this]() { MainProc(); });
  } while (0);
  return open_.load();
}
void IWxui::Stop() {
  do {
    if (!open_.load())
      break;
    IApp::NotifyAppDestroy();
    open_.store(false);
    for (auto &t : threads_)
      t.join();
    threads_.clear();
  } while (0);
}
void IWxui::MainProc() {
  do {
    wxDISABLE_DEBUG_SUPPORT();
    wxInitializer wxinit;
    if (!wxinit.IsOk())
      break;
#ifdef _WIN32
    SetProcessDPIAware();
#else
    wxSystemOptions::SetOption("msw.window-dpi-aware", 1);
#endif

#if defined(__OSMAC__)
    int argc = 1;
    char *argv[] = {const_cast<char *>("myapp")};
    int rc = wxEntry(argc, argv);
#elif defined(__OSWIN__)
    int rc = wxEntry(__argc, __argv);
#endif
    // Config::Get()->OnSystemExit();
    auto ss = 0;
  } while (0);
}
//////////////////////////////////////////////////////////////////////////////
static IWxui *__gpWxui = nullptr;
IWxui *IWxui::Create() {
  if (!__gpWxui) {
    __gpWxui = new IWxui();
    __gpWxui->Start();
  }
  return __gpWxui;
}
void IWxui::Destroy() {
  if (__gpWxui)
    __gpWxui->Stop();
  SK_DELETE_PTR(__gpWxui);
}