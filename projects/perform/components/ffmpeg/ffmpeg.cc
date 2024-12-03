#include "config.h"

FFmpeg::FFmpeg() {
}
FFmpeg::~FFmpeg() {
}
bool FFmpeg::Start() {
  return false;
}
void FFmpeg::Stop() {
}
const std::string &FFmpeg::GetName() const {
  return name_;
}
const std::uint64_t &FFmpeg::GetIdentify() const {
  return identify_;
}