#if !defined(__E7E00AA8_9438_41D1_ACCC_DEE02EF876AB__)
#define __E7E00AA8_9438_41D1_ACCC_DEE02EF876AB__

class Brwmnr final {
public:
  static Brwmnr *GetOrCreate();
  static void Destroy();

public:
  Brwobj *CreateBrowser(const brwcfg::IConfigure &, mp_errno_t &);
  void DestroyBrowser(const browser_id_t &, mp_errno_t &);
  Brwobj *GetBrowser(const browser_id_t &) const;

private:
  Brwmnr();
  ~Brwmnr();

private:
  void Init();
  void UnInit();

private:
  std::map<browser_id_t, Brwobj *> brwobjs_;
  tf_frame_buffer_stream_cb frame_buffer_stream_cb_ = nullptr;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};
/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 17 Mar 2025 01:53:04 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__E7E00AA8_9438_41D1_ACCC_DEE02EF876AB__