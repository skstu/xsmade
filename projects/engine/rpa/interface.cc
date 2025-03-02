#include <brwcfg.h>

static Brwcfg *__gspBrwcfg = nullptr;
Brwcfg *Brwcfg::Create() {
  if (!__gspBrwcfg)
    __gspBrwcfg = new Brwcfg();
  return __gspBrwcfg;
}
void Brwcfg::Destroy() {
  if (__gspBrwcfg)
    __gspBrwcfg->Stop();
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
