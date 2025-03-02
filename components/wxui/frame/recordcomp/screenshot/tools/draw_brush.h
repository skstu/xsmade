#if !defined(__F2907BB4_8A4F_4119_B9EC_A95E86FBD434__)
#define __F2907BB4_8A4F_4119_B9EC_A95E86FBD434__

namespace screenshot {
class DrawBrushTool final : public IDrawTool {
public:
  DrawBrushTool(wxWindow *parent, wxWindowID id, const wxBitmapBundle &bitmap,
                const wxPoint &pos = wxDefaultPosition,
                const wxSize &size = wxDefaultSize, long style = 0,
                const wxValidator &validator = wxDefaultValidator,
                const wxString &name = wxASCII_STR(wxButtonNameStr));
  virtual ~DrawBrushTool();

protected:
  void OnClicked(wxCommandEvent &) override final;
};
} // namespace screenshot

/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 15 Dec 2024 01:12:15 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__F2907BB4_8A4F_4119_B9EC_A95E86FBD434__
