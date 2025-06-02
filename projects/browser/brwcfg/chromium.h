#if !defined(__C44D8EFE_09E4_440E_A764_9915D43B3B0D__)
#define __C44D8EFE_09E4_440E_A764_9915D43B3B0D__

class IChromium {
public:
  IChromium(const ChromiumProcessType &type, const std::string &server_addr);

private:
  void Init();
  void UnInit();

public:
  virtual bool Start();
  virtual void Stop();
  virtual void Release() const = 0;
  virtual const ChromiumProcessType &GetType() const;
  virtual void OnGpuScreenshotImageStream(const char *stream,
                                          const size_t &stream_size) {
  }
  virtual void OnChromiumInputEvent(
      const unsigned long long &reqid,
      const chromium::IConfigure::Input::ResultCode &resultCode) const {
  }

protected:
  ~IChromium();
  virtual void Process();
  const ChromiumProcessType type_;
  const std::string server_addr_;
  policy_id_t policy_id_ = 0;
  std::atomic_bool ready_ = false;
  std::atomic_bool open_ = false;
  IUvpp *uvpp_ = nullptr;
  uvpp::IConfig *uvpp_config_ = nullptr;
  IService *uvpp_client_ = nullptr;
  stl::tfThreads threads_;
  stl::container::queue<std::string> write_cache_;
};

class ChromiumMain final : public IChromium {
public:
  ChromiumMain(const std::string &server_addr);
  ~ChromiumMain();

private:
  void Init();
  void UnInit();

protected:
  void Release() const override final;
  void OnChromiumInputEvent(const unsigned long long &reqid,
                            const chromium::IConfigure::Input::ResultCode
                                &resultCode) const override final;
};

class ChromiumGpu final : public IChromium {
public:
  ChromiumGpu(const std::string &server_addr);
  ~ChromiumGpu();

private:
  void Init();
  void UnInit();

protected:
  void Process() override final;
  void Release() const override final;
  void OnGpuScreenshotImageStream(const char *stream,
                                  const size_t &stream_size) override final;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 22 Mar 2025 04:58:29 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__C44D8EFE_09E4_440E_A764_9915D43B3B0D__