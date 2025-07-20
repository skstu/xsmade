#include "config.h"

IChromium::IChromium() {
}
IChromium::~IChromium() {
}
void IChromium::Release() const {
  delete this;
}
bool IChromium::Open() {
  bool result = false;
  std::lock_guard<std::mutex> lock(*mtx_);
  do {
    const std::string proc = Config::CreateOrGet()->GetChromiumProcess();
    if (!stl::File::Exists(proc))
      break;
    std::vector<const char *> startup_args{nullptr};
    xs_process_id_t pid = 0;
    if (xs_sys_process_spawn(proc.c_str(), &startup_args[0], nullptr, 1, &pid))
      break;
    result = true;
  } while (0);
  return result;
}
void IChromium::Close() {
  std::lock_guard<std::mutex> lock(*mtx_);
}