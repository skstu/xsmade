#if !defined(__EFF64F83_4CF2_4F00_8BBA_5B5261CB65BA__)
#define __EFF64F83_4CF2_4F00_8BBA_5B5261CB65BA__

class Uvpp final : public IUvpp {
public:
  static Uvpp *Create();
  static void Destroy();

private:
  Uvpp();
  virtual ~Uvpp();

protected:
  IConfig *ConfigGet() const override final;
  IService *CreateSevice() const override final;
  IBuffer *CreateBuffer(const char *, size_t) const override final;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 03 Dec 2024 02:22:24 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__EFF64F83_4CF2_4F00_8BBA_5B5261CB65BA__