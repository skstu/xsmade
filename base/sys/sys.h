#if !defined(__2CC5C4ED_79BA_4EA1_B4F2_ABD980B03F15__)
#define __2CC5C4ED_79BA_4EA1_B4F2_ABD980B03F15__

#include <xs.h>
#include <conv.hpp>
#if defined(__OSWIN__)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <shellapi.h>
#include <winioctl.h>
#include <intrin.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <shlobj.h>
#include <objbase.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
#elif defined(__OSLINUX__)

#elif defined(__OSAPPLE__)
#include <netinet/in.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysctl.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <dlfcn.h>
#include <spawn.h>
#include <limits.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <libproc.h>
// #include <Cocoa/Cocoa.h>
#include <CoreFoundation/CoreFoundation.h>
#include <ApplicationServices/ApplicationServices.h>
#include <ImageIO/ImageIO.h>
#endif

/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 12 Nov 2024 02:53:13 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__2CC5C4ED_79BA_4EA1_B4F2_ABD980B03F15__