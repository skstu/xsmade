#if !defined(__DBF6427B_81A7_4A73_8F2F_DED725E368A4__)
#define __DBF6427B_81A7_4A73_8F2F_DED725E368A4__
enum class ModeType { kMode0 = 0, kMode1 = 1, kMode2 = 2, kMode3 = 3 };
class IModel {
protected:
  IModel();
  virtual ~IModel();

private:
  void Init();
  void UnInit();

public:
  virtual bool LoadModelParts();
  virtual void FinishModelParts();
  virtual bool Ready() const;
  virtual void Release() const = 0;
  virtual bool GenModel(const chromium::xsiumio::IXSiumio &) = 0;
  virtual const char *GetModelIdentify() const = 0;
  virtual void SetModelResult(const bool &);
  virtual bool GetModelResult() const;
  virtual void SetModelCache(const std::string &);
  virtual const std::string &GetBridgeStartupArgs() const;

public:
  const chromium::xsiumio::IXSiumio &GetXSCfg() const;

protected:
  virtual void Output(const chromium::xsiumio::IXSiumio &) const;
  virtual void LoadXSCfg();
  virtual void SaveXSCfg();
  virtual void Super();
  virtual void SettingBridgeProxy();
  virtual bool LaunchBrowser(const chromium::xsiumio::tfIdentifyType &);
  virtual bool ShutdownBrowser(const chromium::xsiumio::tfIdentifyType &);
  virtual const ModeType &GetModeType() const = 0;

protected:
  std::atomic_bool ready_ = false;
  std::vector<std::string> proxys_;
  std::map<std::uint64_t, chromium::xsiumio::IXSiumio> xsiumios_;
  std::unique_ptr<std::mutex> mtx_ = std::make_unique<std::mutex>();
  std::atomic_bool model_result_ = false;
  std::string model_cache_;
  chromium::tfRouteRes model_ress_;
  chromium::xsiumio::IFpsdb fpsdb_;
  std::atomic_bool model_parts_updated_ = true;
  std::atomic_size_t signal_proxy_use_count_ = 0;
  std::string bridge_startup_args_;
  chromium::xsiumio::IXSiumio xscfg_;
  ModeType mode_type_ = ModeType::kMode0;
};
class ModelLevel0 final : public IModel {
public:
  ModelLevel0();
  ~ModelLevel0();
  void Release() const override final;

protected:
  const ModeType &GetModeType() const override final;
  const char *GetModelIdentify() const override final;
  bool GenModel(const chromium::xsiumio::IXSiumio &) override final;

private:
};
#if 0
class ModelLevel1 final : public IModel {
public:
  ModelLevel1();
  ~ModelLevel1();
  void Release() const override final;

protected:
  bool GetProxyInfo(chromium::xsiumio::IXSiumio &,
                    std::string &chromiumProxyUrl, std::string &curlProxyUrl,
                    const bool &useCache) override final;
  bool GetModel(chromium::xsiumio::IXSiumio &) override final;
  const char *GetModelIdentify() const override final;

private:
};
class ModelLevel2 final : public IModel {
public:
  ModelLevel2();
  ~ModelLevel2();
  void Release() const override final;

protected:
  bool GetProxyInfo(chromium::xsiumio::IXSiumio &,
                    std::string &chromiumProxyUrl, std::string &curlProxyUrl,
                    const bool &useCache) override final;
  bool GetModel(chromium::xsiumio::IXSiumio &) override final;
  const char *GetModelIdentify() const override final;
};
class ModelLevel3 final : public IModel {
public:
  ModelLevel3();
  ~ModelLevel3();
  void Release() const override final;

protected:
  bool GetModel(chromium::xsiumio::IXSiumio &) override final;
  const char *GetModelIdentify() const override final;
  bool GetProxyInfo(chromium::xsiumio::IXSiumio &,
                    std::string &chromiumProxyUrl, std::string &curlProxyUrl,
                    const bool &useCache) override final;
  const std::string &GetBridgeStartupArgs() const override final;
};
#endif
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 26 Jul 2025 13:07:17 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__DBF6427B_81A7_4A73_8F2F_DED725E368A4__