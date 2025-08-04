#include "cceng.h"

CCEng::CCEng() {
  Init();
}
CCEng::~CCEng() {
  UnInit();
}
void CCEng::Init() {
  do {
    ready_.store(true);
  } while (0);
}
void CCEng::UnInit() {
  ready_.store(false);
}
bool CCEng::Ready() const {
  return ready_.load();
}
//////////////////////////////////////////////////////////////////////////////////////////
static CCEng *__gpCCEng = nullptr;
CCEng *CCEng::Create() {
  if (!__gpCCEng)
    __gpCCEng = new CCEng();
  return __gpCCEng;
}
void CCEng::Destroy() {
  SK_DELETE_PTR(__gpCCEng);
}

#ifdef __cplusplus
extern "C" {
#endif
SHARED_API void *interface_init(void *data, unsigned long len) {
  CCEng::Create();
  if (!__gpCCEng->Ready()) {
    CCEng::Destroy();
  }
  return dynamic_cast<ICCEng *>(__gpCCEng);
}
SHARED_API void interface_uninit() {
  CCEng::Destroy();
}
#ifdef __cplusplus
}
#endif
