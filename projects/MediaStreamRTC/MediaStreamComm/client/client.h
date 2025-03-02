#if !defined(__0792731B_1368_412D_8E9B_B5301E88811A__)
#define __0792731B_1368_412D_8E9B_B5301E88811A__

class IClient {
public:
  virtual bool Start() = 0;
  virtual void Stop() = 0;
  virtual void Release() const = 0;

protected:
  uvpp::IUvpp *uvpp_ = nullptr;
  std::atomic_bool ready_ = false;
  std::atomic_bool open_ = false;
};

/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 08 Dec 2024 08:19:30 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__0792731B_1368_412D_8E9B_B5301E88811A__