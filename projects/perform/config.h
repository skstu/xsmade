#if !defined(__918F8A06_5054_4610_918C_97CFBD43D91B__)
#define __918F8A06_5054_4610_918C_97CFBD43D91B__

#define ENABLE_DEVELOPER_DEBUG 1
#include <stl.hpp>
#include <system.h>
#include <httplib.h>
#include <rapidjson.h>
#include <fmt/format.h>

#include "server.h"
#include "perform.h"
#include "configure.h"

class Config {
public:
  static Config *ConfigGet();

public:
  Config();
  ~Config();

private:
  void Init();
  void UnInit();

public:
  const std::string &CurrentProcessPath() const;
  const std::string &WorkProjectsPath() const;
  void ConfigureSet(const std::string &input_json);
  const Configure &ConfigureGet() const;
  const std::string &ChromiumPath() const;
  unsigned int GetClientLocalPort() const;

public:
  static std::string CreateBrwCloseNotifyPak(const std::string &brwId);

private:
  Configure configure_;
  std::string current_process_path_;
  std::string work_projects_path_;
  std::string chromium_path_;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};

/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 11 Nov 2024 09:56:50 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__918F8A06_5054_4610_918C_97CFBD43D91B__