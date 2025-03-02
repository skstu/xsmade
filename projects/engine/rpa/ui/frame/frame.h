#if !defined(__1AA4C6FD_A98F_48A7_B3C8_CE9F5FAE2179__)
#define __1AA4C6FD_A98F_48A7_B3C8_CE9F5FAE2179__

namespace ui {
class IFrame : public wxFrame {
public:
  IFrame(wxWindow *parent, wxWindowID id = wxID_ANY,
         const wxString &title = wxEmptyString,
         const wxPoint &pos = wxDefaultPosition,
         const wxSize &size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE,
         const wxString &name = wxASCII_STR(wxFrameNameStr));
  virtual ~IFrame();

private:
  virtual void OnSize(wxSizeEvent &);
  virtual void OnClose(wxCloseEvent &);
  virtual void OnPaint(wxPaintEvent &);
  virtual void OnEraseBackground(wxEraseEvent &);
  virtual void OnMove(wxMoveEvent &);
  virtual void OnMouseMove(wxMouseEvent &);
  virtual void OnMouseLeftDown(wxMouseEvent &);
  virtual void OnMouseLeftUp(wxMouseEvent &);
  virtual void OnMouseCaptureLost(wxMouseCaptureLostEvent&);
  // DECLARE_EVENT_TABLE()
};
} // namespace ui
/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 12 Jan 2025 00:14:15 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__1AA4C6FD_A98F_48A7_B3C8_CE9F5FAE2179__