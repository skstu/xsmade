#if !defined(__FB113094_93A6_4EA0_A50B_819E43958F35__)
#define __FB113094_93A6_4EA0_A50B_819E43958F35__

#include "xs.h"
#include <dlfcn.h>
#include <string.h>

using tf_interface_init = void *(*)(void *, unsigned long);
using tf_interface_uninit = void (*)(void);
const char name_interface_init[] = "interface_init";
const char name_interface_uninit[] = "interface_uninit";

template <typename T> class Interface {
public:
  static T *Create(const char *dyPathname) {
    T *result = nullptr;
    void *handle_ = nullptr;
    tf_interface_init init_ = nullptr;
    tf_interface_uninit uninit_ = nullptr;
    do {
      if (!dyPathname) {
        break;
      }
      handle_ = dlopen(dyPathname, /*RTLD_NOW*/ RTLD_LAZY);
      if (!handle_)
        break;
      init_ = decltype(init_)(dlsym(handle_, name_interface_init));
      uninit_ = decltype(uninit_)(dlsym(handle_, name_interface_uninit));
      if (!init_ || !uninit_) {
        break;
      }
      result = (T *)init_((void *)dyPathname,
                          static_cast<unsigned long>(strlen(dyPathname)));
      if (!result) {
        uninit_();
        break;
      }
      result->handle_ = handle_;
      result->interface_init_ = init_;
      result->interface_uninit_ = uninit_;
      strcpy(result->module_filename_, dyPathname);
    } while (0);
    if (!result && handle_) {
      dlclose(handle_);
      handle_ = nullptr;
    }
    return result;
  }
  static void Destroy(T **obj) {
    do {
      if (!(*obj)) {
        break;
      }
      Interface *_this = (Interface *)(*obj);
      if (!_this) {
        break;
      }
      void *htmp = _this->handle_;
      if (_this->interface_uninit_) {
        _this->interface_uninit_();
      }
      if (htmp) {
        dlclose(htmp);
      }
      *obj = nullptr;
    } while (0);
  }

private:
  tf_interface_init interface_init_ = nullptr;
  tf_interface_uninit interface_uninit_ = nullptr;

public:
  void *ModuleHandle() const {
    return handle_;
  }

protected:
  void *handle_ = nullptr;
  char module_filename_[260] = {0};
};

/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 27 Nov 2024 05:37:24 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__FB113094_93A6_4EA0_A50B_819E43958F35__
