#if !defined(__180824B0_BEE4_4DAB_9045_3ADCA77AD0B2__)
#define __180824B0_BEE4_4DAB_9045_3ADCA77AD0B2__

class IChromium final {
  friend class Browser;

private:
  IChromium(const chromium::xsiumio::IXSiumio &);
  virtual ~IChromium();
  void Release() const;

public:
  const xs_process_id_t &GetPid() const;
  const BrowserStatus &GetStatus() const;
  void Request(const std::string &);
  const int &GetPort() const;
  const chromium::xsiumio::tfIdentifyType &GetIdentify() const;
  void SetBridgePid(const xs_process_id_t &pid);

private:
  bool Open();
  void Close();

  void SetStatus(const BrowserStatus &status);
  bool NotifyResult(const chromium::xsiumio::IXSiumio &);
  const xs_process_id_t &GetBridgePid() const;

private:
  chromium::xsiumio::IXSiumio configure_;
  const chromium::xsiumio::tfIdentifyType identify_;
  xs_process_id_t pid_ = 0;
  int port_ = 0;
  xs_process_id_t bridgePid_ = 0;
  BrowserStatus status_ = BrowserStatus::kUnknown;
  const time_t start_time_ = stl::Time::TimeStamp<std::chrono::seconds>();
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};

/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 31 May 2025 04:27:39 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__180824B0_BEE4_4DAB_9045_3ADCA77AD0B2__