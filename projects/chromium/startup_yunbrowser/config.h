#if !defined(__ACA1E418_2B6E_4539_A80F_D74605B0FD7D__)
#define __ACA1E418_2B6E_4539_A80F_D74605B0FD7D__
#include <xs.h>
#include <system.hpp>
#include <base.hpp>
#include <rapidjson.h>
#include <tinyxml2.hpp>
#include <fmt/format.h>
#include <conv.hpp>
#include <zipcc.h>
#include <log.hpp>
#include <httplib.h>
#include <rapidjson.h>
#include <ssl.hpp>
#include <conv.hpp>
#include <packet.hpp>

#include "error.hpp"
#include "settings.hpp"
#include <components/curlcc/export.h>
#include <fpsdb.hpp>
#include "yunlogin/yunlogin_config.hpp"
using namespace chromium;
#include "chromium.h"
#include "browser.h"
#include "server.h"
#include "model/model.h"
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
  void SetChromiumUserDataDir(const std::string &dir);
  const std::string &GetChromiumUserDataDir() const;

public:
  ISettings *settings_ = nullptr;
  std::string current_dir_;
  std::string project_root_dir_;
  std::string project_settings_path_;
  std::string project_cache_dir_;
  std::string project_logs_dir_;
  std::string project_tmp_dir_;
  std::string chromium_process_path_;
  std::string project_model_parts_dir_;
  std::string project_model_dir_;
  std::string chromium_user_data_dir_;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
  std::map<std::string, std::string> chromium_startup_process_;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 30 May 2025 03:32:51 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__ACA1E418_2B6E_4539_A80F_D74605B0FD7D__