#if !defined(__8E0DC06F_77B6_46CB_9E6B_4F98C10F337A__)
#define __8E0DC06F_77B6_46CB_9E6B_4F98C10F337A__
#define ENABLE_WXUI        0
#define ENABLE_PUSH_STREAM 1
#include <xs.h>
#include <conv.hpp>
#include <fmt/format.h>
#include <ibrw.h>
using namespace brw;
#include <rapidjson.h>
#include "wxdeps.h"
#include "configure.hpp"
#include "config.h"
#include "vmem.h"
#include "buffer.h"
#include "extension.h"
#include "args.h"
#if ENABLE_PUSH_STREAM
#endif
// #if ENABLE_WXUI
#include <ui/wxui.h>
// #endif
class Brwcfg final : public IBrw {
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
  void FreeS(void **) const override final;
  void *MallocS(const size_t &) const override final;
  void OnAppendArgs(IArgsArray **) const override final;
  IBrw::IBuffer *CreateBuffer(const char *,
                              const size_t &) const override final;
  void OnExtensionsInstall(const IBuffer *,
                           IExtensionArray **) const override final;
  void OnGetUserDataDirectory(IBuffer **) const override final;
  bool OnExtensionAllowlisted(const char *extid) const override final;
  bool EnableBadFlagsSecurityWarnings(void) const override final;
  bool EnableSessionCrashedBubbleViewShow(void) const override final;
  void OnBrowserStarted(void) const override final;
  void OnBrowserClosing(void) const override final;
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

private:
  void RegisterGoogleApiKey() const;

private:
  VMem* vmem_ = nullptr;
  std::atomic_bool open_ = false;
  Config *config_ = nullptr;
  IConfigure *configure_ = nullptr;
#if ENABLE_WXUI
  Wxui *wxui_ = nullptr;
#endif
};

/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 19 Feb 2025 05:32:06 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__8E0DC06F_77B6_46CB_9E6B_4F98C10F337A__
