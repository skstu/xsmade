#include "config.h"
static std::mutex __mtx__;
Startup::Startup() {
  Init();
}
Startup::~Startup() {
  UnInit();
}
void Startup::Init() {
  do {
    server_ = new Server();
    ready_.store(true);
  } while (0);
}
void Startup::UnInit() {
  if (server_) {
    server_->Stop();
  }
  SK_DELETE_PTR(server_);
  ready_.store(false);
}
void Startup::ChromiumClose() {
  std::unique_lock<std::mutex> lck(__mtx__, std::defer_lock);
  lck.lock();
  if (chromium_main_pid_.load() != 0) {
    xs_sys_process_kill(chromium_main_pid_.load(), 0);
    chromium_main_pid_.store(0);
  }
  lck.unlock();
}
bool Startup::OpenChrome() {
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
             L"%s\\browser\\chromium\\138.0.7204.35\\XSiumio.exe",
             wstrCurrentPath.c_str());
    if (!stl::File::Exists(targetChromium))
      break;
    std::string usr_data_dir = Conv::ws_to_u8(wstrCurrentPath) + "/cache/udd";
    usr_data_dir.insert(0, "--user-data-dir=");
    std::string extension_path =
        Conv::ws_to_u8(wstrCurrentPath) + "/extensions/adscore-handler";
    extension_path.insert(0, "--load-extension=");
    std::vector<const char *> startup_args{
        "--no-first-run",
        "--no-default-browser-check",
        "--disable-web-security",
        "--disable-features=DisableLoadExtensionCommandLineSwitch",
        usr_data_dir.c_str(),
        extension_path.c_str(),
        nullptr};
    xs_process_id_t pid = 0;
    if (xs_sys_process_spawn(Conv::ws_to_u8(targetChromium).c_str(),
                             /*&startup_args[0]*/ nullptr, nullptr, 1, &pid))
      break;
    chromium_main_pid_.store(pid);
    result = true;
  } while (0);
  return result;
}
void Startup::Run() {
  std::thread([this]() {
    bool needStop = true;
    do {
      do { //!@ Server
        if (server_->IsOpen())
          break;
        if (!server_->Start())
          break;
        needStop = false;
      } while (0);

      do {
        std::unique_lock<std::mutex> lck(__mtx__, std::defer_lock);
        lck.lock();
        if (chromium_main_pid_.load() == 0) {
          OpenChrome();
        }
        lck.unlock();
      } while (0);
      if (needStop)
        break;
      std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    } while (1);
  }).join();
}

/////////////////////////////////////////////////////////////////////
Startup *__gpsStartup = nullptr;
Startup *Startup::GetOrCreate() {
  if (!__gpsStartup)
    __gpsStartup = new Startup();
  return __gpsStartup;
}
void Startup::Destroy() {
  if (__gpsStartup) {
    delete __gpsStartup;
    __gpsStartup = nullptr;
  }
}