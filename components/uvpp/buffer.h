#if !defined(__C8A9C62B_A8ED_4660_AC86_8FA5271442BD__)
#define __C8A9C62B_A8ED_4660_AC86_8FA5271442BD__

typedef class Buffer final : public IBuffer {
public:
  Buffer();
  Buffer(const std::string &);
  Buffer(const char *, const size_t &);
  virtual ~Buffer();

public:
  IBuffer *Clone() const override final;
  const char *GetData() const override final;
  size_t GetDataSize() const override final;
  void SetData(const char *, const size_t &) override final;
  void Release() const override final;
  bool Empty() const override final;

public:
  std::string GetString() const;

private:
  std::string buffer_;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
} Data;

/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 21 Jul 2024 00:42:57 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__C8A9C62B_A8ED_4660_AC86_8FA5271442BD__
