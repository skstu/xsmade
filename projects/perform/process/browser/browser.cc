#include <perform.h>

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
  // chrome --host-resolver-rules="MAP * ~NOTFOUND , EXCLUDE 127.0.0.1"
  // --proxy-server=socks://127.0.0.1:1080
  auto config = dynamic_cast<BrowserConfig *>(Perform::ConfigGet());
  if (!config)
    return;
  do {
    std::string cfg_cache;
    do { //!@ 获取缓存配置 用于初始化
      Configure tmpcfg(cfg_);
      cfg_cache = stl::File::ReadFile(
          config->GetXSCacheConfigureFName(Conv::u8_to_u16(tmpcfg.rule_.key)));
    } while (0);

    brwcfg_ = new Configure(cfg_cache);
    *brwcfg_ << cfg_;

    std::u16string brwkey = Conv::u8_to_u16(brwcfg_->rule_.key);
    std::u16string brwver = Conv::u8_to_u16(brwcfg_->worker_.brwver);
    //!@ 浏览器目录
    std::u16string chromium_dir = config->PathGet().chromium_dir;
    std::u16string chromium_user_data_dir = config->GetBrwUserDataDir(brwkey);
    stl::Directory::Create(chromium_user_data_dir);

    config->XSCacheClean(brwkey);

    do { //!@ default args
      brw_startup_args_.emplace_back("--no-first-run");
      brw_startup_args_.emplace_back("--disable-sync");
      brw_startup_args_.emplace_back("--disable-top-sites");
      brw_startup_args_.emplace_back("--disable-gaia-services");
      brw_startup_args_.emplace_back("--disable-account-consistency");
      brw_startup_args_.emplace_back(
          "--disable-features=ChromeSignin,AccountConsistency");
      brw_startup_args_.emplace_back("--disable-background-mode");
      brw_startup_args_.emplace_back("--no-default-browser-check");
      brw_startup_args_.emplace_back("--disable-popup-blocking");
      //!@ 禁用会话恢复
      /*
chrome.exe --new-window about:blank --disable-session-crashed-bubble
--disable-restore-session-state
brw_startup_args_.emplace_back("about:blank");
*/
      brw_startup_args_.emplace_back("--disable-session-crashed-bubble");
      brw_startup_args_.emplace_back("--disable-restore-session-state");
      if (brwcfg_->worker_.enable_lockhp) {
        brw_startup_args_.emplace_back("--xs-lockhp");
      }
    } while (0);

    do { //!@ append args - f12
      if (brwcfg_->worker_.enable_f12)
        break;
      brw_startup_args_.emplace_back("--xs-ddevtool");
    } while (0);

    do { //!@ append args - pwdsavetip
      if (brwcfg_->worker_.enable_pwdsavetip)
        break;
      brw_startup_args_.emplace_back("--xs-dsaveprompt");
    } while (0);

    do { //!@ 指定版本
      std::map<std::u16string, std::u16string> dirs, files;
      stl::Directory::Enum(chromium_dir, dirs, files, false);
      if (dirs.empty())
        break;
      //!@ 如果未指定版本 => 使用当前最新版
      //!@ 如果指定不存在的版本 => 使用当前最新版
      auto found = dirs.find(brwver);
      if (found == dirs.end()) {
        brwver = dirs.begin()->first;
      }
      brw_module_pathname_ = Conv::u8_to_u16(fmt::format(
          R"({}/{}/{})", Conv::u16_to_u8(chromium_dir), Conv::u16_to_u8(brwver),
#if defined(__OSMAC__)
          "/chrome.app/Contents/MacOS/chromium"
#elif defined(__OSWIN__)
          // "/chrome.exe"
          "/fanbrowser.exe"
#endif
          ));
    } while (0);

    if (!brwcfg_->Enable()) {
      ready_.store(true);
      break;
    }
    do {
      auto dir = config->GetXSCacheCfgsDir(brwkey);
      stl::File::WriteFile(config->GetXSCacheConfigureFName(brwkey),
                           brwcfg_->source_);
    } while (0);

    do { //!@ extensions
      if (brwcfg_->rule_.IsDefault())
        break;
      //!@ Install default extensions
      do { //!@ ap
        if (!brwcfg_->proxy_.Enable())
          break;
        //!@ 如果启用了流量中转
        if (brwcfg_->proxy_.traffic_forwarding) {
          // brw_startup_args_.emplace_back(fmt::format(
          //     R"(--host-resolver-rules="MAP * ~NOTFOUND , EXCLUDE {}
          //     --proxy-server=socks://{}:{})", "127.0.0.1", "127.0.0.1",
          //     brwcfg_->worker_.flow_port));
          brw_startup_args_.emplace_back(fmt::format(
              R"(--host-resolver-rules="MAP * ~NOTFOUND , EXCLUDE {})",
              "127.0.0.1"));
        }

        if (!brwcfg_->proxy_.valid())
          break;
        switch (Configure::ProxyType(brwcfg_->proxy_.type)) {
        case Configure::ProxyType::HTTP:
        case Configure::ProxyType::HTTPS: {
          brw_startup_args_.emplace_back(fmt::format(R"(--proxy-server={}:{})",
                                                     brwcfg_->proxy_.addr,
                                                     brwcfg_->proxy_.port));
          if (brwcfg_->proxy_.traffic_forwarding)
            break;
          auto dir = config->GetXSCacheExtsDir(
              brwkey, u"afgbmmdnakcefnkchckgelobigkbboci");
          stl::Directory::Create(dir);
          stl::File::WriteFile(dir + u"/manifest.json",
                               brwcfg_->GetExtensionManifestAP());
          stl::File::WriteFile(dir + u"/background.js",
                               brwcfg_->GetExtensionBackgroundAP());
        } break;
        case Configure::ProxyType::SOCKS4:
        case Configure::ProxyType::SOCKS4A:
        case Configure::ProxyType::SOCKS5: {
          brw_startup_args_.emplace_back(
              fmt::format(R"(--proxy-server=socks://{}:{})",
                          brwcfg_->proxy_.addr, brwcfg_->proxy_.port));
        } break;
        default: {

        } break;
        }

      } while (0);
      do { //!@ fs
        if (!brwcfg_->fp_.Enable())
          break;
        std::u16string dir = config->GetXSCacheExtsDir(
            brwkey, u"ebglcogbaklfalmoeccdjbmgfcacengf");
        stl::Directory::Create(dir);
        stl::File::WriteFile(dir + u"/manifest.json",
                             brwcfg_->GetExtensionManifestFPS());
        stl::File::WriteFile(dir + u"/content.js",
                             brwcfg_->GetExtensionContentFps());
        stl::File::WriteFile(dir + u"/background.js",
                             brwcfg_->GetExtensionBackgroundFps());
      } while (0);
      //!@ Install custom extensions
      std::map<std::u16string, std::u16string> dirs, files;
      stl::Directory::Enum(config->PathGet().chromium_extensions_dir, dirs,
                           files, false);
      if (files.empty())
        break;
      const std::u16string u16extdir = config->GetXSCacheExtsDir(brwkey);
      for (const auto &f : files) {
        auto u16path = f.second;
        Zipcc::zipUnCompress(u16path, u16extdir);
        do { //!@ 自动填充扩展补丁
          if (f.first.find(u"iopcliemaddhijhmjbecffinafojoofk") ==
              std::u16string::npos)
            break;
          std::u16string content_js_path =
              u16extdir + u"/iopcliemaddhijhmjbecffinafojoofk/content.js";
          std::string content_js = stl::File::ReadFile(content_js_path);
          if (content_js.empty())
            break;
          const std::string flagString = "__CONFIGURES__";
          const size_t flagPos = content_js.find(flagString);
          if (flagPos == std::string::npos)
            break;
          std::string finish = content_js.replace(flagPos, flagString.size(),
                                                  brwcfg_->account_.route_);
          stl::File::WriteFile(content_js_path, finish);
        } while (0);

        do { //!@ cookie 扩展补丁
          if (f.first.find(u"facgnnelgcipeopfbjcajpaibhhdjgcp") ==
              std::u16string::npos)
            break;
          std::u16string background_js_path =
              u16extdir + u"/facgnnelgcipeopfbjcajpaibhhdjgcp/background.js";
          if (!stl::File::Exists(background_js_path))
            break;
#if 0
          let envId = __ENVID__
          let envId = "1bcdb1fe0f931b2a07430628ec03213b"
#endif
          std::string background_js = stl::File::ReadFile(background_js_path);
          const std::string flagString = "__ENVID__";
          const size_t flagPos = background_js.find(flagString);
          if (flagPos == std::string::npos)
            break;
          auto patch_code = fmt::format(R"("key":"{}","client_port":{})",
                                        Conv::u16_to_u8(brwkey),
                                        config->GetClientPortCache());
          patch_code.insert(0, "{");
          patch_code.push_back('}');
          std::string finish =
              background_js.replace(flagPos, flagString.size(), patch_code);
          stl::File::WriteFile(background_js_path, finish);
        } while (0);
      }
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
      break;
      if (chromium_user_data_dir.empty())
        break;
      std::string node;
      node = fmt::format(R"(--user-data-dir="{}")",
                         Conv::u16_to_u8(chromium_user_data_dir));
      brw_startup_args_.emplace_back(node);
    } while (0);

    do { //!@ startup url
      break;
      if (brwcfg_->worker_.urls.empty())
        break;
      for (const auto &url : brwcfg_->worker_.urls)
        brw_startup_args_.emplace_back(fmt::format(R"({})", url));
    } while (0);
    do { //!@ cookies
      if (brwcfg_->cookies_.sequence <= 0)
        break;
      std::string cookies_reqData = brwcfg_->cookies_.GetCookiesRequest();
      if (cookies_reqData.empty())
        break;
      std::u16string path =
          config->GetXSCacheRouteReqsDir(brwkey) + u"/" +
          Conv::u8_to_u16(std::to_string(brwcfg_->cookies_.sequence));
      stl::File::WriteFile(path, cookies_reqData);
    } while (0);
    if (brwcfg_->develop_.enable_ && !brwcfg_->develop_.brwargs_.empty()) {
      brw_startup_args_.clear();
      brw_startup_args_.emplace_back(brwcfg_->develop_.brwargs_);
    }

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
    int status =
        xs_sys_process_spawn(Conv::u16_to_u8(brw_module_pathname_).c_str(),
                             nullptr, &startup_args[0], 1, &pid_);
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
    xs_sys_process_kill(pid_, 0);
  } while (0);
  open_.store(false);
}
const xs_process_id_t &Browser::GetPid() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return pid_;
}
const std::string &Browser::GetKey() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return brwcfg_->rule_.key;
}

/*
| 序号 | 参数 | 说明 | |:-------|:-------|:-------|
|1 |--allow-outdated-plugins | 不停用过期的插件。|
|2 |--allow-running-insecure-content | 默认情况下，https 页面不允许从
http链接引用 javascript/css/plug-ins。添加这一参数会放行这些内容。 | |3
|--allow-scripting-gallery
|允许拓展脚本在官方应用中心生效。默认情况下，出于安全因素考虑这些脚本都会被阻止。|
|4 |--disable-accelerated-2d-canvas | 停用 GPU 加速二维画布。|
|5 |--disable-accelerated-video | 停用 GPU 加速视频。|
|6 |--disable-dart | 停用 Dart。|
|7 |--disable-desktop-notifications | 禁用桌面通知，在
Windows中桌面通知默认是启用的。|
|8 |--disable-extensions | 禁用拓展。 |
|9|--disable-file-system | 停用 FileSystem API。（注意一些拓展如 Adblock Plusfor
Google Chrome™ 依赖此 API 运行）|
|10 |--disable-java | 停用 Java。|
|11|--disable-local-storage | 禁用 LocalStorage。 |
|12 |--disable-preconnect | 停用 TCP/IP 预连接。|
|13 |--disable-remote-fonts | 关闭远程字体支持。SVG 中字体不受此参数影响。|
|14 |--disable-speech-input | 停用语音输入。|
|15 |--disable-sync | 停用同步功能。|
|16 |--disable-ssl3 | 停用 SSL v3。|
|17 |--disable-web-security | 不强制遵守同源策略，供网站开发人员测试站点使用。|
|18 |--disk-cache-dir | 将缓存设置在给定的路径。|
|19 |--disk-cache-size | 设置缓存大小上限，以字节为单位。|
|20 |--dns-prefetch-disable | 停用DNS预读。|
|21 |--enable-print-preview | 启用打印预览。|
|22 |--extensions-update-frequency | 设定拓展自动更新频率，以秒为单位。 |
|23 |--incognito | 让浏览器直接以隐身模式启动。|
|24 |--keep-alive-for-test |
最后一个标签关闭后仍保持浏览器进程。（某种意义上可以提高热启动速度，不过你最好得有充足的内存）|
|25 |--kiosk | 启用kiosk模式。（一种类似于全屏的浏览模式）|
|26 |--lang | 使用指定的语言。|
|27 |--no-displaying-insecure-content | 默认情况下，https 页面允许从 http
链接引用图片/字体/框架。添加这一参数会阻止这些内容。|
|28 |--no-first-run | 跳过 Chromium 首次运行检查。|
|29 |--no-referrers | 不发送 Http-Referer 头。|
|30 |--no-sandbox | 彻底停用沙箱。|
|31 |--no-startup-window | 启动时不建立窗口。|
|32 |--proxy-pac-url | 使用给定 URL 的 pac 代理脚本。（也可以使用本地文件，如
--proxy-pac-url="file:\\c:\proxy.pac"）|
|33 |--proxy-server | 使用给定的代理服务器，这个参数只对 http 和 https
有效。（例如 --proxy-server=127.0.0.1:8087 ）|
|34 |--show-component-extension-options | 让自带的拓展组件显示在
chrome://settings/extensions 里。（目前有一个 "Bookmark Manager 0.1"）|
                                                                        //
|35 |--single-process | 以单进程模式运行
Chromium。（启动时浏览器会给出不安全警告）|
|36 |--skip-gpu-data-loading | 跳过启动时的 GPU
信息收集、黑名单读取与黑名单自动更新，这样一来，所有的 GPU 功能都可供使用，并且
about:gpu 页面会显示空白。此参数仅供测试使用。|
|37 |--start-maximized |
启动时最大化。|
|38 |--touch-optimized-ui |
使用对触屏更友好的用户界面。（目前来看似乎只是把一些字体放大了）|
|39 |--user-agent | 使用给定的 User-Agent 字符串。|

*/