#include "config.h"

namespace {
class App : public wxApp{

};

}
#ifdef _WIN32
#include <windows.h>
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline,
                     int cmdshow) {
#else
int main(int argc, char **argv) {
#endif
  return 0;
}
