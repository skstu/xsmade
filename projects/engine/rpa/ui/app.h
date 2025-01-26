#if !defined(__DFCB0F00_F67D_4917_BB7B_B07D2CD0F72C__)
#define __DFCB0F00_F67D_4917_BB7B_B07D2CD0F72C__

namespace ui {
class IApp : public wxApp {
public:
  IApp();
  virtual ~IApp();

public:
  static void NotifyAppDestroy();
private:
  bool OnInit() override;
  int OnExit() override;

private:
  bool OnCreate();
  void OnDestroy(wxThreadEvent &event);
private:
  IFrame *frame_ = nullptr;
};
} // namespace ui

extern const int wxAppEvent_Destroy;
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 11 Jan 2025 23:59:59 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__DFCB0F00_F67D_4917_BB7B_B07D2CD0F72C__