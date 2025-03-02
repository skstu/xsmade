#if !defined(__A3A521A0_3093_4E00_A03D_9CEB29CFC6B5__)
#define __A3A521A0_3093_4E00_A03D_9CEB29CFC6B5__
#if 0

class ICallback {
protected:
	tfOnKeepAliveCb m_OnKeepAliveCb = nullptr;
	tfOnHookKeepAliveSendCb m_OnHookKeepAliveSendCb = nullptr;
	tfOnHelloCb m_OnHelloCb = nullptr;
	tfOnWelcomeCb m_OnWelcomeCb = nullptr;
	tfOnAcceptCb m_OnAcceptCb = nullptr;
	tfOnMessageCb m_OnMessageCb = nullptr;
	tfOnSystemExitCb m_OnSystemExitCb = nullptr;
	tfOnHookWriteCb m_OnHookWriteCb = nullptr;
	tfOnForceCloseCb m_OnForceCloseCb = nullptr;
	tfOnConnectionCb m_OnConnectionCb = nullptr;
	tfOnServerReadyCb m_OnServerReadyCb = nullptr;
	tfOnReceiveReplyCb m_OnReceiveReplyCb = nullptr;
	tfOnDisconnectionCb m_OnDisconnectionCb = nullptr;
	tfOnServerKeepAliveCb m_OnServerKeepAliveCb = nullptr;
	tfOnHookSystemExitCb m_OnHookSystemExitCb = nullptr;
	tfOnSystemMessageCb m_OnSystemMessageCb = nullptr;
	tfOnHookConnectionCb m_OnHookConnectionCb = nullptr;
	tfOnHookServerAddressCb m_OnHookServerAddressCb = nullptr;
	tfOnHookWelcomeSendCb m_OnHookWelcomeSendCb = nullptr;
	tfOnServerSessionReadyCb m_OnServerSessionReadyCb = nullptr;
	tfOnServerSessionTimeoutCb m_OnServerSessionTimeoutCb = nullptr;
	tfOnHookSessionCreateCb m_OnHookSessionCreateCb = nullptr;
	tfOnHookSessionDestoryCb m_OnHookSessionDestoryCb = nullptr;
public:
	virtual void RegisterOnKeepAliveCb(const tfOnKeepAliveCb& cb) { m_OnKeepAliveCb = cb; }
	virtual void RegisterOnHookKeepAliveSendCb(const tfOnHookKeepAliveSendCb& cb) { m_OnHookKeepAliveSendCb = cb; }
	virtual void RegisterOnServerSessionReadyCb(const tfOnServerSessionReadyCb& cb) { m_OnServerSessionReadyCb = cb; }
	virtual void RegisterOnHookWelcomeSendCb(const tfOnHookWelcomeSendCb& cb) { m_OnHookWelcomeSendCb = cb; }
	virtual void RegisterOnHelloCb(const tfOnHelloCb& cb) { m_OnHelloCb = cb; }
	virtual void RegisterOnWelcomeCb(const tfOnWelcomeCb& cb) { m_OnWelcomeCb = cb; }
	virtual void RegisterOnServerKeepAliveCb(const tfOnServerKeepAliveCb& cb) { m_OnServerKeepAliveCb = cb; }
	virtual void RegisterOnServerSessionTimeoutCb(const tfOnServerSessionTimeoutCb& cb) { m_OnServerSessionTimeoutCb = cb; }
	virtual void RegisterOnServerReadyCb(const tfOnServerReadyCb& cb) { m_OnServerReadyCb = cb; }
	virtual void RegisterOnSystemExitCb(const tfOnSystemExitCb& cb) { m_OnSystemExitCb = cb; }
	virtual void RegisterOnHookSystemExitCb(const tfOnHookSystemExitCb& cb) { m_OnHookSystemExitCb = cb; }
	virtual void RegisterOnForceClose(const tfOnForceCloseCb& cb) { m_OnForceCloseCb = cb; }
	virtual void RegisterOnAcceptCb(const tfOnAcceptCb& cb) { m_OnAcceptCb = cb; }
	virtual void RegisterOnMessageCb(const tfOnMessageCb& cb) { m_OnMessageCb = cb; }
	virtual void RegisterOnConnectionCb(const tfOnConnectionCb& cb) { m_OnConnectionCb = cb; }
	virtual void RegisterOnDisconnectionCb(const tfOnDisconnectionCb& cb) { m_OnDisconnectionCb = cb; }
	virtual void RegisterOnSystemMessageCb(const tfOnSystemMessageCb& cb) { m_OnSystemMessageCb = cb; }
	virtual void RegisterOnReceiveReplyCb(const tfOnReceiveReplyCb& cb) { m_OnReceiveReplyCb = cb; }
	virtual void RegisterOnHookWriteCb(const tfOnHookWriteCb& cb) { m_OnHookWriteCb = cb; }
	virtual void RegisterOnHookSessionCreateCb(const tfOnHookSessionCreateCb& cb) { m_OnHookSessionCreateCb = cb; }
	virtual void RegisterOnHookSessionDestoryCb(const tfOnHookSessionDestoryCb& cb) { m_OnHookSessionDestoryCb = cb; }
	virtual void RegisterOnHookConnectionCb(const tfOnHookConnectionCb& cb) { m_OnHookConnectionCb = cb; }
	virtual void RegisterOnHookServerAddressCb(const tfOnHookServerAddressCb& cb) { m_OnHookServerAddressCb = cb; }
protected:
	virtual void OnKeepAlive(const ISession* session, const std::string& message, const tfOnAllcoStringCb& message_reply_cb) const {
		if (m_OnKeepAliveCb) {
			m_OnKeepAliveCb(session, message, message_reply_cb);
		}
	}
	virtual void OnHookKeepAliveSend(const ISession* session, const tfOnAllcoStringCb& message_reply_cb) const {
		if (m_OnHookKeepAliveSendCb) {
			m_OnHookKeepAliveSendCb(session, message_reply_cb);
		}
	}
	virtual void OnServerSessionReady(const ISession* session) const {
		if (m_OnServerSessionReadyCb) {
			m_OnServerSessionReadyCb(session);
		}
	}
	virtual void OnHookWelcomeSend(const ISession* session, const tfOnAllcoStringCb& message_cb) const {
		if (m_OnHookWelcomeSendCb) {
			m_OnHookWelcomeSendCb(session, message_cb);
		}
	}
	virtual void OnHello(ISession* session, const std::string& message_receive, const tfOnAllcoStringCb& message_reply_cb) const {
		if (m_OnHelloCb) {
			m_OnHelloCb(session, message_receive, message_reply_cb);
		}
	}
	virtual void OnWelcome(ISession* session, const std::string& message_receive, const tfOnAllcoStringCb& message_reply_cb) const {
		if (m_OnWelcomeCb) {
			m_OnWelcomeCb(session, message_receive, message_reply_cb);
		}
	}
	virtual void OnServerKeepAlive(const ISession* session, const std::string& message) const {
		if (m_OnServerKeepAliveCb) {
			m_OnServerKeepAliveCb(session, message);
		}
	}
	virtual void OnServerSessionTimeout(const ISession* session, const std::time_t& timeout_ms) const {
		if (m_OnServerSessionTimeoutCb) {
			m_OnServerSessionTimeoutCb(session, timeout_ms);
		}
	}
	virtual void OnServerReady() const {
		if (m_OnServerReadyCb) {
			m_OnServerReadyCb();
		}
	}
	virtual void OnHookServerAddress(std::string& address) const {
		if (m_OnHookServerAddressCb) {
			m_OnHookServerAddressCb(address);
		}
	}
	virtual void OnHookConnection(std::string& address) const {
		if (m_OnHookConnectionCb) {
			m_OnHookConnectionCb(address);
		}
	}
	virtual void OnSystemExit() const {
		if (m_OnSystemExitCb) {
			m_OnSystemExitCb();
		}
	}
	virtual void OnHookSystemExit(bool& action) const {
		if (m_OnHookSystemExitCb) {
			m_OnHookSystemExitCb(action);
		}
	}
	virtual void OnAccept(const ISession* session, const bool& success) const {
		if (m_OnAcceptCb) { m_OnAcceptCb(session, success); }
	}
	virtual void OnForceClose(const ISession* session) const {
		if (m_OnForceCloseCb) { m_OnForceCloseCb(session); }
	}
	virtual void OnConnection(const ISession* session) const {
		if (m_OnConnectionCb) { m_OnConnectionCb(session); }
	}
	virtual void OnDisconnection(const ISession* session) const {
		if (m_OnDisconnectionCb) { m_OnDisconnectionCb(session); }
	}
	virtual void OnHookSessionCreate(ISession* session) const {
		if (m_OnHookSessionCreateCb) { m_OnHookSessionCreateCb(session); }
	}
	virtual void OnHookSessionDestory(ISession* session) const {
		if (m_OnHookSessionDestoryCb) { m_OnHookSessionDestoryCb(session); }
	}
	virtual void OnMessage(const ISession* session, const CommandType& cmd, const std::string& message) const {
		if (m_OnMessageCb) { m_OnMessageCb(session, cmd, message); }
	}
	virtual void OnSystemMessage(const ISession* session, const SystemErrorno& status, const std::string& message) const {
		if (m_OnSystemMessageCb) { m_OnSystemMessageCb(session, status, message); }
	}
	virtual void OnReceiveReply(const ISession* session,
		const CommandType& cmd_receive, const std::string& message_receive, CommandType& cmd_reply,
		const tfOnAllcoStringCb& message_reply_cb) const {
		if (m_OnReceiveReplyCb) {
			m_OnReceiveReplyCb(session, cmd_receive, message_receive, cmd_reply, message_reply_cb);
		}
	}
	virtual void OnHookWrite(const ISession* session, std::string& message) const {
		if (m_OnHookWriteCb) {
			m_OnHookWriteCb(session, message);
		}
	}
};

template<typename T = std::string>
static void T_MESSAGE_REPLY(const T& message, const ICallback::tfOnAllcoStringCb& res_cb) {
	const char* route = message.data();
	size_t route_size = message.size();
	res_cb(&route, &route_size);
}

#endif

class Stream final {
private:
	std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
public:
	Stream(const size_t& buffer_size, const StreamType&);
	~Stream();
public:
	bool operator<<(const std::string&);
	bool operator>>(std::string&);
	void Resize(const size_t& buffer_size);
	void Reset();
	char* Base() const;
	const size_t& BufferSize() const;
	bool Empty() const;
private:
	size_t m_BufferSize;
	char* m_LevelCache1 = nullptr;
	std::string m_LevelCache2;
	const StreamType m_StreamType;
	std::queue<std::string> m_LevelCache3;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 22 Apr 2023 04:20:41 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__A3A521A0_3093_4E00_A03D_9CEB29CFC6B5__