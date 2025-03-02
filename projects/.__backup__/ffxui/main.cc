#include "config.h"

namespace {
#if 0
class MyApp : public wxApp {
public:
  bool OnInit() override {
    return false;
  }
};
class App : public wxApp {
public:
  App() {
  }
  virtual ~App() {
  }

public:
  bool OnInit() override {
    bool result = false;
    do {
      if (!wxApp::OnInit())
        break;
#ifdef _WIN32
      SetProcessDPIAware();
#endif
    } while (0);
    return result;
  }
  int OnExit() override {
    int result = 0;
    do {

      result = wxApp::OnExit();
    } while (0);
    return result;
  }
};
wxIMPLEMENT_APP(App);
#endif
} // namespace

#if 0
#ifdef _WIN32
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline,
                     int cmdshow) {
#else
int main(int argc, char **argv) {
#endif

  return 0;
}
#endif