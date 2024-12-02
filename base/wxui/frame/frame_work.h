#if !defined(__DD760240_2EBB_4674_8F13_09C9C7B0D05A__)
#define __DD760240_2EBB_4674_8F13_09C9C7B0D05A__

class FrameWork final : public FrameBase {
public:
  FrameWork(wxWindow *parent, wxWindowID id = wxID_ANY,
            const wxString &title = wxEmptyString,
            const wxPoint &pos = wxDefaultPosition,
            const wxSize &size = wxDefaultSize,
            long style = wxDEFAULT_FRAME_STYLE,
            const wxString &name = wxASCII_STR(wxFrameNameStr));
  virtual ~FrameWork();

private:
  void OnSize(wxSizeEvent &event);
  void OnClose(wxCloseEvent &event);
  void OnPaint(wxPaintEvent &event);

  wxDECLARE_EVENT_TABLE();
};

/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 01 Dec 2024 12:15:43 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__DD760240_2EBB_4674_8F13_09C9C7B0D05A__
