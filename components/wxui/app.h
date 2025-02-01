#if !defined(__158BBC1C_32DE_4F18_9EFC_E525E259F116__)
#define __158BBC1C_32DE_4F18_9EFC_E525E259F116__
class App : public wxApp {
public:
  App();
  virtual ~App();

public:
  bool OnInit() override;
  int OnExit() override;
  void OnFrameCreate();
  void OnFrameDestroy();
  IFrame *FrameGet() const;

public:
  wxFrame *FrameAppend(const ComponentFrameType &, wxFrame *);
  wxFrame *FrameGet(const ComponentFrameType &) const;
  IFrameComponent *FrameComponentGet(const FrameComponentType &) const;
  void PushThreadEvent(const wxEventType &evtType, const wxCommandEvent &);

private:
  std::map<FrameComponentType, IFrameComponent *> frame_comps_;
  std::map<ComponentFrameType, wxFrame *> comp_frames_;

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
  IFrame *frame_ = nullptr;
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

/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 27 Nov 2024 05:13:12 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__158BBC1C_32DE_4F18_9EFC_E525E259F116__