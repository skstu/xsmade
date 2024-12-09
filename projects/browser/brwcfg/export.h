#if !defined(__5F0E26E1_8D0C_418A_86B1_831DD24458AF__)
#define __5F0E26E1_8D0C_418A_86B1_831DD24458AF__

class IChromium {
public:
  class IExtension {
  public:
    virtual const char *Manifest() const = 0;
    virtual const wchar_t *Root() const = 0;
    virtual void Release() const = 0;
  };
  class IExtensionArray {
  public:
    virtual size_t Total() const = 0;
    virtual IExtension *Next(const size_t &) const = 0;
    virtual bool Empty() const = 0;
    virtual void Release() const = 0;
  };

public:
  virtual void OnBrowserProcessStartup(void) = 0;
  virtual void OnBrowserProcessShutdown(int ret) = 0;
  virtual void OnExtensionInstall(IExtensionArray **) const = 0;
  virtual bool OnExtensionAllowlisted(const char *extension_id) const = 0;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 07 Dec 2024 06:49:11 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__5F0E26E1_8D0C_418A_86B1_831DD24458AF__