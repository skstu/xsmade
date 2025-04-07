#include "system.h"
#include "conv.hpp"
#include "base.hpp"
using namespace xs::base;
int main(int argc, char **argv) {
  xs_base_startup();
  xs_base_spawn("test1", "test2", "test3");
  xs_base_add_task_v1([]() -> xs_errno_t { /**/
                                           return xs_errno_t::XS_OK;
  });
  stl::MainProc([](const std::string &input, bool &exit_flag) {
    if (input == "q") {
      exit_flag = true;
    } else {
      std::cout << "You entered: " << input << std::endl;
    }
  });
  xs_base_shutdown();
  return 0;
}
