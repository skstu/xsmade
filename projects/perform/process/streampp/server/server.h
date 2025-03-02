#if !defined(__1E58097F_BFC9_47B2_98AB_96E3DC84A7E9__)
#define __1E58097F_BFC9_47B2_98AB_96E3DC84A7E9__

namespace streampp {
class Server {
public:
  Server();
  virtual ~Server();

private:
  std::vector<uvpp::IService *> services_;
};
} // namespace streampp
/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 09 Dec 2024 10:02:37 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__1E58097F_BFC9_47B2_98AB_96E3DC84A7E9__