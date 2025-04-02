#include "config.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////
ServerType Protocol::GetServerType(const unsigned long &input) {
  return static_cast<ServerType>(static_cast<unsigned long>(ServerType::MAX) &
                                 input);
}
SessionType Protocol::GetSessionType(const unsigned long &input) {
  return static_cast<SessionType>(static_cast<unsigned long>(SessionType::MAX) &
                                  input);
}
AddressType Protocol::GetAddressType(const unsigned long &input) {
  return static_cast<AddressType>(static_cast<unsigned long>(AddressType::MAX) &
                                  input);
}
std::string Protocol::MakeStream(const HEAD &input_head,
                                 const std::string &input_data) {
  std::string result;
  do {
    result.append((char *)&input_head, PACKET_HEAD_SIZE);
    PHEAD pHead = reinterpret_cast<PHEAD>(result.data());
    pHead->zip_type = static_cast<decltype(pHead->zip_type)>(ZipType::UNKNOWN);
    pHead->encryption_type =
        static_cast<decltype(pHead->encryption_type)>(EncryptType::UNKNOWN);
    pHead->data_size = input_data.size();
    pHead->original_size = pHead->data_size;
    do {
      if (pHead->original_size <= PACKET_COMPRESSION_STANDARD_SIZE)
        break;
      std::string zip;
      if (!Zipcc::zipCompress(input_data, zip) || zip.empty())
        break;
      pHead->zip_type = static_cast<decltype(pHead->zip_type)>(ZipType::ZIP);
      pHead->data_size = zip.size();
      result.pop_back();
      result.append(zip);
      break;
    } while (0);
    if (ZipType(pHead->zip_type) != ZipType::UNKNOWN)
      break;
    if (input_data.empty())
      break;
    result.pop_back();
    result.append(input_data);
  } while (0);
  if (!result.empty())
    ((PHEAD)result.data())->packet_size = result.size();
  return result;
}
bool Protocol::UnMakeStream(const std::string &input_data, HEAD &head,
                            std::string &output_data) {
  bool result = false;
  memset((void *)&head, 0x00, PACKET_HEAD_SIZE);
  output_data.clear();
  do {
    PHEAD pHead = (PHEAD)input_data.data();
    if (!pHead->Verify())
      break;
    memcpy((void *)&head, (void *)pHead, PACKET_HEAD_SIZE);
    switch (ZipType(pHead->Zip())) {
    case ZipType::UNKNOWN: {
      if (!pHead->DataSize())
        break;
      output_data.append(pHead->data, pHead->DataSize());
    } break;
    case ZipType::ZIP: {
      Zipcc::zipUnCompress(pHead->data, pHead->OriginalSize(), output_data);
    } break;
    case ZipType::GZIP: {
      Zipcc::gzipUnCompress(pHead->data, output_data);
    } break;
    default:
      break;
    }
    result = true;
  } while (0);
  return result;
}
bool Protocol::MakeIPAddr(
    const std::string &address_string,
    std::string
        &out_addr_buffer /*out sockaddr_in | sockaddr or sockaddr_in6 buffer*/,
    const AddressType &ip_type /*= AF_INET*/ /*AF_INET or AF_INET6*/) {

  bool result = false;
  out_addr_buffer.clear();

  // 如果输入为空，直接返回失败
  if (address_string.empty())
    return false;

  uv_getaddrinfo_t req;
  struct addrinfo hints;
  struct addrinfo *res = nullptr;

  // 设置 hints 以指定 IP 类型
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = (ip_type == AddressType::IPV4) ? AF_INET : AF_INET6;

  int err = uv_getaddrinfo(uv_default_loop(), &req, nullptr,
                           address_string.c_str(), nullptr, &hints);
  if (err < 0) {
    return false;
  }

  // 获取第一个有效的地址信息
  res = req.addrinfo;
  if (res != nullptr) {
    int addr_len = res->ai_addrlen;
    out_addr_buffer.resize(addr_len);
    memcpy(&out_addr_buffer[0], res->ai_addr, addr_len);
    result = true;
  }

  uv_freeaddrinfo(res); // 释放资源
  return result;
}

bool Protocol::UnMakeIPAddr(
    const std::string
        &address_buffer /*in sockaddr_in | sockaddr or sockaddr_in6 buffer*/,
    std::string &out_address_string) {

  bool result = false;
  out_address_string.clear();

  if (address_buffer.empty())
    return false;

  struct sockaddr_in *addr_in = (struct sockaddr_in *)&address_buffer[0];
  char ip_str[INET6_ADDRSTRLEN] = {0};

  // 判断地址类型并转换
  if (address_buffer.size() == sizeof(struct sockaddr_in)) {
    // IPv4 地址
    uv_inet_ntop(AF_INET, &addr_in->sin_addr, ip_str, sizeof(ip_str));
    out_address_string = ip_str;
    result = true;
  } else if (address_buffer.size() == sizeof(struct sockaddr_in6)) {
    // IPv6 地址
    struct sockaddr_in6 *addr_in6 = (struct sockaddr_in6 *)&address_buffer[0];
    uv_inet_ntop(AF_INET6, &addr_in6->sin6_addr, ip_str, sizeof(ip_str));
    out_address_string = ip_str;
    result = true;
  }

  return result;
}

#if 0
bool Protocol::parser_ipaddr(const sockaddr* in_addr, std::string& address, const IPPROTO& ipv) {
	bool result = false;
	address.clear();
	do {
		if (!in_addr)
			break;
		std::string ip;
		u_short port = 0;
		if (!parser_ipaddr((const sockaddr_storage*)in_addr, ip, port, ipv))
			break;
		address = std::format("{}:{}", ip, port);
		result = true;
	} while (0);
	return result;
}
bool Protocol::parser_ipaddr(const sockaddr* in_addr, char* address, const IPPROTO& ipv) {
	bool result = false;
	do {
		if (!in_addr || !address)
			break;
		std::string ip;
		u_short port = 0;
		if (!parser_ipaddr((const sockaddr_storage*)in_addr, ip, port, ipv))
			break;
		sprintf(address, "%s:%d", ip.c_str(), port);
		result = true;
	} while (0);
	return result;
}
bool Protocol::parser_ipaddr(const sockaddr_storage* in_addr, std::string& out_ip, u_short& out_port, const IPPROTO& ipv) {
	bool result = false;
	out_ip.clear();
	out_port = 0;
	if (!in_addr)
		return result;

	//int inet = (IPPROTO::IPPROTO_IPV6 == ipv) ? AF_INET6 : AF_INET;
	char ipv6[64] = { 0 };
	switch (in_addr->ss_family) {
	case AF_INET6: {
		struct sockaddr_in6* addr6 = (struct sockaddr_in6*)in_addr;
		//低版本windows可能找不到inet_ntop函数。
#if _MSC_VER
		DWORD size = sizeof(ipv6);
		::WSAAddressToStringA((LPSOCKADDR)addr6, sizeof(sockaddr_in6), NULL, ipv6, &size);
		out_ip = std::string(ipv6);
		auto index = out_ip.rfind(":");
		if (index >= 0) {
			out_ip.resize(index);
		}
		out_port = ::htons(addr6->sin6_port);
#else
		std::string str(::inet_ntop(inet, (void*)&(addr6->sin6_addr), ipv6, 64));
		out_ip.swap(str);
		out_port = ::htons(addr6->sin6_port);
#endif
		result = true;
	}break;
	case AF_INET: {
		struct sockaddr_in* addr4 = (struct sockaddr_in*)in_addr;
		std::string str(::inet_ntoa(addr4->sin_addr));
		out_ip.swap(str);
		out_port = ::htons(addr4->sin_port);

		result = true;
	}break;
	default:
		result = false;
		break;
	}
	return result;
}
bool Protocol::parser_ipaddr(const std::string& address, std::string& ip, u_short& port) {
	bool result = false;
	do {
		auto check = address.find("/");
		if (check == std::string::npos)
			break;
		std::vector<std::string> parser = shared::Win::StringSpiltA(address, "/");
		if (parser.size() != 2)
			break;
		ip = parser[0];
		port = atoi(parser[1].c_str());
		if (ip.empty() || port <= 0)
			break;
		result = true;
	} while (0);
	return result;
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////
void Protocol::walk_close_handle_cb(uv_handle_t *handle, void *arg) {
  if (!uv_is_closing(handle)) {
    uv_close(handle, Protocol::uv_close_cb);
  }
}
void Protocol::uv_close_cb(uv_handle_t *handle) {
  do {
    if (!handle || !handle->data)
      break;
    UserData *udata = reinterpret_cast<UserData *>(handle->data);
    Server *pServer = reinterpret_cast<Server *>(udata->Caller());
    do {
      if (!udata || !pServer)
        break;
      switch (udata->ServerTypeGet()) {
      case ServerType::UNKNOWN: {

      } break;
      case ServerType::ACCEPTOR: {
        Config::Get()->OnServerExitBefore(udata);
      } break;
      case ServerType::INITIATOR: {
        Config::Get()->OnServerSessionDestroy(udata);
      } break;
      default:
        break;
      }
    } while (0);
    SK_DELETE_PTR(udata);
    SK_DELETE_PTR(handle);
  } while (0);
}
void Protocol::uv_alloc_cb(uv_handle_t *handle, size_t suggested_size,
                           uv_buf_t *buf) {
  auto udata = USERDATA_PTR(handle);
  /*udata->stream_read->Resize(suggested_size);*/
  if (udata) {
    udata->SetReadBuf(buf);
  }
}
void Protocol::uv_recv_cb(uv_stream_t *stream, ssize_t nread,
                          const uv_buf_t *buf) {
  if (!stream)
    return;
  bool force_close = false;
  auto udata = USERDATA_PTR(stream);
  if (buf->base) {
    if (nread > 0) {
      if (!udata->Read(buf->base, nread))
        force_close = true;
    } else if (nread < 0) {
      force_close = true;
    }
  } else {
    force_close = true;
  }
  if (force_close)
    uv_close((uv_handle_t *)stream, Protocol::uv_close_cb);
}
void Protocol::uv_write_cb(uv_write_t *req, int status) {
  write_req_t *write_req = nullptr;
  do {
    if (!req || !req->data)
      break;
    write_req = reinterpret_cast<write_req_t *>(req->data);
    Session *pClient = SESSION_PTR(write_req->handle);
    if (!pClient)
      break;
    if (status != 0)
      pClient->Status(SessionStatus::FORCECLOSE);
  } while (0);
  SK_DELETE_PTR(write_req);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
tagPacketHeader::tagPacketHeader() {
  memset((void *)this, 0x00, sizeof(*this));
  header_logo = 0xFAC9C2D0;
  footer_logo = 0xB4B4AAC1;
}
tagPacketHeader::tagPacketHeader(const CommandType &input_cmd) {
  memset((void *)this, 0x00, sizeof(*this));
  header_logo = 0xFAC9C2D0;
  footer_logo = 0xB4B4AAC1;
  command_code = static_cast<decltype(command_code)>(input_cmd);
}
tagPacketHeader::~tagPacketHeader() {
}
bool tagPacketHeader::Verify() const {
  return header_logo == 0xFAC9C2D0 && footer_logo == 0xB4B4AAC1;
}
ZipType tagPacketHeader::Zip() const {
  return ZipType(zip_type);
}
EncryptType tagPacketHeader::Encrypt() const {
  return EncryptType(encryption_type);
}
CommandType tagPacketHeader::Command() const {
  return CommandType(command_code);
}
unsigned long tagPacketHeader::DataSize() const {
  return data_size;
}
unsigned long tagPacketHeader::OriginalSize() const {
  return original_size;
}
unsigned long tagPacketHeader::PacketSize() const {
  return packet_size;
}

const std::uint64_t TIMEOUT_HEARBEAT_MS = 30000;
const size_t PACKET_HEAD_SIZE = sizeof(HEAD);
const size_t PACKET_COMPRESSION_STANDARD_SIZE = ((size_t) ~((size_t)0));
