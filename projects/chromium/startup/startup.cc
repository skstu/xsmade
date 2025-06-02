#include "config.h"

Startup::Startup() {
  Init();
}
Startup::~Startup() {
  UnInit();
}
void Startup::Init() {
  do {
    server_ = new Server();
    ready_.store(true);
  } while (0);
}
void Startup::UnInit() {
  if (server_) {
    server_->Stop();
  }
  SK_DELETE_PTR(server_);
  ready_.store(false);
}
void Startup::Run() const {
  std::thread([this]() {
    bool needStop = true;
    do {
      do { //!@ Server
        if (server_->IsOpen())
          break;
        if (!server_->Start())
          break;
        needStop = false;
      } while (0);
      if (needStop)
        break;
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } while (1);
  }).join();
}
