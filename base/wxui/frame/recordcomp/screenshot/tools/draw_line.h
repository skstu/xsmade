#if !defined(__120A9641_1329_492C_9BAF_1CED41FAEB68__)
#define __120A9641_1329_492C_9BAF_1CED41FAEB68__

namespace screenshot {
class DrawLineTool final : public IDrawTool {
public:
  DrawLineTool(wxWindow *parent, wxWindowID id, const wxBitmapBundle &bitmap,
               const wxPoint &pos = wxDefaultPosition,
               const wxSize &size = wxDefaultSize, long style = 0,
               const wxValidator &validator = wxDefaultValidator,
               const wxString &name = wxASCII_STR(wxButtonNameStr));
  virtual ~DrawLineTool();

protected:
  void OnClicked(wxCommandEvent &) override final;
};
} // namespace screenshot

/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 14 Dec 2024 23:49:22 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__120A9641_1329_492C_9BAF_1CED41FAEB68__