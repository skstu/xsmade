#include "stl.hpp"

void stl::Signal::notify() {
  std::unique_lock<std::mutex> lock(mtx_);
  event_signaled_.store(true);
  cv_.notify_one();
}
void stl::Signal::reset() {
  std::unique_lock<std::mutex> lock(mtx_);
  event_signaled_.store(false);
}
void stl::Signal::Release() const {
  delete this;
}
bool stl::Signal::wait_for_event(
    std::chrono::milliseconds timeout /*= std::chrono::milliseconds(0)*/) {
  std::unique_lock<std::mutex> lock(mtx_);
  if (timeout == std::chrono::milliseconds(0)) {
    cv_.wait(lock, [this] { return event_signaled_.load(); });
  } else {
    auto wakeup_time = std::chrono::steady_clock::now() + timeout;
    while (!event_signaled_.load()) {
      if (cv_.wait_until(lock, wakeup_time) == std::cv_status::timeout) {
        return false;
      }
    }
  }
  return true;
}
