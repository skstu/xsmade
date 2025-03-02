#include "perform.h"
using namespace local;
Components::Components() {
  Init();
}

Components::~Components() {
  UnInit();
}

void Components::Init() {
#if 0
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
      std::u16string identify;
      std::u16string main;
      bool enable = false;
      if (obj.HasMember("enable") && obj["enable"].IsBool()) {
        enable = obj["enable"].GetBool();
      }
      if (obj.HasMember("main") && obj["main"].IsString()) {
        main = component_dir + Utfpp::u8_to_u16(obj["main"].GetString());
      }
      if (obj.HasMember("identify") && obj["identify"].IsString()) {
        identify =
            stl::String::Lower(Utfpp::u8_to_u16(obj["identify"].GetString()));
      }
      if (!enable)
        continue;
      if (identify.compare(u"ffmpeg") == 0) {
        if (!stl::File::Exists(main))
          continue;
        auto ff = new FFmpeg();
        ff->enable = enable;
        ff->identify = stl::String::Lower(identify);
        ff->main = main;
        ff->pid_ = 0;
        comps_.emplace(ff->identify, ff);
      }
    }
  } while (0);
#endif
}

void Components::UnInit() {
  for (auto &node : comps_) {
    node.second->Stop();
    node.second->Release();
  }
  comps_.clear();
}
local::IComponent *Components::GetComp(const std::u16string &identify) const {
  IComponent *result = nullptr;
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
  } while (0);
  return result;
}
void Components::DestroyComponent(const std::string &identify,
                                  const ComponentType &type) {
}

/////////////////////////////////////////////////////
#if 0
bool Components::Component::Create(const std::vector<std::string> &args,
                                   const bool &show) {

  for (const auto &node : args) {
    LOG_INFO("{}", node);
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
#endif
bool Components::ffxRecordStart(const wxui::IRecordingArgs *args) {
  bool result = false;
  std::lock_guard<std::mutex> lock{*mtx_};
  do {
    auto fComp = comps_.find(u"ffx");
    if (fComp == comps_.end())
      break;
    if (!args)
      break;
    std::string size = fmt::format("{}x{}", args->GetCX(), args->GetCY());
#if defined(DEBUG)
    std::string outfile = fmt::format(
        R"(C:\Users\k34ub\AppData\Roaming\MarsProjects\userdata\{}.mp4)",
        stl::Time::TimeStamp<std::chrono::microseconds>());
#else
    std::string outfile =
        fmt::format("{}/{}.mp4", System::GetCurrentProcessPath(),
                    stl::Time::TimeStamp<std::chrono::microseconds>());
#endif
    ffx::FFXArgs ffxArgs(ffx::tfFFXArgs{
        {0, {"-y", ""}},
        {1, {"-f", "gdigrab"}},
        {2, {"-video_size", size}},
        {3, {"-offset_x", std::to_string(args->GetX())}},
        {4, {"-offset_y", std::to_string(args->GetY())}},
        {5, {"-framerate", "15"}},
        {6, {"-i", "desktop"}},
        {7, {"-t", "10"}},
        {8, {"-r", "20"}},
        {9, {"-vcodec", "libx264"}},
        {10, {"-s", size}},
        {11, {"-b:v", "10000"}},
        {12, {"-crf", "24"}},
        {13, {"-pix_fmt", "yuv420p"}},
        {14, {"-preset:v", "veryfast"}},
        {15, {"-tune:v", "zerolatency"}},
        {16, {"-xs-outfile", stl::Path::Normalize(outfile)}},
    });
    // fComp->second->Create(ffxArgs.GetArgs(), false);
  } while (0);
  return result;
}
void Components::ffxRecordStop() {
  std::lock_guard<std::mutex> lock{*mtx_};
  do {

  } while (0);
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