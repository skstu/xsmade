#include <xs.h>
#include <dlfcn.h>
#include <projects/browser/ibrwsvr.h>
static char *__gpsFrameBufferPngDir = nullptr;
static size_t __gsFrameId = 0;
static browser_id_t __gsBrowserId = 0;
int main(int argc, char **argv) {
  char *current_path = nullptr;
  size_t current_path_len = 0;
  xs_sys_process_getpath(&current_path, &current_path_len);
  std::string u8strCurrentPath(current_path, current_path_len);
  xs_sys_free((void **)&current_path);
  std::string strFrameBufferPngDir =
      u8strCurrentPath + "\\" +
      std::to_string(stl::Time::TimeStamp<std::chrono::microseconds>()) + "\\";
  __gpsFrameBufferPngDir = (char *)malloc(strFrameBufferPngDir.size() + 1);
  memcpy(__gpsFrameBufferPngDir, strFrameBufferPngDir.c_str(),
         strFrameBufferPngDir.size());
  __gpsFrameBufferPngDir[strFrameBufferPngDir.size()] = '\0';
  stl::Directory::Create(__gpsFrameBufferPngDir);
  std::string componentsDir = u8strCurrentPath.append(R"(\..\components)");
  std::string libbrwsvrPath = componentsDir + R"(\libbrwsvr.dll)";
  void *handle = dlopen(libbrwsvrPath.c_str(), RTLD_NOW);
  tf_startup startup = nullptr;
  tf_shutdown shutdown = nullptr;
  tf_malloc_s malloc_s = nullptr;
  tf_free_s free_s = nullptr;
  tf_request request = nullptr;
  tf_register_request_cbs register_request_cbs = nullptr;
  do {
    if (!handle)
      break;
    startup = (tf_startup)dlsym(handle, "startup");
    shutdown = (tf_shutdown)dlsym(handle, "cleanup");
    malloc_s = (tf_malloc_s)dlsym(handle, "malloc_s");
    free_s = (tf_free_s)dlsym(handle, "free_s");
    request = (tf_request)dlsym(handle, "request");
    register_request_cbs =
        (tf_register_request_cbs)dlsym(handle, "register_request_cbs");
    if (!startup || !shutdown)
      break;
    startup();
  } while (0);
  std::string input;
  /*
分辨率名称	分辨率（宽 x 高）	用途
144p	256x144	极低带宽环境
240p	352x240	低带宽环境，老旧设备
360p	480x360	低带宽环境，移动设备
480p (SD)	640x480	早期标准分辨率
540p	960x540	介于 480p 和 720p 之间
720p (HD)	1280x720	常见高清分辨率
864p	1536x864	介于 720p 和 1080p 之间
1080p (Full HD)	1920x1080	最广泛使用的高清分辨率
1440p (QHD)	2560x1440	高端显示器、游戏设备
4K (UHD)	3840x2160	主流超高清分辨率
8K (FUHD)	7680x4320	最新超高清分辨率
2560x1080	2560x1080	超宽屏显示器
3440x1440	3440x1440	超宽屏显示器
*/
  do {
    input.clear();
    std::getline(std::cin, input);
    if (input == "q" || std::cin.eof()) {
      break;
    } else if (input == "openbrw") {
      const std::string cfg_create_browser = R"(
{
	"enable": true,
	"type": 0,
	"policy": {
		"id": 5568668
	},
	"startup_urls": ["https://baidu.com","https://bing.com"],
	"homepage": {
		"enable": true,
		"open_new_tab": true,
		"url": "zhihu.com"
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
      request_id_t reqid = 0;
      register_request_cbs(
          [](unsigned long long browser_id, const char *stream,
             unsigned long stream_len) {
            ///
            auto ssss = 0;
          },
          [](browser_id_t brwid, request_id_t reqid, mp_errno_t err,
             const char *res, unsigned long reslen) {
            ///////////////////
            auto ssss = 0;
          });
      mp_errno_t ret =
          request(cfg_create_browser.data(), cfg_create_browser.size());
      if (ret != mp_errno_t::MP_DONE) {
        std::cout << "Create browser failed." << std::endl;
      }
    } else if (input == "closebrw") {
      const std::string cfg_destroy_browser = R"(
        {
          "enable": true,
          "type": 1,
          "policy": {
            "id": 5568668
          }
        }
        )";
      mp_errno_t ret =
          request(cfg_destroy_browser.data(), cfg_destroy_browser.size());
      if (ret != mp_errno_t::MP_DONE) {
        std::cout << "Destroy browser failed." << std::endl;
      }
    } else if (input == "input") {
      const std::string cfg_openurl = R"(
        {
	"enable": true,
	"type": 2,
	"policy": {
		"id": 5568668
	},
	"reqid": 1,
	"input": {
		"enable": true,
		"type": 2,
		"url": "",
		"key": "",
		"text": "",
		"pressType": 3,
		"mouseButtonType": 0,
		"x": 123,
		"y": 321,
		"from_x": 0,
		"from_y": 0,
		"to_x": 0,
		"to_y": 0,
		"wheel": 0,
		"touch": 0
	}
}
        )";

      mp_errno_t ret = request(cfg_openurl.data(), cfg_openurl.size());
      if (ret != mp_errno_t::MP_DONE) {
        std::cout << "Destroy browser failed." << std::endl;
      }
    } else {
      std::cout << "Unknown command: " << input << std::endl;
    }
  } while (1);
  free(__gpsFrameBufferPngDir);
  if (shutdown) {
    shutdown();
  }
  dlclose(handle);

  return 0;
}
