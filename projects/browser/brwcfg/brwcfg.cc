#include "brwcfg.h"
Brwcfg::Brwcfg() {
  Init();
}
Brwcfg::~Brwcfg() {
  UnInit();
}
void Brwcfg::Init() {
  do {
    config_ = new Config();

    std::string configure_buffer_u8 =
        stl::File::ReadFile(config_->GetConfigurePathname());
    if (configure_buffer_u8.empty())
      break;
    configure_ = new IConfigure(configure_buffer_u8);
    if (!configure_)
      configure_ = new IConfigure("{}");
  } while (0);
  RegisterGoogleApiKey();
}
void Brwcfg::UnInit() {
  SK_DELETE_PTR(configure_);
  SK_DELETE_PTR(config_);
}

bool Brwcfg::Start() {
  do {
    if (open_.load())
      break;
    std::wstring cmdline = GetCommandLineW();
#if _DEBUG
    vmem_ = new VMem();
#else
    if (cmdline.find(L"--type=gpu-process") != std::wstring::npos) {
      vmem_ = new VMem();
    }
#endif
#if ENABLE_PUSH_STREAM

#endif
#if ENABLE_WXUI
    wxui_ = Wxui::Create();
#endif
    open_.store(true);
  } while (0);
  return open_.load();
}
void Brwcfg::Stop() {
  do {
    if (!open_.load())
      break;
#if ENABLE_WXUI
    if (wxui_)
      wxui_->Stop();
    Wxui::Destroy();
#endif
#if ENABLE_PUSH_STREAM

#endif
    SK_DELETE_PTR(vmem_);
    open_.store(false);
  } while (0);
}

void Brwcfg::FreeS(void **p) const {
  if (p) {
    if (*p) {
      free(*p);
      *p = nullptr;
    }
  }
}
void *Brwcfg::MallocS(const size_t &len) const {
  if (len > 0)
    return malloc(len);
  return nullptr;
}

//////////////////////////////////////////////////////////////////
static Brwcfg *__gpsBrwcfg = nullptr;
Brwcfg *Brwcfg::Create() {
  if (!__gpsBrwcfg)
    __gpsBrwcfg = new Brwcfg();
  return __gpsBrwcfg;
}
void Brwcfg::Destroy() {
  if (__gpsBrwcfg)
    __gpsBrwcfg->Stop();
  SK_DELETE_PTR(__gpsBrwcfg);
}
extern "C" {
SHARED_API void *interface_init(void *, unsigned long) {
  IBrw *result = dynamic_cast<IBrw *>(Brwcfg::Create());
  return result;
}
SHARED_API void interface_uninit(void) {
  Brwcfg::Destroy();
}
} // extern "C"