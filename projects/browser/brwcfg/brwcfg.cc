#include "brwcfg.h"
Brwcfg::Brwcfg() {
  Init();
}
Brwcfg::~Brwcfg() {
  UnInit();
}
void Brwcfg::Init() {
  RegisterGoogleApiKey();
}
void Brwcfg::UnInit() {
}
bool Brwcfg::Start() {
  const auto config = Config::GetOrCreate();
  do {
    if (open_.load())
      break;
    char *cmdline_ = nullptr;
    size_t cmdline_len_ = 0;
    xs_sys_get_commandline(&cmdline_, &cmdline_len_);
    std::string strCmdline(cmdline_, cmdline_len_);
    xs_sys_free((void **)&cmdline_);
    std::string cmdline = stl::String::Lower(strCmdline);
    if (cmdline.find("--type") == std::wstring::npos) {
      LOG_INIT(config->GetPath().logs_dir + u"/" +
               config->GetPath().module_name + u"_main.log");
      chromium_ = new ChromiumMain(
          Config::GetOrCreate()->GetSettings().server.pipe_addr);
    } else if (cmdline.find("--type=gpu-process") != std::wstring::npos) {
      LOG_INIT(config->GetPath().logs_dir + u"/" +
               config->GetPath().module_name + u"_gpu.log");
      chromium_ = new ChromiumGpu(
          Config::GetOrCreate()->GetSettings().server.pipe_addr);
    } else if (cmdline.find("--type=renderer") != std::wstring::npos) {
    } else if (cmdline.find(
                   "--utility-sub-type=network.mojom.networkservice") !=
               std::wstring::npos) {
    } else if (cmdline.find(
                   "--utility-sub-type=storage.mojom.storageservice") !=
               std::wstring::npos) {
    } else if (cmdline.find("--type=crashpad-handler") != std::wstring::npos) {
    } else {
    }
#if ENABLE_WXUI
    wxui_ = Wxui::Create();
#endif
    if (chromium_)
      chromium_->Start();
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
#if ENABLE_VMEM
    SK_DELETE_PTR(vmem_);
#endif
    open_.store(false);
    if (chromium_) {
      chromium_->Stop();
      chromium_->Release();
    }
    LOG_UNINIT;
  } while (0);
}
void Brwcfg::OnGpuScreenshotImageStream(const IBuffer *stream) const {
  do {
    if (!stream)
      break;
    if (!chromium_)
      break;
    chromium_->OnGpuScreenshotImageStream(stream->GetData(), stream->GetSize());
  } while (0);
}
bool Brwcfg::OnGpuCanvasFrameGetResolution(int *width, int *height) const {
  bool result = false;
  const auto &cfg = Config::GetOrCreate()->GetConfigure();
  if (width && height && cfg.frame.enable) {
    if (cfg.frame.resolution.width > 0 && cfg.frame.resolution.height > 0) {

      *width = cfg.frame.resolution.width;
      *height = cfg.frame.resolution.height;
      result = true;
    }
  }
  return result;
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
void Brwcfg::ServerStatus(const bool &status) {
  std::lock_guard<std::mutex> lck(*mtx_);
  server_ready_.store(status);
}
bool Brwcfg::ServerStatus() const {
  std::lock_guard<std::mutex> lck(*mtx_);
  return server_ready_.load();
}
//////////////////////////////////////////////////////////////////
static Brwcfg *__gpsBrwcfg = nullptr;
Brwcfg *Brwcfg::GetOrCreate() {
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
  Config::GetOrCreate();
  return reinterpret_cast<void *>(
      dynamic_cast<IBrwcfg *>(Brwcfg::GetOrCreate()));
}
SHARED_API void interface_uninit(void) {
  Brwcfg::Destroy();
  Config::Destroy();
}
} // extern "C"