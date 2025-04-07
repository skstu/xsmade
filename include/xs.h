#if !defined(__E0803552_809F_4615_ACB4_7DEB537BCEB9__)
#define __E0803552_809F_4615_ACB4_7DEB537BCEB9__

/* Referenced C standard library header files */
#include <stdio.h>
#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
#define __OSWIN__ // Windows 系统
#elif defined(__APPLE__)
#define __OSAPPLE__
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
#define __OSIOS__ // iOS 系统
#elif TARGET_OS_MAC
#define __OSMAC__ // macOS 系统
#endif
#elif defined(__linux__) || defined(__unix__)

#define __OSLINUX__ // Linux 系统（包括 Ubuntu）
// #elif defined(__unix__)
// #define __OSUNIX__ // 其他 UNIX 系统
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

#if defined(__OSWIN__)
#if defined(SHARED_IMPLEMENTATION)
#if defined(_MSC_VER)
#define SHARED_API __declspec(dllexport)
#define SHARED_API_PRIVATE __declspec(dllexport)
#elif defined(__clang__)
#define SHARED_API __declspec(dllexport)
#define SHARED_API_PRIVATE __declspec(dllexport)
#elif defined(__GNUC__)
#define SHARED_API __declspec(dllexport)
#define SHARED_API_PRIVATE __declspec(dllexport)
#else
#define SHARED_API __declspec(dllexport)
#define SHARED_API_PRIVATE __declspec(dllexport)
#endif
#else
#define SHARED_API __declspec(dllimport)
#define SHARED_API_PRIVATE __declspec(dllimport)
#endif
#else // __OSWIN__
#if defined(SHARED_IMPLEMENTATION)
#if defined(__clang__)
#define SHARED_API __attribute__((visibility("default")))
#define SHARED_API_PRIVATE __attribute__((visibility("default")))
#elif defined(__GNUC__)
#define SHARED_API __attribute__((visibility("default")))
#define SHARED_API_PRIVATE __attribute__((visibility("default")))
#else
#define SHARED_API __attribute__((visibility("default")))
#define SHARED_API_PRIVATE __attribute__((visibility("default")))
#endif
#else
#define SHARED_API
#define SHARED_API_PRIVATE
#endif
#endif

#include <macros.h>
#include <xserr.h>
#include <system.h>
#include <stl.hpp>
#include <interface.hpp>

/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 19 Nov 2024 07:42:48 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__E0803552_809F_4615_ACB4_7DEB537BCEB9__