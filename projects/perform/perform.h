#if !defined(__A6E39744_9A1D_4019_B6A3_33C44071925C__)
#define __A6E39744_9A1D_4019_B6A3_33C44071925C__

#define ENABLE_DEVELOPER_LOGGER 1

#include <xs.h>
#include <system.hpp>
#include <httplib.h>
#include <rapidjson.h>
#include <tinyxml2.hpp>
#include <fmt/format.h>
#include <conv.hpp>
#include <zipcc.h>
#include <log.hpp>
#include <components/wxui/export.h>
#include <components/uvpp/export.h>
#include "local.h"

//!@ browser
#include "process/browser/config.h"
#include "process/browser/configure.h"
#include "process/browser/response.h"
#include "process/browser/request.h"
#include "process/browser/browser.h"
#include "process/browser/ibrw.h"
//!@ downloader
#include "process/downloader/downloader.h"
//!@ streampp
#include "process/streampp/client/client.h"
#include "process/streampp/server/server.h"
#include "process/streampp/common/common.h"
#include "process/streampp/streampp.h"

#include "plugins/plugins.h"
#include "components/components.h"
#include "components/ffmpeg/ffxargs.h"
#include "components/ffmpeg/ffmpeg.h"

#include "cmdline.h"

class Perform {
public:
  static Perform *Create();
  static void Destroy();
  static Perform *Get();
  static IConfig *ConfigGet();

private:
  Perform();
  ~Perform();

public:
  void Release() const;
  void Run();

private:
  IPerform *current_ = nullptr;
  std::atomic_bool open_ = false;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 12 Nov 2024 11:26:03 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__A6E39744_9A1D_4019_B6A3_33C44071925C__