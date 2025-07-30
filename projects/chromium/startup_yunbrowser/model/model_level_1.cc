#include "config.h"

ModelLevel1::ModelLevel1() {
}
ModelLevel1::~ModelLevel1() {
}
void ModelLevel1::Release() const {
  delete this;
}
const char *ModelLevel1::GetModelIdentify() const {
  return "Model-Level-1";
}
bool ModelLevel1::GetModel(chromium::xsiumio::IXSiumio &model) const {
  bool result = false;
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    if (xsiumios_.empty())
      break;
    std::uint32_t form = 0;
    std::uint32_t to = static_cast<std::uint32_t>(xsiumios_.size());
    std::uint32_t idx = stl::Random::GetRandomValue<std::uint32_t>(form, to);
    const chromium::xsiumio::IXSiumio *v =
        stl::Common::GetMapValueByKey<std::uint64_t,
                                      chromium::xsiumio::IXSiumio>(
            xsiumios_, static_cast<size_t>(idx));
    if (!v)
      break;
    rapidjson::Document docTmp(rapidjson::Type::kObjectType);
    *v >> docTmp;
    model << docTmp[chromium::xsiumio::kObjectKey];
    result = true;
  } while (0);
  return result;
}
