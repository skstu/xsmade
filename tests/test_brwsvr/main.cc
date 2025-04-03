#include <xs.h>
#include <dlfcn.h>
#include "rapidjson.h"
#include <projects/browser/configure.hpp>
#include <projects/browser/ibrwsvr.h>
#include <projects/browser/protocol.hpp>

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
#if defined(__OSWIN__)
  std::string libbrwsvrPath = componentsDir + R"(\libbrwsvr.dll)";
#elif defined(__OSLINUX__)
  std::string libbrwsvrPath = componentsDir + R"(\libbrwsvr.so)";
#endif
  void *handle =
      dlopen("/home/ponyo/Desktop/projects/xsmade/bin/components/libbrwsvr.so",
             RTLD_NOW);
  auto dlerr = dlerror();
  if (dlerr) {
    std::cerr << "dlopen error: " << dlerr << std::endl;
    return -1;
  }
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

  char *current_dir = nullptr;
  size_t current_dir_len = 0;
  xs_sys_process_getpath(&current_dir, &current_dir_len);
  const std::string configures_dir =
      stl::Path::Parent(std::string(current_dir, current_dir_len)) +
      "\\configures\\";
  xs_sys_free((void **)&current_dir);

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
      std::string cfg =
          stl::File::ReadFile(configures_dir + "test_openbrw.json");
      request_id_t reqid = 0;
      register_request_cbs(
          [](browser_id_t browser_id, const char *stream,
             unsigned long stream_len) {
            std::string strFrameBufferPngDir(__gpsFrameBufferPngDir);
            std::string strFrameBufferPngPath =
                strFrameBufferPngDir + std::to_string(__gsFrameId++) + ".png";
            stl::File::WriteFile(strFrameBufferPngPath,
                                 std::string((char *)stream, stream_len));
            ///
            auto ssss = 0;
          },
          [](browser_id_t brwid, request_id_t reqid, int err, const char *res,
             unsigned long reslen) {
            ///////////////////
            auto ssss = 0;
          });
      int ret = request(cfg.data(), cfg.size());
      if (ret != (int)MP_DONE) {
        std::cout << "Create browser failed." << std::endl;
      }
    } else if (input == "closebrw") {
      std::string cfg =
          stl::File::ReadFile(configures_dir + "test_closebrw.json");
      int ret = request(cfg.data(), cfg.size());
      if (ret != MP_DONE) {
        std::cout << "Destroy browser failed." << std::endl;
      }
    } else if (input == "input") {
      std::string cfg =
          stl::File::ReadFile(configures_dir + "test_brwinput.json");
      int ret = request(cfg.data(), cfg.size());
      if (ret != MP_DONE) {
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
