#include "brwcfg.h"
ChromiumMain::ChromiumMain(const std::string &server_addr)
    : IChromium(ChromiumProcessType::ChromiumProcess, server_addr) {
  Init();
}
ChromiumMain::~ChromiumMain() {
  UnInit();
}
void ChromiumMain::Init() {
  uvpp_config_->RegisterClientMessageReceiveReplyCb([](const ISession *session,
                                                       const CommandType &cmd,
                                                       const IBuffer *buffer,
                                                       CommandType *cmd_reply,
                                                       IBuffer *buffer_reply) {
    brwcfg::IConfigure::Input::ResultCode *resultCode =
        (brwcfg::IConfigure::Input::ResultCode *)malloc(
            sizeof(brwcfg::IConfigure::Input::ResultCode));
    switch (static_cast<command_type_t>(cmd)) {
    case command_type_t::LCT_SERVER_REQCOMMAND:
      [[fallthrough]];
    case command_type_t::LCT_SERVER_REQINPUT: {
      if (buffer->Empty())
        break;
      IRequest req(std::string(buffer->GetData(), buffer->GetDataSize()));
      req.SetErrno(mp_errno_t::MP_EINVALIDREQ);
      *cmd_reply = CommandType(command_type_t::LCT_CHROMIUM_MAIN_REPNOTIFY);
      do {
        if (req.GetCfg().type != brwcfg::IConfigure::Type::BrwInputEvent &&
            req.GetCfg().type != brwcfg::IConfigure::Type::BrwCommandEvent) {
          req.SetErrno(mp_errno_t::MP_EINVEVENT);
          break;
        }
        Brwcfg::IBrowser *brwObj =
            Brwcfg::GetOrCreate()->GetChromiumBrowserObj();

        if (!brwObj) {
          req.SetErrno(mp_errno_t::MP_ESYSNOTFOUND);
          break;
        }
        brwObj->IForwardInputEvent(buffer->GetData(), buffer->GetDataSize());
        req.SetErrno(mp_errno_t::MP_DONE);
      } while (0);
      std::string resBody = req.GetRes();
      // if (req.GetErrno() != mp_errno_t::MP_DONE)
      buffer_reply->SetData(resBody.data(), resBody.size());

    } break;
    case command_type_t::LCT_SERVER_SERVERREADY: {
      Brwcfg::GetOrCreate()->ServerStatus(true);
    } break;
    default:
      break;
    }
    LOG_INFO("module({}) reqCmd({:x}) reqBody({})", "ChromiumMain",
             static_cast<unsigned long>(cmd),
             (buffer && buffer->GetDataSize() > 0)
                 ? std::string(buffer->GetData(), buffer->GetDataSize())
                 : "");
  });
  uvpp_config_->RegisterClientConnection([](const ISession *session,
                                            CommandType *cmd_reply,
                                            IBuffer *buffer_reply) {
    *cmd_reply = CommandType(command_type_t::LCT_CHROMIUM_MAIN_PLEASEPREPARE);
    buffer_reply->SetData("Please prepare on main",
                          strlen("Please prepare on main"));
    LOG_INFO("module({}) ({})", "ChromiumMain", "Request server prepare.");
  });
}
void ChromiumMain::UnInit() {
}
void ChromiumMain::Release() const {
  delete this;
}
void ChromiumMain::OnChromiumInputEvent(
    const unsigned long long &reqid,
    const brwcfg::IConfigure::Input::ResultCode &resultCode) const {
  do {
    if (!uvpp_client_ || !uvpp_)
      break;
    rapidjson::Document doc(rapidjson::kObjectType);
    doc.AddMember(
        rapidjson::Value().SetString("status", doc.GetAllocator()).Move(),
        rapidjson::Value().SetInt(static_cast<int>(MP_EASYNCNOTIFY)).Move(),
        doc.GetAllocator());
    doc.AddMember(
        rapidjson::Value()
            .SetString("inputEventResultCode", doc.GetAllocator())
            .Move(),
        rapidjson::Value().SetInt(static_cast<int>(resultCode)).Move(),
        doc.GetAllocator());
    doc.AddMember(
        rapidjson::Value().SetString("brwid", doc.GetAllocator()).Move(),
        rapidjson::Value().SetUint64(policy_id_).Move(), doc.GetAllocator());
    doc.AddMember(
        rapidjson::Value().SetString("reqid", doc.GetAllocator()).Move(),
        rapidjson::Value().SetUint64(reqid).Move(), doc.GetAllocator());
    doc.AddMember(
        rapidjson::Value().SetString("reqBody", doc.GetAllocator()).Move(),
        rapidjson::Value().SetString("{}", doc.GetAllocator()).Move(),
        doc.GetAllocator());
    std::string body = Json::toString(doc);

    uvpp::IBuffer *buffer = uvpp_->CreateBuffer(body.data(), body.size());
    uvpp_client_->Write(
        static_cast<unsigned long>(command_type_t::LCT_CHROMIUM_MAIN_REPNOTIFY),
        buffer);
  } while (0);
}
