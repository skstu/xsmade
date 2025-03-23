#include "brwcfg.h"

Buffer::Buffer(const std::string &data) : source_(data) {
}
Buffer::Buffer(const char *data, const size_t &len) : source_(data, len) {
}
Buffer::~Buffer() {
}
const char *Buffer::GetData() const {
  return source_.data();
}
size_t Buffer::GetSize() const {
  return source_.size();
}
void Buffer::Release() const {
  delete this;
}
///////////////////////////////////////////////////////////////////////////////////
BufferArray::BufferArray() {
}

BufferArray::~BufferArray() {
  for (auto &data : source_) {
    data->Release();
  }
  source_.clear();
}

void BufferArray::Release() const {
  delete this;
}
void BufferArray::Push(Buffer *buf) {
  source_.emplace_back(buf);
}
void BufferArray::Push(const std::string &u8) {
  source_.emplace_back(new Buffer(u8));
}
void BufferArray::Push(const std::u16string &u16) {
  std::string u8 = Conv::u16_to_u8(u16);
  source_.emplace_back(new Buffer(u8));
}
void BufferArray::Push(const char *u8, const size_t &len) {
  Buffer *buf = new Buffer(u8, len);
  source_.emplace_back(buf);
}
void BufferArray::Push(IBrwcfg::IBuffer *data) {
  std::lock_guard<std::mutex> lock{*mtx_};
  auto in_data = dynamic_cast<Buffer *>(data);
  if (in_data) {
    source_.emplace_back(in_data);
  }
}
IBrwcfg::IBuffer *BufferArray::CreateBuffer(const char *data,
                                            const size_t &len) {
  IBrwcfg::IBuffer *result = nullptr;
  std::lock_guard<std::mutex> lock{*mtx_};
  if (data && len > 0) {
    auto new_data = new Buffer(data, len);
    source_.emplace_back(new_data);
    result = dynamic_cast<IBrwcfg::IBuffer *>(new_data);
  }
  return result;
}
IBrwcfg::IBuffer *BufferArray::Next(const size_t &idx) const {
  IBrwcfg::IBuffer *result = nullptr;
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
    result = dynamic_cast<IBrwcfg::IBuffer *>(*it);
  } while (0);
  return result;
}
size_t BufferArray::Total() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return source_.size();
}