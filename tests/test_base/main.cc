#include "system.h"
#include "conv.hpp"
#include "base.hpp"
using namespace xs::base;
int main(int argc, char **argv) {
  xs_base_startup();
  const char *spawn_args[] = {
      "/home/ponyo/Desktop/projects/work/chromium/scrapeio_fpbrowser_linux/"
      "130.0.6723.116/src/out/release/chrome",
      "--no-sandbox", "--disable-gpu", "--remote-debugging-port=9222", nullptr};
  const char *spawn_envs[] = {"DISPLAY=:0", nullptr};

  const char *proc =
      "/home/ponyo/Desktop/projects/work/chromium/scrapeio_fpbrowser_linux/"
      "130.0.6723.116/src/out/release/chrome";
  xs_base_spawn(spawn_args, spawn_envs);
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
