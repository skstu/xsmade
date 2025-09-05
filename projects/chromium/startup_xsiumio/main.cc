#include "config.h"

// 添加：按指定时区获取秒级/微秒级时间戳（临时设置 TZ 然后恢复）
static std::time_t TimeStampForZoneSeconds(const char *tzName) {
  std::string oldtz;
#ifndef _WIN32
  const char *old = std::getenv("TZ");
  if (old)
    oldtz = old;
  setenv("TZ", tzName, 1);
  tzset();
#else
  const char *old = std::getenv("TZ");
  if (old)
    oldtz = old;
  _putenv_s("TZ", tzName);
  _tzset();
#endif

  std::time_t now = std::time(nullptr);
  struct tm gm = *std::gmtime(&now);
  struct tm loc = *std::localtime(&now);
  std::time_t gm_t = std::mktime(&gm);
  std::time_t loc_t = std::mktime(&loc);
  std::time_t res = now + (loc_t - gm_t);

#ifndef _WIN32
  if (!oldtz.empty())
    setenv("TZ", oldtz.c_str(), 1);
  else
    unsetenv("TZ");
  tzset();
#else
  if (!oldtz.empty())
    _putenv_s("TZ", oldtz.c_str());
  else
    _putenv_s("TZ", "");
  _tzset();
#endif
  return res;
}

static long long TimeStampForZoneMicroseconds(const char *tzName) {
  // setup TZ
  std::string oldtz;
#ifndef _WIN32
  const char *old = std::getenv("TZ");
  if (old)
    oldtz = old;
  setenv("TZ", tzName, 1);
  tzset();
#else
  const char *old = std::getenv("TZ");
  if (old)
    oldtz = old;
  _putenv_s("TZ", tzName);
  _tzset();
#endif

  auto now = std::chrono::system_clock::now();
  auto us_total = std::chrono::duration_cast<std::chrono::microseconds>(
                      now.time_since_epoch())
                      .count();
  std::time_t secs = static_cast<std::time_t>(us_total / 1000000);
  long long micros = us_total % 1000000;

  struct tm gm = *std::gmtime(&secs);
  struct tm loc = *std::localtime(&secs);
  std::time_t gm_t = std::mktime(&gm);
  std::time_t loc_t = std::mktime(&loc);
  long long offset = static_cast<long long>(loc_t - gm_t);

#ifndef _WIN32
  if (!oldtz.empty())
    setenv("TZ", oldtz.c_str(), 1);
  else
    unsetenv("TZ");
  tzset();
#else
  if (!oldtz.empty())
    _putenv_s("TZ", oldtz.c_str());
  else
    _putenv_s("TZ", "");
  _tzset();
#endif

  return (static_cast<long long>(secs) + offset) * 1000000LL + micros;
}

// 计算从公元 1970-01-01 到某个公历日期的天数（Howard Hinnant 算法，纯算术）
static constexpr int64_t days_from_civil(int y, unsigned m,
                                         unsigned d) noexcept {
  y -= m <= 2;
  const int64_t era = (y >= 0 ? y : y - 399) / 400;
  const unsigned yoe = static_cast<unsigned>(y - era * 400);
  const unsigned doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;
  const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
  return era * 146097 + static_cast<int64_t>(doe) - 719468;
}

// 由时间点计算 America/New_York 相对于 UTC 的偏移（分钟）
// 返回值示例：-300 表示 UTC-5，小时时区西移；夏令时返回 -240（UTC-4）。
static int
OffsetMinutesForAmericaNewYork(std::chrono::system_clock::time_point tp =
                                   std::chrono::system_clock::now()) {
  using namespace std::chrono;
  // 秒级 UTC 时间
  const int64_t tsec = duration_cast<seconds>(tp.time_since_epoch()).count();
  const int64_t days = floor(static_cast<long double>(tsec) / 86400.0L);
  // 计算 UTC 的公历年（基于 days since epoch）
  int64_t z = days + 719468; // reverse of days_from_civil
  const int64_t era = (z >= 0 ? z : z - 146096) / 146097;
  const unsigned doe = static_cast<unsigned>(z - era * 146097);
  const unsigned yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;
  int year = static_cast<int>(yoe) + static_cast<int>(era * 400);
  const unsigned doy = doe - (365 * yoe + yoe / 4 - yoe / 100);
  const unsigned mp = (5 * doy + 2) / 153;
  unsigned month = mp + (mp < 10 ? 3u : -9u); // temporary; not used further
  year += (month <= 2);

  // 计算当年第二个周日（Sunday）三月的日期
  auto weekday_of = [](int y, unsigned m, unsigned d) noexcept -> int {
    // Zeller-like weekday: 0 = Sunday ... 6 = Saturday
    int Y = y;
    unsigned M = m;
    if (M <= 2) {
      Y--;
      M += 12;
    }
    int K = Y % 100;
    int J = Y / 100;
    int q = d;
    int h =
        (q + (13 * (M + 1)) / 5 + K + K / 4 + J / 4 + 5 * J) % 7; // 0=Saturday
    int dow = (h + 6) % 7; // convert: 0=Sunday
    return dow;
  };

  int w_mar1 = weekday_of(year, 3, 1);
  int first_sunday_march = 1 + ((7 - w_mar1) % 7);
  int second_sunday_march = first_sunday_march + 7;

  int w_nov1 = weekday_of(year, 11, 1);
  int first_sunday_nov = 1 + ((7 - w_nov1) % 7);

  // transition local times: 2:00 local
  // start UTC = local(YYYY-03-second_sunday,02:00) + 5h (because before start =
  // standard time UTC-5) end UTC   = local(YYYY-11-first_sunday,02:00) + 4h
  // (because before end = daylight time UTC-4)
  int64_t start_local_days =
      days_from_civil(year, 3u, static_cast<unsigned>(second_sunday_march));
  int64_t end_local_days =
      days_from_civil(year, 11u, static_cast<unsigned>(first_sunday_nov));

  int64_t start_utc_sec =
      start_local_days * 86400 + 2 * 3600 + 5 * 3600; // +5h -> to UTC
  int64_t end_utc_sec =
      end_local_days * 86400 + 2 * 3600 + 4 * 3600; // +4h -> to UTC

  if (tsec >= start_utc_sec && tsec < end_utc_sec) {
    return -4 * 60; // DST in effect
  }
  return -5 * 60; // standard time
}

static void mpak(void);
#ifdef __OSWIN__
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
// int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR __cmdline__,
//                      int cmdshow)
int main(int argc, char *args[])
#elif defined(__OSLINUX__)
int main(int argc, char *args[])
#endif
{
  if (0 == xs_sys_process_already_exists(0))
    return 1;

  // do { //!@ timezone
  //   auto newYork = TimeStampForZoneMicroseconds("Asia/Shanghai");

  //   int offset = OffsetMinutesForAmericaNewYork();
  //   auto xx = 0;
  // } while (0);
  // do {
  //   std::map<std::string, std::string> files, dirs;
  //   stl::Directory::Enum(
  //       R"(C:\Users\k34ub\source\skstu\xsmade\bin\model_parts)",
  //       dirs, files, false);
  //   std::set<double> canvas, audio, webgl;
  //   for (auto &f : files) {
  //     do {
  //       auto fb = stl::File::ReadFile(f.second);
  //       if (fb.empty())
  //         break;
  //       rapidjson::Document doc;
  //       if (doc.Parse(fb.c_str(), fb.size()).HasParseError())
  //         break;
  //       if (!doc.IsObject())
  //         break;
  //       if (!doc.HasMember("xsiumio") || !doc["xsiumio"].IsObject())
  //         break;
  //       canvas.emplace(doc["xsiumio"]["fingerprint"]["canvas"]["hash"]["base"]
  //                          .GetDouble());
  //       webgl.emplace(
  //           doc["xsiumio"]["fingerprint"]["webgl"]["hash"]["base"].GetDouble());
  //       audio.emplace(
  //           doc["xsiumio"]["fingerprint"]["audio"]["hash"]["base"].GetDouble());
  //     } while (0);
  //   }

  //   double max_canvas(0.0), min_canvas(0.0), max_webgl(0.0), min_webgl(0.0),
  //       max_audio(0.0), min_audio(0.0);
  //   std::string canvas_output, webgl_output, audio_output;
  //   for (const auto &v : canvas) {
  //     if (v > max_canvas)
  //       max_canvas = v;
  //     if (v < min_canvas || !min_canvas)
  //       min_canvas = v;
  //     canvas_output.append(stl::Common::DoubleToString(v)).append(",");
  //   }
  //   canvas_output.append("\n")
  //       .append(stl::Common::DoubleToString(min_canvas))
  //       .append("\n")
  //       .append(stl::Common::DoubleToString(max_canvas));

  //   for (const auto &v : webgl) {
  //     if (v > max_webgl)
  //       max_webgl = v;
  //     if (v < min_webgl || !min_webgl)
  //       min_webgl = v;
  //     webgl_output.append(stl::Common::DoubleToString(v)).append(",");
  //   }
  //   webgl_output.append("\n")
  //       .append(stl::Common::DoubleToString(min_webgl))
  //       .append("\n")
  //       .append(stl::Common::DoubleToString(max_webgl));

  //   for (const auto &v : audio) {
  //     if (v > max_audio)
  //       max_audio = v;
  //     if (v < min_audio || !min_audio)
  //       min_audio = v;
  //     audio_output.append(stl::Common::DoubleToString(v)).append(",");
  //   }
  //   audio_output.append("\n")
  //       .append(stl::Common::DoubleToString(min_audio))
  //       .append("\n")
  //       .append(stl::Common::DoubleToString(max_audio));

  //   stl::Directory::Create(R"(C:\Users\k34ub\Desktop\AdsModes)");
  //   stl::File::WriteFile(R"(C:\Users\k34ub\Desktop\AdsModes\canvas.txt)",
  //                        canvas_output);
  //   stl::File::WriteFile(R"(C:\Users\k34ub\Desktop\AdsModes\audio.txt)",
  //                        audio_output);
  //   stl::File::WriteFile(R"(C:\Users\k34ub\Desktop\AdsModes\webgl.txt)",
  //                        webgl_output);
  //   auto sss = 0;
  // } while (0);

  char *__cmdline__ = nullptr;
  size_t __cmdline_size__ = 0;
  xs_sys_get_commandline(&__cmdline__, &__cmdline_size__);
  if (!__cmdline__)
    return 0;
  stl::tfCommandLines cmdline = stl::CmdLine::ParserCommandLines(
      std::string(__cmdline__, __cmdline_size__), false);
  xs_sys_free((void **)&__cmdline__);

  auto f_mode = cmdline.find("--mode");
  Config::CreateOrGet();
  if (f_mode->second == "service") {
    Startup::GetOrCreate(RunMode::kModeService)->Run();
  } else if (f_mode->second == "m0") {
    Startup::GetOrCreate(RunMode::kModelLevel0)->Run();
  } else if (f_mode->second == "mpak") {
    mpak();
  } else {
    std::cout << "This is a developer's command that is not open to the public."
              << std::endl;
    // std::this_thread::sleep_for(std::chrono::seconds(10));
  }

  // stl::MainProc([](const std::string &input, bool &exit_flag) {
  //   if (input == "q") {
  //     exit_flag = true;
  //   } else if (input == "obrw") {

  //   } else if (input == "cbrw") {

  //   } else {
  //     std::cout << "You entered: " << input << std::endl;
  //   }
  // });
  Config::Destroy();
  return 0;
}

#if 0

  if (f_mode == cmdline.end()) {
    Startup::GetOrCreate()->Run();
  } else if (f_mode->second == "model_level_0") {
    //Startup::GetOrCreate(RunMode::kModelLevel0)->Run();
  } else if (f_mode->second == "model_level_1") {
    Startup::GetOrCreate(RunMode::kModelLevel1)->Run();
  } else if (f_mode->second == "model_level_2") {
    //Startup::GetOrCreate(RunMode::kModelLevel2)->Run();
  } else if (f_mode->second == "model_level_3") {
    //Startup::GetOrCreate(RunMode::kModelLevel3)->Run();
  } else if (f_mode->second == "production" || f_mode->second == "release") {
    //Startup::GetOrCreate(RunMode::kProductionModel)->Run();
  } else {
    //Startup::GetOrCreate()->Run();
  }

#endif

void mpak(void) {
  do {
    const std::string __cd__ = Config::CreateOrGet()->GetCurrentDir();
    const std::string model_parts_dir =
        Config::CreateOrGet()->GetProjectModelPartsDir();
    const std::string fpsdb_path =
        Config::CreateOrGet()->GetProjectConfiguresDir() + "/fpsdb.json";
    const std::string model_output_dir = __cd__ + R"(/model)";
    stl::Directory::Create(model_output_dir);
    const std::string model_output_file = model_output_dir + "/model.bin";
    const std::string fpsdb_buffer = stl::File::ReadFile(fpsdb_path);
    if (!stl::Directory::Exists(model_parts_dir) ||
        !stl::File::Exists(fpsdb_path)) {
      std::cout << "Model parts dir not exists!" << std::endl;
      break;
    }

    chromium::tfRouteRes paks;
    paks.emplace(static_cast<chromium::tfRouteIndex>(ModelKey::kFpsdb),
                 stl::String::WemadeEncode(fpsdb_buffer));

    std::map<std::string, std::string> dirs, files;
    stl::Directory::Enum(__cd__ + R"(\model_parts)", dirs, files, false);
    if (files.empty()) {
      std::cout << "No model parts found!" << std::endl;
    }

    chromium::tfRouteIndex index =
        static_cast<chromium::tfRouteIndex>(ModelKey::kModelPartsBegin);
    for (const auto &f : files) {
      std::string part_buffer = stl::File::ReadFile(f.second);
      if (part_buffer.empty())
        continue;
      paks.emplace(index, stl::String::WemadeEncode(part_buffer));
      ++index;
    }

    chromium::Packet packet;
    chromium::tfRoutePak route_data;
    if (!packet.made(paks, route_data)) {
      std::cout << "Packet made failed!" << std::endl;
      break;
    }
    stl::File::WriteFile(model_output_file, route_data);

    std::cout << "Model paked success! total " << paks.size()
              << " parts, output: " << model_output_file << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
  } while (0);
}