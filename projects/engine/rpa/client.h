#if !defined(__2FCBAEFB_8E2D_4552_9B60_739569E2E6CF__)
#define __2FCBAEFB_8E2D_4552_9B60_739569E2E6CF__

class Client final {
public:
  Client();
  virtual ~Client();

private:
  void Init();
  void UnInit();

private:
  uvpp::IService *uvclient_ = nullptr;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 18 Dec 2024 01:24:50 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__2FCBAEFB_8E2D_4552_9B60_739569E2E6CF__