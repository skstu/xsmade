#if !defined(__B66757A9_037F_4C82_A63B_CC0EEBC71B0D__)
#define __B66757A9_037F_4C82_A63B_CC0EEBC71B0D__
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
  void OnSize(wxSizeEvent &event);
  void OnClose(wxCloseEvent &event);
  void OnMouseMove(wxMouseEvent &event);
  void OnMouseLeftDown(wxMouseEvent &event);
  void OnMouseLeftUp(wxMouseEvent &event);
  void OnPaint(wxPaintEvent &event);
  void OnShow(wxShowEvent &event);
  void OnKeyDown(wxKeyEvent &event);
  void OnChar(wxKeyEvent &event);

  wxPoint startPoint_;
  wxPoint endPoint_;
  std::atomic_bool drawing_ = false;

  wxDECLARE_EVENT_TABLE();
};

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 13 Dec 2024 05:35:36 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__B66757A9_037F_4C82_A63B_CC0EEBC71B0D__