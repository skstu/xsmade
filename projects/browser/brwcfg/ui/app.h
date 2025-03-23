#if !defined(__D843267E_E383_4213_8A98_905B0C9083D0__)
#define __D843267E_E383_4213_8A98_905B0C9083D0__
#if ENABLE_WXUI
class App : public wxApp {
public:
  App();
  virtual ~App();

public:
  bool OnInit() override;
  int OnExit() override;
  void OnFrameCreate();
  void OnFrameDestroy();
  wxFrame *FrameGet() const;
public:
  void PushThreadEvent(const wxEventType &evtType, const wxCommandEvent &);

private:
  void EnumerateChildren(wxWindow *parent,
                         std::unordered_set<wxWindow *> &childs) const;
  void BroadcastEvent(wxWindow *target, wxCommandEvent &route,
                      std::unordered_set<wxWindowID> &processed) const;
  std::atomic_bool open_ = false;
  stl::container::queue<wxCommandEvent *> evts_;
  void EventProc();
  stl::tfThreads threads_;

private:
  wxFrame *frame_ = nullptr;
  stl::container::set<wxFrame *> frames_;
  void OnThreadEvtDrawToolActivate(wxThreadEvent &evt);
  void OnThreadEvtBroadcastEvent(wxThreadEvent &evt);
  void OnThreadEvtFrameDestroy(wxThreadEvent &event);
  void OnThreadEvtScreenShotFinished(wxThreadEvent &event);
  void OnThreadEvtScreenShotFinalSuccess(wxThreadEvent &evt);
  void OnThreadEvtScreenShotClose(wxThreadEvent &event);
  void OnThreadEvtRecordingBoxSelectionFinished(wxThreadEvent &event);
};

wxDECLARE_EVENT(wxEVT_NotifyType, wxCommandEvent);
wxDECLARE_EVENT(wxEVT_NotifyRecordComp, wxCommandEvent);

extern const int wxAppThreadEvt_ScreenShotFinished;
extern const int wxAppThreadEvt_ScreenShotFinalSuccess;
extern const int wxAppThreadEvt_ScreenShotClose;
extern const int wxAppThreadEvt_RecordingBoxSelectionFinished;
extern const int wxAppThreadEvt_FrameDestroy;
extern const int wxAppThreadEvt_BroadcastEvent;
extern const int wxAppThreadEvt_WorkSpaceModeChanged;
extern const int wxAppThreadEvt_DrawToolActivate;
#endif
/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 02 Mar 2025 12:25:55 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__D843267E_E383_4213_8A98_905B0C9083D0__