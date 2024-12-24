#if !defined(__A95784C9_5F36_4129_B846_5546DE175D09__)
#define __A95784C9_5F36_4129_B846_5546DE175D09__

namespace screenshot {
class DrawTextTool final : public IDrawTool {
public:
  DrawTextTool(wxWindow *parent, wxWindowID id, const wxBitmapBundle &bitmap,
               const wxPoint &pos = wxDefaultPosition,
               const wxSize &size = wxDefaultSize, long style = 0,
               const wxValidator &validator = wxDefaultValidator,
               const wxString &name = wxASCII_STR(wxButtonNameStr));
  virtual ~DrawTextTool();

protected:
  void OnClicked(wxCommandEvent &) override final;
};

} // namespace screenshot

/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 14 Dec 2024 23:50:13 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__A95784C9_5F36_4129_B846_5546DE175D09__