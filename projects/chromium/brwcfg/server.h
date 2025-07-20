#if !defined(__C6045793_E811_49CF_AE14_F3722D8A32AE__)
#define __C6045793_E811_49CF_AE14_F3722D8A32AE__

class Server final {
public:
  static Server *GetOrCreate();
  static void Destroy();

public:
  bool Start();
  void Stop();
  const std::uint16_t &GetPort() const;
  const std::string &GetHost() const;

private:
  Server();
  ~Server();
  void Init();
  void UnInit();
  void Listen();
  void Process();

private:
  stl::tfThreads threads_;
  std::atomic_bool open_ = false;
  httplib::Server *server_ = nullptr;
  std::uint16_t port_ = 0;
  const std::string host_ = "127.0.0.1";
};
/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 02 Jun 2025 11:32:17 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__C6045793_E811_49CF_AE14_F3722D8A32AE__