#if !defined(__94297AF1_CDC2_4CD3_958D_6E5219BEA000__)
#define __94297AF1_CDC2_4CD3_958D_6E5219BEA000__

namespace screenshot {
class DrawNoTool final : public IDrawTool {
public:
  DrawNoTool(wxWindow *parent, wxWindowID id, const wxBitmapBundle &bitmap,
             const wxPoint &pos = wxDefaultPosition,
             const wxSize &size = wxDefaultSize, long style = 0,
             const wxValidator &validator = wxDefaultValidator,
             const wxString &name = wxASCII_STR(wxButtonNameStr));
  virtual ~DrawNoTool();

protected:
  void OnClicked(wxCommandEvent &) override final;
};
} // namespace screenshot

/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 15 Dec 2024 02:10:19 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__94297AF1_CDC2_4CD3_958D_6E5219BEA000__
