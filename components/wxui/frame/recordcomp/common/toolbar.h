#if !defined(__4DAABB6F_EA63_4800_9F29_2FB241B78ADC__)
#define __4DAABB6F_EA63_4800_9F29_2FB241B78ADC__

class IToolbar : public wxFrame {
public:
  IToolbar(wxWindow *parent, wxWindowID id = wxID_ANY,
           const wxString &title = wxEmptyString,
           const wxPoint &pos = wxDefaultPosition,
           const wxSize &size = wxDefaultSize,
           long style = wxDEFAULT_FRAME_STYLE,
           const wxString &name = wxASCII_STR(wxFrameNameStr));
  virtual ~IToolbar();

public:
  virtual void GetExpandToolbar(wxPanel **outPanel, wxBoxSizer **outSizer) {
  }
  virtual void RefreshToolbar() {}
protected:
  virtual void OnFullScreenShown() {
  }
  virtual void OnLayout() {
  }
  virtual void OnToolEvent(wxCommandEvent &event);
  virtual void OnToolbarSizeChanged(const wxRect &) {
  }

protected:
  std::atomic_bool is_allow_move_ = true;
  std::atomic_bool is_dragging_ = false;
  std::atomic_bool is_fullscreen_shown_ = false;
  std::atomic_bool recording_running_ = false;
  wxRect prev_frame_tool_rect_;
  wxRect prev_frame_work_rect_;
  wxPoint delta_;

protected:
  virtual void OnSize(wxSizeEvent &);
  virtual void OnClose(wxCloseEvent &evt) {
    evt.Skip();
  }
  virtual void OnMove(wxMoveEvent &);
  virtual void OnMouseMove(wxMouseEvent &event);
  virtual void OnMouseLeftDown(wxMouseEvent &event);
  virtual void OnMouseLeftUp(wxMouseEvent &event);
  virtual void OnMouseLeftDClick(wxMouseEvent &event);
  DECLARE_EVENT_TABLE()
};
/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 13 Dec 2024 05:26:21 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__4DAABB6F_EA63_4800_9F29_2FB241B78ADC__