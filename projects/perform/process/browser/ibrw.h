#if !defined(__66D36CE1_C3F0_4601_8CB0_3DCE31E2D698__)
#define __66D36CE1_C3F0_4601_8CB0_3DCE31E2D698__
//!@ Browser Interface Service
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
  stl::container::queue<
      std::tuple<std::string /*http.path*/, std::string /*content*/>>
      client_notifys_;
  stl::tfThreads threads_;
  httplib::Server *server_ = nullptr;
  BrowserConfig *config_ = nullptr;
  stl::container::map<std::string /*key*/, Browser *> brws_;
  wxui::IWxui *gpsWxui = nullptr;
  std::atomic_bool gbWxuiStatus = false;

protected:
  void __impl__() const override final {
  }
};
/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 11 Nov 2024 09:56:22 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__66D36CE1_C3F0_4601_8CB0_3DCE31E2D698__