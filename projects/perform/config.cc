#include "config.h"

Config::Config() {
  Init();
}

Config::~Config() {
  UnInit();
}
void Config::Init() {
  PathsInit();
  LOG_INIT(paths_.logs_dir + "perform.log");
}

void Config::UnInit() {
  LOG_UNINIT;
}
void Config::RouteConfigureInit(const unsigned int &server_port) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  do {
    const std::string route_path = paths_.brw_projects_route_file;

    rapidjson::Document doc;
    std::string route_buffer = stl::File::ReadFile(route_path);
    if (doc.Parse(route_buffer.data(), route_buffer.size()).HasParseError()) {
      stl::File::Remove(route_path);
      stl::File::Create(route_path);
      stl::File::WriteFile(route_path, "{}");
      doc.Parse("{}");
    }
    if (doc.HasMember("server_port"))
      doc.RemoveMember("server_port");
    if (!doc.HasMember("client_port")) {
      doc.AddMember(rapidjson::Value()
                        .SetString("client_port", doc.GetAllocator())
                        .Move(),
                    rapidjson::Value().SetUint(0).Move(), doc.GetAllocator());
    }
    doc.AddMember(
        rapidjson::Value().SetString("server_port", doc.GetAllocator()).Move(),
        rapidjson::Value().SetUint(server_port).Move(), doc.GetAllocator());

    stl::File::WriteFile(route_path, Json::toString(doc));
  } while (0);
}
std::string Config::GetBrwUserDataDir(const std::string &brwKey) const {
  std::string result;
  std::lock_guard<std::mutex> lock{*mtx_};
  result = fmt::format(R"({}/{}/)", paths_.chromium_user_data_dir, brwKey);
  return result;
}
/*
    std::string
        chromium_xscache_configure_dir; //
   "/userdata/cache/${key}/Default/xscache/cfgs/" std::string
        chromium_xscache_extensions_dir; //
   "/userdata/cache/${key}/Default/xscache/exts/" std::string
        chromium_xscache_statistics_dir; //
   "/userdata/cache/${key}/Default/xscache/statis/"
*/
std::string Config::GetXSCacheExtsDir(const std::string &brwKey,
                                      const std::string &extId) const {
  std::string result;
  std::lock_guard<std::mutex> lock{*mtx_};
  result = fmt::format(R"({}/{}/Default/XSCache/exts/{}/)",
                       paths_.chromium_user_data_dir, brwKey, extId);
  stl::Directory::Create(result);
  return result;
}
std::string Config::GetXSCacheConfigureFName(const std::string &brwKey) const {
  std::string result;
  std::lock_guard<std::mutex> lock{*mtx_};
  result = fmt::format(R"({}/{}/Default/XSCache/cfgs/configure.json)",
                       paths_.chromium_user_data_dir, brwKey);
  stl::Directory::Create(stl::Path::PathnameToPath(result));
  return result;
}
std::string Config::GetXSCacheExtsDir(const std::string &brwKey) const {
  std::string result;
  std::lock_guard<std::mutex> lock{*mtx_};
  result = fmt::format(R"({}/{}/Default/XSCache/exts/)",
                       paths_.chromium_user_data_dir, brwKey);
  stl::Directory::Create(result);
  return result;
}
std::string Config::GetXSCacheCfgsDir(const std::string &brwKey) const {
  std::string result;
  std::lock_guard<std::mutex> lock{*mtx_};
  result = fmt::format(R"({}/{}/Default/XSCache/cfgs/)",
                       paths_.chromium_user_data_dir, brwKey);
  stl::Directory::Create(result);
  return result;
}
std::string Config::GetXSCacheStatisDir(const std::string &brwKey) const {
  std::string result;
  std::lock_guard<std::mutex> lock{*mtx_};
  result = fmt::format(R"({}/{}/Default/XSCache/statis/)",
                       paths_.chromium_user_data_dir, brwKey);
  stl::Directory::Create(result);
  return result;
}
void Config::XSCacheClean(const std::string &brwKey) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (!brwKey.empty()) {
    std::string xscache_dir = fmt::format(
        R"({}/{}/Default/XSCache/)", paths_.chromium_user_data_dir, brwKey);
    stl::Directory::RemoveAllU8(xscache_dir);
  }
}
unsigned int Config::RouteConfigureGetClientPort() const {
  unsigned int result = 0;
  std::lock_guard<std::mutex> lock{*mtx_};
  do {
    std::string path = paths_.brw_projects_route_file;
    if (!stl::File::Exists(path))
      break;
    std::string route_buffer = stl::File::ReadFile(path);
    if (route_buffer.empty())
      break;
    rapidjson::Document doc;
    if (doc.Parse(route_buffer.data(), route_buffer.size()).HasParseError())
      break;
    if (!doc.IsObject())
      break;
    if (!doc.HasMember("client_port") && !doc["client_port"].IsUint())
      break;
    result = doc["client_port"].GetUint();
  } while (0);
  return result;
}
std::string Config::CreateBrwCloseNotifyPak(const std::string &brwKey) {
  std::string result = fmt::format(R"("key":"{}")", brwKey);
  result.insert(0, "{");
  result.append("}");
  return result;
}
const Config::Paths &Config::PathGet() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return paths_;
}
void Config::PathsInit() {
  do {
    char *path = nullptr;
    size_t path_size = 0;
    xs_sys_get_appdata_path(&path, &path_size);
    paths_.root_dir = std::string(path, path_size);
    paths_.root_dir.append(fmt::format(R"(/{}/)", project_name_));
    xs_sys_free((void **)&path);
#if 0
    xs_sys_process_getpath(&path, &path_size);
    paths_.root_dir = stl::Path::PathnameToPath(std::string(path, path_size));
    xs_sys_free((void **)&path);
#endif
    paths_.logs_dir = paths_.root_dir + "/logs/";
    paths_.brw_projects_route_file = paths_.root_dir + "/route.json";
    paths_.brw_projects_configure_file = paths_.root_dir + "/configure.json";
    paths_.chromium_dir = paths_.root_dir + "/chromium/";
    paths_.chromium_user_data_dir = paths_.root_dir + "/userdata/";
    paths_.chromium_extensions_dir = paths_.root_dir + "/exetnsions/";

    stl::Directory::Create(paths_.root_dir);
    stl::Directory::Create(paths_.logs_dir);
    stl::Directory::Create(paths_.chromium_dir);
    stl::Directory::Create(paths_.chromium_extensions_dir);
  } while (0);
}
////////////////////////////////////////////////////////////////////////////
static Config *__gpConfig = nullptr;
Config *Config::ConfigGet() {
  if (!__gpConfig)
    __gpConfig = new Config();
  return __gpConfig;
}
void Config::Destroy() {
  if (__gpConfig)
    delete __gpConfig;
  __gpConfig = nullptr;
}