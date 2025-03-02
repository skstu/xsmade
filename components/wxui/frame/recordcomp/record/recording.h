#if !defined(__F045CF09_0540_4C2D_8103_5B07E9A45269__)
#define __F045CF09_0540_4C2D_8103_5B07E9A45269__

class FrameRecording final : public IFrameComponent {
public:
  class Background final : public IBackground {
  public:
    Background(wxWindow *parent, wxWindowID id = wxID_ANY,
               const wxString &title = wxEmptyString,
               const wxPoint &pos = wxDefaultPosition,
               const wxSize &size = wxDefaultSize,
               long style = wxDEFAULT_FRAME_STYLE,
               const wxString &name = wxASCII_STR(wxFrameNameStr));
    virtual ~Background();
  };
  class Toolbar final : public IToolbar {
  public:
    Toolbar(wxWindow *parent, wxWindowID id = wxID_ANY,
            const wxString &title = wxEmptyString,
            const wxPoint &pos = wxDefaultPosition,
            const wxSize &size = wxDefaultSize,
            long style = wxDEFAULT_FRAME_STYLE,
            const wxString &name = wxASCII_STR(wxFrameNameStr));
    virtual ~Toolbar();

  private:
    void Init();
    void UnInit();
    const wxSize btn_scale_size_ = {20, 20};
    const wxSize btn_size_ = {40, 40};

  protected:
    void OnToolEvent(wxCommandEvent &event) override;
    void OnFullScreenShown() override;
    void OnLayout() override;
    void OnToolbarSizeChanged(const wxRect &) override;
    void OnClose(wxCloseEvent &event) override final;

  protected:
    const int btn_size = 20;
    const int btn_offset_x_ = 20;
    const int btn_offset_y_ = 10;
    wxBitmapButton *btn_close_ = nullptr;
    wxBitmapButton *btn_edit_ = nullptr;
    wxBitmapButton *btn_screenshot_ = nullptr;
    wxBitmapButton *btn_screenshot_edit_ = nullptr;
    wxBitmapButton *btn_scaling_up_ = nullptr;
    wxBitmapButton *btn_scaling_down_ = nullptr;
    wxBitmapButton *btn_settings_ = nullptr;
    wxBitmapButton *btn_recording_start_ = nullptr;
    wxBitmapButton *btn_recording_stop_ = nullptr;
    wxBitmapButton *btn_window_ = nullptr;
  };
  class WorkSpace final : public IWorkSpace {
  public:
    WorkSpace(wxWindow *parent, wxWindowID id = wxID_ANY,
              const wxString &title = wxEmptyString,
              const wxPoint &pos = wxDefaultPosition,
              const wxSize &size = wxDefaultSize,
              long style = wxDEFAULT_FRAME_STYLE,
              const wxString &name = wxASCII_STR(wxFrameNameStr));
    virtual ~WorkSpace();

  protected:
    void OnWorkSpaceSizeChanged(const wxRect &) override;
  };

public:
  FrameRecording();
  ~FrameRecording();

private:
  void Init();
  void UnInit();

protected:
  void Show(const bool &flag) override final;
  void Center() const override final;
  void OnPosChanged() const override final;
  void OnFullScreenShown() override final;
  void ShowBackground(const bool &flag) override final;
  void OnWorkspacePosUpdate(const wxRect &) override final;
  void OnToolbarPosUpdate(const wxRect &) override final;
  wxRect GetRegion() const override final;
  void SetPos(const wxRect &) override final;

private:
  Background *frame_background_ = nullptr;
  Toolbar *frame_toolbar_ = nullptr;
  WorkSpace *frame_workspace_ = nullptr;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Thu, 12 Dec 2024 01:55:59 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__F045CF09_0540_4C2D_8103_5B07E9A45269__