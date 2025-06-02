#if !defined(__1E7A229B_290A_4E1D_A9CC_6B0B3C5BE0B7__)
#define __1E7A229B_290A_4E1D_A9CC_6B0B3C5BE0B7__
#if ENABLE_WXUI
class IBackground : public IFrame {
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
#endif
/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 02 Mar 2025 12:40:46 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__1E7A229B_290A_4E1D_A9CC_6B0B3C5BE0B7__
