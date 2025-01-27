#include "jsonnet.h"

Jsonnet::Jsonnet() {
}
Jsonnet::~Jsonnet() {
}

///////////////////////////////////////////////////////////////
Jsonnet *Jsonnet::jsonnet_ = nullptr;
std::mutex Jsonnet::mtx_;
Jsonnet *Jsonnet::Get() {
  std::lock_guard<std::mutex> lck(mtx_);
  if (!jsonnet_)
    jsonnet_ = new Jsonnet();
  return jsonnet_;
}
void Jsonnet::Destroy() {
  std::lock_guard<std::mutex> lck(mtx_);
  SK_DELETE_PTR(jsonnet_);
}
#ifdef __cplusplus
extern "C" {
#endif
SHARED_API void *interface_init(void *, unsigned long) {
  IJsonnet *result = dynamic_cast<IJsonnet *>(Jsonnet::Get());
  return result;
}
SHARED_API void interface_uninit() {
  Jsonnet::Destroy();
}
#ifdef __cplusplus
}
#endif