#if !defined(__039580E8_99E9_4E2E_8593_0E395014BEB0__)
#define __039580E8_99E9_4E2E_8593_0E395014BEB0__

namespace ui {
class FrameActivate final : public IFrame {
public:
  FrameActivate(wxWindow *parent, wxWindowID id = wxID_ANY,
         const wxString &title = wxEmptyString,
         const wxPoint &pos = wxDefaultPosition,
         const wxSize &size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE,
         const wxString &name = wxASCII_STR(wxFrameNameStr));
  virtual ~FrameActivate();

protected:
  void OnPaint(wxPaintEvent &) override final;
  void OnEraseBackground(wxEraseEvent &) override final;
};
} // namespace ui

/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 12 Jan 2025 03:19:02 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__039580E8_99E9_4E2E_8593_0E395014BEB0__