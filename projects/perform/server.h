#if !defined(__66D36CE1_C3F0_4601_8CB0_3DCE31E2D698__)
#define __66D36CE1_C3F0_4601_8CB0_3DCE31E2D698__

class Server {
public:
  Server();
  ~Server();

public:
  bool Start();
  void Stop();
  unsigned short GetPort() const;

private:
  void Init();
  void UnInit();
  void Listen();
  unsigned short port_ = 0;
  std::atomic_bool open_ = false;
  tfThreads threads_;
  httplib::Server *server_ = nullptr;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 11 Nov 2024 09:56:22 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__66D36CE1_C3F0_4601_8CB0_3DCE31E2D698__