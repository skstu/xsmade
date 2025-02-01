#if !defined(__072088F2_C7A0_40FD_9570_CA047D8F7281__)
#define __072088F2_C7A0_40FD_9570_CA047D8F7281__

namespace record {
class ActionBoxSelection final : public IActionTool {
public:
  ActionBoxSelection(wxWindow *parent, wxWindowID id, const wxBitmapBundle &bitmap,
                const wxPoint &pos = wxDefaultPosition,
                const wxSize &size = wxDefaultSize, long style = 0,
                  const wxValidator &validator = wxDefaultValidator,
                const wxString &name = wxASCII_STR(wxButtonNameStr));
  virtual ~ActionBoxSelection();

protected:
  void OnClicked(wxCommandEvent &) override final;
};
} // namespace record

/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 16 Dec 2024 00:19:39 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/s
#endif///__072088F2_C7A0_40FD_9570_CA047D8F7281__