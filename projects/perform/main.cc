#include "config.h"

// launchctl submit -l com.example.hidden_app -- /path/to/hidden_app

static bool open_browser();
static bool close_browser();

int main(int argc, char **argv) {
  std::string cmdline = Stl::PackageCommandLine(argc, argv);
  tfCommandLines cmdlines = Stl::ParserCommandLines(cmdline);
#if defined(__APPLE__)
  const char *chromium_path =
      R"(/Users/huoxingxiongmao/Desktop/241107.app/Contents/MacOS/chromium)";
#elif defined(_WIN32)
  const char *chromium_path =
      R"(C:\Users\k34ub\Desktop\ChromeDebug\chromium\130.0.6723.59\chrome.exe)";
#endif
  const char *args[] = {chromium_path, /*"--proxy-server=127.0.0.1",*/
                        "www.baidu.com", nullptr};

  long long pid = 0;
  int status = xs_sys_process_spawn(chromium_path, args, &pid);
  std::this_thread::sleep_for(std::chrono::milliseconds(10000));
  xs_sys_process_kill(pid);
  return 0;
}
//  /Users/huoxingxiongmao/Desktop/skstu/xsmade/out/perform
bool open_browser() {
  char **environ;
  bool result = false;
  do {
#if defined(__APPLE__)
    const char *chromium_path =
        "/Users/huoxingxiongmao/Desktop/241107.app/Contents/MacOS/chromium";
    const char *args[] = {chromium_path, /*"--proxy-server=127.0.0.1",*/
                          "pixelscan.net", nullptr};

    pid_t pid;
    int status;
    if (posix_spawn(&pid, chromium_path, nullptr, nullptr,
                    const_cast<char *const *>(args), environ) != 0)
      break;
#elif _WIN32

#endif
    result = true;
  } while (0);
  return result;
}
bool close_browser() {
  bool result = false;
  do {
#if defined(__APPLE__)
#elif _WIN32
#endif
    result = true;
  } while (0);
  return result;
}

#if 0 //!@ Create browser


  // 浏览器路径和参数
  const char *chromium_path =
      "/Users/huoxingxiongmao/Desktop/241107.app/Contents/MacOS/chromium";
  const char *args[] = {chromium_path, /*"--proxy-server=127.0.0.1",*/
                      "pixelscan.net", nullptr};

  pid_t pid;
  int status;

  // 使用 posix_spawn 打开浏览器
  if (posix_spawn(&pid, chromium_path, nullptr, nullptr,
                  const_cast<char *const *>(args), environ) == 0) {
    // std::cout << "Browser launched successfully with PID: " << pid <<
    // std::endl;

#if 0
    // 等待浏览器进程结束（可选）
    if (waitpid(pid, &status, 0) != -1) {
      // std::cout << "Browser process finished with status: " << status
      //<< std::endl;
    } else {
      // std::cerr << "Failed to wait for browser process." << std::endl;
    }
#endif
  } else {
    // std::cerr << "Failed to launch browser." << std::endl;
  }

#endif