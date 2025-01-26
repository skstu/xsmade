#if !defined(__0CF0E4CD_AFE6_4096_9486_690C231B6975__)
#define __0CF0E4CD_AFE6_4096_9486_690C231B6975__

class Data final : public IBrwcfg::IData {
public:
  Data();
  Data(const char *, const size_t &);

private:
  virtual ~Data();

public:
  void Release() const override final;

protected:
  void *GetData() const override final;
  size_t GetSize() const override final;
  void SetData(const void *, const size_t &) override final;

private:
  char *source_ = nullptr;
  size_t source_len_ = 0;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};

/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 07 Jan 2025 07:31:27 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__0CF0E4CD_AFE6_4096_9486_690C231B6975__
