#if !defined(__7E6F1235_B1C6_494E_AA3B_3D1D6174F41E__)
#define __7E6F1235_B1C6_494E_AA3B_3D1D6174F41E__

enum class RunMode {
  kTrainingModel,
  kNormalModel,
  kReleaseModel,
  kAppModel,
  kProductionModel,
};

class Startup {
public:
  static Startup *GetOrCreate(const RunMode &mode = RunMode::kNormalModel);
  static void Destroy();

private:
  ~Startup();
  Startup(const RunMode &mode = RunMode::kNormalModel);

public:
  void Run();
  void ChromiumClose();
  std::time_t GetChromiumStartTime() const;
  void NotifyRequestResult(const std::string &body);

private:
  void Init();
  void UnInit();
  bool OpenChrome();
  void Configure();
  void ConfigureRelease();
  void GenerateDynamicProxyInfo(std::string &curl, std::string &chromium) const;
  bool ConfigDynamicInfo(const std::string &url,
                         const std::string &proxyString);

private:
  const RunMode mode_;
  std::atomic_bool ready_ = false;
  Server *server_ = nullptr;
  std::atomic<xs_process_id_t> chromium_main_pid_ = 0;
  std::time_t chromium_start_time_ = 0;
  const std::time_t chromium_timeout_ = 60; //!@ seconds
  IComponent *pComponentCurl_ = nullptr;
  chromium::xsiumio::IXSiumio xsiumio;
  std::unique_ptr<std::mutex> mtx_ = std::make_unique<std::mutex>();
  IModel* model_ = nullptr;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 30 May 2025 00:05:44 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__7E6F1235_B1C6_494E_AA3B_3D1D6174F41E__