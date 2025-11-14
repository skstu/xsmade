#include "config.h"

Request::Request() {
}

Request::~Request() {
}

void Request::Release() const {
  delete this;
}

bool Request::GetResponse(char **data, size_t *len) const {
  bool result = false;
  std::lock_guard<std::mutex> lock(*mtx_);
  do {
    if (response_.empty())
      break;
    *len = response_.size();
    *data = (char *)malloc(*len);
    memcpy(*data, response_.data(), *len);
    result = true;
  } while (0);
  return result;
}
void Request::SetUrl(const char *url) {
  std::lock_guard<std::mutex> lock(*mtx_);
  url_ = url ? url : "";
}
void Request::SetMethod(const char *method) {
  std::lock_guard<std::mutex> lock(*mtx_);
  method_ = method ? method : "GET";
}
// void Request::SetHeaders(const std::map<std::string, std::string> &headers) {
//   std::lock_guard<std::mutex> lock(*mtx_);
//   headers_ = headers;
// }
void Request::SetBody(const char *body) {
  std::lock_guard<std::mutex> lock(*mtx_);
  body_ = body ? body : "";
}
bool Request::IsAuth() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return is_auth_.load();
}
void Request::SetProxyString(const char *in_proxy_string, const bool &isAuth) {
  std::lock_guard<std::mutex> lock(*mtx_);
  is_auth_.store(isAuth);
  const std::string proxy_string = in_proxy_string ? in_proxy_string : "";
  if (proxy_string.empty()) {
    proxy_info_.host.clear();
    proxy_info_.username.clear();
    proxy_info_.password.clear();
    return;
  }
  // socks5h://1Ap7HA38151774A39724:EAE0W4S0QLE1@38.15.17.74:39724
  // 支持 http[s]://user:pass@host:port 和 socks4/5/h://user:pass@host:port
  if (is_auth_.load()) {
    std::regex re(
        R"(^(https?|socks4|socks5h?|ftp)://(?:([^:]+):([^@]+)@)?([^\:]+):(\d+)$)");
    std::smatch m;
    if (std::regex_match(proxy_string, m, re)) {
      proxy_info_.scheme = m[1];
      proxy_info_.username = m[2];
      proxy_info_.password = m[3];
      proxy_info_.host = m[4];
      proxy_info_.port = m[5];

      if (proxy_info_.scheme.find("socks5h") != std::string::npos) {
        proxy_info_.type = ProxyType::SOCKS5;
      } else if (proxy_info_.scheme.find("socks5") != std::string::npos) {
        proxy_info_.type = ProxyType::SOCKS5;
      } else if (proxy_info_.scheme.find("socks4") != std::string::npos) {
        proxy_info_.type = ProxyType::SOCKS4;
      } else {
        proxy_info_.type = ProxyType::HTTP;
      }
    }
  } else {
    std::regex re_no_auth(R"(^(https?|socks4|socks5h?|ftp)://([^:]+):(\d+)$)");
    std::smatch m2;
    if (std::regex_match(proxy_string, m2, re_no_auth)) {
      proxy_info_.scheme = m2[1];
      proxy_info_.username.clear();
      proxy_info_.password.clear();
      proxy_info_.host = m2[2];
      proxy_info_.port = m2[3];
    }
  }
}

const std::string &Request::GetMethod() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return method_;
}
const std::map<std::string, std::string> &Request::GetHeaders() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return headers_;
}
const std::string &Request::GetBody() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return body_;
}
void Request::SetResponse(const std::string &response) {
  std::lock_guard<std::mutex> lock(*mtx_);
  response_ = response;
}
void Request::SetResponseCode(const int &code) {
  std::lock_guard<std::mutex> lock(*mtx_);
  response_code_ = code;
}
const std::string Request::GetProxyAddress() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  if (is_auth_.load()) {
    if (proxy_info_.host.empty() || proxy_info_.port.empty()) {
      return "";
    }
    return proxy_info_.host + ":" + proxy_info_.port;
  } else {
    if (proxy_info_.scheme.empty() || proxy_info_.host.empty() ||
        proxy_info_.port.empty()) {
      return "";
    }
    return proxy_info_.scheme + "://" + proxy_info_.host + ":" +
           proxy_info_.port;
  }
}
const std::string &Request::GetProxyUsername() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return proxy_info_.username;
}
const std::string &Request::GetProxyPassword() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return proxy_info_.password;
}
const ProxyType &Request::GetProxyType() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return proxy_info_.type;
}
int Request::GetResponseCode() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return response_code_;
}
const char *Request::GetUrl() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return url_.c_str();
}
///////////////////////////////////////////////////////////////////
RequestArray::RequestArray() {
}

RequestArray::~RequestArray() {
  for (auto &data : source_) {
    data->Release();
  }
  source_.clear();
}
size_t RequestArray::Total() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return source_.size();
}
ICurl::IRequest *RequestArray::Next(const size_t &idx) const {
  ICurl::IRequest *result = nullptr;
  std::lock_guard<std::mutex> lock{*mtx_};
  do {
    if (source_.empty())
      break;
    if (idx >= source_.size())
      break;
    auto it = source_.begin();
    std::advance(it, idx);
    if (it == source_.end())
      break;
    result = dynamic_cast<ICurl::IRequest *>(*it);
  } while (0);
  return result;
}
void RequestArray::Release() const {
  delete this;
}
void RequestArray::Push(ICurl::IRequest *ext) {
  std::lock_guard<std::mutex> lock{*mtx_};
  source_.emplace_back(dynamic_cast<Request *>(ext));
}