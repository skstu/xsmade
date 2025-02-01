#include "launch.h"
#ifdef __OSWIN__
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline,
                     int cmdshow) {
  stl::Args args(std::string(cmdline ? cmdline : ""));
#else
int main(int argc, char **argv) {
  stl::Args args(argc, argv);
#endif

  return 0;
}
