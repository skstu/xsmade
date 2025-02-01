#if !defined(__2A59E452_FE12_4469_B943_0DDE8226E6D6__)
#define __2A59E452_FE12_4469_B943_0DDE8226E6D6__

namespace screenshot {
class DrawOkTool final : public IDrawTool {
public:
  DrawOkTool(wxWindow *parent, wxWindowID id, const wxBitmapBundle &bitmap,
             const wxPoint &pos = wxDefaultPosition,
             const wxSize &size = wxDefaultSize, long style = 0,
             const wxValidator &validator = wxDefaultValidator,
             const wxString &name = wxASCII_STR(wxButtonNameStr));
  virtual ~DrawOkTool();

protected:
  void OnClicked(wxCommandEvent &) override final;
};
} // namespace screenshot

/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 15 Dec 2024 02:12:38 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__2A59E452_FE12_4469_B943_0DDE8226E6D6__
