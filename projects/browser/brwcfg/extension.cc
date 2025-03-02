#include "brwcfg.h"
Extension::Extension(const Buffer *root, const Buffer *manifest,
                     const bool &reload)
    : manifest_(manifest), root_(root), reload_(reload) {
}
Extension::~Extension() {
  if (manifest_)
    manifest_->Release();
  if (root_)
    root_->Release();
}
const IBrw::IBuffer *Extension::Manifest() const {
  return dynamic_cast<const IBrw::IBuffer *>(manifest_);
}
const IBrw::IBuffer *Extension::Root() const {
  return dynamic_cast<const IBrw::IBuffer *>(root_);
}
bool Extension::IsReload() const {
  return reload_;
}
void Extension::Release() const {
  delete this;
}
///////////////////////////////////////////////////////////////////////////////////
ExtensionArray::ExtensionArray() {
}

ExtensionArray::~ExtensionArray() {
  for (auto &data : source_) {
    data->Release();
  }
  source_.clear();
}
size_t ExtensionArray::Total() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return source_.size();
}
IBrw::IExtension *ExtensionArray::Next(const size_t &idx) const {
  IBrw::IExtension *result = nullptr;
  std::lock_guard<std::mutex> lock{*mtx_};
  do {
    if (source_.empty())
      break;
    if (idx >= source_.size())
      break;
    auto it = source_.begin();
    std::advance(it, idx);
    if (it == source_.end())
      break;
    result = dynamic_cast<IBrw::IExtension *>(*it);
  } while (0);
  return result;
}
void ExtensionArray::Release() const {
  delete this;
}
void ExtensionArray::Push(Extension *ext) {
  std::lock_guard<std::mutex> lock{*mtx_};
  source_.emplace_back(ext);
}