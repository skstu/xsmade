#if !defined(__9EA4192E_3567_493D_94AD_6403DF9F34E8__)
#define __9EA4192E_3567_493D_94AD_6403DF9F34E8__
#if ENABLE_VMEM
class VMem final {
public:
  VMem();
  ~VMem();

public:
  const HANDLE &GetHandle() const;
  bool Write(const std::string &) const;
  const void *GetBase() const;
  const std::wstring &GetSharedProcessMutexName() const;
  const unsigned long &GetCurrentPid() const;

private:
  void Init();
  void UnInit();

private:
  unsigned long current_pid_ = 0;
  std::wstring shared_process_mutex_name_;
  void *base_ = nullptr;
  HANDLE handle_ = nullptr;
  const size_t total_ = 1024ull * 1024ull * 1024ull * 128ull;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};
#endif
/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 14 Mar 2025 08:08:02 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__9EA4192E_3567_493D_94AD_6403DF9F34E8__