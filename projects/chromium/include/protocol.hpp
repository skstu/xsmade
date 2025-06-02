#if !defined(__236A1017_0AB0_494A_8A5E_A6F008502268__)
#define __236A1017_0AB0_494A_8A5E_A6F008502268__

#define ENABLE_DEVELOP_DEBUG 0
#define ENABLE_DEVELOP_DEBUG_NOCHROME 0
#define ENABLE_UVPP 0

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
  XX(EINVALIDREQID, "invalid request id")                                      \
  XX(EALREADY, "already running")                                              \
  XX(EINVBRWID, "invalid browser id")                                          \
  XX(EBRWENVCFG, "browser configure error")                                    \
  XX(EBRWOPEN, "browser open error")                                           \
  XX(EREQFAILED, "reqeust failed")                                             \
  XX(EFAILED, "failed")                                                        \
  XX(EINVEVENT, "invalid event")                                               \
  XX(ESYSNOTFOUND, "system error not found")                                   \
  XX(ESYSTEMEXC, "system execure error")                                       \
  XX(ESEEDETAILS, "Please see details")                                        \
  XX(EASYNCNOTIFY, "Asynchronous Notification")                                \
  XX(ECFGNOENABLE, "configure no enable")                                      \
  XX(EUNKN, "unknown error")

/* Define MP_* values for each errno value above */
#define MP_ERRNO_GEN(n, s) MP_##n,
enum mp_errno_t { MP_ERRNO_MAP(MP_ERRNO_GEN) };

#undef MP_ERRNO_GEN
////////////////////////////////////////////////////////////////////////////////
static const char *mp__unknown_err_code(int err) {
  char buf[256];
  char *copy = NULL;

  // snprintf(buf, sizeof(buf), "Unknown system error %d", err);
  sprintf(buf, "Unknown system error %d", err);
  do {
    size_t len = strlen(buf) + 1;
    char *m = (char *)malloc(len);
    if (m == NULL)
      break;
    copy = (char *)memcpy(m, buf, len);
  } while (0);

  return copy != NULL ? copy : "Unknown system error";
}

#define MP_ERR_NAME_GEN(name, _)                                               \
  case MP_##name:                                                              \
    return #name;
static const char *mp_err_name(int err) {
  switch (err) { MP_ERRNO_MAP(MP_ERR_NAME_GEN) }
  return mp__unknown_err_code(err);
}
#undef MP_ERR_NAME_GEN

#define MP_STRERROR_GEN(name, msg)                                             \
  case MP_##name:                                                              \
    return msg;
static const char *mp_strerror(int err) {
  switch (err) { MP_ERRNO_MAP(MP_STRERROR_GEN) }
  return mp__unknown_err_code(err);
}
#undef MP_STRERROR_GEN
} /// extern "C"

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
typedef int tfPipeStatusType;
typedef tfPipeStatusType tfPipeErrornoType;
typedef unsigned long tfPipeCommandType;
typedef unsigned char tfChromiumProcessType;
typedef enum : unsigned char {
  CHROMIUM_PROCESS_TYPE_UNKNOWN = 0x0,
  CHROMIUM_PROCESS_TYPE_MAIN = 0x1,
  CHROMIUM_PROCESS_TYPE_RENDERER = 0x2,
  CHROMIUM_PROCESS_TYPE_GPU = 0x3,
  CHROMIUM_PROCESS_TYPE_UTILITY_NETWORK = 0x4,
  CHROMIUM_PROCESS_TYPE_CRASHPAD_HANDLER = 0x5,
  CHROMIUM_PROCESS_TYPE_UTILITY_STORAGE = 0x6,

  CHROMIUM_PROCESS_TYPE_BASE = 0xF,
} chromium_process_type_t;
typedef enum : unsigned long {
  CMD_UNKNOWN = 0x00000,
  CMD_HELLO = 0x30100,
  CMD_STREAM_GPU_VIZ_DRAWING_FRAME = 0x30200,
  CMD_TESTS = 0x30F00,
  CMD_BASE = 0xFFFFFFF0,
} command_type_t;
inline command_type_t
operator|(const command_type_t &cmd,
          const chromium_process_type_t &chromium_process_type) {
  return static_cast<command_type_t>(
      static_cast<unsigned long>(cmd) |
      static_cast<unsigned long>(chromium_process_type));
}
inline command_type_t GetCommandType(const command_type_t &cmd) {
  return static_cast<command_type_t>(
      static_cast<unsigned long>(cmd) &
      static_cast<unsigned long>(command_type_t::CMD_BASE));
}
inline chromium_process_type_t
GetChromiumProcessType(const command_type_t &cmd) {
  return static_cast<chromium_process_type_t>(
      static_cast<unsigned long>(cmd) &
      static_cast<unsigned long>(
          chromium_process_type_t::CHROMIUM_PROCESS_TYPE_BASE));
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

enum class ChromiumProcessType : unsigned long {
  ChromiumUnknownProcess = 0,
  ChromiumProcess,
  ChromiumGpuProcess,
  ChromiumRendererProcess,
  ChromiumUtilityNetworkMojomServiceProcess,
  ChromiumUtilityStorageMojomServiceProcess,
  ChromiumCrashpadHandlerProcess,
};

/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 18 Mar 2025 06:33:34 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__236A1017_0AB0_494A_8A5E_A6F008502268__