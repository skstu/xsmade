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
IConfig *Wxui::ConfigGet() const {
  return Config::Get();
}
void Wxui::MainProc() {
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
    Config::Get()->OnSystemExit();
  } while (0);
}
IFrame *Wxui::GetFrame() const {
  App *app = wxDynamicCast(wxApp::GetInstance(), App);
  return app->FrameGet();
}
void Wxui::NotifyRecordingEnd() const {
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
#ifdef __cplusplus
extern "C" {
#endif
SHARED_API void *interface_init(void *data, unsigned long len) {
  auto config = Config::Get();
  auto wxui = Wxui::Create();
  do {
    if (!data || len <= 0)
      break;

  } while (0);
  return reinterpret_cast<void *>(dynamic_cast<IWxui *>(wxui));
}
SHARED_API void interface_uninit() {
  Wxui::Destroy();
  Config::Destroy();
}
#ifdef __cplusplus
}
#endif