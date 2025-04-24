#include "server.h"

ChromiumMain::ChromiumMain(const xs_process_id_t &pid)
    : IChromiumProcess(ChromiumProcessType::ChromiumProcess, pid) {
}
ChromiumMain::~ChromiumMain() {
}
void ChromiumMain::Release() const {
  delete this;
}
bool ChromiumMain::Request(const command_type_t &cmd,
                           const std::string &body) const {
  bool result = false;
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
#if ENABLE_UVPP
    if (!session_)
      break;
    if (!session_->Write(cmd, body.data(), body.size()))
      break;
    result = true;
#endif
  } while (0);
  return result;
}
void ChromiumMain::OnMessage(const CommandType &inCmd, const IBuffer *msg,
                             CommandType &repCmd, IBuffer *repMsg) const {
  return;
}