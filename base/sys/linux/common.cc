#include "sys.h"
int xs_sys_get_linux_home_path(char **out, size_t *out_size) {
  int r = -1;
  do {
    const char *home = getenv("HOME");
    if (home) {
      *out_size = strlen(home);
      *out = (char *)malloc(*out_size);
      memcpy(*out, home, *out_size);
      r = 0;
      break;
    }
    struct passwd *pw = getpwuid(getuid());
    if (!pw)
      break;
    *out_size = strlen(pw->pw_dir);
    *out = (char *)malloc(*out_size);
    memcpy(*out, pw->pw_dir, *out_size);
    r = 0;
  } while (0);
  return r;
}
XS_EXTERN int xs_sys_get_linux_config_path(char **, size_t *) {
  int r = -1;
  do {

    r = 0;
  } while (0);
  return r;
}
XS_EXTERN int xs_sys_get_linux_cache_path(char **, size_t *) {
  int r = -1;
  do {

    r = 0;
  } while (0);
  return r;
}
XS_EXTERN int xs_sys_get_linux_local_share_path(char **, size_t *) {
  int r = -1;
  do {

    r = 0;
  } while (0);
  return r;
}

//////////////////////////////////////////////////////////////////////////////////////
XS_EXTERN void xs_sys_startup(void) {
}
XS_EXTERN void xs_sys_shutdown(void) {
}
XS_EXTERN int xs_sys_get_appdata_path(char **out, size_t *len) {
  return -1;
}

XS_EXTERN int xs_sys_capturescreen(xs_position_t pos,
                                   xs_image_stream_type_t type,
                                   xs_image_stream_t **stream) {
  return -1;
}
XS_EXTERN int xs_sys_get_dll_path(xs_buffer_t **out_buffer,
                                  void *static_dummy_variable) {
  return -1;
}