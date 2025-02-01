#include "config.h"

Buffer::Buffer() {

}
Buffer::Buffer(const std::string& buf) : buffer_(buf) {

}
Buffer::Buffer(const char* data, const size_t& len) {
	if (data && len > 0)
		buffer_.append(data, len);
}
Buffer::~Buffer() {

}
void Buffer::Release() const {
	delete this;
}
bool Buffer::Empty() const {
	std::lock_guard<std::mutex> lock{ *mtx_ };
	return buffer_.empty();
}
const char* Buffer::GetData() const {
	std::lock_guard<std::mutex> lock{ *mtx_ };
	return buffer_.data();
}
IBuffer* Buffer::Clone() const {
	IBuffer* result = nullptr;
	std::lock_guard<std::mutex> lock{ *mtx_ };
	if (!buffer_.empty())
		result = dynamic_cast<IBuffer*>(new Buffer(buffer_.data(), buffer_.size()));
	return result;
}
size_t Buffer::GetDataSize() const {
	std::lock_guard<std::mutex> lock{ *mtx_ };
	return buffer_.size();
}
void Buffer::SetData(const char* data, const size_t& len) {
	std::lock_guard<std::mutex> lock{ *mtx_ };
	buffer_.clear();
	if (data && len > 0)
		buffer_.append(data, len);
}
std::string Buffer::GetString() const {
	std::lock_guard<std::mutex> lock{ *mtx_ };
	return buffer_;
}