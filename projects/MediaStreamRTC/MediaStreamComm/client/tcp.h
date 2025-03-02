#if !defined(__01F3E4B1_F0F9_481A_AC0E_EE353840FA56__)
#define __01F3E4B1_F0F9_481A_AC0E_EE353840FA56__

class ClientTcp final : public IClient {
public:
  ClientTcp();
  virtual ~ClientTcp();

protected:
  bool Start() override final;
  void Stop() override final;
  void Release() const override final;

private:
  void Init();
  void UnInit();

private:
  uvpp::IService *client_ = nullptr;
};

/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 08 Dec 2024 08:19:38 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__01F3E4B1_F0F9_481A_AC0E_EE353840FA56__