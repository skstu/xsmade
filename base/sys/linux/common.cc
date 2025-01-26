#include "sys.h"
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
int xs_sys_get_dll_path(xs_buffer_t **out_buffer, void *static_dummy_variable) {
  return -1;
}