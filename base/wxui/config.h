#if !defined(__94970427_2AD3_4804_AD53_04C283031943__)
#define __94970427_2AD3_4804_AD53_04C283031943__

enum CommandTool {
  BTN_SCALING_UP = 10001,
  BTN_SCALING_DOWN = 10002,
};

class Config final : public IConfig {
public:
  static Config *Get();
  static void Destroy();

private:
  Config();
  virtual ~Config();
  void Init();
  void UnInit();

protected:
  void SetFrameType(const FrameType &) override final;
  ITheme *CreateTheme() override final;

public:
  const FrameType &GetFrameType() const;
  const Theme *GetTheme(const wxui::tfThemeIdentify &identify = 0) const;
  wxImage *GetResImage(const std::string &imgName) const;

private:
  FrameType type_ = FrameType::FRAME;
  std::vector<Theme *> themes_;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
  std::map<std::string, wxImage *> imgres_;
};

/// /*_ Memade®（新生™） _**/
/// /*_ Thu, 28 Nov 2024 03:04:17 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__94970427_2AD3_4804_AD53_04C283031943__