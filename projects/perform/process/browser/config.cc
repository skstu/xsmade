#include "perform.h"

BrowserConfig::BrowserConfig() {
  Init();
}

BrowserConfig::~BrowserConfig() {
  UnInit();
}
void BrowserConfig::Init() {
  PathsInit();
  SettingsInit();
  LOG_INIT(paths_.logs_dir + u"/perform.log");
  char *proc_path;
  size_t proc_path_len = 0;
  xs_sys_process_getpath(&proc_path, &proc_path_len);
  LOG_INFO("{}", std::string(proc_path, proc_path_len));
}

void BrowserConfig::UnInit() {
  LOG_UNINIT;
}
void BrowserConfig::RouteConfigureInit(const unsigned int &server_port) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  do {
    const std::u16string route_path = paths_.brw_projects_route_file;

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
std::u16string
BrowserConfig::GetBrwUserDataDir(const std::u16string &brwKey) const {
  std::u16string result;
  std::lock_guard<std::mutex> lock{*mtx_};
  auto u8 =
      fmt::format(R"({}/{}/)", Utfpp::u16_to_u8(paths_.chromium_user_data_dir),
                  Utfpp::u16_to_u8(brwKey));
  result = Utfpp::u8_to_u16(u8);
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
std::u16string
BrowserConfig::GetXSCacheExtsDir(const std::u16string &brwKey,
                                 const std::u16string &extId) const {
  std::u16string result;
  std::lock_guard<std::mutex> lock{*mtx_};
  auto u8 = fmt::format(R"({}/{}/Default/XSCache/exts/{}/)",
                        Utfpp::u16_to_u8(paths_.chromium_user_data_dir),
                        Utfpp::u16_to_u8(brwKey), Utfpp::u16_to_u8(extId));
  result = Utfpp::u8_to_u16(u8);
  stl::Directory::Create(result);
  return result;
}
std::u16string
BrowserConfig::GetXSCacheRouteReqsDir(const std::u16string &brwKey) const {
  std::u16string result;
  std::lock_guard<std::mutex> lock{*mtx_};
  auto u8result = fmt::format(R"({}/{}/Default/XSCache/route/reqs/)",
                              Utfpp::u16_to_u8(paths_.chromium_user_data_dir),
                              Utfpp::u16_to_u8(brwKey));
  result = Utfpp::u8_to_u16(u8result);
  stl::Directory::Create(result);
  return result;
}
std::u16string
BrowserConfig::GetXSCacheRouteRepsDir(const std::u16string &brwKey) const {
  std::u16string result;
  std::lock_guard<std::mutex> lock{*mtx_};
  auto u8result = fmt::format(R"({}/{}/Default/XSCache/route/reps/)",
                              Utfpp::u16_to_u8(paths_.chromium_user_data_dir),
                              Utfpp::u16_to_u8(brwKey));
  result = Utfpp::u8_to_u16(u8result);
  stl::Directory::Create(result);
  return result;
}
std::u16string
BrowserConfig::GetXSCacheConfigureFName(const std::u16string &brwKey) const {
  std::u16string result;
  std::lock_guard<std::mutex> lock{*mtx_};
  auto u8result = fmt::format(R"({}/{}/Default/XSCache/cfgs/configure.json)",
                              Utfpp::u16_to_u8(paths_.chromium_user_data_dir),
                              Utfpp::u16_to_u8(brwKey));
  result = Utfpp::u8_to_u16(u8result);
  stl::Directory::Create(stl::Path::PathnameToPath(result));
  return result;
}
std::u16string
BrowserConfig::GetXSCacheExtsDir(const std::u16string &brwKey) const {
  std::u16string result;
  std::lock_guard<std::mutex> lock{*mtx_};
  auto u8result = fmt::format(R"({}/{}/Default/XSCache/exts/)",
                              Utfpp::u16_to_u8(paths_.chromium_user_data_dir),
                              Utfpp::u16_to_u8(brwKey));
  result = Utfpp::u8_to_u16(u8result);
  stl::Directory::Create(result);
  return result;
}
std::u16string
BrowserConfig::GetXSCacheCfgsDir(const std::u16string &brwKey) const {
  std::u16string result;
  std::lock_guard<std::mutex> lock{*mtx_};
  auto u8result = fmt::format(R"({}/{}/Default/XSCache/cfgs/)",
                              Utfpp::u16_to_u8(paths_.chromium_user_data_dir),
                              Utfpp::u16_to_u8(brwKey));
  result = Utfpp::u8_to_u16(u8result);
  stl::Directory::Create(result);
  return result;
}
std::u16string
BrowserConfig::GetXSCacheStatisDir(const std::u16string &brwKey) const {
  std::u16string result;
  std::lock_guard<std::mutex> lock{*mtx_};
  auto u8result = fmt::format(R"({}/{}/Default/XSCache/statis/)",
                              Utfpp::u16_to_u8(paths_.chromium_user_data_dir),
                              Utfpp::u16_to_u8(brwKey));
  result = Utfpp::u8_to_u16(u8result);
  stl::Directory::Create(result);
  return result;
}
void BrowserConfig::XSCacheClean(const std::u16string &brwKey) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (!brwKey.empty()) {
    std::u16string path = stl::Path::Normalize(
        paths_.chromium_user_data_dir + u"/" + brwKey + u"/Default/XSCache/");
    stl::Directory::RemoveAllU16(path);
  }
}
unsigned int BrowserConfig::RouteConfigureGetClientPort() const {
  unsigned int result = 0;
  std::lock_guard<std::mutex> lock{*mtx_};
  do {
    std::u16string path = paths_.brw_projects_route_file;
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
std::string
BrowserConfig::CreateBrwCloseNotifyPak(const std::u16string &brwKey) {
  std::string result = fmt::format(R"("key":"{}")", Utfpp::u16_to_u8(brwKey));
  result.insert(0, "{");
  result.append("}");
  return result;
}
const BrowserConfig::Settings &BrowserConfig::GetSettings() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return settings_;
}
const BrowserConfig::Paths &BrowserConfig::PathGet() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return paths_;
}
void BrowserConfig::PathsInit() {
  do {
    char *path = nullptr;
    size_t path_size = 0;
    xs_sys_get_appdata_path(&path, &path_size);
    paths_.root_dir =
        stl::Path::Normalize(Utfpp::u8_to_u16(std::string(path, path_size)));
    xs_sys_free((void **)&path);
    paths_.root_dir.append(u"/").append(project_name_).append(u"/");
    paths_.root_dir = stl::Path::Normalize(paths_.root_dir);
    paths_.logs_dir = paths_.root_dir + u"/logs/";
    paths_.brw_projects_route_file = paths_.root_dir + u"/route.json";
    paths_.brw_projects_configure_file = paths_.root_dir + u"/configure.json";
    paths_.chromium_dir = paths_.root_dir + u"/chromium/";
    paths_.chromium_user_data_dir = paths_.root_dir + u"/userdata/";
    paths_.chromium_extensions_dir = paths_.root_dir + u"/exetnsions/";
    paths_.configure_dir = paths_.root_dir + u"/configure/";
    paths_.plugins_dir = paths_.root_dir + u"/plugins/";
    paths_.components_dir = paths_.root_dir + u"/components/";
    paths_.resources_dir = paths_.root_dir + u"/resources/";

    stl::Directory::Create(paths_.root_dir);
    stl::Directory::Create(paths_.configure_dir);
    stl::Directory::Create(paths_.resources_dir);
    stl::Directory::Create(paths_.plugins_dir);
    stl::Directory::Create(paths_.components_dir);
    stl::Directory::Create(paths_.logs_dir);
    stl::Directory::Create(paths_.chromium_dir);
    stl::Directory::Create(paths_.chromium_user_data_dir);
    stl::Directory::Create(paths_.chromium_extensions_dir);
  } while (0);
}
////////////////////////////////////////////////////////////////////////////
BrowserConfig::Settings::Settings() {
}
BrowserConfig::Settings::~Settings() {
}
void BrowserConfig::SettingsInit() {
  do {
    std::string settings_buffer =
        stl::File::ReadFile(paths_.configure_dir + u"/settings.xml");
    if (settings_buffer.empty())
      break;
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError xmlErr =
        doc.Parse(settings_buffer.c_str(), settings_buffer.size());
    if (xmlErr != tinyxml2::XML_SUCCESS)
      break;

    tinyxml2::XMLNode *node_settings = doc.FirstChildElement("settings");
    if (!node_settings)
      break;
    auto node_settings_attr = node_settings->ToElement()->FirstAttribute();
    while (node_settings_attr) {
      if (strcmp("enable_logger", node_settings_attr->Name())) {
        node_settings_attr->QueryBoolValue(&settings_.enable_logger);
      }
      node_settings_attr = node_settings_attr->Next();
    }
    auto first_node = node_settings->FirstChild();
    while (first_node) { //!@ developer
      if (auto element = first_node->ToElement()) {
        if (!strcmp("developer", element->Value())) {
          auto attr = element->FirstAttribute();
          while (attr) {
            if (!strcmp("enable", attr->Name())) {
              attr->QueryBoolValue(&settings_.developer.enable);
            }
            attr = attr->Next();
          }
          auto node = element->FirstChild();
          while (node) {

            node = node->NextSibling();
          }
          break;
        }
      } else if (auto text = first_node->ToText()) {
      } else if (auto comment = first_node->ToComment()) {
      }
      first_node = first_node->NextSibling();
    }
    first_node = node_settings->FirstChild();
    while (first_node) { //!@ plugins
      if (auto element = first_node->ToElement()) {
        if (!strcmp("components", element->Value())) {

          break;
        }
      } else if (auto text = first_node->ToText()) {
      } else if (auto comment = first_node->ToComment()) {
      }
      first_node = first_node->NextSibling();
    }
    first_node = node_settings->FirstChild();
    while (first_node) { //!@ components
      if (auto element = first_node->ToElement()) {
        if (!strcmp("plugins", element->Value())) {
          auto att = element->FirstAttribute();
          while (att) {
            if (!strcmp("vvv", att->Name())) {

              auto value = att->Value();
              auto ssssss = 0;
            }
            att = att->Next();
          }

          auto node = element->FirstChild();
          while (node) {

            node = node->NextSibling();
          }
          break;
        }
      } else if (auto text = first_node->ToText()) {
      } else if (auto comment = first_node->ToComment()) {
      }
      first_node = first_node->NextSibling();
    }
    auto xx = 0;
  } while (0);

#if defined(DEBUG)
  settings_.developer.enable = true;
#endif
}
