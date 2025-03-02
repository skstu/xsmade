#if !defined(__E68008C8_057E_4381_9570_8EEE30A32462__)
#define __E68008C8_057E_4381_9570_8EEE30A32462__
#include <xs.h>
#include <base/sys/sys.h>
#include <system.hpp>
#include <rapidjson.h>
#include <tinyxml2.h>
#include "export.h"
using namespace browser;
#include <components/uvpp/export.h>
#include <components/wxui/export.h>
#include "data.h"
#include "array.h"
#include "config.h"
#include "client.h"
#include <ui/ui.h>

class Brwcfg final : public IBrwcfg {
public:
  static Brwcfg *Create();
  static void Destroy();

private:
  Brwcfg();
  virtual ~Brwcfg();
  void Init();
  void UnInit();
  bool Start();
  void Stop();
  void Proc();

protected:
  IConfig *ConfigGet() const override final;
  bool Ready() const override final;
  void OnMainProcessStartup(void) override final;
  void OnMainProcessShutdown(int rv) override final;
  void OnBrowserStarted() override final;
  void OnCreateWindowExBefore(void **parent, unsigned long *style,
                              unsigned long *exstyle) override final;
  void OnCreateWindowExAfter(void *hwnd) override final;

  IData *CreateData(const char *, const size_t &) const override final;
  IDataArray *CreateDataArray() const override final;

  void OnChromiumExtensionsMessageServiceCreate() override final;
  void OnChromiumExtensionsMessageServiceDestroy() override final;

private:
  void ConfiguringEnvironmentVariables() const;

private:
  std::atomic_bool open_ = false;
  stl::tfThreads threads_;
  Config *config_ = nullptr;
};

#include "interface.h"
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 07 Dec 2024 06:46:24 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__E68008C8_057E_4381_9570_8EEE30A32462__