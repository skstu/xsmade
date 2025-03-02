#if !defined(__ECD4F1B0_06AF_482B_874C_BDFAB464137F__)
#define __ECD4F1B0_06AF_482B_874C_BDFAB464137F__

class IBackground : public wxFrame {
public:
  IBackground(wxWindow *parent, wxWindowID id = wxID_ANY,
              const wxString &title = wxEmptyString,
              const wxPoint &pos = wxDefaultPosition,
              const wxSize &size = wxDefaultSize,
              long style = wxDEFAULT_FRAME_STYLE,
              const wxString &name = wxASCII_STR(wxFrameNameStr));
  virtual ~IBackground();

protected:
  //!@ 拖动开关
  std::atomic_bool is_allow_move_ = false;
  //!@ 拉伸开关
  std::atomic_bool is_allow_stretch_ = false;
  //!@ 画边框
  std::atomic_bool is_draw_border_ = false;
  
  //!@ 边框宽度
  int border_width_ = 5;
  int area_width_min_ = 200;
  int area_height_min_ = 200;

protected:
  wxRect mouse_left_down_rect_;
  wxPoint mouse_left_down_point_;
  std::atomic_bool is_dragging_ = false;

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

protected:
  virtual void OnWorkSpaceSizeChanged(const wxRect &) {
  }

protected:
  virtual void OnSize(wxSizeEvent &event);
  void OnClose(wxCloseEvent &event);
  virtual void OnPaint(wxPaintEvent &event);
  virtual void OnMove(wxMoveEvent &);
  virtual void OnMouseMove(wxMouseEvent &event);
  virtual void OnMouseLeftDown(wxMouseEvent &event);
  virtual void OnMouseLeftUp(wxMouseEvent &event);
  virtual void OnEraseBackground(wxEraseEvent &event);
  wxDECLARE_EVENT_TABLE();
};

/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 05 Feb 2025 01:35:03 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__ECD4F1B0_06AF_482B_874C_BDFAB464137F__