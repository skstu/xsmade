#if !defined(__A7AE0FB6_90A8_4123_82E4_70BE2492B465__)
#define __A7AE0FB6_90A8_4123_82E4_70BE2492B465__

class Curl final : public ICurl {
public:
  static Curl *Create();
  static void Destroy();

private:
  Curl();
  virtual ~Curl();

protected:
  ICurl::IConfig *GetConfig() const override final;
  IRequest *CreateRequest() const override final;
  IRequestArray *CreateRequestArray() const override final;
  bool Start() override final;
  void Stop() override final;
  bool Ready() const override final;
  IRequestArray *Perform(IRequestArray *) override final;
  void Free(void **) const override final;

private:
  void Init();
  void UnInit();

private:
  std::atomic_bool ready_ = false;
  std::atomic_bool open_ = false;
  std::unique_ptr<std::mutex> mtx_ = std::make_unique<std::mutex>();
};

/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 07 Dec 2024 02:23:49 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__A7AE0FB6_90A8_4123_82E4_70BE2492B465__
