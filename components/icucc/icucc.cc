#include "icucc.h"

Icucc::Icucc() {
  Init();
}
Icucc::~Icucc() {
  UnInit();
}
void Icucc::Init() {
  do {
    UErrorCode status = U_ZERO_ERROR;
    u_init(&status);
    if (U_FAILURE(status))
      break;
    ready_.store(true);
  } while (0);
}
void Icucc::UnInit() {
  u_cleanup();
  ready_.store(false);
}
bool Icucc::Ready() const {
  return ready_.load();
}
//////////////////////////////////////////////////////////////////////////////////////////
static Icucc *__gpIcucc = nullptr;
Icucc *Icucc::Create() {
  if (!__gpIcucc)
    __gpIcucc = new Icucc();
  return __gpIcucc;
}
void Icucc::Destroy() {
  SK_DELETE_PTR(__gpIcucc);
}

#ifdef __cplusplus
extern "C" {
#endif
SHARED_API void *interface_init(void *data, unsigned long len) {
  Icucc::Create();
  if (!__gpIcucc->Ready()) {
    Icucc::Destroy();
  }
  return dynamic_cast<IIcucc *>(__gpIcucc);
}
SHARED_API void interface_uninit() {
  Icucc::Destroy();
}
#ifdef __cplusplus
}
#endif
