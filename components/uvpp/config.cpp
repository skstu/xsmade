#include "config.h"

Config::Config() {
  Init();
}
Config::~Config() {
  UnInit();
}
void Config::Init() {
#if 0 //_DEBUG
	m_KeepAliveMS.store(5000000);
	m_SessionTimeoutMS.store(30000000);
#else
  m_KeepAliveMS.store(20000);
  m_SessionTimeoutMS.store(30000);
#endif
  m_ClientReconnectionIntervalMS.store(10000);
  m_Address = R"(0.0.0.0:8888)"; /*[0:0:0:0:0:0:0:0]:8888*/
}
void Config::UnInit() {
}
void Config::SetServiceType(const unsigned long &type) {
  std::lock_guard<std::mutex> lock{*mtx_};
  service_type_ = type;
}
unsigned long Config::GetServiceType() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return service_type_;
}
void Config::Address(const char *addr, const size_t &addr_len) {
  std::lock_guard<std::mutex> lock{*mtx_};
  m_Address.clear();
  if (addr && addr_len > 0)
    m_Address.append(addr, addr_len);
}
const char *Config::Address() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return m_Address.c_str();
}
unsigned long long Config::KeepAliveTimeMS() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return m_KeepAliveMS.load();
}
void Config::KeepAliveTimeMS(const unsigned long long &ms) {
  std::lock_guard<std::mutex> lock{*mtx_};
  m_KeepAliveMS.store(ms);
}
unsigned long long Config::SessionTimeoutMS() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return m_SessionTimeoutMS.load();
}
void Config::SessionTimeoutMS(const unsigned long long &ms) {
  std::lock_guard<std::mutex> lock{*mtx_};
  m_SessionTimeoutMS.store(ms);
}
unsigned long long Config::ClientReconnectionIntervalMS() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return m_ClientReconnectionIntervalMS.load();
}
void Config::ClientReconnectionIntervalMS(const unsigned long long &ms) {
  std::lock_guard<std::mutex> lock{*mtx_};
  m_ClientReconnectionIntervalMS.store(ms);
}
void Config::EnableClientWaitForTheInitialConnectionAndReceiveResult(
    const bool &enable) {
  std::lock_guard<std::mutex> lock{*mtx_};
  m_EnableClientWaitForTheInitialConnectionAndReceiveResult.store(enable);
}
bool Config::EnableClientWaitForTheInitialConnectionAndReceiveResult() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return m_EnableClientWaitForTheInitialConnectionAndReceiveResult.load();
}
unsigned long Config::Version() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return PRODUCT_VERSION_HEX;
}
const char *Config::VersionString() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return PRODUCT_VERSION;
}
void Config::RegisterServerReadyCb(const tfOnServerReadyCb &cb) {
  std::lock_guard<std::mutex> lock{*mtx_};
  server_ready_cb_ = cb;
}
void Config::OnServerReady(void) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (server_ready_cb_)
    server_ready_cb_();
}
void Config::RegisterServerExitCb(const tfOnServerExitCb &cb) {
  std::lock_guard<std::mutex> lock{*mtx_};
  server_exit_cb_ = cb;
}
void Config::RegisterServerExitBeforeCb(const tfOnServerExitBefore &cb) {
  std::lock_guard<std::mutex> lock{*mtx_};
  server_exit_before_cb_ = cb;
}
void Config::OnServerExitBefore(const ISession *session) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (server_exit_before_cb_)
    server_exit_before_cb_(session);
}
void Config::OnServerExit(void) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (server_exit_cb_)
    server_exit_cb_();
}
void Config::RegisterServerErrorCb(const tfOnServerErrorCb &cb) {
  std::lock_guard<std::mutex> lock{*mtx_};
  server_error_cb_ = cb;
}
void Config::OnServerError(const ISession *session, const SystemErrorno &err,
                           const IBuffer *msg) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (server_error_cb_)
    server_error_cb_(session, err, msg);
}
void Config::RegisterServerHelloCb(const tfOnServerHelloCb &cb) {
  std::lock_guard<std::mutex> lock{*mtx_};
  server_hello_cb_ = cb;
}
void Config::OnServerHello(const ISession *session, const IBuffer *data,
                           IBuffer *reply) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (server_hello_cb_)
    server_hello_cb_(session, data, reply);
}
void Config::RegisterClientWelcomeCb(const tfOnClientWelcomeCb &cb) {
  std::lock_guard<std::mutex> lock{*mtx_};
  client_welcome_cb_ = cb;
}
void Config::OnClientWelcome(const IBuffer *recBuffer,
                             IBuffer *repBuffer) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (client_welcome_cb_)
    client_welcome_cb_(recBuffer, repBuffer);
}
void Config::RegisterServerWelcomeSendHookCb(
    const tfOnHookServerWelcomeSendCb &cb) {
  std::lock_guard<std::mutex> lock{*mtx_};
  server_welcome_send_hook_cb_ = cb;
}
void Config::OnHookServerWelcomeSend(const ISession *pSession,
                                     IBuffer *pWelcome) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (server_welcome_send_hook_cb_)
    server_welcome_send_hook_cb_(pSession, pWelcome);
}
void Config::RegisterServerSessionReadyCb(const tfOnServerSessionReadyCb &cb) {
  std::lock_guard<std::mutex> lock{*mtx_};
  server_session_ready_cb_ = cb;
}
void Config::OnServerSessionReady(const ISession *pSession) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (server_session_ready_cb_)
    server_session_ready_cb_(pSession);
}
void Config::RegisterServerSessionAcceptCb(
    const tfOnServerSessionAcceptCb &cb) {
  std::lock_guard<std::mutex> lock{*mtx_};
  server_session_accept_cb_ = cb;
}
void Config::OnServerSessionAccept(const ISession *pSession,
                                   const bool &result) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (server_session_accept_cb_)
    server_session_accept_cb_(pSession, result);
}
void Config::RegisterServerSessionCreateCb(
    const tfOnServerSessionCreateCb &cb) {
  std::lock_guard<std::mutex> lock{*mtx_};
  server_session_create_cb_ = cb;
}
void Config::RegisterServerSessionDestroyCb(
    const tfOnServerSessionDestroyCb &cb) {
  std::lock_guard<std::mutex> lock{*mtx_};
  server_session_destroy_cb_ = cb;
}
void Config::OnServerSessionCreate(const ISession *pSession) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (server_session_create_cb_)
    server_session_create_cb_(pSession);
}
void Config::OnServerSessionDestroy(const ISession *pSession) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (server_session_destroy_cb_)
    server_session_destroy_cb_(pSession);
}
void Config::RegisterServerSessionTimeoutCb(
    const tfOnServerSessionTimeoutCb &cb) {
  std::lock_guard<std::mutex> lock{*mtx_};
  server_session_timeout_cb_ = cb;
}
void Config::OnServerSessionTimeout(const ISession *pSession,
                                    const std::time_t &timeout) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (server_session_timeout_cb_)
    server_session_timeout_cb_(pSession, timeout);
}
void Config::RegisterServerSessionWriteHookCb(
    const tfOnHookServerSessionWriteCb &cb) {
  std::lock_guard<std::mutex> lock{*mtx_};
  server_session_write_hook_cb_ = cb;
}
void Config::OnHookServerSessionWrite(const ISession *pSession,
                                      IBuffer *pBuffer) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (server_session_write_hook_cb_)
    server_session_write_hook_cb_(pSession, pBuffer);
}
void Config::RegisterServerMessageCb(const tfOnServerMessageCb &cb) {
  std::lock_guard<std::mutex> lock{*mtx_};
  server_message_cb_ = cb;
}
void Config::RegisterServerMessageReceiveReplyCb(
    const tfOnServerMessageReceiveReply &cb) {
  std::lock_guard<std::mutex> lock{*mtx_};
  server_message_receive_reply_cb_ = cb;
}
void Config::OnServerMessage(const ISession *pSession, const CommandType &cmd,
                             const IBuffer *pMsg) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (server_message_cb_)
    server_message_cb_(pSession, cmd, pMsg);
}
void Config::OnServerMessageReceiveReply(const ISession *pSession,
                                         const CommandType &cmd,
                                         const IBuffer *pMsg,
                                         CommandType &repCmd,
                                         IBuffer *repMsg) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (server_message_receive_reply_cb_)
    server_message_receive_reply_cb_(pSession, cmd, pMsg, repCmd, repMsg);
}
void Config::RegisterServertfKeepAliveCb(const tfOnServerKeepAliveCb &cb) {
  std::lock_guard<std::mutex> lock{*mtx_};
  server_keep_alive_cb_ = cb;
}
void Config::OnServertfKeepAlive(const ISession *pSession, const IBuffer *msg,
                                 IBuffer *rep) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (server_keep_alive_cb_)
    server_keep_alive_cb_(pSession, msg, rep);
}

void Config::RegisterClientForceCloseCb(const tfOnClientForceCloseCb &cb) {
  std::lock_guard<std::mutex> lock{*mtx_};
  client_force_close_cb_ = cb;
}
void Config::OnClientForceClose(const ISession *pSession) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (client_force_close_cb_)
    client_force_close_cb_(pSession);
}
void Config::RegisterClientErrorCb(const tfOnClientErrorCb &cb) {
  std::lock_guard<std::mutex> lock{*mtx_};
  client_error_cb_ = cb;
}
void Config::OnClientError(const ISession *pSession, const SystemErrorno &err,
                           const IBuffer *buffer) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (client_error_cb_)
    client_error_cb_(pSession, err, buffer);
}
void Config::RegisterClientMessageCb(const tfOnClientMessageCb &cb) {
  std::lock_guard<std::mutex> lock{*mtx_};
  client_message_cb_ = cb;
}
void Config::RegisterClientMessageReceiveReplyCb(
    const tfOnClientMessageReceiveReply &cb) {
  std::lock_guard<std::mutex> lock{*mtx_};
  client_message_receive_reply_cb_ = cb;
}
void Config::OnClientMessageCb(const ISession *pSession, const CommandType &cmd,
                               const IBuffer *msg) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (client_message_cb_)
    client_message_cb_(pSession, cmd, msg);
}
void Config::OnClientMessageReceiveReplyCb(const ISession *pSession,
                                           const CommandType &cmd,
                                           const IBuffer *msg,
                                           CommandType &repCmd,
                                           IBuffer *repMsg) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (client_message_receive_reply_cb_)
    client_message_receive_reply_cb_(pSession, cmd, msg, repCmd, repMsg);
}
void Config::RegisterClientExit(const tfOnClientExitCb &cb) {
  std::lock_guard<std::mutex> lock{*mtx_};
  client_exit_cb_ = cb;
}
void Config::OnClientExit() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (client_exit_cb_)
    client_exit_cb_();
}
void Config::OnClientDisconnection(const ISession *pSession) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (client_disconnection_cb_)
    client_disconnection_cb_(pSession);
}
void Config::OnClientConnection(const ISession *pSession) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (client_connection_cb_)
    client_connection_cb_(pSession);
}
void Config::RegisterClientDisconnection(const tfOnClientDisconnection &cb) {
  std::lock_guard<std::mutex> lock{*mtx_};
  client_disconnection_cb_ = cb;
}
void Config::RegisterClientConnection(const tfOnClientConnection &cb) {
  std::lock_guard<std::mutex> lock{*mtx_};
  client_connection_cb_ = cb;
}
void Config::RegisterClientSessionWriteHookCb(
    const tfOnHookClientSessionWriteCb &cb) {
  std::lock_guard<std::mutex> lock{*mtx_};
  client_session_write_hook_cb_ = cb;
}
void Config::OnClientSessionWriteHookCb(const ISession *pSession,
                                        IBuffer *msg) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  if (client_session_write_hook_cb_)
    client_session_write_hook_cb_(pSession, msg);
}
//////////////////////////////////////////////////////////////////////////////////
static Config *__gpConfig = nullptr;
Config *Config::Create() {
  if (!__gpConfig)
    __gpConfig = new Config();
  return __gpConfig;
}
void Config::Destroy() {
  SK_DELETE_PTR(__gpConfig);
}
Config *Config::Get() {
  return Config::Create();
}