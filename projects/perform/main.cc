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
  PerformCmdLine::Create(cmdline_);
  auto pConfig = Config::ConfigGet();
  auto pTools = Components::Get();
  Perform::Create()->Run();
  Perform::Destroy();
  Components::Destroy();
  Config::Destroy();
  PerformCmdLine::Destroy();
  return 0;
}
