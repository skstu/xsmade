#if !defined(__124DC279_DBF3_41E2_B77D_AAE3834786E5__)
#define __124DC279_DBF3_41E2_B77D_AAE3834786E5__

class FrameWorkImage final : public FrameBase {
public:
  FrameWorkImage(wxWindow *parent, wxWindowID id = wxID_ANY,
                 const wxString &title = wxEmptyString,
                 const wxPoint &pos = wxDefaultPosition,
                 const wxSize &size = wxDefaultSize,
                 long style = wxDEFAULT_FRAME_STYLE,
                 const wxString &name = wxASCII_STR(wxFrameNameStr));
  virtual ~FrameWorkImage();

public:
  bool SetBackgroundBitmap(const std::string& imgPath);
private:
  wxBitmap* backgroundBitmap_ = nullptr;

private:
  void OnSize(wxSizeEvent &event);
  void OnClose(wxCloseEvent &event);
  void OnPaint(wxPaintEvent &event);

  wxDECLARE_EVENT_TABLE();
};

/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 11 Dec 2024 07:06:50 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__124DC279_DBF3_41E2_B77D_AAE3834786E5__
