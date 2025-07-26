#include "config.h"

Browser::Browser() {
  Init();
}
Browser::~Browser() {
  UnInit();
}
void Browser::Init() {
  // Initialization code for the browser can go here
}
void Browser::UnInit() {
  // Cleanup code for the browser can go here
}
bool Browser::CreateChromium(void) {
  bool result = false;
  std::lock_guard<std::mutex> lck(*mtx_);

  return result;
}
void Browser::DestroyChromium(void) {
  std::lock_guard<std::mutex> lck(*mtx_);
}
//////////////////////////////////////////////////////////////
static Browser *__gpBrowser = nullptr;
Browser *Browser::CreateOrGet() {
  if (!__gpBrowser) {
    __gpBrowser = new Browser();
  }
  return __gpBrowser;
}
void Browser::Destroy() {
  if (__gpBrowser) {
    delete __gpBrowser;
    __gpBrowser = nullptr;
  }
}