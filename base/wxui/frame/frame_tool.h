#if !defined(__00E6354C_3D16_4C11_8AAF_51ED98E1BD3A__)
#define __00E6354C_3D16_4C11_8AAF_51ED98E1BD3A__

class FrameTool final : public FrameBase {
public:
  FrameTool(wxWindow *parent, wxWindowID id = wxID_ANY,
               const wxString &title = wxEmptyString,
               const wxPoint &pos = wxDefaultPosition,
               const wxSize &size = wxDefaultSize,
               long style = wxDEFAULT_FRAME_STYLE,
               const wxString &name = wxASCII_STR(wxFrameNameStr));
  virtual ~FrameTool();

private:
  void LayoutEx();
  wxSize prev_frame_tool_size_;
  wxSize prev_frame_work_size_;
  wxPoint m_delta;
  void OnSize(wxSizeEvent &);
  void OnClose(wxCloseEvent &);
  void OnMove(wxMoveEvent &);
  void OnMouseMove(wxMouseEvent &event);
  void OnMouseLeftDown(wxMouseEvent &event);
  void OnMouseLeftUp(wxMouseEvent &event);
  void OnMouseLeftDClick(wxMouseEvent &event);
  void OnToolEvent(wxCommandEvent &event);
  DECLARE_EVENT_TABLE()
private:
  const int btn_size = 20;
  const int btn_offset_x_ = 20;
  const int btn_offset_y_ = 10;
  wxBitmapButton *btn_close_ = nullptr;
  wxBitmapButton *btn_edit_ = nullptr;
  wxBitmapButton *btn_screenshot_ = nullptr;
  wxBitmapButton *btn_scaling_up_ = nullptr;
  wxBitmapButton *btn_scaling_down_ = nullptr;
  wxBitmapButton *btn_settings_ = nullptr;
  wxBitmapButton *btn_recording_start_ = nullptr;
  wxBitmapButton *btn_recording_stop_ = nullptr;
  wxBitmapButton *btn_window_ = nullptr;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 29 Nov 2024 02:19:20 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__00E6354C_3D16_4C11_8AAF_51ED98E1BD3A__
