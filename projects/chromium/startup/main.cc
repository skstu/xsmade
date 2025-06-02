#include "config.h"
#ifdef __OSWIN__
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
// int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline,
//                      int cmdshow)
int main(int argc, char *args[])
#elif defined(__OSLINUX__)
int main(int argc, char *args[])
#endif
{
  if (0 == xs_sys_process_already_exists(0))
    return 1;
  Config::CreateOrGet();
  Startup startup;
  startup.Run();
  Config::Destroy();
  return 0;
}

