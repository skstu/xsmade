#include "component.h"
#include "wxui.h"
class NswxskinTest : public IComponent {
public:
  NswxskinTest() {
  }
  ~NswxskinTest() {
  }
  bool Start() {
    Global::Get()->LoadResource(
        uR"(C:\Users\k34ub\source\skstu\xsmade\tools\NSIS\MakeInstaller\source\skin\images)");
    Wxui::Create()->Start();
    return true;
  }
  void Stop() {
    Wxui::Create()->Stop();
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
