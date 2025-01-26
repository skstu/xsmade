#if !defined(__57A3273D_BCBD_45D1_A36D_C0D66D3D839C__)
#define __57A3273D_BCBD_45D1_A36D_C0D66D3D839C__

class Global {
public:
  static Global *Create();
  static void Destroy();
private:
  Global();
  Global(Global &&global) noexcept;
  Global &operator=(Global &&global) noexcept;

  Global(const Global &) = delete;
  Global &operator=(const Global &) = delete;
  virtual ~Global();

public:
private:
  void Init();
  void UnInit();

private:
  wxString project_root_;
  wxString project_res_dir_;
  wxString project_res_font_dir_;
  wxFont* font_monospace_;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 15 Jan 2025 00:28:38 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__57A3273D_BCBD_45D1_A36D_C0D66D3D839C__