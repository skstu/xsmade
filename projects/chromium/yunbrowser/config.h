#if !defined(__ACA1E418_2B6E_4539_A80F_D74605B0FD7D__)
#define __ACA1E418_2B6E_4539_A80F_D74605B0FD7D__

#define ENABLE_DEVELOP_MODE 1
constexpr int kProxyUseCountMax = 10;
constexpr long long kChromiumTimeout = 70; //!@ seconds

enum class ModelKey {
  kFpsdb = 0x0,
  kNull1 = 0x1,
  kNull2 = 0x2,
  kNull3 = 0x3,
  kNull4 = 0x4,
  kNull5 = 0x5,
  kNull6 = 0x6,
  kNull7 = 0x7,
  kNull8 = 0x8,
  kNull9 = 0x9,
  kModelPartsBegin = kNull9 + 1, // 0xA
  kModelCfgBegin = kFpsdb,
  kModelCfgEnd = kModelPartsBegin - 1,
};

enum class BrowserStatus {
  kUnknown,
  kStarting,
  kStopping,
  kStarted,
  kStopped,
  kTimeout,
  kIdle,
  kReady = kStopped,
  kRunning = kStarted,
};

#include <xs.h>
#include <system.hpp>
#include <base.hpp>
#include <rapidjson.h>
#include <tinyxml2.hpp>
#include <fmt/format.h>
#include <conv.hpp>
#include <zipcc.h>
#include <log.hpp>
#define CPPHTTPLIB_ZLIB_SUPPORT 1
#include <httplib.h>
#include <rapidjson.h>
#include <ssl.hpp>
#include <conv.hpp>
#include <packet.hpp>

#include "error.hpp"
#include "settings.hpp"
#include <components/curlcc/export.h>
#include <components/icucc/export.h>
#include <fpsdb.hpp>
#include "yunlogin/yunlogin_config.hpp"
#include "comps.h"
using namespace chromium;
#include "client.h"
#include "model/model.h"
#include "request.hpp"
#include "chromium.h"
#include "browser.h"
#include "server.h"
#include "startup.h"

class Config final {
public:
  static Config *CreateOrGet();
  static void Destroy();
  static bool DevelopMode();

private:
  Config();
  ~Config();

private:
  void Init();
  void UnInit();

public:
  const std::string &GetCurrentDir() const;
  const std::string &GetProjectLogsDir() const;
  const std::string &GetProjectTmpDir() const;
  const std::string &GetChromiumProcessPath() const;
  const std::string &GetProjectModelPartsDir() const;
  const std::string &GetProjectModelDir() const;
  const std::string &GetProjectCacheDir() const;
  const std::string &GetProjectRootDir() const;
  std::string
  GetChromiumUserDataDir(const chromium::xsiumio::tfIdentifyType &) const;
  const std::string &GetProjectConfiguresDir() const;
  const std::string &GetProjectComponentsDir() const;
  const std::string &GetProjectSettingsDir() const;
  std::string GetChromiumProcessName() const;
  std::string GetChromiumVersion() const;
  const std::string &GetBridgeProcessName() const;
  const std::string &GetBridgeProcessPath() const;
  const std::string &GetProjectXSCfgPath() const;
  const std::string &GetProjectRouteDir() const;
  const std::string &GetGenConfigPath() const;

public:
  ISettings *settings_ = nullptr;
  std::string current_dir_;
  std::string project_root_dir_;
  std::string project_xscfg_path_;
  std::string project_settings_path_;
  std::string project_components_path_;
  std::string project_cache_dir_;
  std::string project_logs_dir_;
  std::string project_tmp_dir_;
  std::string chromium_process_path_;
  std::string project_model_parts_dir_;
  std::string project_model_dir_;
  std::string project_configures_dir_;
  std::string project_settings_dir_;
  std::string project_bridge_process_name_;
  std::string project_bridge_process_path_;
  std::string project_route_dir_;
  std::string project_gen_configure_path_;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
  std::map<std::string, std::string> chromium_startup_process_;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 30 May 2025 03:32:51 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__ACA1E418_2B6E_4539_A80F_D74605B0FD7D__