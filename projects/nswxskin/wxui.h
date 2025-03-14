#if !defined(__00F7CBF4_E965_4FD2_8430_0CB6D1351341__)
#define __00F7CBF4_E965_4FD2_8430_0CB6D1351341__
#include <xs.h>
#include <system.hpp>
#include <conv.hpp>
#include <log.h>
#if defined(__OSWIN__)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#endif
#include <pluginapi.h>
#include "deps.h"
#include "frames/background.h"
#include "frames/frame.h"
#include "app.h"
#include "global.h"

class Wxui {
public:
  static Wxui *Create();
  static void Destroy();

private:
  Wxui();
  virtual ~Wxui();
  void Init();
  void UnInit();

public:
  void Stop();
  bool Start();

protected:
  bool Ready() const;
  Frame *GetFrame() const;
  HWND GetHWND() const;
private:
  void MainProc();
  stl::tfThreads threads_;
  std::atomic_bool open_ = false;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 03 Feb 2025 03:04:19 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__00F7CBF4_E965_4FD2_8430_0CB6D1351341__
