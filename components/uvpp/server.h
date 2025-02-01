#if !defined(__675D16B5_C232_46BE_8996_36A05DB12580__)
#define __675D16B5_C232_46BE_8996_36A05DB12580__

class Server final : public IService {
public:
  static Server *Create();
  static void Destroy();

private:
  Server();
  ~Server();

public:
  bool Start() override final;
  void Stop() override final;
  bool Ready() const override final;
  bool Write(const unsigned long &, const char *, size_t) override final;
  bool Write(const unsigned long &cmd, const IBuffer *buffer) override final;
  ServerStatus Status() const override final;
  size_t SessionCount() const override final;
  void Release() const override final;
  ServerType ServerTypeGet() const override final;
  SessionType SessionTypeGet() const override final;
  AddressType AddressTypeGet() const override final;

public:
  bool IsClose() const;
  void Status(const ServerStatus &);
  void SessionCount(const unsigned long &);

private:
  void Init();
  void UnInit();
  static void MainProcess(void *);
  static void WorkProcess(uv_handle_t *handle, void *arg);
  static void SessionConnectionCb(uv_stream_t *server, int status);
  HANDLE thread_main_ = nullptr;
  std::atomic_bool ready_ = false;
  std::atomic_bool open_ = false;
  std::atomic_ulong m_SessionCount = 0;
  ServerStatus m_ServerStatus = ServerStatus::UNKNOWN;
  stl::container::multimap<CommandType, std::string> m_PushQ;
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
};

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 19 May 2023 10:27:11 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__675D16B5_C232_46BE_8996_36A05DB12580__