#if !defined(__CDAE60E5_071A_4C79_B230_D16638956D91__)
#define __CDAE60E5_071A_4C79_B230_D16638956D91__
#define ENABLE_FFCODEC 0
class Config final {
public:
  class Path final {
  public:
    std::u16string root_dir;
    std::u16string current_dir;
    std::u16string libuvpp_path;
    std::u16string configure_path;
    std::u16string settings_path;
    std::u16string browser_dir;
    std::u16string chromium_dir;
    std::u16string temp_dir;
    std::u16string cache_dir;
    std::u16string logs_path;

  private:
    friend class Config;
    Path() = default;
    ~Path() = default;
    void init(void);
  };

public:
  static Config *GetOrCreate();
  static void Destroy();

private:
  Config();
  ~Config();

private:
  void Init();
  void UnInit();

public:
  bool CreateBrowserEnv(const browser_id_t &, const std::string &buffer) const;
  std::u16string GetChromiumUserDataDir(const browser_id_t &) const;
  std::u16string GetChromiumUserEnvDir(const browser_id_t &) const;
  const brwcfg::IConfigure &GetDefaultConfigure(void) const;
  const brwcfg::ISettings &GetSettings(void) const;
  const Path &GetPath(void) const;
  std::u16string GetChrome(const std::string &brwver = "" /*default*/) const;

private:
  Path path_;
  std::map<std::string /*brwver*/, std::u16string /*brwexepath*/> chromes_;
  brwcfg::ISettings *settings_ = nullptr;
  brwcfg::IConfigure *default_configure_ = nullptr;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};
/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 14 Mar 2025 22:12:25 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__CDAE60E5_071A_4C79_B230_D16638956D91__