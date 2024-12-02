#if !defined(__99D5C9B6_6732_45D0_8454_96D91CE94DC0__)
#define __99D5C9B6_6732_45D0_8454_96D91CE94DC0__

class FrameBase : public wxFrame, public IFrame {
public:
  FrameBase(wxWindow *parent, wxWindowID id = wxID_ANY,
            const wxString &title = wxEmptyString,
            const wxPoint &pos = wxDefaultPosition,
            const wxSize &size = wxDefaultSize,
            long style = wxDEFAULT_FRAME_STYLE,
            const wxString &name = wxASCII_STR(wxFrameNameStr));
  virtual ~FrameBase();

protected:
  const FrameType &Type() const override;
  void SetRegion(long x, long y, long cx, long cy) override;
  bool IsFullScreenShown() const override;
  bool IsDragging() const override;

protected:
  std::atomic_bool is_dragging_ = false;
  std::atomic_bool is_fullscreen_shown_ = false;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Thu, 28 Nov 2024 05:50:44 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__99D5C9B6_6732_45D0_8454_96D91CE94DC0__