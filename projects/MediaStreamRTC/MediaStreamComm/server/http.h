#if !defined(__C952E455_F195_429F_B7DB_B85411F0E82D__)
#define __C952E455_F195_429F_B7DB_B85411F0E82D__

class ServerHttp final : public IServer {
public:
  ServerHttp();
  virtual ~ServerHttp();

protected:
  bool Start() override final;
  void Stop() override final;
  void Release() const override final;

private:
  void Init();
  void UnInit();
};
/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 08 Dec 2024 00:19:43 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__C952E455_F195_429F_B7DB_B85411F0E82D__