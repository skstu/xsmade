#include <perform.h>
Response::Response(const RequestType &reqtype) : reqtype_(reqtype) {
  result_.SetObject();
}
Response::~Response() {
}
void Response::SetResponseCode(const ResponseCode &code) {
  response_code_ = code;
}
void Response::SetReqBody(const std::string &body) {
  reqbody_ = body;
}
void Response::SetResult(const rapidjson::Value &value) {
  if (!value.IsObject())
    return;
  if (result_.HasMember("result"))
    result_.RemoveMember("result");
  rapidjson::Value copy_(rapidjson::Type::kObjectType);
  copy_.CopyFrom(value, result_.GetAllocator());
  result_.AddMember(
      rapidjson::Value().SetString("result", result_.GetAllocator()).Move(),
      copy_, result_.GetAllocator());
}
std::string Response::GetResult() {
  std::string result;
  do {
    if (result_.HasMember("code"))
      result_.RemoveMember("code");
    if (result_.HasMember("message"))
      result_.RemoveMember("message");
    if (result_.HasMember("body"))
      result_.RemoveMember("body");
    if (result_.HasMember("data_time_ms"))
      result_.RemoveMember("data_time_ms");
    result_.AddMember(
        rapidjson::Value()
            .SetString("server_time_ms", result_.GetAllocator())
            .Move(),
        rapidjson::Value()
            .SetUint64(stl::Time::TimeStamp<std::chrono::milliseconds>())
            .Move(),
        result_.GetAllocator());
    result_.AddMember(
        rapidjson::Value().SetString("reqbody", result_.GetAllocator()).Move(),
        rapidjson::Value()
            .SetString(reqbody_.c_str(), result_.GetAllocator())
            .Move(),
        result_.GetAllocator());
    result_.AddMember(
        rapidjson::Value().SetString("code", result_.GetAllocator()).Move(),
        rapidjson::Value().SetInt(static_cast<int>(response_code_)).Move(),
        result_.GetAllocator());
    // data_time_ms
    result_.AddMember(
        rapidjson::Value().SetString("message", result_.GetAllocator()).Move(),
        rapidjson::Value()
            .SetString(ResponseCodeString[response_code_].c_str(),
                       result_.GetAllocator())
            .Move(),
        result_.GetAllocator());
    result = Json::toString(result_);
  } while (0);
  return result;
}