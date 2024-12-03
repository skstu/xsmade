#if !defined(__158BBC1C_32DE_4F18_9EFC_E525E259F116__)
#define __158BBC1C_32DE_4F18_9EFC_E525E259F116__
class App : public wxApp {
public:
  App();
  virtual ~App();

public:
  bool OnInit() override;
  int OnExit() override;
};
#if 0
class App : public wxApp {
public:
  App();
  virtual ~App();

public:
  bool OnInit() override;
  int OnExit() override;

private:
  void OnThreadEvtFrameDestroy(wxThreadEvent &event);

private:
  void OnFrameCreate();
  void OnFrameDestroy();

private:
  stl::tfThreads threads_;
  wxIcon logo_;
  Frame *frame_ = nullptr;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};

extern const int wxAppThreadEvt_FrameDestroy;
#endif
/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 27 Nov 2024 05:13:12 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__158BBC1C_32DE_4F18_9EFC_E525E259F116__