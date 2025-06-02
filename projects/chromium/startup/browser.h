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
  bool CreateChromium(IRequest &req);
  void DestroyChromium(IRequest &req);

private:
  void Init();
  void UnInit();

private:
  std::map<unsigned short, IChromium *> chromium_;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};
/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 30 May 2025 06:26:42 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__21CEC7C3_5B45_4FE4_A959_54643A535B22__