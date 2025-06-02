#if !defined(__0B0874CB_0607_41D4_9CA0_AA7A499DDB8A__)
#define __0B0874CB_0607_41D4_9CA0_AA7A499DDB8A__

class OpenSSL {
public:
  static std::string MD5(const std::string &, const bool &bin2hex = true);
  static std::string Base64Encode(const std::string &,
                                  const bool &multiline = false);
  static std::string Base64Decode(const std::string &,
                                  const bool &multiline = false);

  static std::string SHA256(const std::string &, const bool &bin2hex = true);
  static std::string HMAC_SHA1(const std::string &src, const std::string &seed,
                               const bool &bin2hex = true);
  static std::string HMAC_SHA256(const std::string &src,
                                 const std::string &seed,
                                 const bool &bin2hex = true);
};

/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 31 May 2025 01:04:57 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__0B0874CB_0607_41D4_9CA0_AA7A499DDB8A__