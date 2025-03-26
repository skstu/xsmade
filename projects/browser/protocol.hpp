#if !defined(__236A1017_0AB0_494A_8A5E_A6F008502268__)
#define __236A1017_0AB0_494A_8A5E_A6F008502268__

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

enum class ChromiumProcessType : unsigned long {
  ChromiumUnknownProcess = 0,
  ChromiumProcess,
  ChromiumGpuProcess,
  ChromiumRendererProcess,
  ChromiumUtilityNetworkMojomServiceProcess,
  ChromiumUtilityStorageMojomServiceProcess,
  ChromiumCrashpadHandlerProcess,
};

class IRequest final {
public:
  IRequest(const std::string &protocol_buffer) : source_(protocol_buffer) {
    Init();
  }
  ~IRequest() {
    UnInit();
  }

private:
  inline void Init();
  inline void UnInit();

public:
  inline bool Ready() const;
  inline request_id_t GetReqId() const {
    return cfg_.reqid;
  }
  inline const brwcfg::IConfigure &GetCfg() const;
  inline std::string GetRes();
  inline const mp_errno_t &GetErrno() const {
    return errno_;
  }
  inline void SetErrno(const mp_errno_t &err) {
    errno_ = err;
  }
  inline void SetInputEventResultCode(const int &code) {
    inputEventResultCode_ = code;
  }

private:
  std::atomic_bool ready_ = false;
  rapidjson::Document repDoc_;
  mp_errno_t errno_ = mp_errno_t::MP_EINVALIDREQ;
  int inputEventResultCode_ = -1;

private:
  const std::string source_;
  brwcfg::IConfigure cfg_;
};
inline void IRequest::UnInit() {
  ready_.store(false);
}
inline void IRequest::Init() {
  repDoc_.SetObject();
  do {
    if (source_.empty())
      break;
    cfg_ << source_;
    if (!cfg_.enable) {
      errno_ = MP_ECFGNOENABLE;
      break;
    }
    if (cfg_.policy.id <= 0) {
      errno_ = MP_EINVBRWID;
      break;
    }
    ready_.store(true);
  } while (0);
}
inline bool IRequest::Ready() const {
  return ready_.load();
}
inline const brwcfg::IConfigure &IRequest::GetCfg() const {
  return cfg_;
}
inline std::string IRequest::GetRes() {
  std::string result;
  repDoc_.AddMember(
      rapidjson::Value().SetString("status", repDoc_.GetAllocator()).Move(),
      rapidjson::Value().SetInt(errno_).Move(), repDoc_.GetAllocator());
  repDoc_.AddMember(
      rapidjson::Value().SetString("errname", repDoc_.GetAllocator()).Move(),
      rapidjson::Value()
          .SetString(mp_err_name(errno_), repDoc_.GetAllocator())
          .Move(),
      repDoc_.GetAllocator());
  repDoc_.AddMember(
      rapidjson::Value().SetString("errcode", repDoc_.GetAllocator()).Move(),
      rapidjson::Value()
          .SetString(mp_strerror(errno_), repDoc_.GetAllocator())
          .Move(),
      repDoc_.GetAllocator());
  repDoc_.AddMember(
      rapidjson::Value()
          .SetString("inputEventResultCode", repDoc_.GetAllocator())
          .Move(),
      rapidjson::Value().SetInt(inputEventResultCode_).Move(),
      repDoc_.GetAllocator());
  repDoc_.AddMember(
      rapidjson::Value().SetString("brwid", repDoc_.GetAllocator()).Move(),
      rapidjson::Value().SetUint64(cfg_.policy.id).Move(),
      repDoc_.GetAllocator());
  repDoc_.AddMember(
      rapidjson::Value().SetString("reqid", repDoc_.GetAllocator()).Move(),
      rapidjson::Value().SetUint64(cfg_.reqid).Move(), repDoc_.GetAllocator());
  repDoc_.AddMember(
      rapidjson::Value().SetString("reqBody", repDoc_.GetAllocator()).Move(),
      rapidjson::Value()
          .SetString(cfg_.Serialization().c_str(), repDoc_.GetAllocator())
          .Move(),
      repDoc_.GetAllocator());
  result = Json::toString(repDoc_);
  return result;
}
/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 18 Mar 2025 06:33:34 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__236A1017_0AB0_494A_8A5E_A6F008502268__