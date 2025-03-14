#if !defined(__6B8F81DF_C72D_4C90_A184_F8F2BE7477DC__)
#define __6B8F81DF_C72D_4C90_A184_F8F2BE7477DC__

#include <xs.h>
#include <system.hpp>
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
};

/// /*_ Memade®（新生™） _**/
/// /*_ Thu, 06 Mar 2025 03:10:36 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__6B8F81DF_C72D_4C90_A184_F8F2BE7477DC__