#if !defined(__59A8FD9B_3870_4495_8BBB_A124FAF39C92__)
#define __59A8FD9B_3870_4495_8BBB_A124FAF39C92__
#include <xs.h>
#include <icomponent.h>

class Brwext final : public IBrwComponent {
public:
  static Brwext *Create();
  static void Destroy();

private:
  Brwext();
  virtual ~Brwext();

protected:
  bool Start() override final;
  void Stop() override final;

private:
  std::atomic_bool open_ = false;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 19 Feb 2025 03:12:15 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__59A8FD9B_3870_4495_8BBB_A124FAF39C92__
