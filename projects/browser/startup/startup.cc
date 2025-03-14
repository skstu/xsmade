#include "startup.h"

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

bool OpenChromium() {
  bool result = false;
  do {
    char *current_path = nullptr;
    size_t current_path_size = 0;
    xs_sys_process_getpath(&current_path, &current_path_size);
    std::string strCurrentPath(current_path, current_path_size);
    xs_sys_free((void **)&current_path);
    std::wstring wstrCurrentPath = Conv::u8_to_ws(strCurrentPath);
    wchar_t targetChromium[MAX_PATH];
    swprintf(targetChromium, MAX_PATH,
             L"%s\\browser\\chromium\\130.0.6723.191\\FanBrowser.exe",
             wstrCurrentPath.c_str());
    if (!stl::File::Exists(targetChromium))
      break;
    std::vector<const char *> startup_args{nullptr};
    xs_process_id_t pid = 0;
    if (xs_sys_process_spawn(Conv::ws_to_u8(targetChromium).c_str(),
                             &startup_args[0], 1, &pid))
      break;
    result = true;
  } while (0);
  return result;
}

Startup::Startup() {
}
Startup::~Startup() {
}
void Startup::Run() const {
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
  do {
    // auto ffxObj = new ffx::FFmpeg();
    // ffxObj->Start(ffxArgs.GetArgs(), false);
    // ffxObj->Stop();
    RegisterHandle();
    OpenChromium();

    auto sss = 0;
  } while (0);
}