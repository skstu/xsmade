#include "brwtest.h"
Brwtest::Brwtest() {
}
Brwtest::~Brwtest() {
}
bool Brwtest::Start() {
  do {
    if (open_.load())
      break;
    open_.store(true);

  } while (0);
  return open_.load();
}
void Brwtest::Stop() {
  do {
    if (!open_.load())
      break;
    open_.store(false);
  } while (0);
}

//////////////////////////////////////////////////////////////////
static Brwtest *__gpsBrwtest = nullptr;
Brwtest *Brwtest::Create() {
  if (!__gpsBrwtest)
    __gpsBrwtest = new Brwtest();
  return __gpsBrwtest;
}
void Brwtest::Destroy() {
  if (__gpsBrwtest)
    __gpsBrwtest->Stop();
  SK_DELETE_PTR(__gpsBrwtest);
}
extern "C" {
SHARED_API void *interface_init(void *, unsigned long) {
  IBrwComponent *result = dynamic_cast<IBrwComponent *>(Brwtest::Create());
  return result;
}
SHARED_API void interface_uninit(void) {
  Brwtest::Destroy();
}
} // extern "C"