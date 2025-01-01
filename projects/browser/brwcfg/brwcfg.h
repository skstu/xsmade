#if !defined(__E68008C8_057E_4381_9570_8EEE30A32462__)
#define __E68008C8_057E_4381_9570_8EEE30A32462__

#include <xs.h>
#include <system.hpp>
#include "export.h"
using namespace browser;
#include <base/uvpp/export.h>
#include <base/wxui/export.h>
#include "config.h"
#include "client.h"

class Brwcfg final : public IBrwcfg {
public:
  static Brwcfg *Create();
  static void Destroy();

private:
  Brwcfg();
  virtual ~Brwcfg();
  void Init();
  void UnInit();

protected:
  bool Start() override final;
  void Stop() override final;
  bool Ready() const override final;
  void OnMainProcessStartup(void) override final;
  void OnMainProcessShutdown(int rv) override final;
  void OnBrowserStarted() override final;
  void OnCreateWindowExBefore(void **parent, unsigned long *style,
                              unsigned long *exstyle) override final;
  void OnCreateWindowExAfter(void *hwnd) override final;
};

#ifdef __cplusplus
extern "C" {
#endif
SHARED_API void *interface_init(void *, unsigned long);
SHARED_API void interface_uninit();
#ifdef __cplusplus
}
#endif
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 07 Dec 2024 06:46:24 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__E68008C8_057E_4381_9570_8EEE30A32462__