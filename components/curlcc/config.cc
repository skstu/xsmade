#include "config.h"

Config::Config() {
  Init();
}
Config::~Config() {
  UnInit();
}
void Config::Init() {
}
void Config::UnInit() {
}
bool Config::IsAuth() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return isAuth_.load();
}
const std::string &Config::GetCurlProxyString() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return curl_proxy_string_;
}
void Config::SetCurlResponseFilename(const char *filename) {
  std::lock_guard<std::mutex> lock(*mtx_);
  if (filename) {
    curl_response_filename_ = filename;
  } else {
    curl_response_filename_.clear();
    return;
  }
}
const std::string &Config::GetCurlResponseFilename() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return curl_response_filename_;
}
const CurlProxyInfo &Config::GetCurlProxyInfo() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return curl_proxy_info_;
}
const std::vector<std::string> &Config::GetCurlRequestUrls() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return curl_request_urls_;
}
void Config::AppendCurlRequestUrl(const char *url) {
  std::lock_guard<std::mutex> lock(*mtx_);
  if (!url)
    return;
  curl_request_urls_.emplace_back(url);
}
void Config::SetCurlProxyString(const char *proxy, const bool &isAuth) {
  std::lock_guard<std::mutex> lock(*mtx_);
  do {
    if (!proxy)
      break;
    isAuth_.store(isAuth);
    curl_proxy_string_ = proxy;
    // socks5h://1Ap7HA38151774A39724:EAE0W4S0QLE1@38.15.17.74:39724
    // 支持 http[s]://user:pass@host:port 和 socks4/5/h://user:pass@host:port
    std::regex re(
        R"(^(https?|socks4|socks5h?|ftp)://(?:([^:]+):([^@]+)@)?([^\:]+):(\d+)$)");
    std::smatch m;
    if (std::regex_match(curl_proxy_string_, m, re)) {
      curl_proxy_info_.scheme = m[1];
      curl_proxy_info_.username = m[2];
      curl_proxy_info_.password = m[3];
      curl_proxy_info_.host = m[4];
      curl_proxy_info_.port = m[5];

      if (curl_proxy_info_.scheme.find("socks5h") != std::string::npos) {
        curl_proxy_info_.type = ProxyType::SOCKS5;
      } else if (curl_proxy_info_.scheme.find("socks5") != std::string::npos) {
        curl_proxy_info_.type = ProxyType::SOCKS5;
      } else if (curl_proxy_info_.scheme.find("socks4") != std::string::npos) {
        curl_proxy_info_.type = ProxyType::SOCKS4;
      } else {
        curl_proxy_info_.type = ProxyType::HTTP;
      }
    }
  } while (0);
}
/////////////////////////////////////////////////////////////////////////////
static Config *__config__ = nullptr;
Config *Config::CreateOrGet() {
  if (!__config__) {
    __config__ = new Config();
  }
  return __config__;
}
void Config::Destroy() {
  if (__config__) {
    delete __config__;
    __config__ = nullptr;
  }
}