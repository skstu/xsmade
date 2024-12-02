#if !defined(__13E25DEC_AE9B_4A29_9116_A25BBA35DA21__)
#define __13E25DEC_AE9B_4A29_9116_A25BBA35DA21__

class FrameBgk final : public FrameBase {
public:
  FrameBgk(wxWindow *parent, wxWindowID id = wxID_ANY,
           const wxString &title = wxEmptyString,
           const wxPoint &pos = wxDefaultPosition,
           const wxSize &size = wxDefaultSize,
           long style = wxDEFAULT_FRAME_STYLE,
           const wxString &name = wxASCII_STR(wxFrameNameStr));
  virtual ~FrameBgk();

private:
  void OnSize(wxSizeEvent &event);
  void OnClose(wxCloseEvent &event);
  void OnMouseMove(wxMouseEvent &event);
  void OnMouseLeftDown(wxMouseEvent &event);
  void OnMouseLeftUp(wxMouseEvent &event);
  void OnPaint(wxPaintEvent &event);

  wxPoint startPoint_;               // 鼠标按下时的坐标
  wxPoint endPoint_;                 // 鼠标抬起时的坐标
  std::atomic_bool drawing_ = false; // 标记是否正在绘制

  wxDECLARE_EVENT_TABLE();
};
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 30 Nov 2024 02:58:06 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__13E25DEC_AE9B_4A29_9116_A25BBA35DA21__