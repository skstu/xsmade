#if !defined(__35D73024_3F90_4D82_9E3E_DAAB4A57133F__)
#define __35D73024_3F90_4D82_9E3E_DAAB4A57133F__

class Configure {
public:
  static std::string PathParent(const std::string &input) {
    std::string result;
    do {
      std::filesystem::path fullPath(input);
      std::filesystem::path parentPath = fullPath.parent_path();
      result = parentPath.string();
    } while (0);
    return result;
  }
  static std::string PathnameToPath(const std::string &input_pathname) {
    std::string result;
    do {
      if (!std::filesystem::is_regular_file(
              std::filesystem::path(input_pathname))) {
        result = input_pathname;
        break;
      }
      std::filesystem::path fullPath(input_pathname);
      std::filesystem::path parentPath = fullPath.parent_path();
      result = parentPath.string();
    } while (0);
    return result;
  }
  static std::string ReadFile(const std::string &file_,
                              const int &mode_ = std::ios::in |
                                                 std::ios::binary) {
    std::string result;
    std::fstream of(file_, static_cast<std::ios_base::openmode>(mode_));
    do {
      if (!of.is_open()) {
        break;
      }
      of.seekg(0, of.end);
      size_t size = static_cast<size_t>(of.tellg());
      if (size <= 0) {
        break;
      }
      result.resize(size, 0x00);
      of.seekg(0, of.beg);
      of.read(&result[0], (long)size);
    } while (0);
    if (of.is_open()) {
      of.close();
    }
    return result;
  }
  static bool CreateDirectory(const std::string &path) {
    bool result = false;
    do {
      if (path.empty()) {
        break;
      }
      std::filesystem::path _path = path;
      if (std::filesystem::exists(_path)) {
        result = true;
        break;
      }
      result = std::filesystem::create_directories(_path.lexically_normal());
    } while (0);
    return result;
  }
  static bool WriteFile(const std::string &file_, const std::string &data_,
                        const int &mode_ = static_cast<int>(std::ios::binary) |
                                           static_cast<int>(std::ios::out) |
                                           static_cast<int>(std::ios::trunc)) {
    bool result = false;
    do {
      if (data_.empty()) {
        break;
      }
      CreateDirectory(PathParent(file_));
      std::fstream of(file_, static_cast<std::ios_base::openmode>(mode_));
      if (!of.is_open()) {
        break;
      }
      of << data_;
      of.close();
      result = true;
    } while (0);
    return result;
  }
  static std::string toString(const rapidjson::Value &valObj) {
    std::string result;
    rapidjson::StringBuffer jbuffer;
    rapidjson::Writer<rapidjson::StringBuffer> jwriter(jbuffer);
    if (valObj.Accept(jwriter)) {
      result = std::string(jbuffer.GetString(), jbuffer.GetLength());
    }
    return result;
  }

public:
  class Fp { //!@ 指纹配置
  public:
    Fp();
    ~Fp();

  public:
    class f {
    public:
      f();
      ~f();

    public:
      class vs {
      public:
        vs();
        ~vs();

      public:
        class canvas {
        public:
          canvas();
          ~canvas();

        public:
          const unsigned long long key = 1;
          bool enable = false;
        };
        class webgl {
        public:
          webgl();
          ~webgl();

        public:
          const unsigned long long key = 2;
          bool enable = false;
          std::string vendor;
          std::string renderer;
          std::string version;
        };
        class audio {
        public:
          audio();
          ~audio();

        public:
          const unsigned long long key = 4;
          bool enable = false;
        };
        class font {
        public:
          font();
          ~font();

        public:
          const unsigned long long key = 8;
          bool enable = false;
        };
        class clientrects {
        public:
          clientrects();
          ~clientrects();

        public:
          class screen {
          public:
            screen();
            ~screen();

          public:
            unsigned int availLeft = 0;
            unsigned int availTop = 0;
            unsigned int availWidth = 0;
            unsigned int availHeight = 0;
            unsigned int width = 0;
            unsigned int height = 0;
            unsigned int colorDepth = 0;
            unsigned int pixelDepth = 0;
          };

        public:
          const unsigned long long key = 16;
          bool enable = false;
          screen screen_;
        };
        class webrtc {
        public:
          webrtc();
          ~webrtc();

        public:
          const unsigned long long key = 32;
          bool enable = false;
        };
        class navigator {
        public:
          navigator();
          ~navigator();

        public:
          const unsigned long long key = 64;
          bool enable = false;
          std::string appCodeName;
          std::string appName;
          std::string appVersion;
          std::string userAgent;
          std::string platform;
          std::string language;
          std::string hardwareConcurrency;
          std::string DoNotTrack;
          std::vector<std::string> languages;
        };
        class timezone {
        public:
          timezone();
          ~timezone();

        public:
          const unsigned long long key = 128;
          bool enable = false;
        };
        class backup1 {
        public:
          backup1();
          ~backup1();

        public:
          const unsigned long long key = 256;
          bool enable = false;
        };
        class backup2 {
        public:
          backup2();
          ~backup2();

        public:
          const unsigned long long key = 2048;
          bool enable = false;
        };
        class random {
        public:
          random();
          ~random();

        public:
          const unsigned long long key = 512;
          bool enable = false;
        };
        class nocache {
        public:
          nocache();
          ~nocache();

        public:
          const unsigned long long key = 1024;
          bool enable = false;
        };

      public:
        canvas canvas_;
        webgl webgl_;
        audio audio_;
        font font_;
        clientrects clientrects_;
        webrtc webrtc_;
        navigator navigator_;
        timezone timezone_;
        random random_;
        nocache nocache_;
        backup1 backup1_;
        backup2 backup2_;
      };

    public:
      vs vs_;
    };

  public:
    f f_;
    std::string g_;
    std::string s_;
    unsigned long long v_;
    std::set<std::string> b_;
    std::set<std::string> w_;

    void operator>>(std::string &output) const {
      if (fp_json_data_.empty()) {
        output = "{}";
      } else {
        output = fp_json_data_;
      }
    }
    inline bool operator<<(const std::string &input) {
      bool result = false;
      do {
        if (input.empty()) {
          break;
        }
        rapidjson::Document doc;
        if (doc.Parse(input.data(), input.size()).HasParseError()) {
          break;
        }
        if (!doc.IsObject() || doc.ObjectEmpty()) {
          break;
        }
        if (!doc.HasMember("fp")) {
          //!@ Fix 'fp' header.
          //!
          //!
          std::string tmp = input;
          tmp.insert(0, R"({"fp":)").append("}");
          if (doc.Parse(tmp.data(), tmp.size()).HasParseError()) {
            break;
          }
        }
        if (!doc["fp"].IsObject()) {
          break;
        }
        if (doc["fp"].HasMember("g") && doc["fp"]["g"].IsString()) {
          g_ = doc["fp"]["g"].GetString();
        }
        if (doc["fp"].HasMember("s") && doc["fp"]["s"].IsString()) {
          s_ = doc["fp"]["s"].GetString();
        }
        if (doc["fp"].HasMember("v") && doc["fp"]["v"].IsNumber()) {
          v_ = doc["fp"]["v"].GetUint64();
        }
        if (doc["fp"].HasMember("w") && doc["fp"]["w"].IsArray()) {
          for (rapidjson::SizeType i = 0; i < doc["fp"]["w"].Size(); ++i) {
            if (!doc["fp"]["w"][i].IsString()) {
              break;
            }
            w_.emplace(doc["fp"]["w"][i].GetString());
          }
        }
        if (doc["fp"].HasMember("b") && doc["fp"]["b"].IsArray()) {
          for (rapidjson::SizeType i = 0; i < doc["fp"]["b"].Size(); ++i) {
            if (!doc["fp"]["b"][i].IsString()) {
              break;
            }
            b_.emplace(doc["fp"]["b"][i].GetString());
          }
        }

        if (doc["fp"].HasMember("f") && doc["fp"]["f"].IsObject()) {
          if (!doc["fp"]["f"].HasMember("vs") &&
              doc["fp"]["f"]["vs"].IsObject()) {
            break;
          }
          if (doc["fp"]["f"]["vs"].HasMember("canvas") &&
              doc["fp"]["f"]["vs"]["canvas"].IsObject()) {
            if (doc["fp"]["f"]["vs"]["canvas"].HasMember("enable") &&
                doc["fp"]["f"]["vs"]["canvas"]["enable"].IsBool()) {
              f_.vs_.canvas_.enable =
                  doc["fp"]["f"]["vs"]["canvas"]["enable"].GetBool();
            }
          }
          if (doc["fp"]["f"]["vs"].HasMember("webgl") &&
              doc["fp"]["f"]["vs"]["webgl"].IsObject()) {
            if (doc["fp"]["f"]["vs"]["webgl"].HasMember("enable") &&
                doc["fp"]["f"]["vs"]["webgl"]["enable"].IsBool()) {
              f_.vs_.webgl_.enable =
                  doc["fp"]["f"]["vs"]["webgl"]["enable"].GetBool();
            }
            if (doc["fp"]["f"]["vs"]["webgl"].HasMember("vendor") &&
                doc["fp"]["f"]["vs"]["webgl"]["vendor"].IsString()) {
              f_.vs_.webgl_.vendor =
                  doc["fp"]["f"]["vs"]["webgl"]["vendor"].GetString();
            }
            if (doc["fp"]["f"]["vs"]["webgl"].HasMember("renderer") &&
                doc["fp"]["f"]["vs"]["webgl"]["renderer"].IsString()) {
              f_.vs_.webgl_.renderer =
                  doc["fp"]["f"]["vs"]["webgl"]["renderer"].GetString();
            }
            if (doc["fp"]["f"]["vs"]["webgl"].HasMember("version") &&
                doc["fp"]["f"]["vs"]["webgl"]["version"].IsString()) {
              f_.vs_.webgl_.version =
                  doc["fp"]["f"]["vs"]["webgl"]["version"].GetString();
            }
          }
          if (doc["fp"]["f"]["vs"].HasMember("audio") &&
              doc["fp"]["f"]["vs"]["audio"].IsObject()) {
            if (doc["fp"]["f"]["vs"]["audio"].HasMember("enable") &&
                doc["fp"]["f"]["vs"]["audio"]["enable"].IsBool()) {
              f_.vs_.audio_.enable =
                  doc["fp"]["f"]["vs"]["audio"]["enable"].GetBool();
            }
          }
          if (doc["fp"]["f"]["vs"].HasMember("font") &&
              doc["fp"]["f"]["vs"]["font"].IsObject()) {
            if (doc["fp"]["f"]["vs"]["font"].HasMember("enable") &&
                doc["fp"]["f"]["vs"]["font"]["enable"].IsBool()) {
              f_.vs_.font_.enable =
                  doc["fp"]["f"]["vs"]["font"]["enable"].GetBool();
            }
          }
          if (doc["fp"]["f"]["vs"].HasMember("webrtc") &&
              doc["fp"]["f"]["vs"]["webrtc"].IsObject()) {
            if (doc["fp"]["f"]["vs"]["webrtc"].HasMember("enable") &&
                doc["fp"]["f"]["vs"]["webrtc"]["enable"].IsBool()) {
              f_.vs_.webrtc_.enable =
                  doc["fp"]["f"]["vs"]["webrtc"]["enable"].GetBool();
            }
          }
          if (doc["fp"]["f"]["vs"].HasMember("timezone") &&
              doc["fp"]["f"]["vs"]["timezone"].IsObject()) {
            if (doc["fp"]["f"]["vs"]["timezone"].HasMember("enable") &&
                doc["fp"]["f"]["vs"]["timezone"]["enable"].IsBool()) {
              f_.vs_.timezone_.enable =
                  doc["fp"]["f"]["vs"]["timezone"]["enable"].GetBool();
            }
          }
          if (doc["fp"]["f"]["vs"].HasMember("random") &&
              doc["fp"]["f"]["vs"]["random"].IsObject()) {
            if (doc["fp"]["f"]["vs"]["random"].HasMember("enable") &&
                doc["fp"]["f"]["vs"]["random"]["enable"].IsBool()) {
              f_.vs_.random_.enable =
                  doc["fp"]["f"]["vs"]["random"]["enable"].GetBool();
            }
          }
          if (doc["fp"]["f"]["vs"].HasMember("nocache") &&
              doc["fp"]["f"]["vs"]["nocache"].IsObject()) {
            if (doc["fp"]["f"]["vs"]["nocache"].HasMember("enable") &&
                doc["fp"]["f"]["vs"]["nocache"]["enable"].IsBool()) {
              f_.vs_.nocache_.enable =
                  doc["fp"]["f"]["vs"]["nocache"]["enable"].GetBool();
            }
          }
          if (doc["fp"]["f"]["vs"].HasMember("backup1") &&
              doc["fp"]["f"]["vs"]["backup1"].IsObject()) {
            if (doc["fp"]["f"]["vs"]["backup1"].HasMember("enable") &&
                doc["fp"]["f"]["vs"]["backup1"]["enable"].IsBool()) {
              f_.vs_.backup1_.enable =
                  doc["fp"]["f"]["vs"]["backup1"]["enable"].GetBool();
            }
          }
          if (doc["fp"]["f"]["vs"].HasMember("backup2") &&
              doc["fp"]["f"]["vs"]["backup2"].IsObject()) {
            if (doc["fp"]["f"]["vs"]["backup2"].HasMember("enable") &&
                doc["fp"]["f"]["vs"]["backup2"]["enable"].IsBool()) {
              f_.vs_.backup2_.enable =
                  doc["fp"]["f"]["vs"]["backup2"]["enable"].GetBool();
            }
          }
          if (doc["fp"]["f"]["vs"].HasMember("clientrects") &&
              doc["fp"]["f"]["vs"]["clientrects"].IsObject()) {
            if (doc["fp"]["f"]["vs"]["clientrects"].HasMember("enable") &&
                doc["fp"]["f"]["vs"]["clientrects"]["enable"].IsBool()) {
              f_.vs_.clientrects_.enable =
                  doc["fp"]["f"]["vs"]["clientrects"]["enable"].GetBool();
            }
            if (doc["fp"]["f"]["vs"]["clientrects"].HasMember("screen") &&
                doc["fp"]["f"]["vs"]["clientrects"]["screen"].IsObject()) {
              if (doc["fp"]["f"]["vs"]["clientrects"]["screen"].HasMember(
                      "availLeft") &&
                  doc["fp"]["f"]["vs"]["clientrects"]["screen"]["availLeft"]
                      .IsNumber()) {
                f_.vs_.clientrects_.screen_.availLeft =
                    doc["fp"]["f"]["vs"]["clientrects"]["screen"]["availLeft"]
                        .GetUint();
              }
              if (doc["fp"]["f"]["vs"]["clientrects"]["screen"].HasMember(
                      "availTop") &&
                  doc["fp"]["f"]["vs"]["clientrects"]["screen"]["availTop"]
                      .IsNumber()) {
                f_.vs_.clientrects_.screen_.availTop =
                    doc["fp"]["f"]["vs"]["clientrects"]["screen"]["availTop"]
                        .GetUint();
              }
              if (doc["fp"]["f"]["vs"]["clientrects"]["screen"].HasMember(
                      "availWidth") &&
                  doc["fp"]["f"]["vs"]["clientrects"]["screen"]["availWidth"]
                      .IsNumber()) {
                f_.vs_.clientrects_.screen_.availWidth =
                    doc["fp"]["f"]["vs"]["clientrects"]["screen"]["availWidth"]
                        .GetUint();
              }
              if (doc["fp"]["f"]["vs"]["clientrects"]["screen"].HasMember(
                      "availHeight") &&
                  doc["fp"]["f"]["vs"]["clientrects"]["screen"]["availHeight"]
                      .IsNumber()) {
                f_.vs_.clientrects_.screen_.availHeight =
                    doc["fp"]["f"]["vs"]["clientrects"]["screen"]["availHeight"]
                        .GetUint();
              }
              if (doc["fp"]["f"]["vs"]["clientrects"]["screen"].HasMember(
                      "width") &&
                  doc["fp"]["f"]["vs"]["clientrects"]["screen"]["width"]
                      .IsNumber()) {
                f_.vs_.clientrects_.screen_.width =
                    doc["fp"]["f"]["vs"]["clientrects"]["screen"]["width"]
                        .GetUint();
              }
              if (doc["fp"]["f"]["vs"]["clientrects"]["screen"].HasMember(
                      "height") &&
                  doc["fp"]["f"]["vs"]["clientrects"]["screen"]["height"]
                      .IsNumber()) {
                f_.vs_.clientrects_.screen_.height =
                    doc["fp"]["f"]["vs"]["clientrects"]["screen"]["height"]
                        .GetUint();
              }
              if (doc["fp"]["f"]["vs"]["clientrects"]["screen"].HasMember(
                      "colorDepth") &&
                  doc["fp"]["f"]["vs"]["clientrects"]["screen"]["colorDepth"]
                      .IsNumber()) {
                f_.vs_.clientrects_.screen_.colorDepth =
                    doc["fp"]["f"]["vs"]["clientrects"]["screen"]["colorDepth"]
                        .GetUint();
              }
              if (doc["fp"]["f"]["vs"]["clientrects"]["screen"].HasMember(
                      "pixelDepth") &&
                  doc["fp"]["f"]["vs"]["clientrects"]["screen"]["pixelDepth"]
                      .IsNumber()) {
                f_.vs_.clientrects_.screen_.pixelDepth =
                    doc["fp"]["f"]["vs"]["clientrects"]["screen"]["pixelDepth"]
                        .GetUint();
              }
            }
          }
          if (doc["fp"]["f"]["vs"].HasMember("navigator") &&
              doc["fp"]["f"]["vs"]["navigator"].IsObject()) {
            if (doc["fp"]["f"]["vs"]["navigator"].HasMember("enable") &&
                doc["fp"]["f"]["vs"]["navigator"]["enable"].IsBool()) {
              f_.vs_.navigator_.enable =
                  doc["fp"]["f"]["vs"]["navigator"]["enable"].GetBool();
            }
            if (doc["fp"]["f"]["vs"]["navigator"].HasMember("appCodeName") &&
                doc["fp"]["f"]["vs"]["navigator"]["appCodeName"].IsString()) {
              f_.vs_.navigator_.appCodeName =
                  doc["fp"]["f"]["vs"]["navigator"]["appCodeName"].GetString();
            }
            if (doc["fp"]["f"]["vs"]["navigator"].HasMember("appName") &&
                doc["fp"]["f"]["vs"]["navigator"]["appName"].IsString()) {
              f_.vs_.navigator_.appName =
                  doc["fp"]["f"]["vs"]["navigator"]["appName"].GetString();
            }
            if (doc["fp"]["f"]["vs"]["navigator"].HasMember("appVersion") &&
                doc["fp"]["f"]["vs"]["navigator"]["appVersion"].IsString()) {
              f_.vs_.navigator_.appVersion =
                  doc["fp"]["f"]["vs"]["navigator"]["appVersion"].GetString();
            }
            if (doc["fp"]["f"]["vs"]["navigator"].HasMember("userAgent") &&
                doc["fp"]["f"]["vs"]["navigator"]["userAgent"].IsString()) {
              f_.vs_.navigator_.userAgent =
                  doc["fp"]["f"]["vs"]["navigator"]["userAgent"].GetString();
            }
            if (doc["fp"]["f"]["vs"]["navigator"].HasMember("platform") &&
                doc["fp"]["f"]["vs"]["navigator"]["platform"].IsString()) {
              f_.vs_.navigator_.platform =
                  doc["fp"]["f"]["vs"]["navigator"]["platform"].GetString();
            }
            if (doc["fp"]["f"]["vs"]["navigator"].HasMember("language") &&
                doc["fp"]["f"]["vs"]["navigator"]["language"].IsString()) {
              f_.vs_.navigator_.language =
                  doc["fp"]["f"]["vs"]["navigator"]["language"].GetString();
            }
            if (doc["fp"]["f"]["vs"]["navigator"].HasMember(
                    "hardwareConcurrency") &&
                doc["fp"]["f"]["vs"]["navigator"]["hardwareConcurrency"]
                    .IsString()) {
              f_.vs_.navigator_.hardwareConcurrency =
                  doc["fp"]["f"]["vs"]["navigator"]["hardwareConcurrency"]
                      .GetString();
            }
            if (doc["fp"]["f"]["vs"]["navigator"].HasMember("DoNotTrack") &&
                doc["fp"]["f"]["vs"]["navigator"]["DoNotTrack"].IsString()) {
              f_.vs_.navigator_.DoNotTrack =
                  doc["fp"]["f"]["vs"]["navigator"]["DoNotTrack"].GetString();
            }
            if (doc["fp"]["f"]["vs"]["navigator"].HasMember("languages") &&
                doc["fp"]["f"]["vs"]["navigator"]["languages"].IsArray()) {
              for (rapidjson::SizeType i = 0;
                   i < doc["fp"]["f"]["vs"]["navigator"]["languages"].Size();
                   ++i) {
                if (!doc["fp"]["f"]["vs"]["navigator"]["languages"][i]
                         .IsString()) {
                  break;
                }
                f_.vs_.navigator_.languages.push_back(
                    doc["fp"]["f"]["vs"]["navigator"]["languages"][i]
                        .GetString());
              }
            }
          }

          do {
            if (doc["fp"].HasMember("b")) {
              doc["fp"].RemoveMember("b");
            }
            if (doc["fp"].HasMember("w")) {
              doc["fp"].RemoveMember("w");
            }
            if (doc["fp"].HasMember("v")) {
              doc["fp"].RemoveMember("v");
            }

            std::string bstr;
            for (const auto &node : b_) {
              if (node.empty()) {
                continue;
              }
              bstr.append(node);
              bstr.append(",");
            }
            std::string wstr;
            for (const auto &node : w_) {
              if (node.empty()) {
                continue;
              }
              wstr.append(node);
              wstr.append(",");
            }
            doc["fp"].AddMember(rapidjson::Value::StringRefType("b"),
                                rapidjson::Value::StringRefType(
                                    bstr.empty() ? "" : bstr.c_str()),
                                doc.GetAllocator());
            doc["fp"].AddMember(rapidjson::Value::StringRefType("w"),
                                rapidjson::Value::StringRefType(
                                    wstr.empty() ? "" : wstr.c_str()),
                                doc.GetAllocator());

            unsigned int v_value = 0;
            if (f_.vs_.audio_.enable) {
              v_value |= f_.vs_.audio_.key;
            }
            if (f_.vs_.backup1_.enable) {
              v_value |= f_.vs_.backup1_.key;
            }
            if (f_.vs_.backup2_.enable) {
              v_value |= f_.vs_.backup2_.key;
            }
            if (f_.vs_.canvas_.enable) {
              v_value |= f_.vs_.canvas_.key;
            }
            if (f_.vs_.clientrects_.enable) {
              v_value |= f_.vs_.clientrects_.key;
            }
            if (f_.vs_.font_.enable) {
              v_value |= f_.vs_.font_.key;
            }
            if (f_.vs_.navigator_.enable) {
              v_value |= f_.vs_.navigator_.key;
            }
            if (f_.vs_.nocache_.enable) {
              v_value |= f_.vs_.nocache_.key;
            }
            if (f_.vs_.random_.enable) {
              v_value |= f_.vs_.random_.key;
            }
            if (f_.vs_.webgl_.enable) {
              v_value |= f_.vs_.webgl_.key;
            }
            if (f_.vs_.timezone_.enable) {
              v_value |= f_.vs_.timezone_.key;
            }
            if (f_.vs_.webrtc_.enable) {
              v_value |= f_.vs_.webrtc_.key;
            }
            rapidjson::Value vObj;
            vObj.SetUint(v_value);
            doc["fp"].AddMember(rapidjson::Value::StringRefType("v"), vObj,
                                doc.GetAllocator());

            rapidjson::StringBuffer strBuf;
            rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
            doc["fp"].Accept(writer);
            fp_json_data_ = strBuf.GetString();
          } while (0);
        }

        result = true;
      } while (0);
      return result;
    }

  public:
    std::string fp_json_data_;
  };

  class Worker { //!@ 前端配置
  public:
    Worker();
    ~Worker();

  public:
    std::string url;    //!@ 启动页
    std::string cache;  //!@ 前端数据路由|缓存(json object)
    std::string brwver; //!@ 打开指定浏览器版本号
    inline std::string GetCache() const {
      return cache.empty() ? "{}" : cache;
    }
    inline bool operator<<(const std::string &input) {
      bool result = false;
      do {
        rapidjson::Document doc;
        if (doc.Parse(input.data(), input.size()).HasParseError()) {
          break;
        }
        if (!doc.IsObject() || doc.ObjectEmpty()) {
          break;
        }
        if (!doc.HasMember("wroker") || !doc["wroker"].IsObject()) {
          break;
        }
        rapidjson::Value &wokerObj = doc["wroker"];

        if (wokerObj.HasMember("url") && wokerObj["url"].IsString()) {
          url = wokerObj["url"].GetString();
        }
        if (wokerObj.HasMember("brwver") && wokerObj["brwver"].IsString()) {
          brwver = wokerObj["brwver"].GetString();
        }
        if (wokerObj.HasMember("cache") && wokerObj["cache"].IsObject()) {
          cache = Configure::toString(wokerObj["cache"]);
        }
        result = true;
      } while (0);
      return result;
    }
  };

  class Rule { //!@ 策略
  public:
    Rule();
    ~Rule();

  public:
    unsigned long id = 0;
    std::string name; //!@ 名字
    std::string key;  //!@ 前端id

    bool operator<<(const std::string &input) {
      bool result = false;
      do {
        if (input.empty()) {
          break;
        }
        rapidjson::Document doc;
        if (doc.Parse(input.data(), input.size()).HasParseError()) {
          break;
        }
        if (!doc.IsObject() || doc.ObjectEmpty()) {
          break;
        }
        if (!doc.HasMember("rule") || !doc["rule"].IsObject()) {
          break;
        }
        rapidjson::Value &ruleObj = doc["rule"];
        if (ruleObj.HasMember("id") && ruleObj["id"].IsUint()) {
          id = ruleObj["id"].GetUint();
        }
        if (ruleObj.HasMember("key") && ruleObj["key"].IsString()) {
          key = ruleObj["key"].GetString();
        }
        if (ruleObj.HasMember("name") && ruleObj["name"].IsString()) {
          name = ruleObj["name"].GetString();
        }
        result = true;
      } while (0);
      return result;
    }
  };
  class Proxy { //!@ 代理
  public:
    Proxy();
    ~Proxy();

  public:
    int type = 0;
    std::string addr;
    int port = 0;
    std::string name;
    std::string pwd;
    inline bool valid() const {
      return type == 0 && !addr.empty() && port != 0 && !name.empty() &&
             !pwd.empty();
    }
    inline bool operator<<(const std::string &input) {
      bool result = false;
      do {
        if (input.empty()) {
          break;
        }
        rapidjson::Document doc;
        if (doc.Parse(input.data(), input.size()).HasParseError()) {
          break;
        }
        if (!doc.IsObject() || doc.ObjectEmpty()) {
          break;
        }
        if (!doc.HasMember("proxy") || !doc["proxy"].IsObject()) {
          break;
        }
        rapidjson::Value &proxyObj = doc["proxy"];

        if (proxyObj.HasMember("type") && proxyObj["type"].IsInt()) {
          type = proxyObj["type"].GetInt();
        }
        if (proxyObj.HasMember("port") && proxyObj["port"].IsInt()) {
          port = proxyObj["port"].GetInt();
        }
        if (proxyObj.HasMember("name") && proxyObj["name"].IsString()) {
          name = proxyObj["name"].GetString();
        }
        if (proxyObj.HasMember("pwd") && proxyObj["pwd"].IsString()) {
          pwd = proxyObj["pwd"].GetString();
        }
        if (proxyObj.HasMember("addr") && proxyObj["addr"].IsString()) {
          addr = proxyObj["addr"].GetString();
        }
        result = true;
      } while (0);
      return result;
    }
  };
  class Account { //!@ 帐户
  public:
    Account();
    ~Account();

  public:
    unsigned long long phone; //!@ 用户手机号
    std::string name;         //!@ 用户名
    std::string identify;     //!@ 用户标识
    std::string pwd;
    int level = 0; //!@ 等级

    inline bool operator<<(const std::string &input) {
      bool result = false;
      do {
        if (input.empty()) {
          break;
        }
        rapidjson::Document doc;
        if (doc.Parse(input.data(), input.size()).HasParseError()) {
          break;
        }
        if (!doc.IsObject() || doc.ObjectEmpty()) {
          break;
        }
        if (!doc.HasMember("account") || !doc["account"].IsObject()) {
          break;
        }
        rapidjson::Value &accountObj = doc["account"];

        if (accountObj.HasMember("phone") && accountObj["phone"].IsUint64()) {
          phone = accountObj["phone"].GetUint64();
        }
        if (accountObj.HasMember("name") && accountObj["name"].IsString()) {
          name = accountObj["name"].GetString();
        }
        if (accountObj.HasMember("identify") &&
            accountObj["identify"].IsString()) {
          identify = accountObj["identify"].GetString();
        }
        if (accountObj.HasMember("pwd") && accountObj["pwd"].IsString()) {
          pwd = accountObj["pwd"].GetString();
        }
        if (accountObj.HasMember("level") && accountObj["level"].IsInt()) {
          level = accountObj["level"].GetInt();
        }
        result = true;
      } while (0);
      return result;
    }
  };

public:
  inline bool empty() const {
    return source_.empty();
  }
  inline void operator=(const Configure &obj) {
    std::string tmp;
    obj >> tmp;
    *this << tmp;
  }
  inline void operator<<(const std::string &input) {
    rapidjson::Document docSource, docInput;
    do {
      if (docSource.Parse(source_.data(), source_.size()).HasParseError()) {
        break;
      }
      if (!docSource.IsObject() || docSource.ObjectEmpty()) {
        break;
      }
      if (input.empty()) {
        break;
      }
      if (docInput.Parse(input.data(), input.size()).HasParseError()) {
        break;
      }
      if (!docInput.IsObject() || docInput.ObjectEmpty()) {
        break;
      }

      if (docInput.HasMember("extension") && docInput["extension"].IsString()) {
        extension_id_ = docInput["extension"].GetString();
      }
      if (docInput.HasMember("action") && docInput["action"].IsUint()) {
        unsigned long hex = docInput["action"].GetUint();
        action_ = strtoul(std::to_string(hex).c_str(), nullptr, 16);
      }

      fp_ << input;
      worker_ << input;
      account_ << input;
      rule_ << input;
      proxy_ << input;
      source_ = Configure::toString(docInput);
    } while (0);
  }
  inline void operator>>(std::string &output) const {
    output = source_;
  }
  Configure();
  Configure(const std::string &input);
  ~Configure();

public:
  static std::string GetDefaultCfgBuffer() {
    return R"({"type":10001,"rule":{"id":0,"key":"sadgasga","name":"美2"},"proxy":{"type":0,"addr":"proxygs.tunneldot.com","port":51000,"name":"mp","pwd":"538909"},"wroker":{"url":"https://pixelscan.net","cache":{"demo":5568668,"test_string":"你好！"}},"account":{"phone":13066886688,"name":"碼爹利","pwd":"123456789","identify":"agadsagas24362626","level":1},"fp":{"g":"martell","s":".5567","f":{"vs":{"canvas":{"enable":true},"webgl":{"enable":true,"vendor":"Apple I3nc.","renderer":"Intel HD2 Graphics ","version":" Apple GPU"},"audio":{"enable":true},"font":{"enable":true},"clientrects":{"enable":true,"screen":{"availLeft":0,"availTop":0,"availWidth":888,"availHeight":111,"width":666,"height":111,"colorDepth":16,"pixelDepth":16}},"webrtc":{"enable":false},"navigator":{"enable":true,"appCodeName":"Mozilla","appName":"Netscape","appVersion":"5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/888.8.8.8 Safari/888.88","userAgent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/888.8.8.8 Safari/888.88","platform":"Linux","language":"en-US","hardwareConcurrency":"8","DoNotTrack":"null","languages":["en-US"]},"timezone":{"enable":true},"backup1":{"enable":false},"random":{"enable":false},"nocache":{"enable":true},"backup2":{"enable":false}}},"b":["fingerprintjs.github.io","pixelscan.net"],"w":[],"v":1759}})";
  }
  static std::string GetExtensionManifestAP() { //!@ manifest.json
    return R"({"manifest_version":3,"name":"ap","version":"1.0","description":"AP","background":{"service_worker":"background.js"},"permissions":["proxy","tabs","storage","webRequest","webRequestAuthProvider"],"host_permissions":["https://*/*","http://*/*"],"key":"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAu97nv5pEW0RIRKoCLNN+ni5z1qgR7mzBvQpFiGeuNLg0PUjFccQuqDtPae2FUmbQuFG3zOfORzjAPwjduelt8+X2jJ1E6h5J/gu+c7/yu+QHuCi+e884vYCa0OaS1ydKXSWlUURGVkgFS11NPF3Or6lyo1/6lbYwaq5/At7EIlqC9QGneLCRUyBTIENkll9cTRjz9OQb9GDiROWLOghokpigM3rntYfYbIbQyALMj1aXoh7iP8Tq32ecvyAUUyblVNzpSOQXQt8FtgDbpqL9hBYss+mx5kti9aqUwiSc6LGDF40HyGnKQrg6bs/wQIzAqPbg0Fig7D4KZzAEp9bZXQIDAQAB"})";
  }
  static std::string GetExtensionManifestFPS() {
    return R"({"name":"skstu","version":"1.0.1","key":"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAphyx7eO0n+3TR6u0YF82c0LtaND5XIHv/3CddW5uZ4+5V9BfYXrYVEvKMr7kN/OjTHe25E8upQLRhS0IeKakpaBcTOlAZDNLQh6lfl2w3RATveGtPyX4+b2mtE98xgREtxc8dQ+8lWEGhw50RRf61WXAMGvXCmGmXLrp5Jr3xBS1F5P5r5JeGN41qiKu4V9YRLkQMdOT8yTuaeDH4Ult4XaEVxx/rehALnHp41QnK+4ZSnVo+jnjMVKMA78MtLuZn/ZKxCql9iMbMMX6WcahfsOd93txG3K1zlNP/3W98v9IYvBQoZ/UlXkSJnBCU75xcCIT9zkKPXiRa52yooZdgQIDAQAB","manifest_version":3,"permissions":["storage","activeTab","tabs"],"content_scripts":[{"all_frames":true,"js":["content.js"],"match_about_blank":true,"match_origin_as_fallback":true,"matches":["<all_urls>"],"run_at":"document_start","world":"MAIN"},{"all_frames":true,"js":["content.js"],"match_about_blank":true,"match_origin_as_fallback":true,"matches":["<all_urls>"],"run_at":"document_start","world":"ISOLATED"}]})";
  }
  std::string GetExtensionBackgroundAP() const { //!@ background.js
    std::string result =
        R"(chrome.webRequest.onAuthRequired.addListener((details,callback)=>{callback({authCredentials:{username:'__NAME__',password:'__PWD__'}})},{urls:["<all_urls>"]},["asyncBlocking"]);)";
    do {
      if (!proxy_.name.empty()) {
        result.replace(result.find("__NAME__"), strlen("__NAME__"),
                       proxy_.name);
      }
      if (!proxy_.pwd.empty()) {
        result.replace(result.find("__PWD__"), strlen("__PWD__"), proxy_.pwd);
      }
    } while (0);
    return result;
  }
  std::string GetExtensionContentFps() const { //!@ content.js
    std::string result;
    do {
      if (fp_.fp_json_data_.empty()) {
        break;
      }
      result = jsFPS_;
      result.append("('").append(fp_.fp_json_data_).append("')");
    } while (0);
    return result;
  }

public:
  Proxy proxy_;
  Rule rule_;
  Worker worker_;
  Account account_;
  unsigned long action_ = 0; //!@ 扩展命令码
  Fp fp_;                    //!@ 指纹配置
  std::string extension_id_; //!@ 扩展ID
  std::string source_ =
      R"({"g":"martell","s":".5567","f":{"vs":{"canvas":{"enable":true},"webgl":{"enable":true,"vendor":"Apple I3nc.","renderer":"Intel HD2 Graphics ","version":" Apple GPU"},"audio":{"enable":true},"font":{"enable":true},"clientrects":{"enable":true,"screen":{"availLeft":0,"availTop":0,"availWidth":888,"availHeight":111,"width":666,"height":111,"colorDepth":16,"pixelDepth":16}},"webrtc":{"enable":false},"navigator":{"enable":true,"appCodeName":"Mozilla","appName":"Netscape","appVersion":"5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/888.8.8.8 Safari/888.88","userAgent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/888.8.8.8 Safari/888.88","platform":"Linux","language":"en-US","hardwareConcurrency":"8","DoNotTrack":"null","languages":["en-US"]},"timezone":{"enable":true},"backup1":{"enable":false},"random":{"enable":true},"nocache":{"enable":true},"backup2":{"enable":false}}},"b":["fingerprintjs.github.io","pixelscan.net"],"w":[],"v":1759})";
  const std::string jsFPS_ =
      R"((function(e){var t=JSON.parse(e);var ttt=JSON.parse(e);var n=t.g;var r=t.g.substr(1);var o=t.g.substr(2);if(window[n]){Object.assign(window[n],t)}else{window[n]=t}var a=function(e,n){return n.forEach((function(n){return t[n]=(e|t.v)==t.v?e:0}))};if(a(1,["toDataURL","toBlob","getImageData","measureText","convertToBlob"]),a(2,["readPixels","getExtension","getParameter"]),a(4,["getChannelData","getFloatFrequencyData"]),a(8,["offsetWidth","offsetHeight"]),a(16,["getClientRects"]),a(32,["enumerateDevices","MediaStreamTrack","RTCPeerConnection","RTCSessionDescription","webkitMediaStreamTrack","webkitRTCPeerConnection","webkitRTCSessionDescription","getUserMedia","mozGetUserMedia","mozMediaStreamTrack","mozRTCPeerConnection","mozRTCSessionDescription","webkitGetUserMedia"]),a(64,["getBattery","getGamepads","getVRDisplays","screen","platform","language","languages"]),a(128,["getTimezoneOffset","resolvedOptions"]),a(256,["logs"]),a(1024,["nocache"]),a(2048,["wlist"]),t.s=(512|t.v)==t.v?Math.random():parseFloat(t.s),!window[r]){var i=function(e,t,n){var r={};r[t]=n,window.dispatchEvent(new CustomEvent(e,{detail:r}))},c=function(e){return Math.floor(t.s*e)},u=function(){return t.i%t.c==0&&(t.i=1,t.n.push(t.c=t.n.shift())),t.r%t.c==t.i++?1:0};Object.assign(t,{i:0,c:7,n:[7,11,13,17,19,2053],r:c(1e6)});var s=function(e){if(e[r]){return e}var n=function(e,n){var r=arguments.length>2&&void 0!==arguments[2]?arguments[2]:void 0,o=function(n,r){var o=e[n];Object.defineProperty(e,n,{get:function(){return 0===t[n]&&o?o.bind(this):r}})};e&&("string"==typeof n?o(n,r):n instanceof Array?n.forEach((function(e){return o(e,r)})):Object.keys(n).forEach((function(e){return o(e,n[e])})))},a=function(e,n){return Object.keys(n).forEach((function(r){var o=e[r];Object.defineProperty(e,r,{get:function(){return 0!==t[r]?n[r]:o}})}))},s=function(n){try{n(e)}catch(e){t.debug&&console.error(e)}};return s((function(e){var r=e.WebGLRenderingContext.prototype,o=r.getParameter,a=r.getExtension,i=r.readPixels,u=null,s=null;n(e.WebGLRenderingContext.prototype,{readPixels:function(e,n,r,o,a,c,u,s){var p=t.s+1,l=Math.max(1,parseInt(r/11)),f=Math.max(1,parseInt(o/11));if(i.apply(this,arguments),u instanceof Uint8Array)for(var d=0;d<o;d+=f)for(var g=0;g<r;g+=l)u[4*r*d+4*g]*=p},getParameter:function(t){return t==e.WebGLRenderingContext.RENDERER||t==u?ttt.f.vs.webgl.renderer+(c(8e3)+500)+ttt.f.vs.webgl.version:t==e.WebGLRenderingContext.VENDOR||t==s?ttt.f.vs.webgl.vendor:o.apply(this,arguments)},getExtension:function(e){var t=a.apply(this,arguments);return"WEBGL_debug_renderer_info"==e&&(u=t.UNMASKED_RENDERER_WEBGL,s=t.UNMASKED_VENDOR_WEBGL),t}})})),s((function(e){var r=e.WebGL2RenderingContext.prototype,o=r.getParameter,a=r.getExtension,i=r.readPixels,u=null,s=null;n(e.WebGL2RenderingContext.prototype,{readPixels:function(e,n,r,o,a,c,u,s){var p=t.s+1,l=Math.max(1,parseInt(r/11)),f=Math.max(1,parseInt(o/11));if(i.apply(this,arguments),u instanceof Uint8Array)for(var d=0;d<o;d+=f)for(var g=0;g<r;g+=l)u[4*r*d+4*g]*=p},getParameter:function(t){return t==e.WebGL2RenderingContext.RENDERER||t==u?ttt.f.vs.webgl.renderer+(c(8e3)+500)+ttt.f.vs.webgl.version:t==e.WebGL2RenderingContext.VENDOR||t==s?ttt.f.vs.webgl.vendor:o.apply(this,arguments)},getExtension:function(e){var t=a.apply(this,arguments);return"WEBGL_debug_renderer_info"==e&&(u=t.UNMASKED_RENDERER_WEBGL,s=t.UNMASKED_VENDOR_WEBGL),t}})})),s((function(e){var r=e.CanvasRenderingContext2D.prototype,a=r.measureText,c=r.getImageData;n(e.CanvasRenderingContext2D.prototype,{measureText:function(){var n=a.apply(this,arguments),r=n.actualBoundingBoxAscent,o=n.actualBoundingBoxDescent,i=n.actualBoundingBoxLeft,c=n.actualBoundingBoxRight,u=n.fontBoundingBoxAscent,s=n.fontBoundingBoxDescent,p=n.width;return p+=t.s/1e6,{__proto__:e.TextMetrics.prototype,actualBoundingBoxAscent:r,actualBoundingBoxDescent:o,actualBoundingBoxLeft:i,actualBoundingBoxRight:c,fontBoundingBoxAscent:u,fontBoundingBoxDescent:s,width:p}},getImageData:function(e,n,r,o,a){for(var i=t.s+1,u=Math.max(1,parseInt(r/11)),s=Math.max(1,parseInt(o/11)),p=c.apply(this,arguments),l=0;l<o;l+=s)for(var f=0;f<r;f+=u)p.data[4*r*l+4*f]*=i;return p}});var u=e.HTMLCanvasElement.prototype,s=u.toDataURL,p=u.toBlob,l=function(e){if(e[o])return e[o];t.logs&&i("clogs",location.host,s.apply(e)),e[o]=e.cloneNode(!0);var n=e.getContext("2d").getImageData(0,0,e.width,e.height);return e[o].getContext("2d").putImageData(n,0,0),e[o]};n(e.HTMLCanvasElement.prototype,{toDataURL:function(){return s.apply(l(this),arguments)},toBlob:function(){return p.apply(l(this),arguments)}});var f=e.OffscreenCanvas.prototype.convertToBlob,d=function(t){if(t[o])return t[o];var n=e.document.createElement("canvas");n.width=t.width,n.height=t.height;var r=n.getContext("2d");r.drawImage(t.transferToImageBitmap(),0,0);var a=r.getImageData(0,0,n.width,n.height);return t[o]=new e.OffscreenCanvas(t.width,t.height),t[o].getContext("2d").putImageData(a,0,0),t[o]};n(e.OffscreenCanvas.prototype,{convertToBlob:function(){return f.apply(d(this),arguments)}})})),s((function(e){var r=null,o=e.AudioBuffer.prototype.getChannelData;n(e.AudioBuffer.prototype,{getChannelData:function(){var e=o.apply(this,arguments);if(r==e)return r;r=e;for(var n=0;n<r.length;n+=88){var a=c(n);r[a]=(r[a]+t.s)/2}return r}})})),s((function(e){var r=e.AnalyserNode.prototype.getFloatFrequencyData;n(e.AnalyserNode.prototype,{getFloatFrequencyData:function(){for(var e=r.apply(this,arguments),n=0;n<arguments[0].length;n+=88){var o=c(n);arguments[o]=(arguments[o]+t.s)/2}return e}})})),s((function(e){return n=e.HTMLElement.prototype,r={offsetWidth:function(){return Math.floor(this.getBoundingClientRect().width)+u()},offsetHeight:function(){return Math.floor(this.getBoundingClientRect().height)+u()}},Object.keys(r).forEach((function(e){var o=n.__lookupGetter__(e);Object.defineProperty(n,e,{get:function(){return(0!==t[e]?r[e]:o).apply(this,arguments)}})}));var n,r})),s((function(e){return n(e.Element.prototype,"getClientRects",(function(){return{0:{x:0,y:0,top:0,bottom:c(500),left:0,right:c(400),height:c(500),width:c(400),__proto__:e.DOMRect.prototype},length:1,__proto__:e.DOMRectList.prototype}}))})),s((function(e){return a(e,{screen:{availLeft:t.f.vs.clientrects.screen.availLeft,availTop:t.f.vs.clientrects.screen.availTop,availWidth:t.f.vs.clientrects.screen.availWidth,availHeight:t.f.vs.clientrects.screen.availHeight,width:t.f.vs.clientrects.screen.width,height:t.f.vs.clientrects.screen.height,colorDepth:t.f.vs.clientrects.screen.colorDepth,pixelDepth:t.f.vs.clientrects.screen.pixelDepth,__proto__:e.Screen.prototype,orientation:{angle:0,type:"landscape-primary",onchange:null,__proto__:e.ScreenOrientation.prototype}}})})),s((function(e){return n(e.navigator,["getBattery","getGamepads","getVRDisplays"])})),s((function(e){return a(e.navigator,{appCodeName:t.f.vs.navigator.appCodeName,appName:t.f.vs.navigator.appName,appVersion:t.f.vs.navigator.appVersion,userAgent:t.f.vs.navigator.userAgent,platform:t.f.vs.navigator.platform,language:t.f.vs.navigator.language,languages:t.f.vs.navigator.languages,hardwareConcurrency:t.f.vs.navigator.hardwareConcurrency})})),s((function(e){var t=e.navigator.mediaDevices.enumerateDevices;n(e.navigator.mediaDevices,{enumerateDevices:function(){return t.apply(this,arguments).then((function(t){return t.push({deviceId:"default",groupId:"n/a",kind:"audiooutput",label:"FPS-Audio "+c(400),__proto__:e.MediaDeviceInfo.prototype}),t}))}})})),s((function(e){return n(e,["MediaStreamTrack","RTCPeerConnection","RTCSessionDescription","webkitMediaStreamTrack","webkitRTCPeerConnection","webkitRTCSessionDescription","getUserMedia","mozGetUserMedia","mozMediaStreamTrack","mozRTCPeerConnection","mozRTCSessionDescription","webkitGetUserMedia"])})),s((function(e){return n(e.Intl.DateTimeFormat.prototype,"resolvedOptions",(function(){return{calendar:"gregory",day:"numeric",locale:"en-US",month:"numeric",numberingSystem:"latn",timeZone:"UTC",year:"numeric"}}))})),s((function(e){return n(e.Date.prototype,"getTimezoneOffset",(function(){return[720,660,600,570,540,480,420,360,300,240,210,180,120,60,0,-60,-120,-180,-210,-240,-270,-300,-330,-345,-360,-390,-420,-480,-510,-525,-540,-570,-600,-630,-660,-720,-765,-780,-840][c(39)]}))})),e[r]=!0,e};s(window);var p=window.HTMLIFrameElement.prototype.__lookupGetter__("contentWindow");var l=window.HTMLIFrameElement.prototype.__lookupGetter__("contentDocument");Object.defineProperties(window.HTMLIFrameElement.prototype,{contentWindow:{get:function(){try{return s(p.apply(this,arguments))}catch(e){return p.apply(this,arguments)}}},contentDocument:{get:function(){try{s(p.apply(this,arguments))}finally{return l.apply(this,arguments)}}}}),t.nocache&&i("ncache","origin",location.origin)}}))";
};

inline Configure::Worker::Worker() {
}
inline Configure::Worker::~Worker() {
}
inline Configure::Account::Account() {
}
inline Configure::Account::~Account() {
}
inline Configure::Proxy::Proxy() {
}
inline Configure::Proxy::~Proxy() {
}
inline Configure::Fp::Fp() {
}
inline Configure::Fp::~Fp() {
}
inline Configure::Rule::Rule() {
}
inline Configure::Rule::~Rule() {
}

inline Configure::Fp::f::f() {
}
inline Configure::Fp::f::~f() {
}
inline Configure::Fp::f::vs::vs() {
}
inline Configure::Fp::f::vs::~vs() {
}
inline Configure::Fp::f::vs::canvas::canvas() {
}
inline Configure::Fp::f::vs::canvas::~canvas() {
}
inline Configure::Fp::f::vs::webgl::webgl() {
}
inline Configure::Fp::f::vs::webgl::~webgl() {
}
inline Configure::Fp::f::vs::audio::audio() {
}
inline Configure::Fp::f::vs::audio::~audio() {
}
inline Configure::Fp::f::vs::font::font() {
}
inline Configure::Fp::f::vs::font::~font() {
}
inline Configure::Fp::f::vs::clientrects::clientrects() {
}
inline Configure::Fp::f::vs::clientrects::~clientrects() {
}
inline Configure::Fp::f::vs::clientrects::screen::screen() {
}
inline Configure::Fp::f::vs::clientrects::screen::~screen() {
}
inline Configure::Fp::f::vs::webrtc::webrtc() {
}
inline Configure::Fp::f::vs::webrtc::~webrtc() {
}
inline Configure::Fp::f::vs::navigator::navigator() {
}
inline Configure::Fp::f::vs::navigator::~navigator() {
}
inline Configure::Fp::f::vs::timezone::timezone() {
}
inline Configure::Fp::f::vs::timezone::~timezone() {
}
inline Configure::Fp::f::vs::backup1::backup1() {
}
inline Configure::Fp::f::vs::backup1::~backup1() {
}
inline Configure::Fp::f::vs::backup2::backup2() {
}
inline Configure::Fp::f::vs::backup2::~backup2() {
}
inline Configure::Fp::f::vs::random::random() {
}
inline Configure::Fp::f::vs::random::~random() {
}
inline Configure::Fp::f::vs::nocache::nocache() {
}
inline Configure::Fp::f::vs::nocache::~nocache() {
}

inline Configure::Configure() {
  *this << source_;
}
inline Configure::Configure(const std::string &input) {
  *this << input;
}
inline Configure::~Configure() {
}
/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 13 Nov 2024 05:45:56 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__35D73024_3F90_4D82_9E3E_DAAB4A57133F__