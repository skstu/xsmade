#include "startup.h"
#ifdef __OSWIN__
bool RegisterHandle() {
  bool result = false;
  do {
    HKEY hKey = nullptr;
    LONG ret =
        RegCreateKeyEx(HKEY_CURRENT_USER,
                       L"Software\\FanBrowser\\NativeMessagingHosts\\com."
                       L"shanzi.rpa.nativemsgsvc",
                       0, nullptr, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
                       nullptr, &hKey, nullptr);
    if (ERROR_SUCCESS != ret)
      break;
    char *current_path = nullptr;
    size_t current_path_size = 0;
    xs_sys_process_getpath(&current_path, &current_path_size);
    std::string strCurrentPath(current_path, current_path_size);
    xs_sys_free((void **)&current_path);
    std::wstring wstrCurrentPath = Conv::u8_to_ws(strCurrentPath);
    wchar_t pathToWrite[MAX_PATH];
    swprintf(pathToWrite, MAX_PATH,
             L"%s\\extensions\\crx_host\\nms_manifest.json",
             wstrCurrentPath.c_str());
    ret = RegSetValueEx(hKey, nullptr, 0, REG_SZ, (const BYTE *)pathToWrite,
                        (wcslen(pathToWrite) + 1) * sizeof(wchar_t));
    if (ERROR_SUCCESS != ret)
      break;
    result = true;
  } while (0);

  return result;
}
#endif
static void *hLibbrwsvr = nullptr;

bool OpenChromium() {
  bool result = false;
  do {
    char *current_path = nullptr;
    size_t current_path_size = 0;
    xs_sys_process_getpath(&current_path, &current_path_size);
    std::string strCurrentPath(current_path, current_path_size);
    xs_sys_free((void **)&current_path);
    std::wstring wstrCurrentPath = Conv::u8_to_ws(strCurrentPath);
    wchar_t targetChromium[260];
    swprintf(targetChromium, 260,
             L"%s\\browser\\chromium\\136.0.7103.149\\XSBrowser.exe",
             wstrCurrentPath.c_str());
    if (!stl::File::Exists(targetChromium))
      break;
    std::vector<const char *> startup_args{nullptr};
    xs_process_id_t pid = 0;
    if (xs_sys_process_spawn(Conv::ws_to_u8(targetChromium).c_str(),
                             &startup_args[0], nullptr, 1, &pid))
      break;

    result = true;
  } while (0);
  return result;
}

Startup::Startup() {
  Init();
}
Startup::~Startup() {
  UnInit();
}
void Startup::Init() {
  do {
    char *current_path = nullptr;
    size_t current_path_size = 0;
    xs_sys_process_getpath(&current_path, &current_path_size);
    current_dir.append(current_path, current_path_size);
    xs_sys_free((void **)&current_path);
#if 0
    std::string libbrwsvr_path = current_dir + "/components/libbrwsvr.so";
    hLibbrwsvr = dlopen(libbrwsvr_path.c_str(), RTLD_NOW);
    if (!hLibbrwsvr)
      break;
    brwsvr_startup = (tf_startup)dlsym(hLibbrwsvr, "startup");
    brwsvr_shutdown = (tf_shutdown)dlsym(hLibbrwsvr, "cleanup");
    brwsvr_malloc_s = (tf_malloc_s)dlsym(hLibbrwsvr, "malloc_s");
    brwsvr_free_s = (tf_free_s)dlsym(hLibbrwsvr, "free_s");
    brwsvr_request = (tf_request)dlsym(hLibbrwsvr, "request");
    brwsvr_register_request_cbs =
        (tf_register_request_cbs)dlsym(hLibbrwsvr, "register_request_cbs");
    if (!brwsvr_startup || !brwsvr_shutdown || !brwsvr_request)
      break;
    ready_.store(brwsvr_startup() == 0);
#endif
    ready_.store(true);
  } while (0);
}
void Startup::UnInit() {
#if 0
  if (brwsvr_shutdown)
    brwsvr_shutdown();
  if (hLibbrwsvr)
    dlclose(hLibbrwsvr);
  hLibbrwsvr = nullptr;
#endif
  ready_.store(false);
}
void Startup::Run() const {
  do {
    if (!ready_.load())
      break;
    // OpenProcess();
    OpenChromium();
  } while (0);
}
static const std::string defaultCfg = R"(
{
	"enable": true,
	"type": 0,
	"policy": {
		"id": 254
	},
	"startup_urls": [
		"https://baidu.com",
		"https://bing.com"
	],
	"homepage": {
		"enable": false,
		"open_new_tab": true,
		"url": "zhihu.com"
	},
	"frame":{
		"enable":true
	},
	"search_engine": "bing",
	"startup_args": [
		{
			"key": "--no-sandbox",
			"value": "",
			"type": 0
		},
		{
			"key": "--disable-web-security",
			"value": "",
			"type": 0
		},
		{
			"key": "--no-first-run",
			"value": "",
			"type": 0
		},
		{
			"key": "--disable-sync",
			"value": "",
			"type": 0
		},
		{
			"key": "--disable-top-sites",
			"value": "",
			"type": 0
		},
		{
			"key": "--disable-gaia-services",
			"value": "",
			"type": 0
		},
		{
			"key": "--disable-account-consistency",
			"value": "",
			"type": 0
		},
		{
			"key": "--disable-features",
			"value": "ChromeSignin,AccountConsistency,SameSiteByDefaultCookies,CookiesWithoutSameSiteMustBeSecure,ThirdPartyCookieDeprecationTrial,TrackingProtection3PCD",
			"type": 0
		},
		{
			"key": "--disable-background-mode",
			"value": "",
			"type": 0
		},
		{
			"key": "--no-default-browser-check",
			"value": "",
			"type": 0
		},
		{
			"key": "--disable-popup-blocking",
			"value": "",
			"type": 0
		},
		{
			"key": "--disable-session-crashed-bubble",
			"value": "",
			"type": 0
		},
		{
			"key": "--disable-restore-session-state",
			"value": "",
			"type": 0
		},
		{
			"key": "--lang",
			"value": "en-US",
			"type": 0
		},
		{
			"key": "--accept-lang",
			"value": "en-US",
			"type": 0
		},
		{
			"key": "--headless",
			"value": "new",
			"type": 0
		},
		{
			"key": "--disable-gpu",
			"value": "",
			"type": 0
		},
		{
			"key": "--remote-debugging-port",
			"value": "9222",
			"type": 0
		}
	]
}
)";
void Startup::OpenProcess() const {
  do {
    if (!ready_.load())
      break;
    bool openCfg = false;
    std::string cfg = defaultCfg;
    std::string mainCfgPath = current_dir + "/configures/main.json";
    if (stl::File::Exists(mainCfgPath)) {
      std::string strJson = stl::File::ReadFile(mainCfgPath);
      if (!strJson.empty()) {
        cfg = strJson;
        openCfg = true;
      }
    }
    if (!openCfg)
      stl::File::WriteFile(mainCfgPath, cfg);
    brwsvr_request(cfg.c_str(), cfg.size());
  } while (0);
}
#if 0
// auto ffxObj = new ffx::FFmpeg();
// ffxObj->Start(ffxArgs.GetArgs(), false);
// ffxObj->Stop();
#ifdef __OSWIN__
    RegisterHandle();
#endif
  ffx::FFXArgs ffxArgs(ffx::tfFFXArgs{
      {0, {"-y", ""}},
      {1, {"-f", "gdigrab"}},
      {2, {"-video_size", "640x480"}},
      {3, {"-offset_x", "0"}},
      {4, {"-offset_y", "0"}},
      {5, {"-framerate", "15"}},
      {6, {"-i", "desktop"}},
      {7, {"-t", "30"}},
      {8, {"-r", "20"}},
      {9, {"-vcodec", "libx264"}},
      {10, {"-s", "640x480"}},
      {11, {"-b:v", "10000"}},
      {12, {"-crf", "24"}},
      {13, {"-pix_fmt", "yuv420p"}},
      {14, {"-preset:v", "veryfast"}},
      {15, {"-tune:v", "zerolatency"}},
      {16, {"-xs-outfile", "test_yuv420p_x264.mp4"}},
  });
#endif