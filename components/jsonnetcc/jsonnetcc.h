#if !defined(__B3F92BE2_1C3F_4DCB_87C6_682D16297803__)
#define __B3F92BE2_1C3F_4DCB_87C6_682D16297803__

#include <xs.h>
#include <json.hpp>
#include "export.h"

class Jsonnetcc final : public IJsonnetcc {
public:
  static Jsonnetcc *Create();
  static void Destroy();

private:
  Jsonnetcc();
  virtual ~Jsonnetcc();

public:
  bool Ready() const override final;

private:
  void Init();
  void UnInit();

private:
  std::atomic_bool ready_ = false;
};

/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 02 Feb 2025 14:33:44 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__B3F92BE2_1C3F_4DCB_87C6_682D16297803__
