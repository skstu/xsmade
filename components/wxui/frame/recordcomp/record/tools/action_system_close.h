#if !defined(__7763C690_ACD6_4572_81E8_43EA709EC1F7__)
#define __7763C690_ACD6_4572_81E8_43EA709EC1F7__

namespace record {
class ActionSystemClose final : public IActionTool {
public:
  ActionSystemClose(wxWindow *parent, wxWindowID id,
                   const wxBitmapBundle &bitmap,
                   const wxPoint &pos = wxDefaultPosition,
                   const wxSize &size = wxDefaultSize, long style = 0,
                   const wxValidator &validator = wxDefaultValidator,
                   const wxString &name = wxASCII_STR(wxButtonNameStr));
  virtual ~ActionSystemClose();

protected:
  void OnClicked(wxCommandEvent &) override final;
};
} // namespace record

/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 16 Dec 2024 00:19:12 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__7763C690_ACD6_4572_81E8_43EA709EC1F7__