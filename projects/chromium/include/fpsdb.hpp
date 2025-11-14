#if !defined(__91A7BCE8_86A7_49F2_8FE9_EF591734E9DD__)
#define __91A7BCE8_86A7_49F2_8FE9_EF591734E9DD__
#include "xsiumio.hpp"
#define CHROMIUM_XSIUMIO_IFPSDB_WEBGL_GETPARAMETER_ADD_INT(obj, map)           \
  do {                                                                         \
    if (!obj.IsObject())                                                       \
      break;                                                                   \
    for (auto pv = obj.MemberBegin(); pv != obj.MemberEnd(); ++pv) {           \
      if (!pv->name.IsString())                                                \
        break;                                                                 \
      if (!pv->value.IsArray())                                                \
        break;                                                                 \
      int key = strtol(pv->name.GetString(), nullptr, 10);                     \
      std::vector<int> vs;                                                     \
      for (auto v = pv->value.Begin(); v != pv->value.End(); ++v) {            \
        if (!v->IsInt())                                                       \
          break;                                                               \
        vs.emplace_back(v->GetInt());                                          \
      }                                                                        \
      map.emplace(key, vs);                                                    \
    }                                                                          \
  } while (0);

#define CHROMIUM_XSIUMIO_IFPSDB_WEBGL_GETPARAMETER_ADD_STRING(obj, map)        \
  do {                                                                         \
    if (!obj.IsObject())                                                       \
      break;                                                                   \
    for (auto pv = obj.MemberBegin(); pv != obj.MemberEnd(); ++pv) {           \
      if (!pv->name.IsString())                                                \
        break;                                                                 \
      if (!pv->value.IsArray())                                                \
        break;                                                                 \
      int key = strtol(pv->name.GetString(), nullptr, 10);                     \
      std::vector<std::string> vs;                                             \
      for (auto v = pv->value.Begin(); v != pv->value.End(); ++v) {            \
        if (!v->IsString())                                                    \
          break;                                                               \
        vs.emplace_back(v->GetString());                                       \
      }                                                                        \
      map.emplace(key, vs);                                                    \
    }                                                                          \
  } while (0);

namespace chromium {
namespace xsiumio {
class IFpsdb {
public:
  struct Platform {
    inline Platform();
    inline ~Platform();

    std::map<int /*key*/, std::string> source;
    void operator<<(const rapidjson::Value &value) {
      do {
        if (!value.IsObject())
          break;
        for (auto pv = value.MemberBegin(); pv != value.MemberEnd(); ++pv) {
          if (!pv->name.IsString())
            break;
          if (!pv->value.IsString())
            break;
          int key = strtol(pv->name.GetString(), nullptr, 10);
          source.emplace(key, pv->value.GetString());
        }
      } while (0);
    }
  };
  struct UserAgentMetadata {
    struct Brand_version_list {
      inline Brand_version_list();
      inline ~Brand_version_list();
      std::string brand;
      std::string version;
    };
    struct Brand_full_version_list {
      inline Brand_full_version_list();
      inline ~Brand_full_version_list();
      std::string brand;
      std::string version;
    };
    struct MetaData {
      inline MetaData();
      inline ~MetaData();
      inline MetaData(const MetaData &);

      std::vector<Brand_version_list> brand_version_list;
      std::vector<Brand_full_version_list> brand_full_version_list;
      std::string full_version;
      std::string platform;
      std::string platform_version;
      std::string architecture;
      std::string model;
      bool mobile = false;
      std::string bitness;
      bool wow64 = false;
      std::vector<std::string> form_factors;

      inline void operator<<(const rapidjson::Value &value) {
        do {
          if (!value.IsObject())
            break;
          if (value.HasMember("brand_version_list") &&
              value["brand_version_list"].IsArray()) {
            const rapidjson::Value &brands = value["brand_version_list"];
            for (rapidjson::SizeType i = 0; i < brands.Size(); ++i) {
              if (!brands[i].IsObject())
                continue;
              Brand_version_list bvl;
              if (brands[i].HasMember("brand") &&
                  brands[i]["brand"].IsString()) {
                bvl.brand = brands[i]["brand"].GetString();
              }
              if (brands[i].HasMember("version") &&
                  brands[i]["version"].IsString()) {
                bvl.version = brands[i]["version"].GetString();
              }
              brand_version_list.emplace_back(bvl);
            }
          }
          if (value.HasMember("brand_full_version_list") &&
              value["brand_full_version_list"].IsArray()) {
            const rapidjson::Value &brands = value["brand_full_version_list"];
            for (rapidjson::SizeType i = 0; i < brands.Size(); ++i) {
              if (!brands[i].IsObject())
                continue;
              Brand_full_version_list bfvl;
              if (brands[i].HasMember("brand") &&
                  brands[i]["brand"].IsString()) {
                bfvl.brand = brands[i]["brand"].GetString();
              }
              if (brands[i].HasMember("version") &&
                  brands[i]["version"].IsString()) {
                bfvl.version = brands[i]["version"].GetString();
              }
              brand_full_version_list.emplace_back(bfvl);
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
          if (value.HasMember("form_factors") &&
              value["form_factors"].IsArray()) {
            const rapidjson::Value &factors = value["form_factors"];
            for (rapidjson::SizeType i = 0; i < factors.Size(); ++i) {
              if (factors[i].IsString()) {
                form_factors.emplace_back(factors[i].GetString());
              }
            }
          }
        } while (0);
      }
    };
    inline UserAgentMetadata();
    inline ~UserAgentMetadata();

    std::map<int /*key*/, std::vector<MetaData>> source;
    void operator<<(const rapidjson::Value &value) {
      do {
        if (!value.IsObject())
          break;
        for (auto it = value.MemberBegin(); it != value.MemberEnd(); ++it) {
          if (!it->name.IsString())
            break;
          if (!it->value.IsArray())
            break;
          int key = strtol(it->name.GetString(), nullptr, 10);
          std::vector<MetaData> vs;
          for (auto v = it->value.Begin(); v != it->value.End(); ++v) {
            if (!v->IsObject())
              break;
            MetaData md;
            md << *v;
            vs.emplace_back(md);
          }
          source.emplace(key, vs);
        }
      } while (0);
    }
  };

  struct HardwareConcurrency {
    inline HardwareConcurrency();
    inline ~HardwareConcurrency();
    std::map<int /*key*/, std::vector<int>> source;

    void operator<<(const rapidjson::Value &value) {
      do {
        if (!value.IsObject())
          break;
        for (auto it = value.MemberBegin(); it != value.MemberEnd(); ++it) {
          if (!it->name.IsString())
            break;
          if (!it->value.IsArray())
            break;
          int key = strtol(it->name.GetString(), nullptr, 10);
          std::vector<int> vs;
          for (auto v = it->value.Begin(); v != it->value.End(); ++v) {
            if (!v->IsInt())
              break;
            vs.emplace_back(v->GetInt());
          }
          source.emplace(key, vs);
        }
      } while (0);
    }
  };

  struct DeviceMemory {
    inline DeviceMemory();
    inline ~DeviceMemory();

    std::map<int /*key*/, std::vector<int>> source;
    void operator<<(const rapidjson::Value &value) {
      do {
        if (!value.IsObject())
          break;
        for (auto it = value.MemberBegin(); it != value.MemberEnd(); ++it) {
          if (!it->name.IsString())
            break;
          if (!it->value.IsArray())
            break;
          int key = strtol(it->name.GetString(), nullptr, 10);
          std::vector<int> vs;
          for (auto v = it->value.Begin(); v != it->value.End(); ++v) {
            if (!v->IsInt())
              break;
            vs.emplace_back(v->GetInt());
          }
          source.emplace(key, vs);
        }
      } while (0);
    }
  };
  struct Webgl {
    inline Webgl();
    inline ~Webgl();
    std::map<int /*key*/, std::vector<xsiumio::IXSiumio::Fingerprint::Webgl>>
        source;

    void operator<<(const rapidjson::Value &value) {
      do {
        if (!value.IsObject())
          break;
        for (auto it = value.MemberBegin(); it != value.MemberEnd(); ++it) {
          if (!it->name.IsString())
            break;
          if (!it->value.IsArray())
            break;
          int key = strtol(it->name.GetString(), nullptr, 10);
          std::vector<xsiumio::IXSiumio::Fingerprint::Webgl> vs;
          for (auto v = it->value.Begin(); v != it->value.End(); ++v) {
            if (!v->IsObject())
              break;
            xsiumio::IXSiumio::Fingerprint::Webgl webgl_entry;
            webgl_entry << *v;
            vs.emplace_back(webgl_entry);
          }
          source.emplace(key, vs);
        }
      } while (0);
    }
  };

  struct Voice {
    inline Voice();
    inline ~Voice();

    std::string lang;
    std::string name;
    std::string description;
  };

  struct Font {
    inline Font();
    inline ~Font();
    inline Font(const Font &);
    std::vector<std::string> family;
  };

  struct Screen {

    inline Screen();
    inline ~Screen();

    std::map<int /*key*/, std::vector<xsiumio::IXSiumio::Fingerprint::Screen>>
        source;
    void operator<<(const rapidjson::Value &value) {
      do {
        if (!value.IsObject())
          break;
        for (auto it = value.MemberBegin(); it != value.MemberEnd(); ++it) {
          if (!it->name.IsString())
            break;
          if (!it->value.IsArray())
            break;
          int key = strtol(it->name.GetString(), nullptr, 10);
          std::vector<xsiumio::IXSiumio::Fingerprint::Screen> vs;
          for (auto v = it->value.Begin(); v != it->value.End(); ++v) {
            if (!v->IsObject())
              break;
            xsiumio::IXSiumio::Fingerprint::Screen screen_entry;
            screen_entry << *v;
            vs.emplace_back(screen_entry);
          }
          source.emplace(key, vs);
        }
      } while (0);
    }
  };

  struct Hash {
    inline Hash();
    inline ~Hash();

    double from = 0.0;
    double to = 0.0;
    std::vector<double> base;

    void operator<<(const rapidjson::Value &value) {
      do {
        if (!value.IsObject())
          break;
        if (value.HasMember("from") && value["from"].IsDouble())
          from = value["from"].GetDouble();
        if (value.HasMember("to") && value["to"].IsDouble())
          to = value["to"].GetDouble();
        if (value.HasMember("base") && value["base"].IsArray()) {
          for (auto it = value["base"].Begin(); it != value["base"].End();
               ++it) {
            if (!it->IsDouble())
              break;
            base.emplace_back(it->GetDouble());
          }
        }
      } while (0);
    }
  };

  struct Browser {
    inline Browser();
    inline ~Browser();

    xsiumio::IXSiumio::Fingerprint::UserAgentMetadata userAgentMetadata;
    std::string userAgent;
    xsiumio::IXSiumio::Fingerprint::Product product;
  };

  struct Tzlang {
    inline Tzlang();
    inline ~Tzlang();

    std::map<std::string /*timezone*/, std::vector<std::string> /*language*/>
        languages;
    std::vector<std::string> GetLanguages(const std::string &tz) const {
      std::vector<std::string> result{"en-US", "en"};
      auto f = languages.find(tz);
      if (f != languages.end()) {
        result.clear();
        result = f->second;
      }
      return result;
    }
    void operator<<(const rapidjson::Value &value) {
      do {
        if (!value.IsObject())
          break;
        for (auto it = value.MemberBegin(); it != value.MemberEnd(); ++it) {
          if (!it->name.IsString())
            break;
          if (!it->value.IsObject())
            break;
          if (!it->value.HasMember("languages"))
            break;
          if (!it->value["languages"].IsArray())
            break;
          std::string key = it->name.GetString();
          std::vector<std::string> vs;
          for (auto v = it->value["languages"].Begin();
               v != it->value["languages"].End(); ++v) {
            if (!v->IsString())
              break;
            vs.emplace_back(v->GetString());
          }
          languages.emplace(key, vs);
        }
      } while (0);
    }
  };

public:
  inline IFpsdb();
  inline ~IFpsdb();
  inline void Release() const;
  inline void operator<<(const std::string &input);
  inline bool ValidPlatformKey(int key) const {
    bool result = false;
    do {
      if (platform.source.empty())
        break;
      result = platform.source.find(key) != platform.source.end();
    } while (0);
    return result;
  }
  Platform platform;
  std::map<int /*key*/, std::vector<Browser>> browsers;
  UserAgentMetadata userAgentMetadata;
  DeviceMemory deviceMemory;
  Webgl webgl;
  Tzlang tzlang;
  HardwareConcurrency hardwareConcurrency;
  std::vector<Voice> voice;
  std::map<int /*key*/, Font> font;
  Screen screen;
  Hash hash_canvas;
  Hash hash_webgl;
  Hash hash_audio;
  std::map<int /*key*/,
           std::vector<
               chromium::xsiumio::IXSiumio::Fingerprint::CdmRegistry::CdmEntry>>
      cdmRegistry;
};
inline IFpsdb::IFpsdb() {
}
inline IFpsdb::~IFpsdb() {
}
inline void IFpsdb::Release() const {
  delete this;
}
inline void IFpsdb::operator<<(const std::string &input) {
  do {
    if (input.empty())
      break;
    rapidjson::Document doc(rapidjson::Type::kObjectType);
    if (doc.Parse(input.data(), input.size()).HasParseError())
      break;
    if (!doc.IsObject())
      break;
    if (!doc.HasMember("fpsdb") || !doc["fpsdb"].IsObject())
      break;
    const rapidjson::Value &fpsdb = doc["fpsdb"];
    if (fpsdb.HasMember("platform") && fpsdb["platform"].IsObject()) {
      platform << fpsdb["platform"];
    }
    if (fpsdb.HasMember("browser") && fpsdb["browser"].IsObject()) {
      for (auto it_browser = fpsdb["browser"].MemberBegin();
           it_browser != fpsdb["browser"].MemberEnd(); ++it_browser) {
        if (!it_browser->name.IsString())
          break;
        if (!it_browser->value.IsArray())
          break;
        int key = strtol(it_browser->name.GetString(), nullptr, 10);
        std::vector<Browser> vs;
        for (auto it_browser_elem = it_browser->value.Begin();
             it_browser_elem != it_browser->value.End(); ++it_browser_elem) {
          if (!it_browser_elem->IsObject())
            break;
          Browser browser;
          for (auto it_field = it_browser_elem->MemberBegin();
               it_field != it_browser_elem->MemberEnd(); ++it_field) {
            if (!it_field->name.IsString())
              break;
            if (it_field->name == "userAgentMetadata" &&
                it_field->value.IsObject()) {
              browser.userAgentMetadata << it_field->value;
            } else if (it_field->name == "userAgent" &&
                       it_field->value.IsString()) {
              browser.userAgent = it_field->value.GetString();
            } else if (it_field->name == "product" &&
                       it_field->value.IsObject()) {
              browser.product << it_field->value;
            }
          }
          vs.emplace_back(browser);
        }
        browsers.emplace(key, std::move(vs));
      }
    }
    if (fpsdb.HasMember("userAgentMetadata") &&
        fpsdb["userAgentMetadata"].IsObject()) {
      userAgentMetadata << fpsdb["userAgentMetadata"];
    }
    if (fpsdb.HasMember("hardwareConcurrency") &&
        fpsdb["hardwareConcurrency"].IsObject()) {
      hardwareConcurrency << fpsdb["hardwareConcurrency"];
    }
    if (fpsdb.HasMember("deviceMemory") && fpsdb["deviceMemory"].IsObject()) {
      deviceMemory << fpsdb["deviceMemory"];
    }
    if (fpsdb.HasMember("tzlang") && fpsdb["tzlang"].IsObject()) {
      tzlang << fpsdb["tzlang"];
    }
    if (fpsdb.HasMember("webgl") && fpsdb["webgl"].IsObject()) {
      webgl << fpsdb["webgl"];
    }
    if (fpsdb.HasMember("voice") && fpsdb["voice"].IsArray()) {
      const rapidjson::Value &vObj = fpsdb["voice"];
      for (rapidjson::SizeType i = 0; i < vObj.Size(); ++i) {
        if (!vObj[i].IsObject())
          continue;
        Voice voc;
        if (vObj[i].HasMember("lang") && vObj[i]["lang"].IsString()) {
          voc.lang = vObj[i]["lang"].GetString();
        }
        if (vObj[i].HasMember("name") && vObj[i]["name"].IsString()) {
          voc.name = vObj[i]["name"].GetString();
        }
        if (vObj[i].HasMember("description") &&
            vObj[i]["description"].IsString()) {
          voc.description = vObj[i]["description"].GetString();
        }
        voice.emplace_back(voc);
      }
    }
    if (fpsdb.HasMember("cdmRegistry") && fpsdb["cdmRegistry"].IsObject()) {
      for (auto it = fpsdb["cdmRegistry"].MemberBegin();
           it != fpsdb["cdmRegistry"].MemberEnd(); ++it) {
        if (!it->name.IsString())
          break;
        if (!it->value.IsArray())
          break;
        int key = strtol(it->name.GetString(), nullptr, 10);
        std::vector<
            chromium::xsiumio::IXSiumio::Fingerprint::CdmRegistry::CdmEntry>
            vs;
        for (auto v = it->value.Begin(); v != it->value.End(); ++v) {
          if (!v->IsObject())
            break;
          chromium::xsiumio::IXSiumio::Fingerprint::CdmRegistry::CdmEntry cdm;
          cdm << *v;
          vs.emplace_back(cdm);
        }
        cdmRegistry.emplace(key, std::move(vs));
      }
    }

    if (fpsdb.HasMember("font") && fpsdb["font"].IsObject()) {
      const auto &obj = fpsdb["font"];
      for (auto it = obj.MemberBegin(); it != obj.MemberEnd(); ++it) {
        if (!it->name.IsString())
          break;
        if (!it->value.IsArray())
          break;
        Font font_;
        int key = strtol(it->name.GetString(), nullptr, 10);
        for (auto f = it->value.Begin(); f != it->value.End(); ++f) {
          if (!f->IsString())
            break;
          font_.family.emplace_back(f->GetString());
        }
        font.emplace(key, font_);
      }
    }
    if (fpsdb.HasMember("screen") && fpsdb["screen"].IsObject()) {
      screen << fpsdb["screen"];
    }
    if (fpsdb.HasMember("hash") && fpsdb["hash"].IsObject()) {
      if (fpsdb["hash"].HasMember("canvas") &&
          fpsdb["hash"]["canvas"].IsObject()) {
        hash_canvas << fpsdb["hash"]["canvas"];
      }
      if (fpsdb["hash"].HasMember("webgl") &&
          fpsdb["hash"]["webgl"].IsObject()) {
        hash_webgl << fpsdb["hash"]["webgl"];
      }
      if (fpsdb["hash"].HasMember("audio") &&
          fpsdb["hash"]["audio"].IsObject()) {
        hash_audio << fpsdb["hash"]["audio"];
      }
    }
  } while (0);
}

////////////////////////////////////////////////////////////////////////////////
inline IFpsdb::Platform::Platform() = default;
inline IFpsdb::Platform::~Platform() = default;
inline IFpsdb::Browser::Browser() = default;
inline IFpsdb::Browser::~Browser() = default;
inline IFpsdb::Tzlang::Tzlang() = default;
inline IFpsdb::Tzlang::~Tzlang() = default;
inline IFpsdb::UserAgentMetadata::UserAgentMetadata() = default;
inline IFpsdb::UserAgentMetadata::~UserAgentMetadata() = default;
inline IFpsdb::UserAgentMetadata::Brand_version_list::Brand_version_list() =
    default;
inline IFpsdb::UserAgentMetadata::Brand_version_list::~Brand_version_list() =
    default;
inline IFpsdb::UserAgentMetadata::Brand_full_version_list::
    Brand_full_version_list() = default;
inline IFpsdb::UserAgentMetadata::Brand_full_version_list::
    ~Brand_full_version_list() = default;
inline IFpsdb::UserAgentMetadata::MetaData::MetaData() = default;
inline IFpsdb::UserAgentMetadata::MetaData::~MetaData() = default;
inline IFpsdb::UserAgentMetadata::MetaData::MetaData(
    const IFpsdb::UserAgentMetadata::MetaData &) = default;

inline IFpsdb::HardwareConcurrency::HardwareConcurrency() = default;
inline IFpsdb::HardwareConcurrency::~HardwareConcurrency() = default;
inline IFpsdb::DeviceMemory::DeviceMemory() = default;
inline IFpsdb::DeviceMemory::~DeviceMemory() = default;
inline IFpsdb::Webgl::Webgl() = default;
inline IFpsdb::Webgl::~Webgl() = default;
inline IFpsdb::Voice::Voice() = default;
inline IFpsdb::Voice::~Voice() = default;
inline IFpsdb::Font::Font() = default;
inline IFpsdb::Font::~Font() = default;
inline IFpsdb::Font::Font(const IFpsdb::Font &) = default;
inline IFpsdb::Screen::Screen() = default;
inline IFpsdb::Screen::~Screen() = default;
inline IFpsdb::Hash::Hash() = default;
inline IFpsdb::Hash::~Hash() = default;
} // namespace xsiumio
} // namespace chromium

/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 28 Jul 2025 11:12:06 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__91A7BCE8_86A7_49F2_8FE9_EF591734E9DD__