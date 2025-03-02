#if !defined(__C95ABED3_5399_455D_945F_AE9B2CCEFACB__)
#define __C95ABED3_5399_455D_945F_AE9B2CCEFACB__

class Download final : public IPerform {
public:
  Download();
  virtual ~Download();

private:
  void Init();
  void UnInit();

public:
  void Release() const override final;
  bool Start() override final;
  void Stop() override final;
  IConfig *ConfigGet() const override final;

protected:
  void __impl__() const override final {
  }
};
/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 04 Dec 2024 03:19:13 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__C95ABED3_5399_455D_945F_AE9B2CCEFACB__