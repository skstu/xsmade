#if !defined(__0B1DC6A0_CC0F_41C4_94F9_ACA9A35E8A52__)
#define __0B1DC6A0_CC0F_41C4_94F9_ACA9A35E8A52__

class Config final : public IBrwcfg::IConfig {
public:
  static Config *Create();
  static void Destroy();

protected:
  bool EnableDevTools(void) const override final;
  bool EnableShowBadFlagsSecurityWarnings(void) const override final;
  bool EnableLockFirstTabPage(void) const override final;
  bool EnableProductLogo(void) const override final;
  bool EnableSessionCrashedBubbleViewShow(void) const override final;

private:
  Config();
  virtual ~Config();
};

/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 07 Jan 2025 06:56:48 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__0B1DC6A0_CC0F_41C4_94F9_ACA9A35E8A52__
