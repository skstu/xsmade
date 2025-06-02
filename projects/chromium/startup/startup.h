#if !defined(__7E6F1235_B1C6_494E_AA3B_3D1D6174F41E__)
#define __7E6F1235_B1C6_494E_AA3B_3D1D6174F41E__

class Startup {
public:
  Startup(const Startup &) = delete;
  Startup &operator=(const Startup &) = delete;
  void *operator new(size_t) = delete;
  void operator delete(void *) = delete;
  ~Startup();
  Startup();

public:
  void Run() const;

private:
  void Init();
  void UnInit();

private:
  std::atomic_bool ready_ = false;
  Server* server_ = nullptr;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 30 May 2025 00:05:44 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__7E6F1235_B1C6_494E_AA3B_3D1D6174F41E__