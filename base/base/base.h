#if !defined(__9B3927D2_A7D6_4891_B852_B39860822976__)
#define __9B3927D2_A7D6_4891_B852_B39860822976__

#ifdef __cplusplus
extern "C" {
#endif
#include <uv.h>
#ifdef __cplusplus
}
#endif
#include <base.hpp>
using namespace xs::base;
#ifdef __OSLINUX__
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <spawn.h>    // posix_spawn
#include <signal.h>   // kill
#include <sys/wait.h> // waitpid
#include <fcntl.h>    // file locks
#include <sys/file.h> // flock
#include <pwd.h>      // getpwuid
#include <dlfcn.h>
#endif
#include "task.h"

class Base final {
public:
  static Base *GetOrCreate();
  static void Destroy();

public:
  bool Ready() const;
  bool Start();
  void Stop();
  template <typename RT, typename... Args>
  void AddTask(std::function<RT(Args...)> func, Args &&...args) {
    std::lock_guard<std::mutex> lock(*mtx_);
    tasks_.add(std::move(func), std::forward<Args>(args)...);
  }

private:
  Base();
  ~Base();
  void Init();
  void UnInit();

private:
  void Process();
  Tasks tasks_;
  uv_thread_t thread_;
  std::atomic_bool open_ = false;
  std::atomic_bool ready_ = false;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 05 Apr 2025 23:29:01 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__9B3927D2_A7D6_4891_B852_B39860822976__
