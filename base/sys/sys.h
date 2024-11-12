#if !defined(__2CC5C4ED_79BA_4EA1_B4F2_ABD980B03F15__)
#define __2CC5C4ED_79BA_4EA1_B4F2_ABD980B03F15__

#include <system.h>

#if defined(_WIN32) || defined(_WIN64)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <winioctl.h>
#include <intrin.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#elif __APPLE__
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <unistd.h>
#include <spawn.h>
#include <CoreFoundation/CoreFoundation.h>
#include <ApplicationServices/ApplicationServices.h>
#endif

#include "stl.hpp"

/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 12 Nov 2024 02:53:13 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__2CC5C4ED_79BA_4EA1_B4F2_ABD980B03F15__