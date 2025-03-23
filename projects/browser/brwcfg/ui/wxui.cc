#include "brwcfg.h"
#if ENABLE_WXUI
Wxui::Wxui() {
  Init();
}

Wxui::~Wxui() {
  UnInit();
}
void Wxui::Init() {
  ready_signal_ = new stl::Signal();
}
void Wxui::UnInit() {
  ready_signal_->Release();
}
bool Wxui::Ready() const {
  return open_.load();
}
stl::Signal *Wxui::GetReadySignal() const {
  return ready_signal_;
}
bool Wxui::Start() {
  do {
    if (open_.load())
      break;
    open_.store(true);
    threads_.emplace_back([this]() { MainProc(); });
    ready_signal_->wait_for_event(std::chrono::milliseconds(0));
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

    // App *app = wxDynamicCast(wxApp::GetInstance(), App);
    // app->SetParent(parent_);
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
IFrame *Wxui::GetFrame() const {
  IFrame *result = nullptr;
  App *app = wxDynamicCast(wxApp::GetInstance(), App);
  if (app)
    result = wxDynamicCast(app->FrameGet(), IFrame);
  return result;
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
#endif