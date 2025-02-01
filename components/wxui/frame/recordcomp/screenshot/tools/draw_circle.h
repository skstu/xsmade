#if !defined(__44255068_D997_4262_BCEC_590FD584D538__)
#define __44255068_D997_4262_BCEC_590FD584D538__

namespace screenshot {
class DrawCircleTool final : public IDrawTool {
public:
  DrawCircleTool(wxWindow *parent, wxWindowID id, const wxBitmapBundle &bitmap,
                 const wxPoint &pos = wxDefaultPosition,
                 const wxSize &size = wxDefaultSize, long style = 0,
                 const wxValidator &validator = wxDefaultValidator,
                 const wxString &name = wxASCII_STR(wxButtonNameStr));
  virtual ~DrawCircleTool();

protected:
  void OnClicked(wxCommandEvent &) override final;
};
} // namespace screenshot
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 14 Dec 2024 23:47:22 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__44255068_D997_4262_BCEC_590FD584D538__