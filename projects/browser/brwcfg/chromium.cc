#include "brwcfg.h"

IChromium::IChromium(const ChromiumProcessType &type,
                     const std::string &server_addr)
    : type_(type), server_addr_(server_addr) {
  Init();
}
IChromium::~IChromium() {
  UnInit();
}
void IChromium::Init() {
  do {
    policy_id_ = Config::GetOrCreate()->GetConfigure().policy.id;
    uvpp_ = dynamic_cast<IUvpp *>(IUvpp::Create(
        Conv::u16_to_u8(Config::GetOrCreate()->GetPath().libuvpp_path)
            .c_str()));
    uvpp_config_ = uvpp_->ConfigGet();
    uvpp_config_->SetIdentify(policy_id_);
    uvpp_config_->SetServiceType(
        static_cast<unsigned long>(uvpp::ServerType::INITIATOR) |
        static_cast<unsigned long>(uvpp::AddressType::IPC) |
        static_cast<unsigned long>(uvpp::SessionType::IPC));
    uvpp_config_->Address(server_addr_.data(), server_addr_.size());
    uvpp_client_ = uvpp_->CreateSevice();
    ready_.store(true);
  } while (0);
}
void IChromium::UnInit() {
}
const ChromiumProcessType &IChromium::GetType() const {
  return type_;
}
void IChromium::Process() {
}
bool IChromium::Start() {
  do {
    if (!ready_.load())
      break;
    if (open_.load())
      break;
    if (!uvpp_client_->Start())
      break;
    open_.store(true);
    threads_.emplace_back([this]() { Process(); });
  } while (0);
  return open_.load();
}
void IChromium::Stop() {
  do {
    if (!open_.load())
      break;
    open_.store(false);
    for (auto &t : threads_)
      t.join();
    threads_.clear();
    uvpp_client_->Stop();
  } while (0);
}
/////////////////////////////////////////////////////////////////////////////////////////////
//!@ Private
void Brwcfg::RegisterGoogleApiKey() const {
  void(
      putenv((char *)"GOOGLE_API_KEY=AIzaSyCkfPOPZXDKNn8hhgu3JrA62wIgC93d44k"));
  void(putenv((char *)"GOOGLE_DEFAULT_CLIENT_ID=811574891467.apps."
                      "googleusercontent.com"));
  void(putenv((char *)"GOOGLE_DEFAULT_CLIENT_SECRET=kdloedMFGdGla2P1zacGjAQh"));
}
const char *Brwcfg::IConfigureGet() const {
  const auto &cfg = Config::GetOrCreate()->GetConfigure();
  std::string strJson = cfg.Serialization();
  const size_t len = strJson.size() + sizeof(char);
  char *m = (char *)malloc(len);
  memcpy(m, strJson.data(), strJson.size());
  m[strJson.size()] = 0;
  return m;
}
IBrwcfg::IPosition *Brwcfg::CreatePosition() const {
  IBrwcfg::IPosition *result = nullptr;
  local::Position *pos = new local::Position();
  return dynamic_cast<IBrwcfg::IPosition *>(pos);
}
IBrwcfg::ISize *Brwcfg::CreateSize() const {
  IBrwcfg::ISize *result = nullptr;
  local::Size *size = new local::Size();
  return dynamic_cast<IBrwcfg::ISize *>(size);
}
IBrwcfg::IRectangle *Brwcfg::CreateRectangle() const {
  IBrwcfg::IRectangle *result = nullptr;
  local::Rectangle *rect = new local::Rectangle();
  return dynamic_cast<IBrwcfg::IRectangle *>(rect);
}
IBrwcfg::IBuffer *Brwcfg::CreateBuffer(const char *data,
                                       const size_t &len) const {
  IBrwcfg::IBuffer *result = nullptr;
  Buffer *buf = new Buffer(data, len);
  return dynamic_cast<IBrwcfg::IBuffer *>(buf);
}
void Brwcfg::OnChildProcessAppendArgs(IArgsArray **args) const {
  const auto &cfg = Config::GetOrCreate()->GetConfigure();
  ArgsArray *new_args = new ArgsArray();
  *args = dynamic_cast<IBrwcfg::IArgsArray *>(new_args);
  do {
    if (!cfg.proxy.enable)
      break;
    if (cfg.proxy.username.empty() && cfg.proxy.password.empty())
      break;
    std::string serialization;
    serialization.append(cfg.proxy.address)
        .append(",")
        .append(cfg.proxy.username)
        .append(",")
        .append(cfg.proxy.password);
    new_args->Push(new Args("--xs-proxy", serialization));
  } while (0);
}
bool Brwcfg::OnExtensionMessage(const char *extid, const IBuffer *req,
                                IBuffer **res) const {
  bool result = false;
  *res = nullptr;
  do {
    if (!strcmp("mdmeamacpckfoenjdchgibipmkkakaea", extid)) {

    } else if (!strcmp("mmacanpinhhkmgdoebejenmkngocobej", extid)) {
      break;
    }
  } while (0);
  return result;
}
void Brwcfg::OnExtensionsInstall(const IBuffer *root,
                                 IExtensionArray **exts) const {
  ExtensionArray *array = new ExtensionArray();
  *exts = dynamic_cast<IBrwcfg::IExtensionArray *>(array);
  do {
    std::string u8root(root->GetData(), root->GetSize());
    std::u16string u16root = Conv::u8_to_u16(u8root);
    std::map<std::u16string, std::u16string> dirs, files;
    stl::Directory::Enum(u16root, dirs, files, false);
    if (dirs.empty())
      break;
    for (auto &node : dirs) {
      std::u16string man = node.second + u"/manifest.json";
      if (!stl::File::Exists(man))
        continue;
      std::string man_buffer = stl::File::ReadFile(man);
      std::string u8dir = Conv::u16_to_u8(node.second);
      Extension *ext =
          new Extension(new Buffer(u8dir), new Buffer(man_buffer), true);
      array->Push(ext);
    }
  } while (0);
}
void Brwcfg::OnAppendArgs(IArgsArray **args) const {
  const auto &cfg = Config::GetOrCreate()->GetConfigure();
  ArgsArray *array = new ArgsArray();
  *args = dynamic_cast<IBrwcfg::IArgsArray *>(array);
  for (const auto &node : cfg.startup_args) {
    if (node.first.find("user-data-dir") != std::string::npos)
      continue;
    if (node.first.find("proxy-server") != std::string::npos)
      continue;
    if (!node.second.empty()) {
      array->Push(new Args(node.first, node.second));
    } else {
      array->Push(new Args(node.first));
    }
  }
  if (cfg.proxy.enable) {
    array->Push(new Args("proxy-server", cfg.proxy.address));
  }
}
bool Brwcfg::EnableBadFlagsSecurityWarnings(void) const {
  return false;
}
bool Brwcfg::EnableSessionCrashedBubbleViewShow(void) const {
  return false;
}
void Brwcfg::OnBrowserStarted(void) const {
}
void Brwcfg::OnBrowserClosing(void) const {
}
void Brwcfg::OnBrowserReadyed(void) const {
  std::unique_lock<std::mutex> lck(*mtx_, std::defer_lock);
  lck.lock();
  do {
#if 0
    if (chromium_browser_object_) {
      chromium_browser_object_->IForwardInputEventCb(
          [](unsigned long long reqid, IConfigure::Input::ResultCode resultCode,
             long long route) {
            do {
              IChromium *chromium = reinterpret_cast<IChromium *>(route);
              if (!chromium)
                break;
              chromium->OnChromiumInputEvent(reqid, resultCode);
            } while (0);
            LOG_INFO("module({}) reqid({}) resultCode({})", "BrwcfgInput",
                     reqid, static_cast<int>(resultCode));
          },
          reinterpret_cast<long long>(chromium_));
    }
#endif
  } while (0);
  lck.unlock();
}
bool Brwcfg::EnableNonClientHitTest(void) const {
#if ENABLE_WXUI
  return true;
#else
  return true;
#endif
}
bool Brwcfg::EnableBrowserCaptionButtonContainer(void) const {
#if ENABLE_WXUI
  return true;
#else
  return true;
#endif
}
void Brwcfg::OnCreateWindowExBefore(void **parent, unsigned long *style,
                                    unsigned long *exstyle) const {
#if ENABLE_WXUI
  HWND parent_ = nullptr;
  do {
    if (!wxui_)
      break;
    wxui_->Start();
    IFrame *frame = wxui_->GetFrame();
    parent_ = frame->GetHWND();
    if (!IsWindow(parent_))
      break;
    *parent = reinterpret_cast<void *>(parent_);
    //(*window_style) &= ~(WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
    (*style) &= ~WS_SYSMENU;
    //(*window_style) &= ~WS_VISIBLE;
    (*style) |= WS_CHILD;
    //(*window_exstyle) |= WS_EX_TOOLWINDOW;
  } while (0);
#endif
}
void Brwcfg::OnCreateWindowExAfter(void *hwnd) const {
#if ENABLE_WXUI
  HWND parent = nullptr;
  do {
    if (!wxui_)
      break;
    HWND chromium_handle_ = reinterpret_cast<HWND>(hwnd);
    LONG style = GetWindowLongW(chromium_handle_, GWL_STYLE);
    style |= WS_POPUP;
    SetWindowLongW(chromium_handle_, GWL_STYLE, style);
    SendMessageW(::GetAncestor(chromium_handle_, GA_ROOT), WM_SIZE, 0, 0);
  } while (0);
#endif
}
bool Brwcfg::OnExtensionAllowlisted(const char *extension_id) const {
  bool result = true;
  do {
    if (strcmp("afgbmmdnakcefnkchckgelobigkbboci", extension_id) == 0)
      break;
    if (strcmp("hgcaibhfajimiadchhkppepbecmommad", extension_id) == 0)
      break;
    if (strcmp("iehijoelpeicgdpmemibdkbmpmealfhf", extension_id) == 0)
      break;
    if (strcmp("ijjmpjalkodlophonbmjoeabifkepgke", extension_id) == 0)
      break;
    if (strcmp("iopcliemaddhijhmjbecffinafojoofk", extension_id) == 0)
      break;
    if (strcmp("mdmeamacpckfoenjdchgibipmkkakaea", extension_id) == 0)
      break;
    if (strcmp("mmacanpinhhkmgdoebejenmkngocobej", extension_id) == 0)
      break;
    if (strcmp("modppjhbgaggghdagdlmapifkfiffjem", extension_id) == 0)
      break;
    if (strcmp("ebglcogbaklfalmoeccdjbmgfcacengf", extension_id) == 0)
      break;
    if (strcmp("gdjlkcdpddmfnnafnbjkbamdhjjlpkga", extension_id) == 0)
      break;
    if (strcmp("dkmbljdmlgohodhbbddncmbadcoepobl", extension_id) == 0)
      break;
    if (strcmp("facgnnelgcipeopfbjcajpaibhhdjgcp", extension_id) == 0)
      break;
    result = false;
  } while (0);
  return result;
}
void Brwcfg::OnGetUserDataDirectory(IBuffer **out_user_data_dir) const {
  *out_user_data_dir = nullptr;
  do {
    if (Config::GetOrCreate()->GetConfigure().startup_args.empty())
      break;
    std::string u8dir =
        Conv::u16_to_u8(Config::GetOrCreate()->GetPath().chromium_userdata_dir);
    *out_user_data_dir = dynamic_cast<IBrwcfg::IBuffer *>(new Buffer(u8dir));
  } while (0);
}
IBrwcfg::IBrowser *Brwcfg::GetChromiumBrowserObj() const {
  IBrwcfg::IBrowser *result = nullptr;
  std::unique_lock<std::mutex> lck(*mtx_, std::defer_lock);
  lck.lock();
  result = chromium_browser_object_;
  lck.unlock();
  return result;
}
void Brwcfg::SetChromiumBrowserObj(IBrowser *chromium_browser) {
  std::unique_lock<std::mutex> lck(*mtx_, std::defer_lock);
  lck.lock();
  chromium_browser_object_ = chromium_browser;
  lck.unlock();
}
