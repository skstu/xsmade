#include "server.h"
IChromiumProcess::IChromiumProcess(const ChromiumProcessType &type)
    : process_type_(type) {
}
IChromiumProcess::~IChromiumProcess() {
}
IChromium::IChromium(const browser_id_t &brwid) : browser_id_(brwid) {
}
IChromium::~IChromium() {
}
void IChromium::Release() const {
  delete this;
}
const browser_id_t &IChromium::GetBrowserId() const {
  return browser_id_;
}
bool IChromium::Open() {
  do {
    if (open_.load())
      break;
    if (0 != xs_sys_process_spawn(
                 Conv::u16_to_u8(Config::GetOrCreate()->GetChrome("")).c_str(),
                 nullptr, false, &main_pid_))
      break;
    open_.store(true);
  } while (0);
  return open_.load();
}
void IChromium::Close() {
  do {
    if (!open_.load())
      break;
    xs_sys_process_kill(main_pid_);
    main_pid_ = 0;
    open_.store(false);
  } while (0);
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
    if (0 != xs_sys_process_spawn(
                 Conv::u16_to_u8(Config::GetOrCreate()->GetChrome("")).c_str(),
                 nullptr, false, &pid_))
      break;
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
