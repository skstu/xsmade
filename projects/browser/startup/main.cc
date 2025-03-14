#include "startup.h"
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline,
                     int cmdshow) {
  {
    Startup startup;
    startup.Run();
  }
  return 0;
}