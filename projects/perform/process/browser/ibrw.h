#if !defined(__66D36CE1_C3F0_4601_8CB0_3DCE31E2D698__)
#define __66D36CE1_C3F0_4601_8CB0_3DCE31E2D698__
//!@ Browser Interface Service

enum class RequestType : unsigned long long {
  UNKNOWN = 0x00000,
  SERVER_OPEN = 0x10010,   //!@ 打开(初始化)服务
  SERVER_CLOSE = 0x10020,  //!@ 退出(关闭)服务
  BROWSER_OPEN = 0x10101,  //!@ 打开浏览器
  BROWSER_CLOSE = 0x10102, //!@ 关闭浏览器
  BROWSER_GET = 0x10103,   //!@ 获取浏览器列表
  FFX_START_SCREEN_RECORDING = 0x10201,
  FFX_STOP_SCREEN_RECORDING = 0x10202,
  PLUGIN_FFXUI_OPEN = 0x10301,
  PLUGIN_FFXUI_CLOSE = 0x10302,
  // BROWSER_DOWN = 0x10104,  //!@ 下载浏览器
};
class IBrowserInterfaceServer final : public IPerform {
public:
  IBrowserInterfaceServer();
  ~IBrowserInterfaceServer();

public:
  bool Start() override final;
  void Stop() override final;
  void Process();
  unsigned short GetPort() const;
  void Release() const override final;
  IConfig *ConfigGet() const override final;

private:
  void Init();
  void UnInit();
  void Listen();
  void OnRequest(const RequestType &, const std::string &body,
                 std::string &res);
  unsigned short port_ = 0;
  std::atomic_bool open_ = false;
  stl::container::queue<std::string> client_notifys_;
  stl::tfThreads threads_;
  httplib::Server *server_ = nullptr;
  BrowserConfig *config_ = nullptr;
  stl::container::map<std::string /*key*/, Browser *> brws_;

protected:
  void __impl__() const override final {}
};
/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 11 Nov 2024 09:56:22 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__66D36CE1_C3F0_4601_8CB0_3DCE31E2D698__