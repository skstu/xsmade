#if !defined(__A76E57F8_EA8B_450A_AE7C_181589707521__)
#define __A76E57F8_EA8B_450A_AE7C_181589707521__

#include <brwcfg.h>
#include "wxdeps.h"
#include "global.h"
#include "frame/frame.h"
#include "frame/activate.h"
#include "app.h"

namespace ui {
class IWxui {
public:
  static IWxui *Create();
  static void Destroy();

private:
  IWxui();
  virtual ~IWxui();
  void Init();
  void UnInit();
  void Stop();
  bool Start();

private:
  void MainProc();
  stl::tfThreads threads_;
  std::atomic_bool open_ = false;
};
} // namespace ui

/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 12 Jan 2025 00:00:24 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__A76E57F8_EA8B_450A_AE7C_181589707521__