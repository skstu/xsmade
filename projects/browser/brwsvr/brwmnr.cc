#include "server.h"

Brwmnr::Brwmnr() {
  Init();
}
Brwmnr::~Brwmnr() {
  UnInit();
}
void Brwmnr::Init() {
}
void Brwmnr::UnInit() {
}
Brwobj *Brwmnr::CreateBrowser(const brwcfg::IConfigure &cfg, mp_errno_t &ret) {
  Brwobj *result = nullptr;
  std::lock_guard<std::mutex> lck(*mtx_);
  const auto brwid = cfg.policy.id;
  do {
    if (brwid <= 0) {
      ret = mp_errno_t::MP_EINVBRWID;
      break;
    }
    auto fExists = brwobjs_.find(brwid);
    if (fExists != brwobjs_.end()) {
      result = fExists->second;
      ret = MP_EALREADY;
      break;
    }
    if (!Config::GetOrCreate()->CreateBrowserEnv(brwid, cfg.Serialization())) {
      ret = mp_errno_t::MP_EBRWENVCFG;
      break;
    }
    result = new Brwobj(brwid);
    if (!result->Open()) {
      ret = MP_EFAILED;
      result->Release();
      break;
    }
    brwobjs_[brwid] = result;
    ret = MP_OK;
  } while (0);
  return result;
}
void Brwmnr::DestroyBrowser(const browser_id_t &brwid, mp_errno_t &ret) {
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    auto f = brwobjs_.find(brwid);
    if (f == brwobjs_.end()) {
      ret = MP_ENOTFOUND;
      break;
    }
    f->second->Close();
    f->second->Release();
    brwobjs_.erase(brwid);
    ret = MP_OK;
  } while (0);
}
Brwobj *Brwmnr::GetBrowser(const policy_id_t &plicy_id) const {
  Brwobj *result = nullptr;
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    auto f = brwobjs_.find(plicy_id);
    if (f == brwobjs_.end())
      break;
    result = f->second;
  } while (0);
  return result;
}
///////////////////////////////////////////////////////
static Brwmnr *__gpsBrwmnr = nullptr;
Brwmnr *Brwmnr::GetOrCreate() {
  if (!__gpsBrwmnr) {
    __gpsBrwmnr = new Brwmnr();
  }
  return __gpsBrwmnr;
}
void Brwmnr::Destroy(void) {
  SK_DELETE_PTR(__gpsBrwmnr);
}