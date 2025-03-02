#if !defined(__B8180CB2_CC67_4024_933A_E67AC94FA0DB__)
#define __B8180CB2_CC67_4024_933A_E67AC94FA0DB__

/**
 * @file stl.hpp
 *
 * @brief Only C++ STL functionality is encapsulated.
 *
 * @author Martell
 * @date 2023-11-13
 * @location SHE(ISO 3166-1)
 */

#define _PLATFORM_STL_VER __cplusplus

#ifdef _WIN32
// #define _CRT_SECURE_NO_WARNINGS
#if _MSC_VER
#undef _PLATFORM_STL_VER
#define _PLATFORM_STL_VER _MSVC_LANG
#endif
#endif

#define _STL_HAS_CXX03 0
#define _STL_HAS_CXX11 0
#define _STL_HAS_CXX14 0
#define _STL_HAS_CXX17 0
#define _STL_HAS_CXX20 0
#define _STL_HAS_CXX23 0

#if _PLATFORM_STL_VER >= 199711L
#undef _STL_HAS_CXX03
#define _STL_HAS_CXX03 1
#endif

#if _PLATFORM_STL_VER >= 201103L
#undef _STL_HAS_CXX11
#define _STL_HAS_CXX11 1
#endif

#if _PLATFORM_STL_VER >= 201402L
#undef _STL_HAS_CXX14
#define _STL_HAS_CXX14 1
#endif

#if _PLATFORM_STL_VER >= 201703L
#undef _STL_HAS_CXX17
#define _STL_HAS_CXX17 1
#endif

#if _PLATFORM_STL_VER >= 202002L
#undef _STL_HAS_CXX20
#define _STL_HAS_CXX20 1
#endif

#if _PLATFORM_STL_VER > 202002L
#undef _STL_HAS_CXX23
#define _STL_HAS_CXX23 1
#endif

#if _STL_HAS_CXX03
#include <fcntl.h>

#include <algorithm>
#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#endif

#if _STL_HAS_CXX11
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <random>
#include <regex>
#include <thread>
#include <tuple>
#include <typeinfo>
#endif

#if _STL_HAS_CXX14
#include <any>
#include <bitset>
#include <deque>
#include <future>
#include <optional>
#include <string_view>
#include <variant>
#endif

#if _STL_HAS_CXX17
#include <locale>
#include <codecvt>
#include <filesystem>
#if _PLATFORM_STL_VER == 201703L
// #include <experimental/coroutine>
#endif
#endif

#if _STL_HAS_CXX20
#include <concepts>
#include <coroutine>
#if _WIN32 && _MSC_VER
#include <format>
#endif
#endif

#if _STL_HAS_CXX23
#include <span> //(proposed for C++23, but may be available in some compilers)
#endif

namespace stl {
using tfThreads = std::vector<std::thread>;
using tfCommandLines = std::map<std::string, std::string>;
class CmdLine {
public:
  CmdLine(const std::string &cmdline);
  ~CmdLine();

public:
  virtual void Release() const;
  virtual bool HasKey(const std::string &key) const;
  virtual std::string GetValue(const std::string &key) const;

public:
  static std::string PackageCommandLine(const int &argc, char **argv);
  static std::string PackageCommandLine(const char **args);
  static tfCommandLines ParserCommandLines(const std::string &input);

protected:
  tfCommandLines source_;
};
class Common {
public:
  static std::vector<std::string> StringSpilt(const std::string &input,
                                              const std::string &delim);
  static std::string toLower(const std::string &input);
  static bool strIcmp(const std::string &str1, const std::string &str2);
};
#if 0
class Conv {
public:
  static std::wstring U8StringToWString(const std::string &);
  static std::u16string U8StringToU16String(const std::string &);
  static std::string U16StringToU8String(const std::u16string &);
  static std::u32string U8StringToU32String(const std::string &);
  static std::string U32StringToU8String(const std::u32string &);
  static std::u32string U16StringToU32String(const std::u16string &);
  static std::u16string U32StringToU16String(const std::u32string &);
};
#endif
class Time {
public:
  template <typename T = std::chrono::seconds>
#if _STL_HAS_CXX20
  requires std::is_convertible_v<T, std::chrono::milliseconds> ||
           std::is_convertible_v<T, std::chrono::minutes> ||
           std::is_convertible_v<T, std::chrono::microseconds>
#endif
  static time_t TimeStamp() {
    return std::chrono::duration_cast<T>(
               std::chrono::time_point_cast<T>(std::chrono::system_clock::now())
                   .time_since_epoch())
        .count();
  }
  static std::string GetLocalTimezoneOffset();
  static std::string CurrentDateA();
  static std::wstring CurrentDateW();
  /**
   * ISO
   * 标准时间表示法是指国际标准化组织（ISO）制定的一套时间表示方法，用于在全球范围内统一时间表示方式，避免由于时区和文化差异造成的混淆。
   * ISO 标准时间表示法的格式为：YYYY-MM-DDTHH:mm:ss.sssZ
   * @return ISO 标准时间表示法的字符串，例如 "2023-04-29T13:30:45.500+08:00"
   * 2023-04-29T14:22:37.189Z =>(UTC)
   * 2023-04-29T14:22:37.189+0800 =>(LOCAL)
   *
   */
  template <typename T = std::chrono::seconds>
#if _STL_HAS_CXX20
  requires(std::is_same_v<T, std::chrono::milliseconds> ||
           std::is_same_v<T, std::chrono::seconds>)
#endif
  static std::string
  TimestampToISO8601(std::uint64_t timestamp,
                     const bool &local = true /*or UTC == false*/) {
    std::ostringstream os;
    auto ms = T(timestamp);
    auto tp = std::chrono::time_point<std::chrono::system_clock, T>(ms);
    auto time_t = std::chrono::system_clock::to_time_t(tp);
    if (timestamp > 9999999999) {
      os << std::put_time(std::gmtime(&time_t), "%Y-%m-%dT%H:%M:%S.");
      os << std::setfill('0') << std::setw(3) << (timestamp % 1000);
    } else {
      os << std::put_time(std::gmtime(&time_t), "%Y-%m-%dT%H:%M:%S");
    }
    local ? os << GetLocalTimezoneOffset() : os << "Z";
    return os.str();
  }

  template <typename T = std::chrono::seconds>
#if _STL_HAS_CXX20
  requires(std::is_same_v<T, std::chrono::milliseconds> ||
           std::is_same_v<T, std::chrono::seconds>)
#endif
  static std::time_t TimeStampUTC() {
    return std::chrono::duration_cast<T>(
               std::chrono::time_point_cast<T>(std::chrono::system_clock::now())
                   .time_since_epoch())
        .count();
  }

  static unsigned long GetDateDay();
  static std::string GetDateDayString();
};

#if __ExampleCode
{ //! return value
  std::vector<std::future<int>> results;
  for (int i = 0; i < 8; ++i) {
    results.emplace_back(pool.enqueue([i] {
      std::cout << "hello " << i << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
      std::cout << "world " << i << std::endl;
      return i * i;
    }));
  }
  for (auto &&result : results) {
    std::cout << result.get() << ' ';
  }
  std::cout << std::endl;
} ///! return value
{ //! return void
  for (int i = 0; i < 10; i++) {
    pThreadPool->enqueue(
        [i] { std::cout << "abc123" << " " << i << std::endl; });
  } /// for (int i = 0; i < 10; i++)
} ///! return void
#endif /// ExampleCode
class ThreadPool final {
  const size_t threads_;

public:
  const size_t &Total() const {
    return threads_;
  }
  ThreadPool(size_t threads = 4) : stop(false), threads_(threads) {
    for (size_t i = 0; i < threads; ++i)
      workers.emplace_back([this] {
        for (;;) {
          std::function<void()> task;
          {
            std::unique_lock<std::mutex> lock(this->queue_mutex);
            this->condition.wait(
                lock, [this] { return this->stop || !this->tasks.empty(); });
            if (this->stop && this->tasks.empty())
              return;
            task = std::move(this->tasks.front());
            this->tasks.pop();
          }
          task();
        }
      });
  }
  ~ThreadPool() {
    {
      std::unique_lock<std::mutex> lock(queue_mutex);
      stop = true;
    }
    condition.notify_all();
    for (std::thread &worker : workers)
      worker.join();
  }
#if 0
		template<class F, class... Args>
		auto enqueue(F&& f, Args&& ... args) -> std::future<decltype(std::forward<F>(f)(std::forward<Args>(args)...))>;
#else
  template <class F, class... Args>
  auto enqueue(F &&f, Args &&...args) -> std::future<
      decltype(std::forward<F>(f)(std::forward<Args>(args)...))> {
    auto task = std::make_shared<std::packaged_task<decltype(std::forward<F>(f)(
        std::forward<Args>(args)...))()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    std::future<decltype(std::forward<F>(f)(std::forward<Args>(args)...))> res =
        task->get_future();
    {
      std::unique_lock<std::mutex> lock(queue_mutex);
      // don't allow enqueueing after stopping the pool
      if (stop)
        throw std::runtime_error("enqueue on stopped ThreadPool");
      tasks.emplace([task]() { (*task)(); });
    }
    condition.notify_one();
    return res;
  }
#endif
private:
  // need to keep track of threads so we can join them
  std::vector<std::thread> workers;
  // the task queue
  std::queue<std::function<void()>> tasks;
  // synchronization
  std::mutex queue_mutex;
  std::condition_variable condition;
  bool stop;
};

class String {
public:
  static bool VerifyUrl(const std::string &url);
  static int ICompareA(const std::string &, const std::string &);
  static int ICompareW(const std::wstring &, const std::wstring &);
  static std::string Lower(const std::string &);
  static std::u16string Lower(const std::u16string &);
  static std::wstring Lower(const std::wstring &);
  static std::string Upper(const std::string &);
  static std::wstring Upper(const std::wstring &);
#if _STL_HAS_CXX20
  static std::u8string Lower(const std::u8string &);
  static std::u8string Upper(const std::u8string &);
#endif
  static std::string BinaryToHexString(const std::string &s);
  static std::string HexStringToBinary(const std::string &s);
  static std::vector<std::string> StringSpilt(const std::string &,
                                              const std::string &);
  static std::vector<std::wstring> WStringSplit(const std::wstring &,
                                                const std::wstring &);
  /*
   * Input IPV4: "192.168.0.1:8888"
   * Input IPV6: "[::]:8888"
   */
  static std::tuple<std::string, int> UnmadeIPAddr(const std::string &addr);
  static std::string MadeIPAddr(const std::string &ip, const int &port);
  static std::string UrlFixA(const std::string &inputUrlOrPath);
  static std::string WemadeEncode(const std::string &);
  static std::string WemadeDecode(const std::string &);
};

class Directory {
public:
  //!@ input example : c:\\Windows\\System32\\
	    //!
  static bool Create(const std::string &);
  static bool Create(const std::u16string &);
  static bool Create(const std::wstring &);
  static bool RemoveAll(const std::string &);
  static bool RemoveAll(const std::u16string &);
  static bool RemoveAll(const std::wstring &);
  static std::string GetTempDir();
  static bool Exists(const std::string &);
  static bool Exists(const std::u16string &);
  static bool Exists(const std::wstring &);
#if _STL_HAS_CXX20
  static bool Exists(const std::u8string &);
#endif
  static void Enum(
      const std::string &inputPath,
      std::map<std::string /*full path*/, std::string /*relative path*/> &dirs,
      std::map<std::string /*full path*/, std::string /*relative path*/> &files,
      const bool &recursive);
  static void
  Enum(const std::u16string &inputPath,
       std::map<std::u16string /*full path*/, std::u16string /*relative path*/>
           &dirs,
       std::map<std::u16string /*full path*/, std::u16string /*relative path*/>
           &files,
       const bool &recursive);
  static void
  Enum(const std::wstring &inputPath,
       std::map<std::wstring /*full path*/, std::wstring /*relative path*/>
           &dirs,
       std::map<std::wstring /*full path*/, std::wstring /*relative path*/>
           &files);
#if _STL_HAS_CXX20
  static void
  Enum(const std::u8string &inputPath,
       std::map<std::u8string /*full path*/, std::u8string /*relative path*/>
           &dirs,
       std::map<std::u8string /*full path*/, std::u8string /*relative path*/>
           &files,
       const bool &recursive);
#endif
};

class Path {
public:
  static std::string Normalize(const std::string &PathOrPathname);
  static std::u16string Normalize(const std::u16string &PathOrPathname);
  static std::u16string U8PathToU16Path(const std::string &);
  static std::string U16PathToU8Path(const std::u16string &);
  static std::wstring U16PathToWPath(const std::u16string &);
  static std::u16string WPathToU16Path(const std::wstring &);
#if _STL_HAS_CXX20
  static std::u8string Normal(const std::u8string &);
#endif
  static std::string Normal(const std::string &);
  static std::u16string Normal(const std::u16string &);
  static std::wstring Normal(const std::wstring &);
  static bool IsDirectoryPath(const std::string &input_path);
  static bool IsDirectoryPath(const std::wstring &input_path);
  static bool IsDirectoryPath(const std::u16string &input_path);
  static bool IsFilePath(const std::string &input_path);
  static bool IsFilePath(const std::wstring &input_path);
  static bool IsFilePath(const std::u16string &input_path);
  static std::string Parent(const std::string &);
  static std::u16string Parent(const std::u16string &);
  static std::wstring Parent(const std::wstring &);
  static std::string Append(const std::string &abs, const std::string &rel);
  static std::wstring Append(const std::wstring &abs, const std::wstring &rel);
  static std::string PathnameToPath(const std::string &input_pathname);
  static std::wstring PathnameToPath(const std::wstring &input_pathname);
  static std::u16string PathnameToPath(const std::u16string &input_pathname);
  static bool ParsePathname(const std::string &pathname,
                            std::string &parent_path, std::string &filename,
                            std::string &extension, std::string &stem);
  static bool ParsePathname(const std::wstring &pathname,
                            std::wstring &parent_path, std::wstring &filename,
                            std::wstring &extension, std::wstring &stem);
  static bool ParsePathname(const std::u16string &pathname,
                            std::u16string &parent_path,
                            std::u16string &filename, std::u16string &extension,
                            std::u16string &stem);
};
class File {
public:
  static std::string GetFormat(const std::string &, const bool &lower = false);
  static std::u16string GetFormat(const std::u16string &,
                                  const bool &lower = false);
  static std::wstring GetFormat(const std::wstring &,
                                const bool &lower = false);
  static size_t Size(const std::u16string &);
  static bool Exists(const std::u16string &);
  static bool Exists(const std::wstring &);
  static bool Exists(const std::string &);
  static std::string Create(const std::string &);
  static std::u16string Create(const std::u16string &);
  static bool Remove(const std::string &);
  static bool Remove(const std::wstring &);
  static bool Remove(const std::u16string &);
  static std::string
  ReadFile(/*std::ios::_Nocreate | std::ios::_Noreplace | std::ios::binary*/
           const std::string &,
           const int &mode_ = std::ios::in | std::ios::binary);
#if 0
		static std::string
			ReadFileW(const std::wstring& inputFile, const std::wstring& mode = L"rb");
#endif
  static std::string
  ReadFile(/*std::ios::_Nocreate | std::ios::_Noreplace | std::ios::binary*/
           const std::wstring &,
           const int &mode_ = std::ios::in | std::ios::binary);
  static std::string
  ReadFile(/*std::ios::_Nocreate | std::ios::_Noreplace | std::ios::binary*/
           const std::u16string &,
           const int &mode_ = std::ios::in | std::ios::binary);
  static void
  ReadFile(/*std::ios::_Nocreate | std::ios::_Noreplace | std::ios::binary*/
           const std::string &, std::vector<char> &,
           const int &mode_ = std::ios::in | std::ios::binary);
  static void
  ReadFile(/*std::ios::_Nocreate | std::ios::_Noreplace | std::ios::binary*/
           const std::wstring &, std::vector<wchar_t> &,
           const int &mode_ = std::ios::in | std::ios::binary);
  static bool WriteFile(const std::string &, const std::string &,
                        const int &mode_ = static_cast<int>(std::ios::binary) |
                                           static_cast<int>(std::ios::out) |
                                           static_cast<int>(std::ios::trunc));
  static bool WriteFile(const std::wstring &, const std::string &,
                        const int &mode_ = static_cast<int>(std::ios::binary) |
                                           static_cast<int>(std::ios::out) |
                                           static_cast<int>(std::ios::trunc));
  static bool WriteFile(const std::u16string &, const std::string &,
                        const int &mode_ = static_cast<int>(std::ios::binary) |
                                           static_cast<int>(std::ios::out) |
                                           static_cast<int>(std::ios::trunc));

  static bool WriteFileAddto(const std::string &, const std::string &);
  static bool WriteFileAddto(const std::wstring &, const std::string &);
  static bool WriteFileAddto(const std::u16string &, const std::string &);
};

template <typename T> class Switch {
public:
  // 默认构造函数
  Switch() : value(T{}) {
  }

  // 带参数的构造函数
  Switch(const T &v) : value(v) {
  }

  ~Switch() {
  }

public:
  T Get() const {
    std::lock_guard<std::mutex> lock{*mtx_};
    return value;
  }

  void Set(const T &v) {
    std::lock_guard<std::mutex> lock{*mtx_};
    value = v;
  }

private:
  T value;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};

class Operation {
public:
  Operation() = default;
  void *operator new(size_t) = delete;
  void operator delete(void *) = delete;
  Operation(const Operation &) = delete;
  Operation &operator=(const Operation &) = delete;

private:
  ~Operation() = default;

public:
  static const int SHIFT_DIRECTION_BASE = 4;
  // This is an enumeration class called ShiftDirection.
  // It has two values: LEFT and RIGHT.
  enum class ShiftDirection {
    LEFT, // Represents a left shift.
    RIGHT // Represents a right shift.
  };

  // This is a template function that takes a type T as its input.
  // It requires that T is an integral type (integers and bool).
  template <typename T>
  /*requires std::integral<T>*/

  // This function takes three arguments:
  // 1. num: a constant reference to an object of type T.
  // 2. n: a constant reference to an unsigned 16-bit integer (std::uint16_t).
  // 3. dir: an enum value of type ShiftDirection (LEFT or RIGHT).

  // The function returns a value of type T.
  static T shift_hex_by_nibbles(const T &num, const std::uint16_t &n,
                                const ShiftDirection &dir) {
    // Initialize a variable called "result" of type T with a value of zero.
    T result = 0;
    // Use a switch statement to handle the different cases for the
    // ShiftDirection enum.
    switch (dir) {
      // If the ShiftDirection is LEFT, shift the bits of the input number to
      // the left by n*4.
    case ShiftDirection::LEFT:
      result = num << (n * SHIFT_DIRECTION_BASE);
      break;
      // If the ShiftDirection is RIGHT, shift the bits of the input number to
      // the right by n*4.
    case ShiftDirection::RIGHT:
      result = num >> (n * SHIFT_DIRECTION_BASE);
      break;
      // If neither LEFT nor RIGHT, do nothing.
    default:
      break;
    }
    // Return the result of the shift operation.
    return result;
  }
};
class Signal {
public:
  Signal() = default;
  ~Signal() = default;
  void Release() const;

public:
  void notify();
  void reset();
  bool wait_for_event(
      std::chrono::milliseconds timeout = std::chrono::milliseconds(0));

private:
  std::atomic_bool event_signaled_ = false;
  std::mutex mtx_;
  std::condition_variable cv_;
};

template <typename T> class Value {
public:
  Value() : source_(nullptr) {
  }
  Value(T *src) : source_(src) {
  }
  ~Value() {
    if (source_) {
      source_->Release();
      source_ = nullptr;
    }
  }

public:
  void Reset() {
    if (source_) {
      source_->Release();
      source_ = nullptr;
    }
  }
  void Release() const {
    delete this;
  }
  bool Empty() const {
    std::lock_guard<std::mutex> lock{*mtx_};
    return source_ == nullptr;
  }
  T *operator->() const {
    std::lock_guard<std::mutex> lock{*mtx_};
    return source_;
  }
  void operator=(T *obj) {
    std::lock_guard<std::mutex> lock{*mtx_};
    if (source_) {
      source_->Release();
      source_ = nullptr;
    }
    source_ = obj;
  }
  T *operator*() const {
    std::lock_guard<std::mutex> lock{*mtx_};
    return source_;
  }

public:
private:
  T *source_ = nullptr;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};
template <typename T = std::string> class Buffer {
public:
  Buffer() {
  }
  Buffer(const T &input) : source_(input) {
  }
  ~Buffer() {
  }

public:
  void operator<<(const T &append) {
    std::lock_guard<std::mutex> lock{*mtx_};
    source_.append(append);
  }
  void operator=(const T &input) {
    std::lock_guard<std::mutex> lock{*mtx_};
    source_ = input;
  }
  void operator>>(T &output) const {
    std::lock_guard<std::mutex> lock{*mtx_};
    output = source_;
  }

private:
  T source_;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};
namespace container {
class base {
public:
  base() {
  }
  virtual ~base() {
  }

protected:
  std::shared_ptr<std::mutex> mutex_ = std::make_shared<std::mutex>();
  std::shared_ptr<std::condition_variable> condition_variable_ =
      std::make_shared<std::condition_variable>();
};
template <typename KEY, typename VAL> class unordered_map final : public base {
protected:
  virtual size_t GetSize() {
    return m_unordered_map.size();
  }

public:
  unordered_map() {
  }
  virtual ~unordered_map() {
  }

public:
  size_t size() const {
    std::lock_guard<std::mutex> _lock(*mutex_);
    return m_unordered_map.size();
  }
  bool push(const KEY &key, const VAL &val) {
    std::lock_guard<std::mutex> _lock(*mutex_);
    auto result = m_unordered_map.emplace(std::make_pair(key, val));
    return result.second;
  }
  bool pop(const KEY &key) {
    bool result = false;
    std::lock_guard<std::mutex> _lock(*mutex_);
    auto found = m_unordered_map.find(key);
    if (found != m_unordered_map.end()) {
      result = true;
      m_unordered_map.erase(found);
    }
    return result;
  }
  bool search(const KEY &key,
              const std::function<void(const VAL &)> &search_cb) const {
    bool result = false;
    std::lock_guard<std::mutex> _lock(*mutex_);
    auto found = m_unordered_map.find(key);
    if (found != m_unordered_map.end()) {
      result = true;
      search_cb(found.second);
    }
    return result;
  }
  void
  iterate(const std::function<void(const KEY &, VAL &, bool &)> &iterate_cb) {
    std::lock_guard<std::mutex> _lock(*mutex_);
    bool itbreak = false;
    for (auto &node : m_unordered_map) {
      itbreak = false;
      iterate_cb(node.first, node.second, itbreak);
      if (itbreak)
        break;
    }
  }
  void iterate_clear(
      const std::function<void(const KEY &, const VAL &, bool &)> &iterate_cb) {
    std::lock_guard<std::mutex> _lock(*mutex_);
    bool itclear = false;
    for (auto it = m_unordered_map.begin(); it != m_unordered_map.end();) {
      itclear = false;
      iterate_cb(it->first, it->second, itclear);
      if (itclear) {
        it = m_unordered_map.erase(it);
        continue;
      }
      ++it;
    }
  }
  bool empty() const {
    std::lock_guard<std::mutex> _lock(*mutex_);
    return m_unordered_map.empty();
  }
  std::vector<VAL> Vector() const {
    std::vector<VAL> result;
    std::lock_guard<std::mutex> _lock(*mutex_);
    do {
      if (m_unordered_map.empty())
        break;
      for (auto &node : m_unordered_map)
        result.emplace_back(node.second);
    } while (0);
    return result;
  }

public:
  __inline void operator=(const std::unordered_map<KEY, VAL> &_Target) {
    std::lock_guard<std::mutex> _lock(*mutex_);
    m_unordered_map.clear();
    m_unordered_map = _Target;
  }

private:
  std::unordered_map<KEY, VAL> m_unordered_map;
};

template <typename T> class queue final : public base {
public:
  queue(const size_t &_max = 0) : max_(_max) {
  }
  virtual ~queue() {
  }

private:
  void __onsize() {
    do {
      if (max_ <= 0)
        break;
      const size_t total = q_.size();
      std::cout << total << std::endl;
      if (total <= max_)
        break;
      q_.pop();
    } while (0);
  }

public:
  void push(const T &data) {
    std::lock_guard<std::mutex> _lock(*mutex_);
    __onsize();
    q_.push(data);
  }
  void push(const std::vector<T> &datas) {
    std::lock_guard<std::mutex> _lock(*mutex_);
    for (const auto &data : datas) {
      __onsize();
      q_.push(data);
    }
  }
  std::shared_ptr<T> pop_front() {
    std::shared_ptr<T> result;
    std::lock_guard<std::mutex> _lock(*mutex_);
    if (!q_.empty()) {
      result = std::make_shared<T>(q_.front());
      q_.pop();
    }
    return result;
  }
  std::shared_ptr<T> pop_back() {
    std::shared_ptr<T> result;
    std::lock_guard<std::mutex> _lock(*mutex_);
    if (!q_.empty()) {
      result = std::make_shared<T>(q_.back());
      q_.pop();
    }
    return result;
  }
  std::vector<T> pops() {
    std::vector<T> result;
    std::lock_guard<std::mutex> _lock(*mutex_);
    while (!q_.empty()) {
      result.emplace_back(q_.front());
      q_.pop();
    }
    return result;
  }
  std::shared_ptr<T> pop() {
    std::shared_ptr<T> result;
    std::lock_guard<std::mutex> _lock(*mutex_);
    if (!q_.empty()) {
      result = std::make_shared<T>(q_.front());
      q_.pop();
    }
    return result;
  }
  bool empty() const {
    bool result = false;
    std::lock_guard<std::mutex> _lock(*mutex_);
    result = q_.empty();
    return result;
  }
  size_t size() const {
    size_t result = 0;
    std::lock_guard<std::mutex> _lock(*mutex_);
    result = q_.size();
    return result;
  }
  void clear() {
    std::lock_guard<std::mutex> _lock(*mutex_);
    std::queue<T> empty;
    std::swap(q_, empty);
  }

private:
  std::queue<T> q_;
  const size_t max_;
};

template <typename K, typename V> class map final : public base {
public:
  map() {
  }
  virtual ~map() {
  }

public:
  void push(const K &k, const V &v) {
    std::lock_guard<std::mutex> _lock(*mutex_);
    auto found = map_.find(k);
    if (found != map_.end())
      map_.erase(found);
    map_.emplace(k, v);
  }
  void push(const K &k, const V &v,
            const std::function<void(const V &)> &exists_cb) {
    std::lock_guard<std::mutex> _lock(*mutex_);
    auto found = map_.find(k);
    if (found != map_.end()) {
      exists_cb(found->second);
      map_.erase(found);
    }
    map_.emplace(k, v);
  }
  void push(const K &k, const V &v,
            const std::function<void(const V &old, const V &ins)> &exists_cb) {
    std::lock_guard<std::mutex> _lock(*mutex_);
    auto found = map_.find(k);
    if (found != map_.end()) {
      exists_cb(found->second, v);
      map_.erase(found);
    }
    map_.emplace(k, v);
  }
  std::shared_ptr<V> pop(const K &k) {
    std::shared_ptr<V> result;
    std::lock_guard<std::mutex> _lock(*mutex_);
    auto found = map_.find(k);
    if (found != map_.end()) {
      result = std::make_shared<V>(found->second);
      map_.erase(found);
    }
    return result;
  }
  std::shared_ptr<V> search(const K &k) const {
    std::shared_ptr<V> result = nullptr;
    std::lock_guard<std::mutex> _lock(*mutex_);
    auto found = map_.find(k);
    if (found != map_.end())
      result = std::make_shared<V>(found->second);
    return result;
  }
  void clear() {
    std::lock_guard<std::mutex> _lock(*mutex_);
    map_.clear();
  }
  bool empty() {
    std::lock_guard<std::mutex> _lock(*mutex_);
    return map_.empty();
  }
  size_t size() const {
    std::lock_guard<std::mutex> _lock(*mutex_);
    return map_.size();
  }
  void iterate(const std::function<void(const K &, V &)> &iteratecb) {
    std::lock_guard<std::mutex> lock(*mutex_);
    for (auto it = map_.begin(); it != map_.end(); ++it) {
      iteratecb(it->first, it->second);
    }
  }
  void
  iterate_clear(const std::function<void(const K &, V &, bool &)> &iteratecb) {
    std::lock_guard<std::mutex> lock(*mutex_);
    for (auto it = map_.begin(); it != map_.end();) {
      bool clear = false;
      iteratecb(it->first, it->second, clear);
      if (!clear) {
        ++it;
        continue;
      }
      it = map_.erase(it);
    }
  }
  void iterate(
      const std::function<void(const K &, V &, const size_t &)> &iteratecb) {
    std::lock_guard<std::mutex> lock(*mutex_);
    size_t i = 0;
    for (auto it = map_.begin(); it != map_.end(); ++it, ++i) {
      iteratecb(it->first, it->second, i);
    }
  }
  bool search(const K &key,
              const std::function<void(const K &, V &)> &search_cb) {
    std::lock_guard<std::mutex> lock(*mutex_);
    auto found = map_.find(key);
    if (found == map_.end())
      return false;
    search_cb(found->first, found->second);
    return true;
  }

private:
  std::map<K, V> map_;
};

template <typename T> class list final : public base {
public:
  list() : m_list() {
  }
  virtual ~list() {
  }

public:
  void operator=(const std::list<T> &_Target) {
    std::lock_guard<std::mutex> lock(*mutex_);
    m_list.clear();
    m_list = _Target;
  }
  void operator=(const stl::container::list<T> &_Target) {
    std::lock_guard<std::mutex> lock(*mutex_);
    m_list.clear();
    m_list = _Target.m_list;
  }

public:
  void push_front(const T &data) {
    std::lock_guard<std::mutex> lock(*mutex_);
    m_list.push_front(data);
  }
  void push_back(const T &data) {
    std::lock_guard<std::mutex> lock(*mutex_);
    m_list.push_back(data);
  }
  std::shared_ptr<T> pop_back() {
    std::shared_ptr<T> result;
    std::lock_guard<std::mutex> lock(*mutex_);
    if (m_list.empty()) {
      return result;
    }
    result = std::make_shared<T>(m_list.back());
    m_list.pop_back();
    return result;
  }
  std::shared_ptr<T> pop_front() {
    std::shared_ptr<T> result;
    std::lock_guard<std::mutex> lock(*mutex_);
    if (m_list.empty()) {
      return result;
    }
    result = std::make_shared<T>(m_list.front());
    m_list.pop_front();
    return result;
  }
  std::shared_ptr<T> back() {
    std::shared_ptr<T> result;
    std::lock_guard<std::mutex> lock(*mutex_);
    if (!m_list.empty()) {
      result = std::make_shared<T>(m_list.back());
    }
    return result;
  }
  std::shared_ptr<T> back(const size_t &idx) {
    std::shared_ptr<T> result;
    std::lock_guard<std::mutex> lock(*mutex_);
    if (idx < m_list.size()) {
      auto it = m_list.begin();
      std::advance(it, m_list.size() - 1 - idx);
      result = std::make_shared<T>(*it);
    }
    return result;
  }
  std::shared_ptr<T> front() {
    std::shared_ptr<T> result;
    std::lock_guard<std::mutex> lock(*mutex_);
    if (!m_list.empty()) {
      result = std::make_shared<T>(m_list.front());
    }
    return result;
  }
  std::size_t size() {
    std::lock_guard<std::mutex> lock(*mutex_);
    return m_list.size();
  }
  bool empty() {
    std::lock_guard<std::mutex> lock(*mutex_);
    return m_list.empty();
  }
  void clear() {
    std::lock_guard<std::mutex> lock(*mutex_);
    m_list.clear();
  }
  T *search(const T &data) {
    std::lock_guard<std::mutex> lock(*mutex_);
    auto find = std::find(m_list.begin(), m_list.end(), data);
    if (find != m_list.end()) {
      return &(*find);
    } else {
      return nullptr;
    }
  }
  void iterate(const std::function<void(T &)> &iterate_cb) {
    std::lock_guard<std::mutex> lock(*mutex_);
    for (auto it = m_list.begin(); it != m_list.end(); ++it) {
      iterate_cb(*it);
    }
  }
  void iterate(const std::function<void(T &, bool &clear)> &iterate_cb) {
    std::lock_guard<std::mutex> lock(*mutex_);
    for (auto it = m_list.begin(); it != m_list.end();) {
      bool is_clear = false;
      iterate_cb(*it, is_clear);
      if (is_clear) {
        it = m_list.erase(it);
        continue;
      }
      ++it;
    }
  }
  std::vector<T> Vector() const {
    std::vector<T> result;
    std::lock_guard<std::mutex> lock(*mutex_);
    for (const auto &node : m_list) {
      result.emplace_back(node);
    }
    return result;
  }

private:
  std::list<T> m_list;
};

template <typename T> class set final : public base {
public:
  set() {
  }
  virtual ~set() {
  }
  void operator=(const std::set<T> &stlset) {
    std::lock_guard<std::mutex> lock(*mutex_);
    m_set = stlset;
  }
  void operator=(const set<T> &skset) {
    std::lock_guard<std::mutex> lock(*mutex_);
    m_set = skset.m_set;
  }

public:
  std::shared_ptr<T> begin() const {
    std::shared_ptr<T> result;
    std::lock_guard<std::mutex> lock(*mutex_);
    if (!m_set.empty()) {
      return std::make_shared<T>(*m_set.begin());
    }
    return result;
  }
  std::shared_ptr<T> end() const {
    std::shared_ptr<T> result;
    std::lock_guard<std::mutex> lock(*mutex_);
    if (!m_set.empty()) {
      return std::make_shared<T>(*std::prev(m_set.end()));
    }
    return result;
  }
  std::shared_ptr<T> pop_begin() {
    std::shared_ptr<T> result;
    std::lock_guard<std::mutex> lock(*mutex_);
    if (!m_set.empty()) {
      auto itTarget = m_set.begin();
      result = std::make_shared<T>(*itTarget);
      m_set.erase(itTarget);
    }
    return result;
  }
  std::shared_ptr<T> pop_end() {
    std::shared_ptr<T> result;
    std::lock_guard<std::mutex> lock(*mutex_);
    if (!m_set.empty()) {
      auto itTarget = std::prev(m_set.end());
      result = std::make_shared<T>(*itTarget);
      m_set.erase(itTarget);
    }
    return result;
  }
  //! 签名 : push
  //! 说明 :
  //! 注意 : return true : 存在 false 不存在
  //! 日期 : Sat Jun 13 20:11:38 UTC+0800 2020
  bool push(const T &data) {
    bool result = false;
    std::lock_guard<std::mutex> lock(*mutex_);
    if (m_set.find(data) != m_set.end()) {
      m_set.erase(data);
      result = true;
    }
    m_set.insert(data);
    return result;
  }

  //! 签名 : pushpush
  //! 说明 :
  //! 注意 : 存在回调
  //! 日期 : Sat Jun 13 17:55:07 UTC+0800 2020
  bool pushpush(const T &data, const std::function<void(T &)> &pushpush_cb) {
    bool result = false;
    std::lock_guard<std::mutex> lock(*mutex_);
    auto find = m_set.find(data);
    if (find != m_set.end()) {
      auto val = *find;
      m_set.erase(find);
      pushpush_cb(val);
      result = m_set.insert(val).second;
    } else {
      result = m_set.insert(data).second;
    }
    return result;
  }
  bool pop(const T &key) {
    bool result = false;
    std::lock_guard<std::mutex> lock(*mutex_);
    auto find = m_set.find(key);
    if (find != m_set.end()) {
      m_set.erase(find);
      result = true;
    }
    return result;
  }
  bool empty() const {
    bool result = false;
    std::lock_guard<std::mutex> lock(*mutex_);
    result = m_set.empty();
    return result;
  }
  size_t size() const {
    size_t result = 0;
    std::lock_guard<std::mutex> lock(*mutex_);
    result = m_set.size();
    return result;
  }
  void clear() {
    std::lock_guard<std::mutex> lock(*mutex_);
    m_set.clear();
  }
  void clearat(const std::function<void(const T &, bool &)> &iterate_cb) {
    std::lock_guard<std::mutex> lock(*mutex_);
    bool isClear = false;
    for (auto it = m_set.begin(); it != m_set.end();) {
      isClear = false;
      iterate_cb((T &)(*it), isClear);
      if (true == isClear) {
        it = m_set.erase(it);
      } else {
        ++it;
      }
    }
  }
  bool exists(const T &key) const {
    std::lock_guard<std::mutex> lock(*mutex_);
    return m_set.find(key) != m_set.end();
  }
  std::shared_ptr<T> search(const T &key) {
    std::shared_ptr<T> result;
    std::lock_guard<std::mutex> lock(*mutex_);
    if (!m_set.empty()) {
      auto find = m_set.find(key);
      if (find != m_set.end()) {
        return std::make_shared<T>(*find);
      }
    }
    return result;
  }
  bool search(const T &key, const std::function<void(const T &)> &search_cb) {
    bool result = false;
    std::lock_guard<std::mutex> lock(*mutex_);
    auto find = m_set.find(key);
    if (find != m_set.end()) {
      search_cb(*find);
      result = true;
    }
    return result;
  }
  bool search_noconst(const T &key, const std::function<void(T &)> &search_cb) {
    bool result = false;
    std::lock_guard<std::mutex> lock(*mutex_);
    auto find = m_set.find(key);
    if (find != m_set.end()) {
      search_cb(*find);
      result = true;
    }
    return result;
  }
  bool search(const T &key) const {
    bool result = false;
    std::lock_guard<std::mutex> lock(*mutex_);
    auto find = m_set.find(key);
    if (find != m_set.end()) {
      result = true;
    }
    return result;
  }
  void iterate(const std::function<void(T &)> &iteratecb) {
    std::lock_guard<std::mutex> lock(*mutex_);
    for (auto it = m_set.begin(); it != m_set.end(); ++it) {
      iteratecb((T &)(*it));
    }
  }
  void
  iterate_const(const std::function<void(const T &, bool &)> &iteratecb) const {
    std::lock_guard<std::mutex> lock(*mutex_);
    bool itbreak = false;
    for (auto it = m_set.begin(); it != m_set.end(); ++it) {
      itbreak = false;
      iteratecb((T &)(*it), itbreak);
      if (itbreak)
        break;
    }
  }
  void iterate(const std::function<void(T &, bool &)> &iteratecb) {
    std::lock_guard<std::mutex> lock(*mutex_);
    bool itbreak = false;
    for (auto it = m_set.begin(); it != m_set.end(); ++it) {
      iteratecb((T &)(*it), itbreak);
      if (itbreak == true) {
        break;
      }
    }
  }
  void iterate(const std::function<void(const T &, bool &)> &iteratecb) const {
    std::lock_guard<std::mutex> lock(*mutex_);
    bool itbreak = false;
    for (auto it = m_set.begin(); it != m_set.end(); ++it) {
      iteratecb(*it, itbreak);
      if (itbreak == true) {
        break;
      }
    }
  }
  std::vector<T> Vector() const {
    std::vector<T> result;
    std::lock_guard<std::mutex> lock(*mutex_);
    for (const auto &node : m_set) {
      result.emplace_back(node);
    }
    return result;
  }
  std::set<T> Source() {
    std::set<T> result;
    std::lock_guard<std::mutex> lock(*mutex_);
    for (const auto &node : m_set) {
      result.insert(node);
    }
    return result;
  }

private:
  std::set<T> m_set;
};
template <typename K, typename V> class multimap final : public base {
private:
  size_t m_max_size = 0;

public:
  multimap(const std::multimap<K, V> &obj) : m_map(obj) {
  }
  multimap(size_t max_size = 0) : m_max_size(max_size) {
  }
  virtual ~multimap() {
  }
  void SetMaxSize(const size_t &max_size) {
    std::lock_guard<std::mutex> lock(*mutex_);
    m_max_size = max_size;
  }

public:
  bool empty() const {
    std::lock_guard<std::mutex> lock(*mutex_);
    return m_map.empty();
  }
  size_t push(const K &key, const V &val) {
    std::lock_guard<std::mutex> lock(*mutex_);
    if (m_max_size > 0) {
      while (m_map.size() >= m_max_size) {
        m_map.erase(std::prev(m_map.end()));
      }
    }
    m_map.insert(std::make_pair(key, val));
    return m_map.size();
  }

  std::shared_ptr<std::list<V>>
  search(const std::function<bool(const V &)> &cbSerach) const {
    std::shared_ptr<std::list<V>> result;
    std::lock_guard<std::mutex> lock(*mutex_);
    for (const auto &node : m_map) {
      if (cbSerach(node.second)) {
        if (!result) {
          result = std::make_shared<std::list<V>>();
        }
        result->push_front(node.second);
      } else {
        break;
      }
    }
    return result;
  }

  std::shared_ptr<std::list<V>> get(const size_t &count) {
    std::shared_ptr<std::list<V>> result;
    std::lock_guard<std::mutex> lock(*mutex_);
    if (count > 0) {
      size_t pos = 0;
      for (const auto &node : m_map) {
        if (count < pos)
          break;
        if (!result) {
          result = std::make_shared<std::list<V>>();
        }
        result->push_front(node.second);
        ++pos;
      }
    }
    return result;
  }

  std::shared_ptr<std::tuple<K, V>> pop() {
    std::shared_ptr<std::tuple<K, V>> val;
    std::lock_guard<std::mutex> lock(*mutex_);
    if (m_map.empty()) {
      return val;
    }
    auto it = m_map.begin();
    if (it == m_map.end()) {
      return val;
    }
    val = std::make_shared<std::tuple<K, V>>(std::tie(it->first, it->second));
    m_map.erase(it);
    return val;
  }
  void pop_back(size_t count = 1) {
    std::lock_guard<std::mutex> lock(*mutex_);
    if (m_map.empty()) {
      return;
    }
    if (m_map.size() <= count) {
      m_map.clear();
      return;
    }
    do {
      if (count <= 0) {
        break;
      }
      if (m_map.empty()) {
        break;
      }
      m_map.erase(m_map.end()--);
      --count;
    } while (1);
  }

  std::shared_ptr<V> pop(const K &key) {
    std::shared_ptr<V> result;
    std::lock_guard<std::mutex> lock(*mutex_);
    auto found = m_map.find(key);
    if (found == m_map.end()) {
      return result;
    }
    result = std::make_shared<V>(std::move(found->second));
    m_map.erase(found);
    return result;
  }

  std::shared_ptr<V> search(const K &key, bool itclear = false) {
    std::shared_ptr<V> result;
    std::lock_guard<std::mutex> lock(*mutex_);
    auto found = m_map.find(key);
    if (found == m_map.end())
      return result;
    result = std::make_shared<V>(std::move(found->second));
    if (itclear)
      m_map.erase(found);
    return result;
  }

  std::shared_ptr<V> search(const K &key) const {
    std::shared_ptr<V> result;
    std::lock_guard<std::mutex> lock(*mutex_);
    auto found = m_map.find(key);
    if (found == m_map.end())
      return result;
    result = std::make_shared<V>(std::move(found->second));
    return result;
  }

  std::shared_ptr<std::tuple<K, V>>
  pop(const std::function<void(const K &_key, V &_val)> &_cb) {
    std::shared_ptr<std::tuple<K, V>> val;
    std::lock_guard<std::mutex> lock(*mutex_);
    if (m_map.empty()) {
      return val;
    }
    auto it = m_map.begin();
    if (it == m_map.end()) {
      return val;
    }
    val = std::make_shared<std::tuple<K, V>>(std::tie(it->first, it->second));
    _cb(it->first, it->second);
    m_map.erase(it);
    return val;
  }
  bool pop(const K &key,
           const std::function<void(const K &_key, V &_val)> &_cb) {
    std::lock_guard<std::mutex> lock(*mutex_);
    if (m_map.empty()) {
      return false;
    }
    auto it = m_map.find(key);
    if (it == m_map.end()) {
      return false;
    }
    _cb(it->first, it->second);
    m_map.erase(it);
    return true;
  }
  bool pop(const K &key, const V &value,
           const std::function<void(const K &, const V &)> &pop_cb) {
    if (m_map.empty()) {
      return false;
    }
    std::lock_guard<std::mutex> lock(*mutex_);
    auto itFind = m_map.find(key);
    if (itFind != m_map.end()) {
      for (std::size_t i = 0; i < m_map.count(key); ++i, ++itFind) {
        if (itFind->second == value) {
          if (pop_cb) {
            pop_cb(itFind->first, itFind->second);
          }
          m_map.erase(itFind);
          return true;
        }
      }
    }
    return false;
  }
  void
  riterate(const std::function<void(const K &, const V &)> &riterate_cb) const {
    std::lock_guard<std::mutex> lock(*mutex_);
    if (m_map.empty()) {
      return;
    }
    for (auto rit = m_map.rbegin(); rit != m_map.rend(); ++rit) {
      riterate_cb(rit->first, rit->second);
    }
  }

  std::vector<V> pops(const K &key) {
    std::vector<V> result;
    std::lock_guard<std::mutex> lock(*mutex_);
    if (m_map.empty())
      return result;
    auto find = m_map.find(key);
    if (find != m_map.end()) {
      for (std::size_t i = 0; i < m_map.count(key); ++i, ++find) {
        result.emplace_back(find->second);
      }
      m_map.erase(key);
    }
    return result;
  }

  void iterate_clear(const std::function<void(const K &, V &, bool & /*break*/,
                                              bool & /*clear*/)> &iterate_cb) {
    std::lock_guard<std::mutex> lock(*mutex_);
    if (!m_map.empty()) {
      bool __break = false;
      bool __clear = false;
      for (auto it = m_map.begin(); it != m_map.end();) {
        if (__break)
          break;
        __break = false;
        __clear = false;
        iterate_cb(it->first, it->second, __break, __clear);
        if (__clear) {
          it = m_map.erase(it);
          continue;
        }
        ++it;
      }
    }
  }
  void
  iterate(const std::function<void(const K &, const V &, const int &cycle_index,
                                   bool &_iterate_break)> &cb) const {
    int cycle_index = 0;
    bool _iterate_break = false;
    std::lock_guard<std::mutex> lock(*mutex_);
    if (m_map.empty()) {
      return;
    }
    for (auto it = m_map.begin(); it != m_map.end(); ++it) {
      if (!_iterate_break) {
        cb(it->first, it->second, ++cycle_index, _iterate_break);
      } else {
        break;
      }
    }
  }
  auto count(const K &key) {
    std::lock_guard<std::mutex> lock(*mutex_);
    return m_map.count(key);
  }
  void iterate(const std::function<void(const K &, V &)> &cb) {
    std::lock_guard<std::mutex> lock(*mutex_);
    if (m_map.empty()) {
      return;
    }
    for (auto it = m_map.begin(); it != m_map.end(); ++it) {
      cb(it->first, it->second);
    }
  }
  unsigned long long size() {
    std::lock_guard<std::mutex> lock(*mutex_);
    return m_map.size();
  }
  bool empty() {
    std::lock_guard<std::mutex> lock(*mutex_);
    return m_map.empty();
  }
  void clear() {
    std::lock_guard<std::mutex> lock(*mutex_);
    m_map.clear();
  }
  std::shared_ptr<std::multimap<K, V, std::greater<K>>> src() const {
    std::lock_guard<std::mutex> lock(*mutex_);
    return std::make_shared<decltype(m_map)>(m_map);
  }

private:
  std::multimap<K, V, std::greater<K>> m_map;
};
} // namespace container

template <typename T>
static size_t OneUnknownParseStruct(const char *buf, const size_t &nbuf,
                                    std::vector<T> &Out) {
  Out.clear();
  if (!buf || nbuf <= 0)
    return 0;
  size_t pos = 0;
  const size_t nnode = sizeof(T);
  do {
    if (pos >= nbuf)
      break;
    T *data = (T *)(buf + pos);
    if (!data)
      break;
    Out.emplace_back(*data);
    pos += nnode;
  } while (1);
  return Out.size();
}
template <typename T>
static size_t OneUnknownParseStruct(const char *buf, const size_t &nbuf_total,
                                    const size_t &nbuf_node,
                                    std::vector<T> &Out) {
  Out.clear();
  if (!buf || nbuf_total <= 0 || nbuf_node <= 0)
    return 0;
  size_t pos = 0;
  do {
    if (pos >= nbuf_total)
      break;
    auto data = (T *)(buf + pos);
    if (!data)
      break;
    Out.emplace_back(*data);
    pos += nbuf_node;
  } while (1);
  return Out.size();
}

template <typename T>
static std::shared_ptr<std::vector<T>>
OneUnknownParseStruct(const char *buf, const size_t &nbuf) {
  std::shared_ptr<std::vector<T>> result;
  if (!buf || nbuf <= 0)
    return result;
  size_t pos = 0;
  const size_t nnode = sizeof(T);
  do {
    if (!result) {
      result = std::make_shared<std::vector<T>>();
    }
    if (pos >= nbuf) {
      break;
    }
    auto data = (T *)(buf + pos);
    if (!data) {
      break;
    }
    result->emplace_back(*data);
    pos += nnode;
  } while (1);
  return result;
}
} // namespace stl

/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 05 Nov 2024 12:42:24 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__B8180CB2_CC67_4024_933A_E67AC94FA0DB__