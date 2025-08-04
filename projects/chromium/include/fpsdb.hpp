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

    struct ContextAttributes {
      inline ContextAttributes();
      inline ~ContextAttributes();
      bool alpha = false;
      bool depth = false;
      bool stencil = false;
      bool antialias = false;
      bool premultipliedAlpha = false;
      bool preserveDrawingBuffer = false;
      bool failIfMajorPerformanceCaveat = false;
      std::string powerPreference = "default";
      bool xrCompatible = false;
      void operator<<(const rapidjson::Value &value) {
        do {
          if (!value.IsObject())
            break;
          if (value.HasMember("alpha") && value["alpha"].IsBool()) {
            alpha = value["alpha"].GetBool();
          }
          if (value.HasMember("depth") && value["depth"].IsBool()) {
            depth = value["depth"].GetBool();
          }
          if (value.HasMember("stencil") && value["stencil"].IsBool()) {
            stencil = value["stencil"].GetBool();
          }
          if (value.HasMember("antialias") && value["antialias"].IsBool()) {
            antialias = value["antialias"].GetBool();
          }
          if (value.HasMember("premultipliedAlpha") &&
              value["premultipliedAlpha"].IsBool()) {
            premultipliedAlpha = value["premultipliedAlpha"].GetBool();
          }
          if (value.HasMember("preserveDrawingBuffer") &&
              value["preserveDrawingBuffer"].IsBool()) {
            preserveDrawingBuffer = value["preserveDrawingBuffer"].GetBool();
          }
          if (value.HasMember("failIfMajorPerformanceCaveat") &&
              value["failIfMajorPerformanceCaveat"].IsBool()) {
            failIfMajorPerformanceCaveat =
                value["failIfMajorPerformanceCaveat"].GetBool();
          }
          if (value.HasMember("powerPreference") &&
              value["powerPreference"].IsString()) {
            powerPreference = value["powerPreference"].GetString();
          }
          if (value.HasMember("xrCompatible") &&
              value["xrCompatible"].IsBool()) {
            xrCompatible = value["xrCompatible"].GetBool();
          }
        } while (0);
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
        void operator<<(const rapidjson::Value &v) {
          do {
            if (!v.IsObject())
              break;
            if (v.HasMember("8DF0") && v["8DF0"].IsObject()) {
              const rapidjson::Value &refObj = v["8DF0"];
              if (refObj.HasMember("rangeMin") && refObj["rangeMin"].IsInt()) {
                _8DF0.rangeMin = refObj["rangeMin"].GetInt();
              }
              if (refObj.HasMember("rangeMax") && refObj["rangeMax"].IsInt()) {
                _8DF0.rangeMax = refObj["rangeMax"].GetInt();
              }
              if (refObj.HasMember("precision") &&
                  refObj["precision"].IsInt()) {
                _8DF0.precision = refObj["precision"].GetInt();
              }
            }
            if (v.HasMember("8DF1") && v["8DF1"].IsObject()) {
              const rapidjson::Value &refObj = v["8DF1"];
              if (refObj.HasMember("rangeMin") && refObj["rangeMin"].IsInt()) {
                _8DF1.rangeMin = refObj["rangeMin"].GetInt();
              }
              if (refObj.HasMember("rangeMax") && refObj["rangeMax"].IsInt()) {
                _8DF1.rangeMax = refObj["rangeMax"].GetInt();
              }
              if (refObj.HasMember("precision") &&
                  refObj["precision"].IsInt()) {
                _8DF1.precision = refObj["precision"].GetInt();
              }
            }
            if (v.HasMember("8DF2") && v["8DF2"].IsObject()) {
              const rapidjson::Value &refObj = v["8DF2"];
              if (refObj.HasMember("rangeMin") && refObj["rangeMin"].IsInt()) {
                _8DF2.rangeMin = refObj["rangeMin"].GetInt();
              }
              if (refObj.HasMember("rangeMax") && refObj["rangeMax"].IsInt()) {
                _8DF2.rangeMax = refObj["rangeMax"].GetInt();
              }
              if (refObj.HasMember("precision") &&
                  refObj["precision"].IsInt()) {
                _8DF2.precision = refObj["precision"].GetInt();
              }
            }
            if (v.HasMember("8DF3") && v["8DF3"].IsObject()) {
              const rapidjson::Value &refObj = v["8DF3"];
              if (refObj.HasMember("rangeMin") && refObj["rangeMin"].IsInt()) {
                _8DF3.rangeMin = refObj["rangeMin"].GetInt();
              }
              if (refObj.HasMember("rangeMax") && refObj["rangeMax"].IsInt()) {
                _8DF3.rangeMax = refObj["rangeMax"].GetInt();
              }
              if (refObj.HasMember("precision") &&
                  refObj["precision"].IsInt()) {
                _8DF3.precision = refObj["precision"].GetInt();
              }
            }
            if (v.HasMember("8DF4") && v["8DF4"].IsObject()) {
              const rapidjson::Value &refObj = v["8DF4"];
              if (refObj.HasMember("rangeMin") && refObj["rangeMin"].IsInt()) {
                _8DF4.rangeMin = refObj["rangeMin"].GetInt();
              }
              if (refObj.HasMember("rangeMax") && refObj["rangeMax"].IsInt()) {
                _8DF4.rangeMax = refObj["rangeMax"].GetInt();
              }
              if (refObj.HasMember("precision") &&
                  refObj["precision"].IsInt()) {
                _8DF4.precision = refObj["precision"].GetInt();
              }
            }
            if (v.HasMember("8DF5") && v["8DF5"].IsObject()) {
              const rapidjson::Value &refObj = v["8DF5"];
              if (refObj.HasMember("rangeMin") && refObj["rangeMin"].IsInt()) {
                _8DF5.rangeMin = refObj["rangeMin"].GetInt();
              }
              if (refObj.HasMember("rangeMax") && refObj["rangeMax"].IsInt()) {
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
        void operator<<(const rapidjson::Value &v) {
          do {
            if (!v.IsObject())
              break;
            if (v.HasMember("8DF0") && v["8DF0"].IsObject()) {
              const rapidjson::Value &refObj = v["8DF0"];
              if (refObj.HasMember("rangeMin") && refObj["rangeMin"].IsInt()) {
                _8DF0.rangeMin = refObj["rangeMin"].GetInt();
              }
              if (refObj.HasMember("rangeMax") && refObj["rangeMax"].IsInt()) {
                _8DF0.rangeMax = refObj["rangeMax"].GetInt();
              }
              if (refObj.HasMember("precision") &&
                  refObj["precision"].IsInt()) {
                _8DF0.precision = refObj["precision"].GetInt();
              }
            }
            if (v.HasMember("8DF1") && v["8DF1"].IsObject()) {
              const rapidjson::Value &refObj = v["8DF1"];
              if (refObj.HasMember("rangeMin") && refObj["rangeMin"].IsInt()) {
                _8DF1.rangeMin = refObj["rangeMin"].GetInt();
              }
              if (refObj.HasMember("rangeMax") && refObj["rangeMax"].IsInt()) {
                _8DF1.rangeMax = refObj["rangeMax"].GetInt();
              }
              if (refObj.HasMember("precision") &&
                  refObj["precision"].IsInt()) {
                _8DF1.precision = refObj["precision"].GetInt();
              }
            }
            if (v.HasMember("8DF2") && v["8DF2"].IsObject()) {
              const rapidjson::Value &refObj = v["8DF2"];
              if (refObj.HasMember("rangeMin") && refObj["rangeMin"].IsInt()) {
                _8DF2.rangeMin = refObj["rangeMin"].GetInt();
              }
              if (refObj.HasMember("rangeMax") && refObj["rangeMax"].IsInt()) {
                _8DF2.rangeMax = refObj["rangeMax"].GetInt();
              }
              if (refObj.HasMember("precision") &&
                  refObj["precision"].IsInt()) {
                _8DF2.precision = refObj["precision"].GetInt();
              }
            }
            if (v.HasMember("8DF3") && v["8DF3"].IsObject()) {
              const rapidjson::Value &refObj = v["8DF3"];
              if (refObj.HasMember("rangeMin") && refObj["rangeMin"].IsInt()) {
                _8DF3.rangeMin = refObj["rangeMin"].GetInt();
              }
              if (refObj.HasMember("rangeMax") && refObj["rangeMax"].IsInt()) {
                _8DF3.rangeMax = refObj["rangeMax"].GetInt();
              }
              if (refObj.HasMember("precision") &&
                  refObj["precision"].IsInt()) {
                _8DF3.precision = refObj["precision"].GetInt();
              }
            }
            if (v.HasMember("8DF4") && v["8DF4"].IsObject()) {
              const rapidjson::Value &refObj = v["8DF4"];
              if (refObj.HasMember("rangeMin") && refObj["rangeMin"].IsInt()) {
                _8DF4.rangeMin = refObj["rangeMin"].GetInt();
              }
              if (refObj.HasMember("rangeMax") && refObj["rangeMax"].IsInt()) {
                _8DF4.rangeMax = refObj["rangeMax"].GetInt();
              }
              if (refObj.HasMember("precision") &&
                  refObj["precision"].IsInt()) {
                _8DF4.precision = refObj["precision"].GetInt();
              }
            }
            if (v.HasMember("8DF5") && v["8DF5"].IsObject()) {
              const rapidjson::Value &refObj = v["8DF5"];
              if (refObj.HasMember("rangeMin") && refObj["rangeMin"].IsInt()) {
                _8DF5.rangeMin = refObj["rangeMin"].GetInt();
              }
              if (refObj.HasMember("rangeMax") && refObj["rangeMax"].IsInt()) {
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
    struct GetParameter {
      inline GetParameter();
      inline ~GetParameter();

      std::map<int, std::string> source;
      void operator<<(const rapidjson::Value &value) {
        do {
          if (!value.IsObject())
            break;
          for (auto it = value.MemberBegin(); it != value.MemberEnd(); ++it) {
            if (!it->name.IsString())
              break;
            if (!it->value.IsString())
              break;
            int key = strtol(it->name.GetString(), nullptr, 10);
            source.emplace(key, it->value.GetString());
          }
        } while (0);
      }
    };
    inline Webgl();
    inline ~Webgl();

    struct Device {
      inline Device();
      inline ~Device();
      ShaderPrecisionFormat shaderPrecisionFormat;
      ContextAttributes contextAttributes;
      GetParameter getParameter;
      void operator<<(const rapidjson::Value &value) {
        do {
          if (!value.IsObject())
            break;
          if (value.HasMember("shaderPrecisionFormat") &&
              value["shaderPrecisionFormat"].IsObject()) {
            shaderPrecisionFormat << value["shaderPrecisionFormat"];
          }
          if (value.HasMember("contextAttributes") &&
              value["contextAttributes"].IsObject()) {
            contextAttributes << value["contextAttributes"];
          }
          if (value.HasMember("getParameter") &&
              value["getParameter"].IsObject()) {
            getParameter << value["getParameter"];
          }
        } while (0);
      }
    };

    std::map<int /*key*/, std::vector<Device>> devices;

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
          std::vector<Device> vs;
          for (auto v = it->value.Begin(); v != it->value.End(); ++v) {
            if (!v->IsObject())
              break;
            Device device;
            device << *v;
            vs.emplace_back(device);
          }
          devices.emplace(key, std::move(vs));
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
      struct Dpi {
        inline Dpi();
        inline ~Dpi();
        int x = 96;
        int y = 96;
      };
      inline Info();
      inline ~Info();
      int height = 0;
      int width = 0;
      int colorDepth = 0;
      int pixelDepth = 0;
      int availLeft = 0;
      int availTop = 0;
      int availHeight = 0;
      int availWidth = 0;
      Dpi dpi;
      double devicePixelRatio = 1.0f;
      void operator<<(const rapidjson::Value &value) {
        do {
          if (!value.IsObject())
            break;
          if (value.HasMember("colorDepth") && value["colorDepth"].IsInt())
            colorDepth = value["colorDepth"].GetInt();
          if (value.HasMember("pixelDepth") && value["pixelDepth"].IsInt())
            pixelDepth = value["pixelDepth"].GetInt();
          if (value.HasMember("height") && value["height"].IsInt()) {
            height = value["height"].GetInt();
          }
          if (value.HasMember("width") && value["width"].IsInt()) {
            width = value["width"].GetInt();
          }
          if (value.HasMember("availLeft") && value["availLeft"].IsInt()) {
            availLeft = value["availLeft"].GetInt();
          }
          if (value.HasMember("availTop") && value["availTop"].IsInt()) {
            availTop = value["availTop"].GetInt();
          }
          if (value.HasMember("availHeight") && value["availHeight"].IsInt()) {
            availHeight = value["availHeight"].GetInt();
          }
          if (value.HasMember("availTop") && value["availTop"].IsInt()) {
            availTop = value["availTop"].GetInt();
          }
          if (value.HasMember("availHeight") && value["availHeight"].IsInt()) {
            availHeight = value["availHeight"].GetInt();
          }
          if (value.HasMember("availWidth") && value["availWidth"].IsInt()) {
            availWidth = value["availWidth"].GetInt();
          }
          if (value.HasMember("devicePixelRatio") &&
              value["devicePixelRatio"].IsDouble()) {
            devicePixelRatio = value["devicePixelRatio"].GetDouble();
          }
          if (value.HasMember("availWidth") && value["availWidth"].IsInt()) {
            availWidth = value["availWidth"].GetInt();
          }
          if (value.HasMember("devicePixelRatio") &&
              value["devicePixelRatio"].IsInt()) {
            devicePixelRatio = value["devicePixelRatio"].GetInt() * 1.0f;
          }
          if (value.HasMember("dpi") && value["dpi"].IsObject()) {
            if (value["dpi"].HasMember("x") && value["dpi"]["x"].IsInt()) {
              dpi.x = value["dpi"]["x"].GetInt();
            }
            if (value["dpi"].HasMember("y") && value["dpi"]["y"].IsInt()) {
              dpi.y = value["dpi"]["y"].GetInt();
            }
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
inline IFpsdb::Webgl::Device::Device() = default;
inline IFpsdb::Webgl::Device::~Device() = default;
inline IFpsdb::Webgl::GetParameter::GetParameter() = default;
inline IFpsdb::Webgl::GetParameter::~GetParameter() = default;
inline IFpsdb::Webgl::ContextAttributes::ContextAttributes() = default;
inline IFpsdb::Webgl::ContextAttributes::~ContextAttributes() = default;
inline IFpsdb::Webgl::ShaderPrecisionFormat::ShaderPrecisionFormat() = default;
inline IFpsdb::Webgl::ShaderPrecisionFormat::~ShaderPrecisionFormat() = default;
inline IFpsdb::Webgl::ShaderPrecisionFormat::_8DF_::_8DF_() = default;
inline IFpsdb::Webgl::ShaderPrecisionFormat::_8DF_::~_8DF_() = default;
inline IFpsdb::Webgl::ShaderPrecisionFormat::_8B30_::_8B30_() = default;
inline IFpsdb::Webgl::ShaderPrecisionFormat::_8B30_::~_8B30_() = default;
inline IFpsdb::Webgl::ShaderPrecisionFormat::_8B31_::_8B31_() = default;
inline IFpsdb::Webgl::ShaderPrecisionFormat::_8B31_::~_8B31_() = default;
inline IFpsdb::Voice::Voice() = default;
inline IFpsdb::Voice::~Voice() = default;
inline IFpsdb::Font::Font() = default;
inline IFpsdb::Font::~Font() = default;
inline IFpsdb::Screen::Screen() = default;
inline IFpsdb::Screen::~Screen() = default;
inline IFpsdb::Screen::Info::Info() = default;
inline IFpsdb::Screen::Info::~Info() = default;
inline IFpsdb::Screen::Info::Dpi::Dpi() = default;
inline IFpsdb::Screen::Info::Dpi::~Dpi() = default;
inline IFpsdb::Hash::Hash() = default;
inline IFpsdb::Hash::~Hash() = default;
} // namespace xsiumio
} // namespace chromium

/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 28 Jul 2025 11:12:06 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__91A7BCE8_86A7_49F2_8FE9_EF591734E9DD__