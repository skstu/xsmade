#if !defined(__2086FCD8_A8AD_4114_B744_1BAF649D6A53__)
#define __2086FCD8_A8AD_4114_B744_1BAF649D6A53__

namespace brwcfg {
class ISettings {
public:
  class Server {
  public:
    Server() = default;
    ~Server() = default;

  public:
    std::string pipe_addr;
    std::string tcp_addr;
    std::string udp_addr;
  };

public:
  inline ISettings(const std::string &);
  inline ~ISettings();

private:
  inline void Init();
  inline void UnInit();

public:
  bool enable_logger = false;
  bool enable_devmode = false;
  Server server;

private:
  const std::string config_buffer_;
};
inline ISettings::ISettings(const std::string &buffer)
    : config_buffer_(buffer) {
  Init();
}
inline ISettings::~ISettings() {
  UnInit();
}
inline void ISettings::Init() {
  do {
    if (config_buffer_.empty())
      break;
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError xmlErr =
        doc.Parse(config_buffer_.c_str(), config_buffer_.size());
    if (xmlErr != tinyxml2::XML_SUCCESS)
      break;

    tinyxml2::XMLNode *node_settings = doc.FirstChildElement("settings");
    if (!node_settings)
      break;
    auto node_settings_attr = node_settings->ToElement()->FirstAttribute();
    while (node_settings_attr) {
      if (!strcmp("logger", node_settings_attr->Name())) {
        node_settings_attr->QueryBoolValue(&enable_logger);
      } else if (!strcmp("devmode", node_settings_attr->Name())) {
        node_settings_attr->QueryBoolValue(&enable_devmode);
      }
      node_settings_attr = node_settings_attr->Next();
    }
    auto first_node = node_settings->FirstChild();
    while (first_node) { //!@ server
      if (auto element = first_node->ToElement()) {
        if (!strcmp("server", element->Value())) {
          auto attr = element->FirstAttribute();
          while (attr) {
            if (!strcmp("pipe_addr", attr->Name())) {
              server.pipe_addr = attr->Value();
            }
            if (!strcmp("tcp_addr", attr->Name())) {
              server.tcp_addr = attr->Value();
            }
            if (!strcmp("udp_addr", attr->Name())) {
              server.udp_addr = attr->Value();
            }
            attr = attr->Next();
          }
          auto node = element->FirstChild();
          while (node) {

            node = node->NextSibling();
          }
          break;
        }
      } else if (auto text = first_node->ToText()) {
      } else if (auto comment = first_node->ToComment()) {
      }
      first_node = first_node->NextSibling();
    }
    first_node = node_settings->FirstChild();
    while (first_node) { //!@ plugins
      if (auto element = first_node->ToElement()) {
        if (!strcmp("components", element->Value())) {

          break;
        }
      } else if (auto text = first_node->ToText()) {
      } else if (auto comment = first_node->ToComment()) {
      }
      first_node = first_node->NextSibling();
    }
    first_node = node_settings->FirstChild();
    while (first_node) { //!@ components
      if (auto element = first_node->ToElement()) {
        if (!strcmp("plugins", element->Value())) {
          auto att = element->FirstAttribute();
          while (att) {
            if (!strcmp("vvv", att->Name())) {

              auto value = att->Value();
              auto ssssss = 0;
            }
            att = att->Next();
          }

          auto node = element->FirstChild();
          while (node) {

            node = node->NextSibling();
          }
          break;
        }
      } else if (auto text = first_node->ToText()) {
      } else if (auto comment = first_node->ToComment()) {
      }
      first_node = first_node->NextSibling();
    }
    auto xx = 0;
  } while (0);
}
inline void ISettings::UnInit() {
}
} // namespace brwcfg
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 15 Mar 2025 12:25:29 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__2086FCD8_A8AD_4114_B744_1BAF649D6A53__