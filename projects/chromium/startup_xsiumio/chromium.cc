#include "config.h"

IChromium::IChromium(const chromium::xsiumio::IXSiumio &cfg)
    : configure_(cfg), identify_(cfg.identify) {
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
    const std::string proc = Config::CreateOrGet()->GetChromiumProcessPath();
    if (!stl::File::Exists(proc))
      break;

    if (configure_.startup.enable_cleanup_udd) {
      for (int i = 0; i < 5; ++i) {
        try {
          std::string userDataDir =
              Config::CreateOrGet()->GetChromiumUserDataDir(
                  configure_.GetIdentify());
          stl::Directory::RemoveAll(stl::Path::Parent(userDataDir));
          std::cout << "chromium udd clear success." << std::endl;
          break;
        } catch (const std::exception &e) {
          e.what();
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
      }
    }

    xs_process_id_t pid = 0;
    std::vector<const char *> startup_args{nullptr};
    if (xs_sys_process_spawn(proc.c_str(), &startup_args[0], nullptr, 1, &pid))
      break;
    status_ = BrowserStatus::kStarting;
    result = true;
  } while (0);
  return result;
}
void IChromium::Close() {
  std::lock_guard<std::mutex> lock(*mtx_);
  do {
    if (pid_ <= 0)
      break;
    xs_sys_process_kill(pid_, 0x00);
  } while (0);
}
const xs_process_id_t &IChromium::GetBridgePid() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return bridgePid_;
}
void IChromium::SetBridgePid(const xs_process_id_t &pid) {
  std::lock_guard<std::mutex> lock(*mtx_);
  bridgePid_ = pid;
}
const xs_process_id_t &IChromium::GetPid() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return pid_;
}
const BrowserStatus &IChromium::GetStatus() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return status_;
}
void IChromium::SetStatus(const BrowserStatus &status) {
  std::lock_guard<std::mutex> lock(*mtx_);
  status_ = status;
}
bool IChromium::NotifyResult(const chromium::xsiumio::IXSiumio &result) {
  bool r = false;
  std::lock_guard<std::mutex> lock(*mtx_);
  do {
    if (identify_ != result.GetIdentify())
      break;
    pid_ = result.chromium_main_pid;
    port_ = result.chromium_server_port;
    r = true;
  } while (0);
  return r;
}
const int &IChromium::GetPort() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return port_;
}
const chromium::xsiumio::tfIdentifyType &IChromium::GetIdentify() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return configure_.identify;
}
void IChromium::Request(const std::string &body) {
  std::lock_guard<std::mutex> lock(*mtx_);
  do {
    if (port_ <= 0)
      break;
    if (body.empty())
      break;
    httplib::Client cli("localhost", port_);
    auto postRes =
        cli.Post("/chromium", httplib::Headers{{"Accept", "application/json"}},
                 body.data(), body.size(), "application/json");
  } while (0);
}