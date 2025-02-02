#include "launch.h"
#ifdef __OSWIN__
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline,
                     int cmdshow) {
  LPCWSTR args = GetCommandLineW();
  // stl::Args args(std::string(cmdline ? cmdline : ""));
  std::u16string u16args = Conv::ws_to_u16(args ? args : L"");
#else
int main(int argc, char **argv) {
  std::string cmdline_ = stl::CmdLine::PackageCommandLine(argc, argv);
  // stl::Args args(argc, argv);
#endif

  return 0;
}
