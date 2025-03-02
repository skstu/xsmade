#if !defined(__8FD1939E_CBA3_4EDC_B4A6_CA2886982F84__)
#define __8FD1939E_CBA3_4EDC_B4A6_CA2886982F84__
#include <xs.h>
#include <system.hpp>
#include <log.h>
#include <components/uvpp/export.h>
#include "process/process.h"

#if defined(__OSWIN__)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#endif

class Launch {
public:
  Launch(const std::string &args);
  ~Launch();

private:
  void Init();
  void UnInit();

public:
  void Perform();

private:
  const std::string args_;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 01 Feb 2025 02:56:05 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__8FD1939E_CBA3_4EDC_B4A6_CA2886982F84__