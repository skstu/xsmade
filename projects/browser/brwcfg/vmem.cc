#include "brwcfg.h"

VMem::VMem() {
  Init();
}
VMem::~VMem() {
  UnInit();
}
void VMem::Init() {
  do {
    current_pid_ = GetCurrentProcessId();
    shared_process_mutex_name_ =
        std::to_wstring(stl::Time::TimeStamp<std::chrono::milliseconds>());
    handle_ = GetCurrentProcess();
    base_ = VirtualAllocEx(handle_, nullptr, total_, MEM_COMMIT | MEM_RESERVE,
                           PAGE_EXECUTE_READWRITE);
    if (!base_)
      break;

  } while (0);
}
void VMem::UnInit() {
}
const unsigned long &VMem::GetCurrentPid() const {
  std::lock_guard<std::mutex> lck(*mtx_);
  return current_pid_;
}
const void *VMem::GetBase() const {
  std::lock_guard<std::mutex> lck(*mtx_);
  return base_;
}
const HANDLE &VMem::GetHandle() const {
  std::lock_guard<std::mutex> lck(*mtx_);
  return handle_;
}
bool VMem::Write(const std::string &data) const {
  bool result = false;
  std::lock_guard<std::mutex> lck(*mtx_);
  HANDLE hMutex = nullptr;
  do {
    if (!base_)
      break;
    if (data.empty())
      break;
    hMutex = CreateMutexW(NULL, FALSE, shared_process_mutex_name_.c_str());
    if (!hMutex)
      break;
    DWORD dwWaitResult = WaitForSingleObject(hMutex, INFINITE);
    switch (dwWaitResult) {
    case WAIT_OBJECT_0: {
      SIZE_T sizeNumberOfBytesWritten = 0;
      if (!WriteProcessMemory(handle_, base_, data.data(), data.size(),
                              &sizeNumberOfBytesWritten)) {
        break;
      }
      ReleaseMutex(hMutex);
      result = true;
    } break;

    case WAIT_ABANDONED:
      break;

    default:
      break;
    }
  } while (0);
  CloseHandle(hMutex);
  return result;
}
const std::wstring &VMem::GetSharedProcessMutexName() const {
  std::lock_guard<std::mutex> lck(*mtx_);
  return shared_process_mutex_name_;
}