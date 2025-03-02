#if !defined(__E4F5D930_FBA9_4887_8407_796150979FEA__)
#define __E4F5D930_FBA9_4887_8407_796150979FEA__

class Response {
public:
  Response(const RequestType &);
  ~Response();
  void *operator new(size_t) = delete;
  void operator delete(void *) = delete;
  Response(const Response &) = delete;
  Response &operator=(const Response &) = delete;

public:
  void SetResponseCode(const ResponseCode &);
  void SetResult(const rapidjson::Value &);
  void SetReqBody(const std::string &);
  std::string GetResult();

private:
  std::string reqbody_;
  rapidjson::Document result_;
  ResponseCode response_code_ = ResponseCode::UnsupportedRequest;
  const RequestType reqtype_;
};
#if 0
class Response {
public:
  Response(const RequestType &reqType);
  void *operator new(size_t) = delete;
  void operator delete(void *) = delete;
  Response(const Response &) = delete;
  Response &operator=(const Response &) = delete;
  ~Response();
  void *operator new(size_t) = delete;
  void operator delete(void *) = delete;
  Response(const Response &) = delete;
  Response &operator=(const Response &) = delete;
  std::string ToJson() const {
    std::string result;
    rapidjson::Document doc(rapidjson::Type::kObjectType);
    doc.AddMember(
        rapidjson::Value().SetString("request_type", doc.GetAllocator()).Move(),
        rapidjson::Value()
            .SetString(
                fmt::format("{:X}", static_cast<unsigned long long>(reqtype_))
                    .c_str(),
                doc.GetAllocator())
            .Move(),
        doc.GetAllocator());
    doc.AddMember(
        rapidjson::Value()
            .SetString("response_code", doc.GetAllocator())
            .Move(),
        rapidjson::Value().SetInt(static_cast<int>(response_code_)).Move(),
        doc.GetAllocator());
    doc.AddMember(
        rapidjson::Value().SetString("message", doc.GetAllocator()).Move(),
        rapidjson::Value()
            .SetString(ResponseCodeString[response_code_].c_str(),
                       doc.GetAllocator())
            .Move(),
        doc.GetAllocator());
    doc.AddMember(
        rapidjson::Value().SetString("result", doc.GetAllocator()).Move(),
        rapidjson::Value().SetString(result.c_str(), doc.GetAllocator()).Move(),
        doc.GetAllocator());
    result = Json::toString(doc);
    return result;
  }
  void SetResponseCode(const ResponseCode &code) {
    response_code_ = code;
  }
  void SetResult(const rapidjson::Document &resultDoc) {
    result = "{}";
    do {
      if (!resultDoc.IsObject() && !resultDoc.IsArray())
        break;
      if (resultDoc.IsObject())
        if (resultDoc.ObjectEmpty())
          break;
      if (resultDoc.IsArray())
        if (resultDoc.Empty())
          break;
      result = Json::toString(resultDoc);
    } while (0);
  }

private:
  std::string result;
  ResponseCode response_code_ = ResponseCode::SystemError;
  const RequestType reqtype_;
  ~Response() {
  }
};
#endif
/// /*_ Memade®（新生™） _**/
/// /*_ Thu, 26 Dec 2024 00:32:11 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__E4F5D930_FBA9_4887_8407_796150979FEA__