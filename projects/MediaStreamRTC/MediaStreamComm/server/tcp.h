#if !defined(__F2515155_64C2_4811_B4DA_E1F7BC842BA0__)
#define __F2515155_64C2_4811_B4DA_E1F7BC842BA0__

class ServerTcp final : public IServer {
public:
  ServerTcp();
  virtual ~ServerTcp();

protected:
  bool Start() override final;
  void Stop() override final;
  void Release() const override final;

private:
  void Init();
  void UnInit();

private:
  uvpp::IService *server_ = nullptr;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 08 Dec 2024 00:20:10 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__F2515155_64C2_4811_B4DA_E1F7BC842BA0__