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

#include "error.hpp"
#include "settings.hpp"
#include "configure.hpp"
using namespace chromium;
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
  std::string GetChromiumProcess(const std::string &version = "") const;

public:
  ISettings *settings_ = nullptr;
  std::string current_dir_;
  std::string configures_dir_;
  std::string configure_path_;
  std::string settings_path_;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
  std::map<std::string, std::string> chromium_startup_process_;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 30 May 2025 03:32:51 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__ACA1E418_2B6E_4539_A80F_D74605B0FD7D__