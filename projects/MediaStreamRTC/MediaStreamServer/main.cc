#include "MediaStreamServer.h"
#if 0
// launchctl submit -l com.example.hidden_app -- /path/to/hidden_app
#ifdef __OSWIN__
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline,
                     int cmdshow) {
  std::string cmdline_ = cmdline ? cmdline : "";
#else
int main(int argc, char **argv) {
  std::string cmdline_ = stl::CmdLine::PackageCommandLine(argc, argv);
#endif
#endif
int main(int argc, char **argv) {
  std::string cmdline_ = stl::CmdLine::PackageCommandLine(argc, argv);
  auto server = MediaStreamServer::Create();
  server->Start();
  std::string input;
  do {
    input.clear();
    std::getline(std::cin, input);
    if (input == "q" || std::cin.eof()) {
      server->Stop();
      break;
    } else {
    }
  } while (1);
  MediaStreamServer::Destroy();
  return 0;
}
