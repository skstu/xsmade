#if !defined(__81FDDD44_91F0_40B1_B7F8_9749F23B1A8E__)
#define __81FDDD44_91F0_40B1_B7F8_9749F23B1A8E__

class Service : public uvpp::IServiceManager {
public:
  Service();
  virtual ~Service();

private:
  void Init();
  void UnInit();

public:
  IConfig *ConfigGet() const override final;

protected:
  bool Start() override final;
  void Stop() override final;
  bool Ready() const override final;
  void Release() const override final;
  IService *GetSevice() const override final;
  IBuffer *CreateBuffer(const char *, size_t) const override final;

private:
  std::atomic_bool ready_ = false;
  Config *config_ = nullptr;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};

extern Client *__gpClient;
extern Server *__gpServer;
extern Service *__gpService;
extern Service *ServiceGet();
/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 19 May 2023 10:26:50 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__81FDDD44_91F0_40B1_B7F8_9749F23B1A8E__
