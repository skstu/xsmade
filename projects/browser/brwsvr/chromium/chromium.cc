#include "server.h"
IChromiumProcess::IChromiumProcess(const ChromiumProcessType &type,
                                   const xs_process_id_t &pid)
    : process_type_(type), process_id_(pid) {
}
IChromiumProcess::~IChromiumProcess() {
}
void IChromiumProcess::SetSession(const uvpp::ISession *session) {
  std::lock_guard<std::mutex> lck(*mtx_);
  session_ = const_cast<uvpp::ISession *>(session);
}
const xs_process_id_t &IChromiumProcess::GetProcessId() const {
  std::lock_guard<std::mutex> lck(*mtx_);
  return process_id_;
}
IChromium::IChromium(const browser_id_t &brwid) : browser_id_(brwid) {
}
IChromium::~IChromium() {
}
void IChromium::Release() const {
  delete this;
}
bool IChromium::ProcessReady(const ChromiumProcessType &type,
                             const xs_process_id_t &pid,
                             const uvpp::ISession *session) {
  bool result = false;
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    auto f = processes_.find(type);
    if (f != processes_.end()) {
      std::cout << "Process already exists." << std::endl;
      f->second->Release();
      processes_.erase(f);
    }
    switch (type) {
    case ChromiumProcessType::ChromiumProcess: {
      auto p = new ChromiumMain(pid);
      p->SetSession(session);
      processes_.emplace(type, p);
      result = true;
    } break;
    case ChromiumProcessType::ChromiumGpuProcess: {
      auto p = new ChromiumGpu(pid);
      p->SetSession(session);
      processes_.emplace(type, p);
      result = true;
    } break;
    default:
      std::cout << "Unknown process type." << std::endl;
      break;
    }
  } while (0);
  return result;
}
bool IChromium::Request(const command_type_t &cmd, const std::string &body,
                        mp_errno_t &ret) const {
  bool result = false;
  ret = mp_errno_t::MP_EUNKN;
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    auto f = processes_.find(ChromiumProcessType::ChromiumProcess);
    if (f == processes_.end()) {
      ret = mp_errno_t::MP_ENOTFOUND;
      break;
    }
    IChromiumProcess *main = f->second;
    if (!main) {
      ret = mp_errno_t::MP_ENOTFOUND;
      break;
    }
    if (!main->Request(cmd, body)) {
      ret = mp_errno_t::MP_EREQFAILED;
      break;
    }
    result = true;
    ret = mp_errno_t::MP_OK;
  } while (0);
  return result;
}
const browser_id_t &IChromium::GetBrowserId() const {
  std::lock_guard<std::mutex> lck(*mtx_);
  return browser_id_;
}
bool IChromium::Open() {
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    if (open_.load())
      break;
    if (0 != xs_sys_process_spawn(
                 Conv::u16_to_u8(Config::GetOrCreate()->GetChrome("")).c_str(),
                 nullptr, false, &main_pid_))
      break;
    processes_.emplace(ChromiumProcessType::ChromiumProcess,
                       new ChromiumMain(main_pid_));
    open_.store(true);
  } while (0);
  return open_.load();
}
void IChromium::Close() {
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    if (!open_.load())
      break;
    for (auto &p : processes_) {
      xs_sys_process_kill(p.second->GetProcessId());
      p.second->Release();
    }
    xs_sys_process_kill(main_pid_);
    main_pid_ = 0;
    processes_.clear();
    open_.store(false);
  } while (0);
}
IChromiumProcess *IChromium::GetProcess(const ChromiumProcessType &type) const {
  IChromiumProcess *result = nullptr;
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    auto f = processes_.find(type);
    if (f == processes_.end())
      break;
    result = f->second;
  } while (0);
  return result;
}
/////////////////////////////////////////////////////////////////////////////////
Brwobj::Brwobj(const browser_id_t &brwid) : brwid_(brwid) {
}
Brwobj::~Brwobj() {
}
void Brwobj::Release() const {
  delete this;
}
bool Brwobj::Open() {
  do {
    if (open_.load())
      break;
    xs_process_id_t pid = 0;
    if (0 != xs_sys_process_spawn(
                 Conv::u16_to_u8(Config::GetOrCreate()->GetChrome("")).c_str(),
                 nullptr, false, &pid))
      break;
    pid_ = static_cast<decltype(pid_)>(pid);
    open_.store(true);
  } while (0);
  return open_.load();
}
void Brwobj::Close() {
  do {
    if (!open_.load())
      break;
    xs_sys_process_kill(pid_);
    pid_ = 0;
  } while (0);
  open_.store(false);
}
const browser_id_t &Brwobj::GetId() const {
  return brwid_;
}
const unsigned long &Brwobj::GetPid(void) const {
  return pid_;
}
