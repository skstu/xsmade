#if !defined(__66C85601_CF91_446F_8CB5_96455760E625__)
#define __66C85601_CF91_446F_8CB5_96455760E625__

#include <xs.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__OSWIN__)
typedef unsigned long xs_process_id_t;
#elif defined(__OSAPPLE__)
typedef pid_t xs_process_id_t;
#elif defined(__OSLINUX__)
typedef pid_t xs_process_id_t;
#endif
typedef void *xs_process_handle_t;

typedef struct {
  long x;
  long y;
  long cx;
  long cy;
} xs_position_t;

typedef enum {
  _Unknown,
  _PNG,
  _JPEG,
  _BMP,
  _GIF,
  _ICO,
} xs_image_type_t;

typedef enum {
  PNG = 0,
  JPEG,
  BMP,
} xs_image_stream_type_t;

typedef struct {
  char *buffer;
  size_t len;
} xs_image_stream_t;

typedef xs_image_stream_t xs_buffer_t;

XS_EXTERN void xs_sys_startup(void);
XS_EXTERN void xs_sys_shutdown(void);
XS_EXTERN char *xs_sys_malloc(size_t len);
XS_EXTERN void xs_sys_free(void **p);
XS_EXTERN void xs_sys_free_buffer(xs_buffer_t **);
XS_EXTERN unsigned short xs_sys_get_free_port(void);
XS_EXTERN xs_errno_t xs_sys_process_spawn(const char *proc, const char **argv,
                                   const char **envp, int show_flag,
                                   xs_process_id_t *out_pid);
XS_EXTERN xs_errno_t xs_sys_process_kill(xs_process_id_t pid, int);
//!@ exited == 0 and running  == !0
XS_EXTERN int xs_sys_process_has_exit(xs_process_id_t pid);
XS_EXTERN xs_errno_t xs_sys_process_getpath(char **, size_t *);
XS_EXTERN xs_errno_t xs_sys_process_getpid(xs_process_id_t *);
//!@ exists == 0 and not exists == !0
XS_EXTERN int
xs_sys_process_already_exists(xs_process_id_t pid /*==0 ? current*/);
XS_EXTERN int xs_sys_get_appdata_path(char **, size_t *);
XS_EXTERN int xs_sys_image_stream_destroy(xs_image_stream_t **);
XS_EXTERN int xs_sys_capturescreen(xs_position_t pos,
                                   xs_image_stream_type_t type,
                                   xs_image_stream_t **stream);
XS_EXTERN int xs_sys_get_image_type(const char *buffer, size_t buffer_size,
                                    xs_image_type_t *output_image_type);
XS_EXTERN xs_errno_t xs_sys_get_dll_path(xs_buffer_t **out_buffer,
                                         void *static_dummy_variable);
XS_EXTERN int xs_sys_shared_memory_create(const char *name, size_t size,
                                          void **base);
XS_EXTERN int xs_sys_shared_memory_destroy(const char *name);
XS_EXTERN int xs_sys_shared_memory_open(const char *name, void **base);
XS_EXTERN xs_errno_t xs_sys_get_commandline(char **, size_t *);
//!@ linux ~/.config	~/.local/share	~/.cache  /home
XS_EXTERN xs_errno_t xs_sys_get_home_path(char **, size_t *);
XS_EXTERN xs_errno_t xs_sys_get_config_path(char **, size_t *);
XS_EXTERN xs_errno_t xs_sys_get_cache_path(char **, size_t *);
XS_EXTERN xs_errno_t xs_sys_get_local_share_path(char **, size_t *);
XS_EXTERN xs_errno_t xs_sys_process_already_running(void);
#ifdef __cplusplus
}
#endif
/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 06 Nov 2024 08:00:34 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__66C85601_CF91_446F_8CB5_96455760E625__
