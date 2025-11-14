#if !defined(__B4103B82_7531_480B_B3E2_5231CE27F681__)
#define __B4103B82_7531_480B_B3E2_5231CE27F681__

enum class ProxyType { HTTP, SOCKS4, SOCKS5 };
struct CurlProxyInfo {
  ProxyType type = ProxyType::SOCKS5;
  std::string scheme;
  std::string username;
  std::string password;
  std::string host;
  std::string port;
};

class Request final : public ICurl::IRequest {
public:
  Request();
  ~Request();

public:
  void Release() const override final;
  void SetUrl(const char *) override final;
  void SetMethod(const char *) override final;
  //void SetHeaders(const std::map<std::string, std::string> &) override final;
  void SetBody(const char *) override final;
  void SetProxyString(const char *,const bool&) override final;
  bool GetResponse(char **, size_t *) const override final;
  void SetResponseCode(const int &) override final;
  int GetResponseCode() const override final;
  const char *GetUrl() const override final;

public:
  const std::string &GetMethod() const;
  const std::map<std::string, std::string> &GetHeaders() const;
  const std::string &GetBody() const;
  void SetResponse(const std::string &response);
  const std::string GetProxyAddress() const;
  const std::string &GetProxyUsername() const;
  const std::string &GetProxyPassword() const;
  const ProxyType &GetProxyType() const;
  bool IsAuth() const;

private:
  int response_code_ = 0;
  std::string url_;
  std::string method_;
  std::map<std::string, std::string> headers_;
  std::string body_;
  std::string response_;
  CurlProxyInfo proxy_info_;
  std::atomic_bool is_auth_ = false;
  std::unique_ptr<std::mutex> mtx_ = std::make_unique<std::mutex>();
};

class RequestArray final : public ICurl::IRequestArray {
public:
  RequestArray();

private:
  virtual ~RequestArray();

public:
  size_t Total() const override final;
  ICurl::IRequest *Next(const size_t &) const override final;
  void Release() const override final;
  void Push(ICurl::IRequest *) override final;

private:
  std::vector<Request *> source_;
  std::unique_ptr<std::mutex> mtx_ = std::make_unique<std::mutex>();
};
/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 25 Jul 2025 05:48:15 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__B4103B82_7531_480B_B3E2_5231CE27F681__