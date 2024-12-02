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
  IFrame *FrameToolGet() const;
  IFrame *FrameWorkGet() const;
  IFrame *FrameBgkGet() const;

private:
  IFrame *frame_ = nullptr;
  IFrame *frame_tool_ = nullptr;
  IFrame *frame_work_ = nullptr;
  IFrame *frame_bgk_ = nullptr;
  void OnThreadEvtFrameDestroy(wxThreadEvent &event);
  void OnThreadEvtCaptureFinished(wxThreadEvent &event);
  void MainProc();
  std::atomic_bool open_ = false;
  stl::tfThreads threads_;
};
extern const int wxAppThreadEvt_CaptureFinished;
extern const int wxAppThreadEvt_FrameDestroy;
extern const int wxAppThreadEvt_BroadcastEvent;
/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 27 Nov 2024 05:13:12 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__158BBC1C_32DE_4F18_9EFC_E525E259F116__