#if !defined(__5D4640E8_A90F_4B8B_B805_3C290084EFB3__)
#define __5D4640E8_A90F_4B8B_B805_3C290084EFB3__

class Client final {
public:
  static Client *GetOrCreate();
  static void Destroy();

private:
  Client();
  ~Client();

  void Init();
  void UnInit();
  void Process();

public:
  bool Start();
  void Stop();
  bool Post(const std::string &path, const std::string &body);

private:
  stl::tfThreads threads_;
  std::atomic_bool open_ = false;
  std::string host_ = "127.0.0.1";
  std::uint16_t port_ = 0;
  stl::container::queue<
      std::tuple<std::string /*http.path*/, std::string /*content*/>>
      send_data_q_;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 02 Jun 2025 11:51:21 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__5D4640E8_A90F_4B8B_B805_3C290084EFB3__