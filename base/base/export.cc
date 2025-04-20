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
xs_errno_t xs_base_chmod(const char *path, int mode) {
  xs_errno_t err = xs_errno_t::XS_NO;
  err = static_cast<xs_errno_t>(chmod(path, mode));
  return err;
}
xs_errno_t xs_base_kill(int pid, int signum) {
  xs_errno_t err = xs_errno_t::XS_NO;
  err = static_cast<xs_errno_t>(uv_kill(pid, signum));
  return err;
}
xs_errno_t xs_base_spawn(const char *args[], const char *envs[], void *route,
                         void (*rescb)(xs_process_id_t, xs_errno_t,
                                       const void *)) {
  xs_errno_t err = xs_errno_t::XS_NO;
  std::vector<std::string> spawn_args, spawn_envs;
  if (args) {
    for (int i = 0; args[i]; ++i) {
      spawn_args.push_back(args[i]);
    }
  }
  if (envs) {
    for (int i = 0; envs[i]; ++i) {
      spawn_envs.push_back(envs[i]);
    }
  }
  Base::GetOrCreate()->AddTask(static_cast<std::function<xs_errno_t()>>(
      [spawn_args, spawn_envs, route, rescb]() -> xs_errno_t {
        xs_errno_t err = xs_errno_t::XS_NO;
        xs_process_id_t pid = 0;
        do {
          auto loop = uv_default_loop();
          uv_process_options_t options;
          uv_process_t h = {0};
          memset(&options, 0, sizeof(options));
          std::vector<const char *> args, envs;
          for (const auto &arg : spawn_args) {
            args.push_back(arg.c_str());
          }
          for (const auto &env : spawn_envs) {
            envs.push_back(env.c_str());
          }
          args.push_back(nullptr);
          options.args =
              args.empty() ? nullptr : const_cast<char **>(args.data());
          options.file = args[0];
          options.flags = UV_PROCESS_DETACHED;
          options.env =
              spawn_envs.empty() ? nullptr : const_cast<char **>(envs.data());
          err = static_cast<xs_errno_t>(uv_spawn(loop, &h, &options));
          if (err != xs_errno_t::XS_OK)
            break;
          pid = h.pid;
          uv_unref((uv_handle_t *)&h); // 使得进程不阻止事件循环
          err = xs_errno_t::XS_OK;
        } while (0);
        if (rescb) {
          rescb(pid, err, route);
        }
        return err;
      }));
  err = xs_errno_t::XS_DONE;
  return err;
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