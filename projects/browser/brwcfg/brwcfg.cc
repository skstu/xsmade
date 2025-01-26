#include "brwcfg.h"
// https://abrahamjuliot.github.io/creepjs/ 67.7
// --disable-features=CrossOriginOpenerPolicy,IsolateOrigins,SitePerProcess,WebGL,Canvas2D,WebAudio
// --disable-accelerated-video-decode --use-gl=desktop
// --disable-software-rasterizer --no-sandbox
Brwcfg::Brwcfg() {
  Init();
}
Brwcfg::~Brwcfg() {
  UnInit();
}
void Brwcfg::Init() {
  config_ = Config::Create();
  void(
      putenv((char *)"GOOGLE_API_KEY=AIzaSyCkfPOPZXDKNn8hhgu3JrA62wIgC93d44k"));
  void(putenv((char *)"GOOGLE_DEFAULT_CLIENT_ID=811574891467.apps."
                      "googleusercontent.com"));
  void(putenv((char *)"GOOGLE_DEFAULT_CLIENT_SECRET=kdloedMFGdGla2P1zacGjAQh"));
}
void Brwcfg::UnInit() {
  Config::Destroy();
}
bool Brwcfg::Start() {
  do {
    if (open_.load())
      break;

    open_.store(true);
    open_.store(true);
    threads_.emplace_back([this]() { Proc(); });
  } while (0);
  return open_.load();
}
void Brwcfg::Stop() {
  do {
    if (!open_.load())
      break;
    open_.store(false);
    for (auto &t : threads_)
      t.join();
    threads_.clear();
  } while (0);
}
bool Brwcfg::Ready() const {
  return false;
}
IBrwcfg::IConfig *Brwcfg::ConfigGet() const {
  return dynamic_cast<IBrwcfg::IConfig *>(config_);
}
void Brwcfg::OnMainProcessStartup(void) {
  do {
    xs_buffer_t *dllpath = nullptr;
    static int static_dummy_variable;
    xs_sys_get_dll_path(&dllpath, &static_dummy_variable);
    std::string u8strDllpath(dllpath->buffer, dllpath->len);
    auto kk = u8strDllpath.c_str();
    xs_sys_free_buffer(&dllpath);
    // xs_sys_free(void **p)
    // MessageBoxA(NULL, kk, NULL, NULL);
    Start();
  } while (0);
}
void Brwcfg::OnMainProcessShutdown(int rv) {
  do {
    // MessageBoxA(NULL, "END", NULL, NULL);
  } while (0);
  Stop();
}
void Brwcfg::OnBrowserStarted() {
}
void Brwcfg::OnCreateWindowExBefore(void **parent, unsigned long *style,
                                    unsigned long *exstyle) {
}
void Brwcfg::OnCreateWindowExAfter(void *hwnd) {
#ifdef __OSWIN__
  // HWND hWnd = reinterpret_cast<HWND>(hwnd);
  // do {
  //   if (!hWnd)
  //     break;
  // } while (0);
#endif
}
IBrwcfg::IData *Brwcfg::CreateData(const char *data, const size_t &len) const {
  IBrwcfg::IData *result = nullptr;
  if (data && len > 0) {
    result = dynamic_cast<IBrwcfg::IData *>(new Data(data, len));
  }
  return result;
}
IBrwcfg::IDataArray *Brwcfg::CreateDataArray() const {
  IBrwcfg::IDataArray *result =
      dynamic_cast<IBrwcfg::IDataArray *>(new DataArray());
  return result;
}
void Brwcfg::Proc() {
  auto ui = ui::IWxui::Create();
  do {

    if (!open_.load()) {

      break;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  } while (1);
  ui::IWxui::Destroy();
}
void Brwcfg::OnChromiumExtensionsMessageServiceCreate() {
}
void Brwcfg::OnChromiumExtensionsMessageServiceDestroy() {
}
/////////////////////////////////////////////////////////////////////
void Brwcfg::ConfiguringEnvironmentVariables() const {
  do {

  } while (0);
}