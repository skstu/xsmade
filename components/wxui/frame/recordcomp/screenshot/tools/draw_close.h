#if !defined(__F9C8F966_8B4B_4137_98B8_119D3E25381C__)
#define __F9C8F966_8B4B_4137_98B8_119D3E25381C__

namespace screenshot {
class DrawCloseTool final : public IDrawTool {
public:
  DrawCloseTool(wxWindow *parent, wxWindowID id, const wxBitmapBundle &bitmap,
                const wxPoint &pos = wxDefaultPosition,
                const wxSize &size = wxDefaultSize, long style = 0,
                const wxValidator &validator = wxDefaultValidator,
                const wxString &name = wxASCII_STR(wxButtonNameStr));
  virtual ~DrawCloseTool();

protected:
  void OnClicked(wxCommandEvent &) override final;
};
} // namespace screenshot

/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 15 Dec 2024 02:10:46 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__F9C8F966_8B4B_4137_98B8_119D3E25381C__
