#if !defined(__5DC5638E_C7E9_463C_A551_3645FBD34867__)
#define __5DC5638E_C7E9_463C_A551_3645FBD34867__

class FrameToolScreenShot final : public FrameBase {
public:
  FrameToolScreenShot(wxWindow *parent, wxWindowID id = wxID_ANY,
            const wxString &title = wxEmptyString,
            const wxPoint &pos = wxDefaultPosition,
            const wxSize &size = wxDefaultSize,
            long style = wxDEFAULT_FRAME_STYLE,
            const wxString &name = wxASCII_STR(wxFrameNameStr));
  virtual ~FrameToolScreenShot();

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
  wxBitmapButton *btn_screenshot_toolbar_close_ = nullptr;
  wxBitmapButton *btn_screenshot_toolbar_edit_ = nullptr;
  wxBitmapButton *btn_screenshot_toolbar_ok_ = nullptr;
  wxBitmapButton *btn_screenshot_toolbar_rectangle_ = nullptr;
  wxBitmapButton *btn_screenshot_toolbar_revocation_ = nullptr;
  wxBitmapButton *btn_screenshot_toolbar_round_ = nullptr;
  wxBitmapButton *btn_screenshot_toolbar_text_ = nullptr;
  wxBitmapButton *btn_screenshot_toolbar_mosaic_ = nullptr;
};

/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 10 Dec 2024 06:15:34 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__5DC5638E_C7E9_463C_A551_3645FBD34867__
