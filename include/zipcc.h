#if !defined(__8F227512_937E_4B7C_9330_5007A91EAE6B__)
#define __8F227512_937E_4B7C_9330_5007A91EAE6B__

#include "stl.hpp"

class Zipcc final {
public:
  Zipcc() = default;
  ~Zipcc() = default;

public:
  static bool IsZipCompress(const std::string &buffer);
  static bool zipCompress(const std::string &src, std::string &dst);
  static bool zipUnCompress(const std::string &src, const size_t &nraw,
                            std::string &dst);
  static bool gzipCompress(const std::string &src, std::string &dst,
                           int level = -1);
  static bool gzipUnCompress(const std::string &src, std::string &dst);

  typedef bool (*tfzipUnCompressProgressCb)(size_t total, size_t current,
                                            void *route);
  typedef bool (*tfzipUnCompressCb)(const std::u16string &path,
                                    const std::string &buffer, void *route);
  // static bool zipCompressFile(const std::string& inputFile,const std::string&
  // outputFile);
  static bool zipCompressDirectory(const std::u16string &inputDirpath,
                                   const std::u16string &outputZipfile);
  static bool zipUnCompress(const std::u16string &inputZipFile,
                            const std::u16string &outputUnzipPath);
  static bool zipUnCompress(const std::u16string &inputZipFile,
                            const std::u16string &outputUnzipPath,
                            const tfzipUnCompressProgressCb &);
  static bool zipUnCompress(const std::u16string &inputZipFile,
                            const tfzipUnCompressCb &uncompress_cb,
                            void *route = nullptr);
};

/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 17 Nov 2024 01:20:08 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__8F227512_937E_4B7C_9330_5007A91EAE6B__