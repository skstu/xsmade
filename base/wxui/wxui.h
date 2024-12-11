#if !defined(__D25FAF9D_0CAE_46CA_903C_168D4186E068__)
#define __D25FAF9D_0CAE_46CA_903C_168D4186E068__

#include <xs.h>
#include <system.hpp>
#include <fmt/format.h>
#include "export.h"
using namespace wxui;
#include "deps.h"
#include "theme.h"
#include "config.h"
#include "global.h"
#include "recording_args.h"
#include "frame/frame_base.h"
#include "frame/frame_bkg.h"
#include "frame/frame_work.h"
#include "frame/frame_tool.h"
#include "frame/frame_tool_screenshot.h"
#include "frame/frame_work_image.h"
#include "frame.h"
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

/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 27 Nov 2024 03:59:30 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__D25FAF9D_0CAE_46CA_903C_168D4186E068__