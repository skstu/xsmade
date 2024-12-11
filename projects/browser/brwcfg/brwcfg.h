#if !defined(__E68008C8_057E_4381_9570_8EEE30A32462__)
#define __E68008C8_057E_4381_9570_8EEE30A32462__

#include "macros.h"
#include "export.h"
using namespace browser;
#include "config.h"

class Brwcfg final : public IBrwcfg {
public:
  static Brwcfg *Create();
  static void Destroy();

private:
  Brwcfg();
  virtual ~Brwcfg();

protected:
  IConfig *ConfigGet() const override final;
  void OnMainProcessStartup(void) override final;
  void OnMainProcessShutdown(int rv) override final;
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