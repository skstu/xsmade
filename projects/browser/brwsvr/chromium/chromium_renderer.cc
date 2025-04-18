#include "server.h"

ChromiumRenderer::ChromiumRenderer(const xs_process_id_t &pid)
    : IChromiumProcess(ChromiumProcessType::ChromiumGpuProcess, pid) {
}
ChromiumRenderer::~ChromiumRenderer() {
}
void ChromiumRenderer::Release() const {
  delete this;
}
bool ChromiumRenderer::Request(const command_type_t &,
                               const std::string &) const {
  return false;
}