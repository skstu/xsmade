#include "perform.h"

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
    do {
      switch (PerformCmdLine::Get()->ProcessType()) {
      case PerformProcessType::UTILITY: {
        needStop = true;
      } break;
      case PerformProcessType::DOWNLOAD: {
        current_ = new Download();

        needStop = true;
      } break;
      case PerformProcessType::STREAMPP: {
        current_ = new IStreamPP();
        if (!current_->Start())
          break;
        needStop = false;
      } break;
      case PerformProcessType::IBROWSER: {
        IBrowserInterfaceServer *server =
            dynamic_cast<IBrowserInterfaceServer *>(current_);
        if (server) {
          server->Process();
          break;
        }
        if (0 == xs_sys_process_already_exists(0))
          break;
        current_ = new IBrowserInterfaceServer();
        if (!current_->Start())
          break;
        needStop = false;
      } break;
      default:
        break;
      }
      if (needStop) {
        if (current_) {
          current_->Stop();
          current_->Release();
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
Perform *Perform::Get() {
  return Perform::Create();
}
void Perform::Destroy() {
  SK_DELETE_PTR(__gpPerform);
}
IConfig *Perform::ConfigGet() {
  IConfig *result = nullptr;
  if (__gpPerform) {
    if (__gpPerform->current_) {
      result = __gpPerform->current_->ConfigGet();
    }
  }
  return result;
}