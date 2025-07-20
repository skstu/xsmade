#if !defined(__A8C7D1D9_92CC_4BF8_96DD_06A7F4FED359__)
#define __A8C7D1D9_92CC_4BF8_96DD_06A7F4FED359__

#include "cross_project_compatibility.h"

#if COMPILE_IN_PROJECT_CHROMIUM
#include "chromium/projects/yunlogin/yunlogin_aes.hpp"
#include "chromium/projects/yunlogin/yunlogin_base64.hpp"
#include "build/branding_buildflags.h"
#include "build/build_config.h"
#else
#include "yunlogin_aes.hpp"
#include "yunlogin_base64.hpp"
#endif

namespace chromium {
namespace yunlogin {
namespace {
// 平台密钥与IV
inline std::vector<uint8_t> GetAesKey() {
#if COMPILE_IN_PROJECT_CHROMIUM
#if BUILDFLAG(ENABLE_SDK_BRANDING)
#if BUILDFLAG(IS_MAC)
  static const uint8_t kAesKey[] = {0x3c, 0x88, 0x7e, 0x16, 0x58, 0xae,
                                    0xd6, 0xa6, 0xcb, 0xf7, 0x35, 0x88,
                                    0xf9, 0xcf, 0x6f, 0x3a};
#else
  static constexpr uint8_t kAesKey[] = {0x3c, 0x88, 0x7e, 0x16, 0x58, 0xae,
                                        0xd6, 0xa6, 0xcb, 0xf7, 0x35, 0x88,
                                        0xf9, 0xcf, 0x6f, 0x3a};
#endif
#else
#if BUILDFLAG(IS_MAC)
  static const uint8_t kAesKey[] = {0x3a, 0x7e, 0x88, 0x16, 0x58, 0xae,
                                    0xd6, 0xa6, 0xcb, 0xf7, 0x35, 0x88,
                                    0xf9, 0xcf, 0x6f, 0x3c};
#else
  static constexpr uint8_t kAesKey[] = {0x3a, 0x7e, 0x88, 0x16, 0x58, 0xae,
                                        0xd6, 0xa6, 0xcb, 0xf7, 0x35, 0x88,
                                        0xf9, 0xcf, 0x6f, 0x3c};
#endif
#endif
#else
  static constexpr uint8_t kAesKey[] = {0x3a, 0x7e, 0x88, 0x16, 0x58, 0xae,
                                        0xd6, 0xa6, 0xcb, 0xf7, 0x35, 0x88,
                                        0xf9, 0xcf, 0x6f, 0x3c};
#endif // NOT_COMPILED_IN_CHROMIUM_PROJECT
  return std::vector<uint8_t>(kAesKey, kAesKey + 16);
}

inline std::vector<uint8_t> GetAesIv() {
#if COMPILE_IN_PROJECT_CHROMIUM
#if BUILDFLAG(ENABLE_SDK_BRANDING)
#if BUILDFLAG(IS_MAC)
  static const uint8_t kAesIv[] = {0x0f, 0x09, 0x22, 0x03, 0x35, 0x04,
                                   0x06, 0x30, 0x68, 0x01, 0x0a, 0x0b,
                                   0x3c, 0x0d, 0xde, 0x00};
#else
  static constexpr uint8_t kAesIv[] = {0x0f, 0x09, 0x22, 0x03, 0x35, 0x04,
                                       0x06, 0x30, 0x68, 0x01, 0x0a, 0x0b,
                                       0x3c, 0x0d, 0xde, 0x00};
#endif
#else
#if BUILDFLAG(IS_MAC)
  static const uint8_t kAesIv[] = {0x00, 0x01, 0x22, 0x03, 0x04, 0x35,
                                   0x06, 0x27, 0x68, 0x09, 0x0a, 0x0b,
                                   0x3c, 0x0d, 0xde, 0x0f};
#else
  static constexpr uint8_t kAesIv[] = {0x00, 0x01, 0x22, 0x03, 0x04, 0x35,
                                       0x06, 0x27, 0x68, 0x09, 0x0a, 0x0b,
                                       0x3c, 0x0d, 0xde, 0x0f};
#endif
#endif
#else
  static constexpr uint8_t kAesIv[] = {0x00, 0x01, 0x22, 0x03, 0x04, 0x35,
                                       0x06, 0x27, 0x68, 0x09, 0x0a, 0x0b,
                                       0x3c, 0x0d, 0xde, 0x0f};
#endif
  return std::vector<uint8_t>(kAesIv, kAesIv + 16);
}

// CBC加密，输出补齐后的密文
inline void AesCBCEncrypt(const std::string &jsonString,
                          std::vector<uint8_t> &cipher_text) {
  size_t len = jsonString.length();
  if (len % 16 > 0) {
    len += 16 - (jsonString.length() % 16);
  }
  cipher_text.resize(len, 0);
  std::memcpy(cipher_text.data(), jsonString.data(), jsonString.length());

  aes::AES aes(GetAesKey(), aes::AES::CBC, GetAesIv());
  aes.CBC_Encrypt(cipher_text.data(), cipher_text.size());
}

// CBC解密，去除补零
inline std::string AesCBCDecrypt(std::vector<uint8_t> &cipher_text) {
  aes::AES aes(GetAesKey(), aes::AES::CBC, GetAesIv());
  aes.CBC_Decrypt(cipher_text.data(), cipher_text.size());

  size_t size = cipher_text.size();
  while (size > 0 && cipher_text[size - 1] == 0) {
    --size;
  }
  return std::string(reinterpret_cast<char *>(cipher_text.data()), size);
}

} // namespace

inline std::string AESEncrypt(const std::string &jsonString) {
  std::vector<uint8_t> cipher_text;
  AesCBCEncrypt(jsonString, cipher_text);
  return base64_encode(cipher_text.data(), cipher_text.size());
}

inline std::string AESDecrypt(const std::string &encoded) {
  if (encoded.empty())
    return std::string();
  std::string decoded = base64_decode(encoded);
  std::vector<uint8_t> cipher_text(decoded.begin(), decoded.end());
  return AesCBCDecrypt(cipher_text);
}

} // namespace yunlogin
} // namespace chromium

/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 08 Jul 2025 05:36:00 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__A8C7D1D9_92CC_4BF8_96DD_06A7F4FED359__