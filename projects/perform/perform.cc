#include "config.h"

Perform::Perform() {
}

Perform::~Perform() {
}
void Perform::Release() const {
  delete this;
}
void Perform::Run() {
  std::thread([this]() {
    bool needStop = true;
    IPerform *perform = nullptr;
    do {
      switch (PerformCmdLine::Get()->ProcessType()) {
      case PerformProcessType::UTILITY: {
        needStop = true;
      } break;
      case PerformProcessType::DOWNLOAD: {
        perform = new Download();

        needStop = true;
      } break;
      case PerformProcessType::IBROWSER: {
        Server *server = dynamic_cast<Server *>(perform);
        if (server) {
          server->Process();
          break;
        }
        if (0 == xs_sys_process_already_exists(0))
          break;
        perform = new Server();
        if (!perform->Start())
          break;
        needStop = false;
      } break;
      default:
        break;
      }
      if (needStop) {
        if (perform) {
          perform->Stop();
          perform->Release();
        }
        break;
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } while (1);
  }).join();
}

///////////////////////////////////////////////////////////////////////////////
static Perform *__gpPerform = nullptr;
Perform *Perform::Create() {
  if (!__gpPerform)
    __gpPerform = new Perform();
  return __gpPerform;
}
void Perform::Destroy() {
  SK_DELETE_PTR(__gpPerform);
}