#if !defined(__66C85601_CF91_446F_8CB5_96455760E625__)
#define __66C85601_CF91_446F_8CB5_96455760E625__

#if defined(__APPLE__)
#include "xs/system/apple/mac/sys.h"

#if 0
#if defined(__aarch64__)
// macOS + ARM64 架构
#elif defined(__x86_64__)
// macOS + Intel 64 位架构
#else
// macOS + 其他架构（如 i386）
#endif
#endif
#elif defined(_WIN32) || defined(_WIN64)
#include "xs/system/windows/sys.h"

#elif defined(__linux__)
#include "xs/system/linux/sys.h"
#endif

/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 06 Nov 2024 08:00:34 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__66C85601_CF91_446F_8CB5_96455760E625__
