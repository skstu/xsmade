#if !defined(__8B6326C0_93E4_49D8_BFC7_EB6C3BA59694__)
#define __8B6326C0_93E4_49D8_BFC7_EB6C3BA59694__
#include "rapidjson.h"
namespace chromium {
namespace cfg {
using seed_type_t = unsigned int;
using id_type_t = unsigned long long;
constexpr char project_dirname_chromium[] = "Chromium";
constexpr char project_dirname_default_user_data[] = "chromium";
constexpr char project_dirname_components[] = "components";
constexpr char project_dirname_extensions[] = "extensions";
constexpr char project_dirname_route[] = "route";
constexpr char project_dirname_tmp[] = "tmp";
constexpr char project_dirname_cache[] = "cache";
constexpr char project_dirname_configures[] = "configures";
constexpr char project_filename_configure[] = "configure.json";
constexpr char project_filename_tmpcfgpath[] = "cfgpath.cfg";
///////////////////////////////////////////////////////////////////////////////////////////////
class IStartup final {
public:
  inline IStartup();
  inline ~IStartup();
  inline IStartup(const IStartup &);
  inline IStartup &operator=(const IStartup &);
  inline void operator<<(const rapidjson::Value &value);

public:
  bool enable = false;
  std::string homepage;
  std::string search_engine;
  std::vector<std::string> urls;
  std::vector<std::string> args;
};
inline IStartup::IStartup() {
}
inline IStartup::~IStartup() {
}
inline IStartup::IStartup(const IStartup &obj) {
  *this = obj;
}
inline IStartup &IStartup::operator=(const IStartup &obj) {
  args.clear();
  for (const auto &item : obj.args) {
    args.emplace_back(item);
  }
  enable = obj.enable;
  homepage = obj.homepage;
  search_engine = obj.search_engine;
  urls.clear();
  for (const auto &item : obj.urls) {
    urls.emplace_back(item);
  }
  return *this;
}
inline void IStartup::operator<<(const rapidjson::Value &value) {
  do {
    if (!value.IsObject())
      break;
    if (value.HasMember("args") && value["args"].IsArray()) {
      const rapidjson::Value &refObj = value["args"];
      for (rapidjson::SizeType i = 0; i < refObj.Size(); ++i) {
        if (!refObj[i].IsString())
          break;
        args.emplace_back(refObj[i].GetString());
      }
    }
    if (value.HasMember("enable") && value["enable"].IsBool()) {
      enable = value["enable"].GetBool();
    }
    if (value.HasMember("homepage") && value["homepage"].IsString()) {
      homepage = value["homepage"].GetString();
    }
    if (value.HasMember("search_engine") && value["search_engine"].IsString()) {
      search_engine = value["search_engine"].GetString();
    }
    if (value.HasMember("urls") && value["urls"].IsArray()) {
      const rapidjson::Value &refObj = value["urls"];
      for (rapidjson::SizeType i = 0; i < refObj.Size(); ++i) {
        if (!refObj[i].IsString())
          break;
        urls.emplace_back(refObj[i].GetString());
      }
    }
  } while (0);
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
class IExtensions final {
public:
  inline IExtensions();
  inline ~IExtensions();
  inline IExtensions(const IExtensions &);
  inline IExtensions &operator=(const IExtensions &);
  inline void operator<<(const rapidjson::Value &value);

public:
  bool enable = false;
  std::set<std::string> allowlist;
};
inline IExtensions::IExtensions() {
}
inline IExtensions::~IExtensions() {
}
inline IExtensions::IExtensions(const IExtensions &obj) {
  *this = obj;
}
inline IExtensions &IExtensions::operator=(const IExtensions &obj) {
  enable = obj.enable;
  allowlist.clear();
  for (const auto &item : obj.allowlist) {
    allowlist.emplace(item);
  }
  return *this;
}
inline void IExtensions::operator<<(const rapidjson::Value &value) {
  do {
    if (!value.IsObject())
      break;
    if (value.HasMember("enable") && value["enable"].IsBool()) {
      enable = value["enable"].GetBool();
    }
    if (value.HasMember("allowlist") && value["allowlist"].IsArray()) {
      const rapidjson::Value &refObj = value["allowlist"];
      for (rapidjson::SizeType i = 0; i < refObj.Size(); ++i) {
        if (!refObj[i].IsString())
          break;
        allowlist.emplace(refObj[i].GetString());
      }
    }
  } while (0);
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
class IJss final {
public:
  inline IJss();
  inline ~IJss();
  inline IJss(const IJss &);
  inline IJss &operator=(const IJss &);
  inline void operator<<(const rapidjson::Value &value);

public:
  bool enable = false;
  std::string frameImplDidClearWindowObject;
};
inline IJss::IJss() {
}
inline IJss::~IJss() {
}
inline IJss::IJss(const IJss &obj) {
  *this = obj;
}
inline IJss &IJss::operator=(const IJss &obj) {
  enable = obj.enable;
  frameImplDidClearWindowObject = obj.frameImplDidClearWindowObject;
  return *this;
}
inline void IJss::operator<<(const rapidjson::Value &value) {
  do {
    if (!value.IsObject())
      break;
    if (value.HasMember("enable") && value["enable"].IsBool()) {
      enable = value["enable"].GetBool();
    }
    if (value.HasMember("frameImplDidClearWindowObject") &&
        value["frameImplDidClearWindowObject"].IsString() &&
        value["frameImplDidClearWindowObject"].GetStringLength() > 0) {
      frameImplDidClearWindowObject =
          value["frameImplDidClearWindowObject"].GetString();
    }
  } while (0);
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
class IFingerprint final {
public:
  class Hash final {
  public:
    inline Hash();
    inline ~Hash();
    inline Hash(const Hash &);
    inline Hash &operator=(const Hash &);
    inline void operator<<(const rapidjson::Value &value);

  public:
    bool enable = false;
    bool random = false;
    double base = 0.0;
    double from = 0.0;
    double to = 0.0;
  };
  class Canvas final {
  public:
    inline Canvas();
    inline ~Canvas();
    inline Canvas(const Canvas &);
    inline Canvas &operator=(const Canvas &);
    inline void operator<<(const rapidjson::Value &value);

  public:
    bool enable = false;
    Hash hash;
  };
  class Webgl final {
  public:
    inline Webgl();
    inline ~Webgl();
    inline Webgl(const Webgl &);
    inline Webgl &operator=(const Webgl &);
    inline void operator<<(const rapidjson::Value &value);

  public:
    bool enable = false;
    Hash hash;
  };
  class Audio final {
  public:
    inline Audio();
    inline ~Audio();
    inline Audio(const Audio &);
    inline Audio &operator=(const Audio &);
    inline void operator<<(const rapidjson::Value &value);

  public:
    bool enable = false;
    Hash hash;
  };
  class Font final {
  public:
    inline Font();
    inline ~Font();
    inline Font(const Font &);
    inline Font &operator=(const Font &);
    inline void operator<<(const rapidjson::Value &value);

  public:
    bool enable = false;
    Hash hash;
    std::set<std::string> allowlist;
  };
  class Webrtc final {
  public:
    inline Webrtc();
    inline ~Webrtc();
    inline Webrtc(const Webrtc &);
    inline Webrtc &operator=(const Webrtc &);
    inline void operator<<(const rapidjson::Value &value);

  public:
    bool enable = false;
    bool enable_protected = false;
    std::string localIP = "192.168.0.100";
    std::string publicIP = "88.66.66.88";
  };

public:
  inline IFingerprint();
  inline ~IFingerprint();
  inline IFingerprint(const IFingerprint &);
  inline IFingerprint &operator=(const IFingerprint &);
  inline void operator<<(const rapidjson::Value &value);

public:
  bool enable = false;
  Font font;
  Canvas canvas;
  Webgl webgl;
  Audio audio;
  Webrtc webrtc;
  std::string timezone = "Asia/Shanghai";
  std::string enable_do_not_track = "null";
  std::string platform = "Win32";
  unsigned int hardwareConcurrency = 4;
  unsigned int deviceMemory = 8;
  std::string userAgent =
      "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, "
      "like Gecko) Chrome/138.0.0.0 Safari/537.36";
};
inline IFingerprint::IFingerprint() {
}
inline IFingerprint::~IFingerprint() {
}
inline IFingerprint::IFingerprint(const IFingerprint &obj) {
  *this = obj;
}
inline IFingerprint &IFingerprint::operator=(const IFingerprint &obj) {
  // Copy constructor logic if needed
  enable = obj.enable;
  font = obj.font;
  canvas = obj.canvas;
  webgl = obj.webgl;
  audio = obj.audio;
  webrtc = obj.webrtc;
  timezone = obj.timezone;
  userAgent = obj.userAgent;
  deviceMemory = obj.deviceMemory;
  hardwareConcurrency = obj.hardwareConcurrency;
  platform = obj.platform;
  enable_do_not_track = obj.enable_do_not_track;
  return *this;
}
inline void IFingerprint::operator<<(const rapidjson::Value &value) {
  // Parse the fingerprint data from the JSON value
  // This is a placeholder; actual implementation will depend on the structure
  // of the JSON
  do {
    if (!value.IsObject())
      break;
    if (value.HasMember("enable") && value["enable"].IsBool())
      enable = value["enable"].GetBool();
    if (value.HasMember("font"))
      font << value["font"];
    if (value.HasMember("canvas"))
      canvas << value["canvas"];
    if (value.HasMember("webgl"))
      webgl << value["webgl"];
    if (value.HasMember("audio"))
      audio << value["audio"];
    if (value.HasMember("webrtc"))
      webrtc << value["webrtc"];
    if (value.HasMember("enable_do_not_track") &&
        value["enable_do_not_track"].IsString() &&
        value["enable_do_not_track"].GetStringLength() > 0)
      enable_do_not_track = value["enable_do_not_track"].GetString();
    if (value.HasMember("platform") && value["platform"].IsString() &&
        value["platform"].GetStringLength() > 0)
      platform = value["platform"].GetString();
    if (value.HasMember("userAgent") && value["userAgent"].IsString() &&
        value["userAgent"].GetStringLength() > 0)
      userAgent = value["userAgent"].GetString();
    if (value.HasMember("timezone") && value["timezone"].IsString() &&
        value["timezone"].GetStringLength() > 0)
      timezone = value["timezone"].GetString();
    if (value.HasMember("deviceMemory") && value["deviceMemory"].IsUint())
      deviceMemory = value["deviceMemory"].GetUint();
    if (value.HasMember("hardwareConcurrency") &&
        value["hardwareConcurrency"].IsUint())
      hardwareConcurrency = value["hardwareConcurrency"].GetUint();
    // Process the fingerprint data here
  } while (0);
}
IFingerprint::Hash::Hash() {
}
IFingerprint::Hash::~Hash() {
}
inline IFingerprint::Hash::Hash(const IFingerprint::Hash &obj) {
  *this = obj;
}
inline IFingerprint::Hash &
IFingerprint::Hash::operator=(const IFingerprint::Hash &obj) {
  enable = obj.enable;
  random = obj.random;
  base = obj.base;
  from = obj.from;
  to = obj.to;
  return *this;
}
inline void IFingerprint::Hash::operator<<(const rapidjson::Value &value) {
  do {
    if (!value.IsObject())
      break;
    if (value.HasMember("enable") && value["enable"].IsBool())
      enable = value["enable"].GetBool();

    if (value.HasMember("random") && value["random"].IsBool())
      random = value["random"].GetBool();

    if (value.HasMember("base") && value["base"].IsNumber()) {
      if (value.IsDouble())
        base = value["base"].GetDouble();
      else if (value.IsInt())
        base = static_cast<double>(value["base"].GetInt());
      else if (value.IsUint())
        base = static_cast<double>(value["base"].GetUint());
      else if (value.IsInt64())
        base = static_cast<double>(value["base"].GetInt64());
      else if (value.IsUint64())
        base = static_cast<double>(value["base"].GetUint64());
    }

    if (value.HasMember("from") && value["from"].IsNumber()) {
      if (value["from"].IsDouble())
        from = value["from"].GetDouble();
      else if (value["from"].IsInt())
        from = static_cast<double>(value["from"].GetInt());
      else if (value["from"].IsUint())
        from = static_cast<double>(value["from"].GetUint());
      else if (value["from"].IsInt64())
        from = static_cast<double>(value["from"].GetInt64());
      else if (value["from"].IsUint64())
        from = static_cast<double>(value["from"].GetUint64());
    }

    if (value.HasMember("to") && value["to"].IsNumber()) {
      if (value["to"].IsDouble())
        to = value["to"].GetDouble();
      else if (value["to"].IsInt())
        to = static_cast<double>(value["to"].GetInt());
      else if (value["to"].IsUint())
        to = static_cast<double>(value["to"].GetUint());
      else if (value["to"].IsInt64())
        to = static_cast<double>(value["to"].GetInt64());
      else if (value["to"].IsUint64())
        to = static_cast<double>(value["to"].GetUint64());
    }

  } while (0);
}
///////////////////////////////////////////////////////////////////////////////////////////////
inline IFingerprint::Canvas::Canvas() {
}
inline IFingerprint::Canvas::~Canvas() {
}
inline IFingerprint::Canvas::Canvas(const IFingerprint::Canvas &obj) {
  *this = obj;
}
inline IFingerprint::Canvas &
IFingerprint::Canvas::operator=(const IFingerprint::Canvas &obj) {
  enable = obj.enable;
  hash = obj.hash;
  return *this;
}
inline void IFingerprint::Canvas::operator<<(const rapidjson::Value &value) {
  do {
    if (!value.IsObject())
      break;
    if (value.HasMember("enable") && value["enable"].IsBool())
      enable = value["enable"].GetBool();
    if (value.HasMember("hash"))
      hash << value["hash"];
  } while (0);
}
///////////////////////////////////////////////////////////////////////////////////////////////
inline IFingerprint::Webrtc::Webrtc() {
}
inline IFingerprint::Webrtc::~Webrtc() {
}
inline IFingerprint::Webrtc::Webrtc(const IFingerprint::Webrtc &obj) {
  *this = obj;
}
inline IFingerprint::Webrtc &
IFingerprint::Webrtc::operator=(const IFingerprint::Webrtc &obj) {
  enable = obj.enable;
  enable_protected = obj.enable_protected;
  localIP = obj.localIP;
  publicIP = obj.publicIP;
  return *this;
}
inline void IFingerprint::Webrtc::operator<<(const rapidjson::Value &value) {
  do {
    if (!value.IsObject())
      break;
    if (value.HasMember("enable") && value["enable"].IsBool())
      enable = value["enable"].GetBool();
    if (value.HasMember("enable_protected") &&
        value["enable_protected"].IsBool())
      enable_protected = value["enable_protected"].GetBool();
    if (value.HasMember("localIP") && value["localIP"].IsString() &&
        value["localIP"].GetStringLength())
      localIP = value["localIP"].GetString();
    if (value.HasMember("publicIP") && value["publicIP"].IsString() &&
        value["publicIP"].GetStringLength())
      publicIP = value["publicIP"].GetString();
  } while (0);
}
///////////////////////////////////////////////////////////////////////////////////////////////
inline IFingerprint::Webgl::Webgl() {
}
inline IFingerprint::Webgl::~Webgl() {
}
inline IFingerprint::Webgl::Webgl(const IFingerprint::Webgl &obj) {
  *this = obj;
}
inline IFingerprint::Webgl &
IFingerprint::Webgl::operator=(const IFingerprint::Webgl &obj) {
  enable = obj.enable;
  hash = obj.hash;
  return *this;
}
inline void IFingerprint::Webgl::operator<<(const rapidjson::Value &value) {
  do {
    if (!value.IsObject())
      break;
    if (value.HasMember("enable") && value["enable"].IsBool())
      enable = value["enable"].GetBool();
    if (value.HasMember("hash"))
      hash << value["hash"];
  } while (0);
}
///////////////////////////////////////////////////////////////////////////////////////////////
inline IFingerprint::Audio::Audio() {
}
inline IFingerprint::Audio::~Audio() {
}
inline IFingerprint::Audio::Audio(const IFingerprint::Audio &obj) {
  *this = obj;
}
inline IFingerprint::Audio &
IFingerprint::Audio::operator=(const IFingerprint::Audio &obj) {
  enable = obj.enable;
  hash = obj.hash;
  return *this;
}
inline void IFingerprint::Audio::operator<<(const rapidjson::Value &value) {
  do {
    if (!value.IsObject())
      break;
    if (value.HasMember("enable") && value["enable"].IsBool())
      enable = value["enable"].GetBool();
    if (value.HasMember("hash"))
      hash << value["hash"];
  } while (0);
}
///////////////////////////////////////////////////////////////////////////////////////////////
inline IFingerprint::Font::Font() {
}
inline IFingerprint::Font::~Font() {
}
inline IFingerprint::Font::Font(const IFingerprint::Font &obj) {
  *this = obj;
}
inline IFingerprint::Font &
IFingerprint::Font::operator=(const IFingerprint::Font &obj) {
  enable = obj.enable;
  hash = obj.hash;
  allowlist.clear();
  for (const auto &item : obj.allowlist) {
    allowlist.emplace(item);
  }
  return *this;
}
inline void IFingerprint::Font::operator<<(const rapidjson::Value &value) {
  do {
    if (!value.IsObject())
      break;
    if (value.HasMember("enable") && value["enable"].IsBool())
      enable = value["enable"].GetBool();
    if (value.HasMember("hash"))
      hash << value["hash"];
    if (value.HasMember("allowlist") && value["allowlist"].IsArray()) {
      const rapidjson::Value &refObj = value["allowlist"];
      for (rapidjson::SizeType i = 0; i < refObj.Size(); ++i) {
        if (!refObj[i].IsString())
          break;
        allowlist.emplace(refObj[i].GetString());
      }
    }
  } while (0);
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
class IServer final {
public:
  inline IServer();
  inline ~IServer();
  inline IServer(const IServer &);
  inline IServer &operator=(const IServer &);
  inline void operator<<(const rapidjson::Value &value);

public:
  bool enable = false;
  std::string pipe;
  std::string tcp;
  std::string udp;
  std::string http;
};
inline IServer::IServer() {
}
inline IServer::~IServer() {
}
inline IServer::IServer(const IServer &obj) {
  *this = obj;
}
inline IServer &IServer::operator=(const IServer &obj) {
  enable = obj.enable;
  pipe = obj.pipe;
  tcp = obj.tcp;
  udp = obj.udp;
  http = obj.http;
  return *this;
}
inline void IServer::operator<<(const rapidjson::Value &value) {
  do {
    if (!value.IsObject())
      break;
    if (value.HasMember("enable") && value["enable"].IsBool())
      enable = value["enable"].GetBool();
    if (value.HasMember("pipe") && value["pipe"].IsString())
      pipe = value["pipe"].GetString();
    if (value.HasMember("tcp") && value["tcp"].IsString())
      tcp = value["tcp"].GetString();
    if (value.HasMember("udp") && value["udp"].IsString())
      udp = value["udp"].GetString();
    if (value.HasMember("http") && value["http"].IsString())
      http = value["http"].GetString();
  } while (0);
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
class ICookies final {
public:
  inline ICookies();
  inline ~ICookies();
  inline ICookies(const ICookies &);
  inline ICookies &operator=(const ICookies &);
  inline void operator<<(const rapidjson::Value &value);

public:
  bool enable = false;
  std::set<std::string> blocklist;
};
inline ICookies::ICookies() {
}
inline ICookies::~ICookies() {
}
inline ICookies::ICookies(const ICookies &obj) {
  *this = obj;
}
inline ICookies &ICookies::operator=(const ICookies &obj) {
  enable = obj.enable;
  blocklist.clear();
  for (const auto &item : obj.blocklist) {
    blocklist.emplace(item);
  }
  return *this;
}
inline void ICookies::operator<<(const rapidjson::Value &value) {
  do {
    if (!value.IsObject())
      break;
    if (value.HasMember("enable") && value["enable"].IsBool())
      enable = value["enable"].GetBool();
    if (value.HasMember("blocklist") && value["blocklist"].IsArray()) {
      const rapidjson::Value &refObj = value["blocklist"];
      for (rapidjson::SizeType i = 0; i < refObj.Size(); ++i) {
        if (!refObj[i].IsString())
          break;
        std::string tmp(refObj[i].GetString());
        if (tmp.empty())
          continue;
        std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
        blocklist.emplace(tmp);
      }
    }
  } while (0);
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
class IStorage final {
public:
  inline IStorage();
  inline ~IStorage();
  inline IStorage(const IStorage &);
  inline IStorage &operator=(const IStorage &);
  inline void operator<<(const rapidjson::Value &value);

public:
  bool enable = false;
  std::set<std::string> blocklist;
};
inline IStorage::IStorage() {
}
inline IStorage::~IStorage() {
}
inline IStorage::IStorage(const IStorage &obj) {
  *this = obj;
}
inline IStorage &IStorage::operator=(const IStorage &obj) {
  enable = obj.enable;
  blocklist.clear();
  for (const auto &item : obj.blocklist) {
    blocklist.emplace(item);
  }
  return *this;
}
inline void IStorage::operator<<(const rapidjson::Value &value) {
  do {
    if (!value.IsObject())
      break;
    if (value.HasMember("enable") && value["enable"].IsBool())
      enable = value["enable"].GetBool();
    if (value.HasMember("blocklist") && value["blocklist"].IsArray()) {
      const rapidjson::Value &refObj = value["blocklist"];
      for (rapidjson::SizeType i = 0; i < refObj.Size(); ++i) {
        std::string tmp(refObj[i].GetString());
        if (tmp.empty())
          continue;
        std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
        blocklist.emplace(tmp);
      }
    }
  } while (0);
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
class IConfigure final {
public:
  inline IConfigure();
  inline IConfigure(const std::string &cfg_buffer);
  inline ~IConfigure();

public:
  inline void operator<<(const std::string &);
  inline void operator>>(std::string &cfg_buffer) const;
  inline IConfigure(const IConfigure &);
  inline IConfigure &operator=(const IConfigure &);

public:
  id_type_t id = 0;
  bool enable = false;
  IServer server;
  IStartup startup;
  IJss jss;
  IExtensions extensions;
  IFingerprint fingerprint;
  IStorage storage;
  ICookies cookies;
  std::string version = "1.0.0";
  std::string source = R"({})";
};
inline IConfigure::IConfigure() {
}
inline IConfigure::~IConfigure() {
}
inline IConfigure::IConfigure(const IConfigure &obj) {
  *this = obj;
}
inline IConfigure &IConfigure::operator=(const IConfigure &obj) {
  id = obj.id;
  enable = obj.enable;
  source = obj.source;
  server = obj.server;
  version = obj.version;
  fingerprint = obj.fingerprint;
  startup = obj.startup;
  extensions = obj.extensions;
  cookies = obj.cookies;
  storage = obj.storage;
  jss = obj.jss;
  return *this;
}
inline IConfigure::IConfigure(const std::string &cfg_buffer) {
  *this << cfg_buffer;
}
inline void IConfigure::operator<<(const std::string &cfg_buffer) {
  do {
    if (cfg_buffer.empty())
      break;
    rapidjson::Document doc;
    if (doc.Parse(cfg_buffer.data(), cfg_buffer.size()).HasParseError())
      break;
    if (!doc.IsObject())
      break;
    source = Json::toString(doc);
    if (doc.HasMember("version") && doc["version"].IsString())
      version = doc["version"].GetString();
    if (doc.HasMember("id") && doc["id"].IsUint64())
      id = static_cast<id_type_t>(doc["id"].GetUint64());
    if (doc.HasMember("enable") && doc["enable"].IsBool())
      enable = doc["enable"].GetBool();
    if (doc.HasMember("startup"))
      startup << doc["startup"];
    if (doc.HasMember("extensions"))
      extensions << doc["extensions"];
    if (doc.HasMember("fingerprint"))
      fingerprint << doc["fingerprint"];
    if (doc.HasMember("jss"))
      jss << doc["jss"];
    if (doc.HasMember("storage"))
      storage << doc["storage"];
    if (doc.HasMember("cookies"))
      cookies << doc["cookies"];
  } while (0);
}
inline void IConfigure::operator>>(std::string &out_buffer) const {
  out_buffer = source.empty() ? "{}" : source;
  rapidjson::Document doc;
  if (doc.Parse(out_buffer.data(), out_buffer.size()).HasParseError()) {
    if (!doc.IsObject()) {
      out_buffer = "{}";
    }
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////
} // namespace cfg
} // namespace chromium
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 22 Feb 2025 13:22:06 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__8B6326C0_93E4_49D8_BFC7_EB6C3BA59694__