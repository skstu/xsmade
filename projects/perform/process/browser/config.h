#if !defined(__918F8A06_5054_4610_918C_97CFBD43D91B__)
#define __918F8A06_5054_4610_918C_97CFBD43D91B__

class BrowserConfig final : public IConfig {
public:
  class Paths {
  public:
    std::string root_dir;                // "${AppData}/MarsProjects/"
    std::string logs_dir;                // "/logs/"
    std::string chromium_dir;            // "/chromium/"
    std::string chromium_user_data_dir;  // "/userdata/"
    std::string chromium_extensions_dir; // "/chromium/extensions/"
    std::string brw_projects_route_file; // "${AppData}/MarsProjects/route.json"
    std::string
        brw_projects_configure_file; // "${AppData}/MarsProjects/configure.json"
    std::string configure_dir;       // "/configure/"
    std::string plugins_dir;         // "/plugins/"
    std::string components_dir;      // "/components/"
    std::string resources_dir;       // "/resources/"
  };
  class Settings {
  public:
    class Developer {
    public:
      bool enable = false;
    };

  public:
    Settings();
    ~Settings();

  public:
    Developer developer;
    bool enable_logger = false;
  };

public:
  BrowserConfig();
  virtual ~BrowserConfig();

private:
  void Init();
  void UnInit();
  void PathsInit();
  void SettingsInit();

public:
  void RouteConfigureInit(const unsigned int &) const;
  unsigned int RouteConfigureGetClientPort() const;
  const Paths &PathGet() const;
  std::string GetBrwUserDataDir(const std::string &brwKey) const;
  std::string GetXSCacheExtsDir(const std::string &brwKey) const;
  std::string GetXSCacheExtsDir(const std::string &brwKey,
                                const std::string &extId) const;
  std::string GetXSCacheCfgsDir(const std::string &brwKey) const;
  std::string GetXSCacheStatisDir(const std::string &brwKey) const;
  std::string GetXSCacheConfigureFName(const std::string &brwKey) const;
  void XSCacheClean(const std::string &brwKey) const;
  const Settings &GetSettings() const;

public:
  static std::string CreateBrwCloseNotifyPak(const std::string &brwId);

private:
  Paths paths_;
  std::string current_process_path_;
  std::string work_projects_path_;
  std::string chromium_path_;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
  Settings settings_;

public:
  const std::string project_name_ = "MarsProjects";

protected:
  void __impl__() const override final {}
};

/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 11 Nov 2024 09:56:50 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__918F8A06_5054_4610_918C_97CFBD43D91B__