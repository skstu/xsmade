#if !defined(__1DEAAA9E_B38C_431E_945C_B8BF2A69DF0F__)
#define __1DEAAA9E_B38C_431E_945C_B8BF2A69DF0F__

#define CURLCC_USE_SOCKS5 0

#include <xs.h>
#include <stl.hpp>
#include <curl/curl.h>
#include <rapidjson.h>
#include "export.h"
using namespace curl;
#include "request.h"
#include "crawler/web.h"
#include "curlcc.h"

class Config final : public ICurl::IConfig {
public:
  static Config *CreateOrGet();
  static void Destroy();

private:
  Config();
  ~Config();
  void Init();
  void UnInit();

public:
  const std::string &GetCurlProxyString() const;
  const CurlProxyInfo &GetCurlProxyInfo() const;
  const std::vector<std::string> &GetCurlRequestUrls() const;
  const std::string &GetCurlResponseFilename() const;

protected:
  void SetCurlProxyString(const char *proxy) override final;
  void AppendCurlRequestUrl(const char *url) override final;
  void SetCurlResponseFilename(const char *filename) override final;

private:
  CurlProxyInfo curl_proxy_info_;
  std::string curl_proxy_string_;
  std::vector<std::string> curl_request_urls_;
  std::string curl_response_filename_;
  std::unique_ptr<std::mutex> mtx_ = std::make_unique<std::mutex>();
};
/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 21 Jul 2025 08:05:13 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__1DEAAA9E_B38C_431E_945C_B8BF2A69DF0F__