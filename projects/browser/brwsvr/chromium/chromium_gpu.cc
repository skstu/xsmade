#include "server.h"

ChromiumGpu::ChromiumGpu()
    : IChromiumProcess(ChromiumProcessType::ChromiumGpuProcess) {
}
ChromiumGpu::~ChromiumGpu() {
}
void ChromiumGpu::Release() const {
  delete this;
}