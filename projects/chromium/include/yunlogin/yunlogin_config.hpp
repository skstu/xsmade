#if !defined(__C8214189_EE1B_4726_BECE_3CBE103F523F__)
#define __C8214189_EE1B_4726_BECE_3CBE103F523F__

#include "cross_project_compatibility.h"

#if COMPILE_IN_PROJECT_CHROMIUM
#include "chromium/include/chromium.h"
#include "chromium/include/rapidjson.h"
#include "chromium/projects/yunlogin/yunlogin.hpp"
#include "chromium/include/xsiumio.hpp"
#else
#include <rapidjson.h>
#include <xsiumio.hpp>
#include "yunlogin.hpp"
#endif

namespace chromium {
namespace yunlogin {
constexpr const char kDirectoryExtensions[] = "fbp";
constexpr const char kFilenameConfig[] = "cfg.dat";
constexpr const char kFilenameUdd[] = ".udd";
constexpr const char kSwitchIpinfoio[] = "ipinfoio";
constexpr const char kSwitchMyipyunlogincom[] = "myipyunlogincom";
constexpr const char kSwitchBaseData[] = "base-data";
constexpr const char kSwitchBrowserId[] = "browser-id";
constexpr const char kSwitchShopId[] = "shop-id";
constexpr const char kSwitchInstallExtension[] = "install-extension";
constexpr const char kSwitchUninstallExtension[] = "uninstall-extension";
constexpr const char kCustomDataDir[] = "user-data-dir";
constexpr const char kSwitchListInstalledExtension[] =
    "list-installed-extensions";
constexpr const char kSwitchReloadCookies[] = "reload-cookies";
constexpr const char kSwitchUpdateCookies[] = "update-cookies";
constexpr const char kSwitchCloseBrowser[] = "close-browser";
constexpr const char kSwitchNotifyUserLogout[] = "notify-user-logout";
constexpr const char kSwitchNotifySyncopMaster[] = "notify-syncop-master";
constexpr const char kSwitchClientAppId[] = "client-appid";
constexpr const char kSwitchClientAppIcon[] = "client-appicon";
constexpr const char kSwitchBrandingName[] = "branding-name";
namespace {
inline std::string TrimQuotes(const std::string &s) {
  size_t start = 0, end = s.size();
  while (start < end && (s[start] == ' ' || s[start] == '\"'))
    ++start;
  while (end > start && (s[end - 1] == ' ' || s[end - 1] == '\"'))
    --end;
  return s.substr(start, end - start);
}
inline std::set<std::string> SplitFontsUnique(const std::string &fonts_str) {
  std::set<std::string> font_set;
  std::string token;
  bool in_quotes = false;
  for (char c : fonts_str) {
    if (c == '\"') {
      in_quotes = !in_quotes;
    } else if (c == ',' && !in_quotes) {
      if (!token.empty())
        font_set.insert(TrimQuotes(token));
      token.clear();
    } else {
      token += c;
    }
  }
  if (!token.empty())
    font_set.insert(TrimQuotes(token));
  return font_set;
}
} // namespace

class IConfigure {
public:
  struct BaseData {
    std::string wsPort;
    std::string rpaPort;
    std::string appVersion;
    std::string versionCode;
    std::string bitness;
    std::string platform;
    std::string browser;
    std::string ts;
    std::string deviceId;
    std::string mac;
    std::string computerName;
    std::string ipifyPort;
    std::string cookiefyPort;
    std::string appPort;

    std::string searchEngine;
    std::string channel;

    std::string sdkVersion;
    std::string sdkVersionCode;

    std::string source;
    inline BaseData();
    inline ~BaseData();

    inline bool IsValid() const {
      return !wsPort.empty();
    }

    inline std::string GetAppInfo() const {
      std::string appInfo;
#if COMPILE_IN_PROJECT_CHROMIUM
#if BUILDFLAG(ENABLE_SDK_BRANDING)
      appInfo += "sdkVersion=";
      appInfo += sdkVersion;

      appInfo += "&";

      appInfo += "sdkVersionCode=";
      appInfo += sdkVersionCode;
#else
      appInfo += "appVersion=";
      appInfo += appVersion;

      appInfo += "&";

      appInfo += "versionCode=";
      appInfo += versionCode;
#endif
#else
      appInfo += "appVersion=";
      appInfo += appVersion;

      appInfo += "&";

      appInfo += "versionCode=";
      appInfo += versionCode;
#endif

      appInfo += "&";

      appInfo += "bitness=";
      appInfo += bitness;

      appInfo += "&";

      appInfo += "platform=";
      appInfo += platform;

      appInfo += "&";

      appInfo += "browser=";
      appInfo += browser;

      appInfo += "&";

      appInfo += "deviceId=";
      appInfo += deviceId;

      appInfo += "&";

      appInfo += "mac=";
      appInfo += mac;

      appInfo += "&";

      appInfo += "computerName=";
      appInfo += computerName;

      appInfo += "&";

      appInfo += "channel=";
      appInfo += channel;

      return appInfo;
    }

    inline std::string ToLower(const std::string &s) const {
      std::string r = s;
      std::transform(r.begin(), r.end(), r.begin(),
                     [](unsigned char c) { return std::tolower(c); });
      return r;
    }

    inline bool EqualsCaseInsensitiveASCII(const std::string &a,
                                           const std::string &b) const {
      return ToLower(a) == ToLower(b);
    }
    inline void operator<<(const rapidjson::Value &v) {
      if (!v.IsString())
        return;
      source = v.GetString();
      *this << source;
    }
    inline void operator<<(const std::string &data) {
      std::istringstream ss(data);
      std::string token;
      while (std::getline(ss, token, '&')) {
        std::istringstream ss2(token);
        std::string name, value;
        if (std::getline(ss2, name, '=') && std::getline(ss2, value)) {
          if (EqualsCaseInsensitiveASCII(name, "wsPort"))
            wsPort = value;
          else if (EqualsCaseInsensitiveASCII(name, "appVersion"))
            appVersion = value;
          else if (EqualsCaseInsensitiveASCII(name, "versionCode"))
            versionCode = value;
          else if (EqualsCaseInsensitiveASCII(name, "bitness"))
            bitness = value;
          else if (EqualsCaseInsensitiveASCII(name, "platform"))
            platform = value;
          else if (EqualsCaseInsensitiveASCII(name, "browser"))
            browser = value;
          else if (EqualsCaseInsensitiveASCII(name, "ts"))
            ts = value;
          else if (EqualsCaseInsensitiveASCII(name, "rpaPort"))
            rpaPort = value;
          else if (EqualsCaseInsensitiveASCII(name, "deviceId"))
            deviceId = value;
          else if (EqualsCaseInsensitiveASCII(name, "mac"))
            mac = value;
          else if (EqualsCaseInsensitiveASCII(name, "computerName"))
            computerName = value;
          else if (EqualsCaseInsensitiveASCII(name, "ipifyPort"))
            ipifyPort = value;
          else if (EqualsCaseInsensitiveASCII(name, "cookiefyPort"))
            cookiefyPort = value;
          else if (EqualsCaseInsensitiveASCII(name, "appPort"))
            appPort = value;
          else if (EqualsCaseInsensitiveASCII(name, "se"))
            searchEngine = value;
          else if (EqualsCaseInsensitiveASCII(name, "channel"))
            channel = value;
          else if (EqualsCaseInsensitiveASCII(name, "sdkVersion"))
            sdkVersion = value;
          else if (EqualsCaseInsensitiveASCII(name, "sdkVersionCode"))
            sdkVersionCode = value;
        }
      }
      source = data;
    }
    void operator>>(rapidjson::Document &doc) const {
      if (!doc.IsObject())
        return;
      if (doc.HasMember(kSwitchBaseData))
        doc.RemoveMember(kSwitchBaseData);
      doc.AddMember(rapidjson::Value()
                        .SetString(kSwitchBaseData, doc.GetAllocator())
                        .Move(),
                    rapidjson::Value()
                        .SetString(source.empty() ? "" : source.c_str(),
                                   doc.GetAllocator())
                        .Move(),
                    doc.GetAllocator());
    }
  };

  struct Device {
    inline Device();
    inline ~Device();

    inline std::string GetIpDisplayString() const {
      return std::string("---.---.---.--- / -- --");
    }

    inline bool IsLocalProxy() const {
      return !protocol.compare("local");
    }

    inline bool IsDynamicProxy() const {
      return !protocol.compare("dynamic");
    }
    inline bool IsStaticProxy() const {
      bool result = true;
      do {
        if (!protocol.compare("http"))
          break;
        if (!protocol.compare("https"))
          break;
        if (!protocol.compare("socks5"))
          break;
        result = false;
      } while (0);
      return result;
    }

    inline bool IsIpSwitchable() const {
      return !ipSwitchable.compare("1");
    }

    std::string proxyTypeDesc;
    std::string ipTypeDesc;
    std::string ipSwitchable;
    std::string vendor;
    std::string vendorDesc;
    std::string deviceName;
    std::string protocol;
    std::string host;
    int port = 0;
    std::string userName;
    std::string password;
    std::set<std::string> proxyaddrArr;
    std::string ipTerrInfo;
    std::string uuid;
    inline void operator>>(rapidjson::Document &doc) const {
      if (!doc.IsObject())
        return;
      if (doc.HasMember("device"))
        doc.RemoveMember("device");
      rapidjson::Value deviceObj(rapidjson::kObjectType);
      auto &allocator = doc.GetAllocator();

      RAPIDJSON_ADDMEMBER_STRING(deviceObj, std::string("proxyTypeDesc"),
                                 proxyTypeDesc, allocator);
      RAPIDJSON_ADDMEMBER_STRING(deviceObj, std::string("ipTypeDesc"),
                                 ipTypeDesc, allocator);
      RAPIDJSON_ADDMEMBER_STRING(deviceObj, std::string("ipSwitchable"),
                                 ipSwitchable, allocator);
      RAPIDJSON_ADDMEMBER_STRING(deviceObj, std::string("vendor"), vendor,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(deviceObj, std::string("vendorDesc"),
                                 vendorDesc, allocator);
      RAPIDJSON_ADDMEMBER_STRING(deviceObj, std::string("deviceName"),
                                 deviceName, allocator);
      RAPIDJSON_ADDMEMBER_STRING(deviceObj, std::string("protocol"), protocol,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(deviceObj, std::string("host"), host,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(deviceObj, std::string("userName"), userName,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(deviceObj, std::string("password"), password,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(deviceObj, std::string("ipTerrInfo"),
                                 ipTerrInfo, allocator);
      RAPIDJSON_ADDMEMBER_STRING(deviceObj, std::string("uuid"), uuid,
                                 allocator);
      RAPIDJSON_ADDMEMBER_INT(deviceObj, std::string("port"), port, allocator);
      rapidjson::Value proxyaddrArrArray(rapidjson::kArrayType);
      for (const auto &addr : proxyaddrArr) {
        if (addr.empty())
          continue;
        proxyaddrArrArray.PushBack(
            rapidjson::Value().SetString(addr.c_str(), allocator).Move(),
            allocator);
      }
      RAPIDJSON_ADDMEMBER_OBJECT(deviceObj, std::string("proxyaddrArr"),
                                 proxyaddrArrArray, allocator);
      RAPIDJSON_ADDMEMBER_OBJECT(doc, std::string("device"), deviceObj,
                                 allocator);
    }
    inline void operator<<(const rapidjson::Value &v) {
      do {
        if (!v.IsObject())
          break;
        if (v.HasMember("proxyTypeDesc") && v["proxyTypeDesc"].IsString())
          proxyTypeDesc = v["proxyTypeDesc"].GetString();
        if (v.HasMember("ipTypeDesc") && v["ipTypeDesc"].IsString())
          ipTypeDesc = v["ipTypeDesc"].GetString();
        if (v.HasMember("ipSwitchable") && v["ipSwitchable"].IsString())
          ipSwitchable = v["ipSwitchable"].GetString();
        if (v.HasMember("vendor") && v["vendor"].IsString())
          vendor = v["vendor"].GetString();
        if (v.HasMember("vendorDesc") && v["vendorDesc"].IsString())
          vendorDesc = v["vendorDesc"].GetString();
        if (v.HasMember("deviceName") && v["deviceName"].IsString())
          deviceName = v["deviceName"].GetString();
        if (v.HasMember("protocol") && v["protocol"].IsString())
          protocol = v["protocol"].GetString();
        if (v.HasMember("host") && v["host"].IsString())
          host = v["host"].GetString();
        if (v.HasMember("port") && v["port"].IsInt())
          port = v["port"].GetInt();
        if (v.HasMember("userName") && v["userName"].IsString())
          userName = v["userName"].GetString();
        if (v.HasMember("password") && v["password"].IsString())
          password = v["password"].GetString();
        if (v.HasMember("ipTerrInfo") && v["ipTerrInfo"].IsString())
          ipTerrInfo = v["ipTerrInfo"].GetString();
        if (v.HasMember("uuid") && v["uuid"].IsString())
          uuid = v["uuid"].GetString();
        if (v.HasMember("proxyaddrArr") && v["proxyaddrArr"].IsArray()) {
          proxyaddrArr.clear();
          for (auto &addr : v["proxyaddrArr"].GetArray()) {
            if (addr.IsString() && addr.GetStringLength() > 0)
              proxyaddrArr.insert(addr.GetString());
          }
        }
      } while (0);
    }
  };

  struct ProxyInfo {
    struct Outbound {
      inline Outbound();
      inline ~Outbound();
      std::string protocol;
      std::string server;
      int port = 0;
      std::string username;
      std::string password;

      inline void operator<<(const rapidjson::Value &v) {
        do {
          if (!v.IsObject())
            break;
          if (v.HasMember("protocol") && v["protocol"].IsString())
            protocol = v["protocol"].GetString();
          if (v.HasMember("server") && v["server"].IsString())
            server = v["server"].GetString();
          if (v.HasMember("port") && v["port"].IsInt())
            port = v["port"].GetInt();
          if (v.HasMember("username") && v["username"].IsString())
            username = v["username"].GetString();
          if (v.HasMember("password") && v["password"].IsString())
            password = v["password"].GetString();
        } while (0);
      }
    };

    struct Bridge {
      inline Bridge();
      inline ~Bridge();
      std::string protocol;
      std::string server;
      int port = 0;
      std::string username;
      std::string password;
      int mode = 0;

      inline void operator<<(const rapidjson::Value &v) {
        do {
          if (!v.IsObject())
            break;
          if (v.HasMember("protocol") && v["protocol"].IsString())
            protocol = v["protocol"].GetString();
          if (v.HasMember("server") && v["server"].IsString())
            server = v["server"].GetString();
          if (v.HasMember("port") && v["port"].IsInt())
            port = v["port"].GetInt();
          if (v.HasMember("username") && v["username"].IsString())
            username = v["username"].GetString();
          if (v.HasMember("password") && v["password"].IsString())
            password = v["password"].GetString();
          if (v.HasMember("mode") && v["mode"].IsInt())
            mode = v["mode"].GetInt();
        } while (0);
      }
    };

    struct Dns {
      inline Dns();
      inline ~Dns();
      std::string tag;
      std::string server;

      inline void operator<<(const rapidjson::Value &v) {
        do {
          if (!v.IsObject())
            break;
          if (v.HasMember("tag") && v["tag"].IsString())
            tag = v["tag"].GetString();
          if (v.HasMember("server") && v["server"].IsString())
            server = v["server"].GetString();
        } while (0);
      }
    };
    inline bool IsUseProxy() const {
      return IsUseBridge() || IsUseOutbound();
    }
    inline bool IsUseBridge() const {
      return !bridge.protocol.empty() && !bridge.server.empty() &&
             bridge.port > 0 && !bridge.username.empty() &&
             !bridge.password.empty();
    }
    inline bool IsUseOutbound() const {
      return !outbound.protocol.empty() && !outbound.server.empty() &&
             outbound.port > 0 && !outbound.username.empty() &&
             !outbound.password.empty();
    }
    inline ProxyInfo();
    inline ~ProxyInfo();
    Outbound outbound;
    Bridge bridge;
    Dns dns;
    inline void operator<<(const rapidjson::Value &v) {
      do {
        if (!v.IsObject())
          break;
        if (v.HasMember("outbound") && v["outbound"].IsObject())
          outbound << v["outbound"];
        if (v.HasMember("bridge") && v["bridge"].IsObject())
          bridge << v["bridge"];
        if (v.HasMember("dns") && v["dns"].IsObject())
          dns << v["dns"];
      } while (0);
    }
    inline void operator>>(rapidjson::Document &doc) const {
      if (!doc.IsObject())
        return;
      auto &allocator = doc.GetAllocator();
      if (doc.HasMember("proxyInfo"))
        doc.RemoveMember("proxyInfo");
      rapidjson::Value proxyInfoObj(rapidjson::kObjectType);
      rapidjson::Value outboundObj(rapidjson::kObjectType);
      rapidjson::Value bridgeObj(rapidjson::kObjectType);
      rapidjson::Value dnsObj(rapidjson::kObjectType);

      RAPIDJSON_ADDMEMBER_STRING(outboundObj, std::string("protocol"),
                                 outbound.protocol, allocator);
      RAPIDJSON_ADDMEMBER_STRING(outboundObj, std::string("server"),
                                 outbound.server, allocator);
      RAPIDJSON_ADDMEMBER_INT(outboundObj, std::string("port"), outbound.port,
                              allocator);
      RAPIDJSON_ADDMEMBER_STRING(outboundObj, std::string("username"),
                                 outbound.username, allocator);
      RAPIDJSON_ADDMEMBER_STRING(outboundObj, std::string("password"),
                                 outbound.password, allocator);

      RAPIDJSON_ADDMEMBER_STRING(bridgeObj, std::string("protocol"),
                                 bridge.protocol, allocator);
      RAPIDJSON_ADDMEMBER_STRING(bridgeObj, std::string("server"),
                                 bridge.server, allocator);
      RAPIDJSON_ADDMEMBER_INT(bridgeObj, std::string("port"), bridge.port,
                              allocator);
      RAPIDJSON_ADDMEMBER_INT(bridgeObj, std::string("mode"), bridge.mode,
                              allocator);
      RAPIDJSON_ADDMEMBER_STRING(bridgeObj, std::string("username"),
                                 bridge.username, allocator);
      RAPIDJSON_ADDMEMBER_STRING(bridgeObj, std::string("password"),
                                 bridge.password, allocator);

      RAPIDJSON_ADDMEMBER_STRING(dnsObj, std::string("tag"), dns.tag,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(dnsObj, std::string("server"), dns.server,
                                 allocator);

      RAPIDJSON_ADDMEMBER_OBJECT(proxyInfoObj, std::string("outbound"),
                                 outboundObj, allocator);
      RAPIDJSON_ADDMEMBER_OBJECT(proxyInfoObj, std::string("bridge"), bridgeObj,
                                 allocator);
      RAPIDJSON_ADDMEMBER_OBJECT(proxyInfoObj, std::string("dns"), dnsObj,
                                 allocator);

      RAPIDJSON_ADDMEMBER_OBJECT(doc, std::string("proxyInfo"), proxyInfoObj,
                                 allocator);
    }
  };

  struct Shop {
    inline Shop();
    inline ~Shop();

    std::string shopId;
    std::string name;
    std::string shortName;
    std::string platform;
    std::string serial;

    inline std::string GetAccountDisplayString() const {
      std::string result(serial);

      if (!result.empty()) {
        result += " / ";
      }
      result += name;

      if (result.empty()) {
        result = "-- / -- --";
      }
      return result;
    }

    inline std::string GetSerialDisplayString() const {
      return serial.empty() ? "n/a" : serial;
    }

    inline std::string GetShopShortNameString() const {
      return shortName.empty() ? "" : shortName;
    }
    inline void operator>>(rapidjson::Document &doc) const {
      if (!doc.IsObject())
        return;
      auto &allocator = doc.GetAllocator();
      if (doc.HasMember("shop"))
        doc.RemoveMember("shop");
      rapidjson::Value shopObj(rapidjson::kObjectType);
      RAPIDJSON_ADDMEMBER_STRING(shopObj, std::string("shopId"), shopId,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(shopObj, std::string("name"), name, allocator);
      RAPIDJSON_ADDMEMBER_STRING(shopObj, std::string("shortName"), shortName,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(shopObj, std::string("platform"), platform,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(shopObj, std::string("serial"), serial,
                                 allocator);
      RAPIDJSON_ADDMEMBER_OBJECT(doc, std::string("shop"), shopObj, allocator);
    }
    inline void operator<<(const rapidjson::Value &v) {
      do {
        if (!v.IsObject())
          break;
        if (v.HasMember("shopId") && v["shopId"].IsString())
          shopId = v["shopId"].GetString();
        if (v.HasMember("name") && v["name"].IsString())
          name = v["name"].GetString();
        if (v.HasMember("shortName") && v["shortName"].IsString())
          shortName = v["shortName"].GetString();
        if (v.HasMember("platform") && v["platform"].IsString())
          platform = v["platform"].GetString();
        if (v.HasMember("serial") && v["serial"].IsString())
          serial = v["serial"].GetString();
      } while (0);
    }
  };

  struct Browser {
    inline Browser();
    inline ~Browser();
    std::string version = "138";
    std::string kernel = "Chrome";
    int mapId = 0;
    inline void operator>>(rapidjson::Document &doc) const {
      if (!doc.IsObject())
        return;
      auto &allocator = doc.GetAllocator();
      if (doc.HasMember("browser"))
        doc.RemoveMember("browser");
      rapidjson::Value browserObj(rapidjson::kObjectType);
      RAPIDJSON_ADDMEMBER_STRING(browserObj, std::string("version"), version,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(browserObj, std::string("kernel"), kernel,
                                 allocator);
      RAPIDJSON_ADDMEMBER_INT(browserObj, std::string("mapId"), mapId,
                              allocator);
      RAPIDJSON_ADDMEMBER_OBJECT(doc, std::string("browser"), browserObj,
                                 allocator);
    }
    inline void operator<<(const rapidjson::Value &v) {
      do {
        if (!v.IsObject())
          break;
        if (v.HasMember("version") && v["version"].IsString())
          version = v["version"].GetString();
        if (v.HasMember("kernel") && v["kernel"].IsString())
          kernel = v["kernel"].GetString();
        if (v.HasMember("mapId") && v["mapId"].IsInt())
          mapId = v["mapId"].GetInt();
      } while (0);
    }
  };

  struct SearchEngine {
    inline SearchEngine();
    inline ~SearchEngine();

    std::string site;
    std::string siteDesc;
    std::string url;
    inline void operator>>(rapidjson::Document &doc) const {
      if (!doc.IsObject())
        return;
      auto &allocator = doc.GetAllocator();
      if (doc.HasMember("search_engine"))
        doc.RemoveMember("search_engine");
      rapidjson::Value searchEngineObj(rapidjson::kObjectType);
      RAPIDJSON_ADDMEMBER_STRING(searchEngineObj, std::string("site"), site,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(searchEngineObj, std::string("siteDesc"),
                                 siteDesc, allocator);
      RAPIDJSON_ADDMEMBER_STRING(searchEngineObj, std::string("url"), url,
                                 allocator);
      RAPIDJSON_ADDMEMBER_OBJECT(doc, std::string("search_engine"),
                                 searchEngineObj, allocator);
    }
    inline void operator<<(const rapidjson::Value &v) {
      do {
        if (!v.IsObject())
          break;
        if (v.HasMember("site") && v["site"].IsString())
          site = v["site"].GetString();
        if (v.HasMember("siteDesc") && v["siteDesc"].IsString())
          siteDesc = v["siteDesc"].GetString();
        if (v.HasMember("url") && v["url"].IsString())
          url = v["url"].GetString();
      } while (0);
    }
  };

  struct DataSync {
    inline DataSync();
    inline ~DataSync();
    int devices = 0;
    int cookie = 0;
    int password = 0;
    int bookmarks = 0;
    int local_storage = 0;
    int session_storage = 0;
    int plugin = 0;
    int history = 0;
    inline void operator>>(rapidjson::Document &doc) const {
      if (!doc.IsObject())
        return;
      auto &allocator = doc.GetAllocator();
      if (doc.HasMember("data_sync"))
        doc.RemoveMember("data_sync");
      rapidjson::Value dataSyncObj(rapidjson::kObjectType);
      RAPIDJSON_ADDMEMBER_INT(dataSyncObj, std::string("devices"), devices,
                              allocator);
      RAPIDJSON_ADDMEMBER_INT(dataSyncObj, std::string("cookie"), cookie,
                              allocator);
      RAPIDJSON_ADDMEMBER_INT(dataSyncObj, std::string("password"), password,
                              allocator);
      RAPIDJSON_ADDMEMBER_INT(dataSyncObj, std::string("bookmarks"), bookmarks,
                              allocator);
      RAPIDJSON_ADDMEMBER_INT(dataSyncObj, std::string("local_storage"),
                              local_storage, allocator);
      RAPIDJSON_ADDMEMBER_INT(dataSyncObj, std::string("session_storage"),
                              session_storage, allocator);
      RAPIDJSON_ADDMEMBER_INT(dataSyncObj, std::string("plugin"), plugin,
                              allocator);
      RAPIDJSON_ADDMEMBER_INT(dataSyncObj, std::string("history"), history,
                              allocator);
      RAPIDJSON_ADDMEMBER_OBJECT(doc, std::string("data_sync"), dataSyncObj,
                                 allocator);
    }
    inline void operator<<(const rapidjson::Value &v) {
      do {
        if (!v.IsObject())
          break;
        if (v.HasMember("devices") && v["devices"].IsInt())
          devices = v["devices"].GetInt();
        if (v.HasMember("cookie") && v["cookie"].IsInt())
          cookie = v["cookie"].GetInt();
        if (v.HasMember("password") && v["password"].IsInt())
          password = v["password"].GetInt();
        if (v.HasMember("bookmarks") && v["bookmarks"].IsInt())
          bookmarks = v["bookmarks"].GetInt();
        if (v.HasMember("local_storage") && v["local_storage"].IsInt())
          local_storage = v["local_storage"].GetInt();
        if (v.HasMember("session_storage") && v["session_storage"].IsInt())
          session_storage = v["session_storage"].GetInt();
        if (v.HasMember("plugin") && v["plugin"].IsInt())
          plugin = v["plugin"].GetInt();
        if (v.HasMember("history") && v["history"].IsInt())
          history = v["history"].GetInt();
      } while (0);
    }
  };

  struct Finger {
    enum class WebRTCIPHandlingProtectedType : int {
      kWebRTCIPHandlingDefaultPublicInterfaceOnly = 0,
      kWebRTCIPHandlingDefaultProtected = 1,
      kWebRTCIPHandlingDefaultPublicAndPrivateInterfaces = 2,
      kWebRTCIPHandlingDisableNonProxiedUdp = 3,
    };
    struct ClientHints {
      inline ClientHints();
      inline ~ClientHints();
      std::string model;
      std::string mobile;
      std::string bitness;
      std::string platform;
      std::string architecture;
      std::string uaFullVersion;
      std::string platformVersion;
      std::string Product;
      bool wow64 = false;
      std::vector<std::string> form_factors;

      inline void operator<<(const rapidjson::Value &v) {
        if (!v.IsObject())
          return;
        if (v.HasMember("model") && v["model"].IsString())
          model = v["model"].GetString();
        if (v.HasMember("mobile") && v["mobile"].IsString())
          mobile = v["mobile"].GetString();
        if (v.HasMember("bitness") && v["bitness"].IsString())
          bitness = v["bitness"].GetString();
        if (v.HasMember("platform") && v["platform"].IsString())
          platform = v["platform"].GetString();
        if (v.HasMember("architecture") && v["architecture"].IsString())
          architecture = v["architecture"].GetString();
        if (v.HasMember("uaFullVersion") && v["uaFullVersion"].IsString())
          uaFullVersion = v["uaFullVersion"].GetString();
        if (v.HasMember("platformVersion") && v["platformVersion"].IsString())
          platformVersion = v["platformVersion"].GetString();
        if (v.HasMember("Product") && v["Product"].IsString())
          Product = v["Product"].GetString();
        if (v.HasMember("wow64") && v["wow64"].IsBool())
          wow64 = v["wow64"].GetBool();
        if (v.HasMember("form_factors") && v["form_factors"].IsArray()) {
          form_factors.clear();
          for (const auto &item : v["form_factors"].GetArray()) {
            if (item.IsString()) {
              form_factors.push_back(item.GetString());
            }
          }
        }
      }
    };

    struct Plugin {
      inline Plugin();
      inline ~Plugin();
      inline Plugin(const Plugin &);
      inline Plugin &operator=(const Plugin &);
      inline Plugin(Plugin &&);
      inline Plugin &operator=(Plugin &&);

      std::string name;
      std::string version;
      std::string filename;
      std::string description;

      inline void operator<<(const rapidjson::Value &v) {
        if (!v.IsObject())
          return;
        if (v.HasMember("name") && v["name"].IsString())
          name = v["name"].GetString();
        if (v.HasMember("version") && v["version"].IsString())
          version = v["version"].GetString();
        if (v.HasMember("filename") && v["filename"].IsString())
          filename = v["filename"].GetString();
        if (v.HasMember("description") && v["description"].IsString())
          description = v["description"].GetString();
      }
    };

    struct MediaMime {
      inline MediaMime();
      inline ~MediaMime();
      std::string type;
      std::string can_play;

      inline void operator<<(const rapidjson::Value &v) {
        if (!v.IsObject())
          return;
        if (v.HasMember("type") && v["type"].IsString())
          type = v["type"].GetString();
        if (v.HasMember("can_play") && v["can_play"].IsString())
          can_play = v["can_play"].GetString();
      }
    };

    struct DeviceInput {
      inline DeviceInput();
      inline ~DeviceInput();
      std::string label;
      std::string groupId;
      std::string deviceId;

      inline void operator<<(const rapidjson::Value &v) {
        if (!v.IsObject())
          return;
        if (v.HasMember("label") && v["label"].IsString())
          label = v["label"].GetString();
        if (v.HasMember("groupId") && v["groupId"].IsString())
          groupId = v["groupId"].GetString();
        if (v.HasMember("deviceId") && v["deviceId"].IsString())
          deviceId = v["deviceId"].GetString();
      }
    };

    struct FpSwitches {
      inline FpSwitches();
      inline ~FpSwitches();

      int fpEnableALL = 1;
      int fpEnableJS = 1;
      int fpComputerName = 1;
      int fpMacAddr = 1;
      int fpGPU = 1;
      int fpLanguage = 1;
      int fpSettingNotification = 1;
      int fpProxy = 1;
      int fpHandlePersistentPrefStore = 1;
      int fpWebRTC = 1;
      int fpBookmark = 1;
      int fpBrowserFrameSize = 1;
      int fpLogoButton = 1;
      int fpAppIcon = 1;
      int fpWinTitle = 1;
      int fpShopSN = 1;
      int fpSettingSound = 1;
      int fpTimezone = 1;
      int fpReduceUA = 1;
      int fpUA = 1;
      int fpClientHints = 1;
      int fpDoNotTrack = 1;
      int fpRestoreFocus = 1;
      int fpBlueTooth = 1;
      int fpGeoLocation = 1;
      int fpCookieEncrypt = 1;
      int fpFontsFull = 1;
      int fpHandleURL = 1;
      int fpBlockPort = 1;
      int fpCanvas = 1;
      int fpWebGL = 1;
      int fpTLS = 1;
      int fpImage = 1;
      int fpQuataStorage = 1;
      int fpAnimation = 1;
      int fpScreen = 1;
      int fpPlatform = 1;
      int fpDevice = 1;
      int fpAppCodeName = 1;
      int fpAppName = 1;
      int fpProduct = 1;
      int fpSettingVideo = 1;
      int fpMediaMimes = 1;
      int fpSVG = 1;
      int fpHardware = 1;
      int fpBattery = 1;
      int fpMediaDevice = 1;
      int fpPlugin = 1;
      int fpSpeechVoices = 1;
      int fpHardwarePref = 1;
      int fpAudioContext = 1;

      void operator>>(rapidjson::Document &doc) const {
        if (!doc.IsObject())
          return;
        auto &allocator = doc.GetAllocator();
        if (doc.HasMember("fpSwitches"))
          doc.RemoveMember("fpSwitches");
        rapidjson::Value fpSwitchesObj(rapidjson::kObjectType);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpEnableALL"),
                                fpEnableALL, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpEnableJS"),
                                fpEnableJS, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpComputerName"),
                                fpComputerName, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpMacAddr"),
                                fpMacAddr, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpGPU"), fpGPU,
                                allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpLanguage"),
                                fpLanguage, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj,
                                std::string("fpSettingNotification"),
                                fpSettingNotification, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpProxy"), fpProxy,
                                allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj,
                                std::string("fpHandlePersistentPrefStore"),
                                fpHandlePersistentPrefStore, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpWebRTC"),
                                fpWebRTC, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpBookmark"),
                                fpBookmark, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj,
                                std::string("fpBrowserFrameSize"),
                                fpBrowserFrameSize, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpLogoButton"),
                                fpLogoButton, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpAppIcon"),
                                fpAppIcon, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpWinTitle"),
                                fpWinTitle, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpShopSN"),
                                fpShopSN, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpSettingSound"),
                                fpSettingSound, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpTimezone"),
                                fpTimezone, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpReduceUA"),
                                fpReduceUA, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpUA"), fpUA,
                                allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpClientHints"),
                                fpClientHints, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpDoNotTrack"),
                                fpDoNotTrack, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpRestoreFocus"),
                                fpRestoreFocus, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpBlueTooth"),
                                fpBlueTooth, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpGeoLocation"),
                                fpGeoLocation, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpCookieEncrypt"),
                                fpCookieEncrypt, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpFontsFull"),
                                fpFontsFull, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpHandleURL"),
                                fpHandleURL, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpBlockPort"),
                                fpBlockPort, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpCanvas"),
                                fpCanvas, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpWebGL"), fpWebGL,
                                allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpTLS"), fpTLS,
                                allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpImage"), fpImage,
                                allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpQuataStorage"),
                                fpQuataStorage, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpAnimation"),
                                fpAnimation, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpScreen"),
                                fpScreen, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpPlatform"),
                                fpPlatform, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpDevice"),
                                fpDevice, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpAppCodeName"),
                                fpAppCodeName, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpAppName"),
                                fpAppName, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpProduct"),
                                fpProduct, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpSettingVideo"),
                                fpSettingVideo, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpMediaMimes"),
                                fpMediaMimes, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpSVG"), fpSVG,
                                allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpHardware"),
                                fpHardware, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpBattery"),
                                fpBattery, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpMediaDevice"),
                                fpMediaDevice, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpPlugin"),
                                fpPlugin, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpSpeechVoices"),
                                fpSpeechVoices, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpHardwarePref"),
                                fpHardwarePref, allocator);
        RAPIDJSON_ADDMEMBER_INT(fpSwitchesObj, std::string("fpAudioContext"),
                                fpAudioContext, allocator);
        if (doc.HasMember("finger")) {
          doc["finger"].RemoveMember("fpSwitches");
          doc["finger"].AddMember("fpSwitches", fpSwitchesObj, allocator);
        }
      }
      void operator<<(const rapidjson::Value &v) {
        if (!v.IsObject())
          return;
        if (v.HasMember("fpEnableALL") && v["fpEnableALL"].IsInt())
          fpEnableALL = v["fpEnableALL"].GetInt();
        if (v.HasMember("fpEnableJS") && v["fpEnableJS"].IsInt())
          fpEnableJS = v["fpEnableJS"].GetInt();
        if (v.HasMember("fpComputerName") && v["fpComputerName"].IsInt())
          fpComputerName = v["fpComputerName"].GetInt();
        if (v.HasMember("fpMacAddr") && v["fpMacAddr"].IsInt())
          fpMacAddr = v["fpMacAddr"].GetInt();
        if (v.HasMember("fpGPU") && v["fpGPU"].IsInt())
          fpGPU = v["fpGPU"].GetInt();
        if (v.HasMember("fpLanguage") && v["fpLanguage"].IsInt())
          fpLanguage = v["fpLanguage"].GetInt();
        if (v.HasMember("fpSettingNotification") &&
            v["fpSettingNotification"].IsInt())
          fpSettingNotification = v["fpSettingNotification"].GetInt();
        if (v.HasMember("fpProxy") && v["fpProxy"].IsInt())
          fpProxy = v["fpProxy"].GetInt();
        if (v.HasMember("fpHandlePersistentPrefStore") &&
            v["fpHandlePersistentPrefStore"].IsInt())
          fpHandlePersistentPrefStore =
              v["fpHandlePersistentPrefStore"].GetInt();
        if (v.HasMember("fpWebRTC") && v["fpWebRTC"].IsInt())
          fpWebRTC = v["fpWebRTC"].GetInt();
        if (v.HasMember("fpBookmark") && v["fpBookmark"].IsInt())
          fpBookmark = v["fpBookmark"].GetInt();
        if (v.HasMember("fpBrowserFrameSize") &&
            v["fpBrowserFrameSize"].IsInt())
          fpBrowserFrameSize = v["fpBrowserFrameSize"].GetInt();
        if (v.HasMember("fpLogoButton") && v["fpLogoButton"].IsInt())
          fpLogoButton = v["fpLogoButton"].GetInt();
        if (v.HasMember("fpAppIcon") && v["fpAppIcon"].IsInt())
          fpAppIcon = v["fpAppIcon"].GetInt();
        if (v.HasMember("fpWinTitle") && v["fpWinTitle"].IsInt())
          fpWinTitle = v["fpWinTitle"].GetInt();
        if (v.HasMember("fpShopSN") && v["fpShopSN"].IsInt())
          fpShopSN = v["fpShopSN"].GetInt();
        if (v.HasMember("fpSettingSound") && v["fpSettingSound"].IsInt())
          fpSettingSound = v["fpSettingSound"].GetInt();
        if (v.HasMember("fpTimezone") && v["fpTimezone"].IsInt())
          fpTimezone = v["fpTimezone"].GetInt();
        if (v.HasMember("fpReduceUA") && v["fpReduceUA"].IsInt())
          fpReduceUA = v["fpReduceUA"].GetInt();
        if (v.HasMember("fpUA") && v["fpUA"].IsInt())
          fpUA = v["fpUA"].GetInt();
        if (v.HasMember("fpClientHints") && v["fpClientHints"].IsInt())
          fpClientHints = v["fpClientHints"].GetInt();
        if (v.HasMember("fpDoNotTrack") && v["fpDoNotTrack"].IsInt())
          fpDoNotTrack = v["fpDoNotTrack"].GetInt();
        if (v.HasMember("fpRestoreFocus") && v["fpRestoreFocus"].IsInt())
          fpRestoreFocus = v["fpRestoreFocus"].GetInt();
        if (v.HasMember("fpBlueTooth") && v["fpBlueTooth"].IsInt())
          fpBlueTooth = v["fpBlueTooth"].GetInt();
        if (v.HasMember("fpGeoLocation") && v["fpGeoLocation"].IsInt())
          fpGeoLocation = v["fpGeoLocation"].GetInt();
        if (v.HasMember("fpCookieEncrypt") && v["fpCookieEncrypt"].IsInt())
          fpCookieEncrypt = v["fpCookieEncrypt"].GetInt();
        if (v.HasMember("fpFontsFull") && v["fpFontsFull"].IsInt())
          fpFontsFull = v["fpFontsFull"].GetInt();
        if (v.HasMember("fpHandleURL") && v["fpHandleURL"].IsInt())
          fpHandleURL = v["fpHandleURL"].GetInt();
        if (v.HasMember("fpBlockPort") && v["fpBlockPort"].IsInt())
          fpBlockPort = v["fpBlockPort"].GetInt();
        if (v.HasMember("fpCanvas") && v["fpCanvas"].IsInt())
          fpCanvas = v["fpCanvas"].GetInt();
        if (v.HasMember("fpWebGL") && v["fpWebGL"].IsInt())
          fpWebGL = v["fpWebGL"].GetInt();
        if (v.HasMember("fpTLS") && v["fpTLS"].IsInt())
          fpTLS = v["fpTLS"].GetInt();
        if (v.HasMember("fpImage") && v["fpImage"].IsInt())
          fpImage = v["fpImage"].GetInt();
        if (v.HasMember("fpQuataStorage") && v["fpQuataStorage"].IsInt())
          fpQuataStorage = v["fpQuataStorage"].GetInt();
        if (v.HasMember("fpAnimation") && v["fpAnimation"].IsInt())
          fpAnimation = v["fpAnimation"].GetInt();
        if (v.HasMember("fpScreen") && v["fpScreen"].IsInt())
          fpScreen = v["fpScreen"].GetInt();
        if (v.HasMember("fpPlatform") && v["fpPlatform"].IsInt())
          fpPlatform = v["fpPlatform"].GetInt();
        if (v.HasMember("fpDevice") && v["fpDevice"].IsInt())
          fpDevice = v["fpDevice"].GetInt();
        if (v.HasMember("fpAppCodeName") && v["fpAppCodeName"].IsInt())
          fpAppCodeName = v["fpAppCodeName"].GetInt();
        if (v.HasMember("fpAppName") && v["fpAppName"].IsInt())
          fpAppName = v["fpAppName"].GetInt();
        if (v.HasMember("fpProduct") && v["fpProduct"].IsInt())
          fpProduct = v["fpProduct"].GetInt();
        if (v.HasMember("fpSettingVideo") && v["fpSettingVideo"].IsInt())
          fpSettingVideo = v["fpSettingVideo"].GetInt();
        if (v.HasMember("fpMediaMimes") && v["fpMediaMimes"].IsInt())
          fpMediaMimes = v["fpMediaMimes"].GetInt();
        if (v.HasMember("fpSVG") && v["fpSVG"].IsInt())
          fpSVG = v["fpSVG"].GetInt();
        if (v.HasMember("fpHardware") && v["fpHardware"].IsInt())
          fpHardware = v["fpHardware"].GetInt();
        if (v.HasMember("fpBattery") && v["fpBattery"].IsInt())
          fpBattery = v["fpBattery"].GetInt();
        if (v.HasMember("fpMediaDevice") && v["fpMediaDevice"].IsInt())
          fpMediaDevice = v["fpMediaDevice"].GetInt();
        if (v.HasMember("fpPlugin") && v["fpPlugin"].IsInt())
          fpPlugin = v["fpPlugin"].GetInt();
        if (v.HasMember("fpSpeechVoices") && v["fpSpeechVoices"].IsInt())
          fpSpeechVoices = v["fpSpeechVoices"].GetInt();
        if (v.HasMember("fpHardwarePref") && v["fpHardwarePref"].IsInt())
          fpHardwarePref = v["fpHardwarePref"].GetInt();
        if (v.HasMember("fpAudioContext") && v["fpAudioContext"].IsInt())
          fpAudioContext = v["fpAudioContext"].GetInt();
      }
    };
    struct SpeechVoice {
      inline SpeechVoice();
      inline ~SpeechVoice();
      inline SpeechVoice(const SpeechVoice &);
      inline SpeechVoice &operator=(const SpeechVoice &);
      inline SpeechVoice(SpeechVoice &&);
      inline SpeechVoice &operator=(SpeechVoice &&);

      std::string lang;
      std::string name;
      std::string voice_uri;
      int is_default = 0;
      int is_local_service = 0;

      inline void operator<<(const rapidjson::Value &v) {
        if (!v.IsObject())
          return;
        if (v.HasMember("lang") && v["lang"].IsString())
          lang = v["lang"].GetString();
        if (v.HasMember("name") && v["name"].IsString())
          name = v["name"].GetString();
        if (v.HasMember("voice_uri") && v["voice_uri"].IsString())
          voice_uri = v["voice_uri"].GetString();
        if (v.HasMember("is_default") && v["is_default"].IsInt())
          is_default = v["is_default"].GetInt();
        if (v.HasMember("is_local_service") && v["is_local_service"].IsInt())
          is_local_service = v["is_local_service"].GetInt();
      }
    };

    struct Geographic {
      inline Geographic();
      inline ~Geographic();
      int enable = 0;
      std::string longitude;
      std::string latitude;
      std::string accuracy;

      inline void operator<<(const rapidjson::Value &v) {
        if (!v.IsObject())
          return;
        if (v.HasMember("enable") && v["enable"].IsInt())
          enable = v["enable"].GetInt();
        if (v.HasMember("longitude") && v["longitude"].IsString())
          longitude = v["longitude"].GetString();
        if (v.HasMember("latitude") && v["latitude"].IsString())
          latitude = v["latitude"].GetString();
        if (v.HasMember("accuracy") && v["accuracy"].IsString())
          accuracy = v["accuracy"].GetString();
      }
    };
    inline void GetScreenSize(double &width, double &height) const {
      if (screenSize.empty())
        return;
      size_t x_pos = screenSize.find('x');
      if (x_pos != std::string::npos) {
        width = std::stod(screenSize.substr(0, x_pos));
        height = std::stod(screenSize.substr(x_pos + 1));
      }
    }
    inline bool EnabledNoiseAudio() const {
      return !!audio;
    }
    inline int GetCommonNoiseComputingFactor() const {
      return commonPerturb;
    }
    inline bool EnabledNoiseWebgl() const {
      return webglEnabled != 0;
    }
    inline bool EnabledNoiseCanvas() const {
      return canvasPerturbEnabled != 0;
    }
    inline bool EnabledNoiseFont() const {
      return canvasFontEnabled != 0;
    }
    inline bool EnabledImage() const {
      return !enablepic;
    }
    inline bool EnabledNotification() const {
      return !enablenotice;
    }
    inline bool EnabledAudio() const {
      return !enablesound;
    }
    inline bool EnabledVideo() const {
      return !enablevideo;
    }
    inline bool EnabledBluetooth() const {
      return bluetoothDisabled == 0;
    }

    inline long long GetQuataStorage() const {
      long long result = 0;
      if (!storage.empty()) {
        std::stringstream ss(storage);
        ss >> result;
      }
      return result;
    }

    inline Finger();
    inline ~Finger();

    std::string dnt;
    std::string computerName;
    std::string macAddress;
    std::string userAgent;
    std::string appVersion;
    std::string platform;
    std::string vendor;
    std::string appCodeName;
    std::string appName;
    std::string product;
    std::string browser;
    std::vector<std::string> languages;
    std::string acceptLanguage = "zh-CN,zh;q=0.9";
    std::string timezone = "Asia/Shanghai";
    int deviceMemory = 8;
    int cpu = 4;
    std::string screenSize = "2256x1504.5";
    double devicePixelRatio = 1.0;
    int colorDepth = 24;
    std::string colorGamut;
    std::string batteryType;
    int batteryLevel = 0;
    std::string batteryLevelF;
    bool batteryCharging = false;
    int batteryChargingTime = 0;
    int batteryDischargingTime = 0;
    std::string pluginType;
    std::string fontsFull;
    std::string fonts;
    std::set<std::string> setFonts;
    std::set<std::string> setFontsFull;
    std::string webglType;
    std::string webglVendor;
    std::string webglRenderer;

    FpSwitches fpSwitches;
    double canvasPerturbX = 0.0;
    double canvasPerturbY = 0.0;
    double canvasFontY = 0.0;
    double canvasFontX = 0.0;
    int canvasPerturbEnabled = 0;
    int canvasFontEnabled = 1;
    int webglEnabled = 0;
    double webglPerturbX = 0.0;
    double audio = 0.0;
    int bluetoothDisabled = 0;
    std::string mediaType;
    std::string webrtcMode;
    std::string webrtcPublicIp;
    std::string webrtcInnerIp;
    bool blockPortScanning = false;
    std::string portScanningWhitelist;
    double rectDX = 0.0;
    double glyphsMeasureTextDX = 0.0;
    double textMetricsBoundingDX = 0.0;
    std::string windowSize;
    std::string storage;
    int enableCookie = 0;
    int enableopen = 0;
    int enablenotice = 0;
    int clientRects = 0;
    int enablepic = 0;
    std::string picsize;
    int enablesound = 0;
    int enablevideo = 0;
    int enableGPU = 0;
    int commonPerturb = 0;
    int version = 0;
    ClientHints clientHints;
    std::vector<Plugin> plugins;
    std::vector<DeviceInput> videoInputs;
    std::vector<DeviceInput> audioInputs;
    std::vector<DeviceInput> audioOutputs;
    std::vector<std::string> speeches;
    std::vector<SpeechVoice> speechVoices;
    Geographic geographic;
    std::vector<MediaMime> mediaMimes;
    WebRTCIPHandlingProtectedType webRTCIPHandlingProtectedType =
        WebRTCIPHandlingProtectedType::
            kWebRTCIPHandlingDefaultPublicInterfaceOnly;
    inline void operator>>(rapidjson::Document &doc) const {
      if (!doc.IsObject())
        return;
      auto &allocator = doc.GetAllocator();
      if (doc.HasMember("finger"))
        doc.RemoveMember("finger");
      rapidjson::Value fingerObj(rapidjson::kObjectType);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("dnt"), dnt, allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("computerName"),
                                 computerName, allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("macAddress"),
                                 macAddress, allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("userAgent"), userAgent,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("appVersion"),
                                 appVersion, allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("platform"), platform,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("vendor"), vendor,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("appCodeName"),
                                 appCodeName, allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("appName"), appName,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("product"), product,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("browser"), browser,
                                 allocator);
      rapidjson::Value languagesArray(rapidjson::kArrayType);
      for (const auto &lang : languages) {
        languagesArray.PushBack(
            rapidjson::Value().SetString(lang.c_str(), allocator).Move(),
            allocator);
      }
      RAPIDJSON_ADDMEMBER_OBJECT(fingerObj, std::string("languages"),
                                 languagesArray, allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("acceptLanguage"),
                                 acceptLanguage, allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("timezone"), timezone,
                                 allocator);
      RAPIDJSON_ADDMEMBER_INT(fingerObj, std::string("deviceMemory"),
                              deviceMemory, allocator);
      RAPIDJSON_ADDMEMBER_INT(fingerObj, std::string("cpu"), cpu, allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("screenSize"),
                                 screenSize, allocator);
      RAPIDJSON_ADDMEMBER_DOUBLE(fingerObj, std::string("devicePixelRatio"),
                                 devicePixelRatio, allocator);
      RAPIDJSON_ADDMEMBER_INT(fingerObj, std::string("colorDepth"), colorDepth,
                              allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("colorGamut"),
                                 colorGamut, allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("batteryType"),
                                 batteryType, allocator);
      RAPIDJSON_ADDMEMBER_INT(fingerObj, std::string("batteryLevel"),
                              batteryLevel, allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("batteryLevelF"),
                                 batteryLevelF, allocator);
      RAPIDJSON_ADDMEMBER_BOOL(fingerObj, std::string("batteryCharging"),
                               batteryCharging, allocator);
      RAPIDJSON_ADDMEMBER_INT(fingerObj, std::string("batteryChargingTime"),
                              batteryChargingTime, allocator);
      RAPIDJSON_ADDMEMBER_INT(fingerObj, std::string("batteryDischargingTime"),
                              batteryDischargingTime, allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("pluginType"),
                                 pluginType, allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("fontsFull"), fontsFull,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("fonts"), fonts,
                                 allocator);
      rapidjson::Value fontsArray(rapidjson::kArrayType);
      for (const auto &font : setFonts) {
        fontsArray.PushBack(
            rapidjson::Value().SetString(font.c_str(), allocator).Move(),
            allocator);
      }
      RAPIDJSON_ADDMEMBER_OBJECT(fingerObj, std::string("setFonts"), fontsArray,
                                 allocator);
      rapidjson::Value fontsFullArray(rapidjson::kArrayType);
      for (const auto &font : setFontsFull) {
        fontsFullArray.PushBack(
            rapidjson::Value().SetString(font.c_str(), allocator).Move(),
            allocator);
      }
      RAPIDJSON_ADDMEMBER_OBJECT(fingerObj, std::string("setFontsFull"),
                                 fontsFullArray, allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("webglType"), webglType,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("webglVendor"),
                                 webglVendor, allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("webglRenderer"),
                                 webglRenderer, allocator);
      RAPIDJSON_ADDMEMBER_DOUBLE(fingerObj, std::string("canvasPerturbX"),
                                 canvasPerturbX, allocator);
      RAPIDJSON_ADDMEMBER_DOUBLE(fingerObj, std::string("canvasPerturbY"),
                                 canvasPerturbY, allocator);
      RAPIDJSON_ADDMEMBER_DOUBLE(fingerObj, std::string("canvasFontY"),
                                 canvasFontY, allocator);
      RAPIDJSON_ADDMEMBER_DOUBLE(fingerObj, std::string("canvasFontX"),
                                 canvasFontX, allocator);
      RAPIDJSON_ADDMEMBER_INT(fingerObj, std::string("canvasPerturbEnabled"),
                              canvasPerturbEnabled, allocator);
      RAPIDJSON_ADDMEMBER_INT(fingerObj, std::string("canvasFontEnabled"),
                              canvasFontEnabled, allocator);
      RAPIDJSON_ADDMEMBER_INT(fingerObj, std::string("webglEnabled"),
                              webglEnabled, allocator);
      RAPIDJSON_ADDMEMBER_DOUBLE(fingerObj, std::string("webglPerturbX"),
                                 webglPerturbX, allocator);
      RAPIDJSON_ADDMEMBER_DOUBLE(fingerObj, std::string("audio"), audio,
                                 allocator);
      RAPIDJSON_ADDMEMBER_INT(fingerObj, std::string("bluetoothDisabled"),
                              bluetoothDisabled, allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("mediaType"), mediaType,
                                 allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("webrtcMode"),
                                 webrtcMode, allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("webrtcPublicIp"),
                                 webrtcPublicIp, allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("webrtcInnerIp"),
                                 webrtcInnerIp, allocator);
      RAPIDJSON_ADDMEMBER_BOOL(fingerObj, std::string("blockPortScanning"),
                               blockPortScanning, allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj,
                                 std::string("portScanningWhitelist"),
                                 portScanningWhitelist, allocator);
      RAPIDJSON_ADDMEMBER_DOUBLE(fingerObj, std::string("rectDX"), rectDX,
                                 allocator);
      RAPIDJSON_ADDMEMBER_DOUBLE(fingerObj, std::string("glyphsMeasureTextDX"),
                                 glyphsMeasureTextDX, allocator);
      RAPIDJSON_ADDMEMBER_DOUBLE(fingerObj,
                                 std::string("textMetricsBoundingDX"),
                                 textMetricsBoundingDX, allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("windowSize"),
                                 windowSize, allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("storage"), storage,
                                 allocator);
      RAPIDJSON_ADDMEMBER_INT(fingerObj, std::string("enableCookie"),
                              enableCookie, allocator);
      RAPIDJSON_ADDMEMBER_INT(fingerObj, std::string("enableopen"), enableopen,
                              allocator);
      RAPIDJSON_ADDMEMBER_INT(fingerObj, std::string("enablenotice"),
                              enablenotice, allocator);
      RAPIDJSON_ADDMEMBER_INT(fingerObj, std::string("clientRects"),
                              clientRects, allocator);
      RAPIDJSON_ADDMEMBER_INT(fingerObj, std::string("enablepic"), enablepic,
                              allocator);
      RAPIDJSON_ADDMEMBER_STRING(fingerObj, std::string("picsize"), picsize,
                                 allocator);
      RAPIDJSON_ADDMEMBER_INT(fingerObj, std::string("enablesound"),
                              enablesound, allocator);
      RAPIDJSON_ADDMEMBER_INT(fingerObj, std::string("enablevideo"),
                              enablevideo, allocator);
      RAPIDJSON_ADDMEMBER_INT(fingerObj, std::string("enableGPU"), enableGPU,
                              allocator);
      RAPIDJSON_ADDMEMBER_INT(fingerObj, std::string("commonPerturb"),
                              commonPerturb, allocator);
      RAPIDJSON_ADDMEMBER_INT(fingerObj, std::string("version"), version,
                              allocator);
      rapidjson::Value clientHintsObj(rapidjson::kObjectType);
      RAPIDJSON_ADDMEMBER_STRING(clientHintsObj, std::string("model"),
                                 clientHints.model, allocator);
      RAPIDJSON_ADDMEMBER_STRING(clientHintsObj, std::string("mobile"),
                                 clientHints.mobile, allocator);
      RAPIDJSON_ADDMEMBER_STRING(clientHintsObj, std::string("bitness"),
                                 clientHints.bitness, allocator);
      RAPIDJSON_ADDMEMBER_BOOL(clientHintsObj, std::string("wow64"),
                               clientHints.wow64, allocator);
      RAPIDJSON_ADDMEMBER_STRING(clientHintsObj, std::string("platform"),
                                 clientHints.platform, allocator);
      RAPIDJSON_ADDMEMBER_STRING(clientHintsObj, std::string("architecture"),
                                 clientHints.architecture, allocator);
      RAPIDJSON_ADDMEMBER_STRING(clientHintsObj, std::string("uaFullVersion"),
                                 clientHints.uaFullVersion, allocator);
      RAPIDJSON_ADDMEMBER_STRING(clientHintsObj, std::string("platformVersion"),
                                 clientHints.platformVersion, allocator);
      RAPIDJSON_ADDMEMBER_STRING(clientHintsObj, std::string("Product"),
                                 clientHints.Product, allocator);
      rapidjson::Value form_factorsObj(rapidjson::kArrayType);
      for (const auto &ff : clientHints.form_factors) {
        form_factorsObj.PushBack(
            rapidjson::Value().SetString(ff.c_str(), allocator).Move(),
            allocator);
      }
      RAPIDJSON_ADDMEMBER_OBJECT(clientHintsObj, std::string("form_factors"),
                                 form_factorsObj, allocator);
      RAPIDJSON_ADDMEMBER_OBJECT(fingerObj, std::string("ClientHints"),
                                 clientHintsObj, allocator);
      rapidjson::Value pluginsArray(rapidjson::kArrayType);
      for (const auto &plugin : plugins) {
        rapidjson::Value pluginObj(rapidjson::kObjectType);
        RAPIDJSON_ADDMEMBER_STRING(pluginObj, std::string("name"), plugin.name,
                                   allocator);
        RAPIDJSON_ADDMEMBER_STRING(pluginObj, std::string("version"),
                                   plugin.version, allocator);
        RAPIDJSON_ADDMEMBER_STRING(pluginObj, std::string("filename"),
                                   plugin.filename, allocator);
        RAPIDJSON_ADDMEMBER_STRING(pluginObj, std::string("description"),
                                   plugin.description, allocator);
        pluginsArray.PushBack(pluginObj, allocator);
      }
      RAPIDJSON_ADDMEMBER_OBJECT(fingerObj, std::string("plugins"),
                                 pluginsArray, allocator);
      rapidjson::Value videoInputsArray(rapidjson::kArrayType);
      for (const auto &input : videoInputs) {
        rapidjson::Value inputObj(rapidjson::kObjectType);
        RAPIDJSON_ADDMEMBER_STRING(inputObj, std::string("label"), input.label,
                                   allocator);
        RAPIDJSON_ADDMEMBER_STRING(inputObj, std::string("groupId"),
                                   input.groupId, allocator);
        RAPIDJSON_ADDMEMBER_STRING(inputObj, std::string("deviceId"),
                                   input.deviceId, allocator);
        videoInputsArray.PushBack(inputObj, allocator);
      }
      RAPIDJSON_ADDMEMBER_OBJECT(fingerObj, std::string("videoInputs"),
                                 videoInputsArray, allocator);
      rapidjson::Value audioInputsArray(rapidjson::kArrayType);
      for (const auto &input : audioInputs) {
        rapidjson::Value inputObj(rapidjson::kObjectType);
        RAPIDJSON_ADDMEMBER_STRING(inputObj, std::string("label"), input.label,
                                   allocator);
        RAPIDJSON_ADDMEMBER_STRING(inputObj, std::string("groupId"),
                                   input.groupId, allocator);
        RAPIDJSON_ADDMEMBER_STRING(inputObj, std::string("deviceId"),
                                   input.deviceId, allocator);
        audioInputsArray.PushBack(inputObj, allocator);
      }
      RAPIDJSON_ADDMEMBER_OBJECT(fingerObj, std::string("audioInputs"),
                                 audioInputsArray, allocator);
      rapidjson::Value audioOutputsArray(rapidjson::kArrayType);
      for (const auto &output : audioOutputs) {
        rapidjson::Value outputObj(rapidjson::kObjectType);
        RAPIDJSON_ADDMEMBER_STRING(outputObj, std::string("label"),
                                   output.label, allocator);
        RAPIDJSON_ADDMEMBER_STRING(outputObj, std::string("groupId"),
                                   output.groupId, allocator);
        RAPIDJSON_ADDMEMBER_STRING(outputObj, std::string("deviceId"),
                                   output.deviceId, allocator);
        audioOutputsArray.PushBack(outputObj, allocator);
      }
      RAPIDJSON_ADDMEMBER_OBJECT(fingerObj, std::string("audioOutputs"),
                                 audioOutputsArray, allocator);
      rapidjson::Value speechesArray(rapidjson::kArrayType);
      for (const auto &speech : speeches) {
        speechesArray.PushBack(
            rapidjson::Value().SetString(speech.c_str(), allocator).Move(),
            allocator);
      }
      RAPIDJSON_ADDMEMBER_OBJECT(fingerObj, std::string("speeches"),
                                 speechesArray, allocator);
      rapidjson::Value speechVoicesArray(rapidjson::kArrayType);
      for (const auto &voice : speechVoices) {
        rapidjson::Value voiceObj(rapidjson::kObjectType);
        RAPIDJSON_ADDMEMBER_STRING(voiceObj, std::string("lang"), voice.lang,
                                   allocator);
        RAPIDJSON_ADDMEMBER_STRING(voiceObj, std::string("name"), voice.name,
                                   allocator);
        RAPIDJSON_ADDMEMBER_STRING(voiceObj, std::string("voice_uri"),
                                   voice.voice_uri, allocator);
        RAPIDJSON_ADDMEMBER_INT(voiceObj, std::string("is_default"),
                                voice.is_default, allocator);
        RAPIDJSON_ADDMEMBER_INT(voiceObj, std::string("is_local_service"),
                                voice.is_local_service, allocator);
        speechVoicesArray.PushBack(voiceObj, allocator);
      }
      RAPIDJSON_ADDMEMBER_OBJECT(fingerObj, std::string("speechVoices"),
                                 speechVoicesArray, allocator);
      rapidjson::Value geographicObj(rapidjson::kObjectType);
      RAPIDJSON_ADDMEMBER_INT(geographicObj, std::string("enable"),
                              geographic.enable, allocator);
      RAPIDJSON_ADDMEMBER_STRING(geographicObj, std::string("longitude"),
                                 geographic.longitude, allocator);
      RAPIDJSON_ADDMEMBER_STRING(geographicObj, std::string("latitude"),
                                 geographic.latitude, allocator);
      RAPIDJSON_ADDMEMBER_STRING(geographicObj, std::string("accuracy"),
                                 geographic.accuracy, allocator);
      RAPIDJSON_ADDMEMBER_OBJECT(fingerObj, std::string("geographic"),
                                 geographicObj, allocator);
      RAPIDJSON_ADDMEMBER_OBJECT(doc, std::string("finger"), fingerObj,
                                 allocator);
      fpSwitches >> doc;
    }
    inline void operator<<(const rapidjson::Value &v) {
      if (!v.IsObject())
        return;
      if (v.HasMember("dnt") && v["dnt"].IsString())
        dnt = v["dnt"].GetString();
      if (v.HasMember("computerName") && v["computerName"].IsString())
        computerName = v["computerName"].GetString();
      if (v.HasMember("macAddress") && v["macAddress"].IsString())
        macAddress = v["macAddress"].GetString();
      if (v.HasMember("userAgent") && v["userAgent"].IsString())
        userAgent = v["userAgent"].GetString();
      if (v.HasMember("appVersion") && v["appVersion"].IsString())
        appVersion = v["appVersion"].GetString();
      if (v.HasMember("platform") && v["platform"].IsString())
        platform = v["platform"].GetString();
      if (v.HasMember("vendor") && v["vendor"].IsString())
        vendor = v["vendor"].GetString();
      if (v.HasMember("appCodeName") && v["appCodeName"].IsString())
        appCodeName = v["appCodeName"].GetString();
      if (v.HasMember("appName") && v["appName"].IsString())
        appName = v["appName"].GetString();
      if (v.HasMember("product") && v["product"].IsString())
        product = v["product"].GetString();
      if (v.HasMember("browser") && v["browser"].IsString())
        browser = v["browser"].GetString();
      if (v.HasMember("languages") && v["languages"].IsArray()) {
        languages.clear();
        for (auto &lang : v["languages"].GetArray()) {
          if (lang.IsString())
            languages.push_back(lang.GetString());
        }
      }
      if (v.HasMember("acceptLanguage") && v["acceptLanguage"].IsString())
        acceptLanguage = v["acceptLanguage"].GetString();
      if (v.HasMember("timezone") && v["timezone"].IsString())
        timezone = v["timezone"].GetString();
      if (v.HasMember("deviceMemory") && v["deviceMemory"].IsInt())
        deviceMemory = v["deviceMemory"].GetInt();
      if (v.HasMember("cpu") && v["cpu"].IsInt())
        cpu = v["cpu"].GetInt();
      if (v.HasMember("screenSize") && v["screenSize"].IsString())
        screenSize = v["screenSize"].GetString();
      if (v.HasMember("devicePixelRatio") && v["devicePixelRatio"].IsNumber())
        devicePixelRatio = v["devicePixelRatio"].GetDouble();
      if (v.HasMember("colorDepth") && v["colorDepth"].IsInt())
        colorDepth = v["colorDepth"].GetInt();
      if (v.HasMember("colorGamut") && v["colorGamut"].IsString())
        colorGamut = v["colorGamut"].GetString();
      if (v.HasMember("batteryType") && v["batteryType"].IsString())
        batteryType = v["batteryType"].GetString();
      if (v.HasMember("batteryLevel") && v["batteryLevel"].IsInt())
        batteryLevel = v["batteryLevel"].GetInt();
      if (v.HasMember("batteryLevelF") && v["batteryLevelF"].IsString())
        batteryLevelF = v["batteryLevelF"].GetString();
      if (v.HasMember("batteryCharging") && v["batteryCharging"].IsBool())
        batteryCharging = v["batteryCharging"].GetBool();
      if (v.HasMember("batteryChargingTime") &&
          v["batteryChargingTime"].IsInt())
        batteryChargingTime = v["batteryChargingTime"].GetInt();
      if (v.HasMember("batteryDischargingTime") &&
          v["batteryDischargingTime"].IsInt())
        batteryDischargingTime = v["batteryDischargingTime"].GetInt();
      if (v.HasMember("pluginType") && v["pluginType"].IsString())
        pluginType = v["pluginType"].GetString();
      if (v.HasMember("fontsFull") && v["fontsFull"].IsString()) {
        fontsFull = v["fontsFull"].GetString();
        setFontsFull = SplitFontsUnique(fontsFull);
      }
      if (v.HasMember("fonts") && v["fonts"].IsString()) {
        fonts = v["fonts"].GetString();
        setFonts = SplitFontsUnique(fonts);
        const std::vector<std::string> fallback = {
            "Arial",           "Calibri",
            "Verdana",         "Segoe UI",
            "Segoe UI Symbol", "Segoe UI Emoji",
            "Yu Gothic",       "MS Gothic",
            "MS PGothic",      "MS UI Gothic",
            "Malgun Gothic",   "Microsoft YaHei",
            "SimSun",          "Microsoft JhengHei",
            "PMingLiU",        "Leelawadee UI",
            "Nirmala UI",      "Myanmar Text",
            "Ebrima",
        };
        for (const auto &it : fallback)
          setFonts.insert(it);
      }
      if (v.HasMember("fpSwitches") && v["fpSwitches"].IsObject())
        fpSwitches << v["fpSwitches"];
      if (v.HasMember("webglType") && v["webglType"].IsString())
        webglType = v["webglType"].GetString();
      if (v.HasMember("webglVendor") && v["webglVendor"].IsString())
        webglVendor = v["webglVendor"].GetString();
      if (v.HasMember("webglRenderer") && v["webglRenderer"].IsString())
        webglRenderer = v["webglRenderer"].GetString();
      if (v.HasMember("canvasPerturbX") && v["canvasPerturbX"].IsNumber())
        canvasPerturbX = v["canvasPerturbX"].GetDouble();
      if (v.HasMember("canvasPerturbY") && v["canvasPerturbY"].IsNumber())
        canvasPerturbY = v["canvasPerturbY"].GetDouble();
      if (v.HasMember("canvasFontY") && v["canvasFontY"].IsNumber())
        canvasFontY = v["canvasFontY"].GetDouble();
      if (v.HasMember("canvasFontX") && v["canvasFontX"].IsNumber())
        canvasFontX = v["canvasFontX"].GetDouble();
      if (v.HasMember("canvasPerturbEnabled") &&
          v["canvasPerturbEnabled"].IsInt())
        canvasPerturbEnabled = v["canvasPerturbEnabled"].GetInt();
      if (v.HasMember("canvasFontEnabled") && v["canvasFontEnabled"].IsInt())
        canvasFontEnabled = v["canvasFontEnabled"].GetInt();
      if (v.HasMember("webglEnabled") && v["webglEnabled"].IsInt())
        webglEnabled = v["webglEnabled"].GetInt();
      if (v.HasMember("webglPerturbX") && v["webglPerturbX"].IsNumber())
        webglPerturbX = v["webglPerturbX"].GetDouble();
      if (v.HasMember("audio") && v["audio"].IsNumber())
        audio = v["audio"].GetDouble();
      if (v.HasMember("bluetoothDisabled") && v["bluetoothDisabled"].IsInt())
        bluetoothDisabled = v["bluetoothDisabled"].GetInt();
      if (v.HasMember("mediaType") && v["mediaType"].IsString())
        mediaType = v["mediaType"].GetString();
      if (v.HasMember("webrtcMode") && v["webrtcMode"].IsString())
        webrtcMode = v["webrtcMode"].GetString();
      if (v.HasMember("webrtcPublicIp") && v["webrtcPublicIp"].IsString())
        webrtcPublicIp = v["webrtcPublicIp"].GetString();
      if (v.HasMember("webrtcInnerIp") && v["webrtcInnerIp"].IsString())
        webrtcInnerIp = v["webrtcInnerIp"].GetString();
      if (v.HasMember("blockPortScanning") && v["blockPortScanning"].IsBool())
        blockPortScanning = v["blockPortScanning"].GetBool();
      if (v.HasMember("portScanningWhitelist") &&
          v["portScanningWhitelist"].IsString())
        portScanningWhitelist = v["portScanningWhitelist"].GetString();
      if (v.HasMember("rectDX") && v["rectDX"].IsNumber())
        rectDX = v["rectDX"].GetDouble();
      if (v.HasMember("glyphsMeasureTextDX") &&
          v["glyphsMeasureTextDX"].IsNumber())
        glyphsMeasureTextDX = v["glyphsMeasureTextDX"].GetDouble();
      if (v.HasMember("textMetricsBoundingDX") &&
          v["textMetricsBoundingDX"].IsNumber())
        textMetricsBoundingDX = v["textMetricsBoundingDX"].GetDouble();
      if (v.HasMember("windowSize") && v["windowSize"].IsString())
        windowSize = v["windowSize"].GetString();
      if (v.HasMember("storage") && v["storage"].IsString())
        storage = v["storage"].GetString();
      if (v.HasMember("enableCookie") && v["enableCookie"].IsInt())
        enableCookie = v["enableCookie"].GetInt();
      if (v.HasMember("enableopen") && v["enableopen"].IsInt())
        enableopen = v["enableopen"].GetInt();
      if (v.HasMember("enablenotice") && v["enablenotice"].IsInt())
        enablenotice = v["enablenotice"].GetInt();
      if (v.HasMember("clientRects") && v["clientRects"].IsInt())
        clientRects = v["clientRects"].GetInt();
      if (v.HasMember("enablepic") && v["enablepic"].IsInt())
        enablepic = v["enablepic"].GetInt();
      if (v.HasMember("picsize") && v["picsize"].IsString())
        picsize = v["picsize"].GetString();
      if (v.HasMember("enablesound") && v["enablesound"].IsInt())
        enablesound = v["enablesound"].GetInt();
      if (v.HasMember("enablevideo") && v["enablevideo"].IsInt())
        enablevideo = v["enablevideo"].GetInt();
      if (v.HasMember("enableGPU") && v["enableGPU"].IsInt())
        enableGPU = v["enableGPU"].GetInt();
      if (v.HasMember("commonPerturb") && v["commonPerturb"].IsInt())
        commonPerturb = v["commonPerturb"].GetInt();
      if (v.HasMember("version") && v["version"].IsInt())
        version = v["version"].GetInt();
      if (v.HasMember("ClientHints") && v["ClientHints"].IsObject())
        clientHints << v["ClientHints"];
      if (v.HasMember("plugins") && v["plugins"].IsArray()) {
        plugins.clear();
        for (auto &item : v["plugins"].GetArray()) {
          Plugin p;
          p << item;
          plugins.push_back(p);
        }
      }
      if (v.HasMember("videoInputs") && v["videoInputs"].IsArray()) {
        videoInputs.clear();
        for (auto &item : v["videoInputs"].GetArray()) {
          DeviceInput d;
          d << item;
          videoInputs.push_back(d);
        }
      }
      if (v.HasMember("audioInputs") && v["audioInputs"].IsArray()) {
        audioInputs.clear();
        for (auto &item : v["audioInputs"].GetArray()) {
          DeviceInput d;
          d << item;
          audioInputs.push_back(d);
        }
      }
      if (v.HasMember("audioOutputs") && v["audioOutputs"].IsArray()) {
        audioOutputs.clear();
        for (auto &item : v["audioOutputs"].GetArray()) {
          DeviceInput d;
          d << item;
          audioOutputs.push_back(d);
        }
      }
      if (v.HasMember("speeches") && v["speeches"].IsArray()) {
        speeches.clear();
        for (auto &item : v["speeches"].GetArray()) {
          if (item.IsString())
            speeches.push_back(item.GetString());
        }
      }
      if (v.HasMember("speechVoices") && v["speechVoices"].IsArray()) {
        speechVoices.clear();
        for (auto &item : v["speechVoices"].GetArray()) {
          SpeechVoice s;
          s << item;
          speechVoices.push_back(s);
        }
      }
      if (v.HasMember("geographic") && v["geographic"].IsObject())
        geographic << v["geographic"];
      if (v.HasMember("mediaMimes") && v["mediaMimes"].IsArray()) {
        mediaMimes.clear();
        for (auto &item : v["mediaMimes"].GetArray()) {
          MediaMime m;
          m << item;
          mediaMimes.push_back(m);
        }
      }

    } /// function end
  };

public:
  inline IConfigure(const std::string &);
  inline ~IConfigure();
  inline void operator>>(std::string &) const;
  inline bool IsEnabledCookies() const {
    return !finger.enableCookie;
  }
  inline const std::string &GetTimeZoneID() const {
    std::lock_guard<std::mutex> lock(*mtx_);
    return finger.timezone;
  }
  inline const std::string &GetPublicIP() const {
    return finger.webrtcPublicIp;
  }
  inline const std::string &GetLocalIP() const {
    return finger.webrtcInnerIp;
  }
  inline void SetMainSwitchState(const bool &enable) {
    std::lock_guard<std::mutex> lock(*mtx_);
    xsiumio.enable = enable;
  }
  inline const bool &GetMainSwitchState() const {
    std::lock_guard<std::mutex> lock(*mtx_);
    return xsiumio.enable;
  }
  inline bool IsEnabledStorage() const {
    return !enable_storage;
  }
  inline bool Enabled() const {
    return xsiumio.enable;
  }
  inline void SetBrowserAndShopID(const std::string &brwid) {
    do {
      browser_id = brwid;
      shop_id.clear();
      if (browser_id.size() > 5) {
        if (std::equal(browser_id.begin(), browser_id.begin() + 5, "Shop-",
                       [](char a, char b) {
                         return std::tolower(a) == std::tolower(b);
                       })) {
          shop_id = browser_id.substr(5);
        }
      }
    } while (0);
  }
  inline void SetBaseData(const std::string &input) {
    baseData << input;
  }
  inline const std::string &GetProxyBypassList() const {
    return bypassList;
  }
  inline bool IsFingerEnv() const {
    bool result = false;
    do {
      if (browser_id.empty() || shop_id.empty())
        break;
      if (browser_id.find("Shop-") == std::string::npos)
        break;
      result = true;
    } while (0);
    return result;
  }
  inline const std::string &GetShopID() const {
    return shop_id;
  }
  inline const std::string &GetBrowserID() const {
    return browser_id;
  }
  inline const xsiumio::IXSiumio &GetXSiumio() const {
    return xsiumio;
  }
  inline void operator<<(const std::string &);

  inline void
  AutoSettingProxy(const std::function<unsigned int(void)> &get_free_port_cb) {
    do {
      std::string proxyString = GetProxyAuthUrl();
      if (proxyString.empty()) {
        xsiumio.bridge.enable = false;
        xsiumio.proxy.enable = false;
        xsiumio.proxy.credentials = false;
        xsiumio.proxy.url.clear();
        break;
      }
      unsigned int free_port = 0;
      if (get_free_port_cb)
        free_port = get_free_port_cb();
      xsiumio.bridge.enable = true;
      xsiumio.proxy.url = "http://127.0.0.1:" + std::to_string(free_port);
      xsiumio.proxy.credentials = false;
      xsiumio.bridge.proxy_pass = proxyString;
      xsiumio.bridge.server_listen = "127.0.0.1:" + std::to_string(free_port);
      xsiumio.bridge.ProxyPassFixed();
    } while (0);
  }
  inline std::string GetProxyAuthUrl() const {
    std::string result;
    if (proxyInfo.IsUseBridge()) {
      result.append(proxyInfo.bridge.protocol)
          .append("://")
          .append(proxyInfo.bridge.username)
          .append(":")
          .append(proxyInfo.bridge.password)
          .append("@")
          .append(proxyInfo.bridge.server)
          .append(":")
          .append(std::to_string(proxyInfo.bridge.port));
    } else if (proxyInfo.IsUseOutbound()) {
      result.append(proxyInfo.outbound.protocol)
          .append("://")
          .append(proxyInfo.outbound.username)
          .append(":")
          .append(proxyInfo.outbound.password)
          .append("@")
          .append(proxyInfo.outbound.server)
          .append(":")
          .append(std::to_string(proxyInfo.outbound.port));
    } else if (!device.protocol.empty() && !device.host.empty() &&
               !device.userName.empty() && !device.password.empty() &&
               device.port > 0) {
      result.append(device.protocol)
          .append("://")
          .append(device.userName)
          .append(":")
          .append(device.password)
          .append("@")
          .append(device.host)
          .append(":")
          .append(std::to_string(device.port));
    }
    return result;
  }
  bool IsAllowPort(const int &port) const {
    if (!finger.blockPortScanning || finger.portScanningWhitelist.empty())
      return true;
    const std::string filter = "," + finger.portScanningWhitelist + ",";
    const std::string target = "," + std::to_string(port) + ",";
    if (filter.find(target) != std::string::npos)
      return true;
    return false;
  }

private:
  std::string shop_id;
  std::string browser_id;

public:
  BaseData baseData;
  ProxyInfo proxyInfo;
  Device device;
  SearchEngine search_engine;
  DataSync data_sync;
  Finger finger;
  Browser browser;
  Shop shop;
  std::string security_strategy;
  std::set<std::string> blacklist;
  std::set<std::string> whitelist;
  std::string cdk;
  std::string bypassList;
  int enable_devtools_all = 0;
  int enable_storage = 0;
  std::string remote_debugging_protocol = "cdp";
  std::string authorization;
  //!@ patch by Martell 2025.7.18
  xsiumio::IXSiumio xsiumio;

private:
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};
inline IConfigure::IConfigure(const std::string &input) {
  *this << input;
}
inline IConfigure::~IConfigure() {
}
inline void IConfigure::operator>>(std::string &output) const {
  std::lock_guard<std::mutex> lock(*mtx_);
  rapidjson::Document doc;
  doc.SetObject();
  auto &allocator = doc.GetAllocator();
  baseData >> doc;
  if (doc.HasMember(kSwitchShopId))
    doc.RemoveMember(kSwitchShopId);
  RAPIDJSON_ADDMEMBER_STRING(doc, std::string(kSwitchShopId), shop_id,
                             allocator);
  if (doc.HasMember(kSwitchBrowserId))
    doc.RemoveMember(kSwitchBrowserId);
  RAPIDJSON_ADDMEMBER_STRING(doc, std::string(kSwitchBrowserId), browser_id,
                             allocator);

  device >> doc;
  proxyInfo >> doc;
  shop >> doc;
  browser >> doc;
  search_engine >> doc;
  data_sync >> doc;
  finger >> doc;

  if (doc.HasMember("security_strategy"))
    doc.RemoveMember("security_strategy");
  RAPIDJSON_ADDMEMBER_STRING(doc, std::string("security_strategy"),
                             security_strategy, allocator);

  if (doc.HasMember("cdk"))
    doc.RemoveMember("cdk");
  RAPIDJSON_ADDMEMBER_STRING(doc, std::string("cdk"), cdk, allocator);
  RAPIDJSON_ADDMEMBER_STRING(doc, std::string("bypassList"), bypassList,
                             allocator);

  if (doc.HasMember("remote_debugging_protocol"))
    doc.RemoveMember("remote_debugging_protocol");
  RAPIDJSON_ADDMEMBER_STRING(doc, std::string("remote_debugging_protocol"),
                             remote_debugging_protocol, allocator);

  if (doc.HasMember("authorization"))
    doc.RemoveMember("authorization");
  RAPIDJSON_ADDMEMBER_STRING(doc, std::string("authorization"), authorization,
                             allocator);

  if (doc.HasMember("enable_devtools_all"))
    doc.RemoveMember("enable_devtools_all");
  RAPIDJSON_ADDMEMBER_INT(doc, std::string("enable_devtools_all"),
                          enable_devtools_all, allocator);

  if (doc.HasMember("enable_storage"))
    doc.RemoveMember("enable_storage");
  RAPIDJSON_ADDMEMBER_INT(doc, std::string("enable_storage"), enable_storage,
                          allocator);

  rapidjson::Value blacklistArray(rapidjson::kArrayType);
  for (const auto &it : blacklist) {
    if (it.empty())
      continue;
    blacklistArray.PushBack(
        rapidjson::Value().SetString(it.c_str(), allocator).Move(), allocator);
  }
  if (doc.HasMember("blacklist"))
    doc.RemoveMember("blacklist");
  RAPIDJSON_ADDMEMBER_OBJECT(doc, std::string("blacklist"), blacklistArray,
                             allocator);

  rapidjson::Value whitelistArray(rapidjson::kArrayType);
  for (const auto &it : whitelist) {
    if (it.empty())
      continue;
    whitelistArray.PushBack(
        rapidjson::Value().SetString(it.c_str(), allocator).Move(), allocator);
  }
  if (doc.HasMember("whitelist"))
    doc.RemoveMember("whitelist");
  RAPIDJSON_ADDMEMBER_OBJECT(doc, std::string("whitelist"), whitelistArray,
                             allocator);

  //!@ Martell Patch on HangZhou 2025.7.19
  //!
  //!
  xsiumio >> doc;

  output = Json::toString(doc);
}
inline void IConfigure::operator<<(const std::string &input) {
  do {
    if (input.empty())
      break;
    rapidjson::Document doc;
    if (doc.Parse(input.data(), input.size()).HasParseError())
      break;
    if (!doc.IsObject())
      break;
    //!@ patch by Martell 2025.7.18
    if (doc.HasMember(xsiumio::kObjectKey) &&
        doc[xsiumio::kObjectKey].IsObject()) {
      xsiumio << doc[xsiumio::kObjectKey];
    }
    //-----------------------------------------------------------------------------------------
    if (doc.HasMember(kSwitchBaseData) && doc[kSwitchBaseData].IsString() &&
        doc[kSwitchBaseData].GetStringLength() > 0) {
      SetBaseData(doc[kSwitchBaseData].GetString());
    }
    if (doc.HasMember(kSwitchBrowserId) && doc[kSwitchBrowserId].IsString() &&
        doc[kSwitchBrowserId].GetStringLength() > 0) {
      SetBrowserAndShopID(doc[kSwitchBrowserId].GetString());
    }
    if (doc.HasMember("device") && doc["device"].IsObject())
      device << doc["device"];
    if (doc.HasMember("shop") && doc["shop"].IsObject())
      shop << doc["shop"];
    if (doc.HasMember("proxyInfo") && doc["proxyInfo"].IsObject())
      proxyInfo << doc["proxyInfo"];
    if (doc.HasMember("data_sync") && doc["data_sync"].IsObject())
      data_sync << doc["data_sync"];
    if (doc.HasMember("search_engine") && doc["search_engine"].IsObject())
      search_engine << doc["search_engine"];
    if (doc.HasMember("finger") && doc["finger"].IsObject())
      finger << doc["finger"];
    if (doc.HasMember("browser") && doc["browser"].IsObject())
      browser << doc["browser"];
    if (doc.HasMember("cdk") && doc["cdk"].IsString())
      cdk = doc["cdk"].GetString();
    if (doc.HasMember("security_strategy") &&
        doc["security_strategy"].IsString())
      security_strategy = doc["security_strategy"].GetString();
    if (doc.HasMember("authorization") && doc["authorization"].IsString())
      authorization = doc["authorization"].GetString();
    if (doc.HasMember("remote_debugging_protocol") &&
        doc["remote_debugging_protocol"].IsString())
      remote_debugging_protocol = doc["remote_debugging_protocol"].GetString();
    if (doc.HasMember("enable_devtools_all") &&
        doc["enable_devtools_all"].IsInt())
      enable_devtools_all = doc["enable_devtools_all"].GetInt();
    if (doc.HasMember("enable_storage") && doc["enable_storage"].IsInt())
      enable_storage = doc["enable_storage"].GetInt();
    if (doc.HasMember("bypassList") && doc["bypassList"].IsString())
      bypassList = doc["bypassList"].GetString();
    if (doc.HasMember("whitelist") && doc["whitelist"].IsArray()) {
      whitelist.clear();
      for (auto &w : doc["whitelist"].GetArray()) {
        if (w.IsString() && w.GetStringLength() > 0)
          whitelist.insert(w.GetString());
      }
    }

    if (doc.HasMember("blacklist") && doc["blacklist"].IsArray()) {
      blacklist.clear();
      for (auto &w : doc["blacklist"].GetArray()) {
        if (w.IsString() && w.GetStringLength() > 0)
          blacklist.insert(w.GetString());
      }
    }

  } while (0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline IConfigure::Device::Device() = default;
inline IConfigure::Device::~Device() = default;
inline IConfigure::ProxyInfo::ProxyInfo() = default;
inline IConfigure::ProxyInfo::~ProxyInfo() = default;
inline IConfigure::ProxyInfo::Bridge::Bridge() = default;
inline IConfigure::ProxyInfo::Bridge::~Bridge() = default;
inline IConfigure::ProxyInfo::Dns::Dns() = default;
inline IConfigure::ProxyInfo::Dns::~Dns() = default;
inline IConfigure::ProxyInfo::Outbound::Outbound() = default;
inline IConfigure::ProxyInfo::Outbound::~Outbound() = default;
inline IConfigure::Browser::Browser() = default;
inline IConfigure::Browser::~Browser() = default;
inline IConfigure::DataSync::DataSync() = default;
inline IConfigure::DataSync::~DataSync() = default;
inline IConfigure::Finger::Finger() = default;
inline IConfigure::Finger::~Finger() = default;
inline IConfigure::Shop::Shop() = default;
inline IConfigure::Shop::~Shop() = default;
inline IConfigure::SearchEngine::SearchEngine() = default;
inline IConfigure::SearchEngine::~SearchEngine() = default;
inline IConfigure::Finger::FpSwitches::FpSwitches() = default;
inline IConfigure::Finger::FpSwitches::~FpSwitches() = default;
inline IConfigure::Finger::ClientHints::ClientHints() = default;
inline IConfigure::Finger::ClientHints::~ClientHints() = default;
inline IConfigure::Finger::Plugin::Plugin() = default;
inline IConfigure::Finger::Plugin::~Plugin() = default;
inline IConfigure::Finger::Plugin::Plugin(const Plugin &) = default;
inline IConfigure::Finger::Plugin &
IConfigure::Finger::Plugin::operator=(const Plugin &) = default;
inline IConfigure::Finger::Plugin::Plugin(Plugin &&) = default;
inline IConfigure::Finger::Plugin &
IConfigure::Finger::Plugin::operator=(Plugin &&) = default;
inline IConfigure::Finger::DeviceInput::DeviceInput() = default;
inline IConfigure::Finger::DeviceInput::~DeviceInput() = default;
inline IConfigure::Finger::SpeechVoice::SpeechVoice() = default;
inline IConfigure::Finger::SpeechVoice::~SpeechVoice() = default;
inline IConfigure::Finger::SpeechVoice::SpeechVoice(const SpeechVoice &) =
    default;
inline IConfigure::Finger::SpeechVoice &
IConfigure::Finger::SpeechVoice::operator=(const SpeechVoice &) = default;
inline IConfigure::Finger::SpeechVoice::SpeechVoice(SpeechVoice &&) = default;
inline IConfigure::Finger::SpeechVoice &
IConfigure::Finger::SpeechVoice::operator=(SpeechVoice &&) = default;
inline IConfigure::Finger::Geographic::Geographic() = default;
inline IConfigure::Finger::Geographic::~Geographic() = default;
inline IConfigure::Finger::MediaMime::MediaMime() = default;
inline IConfigure::Finger::MediaMime::~MediaMime() = default;
inline IConfigure::BaseData::BaseData() = default;
inline IConfigure::BaseData::~BaseData() = default;
} // namespace yunlogin
} // namespace chromium
/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 09 Jul 2025 01:28:50 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__C8214189_EE1B_4726_BECE_3CBE103F523F__