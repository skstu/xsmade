#include <wxui.h>

IFrameComponent::IFrameComponent(const FrameComponentType &type) : type_(type) {
}
const FrameComponentType &IFrameComponent::Type() const {
  return type_;
}