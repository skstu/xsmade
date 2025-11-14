#if !defined(__840E397A_D05F_4982_851D_C850B9CECADE__)
#define __840E397A_D05F_4982_851D_C850B9CECADE__

class IDeviceFingerprint {
protected:
  IDeviceFingerprint();
  virtual ~IDeviceFingerprint();
  bool InitPlatform();
  bool SelectBrowser();
  const bool &IsGoogleChrome() const;
  const bool &IsMicrosoftEdge() const;
  bool EnableGpu();
  bool UseAngleSwiftshader();
  bool InitFpsUtil();
  bool InitFpsHash();
  bool InitCdmRegistry();
  bool InitFont();
  bool InitATI();
  bool InitVoiceAndLanguages();
  bool InitScreen();

protected:
  chromium::xsiumio::IXSiumio xscfg_;
  chromium::xsiumio::IFpsdb fpsdb_;
  int platform_key_ = -1;
  bool isGoogleChrome_ = false;
  bool isMicrosoftEdge_ = false;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 16 Sep 2025 06:07:58 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__840E397A_D05F_4982_851D_C850B9CECADE__