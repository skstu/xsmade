#if !defined(__57DD9926_BA9A_4031_99FE_F02A69081173__)
#define __57DD9926_BA9A_4031_99FE_F02A69081173__

#include <xs.h>
#include <system.hpp>
#include "MediaStreamComm/MediaStreamComm.h"
#if defined(__OSWIN__)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#elif defined(__OSMAC__)
#endif
class MediaStreamServer {
public:
  static MediaStreamServer *Create();
  static void Destroy();
private:
  MediaStreamServer();
  ~MediaStreamServer();

public:
  bool Start();
  void Stop();

private:
  std::atomic_bool open_ = false;
  std::vector<IServer *> servers_;
};

/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 07 Dec 2024 23:02:38 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__57DD9926_BA9A_4031_99FE_F02A69081173__