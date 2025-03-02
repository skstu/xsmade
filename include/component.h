#if !defined(__DCD11EA8_96DE_4B34_8541_8B4740681958__)
#define __DCD11EA8_96DE_4B34_8541_8B4740681958__

#include "interface.hpp"

class IComponent : public Interface<IComponent> {
public:
  virtual bool Start() = 0;
  virtual void Stop() = 0;
  virtual bool Ready() const = 0;

protected:
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};

/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 01 Feb 2025 22:59:13 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__DCD11EA8_96DE_4B34_8541_8B4740681958__