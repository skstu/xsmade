#if !defined(__657ADCA2_259A_4C56_81A2_7572A64357CE__)
#define __657ADCA2_259A_4C56_81A2_7572A64357CE__
#include <xs.h>
extern "C" {
////////////////////////////////////////////////////////////////////////////////
#define MP_ERRNO_MAP(XX)                                                       \
  XX(OK, "ok")                                                                 \
  XX(DONE, "done")                                                             \
  XX(EBUYS, "buys")                                                            \
  XX(ETIMEOUT, "timeout")                                                      \
  XX(ENOTFOUND, "not found")                                                   \
  XX(ENOTIMPL, "not implemented")                                              \
  XX(EINVALIDREQ, "invalid request")                                           \
  XX(EALREADY, "already running")                                              \
  XX(EINVBRWID, "invalid browser id")                                          \
  XX(EBRWENVCFG, "browser configure error")                                    \
  XX(EREQFAILED, "reqeust failed")                                             \
  XX(EFAILED, "failed")                                                        \
  XX(EINVEVENT, "invalid event")                                               \
  XX(ESYSNOTFOUND, "system error not found")                                   \
  XX(ESYSTEMEXC, "system execure error")                                       \
  XX(ESEEDETAILS, "Please see details")                                        \
  XX(EUNKN, "unknown error")

/* Define MP_* values for each errno value above */
#define MP_ERRNO_GEN(n, s) MP_##n,
enum mp_errno_t { MP_ERRNO_MAP(MP_ERRNO_GEN) };
#undef MP_ERRNO_GEN
////////////////////////////////////////////////////////////////////////////////
#if !defined(SHARED_API)
#if _WIN32
#define SHARED_API __declspec(dllimport)
#else
#define SHARED_API __attribute__((visibility("default")))
#endif
#endif
////////////////////////////////////////////////////////////////////////////////
typedef unsigned long long browser_id_t;
typedef unsigned long long request_id_t;
typedef browser_id_t policy_id_t;
typedef void (*tf_frame_buffer_stream_cb)(browser_id_t browser_id,
                                          const char *stream,
                                          unsigned long stream_len);
typedef void (*tf_notify_cb)(browser_id_t, request_id_t, mp_errno_t,
                             const char *, unsigned long);
typedef mp_errno_t (*tf_startup)(void);
typedef void (*tf_shutdown)(void);
typedef char *(*tf_malloc_s)(unsigned long long);
typedef void (*tf_free_s)(void **);
typedef mp_errno_t (*tf_request)(const char *, unsigned long);
typedef mp_errno_t (*tf_register_request_cbs)(tf_frame_buffer_stream_cb,
                                              tf_notify_cb);
////////////////////////////////////////////////////////////////////////////////
SHARED_API mp_errno_t startup(void);
SHARED_API void cleanup(void);
SHARED_API char *malloc_s(unsigned long long);
SHARED_API void free_s(void **);
SHARED_API mp_errno_t request(const char *protocol, unsigned long protocol_len);
SHARED_API mp_errno_t register_request_cbs(tf_frame_buffer_stream_cb,
                                           tf_notify_cb);

} /// extern "C"

/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 19 Mar 2025 01:05:09 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__657ADCA2_259A_4C56_81A2_7572A64357CE__