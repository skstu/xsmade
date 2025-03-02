#include "stl.hpp"
#include "conv.hpp"
#ifndef __RUNTIMES_LOG_H
#define __RUNTIMES_LOG_H

#define LOG_MODULE_ENABLE_FMT 1

#ifdef _WIN32
#pragma warning(disable : 4996)
#endif

#if LOG_MODULE_ENABLE_FMT
#include <fmt/format.h>
#endif /// LOG_MODULE_ENABLE_FMT

enum class LogOutputType : std::uint64_t {
  OutputConsole = 1,
  OutputFile = OutputConsole << 1,
};

class Log final {
public:
  Log(const std::u16string &outputFilePathname = u"")
      : m_OutputFilePathname(outputFilePathname) {

    if (!m_OutputFilePathname.empty()) {
      if (!stl::File::Exists(m_OutputFilePathname)) {
        isinit_ = true;
        stl::File::Create(m_OutputFilePathname);
      }
      m_OutputType = static_cast<std::uint64_t>(LogOutputType::OutputFile);
    }

    m_Mutex = std::make_shared<std::mutex>();
    m_IsOpen.store(true);
    m_ProcessThread = std::thread([this]() {
      do {
        Output();

        if (Empty())
          std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (!m_IsOpen.load() && Empty())
          break;
      } while (1);
    });
  }
  ~Log() {
    m_IsOpen.store(false);
    if (m_ProcessThread.joinable())
      m_ProcessThread.join();
  }

public:
  void operator<<(const std::string &log_data) {
    std::unique_lock<std::mutex> lock{*m_Mutex, std::defer_lock};
    lock.lock();
    m_OutputQ.push(log_data);
    lock.unlock();
  }
  bool Empty() const {
    bool result = false;
    std::unique_lock<std::mutex> lock{*m_Mutex, std::defer_lock};
    lock.lock();
    result = m_OutputQ.empty();
    lock.unlock();
    return result;
  }
  bool IsInit() const {
    return isinit_;
  }

private:
  void Output() {
    std::unique_lock<std::mutex> lock{*m_Mutex, std::defer_lock};
    lock.lock();
    do {
      if (m_OutputQ.empty())
        break;
      std::string data = m_OutputQ.front();
      std::chrono::system_clock::time_point now =
          std::chrono::system_clock::now();
      std::time_t now_time = std::chrono::system_clock::to_time_t(now);
      std::chrono::milliseconds ms =
          std::chrono::duration_cast<std::chrono::milliseconds>(
              now.time_since_epoch()) %
          1000;
      std::tm local_time = *std::localtime(&now_time);
#if LOG_MODULE_ENABLE_FMT
      data.insert(0,
                  fmt::format("{:04}/{:02}/{:02} {:02}:{:02}:{:02}/{:03}\t",
                              local_time.tm_year + 1900, local_time.tm_mon + 1,
                              local_time.tm_mday, local_time.tm_hour,
                              local_time.tm_min, local_time.tm_sec,
                              static_cast<int>(ms.count())));
#else
      std::ostringstream oss;
      oss << std::put_time(&local_time, "%Y/%m/%d %H:%M:%S");
      oss << '/' << std::setw(3) << std::setfill('0') << ms.count() << "\t";
      data.insert(0, oss.str());
#endif
      data.append("\r\n");
      if (m_OutputType &
          static_cast<std::uint64_t>(LogOutputType::OutputConsole))
        std::cout << data << std::endl;
      if (m_OutputType &
          static_cast<std::uint64_t>(LogOutputType::OutputFile)) {
        if (!m_OutputFilePathname.empty())
          stl::File::WriteFileAddto(m_OutputFilePathname, data);
      }

      m_OutputQ.pop();
    } while (0);
    lock.unlock();
  }

private:
  const std::u16string m_OutputFilePathname;
  std::uint64_t m_OutputType =
      static_cast<std::uint64_t>(LogOutputType::OutputConsole);
  std::shared_ptr<std::mutex> m_Mutex;
  std::atomic_bool m_IsOpen = false;
  std::thread m_ProcessThread;
  std::queue<std::string> m_OutputQ;
  bool isinit_ = false;
};

inline Log *__gspLog = nullptr;

/**/
#if LOG_MODULE_ENABLE_FMT
template <typename... T>
static void LOG_OUTPUT(fmt::format_string<T...> fmt, T &&...args) {
  do {
    if (!__gspLog)
      break;
    std::string s = fmt::vformat(fmt, fmt::make_format_args(args...));
    if (s.empty())
      break;
    *__gspLog << s;
  } while (0);
}

template <typename... T>
static void LOG_INFO(fmt::format_string<T...> fmt, T &&...args) {
  do {
    if (!__gspLog)
      break;
    std::string s = fmt::vformat(fmt, fmt::make_format_args(args...));
    if (s.empty())
      break;
    s.insert(0, "[INFO]=>");
    *__gspLog << s;
  } while (0);
}

template <typename... T>
static void LOG_FATAL(fmt::format_string<T...> fmt, T &&...args) {
  do {
    if (!__gspLog)
      break;
    std::string s = fmt::vformat(fmt, fmt::make_format_args(args...));
    if (s.empty())
      break;
    s.insert(0, "[FATAL ERROR]=>");
    *__gspLog << s;
  } while (0);
}
template <typename... T>
static void LOG_ERROR(fmt::format_string<T...> fmt, T &&...args) {
  do {
    if (!__gspLog)
      break;
    std::string s = fmt::vformat(fmt, fmt::make_format_args(args...));
    if (s.empty())
      break;
    s.insert(0, "[ERROR]=>");
    *__gspLog << s;
  } while (0);
}
template <typename... T>
static void LOG_WARN(fmt::format_string<T...> fmt, T &&...args) {
  do {
    if (!__gspLog)
      break;
    std::string s = fmt::vformat(fmt, fmt::make_format_args(args...));
    if (s.empty())
      break;
    s.insert(0, "[WARN]=>");
    *__gspLog << s;
  } while (0);
}
#else
static void LOG_OUTPUT(const std::string &data) {
  do {
    if (!__gspLog)
      break;
    if (data.empty())
      break;
    *__gspLog << data;
  } while (0);
}

#if 0
template <class... _Types>
static void LOG_OUTPUT(const _STD _Fmt_string<_Types...> _Fmt, _Types&&... _Args) {
	do {
		if (!__gspLog)
			break;
		_STD string s = _STD vformat(_Fmt._Str, _STD make_format_args(_Args...));
		if (s.empty())
			break;
		*__gspLog << s;
	} while (0);
}

template <class... _Types>
static void LOG_MSGBOX(const _STD _Fmt_string<_Types...> _Fmt, _Types&&... _Args) {
	_STD string s = _STD vformat(_Fmt._Str, _STD make_format_args(_Args...));
	::MessageBoxA(NULL, s.c_str(), __FUNCTION__, MB_TOPMOST);
}
template <class... _Types>
static void LOG_MSGBOX(const _STD _Fmt_wstring<_Types...> _Fmt, _Types&&... _Args) {
	_STD wstring s = _STD vformat(_Fmt._Str, _STD make_wformat_args(_Args...));
	::MessageBoxW(NULL, s.c_str(), __FUNCTIONW__, MB_TOPMOST);
}
#endif
#if 0 //!@ Not supported at present
template <class... _Types>
static void LOG_OUTPUT(const _STD wformat_string<_Types...> _Fmt, _Types&&... _Args) {
	do {
		_STD wstring s = _STD vformat(_Fmt.get(), _STD make_wformat_args(_Args...));
		if (s.empty())
			break;
		*__gspLog << s;
	} while (0);
}
#endif
#endif

#define LOG_INIT(strFilename)                                                  \
  do {                                                                         \
    if (!__gspLog) {                                                           \
      __gspLog = new Log(strFilename);                                         \
      if (__gspLog->IsInit()) {                                                \
        *__gspLog << "___安全、稳定、声誉___";                                 \
      }                                                                        \
    }                                                                          \
  } while (0);

//*__gspLog << "___www.skstu.com___";                                           \

#define LOG_UNINIT                                                             \
  do {                                                                         \
    if (!__gspLog)                                                             \
      break;                                                                   \
    delete __gspLog;                                                           \
    __gspLog = nullptr;                                                        \
  } while (0);

#if 0
#define LOG_OUTPUT(s)                                                          \
  do {                                                                         \
    if (!__gspLog)                                                             \
      break;                                                                   \
    if (s.empty())                                                             \
      break;                                                                   \
    *__gspLog << s;                                                            \
  } while (0);
#endif

/// /*_ Memade®（新生™） _**/
/// /*_ Thu, 27 Apr 2023 08:29:20 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
// #endif///__B4907D76_FA9F_49AD_AC90_62EB586B8F99__

#endif
