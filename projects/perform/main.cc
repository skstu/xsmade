#include "config.h"

// launchctl submit -l com.example.hidden_app -- /path/to/hidden_app
#ifdef __OSWIN__
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline,
                     int cmdshow) {

  std::string cmdline_ = cmdline ? cmdline : "";
#else
int main(int argc, char **argv) {
  std::string cmdline_ = stl::CmdLine::PackageCommandLine(argc, argv);
#endif

  Perform *perform = new Perform(cmdline_);
  perform->Run();
  perform->Release();

  return 0;
}
#if 0
int main(int argc, char **argv) {
  std::string cmdline = stl::Cmdline::PackageCommandLine(argc, argv);
  tfCommandLines cmdlines = stl::Cmdline::ParserCommandLines(cmdline);

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
#endif
