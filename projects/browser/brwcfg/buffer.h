#if !defined(__9CCACBF3_859C_4364_9D98_F0F073858107__)
#define __9CCACBF3_859C_4364_9D98_F0F073858107__

class Buffer final : public IBrwcfg::IBuffer {
public:
  Buffer(const std::string &);
  Buffer(const char *, const size_t &);
  virtual ~Buffer();

public:
  const char *GetData() const override final;
  size_t GetSize() const override final;
  void Release() const override final;

private:
  const std::string source_;
};

class BufferArray final : public IBrwcfg::IBufferArray {
public:
  BufferArray();

private:
  virtual ~BufferArray();

public:
  void Push(Buffer *);
  void Push(const std::string &u8);
  void Push(const std::u16string &u16);
  void Push(const char *u8, const size_t &len);

protected:
  void Push(IBrwcfg::IBuffer *) override final;
  IBrwcfg::IBuffer *CreateBuffer(const char *, const size_t &) override final;
  IBrwcfg::IBuffer *Next(const size_t &) const override final;
  size_t Total() const override final;
  void Release() const override final;

private:
  std::vector<Buffer *> source_;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};
/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 19 Feb 2025 07:26:24 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__9CCACBF3_859C_4364_9D98_F0F073858107__