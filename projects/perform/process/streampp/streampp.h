#if !defined(__AF55C7A1_41D9_4FFB_9453_FF4B466D18C4__)
#define __AF55C7A1_41D9_4FFB_9453_FF4B466D18C4__

class IStreamPP final : public IPerform {
public:
  IStreamPP();
  virtual ~IStreamPP();

private:
  void Init();
  void UnInit();

protected:
  void Release() const override final;
  bool Start() override final;
  void Stop() override final;
  IConfig *ConfigGet() const override final;

private:
  uvpp::IService *server_udp_ = nullptr;
  uvpp::IService *server_tcp_ = nullptr;
  uvpp::IService *server_ipc_ = nullptr;
  std::map<std::string, uvpp::IService *> client_ipc_s_;
  std::map<std::string, uvpp::IService *> client_tcp_s_;
  std::map<std::string, uvpp::IService *> client_udp_s_;

protected:
  void __impl__() const override final {
  }
};
/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 09 Dec 2024 09:43:37 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__AF55C7A1_41D9_4FFB_9453_FF4B466D18C4__