#if !defined(__E18386CA_FD47_47AA_B602_9B13E608B92C__)
#define __E18386CA_FD47_47AA_B602_9B13E608B92C__

class IFrame : public wxFrame {
public:
  IFrame(wxWindow *parent, wxWindowID id = wxID_ANY,
         const wxString &title = wxEmptyString,
         const wxPoint &pos = wxDefaultPosition,
         const wxSize &size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE,
         const wxString &name = wxASCII_STR(wxFrameNameStr));
  virtual ~IFrame();

private:
  void OnSize(wxSizeEvent &);
  void OnClose(wxCloseEvent &);
  DECLARE_EVENT_TABLE()
};
#if 0
class Frame : public wxFrame {
public:
  Frame(wxWindow *parent, wxWindowID id = wxID_ANY,
        const wxString &title = wxEmptyString,
        const wxPoint &pos = wxDefaultPosition,
        const wxSize &size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE,
        const wxString &name = wxASCII_STR(wxFrameNameStr));
  virtual ~Frame();

private:
  wxBitmap m_bmp;
  wxPoint m_delta;
  wxImage *image_ = nullptr;
  wxGraphicsPath m_shapePath;
  void OnMouseMove(wxMouseEvent &event);
  void OnPaint(wxPaintEvent &event);
  void OnMouseLeftDown(wxMouseEvent &event);
  void OnMouseLeftUp(wxMouseEvent &event);
  void OnErase(wxEraseEvent &event);
  bool SetShape(const wxBufferedPaintDC &);
#ifdef __WXGTK__
  void OnWindowCreate(wxWindowCreateEvent &event);
#endif
  DECLARE_EVENT_TABLE()
};
#endif
/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 02 Mar 2025 12:27:31 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__E18386CA_FD47_47AA_B602_9B13E608B92C__
