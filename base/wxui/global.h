#if !defined(__EC4BDEC9_2CE6_4795_9E7C_A54E3A140380__)
#define __EC4BDEC9_2CE6_4795_9E7C_A54E3A140380__

class Global {
public:
  Global() = default;
  ~Global() = default;

public:
  static void ffxScaling(const float &scaling);
  static void ffxFullScreen(const bool &entry, const wxSize &prev_frame_tool,
                            const wxSize &perv_frame_shape);
  static void ffxShowWindow(const bool &flag);
  static void ffxSetPos(const wxRect &,
                        const CapturingHostType &captureType =
                            CapturingHostType::CAPTUREING_RECORDING);
  static void ffxLayout();
  static void ffxCenter();
  static void ffxTopmost();

  static void ffxHideScreenShotToolbar();
  static void ffxShowScreenShotToolbar(const wxRect &);

  static void ffxShowBkg(const bool &flag);
};

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 29 Nov 2024 22:18:05 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__EC4BDEC9_2CE6_4795_9E7C_A54E3A140380__