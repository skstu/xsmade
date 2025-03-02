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
//!@ Private
void Brwcfg::RegisterGoogleApiKey() const {
  void(
      putenv((char *)"GOOGLE_API_KEY=AIzaSyCkfPOPZXDKNn8hhgu3JrA62wIgC93d44k"));
  void(putenv((char *)"GOOGLE_DEFAULT_CLIENT_ID=811574891467.apps."
                      "googleusercontent.com"));
  void(putenv((char *)"GOOGLE_DEFAULT_CLIENT_SECRET=kdloedMFGdGla2P1zacGjAQh"));
}
bool Brwcfg::Start() {
  do {
    if (open_.load())
      break;

    open_.store(true);
  } while (0);
  return open_.load();
}
void Brwcfg::Stop() {
  do {
    if (!open_.load())
      break;
    open_.store(false);
  } while (0);
}
const char *Brwcfg::IConfigureGet() const {
  std::string strJson = configure_->Serialization();
  const size_t len = strJson.size() + sizeof(char);
  char *m = (char *)malloc(len);
  memcpy(m, strJson.data(), strJson.size());
  m[strJson.size()] = 0;
  return m;
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
void Brwcfg::OnCreateWindowExBefore(void **parent, unsigned long *style,
                                    unsigned long *exstyle) const {
}
void Brwcfg::OnCreateWindowExAfter(void *hwnd) const {
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