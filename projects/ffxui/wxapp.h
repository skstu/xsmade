#if !defined(__356CC458_E9D3_4071_9BFC_B83BB412B48A__)
#define __356CC458_E9D3_4071_9BFC_B83BB412B48A__

class App : public wxApp {
public:
  App();
  virtual ~App();

public:
  bool OnInit() override;
  int OnExit() override;

private:
  Frame *frame_ = nullptr;
};

/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 09 Nov 2024 13:52:31 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__356CC458_E9D3_4071_9BFC_B83BB412B48A__