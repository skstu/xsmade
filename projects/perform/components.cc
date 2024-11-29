#include "config.h"

Components::Components() {
  Init();
}

Components::~Components() {
  UnInit();
}

void Components::Init() {
  do {
    const std::u16string current_path =
        Utfpp::u8_to_u16(Config::ConfigGet()->PathGet().root_dir);
    const std::u16string component_dir =
        stl::Path::Mormalize(current_path + u"/" + root_dir_name_ + u"/");
    stl::Directory::Create(component_dir);
    const std::u16string component_config_path =
        stl::Path::Mormalize(component_dir + u"/" + root_dir_name_ + u".json");
    if (!stl::File::Exists(component_config_path)) {
      stl::File::Create(component_config_path);
    }
    std::string read = stl::File::ReadFile(component_config_path);
    if (read.empty()) {
      read = "[]";
      stl::File::Remove(component_config_path);
      stl::File::WriteFile(component_config_path, read);
    }

    rapidjson::Document doc;
    if (doc.Parse(read.data(), read.size()).HasParseError())
      break;
    if (!doc.IsArray())
      break;
    if (doc.Empty())
      break;
    for (auto it = doc.Begin(); it != doc.End(); ++it) {
      auto &obj = *it;
      Component *comp = new Component();
      if (obj.HasMember("enable") && obj["enable"].IsBool()) {
        comp->enable = obj["enable"].GetBool();
      }
      if (obj.HasMember("main") && obj["main"].IsString()) {
        comp->main = component_dir + Utfpp::u8_to_u16(obj["main"].GetString());
      }
      if (obj.HasMember("identify") && obj["identify"].IsString()) {
        comp->identify =
            stl::String::Lower(Utfpp::u8_to_u16(obj["identify"].GetString()));
      }
      if (comp->enable && !comp->identify.empty() &&
          stl::File::Exists(comp->main)) {
        auto exists = comps_.find(comp->identify);
        if (exists != comps_.end())
          comps_.erase(exists);
        comps_.emplace(comp->identify, comp);
      } else {
        delete comp;
        comp = nullptr;
      }
    }
  } while (0);
}

void Components::UnInit() {
}
Components::Component *
Components::GetComp(const std::u16string &identify) const {
  Component *result = nullptr;
  std::lock_guard<std::mutex> lock{*mtx_};
  auto found = comps_.find(stl::String::Lower(identify));
  do {
    if (identify.empty())
      break;
    if (found == comps_.end())
      break;
    result = found->second;
  } while (0);
  return result;
}
bool Components::CreateComponent(const std::string &identify,
                                 const ComponentType &ctype,
                                 const std::vector<std::string> &startup_args,
                                 const bool &show) {
  bool result = false;
  do {


    result = true;
  }while(0);
  return result;
}
void Components::DestroyComponent(const std::string &identify,
                                  const ComponentType &type) {
}

/////////////////////////////////////////////////////
bool Components::Component::Create(const std::vector<std::string> &args,
                                   const bool &show) {

  for (const auto &node : args) {
    LOG_INFO("{}",node);
  }
  std::vector<const char *> startup_args;
  for (const auto &node : args)
    startup_args.emplace_back(node.c_str());
  startup_args.emplace_back(nullptr);

  int status = xs_sys_process_spawn(Utfpp::u16_to_u8(main).c_str(),
                                    &startup_args[0], show ? 1 : 0, &pid_);
  return status == 0;
}
void Components::Component::Destroy() {
  auto ss = 0;
}
///////////////////////////////////////////////////
static Components *__gpTools = nullptr;
Components *Components::Get() {
  if (!__gpTools)
    __gpTools = new Components();
  return __gpTools;
}
void Components::Destroy() {
  if (__gpTools) {
    delete __gpTools;
    __gpTools = nullptr;
  }
}