#if !defined(__181658D0_68ED_45A2_ABF9_F6B09AEB99E7__)
#define __181658D0_68ED_45A2_ABF9_F6B09AEB99E7__

class Client final {
public:
  struct Packet {
    Packet();
    ~Packet();
    int target_port = 0;
    std::string target_host;
    std::string body;
    httplib::Headers headers;
    std::string path = "/";
    bool gzip = false;
  };

public:
  static Client *CreateOrGet();
  static void Destroy();

public:
  bool Start();
  void Stop();

  void Post(const Packet&);

private:
  Client();
  ~Client();

  void Init();
  void UnInit();
  void Process();
  stl::tfThreads threads_;
  std::atomic_bool open_ = false;
  stl::container::queue<Packet> requests_;
  std::unique_ptr<std::mutex> mtx_ = std::make_unique<std::mutex>();
};

/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 02 Sep 2025 00:05:01 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__181658D0_68ED_45A2_ABF9_F6B09AEB99E7__