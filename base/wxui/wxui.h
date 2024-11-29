#if !defined(__D25FAF9D_0CAE_46CA_903C_168D4186E068__)
#define __D25FAF9D_0CAE_46CA_903C_168D4186E068__

#include <xs.h>
#include <system.h>
#include <sys.hpp>
#include <macros.h>
#include <stl.hpp>
#include "export.h"
using namespace wxui;
#include "deps.h"
#include "theme.h"
#include "config.h"
#include "frame_base.h"
#include "shape_frame.h"
#include "toolbar_frame.h"
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
protected:
  bool Start() override final;
  void Stop() override final;
  IConfig* ConfigGet() const override final;
  IFrame *GetFrame() const override;

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