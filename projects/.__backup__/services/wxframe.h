#if !defined(__610793FB_7D39_4D7C_9B01_AF8386673135__)
#define __610793FB_7D39_4D7C_9B01_AF8386673135__

class Frame : public wxFrame {
public:
  Frame(wxWindow *parent, wxWindowID id, const wxString &title,
        const wxPoint &pos = wxDefaultPosition,
        const wxSize &size = wxDefaultSize,
        long style = wxDEFAULT_FRAME_STYLE /* wxNO_BORDER | wxFRAME_SHAPED*/,
        const wxString &name = wxASCII_STR(wxFrameNameStr));
  virtual ~Frame();

private:
  wxGauge *gauge_ = nullptr;

private:
  void OnSize(wxSizeEvent &);
  void OnClose(wxCloseEvent &);
  /*WXLRESULT
  MSWWindowProc(WXUINT nMsg, WXWPARAM wParam, WXLPARAM lParam) override final;*/
  wxDECLARE_EVENT_TABLE();
};

/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 09 Nov 2024 13:52:05 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__610793FB_7D39_4D7C_9B01_AF8386673135__
