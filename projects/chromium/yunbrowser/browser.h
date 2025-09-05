#if !defined(__21CEC7C3_5B45_4FE4_A959_54643A535B22__)
#define __21CEC7C3_5B45_4FE4_A959_54643A535B22__

class Browser final {
public:
  static Browser *CreateOrGet();
  static void Destroy();

private:
  Browser();
  ~Browser();

public:
  IChromium *CreateChromium(chromium::IRequest *);
  void DestroyChromium(chromium::IRequest *);
  IChromium *ResetChromium(chromium::IRequest *);
  void CreateChromiumResult(chromium::IRequest *);
  void CheckChromium(const std::function<bool(IChromium *)> &);
  const BrowserStatus &GetStatus() const;
  bool IsIdle() const;

private:
  void Init();
  void UnInit();

private:
  BrowserStatus status_ = BrowserStatus::kIdle;
  std::map<chromium::xsiumio::tfIdentifyType, IChromium *> chromium_;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};
/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 30 May 2025 06:26:42 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__21CEC7C3_5B45_4FE4_A959_54643A535B22__