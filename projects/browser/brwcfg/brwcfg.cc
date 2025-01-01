#include "brwcfg.h"

Brwcfg::Brwcfg() {
  Init();
}
Brwcfg::~Brwcfg() {
  UnInit();
}
void Brwcfg::Init() {
}
void Brwcfg::UnInit() {
}
bool Brwcfg::Start() {
  return false;
}
void Brwcfg::Stop() {
}
bool Brwcfg::Ready() const {
  return false;
}
//!@ [\src\chrome\app\chrome_main.cc (16)]
//!@ [\src\chrome\app\chrome_main.cc (232-242)]
void Brwcfg::OnMainProcessStartup(void) {
  do {

  } while (0);
}
void Brwcfg::OnMainProcessShutdown(int rv) {
  do {

  } while (0);
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
/////////////////////////////////////////////////////////////////////
static Brwcfg *__gspBrwcfg = nullptr;
Brwcfg *Brwcfg::Create() {
  if (!__gspBrwcfg)
    __gspBrwcfg = new Brwcfg();
  return __gspBrwcfg;
}
void Brwcfg::Destroy() {
  SK_DELETE_PTR(__gspBrwcfg);
}
#ifdef __cplusplus
extern "C" {
#endif
SHARED_API void *interface_init(void *, unsigned long) {
  IBrwcfg *result = dynamic_cast<IBrwcfg *>(Brwcfg::Create());
  return result;
}
SHARED_API void interface_uninit() {
  Brwcfg::Destroy();
}
#ifdef __cplusplus
}
#endif