#include "launch.h"
#if defined(__OSWIN__) && !defined(_DEBUG)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline,
                     int cmdshow) {
  LPCWSTR args = GetCommandLineW();
  // stl::Args args(std::string(cmdline ? cmdline : ""));
  std::string cmdline_ = Conv::ws_to_u8(args ? args : L"");
#else
int main(int argc, char **argv) {
  std::string cmdline_ = stl::CmdLine::PackageCommandLine(argc, argv);
  // stl::Args args(argc, argv);
#endif
  Launch *pLaunch = new Launch(cmdline_);
  pLaunch->Perform();
  SK_DELETE_PTR(pLaunch);
  return 0;
}
