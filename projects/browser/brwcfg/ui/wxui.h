#if !defined(__7FA73519_E036_48E2_AAB7_1DB9C715BA5F__)
#define __7FA73519_E036_48E2_AAB7_1DB9C715BA5F__

#include "frame/frame.h"
#include "frame/background.h"
#include "app.h"

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

public:
  bool Ready() const;
  IFrame *GetFrame() const;
  stl::Signal *GetReadySignal() const;

private:
  void MainProc();
  stl::tfThreads threads_;
  std::atomic_bool open_ = false;
  stl::Signal *ready_signal_ = nullptr;
};

/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 02 Mar 2025 12:28:27 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__7FA73519_E036_48E2_AAB7_1DB9C715BA5F__