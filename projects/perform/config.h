#if !defined(__918F8A06_5054_4610_918C_97CFBD43D91B__)
#define __918F8A06_5054_4610_918C_97CFBD43D91B__

#define ENABLE_DEVELOPER_DEBUG 1
#define ENABLE_DEVELOPER_LOGGER 1

#include <sys.hpp>
#include <httplib.h>
#include <rapidjson.h>
#include <fmt/format.h>
#include <utfpp.hpp>
#include <zipcc.h>
#include <log.hpp>
#include <projects/ffxctrl/export.h>

#include "define.h"
#include "configure.h"
#include "ffxargs.h"
#include "browser.h"
#include "components.h"
#include "server.h"
#include "perform.h"

class Config {
public:
  class Paths {
  public:
    std::string root_dir;                // "${AppData}/MarsProjects/"
    std::string logs_dir;                // "/logs/"
    std::string chromium_dir;            // "/chromium/"
    std::string chromium_user_data_dir;  // "/userdata/"
    std::string chromium_extensions_dir; // "/chromium/extensions/"
    std::string brw_projects_route_file; // "${AppData}/MarsProjects/route.json"
    std::string
        brw_projects_configure_file; // "${AppData}/MarsProjects/configure.json"
  };

public:
  static Config *ConfigGet();
  static void Destroy();

private:
  Config();
  ~Config();

private:
  void Init();
  void UnInit();
  void PathsInit();

public:
  void RouteConfigureInit(const unsigned int &) const;
  unsigned int RouteConfigureGetClientPort() const;
  const Paths &PathGet() const;
  std::string GetBrwUserDataDir(const std::string &brwKey) const;
  std::string GetXSCacheExtsDir(const std::string &brwKey) const;
  std::string GetXSCacheExtsDir(const std::string &brwKey,
                                const std::string &extId) const;
  std::string GetXSCacheCfgsDir(const std::string &brwKey) const;
  std::string GetXSCacheStatisDir(const std::string &brwKey) const;
  std::string GetXSCacheConfigureFName(const std::string &brwKey) const;
  void XSCacheClean(const std::string &brwKey) const;

public:
  static std::string CreateBrwCloseNotifyPak(const std::string &brwId);

private:
  Paths paths_;
  std::string current_process_path_;
  std::string work_projects_path_;
  std::string chromium_path_;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();

public:
  const std::string project_name_ = "MarsProjects";
};

/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 11 Nov 2024 09:56:50 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__918F8A06_5054_4610_918C_97CFBD43D91B__