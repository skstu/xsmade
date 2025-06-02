#include <perform.h>

#if defined(__OSWIN__)
#include <winsock2.h>
#include <iphlpapi.h>
#pragma comment(lib, "IPHLPAPI.lib")
#endif

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
  GetIPAddr();
  GetLocalIPAddr();
  GetLocalMachineAllNetWorkCardMAC(macs_);
  LOG_INFO("{}", std::string(proc_path, proc_path_len));
  auto xx = 0;
}

void BrowserConfig::UnInit() {
  LOG_UNINIT;
}
void BrowserConfig::RouteConfigureInit(const unsigned int &server_port) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  do {
    const std::u16string route_path = paths_.brw_projects_route_file;
#if 0
    std::string data;
    data.append(R"({"server_port":)").append(std::to_string(server_port)).append(R"(})");
#endif
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
      fmt::format(R"({}/{}/)", Conv::u16_to_u8(paths_.chromium_user_data_dir),
                  Conv::u16_to_u8(brwKey));
  result = Conv::u8_to_u16(u8);
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
                        Conv::u16_to_u8(paths_.chromium_user_data_dir),
                        Conv::u16_to_u8(brwKey), Conv::u16_to_u8(extId));
  result = Conv::u8_to_u16(u8);
  stl::Directory::Create(result);
  return result;
}
std::u16string
BrowserConfig::GetXSCacheRouteReqsDir(const std::u16string &brwKey) const {
  std::u16string result;
  std::lock_guard<std::mutex> lock{*mtx_};
  auto u8result = fmt::format(R"({}/{}/Default/XSCache/route/reqs/)",
                              Conv::u16_to_u8(paths_.chromium_user_data_dir),
                              Conv::u16_to_u8(brwKey));
  result = Conv::u8_to_u16(u8result);
  stl::Directory::Create(result);
  return result;
}
std::u16string
BrowserConfig::GetXSCacheRouteRepsDir(const std::u16string &brwKey) const {
  std::u16string result;
  std::lock_guard<std::mutex> lock{*mtx_};
  auto u8result = fmt::format(R"({}/{}/Default/XSCache/route/reps/)",
                              Conv::u16_to_u8(paths_.chromium_user_data_dir),
                              Conv::u16_to_u8(brwKey));
  result = Conv::u8_to_u16(u8result);
  stl::Directory::Create(result);
  return result;
}
std::u16string
BrowserConfig::GetXSCacheConfigureFName(const std::u16string &brwKey) const {
  std::u16string result;
  std::lock_guard<std::mutex> lock{*mtx_};
  auto u8result = fmt::format(R"({}/{}/Default/XSCache/cfgs/configure.json)",
                              Conv::u16_to_u8(paths_.chromium_user_data_dir),
                              Conv::u16_to_u8(brwKey));
  result = Conv::u8_to_u16(u8result);
  stl::Directory::Create(stl::Path::PathnameToPath(result));
  return result;
}
std::u16string
BrowserConfig::GetXSCacheExtsDir(const std::u16string &brwKey) const {
  std::u16string result;
  std::lock_guard<std::mutex> lock{*mtx_};
  auto u8result = fmt::format(R"({}/{}/Default/XSCache/exts/)",
                              Conv::u16_to_u8(paths_.chromium_user_data_dir),
                              Conv::u16_to_u8(brwKey));
  result = Conv::u8_to_u16(u8result);
  stl::Directory::Create(result);
  return result;
}
std::u16string
BrowserConfig::GetXSCacheCfgsDir(const std::u16string &brwKey) const {
  std::u16string result;
  std::lock_guard<std::mutex> lock{*mtx_};
  auto u8result = fmt::format(R"({}/{}/Default/XSCache/cfgs/)",
                              Conv::u16_to_u8(paths_.chromium_user_data_dir),
                              Conv::u16_to_u8(brwKey));
  result = Conv::u8_to_u16(u8result);
  stl::Directory::Create(result);
  return result;
}
std::u16string
BrowserConfig::GetXSCacheStatisDir(const std::u16string &brwKey) const {
  std::u16string result;
  std::lock_guard<std::mutex> lock{*mtx_};
  auto u8result = fmt::format(R"({}/{}/Default/XSCache/statis/)",
                              Conv::u16_to_u8(paths_.chromium_user_data_dir),
                              Conv::u16_to_u8(brwKey));
  result = Conv::u8_to_u16(u8result);
  stl::Directory::Create(result);
  return result;
}
void BrowserConfig::XSCacheClean(const std::u16string &brwKey) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (!brwKey.empty()) {
    std::u16string path =
        paths_.chromium_user_data_dir + u"/" + brwKey + u"/Default/XSCache/";
    stl::Directory::RemoveAll(path);
  }
}
unsigned int BrowserConfig::RouteConfigureGetClientPort() {
  unsigned int result = 0;
  std::lock_guard<std::mutex> lock{*mtx_};
  do {
    std::u16string path = paths_.brw_projects_route2_file;
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
#if DEBUG
    result = 65534;
#else
    result = doc["client_port"].GetUint();
#endif
    client_port_cache_.store(result);
  } while (0);
  return result;
}

bool BrowserConfig::IsDevMode() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return settings_.developer.enable;
}
unsigned int BrowserConfig::GetClientPortCache() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return client_port_cache_.load();
}
std::string
BrowserConfig::CreateBrwCloseNotifyPak(const std::u16string &brwKey) {
  std::string result;
  rapidjson::Document doc;
  doc.SetObject();
  doc.AddMember(
      rapidjson::Value().SetString("key", doc.GetAllocator()).Move(),
      rapidjson::Value()
          .SetString(Conv::u16_to_u8(brwKey).c_str(), doc.GetAllocator())
          .Move(),
      doc.GetAllocator());
  doc.AddMember(
      rapidjson::Value().SetString("data_time_ms", doc.GetAllocator()).Move(),
      rapidjson::Value()
          .SetUint64(stl::Time::TimeStamp<std::chrono::milliseconds>())
          .Move(),
      doc.GetAllocator());
  result = Json::toString(doc);
  return result;
}
std::string
BrowserConfig::CreateBrwCookiesNotifyPak(const std::u16string &brwKey,
                                         const std::string &cookies) {
  std::string result;
  do {
    rapidjson::Document doc;
    if (doc.Parse(cookies.data(), cookies.size()).HasParseError())
      break;
    if (!doc.IsObject())
      break;
    if (doc.HasMember("key"))
      doc.RemoveMember("key");
    doc.AddMember(
        rapidjson::Value().SetString("key", doc.GetAllocator()).Move(),
        rapidjson::Value()
            .SetString(Conv::u16_to_u8(brwKey).c_str(), doc.GetAllocator())
            .Move(),
        doc.GetAllocator());
    doc.AddMember(
        rapidjson::Value().SetString("data_time_ms", doc.GetAllocator()).Move(),
        rapidjson::Value()
            .SetUint64(stl::Time::TimeStamp<std::chrono::milliseconds>())
            .Move(),
        doc.GetAllocator());
    result = Json::toString(doc);
  } while (0);
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
#if 0
    char *path = nullptr;
    size_t path_size = 0;
    xs_sys_get_appdata_path(&path, &path_size);
    paths_.root_dir =
        stl::Path::Normalize(Conv::u8_to_u16(std::string(path, path_size)));
xs_sys_free((void **)&path);
#endif

#if 0 //!@ v1
    paths_.root_dir = System::GetCurrentProcessPathU16();
    //paths_.root_dir.append(u"/").append(project_name_).append(u"/");
    paths_.root_dir = stl::Path::Normalize(paths_.root_dir);
    paths_.logs_dir = paths_.root_dir + u"/logs/";
    paths_.brw_projects_route_file = paths_.root_dir + u"/route.json";
    paths_.brw_projects_configure_file = paths_.root_dir + u"/configure.json";
    paths_.chromium_dir = paths_.root_dir + u"/chromium/";
    paths_.chromium_user_data_dir = paths_.root_dir + u"/userdata/";
    paths_.chromium_extensions_dir = paths_.root_dir + u"/extensions/";
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
#else //!@ v2 配置计划目录
    char *path_appdata = nullptr;
    size_t path_appdata_len = 0;
    xs_sys_get_appdata_path(&path_appdata, &path_appdata_len);
    std::u16string u16appdatapath =
        Conv::u8_to_u16(std::string(path_appdata, path_appdata_len));
    xs_sys_free((void **)&path_appdata);

    char *path = nullptr;
    size_t path_len = 0;
    xs_sys_process_getpath(&path, &path_len);
    paths_.root_dir = Conv::u8_to_u16(std::string(path, path_len));
    xs_sys_free((void **)&path);
    paths_.root_dir = paths_.root_dir;
    paths_.logs_dir = paths_.root_dir + u"/logs";
    paths_.configure_dir = paths_.root_dir + u"/configure";
    paths_.plugins_dir = paths_.root_dir + u"/plugins";
    paths_.components_dir = paths_.root_dir + u"/components";
    paths_.resources_dir = paths_.root_dir + u"/resources/";
    paths_.brw_projects_route_file = paths_.configure_dir + u"/route.json";
    paths_.brw_projects_route2_file =
        paths_.configure_dir + u"/clientInfo.json";
    paths_.brw_projects_configure_file =
        paths_.configure_dir + u"/configure.json";
    paths_.chromium_dir = paths_.root_dir + u"/ext/browser/Chromium";
    paths_.firefox_dir = paths_.root_dir + u"/ext/browser/Firefox";
#if 0
    paths_.chromium_user_data_dir = paths_.root_dir + u"/data/brwcaches";
#else
    paths_.chromium_user_data_dir = u16appdatapath + u"/Chromium/";
#endif
    paths_.chromium_extensions_dir = paths_.plugins_dir + u"/brwexts";
#endif
    stl::Directory::Create(paths_.logs_dir);
    stl::Directory::Create(paths_.configure_dir);
    stl::Directory::Create(paths_.chromium_dir);
    stl::Directory::Create(paths_.firefox_dir);
    stl::Directory::Create(paths_.components_dir);
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
const std::set<std::string> &BrowserConfig::GetMACs() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return macs_;
}
std::string BrowserConfig::GetLocalIPAddr(const bool &rereq) {
  std::string result;
  std::lock_guard<std::mutex> lock{*mtx_};
  do {
    if (!ipaddr_local_.empty() && !rereq) {
      result = ipaddr_local_;
      break;
    }
    char *ret;
    char host_name[256] = "";
    WSADATA wsaData;
    WSAStartup(0x101, &wsaData);
    if (gethostname(host_name, 256))
      break;
    ret = inet_ntoa(*((struct in_addr *)gethostbyname(host_name)->h_addr));
    if (!ret)
      break;
    result = ret;
    ipaddr_local_ = result;
    // WSACleanup();
  } while (0);
  return result;
}
std::string BrowserConfig::GetIPAddr(const bool &rereq) {
  std::string result;
  std::lock_guard<std::mutex> lock{*mtx_};
  do {
    if (!ipaddr_.empty() && !rereq) {
      result = ipaddr_;
      break;
    }
    httplib::Client cli("http://api.ipify.org");
    auto res = cli.Get("/");
    if (!res || res->status != httplib::StatusCode::OK_200) {
      httplib::Client cli2("http://www.3322.org");
      res = cli2.Get("/dyndns/getip");
      if (!res || res->status != httplib::StatusCode::OK_200)
        break;
    }
    result = res->body;
    for (auto it = result.begin(); it != result.end(); ++it) {
      if (*it < '0' || *it > '9') {
        if (*it != '.') {
          *it = 0;
          break;
        }
      }
    }
    ipaddr_ = result;
  } while (0);
  return result;
}
std::string BrowserConfig::GetLocalMachineAllNetWorkCardMAC(
    std::set<std::string> &macs, const char &space, const bool &lower) const {
  std::string resultMacStr = "FFFFFFFFFFFF";
  macs.insert(resultMacStr);
#if defined(__OSWIN__)
  macs.clear();
  resultMacStr.clear();
  IP_ADAPTER_INFO *oldptr = nullptr;
  IP_ADAPTER_INFO *pIPAdapterInfo = new IP_ADAPTER_INFO;
  ULONG nIPAdapterInfo = static_cast<ULONG>(sizeof(IP_ADAPTER_INFO));
  ULONG result = ::GetAdaptersInfo(pIPAdapterInfo, &nIPAdapterInfo);
  if (ERROR_BUFFER_OVERFLOW == result) {
    SK_DELETE_PTR(pIPAdapterInfo);
    pIPAdapterInfo = (PIP_ADAPTER_INFO) new std::uint8_t[nIPAdapterInfo];
    result = ::GetAdaptersInfo(pIPAdapterInfo, &nIPAdapterInfo);
  }
  oldptr = pIPAdapterInfo;
  if (ERROR_SUCCESS == result) {
    do {
      if (!pIPAdapterInfo)
        break;
      std::string mac;
      for (decltype(pIPAdapterInfo->AddressLength) i = 0;
           i < __min(MAX_ADAPTER_ADDRESS_LENGTH, pIPAdapterInfo->AddressLength);
           ++i) {
        char szTemp[5] = {0};
        if (lower)
          sprintf_s(szTemp, _countof(szTemp), "%02x",
                    pIPAdapterInfo->Address[i]);
        else
          sprintf_s(szTemp, _countof(szTemp), "%02X",
                    pIPAdapterInfo->Address[i]);
        mac.append(szTemp);
        if (space)
          mac.append(sizeof(char), space);
      }
      if (!mac.empty()) {
        if (space)
          mac.pop_back();
        macs.insert(mac);
      }
      pIPAdapterInfo = pIPAdapterInfo->Next;
    } while (1);
  }
  SK_DELETE_PTR(oldptr);
  for (const auto &mac : macs)
    resultMacStr.append(mac).append(",");
  if (!resultMacStr.empty())
    resultMacStr.pop_back();
#endif
  return resultMacStr;
}

bool BrowserConfig::GetWindowsAccountInfo(std::wstring &Usersid,
                                          std::wstring &ComputerName,
                                          std::wstring &UserName,
                                          const bool &full_sid) const {
  bool result = false;
#if defined(__OSWIN__)
  Usersid.clear();
  ComputerName.resize(MAX_PATH, 0x00);
  DWORD lenComputerName = ComputerName.size();
  UserName.resize(MAX_PATH, 0x00);
  DWORD lenUserName = UserName.size();
  wchar_t UserSid[_MAX_PATH] = {0};
  DWORD dwUserSid = _MAX_PATH;
  do {
    if (FALSE == ::GetUserNameW(&ComputerName[0], &lenComputerName))
      break;
    ComputerName.resize(lenComputerName);
    SID_NAME_USE SidNameUser;
    if (FALSE == ::LookupAccountNameW(nullptr, ComputerName.c_str(), UserSid,
                                      &dwUserSid, &UserName[0], &lenUserName,
                                      &SidNameUser))
      break;
    UserName.resize(lenUserName);
    PSID_IDENTIFIER_AUTHORITY pSID_IDENTIFIER_AUTHORITY =
        ::GetSidIdentifierAuthority(UserSid);
    if (!pSID_IDENTIFIER_AUTHORITY)
      break;
    wchar_t tmp[256] = {0};
    wsprintfW(tmp, L"S-%d-%d", SID_REVISION,
              pSID_IDENTIFIER_AUTHORITY->Value[5]);
    Usersid = tmp;
    auto pGetSidSubAuthorityCount = ::GetSidSubAuthorityCount(UserSid);
    if (!pGetSidSubAuthorityCount)
      break;
    const int SidSubAuthorityCount = *pGetSidSubAuthorityCount;
    if (full_sid ? (SidSubAuthorityCount <= 0) : (SidSubAuthorityCount <= 1))
      break;
    for (int i = 0; i < SidSubAuthorityCount - (full_sid ? 0 : 1); ++i) {
      auto pGetSidSubAuthority = ::GetSidSubAuthority(UserSid, i);
      if (!pGetSidSubAuthority)
        break;
      wchar_t tmp[64] = {0};
      wsprintfW(tmp, L"%lu", *pGetSidSubAuthority);
      Usersid.append(L"-").append(tmp);
    }
    result = !Usersid.empty();
  } while (0);
#endif
  return result;
}