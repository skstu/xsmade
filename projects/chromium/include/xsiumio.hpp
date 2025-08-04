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
constexpr char kProjectDirnameFpsdb[] = "fpsdb";
constexpr char kProjectDirnameDeviceOutput[] = "devices";
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
      struct Dpi {
        inline Dpi();
        inline ~Dpi();

        int x = 96; //!@ Default DPI for X axis
        int y = 96; //!@ Default DPI for Y axis

        void operator>>(rapidjson::Document &doc) const {
          if (!doc.IsObject())
            return;
          rapidjson::Document tmpDoc(rapidjson::Type::kObjectType);
          auto &allocHash = tmpDoc.GetAllocator();
          RAPIDJSON_ADDMEMBER_INT(tmpDoc, std::string("x"), x, allocHash);
          RAPIDJSON_ADDMEMBER_INT(tmpDoc, std::string("y"), y, allocHash);
          rapidjson::Value tmpValue(tmpDoc, doc.GetAllocator());
          doc.AddMember(rapidjson::Value("dpi", doc.GetAllocator()).Move(),
                        tmpValue, doc.GetAllocator());
        }
        void operator<<(const rapidjson::Value &v) {
          if (!v.IsObject())
            return;
          if (v.HasMember("x") && v["x"].IsInt()) {
            x = v["x"].GetInt();
          }
          if (v.HasMember("y") && v["y"].IsInt()) {
            y = v["y"].GetInt();
          }
        }
      };
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
      Dpi dpi; //!@ Default DPI for screen, usually 96x96
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
        dpi >> tmpDoc;
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
        if (v.HasMember("dpi") && v["dpi"].IsObject()) {
          dpi << v["dpi"];
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
      struct ContextAttributes {
        inline ContextAttributes();
        inline ~ContextAttributes();
        bool enable = false;
        bool alpha = true;
        bool antialias = true;
        bool depth = true;
        bool desynchronized = false;
        bool failIfMajorPerformanceCaveat = false;
        std::string powerPreference =
            "default"; //"default", "low-power", "high-performance"
        bool premultipliedAlpha = true;
        bool preserveDrawingBuffer = false;
        bool stencil = false;
        bool xrCompatible = false;
        inline void operator>>(rapidjson::Document &doc) const {
          if (!doc.IsObject())
            return;
          rapidjson::Document tmpDoc(rapidjson::Type::kObjectType);
          auto &allocHash = tmpDoc.GetAllocator();
          RAPIDJSON_ADDMEMBER_BOOL(tmpDoc, std::string("alpha"), alpha,
                                   allocHash);
          RAPIDJSON_ADDMEMBER_BOOL(tmpDoc, std::string("antialias"), antialias,
                                   allocHash);
          RAPIDJSON_ADDMEMBER_BOOL(tmpDoc, std::string("depth"), depth,
                                   allocHash);
          RAPIDJSON_ADDMEMBER_BOOL(tmpDoc, std::string("desynchronized"),
                                   desynchronized, allocHash);
          RAPIDJSON_ADDMEMBER_BOOL(tmpDoc,
                                   std::string("failIfMajorPerformanceCaveat"),
                                   failIfMajorPerformanceCaveat, allocHash);
          RAPIDJSON_ADDMEMBER_STRING(tmpDoc, std::string("powerPreference"),
                                     powerPreference, allocHash);
          RAPIDJSON_ADDMEMBER_BOOL(tmpDoc, std::string("premultipliedAlpha"),
                                   premultipliedAlpha, allocHash);
          RAPIDJSON_ADDMEMBER_BOOL(tmpDoc, std::string("preserveDrawingBuffer"),
                                   preserveDrawingBuffer, allocHash);
          RAPIDJSON_ADDMEMBER_BOOL(tmpDoc, std::string("stencil"), stencil,
                                   allocHash);
          RAPIDJSON_ADDMEMBER_BOOL(tmpDoc, std::string("xrCompatible"),
                                   xrCompatible, allocHash);
          RAPIDJSON_ADDMEMBER_BOOL(tmpDoc, std::string("enable"), enable,
                                   allocHash);
          rapidjson::Value tmpValue(tmpDoc, doc.GetAllocator());
          doc.AddMember(
              rapidjson::Value("contextAttributes", doc.GetAllocator()).Move(),
              tmpValue, doc.GetAllocator());
        }
        inline void operator<<(const std::string &str) {
          rapidjson::Document doc(rapidjson::Type::kObjectType);
          if (doc.Parse(str.data(), str.size()).HasParseError())
            return;
          operator<<(doc);
        }
        inline void operator<<(const rapidjson::Value &v) {
          if (!v.IsObject())
            return;
          if (v.HasMember("enable") && v["enable"].IsBool()) {
            enable = v["enable"].GetBool();
          }
          if (v.HasMember("alpha") && v["alpha"].IsBool()) {
            alpha = v["alpha"].GetBool();
          }
          if (v.HasMember("antialias") && v["antialias"].IsBool()) {
            antialias = v["antialias"].GetBool();
          }
          if (v.HasMember("depth") && v["depth"].IsBool()) {
            depth = v["depth"].GetBool();
          }
          if (v.HasMember("desynchronized") && v["desynchronized"].IsBool()) {
            desynchronized = v["desynchronized"].GetBool();
          }
          if (v.HasMember("failIfMajorPerformanceCaveat") &&
              v["failIfMajorPerformanceCaveat"].IsBool()) {
            failIfMajorPerformanceCaveat =
                v["failIfMajorPerformanceCaveat"].GetBool();
          }
          if (v.HasMember("powerPreference") &&
              v["powerPreference"].IsString()) {
            powerPreference = v["powerPreference"].GetString();
          }
          if (v.HasMember("premultipliedAlpha") &&
              v["premultipliedAlpha"].IsBool()) {
            premultipliedAlpha = v["premultipliedAlpha"].GetBool();
          }
          if (v.HasMember("preserveDrawingBuffer") &&
              v["preserveDrawingBuffer"].IsBool()) {
            preserveDrawingBuffer = v["preserveDrawingBuffer"].GetBool();
          }
          if (v.HasMember("stencil") && v["stencil"].IsBool()) {
            stencil = v["stencil"].GetBool();
          }
          if (v.HasMember("xrCompatible") && v["xrCompatible"].IsBool()) {
            xrCompatible = v["xrCompatible"].GetBool();
          }
        }
      };
      struct ShaderPrecisionFormat {
        struct _8DF_ {
          inline _8DF_();
          inline ~_8DF_();
          int rangeMin = 0;
          int rangeMax = 0;
          int precision = 0;
        };
        struct _8B30_ {
          inline _8B30_();
          inline ~_8B30_();
          _8DF_ _8DF0;
          _8DF_ _8DF1;
          _8DF_ _8DF2;
          _8DF_ _8DF3;
          _8DF_ _8DF4;
          _8DF_ _8DF5;
          void operator>>(rapidjson::Document &doc) const {
            if (!doc.IsObject())
              return;
            rapidjson::Document tmpDoc(rapidjson::Type::kObjectType);
            auto &allocHash = tmpDoc.GetAllocator();
            rapidjson::Value _8DF0Obj(rapidjson::Type::kObjectType);
            RAPIDJSON_ADDMEMBER_INT(_8DF0Obj, std::string("rangeMin"),
                                    _8DF0.rangeMin, allocHash);
            RAPIDJSON_ADDMEMBER_INT(_8DF0Obj, std::string("rangeMax"),
                                    _8DF0.rangeMax, allocHash);
            RAPIDJSON_ADDMEMBER_INT(_8DF0Obj, std::string("precision"),
                                    _8DF0.precision, allocHash);
            tmpDoc.AddMember(rapidjson::Value("8DF0", allocHash).Move(),
                             _8DF0Obj, allocHash);
            rapidjson::Value _8DF1Obj(rapidjson::Type::kObjectType);
            RAPIDJSON_ADDMEMBER_INT(_8DF1Obj, std::string("rangeMin"),
                                    _8DF1.rangeMin, allocHash);
            RAPIDJSON_ADDMEMBER_INT(_8DF1Obj, std::string("rangeMax"),
                                    _8DF1.rangeMax, allocHash);
            RAPIDJSON_ADDMEMBER_INT(_8DF1Obj, std::string("precision"),
                                    _8DF1.precision, allocHash);
            tmpDoc.AddMember(rapidjson::Value("8DF1", allocHash).Move(),
                             _8DF1Obj, allocHash);
            rapidjson::Value _8DF2obj(rapidjson::Type::kObjectType);
            RAPIDJSON_ADDMEMBER_INT(_8DF2obj, std::string("rangeMin"),
                                    _8DF2.rangeMin, allocHash);
            RAPIDJSON_ADDMEMBER_INT(_8DF2obj, std::string("rangeMax"),
                                    _8DF2.rangeMax, allocHash);
            RAPIDJSON_ADDMEMBER_INT(_8DF2obj, std::string("precision"),
                                    _8DF2.precision, allocHash);
            tmpDoc.AddMember(rapidjson::Value("8DF2", allocHash).Move(),
                             _8DF2obj, allocHash);
            rapidjson::Value _8DF3Obj(rapidjson::Type::kObjectType);
            RAPIDJSON_ADDMEMBER_INT(_8DF3Obj, std::string("rangeMin"),
                                    _8DF3.rangeMin, allocHash);
            RAPIDJSON_ADDMEMBER_INT(_8DF3Obj, std::string("rangeMax"),
                                    _8DF3.rangeMax, allocHash);
            RAPIDJSON_ADDMEMBER_INT(_8DF3Obj, std::string("precision"),
                                    _8DF3.precision, allocHash);
            tmpDoc.AddMember(rapidjson::Value("8DF3", allocHash).Move(),
                             _8DF3Obj, allocHash);
            rapidjson::Value _8DF4obj(rapidjson::Type::kObjectType);
            RAPIDJSON_ADDMEMBER_INT(_8DF4obj, std::string("rangeMin"),
                                    _8DF4.rangeMin, allocHash);
            RAPIDJSON_ADDMEMBER_INT(_8DF4obj, std::string("rangeMax"),
                                    _8DF4.rangeMax, allocHash);
            RAPIDJSON_ADDMEMBER_INT(_8DF4obj, std::string("precision"),
                                    _8DF4.precision, allocHash);
            tmpDoc.AddMember(rapidjson::Value("8DF4", allocHash).Move(),
                             _8DF4obj, allocHash);
            rapidjson::Value _8DF5obj(rapidjson::Type::kObjectType);
            RAPIDJSON_ADDMEMBER_INT(_8DF5obj, std::string("rangeMin"),
                                    _8DF5.rangeMin, allocHash);
            RAPIDJSON_ADDMEMBER_INT(_8DF5obj, std::string("rangeMax"),
                                    _8DF5.rangeMax, allocHash);
            RAPIDJSON_ADDMEMBER_INT(_8DF5obj, std::string("precision"),
                                    _8DF5.precision, allocHash);
            tmpDoc.AddMember(rapidjson::Value("8DF5", allocHash).Move(),
                             _8DF5obj, allocHash);

            rapidjson::Value tmpValue(tmpDoc, doc.GetAllocator());
            doc.AddMember(rapidjson::Value("8B30", doc.GetAllocator()).Move(),
                          tmpValue, doc.GetAllocator());
          }
          void operator<<(const std::string &str) {
            rapidjson::Document doc(rapidjson::Type::kObjectType);
            if (doc.Parse(str.data(), str.size()).HasParseError())
              return;
            operator<<(doc);
          }
          void operator<<(const rapidjson::Value &v) {
            do {
              if (!v.IsObject())
                break;
              if (v.HasMember("8DF0") && v["8DF0"].IsObject()) {
                const rapidjson::Value &refObj = v["8DF0"];
                if (refObj.HasMember("rangeMin") &&
                    refObj["rangeMin"].IsInt()) {
                  _8DF0.rangeMin = refObj["rangeMin"].GetInt();
                }
                if (refObj.HasMember("rangeMax") &&
                    refObj["rangeMax"].IsInt()) {
                  _8DF0.rangeMax = refObj["rangeMax"].GetInt();
                }
                if (refObj.HasMember("precision") &&
                    refObj["precision"].IsInt()) {
                  _8DF0.precision = refObj["precision"].GetInt();
                }
              }
              if (v.HasMember("8DF1") && v["8DF1"].IsObject()) {
                const rapidjson::Value &refObj = v["8DF1"];
                if (refObj.HasMember("rangeMin") &&
                    refObj["rangeMin"].IsInt()) {
                  _8DF1.rangeMin = refObj["rangeMin"].GetInt();
                }
                if (refObj.HasMember("rangeMax") &&
                    refObj["rangeMax"].IsInt()) {
                  _8DF1.rangeMax = refObj["rangeMax"].GetInt();
                }
                if (refObj.HasMember("precision") &&
                    refObj["precision"].IsInt()) {
                  _8DF1.precision = refObj["precision"].GetInt();
                }
              }
              if (v.HasMember("8DF2") && v["8DF2"].IsObject()) {
                const rapidjson::Value &refObj = v["8DF2"];
                if (refObj.HasMember("rangeMin") &&
                    refObj["rangeMin"].IsInt()) {
                  _8DF2.rangeMin = refObj["rangeMin"].GetInt();
                }
                if (refObj.HasMember("rangeMax") &&
                    refObj["rangeMax"].IsInt()) {
                  _8DF2.rangeMax = refObj["rangeMax"].GetInt();
                }
                if (refObj.HasMember("precision") &&
                    refObj["precision"].IsInt()) {
                  _8DF2.precision = refObj["precision"].GetInt();
                }
              }
              if (v.HasMember("8DF3") && v["8DF3"].IsObject()) {
                const rapidjson::Value &refObj = v["8DF3"];
                if (refObj.HasMember("rangeMin") &&
                    refObj["rangeMin"].IsInt()) {
                  _8DF3.rangeMin = refObj["rangeMin"].GetInt();
                }
                if (refObj.HasMember("rangeMax") &&
                    refObj["rangeMax"].IsInt()) {
                  _8DF3.rangeMax = refObj["rangeMax"].GetInt();
                }
                if (refObj.HasMember("precision") &&
                    refObj["precision"].IsInt()) {
                  _8DF3.precision = refObj["precision"].GetInt();
                }
              }
              if (v.HasMember("8DF4") && v["8DF4"].IsObject()) {
                const rapidjson::Value &refObj = v["8DF4"];
                if (refObj.HasMember("rangeMin") &&
                    refObj["rangeMin"].IsInt()) {
                  _8DF4.rangeMin = refObj["rangeMin"].GetInt();
                }
                if (refObj.HasMember("rangeMax") &&
                    refObj["rangeMax"].IsInt()) {
                  _8DF4.rangeMax = refObj["rangeMax"].GetInt();
                }
                if (refObj.HasMember("precision") &&
                    refObj["precision"].IsInt()) {
                  _8DF4.precision = refObj["precision"].GetInt();
                }
              }
              if (v.HasMember("8DF5") && v["8DF5"].IsObject()) {
                const rapidjson::Value &refObj = v["8DF5"];
                if (refObj.HasMember("rangeMin") &&
                    refObj["rangeMin"].IsInt()) {
                  _8DF5.rangeMin = refObj["rangeMin"].GetInt();
                }
                if (refObj.HasMember("rangeMax") &&
                    refObj["rangeMax"].IsInt()) {
                  _8DF5.rangeMax = refObj["rangeMax"].GetInt();
                }
                if (refObj.HasMember("precision") &&
                    refObj["precision"].IsInt()) {
                  _8DF5.precision = refObj["precision"].GetInt();
                }
              }
            } while (0);
          }
        };
        struct _8B31_ {
          inline _8B31_();
          inline ~_8B31_();
          _8DF_ _8DF0;
          _8DF_ _8DF1;
          _8DF_ _8DF2;
          _8DF_ _8DF3;
          _8DF_ _8DF4;
          _8DF_ _8DF5;
          void operator>>(rapidjson::Document &doc) const {
            if (!doc.IsObject())
              return;
            rapidjson::Document tmpDoc(rapidjson::Type::kObjectType);
            auto &allocHash = tmpDoc.GetAllocator();
            rapidjson::Value _8DF0Obj(rapidjson::Type::kObjectType);
            RAPIDJSON_ADDMEMBER_INT(_8DF0Obj, std::string("rangeMin"),
                                    _8DF0.rangeMin, allocHash);
            RAPIDJSON_ADDMEMBER_INT(_8DF0Obj, std::string("rangeMax"),
                                    _8DF0.rangeMax, allocHash);
            RAPIDJSON_ADDMEMBER_INT(_8DF0Obj, std::string("precision"),
                                    _8DF0.precision, allocHash);
            tmpDoc.AddMember(rapidjson::Value("8DF0", allocHash).Move(),
                             _8DF0Obj, allocHash);
            rapidjson::Value _8DF1Obj(rapidjson::Type::kObjectType);
            RAPIDJSON_ADDMEMBER_INT(_8DF1Obj, std::string("rangeMin"),
                                    _8DF1.rangeMin, allocHash);
            RAPIDJSON_ADDMEMBER_INT(_8DF1Obj, std::string("rangeMax"),
                                    _8DF1.rangeMax, allocHash);
            RAPIDJSON_ADDMEMBER_INT(_8DF1Obj, std::string("precision"),
                                    _8DF1.precision, allocHash);
            tmpDoc.AddMember(rapidjson::Value("8DF1", allocHash).Move(),
                             _8DF1Obj, allocHash);
            rapidjson::Value _8DF2obj(rapidjson::Type::kObjectType);
            RAPIDJSON_ADDMEMBER_INT(_8DF2obj, std::string("rangeMin"),
                                    _8DF2.rangeMin, allocHash);
            RAPIDJSON_ADDMEMBER_INT(_8DF2obj, std::string("rangeMax"),
                                    _8DF2.rangeMax, allocHash);
            RAPIDJSON_ADDMEMBER_INT(_8DF2obj, std::string("precision"),
                                    _8DF2.precision, allocHash);
            tmpDoc.AddMember(rapidjson::Value("8DF2", allocHash).Move(),
                             _8DF2obj, allocHash);
            rapidjson::Value _8DF3Obj(rapidjson::Type::kObjectType);
            RAPIDJSON_ADDMEMBER_INT(_8DF3Obj, std::string("rangeMin"),
                                    _8DF3.rangeMin, allocHash);
            RAPIDJSON_ADDMEMBER_INT(_8DF3Obj, std::string("rangeMax"),
                                    _8DF3.rangeMax, allocHash);
            RAPIDJSON_ADDMEMBER_INT(_8DF3Obj, std::string("precision"),
                                    _8DF3.precision, allocHash);
            tmpDoc.AddMember(rapidjson::Value("8DF3", allocHash).Move(),
                             _8DF3Obj, allocHash);
            rapidjson::Value _8DF4obj(rapidjson::Type::kObjectType);
            RAPIDJSON_ADDMEMBER_INT(_8DF4obj, std::string("rangeMin"),
                                    _8DF4.rangeMin, allocHash);
            RAPIDJSON_ADDMEMBER_INT(_8DF4obj, std::string("rangeMax"),
                                    _8DF4.rangeMax, allocHash);
            RAPIDJSON_ADDMEMBER_INT(_8DF4obj, std::string("precision"),
                                    _8DF4.precision, allocHash);
            tmpDoc.AddMember(rapidjson::Value("8DF4", allocHash).Move(),
                             _8DF4obj, allocHash);
            rapidjson::Value _8DF5obj(rapidjson::Type::kObjectType);
            RAPIDJSON_ADDMEMBER_INT(_8DF5obj, std::string("rangeMin"),
                                    _8DF5.rangeMin, allocHash);
            RAPIDJSON_ADDMEMBER_INT(_8DF5obj, std::string("rangeMax"),
                                    _8DF5.rangeMax, allocHash);
            RAPIDJSON_ADDMEMBER_INT(_8DF5obj, std::string("precision"),
                                    _8DF5.precision, allocHash);
            tmpDoc.AddMember(rapidjson::Value("8DF5", allocHash).Move(),
                             _8DF5obj, allocHash);
            rapidjson::Value tmpValue(tmpDoc, doc.GetAllocator());
            doc.AddMember(rapidjson::Value("8B31", doc.GetAllocator()).Move(),
                          tmpValue, doc.GetAllocator());
          }
          void operator<<(const rapidjson::Value &v) {
            do {
              if (!v.IsObject())
                break;
              if (v.HasMember("8DF0") && v["8DF0"].IsObject()) {
                const rapidjson::Value &refObj = v["8DF0"];
                if (refObj.HasMember("rangeMin") &&
                    refObj["rangeMin"].IsInt()) {
                  _8DF0.rangeMin = refObj["rangeMin"].GetInt();
                }
                if (refObj.HasMember("rangeMax") &&
                    refObj["rangeMax"].IsInt()) {
                  _8DF0.rangeMax = refObj["rangeMax"].GetInt();
                }
                if (refObj.HasMember("precision") &&
                    refObj["precision"].IsInt()) {
                  _8DF0.precision = refObj["precision"].GetInt();
                }
              }
              if (v.HasMember("8DF1") && v["8DF1"].IsObject()) {
                const rapidjson::Value &refObj = v["8DF1"];
                if (refObj.HasMember("rangeMin") &&
                    refObj["rangeMin"].IsInt()) {
                  _8DF1.rangeMin = refObj["rangeMin"].GetInt();
                }
                if (refObj.HasMember("rangeMax") &&
                    refObj["rangeMax"].IsInt()) {
                  _8DF1.rangeMax = refObj["rangeMax"].GetInt();
                }
                if (refObj.HasMember("precision") &&
                    refObj["precision"].IsInt()) {
                  _8DF1.precision = refObj["precision"].GetInt();
                }
              }
              if (v.HasMember("8DF2") && v["8DF2"].IsObject()) {
                const rapidjson::Value &refObj = v["8DF2"];
                if (refObj.HasMember("rangeMin") &&
                    refObj["rangeMin"].IsInt()) {
                  _8DF2.rangeMin = refObj["rangeMin"].GetInt();
                }
                if (refObj.HasMember("rangeMax") &&
                    refObj["rangeMax"].IsInt()) {
                  _8DF2.rangeMax = refObj["rangeMax"].GetInt();
                }
                if (refObj.HasMember("precision") &&
                    refObj["precision"].IsInt()) {
                  _8DF2.precision = refObj["precision"].GetInt();
                }
              }
              if (v.HasMember("8DF3") && v["8DF3"].IsObject()) {
                const rapidjson::Value &refObj = v["8DF3"];
                if (refObj.HasMember("rangeMin") &&
                    refObj["rangeMin"].IsInt()) {
                  _8DF3.rangeMin = refObj["rangeMin"].GetInt();
                }
                if (refObj.HasMember("rangeMax") &&
                    refObj["rangeMax"].IsInt()) {
                  _8DF3.rangeMax = refObj["rangeMax"].GetInt();
                }
                if (refObj.HasMember("precision") &&
                    refObj["precision"].IsInt()) {
                  _8DF3.precision = refObj["precision"].GetInt();
                }
              }
              if (v.HasMember("8DF4") && v["8DF4"].IsObject()) {
                const rapidjson::Value &refObj = v["8DF4"];
                if (refObj.HasMember("rangeMin") &&
                    refObj["rangeMin"].IsInt()) {
                  _8DF4.rangeMin = refObj["rangeMin"].GetInt();
                }
                if (refObj.HasMember("rangeMax") &&
                    refObj["rangeMax"].IsInt()) {
                  _8DF4.rangeMax = refObj["rangeMax"].GetInt();
                }
                if (refObj.HasMember("precision") &&
                    refObj["precision"].IsInt()) {
                  _8DF4.precision = refObj["precision"].GetInt();
                }
              }
              if (v.HasMember("8DF5") && v["8DF5"].IsObject()) {
                const rapidjson::Value &refObj = v["8DF5"];
                if (refObj.HasMember("rangeMin") &&
                    refObj["rangeMin"].IsInt()) {
                  _8DF5.rangeMin = refObj["rangeMin"].GetInt();
                }
                if (refObj.HasMember("rangeMax") &&
                    refObj["rangeMax"].IsInt()) {
                  _8DF5.rangeMax = refObj["rangeMax"].GetInt();
                }
                if (refObj.HasMember("precision") &&
                    refObj["precision"].IsInt()) {
                  _8DF5.precision = refObj["precision"].GetInt();
                }
              }
            } while (0);
          }
        };

        inline ShaderPrecisionFormat();
        inline ~ShaderPrecisionFormat();

        bool enable = false;
        _8B30_ _8B30;
        _8B31_ _8B31;

        void operator>>(rapidjson::Document &doc) const {
          if (!doc.IsObject())
            return;
          rapidjson::Document tmpDoc(rapidjson::Type::kObjectType);

          _8B30 >> tmpDoc;
          _8B31 >> tmpDoc;
          auto &allocHash = tmpDoc.GetAllocator();
          RAPIDJSON_ADDMEMBER_BOOL(tmpDoc, std::string("enable"), enable,
                                   allocHash);
          rapidjson::Value tmpValue(tmpDoc, doc.GetAllocator());
          doc.AddMember(
              rapidjson::Value("shaderPrecisionFormat", doc.GetAllocator())
                  .Move(),
              tmpValue, doc.GetAllocator());
        }
        void operator<<(const rapidjson::Value &value) {
          do {
            if (!value.IsObject())
              break;
            if (value.HasMember("enable") && value["enable"].IsBool()) {
              enable = value["enable"].GetBool();
            }
            if (!value.HasMember("8B30") || !value["8B30"].IsObject() ||
                !value.HasMember("8B31") || !value["8B31"].IsObject()) {
              break;
            }
            _8B30 << value["8B30"];
            _8B31 << value["8B31"];
          } while (0);
        }
      };
      inline Webgl();
      inline ~Webgl();

      bool enable = false;
      Hash hash;
      ContextAttributes contextAttributes;
      ShaderPrecisionFormat shaderPrecisionFormat;
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
        contextAttributes >> tmpDoc;
        shaderPrecisionFormat >> tmpDoc;
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
        if (v.HasMember("contextAttributes") &&
            v["contextAttributes"].IsObject()) {
          contextAttributes << v["contextAttributes"];
        }
        if (v.HasMember("shaderPrecisionFormat") &&
            v["shaderPrecisionFormat"].IsObject()) {
          shaderPrecisionFormat << v["shaderPrecisionFormat"];
        }
      }
    };

    struct Disk {
      inline Disk();
      inline ~Disk();

      bool enable = false;
      Hash hash;
      int64_t quota = 0;
      int64_t usage = 0;
      inline void operator>>(rapidjson::Document &doc) const {
        if (!doc.IsObject())
          return;
        rapidjson::Document tmpDoc(rapidjson::Type::kObjectType);
        auto &allocHash = tmpDoc.GetAllocator();
        RAPIDJSON_ADDMEMBER_BOOL(tmpDoc, std::string("enable"), enable,
                                 allocHash);
        hash >> tmpDoc;
        RAPIDJSON_ADDMEMBER_INT64(tmpDoc, std::string("quota"), quota,
                                  allocHash);
        RAPIDJSON_ADDMEMBER_INT64(tmpDoc, std::string("usage"), usage,
                                  allocHash);
        rapidjson::Value tmpValue(tmpDoc, doc.GetAllocator());
        doc.AddMember(rapidjson::Value("disk", doc.GetAllocator()).Move(),
                      tmpValue, doc.GetAllocator());
      }
      inline void operator<<(const rapidjson::Value &v) {
        if (!v.IsObject())
          return;
        if (v.HasMember("enable") && v["enable"].IsBool()) {
          enable = v["enable"].GetBool();
        }
        if (v.HasMember("hash") && v["hash"].IsObject()) {
          hash << v["hash"];
        }
        if (v.HasMember("quota") && v["quota"].IsInt64()) {
          quota = v["quota"].GetInt64();
        }
        if (v.HasMember("usage") && v["usage"].IsInt64()) {
          usage = v["usage"].GetInt64();
        }
      }
    };
    struct Voice {
      struct Data {
        inline Data();
        inline ~Data();

        std::string lang;
        std::string name;
      };
      inline Voice();
      inline ~Voice();

      bool enable = false;
      std::vector<Data> datas;
      void operator>>(rapidjson::Document &doc) const {
        if (!doc.IsObject())
          return;
        rapidjson::Document tmpDoc(rapidjson::Type::kObjectType);
        auto &allocHash = tmpDoc.GetAllocator();
        RAPIDJSON_ADDMEMBER_BOOL(tmpDoc, std::string("enable"), enable,
                                 allocHash);
        rapidjson::Value datasArray(rapidjson::Type::kArrayType);
        for (const auto &item : datas) {
          rapidjson::Value itemObj(rapidjson::Type::kObjectType);
          RAPIDJSON_ADDMEMBER_STRING(itemObj, std::string("lang"), item.lang,
                                     allocHash);
          RAPIDJSON_ADDMEMBER_STRING(itemObj, std::string("name"), item.name,
                                     allocHash);
          datasArray.PushBack(itemObj, allocHash);
        }
        RAPIDJSON_ADDMEMBER_OBJECT(tmpDoc, std::string("datas"), datasArray,
                                   allocHash);
        rapidjson::Value tmpValue(tmpDoc, doc.GetAllocator());
        doc.AddMember(rapidjson::Value("voice", doc.GetAllocator()).Move(),
                      tmpValue, doc.GetAllocator());
      }
      void operator<<(const rapidjson::Value &v) {
        if (!v.IsObject())
          return;
        if (v.HasMember("enable") && v["enable"].IsBool()) {
          enable = v["enable"].GetBool();
        }
        datas.clear();
        if (v.HasMember("datas") && v["datas"].IsArray()) {
          const rapidjson::Value &refObj = v["datas"];
          for (rapidjson::SizeType i = 0; i < refObj.Size(); ++i) {
            if (!refObj[i].IsObject())
              break;
            Data item;
            if (refObj[i].HasMember("lang") && refObj[i]["lang"].IsString()) {
              item.lang = refObj[i]["lang"].GetString();
            }
            if (refObj[i].HasMember("name") && refObj[i]["name"].IsString()) {
              item.name = refObj[i]["name"].GetString();
            }
            datas.emplace_back(item);
          }
        }
      }
    };
    struct UserAgentMetadata {
      struct Brand_version {
        inline Brand_version();
        inline ~Brand_version();
        std::string brand;
        std::string version;
      };
      struct Brand_full_version {
        inline Brand_full_version();
        inline ~Brand_full_version();
        std::string brand;
        std::string version;
      };
      inline UserAgentMetadata();
      inline ~UserAgentMetadata();

      bool enable = false;
      std::vector<Brand_version> brand_version_list;
      std::vector<Brand_full_version> brand_full_version_list;
      std::string full_version = "138.0.7204.158";
      std::string platform = "Windows";
      std::string platform_version = "11.0.0";
      std::string architecture = "x86_64";
      std::string model = "";
      bool mobile = false;
      std::string bitness = "64";
      bool wow64 = false;
      std::vector<std::string> form_factors = {"Desktop"};

      void operator<<(const rapidjson::Value &value) {
        do {
          if (!value.IsObject())
            break;
          if (value.HasMember("enable") && value["enable"].IsBool()) {
            enable = value["enable"].GetBool();
          }
          brand_version_list.clear();
          if (value.HasMember("brand_version_list") &&
              value["brand_version_list"].IsArray()) {
            const rapidjson::Value &refObj = value["brand_version_list"];
            for (rapidjson::SizeType i = 0; i < refObj.Size(); ++i) {
              if (!refObj[i].IsObject())
                break;
              if (!refObj[i].HasMember("brand") ||
                  !refObj[i]["brand"].IsString() ||
                  !refObj[i].HasMember("version") ||
                  !refObj[i]["version"].IsString())
                break;
              Brand_version item;
              item.brand = refObj[i]["brand"].GetString();
              item.version = refObj[i]["version"].GetString();
              brand_version_list.emplace_back(item);
            }
          }
          brand_full_version_list.clear();
          if (value.HasMember("brand_full_version_list") &&
              value["brand_full_version_list"].IsArray()) {
            const rapidjson::Value &refObj = value["brand_full_version_list"];
            for (rapidjson::SizeType i = 0; i < refObj.Size(); ++i) {
              if (!refObj[i].IsObject())
                break;
              if (!refObj[i].HasMember("brand") ||
                  !refObj[i]["brand"].IsString() ||
                  !refObj[i].HasMember("version") ||
                  !refObj[i]["version"].IsString())
                break;
              Brand_full_version item;
              item.brand = refObj[i]["brand"].GetString();
              item.version = refObj[i]["version"].GetString();
              brand_full_version_list.emplace_back(item);
            }
          }
          if (value.HasMember("full_version") &&
              value["full_version"].IsString()) {
            full_version = value["full_version"].GetString();
          }
          if (value.HasMember("platform") && value["platform"].IsString()) {
            platform = value["platform"].GetString();
          }
          if (value.HasMember("platform_version") &&
              value["platform_version"].IsString()) {
            platform_version = value["platform_version"].GetString();
          }
          if (value.HasMember("architecture") &&
              value["architecture"].IsString()) {
            architecture = value["architecture"].GetString();
          }
          if (value.HasMember("model") && value["model"].IsString()) {
            model = value["model"].GetString();
          }
          if (value.HasMember("mobile") && value["mobile"].IsBool()) {
            mobile = value["mobile"].GetBool();
          }
          if (value.HasMember("bitness") && value["bitness"].IsString()) {
            bitness = value["bitness"].GetString();
          }
          if (value.HasMember("wow64") && value["wow64"].IsBool()) {
            wow64 = value["wow64"].GetBool();
          }
          form_factors.clear();
          if (value.HasMember("form_factors") &&
              value["form_factors"].IsArray()) {
            const rapidjson::Value &refObj = value["form_factors"];
            for (rapidjson::SizeType i = 0; i < refObj.Size(); ++i) {
              if (!refObj[i].IsString())
                break;
              std::string tmp(refObj[i].GetString());
              if (tmp.empty())
                continue;
              // std::transform(tmp.begin(), tmp.end(), tmp.begin(),
              // ::tolower);
              form_factors.emplace_back(tmp);
            }
          }
        } while (0);
      }
      void operator>>(rapidjson::Document &output) const {
        if (!output.IsObject())
          return;
        rapidjson::Document tmpDoc(rapidjson::Type::kObjectType);
        auto &allocHash = tmpDoc.GetAllocator();
        RAPIDJSON_ADDMEMBER_BOOL(tmpDoc, std::string("enable"), enable,
                                 allocHash);

        rapidjson::Value brandVersionArray(rapidjson::Type::kArrayType);
        for (const auto &item : brand_version_list) {
          rapidjson::Value itemObj(rapidjson::Type::kObjectType);
          RAPIDJSON_ADDMEMBER_STRING(itemObj, std::string("brand"), item.brand,
                                     allocHash);
          RAPIDJSON_ADDMEMBER_STRING(itemObj, std::string("version"),
                                     item.version, allocHash);
          brandVersionArray.PushBack(itemObj, allocHash);
        }
        RAPIDJSON_ADDMEMBER_OBJECT(tmpDoc, std::string("brand_version_list"),
                                   brandVersionArray, allocHash);

        rapidjson::Value brandFullVersionArray(rapidjson::Type::kArrayType);
        for (const auto &item : brand_full_version_list) {
          rapidjson::Value itemObj(rapidjson::Type::kObjectType);
          RAPIDJSON_ADDMEMBER_STRING(itemObj, std::string("brand"), item.brand,
                                     allocHash);
          RAPIDJSON_ADDMEMBER_STRING(itemObj, std::string("version"),
                                     item.version, allocHash);
          brandFullVersionArray.PushBack(itemObj, allocHash);
        }
        RAPIDJSON_ADDMEMBER_OBJECT(tmpDoc,
                                   std::string("brand_full_version_list"),
                                   brandFullVersionArray, allocHash);

        RAPIDJSON_ADDMEMBER_STRING(tmpDoc, std::string("full_version"),
                                   full_version, allocHash);
        RAPIDJSON_ADDMEMBER_STRING(tmpDoc, std::string("platform"), platform,
                                   allocHash);
        RAPIDJSON_ADDMEMBER_STRING(tmpDoc, std::string("platform_version"),
                                   platform_version, allocHash);
        RAPIDJSON_ADDMEMBER_STRING(tmpDoc, std::string("architecture"),
                                   architecture, allocHash);
        RAPIDJSON_ADDMEMBER_STRING(tmpDoc, std::string("model"), model,
                                   allocHash);
        RAPIDJSON_ADDMEMBER_BOOL(tmpDoc, std::string("mobile"), mobile,
                                 allocHash);
        RAPIDJSON_ADDMEMBER_STRING(tmpDoc, std::string("bitness"), bitness,
                                   allocHash);
        RAPIDJSON_ADDMEMBER_BOOL(tmpDoc, std::string("wow64"), wow64,
                                 allocHash);
        rapidjson::Value formFactorsArray(rapidjson::Type::kArrayType);
        for (const auto &item : form_factors) {
          if (item.empty())
            continue;
          rapidjson::Value itemValue(rapidjson::Type::kStringType);
          itemValue.SetString(item.c_str(),
                              static_cast<rapidjson::SizeType>(item.size()),
                              allocHash);
          formFactorsArray.PushBack(itemValue, allocHash);
        }
        RAPIDJSON_ADDMEMBER_OBJECT(tmpDoc, std::string("form_factors"),
                                   formFactorsArray, allocHash);
        rapidjson::Value tmpValue(tmpDoc, output.GetAllocator());
        output.AddMember(
            rapidjson::Value("userAgentMetadata", output.GetAllocator()).Move(),
            tmpValue, output.GetAllocator());
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
    bool real_fingerprint_output = false;
    std::string do_not_track = "1";
    std::string platform = "Win32";
    unsigned int rtt = 0; //!@ Round-trip time in milliseconds, default is 0
    bool netDnsAllowFallbackToSystemtask =
        true; //!@ Allow fallback to system task for DNS resolution
    int hardwareConcurrency = 8;
    int deviceMemory = 16;
    std::string userAgent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
                            "AppleWebKit/537.36 (KHTML, "
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
    Disk disk;
    UserAgentMetadata userAgentMetadata;
    Voice voice;
    inline void operator>>(rapidjson::Document &doc) const {
      if (!doc.IsObject())
        return;
      rapidjson::Document fpsDoc(rapidjson::kObjectType);
      auto &fpsAllocator = fpsDoc.GetAllocator();
      RAPIDJSON_ADDMEMBER_BOOL(fpsDoc, std::string("enable"), enable,
                               fpsAllocator);
      RAPIDJSON_ADDMEMBER_BOOL(fpsDoc, std::string("real_fingerprint_output"),
                               real_fingerprint_output, fpsAllocator);
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
      RAPIDJSON_ADDMEMBER_UINT(fpsDoc, std::string("rtt"), rtt, fpsAllocator);
      RAPIDJSON_ADDMEMBER_BOOL(fpsDoc,
                               std::string("netDnsAllowFallbackToSystemtask"),
                               netDnsAllowFallbackToSystemtask, fpsAllocator);
      rapidjson::Value languagesArray(rapidjson::Type::kArrayType);
      for (const auto &lang : languages) {
        if (lang.empty())
          continue;
        rapidjson::Value langValue(rapidjson::Type::kStringType);
        langValue.SetString(lang.c_str(),
                            static_cast<rapidjson::SizeType>(lang.size()),
                            fpsAllocator);
        languagesArray.PushBack(langValue, fpsAllocator);
      }
      RAPIDJSON_ADDMEMBER_OBJECT(fpsDoc, std::string("languages"),
                                 languagesArray, fpsAllocator);
      RAPIDJSON_ADDMEMBER_STRING(fpsDoc, std::string("acceptLanguage"),
                                 acceptLanguage, fpsAllocator);
      userAgentMetadata >> fpsDoc;
      voice >> fpsDoc;
      canvas >> fpsDoc;
      webgl >> fpsDoc;
      audio >> fpsDoc;
      math >> fpsDoc;
      font >> fpsDoc;
      timezone >> fpsDoc;
      screen >> fpsDoc;
      disk >> fpsDoc;
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
      if (v.HasMember("real_fingerprint_output") &&
          v["real_fingerprint_output"].IsBool()) {
        real_fingerprint_output = v["real_fingerprint_output"].GetBool();
      }
      if (v.HasMember("do_not_track") && v["do_not_track"].IsString()) {
        do_not_track = v["do_not_track"].GetString();
      }
      if (v.HasMember("rtt") && v["rtt"].IsUint()) {
        rtt = v["rtt"].GetUint();
      }
      if (v.HasMember("disk") && v["disk"].IsObject()) {
        disk << v["disk"];
      }
      if (v.HasMember("netDnsAllowFallbackToSystemtask") &&
          v["netDnsAllowFallbackToSystemtask"].IsBool()) {
        netDnsAllowFallbackToSystemtask =
            v["netDnsAllowFallbackToSystemtask"].GetBool();
      }
      if (v.HasMember("userAgentMetadata") &&
          v["userAgentMetadata"].IsObject()) {
        userAgentMetadata << v["userAgentMetadata"];
      }
      if (v.HasMember("voice") && v["voice"].IsObject()) {
        voice << v["voice"];
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
  struct DynamicFpsInfo {
    struct Ipinfo {
      inline Ipinfo();
      inline ~Ipinfo();

      std::string ip;
      std::string country;
      std::string region;
      std::string city;
      std::string zip;
      std::string lat;
      std::string lon;
      std::string timezone;
      std::string isp;

      void operator>>(rapidjson::Document &doc) const {
        if (!doc.IsObject())
          return;
        rapidjson::Document tmpDoc(rapidjson::Type::kObjectType);
        auto &allocator = tmpDoc.GetAllocator();
        RAPIDJSON_ADDMEMBER_STRING(tmpDoc, std::string("ip"), ip, allocator);
        RAPIDJSON_ADDMEMBER_STRING(tmpDoc, std::string("country"), country,
                                   allocator);
        RAPIDJSON_ADDMEMBER_STRING(tmpDoc, std::string("region"), region,
                                   allocator);
        RAPIDJSON_ADDMEMBER_STRING(tmpDoc, std::string("city"), city,
                                   allocator);
        RAPIDJSON_ADDMEMBER_STRING(tmpDoc, std::string("zip"), zip, allocator);
        RAPIDJSON_ADDMEMBER_STRING(tmpDoc, std::string("lat"), lat, allocator);
        RAPIDJSON_ADDMEMBER_STRING(tmpDoc, std::string("lon"), lon, allocator);
        RAPIDJSON_ADDMEMBER_STRING(tmpDoc, std::string("timezone"), timezone,
                                   allocator);
        rapidjson::Value tmpValue(tmpDoc, doc.GetAllocator());
        doc.AddMember(rapidjson::Value("ipinfo", doc.GetAllocator()).Move(),
                      tmpValue, doc.GetAllocator());
      }
      void operator<<(const rapidjson::Value &v) {
        if (!v.IsObject())
          return;
        if (v.HasMember("ip") && v["ip"].IsString()) {
          ip = v["ip"].GetString();
        }
        if (v.HasMember("country") && v["country"].IsString()) {
          country = v["country"].GetString();
        }
        if (v.HasMember("region") && v["region"].IsString()) {
          region = v["region"].GetString();
        }
        if (v.HasMember("city") && v["city"].IsString()) {
          city = v["city"].GetString();
        }
        if (v.HasMember("zip") && v["zip"].IsString()) {
          zip = v["zip"].GetString();
        }
        if (v.HasMember("lat") && v["lat"].IsString()) {
          lat = v["lat"].GetString();
        }
        if (v.HasMember("lon") && v["lon"].IsString()) {
          lon = v["lon"].GetString();
        }
        if (v.HasMember("timezone") && v["timezone"].IsString()) {
          timezone = v["timezone"].GetString();
        }
      }
    };
    inline DynamicFpsInfo();
    inline ~DynamicFpsInfo();

    bool enable = false; //!@ Enable dynamic FPS, default is false
    Ipinfo ipinfo;       //!@ IP information, default is empty
    void operator>>(rapidjson::Document &doc) const {
      if (!doc.IsObject())
        return;
      rapidjson::Document tmpDoc(rapidjson::Type::kObjectType);
      auto &allocator = tmpDoc.GetAllocator();
      RAPIDJSON_ADDMEMBER_BOOL(tmpDoc, std::string("enable"), enable,
                               allocator);
      ipinfo >> tmpDoc;
      rapidjson::Value tmpValue(tmpDoc, doc.GetAllocator());
      doc.AddMember(rapidjson::Value("dynFpsInfo", doc.GetAllocator()).Move(),
                    tmpValue, doc.GetAllocator());
    }
    void operator<<(const rapidjson::Value &v) {
      if (!v.IsObject())
        return;
      if (v.HasMember("enable") && v["enable"].IsBool()) {
        enable = v["enable"].GetBool();
      }
      if (v.HasMember("ipinfo") && v["ipinfo"].IsObject()) {
        ipinfo << v["ipinfo"];
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
  inline void operator<<(const std::string &json) {
    do {
      rapidjson::Document doc;
      if (doc.Parse(json.data(), json.size()).HasParseError())
        break;
      if (!doc.IsObject())
        break;
      if (doc.HasMember(kObjectKey)) {
        *this << doc[kObjectKey];
      } else {
        *this << doc;
      }
    } while (0);
  }

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
  DynamicFpsInfo dynFpsInfo; //!@ Dynamic FPS information, default is empty
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
  if (v.HasMember("dynFpsInfo") && v["dynFpsInfo"].IsObject()) {
    dynFpsInfo << v["dynFpsInfo"];
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
  dynFpsInfo >> xsiumioDoc;
  RAPIDJSON_ADDMEMBER_STRING(xsiumioDoc, std::string("proxy_info_request_url"),
                             proxy_info_request_url, xsiumioAllocator);
  yunlogin >> xsiumioDoc;
  rapidjson::Value xsiumioValue(xsiumioDoc, allocator);
  doc.AddMember(rapidjson::Value(kObjectKey, allocator).Move(), xsiumioValue,
                allocator);
}
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
inline IXSiumio::Fingerprint::Webgl::ContextAttributes::ContextAttributes() =
    default;
inline IXSiumio::Fingerprint::Webgl::ContextAttributes::~ContextAttributes() =
    default;
inline IXSiumio::Fingerprint::Webgl::ShaderPrecisionFormat::
    ShaderPrecisionFormat() = default;
inline IXSiumio::Fingerprint::Webgl::ShaderPrecisionFormat::
    ~ShaderPrecisionFormat() = default;
inline IXSiumio::Fingerprint::Webgl::ShaderPrecisionFormat::_8DF_::_8DF_() =
    default;
inline IXSiumio::Fingerprint::Webgl::ShaderPrecisionFormat::_8DF_::~_8DF_() =
    default;
inline IXSiumio::Fingerprint::Webgl::ShaderPrecisionFormat::_8B30_::_8B30_() =
    default;
inline IXSiumio::Fingerprint::Webgl::ShaderPrecisionFormat::_8B30_::~_8B30_() =
    default;
inline IXSiumio::Fingerprint::Webgl::ShaderPrecisionFormat::_8B31_::_8B31_() =
    default;
inline IXSiumio::Fingerprint::Webgl::ShaderPrecisionFormat::_8B31_::~_8B31_() =
    default;
inline IXSiumio::Fingerprint::Font::Font() = default;
inline IXSiumio::Fingerprint::Font::~Font() = default;
inline IXSiumio::Fingerprint::TimeZone::TimeZone() = default;
inline IXSiumio::Fingerprint::TimeZone::~TimeZone() = default;
inline IXSiumio::Fingerprint::Screen::Screen() = default;
inline IXSiumio::Fingerprint::Screen::~Screen() = default;
inline IXSiumio::Fingerprint::Screen::Dpi::Dpi() = default;
inline IXSiumio::Fingerprint::Screen::Dpi::~Dpi() = default;
inline IXSiumio::Fingerprint::Disk::Disk() = default;
inline IXSiumio::Fingerprint::Disk::~Disk() = default;
inline IXSiumio::Fingerprint::UserAgentMetadata::UserAgentMetadata() = default;
inline IXSiumio::Fingerprint::UserAgentMetadata::~UserAgentMetadata() = default;
inline IXSiumio::Fingerprint::UserAgentMetadata::Brand_version::
    Brand_version() = default;
inline IXSiumio::Fingerprint::UserAgentMetadata::Brand_version::
    ~Brand_version() = default;
inline IXSiumio::Fingerprint::UserAgentMetadata::Brand_full_version::
    Brand_full_version() = default;
inline IXSiumio::Fingerprint::UserAgentMetadata::Brand_full_version::
    ~Brand_full_version() = default;
inline IXSiumio::Fingerprint::Voice::Voice() = default;
inline IXSiumio::Fingerprint::Voice::~Voice() = default;
inline IXSiumio::Fingerprint::Voice::Data::Data() = default;
inline IXSiumio::Fingerprint::Voice::Data::~Data() = default;
inline IXSiumio::DynamicFpsInfo::DynamicFpsInfo() = default;
inline IXSiumio::DynamicFpsInfo::~DynamicFpsInfo() = default;
inline IXSiumio::DynamicFpsInfo::Ipinfo::Ipinfo() = default;
inline IXSiumio::DynamicFpsInfo::Ipinfo::~Ipinfo() = default;
} // namespace xsiumio
} // namespace chromium
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 19 Jul 2025 21:20:54 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__5E6CBAF3_846B_4EF0_B587_0B9D7DC7F803__