#if !defined(__CDA0FE42_5C23_4350_89DE_6EE9A7004DB7__)
#define __CDA0FE42_5C23_4350_89DE_6EE9A7004DB7__

#include "interface.hpp"
#include <tinyxml2.hpp>
#include "export.h"

class Settings final : public IXSiumioSettings {
public:
  static Settings *GetOrCreate();
  static void Destroy();
  void Release() const override final;
  bool operator<<(const std::string &);

private:
  Settings();
  virtual ~Settings();

private:
  void Init();
  void UnInit();

private:
  std::unique_ptr<std::mutex> mtx_ = std::make_unique<std::mutex>();
};
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 22 Feb 2025 05:04:36 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__CDA0FE42_5C23_4350_89DE_6EE9A7004DB7__