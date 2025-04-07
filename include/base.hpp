#if !defined(__F1A22018_64A3_4A0E_AD6A_1B8A0183C9EC__)
#define __F1A22018_64A3_4A0E_AD6A_1B8A0183C9EC__
#include "xs.h"
#ifdef __cplusplus
extern "C" {
#endif
XS_EXTERN xs_errno_t xs_base_startup(void);
XS_EXTERN xs_errno_t xs_base_shutdown(void);
XS_EXTERN xs_errno_t xs_base_free(void **p);
XS_EXTERN char *xs_base_malloc(size_t len);
XS_EXTERN xs_errno_t xs_base_spawn(const char *args[], const char *envs[],
                                   void *route,
                                   void (*rescb)(xs_process_id_t, xs_errno_t,
                                                 const void *));
XS_EXTERN xs_errno_t xs_base_kill(int pid, int signum);
typedef xs_errno_t (*tf_xs_base_task_v1)();
XS_EXTERN xs_errno_t xs_base_add_task_v1(tf_xs_base_task_v1);
// XS_EXTERN void AddTask_C_void(void (*func)(void), const char* message) {
//   AddTask([func, message]() {
//       func();  // 调用传入的 C 风格函数
//       std::cout << "Message: " << message << std::endl;
//   });
// }
// XS_EXTERN void AddTask_C_int(int (*func)(int, int), int a, int b) {
//   AddTask([func, a, b]() {
//       int result = func(a, b);  // 调用传入的 C 风格函数并处理返回值
//       std::cout << "Result: " << result << std::endl;
//   });
// }
// XS_EXTERN void AddTask_C_string(void (*func)(const std::string&), const char*
// message) {
//   AddTask([func, message]() {
//       func(message);  // 调用传入的 C 风格函数
//   });
// }

// UV_EXTERN int uv_spawn(uv_loop_t* loop,
//   uv_process_t* handle,
//   const uv_process_options_t* options);
// UV_EXTERN int uv_process_kill(uv_process_t*, int signum);
// UV_EXTERN int uv_kill(int pid, int signum);
// UV_EXTERN uv_pid_t uv_process_get_pid(const uv_process_t*);
#ifdef __cplusplus
}
#endif

namespace xs {
namespace base {
class System final {
public:
  System();
  ~System();

public:
  static xs_errno_t exepath(std::string &);
  static xs_errno_t os_gethostname(std::string &hostname);
  struct utsname_t {
    std::string sysname;
    std::string release;
    std::string version;
    std::string machine;
  };
  static xs_errno_t os_uname(utsname_t &uname);
};
} // namespace base
} // namespace xs

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 04 Apr 2025 23:46:19 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__F1A22018_64A3_4A0E_AD6A_1B8A0183C9EC__