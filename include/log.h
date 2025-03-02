#if !defined(__ACF37D9A_0520_4D8A_83D8_97370985981D__)
#define __ACF37D9A_0520_4D8A_83D8_97370985981D__
#define SPDLOG_WCHAR_TO_UTF8_SUPPORT
#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/details/fmt_helper.h>
#include <spdlog/details/os.h>

#ifndef SPDLOG_NO_TLS
#include <spdlog/mdc.h>
#endif

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/null_sink.h>
#include <spdlog/sinks/ostream_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/msvc_sink.h>
#include <spdlog/pattern_formatter.h>

template <typename... Args>
inline void log_warn(const std::string &msg, Args &&...args) {
  spdlog::warn(msg.c_str(), std::forward<Args>(args)...);
}

template <typename... Args>
inline void log_info(const std::string &msg, Args &&...args) {
  spdlog::info(msg.c_str(), std::forward<Args>(args)...);
}

template <typename... Args>
inline void log_error(const std::string &msg, Args &&...args) {
  spdlog::error(msg.c_str(), std::forward<Args>(args)...);
}
#if defined(SPDLOG_WCHAR_TO_UTF8_SUPPORT)
template <typename... Args>
inline void log_warn(const std::wstring &msg, Args &&...args) {
  spdlog::warn(msg.c_str(), std::forward<Args>(args)...);
}

template <typename... Args>
inline void log_info(const std::wstring &msg, Args &&...args) {
  spdlog::info(msg.c_str(), std::forward<Args>(args)...);
}

template <typename... Args>
inline void log_error(const std::wstring &msg, Args &&...args) {
  spdlog::error(msg.c_str(), std::forward<Args>(args)...);
}
#endif

#if 0
  // log_warn("Easy padding in numbers like {:08d}", 12);
  // log_warn(L"Easy padding in numbers like {:08d}", 18);
  spdlog::file_event_handlers handlers;
  handlers.before_open = [](spdlog::filename_t filename) {
    spdlog::info("Before opening {}", filename);
  };
  handlers.after_open = [](spdlog::filename_t filename, std::FILE *fstream) {
    spdlog::info("After opening {}", filename);
    fputs("After opening\n", fstream);
  };
  handlers.before_close = [](spdlog::filename_t filename, std::FILE *fstream) {
    spdlog::info("Before closing {}", filename);
    fputs("Before closing\n", fstream);
  };
  handlers.after_close = [](spdlog::filename_t filename) {
    spdlog::info("After closing {}", filename);
  };
  auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
      "c:/logs/events-sample.txt", true, handlers);
  spdlog::logger my_logger("some_logger", file_sink);
  my_logger.info("Some log line");
#endif
#if 0
  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  console_sink->set_level(spdlog::level::warn);
  console_sink->set_pattern("[multi_sink_example] [%^%l%$] %v");

  auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
      "c:/logs/multisink.txt", true);
  file_sink->set_level(spdlog::level::trace);

  spdlog::logger logger("multi_sink", {console_sink, file_sink});
  logger.set_level(spdlog::level::debug);
  logger.warn("this should appear in both console and file");
  logger.info(
      "this message should not appear in the console, only in the file");
#endif
/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 02 Feb 2025 02:48:00 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__ACF37D9A_0520_4D8A_83D8_97370985981D__