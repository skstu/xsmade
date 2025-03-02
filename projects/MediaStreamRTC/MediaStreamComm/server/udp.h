#if !defined(__C3B4A278_715D_400A_AC8B_E473536FB6C4__)
#define __C3B4A278_715D_400A_AC8B_E473536FB6C4__

class ServerUdp final : public IServer {
public:
  ServerUdp();
  virtual ~ServerUdp();

protected:
  bool Start() override final;
  void Stop() override final;
  void Release() const override final;

private:
  void Init();
  void UnInit();
};
/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 08 Dec 2024 00:20:17 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__C3B4A278_715D_400A_AC8B_E473536FB6C4__