#if !defined(__CDA0FE42_5C23_4350_89DE_6EE9A7004DB7__)
#define __CDA0FE42_5C23_4350_89DE_6EE9A7004DB7__

class Config final {
public:
  class Path final {
  public:
    Path() = default;
    ~Path() = default;

  public:
    std::u16string root;
    std::u16string module_name;
    std::u16string logs_dir;
    std::u16string temp_dir;
    std::u16string configure_path;
    std::u16string chromium_cache_dir;
    std::u16string settings_path;
    std::u16string libuvpp_path;
    std::u16string components_dir;
    std::u16string chromium_userdata_dir;
    std::u16string chromium_userenv_dir;
    std::u16string configure_cache_dir;
    std::u16string configure_cache_path;
    std::u16string chromium_envpath_route_path;
  };

public:
  static Config *GetOrCreate();
  static void Destroy();

private:
  Config();
  virtual ~Config();

private:
  void Init();
  void UnInit();

public:
  const brwcfg::ISettings &GetSettings() const;
  const chromium::IConfigure &GetConfigure() const;
  const Path &GetPath() const;

private:
  Path path_;
  brwcfg::ISettings *settings_ = nullptr;
  chromium::IConfigure *configure_ = nullptr;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 22 Feb 2025 05:04:36 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__CDA0FE42_5C23_4350_89DE_6EE9A7004DB7__