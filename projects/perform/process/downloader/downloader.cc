#include "perform.h"

Download::Download() {
  Init();
}
Download::~Download() {
  UnInit();
}
void Download::Release() const {
  delete this;
}
void Download::Init() {
  do {
    auto cmdline = PerformCmdLine::Get();
    if (!cmdline->HasKey("url")) {
      LOG_ERROR("{}", xs_err_name(xs_errno_t::XS_NO));
      break;
    }

  } while (0);
}
void Download::UnInit() {
}
IConfig *Download::ConfigGet() const {
  return nullptr;
}
bool Download::Start() {
  return false;
}
void Download::Stop() {
}