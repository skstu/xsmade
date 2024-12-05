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

/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 24 Nov 2024 00:30:18 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__5482320A_C40E_4778_B4AC_579DB3BEADAB__