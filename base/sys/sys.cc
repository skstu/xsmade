#include "sys.h"

XS_EXTERN char *xs_sys_malloc(size_t len) {
  char *result = nullptr;
  do {
    if (len <= 0)
      break;
    result = (char *)malloc(len);
  } while (0);
  return result;
}

XS_EXTERN void xs_sys_free(void **p) {
  if (p) {
    if (*p) {
      free(*p);
      *p = nullptr;
    }
  }
}

XS_EXTERN int xs_sys_image_stream_destroy(xs_image_stream_t **p) {
  if (p && (*p)) {
    xs_sys_free((void **)&(*p)->buffer);
    free(*p);
    *p = nullptr;
  }
  return 0;
}
