#if !defined(__94970427_2AD3_4804_AD53_04C283031943__)
#define __94970427_2AD3_4804_AD53_04C283031943__

enum CommandTool {
  TOOL_SCALING_UP = 10001,
  TOOL_SCALING_DOWN = 10002,
  TOOL_WINDOW = 10003,
  TOOL_SYSTEM_CLOSE = 10004,
  EVT_COMMAND_CAPTURE_FINISHED = 10005,
  TOOL_SCREENSHOT = 10006,
  TOOL_SETTINGS = 10007,
  TOOL_RECORDING_START = 10008,
  TOOL_RECORDING_STOP = 10009,
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
  void SetResourceDir(const char *) override final;
  void RegisterRecordingStartCb(tfRecordingStartCb, void *) override final;
  void RegisterRecordingStopCb(tfRecordingStopCb, void *) override final;
  void RegisterSystemExitCb(tfSystemExitCb, void *) override final;

public:
  const FrameType &GetFrameType() const;
  const Theme *GetTheme(const wxui::tfThemeIdentify &identify = 0) const;
  wxImage *GetResImage(const std::string &imgName) const;
  void OnRecordingStart(const IRecordingArgs *) const;
  void OnRecordingStop() const;
  void OnSystemExit() const;
private:
  FrameType type_ = FrameType::FRAME;
  std::vector<Theme *> themes_;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
  std::map<std::string, wxImage *> imgres_;
  std::string resource_dir_;
  tfRecordingStartCb recording_start_cb_ = nullptr;
  void *recording_start_cb_route_ = nullptr;
  tfRecordingStopCb recording_stop_cb_ = nullptr;
  void *recording_stop_cb_route_ = nullptr;
  tfSystemExitCb system_exit_cb_ = nullptr;
  void *system_exit_cb_route_ = nullptr;
};

extern std::map<CommandTool, wxString> gpCommandToolTipMap;
/// /*_ Memade®（新生™） _**/
/// /*_ Thu, 28 Nov 2024 03:04:17 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__94970427_2AD3_4804_AD53_04C283031943__