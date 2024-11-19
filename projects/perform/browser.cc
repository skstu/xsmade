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
    std::string cfg_cache;
    do { //!@ 获取缓存配置 用于初始化
      Configure tmpcfg(cfg_);
      cfg_cache = stl::File::ReadFile(
          Config::ConfigGet()->GetXSCacheConfigureFName(tmpcfg.rule_.key));
    } while (0);

    brwcfg_ = new Configure(cfg_cache);
    *brwcfg_ << cfg_;

    std::string brwkey = brwcfg_->rule_.key;
    std::string brwver = brwcfg_->worker_.brwver;
    //!@ 浏览器目录
    std::string chromium_dir = Config::ConfigGet()->PathGet().chromium_dir;
    std::string chromium_user_data_dir =
        Config::ConfigGet()->GetBrwUserDataDir(brwkey);
    stl::Directory::Create(chromium_user_data_dir);

    Config::ConfigGet()->XSCacheClean(brwkey);

    do {
      auto dir = Config::ConfigGet()->GetXSCacheCfgsDir(brwkey);
      stl::File::WriteFile(
          Config::ConfigGet()->GetXSCacheConfigureFName(brwkey),
          brwcfg_->source_);
    } while (0);

    //!@ 总开关
    if (!brwcfg_->Enable())
      break;

    do { //!@ extensions
      if (brwcfg_->rule_.IsDefault())
        break;
      //!@ Install default extensions
      do { //!@ ap
        if (!brwcfg_->proxy_.Enable())
          break;
        if (!brwcfg_->proxy_.valid())
          break;
        auto dir = Config::ConfigGet()->GetXSCacheExtsDir(
            brwkey, "afgbmmdnakcefnkchckgelobigkbboci");
        stl::File::WriteFile(dir + "/manifest.json",
                             brwcfg_->GetExtensionManifestAP());
        stl::File::WriteFile(dir + "/background.js",
                             brwcfg_->GetExtensionBackgroundAP());
        brw_startup_args_.emplace_back(fmt::format(R"(--proxy-server={}:{})",
                                                   brwcfg_->proxy_.addr,
                                                   brwcfg_->proxy_.port));
      } while (0);
      do { //!@ fs
        if (!brwcfg_->fp_.Enable())
          break;
        auto dir = Config::ConfigGet()->GetXSCacheExtsDir(
            brwkey, "ebglcogbaklfalmoeccdjbmgfcacengf");
        stl::File::WriteFile(dir + "/manifest.json",
                             brwcfg_->GetExtensionManifestFPS());
        stl::File::WriteFile(dir + "/content.js",
                             brwcfg_->GetExtensionContentFps());
        stl::File::WriteFile(dir + "/background.js",
                             brwcfg_->GetExtensionBackgroundFps());
      } while (0);
      //!@ Install custom extensions
      std::map<std::string, std::string> dirs, files;
      stl::Directory::EnumU8(
          Config::ConfigGet()->PathGet().chromium_extensions_dir, dirs, files,
          false);
      if (files.empty())
        break;

      const std::u16string u16extdir =
          Utfpp::u8_to_u16(Config::ConfigGet()->GetXSCacheExtsDir(brwkey));
      for (const auto &f : files) {
        auto u16path = Utfpp::u8_to_u16(f.second);
        Zipcc::zipUnCompress(u16path, u16extdir);
      }
    } while (0);

    do { //!@ default args
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

    do { //!@ userAgent
      if (brwcfg_->fp_.f_.vs_.navigator_.userAgent.empty())
        break;
      std::string node = fmt::format(R"(--user-agent="{}")",
                                     brwcfg_->fp_.f_.vs_.navigator_.userAgent);
      brw_startup_args_.emplace_back(node);
    } while (0);

    do { //!@ --lang=zh-CN
      if (brwcfg_->fp_.f_.vs_.navigator_.language.empty())
        break;
      std::string node =
          fmt::format(R"(--lang={})", brwcfg_->fp_.f_.vs_.navigator_.language);
      brw_startup_args_.emplace_back(node);
    } while (0);

    do { //!@ user-data-dir
      std::string node;
      node = fmt::format(R"(--user-data-dir={})", chromium_user_data_dir);
      brw_startup_args_.emplace_back(node);
    } while (0);

    do { //!@ startup url
      if (brwcfg_->worker_.url.empty())
        break;
      std::string node = fmt::format("--xs-openurl={}", brwcfg_->worker_.url);
      brw_startup_args_.emplace_back(node);
    } while (0);

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
    xs_sys_process_kill(pid_);
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
