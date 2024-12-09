#if !defined(__F0C056AC_593B_44F9_873E_A2D6D3FAF12D__)
#define __F0C056AC_593B_44F9_873E_A2D6D3FAF12D__

class IServer {
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
/// /*_ Sun, 08 Dec 2024 00:38:13 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__F0C056AC_593B_44F9_873E_A2D6D3FAF12D__