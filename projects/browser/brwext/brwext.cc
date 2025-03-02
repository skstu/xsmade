#include "brwext.h"
Brwext::Brwext() {
}
Brwext::~Brwext() {
}
bool Brwext::Start() {
  do {
    if (open_.load())
      break;
    open_.store(true);

  } while (0);
  return open_.load();
}
void Brwext::Stop() {
  do {
    if (!open_.load())
      break;
    open_.store(false);
  } while (0);
}

//////////////////////////////////////////////////////////////////
static Brwext *__gpsBrwext = nullptr;
Brwext *Brwext::Create() {
  if (!__gpsBrwext)
    __gpsBrwext = new Brwext();
  return __gpsBrwext;
}
void Brwext::Destroy() {
  if (__gpsBrwext)
    __gpsBrwext->Stop();
  SK_DELETE_PTR(__gpsBrwext);
}
extern "C" {
SHARED_API void *interface_init(void *, unsigned long) {
  IBrwComponent *result = dynamic_cast<IBrwComponent *>(Brwext::Create());
  return result;
}
SHARED_API void interface_uninit(void) {
  Brwext::Destroy();
}
} // extern "C"