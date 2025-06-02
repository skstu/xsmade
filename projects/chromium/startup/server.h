#if !defined(__0CD5AA07_1174_4BBC_ABC1_A713F99D7566__)
#define __0CD5AA07_1174_4BBC_ABC1_A713F99D7566__

class Server final {
public:
  Server();
  ~Server();

private:
  void Init();
  void UnInit();

public:
  bool Start();
  void Stop();
  bool IsOpen() const;

private:
  void Listen();
  stl::tfThreads threads_;
  std::atomic_bool open_ = false;
  httplib::Server *server_ = nullptr;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 30 May 2025 05:26:23 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__0CD5AA07_1174_4BBC_ABC1_A713F99D7566__