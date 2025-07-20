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

public:
  inline void operator>>(rapidjson::Document &doc) const;
  inline void operator<<(const rapidjson::Value &v);

public:
  inline IXSiumio();
  inline ~IXSiumio();

  bool enable = false; //!@ Main switch for the browser, default is true
  bool navigatorWebdriver =
      false; //!@ blink navigator.webdriver, default is false
  Yunlogin yunlogin;
  MyIp_yunlogin_com myipyunlogincom;
  Cookies cookies;
  Storage storage;
  Jss jss;
  Startup startup;
  WebRTCIPHandling webrtcIPHandling;
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
  yunlogin >> xsiumioDoc;
  myipyunlogincom >> xsiumioDoc;
  cookies >> xsiumioDoc;
  storage >> xsiumioDoc;
  jss >> xsiumioDoc;
  startup >> xsiumioDoc;
  webrtcIPHandling >> xsiumioDoc;
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

} // namespace xsiumio
} // namespace chromium
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 19 Jul 2025 21:20:54 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__5E6CBAF3_846B_4EF0_B587_0B9D7DC7F803__