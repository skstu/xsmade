#include "server.h"

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
