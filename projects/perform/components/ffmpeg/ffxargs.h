#if !defined(__5482320A_C40E_4778_B4AC_579DB3BEADAB__)
#define __5482320A_C40E_4778_B4AC_579DB3BEADAB__

namespace ffx {
using tfArgs = std::pair<std::string, std::string>;
using tfFFXArgs = std::map<int, tfArgs>;
class FFXArgs {
public:
  FFXArgs(const tfFFXArgs &);
  void *operator new(size_t) = delete;
  void operator delete(void *) = delete;
  FFXArgs(const FFXArgs &) = delete;
  FFXArgs &operator=(const FFXArgs &) = delete;
  ~FFXArgs();

public:
  void Push(const std::string &key, const std::string &value);
  std::vector<std::string> GetArgs() const;

private:
  tfFFXArgs args_;
};
} // namespace ffx

/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 24 Nov 2024 00:30:18 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__5482320A_C40E_4778_B4AC_579DB3BEADAB__