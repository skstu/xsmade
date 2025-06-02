#if !defined(__8E0DC06F_77B6_46CB_9E6B_4F98C10F337A__)
#define __8E0DC06F_77B6_46CB_9E6B_4F98C10F337A__
#define ENABLE_WXUI 0
#define ENABLE_VMEM 0
#include <dlfcn.h>
#include <xs.h>
#include <httplib.h>
#if defined(__OSWIN__)
#include <windows.h>
#endif
#include <conv.hpp>
#include <fmt/format.h>
#include <log.hpp>
#include <rapidjson.h>
#include <tinyxml2.hpp>
#include <configure.hpp>
using namespace chromium;
#include <settings.hpp>
#include <ibrwcfg.h>
#include "wxdeps.h"
#include "protocol.hpp"
#include "config.h"
#if ENABLE_VMEM
#include "vmem.h"
#endif
#include "buffer.h"
#include "position.h"
#include "extension.h"
#include "args.h"
#include <components/uvpp/export.h>
using namespace uvpp;
#include "chromium.h"
#if ENABLE_WXUI
#include <ui/wxui.h>
#endif
class Brwcfg final : public IBrwcfg {
public:
  static Brwcfg *GetOrCreate();
  static void Destroy();

private:
  Brwcfg();
  virtual ~Brwcfg();
  void Init();
  void UnInit();

  void Process();

protected:
  bool Start() override final;
  void Stop() override final;
  void FreeS(void **) const override final;
  void *MallocS(const size_t &) const override final;
  void OnAppendArgs(IArgsArray **) const override final;
  IBrwcfg::IBuffer *CreateBuffer(const char *,
                                 const size_t &) const override final;
  IPosition *CreatePosition() const override final;
  ISize *CreateSize() const override final;
  IRectangle *CreateRectangle() const override final;
  void OnExtensionsInstall(const IBuffer *,
                           IExtensionArray **) const override final;
  void OnGetUserDataDirectory(IBuffer **) const override final;
  bool OnExtensionAllowlisted(const char *extid) const override final;
  bool EnableBadFlagsSecurityWarnings(void) const override final;
  bool EnableSessionCrashedBubbleViewShow(void) const override final;
  void OnBrowserStarted(void) const override final;
  void OnBrowserClosing(void) const override final;
  void OnBrowserReadyed(void) const override final;
  void OnCreateWindowExBefore(void **parent, unsigned long *style,
                              unsigned long *exstyle) const override final;
  void OnCreateWindowExAfter(void *hwnd) const override final;
  void OnChildProcessAppendArgs(IArgsArray **) const override final;
  const char *IConfigureGet() const override final;
  bool EnableNonClientHitTest(void) const override final;
  bool EnableBrowserCaptionButtonContainer(void) const override final;
  bool OnExtensionMessage(const char *extid, const IBuffer *req,
                          IBuffer **res) const override final;
  void OnGpuScreenshotImageStream(const IBuffer *) const override final;
  bool OnGpuCanvasFrameGetResolution(int *width,
                                     int *height) const override final;
  void SetChromiumBrowserObj(IBrowser *) override final;

public:
  IBrowser *GetChromiumBrowserObj() const override final;

public:
  void ServerStatus(const bool &);
  bool ServerStatus() const;

private:
  void RegisterGoogleApiKey() const;

private:
  IChromium *chromium_ = nullptr;
  IBrowser *chromium_browser_object_ = nullptr;
  std::atomic_bool open_ = false;
  std::atomic_bool server_ready_ = false;
#if ENABLE_VMEM
  VMem *vmem_ = nullptr;
#endif
#if ENABLE_WXUI
  Wxui *wxui_ = nullptr;
#endif
  stl::tfThreads threads_;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();

public:
  stl::container::queue<
      std::tuple<std::string /*http.path*/, std::string /*content*/>>
      chromium_cookies_notifys_;
};

/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 19 Feb 2025 05:32:06 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__8E0DC06F_77B6_46CB_9E6B_4F98C10F337A__
