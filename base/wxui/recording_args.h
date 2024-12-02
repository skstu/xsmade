#if !defined(__5482320A_C40E_4778_B4AC_579DB3BEADAB__)
#define __5482320A_C40E_4778_B4AC_579DB3BEADAB__

class RecordingArgs final : public IRecordingArgs {
public:
  RecordingArgs();
  virtual ~RecordingArgs();
  void Release() const override final;

protected:
  int GetX() const override final;
  int GetY() const override final;
  int GetCX() const override final;
  int GetCY() const override final;

public:
  void SetPos(const int &x, const int &y, const int &cx, const int &cy);

private:
  int x_ = 0;
  int y_ = 0;
  int cx_ = 0;
  int cy_ = 0;
};
#if 0
namespace ffx {
using tfArgs = std::pair<std::string, std::string>;
using tfFFXArgs = std::map<int, tfArgs>;
class Args {
  friend class FFXArgs;

public:
  void Release() const;

private:
  Args();
  ~Args();
  void Push(const std::string &input);
  void PushEnd();

public:
  std::vector<const char *> GetSource() const;

private:
  std::vector<const char *> source_;
};
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
  Args *GetArgs() const;

private:
  tfFFXArgs args_;
};
} // namespace ffx
#endif
/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 24 Nov 2024 00:30:18 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__5482320A_C40E_4778_B4AC_579DB3BEADAB__