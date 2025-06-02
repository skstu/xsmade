
#include "sys.h"

class SingleInstance {
public:
  SingleInstance(const char *lockfile) : locked_(false) {
#ifdef _WIN32
    hMutex_ = CreateMutexA(NULL, TRUE, lockfile);
    locked_ = (GetLastError() != ERROR_ALREADY_EXISTS);
#else
    fd_ = open(lockfile, O_CREAT | O_RDWR, 0666);
    if (fd_ >= 0) {
      locked_ = (lockf(fd_, F_TLOCK, 0) == 0);
    }
#endif
  }
  ~SingleInstance() {
#ifdef _WIN32
    if (hMutex_)
      CloseHandle(hMutex_);
#else
    if (locked_ && fd_ >= 0) {
      lockf(fd_, F_ULOCK, 0);
      close(fd_);
    }
#endif
  }
  bool IsSingle() const {
    return locked_;
  }

private:
  bool locked_;
#ifdef _WIN32
  HANDLE hMutex_;
#else
  int fd_;
#endif
};

xs_errno_t xs_sys_process_already_running(void) {
  xs_errno_t r = XS_OK;
  SingleInstance instance("my_unique_app_lock");
  if (!instance.IsSingle()) {
    r = xs_errno_t::XS_WALREADYRUNNING;
  }
  return r;
}