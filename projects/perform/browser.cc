#include "config.h"

Browser::Browser(const std::string &cfg) : cfg_(cfg) {
  Init();
}
Browser::~Browser() {
  UnInit();
}
void Browser::Release() const {
  delete this;
}
void Browser::Init() {
  do {
    brwcfg_ = new Configure(cfg_);

    const std::string chromium_user_data_dir =
        Config::ConfigGet()->GetBrwUserDataDir(brwcfg_->rule_.key);
    stl::Directory::Create(chromium_user_data_dir);

    do { //!@ extensions
    //!@ fp
    //!@ proxy
    
    } while (0);

    do { //!@ default
      brw_startup_args_.emplace_back("--no-first-run");
      brw_startup_args_.emplace_back("--disable-sync");
      brw_startup_args_.emplace_back("--disable-gaia-services");
      brw_startup_args_.emplace_back("--disable-account-consistency");
      brw_startup_args_.emplace_back(
          "--disable-features=ChromeSignin,AccountConsistency");
      brw_startup_args_.emplace_back("--disable-background-mode");
      brw_startup_args_.emplace_back("--no-default-browser-check");
    } while (0);

    do { //!@ 指定版本
      std::string brwver = brwcfg_->worker_.brwver;
      //!@ 浏览器目录
      std::string chromium_dir = Config::ConfigGet()->PathGet().chromium_dir;
      std::map<std::string, std::string> dirs, files;
      stl::Directory::EnumU8(chromium_dir, dirs, files, false);
      if (dirs.empty())
        break;
      //!@ 如果未指定版本 => 使用当前最新版
      //!@ 如果指定不存在的版本 => 使用当前最新版
      auto found = dirs.find(brwver);
      if (found == dirs.end()) {
        brwver = dirs.begin()->first;
      }
      brw_module_pathname_ = fmt::format(R"({}/{}/{})", chromium_dir, brwver,
#if defined(__OSMAC__)
                                         "/chrome.app/Contents/MacOS/chromium"
#elif defined(__OSWIN__)
                                         "/chrome.exe"
#endif
      );
    } while (0);

    do { //!@ user-data-dir
      std::string node;
      node = fmt::format(R"(--user-data-dir={})", chromium_user_data_dir);
      brw_startup_args_.emplace_back(node);
    } while (0);

#if 0 
    stl::File::WriteFile(
        Config::ConfigGet()->PathGet().brw_projects_configure_file,
        brwConfig.source_);
    std::vector<std::string> brw_startup_args;

    do { //!@ proxy
      if (!brwConfig.proxy_.valid())
        break;
      std::string node = fmt::format(
          "--proxy-server={}:{}", brwConfig.proxy_.addr, brwConfig.proxy_.port);
      brw_startup_args.emplace_back(node);
    } while (0);

    do { //!@ startup url
      if (brwConfig.worker_.url.empty())
        break;
      std::string node = fmt::format("--xs-openurl={}", brwConfig.worker_.url);
      brw_startup_args.emplace_back(node);
    } while (0);

    do { //!@ userAgent
      if (brwConfig.fp_.f_.vs_.navigator_.userAgent.empty())
        break;
      std::string node = fmt::format(R"(--user-agent="{}")",
                                     brwConfig.fp_.f_.vs_.navigator_.userAgent);
      brw_startup_args.emplace_back(node);
    } while (0);


    if (brws_.search(final_brw_key)) {
      code = -1002;
      message = "The target is already running";
      break;
    }


    if (!final_brw_prog_fname.empty()) {
      // brw_startup_args
    }
#endif
    ready_.store(true);
  } while (0);
}
void Browser::UnInit() {
  delete brwcfg_;
}
bool Browser::Open() {
  do {
    if (open_.load() || !ready_.load())
      break;
    if (!stl::File::Exists(brw_module_pathname_))
      break;
    std::vector<const char *> startup_args;
    for (const auto &node : brw_startup_args_)
      startup_args.emplace_back(node.c_str());
    startup_args.emplace_back(nullptr);
    int status = xs_sys_process_spawn(brw_module_pathname_.c_str(),
                                      &startup_args[0], &pid_);
    if (status != 0)
      break;
    open_.store(true);
  } while (0);
  return open_.load();
}
void Browser::Close() {
  do {
    if (!open_.load())
      break;
  } while (0);
  open_.store(false);
}
const process_id_t &Browser::GetPid() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return pid_;
}
const std::string &Browser::GetKey() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return brwcfg_->rule_.key;
}
