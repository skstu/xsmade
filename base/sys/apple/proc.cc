#include "sys.h"

XS_EXTERN int xs_sys_process_spawn(const char *proc, const char **args,
                                   int show_flag, xs_process_id_t *out_pid) {
  int r = -1;
  do {
    pid_t pid = 0;
    r = posix_spawn(&pid, proc, nullptr, nullptr,
                    const_cast<char *const *>(args), nullptr);
    if (r != 0)
      break;
    *out_pid = static_cast<xs_process_id_t>(pid);
  } while (0);
  return r;
}

XS_EXTERN int xs_sys_process_kill(xs_process_id_t pid) {
  int r = 0;
  r = kill(pid, 9);
  return r;
}
// XS_EXTERN int xs_sys_process_has_exit(long long pid) {
//   return kill(pid, 0) == 0 ? 1 : 0;
// }
XS_EXTERN int xs_sys_process_has_exit(xs_process_id_t pid) {
  int r = -1;
  int status;
  xs_process_id_t result = waitpid((xs_process_id_t)pid, &status, WNOHANG);
  if (result == 0) {
    r = 1;
    // 进程还在运行
    // return 0;
  } else if (result == pid) {
    // 进程已退出
    // return 1;
    r = 0;
  } else {
    // 出现错误，可能是进程不存在
    // return -1;
    r = -1;
  }
  return r;
}
XS_EXTERN int xs_sys_process_getpid(long *pid) {
  *pid = getpid();
  return 0;
}
XS_EXTERN int xs_sys_process_getpath(char **exepath, size_t *len) {
  int r = -1;
  *exepath = NULL;
  *len = 0;

  pid_t pid = getpid();
  char path[PROC_PIDPATHINFO_MAXSIZE];

  *len = proc_pidpath(pid, path, sizeof(path));
  if (*len <= 0) {
    return r;
  }
  *exepath = (char *)malloc(*len);
  if (*exepath) {
    memcpy(*exepath, path, *len);
    r = 0;
  }
  return r;
}
XS_EXTERN int
xs_sys_process_already_exists(xs_process_id_t pid /*==0 ? current*/) {
  int r = -1;
  int fd = -1;
  do {
    if (pid == 0)
      break;
    if (xs_sys_process_has_exit(pid) != 0) {
      r = 0;
    }
  } while (0);
  do {
    if (pid != 0)
      break;
    fd =
        open("/tmp/LaunchProjectsMutex.Service.lock", O_CREAT | O_WRONLY, 0666);
    if (fd == -1)
      break;
    if (flock(fd, LOCK_EX | LOCK_NB) == 0) {
      break;
    } else {
      r = 0;
      break;
    }
  } while (0);
  //!@ You cannot clean the file lock here, because the process exclusion will
  //! be invalidated once the file lock is cleaned
  // if (-1 != fd)
  //   close(fd);
  return r;
}