#include "server.h"

ChromiumMain::ChromiumMain()
    : IChromiumProcess(ChromiumProcessType::ChromiumProcess) {
}
ChromiumMain::~ChromiumMain() {
}
void ChromiumMain::Release() const {
  delete this;
}