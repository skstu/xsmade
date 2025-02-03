#if !defined(__00F7CBF4_E965_4FD2_8430_0CB6D1351341__)
#define __00F7CBF4_E965_4FD2_8430_0CB6D1351341__
#include <xs.h>
#include <system.hpp>
#include <log.h>
#if defined(__OSWIN__)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#endif
#include <pluginapi.h>
#include "deps.h"
#include "app.h"

extern extra_parameters *nsis_extra_parameters;
#define NSIS_INIT_EXTRA_PARAMETERS(p)                                          \
  do {                                                                         \
    if (!nsis_extra_parameters)                                                \
      nsis_extra_parameters = p;                                               \
  } while (0);

#if 0
#include <xs.h>
#include <system.hpp>
#include <fmt/format.h>
#include <rapidjson.h>
#include "export.h"
using namespace wxui;
#include "deps.h"
#include "theme.h"
#include "config.h"
#include "global.h"
#include "recording_args.h"
#include "frame/frame_base.h"
#include "frame.h"
#include "frame/guide.h"
#include "app.h"

class Wxui final : public IWxui {
public:
  static Wxui *Create();
  static void Destroy();

private:
  Wxui();
  virtual ~Wxui();
  void Init();
  void UnInit();

public:
  void Stop() override final;

protected:
  bool Start() override final;
  bool Ready() const override final;
  IConfig *ConfigGet() const override final;
  IFrame *GetFrame() const override final;
  void NotifyRecordingEnd() const override final;

private:
  void MainProc();
  stl::tfThreads threads_;
  std::atomic_bool open_ = false;
};

#ifdef __cplusplus
extern "C" {
#endif
SHARED_API void *interface_init(void *, unsigned long);
SHARED_API void interface_uninit();
#ifdef __cplusplus
}
#endif
#endif
/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 03 Feb 2025 03:04:19 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__00F7CBF4_E965_4FD2_8430_0CB6D1351341__
