#include "server.h"
//!@ Private
void Server::Process(void) {
  const Config *pConfig = Config::GetOrCreate();
  do {
    do { //!@ process request queue.
      if (request_queue_.empty())
        break;
      mp_errno_t ret = mp_errno_t::MP_EUNKN;
      std::string resBody("{}");
      IRequest *req = *request_queue_.pop();
      if (!req->Ready())
        break;
      LOG_INFO("module({}) cfgType({:x}) cfgBody({})", "ServerProcess",
               static_cast<unsigned long>(req->GetCfg().type),
               req->GetCfg().Serialization());
      const policy_id_t policy_id = req->GetCfg().policy.id;

      switch (req->GetCfg().type) {
      case brwcfg::IConfigure::Type::BrwCreate: {
        Brwobj *brwObj =
            Brwmnr::GetOrCreate()->CreateBrowser(req->GetCfg(), ret);
        if (!brwObj)
          break;
      } break;
      case brwcfg::IConfigure::Type::BrwDestory: {
        const policy_id_t policy_id = req->GetCfg().policy.id;
        Brwmnr::GetOrCreate()->DestroyBrowser(policy_id, ret);

      } break;
      case brwcfg::IConfigure::Type::BrwInputEvent: {
        Brwobj *brwobj = Brwmnr::GetOrCreate()->GetBrowser(policy_id);
        if (!brwobj) {
          ret = mp_errno_t::MP_ENOTFOUND;
          break;
        }
        if (!RequestInput(policy_id, req->GetCfg().Serialization())) {
          ret = mp_errno_t::MP_EREQFAILED;
          break;
        }
        ret = MP_DONE;
      } break;
      default:
        break;
      }
    } while (0);
    if (!open_.load()) {
      LOG_INFO("module({}) ({})", "ServerProcess", "Process thread stopped.");
      break;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  } while (1);
}