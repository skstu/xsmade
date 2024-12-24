#if !defined(__F4271202_5D80_4C2C_80BC_F6432B0236C7__)
#define __F4271202_5D80_4C2C_80BC_F6432B0236C7__

enum class FrameComponentType : unsigned long long {
  UNDEFINED = 0x00,
  SCREENSHOT = 0x01,
  RECORDING = 0x02,
};
enum class ComponentFrameType : unsigned long long {
  UNKNOWN = 0x00,
  SCREENSHOT_TOOLBAR = 0x0110,
  SCREENSHOT_TOOLBAR_FONT = 0x0111,
  SCREENSHOT_WORKSPACE = 0x0120,
  SCREENSHOT_WORKSPACE_INPUT = 0x0121,
  SCREENSHOT_BACKGROUND = 0x0130,
  RECORDING_TOOLBAR = 0x0210,
  RECORDING_WORKSPACE = 0x0220,
  RECORDING_BACKGROUND = 0x0230,
};

class IFrameComponent {
public:
  IFrameComponent(const FrameComponentType &);
  virtual const FrameComponentType &Type() const;
  virtual void Show(const bool &flag) = 0;
  virtual void ShowBackground(const bool &flag) = 0;
  virtual void Center() const = 0;
  virtual void SetPos(const wxRect &) {
  }
  virtual void OnPosChanged() const = 0;
  virtual void OnFullScreenShown() = 0;
  virtual void OnWorkspacePosUpdate(const wxRect &) = 0;
  virtual void OnToolbarPosUpdate(const wxRect &) = 0;
  virtual wxRect GetRegion() const = 0;
  virtual void SetWorkSpace(const std::string &imageStream) {
  }

protected:
  const FrameComponentType type_;
  std::atomic_bool show_status_ = false;
};

/// /*_ Memade®（新生™） _**/
/// /*_ Thu, 12 Dec 2024 02:38:09 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__F4271202_5D80_4C2C_80BC_F6432B0236C7__