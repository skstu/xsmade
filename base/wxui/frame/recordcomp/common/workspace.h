#if !defined(__7FC2B232_8D41_4E61_89A5_47DF6071326D__)
#define __7FC2B232_8D41_4E61_89A5_47DF6071326D__

class IWorkSpace : public wxFrame {
public:
  IWorkSpace(wxWindow *parent, wxWindowID id = wxID_ANY,
             const wxString &title = wxEmptyString,
             const wxPoint &pos = wxDefaultPosition,
             const wxSize &size = wxDefaultSize,
             long style = wxDEFAULT_FRAME_STYLE,
             const wxString &name = wxASCII_STR(wxFrameNameStr));
  virtual ~IWorkSpace();

protected:
  wxRect mouse_left_down_rect_;
  wxPoint mouse_left_down_point_;
  std::atomic_bool is_dragging_ = false;
  //!@ 拖动开关
  bool is_allow_move_ = true;
  //!@ 拉伸开关
  bool is_allow_stretch_ = true;
  //!@ 边框宽度
  int border_width_ = 5;
  int area_width_min_ = 200;
  int area_height_min_ = 200;
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
  void OnSize(wxSizeEvent &event);
  void OnClose(wxCloseEvent &event);
  void OnPaint(wxPaintEvent &event);
  void OnMove(wxMoveEvent &);
  void OnMouseMove(wxMouseEvent &event);
  void OnMouseLeftDown(wxMouseEvent &event);
  void OnMouseLeftUp(wxMouseEvent &event);
  wxDECLARE_EVENT_TABLE();
};

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 13 Dec 2024 05:15:53 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__7FC2B232_8D41_4E61_89A5_47DF6071326D__