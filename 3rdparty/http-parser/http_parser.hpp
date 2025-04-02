#if !defined(__B1027CDC_2643_45DF_A446_AC4CA7F399DF__)
#define __B1027CDC_2643_45DF_A446_AC4CA7F399DF__

#include <string.h>
#include <http_parser.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
// #include <string.h>
#include <stdarg.h>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <mutex>
#include <memory>
#include <algorithm>
#include <unordered_map>

namespace httpparser {
const unsigned int MAX_HEADERS = 13;
const unsigned int MAX_ELEMENT_SIZE = 2048;
const unsigned int MAX_CHUNKS = 16;

#pragma pack(push, 1)

typedef struct tag_message {
  const char *name; // for debugging purposes
  const char *raw;
  enum http_parser_type type;
  enum http_method method;
  int status_code;
  char response_status[MAX_ELEMENT_SIZE];
  char request_path[MAX_ELEMENT_SIZE];
  char request_url[MAX_ELEMENT_SIZE];
  char fragment[MAX_ELEMENT_SIZE];
  char query_string[MAX_ELEMENT_SIZE];
  char body[MAX_ELEMENT_SIZE];
  size_t body_size;
  const char *host;
  const char *userinfo;
  uint16_t port;
  int num_headers;
  enum { NONE = 0, FIELD, VALUE } last_header_element;
  char headers[MAX_HEADERS][2][MAX_ELEMENT_SIZE];
  int should_keep_alive;

  int num_chunks;
  int num_chunks_complete;
  int chunk_lengths[MAX_CHUNKS];

  const char *upgrade; // upgraded body

  unsigned short http_major;
  unsigned short http_minor;
  uint64_t content_length;

  int message_begin_cb_called;
  int headers_complete_cb_called;
  int message_complete_cb_called;
  int status_cb_called;
  int message_complete_on_eof;
  int body_is_final;
  int allow_chunked_length;

  tag_message() {
    memset(this, 0x00, sizeof(*this));
  }
  void operator=(const tag_message &msg) {
    memcpy(this, &msg, sizeof(*this));
  }
} message;
#pragma pack(pop)
const size_t LENTAGMESSAGE = sizeof(message);

using tf_request_url_cb = int (*)(http_parser *, const char *, size_t);
using tf_header_field_cb = int (*)(http_parser *, const char &, size_t);
using tf_header_value_cb = int (*)(http_parser *, const char *, size_t);
using tf_body_cb = int (*)(http_parser *, const char *, size_t);
using tf_count_body_cb = int (*)(http_parser *, const char *, size_t);
using tf_message_begin_cb = int (*)(http_parser *);
using tf_headers_complete_cb = int (*)(http_parser *);
using tf_message_complete_cb = int (*)(http_parser *);
using tf_response_status_cb = int (*)(http_parser *, const char *, size_t);
using tf_chunk_header_cb = int (*)(http_parser *);
using tf_chunk_complete_cb = int (*)(http_parser *);
using tf_dontcall_message_begin_cb = int (*)(http_parser *);
using tf_dontcall_header_field_cb = int (*)(http_parser *, const char *,
                                            size_t);
using tf_dontcall_header_value_cb = int (*)(http_parser *, const char *,
                                            size_t);
using tf_dontcall_request_url_cb = int (*)(http_parser *, const char *, size_t);
using tf_dontcall_body_cb = int (*)(http_parser *, const char *, size_t);
using tf_dontcall_headers_complete_cb = int (*)(http_parser *);
using tf_dontcall_message_complete_cb = int (*)(http_parser *);
using tf_dontcall_response_status_cb = int (*)(http_parser *, const char *,
                                               size_t);
using tf_dontcall_chunk_header_cb = int (*)(http_parser *);
using tf_dontcall_chunk_complete_cb = int (*)(http_parser *);
using tf_pause_message_begin_cb = int (*)(http_parser *);
using tf_pause_header_field_cb = int (*)(http_parser *, const char *, size_t);
using tf_pause_header_value_cb = int (*)(http_parser *, const char *, size_t);
using tf_pause_request_url_cb = int (*)(http_parser *, const char *, size_t);
using tf_pause_body_cb = int (*)(http_parser *, const char *, size_t);
using tf_pause_headers_complete_cb = int (*)(http_parser *);
using tf_pause_message_complete_cb = int (*)(http_parser *);
using tf_pause_response_status_cb = int (*)(http_parser *, const char *,
                                            size_t);
using tf_pause_chunk_header_cb = int (*)(http_parser *);
using tf_pause_chunk_complete_cb = int (*)(http_parser *);
using tf_connect_headers_complete_cb = int (*)(http_parser *);
using tf_connect_message_complete_cb = int (*)(http_parser *);

class HttpRequest {
protected:
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();

public:
  HttpRequest();
  virtual ~HttpRequest();

public:
  void PushHeaderKey(const char *, const size_t &);
  void PushHeaderValue(const char *, const size_t &);
  void HeaderClear();
  std::string operator[](const std::string &);

private:
  std::map<std::string, std::string> m_mapHeader;
};

using EnHttpUrlFieldType = http_parser_url_fields;

class HttpUrlFields {
protected:
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();

public:
  HttpUrlFields();
  virtual ~HttpUrlFields();

public:
  const unsigned short &port() const;
  void port(const unsigned short &);
  void clear();
  bool empty() const;
  void push(const EnHttpUrlFieldType &key, const std::string &value);
  std::string operator[](const EnHttpUrlFieldType &);

private:
  unsigned short m_port = 0;
  std::map<EnHttpUrlFieldType, std::string> m_mapUrlField;
};

class Method {
public:
  static void version(std::string &strVersion, unsigned long &nVersion);
  static bool parse_http_request(const std::string &http_data,
                                 size_t &parse_size, HttpRequest &);
  static bool parse_http_url(const std::string &url, HttpUrlFields &);
  // http_parser_version
};
} // namespace httpparser

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 27 Jan 2023 09:45:46 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__B1027CDC_2643_45DF_A446_AC4CA7F399DF__
