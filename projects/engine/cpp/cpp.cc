#include "cpp.h"

Cpp::Cpp() {
}
Cpp::~Cpp() {
}

///////////////////////////////////////////////////////////////
Cpp *Cpp::cpp_ = nullptr;
std::mutex Cpp::mtx_;
Cpp *Cpp::Get() {
  std::lock_guard<std::mutex> lck(mtx_);
  if (!cpp_)
    cpp_ = new Cpp();
  return cpp_;
}
void Cpp::Destroy() {
  std::lock_guard<std::mutex> lck(mtx_);
  SK_DELETE_PTR(cpp_);
}
#ifdef __cplusplus
extern "C" {
#endif
SHARED_API void *interface_init(void *, unsigned long) {
  ICpp *result = dynamic_cast<ICpp *>(Cpp::Get());
  return result;
}
SHARED_API void interface_uninit() {
  Cpp::Destroy();
}
#ifdef __cplusplus
}
#endif