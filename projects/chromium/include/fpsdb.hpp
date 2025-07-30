#if !defined(__91A7BCE8_86A7_49F2_8FE9_EF591734E9DD__)
#define __91A7BCE8_86A7_49F2_8FE9_EF591734E9DD__

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

  struct Languages {
    inline Languages();
    inline ~Languages();
    std::vector<std::string> language;
    std::string acceptLanguage;
    inline void operator<<(const rapidjson::Value &value) {
      do {
        if (!value.IsObject())
          break;
        if (value.HasMember("language") && value["language"].IsArray()) {
          const rapidjson::Value &langs = value["language"];
          for (rapidjson::SizeType i = 0; i < langs.Size(); ++i) {
            if (langs[i].IsString()) {
              language.emplace_back(langs[i].GetString());
            }
          }
        }
        if (value.HasMember("accept_language") &&
            value["accept_language"].IsString()) {
          acceptLanguage = value["accept_language"].GetString();
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

  struct UserAgent {
    inline UserAgent();
    inline ~UserAgent();

    std::map<int /*key*/, std::vector<std::string>> source;
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
          std::vector<std::string> vs;
          for (auto v = it->value.Begin(); v != it->value.End(); ++v) {
            if (!v->IsString())
              break;
            vs.emplace_back(v->GetString());
          }
          source.emplace(key, vs);
        }
      } while (0);
    }
  };

  struct Webgl {
    struct GetParameter {
      struct Devices {
        inline Devices();
        inline ~Devices();
        std::string _7936_;
        std::string _7937_;
        std::string _37445_;
        std::string _37446_;
      };
      inline GetParameter();
      inline ~GetParameter();
      std::map<int /*key*/, std::vector<int>> _3379_;
      std::map<int /*key*/, std::vector<int>> _3386_;
      std::map<int /*key*/, std::vector<int>> _3410_;
      std::map<int /*key*/, std::vector<int>> _3411_;
      std::map<int /*key*/, std::vector<int>> _3412_;
      std::map<int /*key*/, std::vector<int>> _3413_;
      std::map<int /*key*/, std::vector<int>> _3414_;
      std::map<int /*key*/, std::vector<int>> _3415_;
      std::map<int /*key*/, std::vector<std::string>> _33901_;
      std::map<int /*key*/, std::vector<int>> _34024_;
      std::map<int /*key*/, std::vector<int>> _34047_;
      std::map<int /*key*/, std::vector<int>> _34076_;
      std::map<int /*key*/, std::vector<int>> _34921_;
      std::map<int /*key*/, std::vector<int>> _34930_;
      std::map<int /*key*/, std::vector<int>> _35660_;
      std::map<int /*key*/, std::vector<int>> _35661_;
      std::map<int /*key*/, std::vector<int>> _36347_;
      std::map<int /*key*/, std::vector<int>> _36348_;
      std::map<int /*key*/, std::vector<int>> _36349_;
      std::map<int /*key*/, std::vector<Devices>> _devices_;

      void operator<<(const rapidjson::Value &value) {
        do {
          if (!value.IsObject())
            break;
          for (auto it = value.MemberBegin(); it != value.MemberEnd(); ++it) {
            if (!it->name.IsString())
              break;
            if (!it->value.IsObject())
              break;
            if (strcmp("devices", it->name.GetString()) == 0) {
              do {
                if (!it->value.IsObject())
                  break;
                for (auto jt = it->value.MemberBegin();
                     jt != it->value.MemberEnd(); ++jt) {
                  if (!jt->name.IsString())
                    break;
                  if (!jt->value.IsArray())
                    break;
                  const int key = strtol(jt->name.GetString(), nullptr, 10);
                  std::vector<Devices> ds;
                  for (auto jt2 = jt->value.Begin(); jt2 != jt->value.End();
                       ++jt2) {
                    if (!jt2->IsObject())
                      break;
                    Devices d;
                    for (auto jt3 = jt2->MemberBegin(); jt3 != jt2->MemberEnd();
                         ++jt3) {
                      if (!jt3->name.IsString())
                        break;
                      if (!jt3->value.IsString())
                        break;
                      const int pname =
                          strtol(jt3->name.GetString(), nullptr, 10);
                      switch (pname) {
                      case 7936: {
                        d._7936_ = jt3->value.GetString();
                      } break;
                      case 7937: {
                        d._7937_ = jt3->value.GetString();
                      } break;
                      case 37445: {
                        d._37445_ = jt3->value.GetString();
                      } break;
                      case 37446: {
                        d._37446_ = jt3->value.GetString();
                      } break;
                      default:
                        break;
                      }
                    }
                    ds.push_back(d);
                  }
                  _devices_.emplace(key, ds);
                }
              } while (0);
              continue;
            }
            const int pname = strtol(it->name.GetString(), nullptr, 10);
            switch (pname) {
            case 3379: {
              CHROMIUM_XSIUMIO_IFPSDB_WEBGL_GETPARAMETER_ADD_INT(it->value,
                                                                 _3379_);
            } break;
            case 3386: {
              CHROMIUM_XSIUMIO_IFPSDB_WEBGL_GETPARAMETER_ADD_INT(it->value,
                                                                 _3386_);
            } break;
            case 3410: {
              CHROMIUM_XSIUMIO_IFPSDB_WEBGL_GETPARAMETER_ADD_INT(it->value,
                                                                 _3410_);
            } break;
            case 3411: {
              CHROMIUM_XSIUMIO_IFPSDB_WEBGL_GETPARAMETER_ADD_INT(it->value,
                                                                 _3411_);
            } break;
            case 3412: {
              CHROMIUM_XSIUMIO_IFPSDB_WEBGL_GETPARAMETER_ADD_INT(it->value,
                                                                 _3412_);
            } break;
            case 3413: {
              CHROMIUM_XSIUMIO_IFPSDB_WEBGL_GETPARAMETER_ADD_INT(it->value,
                                                                 _3413_);
            } break;
            case 3414: {
              CHROMIUM_XSIUMIO_IFPSDB_WEBGL_GETPARAMETER_ADD_INT(it->value,
                                                                 _3414_);
            } break;
            case 3415: {
              CHROMIUM_XSIUMIO_IFPSDB_WEBGL_GETPARAMETER_ADD_INT(it->value,
                                                                 _3415_);
            } break;
            case 34024: {
              CHROMIUM_XSIUMIO_IFPSDB_WEBGL_GETPARAMETER_ADD_INT(it->value,
                                                                 _34024_);
            } break;
            case 34047: {
              CHROMIUM_XSIUMIO_IFPSDB_WEBGL_GETPARAMETER_ADD_INT(it->value,
                                                                 _34047_);
            } break;
            case 34076: {
              CHROMIUM_XSIUMIO_IFPSDB_WEBGL_GETPARAMETER_ADD_INT(it->value,
                                                                 _34076_);
            } break;
            case 34921: {
              CHROMIUM_XSIUMIO_IFPSDB_WEBGL_GETPARAMETER_ADD_INT(it->value,
                                                                 _34921_);
            } break;
            case 34930: {
              CHROMIUM_XSIUMIO_IFPSDB_WEBGL_GETPARAMETER_ADD_INT(it->value,
                                                                 _34930_);
            } break;
            case 35660: {
              CHROMIUM_XSIUMIO_IFPSDB_WEBGL_GETPARAMETER_ADD_INT(it->value,
                                                                 _35660_);
            } break;
            case 35661: {
              CHROMIUM_XSIUMIO_IFPSDB_WEBGL_GETPARAMETER_ADD_INT(it->value,
                                                                 _35661_);
            } break;
            case 36347: {
              CHROMIUM_XSIUMIO_IFPSDB_WEBGL_GETPARAMETER_ADD_INT(it->value,
                                                                 _36347_);
            } break;
            case 36348: {
              CHROMIUM_XSIUMIO_IFPSDB_WEBGL_GETPARAMETER_ADD_INT(it->value,
                                                                 _36348_);
            } break;
            case 36349: {
              CHROMIUM_XSIUMIO_IFPSDB_WEBGL_GETPARAMETER_ADD_INT(it->value,
                                                                 _36349_);
            } break;
            case 33901: {
              CHROMIUM_XSIUMIO_IFPSDB_WEBGL_GETPARAMETER_ADD_STRING(it->value,
                                                                    _33901_);
            } break;
            default:
              break;
            }
          }
        } while (0);
      }
    };
    inline Webgl();
    inline ~Webgl();

    GetParameter getParameter;

    void operator<<(const rapidjson::Value &value) {
      do {
        if (!value.IsObject())
          break;
        if (value.HasMember("getParameter") &&
            value["getParameter"].IsObject()) {
          getParameter << value["getParameter"];
        }
      } while (0);
    }
  };

  struct Voice {
    inline Voice();
    inline ~Voice();
    std::string lang;
    std::string name;
  };

  struct Font {
    inline Font();
    inline ~Font();
    std::vector<std::string> family;
  };

  struct Screen {
    struct Info {
      inline Info();
      inline ~Info();
      double height = 0;
      double width = 0;
      int colorDepth = 0;
      int pixelDepth = 0;
      double availLeft = 0;
      double availTop = 0;
      double availHeight = 0;
      double availWidth = 0;
      double devicePixelRatio = 1.0f;
      void operator<<(const rapidjson::Value &value) {
        do {
          if (!value.IsObject())
            break;
          if (value.HasMember("colorDepth") && value["colorDepth"].IsInt())
            colorDepth = value["colorDepth"].GetInt();
          if (value.HasMember("pixelDepth") && value["pixelDepth"].IsInt())
            pixelDepth = value["pixelDepth"].GetInt();
          if (value.HasMember("height")) {
            if (value["height"].IsInt())
              height = value["height"].GetInt() * 1.0f;
            else if (value["height"].IsDouble())
              height = value["height"].GetDouble();
          }
          if (value.HasMember("width")) {
            if (value["width"].IsInt())
              width = value["width"].GetInt() * 1.0f;
            else if (value["width"].IsDouble())
              width = value["width"].GetDouble();
          }
          if (value.HasMember("availLeft")) {
            if (value["availLeft"].IsInt())
              availLeft = value["availLeft"].GetInt() * 1.0f;
            else if (value["availLeft"].IsDouble())
              availLeft = value["availLeft"].GetDouble();
          }
          if (value.HasMember("availTop")) {
            if (value["availTop"].IsInt())
              availTop = value["availTop"].GetInt() * 1.0f;
            else if (value["availTop"].IsDouble())
              availTop = value["availTop"].GetDouble();
          }
          if (value.HasMember("availHeight")) {
            if (value["availHeight"].IsInt())
              availHeight = value["availHeight"].GetInt() * 1.0f;
            else if (value["availHeight"].IsDouble())
              availHeight = value["availHeight"].GetDouble();
          }
          if (value.HasMember("availWidth")) {
            if (value["availWidth"].IsInt())
              availWidth = value["availWidth"].GetInt() * 1.0f;
            else if (value["availWidth"].IsDouble())
              availWidth = value["availWidth"].GetDouble();
          }
          if (value.HasMember("devicePixelRatio")) {
            if (value["devicePixelRatio"].IsInt())
              devicePixelRatio = value["devicePixelRatio"].GetInt() * 1.0f;
            else if (value["devicePixelRatio"].IsDouble())
              devicePixelRatio = value["devicePixelRatio"].GetDouble();
          }
        } while (0);
      }
    };
    inline Screen();
    inline ~Screen();

    std::map<int /*key*/, std::vector<Info>> source;
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
          std::vector<Info> vs;
          for (auto v = it->value.Begin(); v != it->value.End(); ++v) {
            if (!v->IsObject())
              break;
            Info info;
            info << *v;
            vs.emplace_back(info);
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

public:
  inline IFpsdb();
  inline ~IFpsdb();
  inline void Release() const;
  inline void operator<<(const std::string &input);
  Platform platform;
  std::vector<Languages> languages;
  UserAgentMetadata userAgentMetadata;
  DeviceMemory deviceMemory;
  UserAgent userAgent;
  Webgl webgl;
  HardwareConcurrency hardwareConcurrency;
  std::vector<Voice> voice;
  std::map<int /*key*/, Font> font;
  Screen screen;
  Hash hash_canvas;
  Hash hash_webgl;
  Hash hash_audio;
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
    if (fpsdb.HasMember("languages") && fpsdb["languages"].IsObject()) {
      Languages langs;
      langs << fpsdb["languages"];
      languages.emplace_back(langs);
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
    if (fpsdb.HasMember("userAgent") && fpsdb["userAgent"].IsObject()) {
      userAgent << fpsdb["userAgent"];
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
        voice.emplace_back(voc);
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
inline IFpsdb::Languages::Languages() = default;
inline IFpsdb::Languages::~Languages() = default;
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
inline IFpsdb::HardwareConcurrency::HardwareConcurrency() = default;
inline IFpsdb::HardwareConcurrency::~HardwareConcurrency() = default;
inline IFpsdb::DeviceMemory::DeviceMemory() = default;
inline IFpsdb::DeviceMemory::~DeviceMemory() = default;
inline IFpsdb::UserAgent::UserAgent() = default;
inline IFpsdb::UserAgent::~UserAgent() = default;
inline IFpsdb::Webgl::Webgl() = default;
inline IFpsdb::Webgl::~Webgl() = default;
inline IFpsdb::Webgl::GetParameter::GetParameter() = default;
inline IFpsdb::Webgl::GetParameter::~GetParameter() = default;
inline IFpsdb::Webgl::GetParameter::Devices::Devices() = default;
inline IFpsdb::Webgl::GetParameter::Devices::~Devices() = default;
inline IFpsdb::Voice::Voice() = default;
inline IFpsdb::Voice::~Voice() = default;
inline IFpsdb::Font::Font() = default;
inline IFpsdb::Font::~Font() = default;
inline IFpsdb::Screen::Screen() = default;
inline IFpsdb::Screen::~Screen() = default;
inline IFpsdb::Screen::Info::Info() = default;
inline IFpsdb::Screen::Info::~Info() = default;
inline IFpsdb::Hash::Hash() = default;
inline IFpsdb::Hash::~Hash() = default;
} // namespace xsiumio
} // namespace chromium

/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 28 Jul 2025 11:12:06 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__91A7BCE8_86A7_49F2_8FE9_EF591734E9DD__