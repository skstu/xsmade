#include <xs.h>
#include <stl.hpp>
#include <pipe.hpp>
int main(int argc, char **argv) {
  Pipe *pp = new Pipe("/tmp/xs_pipe_server.sock");
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
