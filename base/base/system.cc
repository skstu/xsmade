#include "base.h"
#ifndef PATHMAX
#undef PATHMAX
#define PATHMAX 4096
#endif
using namespace xs::base;
System::System() {
}

System::~System() {
}
xs_errno_t System::os_gethostname(std::string &buffer) {
  xs_errno_t err = xs_errno_t::XS_NO;
  buffer.resize(UV_MAXHOSTNAMESIZE, 0x00);
  size_t size = buffer.size();
  int r = uv_os_gethostname(&buffer[0], &size);
  if (r > 0) {
    buffer.resize(size);
    err = xs_errno_t::XS_OK;
  }
  return err;
}
xs_errno_t System::os_uname(utsname_t &uname) {
  xs_errno_t err = xs_errno_t::XS_NO;
  uv_utsname_t utsname = {0};
  err = static_cast<xs_errno_t>(uv_os_uname(&utsname));
  if (err == xs_errno_t::XS_OK) {
    uname.sysname = utsname.sysname;
    uname.release = utsname.release;
    uname.version = utsname.version;
    uname.machine = utsname.machine;
    err = xs_errno_t::XS_OK;
  }
  return err;
}
xs_errno_t System::exepath(std::string &path) {
  xs_errno_t err = xs_errno_t::XS_NO;
  path.resize(PATHMAX, 0x00);
  size_t path_len = path.size();
  err = static_cast<xs_errno_t>(uv_exepath(&path[0], &path_len));
  if (err == xs_errno_t::XS_OK)
    path.resize(path_len);
  return err;
}