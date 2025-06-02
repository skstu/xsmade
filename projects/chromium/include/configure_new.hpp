#if !defined(__F6058B7C_FA8D_4C9D_A424_6B2548FF1F7E__)
#define __F6058B7C_FA8D_4C9D_A424_6B2548FF1F7E__

#include "rapidjson.h"

namespace chromium {
constexpr char project_dirname_chromium[] = "Chromium";
constexpr char project_dirname_default_user_data[] = "default";
constexpr char project_dirname_extensions[] = "extensions";
constexpr char project_dirname_route[] = "route";
constexpr char project_dirname_tmp[] = "tmp";
constexpr char project_dirname_cache[] = "cache";
constexpr char project_dirname_configures[] = "configures";
constexpr char project_filename_configure[] = "configure.json";
constexpr char project_filename_tmpcfgpath[] = "cfgpath.cfg";
namespace { //!@ class Chromium Configure
class Chromium final {
public:
  class StartupArgs final {
  public:
    class Source final {
    public:
      inline Source();
      inline ~Source();
      inline Source(const Source &obj);
      inline void operator=(const Source &obj);
      inline void operator<<(const std::string &);
      inline void FixKey();
      std::string key;
      std::string value;
    };

  public:
    inline StartupArgs();
    inline ~StartupArgs();
    inline StartupArgs(const StartupArgs &obj);
    inline void operator=(const StartupArgs &obj);
    inline bool operator<<(const rapidjson::Value &);
    bool enable = false;
    std::vector<Source> sources;
  };
  class Proxy final {
    enum class SocksType : unsigned char {
      Default = 0,
      SocksH = 1,
      SocksA = 2,
    };
    enum class Type : unsigned long {
      HTTP = 0,
      HTTPS = 1,
      SOCKS4 = 2,
      SOCKS5 = 3,
    };

  public:
    inline Proxy();
    inline ~Proxy();
    inline Proxy(const Proxy &obj);
    inline void operator=(const Proxy &obj);
    inline bool operator<<(const rapidjson::Value &);
    inline bool Parse();
    Type type = Type::HTTP;
    SocksType socks_type = SocksType::Default;
    std::string host;
    unsigned short port = 80;
    std::string username;
    std::string password;
    std::string address;
    std::string source;
    bool enable = false;
  };
  class Extensions final {
  public:
    inline Extensions();
    inline ~Extensions();
    inline Extensions(const Extensions &obj);
    inline void operator=(const Extensions &obj);
    inline bool operator<<(const rapidjson::Value &);
    inline bool IsAllowlisted(const std::string &extid) const;

  public:
    bool enable = false;
    std::set<std::string> allowlist;
  };
  class Fingerprint final {
  public:
    class Screen final {
    public:
      inline Screen();
      inline Screen(const Screen &);
      inline ~Screen();
      inline void operator=(const Screen &);
      inline bool operator<<(const rapidjson::Value &);

    public:
      int height = 0;
      int width = 0;
      int colorDepth = 0;
      int pixelDepth = 0;
      int availLeft = 0;
      int availTop = 0;
      int availHeight = 0;
      int availWidth = 0;
      double devicePixelRatio = 1.0;
      bool enable = false;
    };
    class WebRTC final {
    public:
      enum class ProtectionType : int {
        Default = 0,
        WebRTCIPHandlingProtected = 1,
        CustomIPAddrProtected = 2,
      };

      enum class WebRTCIPHandlingProtectedType : int {
        kWebRTCIPHandlingDefault = 0,
        kWebRTCIPHandlingDefaultPublicAndPrivateInterfaces = 1,
        kWebRTCIPHandlingDefaultPublicInterfaceOnly = 2,
        kWebRTCIPHandlingDisableNonProxiedUdp = 3,
      };

    public:
      inline WebRTC();
      inline WebRTC(const WebRTC &);
      inline ~WebRTC();
      inline void operator=(const WebRTC &);
      inline bool operator<<(const rapidjson::Value &);

    public:
      bool enable = false;
      ProtectionType protection_type = ProtectionType::Default;
      std::string ip = "203.0.113.1";
      unsigned short port = 8888;
      std::string dns = "8.8.8.8";
      WebRTCIPHandlingProtectedType webrtc_ip_handling_protected_type =
          WebRTCIPHandlingProtectedType::kWebRTCIPHandlingDefault;
    };
    class HardwareInfo final {
    public:
      inline HardwareInfo();
      inline ~HardwareInfo();
      inline HardwareInfo(const HardwareInfo &);
      inline void operator=(const HardwareInfo &);
      std::string model = "Z790 UD AX";
      std::string manufacturer = "Gigabyte Technology Co., Ltd.";
    };

  public:
    inline Fingerprint();
    inline ~Fingerprint();
    inline Fingerprint(const Fingerprint &obj);
    inline void operator=(const Fingerprint &obj);
    inline bool operator<<(const rapidjson::Value &);
    bool enable = false;
    std::string systemProductName = "Z790 UD AX";
    std::string platform = "Win32";
    std::string enable_do_not_track = "1";
    unsigned int hardwareConcurrency = 4;
    unsigned long long deviceMemory = 2147483648;
    std::string userAgent =
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, "
        "like Gecko) Chrome/130.0.0.0 Safari/537.36";
    Screen screen;
    WebRTC webrtc;
    HardwareInfo hardwareInfo;
  };

public:
  inline Chromium();
  inline Chromium(const std::string &);
  inline ~Chromium();
  inline bool operator<<(const rapidjson::Value &);
  inline bool operator<<(const std::string &);
  inline void operator>>(std::string &) const;

public:
  StartupArgs startup_args;
  Proxy proxy;
  Fingerprint fingerprint;
  Extensions extensions;

private:
  std::string source;
};

inline Chromium::Chromium() {
}
inline Chromium::Chromium(const std::string &data) {
  *this << data;
}
inline Chromium::~Chromium() {
}
inline void Chromium::operator>>(std::string &output) const {
  rapidjson::Document doc;
  if (source.empty()) {
    doc.SetObject();
  } else {
    if (doc.Parse(source.data(), source.size()).HasParseError()) {
      doc.SetObject();
    }
  }
  output = Json::toString(doc);
}
bool Chromium::operator<<(const rapidjson::Value &chromium_root) {
  bool result = false;
  do {
    if (!chromium_root.IsObject())
      break;
    proxy << chromium_root;
    startup_args << chromium_root;
    fingerprint << chromium_root;
    extensions << chromium_root;
    source = Json::toString(chromium_root);
    result = true;
  } while (0);
  return result;
}
inline bool Chromium::operator<<(const std::string &data) {
  bool result = false;
  do {
    if (data.empty())
      break;
    rapidjson::Document doc;
    if (doc.Parse(data.data(), data.size()).HasParseError())
      break;
    if (!doc.IsObject())
      break;
    proxy << doc;
    startup_args << doc;
    fingerprint << doc;
    extensions << doc;
    source = Json::toString(doc);
    result = true;
  } while (0);
  return result;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline Chromium::Fingerprint::HardwareInfo::HardwareInfo() {
}
inline Chromium::Fingerprint::HardwareInfo::~HardwareInfo() {
}
inline Chromium::Fingerprint::HardwareInfo::HardwareInfo(
    const HardwareInfo &obj) {
  *this = obj;
}
inline void
Chromium::Fingerprint::HardwareInfo::operator=(const HardwareInfo &obj) {
  model = obj.model;
  manufacturer = obj.manufacturer;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline Chromium::Proxy::Proxy() {
}
inline Chromium::Proxy::~Proxy() {
}
inline Chromium::Proxy::Proxy(const Proxy &obj) {
  *this = obj;
}
inline void Chromium::Proxy::operator=(const Proxy &obj) {
  enable = obj.enable;
  type = obj.type;
  port = obj.port;
  username = obj.username;
  password = obj.password;
  host = obj.host;
  source = obj.source;
}
inline bool Chromium::Proxy::operator<<(const rapidjson::Value &root) {
  bool result = false;
  do {
    if (!root.IsObject())
      break;
    if (!root.HasMember("proxy") || !root["proxy"].IsObject())
      break;
    auto &proxyObj = root["proxy"];
    if (proxyObj.HasMember("enable") && proxyObj["enable"].IsBool()) {
      enable = proxyObj["enable"].GetBool();
    }
    if (proxyObj.HasMember("source") && proxyObj["source"].IsString()) {
      source = proxyObj["source"].GetString();
      Parse();
    }
    result = true;
  } while (0);
  return result;
}
inline bool Chromium::Proxy::Parse() {
  bool result = false;
  do {
    std::regex url_regex(
        R"(^(http[s]?|socks[4-5](h|a)?):\/\/([^:]+):([^@]+)@([^:]+):(\d+)$)");
    std::smatch url_match;
    if (!std::regex_match(source, url_match, url_regex)) {
      address = source;
      break;
    }
    if (url_match.size() != 7)
      break;
    std::string protocol;
    if (std::string(url_match[1]).find("https") != std::string::npos) {
      protocol = "https";
      type = Proxy::Type::HTTPS;
    } else if (std::string(url_match[1]).find("http") != std::string::npos) {
      protocol = "http";
      type = Proxy::Type::HTTP;
    } else if (std::string(url_match[1]).find("socks4") != std::string::npos) {
      protocol = "socks4";
      type = Proxy::Type::SOCKS4;
    } else if (std::string(url_match[1]).find("socks5") != std::string::npos) {
      protocol = "socks5";
      type = Proxy::Type::SOCKS5;
    }
    if (protocol.empty())
      break;
    if (url_match[2].matched) {
      const std::string tmp(url_match[2]);
      if (tmp.find("h") != std::string::npos) {
        socks_type = Proxy::SocksType::SocksH;
      } else if (tmp.find("a") != std::string::npos) {
        socks_type = Proxy::SocksType::SocksA;
      }
    }
    if (url_match[3].matched)
      username = url_match[3];
    if (url_match[4].matched)
      password = url_match[4];
    if (url_match[5].matched)
      host = url_match[5];
    if (url_match[6].matched)
      port =
          static_cast<decltype(port)>(atoi(std::string(url_match[6]).c_str()));
    if (!protocol.empty() && !host.empty()) {
      address.clear();
      address.append(protocol).append("://").append(host).append(":").append(
          std::to_string(port));
    }
    result = true;
  } while (0);
  return result;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline Chromium::StartupArgs::Source::Source() {
}
inline Chromium::StartupArgs::Source::~Source() {
}
inline Chromium::StartupArgs::Source::Source(const Source &obj) {
  *this = obj;
}
inline void Chromium::StartupArgs::Source::operator=(const Source &obj) {
  key = obj.key;
  value = obj.value;
}
void Chromium::StartupArgs::Source::FixKey() {
  do {
    if (key.empty())
      break;
    if (*key.begin() == '-')
      key.erase(key.begin());
    else
      break;
  } while (true);
}
inline void
Chromium::StartupArgs::Source::operator<<(const std::string &argstr) {
  do {
    if (argstr.empty())
      break;
    auto f = argstr.find('=');
    if (f == std::string::npos) {
      key = argstr;
      value.clear();
    } else {
      key = argstr.substr(0, f);
      value = argstr.substr(f + 1);
    }
    FixKey();
  } while (0);
}
inline Chromium::StartupArgs::StartupArgs() {
}
inline Chromium::StartupArgs::~StartupArgs() {
}
inline Chromium::StartupArgs::StartupArgs(const StartupArgs &obj) {
  *this = obj;
}
inline void Chromium::StartupArgs::operator=(const StartupArgs &obj) {
  enable = obj.enable;
  sources.clear();
  for (const auto &src : obj.sources) {
    sources.emplace_back(src);
  }
}
inline bool Chromium::StartupArgs::operator<<(const rapidjson::Value &root) {
  bool result = false;
  do {
    if (!root.IsObject())
      break;
    if (!root.HasMember("startup_args") || !root["startup_args"].IsObject())
      break;
    auto &argsObj = root["startup_args"];
    if (argsObj.HasMember("enable") && argsObj["enable"].IsBool()) {
      enable = argsObj["enable"].GetBool();
    }
    if (argsObj.HasMember("source") && argsObj["source"].IsArray()) {
      sources.clear();
      for (auto it = argsObj["source"].Begin(); it != argsObj["source"].End();
           ++it) {
        if (!it->IsString())
          break;
        Chromium::StartupArgs::Source src;
        src << it->GetString();
        if (!src.key.empty()) {
          sources.emplace_back(src);
        }
      }
    }
    result = true;
  } while (0);
  return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline Chromium::Extensions::Extensions() {
}
inline Chromium::Extensions::~Extensions() {
}
inline Chromium::Extensions::Extensions(const Extensions &obj) {
  *this = obj;
}
inline void Chromium::Extensions::operator=(const Extensions &obj) {
  allowlist.clear();
  for (const auto &ext : obj.allowlist) {
    allowlist.insert(ext);
  }
}
inline bool
Chromium::Extensions::IsAllowlisted(const std::string &extid) const {
  return allowlist.find(extid) != allowlist.end();
}
inline bool Chromium::Extensions::operator<<(const rapidjson::Value &root) {
  bool result = false;
  do {
    if (!root.IsObject())
      break;
    if (!root.HasMember("extensions") || !root["extensions"].IsObject())
      break;
    auto &extObj = root["extensions"];
    if (extObj.HasMember("enable") && extObj["enable"].IsBool()) {
      enable = extObj["enable"].GetBool();
    }
    if (extObj.HasMember("allowlist") && extObj["allowlist"].IsArray()) {
      allowlist.clear();
      for (auto it = extObj["allowlist"].Begin();
           it != extObj["allowlist"].End(); ++it) {
        if (!it->IsString())
          break;
        allowlist.insert(it->GetString());
      }
    }
    result = true;
  } while (0);
  return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline Chromium::Fingerprint::Screen::Screen() {
}
inline Chromium::Fingerprint::Screen::Screen(const Screen &obj) {
  *this = obj;
}
inline Chromium::Fingerprint::Screen::~Screen() {
}
inline void Chromium::Fingerprint::Screen::operator=(const Screen &obj) {
  height = obj.height;
  width = obj.width;
  colorDepth = obj.colorDepth;
  pixelDepth = obj.pixelDepth;
  availLeft = obj.availLeft;
  availTop = obj.availTop;
  availHeight = obj.availHeight;
  availWidth = obj.availWidth;
  devicePixelRatio = obj.devicePixelRatio;
  enable = obj.enable;
}
inline bool
Chromium::Fingerprint::Screen::operator<<(const rapidjson::Value &root) {
  bool result = false;
  do {
    if (!root.IsObject())
      break;
    if (!root.HasMember("screen") || !root["screen"].IsObject())
      break;
    auto &screenObj = root["screen"];
    if (screenObj.HasMember("height") && screenObj["height"].IsInt()) {
      height = screenObj["height"].GetInt();
    }
    if (screenObj.HasMember("width") && screenObj["width"].IsInt()) {
      width = screenObj["width"].GetInt();
    }
    if (screenObj.HasMember("colorDepth") && screenObj["colorDepth"].IsInt()) {
      colorDepth = screenObj["colorDepth"].GetInt();
    }
    if (screenObj.HasMember("pixelDepth") && screenObj["pixelDepth"].IsInt()) {
      pixelDepth = screenObj["pixelDepth"].GetInt();
    }
    if (screenObj.HasMember("availLeft") && screenObj["availLeft"].IsInt()) {
      availLeft = screenObj["availLeft"].GetInt();
    }
    if (screenObj.HasMember("availTop") && screenObj["availTop"].IsInt()) {
      availTop = screenObj["availTop"].GetInt();
    }
    if (screenObj.HasMember("availHeight") &&
        screenObj["availHeight"].IsInt()) {
      availHeight = screenObj["availHeight"].GetInt();
    }
    if (screenObj.HasMember("availWidth") && screenObj["availWidth"].IsInt()) {
      availWidth = screenObj["availWidth"].GetInt();
    }
    if (screenObj.HasMember("devicePixelRatio") &&
        screenObj["devicePixelRatio"].IsDouble()) {
      devicePixelRatio = screenObj["devicePixelRatio"].GetDouble();
    }
    if (screenObj.HasMember("enable") && screenObj["enable"].IsBool()) {
      enable = screenObj["enable"].GetBool();
    }
    result = true;
  } while (0);
  return result;
}
////////////////////////////////////////////////////////////////////////
inline Chromium::Fingerprint::WebRTC::WebRTC() {
}
inline Chromium::Fingerprint::WebRTC::WebRTC(const WebRTC &obj) {
  *this = obj;
}
inline Chromium::Fingerprint::WebRTC::~WebRTC() {
}
inline void Chromium::Fingerprint::WebRTC::operator=(const WebRTC &obj) {
  enable = obj.enable;
  protection_type = obj.protection_type;
  ip = obj.ip;
  port = obj.port;
  dns = obj.dns;
  webrtc_ip_handling_protected_type = obj.webrtc_ip_handling_protected_type;
}
inline bool
Chromium::Fingerprint::WebRTC::operator<<(const rapidjson::Value &root) {
  bool result = false;
  do {
    if (!root.IsObject())
      break;
    if (!root.HasMember("webrtc") || !root["webrtc"].IsObject())
      break;
    auto &webrtcObj = root["webrtc"];
    if (webrtcObj.HasMember("enable") && webrtcObj["enable"].IsBool()) {
      enable = webrtcObj["enable"].GetBool();
    }
    if (webrtcObj.HasMember("ip") && webrtcObj["ip"].IsString()) {
      ip = webrtcObj["ip"].GetString();
    }
    if (webrtcObj.HasMember("port") && webrtcObj["port"].IsUint()) {
      port = static_cast<decltype(port)>(webrtcObj["port"].GetUint());
    }
    if (webrtcObj.HasMember("dns") && webrtcObj["dns"].IsString()) {
      dns = webrtcObj["dns"].GetString();
    }
    if (webrtcObj.HasMember("protection_type") &&
        webrtcObj["protection_type"].IsInt()) {
      protection_type = static_cast<decltype(protection_type)>(
          webrtcObj["protection_type"].GetInt());
    }
    if (webrtcObj.HasMember("webrtc_ip_handling_protected_type") &&
        webrtcObj["webrtc_ip_handling_protected_type"].IsInt()) {
      webrtc_ip_handling_protected_type =
          static_cast<decltype(webrtc_ip_handling_protected_type)>(
              webrtcObj["webrtc_ip_handling_protected_type"].GetInt());
    }
    result = true;
  } while (0);
  return result;
}
////////////////////////////////////////////////////////////////////////
inline Chromium::Fingerprint::Fingerprint() {
}
inline Chromium::Fingerprint::~Fingerprint() {
}
inline Chromium::Fingerprint::Fingerprint(const Fingerprint &obj) {
  *this = obj;
}
inline void Chromium::Fingerprint::operator=(const Fingerprint &obj) {
  screen = obj.screen;
  webrtc = obj.webrtc;
  enable = obj.enable;
  platform = obj.platform;
  enable_do_not_track = obj.enable_do_not_track;
  hardwareConcurrency = obj.hardwareConcurrency;
  deviceMemory = obj.deviceMemory;
  userAgent = obj.userAgent;
  systemProductName = obj.systemProductName;
}
inline bool Chromium::Fingerprint::operator<<(const rapidjson::Value &root) {
  bool result = false;
  do {
    if (!root.IsObject())
      break;
    if (!root.HasMember("fingerprint") || !root["fingerprint"].IsObject())
      break;
    auto &fpsObj = root["fingerprint"];
    if (fpsObj.HasMember("enable") && fpsObj["enable"].IsBool()) {
      enable = fpsObj["enable"].GetBool();
    }
    if (fpsObj.HasMember("platform") && fpsObj["platform"].IsString()) {
      platform = fpsObj["platform"].GetString();
    }
    if (fpsObj.HasMember("enable_do_not_track") &&
        fpsObj["enable_do_not_track"].IsString()) {
      enable_do_not_track = fpsObj["enable_do_not_track"].GetString();
    }
    if (fpsObj.HasMember("hardwareConcurrency") &&
        fpsObj["hardwareConcurrency"].IsUint()) {
      hardwareConcurrency = fpsObj["hardwareConcurrency"].GetUint();
    }
    if (fpsObj.HasMember("deviceMemory") && fpsObj["deviceMemory"].IsUint64()) {
      deviceMemory = fpsObj["deviceMemory"].GetUint64();
    }
    if (fpsObj.HasMember("userAgent") && fpsObj["userAgent"].IsString()) {
      userAgent = fpsObj["userAgent"].GetString();
    }
    if (fpsObj.HasMember("hardwareInfo") && fpsObj["hardwareInfo"].IsObject()) {
      auto &hwObj = fpsObj["hardwareInfo"];
      if (hwObj.HasMember("model") && hwObj["model"].IsString()) {
        hardwareInfo.model = hwObj["model"].GetString();
      }
      if (hwObj.HasMember("manufacturer") && hwObj["manufacturer"].IsString()) {
        hardwareInfo.manufacturer = hwObj["manufacturer"].GetString();
      }
    }
    webrtc << fpsObj;
    screen << fpsObj;
    result = true;
  } while (0);
  return result;
}
} // namespace

class IConfigure final {
public:
  inline IConfigure(const std::string &);
  inline ~IConfigure();
  inline void operator>>(std::string &) const;

private:
  inline IConfigure();
  inline IConfigure(const IConfigure &);
  inline void operator=(const IConfigure &);
  inline bool operator<<(const std::string &);

public:
  inline const Chromium &GetChromium() const;
  inline const unsigned short &GetID() const;
  inline const std::string &GetSuperMAC() const;
  inline const std::string &GetRootDir() const;
  inline std::string GetExtensionsDir() const;
  inline std::string GetDefaultConfigurePath() const;
  inline std::string GetEnvironmentConfigurePath() const;
  inline std::string GetUserDataDir() const;
  inline std::string GetRouteDir() const;
  inline std::string GetTmpDir() const;

public: //!@ 'Non-chromium usage' | 'Enabler or third-party method'
  inline void
  SetSuperMAC(const std::function<std::string(const std::string &)> &);
  inline void SetRootDir(const std::string &);

private:
  inline std::string FixPath(const std::string &) const;

private:
  Chromium chromium;
  std::string root_dir = "/";
  unsigned short id = 0;
  std::string super_mac =
      "B7C526C87A5028D5DD5A472E7C3E7D23E835B2CDE16B32F9CF7185462923B0AB";
  std::string source = "{}";
};
inline IConfigure::IConfigure() {
}
inline IConfigure::~IConfigure() {
}
inline IConfigure::IConfigure(const IConfigure &obj) {
  *this = obj;
}
inline IConfigure::IConfigure(const std::string &body) {
  *this << body;
}
inline void IConfigure::operator=(const IConfigure &obj) {
  chromium = obj.chromium;
  super_mac = obj.super_mac;
  root_dir = obj.root_dir;
  source = obj.source;
  id = obj.id;
}
inline std::string IConfigure::FixPath(const std::string &path) const {
  std::string result = path;
  for (auto it = result.begin(); it != result.end(); ++it) {
    if (*it == '\\') {
      *it = '/';
    }
  }
  return result;
}
inline bool IConfigure::operator<<(const std::string &data) {
  bool result = false;
  do {
    if (data.empty())
      break;
    rapidjson::Document doc;
    if (doc.Parse(data.data(), data.size()).HasParseError())
      break;
    if (!doc.IsObject())
      break;
    if (doc.HasMember("id") && doc["id"].IsUint()) {
      id = static_cast<decltype(id)>(doc["id"].GetUint());
    }
    if (doc.HasMember("super_mac") && doc["super_mac"].IsString()) {
      super_mac = doc["super_mac"].GetString();
    }
    if (doc.HasMember("root_dir") && doc["root_dir"].IsString()) {
      root_dir = doc["root_dir"].GetString();
      root_dir = FixPath(root_dir);
    }
    if (doc.HasMember("chromium") && doc["chromium"].IsObject()) {
      chromium << doc["chromium"];
    }
    source = Json::toString(doc);
    result = true;
  } while (0);
  return result;
}
inline void IConfigure::operator>>(std::string &output) const {
  output = source;
}
inline const Chromium &IConfigure::GetChromium() const {
  return chromium;
}
inline const std::string &IConfigure::GetRootDir() const {
  return root_dir;
}
inline std::string IConfigure::GetExtensionsDir() const {
  return root_dir + "/" + chromium::project_dirname_extensions;
}
inline std::string IConfigure::GetDefaultConfigurePath() const {
  return root_dir + "/" + chromium::project_dirname_configures + "/" +
         chromium::project_filename_configure;
}
inline std::string IConfigure::GetEnvironmentConfigurePath() const {
  return GetUserDataDir() + "/" + project_dirname_chromium + "/" +
         chromium::project_filename_configure;
}
inline std::string IConfigure::GetUserDataDir() const {
  std::stringstream ss;
  ss << std::hex << id;
  return root_dir + "/" + chromium::project_dirname_cache + "/" + ss.str();
}
inline std::string IConfigure::GetRouteDir() const {
  return root_dir + "/" + chromium::project_dirname_route;
}
inline std::string IConfigure::GetTmpDir() const {
  return root_dir + "/" + chromium::project_dirname_tmp;
}
inline const unsigned short &IConfigure::GetID() const {
  return id;
}
inline const std::string &IConfigure::GetSuperMAC() const {
  return super_mac;
}
inline void IConfigure::SetSuperMAC(
    const std::function<std::string(const std::string &)> &func) {
  if (!func) {
    return;
  }
  rapidjson::Document doc;
  if (source.empty()) {
    doc.SetObject();
  } else {
    if (doc.Parse(source.data(), source.size()).HasParseError()) {
      doc.SetObject();
    }
  }
  std::string super_mac_value;
  if (doc.HasMember("chromium") && doc["chromium"].IsObject()) {
    Json::Sort(doc["chromium"], doc.GetAllocator());
    super_mac_value = func(Json::toString(doc["chromium"]));
  }
  rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();
  if (doc.HasMember("super_mac")) {
    doc.RemoveMember("super_mac");
  }
  doc.AddMember(
      rapidjson::Value().SetString("super_mac", allocator).Move(),
      rapidjson::Value()
          .SetString(super_mac_value.empty() ? "" : super_mac_value.c_str(),
                     allocator)
          .Move(),
      allocator);
  source = Json::toString(doc);
  super_mac = super_mac_value;
}
inline void IConfigure::SetRootDir(const std::string &dir) {
  root_dir = FixPath(dir);
  rapidjson::Document doc;
  if (source.empty()) {
    doc.SetObject();
  } else {
    if (doc.Parse(source.data(), source.size()).HasParseError()) {
      doc.SetObject();
    }
  }
  rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();
  if (doc.HasMember("root_dir")) {
    doc.RemoveMember("root_dir");
  }
  doc.AddMember(
      rapidjson::Value().SetString("root_dir", allocator).Move(),
      rapidjson::Value()
          .SetString(root_dir.empty() ? "/" : root_dir.c_str(), allocator)
          .Move(),
      allocator);
  source = Json::toString(doc);
}
} // namespace chromium

/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 26 May 2025 03:59:30 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__F6058B7C_FA8D_4C9D_A424_6B2548FF1F7E__