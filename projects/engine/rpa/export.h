#if !defined(__5F0E26E1_8D0C_418A_86B1_831DD24458AF__)
#define __5F0E26E1_8D0C_418A_86B1_831DD24458AF__
#include <interface.hpp>
namespace browser {
class IBrwcfg : public Interface<IBrwcfg> {
public:
  class IData {
  public:
    virtual void *GetData() const = 0;
    virtual size_t GetSize() const = 0;
    virtual void Release() const = 0;
    virtual void SetData(const void *, const size_t &) = 0;
  };
  class IDataArray {
  public:
    virtual void Push(IData *) = 0;
    virtual IData* CreateData(const char *, const size_t &) = 0;
    virtual IData* Next(const size_t &) const = 0;
    virtual size_t Total() const = 0;
    virtual void Release() const = 0;
  };

  class IConfig {
  public:
    virtual bool EnableDevTools(void) const = 0;
    virtual bool EnableShowBadFlagsSecurityWarnings(void) const = 0;
    virtual bool EnableLockFirstTabPage(void) const = 0;
    virtual bool EnableProductLogo(void) const = 0;
    virtual bool EnableSessionCrashedBubbleViewShow(void) const = 0;
  };

public:
  virtual IConfig *ConfigGet() const = 0;
  virtual bool Ready(void) const = 0;
  virtual void OnMainProcessStartup(void) = 0;
  virtual void OnMainProcessShutdown(int rv) = 0;
  virtual void OnBrowserStarted() = 0;
  virtual void OnCreateWindowExBefore(void **parent, unsigned long *style,
                                      unsigned long *exstyle) = 0;
  virtual void OnCreateWindowExAfter(void *hwnd) = 0;
  virtual IData *CreateData(const char *, const size_t &) const = 0;
  virtual IDataArray *CreateDataArray() const = 0;
};
} // namespace browser

/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 07 Dec 2024 06:49:11 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__5F0E26E1_8D0C_418A_86B1_831DD24458AF__