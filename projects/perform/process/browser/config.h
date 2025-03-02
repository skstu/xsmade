#if !defined(__918F8A06_5054_4610_918C_97CFBD43D91B__)
#define __918F8A06_5054_4610_918C_97CFBD43D91B__

class BrowserConfig final : public IConfig {
public:
  class Paths {
  public:
    std::u16string root_dir;                // "${AppData}/FanOffice/"
    std::u16string logs_dir;                // "/logs/"
    std::u16string chromium_dir;            // "/chromium/"
    std::u16string firefox_dir;              // "/firefox/"                                        
    std::u16string chromium_user_data_dir;  // "/userdata/"
    std::u16string chromium_extensions_dir; // "/chromium/extensions/"
    std::u16string brw_projects_route_file; // "${AppData}/FanOffice/route.json"
    std::u16string brw_projects_route2_file;// "./configure/clientInfo.json"
    std::u16string
        brw_projects_configure_file; // "${AppData}/FanOffice/configure.json"
    std::u16string configure_dir;    // "/configure/"
    std::u16string plugins_dir;      // "/plugins/"
    std::u16string components_dir;   // "/components/"
    std::u16string resources_dir;    // "/resources/"
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
  bool IsDevMode() const;
  void RouteConfigureInit(const unsigned int &) const;
  unsigned int RouteConfigureGetClientPort();
  const Paths &PathGet() const;
  std::u16string GetBrwUserDataDir(const std::u16string &brwKey) const;
  std::u16string GetXSCacheExtsDir(const std::u16string &brwKey) const;
  std::u16string GetXSCacheExtsDir(const std::u16string &brwKey,
                                   const std::u16string &extId) const;
  std::u16string GetXSCacheRouteReqsDir(const std::u16string &brwKey) const;
  std::u16string GetXSCacheRouteRepsDir(const std::u16string &brwKey) const;
  std::u16string GetXSCacheCfgsDir(const std::u16string &brwKey) const;
  std::u16string GetXSCacheStatisDir(const std::u16string &brwKey) const;
  std::u16string GetXSCacheConfigureFName(const std::u16string &brwKey) const;
  void XSCacheClean(const std::u16string &brwKey) const;
  const Settings &GetSettings() const;

  unsigned int GetClientPortCache() const;

  bool GetWindowsAccountInfo(std::wstring &sid, std::wstring &computer_name,
                             std::wstring &user_name,
                             const bool &full_sid = false) const;
  std::string GetLocalMachineAllNetWorkCardMAC(std::set<std::string> &macs,
                                               const char &space = 0,
                                               const bool &lower = false) const;
  std::string GetIPAddr(const bool &rereq = false);
  std::string GetLocalIPAddr(const bool &rereq = false);
  const std::set<std::string> &GetMACs() const;

public:
  static std::string CreateBrwCloseNotifyPak(const std::u16string &brwId);
  static std::string CreateBrwCookiesNotifyPak(const std::u16string &brwId,
                                               const std::string &cookies);

private:
  std::string ipaddr_;
  std::string ipaddr_local_;
  std::set<std::string> macs_;
  std::atomic_uint client_port_cache_ = 0;
  Paths paths_;
  std::u16string current_process_path_;
  std::u16string work_projects_path_;
  std::u16string chromium_path_;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
  Settings settings_;

public:
  const std::u16string project_name_ = u"FanOffice";

protected:
  void __impl__() const override final {
  }
};

/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 11 Nov 2024 09:56:50 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__918F8A06_5054_4610_918C_97CFBD43D91B__