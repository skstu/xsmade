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
  class HomePage final {
  public:
    inline HomePage();
    inline ~HomePage();

  public:
    bool enable = false;
    std::string url;
    bool open_new_tab = false;
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
    class Navigator final {
    public:
      class Plugins final {
      public:
        class Plugin final {
        public:
          class MimeType final {
          public:
            inline MimeType();
            inline ~MimeType();
            inline bool operator<(const MimeType &) const;
            inline bool operator==(const MimeType &) const;
            inline void operator=(const MimeType &);

          public:
            std::string key; //!@ type
            std::string type;
            std::string suffixes;
          };

        public:
          inline Plugin();
          inline ~Plugin();
          inline bool operator<(const Plugin &) const;
          inline bool operator==(const Plugin &) const;
          inline void operator=(const Plugin &);
          inline Plugin(const Plugin &);

        public:
          bool enable = false;
          std::string key; //!@ name
          std::string name;
          std::string description;
          std::set<MimeType> mimeTypes;
        };

      public:
        inline Plugins();
        inline ~Plugins();
        std::set<Plugin> plugins;
        bool enable = false;
        bool pdfViewerEnabled = true;
        bool javaEnabled = false;
      };

    public:
      inline Navigator();
      inline ~Navigator();
      inline void operator<<(const rapidjson::Value &);

    public:
      Plugins plugins;
    };
    class Timezone final {
    public:
      class Source final {
      public:
        inline Source(const unsigned int &, const std::string &);
        inline ~Source();

      public:
        const unsigned int id;
        const std::string name;
        short offset = 0;
        std::string description;
      };

    public:
      inline Timezone();
      inline ~Timezone();

    public:
      bool enable = false;
      Hash hash;
      std::map<unsigned int, Source> sources;
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
      class ContextAttributes final {
      public:
        inline ContextAttributes();
        inline ~ContextAttributes();
        inline void operator=(const ContextAttributes &);

      public:
        bool alpha = true;
        bool antialias = true;
        bool depth = true;
        bool desynchronized = false;
        bool failIfMajorPerformanceCaveat = false;
        bool powerPreference = false;
        bool premultipliedAlpha = true;
        bool preserveDrawingBuffer = false;
        bool stencil = false;
        bool xrCompatible = false;
      };
      class ShaderPrecisionFormat final {
      public:
        enum class SharedType : unsigned int {
          Unknown = 0,
          FRAGMENT_SHADER = 0x8B30,
          VERTEX_SHADER = 0x8B31,
        };
        enum class FormatType : unsigned int {
          Unknown = 0,
          LOW_FLOAT = 0x8DF0,
          MEDIUM_FLOAT = 0x8DF1,
          HIGH_FLOAT = 0x8DF2,
          LOW_INT = 0x8DF3,
          MEDIUM_INT = 0x8DF4,
          HIGH_INT = 0x8DF5,
        };

        class Format final {
        public:
          inline Format();
          inline ~Format();
          inline void operator=(const Format &);

        public:
          int rangeMin = 0;
          int rangeMax = 0;
          int precision = 0;
        };
        class FRAGMENT_SHADER final {
        public:
          inline FRAGMENT_SHADER();
          inline ~FRAGMENT_SHADER();
          void operator=(const FRAGMENT_SHADER &);

        public:
          Format LOW_FLOAT;
          Format MEDIUM_FLOAT;
          Format HIGH_FLOAT;
          Format LOW_INT;
          Format MEDIUM_INT;
          Format HIGH_INT;
        };

        class VERTEX_SHADER final {
        public:
          inline VERTEX_SHADER();
          inline ~VERTEX_SHADER();
          void operator=(const VERTEX_SHADER &);

        public:
          Format LOW_FLOAT;
          Format MEDIUM_FLOAT;
          Format HIGH_FLOAT;
          Format LOW_INT;
          Format MEDIUM_INT;
          Format HIGH_INT;
        };

      public:
        inline ShaderPrecisionFormat();
        inline ~ShaderPrecisionFormat();
        void operator=(const ShaderPrecisionFormat &);

      public:
        FRAGMENT_SHADER gl_fragment_shader;
        VERTEX_SHADER gl_vertex_shader;
      };

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
      std::set<std::string> enabledExtensions;
      ContextAttributes contextAttributes;
      ShaderPrecisionFormat shaderPrecisionFormat;
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
      class Keyword final {
      public:
        inline Keyword();
        inline ~Keyword();
        inline Keyword(const std::string &kv);
        inline Keyword(const std::string &k, const std::string &v);
        inline bool operator<(const Keyword &) const;
        inline bool operator==(const Keyword &) const;

      public:
        std::string key;
        std::string value;
      };

    public:
      inline Font();
      inline ~Font();

    public:
      bool enable = false;
      Hash hash;
      std::set<Keyword> keywords;
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
      double devicePixelRatio = 1.0;
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
    Timezone timezone;
    Navigator navigator;
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
  std::set<std::string> startup_urls;
  HomePage homepage;
  std::string search_engine;
};

inline IConfigure::~IConfigure() {
}
inline IConfigure::Policy::Policy() {
}
inline IConfigure::Policy::~Policy() {
}
inline IConfigure::HomePage::HomePage() {
}
inline IConfigure::HomePage::~HomePage() {
}
inline IConfigure::Proxy::Proxy() {
}
inline IConfigure::Proxy::~Proxy() {
}
inline IConfigure::Fps::Fps() {
}
inline IConfigure::Fps::~Fps() {
}
inline IConfigure::Fps::Navigator::Navigator() {
}
inline IConfigure::Fps::Navigator::~Navigator() {
}
inline IConfigure::Fps::Navigator::Plugins::Plugins() {
}
inline IConfigure::Fps::Navigator::Plugins::~Plugins() {
}
inline IConfigure::Fps::Navigator::Plugins::Plugin::Plugin() {
}
inline IConfigure::Fps::Navigator::Plugins::Plugin::~Plugin() {
}
inline IConfigure::Fps::Navigator::Plugins::Plugin::Plugin(
    const Plugin &other) {
  key = other.key;
  name = other.name;
  description = other.description;
  mimeTypes = other.mimeTypes;
}
inline bool IConfigure::Fps::Navigator::Plugins::Plugin::operator<(
    const Plugin &rhs) const {
  return key.compare(rhs.key) < 0;
}
inline bool IConfigure::Fps::Navigator::Plugins::Plugin::operator==(
    const Plugin &rhs) const {
  return key.compare(rhs.key) == 0;
}
inline void
IConfigure::Fps::Navigator::Plugins::Plugin::operator=(const Plugin &rhs) {
  key = rhs.key;
  name = rhs.name;
  description = rhs.description;
  mimeTypes = rhs.mimeTypes;
}
inline IConfigure::Fps::Navigator::Plugins::Plugin::MimeType::MimeType() {
}
inline IConfigure::Fps::Navigator::Plugins::Plugin::MimeType::~MimeType() {
}
inline bool IConfigure::Fps::Navigator::Plugins::Plugin::MimeType::operator<(
    const MimeType &rhs) const {
  return key.compare(rhs.key) < 0;
}
inline bool IConfigure::Fps::Navigator::Plugins::Plugin::MimeType::operator==(
    const MimeType &rhs) const {
  return key.compare(rhs.key) == 0;
}

inline void IConfigure::Fps::Navigator::Plugins::Plugin::MimeType::operator=(
    const MimeType &rhs) {
  key = rhs.key;
  type = rhs.type;
  suffixes = rhs.suffixes;
}
inline IConfigure::Fps::Screen::Screen() {
}
inline IConfigure::Fps::Screen::~Screen() {
}
inline IConfigure::Fps::Timezone::Timezone() {
}
inline IConfigure::Fps::Timezone::~Timezone() {
}
inline IConfigure::Fps::Timezone::Source::Source(const unsigned int &id_,
                                                 const std::string &name_)
    : id(id_), name(name_) {
}
inline IConfigure::Fps::Timezone::Source::~Source() {
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
inline IConfigure::Fps::Webgl::ContextAttributes::ContextAttributes() {
}
inline IConfigure::Fps::Webgl::ContextAttributes::~ContextAttributes() {
}
inline void IConfigure::Fps::Webgl::ContextAttributes::operator=(
    const ContextAttributes &rhs) {
  alpha = rhs.alpha;
  antialias = rhs.antialias;
  depth = rhs.depth;
  desynchronized = rhs.desynchronized;
  failIfMajorPerformanceCaveat = rhs.failIfMajorPerformanceCaveat;
  powerPreference = rhs.powerPreference;
  premultipliedAlpha = rhs.premultipliedAlpha;
  preserveDrawingBuffer = rhs.preserveDrawingBuffer;
  stencil = rhs.stencil;
  xrCompatible = rhs.xrCompatible;
}
inline IConfigure::Fps::Webgl::ShaderPrecisionFormat::ShaderPrecisionFormat() {
}
inline IConfigure::Fps::Webgl::ShaderPrecisionFormat::~ShaderPrecisionFormat() {
}
inline void IConfigure::Fps::Webgl::ShaderPrecisionFormat::operator=(
    const ShaderPrecisionFormat &rhs) {
  gl_fragment_shader = rhs.gl_fragment_shader;
  gl_vertex_shader = rhs.gl_vertex_shader;
}
inline IConfigure::Fps::Webgl::ShaderPrecisionFormat::FRAGMENT_SHADER::
    FRAGMENT_SHADER() {
}
inline IConfigure::Fps::Webgl::ShaderPrecisionFormat::FRAGMENT_SHADER::
    ~FRAGMENT_SHADER() {
}
inline void
IConfigure::Fps::Webgl::ShaderPrecisionFormat::FRAGMENT_SHADER::operator=(
    const FRAGMENT_SHADER &rhs) {
  LOW_FLOAT = rhs.LOW_FLOAT;
  MEDIUM_FLOAT = rhs.MEDIUM_FLOAT;
  HIGH_FLOAT = rhs.HIGH_FLOAT;
  LOW_INT = rhs.LOW_INT;
  MEDIUM_INT = rhs.MEDIUM_INT;
  HIGH_INT = rhs.HIGH_INT;
}

inline IConfigure::Fps::Webgl::ShaderPrecisionFormat::VERTEX_SHADER::
    VERTEX_SHADER() {
}
inline IConfigure::Fps::Webgl::ShaderPrecisionFormat::VERTEX_SHADER::
    ~VERTEX_SHADER() {
}
inline void
IConfigure::Fps::Webgl::ShaderPrecisionFormat::VERTEX_SHADER::operator=(
    const VERTEX_SHADER &rhs) {
  LOW_FLOAT = rhs.LOW_FLOAT;
  MEDIUM_FLOAT = rhs.MEDIUM_FLOAT;
  HIGH_FLOAT = rhs.HIGH_FLOAT;
  LOW_INT = rhs.LOW_INT;
  MEDIUM_INT = rhs.MEDIUM_INT;
  HIGH_INT = rhs.HIGH_INT;
}
inline IConfigure::Fps::Webgl::ShaderPrecisionFormat::Format::Format() {
}
inline IConfigure::Fps::Webgl::ShaderPrecisionFormat::Format::~Format() {
}
inline void IConfigure::Fps::Webgl::ShaderPrecisionFormat::Format::operator=(
    const Format &rhs) {
  rangeMin = rhs.rangeMin;
  rangeMax = rhs.rangeMax;
  precision = rhs.precision;
}
inline IConfigure::Fps::Font::Font() {
}
inline IConfigure::Fps::Font::~Font() {
}
inline IConfigure::Fps::Font::Keyword::Keyword() {
}
inline IConfigure::Fps::Font::Keyword::~Keyword() {
}
inline IConfigure::Fps::Font::Keyword::Keyword(const std::string &k,
                                               const std::string &v) {
  key = k;
  value = v;
}
inline IConfigure::Fps::Font::Keyword::Keyword(const std::string &kv) {
  key = kv;
  value = kv;
  std::transform(key.begin(), key.end(), key.begin(), ::tolower);
}
inline bool
IConfigure::Fps::Font::Keyword::operator<(const Keyword &rhs) const {
  return key.compare(rhs.key) < 0;
}
inline bool
IConfigure::Fps::Font::Keyword::operator==(const Keyword &rhs) const {
  return key.compare(rhs.key) == 0;
}
inline IConfigure::Fps::Hash::Hash() {
}
inline IConfigure::Fps::Hash::~Hash() {
}
inline IConfigure::Jss::Jss() {
}
inline IConfigure::Jss::~Jss() {
}
inline void
IConfigure::Fps::Navigator::operator<<(const rapidjson::Value &navigatorObj) {
  do {
    if (!navigatorObj.IsObject())
      break;
    if (navigatorObj.ObjectEmpty())
      break;
    if (!navigatorObj.HasMember("plugins"))
      break;
    if (!navigatorObj["plugins"].IsObject())
      break;
    auto &pluginsObj = navigatorObj["plugins"];
    if (pluginsObj.HasMember("enable") && pluginsObj["enable"].IsBool()) {
      plugins.enable = pluginsObj["enable"].GetBool();
    }
    if (pluginsObj.HasMember("pdfViewerEnabled") &&
        pluginsObj["pdfViewerEnabled"].IsBool()) {
      plugins.pdfViewerEnabled = pluginsObj["pdfViewerEnabled"].GetBool();
    }
    if (pluginsObj.HasMember("javaEnabled") &&
        pluginsObj["javaEnabled"].IsBool()) {
      plugins.javaEnabled = pluginsObj["javaEnabled"].GetBool();
    }
    if (pluginsObj.HasMember("pluginArray") &&
        pluginsObj["pluginArray"].IsArray()) {
      for (auto itPluginArray = pluginsObj["pluginArray"].Begin();
           itPluginArray != pluginsObj["pluginArray"].End(); ++itPluginArray) {
        if (!itPluginArray->IsObject())
          break;
        auto &pluginObj = *itPluginArray;
        Plugins::Plugin plugin;
        if (pluginObj.HasMember("name") && pluginObj["name"].IsString()) {
          plugin.name = pluginObj["name"].GetString();
          plugin.key = plugin.name;
          std::transform(plugin.key.begin(), plugin.key.end(),
                         plugin.key.begin(), ::tolower);
        }
        if (pluginObj.HasMember("description") &&
            pluginObj["description"].IsString()) {
          plugin.description = pluginObj["description"].GetString();
        }
        if (pluginObj.HasMember("mimeTypes") &&
            pluginObj["mimeTypes"].IsArray()) {
          for (auto itMimeTypes = pluginObj["mimeTypes"].Begin();
               itMimeTypes != pluginObj["mimeTypes"].End(); ++itMimeTypes) {
            if (!itMimeTypes->IsObject())
              break;
            auto &mimeTypeObj = *itMimeTypes;
            Plugins::Plugin::MimeType mimeType;
            if (mimeTypeObj.HasMember("type") &&
                mimeTypeObj["type"].IsString()) {
              mimeType.type = mimeTypeObj["type"].GetString();
              mimeType.key = mimeType.type;
              std::transform(mimeType.key.begin(), mimeType.key.end(),
                             mimeType.key.begin(), ::tolower);
            }
            if (mimeTypeObj.HasMember("suffixes") &&
                mimeTypeObj["suffixes"].IsString()) {
              mimeType.suffixes = mimeTypeObj["suffixes"].GetString();
            }
            if (mimeType.key.empty())
              continue;
            plugin.mimeTypes.emplace(mimeType);
          }
        }
        if (plugin.key.empty())
          continue;
        plugins.plugins.emplace(plugin);
      }
    }
  } while (0);
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
    if (docHash.HasMember("base") && docHash["base"].IsNumber()) {
      if (docHash["base"].IsInt()) {
        base = docHash["base"].GetInt() * 1.0;
      } else if (docHash["base"].IsUint()) {
        base = docHash["base"].GetUint() * 1.0;
      } else if (docHash["base"].IsInt64()) {
        base = docHash["base"].GetInt64() * 1.0;
      } else if (docHash["base"].IsUint64()) {
        base = docHash["base"].GetUint64() * 1.0;
      } else if (docHash["base"].IsDouble()) {
        base = docHash["base"].GetDouble();
      }
    }
    if (docHash.HasMember("from") && docHash["from"].IsNumber()) {
      if (docHash["from"].IsInt()) {
        from = docHash["from"].GetInt() * 1.0;
      } else if (docHash["from"].IsUint()) {
        from = docHash["from"].GetUint() * 1.0;
      } else if (docHash["from"].IsInt64()) {
        from = docHash["from"].GetInt64() * 1.0;
      } else if (docHash["from"].IsUint64()) {
        from = docHash["from"].GetUint64() * 1.0;
      } else if (docHash["from"].IsDouble()) {
        from = docHash["from"].GetDouble();
      }
    }
    if (docHash.HasMember("to") && docHash["to"].IsNumber()) {
      if (docHash["to"].IsInt()) {
        to = docHash["to"].GetInt() * 1.0;
      } else if (docHash["to"].IsUint()) {
        to = docHash["to"].GetUint() * 1.0;
      } else if (docHash["to"].IsInt64()) {
        to = docHash["to"].GetInt64() * 1.0;
      } else if (docHash["to"].IsUint64()) {
        to = docHash["to"].GetUint64() * 1.0;
      } else if (docHash["to"].IsDouble()) {
        to = docHash["to"].GetDouble();
      }
    }
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

    do { //!@ .startup_urls
      if (!doc.HasMember("startup_urls"))
        break;
      if (!doc["startup_urls"].IsArray())
        break;
      for (auto it = doc["startup_urls"].Begin();
           it != doc["startup_urls"].End(); ++it) {
        if (!it->IsString())
          break;
        if (it->GetStringLength() <= 0)
          continue;
        startup_urls.emplace(it->GetString());
      }
    } while (0);
    do { //!@ .homepage
      if (!doc.HasMember("homepage"))
        break;
      if (!doc["homepage"].IsObject())
        break;
      auto &homepageObj = doc["homepage"];
      if (homepageObj.HasMember("enable") && homepageObj["enable"].IsBool()) {
        homepage.enable = homepageObj["enable"].GetBool();
      }
      if (homepageObj.HasMember("url") && homepageObj["url"].IsString()) {
        homepage.url = homepageObj["url"].GetString();
      }
      if (homepageObj.HasMember("open_new_tab") &&
          homepageObj["open_new_tab"].IsBool()) {
        homepage.open_new_tab = homepageObj["open_new_tab"].GetBool();
      }
    } while (0);
    do { //!@ .search_engine
      if (!doc.HasMember("search_engine"))
        break;
      if (!doc["search_engine"].IsString())
        break;
      if (doc["search_engine"].GetStringLength() <= 0)
        break;
      search_engine = doc["search_engine"].GetString();
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
      do { //!@ .fps.navigator
        if (!fpsObj.HasMember("navigator"))
          break;
        if (!fpsObj["navigator"].IsObject())
          break;
        fps.navigator << fpsObj["navigator"];

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
            Fps::Font::Keyword keyword;
            keyword.value = it->GetString();
            keyword.key = keyword.value;
            std::transform(keyword.key.begin(), keyword.key.end(),
                           keyword.key.begin(), ::tolower);
            fps.font.keywords.emplace(keyword);
          }
        }
        if (fpsObj["font"].HasMember("hash") &&
            fpsObj["font"]["hash"].IsObject()) {
          fps.font.hash << Json::toString(fpsObj["font"]["hash"]);
        }
      } while (0);
      do { //!@ .fps.timezone
        if (!fpsObj.HasMember("timezone"))
          break;
        if (!fpsObj["timezone"].IsObject())
          break;
        if (fpsObj["timezone"].HasMember("enable") &&
            fpsObj["timezone"]["enable"].IsBool())
          fps.timezone.enable = fpsObj["timezone"]["enable"].GetBool();
        if (fpsObj["timezone"].HasMember("hash") &&
            fpsObj["timezone"]["hash"].IsObject()) {
          fps.timezone.hash << Json::toString(fpsObj["timezone"]["hash"]);
        }
        if (fpsObj["timezone"].HasMember("source") &&
            fpsObj["timezone"]["source"].IsObject()) {
          for (auto it = fpsObj["timezone"]["source"].MemberBegin();
               it != fpsObj["timezone"]["source"].MemberEnd(); ++it) {
            do {
              auto &keyObj = it->name;
              auto &valObj = it->value;
              if (!keyObj.IsString())
                continue;
              if (!valObj.IsObject())
                continue;
              if (!valObj.HasMember("id") || !valObj["id"].IsUint())
                break;
              Fps::Timezone::Source source(valObj["id"].GetUint(),
                                           keyObj.GetString());
              if (!valObj.HasMember("offset") || !valObj["offset"].IsInt())
                break;
              source.offset = static_cast<decltype(source.offset)>(
                  valObj["offset"].GetInt());
              if (!valObj.HasMember("description") &&
                  !valObj["description"].IsString())
                break;
              source.description = valObj["description"].GetString();
              fps.timezone.sources.emplace(source.id, source);
            } while (0);
          }
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
        if (fpsObj["webgl"].HasMember("shaderPrecisionFormat") &&
            fpsObj["webgl"]["shaderPrecisionFormat"].IsObject()) {
          for (auto it = fpsObj["webgl"]["shaderPrecisionFormat"].MemberBegin();
               it != fpsObj["webgl"]["shaderPrecisionFormat"].MemberEnd();
               ++it) {
            if (!it->name.IsString())
              break;
            if (!it->value.IsObject())
              break;
            if (it->name.GetStringLength() <= 0)
              continue;
            std::string name = it->name.GetString();
            Fps::Webgl::ShaderPrecisionFormat::SharedType type =
                Fps::Webgl::ShaderPrecisionFormat::SharedType(
                    strtoul(name.c_str(), nullptr, 16));
            switch (type) {
            case Fps::Webgl::ShaderPrecisionFormat::SharedType::FRAGMENT_SHADER:
            case Fps::Webgl::ShaderPrecisionFormat::SharedType::VERTEX_SHADER:
              for (auto it2 = it->value.MemberBegin();
                   it2 != it->value.MemberEnd(); ++it2) {
                if (!it2->name.IsString())
                  continue;
                if (!it2->value.IsObject())
                  continue;
                if (it2->name.GetStringLength() <= 0)
                  continue;
                if (!it2->value.HasMember("rangeMin") ||
                    !it2->value["rangeMin"].IsInt())
                  continue;
                if (!it2->value.HasMember("rangeMax") ||
                    !it2->value["rangeMax"].IsInt())
                  continue;
                if (!it2->value.HasMember("precision") ||
                    !it2->value["precision"].IsInt())
                  continue;

                std::string name2 = it2->name.GetString();
                Fps::Webgl::ShaderPrecisionFormat::FormatType format_type =
                    Fps::Webgl::ShaderPrecisionFormat::FormatType(
                        strtoul(name2.c_str(), nullptr, 16));
                switch (format_type) {
                case Fps::Webgl::ShaderPrecisionFormat::FormatType::LOW_FLOAT:
                  if (type == Fps::Webgl::ShaderPrecisionFormat::SharedType::
                                  FRAGMENT_SHADER) {
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader.LOW_FLOAT
                        .rangeMin = it2->value["rangeMin"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader.LOW_FLOAT
                        .rangeMax = it2->value["rangeMax"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader.LOW_FLOAT
                        .precision = it2->value["precision"].GetInt();
                  } else {
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.LOW_FLOAT
                        .rangeMin = it2->value["rangeMin"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.LOW_FLOAT
                        .rangeMax = it2->value["rangeMax"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.LOW_FLOAT
                        .precision = it2->value["precision"].GetInt();
                  }
                  break;
                case Fps::Webgl::ShaderPrecisionFormat::FormatType::
                    MEDIUM_FLOAT:
                  if (type == Fps::Webgl::ShaderPrecisionFormat::SharedType::
                                  FRAGMENT_SHADER) {
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader
                        .MEDIUM_FLOAT.rangeMin =
                        it2->value["rangeMin"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader
                        .MEDIUM_FLOAT.rangeMax =
                        it2->value["rangeMax"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader
                        .MEDIUM_FLOAT.precision =
                        it2->value["precision"].GetInt();
                  } else {
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader
                        .MEDIUM_FLOAT.rangeMin =
                        it2->value["rangeMin"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader
                        .MEDIUM_FLOAT.rangeMax =
                        it2->value["rangeMax"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader
                        .MEDIUM_FLOAT.precision =
                        it2->value["precision"].GetInt();
                  }
                  break;
                case Fps::Webgl::ShaderPrecisionFormat::FormatType::HIGH_FLOAT:
                  if (type == Fps::Webgl::ShaderPrecisionFormat::SharedType::
                                  FRAGMENT_SHADER) {
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader
                        .HIGH_FLOAT.rangeMin = it2->value["rangeMin"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader
                        .HIGH_FLOAT.rangeMax = it2->value["rangeMax"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader
                        .HIGH_FLOAT.precision =
                        it2->value["precision"].GetInt();
                  } else {
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.HIGH_FLOAT
                        .rangeMin = it2->value["rangeMin"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.HIGH_FLOAT
                        .rangeMax = it2->value["rangeMax"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.HIGH_FLOAT
                        .precision = it2->value["precision"].GetInt();
                  }
                  break;
                case Fps::Webgl::ShaderPrecisionFormat::FormatType::LOW_INT:
                  if (type == Fps::Webgl::ShaderPrecisionFormat::SharedType::
                                  FRAGMENT_SHADER) {
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader.LOW_INT
                        .rangeMin = it2->value["rangeMin"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader.LOW_INT
                        .rangeMax = it2->value["rangeMax"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader.LOW_INT
                        .precision = it2->value["precision"].GetInt();

                  } else {
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.LOW_INT
                        .rangeMin = it2->value["rangeMin"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.LOW_INT
                        .rangeMax = it2->value["rangeMax"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.LOW_INT
                        .precision = it2->value["precision"].GetInt();
                  }
                  break;
                case Fps::Webgl::ShaderPrecisionFormat::FormatType::MEDIUM_INT:
                  if (type == Fps::Webgl::ShaderPrecisionFormat::SharedType::
                                  FRAGMENT_SHADER) {
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader
                        .MEDIUM_INT.rangeMin = it2->value["rangeMin"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader
                        .MEDIUM_INT.rangeMax = it2->value["rangeMax"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader
                        .MEDIUM_INT.precision =
                        it2->value["precision"].GetInt();
                  } else {
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.MEDIUM_INT
                        .rangeMin = it2->value["rangeMin"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.MEDIUM_INT
                        .rangeMax = it2->value["rangeMax"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.MEDIUM_INT
                        .precision = it2->value["precision"].GetInt();
                  }
                  break;
                case Fps::Webgl::ShaderPrecisionFormat::FormatType::HIGH_INT:
                  if (type == Fps::Webgl::ShaderPrecisionFormat::SharedType::
                                  FRAGMENT_SHADER) {
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader.HIGH_INT
                        .rangeMin = it2->value["rangeMin"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader.HIGH_INT
                        .rangeMax = it2->value["rangeMax"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader.HIGH_INT
                        .precision = it2->value["precision"].GetInt();

                  } else {
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.HIGH_INT
                        .rangeMin = it2->value["rangeMin"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.HIGH_INT
                        .rangeMax = it2->value["rangeMax"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.HIGH_INT
                        .precision = it2->value["precision"].GetInt();
                  }
                  break;
                default:
                  break;
                }
              }
              break;
            default:
              break;
            }
          }
        }

        if (fpsObj["webgl"].HasMember("contextAttributes") &&
            fpsObj["webgl"]["contextAttributes"].IsObject()) {
          for (auto it = fpsObj["webgl"]["contextAttributes"].MemberBegin();
               it != fpsObj["webgl"]["contextAttributes"].MemberEnd(); ++it) {
            do {
              if (!it->name.IsString())
                break;
              if (!it->value.IsBool())
                break;
              if (it->name.GetStringLength() <= 0)
                break;
              std::string name = it->name.GetString();
              if (name.compare("desynchronized") == 0) {
                fps.webgl.contextAttributes.desynchronized =
                    it->value.GetBool();
              } else if (name.compare("failIfMajorPerformanceCaveat") == 0) {
                fps.webgl.contextAttributes.failIfMajorPerformanceCaveat =
                    it->value.GetBool();
              } else if (name.compare("powerPreference") == 0) {
                fps.webgl.contextAttributes.powerPreference =
                    it->value.GetBool();
              } else if (name.compare("premultipliedAlpha") == 0) {
                fps.webgl.contextAttributes.premultipliedAlpha =
                    it->value.GetBool();
              } else if (name.compare("preserveDrawingBuffer") == 0) {
                fps.webgl.contextAttributes.preserveDrawingBuffer =
                    it->value.GetBool();
              } else if (name.compare("stencil") == 0) {
                fps.webgl.contextAttributes.stencil = it->value.GetBool();
              } else if (name.compare("alpha") == 0) {
                fps.webgl.contextAttributes.alpha = it->value.GetBool();
              } else if (name.compare("antialias") == 0) {
                fps.webgl.contextAttributes.antialias = it->value.GetBool();
              } else if (name.compare("depth") == 0) {
                fps.webgl.contextAttributes.depth = it->value.GetBool();
              } else if (name.compare("xrCompatible") == 0) {
                fps.webgl.contextAttributes.xrCompatible = it->value.GetBool();
              } else {
              }
            } while (0);
          }
        }
        if (fpsObj["webgl"].HasMember("enabledExtensions") &&
            fpsObj["webgl"]["enabledExtensions"].IsArray()) {
          for (auto it = fpsObj["webgl"]["enabledExtensions"].Begin();
               it != fpsObj["webgl"]["enabledExtensions"].End(); ++it) {
            if (!it->IsString())
              break;
            if (it->GetStringLength() <= 0)
              continue;
            std::string value = it->GetString();
            std::transform(value.begin(), value.end(), value.begin(),
                           ::tolower);
            fps.webgl.enabledExtensions.emplace(value);
          }
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
        if (fpsObj["screen"].HasMember("devicePixelRatio") &&
            fpsObj["screen"]["devicePixelRatio"].IsDouble()) {
          fps.screen.devicePixelRatio =
              fpsObj["screen"]["devicePixelRatio"].GetDouble();
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