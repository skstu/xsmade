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
    std::wstring cmdline = stl::String::Lower(GetCommandLineW());
    if (cmdline.find(L"--type") == std::wstring::npos) {
      LOG_INIT(config->GetPath().logs_dir + u"/" +
               config->GetPath().module_name + u"_main.log");
      chromium_ = new ChromiumMain(
          Config::GetOrCreate()->GetSettings().server.pipe_addr);
    } else if (cmdline.find(L"--type=gpu-process") != std::wstring::npos) {
      LOG_INIT(config->GetPath().logs_dir + u"/" +
               config->GetPath().module_name + u"_gpu.log");
      chromium_ = new ChromiumGpu(
          Config::GetOrCreate()->GetSettings().server.pipe_addr);
    } else if (cmdline.find(L"--type=renderer") != std::wstring::npos) {
    } else if (cmdline.find(
                   L"--utility-sub-type=network.mojom.networkservice") !=
               std::wstring::npos) {
    } else if (cmdline.find(
                   L"--utility-sub-type=storage.mojom.storageservice") !=
               std::wstring::npos) {
    } else if (cmdline.find(L"--type=crashpad-handler") != std::wstring::npos) {
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
  do {
    if (!width || !height)
      break;
    if (!Config::GetOrCreate()->GetConfigure().frame.enable)
      break;
    if (Config::GetOrCreate()->GetConfigure().frame.resolution.width <= 0 ||
        Config::GetOrCreate()->GetConfigure().frame.resolution.height <= 0)
      break;
    *width = Config::GetOrCreate()->GetConfigure().frame.resolution.width;
    *height = Config::GetOrCreate()->GetConfigure().frame.resolution.height;
    result = true;
  } while (0);
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
  IBrwcfg *result = dynamic_cast<IBrwcfg *>(Brwcfg::GetOrCreate());
  return result;
}
SHARED_API void interface_uninit(void) {
  Brwcfg::Destroy();
  Config::Destroy();
}
} // extern "C"