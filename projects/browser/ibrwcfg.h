#if !defined(__7B07A640_1E04_4174_A41E_1C44EA560B44__)
#define __7B07A640_1E04_4174_A41E_1C44EA560B44__
#include <interface.hpp>
#include "configure.hpp"
namespace brwcfg {
typedef void *(*tf_chromium_module_interface_init)(void *, unsigned long);
typedef void (*tf_chromium_module_interface_uninit)(void);

class IBrwcfg : public Interface<IBrwcfg> {
public:
  class IBrowser {
  public:
    virtual bool IForwardInputEvent(const char *, size_t) = 0;
  };
  class IBuffer {
  public:
    virtual const char *GetData() const = 0;
    virtual size_t GetSize() const = 0;
    virtual void Release() const = 0;
  };
  class IBufferArray {
  public:
    virtual void Push(IBuffer *) = 0;
    virtual IBuffer *CreateBuffer(const char *, const size_t &) = 0;
    virtual IBuffer *Next(const size_t &) const = 0;
    virtual size_t Total() const = 0;
    virtual void Release() const = 0;
  };

  class IArgs {
  public:
    virtual bool IsPath() const = 0;
    virtual IBuffer *GetKey() const = 0;
    virtual IBuffer *GetValue() const = 0;
    virtual void Release() const = 0;
  };
  class IArgsArray {
  public:
    virtual size_t Total() const = 0;
    virtual IArgs *Next(const size_t &) const = 0;
    virtual void Release() const = 0;
  };
  class IExtension {
  public:
    virtual bool IsReload() const = 0;
    virtual const IBuffer *Manifest() const = 0;
    virtual const IBuffer *Root() const = 0;
    virtual void Release() const = 0;
  };
  class IExtensionArray {
  public:
    virtual size_t Total() const = 0;
    virtual IExtension *Next(const size_t &) const = 0;
    virtual void Release() const = 0;
  };

public:
  virtual bool Start() = 0;
  virtual void Stop() = 0;
  virtual void FreeS(void **) const = 0;
  virtual void *MallocS(const size_t &) const = 0;
  virtual IBuffer *CreateBuffer(const char *, const size_t &) const = 0;
  virtual void OnAppendArgs(IArgsArray **) const = 0;
  virtual bool OnExtensionMessage(const char *extid, const IBuffer *req,
                                  IBuffer **res) const = 0;
  virtual void OnExtensionsInstall(const IBuffer *,
                                   IExtensionArray **) const = 0;
  virtual void OnGetUserDataDirectory(IBuffer **) const = 0;
  virtual bool OnExtensionAllowlisted(const char *extid) const = 0;
  virtual bool EnableBadFlagsSecurityWarnings(void) const = 0;
  virtual bool EnableSessionCrashedBubbleViewShow(void) const = 0;
  virtual void OnBrowserStarted(void) const = 0;
  virtual void OnBrowserClosing(void) const = 0;
  virtual void OnBrowserReadyed(void) const = 0;
  virtual void OnCreateWindowExBefore(void **parent, unsigned long *style,
                                      unsigned long *exstyle) const = 0;
  virtual void OnCreateWindowExAfter(void *hwnd) const = 0;
  virtual void OnChildProcessAppendArgs(IArgsArray **) const = 0;
  virtual const char *IConfigureGet() const = 0;
  virtual bool EnableNonClientHitTest(void) const = 0;
  virtual bool EnableBrowserCaptionButtonContainer(void) const = 0;
  virtual void OnGpuScreenshotImageStream(const IBuffer *) const = 0;
  virtual bool OnGpuCanvasFrameGetResolution(int *width, int *height) const = 0;
  virtual void SetChromiumBrowserObj(IBrowser *) = 0;
  virtual IBrowser *GetChromiumBrowserObj() const = 0;
};
} // namespace brwcfg

/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 19 Feb 2025 02:59:31 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__7B07A640_1E04_4174_A41E_1C44EA560B44__