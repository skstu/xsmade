#include <brwcfg.h>

Data::Data() : source_(nullptr), source_len_(0) {
}
Data::Data(const char *src, const size_t &len) {
  if (src && len > 0) {
    source_len_ = len;
    source_ = (char *)malloc(source_len_);
    memcpy(source_, src, source_len_);
  }
}
Data::~Data() {
  free(source_);
}
void Data::Release() const {
  delete this;
}
void *Data::GetData() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return source_;
}
size_t Data::GetSize() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return source_len_;
}
void Data::SetData(const void *src, const size_t &len) {
  std::lock_guard<std::mutex> lock{*mtx_};
  source_len_ = len;
  free(source_);
  source_ = nullptr;
  if (source_len_ > 0) {
    source_ = (char *)malloc(source_len_);
    memcpy(source_, src, len);
  }
}
