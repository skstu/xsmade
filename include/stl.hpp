#if !defined(__B8180CB2_CC67_4024_933A_E67AC94FA0DB__)
#define __B8180CB2_CC67_4024_933A_E67AC94FA0DB__

/**
* @file stl.hpp
*
* @brief Only C++ STL functionality is encapsulated.
*
* @author Martell
* @date 2023-11-13
* @location SHE(ISO 3166-1)
*/

#define _PLATFORM_STL_VER __cplusplus

#ifdef _WIN32
	// #define _CRT_SECURE_NO_WARNINGS
#if _MSC_VER
#undef _PLATFORM_STL_VER
#define _PLATFORM_STL_VER _MSVC_LANG
#endif
#endif

#define _STL_HAS_CXX03 0
#define _STL_HAS_CXX11 0
#define _STL_HAS_CXX14 0
#define _STL_HAS_CXX17 0
#define _STL_HAS_CXX20 0
#define _STL_HAS_CXX23 0

#if _PLATFORM_STL_VER >= 199711L
#undef _STL_HAS_CXX03
#define _STL_HAS_CXX03 1
#endif

#if _PLATFORM_STL_VER >= 201103L
#undef _STL_HAS_CXX11
#define _STL_HAS_CXX11 1
#endif

#if _PLATFORM_STL_VER >= 201402L
#undef _STL_HAS_CXX14
#define _STL_HAS_CXX14 1
#endif

#if _PLATFORM_STL_VER >= 201703L
#undef _STL_HAS_CXX17
#define _STL_HAS_CXX17 1
#endif

#if _PLATFORM_STL_VER >= 202002L
#undef _STL_HAS_CXX20
#define _STL_HAS_CXX20 1
#endif

#if _PLATFORM_STL_VER > 202002L
#undef _STL_HAS_CXX23
#define _STL_HAS_CXX23 1
#endif

#if _STL_HAS_CXX03
#include <fcntl.h>

#include <algorithm>
#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#endif

#if _STL_HAS_CXX11
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <random>
#include <regex>
#include <thread>
#include <tuple>
#include <typeinfo>
#endif

#if _STL_HAS_CXX14
#include <any>
#include <bitset>
#include <deque>
#include <future>
#include <optional>
#include <string_view>
#include <variant>
#endif

#if _STL_HAS_CXX17
#include <locale>
#include <codecvt>
#include <filesystem>
//#if _PLATFORM_STL_VER == 201703L
//#include <experimental/coroutine>
//#endif
#endif

#if _STL_HAS_CXX20
#include <concepts>
#include <coroutine>
#if _WIN32 && _MSC_VER
#include <format>
#endif
#endif

#if _STL_HAS_CXX23
#include <span> //(proposed for C++23, but may be available in some compilers)
#endif

/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 05 Nov 2024 12:42:24 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__B8180CB2_CC67_4024_933A_E67AC94FA0DB__