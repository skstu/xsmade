#if !defined(__A7AE0FB6_90A8_4123_82E4_70BE2492B465__)
#define __A7AE0FB6_90A8_4123_82E4_70BE2492B465__

#include <macros.h>
#include <system.h>
#include <sys.hpp>
#include <stl.hpp>
#include <curl/curl.h>
#include "export.h"
using namespace curl;

class Curl final : public ICurl {
public:
  static Curl *Create();
  static void Destroy();
private:
  Curl();
  virtual ~Curl();

protected:
  bool Start() override final;
  void Stop() override final;
  bool Ready() const override final;

private:
  void Init();
  void UnInit();

private:
  std::atomic_bool ready_ = false;
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
/// /*_ Sat, 07 Dec 2024 02:23:49 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__A7AE0FB6_90A8_4123_82E4_70BE2492B465__
