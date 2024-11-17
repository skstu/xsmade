#if !defined(__66C85601_CF91_446F_8CB5_96455760E625__)
#define __66C85601_CF91_446F_8CB5_96455760E625__

#ifdef __cplusplus
extern "C" {
#endif
/* Referenced C standard library header files */
#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#if defined(_WIN32) || defined(_WIN64)
#define __OSWIN__ // Windows 系统
#elif defined(__APPLE__)
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
#define __OSIOS__ // iOS 系统
#elif TARGET_OS_MAC
#define __OSMAC__ // macOS 系统
#endif
#elif defined(__linux__)
#define __OSLINUX__ // Linux 系统（包括 Ubuntu）
#elif defined(__unix__)
#define __OSUNIX__ // 其他 UNIX 系统
#endif

/* Interface definition */
#if defined(BUILDING_XS_SHARED) && defined(USING_XS_SHARED)
#error "Define either BUILDING_XS_SHARED or USING_XS_SHARED, not both."
#endif

#ifndef XS_EXTERN
#ifdef __OSWIN__
/* Windows - set up dll import/export decorators. */
#if defined(BUILDING_XS_SHARED)
/* Building shared library. */
#define XS_EXTERN __declspec(dllexport)
#elif defined(USING_XS_SHARED)
/* Using shared library. */
#define XS_EXTERN __declspec(dllimport)
#else
/* Building static library. */
#define XS_EXTERN /* nothing */
#endif
#elif __GNUC__ >= 4
#define XS_EXTERN __attribute__((visibility("default")))
#elif defined(__SUNPRO_C) && (__SUNPRO_C >= 0x550) /* Sun Studio >= 8 */
#define XS_EXTERN __global
#else
#define XS_EXTERN /* nothing */
#endif
#endif /* XS_EXTERN */

typedef long long process_id_t;

XS_EXTERN char *xs_sys_malloc(size_t len);
XS_EXTERN void xs_sys_free(void **p);
XS_EXTERN unsigned short xs_sys_get_free_port(void);
XS_EXTERN int xs_sys_process_spawn(const char *proc, const char **args,
                                   long long *out_pid);
XS_EXTERN int xs_sys_process_kill(long long pid);
//!@ exited == 0 and running  == !0
XS_EXTERN int xs_sys_process_has_exit(long long pid);
XS_EXTERN int xs_sys_process_getpath(char **, size_t *);
XS_EXTERN int xs_sys_process_getpid(long long *);
//!@ exists == 0 and not exists == !0
XS_EXTERN int xs_sys_process_already_exists(long long pid /*==0 ? current*/);
XS_EXTERN int xs_sys_get_appdata_path(char **, size_t *);
#ifdef __cplusplus
}
#endif
/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 06 Nov 2024 08:00:34 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__66C85601_CF91_446F_8CB5_96455760E625__
