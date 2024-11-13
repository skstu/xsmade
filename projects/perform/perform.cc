#include "config.h"

Perform::Perform(const std::string &cmdline) {
  cmdline_ = new stl::CmdLine(cmdline);
}

Perform::~Perform() {
  delete cmdline_;
}
void Perform::Release() const {
  delete this;
}
void Perform::Run() {
  std::thread([this]() {
    bool stop = true;
    Server *server = nullptr;
    do {
      std::string process_type = cmdline_->GetValue("type");
      if (stl::Common::strIcmp(process_type, "service")) {
        do {
          if (server) {
            server->Process();
            break;
          }
          if (0 == xs_sys_process_already_exists(0))
            break;
          server = new Server();
          if (!server->Start())
            break;

          stop = false;
        } while (0);
      }
      if (stop) {
        if (server) {
          server->Stop();
          delete server;
        }
        break;
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } while (1);
  }).join();
}