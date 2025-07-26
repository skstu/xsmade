#if !defined(__03406DC9_3BF3_47A3_927C_502ACED2AF60__)
#define __03406DC9_3BF3_47A3_927C_502ACED2AF60__

#include "component.h"

namespace curl {
class ICurl : public IComponent {
public:
  class IConfig {
  public:
    virtual void SetCurlProxyString(const char *) = 0;
    virtual void AppendCurlRequestUrl(const char *) = 0;
    virtual void SetCurlResponseFilename(const char *) = 0;
  };

  class IRequest {
  public:
    virtual void Release() const = 0;
    virtual void SetUrl(const char *) = 0;
    virtual const char* GetUrl() const = 0;
    virtual void SetMethod(const char *) = 0;
    virtual void SetHeaders(const std::map<std::string, std::string> &) = 0;
    virtual void SetBody(const char *) = 0;
    virtual void SetProxyString(const char *) = 0;
    virtual bool GetResponse(char **, size_t *) const = 0;
    virtual void SetResponseCode(const int &) = 0;
    virtual int GetResponseCode() const = 0;
  };

  class IRequestArray {
  public:
    virtual size_t Total() const = 0;
    virtual IRequest *Next(const size_t &) const = 0;
    virtual void Release() const = 0;
    virtual void Push(IRequest *) = 0;
  };

public:
  virtual void Free(void **) const = 0;
  virtual IConfig *GetConfig() const = 0;
  virtual IRequest *CreateRequest() const = 0;
  virtual IRequestArray *CreateRequestArray() const = 0;
  virtual bool Start() = 0;
  virtual void Stop() = 0;
  virtual IRequestArray *Perform(IRequestArray *) = 0;
  virtual bool Ready() const = 0;
};
} // namespace curl
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 07 Dec 2024 06:16:26 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__03406DC9_3BF3_47A3_927C_502ACED2AF60__