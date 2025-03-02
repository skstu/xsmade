#include <wxui.h>

Global::Global() {
  Init();
}
Global::~Global() {
  UnInit();
}
void Global::Init() {
  wxInitAllImageHandlers();
}
void Global::UnInit() {
}
stl::Signal *Global::SignalGet() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return signal_.get();
}
void Global::SetExtra(extra_parameters *extra) {
  std::lock_guard<std::mutex> lock(*mtx_);
  if (!extra_)
    extra_ = extra;
}
extra_parameters *Global::GetExtra() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return extra_;
}
void Global::LoadResource(const std::u16string &resPath) {
  std::lock_guard<std::mutex> lock(*mtx_);
  do {
    if (!stl::Directory::Exists(resPath))
      break;
    resource_dir_ = resPath;
    std::map<std::u16string, std::u16string> files, dirs;
    stl::Directory::Enum(resource_dir_, dirs, files, true);
    if (files.empty())
      break;
    for (const auto &file : files) {
      do {
        auto fext = stl::File::GetFormat(file.second, true);
        if (fext.compare(u".png") == 0 || fext.compare(u".bmp") == 0 ||
            fext.compare(u".jpeg") == 0 || fext.compare(u".ico") == 0 ||
            fext.compare(u".gif") == 0) {
          wxImage* img = nullptr;
          if (wxComm::LoadImg(file.second, &img)) {
            imgres_.emplace(stl::String::Lower(file.first), img);
            break;
          }
        }
        std::string buffer = stl::File::ReadFile(file.second);
        if (buffer.empty())
          break;
        binres_.emplace(stl::String::Lower(file.first), buffer);
      } while (0);
    }
  } while (0);
}
wxImage *Global::GetResImage(const std::u16string &imgName) const {
  wxImage *result = nullptr;
  std::lock_guard<std::mutex> lock(*mtx_);
  do {
    auto found = imgres_.find(stl::String::Lower(imgName));
    if (found == imgres_.end())
      break;
    result = found->second;
  } while (0);
  return result;
}
///////////////////////////////////////////////////////////
Global *Global::Get() {
  static Global global;
  return &global;
}
