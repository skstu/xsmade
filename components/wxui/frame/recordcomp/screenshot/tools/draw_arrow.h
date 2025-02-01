#if !defined(__80967A6A_A487_46FD_BCA3_857AE5B18935__)
#define __80967A6A_A487_46FD_BCA3_857AE5B18935__

namespace screenshot {
class DrawArrowTool final : public IDrawTool {
public:
  DrawArrowTool(wxWindow *parent, wxWindowID id, const wxBitmapBundle &bitmap,
                const wxPoint &pos = wxDefaultPosition,
                const wxSize &size = wxDefaultSize, long style = 0,
                const wxValidator &validator = wxDefaultValidator,
                const wxString &name = wxASCII_STR(wxButtonNameStr));
  virtual ~DrawArrowTool();

protected:
  void OnClicked(wxCommandEvent &) override final;
};
} // namespace screenshot

/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 14 Dec 2024 23:53:12 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__80967A6A_A487_46FD_BCA3_857AE5B18935__