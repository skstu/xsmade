#include "sys.h"
XS_EXTERN xs_errno_t xs_sys_get_home_path(char **out, size_t *out_size) {
  xs_errno_t err = xs_errno_t::XS_NO;
  do {
    const char *home = getenv("HOME");
    if (home) {
      *out_size = strlen(home);
      *out = (char *)malloc(*out_size);
      memcpy(*out, home, *out_size);
      err = xs_errno_t::XS_OK;
      break;
    }
    struct passwd *pw = getpwuid(getuid());
    if (!pw)
      break;
    *out_size = strlen(pw->pw_dir);
    *out = (char *)malloc(*out_size);
    memcpy(*out, pw->pw_dir, *out_size);
    err = xs_errno_t::XS_OK;
  } while (0);
  return err;
}
XS_EXTERN xs_errno_t xs_sys_get_config_path(char **out, size_t *out_size) {
  xs_errno_t err = xs_errno_t::XS_NO;
  do {
    char *path = getenv("XDG_CONFIG_HOME"); // ~/.config
    if (path) {
      *out_size = strlen(path);
      *out = (char *)malloc(*out_size);
      memcpy(*out, path, *out_size);
      err = xs_errno_t::XS_OK;
      break;
    }
    char *tmp = nullptr;
    size_t tmp_size = 0;
    xs_sys_get_home_path(&tmp, &tmp_size);
    std::string strTmp(tmp, tmp_size);
    free(tmp);
    strTmp += "/.config";
    *out_size = strTmp.size();
    *out = (char *)malloc(*out_size);
    memcpy(*out, strTmp.c_str(), *out_size);
    err = xs_errno_t::XS_OK;
  } while (0);
  return err;
}
XS_EXTERN xs_errno_t xs_sys_get_cache_path(char **out, size_t *out_size) {
  xs_errno_t err = xs_errno_t::XS_NO;
  do {
    char *path = getenv("XDG_CACHE_HOME"); // ~/.config
    if (path) {
      *out_size = strlen(path);
      *out = (char *)malloc(*out_size);
      memcpy(*out, path, *out_size);
      err = xs_errno_t::XS_OK;
      break;
    }
    char *tmp = nullptr;
    size_t tmp_size = 0;
    xs_sys_get_home_path(&tmp, &tmp_size);
    std::string strTmp(tmp, tmp_size);
    free(tmp);
    strTmp += "/.cache";
    *out_size = strTmp.size();
    *out = (char *)malloc(*out_size);
    memcpy(*out, strTmp.c_str(), *out_size);
    err = xs_errno_t::XS_OK;
  } while (0);
  return err;
}
XS_EXTERN xs_errno_t xs_sys_get_local_share_path(char **out, size_t *out_size) {
  xs_errno_t err = xs_errno_t::XS_NO;
  do {
    char *path = getenv("XDG_DATA_HOME"); // ~/.config
    if (path) {
      *out_size = strlen(path);
      *out = (char *)malloc(*out_size);
      memcpy(*out, path, *out_size);
      err = xs_errno_t::XS_OK;
      break;
    }
    char *tmp = nullptr;
    size_t tmp_size = 0;
    xs_sys_get_home_path(&tmp, &tmp_size);
    std::string strTmp(tmp, tmp_size);
    free(tmp);
    strTmp += "/.local/share";
    *out_size = strTmp.size();
    *out = (char *)malloc(*out_size);
    memcpy(*out, strTmp.c_str(), *out_size);
    err = xs_errno_t::XS_OK;
  } while (0);
  return err;
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