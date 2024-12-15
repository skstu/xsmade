#if !defined(__EEFDE6FB_EE41_4A77_AA86_A9755D2F6F73__)
#define __EEFDE6FB_EE41_4A77_AA86_A9755D2F6F73__

namespace screenshot {
class DrawRectangleTool final : public IDrawTool {
public:
  DrawRectangleTool(wxWindow *parent, wxWindowID id,
                    const wxBitmapBundle &bitmap,
                    const wxPoint &pos = wxDefaultPosition,
                    const wxSize &size = wxDefaultSize, long style = 0,
                    const wxValidator &validator = wxDefaultValidator,
                    const wxString &name = wxASCII_STR(wxButtonNameStr));
  virtual ~DrawRectangleTool();

protected:
  void OnClicked(wxCommandEvent &) override final;
};
} // namespace screenshot

/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 14 Dec 2024 23:48:38 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__EEFDE6FB_EE41_4A77_AA86_A9755D2F6F73__