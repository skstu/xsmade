#if !defined(__8B6326C0_93E4_49D8_BFC7_EB6C3BA59694__)
#define __8B6326C0_93E4_49D8_BFC7_EB6C3BA59694__

namespace brw {
class IConfigure final {
public:
  class Policy final {
  public:
    inline Policy();
    inline ~Policy();

  public:
    unsigned long long id = 0;
  };
  class Proxy final {
  public:
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

  public:
    bool enable = false;
    Type type = Type::HTTP;
    SocksType socks_type = SocksType::Default;
    std::string host;
    unsigned short port = 80;
    std::string username;
    std::string password;
    std::string address;
    std::string credentials_url;
  };
  class Fps final {
  public:
    class Hash final {
    public:
      inline Hash();
      inline ~Hash();

    public:
      bool enable = false;
      bool random = false;
      double base = 0.0;
      double from = 0.0;
      double to = 0.0;

    public:
      inline void operator<<(const std::string &);
    };

    class Canvas final {
    public:
      inline Canvas();
      inline ~Canvas();

    public:
      bool enable = false;
      Hash hash;
    };
    class Webgl final {
    public:
      inline Webgl();
      inline ~Webgl();

    public:
      bool enable = false;
      Hash hash;
      std::string vendor;
      std::string renderer;
      std::string driver_version;
      std::string version;
      std::map<unsigned int, std::string> parameters;
    };
    class Audio final {
    public:
      inline Audio();
      inline ~Audio();

    public:
      bool enable = false;
      Hash hash;
    };
    class Font final {
    public:
      inline Font();
      inline ~Font();

    public:
      bool enable = false;
      Hash hash;
      std::vector<std::string> keywords;
    };
    class Screen final {
    public:
      inline Screen();
      inline ~Screen();

    public:
      int height = 0;
      int width = 0;
      int colorDepth = 0;
      int pixelDepth = 0;
      int availLeft = 0;
      int availTop = 0;
      int availHeight = 0;
      int availWidth = 0;
      bool enable = false;
    };

  public:
    inline Fps();
    inline ~Fps();

  public:
    bool enable = false;
    std::string enable_do_not_track = "null";
    std::string platform = "Win32";
    std::string userAgent =
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, "
        "like Gecko) Chrome/130.0.0.0 Safari/537.36";
    unsigned short hardwareConcurrency = 2;
    unsigned long long deviceMemory = 2147483648;
    Font font;
    Canvas canvas;
    Webgl webgl;
    Audio audio;
    Screen screen;
  };

  class Jss final {
  public:
    inline Jss();
    inline ~Jss();

  public:
    bool enable = false;
    std::map<std::string, std::string> source;
  };

public:
  inline IConfigure(const std::string &input);
  inline ~IConfigure();
  inline std::string Serialization() const;

public:
  bool enable = false;
  Fps fps;
  Jss jss;
  std::map<std::string, std::string> startup_args;
  rapidjson::Document doc;
  Policy policy;
  Proxy proxy;
};

inline IConfigure::~IConfigure() {
}
inline IConfigure::Policy::Policy() {
}
inline IConfigure::Policy::~Policy() {
}
inline IConfigure::Proxy::Proxy() {
}
inline IConfigure::Proxy::~Proxy() {
}
inline IConfigure::Fps::Fps() {
}
inline IConfigure::Fps::~Fps() {
}
inline IConfigure::Fps::Screen::Screen() {
}
inline IConfigure::Fps::Screen::~Screen() {
}
inline IConfigure::Fps::Audio::Audio() {
}
inline IConfigure::Fps::Audio::~Audio() {
}
inline IConfigure::Fps::Canvas::Canvas() {
}
inline IConfigure::Fps::Canvas::~Canvas() {
}
inline IConfigure::Fps::Webgl::Webgl() {
}
inline IConfigure::Fps::Webgl::~Webgl() {
}
inline IConfigure::Fps::Font::Font() {
}
inline IConfigure::Fps::Font::~Font() {
}
inline IConfigure::Fps::Hash::Hash() {
}
inline IConfigure::Fps::Hash::~Hash() {
}
inline IConfigure::Jss::Jss() {
}
inline IConfigure::Jss::~Jss() {
}
inline void IConfigure::Fps::Hash::operator<<(const std::string &input) {
  do {
    if (input.empty())
      break;
    rapidjson::Document docHash;
    if (docHash.Parse(input.data(), input.size()).HasParseError())
      break;
    if (!docHash.IsObject())
      break;
    if (docHash.HasMember("random") && docHash["random"].IsBool())
      random = docHash["random"].GetBool();
    if (docHash.HasMember("base") && docHash["base"].IsDouble())
      base = docHash["base"].GetDouble();
    if (docHash.HasMember("from") && docHash["from"].IsDouble())
      from = docHash["from"].GetDouble();
    if (docHash.HasMember("to") && docHash["to"].IsDouble())
      to = docHash["to"].GetDouble();
  } while (0);
}
inline IConfigure::IConfigure(const std::string &input) {
  bool success = false;
  do {
    if (input.empty())
      break;
    if (doc.Parse(input.data(), input.size()).HasParseError())
      break;
    if (!doc.IsObject())
      break;
    if (doc.ObjectEmpty())
      break;
    do { //!@ .enable
      if (!doc.HasMember("enable"))
        break;
      if (!doc["enable"].IsBool())
        break;
      enable = doc["enable"].GetBool();
    } while (0);
    do { //!@ .policy
      if (!doc.HasMember("policy"))
        break;
      if (!doc["policy"].IsObject())
        break;
      auto &policyObj = doc["policy"];
      if (!policyObj.HasMember("id"))
        break;
      if (!policyObj["id"].IsUint64())
        break;
      policy.id = policyObj["id"].GetUint64();
    } while (0);
    do { //!@ .proxy
      if (!doc.HasMember("proxy"))
        break;
      if (!doc["proxy"].IsObject())
        break;
      auto &proxyObj = doc["proxy"];
      if (proxyObj.HasMember("enable") && proxyObj["enable"].IsBool()) {
        proxy.enable = proxyObj["enable"].GetBool();
      }
      if (!proxyObj.HasMember("credentials_url"))
        break;
      if (!proxyObj["credentials_url"].IsString())
        break;
      proxy.credentials_url = proxyObj["credentials_url"].GetString();
      std::regex url_regex(
          R"(^(http[s]?|socks[4-5](h|a)?):\/\/([^:]+):([^@]+)@([^:]+):(\d+)$)");
      std::smatch url_match;
      if (!std::regex_match(proxy.credentials_url, url_match, url_regex)) {
        proxy.address = proxy.credentials_url;
        break;
      }
      do {
        if (url_match.size() != 7)
          break;
        std::string protocol;
        if (std::string(url_match[1]).find("https") != std::string::npos) {
          protocol = "https";
          proxy.type = Proxy::Type::HTTPS;
        } else if (std::string(url_match[1]).find("http") !=
                   std::string::npos) {
          protocol = "http";
          proxy.type = Proxy::Type::HTTP;
        } else if (std::string(url_match[1]).find("socks4") !=
                   std::string::npos) {
          protocol = "socks4";
          proxy.type = Proxy::Type::SOCKS4;
        } else if (std::string(url_match[1]).find("socks5") !=
                   std::string::npos) {
          protocol = "socks5";
          proxy.type = Proxy::Type::SOCKS5;
        }
        if (protocol.empty())
          break;
        if (url_match[2].matched) {
          const std::string tmp(url_match[2]);
          if (tmp.find("h") != std::string::npos) {
            proxy.socks_type = Proxy::SocksType::SocksH;
          } else if (tmp.find("a") != std::string::npos) {
            proxy.socks_type = Proxy::SocksType::SocksA;
          }
        }
        if (url_match[3].matched)
          proxy.username = url_match[3];
        if (url_match[4].matched)
          proxy.password = url_match[4];
        if (url_match[5].matched)
          proxy.host = url_match[5];
        if (url_match[6].matched)
          proxy.port = static_cast<decltype(proxy.port)>(
              atoi(std::string(url_match[6]).c_str()));
        if (!protocol.empty() && !proxy.host.empty()) {
          proxy.address.clear();
          proxy.address.append(protocol)
              .append("://")
              .append(proxy.host)
              .append(":")
              .append(std::to_string(proxy.port));
        }
      } while (0);

    } while (0);
    do { //!@ .startup_args
      if (!doc.HasMember("startup_args"))
        break;
      if (!doc["startup_args"].IsArray())
        break;

      for (auto it = doc["startup_args"].Begin();
           it != doc["startup_args"].End(); ++it) {
        if (!it->IsObject())
          break;
        auto &obj = *it;
        std::string key, value;
        if (obj.HasMember("key") && obj["key"].IsString() &&
            obj["key"].GetStringLength() > 0) {
          key = obj["key"].GetString();
          do {
            if (key.empty())
              break;
            if (*key.begin() == '-')
              key.erase(key.begin());
            else
              break;
          } while (1);
          std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        }
        if (obj.HasMember("value") && obj["value"].IsString() &&
            obj["value"].GetStringLength() > 0) {
          value = obj["value"].GetString();
        }
        if (!key.empty()) {
          startup_args.emplace(key, value);
        }
      }
    } while (0);
    do { //!@ .jss
      if (!doc.HasMember("jss"))
        break;
      if (!doc["jss"].IsObject())
        break;
      auto &jssObj = doc["jss"];
      if (jssObj.HasMember("enable") && jssObj["enable"].IsBool()) {
        jss.enable = jssObj["enable"].GetBool();
      }
      if (jssObj.HasMember("source") && jssObj["source"].IsObject()) {
        for (auto it = jssObj["source"].MemberBegin();
             it != jssObj["source"].MemberEnd(); ++it) {
          if (!it->name.IsString())
            break;
          if (!it->value.IsString())
            break;
          if (it->value.GetStringLength() <= 0)
            continue;
          std::string name = it->name.GetString();
          std::transform(name.begin(), name.end(), name.begin(), ::tolower);
          jss.source.emplace(name, it->value.GetString());
        }
      }

    } while (0);
    do { //!@ .fps
      if (!doc.HasMember("fps"))
        break;
      if (!doc["fps"].IsObject())
        break;
      auto &fpsObj = doc["fps"];
      do { //!@ .fps.enable
        if (!fpsObj.HasMember("enable"))
          break;
        if (!fpsObj["enable"].IsBool())
          break;
        fps.enable = fpsObj["enable"].GetBool();
      } while (0);
      do { //!@ .fps.enable_do_not_track
        if (!fpsObj.HasMember("enable_do_not_track"))
          break;
        if (!fpsObj["enable_do_not_track"].IsString())
          break;
        fps.enable_do_not_track = fpsObj["enable_do_not_track"].GetString();
      } while (0);
      do { //!@ .fps.platform
        if (!fpsObj.HasMember("platform"))
          break;
        if (!fpsObj["platform"].IsString())
          break;
        fps.platform = fpsObj["platform"].GetString();
      } while (0);
      do { //!@ .fps.userAgent
        if (!fpsObj.HasMember("userAgent"))
          break;
        if (!fpsObj["userAgent"].IsString())
          break;
        if (fpsObj["userAgent"].GetStringLength() <= 0)
          break;
        fps.userAgent = fpsObj["userAgent"].GetString();
      } while (0);
      do { //!@ .fps.hardwareConcurrency
        if (!fpsObj.HasMember("hardwareConcurrency"))
          break;
        if (!fpsObj["hardwareConcurrency"].IsUint())
          break;
        fps.hardwareConcurrency =
            static_cast<decltype(fps.hardwareConcurrency)>(
                fpsObj["hardwareConcurrency"].GetUint());
      } while (0);
      do { //!@ .fps.deviceMemory
        if (!fpsObj.HasMember("deviceMemory"))
          break;
        if (!fpsObj["deviceMemory"].IsUint64())
          break;
        fps.deviceMemory = fpsObj["deviceMemory"].GetUint64();
      } while (0);
      do { //!@ .fps.font
        if (!fpsObj.HasMember("font"))
          break;
        if (!fpsObj["font"].IsObject())
          break;
        if (fpsObj["font"].HasMember("enable") &&
            fpsObj["font"]["enable"].IsBool())
          fps.font.enable = fpsObj["font"]["enable"].GetBool();
        if (fpsObj["font"].HasMember("keywords") &&
            fpsObj["font"]["keywords"].IsArray()) {
          for (auto it = fpsObj["font"]["keywords"].Begin();
               it != fpsObj["font"]["keywords"].End(); ++it) {
            if (!it->IsString())
              break;
            if (it->GetStringLength() <= 0)
              continue;
            fps.font.keywords.emplace_back(it->GetString());
          }
        }
        if (fpsObj["font"].HasMember("hash") &&
            fpsObj["font"]["hash"].IsObject()) {
          fps.font.hash << Json::toString(fpsObj["font"]["hash"]);
        }
      } while (0);
      do { //!@ .fps.canvas
        if (!fpsObj.HasMember("canvas"))
          break;
        if (!fpsObj["canvas"].IsObject())
          break;
        if (fpsObj["canvas"].HasMember("enable") &&
            fpsObj["canvas"]["enable"].IsBool())
          fps.canvas.enable = fpsObj["canvas"]["enable"].GetBool();
        if (fpsObj["canvas"].HasMember("hash") &&
            fpsObj["canvas"]["hash"].IsObject()) {
          fps.canvas.hash << Json::toString(fpsObj["canvas"]["hash"]);
        }
      } while (0);
      do { //!@ .fps.audio
        if (!fpsObj.HasMember("audio"))
          break;
        if (!fpsObj["audio"].IsObject())
          break;
        if (fpsObj["audio"].HasMember("enable") &&
            fpsObj["audio"]["enable"].IsBool())
          fps.audio.enable = fpsObj["audio"]["enable"].GetBool();
        if (fpsObj["audio"].HasMember("hash") &&
            fpsObj["audio"]["hash"].IsObject()) {
          fps.audio.hash << Json::toString(fpsObj["audio"]["hash"]);
        }
      } while (0);
      do { //!@ .fps.webgl
        if (!fpsObj.HasMember("webgl"))
          break;
        if (!fpsObj["webgl"].IsObject())
          break;
        if (fpsObj["webgl"].HasMember("enable") &&
            fpsObj["webgl"]["enable"].IsBool())
          fps.webgl.enable = fpsObj["webgl"]["enable"].GetBool();
        if (fpsObj["webgl"].HasMember("hash") &&
            fpsObj["webgl"]["hash"].IsObject()) {
          fps.webgl.hash << Json::toString(fpsObj["webgl"]["hash"]);
        }
        if (fpsObj["webgl"].HasMember("vendor") &&
            fpsObj["webgl"]["vendor"].IsString()) {
          fps.webgl.vendor = fpsObj["webgl"]["vendor"].GetString();
        }
        if (fpsObj["webgl"].HasMember("renderer") &&
            fpsObj["webgl"]["renderer"].IsString()) {
          fps.webgl.renderer = fpsObj["webgl"]["renderer"].GetString();
        }
        if (fpsObj["webgl"].HasMember("driver_version") &&
            fpsObj["webgl"]["driver_version"].IsString()) {
          fps.webgl.driver_version =
              fpsObj["webgl"]["driver_version"].GetString();
        }
        if (fpsObj["webgl"].HasMember("version") &&
            fpsObj["webgl"]["version"].IsString()) {
          fps.webgl.version = fpsObj["webgl"]["version"].GetString();
        }
        if (fpsObj["webgl"].HasMember("parameters") &&
            fpsObj["webgl"]["parameters"].IsObject()) {
          for (auto it = fpsObj["webgl"]["parameters"].MemberBegin();
               it != fpsObj["webgl"]["parameters"].MemberEnd(); ++it) {
            do {
              if (!it->name.IsString())
                break;
              if (!it->value.IsString())
                break;
              unsigned int key = strtoul(it->name.GetString(), nullptr, 10);
              std::string value;
              if (it->value.GetStringLength() > 0)
                value = it->value.GetString();
              auto f = fps.webgl.parameters.find(key);
              if (f != fps.webgl.parameters.end())
                fps.webgl.parameters.erase(f);
              fps.webgl.parameters.emplace(key, value);
            } while (0);
          }
        }
      } while (0);
      do { //!@ .fps.screen
        if (!fpsObj.HasMember("screen"))
          break;
        if (!fpsObj["screen"].IsObject())
          break;
        if (fpsObj["screen"].HasMember("enable") &&
            fpsObj["screen"]["enable"].IsBool())
          fps.screen.enable = fpsObj["screen"]["enable"].GetBool();
        if (fpsObj["screen"].HasMember("height") &&
            fpsObj["screen"]["height"].IsInt()) {
          fps.screen.height = fpsObj["screen"]["height"].GetInt();
        }
        if (fpsObj["screen"].HasMember("width") &&
            fpsObj["screen"]["width"].IsInt()) {
          fps.screen.width = fpsObj["screen"]["width"].GetInt();
        }
        if (fpsObj["screen"].HasMember("colorDepth") &&
            fpsObj["screen"]["colorDepth"].IsInt()) {
          fps.screen.colorDepth = fpsObj["screen"]["colorDepth"].GetInt();
        }
        if (fpsObj["screen"].HasMember("pixelDepth") &&
            fpsObj["screen"]["pixelDepth"].IsInt()) {
          fps.screen.pixelDepth = fpsObj["screen"]["pixelDepth"].GetInt();
        }
        if (fpsObj["screen"].HasMember("availLeft") &&
            fpsObj["screen"]["availLeft"].IsInt()) {
          fps.screen.availLeft = fpsObj["screen"]["availLeft"].GetInt();
        }
        if (fpsObj["screen"].HasMember("availTop") &&
            fpsObj["screen"]["availTop"].IsInt()) {
          fps.screen.availTop = fpsObj["screen"]["availTop"].GetInt();
        }
        if (fpsObj["screen"].HasMember("availHeight") &&
            fpsObj["screen"]["availHeight"].IsInt()) {
          fps.screen.availHeight = fpsObj["screen"]["availHeight"].GetInt();
        }
        if (fpsObj["screen"].HasMember("availWidth") &&
            fpsObj["screen"]["availWidth"].IsInt()) {
          fps.screen.availWidth = fpsObj["screen"]["availWidth"].GetInt();
        }
      } while (0);
    } while (0);
    success = true;
  } while (0);
  if (!success)
    doc.SetObject();
}
inline std::string IConfigure::Serialization() const {
  return Json::toString(doc);
}
} // namespace brw
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 22 Feb 2025 13:22:06 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__8B6326C0_93E4_49D8_BFC7_EB6C3BA59694__