#if !defined(__DF04609E_A0A4_4236_8390_A763A9F4678B__)
#define __DF04609E_A0A4_4236_8390_A763A9F4678B__

#include <macros.h>
#include <stl.hpp>
#include <uv.h>
#include <fmt/format.h>
#include <log.hpp>
#include <zipcc.h>
#include "version.h"
#include "export.h"
using namespace uvpp;
#include "uvpp.h"

class Config final : public IConfig {
public:
  static Config *Create();
  static void Destroy();
  static Config *Get();

private:
  Config();
  ~Config();

private:
  void Init();
  void UnInit();

public:
  void SetIdentify(const unsigned long long &) override final;
  unsigned long long GetIdentify() const override final;
  void Address(const char *, const size_t &) override final;
  const char *Address() const override final;
  unsigned long Version() const override final;
  const char *VersionString() const override final;
  void SetServiceType(const unsigned long &) override final;
  unsigned long GetServiceType() const override final;
  unsigned long long SessionTimeoutMS() const override final;
  void SessionTimeoutMS(const unsigned long long &) override final;
  unsigned long long KeepAliveTimeMS() const override final;
  void KeepAliveTimeMS(const unsigned long long &) override final;
  unsigned long long ClientReconnectionIntervalMS() const override final;
  void ClientReconnectionIntervalMS(const unsigned long long &) override final;
  void EnableClientWaitForTheInitialConnectionAndReceiveResult(
      const bool &) override final;
  bool EnableClientWaitForTheInitialConnectionAndReceiveResult()
      const override final;

private:
  std::atomic_ullong m_Identify = 0;
  unsigned long service_type_ = 0;
  std::string m_Address;
  std::atomic_ullong m_SessionTimeoutMS;
  std::atomic_ullong m_KeepAliveMS;
  std::atomic_ullong m_ClientReconnectionIntervalMS;
  std::atomic_bool m_EnableClientWaitForTheInitialConnectionAndReceiveResult =
      false;

protected:
  void RegisterServerReadyCb(const tfOnServerReadyCb &) override final;
  void RegisterServerExitCb(const tfOnServerExitCb &) override final;
  void RegisterServerExitBeforeCb(const tfOnServerExitBefore &) override final;
  void RegisterServerErrorCb(const tfOnServerErrorCb &) override final;
  void RegisterServerHelloCb(const tfOnServerHelloCb &) override final;
  void
  RegisterServerSessionReadyCb(const tfOnServerSessionReadyCb &) override final;
  void RegisterServerSessionAcceptCb(
      const tfOnServerSessionAcceptCb &) override final;
  void RegisterServerSessionCreateCb(
      const tfOnServerSessionCreateCb &) override final;
  void RegisterServerSessionDestroyCb(
      const tfOnServerSessionDestroyCb &) override final;
  void RegisterServerSessionTimeoutCb(
      const tfOnServerSessionTimeoutCb &) override final;
  void RegisterServerSessionWriteHookCb(
      const tfOnHookServerSessionWriteCb &) override final;
  void RegisterServerWelcomeSendHookCb(
      const tfOnHookServerWelcomeSendCb &) override final;
  void RegisterServerMessageCb(const tfOnServerMessageCb &) override final;
  void
  RegisterServertfKeepAliveCb(const tfOnServerKeepAliveCb &) override final;
  void RegisterServerMessageReceiveReplyCb(
      const tfOnServerMessageReceiveReply &) override final;

  void RegisterClientWelcomeCb(const tfOnClientWelcomeCb &) override final;
  void
  RegisterClientForceCloseCb(const tfOnClientForceCloseCb &) override final;
  void RegisterClientErrorCb(const tfOnClientErrorCb &) override final;
  void RegisterClientMessageCb(const tfOnClientMessageCb &) override final;
  void RegisterClientMessageReceiveReplyCb(
      const tfOnClientMessageReceiveReply &) override final;
  void RegisterClientExit(const tfOnClientExitCb &) override final;
  void
  RegisterClientDisconnection(const tfOnClientDisconnection &) override final;
  void RegisterClientConnection(const tfOnClientConnection &) override final;
  void RegisterClientSessionWriteHookCb(
      const tfOnHookClientSessionWriteCb &) override final;

public:
  void OnServerReady(void) const;
  void OnServerExitBefore(const ISession *) const;
  void OnServerExit(void) const;
  void OnServerError(const ISession *, const SystemErrorno &,
                     const IBuffer *) const;
  void OnServerHello(ISession *, const IBuffer *, IBuffer *) const;
  void OnServerSessionReady(ISession *) const;
  void OnServerSessionCreate(const ISession *) const;
  void OnServerSessionDestroy(const ISession *) const;
  void OnServerSessionTimeout(const ISession *, const std::time_t &) const;
  void OnServerSessionAccept(const ISession *, const bool &) const;
  void OnClientWelcome(const IBuffer *, IBuffer *) const;
  void OnHookServerWelcomeSend(const ISession *, IBuffer *) const;
  void OnHookServerSessionWrite(const ISession *, IBuffer *) const;
  void OnServerMessage(ISession *, const CommandType &, const IBuffer *) const;
  void OnServertfKeepAlive(const ISession *, const IBuffer *, IBuffer *) const;
  void OnServerMessageReceiveReply(const ISession *, const CommandType &,
                                   const IBuffer *, CommandType &,
                                   IBuffer *) const;
  void OnClientForceClose(const ISession *) const;
  void OnClientError(const ISession *, const SystemErrorno &,
                     const IBuffer *) const;
  void OnClientMessageCb(const ISession *, const CommandType &,
                         const IBuffer *) const;
  void OnClientMessageReceiveReplyCb(const ISession *, const CommandType &,
                                     const IBuffer *, CommandType *,
                                     IBuffer *) const;
  void OnClientExit() const;
  void OnClientDisconnection(const ISession *) const;
  void OnClientConnection(const ISession *, CommandType *, IBuffer *) const;
  void OnClientSessionWriteHookCb(const ISession *, IBuffer *) const;

private:
  tfOnClientMessageCb client_message_cb_ = nullptr;
  tfOnClientMessageReceiveReply client_message_receive_reply_cb_ = nullptr;
  tfOnClientForceCloseCb client_force_close_cb_ = nullptr;
  tfOnServerReadyCb server_ready_cb_ = nullptr;
  tfOnServerExitCb server_exit_cb_ = nullptr;
  tfOnServerExitBefore server_exit_before_cb_ = nullptr;
  tfOnServerErrorCb server_error_cb_ = nullptr;
  tfOnServerHelloCb server_hello_cb_ = nullptr;
  tfOnClientWelcomeCb client_welcome_cb_ = nullptr;
  tfOnServerSessionAcceptCb server_session_accept_cb_ = nullptr;
  tfOnServerSessionReadyCb server_session_ready_cb_ = nullptr;
  tfOnServerSessionCreateCb server_session_create_cb_ = nullptr;
  tfOnServerSessionDestroyCb server_session_destroy_cb_ = nullptr;
  tfOnServerSessionTimeoutCb server_session_timeout_cb_ = nullptr;
  tfOnHookServerWelcomeSendCb server_welcome_send_hook_cb_ = nullptr;
  tfOnHookServerSessionWriteCb server_session_write_hook_cb_ = nullptr;
  tfOnServerMessageCb server_message_cb_ = nullptr;
  tfOnServerKeepAliveCb server_keep_alive_cb_ = nullptr;
  tfOnServerMessageReceiveReply server_message_receive_reply_cb_ = nullptr;
  tfOnClientErrorCb client_error_cb_ = nullptr;
  tfOnClientExitCb client_exit_cb_ = nullptr;
  tfOnClientConnection client_connection_cb_ = nullptr;
  tfOnClientDisconnection client_disconnection_cb_ = nullptr;
  tfOnHookClientSessionWriteCb client_session_write_hook_cb_ = nullptr;

private:
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};

#include "buffer.h"
#include "protocol.h"
#include "stream.h"
#include "session.h"
#include "config.h"
#include "client.h"
#include "server.h"
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 20 May 2023 01:20:31 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__DF04609E_A0A4_4236_8390_A763A9F4678B__