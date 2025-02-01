#if !defined(__078EF4BF_E554_4CF9_8E04_46396FC575B8__)
#define __078EF4BF_E554_4CF9_8E04_46396FC575B8__

namespace record {
class IActionTool : public wxBitmapButton {
public:
  IActionTool(wxWindow *parent, wxWindowID id, const wxBitmapBundle &bitmap,
            const wxPoint &pos = wxDefaultPosition,
            const wxSize &size = wxDefaultSize, long style = 0,
            const wxValidator &validator = wxDefaultValidator,
            const wxString &name = wxASCII_STR(wxButtonNameStr));
  virtual ~IActionTool();

protected:
  virtual void OnClicked(wxCommandEvent &evt);
};
} // namespace record
  
/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 16 Dec 2024 00:30:17 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__078EF4BF_E554_4CF9_8E04_46396FC575B8__