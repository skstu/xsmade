#include <xs.h>
#include <stl.hpp>
#include <pipe.hpp>
int main(int argc, char **argv) {
  Pipe *pp = new Pipe();
  pp->RegisterConnectedCb([](tfPipeCommandType &reqcmd, std::string &reqbody) {
    std::cout << "Connected." << std::endl;
    reqcmd = 0x01;
    reqbody = "Hello, server!";
  });
  pp->RegisterDisconnectCb([]() { ///
                                  ///
                                  ///
    std::cout << "Disconnected." << std::endl;
  });
  pp->RegisterErrorCb([](const int &eno, const char *estr) {
    std::cout << "Error: " << eno << " " << estr << std::endl;
  });
  pp->RegisterMessageCb([](const tfPipeCommandType &cmd,
                           const std::string &data, tfPipeCommandType &replyCmd,
                           std::string &reply) {
    std::cout << "Received command: " << cmd << ", data: " << data << std::endl;
    reply = "Reply from server";
  });
  pp->RegisterReadyedCb([]() { std::cout << "Server is ready." << std::endl; });
  pp->ConfigGet()->Address("/tmp/xs_pipe_server.sock");
  pp->Start();
  stl::MainProc([](const std::string &input, bool &exit_flag) {
    if (input == "q") {
      exit_flag = true;
    }
  });
  pp->Stop();
  pp->Release();
  return 0;
}
