#include "config.h"

Browser::Browser() {
  Init();
}
Browser::~Browser() {
  UnInit();
}
void Browser::Init() {
  // Initialization code for the browser can go here
}
void Browser::UnInit() {
  // Cleanup code for the browser can go here
}
IChromium *Browser::CreateChromium(chromium::IRequest *req) {
  IChromium *chromium = nullptr;
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    if (status_ != BrowserStatus::kIdle &&
        status_ != BrowserStatus::kStarting) {
      req->SetErrorCode(chromium::ErrorCode::ServiceBusy);
      break;
    }
    auto f_exists = chromium_.find(req->GetConfig().GetIdentify());
    if (f_exists != chromium_.end()) {
      req->SetErrorCode(chromium::ErrorCode::AlreadyRunning);
      break;
    }
    {
      std::string userDataDir = Config::CreateOrGet()->GetChromiumUserDataDir(
          req->GetConfig().GetIdentify());
      stl::Directory::Create(userDataDir);
      std::string uddPathPath = Config::CreateOrGet()->GetProjectRouteDir() +
                                "/" +
                                chromium::xsiumio::kProjectFilenameUddPath;
      stl::File::WriteFile(uddPathPath, userDataDir);
    }
    chromium = new IChromium(req->GetConfig());
    chromium->Open();
    status_ = chromium->GetStatus();
    chromium_.emplace(chromium->GetIdentify(), chromium);
  } while (0);
  return chromium;
}
void Browser::DestroyChromium(chromium::IRequest *req) {
  std::lock_guard<std::mutex> lck(*mtx_);
  // auto f_chromium = chromium_.find(cfg.GetIdentify());
  // if (f_chromium != chromium_.end()) {
  //   f_chromium->second->Close();
  //   chromium_.erase(f_chromium);
  // }
}
IChromium *Browser::ResetChromium(chromium::IRequest *req) {
  DestroyChromium(req);
  return CreateChromium(req);
}
void Browser::CheckChromium(
    const std::function<bool(IChromium *)> &isRunningCb) {
  std::lock_guard<std::mutex> lck(*mtx_);
  for (auto it = chromium_.begin(); it != chromium_.end();) {
    if (!isRunningCb(it->second)) {
      xs_process_id_t bridgePid = it->second->GetBridgePid();
      if (bridgePid > 4) {
        xs_sys_process_kill(bridgePid, 0x00);
      }
      it->second->Release();
      it = chromium_.erase(it);
    } else {
      ++it;
    }
  }
}
void Browser::CreateChromiumResult(chromium::IRequest *req) {
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    auto f_chromium = chromium_.find(req->GetConfig().GetIdentify());
    if (f_chromium != chromium_.end()) {
      if (!f_chromium->second->NotifyResult(req->GetConfig())) {
        f_chromium->second->Close();
        chromium_.erase(f_chromium);
        f_chromium->second->Release();
      }
    }
    status_ = BrowserStatus::kIdle;
  } while (0);
}
void Browser::ClearChromium() {
  std::lock_guard<std::mutex> lck(*mtx_);
  for (auto &pair : chromium_) {
    pair.second->Close();
    pair.second->Release();
  }
  chromium_.clear();
  xs_process_id_t bridge_pid = 0;

  xs_sys_process_kill_name(
      Config::CreateOrGet()->GetBridgeProcessName().c_str(), &bridge_pid);

  std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  status_ = BrowserStatus::kIdle;
}
const BrowserStatus &Browser::GetStatus() const {
  std::lock_guard<std::mutex> lck(*mtx_);
  return status_;
}
void Browser::SetStatus(const BrowserStatus &status) {
  std::lock_guard<std::mutex> lck(*mtx_);
  status_ = status;
}
bool Browser::IsIdle() const {
  std::lock_guard<std::mutex> lck(*mtx_);
  return status_ == BrowserStatus::kIdle;
}
//////////////////////////////////////////////////////////////
static Browser *__gpBrowser = nullptr;
Browser *Browser::CreateOrGet() {
  if (!__gpBrowser) {
    __gpBrowser = new Browser();
  }
  return __gpBrowser;
}
void Browser::Destroy() {
  if (__gpBrowser) {
    delete __gpBrowser;
    __gpBrowser = nullptr;
  }
}