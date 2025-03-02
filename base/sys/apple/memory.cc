#include "sys.h"

XS_EXTERN int xs_sys_shared_memory_create(const char *name, size_t size,
                                          void **base) {
  return 0;
}
XS_EXTERN int xs_sys_shared_memory_destroy(const char *name) {
  return 0;
}
XS_EXTERN int xs_sys_shared_memory_open(const char *name, void **base) {

  return 0;
}