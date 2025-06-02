#if !defined(__78500B5C_E36B_4D50_9C53_8F10D7578E9E__)
#define __78500B5C_E36B_4D50_9C53_8F10D7578E9E__
namespace local {
class Position final : public IBrwcfg::IPosition {
public:
  Position() {
  }
  virtual ~Position() {
  }

public:
  int GetX() const override final {
    return x_;
  }
  int GetY() const override final {
    return y_;
  }
  void SetX(int v) override final {
    x_ = v;
  }
  void SetY(int v) override final {
    y_ = v;
  }
  void Release() const override final {
    delete this;
  }

private:
  int x_ = 0;
  int y_ = 0;
};
class Size final : public IBrwcfg::ISize {
public:
  Size() {
  }
  virtual ~Size() {
  }

public:
  void SetWidth(int v) override final {
    width_ = v;
  }
  void SetHeight(int v) override final {
    height_ = v;
  }
  int GetWidth() const override final {
    return width_;
  }
  int GetHeight() const override final {
    return height_;
  }
  void Release() const override final {
    delete this;
  }

private:
  int width_ = 0;
  int height_ = 0;
};
class Rectangle final : public IBrwcfg::IRectangle {
public:
  Rectangle() {
  }
  virtual ~Rectangle() {
  }

protected:
  void SetX(int v) override final {
    x_ = v;
  }
  void SetY(int v) override final {
    y_ = v;
  }
  void SetWidth(int v) override final {
    width_ = v;
  }
  void SetHeight(int v) override final {
    height_ = v;
  }
  int GetX() const override final {
    return x_;
  }
  int GetY() const override final {
    return y_;
  }
  int GetWidth() const override final {
    return width_;
  }
  int GetHeight() const override final {
    return height_;
  }
  void Release() const override final {
    delete this;
  }

private:
  int x_ = 0;
  int y_ = 0;
  int width_ = 0;
  int height_ = 0;
};
} // namespace local

/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 26 Mar 2025 00:14:32 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__78500B5C_E36B_4D50_9C53_8F10D7578E9E__