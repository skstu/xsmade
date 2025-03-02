#if !defined(__F818021A_0DEB_4B35_A06D_BCB586657D37__)
#define __F818021A_0DEB_4B35_A06D_BCB586657D37__

namespace screenshot {
class DrawMosaicTool final : public IDrawTool {
public:
  DrawMosaicTool(wxWindow *parent, wxWindowID id, const wxBitmapBundle &bitmap,
                 const wxPoint &pos = wxDefaultPosition,
                 const wxSize &size = wxDefaultSize, long style = 0,
                 const wxValidator &validator = wxDefaultValidator,
                 const wxString &name = wxASCII_STR(wxButtonNameStr));
  virtual ~DrawMosaicTool();

protected:
  void OnClicked(wxCommandEvent &) override final;
};
} // namespace screenshot
  //
/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 15 Dec 2024 01:01:51 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__F818021A_0DEB_4B35_A06D_BCB586657D37__