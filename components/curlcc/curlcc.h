#if !defined(__A7AE0FB6_90A8_4123_82E4_70BE2492B465__)
#define __A7AE0FB6_90A8_4123_82E4_70BE2492B465__

#include <xs.h>
#include <stl.hpp>
#include <curl/curl.h>
#include <rapidjson.h>
#include "export.h"
#include "crawler/web.h"

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
  bool Perform() override final;

private:
  void Init();
  void UnInit();

private:
  std::atomic_bool ready_ = false;
  std::atomic_bool open_ = false;
};

/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 07 Dec 2024 02:23:49 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__A7AE0FB6_90A8_4123_82E4_70BE2492B465__
