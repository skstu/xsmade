#include "brwcfg.h"

const std::map<ExtensionsRequest::Method, std::string>
    ExtensionsRequest::MethodToStringMap = {
        {ExtensionsRequest::Method::init, "init"},
        {ExtensionsRequest::Method::uninit, "uninit"}};
const std::map<ExtensionsRequest::Target, std::string>
    ExtensionsRequest::TargetToStringMap = {
        {ExtensionsRequest::Target::kernel, "kernel"}};
const std::map<std::string, ExtensionsRequest::Method>
    ExtensionsRequest::StringToMethodMap = {
        {"init", ExtensionsRequest::Method::init},
        {"uninit", ExtensionsRequest::Method::uninit}};
const std::map<std::string, ExtensionsRequest::Target>
    ExtensionsRequest::StringToTargetMap = {
        {"kernel", ExtensionsRequest::Target::kernel}};

std::string ExtensionsRequest::MethodToString(Method m) {
  auto it = MethodToStringMap.find(m);
  if (it != MethodToStringMap.end())
    return it->second;
  return "unknown";
}
std::string ExtensionsRequest::TargetToString(Target m) {
  auto it = TargetToStringMap.find(m);
  if (it != TargetToStringMap.end())
    return it->second;
  return "unknown";
}

ExtensionsRequest::Method
ExtensionsRequest::StringToMethod(const std::string &str) {
  std::string lower = str;
  std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
  auto it = StringToMethodMap.find(lower);
  if (it != StringToMethodMap.end())
    return it->second;
  return Method::unknown;
}

ExtensionsRequest::Target
ExtensionsRequest::StringToTarget(const std::string &str) {
  std::string lower = str;
  std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
  auto it = StringToTargetMap.find(lower);
  if (it != StringToTargetMap.end())
    return it->second;
  return Target::unknown;
}

ExtensionsRequest::ExtensionsRequest(const std::string &id,
                                     const std::string &body)
    : id_(id) {
  *this << body;
}
const std::string &ExtensionsRequest::GetExtensionsId() const {
  return id_;
}
bool ExtensionsRequest::operator<<(const std::string &body) {
  bool result = false;
  do {
    if (body.empty())
      break;
    rapidjson::Document doc(rapidjson::Type::kObjectType);
    if (doc.Parse(body.data(), body.size()).HasParseError())
      break;
    if (!doc.IsObject())
      break;
    if (doc.HasMember("method") && doc["method"].IsString()) {
      auto ss = 0;
    }
    if (doc.HasMember("target") && doc["target"].IsString()) {
      auto ss = 0;
    }
  } while (0);
  return result;
}