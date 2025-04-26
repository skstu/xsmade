#if !defined(__EFF64F83_4CF2_4F00_8BBA_5B5261CB65BA__)
#define __EFF64F83_4CF2_4F00_8BBA_5B5261CB65BA__

class Uvpp final : public IUvpp {
public:
  static Uvpp *Create();
  static void Destroy();

private:
  Uvpp();
  virtual ~Uvpp();
  void Init();
  void UnInit();

  stl::tfThreads threads_;
  std::atomic_bool open_ = false;
  static void WorkProcess(uv_handle_t *handle, void *arg);
  void MainProcess();

protected:
  IConfig *ConfigGet() const override final;
  IService *CreateSevice() const override final;
  IBuffer *CreateBuffer(const char *, size_t) const override final;
  bool Start() override final;
  void Stop() override final;
  bool Ready() const override final;

private:
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};
/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 03 Dec 2024 02:22:24 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__EFF64F83_4CF2_4F00_8BBA_5B5261CB65BA__