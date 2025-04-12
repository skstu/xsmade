#if !defined(__6B8F81DF_C72D_4C90_A184_F8F2BE7477DC__)
#define __6B8F81DF_C72D_4C90_A184_F8F2BE7477DC__

#include <xs.h>
#include <system.hpp>
#include <base.hpp>
#include <httplib.h>
#include <rapidjson.h>
#include <tinyxml2.hpp>
#include <fmt/format.h>
#include <conv.hpp>
#include <zipcc.h>
#include <log.hpp>
#include "config.h"
#include "ffx/ffxargs.h"
#include "ffx/ffmpeg.h"
#include "ibrwsvr.h"
class Startup {
public:
  Startup(const Startup &) = delete;
  Startup &operator=(const Startup &) = delete;
  void *operator new(size_t) = delete;
  void operator delete(void *) = delete;
  ~Startup();
  Startup();

public:
  void Run() const;

private:
  void Init();
  void UnInit();
  void OpenProcess() const;

private:
  std::string current_dir;
  std::atomic_bool ready_ = false;
  void *brwsvr_handle = nullptr;
  tf_startup brwsvr_startup = nullptr;
  tf_shutdown brwsvr_shutdown = nullptr;
  tf_malloc_s brwsvr_malloc_s = nullptr;
  tf_free_s brwsvr_free_s = nullptr;
  tf_request brwsvr_request = nullptr;
  tf_register_request_cbs brwsvr_register_request_cbs = nullptr;
};

/// /*_ Memade®（新生™） _**/
/// /*_ Thu, 06 Mar 2025 03:10:36 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__6B8F81DF_C72D_4C90_A184_F8F2BE7477DC__