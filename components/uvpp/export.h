#if !defined(__EDFDD880_A47B_4806_8F76_D2771575F3D7__)
#define __EDFDD880_A47B_4806_8F76_D2771575F3D7__

#include "component.h"

namespace uvpp {

using TypeIdentify = unsigned long long;
using TypeStreamType = unsigned char;
using TypeZipType = unsigned char;
using TypeSessionStatus = unsigned char;
using TypeCommandType = unsigned long;
using TypeEncryptType = unsigned char;
using TypeErrnoType = long;

enum class ServerType : unsigned long {
  UNKNOWN = 0x00000000,
  INITIATOR = 0x00100000,
  ACCEPTOR = 0x00200000,

  MAX = 0x00FF0000,
  MIN = 0x00000000,
};

enum class SessionType : unsigned short {
  UNKNOWN = 0x0000,
  TCP = 0x0100,
  UDP = 0x0200,
  IPC = 0x0300,
  HTTP = 0x0400,

  MAX = 0xFF00,
  MIN = 0x0000,
};
enum class AddressType : unsigned char {
  UNKNOWN = 0x00,
  IPV4 = 0x01,
  IPV6 = 0x02,
  IPC = 0x03,

  BEGIN = IPV4,
  END = IPC,
  MAX = 0xFF,
  MIN = 0x00,
};

// Enum for different connection status types with integer values
typedef enum class SessionStatus : TypeSessionStatus {
  UNKNOWN = 0x0,

  UNREADY = UNKNOWN, //!@ opening or initialize failed.

  INPREPARATION = 0x1,
  READY = 0x2, //!@ Connection is ready

  FORCECLOSE = 0x3, //!@ Close command has been initiated

  CLOSING = 0x4, //!@ Connection is being closed
  STOPPING = CLOSING,
  CLOSED = 0x5, //!@ Connection is closed and not opened yet
  STOPPED = CLOSED,
  DISCONNECTED = CLOSED, //!@ Connection is completed with failure

  OPENING = 0x6,        //!@ Connection is being opened
  CONNECTING = OPENING, //!@ Connection is being established
  STARTING = OPENING,
  OPENED = 0x7, //!@ Connection is opened successfully
  STARTED = OPENED,
  CONNECTED = OPENED, //!@ Connection is completed successfully
  ACTIVATE = OPENED,

  BEGIN = UNKNOWN,
  END = ACTIVATE,
} ServerStatus;

enum class StreamType : TypeStreamType {
  UNKNOWN = 0x0,
  READ = 0x1,
  WRITE = 0x2,
};

enum class ZipType : TypeZipType {
  UNKNOWN = 0x0,
  ZIP = 0x1,
  GZIP = 0x2,
};

enum class EncryptType : TypeEncryptType {
  UNKNOWN = 0x0,
  WEMADE = 0x1,
};

enum class CommandType : TypeCommandType {
  UNKNOWN = 0x00000,
  WELCOME = 0x10000,
  HELLO = WELCOME,
  HEARTBEAT = 0x10100,
  KEEPALIVE = HEARTBEAT,
  TESTMSG = 0x10200,
};

enum class SystemErrorno : TypeErrnoType {
  E_UNKNOWN = -0xFFFF,
  E_STREAM_PARSING = E_UNKNOWN + 1,
  E_STREAM_RECV = E_STREAM_PARSING,
  E_READ = E_STREAM_PARSING,
  E_STREAM_SEND = E_UNKNOWN + 2,
  E_WRITE = E_STREAM_SEND,
  E_SYSTEM_CORE_INIT = E_UNKNOWN + 3,
  E_SERVER_SESSION_INIT = E_UNKNOWN + 4,
};

struct IPacketHeader {
  virtual ZipType Zip() const = 0;
  virtual EncryptType Encrypt() const = 0;
  virtual CommandType Command() const = 0;
  virtual bool Verify() const = 0;
  virtual unsigned long DataSize() const = 0;
  virtual unsigned long OriginalSize() const = 0;
  virtual unsigned long PacketSize() const = 0;
};

class IBuffer {
public:
  virtual IBuffer *Clone() const = 0;
  virtual const char *GetData() const = 0;
  virtual size_t GetDataSize() const = 0;
  virtual void SetData(const char *, const size_t &) = 0;
  virtual void Release() const = 0;
  virtual bool Empty() const = 0;
};

class ISession {
public:
  virtual void Route(void *) = 0;
  virtual void *Route() const = 0;
  virtual bool Read(const char *, const size_t &) = 0;
  virtual bool Write(const unsigned long &, const IBuffer *) = 0;
  virtual bool Write(const unsigned long &, const char *, const size_t &) = 0;
  virtual const SessionStatus &Status() const = 0;
  virtual void Address(const char *, const size_t &) = 0;
  virtual void ForceClose() = 0;
  virtual const char *Address() const = 0;
  virtual void ServerTypeSet(const ServerType &) = 0;
  virtual const ServerType &ServerTypeGet() const = 0;
  virtual void SessionTypeSet(const SessionType &) = 0;
  virtual const SessionType &SessionTypeGet() const = 0;
  virtual unsigned long long CreateTimeMS() const = 0;
};

class IService {
public:
  virtual bool Start() = 0;
  virtual void Stop() = 0;
  virtual bool Ready() const = 0;
  virtual void Release() const = 0;
  virtual SessionStatus Status() const {
    return SessionStatus::UNKNOWN;
  }
  virtual bool Write(const unsigned long &, const IBuffer *) {
    return false;
  }
  virtual bool Write(const unsigned long &, const char *, size_t) {
    return false;
  }
  virtual ServerType ServerTypeGet() const {
    return ServerType::UNKNOWN;
  }
  virtual SessionType SessionTypeGet() const {
    return SessionType::UNKNOWN;
  }
  virtual AddressType AddressTypeGet() const {
    return AddressType::UNKNOWN;
  }
  virtual size_t SessionCount() const {
    return 0;
  }
};

class IConfig {
public:
  using tfOnServerErrorCb = void (*)(const ISession *, const SystemErrorno &,
                                     const IBuffer *);
  using tfOnClientErrorCb = tfOnServerErrorCb;
  using tfOnServerExitCb = void (*)(void);
  using tfOnServerExitBefore = void (*)(const ISession *);
  using tfOnClientExitCb = tfOnServerExitCb;
  using tfOnServerReadyCb = void (*)(void);
  using tfOnServerHelloCb = void (*)(const ISession *, const IBuffer *,
                                     IBuffer *);
  using tfOnServerSessionCreateCb = void (*)(const ISession *);
  using tfOnServerSessionDestroyCb = void (*)(const ISession *);
  using tfOnServerSessionReadyCb = void (*)(const ISession *);
  using tfOnServerSessionTimeoutCb = void (*)(const ISession *, const time_t &);
  using tfOnServerSessionAcceptCb = void (*)(const ISession *, const bool &);
  using tfOnHookServerWelcomeSendCb = void (*)(const ISession *, IBuffer *);
  using tfOnHookServerSessionWriteCb = void (*)(const ISession *, IBuffer *);
  using tfOnServerKeepAliveCb = void (*)(const ISession *, const IBuffer *,
                                         IBuffer *);
  using tfOnServerMessageCb = void (*)(const ISession *, const CommandType &,
                                       const IBuffer *);
  using tfOnServerMessageReceiveReply = void (*)(const ISession *,
                                                 const CommandType &,
                                                 const IBuffer *, CommandType &,
                                                 IBuffer *);
  using tfOnClientWelcomeCb = void (*)(const IBuffer * /*welcome*/,
                                       IBuffer * /*hello*/);
  using tfOnClientForceCloseCb = void (*)(const ISession *);
  using tfOnClientMessageCb = void (*)(const ISession *, const CommandType &,
                                       const IBuffer *);
  using tfOnClientMessageReceiveReply = void (*)(const ISession *,
                                                 const CommandType &,
                                                 const IBuffer *, CommandType &,
                                                 IBuffer *);
  using tfOnClientDisconnection = void (*)(const ISession *);
  using tfOnClientConnection = void (*)(const ISession *);
  using tfOnHookClientSessionWriteCb = void (*)(const ISession *, IBuffer *);

public:
  virtual unsigned long Version() const = 0;
  virtual const char *VersionString() const = 0;
  /*
   * ipv4: 0.0.0.0:8888
   * ipv6: [0:0:0:0:0:0:0:0]:8888
   * windows pipe: \\.\pipe\ipc_server
   */
  virtual void Address(const char *, const size_t &) = 0;
  virtual const char *Address() const = 0;
  virtual void SetServiceType(const unsigned long &) = 0;
  virtual unsigned long GetServiceType() const = 0;
  virtual unsigned long long SessionTimeoutMS() const = 0;
  virtual void SessionTimeoutMS(const unsigned long long &) = 0;
  virtual unsigned long long KeepAliveTimeMS() const = 0;
  virtual void KeepAliveTimeMS(const unsigned long long &) = 0;
  virtual unsigned long long ClientReconnectionIntervalMS() const = 0;
  virtual void ClientReconnectionIntervalMS(const unsigned long long &) = 0;
  //!@ The client enables wait for the initial connection to complete and
  //! receive successfully
  virtual void
  EnableClientWaitForTheInitialConnectionAndReceiveResult(const bool &) = 0;
  virtual bool
  EnableClientWaitForTheInitialConnectionAndReceiveResult() const = 0;

public:
  virtual void RegisterServerReadyCb(const tfOnServerReadyCb &) = 0;
  virtual void RegisterServerExitCb(const tfOnServerExitCb &) = 0;
  virtual void RegisterServerExitBeforeCb(const tfOnServerExitBefore &) = 0;
  virtual void RegisterServerErrorCb(const tfOnServerErrorCb &) = 0;
  virtual void RegisterServerHelloCb(const tfOnServerHelloCb &) = 0;
  virtual void
  RegisterServerSessionCreateCb(const tfOnServerSessionCreateCb &) = 0;
  virtual void
  RegisterServerSessionDestroyCb(const tfOnServerSessionDestroyCb &) = 0;
  virtual void
  RegisterServerSessionAcceptCb(const tfOnServerSessionAcceptCb &) = 0;
  virtual void
  RegisterServerSessionReadyCb(const tfOnServerSessionReadyCb &) = 0;
  virtual void
  RegisterServerSessionTimeoutCb(const tfOnServerSessionTimeoutCb &) = 0;
  virtual void RegisterClientWelcomeCb(const tfOnClientWelcomeCb &) = 0;
  virtual void
  RegisterServerSessionWriteHookCb(const tfOnHookServerSessionWriteCb &) = 0;
  virtual void RegisterServerMessageCb(const tfOnServerMessageCb &) = 0;
  virtual void RegisterServertfKeepAliveCb(const tfOnServerKeepAliveCb &) = 0;
  virtual void RegisterServerMessageReceiveReplyCb(
      const tfOnServerMessageReceiveReply &) = 0;
  virtual void
  RegisterServerWelcomeSendHookCb(const tfOnHookServerWelcomeSendCb &) = 0;
  virtual void RegisterClientForceCloseCb(const tfOnClientForceCloseCb &) = 0;
  virtual void RegisterClientErrorCb(const tfOnClientErrorCb &) = 0;
  virtual void RegisterClientMessageCb(const tfOnClientMessageCb &) = 0;
  virtual void RegisterClientMessageReceiveReplyCb(
      const tfOnClientMessageReceiveReply &) = 0;
  virtual void RegisterClientExit(const tfOnClientExitCb &) = 0;
  virtual void RegisterClientDisconnection(const tfOnClientDisconnection &) = 0;
  virtual void RegisterClientConnection(const tfOnClientConnection &) = 0;
  virtual void
  RegisterClientSessionWriteHookCb(const tfOnHookClientSessionWriteCb &) = 0;
};

class IUvpp : public IComponent {
public:
  virtual IConfig *ConfigGet() const = 0;
  virtual IService *CreateSevice() const = 0;
  virtual IBuffer *CreateBuffer(const char *, size_t) const = 0;
  virtual bool Start() {
    return false;
  }
  virtual void Stop() {
  }
  virtual bool Ready() const {
    return false;
  }
};
} // namespace uvpp

/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 03 Dec 2024 02:09:20 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__EDFDD880_A47B_4806_8F76_D2771575F3D7__
