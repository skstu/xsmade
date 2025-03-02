#include "wxui.h"

Wxui::Wxui() {
  Init();
}

Wxui::~Wxui() {
  UnInit();
}
void Wxui::Init() {
}
void Wxui::UnInit() {
}
bool Wxui::Ready() const {
  return open_.load();
}
bool Wxui::Start() {
  do {
    if (open_.load())
      break;
    open_.store(true);
    threads_.emplace_back([this]() { MainProc(); });
  } while (0);
  return open_.load();
}
void Wxui::Stop() {
  do {
    if (!open_.load())
      break;
    open_.store(false);
    for (auto &t : threads_)
      t.join();
    threads_.clear();
  } while (0);
}
void Wxui::MainProc() {
  do {
    wxDISABLE_DEBUG_SUPPORT();
    wxSystemOptions::SetOption("msw.no-manifest-check", 1);
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
  } while (0);
}
Frame *Wxui::GetFrame() const {
  App *app = wxDynamicCast(wxApp::GetInstance(), App);
  return app->FrameGet();
}
/////////////////////////////////////////////////////////////////////
static Wxui *__gpsWxui = nullptr;
Wxui *Wxui::Create() {
  if (!__gpsWxui)
    __gpsWxui = new Wxui();
  return __gpsWxui;
}
void Wxui::Destroy() {
  if (__gpsWxui) {
    delete __gpsWxui;
    __gpsWxui = nullptr;
  }
}
