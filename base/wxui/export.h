#if !defined(__4132C3D7_60F3_49F7_BE5C_4B2B46C61895__)
#define __4132C3D7_60F3_49F7_BE5C_4B2B46C61895__

#include "interface.hpp"

namespace wxui {
using tfThemeIdentify = unsigned long;

enum class FrameType : long {
  FRAME = 0x00,
  MDIFRAME = 0x01,
  SHAPEFRAME = 0x02,
};
class IFrame {
public:
  virtual const FrameType &Type() const = 0;
  virtual void SetRegion(long x, long y, long cx, long cy) = 0;
};
class ITheme {
public:
  virtual void SetShapeImage(const char *) = 0;
  virtual void SetBackgroundImage(const char *) = 0;
  virtual tfThemeIdentify Identify() const = 0;
};
class IConfig {
public:
  virtual void SetFrameType(const FrameType &) = 0;
  virtual ITheme *CreateTheme() = 0;
};
class IWxui : public Interface<IWxui> {
public:
public:
  virtual bool Start() = 0;
  virtual void Stop() = 0;
  virtual IConfig *ConfigGet() const = 0;
  virtual IFrame *GetFrame() const = 0;
};
} // namespace wxui

/// /*_ Memade®（新生™） _**/
/// /*_ Thu, 28 Nov 2024 00:47:50 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__4132C3D7_60F3_49F7_BE5C_4B2B46C61895__
