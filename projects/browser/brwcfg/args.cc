#include "brwcfg.h"

Args::Args() {
}
Args::Args(const std::string &u8key) {
  key_ = new Buffer(u8key);
  ispath_ = false;
}
Args::Args(const std::string &u8key, const std::string &u8value,
           const bool &ispath) {
  key_ = new Buffer(u8key);
  value_ = new Buffer(u8value);
  ispath_ = ispath;
}
Args::~Args() {
  if (key_)
    key_->Release();
  if (value_)
    value_->Release();
}
void Args::Release() const {
  delete this;
}
IBrwcfg::IBuffer *Args::GetKey() const {
  return dynamic_cast<IBrwcfg::IBuffer *>(key_);
}
IBrwcfg::IBuffer *Args::GetValue() const {
  return dynamic_cast<IBrwcfg::IBuffer *>(value_);
}
bool Args::IsPath() const {
  return ispath_;
}
///////////////////////////////////////////////////////////////////////////////////
ArgsArray::ArgsArray() {
}

ArgsArray::~ArgsArray() {
  for (auto &data : source_) {
    data->Release();
  }
  source_.clear();
}
size_t ArgsArray::Total() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return source_.size();
}
IBrwcfg::IArgs *ArgsArray::Next(const size_t &idx) const {
  IBrwcfg::IArgs *result = nullptr;
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
    result = dynamic_cast<IBrwcfg::IArgs *>(*it);
  } while (0);
  return result;
}
void ArgsArray::Release() const {
  delete this;
}
void ArgsArray::Push(Args *ext) {
  std::lock_guard<std::mutex> lock{*mtx_};
  source_.emplace_back(ext);
}