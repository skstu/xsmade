#include "server.h"
IChromiumProcess::IChromiumProcess(const ChromiumProcessType &type,
                                   const xs_process_id_t &pid)
    : process_type_(type), process_id_(pid) {
}
IChromiumProcess::~IChromiumProcess() {
}
#if ENABLE_UVPP
void IChromiumProcess::SetSession(const uvpp::ISession *session) {
  std::lock_guard<std::mutex> lck(*mtx_);
  session_ = const_cast<uvpp::ISession *>(session);
}
#endif
const xs_process_id_t &IChromiumProcess::GetProcessId() const {
  std::lock_guard<std::mutex> lck(*mtx_);
  return process_id_;
}
IChromium::IChromium(const std::string &cfg) : brwcfg_(cfg) {
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
#if ENABLE_UVPP
      p->SetSession(session);
#endif
      processes_.push(type, p);
      result = true;
    } break;
    case ChromiumProcessType::ChromiumGpuProcess: {
      auto p = new ChromiumGpu(pid);
#if ENABLE_UVPP
      p->SetSession(session);
#endif
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
  return brwcfg_.policy.id;
}
bool IChromium::Open() {
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    if (open_.load())
      break;
    main_pid_ = 0;
    const std::string u8path =
        Conv::u16_to_u8(Config::GetOrCreate()->GetChrome(""));
    LOG_INFO("current dir", u8path);
    std::vector<std::string> startup_args_cache, startup_envs_cache;
    for (const auto &it : brwcfg_.startup_args) {
      if (it.first.empty())
        continue;
      std::string args = it.first;
      if (!it.second.empty()) {
        args.append("=");
        args.append(it.second);
      }
      startup_args_cache.push_back(args);
    }
    for (const auto &it : brwcfg_.startup_envs) {
      if (it.first.empty() || it.second.empty())
        continue;
      std::string args = it.first;
      args.append("=");
      args.append(it.second);
      startup_envs_cache.push_back(args);
    }
    std::vector<const char *> startup_args{u8path.c_str()}, startup_envs;
    for (const auto &it : startup_args_cache) {
      startup_args.push_back(it.c_str());
    }
    for (const auto &it : startup_envs_cache) {
      startup_envs.push_back(it.c_str());
    }

    // // brwcfg_.startup_args
    // const char *spawn_args[] = {u8path.c_str(), "--no-sandbox",
    // "--disable-gpu",
    //                             "--headless=new", nullptr};
    // /*"DISPLAY=:0"*/
    // const char *spawn_envs[] = {"", nullptr};

    startup_args.push_back(nullptr);
    startup_envs.push_back(nullptr);
    for (const auto &it : startup_args) {
      if (it == nullptr)
        break;
      LOG_INFO("args: {}", it);
    }
    for (const auto &it : startup_envs) {
      if (it == nullptr)
        break;
      LOG_INFO("envs: {}", it);
    }
    xs_base_spawn(&startup_args[0], &startup_envs[0], this,
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
