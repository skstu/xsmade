#if !defined(__60FED7B9_5B56_4017_B370_94F887988383__)
#define __60FED7B9_5B56_4017_B370_94F887988383__

namespace record {
class ActionRecording final : public IActionTool {
public:
  ActionRecording(wxWindow *parent, wxWindowID id, const wxBitmapBundle &bitmap,
                  const wxPoint &pos = wxDefaultPosition,
                  const wxSize &size = wxDefaultSize, long style = 0,
                  const wxValidator &validator = wxDefaultValidator,
                  const wxString &name = wxASCII_STR(wxButtonNameStr));
  virtual ~ActionRecording();

protected:
  void OnClicked(wxCommandEvent &) override final;
};
} // namespace record

/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 16 Dec 2024 00:19:31 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__60FED7B9_5B56_4017_B370_94F887988383__