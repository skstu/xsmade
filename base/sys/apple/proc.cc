#include "sys.h"

XS_EXTERN int xs_sys_process_spawn(const char *proc, const char **args,
                                    long long *out_pid) {
  int r = -1;
  do {
    pid_t pid = 0;
    r = posix_spawn(&pid, proc, nullptr, nullptr,
                    const_cast<char *const *>(args), nullptr);
    if (r != 0)
      break;
    *out_pid = static_cast<long long>(pid);
  } while (0);
  return r;
}

XS_EXTERN int xs_sys_process_kill(long long pid) {
  int r = 0;
  r = kill(pid, 9);
  return r;
}