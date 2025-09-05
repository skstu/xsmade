#include "stl.hpp"
using namespace stl;
using namespace std;
unsigned long long Time::GoogleTimestamp() {
  const unsigned long long EPOCH_DIFF_US =
      11644473600000000ULL; // 1601->1970 in µs
  auto now = std::chrono::system_clock::now();
  auto us =
      std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
  unsigned long long micros_since_1601 =
      static_cast<unsigned long long>(us) + EPOCH_DIFF_US;
  return micros_since_1601;
}
std::string Time::GetLogTimeCN() {
  auto now = std::chrono::system_clock::now();
  std::time_t now_c = std::chrono::system_clock::to_time_t(now);
  std::stringstream ss;
  ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S");
  return ss.str();
}
unsigned long Time::GetDateDay() {
  string strDate = GetDateDayString();
  return strtoul(strDate.c_str(), nullptr, 10);
}
string Time::GetDateDayString() {
  time_t t = time(nullptr);
  tm *tm = localtime(&t);
  char buffer[64] = {0};
  size_t buffer_len = strftime(buffer, sizeof(buffer), "%Y%m%d", tm);
  return string(buffer, buffer_len);
}
string Time::CurrentDateA() {
  time_t t = time(nullptr);
  tm *tm = localtime(&t);
  char buffer[64] = {0};
  size_t buffer_len = strftime(buffer, sizeof(buffer), "%Y-%m-%d", tm);
  return string(buffer, buffer_len);
}

wstring Time::CurrentDateW() {
  time_t t = time(nullptr);
  tm *tm = localtime(&t);
  wchar_t buffer[64] = {0};
  size_t buffer_len = wcsftime(buffer, sizeof(buffer), L"%Y-%m-%d", tm);
  return wstring(buffer, buffer_len);
}

/*
 * 2023-04-29T13:39:25+0800
 * 2023-04-29T13:39:25.724+0800
 */
static std::string format_current_time(bool with_milliseconds) {
  auto now = std::chrono::system_clock::now();
  std::time_t now_c = std::chrono::system_clock::to_time_t(now);
  std::stringstream ss;
  ss << std::put_time(std::gmtime(&now_c), "%FT%T");
  if (with_milliseconds) {
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                  now.time_since_epoch()) %
              1000;
    ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
  }
  ss << std::put_time(std::gmtime(&now_c), "%z");
  return ss.str();
}
/* 获取本地时区的偏移量
 * ISO 标准时间表示法中，字母 "Z" 表示协调世界时（UTC）时间。它表示时间与 UTC
 * 时间相同，即没有时区偏移量 result: +0800 or Z
 *
 */
std::string GetLocalTimezoneOffset() {
  std::string result;
  std::time_t now = std::time(nullptr);
  std::tm local_tm = *std::localtime(&now);
  std::tm utc_tm = *std::gmtime(&now);
  // 本地时区的偏移量为UTC时间减去本地时间的秒数
  int local_offset_seconds = static_cast<int>(
      std::difftime(std::mktime(&local_tm), std::mktime(&utc_tm)));
  int hours = local_offset_seconds / 3600;
  int minutes = std::abs(local_offset_seconds % 3600) / 60;
  // 生成偏移量的字符串表示
  if (hours == 0) {
    result = "Z";
  } else {
    result = ((hours >= 0) ? "+" : "-") +
             (hours < 10 ? "0" + std::to_string(std::abs(hours))
                         : std::to_string(std::abs(hours))) +
             (minutes < 10 ? "0" + std::to_string(minutes)
                           : std::to_string(minutes));
  }
  return result;
}
