#if !defined(__6CACE624_3CBC_4736_82FF_CBB0C9F28EF9__)
#define __6CACE624_3CBC_4736_82FF_CBB0C9F28EF9__

namespace record {
class ActionScreenshot final : public IActionTool {
public:
  ActionScreenshot(wxWindow *parent, wxWindowID id,
                   const wxBitmapBundle &bitmap,
                   const wxPoint &pos = wxDefaultPosition,
                   const wxSize &size = wxDefaultSize, long style = 0,
                   const wxValidator &validator = wxDefaultValidator,
                   const wxString &name = wxASCII_STR(wxButtonNameStr));
  virtual ~ActionScreenshot();

protected:
  void OnClicked(wxCommandEvent &) override final;
};
} // namespace record

/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 16 Dec 2024 00:19:23 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__6CACE624_3CBC_4736_82FF_CBB0C9F28EF9__