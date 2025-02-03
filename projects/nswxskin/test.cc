#include "component.h"

class NswxskinTest : public IComponent {
public:
  NswxskinTest() {
  }
  ~NswxskinTest() {
  }
  bool Start() {
    return true;
  }
  void Stop() {
  }
  bool Ready() const {
    return true;
  }
};
////////////////////////////////////////////////////////////////////////////////////////////////////////
static NswxskinTest *__gpNswxskinTest = nullptr;
#ifdef __cplusplus
extern "C" {
#endif

SHARED_API void *interface_init(void *data, unsigned long len) {
  __gpNswxskinTest = new NswxskinTest();

  return dynamic_cast<IComponent *>(__gpNswxskinTest);
}
SHARED_API void interface_uninit() {
  if (__gpNswxskinTest) {
    delete __gpNswxskinTest;
    __gpNswxskinTest = nullptr;
  }
}

#ifdef __cplusplus
}
#endif
