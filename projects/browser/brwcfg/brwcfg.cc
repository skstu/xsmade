#include "brwcfg.h"

Brwcfg::Brwcfg() {
}
Brwcfg::~Brwcfg() {
}
IConfig *Brwcfg::ConfigGet() const {
  return dynamic_cast<IConfig *>(Config::Create());
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
  Config::Create();
  Brwcfg::Create();
}
SHARED_API void interface_uninit() {
  Brwcfg::Destroy();
  Config::Destroy();
}
#ifdef __cplusplus
}
#endif