#if !defined(__2BFBE9A5_EDD9_447B_A673_9BACBBD7CBB8__)
#define __2BFBE9A5_EDD9_447B_A673_9BACBBD7CBB8__

class Client final : public IService {
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();

public:
  static Client *Create();
  static void Destroy();

private:
  Client(/*const unsigned long&*/);
  ~Client();

public:
  bool Ready() const override final;
  bool Start() override final;
  void Stop() override final;
  void Release() const override final;
  size_t SessionCount() const override final;
  ServerStatus Status() const override final;
  bool Write(const unsigned long &, const char *, size_t) override final;
  bool Write(const unsigned long &, const IBuffer *) override final;

public:
  ServerType ServerTypeGet() const override final;
  SessionType SessionTypeGet() const override final;
  AddressType AddressTypeGet() const override final;

private:
  static void MainProcess(void *);
  static void ConnectCb(uv_connect_t *req, int status);
  static bool Connect(const std::string &, uv_handle_t *, uv_handle_t *);
  void Init();
  void UnInit();
  bool IsClose() const;
  HANDLE thread_main_ = nullptr;
  std::atomic_bool ready_ = false;
  std::atomic_bool open_ = false;
  ServerStatus m_ServerStatus = ServerStatus::UNKNOWN;
  // const unsigned long m_Identify;
  std::atomic_bool m_FirstLogicalEventTriggerFlag = false;
  stl::container::multimap<CommandType, std::string> m_WriteBufferQ;
};

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 19 May 2023 10:23:40 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__2BFBE9A5_EDD9_447B_A673_9BACBBD7CBB8__