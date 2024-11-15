#include "config.h"

Config::Config() {
  Init();
}

Config::~Config() {
  UnInit();
}

void Config::Init() {
  do {
    current_process_path_.clear();
    char *path = nullptr;
    size_t path_size = 0;
    xs_sys_process_getpath(&path, &path_size);
    current_process_path_.append(path, path_size);
    xs_sys_free((void **)&path);
    current_process_path_ = stl::Path::PathnameToPath(current_process_path_);

    chromium_path_ = current_process_path_ + "/chromium/";
  } while (0);

  do {
    work_projects_path_.clear();
    char *appdata = nullptr;
    size_t appdata_path_len = 0;
    xs_sys_get_appdata_path(&appdata, &appdata_path_len);
    work_projects_path_.append(appdata, appdata_path_len);
    xs_sys_free((void **)&appdata);
    work_projects_path_.append("/WorkProjects");
  } while (0);
}

void Config::UnInit() {
}
const std::string &Config::CurrentProcessPath() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return current_process_path_;
}
const std::string &Config::WorkProjectsPath() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return work_projects_path_;
}
void Config::ConfigureSet(const std::string &input_json) {
  std::lock_guard<std::mutex> lock{*mtx_};
  configure_ << input_json;
}
const Configure &Config::ConfigureGet() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return configure_;
}
const std::string &Config::ChromiumPath() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return chromium_path_;
}
unsigned int Config::GetClientLocalPort() const {
  unsigned int result = 0;
  std::lock_guard<std::mutex> lock{*mtx_};
  do {
#if ENABLE_DEVELOPER_DEBUG
    std::string path =
        R"(C:\Users\k34ub\AppData\Roaming\MarsProjects\route.json)";
#else
    std::string path = current_process_path_ + "/route.json";
#endif
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
////////////////////////////////////////////////////////////////////////////
static Config *__gpConfig = nullptr;
Config *Config::ConfigGet() {
  if (!__gpConfig)
    __gpConfig = new Config();
  return __gpConfig;
}
