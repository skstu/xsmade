#if !defined(__56204290_3F58_4165_A60E_291616C3C9E1__)
#define __56204290_3F58_4165_A60E_291616C3C9E1__

class Theme final : public ITheme {
public:
  Theme();
  virtual ~Theme();

protected:
  void SetShapeImage(const char *) override final;
  void SetBackgroundImage(const char *) override final;
  public:
  tfThemeIdentify Identify() const override final;

public:
  const wxImage &GetShapeImage() const;
  const wxImage &GetBackgroundImage() const;

private:
  std::string image_shape_;
  std::string image_background_;
  tfThemeIdentify identify_ = 0;

  wxImage *wximage_shape_ = nullptr;
  wxImage *wximage_bkg_ = nullptr;
};

/// /*_ Memade®（新生™） _**/
/// /*_ Thu, 28 Nov 2024 06:41:58 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__56204290_3F58_4165_A60E_291616C3C9E1__