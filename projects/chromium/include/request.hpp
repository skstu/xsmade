#if !defined(__00B59F70_C296_4392_8611_D5E1C316657C__)
#define __00B59F70_C296_4392_8611_D5E1C316657C__
namespace chromium {
class IRequest final {
public:
  inline IRequest(const std::string &reqBody) : reqBody_(reqBody) {
    Init();
  }
  inline void Release() const {
    delete this;
  }
  inline std::string GetResponse() const;

private:
  inline IRequest(const IRequest &) = delete;
  inline IRequest &operator=(const IRequest &) = delete;
  // inline void *operator new(size_t) = delete;
  // inline void operator delete(void *) = delete;

  inline ~IRequest() {
    UnInit();
  }

public:
  inline bool Ready() const {
    return static_cast<ErrorCode>(configure_.notifyCode) ==
               ErrorCode::Success ||
           static_cast<ErrorCode>(configure_.notifyCode) == ErrorCode::Done;
  }
  inline void SetErrorCode(const ErrorCode &err) {
    configure_.notifyCode = static_cast<decltype(configure_.notifyCode)>(err);
    configure_.notifyMsg = ErrorCodeToString(err);
  }
  inline void SetRequestType(const chromium::xsiumio::RequestType &type) {
    configure_.type = type;
  }
  inline ErrorCode GetErrorCode() const {
    return static_cast<ErrorCode>(configure_.notifyCode);
  }
  inline const chromium::xsiumio::RequestType &GetRequestType() const {
    return configure_.type;
  }
  inline chromium::xsiumio::IXSiumio &GetConfig() {
    return configure_;
  }

private:
  inline void Init();
  inline void UnInit();
  const std::string reqBody_;
  chromium::xsiumio::IXSiumio configure_;
};
inline void IRequest::Init() {
  ErrorCode code;
  rapidjson::Document doc;
  if (doc.Parse(reqBody_.data(), reqBody_.size()).HasParseError()) {
    code = ErrorCode::RequestParseError;
  } else {
    configure_ << reqBody_;
    if (configure_.ValidateRequestType()) {
      code = ErrorCode::Done;
    } else {
      code = ErrorCode::BadRequest;
    }
  }
  configure_.notifyCode = static_cast<decltype(configure_.notifyCode)>(code);
  configure_.notifyMsg = ErrorCodeToString(code);
}
inline void IRequest::UnInit() {
}
inline std::string IRequest::GetResponse() const {
  std::string result;
  configure_ >> result;
  return result;
}
} // namespace chromium
/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 30 May 2025 07:06:43 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__00B59F70_C296_4392_8611_D5E1C316657C__