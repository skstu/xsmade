#include "base.h"
xs_errno_t xs_base_startup(void) {
  auto p = Base::GetOrCreate();
  p->Start();
  return xs_errno_t::XS_EBASINIT;
}
xs_errno_t xs_base_shutdown(void) {
  Base::Destroy();
  return xs_errno_t::XS_EBASUNINIT;
}
xs_errno_t xs_base_free(void **p) {
  if (p) {
    if (*p) {
      free(*p);
      *p = nullptr;
      return xs_errno_t::XS_OK;
    }
  }
  return xs_errno_t::XS_EBASFREE;
}
char *xs_base_malloc(size_t len) {
  char *result = nullptr;
  do {
    if (len <= 0)
      break;
    result = (char *)malloc(len);
  } while (0);
  return result;
}

xs_errno_t xs_base_spawn(const char *proc, const char *cmdline,
                         const char *env) {
  std::string strProc(proc);
  std::string strCmdline(cmdline);
  std::string strEnv(env);
  Base::GetOrCreate()->AddTask(static_cast<std::function<xs_errno_t()>>(
      [strProc, strCmdline, strEnv]() -> xs_errno_t { ////
        auto loop = uv_default_loop();
        return xs_errno_t::XS_OK;
      }));
  return xs_errno_t::XS_OK;
}
xs_errno_t xs_base_add_task_v1(tf_xs_base_task_v1 func) {
  xs_errno_t err = xs_errno_t::XS_OK;
  // Base::GetOrCreate()->AddTask(std::function<xs_errno_t()>(func));
  Base::GetOrCreate()->AddTask(
      static_cast<std::function<xs_errno_t()>>([func]() -> xs_errno_t { ////
        auto loop = uv_default_loop();
        return func();
      }));
  return err;
}