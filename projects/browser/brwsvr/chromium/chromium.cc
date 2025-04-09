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
    auto f = processes_.search(type);
    if (!f) {
      std::cout << "Process already exists." << std::endl;
      (*f)->Release();
      processes_.pop(type);
    }
    switch (type) {
    case ChromiumProcessType::ChromiumProcess: {
      auto p = new ChromiumMain(pid);
      p->SetSession(session);
      processes_.push(type, p);
      result = true;
    } break;
    case ChromiumProcessType::ChromiumGpuProcess: {
      auto p = new ChromiumGpu(pid);
      p->SetSession(session);
      processes_.push(type, p);
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
    auto f = processes_.search(ChromiumProcessType::ChromiumProcess);
    if (!f) {
      ret = mp_errno_t::MP_ENOTFOUND;
      break;
    }
    IChromiumProcess *main = *f;
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
    main_pid_ = 0;
    auto u8path = Conv::u16_to_u8(Config::GetOrCreate()->GetChrome(""));
    // xs_base_spawn(const char **args, const char **envs);
    //  if (0 != xs_sys_process_spawn(
    //               Conv::u16_to_u8(Config::GetOrCreate()->GetChrome("")).c_str(),
    //               nullptr, false, &main_pid_))
    //    break;
#if 0
"--no-sandbox",
"--disable-gpu",
"--headless=new",
"--remote-debugging-port=9222",
#endif
    const char *spawn_args[] = {u8path.c_str(),
                                "--no-sandbox",
                                "--disable-gpu",
                                "--headless=new",
                                "--remote-debugging-port=9222",
                                nullptr};
    const char *spawn_envs[] = {"DISPLAY=:0", nullptr};
    xs_base_spawn(spawn_args, spawn_envs, this,
                  [](xs_process_id_t pid, xs_errno_t err, const void *route) {
                    auto self =
                        static_cast<IChromium *>(const_cast<void *>(route));
                    self->main_pid_ = pid;
                    self->processes_.push(ChromiumProcessType::ChromiumProcess,
                                          new ChromiumMain(self->main_pid_));
                  });
    open_.store(true);
  } while (0);
  return open_.load();
}
void IChromium::Close() {
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    if (!open_.load())
      break;
    processes_.iterate([&](const auto &, auto brw) {
      xs_base_kill(brw->GetProcessId(), 9);
      brw->Release();
    });
    xs_base_kill(main_pid_, 9);
    main_pid_ = 0;
    processes_.clear();
    open_.store(false);
  } while (0);
}
IChromiumProcess *IChromium::GetProcess(const ChromiumProcessType &type) const {
  IChromiumProcess *result = nullptr;
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    auto f = processes_.search(type);
    if (!f)
      break;
    result = *f;
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
