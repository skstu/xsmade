#if !defined(__A6E39744_9A1D_4019_B6A3_33C44071925C__)
#define __A6E39744_9A1D_4019_B6A3_33C44071925C__

class Perform {
public:
  Perform(const std::string &cmdline);
  ~Perform();

public:
  void Release() const;
  void Run();

public:
private:
  std::atomic_bool open_ = false;
  stl::CmdLine *cmdline_ = nullptr;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 12 Nov 2024 11:26:03 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__A6E39744_9A1D_4019_B6A3_33C44071925C__