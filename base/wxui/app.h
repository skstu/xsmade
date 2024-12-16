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

private:
  std::map<FrameComponentType, IFrameComponent *> frame_comps_;
  std::map<ComponentFrameType, wxFrame *> frames_;

private:
  IFrame *frame_ = nullptr;
  void OnThreadEvtFrameDestroy(wxThreadEvent &event);
  void OnThreadEvtScreenShotFinished(wxThreadEvent &event);
  void OnThreadEvtScreenShotClose(wxThreadEvent &event);
  void OnThreadEvtRecordingBoxSelection(wxThreadEvent &event);
  void OnThreadEvtRecordingBoxSelectionFinished(wxThreadEvent &event);
};
extern const int wxAppThreadEvt_ScreenShotFinished;
extern const int wxAppThreadEvt_ScreenShotClose;
extern const int wxAppThreadEvt_RecordingBoxSelection;
extern const int wxAppThreadEvt_RecordingBoxSelectionFinished;
extern const int wxAppThreadEvt_FrameDestroy;
extern const int wxAppThreadEvt_BroadcastEvent;
/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 27 Nov 2024 05:13:12 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__158BBC1C_32DE_4F18_9EFC_E525E259F116__