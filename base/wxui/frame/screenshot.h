#if !defined(__F562BABA_EB45_4A2B_BF31_69B01EFF82E5__)
#define __F562BABA_EB45_4A2B_BF31_69B01EFF82E5__

class FrameScreenShot final : public IFrameComponent {
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

  protected:
    void LayoutEx() override final;
    void OnToolEvent(wxCommandEvent &event) override final;
    void OnToolbarSizeChanged(const wxRect &) override final;

  private:
    const int btn_size = 20;
    const int btn_offset_x_ = 20;
    const int btn_offset_y_ = 10;
    wxBitmapButton *btn_screenshot_toolbar_close_ = nullptr;
    wxBitmapButton *btn_screenshot_toolbar_edit_ = nullptr;
    wxBitmapButton *btn_screenshot_toolbar_ok_ = nullptr;
    wxBitmapButton *btn_screenshot_toolbar_rectangle_ = nullptr;
    wxBitmapButton *btn_screenshot_toolbar_revocation_ = nullptr;
    wxBitmapButton *btn_screenshot_toolbar_round_ = nullptr;
    wxBitmapButton *btn_screenshot_toolbar_text_ = nullptr;
    wxBitmapButton *btn_screenshot_toolbar_mosaic_ = nullptr;
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
    void OnWorkSpaceSizeChanged(const wxRect &) override final;
  };

public:
  FrameScreenShot();
  virtual ~FrameScreenShot();

private:
  void Init();
  void UnInit();

protected:
  void Show(const bool &flag) override final;
  void Center() const override final;
  void OnPosChanged() const override final {
  }
  void OnFullScreenShown() override final {
  }
  void OnWorkspacePosUpdate(const wxRect &) override final;
  void OnToolbarPosUpdate(const wxRect &) override final {
  }
  void SetPos(const wxRect &) override final;
  void ShowBackground(const bool &flag) override final;

private:
  Background *frame_background_ = nullptr;
  Toolbar *frame_toolbar_ = nullptr;
  WorkSpace *frame_workspace_ = nullptr;
};

/// /*_ Memade®（新生™） _**/
/// /*_ Thu, 12 Dec 2024 01:27:00 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__F562BABA_EB45_4A2B_BF31_69B01EFF82E5__