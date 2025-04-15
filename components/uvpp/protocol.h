#if !defined(__291A2E20_BCB0_4E74_985A_ED27CF6A5528__)
#define __291A2E20_BCB0_4E74_985A_ED27CF6A5528__
#include <structs.h>
#define SESSION_PTR(uv_handle) reinterpret_cast<Session *>(uv_handle->data)
#define USERDATA_PTR(p) SESSION_PTR(p)

class Protocol final {
public:
  static bool HeadVerify(const HEAD &);

public:
  //!@ Need WSAStartup and WSACleanup
  //! But libuv has already initialized the method
  static bool MakeIPAddr(
      const std::string &address_string,
      std::string
          &out_addr_buffer /*sockaddr_in|sockaddr|sockaddr_in6|sockaddr_storage
                              buffer*/
      ,
      const AddressType &ip_type = AddressType::IPV4);
  static bool UnMakeIPAddr(
      const std::string
          &address_buffer /*sockaddr_in|sockaddr|sockaddr_in6|sockaddr_storage
                             buffer*/
      ,
      std::string &out_address_string);
  static std::string MakeStream(const HEAD &, const std::string &);
  static bool UnMakeStream(const std::string &input, HEAD &,
                           std::string &output);
  static ServerType GetServerType(const unsigned long &);
  static SessionType GetSessionType(const unsigned long &);
  static AddressType GetAddressType(const unsigned long &);

public:
  static void uv_alloc_cb(uv_handle_t *handle, size_t suggested_size,
                          uv_buf_t *buf);
  static void uv_recv_cb(uv_stream_t *stream, ssize_t nread,
                         const uv_buf_t *buf);
  static void uv_write_cb(uv_write_t *req, int status);
  static void uv_close_cb(uv_handle_t *handle);
  static void walk_close_handle_cb(uv_handle_t *handle, void *arg);
};

extern const size_t PACKET_HEAD_SIZE;
extern const size_t PACKET_COMPRESSION_STANDARD_SIZE;
extern const std::uint64_t TIMEOUT_HEARBEAT_MS;

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 19 May 2023 14:28:32 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__291A2E20_BCB0_4E74_985A_ED27CF6A5528__