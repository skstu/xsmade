#if !defined(__7E6F1235_B1C6_494E_AA3B_3D1D6174F41E__)
#define __7E6F1235_B1C6_494E_AA3B_3D1D6174F41E__

enum class RunMode {
  kModelLevel0 = 0,
  kModelLevel1 = 1,
  kModelLevel2 = 2,
  kModelLevel3 = 3,
  kModeService = 4,

  kProductionModel = kModelLevel1,
  kNormalModel = kModelLevel0,
  kReleaseModel = kProductionModel,
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
#if 0
  void ChromiumClose();
  std::time_t GetChromiumStartTime() const;
#endif
  void NotifyRequestResult(const std::string &body);

  void Request(chromium::IRequest *);

  bool Ready() const;
private:
  void Init();
  void UnInit();
#if 0
  void ConfigureBegin();
  bool ConfigureEnd();
#endif
  bool ConfigDynamicInfo(const std::string &url, const std::string &proxyString,
                         chromium::xsiumio::IXSiumio &) const;

private:
  const RunMode mode_;
  std::atomic_bool ready_ = false;
  std::unique_ptr<std::mutex> mtx_ = std::make_unique<std::mutex>();
  IModel *model_ = nullptr;
  stl::container::queue<chromium::IRequest *> requests_;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 30 May 2025 00:05:44 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__7E6F1235_B1C6_494E_AA3B_3D1D6174F41E__