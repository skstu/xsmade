#include "startup.h"
#ifdef __OSWIN__
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline,
                     int cmdshow) {
  {
    Startup startup;
    startup.Run();
  }
  return 0;
}
#elif defined(__OSLINUX__)
int main(int argc, char *args[]) {
  {
    Startup startup;
    startup.Run();
  }
  return 0;
}

#endif
