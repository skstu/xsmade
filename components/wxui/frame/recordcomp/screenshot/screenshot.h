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

  private:
    void Init();
    void UnInit();

  public:
    void GetExpandToolbar(wxPanel **outPanel,
                          wxBoxSizer **outSizer) override final;
    void RefreshToolbar() override final;

  protected:
    void OnLayout() override final;
    void OnToolEvent(wxCommandEvent &event) override final;
    void OnToolbarSizeChanged(const wxRect &) override final;

  private:
    wxPanel *panel = nullptr;
    wxBoxSizer *sizer = nullptr;
    wxBoxSizer *sizer_top = nullptr;
    wxBoxSizer *sizer_expand = nullptr;
    const wxSize btn_scale_size_ = {20, 20};
    const wxSize btn_size_ = {40, 40};
  };
  class FontToolbar final : public IToolbar {
  public:
    FontToolbar(wxWindow *parent, wxWindowID id = wxID_ANY,
                const wxString &title = wxEmptyString,
                const wxPoint &pos = wxDefaultPosition,
                const wxSize &size = wxDefaultSize,
                long style = wxDEFAULT_FRAME_STYLE,
                const wxString &name = wxASCII_STR(wxFrameNameStr));
    virtual ~FontToolbar();

  protected:
    void OnLayout() override final;
    void OnToolEvent(wxCommandEvent &event) override final;
    void OnToolbarSizeChanged(const wxRect &) override final;

  private:
    wxArrayString m_arrItems_pixel;
    wxArrayString m_arrItems_font;
    const int btn_size = 20;
    const int btn_offset_x_ = 20;
    const int btn_offset_y_ = 10;
    // wxBitmapButton *btn_screenshot_toolbar_close_ = nullptr;
    // wxBitmapButton *btn_screenshot_toolbar_edit_ = nullptr;
  };
  class WorkSpace final : public IWorkSpace {
  public:
    class TextInputCtrl : public wxRichTextCtrl {
    public:
      TextInputCtrl(const wxBitmap &bgnImg, wxWindow *parent,
                    const wxPoint &pos = wxDefaultPosition,
                    const wxSize &size = wxDefaultSize,
                    const wxString &value = wxT(""), wxWindowID id = wxID_ANY,
                    long style = wxTE_MULTILINE | wxBORDER_NONE |
                                 wxTE_NO_VSCROLL);
      virtual ~TextInputCtrl();

    public:
      bool IsTextEmtpy() const;
    protected:
      void OnPaint(wxPaintEvent &evt);
      void OnSize(wxSizeEvent &evt);
      void OnMove(wxMoveEvent &evt);
      void OnMouseMove(wxMouseEvent &evt);
      void OnMouseLeftDown(wxMouseEvent &evt);
      void OnMouseLeftUp(wxMouseEvent &evt);
      void OnEraseBackground(wxEraseEvent &evt);
      void OnMouseCaptureLost(wxMouseCaptureLostEvent &evt);
      void OnTextChanged(wxCommandEvent &event);

    private:
      void SetCustomCaret();
      void OnBackgroundUpdate();
    private:
      wxCoord text_width_;
      wxCoord text_height_;
      wxBitmap background_dest_;
      const wxBitmap background_src_;
      wxRect mouse_left_down_rect_;
      wxPoint mouse_left_down_point_;
      std::atomic_bool is_dragging_ = false;
      std::atomic_bool is_allow_move_ = true;
      enum class ResizeMode {
        None,
        Left,
        Right,
        Top,
        Bottom,
        LeftTop,
        RightTop,
        LeftBottom,
        RightBottom
      };

      std::atomic<ResizeMode> resize_mode_ = ResizeMode::None;
    };

  public:
    WorkSpace(wxWindow *parent, wxWindowID id = wxID_ANY,
              const wxString &title = wxEmptyString,
              const wxPoint &pos = wxDefaultPosition,
              const wxSize &size = wxDefaultSize,
              long style = wxDEFAULT_FRAME_STYLE,
              const wxString &name = wxASCII_STR(wxFrameNameStr));
    virtual ~WorkSpace();

  public:
    void DrawSave();
    void SetImage(const wxImage *, const bool &cache = true);

  protected:
    void OnDrawToolbar(wxCommandEvent &);
    void OnWorkSpaceSizeChanged(const wxRect &) override final;
    void OnScreenShot(wxCommandEvent &);
  protected:
    void OnSize(wxSizeEvent &) override final;
    void OnPaint(wxPaintEvent &) override final;
    void OnMove(wxMoveEvent &) override final;
    void OnMouseMove(wxMouseEvent &event) override final;
    void OnMouseLeftDown(wxMouseEvent &event) override final;
    void OnMouseLeftUp(wxMouseEvent &event) override final;
    void OnEraseBackground(wxEraseEvent &event) override final;

  private:
    bool OnUserDraw(const wxMouseEvent &evt);

  private:
    wxOverlay overlay_;
    wxPoint draw_point_begin_;
    wxPoint draw_point_end_;
    std::atomic<CommandTool> draw_mode_ = CommandTool::TOOL_NULL;
    stl::container::list<std::tuple<CommandTool, std::vector<wxPoint>>>
        draw_cache_;
    stl::container::list<wxImage *> draw_success_cache_;
    stl::container::list<wxPoint> draw_arbitrary_cache_;
    stl::container::list<wxPoint> draw_mosaic_cache_;
    stl::container::list<TextInputCtrl *> draw_text_cache_;
    wxBitmap *backgroundBitmap_ = nullptr;
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
  wxRect GetRegion() const override final;
  void SetWorkSpace(const std::string &imageStream) override final;

private:
  Background *frame_background_ = nullptr;
  Toolbar *frame_toolbar_ = nullptr;
  FontToolbar *font_toolbar_ = nullptr;
  WorkSpace *frame_workspace_ = nullptr;
};

/// /*_ Memade®（新生™） _**/
/// /*_ Thu, 12 Dec 2024 01:27:00 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__F562BABA_EB45_4A2B_BF31_69B01EFF82E5__