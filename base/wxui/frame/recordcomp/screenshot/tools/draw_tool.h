#if !defined(__4C4F46DE_1E64_42F0_B961_9D02784A3617__)
#define __4C4F46DE_1E64_42F0_B961_9D02784A3617__

namespace screenshot {
class IDrawTool : public wxBitmapButton {
public:
  IDrawTool(wxWindow *parent, wxWindowID id, const wxBitmapBundle &bitmap,
            const wxPoint &pos = wxDefaultPosition,
            const wxSize &size = wxDefaultSize, long style = 0,
            const wxValidator &validator = wxDefaultValidator,
            const wxString &name = wxASCII_STR(wxButtonNameStr));
  virtual ~IDrawTool();

protected:
  virtual void OnClicked(wxCommandEvent &evt);
  virtual void OnNotify(wxCommandEvent &evt);

protected:
  std::atomic_bool pressed_ = false;

private:
  wxDECLARE_EVENT_TABLE();
};
} // namespace screenshot
/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 15 Dec 2024 02:32:16 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__4C4F46DE_1E64_42F0_B961_9D02784A3617__
