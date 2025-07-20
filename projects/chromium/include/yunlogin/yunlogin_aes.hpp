#if !defined(__5601EBDE_20FE_4A4E_8458_9DE599DBA776__)
#define __5601EBDE_20FE_4A4E_8458_9DE599DBA776__

#include <cstdint>
#include <cstring>
#include <vector>

namespace aes {

 constexpr int AES_BLOCKLEN = 16;

#if defined(AES256) && (AES256 == 1)
 constexpr int AES_KEYLEN = 32;
 constexpr int AES_keyExpSize = 240;
#elif defined(AES192) && (AES192 == 1)
 constexpr int AES_KEYLEN = 24;
 constexpr int AES_keyExpSize = 208;
#else
 constexpr int AES_KEYLEN = 16;
 constexpr int AES_keyExpSize = 176;
#endif

 class AES {
 public:
  enum Mode { ECB, CBC, CTR };

  AES(const std::vector<std::uint8_t>& key, Mode mode = ECB,
   const std::vector<std::uint8_t>& iv = {})
   : mode_(mode) {
   if (key.size() != AES_KEYLEN)
    return;
   KeyExpansion(RoundKey_, key.data());
   if ((mode == CBC || mode == CTR)) {
    if (iv.size() != AES_BLOCKLEN)
     return;
    std::memcpy(Iv_, iv.data(), AES_BLOCKLEN);
   }
  }

  // ECB: buf size must be AES_BLOCKLEN
  void EncryptBlock(std::uint8_t* buf) const {
   if (!buf) return;
   Cipher((state_t*)buf, RoundKey_);
  }
  void DecryptBlock(std::uint8_t* buf) const {
   if (!buf) return;
   InvCipher((state_t*)buf, RoundKey_);
  }

  // CBC: buf size must be multiple of AES_BLOCKLEN
  void CBC_Encrypt(std::uint8_t* buf, std::size_t length) {
   if (mode_ != CBC || !buf || length % AES_BLOCKLEN != 0) return;
   std::uint8_t* Iv = Iv_;
   for (std::size_t i = 0; i < length; i += AES_BLOCKLEN) {
    XorWithIv(buf, Iv);
    Cipher((state_t*)buf, RoundKey_);
    Iv = buf;
    buf += AES_BLOCKLEN;
   }
   std::memcpy(Iv_, Iv, AES_BLOCKLEN);
  }

  void CBC_Decrypt(std::uint8_t* buf, std::size_t length) {
   if (mode_ != CBC || !buf || length % AES_BLOCKLEN != 0) return;
   std::uint8_t storeNextIv[AES_BLOCKLEN];
   for (std::size_t i = 0; i < length; i += AES_BLOCKLEN) {
    std::memcpy(storeNextIv, buf, AES_BLOCKLEN);
    InvCipher((state_t*)buf, RoundKey_);
    XorWithIv(buf, Iv_);
    std::memcpy(Iv_, storeNextIv, AES_BLOCKLEN);
    buf += AES_BLOCKLEN;
   }
  }

  // CTR: encrypt/decrypt
  void CTR_xcrypt(std::uint8_t* buf, std::size_t length) {
   if (mode_ != CTR || !buf) return;
   std::uint8_t buffer[AES_BLOCKLEN];
   unsigned i;
   int bi;
   for (i = 0, bi = AES_BLOCKLEN; i < length; ++i, ++bi) {
    if (bi == AES_BLOCKLEN) {
     std::memcpy(buffer, Iv_, AES_BLOCKLEN);
     Cipher((state_t*)buffer, RoundKey_);
     for (bi = (AES_BLOCKLEN - 1); bi >= 0; --bi) {
      if (Iv_[bi] == 255) {
       Iv_[bi] = 0;
       continue;
      }
      Iv_[bi] += 1;
      break;
     }
     bi = 0;
    }
    buf[i] ^= buffer[bi];
   }
  }

  // Reset IV (for CBC/CTR)
  void SetIv(const std::vector<std::uint8_t>& iv) {
   if (iv.size() != AES_BLOCKLEN)
    return;
   std::memcpy(Iv_, iv.data(), AES_BLOCKLEN);
  }

 private:
  using state_t = std::uint8_t[4][4];

  Mode mode_;
  std::uint8_t RoundKey_[AES_keyExpSize]{};
  std::uint8_t Iv_[AES_BLOCKLEN]{};

  // --- AES internals (static tables and helpers) ---
  static constexpr std::uint8_t sbox[256] = {
      0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b,
      0xfe, 0xd7, 0xab, 0x76, 0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
      0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, 0xb7, 0xfd, 0x93, 0x26,
      0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
      0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2,
      0xeb, 0x27, 0xb2, 0x75, 0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
      0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, 0x53, 0xd1, 0x00, 0xed,
      0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
      0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f,
      0x50, 0x3c, 0x9f, 0xa8, 0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
      0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, 0xcd, 0x0c, 0x13, 0xec,
      0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
      0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14,
      0xde, 0x5e, 0x0b, 0xdb, 0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
      0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, 0xe7, 0xc8, 0x37, 0x6d,
      0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
      0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f,
      0x4b, 0xbd, 0x8b, 0x8a, 0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
      0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, 0xe1, 0xf8, 0x98, 0x11,
      0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
      0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f,
      0xb0, 0x54, 0xbb, 0x16 };
  static constexpr std::uint8_t rsbox[256] = {
      0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e,
      0x81, 0xf3, 0xd7, 0xfb, 0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87,
      0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb, 0x54, 0x7b, 0x94, 0x32,
      0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
      0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49,
      0x6d, 0x8b, 0xd1, 0x25, 0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16,
      0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92, 0x6c, 0x70, 0x48, 0x50,
      0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
      0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05,
      0xb8, 0xb3, 0x45, 0x06, 0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02,
      0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b, 0x3a, 0x91, 0x11, 0x41,
      0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
      0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8,
      0x1c, 0x75, 0xdf, 0x6e, 0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89,
      0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b, 0xfc, 0x56, 0x3e, 0x4b,
      0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
      0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59,
      0x27, 0x80, 0xec, 0x5f, 0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d,
      0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef, 0xa0, 0xe0, 0x3b, 0x4d,
      0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
      0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63,
      0x55, 0x21, 0x0c, 0x7d };
  static constexpr std::uint8_t Rcon[11] = {
      0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };

  static constexpr std::uint8_t getSBoxValue(std::uint8_t num) { return sbox[num]; }
  static constexpr std::uint8_t getSBoxInvert(std::uint8_t num) { return rsbox[num]; }

  static std::uint8_t xtime(std::uint8_t x) { return static_cast<std::uint8_t>((x << 1) ^ (((x >> 7) & 1) * 0x1b)); }

  static std::uint8_t Multiply(std::uint8_t x, std::uint8_t y) {
   return static_cast<std::uint8_t>(
    ((y & 1) * x) ^
    ((y >> 1 & 1) * xtime(x)) ^
    ((y >> 2 & 1) * xtime(xtime(x))) ^
    ((y >> 3 & 1) * xtime(xtime(xtime(x)))) ^
    ((y >> 4 & 1) * xtime(xtime(xtime(xtime(x)))))
    );
  }

  static void KeyExpansion(std::uint8_t* RoundKey, const std::uint8_t* Key) {
   unsigned i, j, k;
   std::uint8_t tempa[4];
   for (i = 0; i < Nk; ++i) {
    RoundKey[(i * 4) + 0] = Key[(i * 4) + 0];
    RoundKey[(i * 4) + 1] = Key[(i * 4) + 1];
    RoundKey[(i * 4) + 2] = Key[(i * 4) + 2];
    RoundKey[(i * 4) + 3] = Key[(i * 4) + 3];
   }
   for (i = Nk; i < Nb * (Nr + 1); ++i) {
    k = (i - 1) * 4;
    tempa[0] = RoundKey[k + 0];
    tempa[1] = RoundKey[k + 1];
    tempa[2] = RoundKey[k + 2];
    tempa[3] = RoundKey[k + 3];
    if (i % Nk == 0) {
     const std::uint8_t u8tmp = tempa[0];
     tempa[0] = tempa[1];
     tempa[1] = tempa[2];
     tempa[2] = tempa[3];
     tempa[3] = u8tmp;
     tempa[0] = getSBoxValue(tempa[0]);
     tempa[1] = getSBoxValue(tempa[1]);
     tempa[2] = getSBoxValue(tempa[2]);
     tempa[3] = getSBoxValue(tempa[3]);
     tempa[0] = tempa[0] ^ Rcon[i / Nk];
    }
#if defined(AES256) && (AES256 == 1)
    if (i % Nk == 4) {
     tempa[0] = getSBoxValue(tempa[0]);
     tempa[1] = getSBoxValue(tempa[1]);
     tempa[2] = getSBoxValue(tempa[2]);
     tempa[3] = getSBoxValue(tempa[3]);
    }
#endif
    j = i * 4;
    k = (i - Nk) * 4;
    RoundKey[j + 0] = RoundKey[k + 0] ^ tempa[0];
    RoundKey[j + 1] = RoundKey[k + 1] ^ tempa[1];
    RoundKey[j + 2] = RoundKey[k + 2] ^ tempa[2];
    RoundKey[j + 3] = RoundKey[k + 3] ^ tempa[3];
   }
  }

  static void AddRoundKey(std::uint8_t round, state_t* state, const std::uint8_t* RoundKey) {
   for (std::uint8_t i = 0; i < 4; ++i)
    for (std::uint8_t j = 0; j < 4; ++j)
     (*state)[i][j] ^= RoundKey[(round * Nb * 4) + (i * Nb) + j];
  }

  static void SubBytes(state_t* state) {
   for (std::uint8_t i = 0; i < 4; ++i)
    for (std::uint8_t j = 0; j < 4; ++j)
     (*state)[j][i] = getSBoxValue((*state)[j][i]);
  }

  static void ShiftRows(state_t* state) {
   std::uint8_t temp;
   temp = (*state)[0][1];
   (*state)[0][1] = (*state)[1][1];
   (*state)[1][1] = (*state)[2][1];
   (*state)[2][1] = (*state)[3][1];
   (*state)[3][1] = temp;
   temp = (*state)[0][2];
   (*state)[0][2] = (*state)[2][2];
   (*state)[2][2] = temp;
   temp = (*state)[1][2];
   (*state)[1][2] = (*state)[3][2];
   (*state)[3][2] = temp;
   temp = (*state)[0][3];
   (*state)[0][3] = (*state)[3][3];
   (*state)[3][3] = (*state)[2][3];
   (*state)[2][3] = (*state)[1][3];
   (*state)[1][3] = temp;
  }

  static void MixColumns(state_t* state) {
   std::uint8_t i, Tmp, Tm, t;
   for (i = 0; i < 4; ++i) {
    t = (*state)[i][0];
    Tmp = (*state)[i][0] ^ (*state)[i][1] ^ (*state)[i][2] ^ (*state)[i][3];
    Tm = (*state)[i][0] ^ (*state)[i][1];
    Tm = xtime(Tm);
    (*state)[i][0] ^= Tm ^ Tmp;
    Tm = (*state)[i][1] ^ (*state)[i][2];
    Tm = xtime(Tm);
    (*state)[i][1] ^= Tm ^ Tmp;
    Tm = (*state)[i][2] ^ (*state)[i][3];
    Tm = xtime(Tm);
    (*state)[i][2] ^= Tm ^ Tmp;
    Tm = (*state)[i][3] ^ t;
    Tm = xtime(Tm);
    (*state)[i][3] ^= Tm ^ Tmp;
   }
  }

  static void Cipher(state_t* state, const std::uint8_t* RoundKey) {
   std::uint8_t round = 0;
   AddRoundKey(0, state, RoundKey);
   for (round = 1; round < Nr; ++round) {
    SubBytes(state);
    ShiftRows(state);
    MixColumns(state);
    AddRoundKey(round, state, RoundKey);
   }
   SubBytes(state);
   ShiftRows(state);
   AddRoundKey(Nr, state, RoundKey);
  }

  static void XorWithIv(std::uint8_t* buf, const std::uint8_t* Iv) {
   for (std::uint8_t i = 0; i < AES_BLOCKLEN; ++i)
    buf[i] ^= Iv[i];
  }

  // --- Decryption helpers ---
  static void InvMixColumns(state_t* state) {
   int i;
   std::uint8_t a, b, c, d;
   for (i = 0; i < 4; ++i) {
    a = (*state)[i][0];
    b = (*state)[i][1];
    c = (*state)[i][2];
    d = (*state)[i][3];
    (*state)[i][0] = Multiply(a, 0x0e) ^ Multiply(b, 0x0b) ^ Multiply(c, 0x0d) ^ Multiply(d, 0x09);
    (*state)[i][1] = Multiply(a, 0x09) ^ Multiply(b, 0x0e) ^ Multiply(c, 0x0b) ^ Multiply(d, 0x0d);
    (*state)[i][2] = Multiply(a, 0x0d) ^ Multiply(b, 0x09) ^ Multiply(c, 0x0e) ^ Multiply(d, 0x0b);
    (*state)[i][3] = Multiply(a, 0x0b) ^ Multiply(b, 0x0d) ^ Multiply(c, 0x09) ^ Multiply(d, 0x0e);
   }
  }

  static void InvSubBytes(state_t* state) {
   for (std::uint8_t i = 0; i < 4; ++i)
    for (std::uint8_t j = 0; j < 4; ++j)
     (*state)[j][i] = getSBoxInvert((*state)[j][i]);
  }

  static void InvShiftRows(state_t* state) {
   std::uint8_t temp;
   temp = (*state)[3][1];
   (*state)[3][1] = (*state)[2][1];
   (*state)[2][1] = (*state)[1][1];
   (*state)[1][1] = (*state)[0][1];
   (*state)[0][1] = temp;
   temp = (*state)[0][2];
   (*state)[0][2] = (*state)[2][2];
   (*state)[2][2] = temp;
   temp = (*state)[1][2];
   (*state)[1][2] = (*state)[3][2];
   (*state)[3][2] = temp;
   temp = (*state)[0][3];
   (*state)[0][3] = (*state)[1][3];
   (*state)[1][3] = (*state)[2][3];
   (*state)[2][3] = (*state)[3][3];
   (*state)[3][3] = temp;
  }

  static void InvCipher(state_t* state, const std::uint8_t* RoundKey) {
   std::uint8_t round = 0;
   AddRoundKey(Nr, state, RoundKey);
   for (round = (Nr - 1); round > 0; --round) {
    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(round, state, RoundKey);
    InvMixColumns(state);
   }
   InvShiftRows(state);
   InvSubBytes(state);
   AddRoundKey(0, state, RoundKey);
  }

  // --- AES params ---
  static constexpr int Nb = 4;
#if defined(AES256) && (AES256 == 1)
  static constexpr int Nk = 8;
  static constexpr int Nr = 14;
#elif defined(AES192) && (AES192 == 1)
  static constexpr int Nk = 6;
  static constexpr int Nr = 12;
#else
  static constexpr int Nk = 4;
  static constexpr int Nr = 10;
#endif
 };

}  // namespace aes

/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 08 Jul 2025 12:22:56 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__5601EBDE_20FE_4A4E_8458_9DE599DBA776__
