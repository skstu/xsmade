#if !defined(__00B59F70_C296_4392_8611_D5E1C316657C__)
#define __00B59F70_C296_4392_8611_D5E1C316657C__
namespace chromium {
class IRequest final {
public:
  IRequest(const IRequest &) = delete;
  IRequest &operator=(const IRequest &) = delete;
  void *operator new(size_t) = delete;
  void operator delete(void *) = delete;
  IRequest(const std::string &reqBody, const std::string &project_root_dir) {
    body = reqBody;
    configure_ = std::make_unique<chromium::cfg::IConfigure>(body);
    SuperMAC();
  }
  ~IRequest() = default;

  inline void operator>>(std::string &output) const;

public:
  const chromium::cfg::IConfigure &GetConfigure() const {
    return *configure_;
  }

  void SetErrorCode(const ErrorCode &err) {
    code = err;
  }

private:
  std::string body;
  std::string hash_source;
  std::string hash;
  inline void SuperMAC();
  ErrorCode code = ErrorCode::UnknownError;
  std::unique_ptr<chromium::cfg::IConfigure> configure_;
};
inline void IRequest::operator>>(std::string &output) const {
  rapidjson::Document doc(rapidjson::Type::kObjectType);
  rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();
  doc.AddMember(rapidjson::Value().SetString("code", allocator).Move(),
                rapidjson::Value().SetInt(static_cast<int>(code)).Move(),
                allocator);
  doc.AddMember(
      rapidjson::Value().SetString("code", allocator).Move(),
      rapidjson::Value().SetString(ErrorCodeToString(code), allocator).Move(),
      allocator);
  if (code == ErrorCode::Success || code == ErrorCode::AlreadyRunning) {
    doc.AddMember(rapidjson::Value().SetString("id", allocator).Move(),
                  rapidjson::Value().SetUint(configure_->id).Move(), allocator);
    doc.AddMember(rapidjson::Value().SetString("hash", allocator).Move(),
                  rapidjson::Value()
                      .SetString(hash.empty() ? "" : hash.c_str(), allocator)
                      .Move(),
                  allocator);
  }
#if 0
  rapidjson::Document docHashSource(rapidjson::Type::kObjectType);
  if (!docHashSource.Parse(hash_source.data(), hash_source.size())
           .HasParseError()) {
    doc.AddMember(rapidjson::Value().SetString("source", allocator).Move(),
                  rapidjson::Value(docHashSource, allocator).Move(), allocator);
  }
#endif
  output = Json::toString(doc);
}
inline void IRequest::SuperMAC() {
  rapidjson::Document docHash(rapidjson::kObjectType);
  rapidjson::Document::AllocatorType &allocator = docHash.GetAllocator();
  do {
    if (body.empty())
      break;
    rapidjson::Document doc;
    if (doc.Parse(body.data(), body.size()).HasParseError())
      break;
    if (!doc.IsObject())
      break;

    const char *keys[] = {
        "enable", "type", "fps_use3rd",   "policy",
        "proxy",  "fps",  "startup_args",
    };
    for (const char *key : keys) {
      if (doc.HasMember(key)) {
        docHash.AddMember(rapidjson::Value(key, allocator).Move(),
                          rapidjson::Value(doc[key], allocator).Move(),
                          allocator);
      }
    }
  } while (0);

  Json::Sort(docHash, allocator);
  hash_source = Json::toString(docHash);
  hash = OpenSSL::HMAC_SHA256(hash_source, "martell", true);
}
} // namespace chromium
/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 30 May 2025 07:06:43 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__00B59F70_C296_4392_8611_D5E1C316657C__