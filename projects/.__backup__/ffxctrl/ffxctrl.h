#if !defined(__D25FAF9D_0CAE_46CA_903C_168D4186E068__)
#define __D25FAF9D_0CAE_46CA_903C_168D4186E068__

class FFXCtrl final : public IFFXCtrl {
public:
  static FFXCtrl *Create();
  static void Destroy();

private:
  FFXCtrl();
  virtual ~FFXCtrl();

protected:
  bool Start() override final;
  void Stop() override final;

private:
  void MainProc();
  stl::tfThreads threads_;
  std::atomic_bool open_ = false;
};

#ifdef __cplusplus
extern "C" {
#endif
SHARED_API void *interface_init(void *, unsigned long);
SHARED_API void interface_uninit();
#ifdef __cplusplus
}
#endif

/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 27 Nov 2024 03:59:30 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__D25FAF9D_0CAE_46CA_903C_168D4186E068__