#include <brwcfg.h>

DataArray::DataArray() {
}

DataArray::~DataArray() {
  for (auto &data : source_) {
    data->Release();
  }
  source_.clear();
}

void DataArray::Release() const {
  delete this;
}
void DataArray::Push(IBrwcfg::IData *data) {
  std::lock_guard<std::mutex> lock{*mtx_};
  auto in_data = dynamic_cast<Data *>(data);
  if (in_data) {
    source_.emplace_back(in_data);
  }
}
IBrwcfg::IData *DataArray::CreateData(const char *data, const size_t &len) {
  IBrwcfg::IData *result = nullptr;
  std::lock_guard<std::mutex> lock{*mtx_};
  if (data && len > 0) {
    auto new_data = new Data(data, len);
    source_.emplace_back(new_data);
    result = dynamic_cast<IBrwcfg::IData *>(new_data);
  }
  return result;
}
IBrwcfg::IData *DataArray::Next(const size_t &idx) const {
  IBrwcfg::IData *result = nullptr;
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
    result = dynamic_cast<IBrwcfg::IData *>(*it);
  } while (0);
  return result;
}
size_t DataArray::Total() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return source_.size();
}
