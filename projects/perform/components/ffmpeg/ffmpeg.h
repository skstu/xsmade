#if !defined(__8E3607D2_F65F_4D20_A47C_29E2F4429D98__)
#define __8E3607D2_F65F_4D20_A47C_29E2F4429D98__

class FFmpeg final : public local::IComponent {
public:
  FFmpeg();
  virtual ~FFmpeg();

protected:
  void Release() const override final;
  bool Start(const std::vector<std::string> &cmdline,
             const bool &show) override final;
  void Stop() override final;

private:
  std::atomic_bool open_ = false;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 02 Dec 2024 07:43:29 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__8E3607D2_F65F_4D20_A47C_29E2F4429D98__