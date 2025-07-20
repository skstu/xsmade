#ifndef BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A
#define BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A

#include <string>
#include <vector>
#include <cstddef>
#include <algorithm>
#if __cplusplus >= 201703L
#include <string_view>
#endif

inline std::string base64_encode(const unsigned char* bytes_to_encode, size_t in_len, bool url = false) {
 static const char* base64_chars_url = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
 static const char* base64_chars_std = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
 const char* base64_chars = url ? base64_chars_url : base64_chars_std;
 unsigned char trailing_char = url ? '.' : '=';

 std::string ret;
 ret.reserve((in_len + 2) / 3 * 4);

 size_t pos = 0;
 while (pos < in_len) {
  unsigned char b0 = bytes_to_encode[pos + 0];
  unsigned char b1 = (pos + 1 < in_len) ? bytes_to_encode[pos + 1] : 0;
  unsigned char b2 = (pos + 2 < in_len) ? bytes_to_encode[pos + 2] : 0;

  ret.push_back(base64_chars[(b0 & 0xfc) >> 2]);
  ret.push_back(base64_chars[((b0 & 0x03) << 4) | ((b1 & 0xf0) >> 4)]);
  if (pos + 1 < in_len) {
   ret.push_back(base64_chars[((b1 & 0x0f) << 2) | ((b2 & 0xc0) >> 6)]);
  }
  else {
   ret.push_back(static_cast<char>(trailing_char));
  }
  if (pos + 2 < in_len) {
   ret.push_back(base64_chars[b2 & 0x3f]);
  }
  else {
   ret.push_back(static_cast<char>(trailing_char));
  }
  pos += 3;
 }
 return ret;
}

inline std::string base64_encode(const std::string& s, bool url = false) {
 return base64_encode(reinterpret_cast<const unsigned char*>(s.data()), s.size(), url);
}

#if __cplusplus >= 201703L
inline std::string base64_encode(std::string_view s, bool url = false) {
 return base64_encode(reinterpret_cast<const unsigned char*>(s.data()), s.size(), url);
}
#endif

inline std::string base64_encode_pem(const std::string& s) {
 std::string encoded = base64_encode(s, false);
 std::string out;
 for (size_t i = 0; i < encoded.size(); i += 64) {
  out.append(encoded.substr(i, 64));
  out.push_back('\n');
 }
 return out;
}
inline std::string base64_encode_mime(const std::string& s) {
 std::string encoded = base64_encode(s, false);
 std::string out;
 for (size_t i = 0; i < encoded.size(); i += 76) {
  out.append(encoded.substr(i, 76));
  out.push_back('\n');
 }
 return out;
}
#if __cplusplus >= 201703L
inline std::string base64_encode_pem(std::string_view s) {
 return base64_encode_pem(std::string(s));
}
inline std::string base64_encode_mime(std::string_view s) {
 return base64_encode_mime(std::string(s));
}
#endif

inline unsigned int base64_pos_of_char(unsigned char chr) {
 if (chr >= 'A' && chr <= 'Z') return chr - 'A';
 if (chr >= 'a' && chr <= 'z') return chr - 'a' + 26;
 if (chr >= '0' && chr <= '9') return chr - '0' + 52;
 if (chr == '+' || chr == '-') return 62;
 if (chr == '/' || chr == '_') return 63;
 return 0;
}

inline std::string base64_decode(const std::string& encoded_string, bool remove_linebreaks = false) {
 if (encoded_string.empty()) return std::string();

 std::string input(encoded_string);
 if (remove_linebreaks) {
  input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
 }

 size_t length_of_string = input.length();
 size_t pos = 0;
 size_t approx_length_of_decoded_string = length_of_string / 4 * 3;
 std::string ret;
 ret.reserve(approx_length_of_decoded_string);

 while (pos < length_of_string) {
  unsigned char c0 = static_cast<unsigned char>(input[pos + 0]);
  unsigned char c1 = static_cast<unsigned char>(input[pos + 1]);
  unsigned int pos_of_char_1 = base64_pos_of_char(c1);
  ret.push_back(static_cast<char>(((base64_pos_of_char(c0)) << 2) + ((pos_of_char_1 & 0x30) >> 4)));

  if ((pos + 2 < length_of_string) &&
   input[pos + 2] != '=' && input[pos + 2] != '.') {
   unsigned char c2 = static_cast<unsigned char>(input[pos + 2]);
   unsigned int pos_of_char_2 = base64_pos_of_char(c2);
   ret.push_back(static_cast<char>(((pos_of_char_1 & 0x0f) << 4) + ((pos_of_char_2 & 0x3c) >> 2)));

   if ((pos + 3 < length_of_string) &&
    input[pos + 3] != '=' && input[pos + 3] != '.') {
    unsigned char c3 = static_cast<unsigned char>(input[pos + 3]);
    ret.push_back(static_cast<char>(((pos_of_char_2 & 0x03) << 6) + base64_pos_of_char(c3)));
   }
  }
  pos += 4;
 }
 return ret;
}

#if __cplusplus >= 201703L
inline std::string base64_decode(std::string_view s, bool remove_linebreaks = false) {
 return base64_decode(std::string(s), remove_linebreaks);
}
#endif

#endif /* BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A */