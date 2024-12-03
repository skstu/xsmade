#if !defined(__8E3607D2_F65F_4D20_A47C_29E2F4429D98__)
#define __8E3607D2_F65F_4D20_A47C_29E2F4429D98__

class FFmpeg final : public IComponent {
public:
  FFmpeg();
  virtual ~FFmpeg();

protected:
  bool Start() override final;
  void Stop() override final;
  const std::string &GetName() const override final;
  const std::uint64_t &GetIdentify() const override final;

private:
  std::string name_;
  std::uint64_t identify_ = 0;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 02 Dec 2024 07:43:29 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__8E3607D2_F65F_4D20_A47C_29E2F4429D98__