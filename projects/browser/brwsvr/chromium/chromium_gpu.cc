#include "server.h"

ChromiumGpu::ChromiumGpu(const xs_process_id_t &pid)
    : IChromiumProcess(ChromiumProcessType::ChromiumGpuProcess, pid) {
}
ChromiumGpu::~ChromiumGpu() {
}
void ChromiumGpu::Release() const {
  delete this;
}
bool ChromiumGpu::Request(const command_type_t &, const std::string &) const {
  return false;
}
void ChromiumGpu::OnMessage(const CommandType &inCmd, const IBuffer *msg,
                            CommandType &repCmd, IBuffer *repMsg) const {
  return;
}