#include "config.h"
void uv__read_cb(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf);
void uv__udp_alloc_cb(uv_handle_t *handle, size_t suggested_size,
                      uv_buf_t *buf);
void uv__udp_recv_cb(uv_udp_t *handle, ssize_t nread, const uv_buf_t *buf,
                     const struct sockaddr *addr, unsigned flags);
///////////////////////////////////////////////////////////////////////////////////////////////////////////
Client::Client() {
  // LOG_INIT;
  Init();
}
Client::~Client() {
  UnInit();
  // LOG_UNINIT;
}
bool Client::Ready() const {
  return ready_.load();
}
void Client::Release() const {
  delete this;
}
void Client::Init() {
}
void Client::UnInit() {
}
size_t Client::SessionCount() const {
  std::lock_guard<std::mutex> lock{*m_Mutex};
  return 1;
}
bool Client::IsClose() const {
  std::lock_guard<std::mutex> lock{*m_Mutex};
  return !open_.load();
}
bool Client::Start() {
  do {
    if (open_.load())
      break;
    /*if (m_pConfig->EnableClientWaitForTheInitialConnectionAndReceiveResult())
            m_hFirstLogicalEvent = ::CreateEventW(NULL, TRUE, FALSE, NULL);*/

    open_.store(true);
    if (0 != uv_thread_create(&thread_main_, MainProcess, this)) {
      open_.store(false);
      break;
    }

    if (!open_.load())
      break;

    /*if (m_hFirstLogicalEvent)
            ::WaitForSingleObject(m_hFirstLogicalEvent, INFINITE);*/

  } while (0);
  return open_.load();
}
void Client::Stop() {
  do {
    if (!open_.load())
      break;
    /*if (m_hFirstLogicalEvent) {
            ::SetEvent(m_hFirstLogicalEvent);
            ::WaitForSingleObject(m_hFirstLogicalEvent, INFINITE);
    }
    SK_CLOSE_HANDLE(m_hFirstLogicalEvent);*/
    open_.store(false);
    uv_thread_join(&thread_main_);
  } while (0);
}
bool Client::Write(const unsigned long &cmd, const IBuffer *buffer) {
  bool result = false;
  do {
    if (!buffer)
      break;
    result = Write(cmd, buffer->GetData(), buffer->GetDataSize());
    // SK_RELEASE_PTR(buffer);
  } while (0);
  return result;
}
bool Client::Write(const unsigned long &cmd, const char *data, size_t len) {
  bool result = false;
  std::lock_guard<std::mutex> lock{*m_Mutex};
  do {
    if (!data || len <= 0)
      break;
    std::string local(data, len);
    m_WriteBufferQ.push(CommandType(cmd), local);
    result = true;
  } while (0);
  return result;
}
/*void Client::NotifyFirstLogicalEvent() {
        std::lock_guard<std::mutex> lock{*m_Mutex};
        if (m_hFirstLogicalEvent && !m_FirstLogicalEventTriggerFlag.load()) {
                ::SetEvent(m_hFirstLogicalEvent);
                m_FirstLogicalEventTriggerFlag.store(true);
        }
}*/
ServerStatus Client::Status() const {
  return m_ServerStatus;
}
ServerType Client::ServerTypeGet() const {
  std::lock_guard<std::mutex> lock{*m_Mutex};
  return Protocol::GetServerType(Config::Get()->GetServiceType());
  ;
}
SessionType Client::SessionTypeGet() const {
  std::lock_guard<std::mutex> lock{*m_Mutex};
  return Protocol::GetSessionType(Config::Get()->GetServiceType());
}
AddressType Client::AddressTypeGet() const {
  std::lock_guard<std::mutex> lock{*m_Mutex};
  return Protocol::GetAddressType(Config::Get()->GetServiceType());
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
static void uv_main_uninit(void *arg, uv_loop_t *&loop, uv_handle_t *&client,
                           uv_handle_t *&connect) {
  do {
    if (!arg || !loop || !client)
      break;
    uv_close(client, Protocol::uv_close_cb);
    uv_walk(loop, Protocol::walk_close_handle_cb, arg);
    uv_run(loop, uv_run_mode::UV_RUN_DEFAULT);
    uv_loop_close(loop);
  } while (0);

  client = nullptr;

  SK_DELETE_PTR(connect);

  if (loop) {
    auto udata = USERDATA_PTR(loop);
    SK_DELETE_PTR(udata);
    SK_DELETE_PTR(loop);
  }
}
static void uv_main_init(void *arg, uv_loop_t *&loop, uv_handle_t *&client,
                         uv_handle_t *&connect) {
  auto pClient = reinterpret_cast<Client *>(arg);
  do {
    loop = new uv_loop_t;
    loop->data = new UserData;
    if (0 != uv_loop_init(loop))
      break;

    switch (pClient->SessionTypeGet()) {
    case SessionType::TCP: {
      client = reinterpret_cast<uv_handle_t *>(new uv_tcp_t);
      connect = reinterpret_cast<uv_handle_t *>(new uv_connect_t);
      if (0 != uv_tcp_init(loop, reinterpret_cast<uv_tcp_t *>(client)))
        break;

    } break;
    case SessionType::IPC: {
      client = reinterpret_cast<uv_handle_t *>(new uv_pipe_t);
      connect = reinterpret_cast<uv_handle_t *>(new uv_connect_t);
      if (0 != uv_pipe_init(loop, reinterpret_cast<uv_pipe_t *>(client), 1))
        break;

    } break;
    case SessionType::UDP: {
      client = reinterpret_cast<uv_handle_t *>(new uv_udp_t);
      if (0 != uv_udp_init(loop, reinterpret_cast<uv_udp_t *>(client)))
        break;

    } break;
    default:
      break;
    }

    Session *newSessing = new Session();
    newSessing->SetIdentify(Config::Get()->GetIdentify());
    newSessing->ServerTypeSet(ServerType::INITIATOR);
    client->data = newSessing;
    if (connect)
      connect->data = client->data;
    USERDATA_PTR(loop)->Caller(arg);
    USERDATA_PTR(client)->Caller(arg);
    USERDATA_PTR(client)->Handle(client);
  } while (0);
}
void Client::MainProcess(void *arg) {
  Client *pClient = reinterpret_cast<Client *>(arg);
  uv_loop_t *loop = nullptr;
  uv_handle_t *client = nullptr;
  uv_handle_t *connect = nullptr;
  unsigned long long prev_time_ms_reconn = 0;
  unsigned long long prev_time_ms_keepalive = 0;
  SessionStatus status = SessionStatus::UNKNOWN;
  do {
    if (client)
      status = USERDATA_PTR(client)->Status();

    const unsigned long long time_current_ms =
        stl::Time::TimeStampUTC<std::chrono::milliseconds>();
    const unsigned long long time_reconnection_interval =
        time_current_ms - prev_time_ms_reconn;

    do {
      if (time_reconnection_interval <
          Config::Get()->ClientReconnectionIntervalMS())
        break;
      prev_time_ms_reconn = time_current_ms;

      switch (status) {
      case SessionStatus::UNKNOWN:
        [[fallthrough]];
      case SessionStatus::DISCONNECTED: {
        prev_time_ms_keepalive = 0;
        if (!loop || !client || !connect) {
          uv_main_init(arg, loop, client, connect);
        }
        std::string connection_address = Config::Get()->Address();

        Connect(Config::Get()->Address(), connect, client);
        LOG_OUTPUT("Preparing to connect to the service ({}).",
                   Config::Get()->Address());
      } break;
      case SessionStatus::FORCECLOSE: {
        prev_time_ms_keepalive = 0;
        Config::Get()->OnClientForceClose(client ? SESSION_PTR(client)
                                                 : nullptr);
        LOG_OUTPUT("Disconnect from the service ({}).",
                   Config::Get()->Address());
        uv_main_uninit(arg, loop, client, connect);
        uv_main_init(arg, loop, client, connect);
      } break;
      default:
        break;
      }

    } while (0);

    if (status == SessionStatus::CONNECTED && client) {
      auto pSession = SESSION_PTR(client);

      do {
        if (pClient->m_WriteBufferQ.empty())
          break;
        pClient->m_WriteBufferQ.iterate_clear(
            [&](const auto &cmd, auto &data, bool &, bool &itclear) {
              pSession->Write(static_cast<unsigned long>(cmd), data.data(),
                              data.size());
              itclear = true;
            });
      } while (0);

      do { //!@ keepalive
        if (prev_time_ms_keepalive <= 0) {
          prev_time_ms_keepalive = time_current_ms;
          break;
        }
        if (time_current_ms - prev_time_ms_keepalive <
            Config::Get()->KeepAliveTimeMS())
          break;
        prev_time_ms_keepalive = time_current_ms;
        if (!pSession)
          break;

        const std::string keepalive_send_data = R"(#---!)";
        if (!pSession->Write(static_cast<unsigned long>(CommandType::KEEPALIVE),
                             keepalive_send_data.data(),
                             keepalive_send_data.size()))
          pSession->ForceClose();
      } while (0);

      do { //!@ write
        write_req_t *req = pSession->Write([&](std::string &message) {
          Buffer buf(message);
          Config::Get()->OnClientSessionWriteHookCb(
              pSession, dynamic_cast<IBuffer *>(&buf));
          message = buf.GetString();
        });
        if (!req)
          break;
        req->handle = client;
        if (0 != uv_write(&req->write,
                          reinterpret_cast<uv_stream_t *>(req->handle),
                          &req->buf, 1, Protocol::uv_write_cb)) {
          Buffer buf(req->buf.base, req->buf.len);
          Config::Get()->OnClientError(pSession, SystemErrorno::E_STREAM_SEND,
                                       dynamic_cast<IBuffer *>(&buf));
          SK_DELETE_PTR(req);
          pSession->ForceClose();
          break;
        }

        prev_time_ms_keepalive = time_current_ms;
      } while (0);

      do { // read
        std::string read_data = pSession->Read();
        if (read_data.empty())
          break;
        HEAD head;
        std::string message;
        if (!Protocol::UnMakeStream(read_data, head, message)) {
          Buffer buf(read_data);
          Config::Get()->OnClientError(pSession, SystemErrorno::E_STREAM_RECV,
                                       dynamic_cast<IBuffer *>(&buf));
          pSession->ForceClose();
          break;
        }
        Buffer msg(message);
        Config::Get()->OnClientMessageCb(pSession, head.Command(),
                                         dynamic_cast<IBuffer *>(&msg));
        {
          CommandType cmdReply = CommandType::UNKNOWN;
          Buffer *messageReply = new Buffer();
          Config::Get()->OnClientMessageReceiveReplyCb(
              pSession, head.Command(), dynamic_cast<IBuffer *>(&msg),
              &cmdReply, dynamic_cast<IBuffer *>(messageReply));
          if (CommandType::UNKNOWN != cmdReply) {
            if (!pSession->Write(static_cast<unsigned long>(cmdReply),
                                 messageReply))
              pSession->ForceClose();
          } else {
            messageReply->Release();
          }
        }

        // LOG_OUTPUT(std::format("recv message({:X}:{})", static_cast<unsigned
        // long>(head.Command()), message));
        switch (head.Command()) {
        case CommandType::WELCOME: {
          Buffer buffer(message);
          Buffer *replyWelcome = new Buffer();
          Config::Get()->OnClientWelcome(dynamic_cast<IBuffer *>(&buffer),
                                         dynamic_cast<IBuffer *>(replyWelcome));
          if (!replyWelcome->Empty()) {
            if (!pSession->Write(static_cast<unsigned long>(CommandType::HELLO),
                                 replyWelcome->GetData(),
                                 replyWelcome->GetDataSize())) {
              pSession->ForceClose();
            }

          } else {
            replyWelcome->Release();
          }
        } break;
        default:
          break;
        }
        //!@ 等待第一次接收处理完成
        /*pClient->NotifyFirstLogicalEvent();*/
      } while (0);
    }

    if (loop) {
      uv_run(loop, uv_run_mode::UV_RUN_NOWAIT);
    }
    if (pClient->IsClose()) {
      bool is_close = pClient->IsClose();
      if (is_close)
        break;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  } while (1);
  uv_main_uninit(arg, loop, client, connect);
  Config::Get()->OnClientExit();
}
bool Client::Connect(const std::string &address, uv_handle_t *connect,
                     uv_handle_t *client) {
  bool result = false;
  Client *pClient = nullptr;
  Session *pSession = nullptr;
  do {
    if (address.empty() || !connect || !client)
      break;
    if (uv_is_closing(client))
      break;
    pSession = SESSION_PTR(client);
    if (!pSession)
      break;
    pClient = reinterpret_cast<Client *>(pSession->Caller());
    if (!pClient)
      break;
    if (pSession->Status() == SessionStatus::CONNECTING)
      break;
    pSession->Status(SessionStatus::CONNECTING);

    switch (pClient->SessionTypeGet()) {
    case SessionType::TCP: {
      std::string sockaddr_buffer;
      if (!Protocol::MakeIPAddr(Config::Get()->Address(), sockaddr_buffer,
                                pClient->AddressTypeGet()))
        break;
      if (0 != uv_tcp_connect(reinterpret_cast<uv_connect_t *>(connect),
                              reinterpret_cast<uv_tcp_t *>(client),
                              (const struct sockaddr *)sockaddr_buffer.data(),
                              Client::ConnectCb))
        break;
      result = true;
    } break;
    case SessionType::IPC: {
      uv_pipe_connect(reinterpret_cast<uv_connect_t *>(connect),
                      reinterpret_cast<uv_pipe_t *>(client),
                      Config::Get()->Address(), Client::ConnectCb);
      result = true;
    } break;
    case SessionType::UDP: {
      std::string sockaddr_buffer;
      if (!Protocol::MakeIPAddr(Config::Get()->Address(), sockaddr_buffer,
                                pClient->AddressTypeGet()))
        break;
      pSession->SockAddr(*reinterpret_cast<sockaddr *>(sockaddr_buffer.data()));
      if (0 !=
          uv_udp_connect(reinterpret_cast<uv_udp_t *>(client),
                         reinterpret_cast<sockaddr *>(sockaddr_buffer.data())))
        break;
      if (0 != uv_udp_recv_start(reinterpret_cast<uv_udp_t *>(client),
                                 uv__udp_alloc_cb, uv__udp_recv_cb))
        break;
      result = true;
    } break;
    default:
      break;
    }

    if (!result)
      break;
    result = false;

    {}

    result = true;
  } while (0);
  if (!result && pSession)
    pSession->ForceClose();
  return result;
}

void Client::ConnectCb(uv_connect_t *req, int status) {
  bool success = false;
  Session *pSession = nullptr;
  Client *pClient = nullptr;
  do {
    pSession = SESSION_PTR(req);
    if (!pSession)
      break;
    pClient = reinterpret_cast<Client *>(pSession->Caller());
    if (!pClient)
      break;
    if (status < 0) {
      Config::Get()->OnClientDisconnection(pSession);
      /*pClient->NotifyFirstLogicalEvent();*/
      break;
    }
    if (0 != uv_read_start(reinterpret_cast<uv_stream_t *>(pSession->Handle()),
                           Protocol::uv_alloc_cb, uv__read_cb))
      break;
    pSession->Status(SessionStatus::CONNECTED);
    CommandType reqCmd = CommandType::UNKNOWN;
    Buffer *reqMsg = new Buffer();
    Config::Get()->OnClientConnection(pSession, &reqCmd, reqMsg);
    pSession->Write(static_cast<unsigned long>(reqCmd), reqMsg);
    LOG_OUTPUT("Connect to the service({}) complete.",
               Config::Get()->Address());
    success = true;
  } while (0);
  if (!success && pSession)
    pSession->ForceClose();
}

void uv__read_cb(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf) {
  if (!stream)
    return;
  bool force_close = false;
  Session *pSession = USERDATA_PTR(stream);
  if (buf->base) {
    if (nread > 0) {
      if (!pSession->Read(buf->base, nread))
        force_close = true;
    } else if (nread < 0) {
      force_close = true;
    }
  } else {
    force_close = true;
  }
  if (force_close)
    pSession->ForceClose();
}

void uv__udp_alloc_cb(uv_handle_t *handle, size_t suggested_size,
                      uv_buf_t *buf) {

  auto sk = 0;
}
void uv__udp_recv_cb(uv_udp_t *handle, ssize_t nread, const uv_buf_t *buf,
                     const struct sockaddr *addr, unsigned flags) {

  auto sk = 0;
}
////////////////////////////////////////////////////////////////////////////////////
static Client *__gpClient = nullptr;
Client *Client::Create() {
  if (!__gpClient)
    __gpClient = new Client();
  return __gpClient;
}
void Client::Destroy() {
  if (__gpClient)
    __gpClient->Stop();
  SK_DELETE_PTR(__gpClient);
}