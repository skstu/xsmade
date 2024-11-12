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

/* Interface definition */
#if defined(BUILDING_XS_SHARED) && defined(USING_XS_SHARED)
#error "Define either BUILDING_XS_SHARED or USING_XS_SHARED, not both."
#endif

#ifndef XS_EXTERN
#ifdef _WIN32
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

XS_EXTERN unsigned short xs_sys_get_free_port(void);
XS_EXTERN int xs_sys_process_spawn(const char *proc, const char **args,
                                    long long *out_pid);
XS_EXTERN int xs_sys_process_kill(long long pid);
XS_EXTERN int xs_sys_process_has_exit(long long pid);
#ifdef __cplusplus
}
#endif
/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 06 Nov 2024 08:00:34 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__66C85601_CF91_446F_8CB5_96455760E625__
