#include "sys.h"
#ifndef PROC_PIDPATHINFO_MAXSIZE
#define PROC_PIDPATHINFO_MAXSIZE 1024
#endif
XS_EXTERN xs_errno_t xs_sys_process_getpid(xs_process_id_t *pid) {
  *pid = getpid();
  return xs_errno_t::XS_OK;
}
XS_EXTERN xs_errno_t xs_sys_get_commandline(char **out, size_t *out_size) {
  xs_errno_t err = xs_errno_t::XS_NO;
  do {
    std::vector<char> args = stl::File::Read("/proc/self/cmdline");
    if (args.empty())
      break;
    std::string final_args;
    for (auto &c : args) {
      if (c == 0)
        c = ' ';
    }
    final_args.append(&args[0], args.size());
    *out_size = final_args.size();
    *out = (char *)malloc(*out_size);
    memcpy(*out, final_args.data(), *out_size);
    err = xs_errno_t::XS_OK;
  } while (0);
  return err;
}
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

XS_EXTERN xs_errno_t xs_sys_process_kill(xs_process_id_t pid) {
  xs_errno_t err = xs_errno_t::XS_NO;
  err = (xs_errno_t)kill(pid, 9);
  return err;
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
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include <sys/types.h>

#if 0
char *get_exe_path(char *buf, int count)
{
    int i;
    
    int result = readlink("/home/ubuntu14-04/workspace/abcd",buf,count - 1);
    if (result < 0 || (result >= count - 1))
    {
        perror("readlink ");
        return NULL;
    }

    buf[result] = '\0';
    for (i = result; i >= 0; i--)
    {
        printf("buf[%d] %c\n",i,buf[i]);
        if (buf[i] == '/')
        {
            buf[i+1] = '\0';
            break;
        }
    }

    return buf;
}
#endif
XS_EXTERN xs_errno_t xs_sys_process_getpath(char **exepath, size_t *len) {
  xs_errno_t err = xs_errno_t::XS_NO;
  char path[4096] = {0};
  ssize_t readlink_len = readlink("/proc/self/exe", path, sizeof(path) - 1);
  do {
    if (readlink_len <= 0)
      break;
    std::string strPath(path, readlink_len);
    strPath = stl::Path::PathnameToPath(strPath);
    *len = strPath.size();
    *exepath = (char *)malloc(*len);
    memcpy(*exepath, strPath.data(), *len);
    err = xs_errno_t::XS_OK;
  } while (0);
  return err;
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
