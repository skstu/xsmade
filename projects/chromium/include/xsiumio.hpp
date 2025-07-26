#if !defined(__5E6CBAF3_846B_4EF0_B587_0B9D7DC7F803__)
#define __5E6CBAF3_846B_4EF0_B587_0B9D7DC7F803__

#include "yunlogin/cross_project_compatibility.h"

#if COMPILE_IN_PROJECT_CHROMIUM
#include "chromium/include/rapidjson.h"
#else
#include <rapidjson.h>
#endif

namespace chromium {
namespace xsiumio {
constexpr char kObjectKey[] = "xsiumio";
constexpr char kProjectDirnameChromium[] = "Chromium";
constexpr char kProjectDirnameDefaultUserData[] = "chromium";
constexpr char kProjectDirnameComponents[] = "components";
constexpr char kProjectDirnameExtensions[] = "extensions";
constexpr char kProjectDirnameRoute[] = "route";
constexpr char kProjectDirnameTmp[] = "tmp";
constexpr char kProjectDirnameCache[] = "cache";
constexpr char kProjectDirnameLogs[] = "logs";
constexpr char kProjectDirnameConfigures[] = "configures";
constexpr char kProjectFilenameConfigure[] = "configure.json";
constexpr char kProjectFilenameTmpcfgpath[] = "cfgpath.cfg";
constexpr char kProjectFilenameStartupEnv[] = ".startup";
constexpr char kProjectFilenameChromiumProcessId[] = "chromium.pid";

constexpr char kWebRTCIPHandlingDefault[] = "default";
constexpr char kWebRTCIPHandlingDefaultPublicAndPrivateInterfaces[] =
    "default_public_and_private_interfaces";
constexpr char kWebRTCIPHandlingDefaultPublicInterfaceOnly[] =
    "default_public_interface_only";
constexpr char kWebRTCIPHandlingDisableNonProxiedUdp[] =
    "disable_non_proxied_udp";
enum class WebRTCIPHandlingPolicy {
  kDefault = 0,
  kDefaultPublicAndPrivateInterfaces = 1,
  kDefaultPublicInterfaceOnly = 2,
  kDisableNonProxiedUdp = 3,
};
class IXSiumio {
public:
  enum class ProxyType { HTTP, SOCKS4, SOCKS5, SOCKS5H };
  static bool ParseProxyCredentialsUrl(const std::string &authString,
                                       ProxyType &type, std::string &scheme,
                                       int &port, std::string &username,
                                       std::string &password,
                                       std::string &host) {
    bool result = false;
    do {
      if (authString.empty())
        break;
      std::regex re(
          R"(^(https?|socks4|socks5h?|ftp)://(?:([^:]+):([^@]+)@)?([^\:]+):(\d+)$)");
      std::smatch m;
      if (!std::regex_match(authString, m, re))
        break;
      scheme = m[1];
      username = m[2];
      password = m[3];
      host = m[4];
      std::string portStr = m[5];
      port = portStr.empty() ? 80 : std::strtol(portStr.c_str(), nullptr, 10);
      if (scheme.find("socks5h") != std::string::npos) {
        type = ProxyType::SOCKS5H;
      } else if (scheme.find("socks5") != std::string::npos) {
        type = ProxyType::SOCKS5;
      } else if (scheme.find("socks4") != std::string::npos) {
        type = ProxyType::SOCKS4;
      } else {
        type = ProxyType::HTTP;
      }
      result = true;
    } while (0);
    return result;
  }
  struct Proxy {
    ProxyType type = ProxyType::SOCKS5H;
    std::string scheme = "SOCKS5H";
    std::string username = "";
    std::string password = "";
    std::string host = "127.0.0.1";
    int port = 80;

    bool enable = false;
    std::string credentials_url;
    inline Proxy();
    inline ~Proxy();

    inline void operator<<(const rapidjson::Value &v) {
      do {
        if (!v.IsObject())
          return;
        if (v.HasMember("enable") && v["enable"].IsBool())
          enable = v["enable"].GetBool();
        if (v.HasMember("credentials_url") && v["credentials_url"].IsString()) {
          credentials_url = v["credentials_url"].GetString();
          *this << credentials_url;
        }
      } while (0);
    }
    inline void operator>>(rapidjson::Document &doc) const {
      if (!doc.IsObject())
        return;
      rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();
      rapidjson::Value obj(rapidjson::Type::kObjectType);
      RAPIDJSON_ADDMEMBER_BOOL(obj, std::string("enable"), enable, allocator);
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("credentials_url"),
                                 credentials_url, allocator);
      doc.AddMember("proxy", obj, allocator);
    }
    inline void operator<<(const std::string &authString) {
      ParseProxyCredentialsUrl(authString, type, scheme, port, username,
                               password, host);
    }
  };
  struct Jss {
  public:
    inline Jss();
    inline ~Jss();

    bool enable = false;
    std::string frameImplDidClearWindowObject;

    inline void operator>>(rapidjson::Document &doc) const {
      if (!doc.IsObject())
        return;
      rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();
      rapidjson::Value obj(rapidjson::Type::kObjectType);
      RAPIDJSON_ADDMEMBER_BOOL(obj, std::string("enable"), enable, allocator);
      RAPIDJSON_ADDMEMBER_STRING(obj,
                                 std::string("frameImplDidClearWindowObject"),
                                 frameImplDidClearWindowObject, allocator);
      doc.AddMember("jss", obj, allocator);
    }
    inline void operator<<(const rapidjson::Value &value) {
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
  };
  struct Startup {
    inline Startup();
    inline ~Startup();

    bool enable = false;
    bool enable_cleanup_udd = false;
    std::string homepage;
    std::string search_engine;
    unsigned int search_engine_id = 0;
    std::vector<std::string> urls;
    std::vector<std::string> args;
    inline void operator>>(rapidjson::Document &doc) const {
      if (!doc.IsObject())
        return;
      rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();
      rapidjson::Value obj(rapidjson::Type::kObjectType);
      RAPIDJSON_ADDMEMBER_BOOL(obj, std::string("enable"), enable, allocator);
      RAPIDJSON_ADDMEMBER_BOOL(obj, std::string("enable_cleanup_udd"),
                               enable_cleanup_udd, allocator);
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("homepage"), homepage,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("search_engine"),
                                 search_engine, allocator);
      RAPIDJSON_ADDMEMBER_UINT(obj, std::string("search_engine_id"),
                               search_engine_id, allocator);
      rapidjson::Value urlsArray(rapidjson::Type::kArrayType);
      for (const auto &url : urls) {
        if (url.empty())
          continue;
        rapidjson::Value urlValue(rapidjson::Type::kStringType);
        urlValue.SetString(url.c_str(),
                           static_cast<rapidjson::SizeType>(url.size()),
                           allocator);
        urlsArray.PushBack(urlValue, allocator);
      }
      RAPIDJSON_ADDMEMBER_OBJECT(obj, std::string("urls"), urlsArray,
                                 allocator);
      rapidjson::Value argsArray(rapidjson::Type::kArrayType);
      for (const auto &arg : args) {
        if (arg.empty())
          continue;
        rapidjson::Value argValue(rapidjson::Type::kStringType);
        argValue.SetString(arg.c_str(),
                           static_cast<rapidjson::SizeType>(arg.size()),
                           allocator);
        argsArray.PushBack(argValue, allocator);
      }
      RAPIDJSON_ADDMEMBER_OBJECT(obj, std::string("args"), argsArray,
                                 allocator);
      doc.AddMember("startup", obj, allocator);
    }
    inline void operator<<(const rapidjson::Value &value) {
      enable = false;
      homepage.clear();
      search_engine.clear();
      args.clear();
      urls.clear();
      search_engine_id = 0;
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
        if (value.HasMember("enable_cleanup_udd") &&
            value["enable_cleanup_udd"].IsBool()) {
          enable_cleanup_udd = value["enable_cleanup_udd"].GetBool();
        }
        if (value.HasMember("homepage") && value["homepage"].IsString()) {
          homepage = value["homepage"].GetString();
        }
        if (value.HasMember("search_engine") &&
            value["search_engine"].IsString()) {
          search_engine = value["search_engine"].GetString();
        }
        if (value.HasMember("search_engine_id") &&
            value["search_engine_id"].IsUint()) {
          search_engine_id = value["search_engine_id"].GetUint();
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
  };
  struct Cookies {
    inline Cookies();
    inline ~Cookies();

    bool enable = false;
    std::set<std::string> blocklist;
    inline void operator>>(rapidjson::Document &doc) const {
      if (!doc.IsObject())
        return;
      rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();
      rapidjson::Value obj(rapidjson::Type::kObjectType);
      RAPIDJSON_ADDMEMBER_BOOL(obj, std::string("enable"), enable, allocator);
      rapidjson::Value blocklistArray(rapidjson::Type::kArrayType);
      for (const auto &item : blocklist) {
        if (item.empty())
          continue;
        rapidjson::Value itemValue(rapidjson::Type::kStringType);
        itemValue.SetString(item.c_str(),
                            static_cast<rapidjson::SizeType>(item.size()),
                            allocator);
        blocklistArray.PushBack(itemValue, allocator);
      }
      RAPIDJSON_ADDMEMBER_OBJECT(obj, std::string("blocklist"), blocklistArray,
                                 allocator);
      doc.AddMember("cookies", obj, allocator);
    }
    inline void operator<<(const rapidjson::Value &value) {
      blocklist.clear();
      enable = false;
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
  };
  struct Storage {
    inline Storage();
    inline ~Storage();

    bool enable = false;
    std::set<std::string> blocklist;
    inline void operator>>(rapidjson::Document &doc) const {
      if (!doc.IsObject())
        return;
      rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();
      rapidjson::Value obj(rapidjson::Type::kObjectType);
      RAPIDJSON_ADDMEMBER_BOOL(obj, std::string("enable"), enable, allocator);
      rapidjson::Value blocklistArray(rapidjson::Type::kArrayType);
      for (const auto &item : blocklist) {
        if (item.empty())
          continue;
        rapidjson::Value itemValue(rapidjson::Type::kStringType);
        itemValue.SetString(item.c_str(),
                            static_cast<rapidjson::SizeType>(item.size()),
                            allocator);
        blocklistArray.PushBack(itemValue, allocator);
      }
      RAPIDJSON_ADDMEMBER_OBJECT(obj, std::string("blocklist"), blocklistArray,
                                 allocator);
      doc.AddMember("storage", obj, allocator);
    }
    inline void operator<<(const rapidjson::Value &value) {
      blocklist.clear();
      enable = false;
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
  };

  struct Yunlogin {
    inline Yunlogin();
    inline ~Yunlogin();
    bool enable = false;
    bool enable_finger = false;
    bool enable_extensions = false;
    bool enable_proxy = false;
    inline void operator>>(rapidjson::Document &doc) const {
      if (!doc.IsObject())
        return;
      rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();
      rapidjson::Value obj(rapidjson::Type::kObjectType);
      RAPIDJSON_ADDMEMBER_BOOL(obj, std::string("enable"), enable, allocator);
      RAPIDJSON_ADDMEMBER_BOOL(obj, std::string("enable_finger"), enable_finger,
                               allocator);
      RAPIDJSON_ADDMEMBER_BOOL(obj, std::string("enable_extensions"),
                               enable_extensions, allocator);
      RAPIDJSON_ADDMEMBER_BOOL(obj, std::string("enable_proxy"), enable_proxy,
                               allocator);
      doc.AddMember("yunlogin", obj, allocator);
    }
    void operator<<(const rapidjson::Value &value) {
      do {
        if (!value.IsObject())
          break;
        if (value.HasMember("enable") && value["enable"].IsBool())
          enable = value["enable"].GetBool();
        if (value.HasMember("enable_finger") && value["enable_finger"].IsBool())
          enable_finger = value["enable_finger"].GetBool();
        if (value.HasMember("enable_extensions") &&
            value["enable_extensions"].IsBool())
          enable_extensions = value["enable_extensions"].GetBool();
        if (value.HasMember("enable_proxy") && value["enable_proxy"].IsBool())
          enable_proxy = value["enable_proxy"].GetBool();
      } while (0);
    }
  };

  struct MyIp_yunlogin_com {
    inline MyIp_yunlogin_com();
    inline ~MyIp_yunlogin_com();

    std::string Continent;
    std::string ContinentEn;
    std::string Country;
    std::string CountryEnglish;
    std::string CountryCode;
    std::string Province;
    std::string ProvinceEn;
    std::string City;
    std::string CityEn;
    std::string District;
    std::string AreaCode;
    std::string ISP;
    std::string Longitude;
    std::string Latitude;
    std::string LocalTime;
    std::string Elevation;
    std::string WeatherStation;
    std::string ZipCode;
    std::string CityCode;
    std::string Asn;
    std::string Ip;
    std::string db;

    inline const std::string &GetTimeZoneID() const {
      return LocalTime;
    }
    inline const std::string &GetIP() const {
      return Ip;
    }
    inline void operator>>(rapidjson::Document &doc) const {
      if (!doc.IsObject())
        return;
      rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();
      rapidjson::Value obj(rapidjson::Type::kObjectType);
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("Continent"), Continent,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("ContinentEn"), ContinentEn,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("Country"), Country,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("CountryEnglish"),
                                 CountryEnglish, allocator);
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("CountryCode"), CountryCode,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("Province"), Province,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("ProvinceEn"), ProvinceEn,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("City"), City, allocator);
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("CityEn"), CityEn, allocator);
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("District"), District,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("AreaCode"), AreaCode,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("ISP"), ISP, allocator);
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("Longitude"), Longitude,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("Latitude"), Latitude,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("LocalTime"), LocalTime,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("Elevation"), Elevation,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("WeatherStation"),
                                 WeatherStation, allocator);
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("ZipCode"), ZipCode,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("CityCode"), CityCode,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("Asn"), Asn, allocator);
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("Ip"), Ip, allocator);
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("db"), db, allocator);
      doc.AddMember("myipyunlogincom", obj, allocator);
    }
    void operator<<(const rapidjson::Value &v) {
      do {
        if (!v.IsObject())
          break;
        if (v.HasMember("Continent") && v["Continent"].IsString())
          Continent = v["Continent"].GetString();
        if (v.HasMember("ContinentEn") && v["ContinentEn"].IsString())
          ContinentEn = v["ContinentEn"].GetString();
        if (v.HasMember("Country") && v["Country"].IsString())
          Country = v["Country"].GetString();
        if (v.HasMember("CountryEnglish") && v["CountryEnglish"].IsString())
          CountryEnglish = v["CountryEnglish"].GetString();
        if (v.HasMember("CountryCode") && v["CountryCode"].IsString())
          CountryCode = v["CountryCode"].GetString();
        if (v.HasMember("Province") && v["Province"].IsString())
          Province = v["Province"].GetString();
        if (v.HasMember("ProvinceEn") && v["ProvinceEn"].IsString())
          ProvinceEn = v["ProvinceEn"].GetString();
        if (v.HasMember("City") && v["City"].IsString())
          City = v["City"].GetString();
        if (v.HasMember("CityEn") && v["CityEn"].IsString())
          CityEn = v["CityEn"].GetString();
        if (v.HasMember("District") && v["District"].IsString())
          District = v["District"].GetString();
        if (v.HasMember("AreaCode") && v["AreaCode"].IsString())
          AreaCode = v["AreaCode"].GetString();
        if (v.HasMember("ISP") && v["ISP"].IsString())
          ISP = v["ISP"].GetString();
        if (v.HasMember("Longitude") && v["Longitude"].IsString())
          Longitude = v["Longitude"].GetString();
        if (v.HasMember("Latitude") && v["Latitude"].IsString())
          Latitude = v["Latitude"].GetString();
        if (v.HasMember("LocalTime") && v["LocalTime"].IsString())
          LocalTime = v["LocalTime"].GetString();
        if (v.HasMember("Elevation") && v["Elevation"].IsString())
          Elevation = v["Elevation"].GetString();
        if (v.HasMember("WeatherStation") && v["WeatherStation"].IsString())
          WeatherStation = v["WeatherStation"].GetString();
        if (v.HasMember("ZipCode") && v["ZipCode"].IsString())
          ZipCode = v["ZipCode"].GetString();
        if (v.HasMember("CityCode") && v["CityCode"].IsString())
          CityCode = v["CityCode"].GetString();
        if (v.HasMember("Asn") && v["Asn"].IsString())
          Asn = v["Asn"].GetString();
        if (v.HasMember("Ip") && v["Ip"].IsString())
          Ip = v["Ip"].GetString();
        if (v.HasMember("db") && v["db"].IsString())
          db = v["db"].GetString();
      } while (0);
    }
  };

  struct WebRTCIPHandling {
    inline WebRTCIPHandling();
    inline ~WebRTCIPHandling();

    WebRTCIPHandlingPolicy policy =
        WebRTCIPHandlingPolicy::kDefaultPublicInterfaceOnly;

    std::string public_ip;   //!@ Public IP, can be empty
    std::string internal_ip; //!@ Internal network IP
    int port = 0;            //!@ Port, default is 0
    inline void operator>>(rapidjson::Document &doc) const {
      if (!doc.IsObject())
        return;
      rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();
      rapidjson::Value obj(rapidjson::Type::kObjectType);
      std::string policyStr;
      switch (policy) {
      case WebRTCIPHandlingPolicy::kDefault:
        policyStr = kWebRTCIPHandlingDefault;
        break;
      case WebRTCIPHandlingPolicy::kDefaultPublicAndPrivateInterfaces:
        policyStr = kWebRTCIPHandlingDefaultPublicAndPrivateInterfaces;
        break;
      case WebRTCIPHandlingPolicy::kDefaultPublicInterfaceOnly:
        policyStr = kWebRTCIPHandlingDefaultPublicInterfaceOnly;
        break;
      case WebRTCIPHandlingPolicy::kDisableNonProxiedUdp:
        policyStr = kWebRTCIPHandlingDisableNonProxiedUdp;
        break;
      }
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("policy"), policyStr,
                                 allocator);
      RAPIDJSON_ADDMEMBER_INT(obj, std::string("port"), port, allocator);
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("public_ip"), public_ip,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(obj, std::string("internal_ip"), internal_ip,
                                 allocator);
      doc.AddMember("webrtcIPHandling", obj, allocator);
    }
    inline void operator<<(const rapidjson::Value &value) {
      do {
        if (!value.IsObject())
          break;
        if (value.HasMember("policy") && value["policy"].IsString()) {
          std::string policyStr = value["policy"].GetString();
          if (policyStr == kWebRTCIPHandlingDefault) {
            policy = WebRTCIPHandlingPolicy::kDefault;
          } else if (policyStr ==
                     kWebRTCIPHandlingDefaultPublicAndPrivateInterfaces) {
            policy = WebRTCIPHandlingPolicy::kDefaultPublicAndPrivateInterfaces;
          } else if (policyStr == kWebRTCIPHandlingDefaultPublicInterfaceOnly) {
            policy = WebRTCIPHandlingPolicy::kDefaultPublicInterfaceOnly;
          } else if (policyStr == kWebRTCIPHandlingDisableNonProxiedUdp) {
            policy = WebRTCIPHandlingPolicy::kDisableNonProxiedUdp;
          }
        }
        if (value.HasMember("port") && value["port"].IsInt()) {
          port = value["port"].GetInt();
        }
        if (value.HasMember("public_ip") && value["public_ip"].IsString()) {
          public_ip = value["public_ip"].GetString();
        }
        if (value.HasMember("internal_ip") && value["internal_ip"].IsString()) {
          internal_ip = value["internal_ip"].GetString();
        }
      } while (0);
    }
  };

  struct Fingerprint {
    struct Hash {
      inline Hash();
      inline ~Hash();

      bool random = false;
      double base = 0.0;
      double from = 0.0;
      double to = 0.0;

      inline void operator>>(rapidjson::Document &doc) const {
        if (!doc.IsObject())
          return;
        auto &allocator = doc.GetAllocator();
        rapidjson::Value obj(rapidjson::Type::kObjectType);
        RAPIDJSON_ADDMEMBER_BOOL(obj, std::string("random"), random, allocator);
        RAPIDJSON_ADDMEMBER_DOUBLE(obj, std::string("base"), base, allocator);
        RAPIDJSON_ADDMEMBER_DOUBLE(obj, std::string("from"), from, allocator);
        RAPIDJSON_ADDMEMBER_DOUBLE(obj, std::string("to"), to, allocator);
        doc.AddMember("hash", obj, allocator);
      }
      inline void operator<<(const rapidjson::Value &v) {
        do {
          if (!v.IsObject())
            break;
          if (v.HasMember("random") && v["random"].IsBool()) {
            random = v["random"].GetBool();
          }
          if (v.HasMember("base") && v["base"].IsDouble()) {
            base = v["base"].GetDouble();
          }
          if (v.HasMember("from") && v["from"].IsDouble()) {
            from = v["from"].GetDouble();
          }
          if (v.HasMember("to") && v["to"].IsDouble()) {
            to = v["to"].GetDouble();
          }
        } while (0);
      }
    };
    struct Screen {
      inline Screen();
      inline ~Screen();

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

      void operator>>(rapidjson::Document &doc) const {
        if (!doc.IsObject())
          return;
        rapidjson::Document tmpDoc(rapidjson::Type::kObjectType);
        auto &allocHash = tmpDoc.GetAllocator();
        RAPIDJSON_ADDMEMBER_BOOL(tmpDoc, std::string("enable"), enable,
                                 allocHash);
        RAPIDJSON_ADDMEMBER_INT(tmpDoc, std::string("height"), height,
                                allocHash);
        RAPIDJSON_ADDMEMBER_INT(tmpDoc, std::string("width"), width, allocHash);
        RAPIDJSON_ADDMEMBER_INT(tmpDoc, std::string("colorDepth"), colorDepth,
                                allocHash);
        RAPIDJSON_ADDMEMBER_INT(tmpDoc, std::string("pixelDepth"), pixelDepth,
                                allocHash);
        RAPIDJSON_ADDMEMBER_INT(tmpDoc, std::string("availLeft"), availLeft,
                                allocHash);
        RAPIDJSON_ADDMEMBER_INT(tmpDoc, std::string("availTop"), availTop,
                                allocHash);
        RAPIDJSON_ADDMEMBER_INT(tmpDoc, std::string("availHeight"), availHeight,
                                allocHash);
        RAPIDJSON_ADDMEMBER_INT(tmpDoc, std::string("availWidth"), availWidth,
                                allocHash);
        RAPIDJSON_ADDMEMBER_DOUBLE(tmpDoc, std::string("devicePixelRatio"),
                                   devicePixelRatio, allocHash);

        rapidjson::Value tmpValue(tmpDoc, doc.GetAllocator());
        doc.AddMember(rapidjson::Value("screen", doc.GetAllocator()).Move(),
                      tmpValue, doc.GetAllocator());
      }
      void operator<<(const rapidjson::Value &v) {
        if (!v.IsObject())
          return;
        if (v.HasMember("height") && v["height"].IsInt()) {
          height = v["height"].GetInt();
        }
        if (v.HasMember("width") && v["width"].IsInt()) {
          width = v["width"].GetInt();
        }
        if (v.HasMember("colorDepth") && v["colorDepth"].IsInt()) {
          colorDepth = v["colorDepth"].GetInt();
        }
        if (v.HasMember("pixelDepth") && v["pixelDepth"].IsInt()) {
          pixelDepth = v["pixelDepth"].GetInt();
        }
        if (v.HasMember("availLeft") && v["availLeft"].IsInt()) {
          availLeft = v["availLeft"].GetInt();
        }
        if (v.HasMember("availTop") && v["availTop"].IsInt()) {
          availTop = v["availTop"].GetInt();
        }
        if (v.HasMember("availHeight") && v["availHeight"].IsInt()) {
          availHeight = v["availHeight"].GetInt();
        }
        if (v.HasMember("availWidth") && v["availWidth"].IsInt()) {
          availWidth = v["availWidth"].GetInt();
        }
        if (v.HasMember("devicePixelRatio") &&
            v["devicePixelRatio"].IsDouble()) {
          devicePixelRatio = v["devicePixelRatio"].GetDouble();
        }
        if (v.HasMember("enable") && v["enable"].IsBool()) {
          enable = v["enable"].GetBool();
        }
      }
    };
    struct TimeZone {
      inline TimeZone();
      inline ~TimeZone();

      std::string id;
      std::string label;
      int offset = 0;

      inline void operator>>(rapidjson::Document &doc) const {
        if (!doc.IsObject())
          return;
        auto &allocator = doc.GetAllocator();
        rapidjson::Value obj(rapidjson::Type::kObjectType);
        RAPIDJSON_ADDMEMBER_STRING(obj, std::string("id"), id, allocator);
        RAPIDJSON_ADDMEMBER_STRING(obj, std::string("label"), label, allocator);
        RAPIDJSON_ADDMEMBER_INT(obj, std::string("offset"), offset, allocator);
        doc.AddMember("timezone", obj, allocator);
      }
      inline void operator<<(const rapidjson::Value &value) {
        do {
          if (!value.IsObject())
            break;
          if (value.HasMember("id") && value["id"].IsString()) {
            id = value["id"].GetString();
          }
          if (value.HasMember("label") && value["label"].IsString()) {
            label = value["label"].GetString();
          }
          if (value.HasMember("offset") && value["offset"].IsInt()) {
            offset = value["offset"].GetInt();
          }
        } while (0);
      }
    };
    struct Math {
      inline Math();
      inline ~Math();

      bool enable = false;
      Hash hash;
      void operator>>(rapidjson::Document &doc) const {
        if (!doc.IsObject())
          return;
        rapidjson::Document tmpDoc(rapidjson::Type::kObjectType);
        auto &allocHash = tmpDoc.GetAllocator();
        RAPIDJSON_ADDMEMBER_BOOL(tmpDoc, std::string("enable"), enable,
                                 allocHash);
        hash >> tmpDoc;

        rapidjson::Value tmpValue(tmpDoc, doc.GetAllocator());
        doc.AddMember(rapidjson::Value("math", doc.GetAllocator()).Move(),
                      tmpValue, doc.GetAllocator());
      }
      void operator<<(const rapidjson::Value &v) {
        if (!v.IsObject())
          return;
        if (v.HasMember("enable") && v["enable"].IsBool()) {
          enable = v["enable"].GetBool();
        }
        hash << v["hash"];
      }
    };
    struct Canvas {
      inline Canvas();
      inline ~Canvas();

      bool enable = false;
      Hash hash;
      inline void operator>>(rapidjson::Document &doc) const {
        if (!doc.IsObject())
          return;
        rapidjson::Document tmpDoc(rapidjson::Type::kObjectType);
        auto &allocHash = tmpDoc.GetAllocator();
        RAPIDJSON_ADDMEMBER_BOOL(tmpDoc, std::string("enable"), enable,
                                 allocHash);
        hash >> tmpDoc;
        rapidjson::Value tmpValue(tmpDoc, doc.GetAllocator());
        doc.AddMember(rapidjson::Value("canvas", doc.GetAllocator()).Move(),
                      tmpValue, doc.GetAllocator());
      }
      inline void operator<<(const rapidjson::Value &v) {
        if (!v.IsObject())
          return;
        if (v.HasMember("enable") && v["enable"].IsBool()) {
          enable = v["enable"].GetBool();
        }
        hash << v["hash"];
      }
    };
    struct Audio {
      inline Audio();
      inline ~Audio();

      bool enable = false;
      Hash hash;
      inline void operator>>(rapidjson::Document &doc) const {
        if (!doc.IsObject())
          return;
        rapidjson::Document tmpDoc(rapidjson::Type::kObjectType);
        auto &allocHash = tmpDoc.GetAllocator();
        RAPIDJSON_ADDMEMBER_BOOL(tmpDoc, std::string("enable"), enable,
                                 allocHash);
        hash >> tmpDoc;

        rapidjson::Value tmpValue(tmpDoc, doc.GetAllocator());
        doc.AddMember(rapidjson::Value("audio", doc.GetAllocator()).Move(),
                      tmpValue, doc.GetAllocator());
      }
      inline void operator<<(const rapidjson::Value &v) {
        if (!v.IsObject())
          return;
        if (v.HasMember("enable") && v["enable"].IsBool()) {
          enable = v["enable"].GetBool();
        }
        hash << v["hash"];
      }
    };
    struct Webgl {
      inline Webgl();
      inline ~Webgl();

      bool enable = false;
      Hash hash;
      std::map<int, std::string> getParameter;
      inline void operator>>(rapidjson::Document &doc) const {
        if (!doc.IsObject())
          return;
        rapidjson::Document tmpDoc(rapidjson::Type::kObjectType);
        auto &allocHash = tmpDoc.GetAllocator();
        RAPIDJSON_ADDMEMBER_BOOL(tmpDoc, std::string("enable"), enable,
                                 allocHash);
        hash >> tmpDoc;

        rapidjson::Value getParameterObj(rapidjson::Type::kObjectType);
        for (const auto &item : getParameter) {
          if (item.second.empty())
            continue;
          rapidjson::Value keyValue(rapidjson::Type::kStringType);
          keyValue.SetString(std::to_string(item.first).c_str(),
                             static_cast<rapidjson::SizeType>(
                                 std::to_string(item.first).size()),
                             allocHash);
          rapidjson::Value valueValue(rapidjson::Type::kStringType);
          valueValue.SetString(
              item.second.c_str(),
              static_cast<rapidjson::SizeType>(item.second.size()), allocHash);
          getParameterObj.AddMember(keyValue, valueValue, allocHash);
        }
        RAPIDJSON_ADDMEMBER_OBJECT(tmpDoc, std::string("getParameter"),
                                   getParameterObj, allocHash);
        rapidjson::Value tmpValue(tmpDoc, doc.GetAllocator());
        doc.AddMember(rapidjson::Value("webgl", doc.GetAllocator()).Move(),
                      tmpValue, doc.GetAllocator());
      }
      inline void operator<<(const rapidjson::Value &v) {
        if (!v.IsObject())
          return;
        if (v.HasMember("enable") && v["enable"].IsBool()) {
          enable = v["enable"].GetBool();
        }
        hash << v["hash"];
        getParameter.clear();
        if (v.HasMember("getParameter") && v["getParameter"].IsObject()) {
          const rapidjson::Value &refObj = v["getParameter"];
          for (auto itr = refObj.MemberBegin(); itr != refObj.MemberEnd();
               ++itr) {
            if (!itr->value.IsString())
              continue;
            if (itr->name.GetStringLength() <= 0)
              continue;
            int key = strtol(itr->name.GetString(), nullptr, 10);
            std::string value = itr->value.GetString();
            getParameter[key] = value;
          }
        }
      }
    };

    struct Font {
      inline Font();
      inline ~Font();

      bool enable = false;
      Hash hash;
      std::set<std::string> allowlist;
      inline void operator>>(rapidjson::Document &doc) const {
        if (!doc.IsObject())
          return;
        rapidjson::Document tmpDoc(rapidjson::Type::kObjectType);
        auto &allocHash = tmpDoc.GetAllocator();
        RAPIDJSON_ADDMEMBER_BOOL(tmpDoc, std::string("enable"), enable,
                                 allocHash);
        hash >> tmpDoc;

        rapidjson::Value allowlistArray(rapidjson::Type::kArrayType);
        for (const auto &item : allowlist) {
          if (item.empty())
            continue;
          rapidjson::Value itemValue(rapidjson::Type::kStringType);
          itemValue.SetString(item.c_str(),
                              static_cast<rapidjson::SizeType>(item.size()),
                              allocHash);
          allowlistArray.PushBack(itemValue, allocHash);
        }
        RAPIDJSON_ADDMEMBER_OBJECT(tmpDoc, std::string("allowlist"),
                                   allowlistArray, allocHash);

        rapidjson::Value tmpValue(tmpDoc, doc.GetAllocator());
        doc.AddMember(rapidjson::Value("font", doc.GetAllocator()).Move(),
                      tmpValue, doc.GetAllocator());
      }
      inline void operator<<(const rapidjson::Value &v) {
        if (!v.IsObject())
          return;
        if (v.HasMember("enable") && v["enable"].IsBool()) {
          enable = v["enable"].GetBool();
        }
        hash << v["hash"];
        allowlist.clear();
        if (v.HasMember("allowlist") && v["allowlist"].IsArray()) {
          const rapidjson::Value &refObj = v["allowlist"];
          for (rapidjson::SizeType i = 0; i < refObj.Size(); ++i) {
            if (!refObj[i].IsString())
              break;
            std::string tmp(refObj[i].GetString());
            if (tmp.empty())
              continue;
            std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
            allowlist.emplace(tmp);
          }
        }
      }
    };
    inline Fingerprint();
    inline ~Fingerprint();

    bool enable = false;

    std::string do_not_track = "1";
    std::string platform = "Win32";
    int hardwareConcurrency = 8;
    int deviceMemory = 16;
    std::string userAgent =
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, "
        "like Gecko) Chrome/138.0.0.0 Safari/537.36";
    std::vector<std::string> languages = {
        "en-US", "en"}; //!@ Language list, default is ["en-US", "en"]
    std::string acceptLanguage =
        "en-US,en;q=0.9,en;q=0.8"; //!@ Accept-Language header
    Canvas canvas;
    Webgl webgl;
    Audio audio;
    Math math;
    Font font;
    Screen screen;
    TimeZone timezone;
    inline void operator>>(rapidjson::Document &doc) const {
      if (!doc.IsObject())
        return;
      rapidjson::Document fpsDoc(rapidjson::kObjectType);
      auto &fpsAllocator = fpsDoc.GetAllocator();
      RAPIDJSON_ADDMEMBER_BOOL(fpsDoc, std::string("enable"), enable,
                               fpsAllocator);
      RAPIDJSON_ADDMEMBER_STRING(fpsDoc, std::string("do_not_track"),
                                 do_not_track, fpsAllocator);
      RAPIDJSON_ADDMEMBER_STRING(fpsDoc, std::string("platform"), platform,
                                 fpsAllocator);
      RAPIDJSON_ADDMEMBER_INT(fpsDoc, std::string("hardwareConcurrency"),
                              hardwareConcurrency, fpsAllocator);
      RAPIDJSON_ADDMEMBER_INT(fpsDoc, std::string("deviceMemory"), deviceMemory,
                              fpsAllocator);
      RAPIDJSON_ADDMEMBER_STRING(fpsDoc, std::string("userAgent"), userAgent,
                                 fpsAllocator);
      canvas >> fpsDoc;
      webgl >> fpsDoc;
      audio >> fpsDoc;
      math >> fpsDoc;
      font >> fpsDoc;
      timezone >> fpsDoc;
      screen >> fpsDoc;
      rapidjson::Value fpsValue(fpsDoc, doc.GetAllocator());
      doc.AddMember(rapidjson::Value("fingerprint", doc.GetAllocator()).Move(),
                    fpsValue, doc.GetAllocator());
    }
    inline void operator<<(const rapidjson::Value &v) {
      if (!v.IsObject())
        return;
      if (v.HasMember("enable") && v["enable"].IsBool()) {
        enable = v["enable"].GetBool();
      }
      if (v.HasMember("do_not_track") && v["do_not_track"].IsString()) {
        do_not_track = v["do_not_track"].GetString();
      }
      if (v.HasMember("platform") && v["platform"].IsString()) {
        platform = v["platform"].GetString();
      }
      if (v.HasMember("hardwareConcurrency") &&
          v["hardwareConcurrency"].IsInt()) {
        hardwareConcurrency = v["hardwareConcurrency"].GetInt();
      }
      if (v.HasMember("deviceMemory") && v["deviceMemory"].IsInt()) {
        deviceMemory = v["deviceMemory"].GetInt();
      }
      if (v.HasMember("userAgent") && v["userAgent"].IsString()) {
        userAgent = v["userAgent"].GetString();
      }
      if (v.HasMember("screen") && v["screen"].IsObject()) {
        screen << v["screen"];
      }
      if (v.HasMember("languages") && v["languages"].IsArray()) {
        languages.clear();
        const rapidjson::Value &refObj = v["languages"];
        for (rapidjson::SizeType i = 0; i < refObj.Size(); ++i) {
          if (!refObj[i].IsString())
            break;
          std::string tmp(refObj[i].GetString());
          if (tmp.empty())
            continue;
          languages.emplace_back(tmp);
        }
      }
      if (v.HasMember("acceptLanguage") && v["acceptLanguage"].IsString()) {
        acceptLanguage = v["acceptLanguage"].GetString();
      }
      if (v.HasMember("canvas") && v["canvas"].IsObject()) {
        canvas << v["canvas"];
      }
      if (v.HasMember("webgl") && v["webgl"].IsObject()) {
        webgl << v["webgl"];
      }
      if (v.HasMember("audio") && v["audio"].IsObject()) {
        audio << v["audio"];
      }
      if (v.HasMember("math") && v["math"].IsObject()) {
        math << v["math"];
      }
      if (v.HasMember("font") && v["font"].IsObject()) {
        font << v["font"];
      }
      if (v.HasMember("timezone") && v["timezone"].IsObject()) {
        timezone << v["timezone"];
      }
    }
  };
  struct Extensions {
    inline Extensions();
    inline ~Extensions();

    bool enable = false;
    std::set<std::string> allowlist;
    inline void operator>>(rapidjson::Document &doc) const {
      if (!doc.IsObject())
        return;
      rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();
      rapidjson::Value obj(rapidjson::Type::kObjectType);
      RAPIDJSON_ADDMEMBER_BOOL(obj, std::string("enable"), enable, allocator);
      rapidjson::Value allowlistArray(rapidjson::Type::kArrayType);
      for (const auto &item : allowlist) {
        if (item.empty())
          continue;
        rapidjson::Value itemValue(rapidjson::Type::kStringType);
        itemValue.SetString(item.c_str(),
                            static_cast<rapidjson::SizeType>(item.size()),
                            allocator);
        allowlistArray.PushBack(itemValue, allocator);
      }
      RAPIDJSON_ADDMEMBER_OBJECT(obj, std::string("allowlist"), allowlistArray,
                                 allocator);
      doc.AddMember("extensions", obj, allocator);
    }
    inline void operator<<(const rapidjson::Value &v) {
      allowlist.clear();
      enable = false;
      do {
        if (!v.IsObject())
          break;
        if (v.HasMember("enable") && v["enable"].IsBool()) {
          enable = v["enable"].GetBool();
        }
        if (v.HasMember("allowlist") && v["allowlist"].IsArray()) {
          const rapidjson::Value &refObj = v["allowlist"];
          for (rapidjson::SizeType i = 0; i < refObj.Size(); ++i) {
            if (!refObj[i].IsString())
              break;
            std::string tmp(refObj[i].GetString());
            if (tmp.empty())
              continue;
            std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
            allowlist.emplace(tmp);
          }
        }
      } while (0);
    }
  };

public:
  inline void operator>>(rapidjson::Document &doc) const;
  inline void operator<<(const rapidjson::Value &v);

public:
  inline IXSiumio();
  inline ~IXSiumio();

  bool enable = false; //!@ Main switch for the browser, default is true
  bool enable_proxy_info_sync =
      false; //!@ Enable proxy data synchronization, default is false
  bool navigatorWebdriver =
      false; //!@ blink navigator.webdriver, default is false
  unsigned long long timestamp =
      0; //!@ Timestamp, default is 0, used for synchronization
  unsigned long long identify =
      0; //!@ Unique identifier, default is 0, used for synchronization
  Yunlogin yunlogin;
  std::string proxy_info_request_url;
  Cookies cookies;
  Storage storage;
  Jss jss;
  Startup startup;
  Extensions extensions;
  Fingerprint fps; //!@ Fingerprint settings, default is empty
  Proxy proxy;     //!@ Proxy information, default is empty
  WebRTCIPHandling webrtcIPHandling;
  MyIp_yunlogin_com myipyunlogincom;
};
inline IXSiumio::IXSiumio() {
}
inline IXSiumio::~IXSiumio() {
}
inline void IXSiumio::operator<<(const rapidjson::Value &v) {
  if (!v.IsObject())
    return;
  if (v.HasMember("enable") && v["enable"].IsBool()) {
    enable = v["enable"].GetBool();
  }
  if (v.HasMember("timestamp") && v["timestamp"].IsUint64()) {
    timestamp = v["timestamp"].GetUint64();
  }
  if (v.HasMember("identify") && v["identify"].IsUint64()) {
    identify = v["identify"].GetUint64();
  }
  if (v.HasMember("myipyunlogincom") && v["myipyunlogincom"].IsObject()) {
    myipyunlogincom << v["myipyunlogincom"];
  }
  if (v.HasMember("cookies") && v["cookies"].IsObject()) {
    cookies << v["cookies"];
  }
  if (v.HasMember("storage") && v["storage"].IsObject()) {
    storage << v["storage"];
  }
  if (v.HasMember("jss") && v["jss"].IsObject()) {
    jss << v["jss"];
  }
  if (v.HasMember("startup") && v["startup"].IsObject()) {
    startup << v["startup"];
  }
  if (v.HasMember("yunlogin") && v["yunlogin"].IsObject()) {
    yunlogin << v["yunlogin"];
  }
  if (v.HasMember("webrtcIPHandling") && v["webrtcIPHandling"].IsObject()) {
    webrtcIPHandling << v["webrtcIPHandling"];
  }
  if (v.HasMember("enable_proxy_info_sync") &&
      v["enable_proxy_info_sync"].IsBool()) {
    enable_proxy_info_sync = v["enable_proxy_info_sync"].GetBool();
  }
  if (v.HasMember("proxy_info_request_url") &&
      v["proxy_info_request_url"].IsString()) {
    proxy_info_request_url = v["proxy_info_request_url"].GetString();
  }
  if (v.HasMember("proxy") && v["proxy"].IsObject()) {
    proxy << v["proxy"];
  }
  if (v.HasMember("fingerprint") && v["fingerprint"].IsObject()) {
    fps << v["fingerprint"];
  }
  if (v.HasMember("extensions") && v["extensions"].IsObject()) {
    extensions << v["extensions"];
  }
}
inline void IXSiumio::operator>>(rapidjson::Document &doc) const {
  if (!doc.IsObject())
    return;
  auto &allocator = doc.GetAllocator();
  if (doc.HasMember(kObjectKey))
    doc.RemoveMember(kObjectKey);

  rapidjson::Document xsiumioDoc(rapidjson::kObjectType);
  xsiumioDoc.SetObject();
  auto &xsiumioAllocator = xsiumioDoc.GetAllocator();
  RAPIDJSON_ADDMEMBER_BOOL(xsiumioDoc, std::string("enable"), enable,
                           xsiumioAllocator);
  RAPIDJSON_ADDMEMBER_BOOL(xsiumioDoc, std::string("navigatorWebdriver"),
                           navigatorWebdriver, xsiumioAllocator);
  RAPIDJSON_ADDMEMBER_BOOL(xsiumioDoc, std::string("enable_proxy_info_sync"),
                           enable_proxy_info_sync, xsiumioAllocator);
  RAPIDJSON_ADDMEMBER_UINT64(xsiumioDoc, std::string("timestamp"), timestamp,
                             xsiumioAllocator);
  RAPIDJSON_ADDMEMBER_UINT64(xsiumioDoc, std::string("identify"), identify,
                             xsiumioAllocator);
  proxy >> xsiumioDoc;
  cookies >> xsiumioDoc;
  storage >> xsiumioDoc;
  jss >> xsiumioDoc;
  startup >> xsiumioDoc;
  fps >> xsiumioDoc;
  extensions >> xsiumioDoc;
  webrtcIPHandling >> xsiumioDoc;
  myipyunlogincom >> xsiumioDoc;
  RAPIDJSON_ADDMEMBER_STRING(xsiumioDoc, std::string("proxy_info_request_url"),
                             proxy_info_request_url, xsiumioAllocator);
  yunlogin >> xsiumioDoc;
  rapidjson::Value xsiumioValue(xsiumioDoc, allocator);
  doc.AddMember(rapidjson::Value(kObjectKey, allocator).Move(), xsiumioValue,
                allocator);
}
inline IXSiumio::MyIp_yunlogin_com::MyIp_yunlogin_com() = default;
inline IXSiumio::MyIp_yunlogin_com::~MyIp_yunlogin_com() = default;
inline IXSiumio::Cookies::Cookies() = default;
inline IXSiumio::Cookies::~Cookies() = default;
inline IXSiumio::Storage::Storage() = default;
inline IXSiumio::Storage::~Storage() = default;
inline IXSiumio::Startup::Startup() = default;
inline IXSiumio::Startup::~Startup() = default;
inline IXSiumio::Jss::Jss() = default;
inline IXSiumio::Jss::~Jss() = default;
inline IXSiumio::Yunlogin::Yunlogin() = default;
inline IXSiumio::Yunlogin::~Yunlogin() = default;
inline IXSiumio::WebRTCIPHandling::WebRTCIPHandling() = default;
inline IXSiumio::WebRTCIPHandling::~WebRTCIPHandling() = default;
inline IXSiumio::Proxy::Proxy() = default;
inline IXSiumio::Proxy::~Proxy() = default;
inline IXSiumio::Extensions::Extensions() = default;
inline IXSiumio::Extensions::~Extensions() = default;
inline IXSiumio::Fingerprint::Fingerprint() = default;
inline IXSiumio::Fingerprint::~Fingerprint() = default;
inline IXSiumio::Fingerprint::Hash::Hash() = default;
inline IXSiumio::Fingerprint::Hash::~Hash() = default;
inline IXSiumio::Fingerprint::Math::Math() = default;
inline IXSiumio::Fingerprint::Math::~Math() = default;
inline IXSiumio::Fingerprint::Canvas::Canvas() = default;
inline IXSiumio::Fingerprint::Canvas::~Canvas() = default;
inline IXSiumio::Fingerprint::Audio::Audio() = default;
inline IXSiumio::Fingerprint::Audio::~Audio() = default;
inline IXSiumio::Fingerprint::Webgl::Webgl() = default;
inline IXSiumio::Fingerprint::Webgl::~Webgl() = default;
inline IXSiumio::Fingerprint::Font::Font() = default;
inline IXSiumio::Fingerprint::Font::~Font() = default;
inline IXSiumio::Fingerprint::TimeZone::TimeZone() = default;
inline IXSiumio::Fingerprint::TimeZone::~TimeZone() = default;
inline IXSiumio::Fingerprint::Screen::Screen() = default;
inline IXSiumio::Fingerprint::Screen::~Screen() = default;
} // namespace xsiumio
} // namespace chromium
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 19 Jul 2025 21:20:54 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__5E6CBAF3_846B_4EF0_B587_0B9D7DC7F803__