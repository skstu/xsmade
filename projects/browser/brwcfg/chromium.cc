#include "brwcfg.h"

//!@ Private
void Brwcfg::RegisterGoogleApiKey() const {
  void(
      putenv((char *)"GOOGLE_API_KEY=AIzaSyCkfPOPZXDKNn8hhgu3JrA62wIgC93d44k"));
  void(putenv((char *)"GOOGLE_DEFAULT_CLIENT_ID=811574891467.apps."
                      "googleusercontent.com"));
  void(putenv((char *)"GOOGLE_DEFAULT_CLIENT_SECRET=kdloedMFGdGla2P1zacGjAQh"));
}
const char *Brwcfg::IConfigureGet() const {
  std::string strJson = configure_->Serialization();
  const size_t len = strJson.size() + sizeof(char);
  char *m = (char *)malloc(len);
  memcpy(m, strJson.data(), strJson.size());
  m[strJson.size()] = 0;
  return m;
}
IBrw::IBuffer *Brwcfg::CreateBuffer(const char *data, const size_t &len) const {
  IBrw::IBuffer *result = nullptr;
  Buffer *buf = new Buffer(data, len);
  return dynamic_cast<IBrw::IBuffer *>(buf);
}
void Brwcfg::OnChildProcessAppendArgs(IArgsArray **args) const {
  ArgsArray *new_args = new ArgsArray();
  *args = dynamic_cast<IBrw::IArgsArray *>(new_args);
  do {
    if (!configure_->proxy.enable)
      break;
    if (configure_->proxy.username.empty() &&
        configure_->proxy.password.empty())
      break;
    std::string serialization;
    serialization.append(configure_->proxy.address)
        .append(",")
        .append(configure_->proxy.username)
        .append(",")
        .append(configure_->proxy.password);
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
  *exts = dynamic_cast<IBrw::IExtensionArray *>(array);
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
  ArgsArray *array = new ArgsArray();
  *args = dynamic_cast<IBrw::IArgsArray *>(array);
  if (!configure_)
    return;
  for (const auto &node : configure_->startup_args) {
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
  if (configure_->proxy.enable) {
    array->Push(new Args("proxy-server", configure_->proxy.address));
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
    if (!configure_)
      break;
    if (configure_->startup_args.empty())
      break;
#if 0
      auto f_user_data_dir = configure_->startup_args.find("user-data-dir");
      if (f_user_data_dir == configure_->startup_args.end())
        break;
      if (f_user_data_dir->second.empty())
        break;
      auto buf = new Buffer(f_user_data_dir->second);
#endif
    std::u16string u16dir =
        config_->GetChromiumCachePath(configure_->policy.id);
    std::string u8dir = Conv::u16_to_u8(u16dir);
    *out_user_data_dir = dynamic_cast<IBrw::IBuffer *>(new Buffer(u8dir));
  } while (0);
}

void Brwcfg::OnGpuScreenshotImageStream(const IBuffer *stream) const {
  do {
    if (!stream)
      break;
    
  } while (0);
}