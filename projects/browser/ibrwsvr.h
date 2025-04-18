#if !defined(__657ADCA2_259A_4C56_81A2_7572A64357CE__)
#define __657ADCA2_259A_4C56_81A2_7572A64357CE__
#include <xs.h>
extern "C" {
#if !defined(SHARED_API)
#if _WIN32
#define SHARED_API __declspec(dllimport)
#else
#define SHARED_API __attribute__((visibility("default")))
#endif
#endif
////////////////////////////////////////////////////////////////////////////////
typedef unsigned long browser_id_t;
typedef unsigned long long request_id_t;
typedef browser_id_t policy_id_t;
typedef void (*tf_frame_buffer_stream_cb)(browser_id_t browser_id,
                                          const char *stream,
                                          unsigned long stream_len);
typedef void (*tf_notify_cb)(browser_id_t, request_id_t, int, const char *,
                             unsigned long);
typedef int (*tf_startup)(void);
typedef void (*tf_shutdown)(void);
typedef char *(*tf_malloc_s)(unsigned long long);
typedef void (*tf_free_s)(void **);
typedef int (*tf_request)(const char *, unsigned long);
typedef int (*tf_register_request_cbs)(tf_frame_buffer_stream_cb, tf_notify_cb);
////////////////////////////////////////////////////////////////////////////////
SHARED_API int startup(void);
SHARED_API void cleanup(void);
SHARED_API char *malloc_s(unsigned long long);
SHARED_API void free_s(void **);
SHARED_API int request(const char *protocol, unsigned long protocol_len);
SHARED_API int register_request_cbs(tf_frame_buffer_stream_cb, tf_notify_cb);

} /// extern "C"

/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 19 Mar 2025 01:05:09 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__657ADCA2_259A_4C56_81A2_7572A64357CE__