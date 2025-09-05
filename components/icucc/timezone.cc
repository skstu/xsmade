#include "icucc.h"
// 把指定时区下的本地时间转成 UTC 微秒时间戳
// month: 1-12；usec: 0-999999
static bool LocalTimeToUtcMicrosecondsICU(const std::string &tzid, int year,
                                          unsigned month, unsigned day,
                                          unsigned hour, unsigned minute,
                                          unsigned second, unsigned usec,
                                          long long &out_utc_microseconds) {
  UErrorCode status = U_ZERO_ERROR;
  icu::UnicodeString uids = icu::UnicodeString::fromUTF8(tzid);
  std::unique_ptr<icu::TimeZone> tz(icu::TimeZone::createTimeZone(uids));
  std::unique_ptr<icu::Calendar> cal(
      icu::Calendar::createInstance(tz.get(), status));
  if (U_FAILURE(status))
    return false;

  // ICU month 从 0 开始
  cal->set(year, static_cast<int>(month - 1), static_cast<int>(day),
           static_cast<int>(hour), static_cast<int>(minute),
           static_cast<int>(second));
  cal->set(UCAL_MILLISECOND, static_cast<int>(usec / 1000));

  UDate utcMillis = cal->getTime(status); // 毫秒级 UTC timestamp
  if (U_FAILURE(status))
    return false;

  out_utc_microseconds =
      static_cast<long long>(static_cast<int64_t>(utcMillis)) * 1000LL +
      static_cast<long long>(usec % 1000);
  return true;
}

bool Icucc::GetZoneOffsetMinutes(const char *tzid, int &out_minutes,
                                 long long tp_ms) const {

  bool result = false;
  do {
    if (tp_ms <= 0)
      tp_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                  std::chrono::system_clock::now().time_since_epoch())
                  .count();
    UErrorCode status = U_ZERO_ERROR;
    icu::UnicodeString uids = icu::UnicodeString::fromUTF8(tzid);
    std::unique_ptr<icu::TimeZone> tz(
        icu::TimeZone::createTimeZone(uids)); // 若 id 无效会回退到 "GMT"
    // 可选：拿回 ICU 解析后的 ID 以检测回退
    icu::UnicodeString realId;
    tz->getID(realId);
    std::string realIdUtf8;
    realId.toUTF8String(realIdUtf8);

    // tp_ms 已经是毫秒单位
    UDate udate = static_cast<UDate>(tp_ms);

    int32_t rawOffsetMs = 0;
    int32_t dstOffsetMs = 0;
    tz->getOffset(udate, /*local*/ false, rawOffsetMs, dstOffsetMs, status);
    if (U_FAILURE(status))
      break;
    out_minutes =
        static_cast<int>((rawOffsetMs + dstOffsetMs) / 60000); // 毫秒->分钟
    result = true;
  } while (0);
  return result;
}