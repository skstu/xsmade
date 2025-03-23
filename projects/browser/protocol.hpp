#if !defined(__236A1017_0AB0_494A_8A5E_A6F008502268__)
#define __236A1017_0AB0_494A_8A5E_A6F008502268__

enum class LocalCommandType : unsigned long {
  LCT_UNKNOWN = 0x0000,
  LCT_CHROMIUM_GPU_PLEASEPREPARE = 0x20100,
  LCT_CHROMIUM_GPU_FRAMEBUFFERSTREAM = 0x20110,
  LCT_CHROMIUM_GPU_REPNOTIFY = 0x20120,
  LCT_CHROMIUM_MAIN_PLEASEPREPARE = 0x20200,
  LCT_CHROMIUM_MAIN_REPNOTIFY = 0x20210,
  LCT_SERVER_SERVERREADY = 0x20300,
  LCT_SERVER_REQINPUT = 0x20310,
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
  inline const brwcfg::IConfigure &GetCfg() const;
  inline std::string GetRes();
  inline const mp_errno_t &GetErrno() const {
    return errno_;
  }
  inline void SetErrno(const mp_errno_t &err) {
    errno_ = err;
  }

private:
  std::atomic_bool ready_ = false;
  rapidjson::Document repDoc_;
  mp_errno_t errno_ = mp_errno_t::MP_EUNKN;

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
  if (!ready_.load()) {
    errno_ = MP_EINVALIDREQ;
  }

  repDoc_.AddMember(
      rapidjson::Value().SetString("status", repDoc_.GetAllocator()).Move(),
      rapidjson::Value().SetInt(errno_).Move(), repDoc_.GetAllocator());
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