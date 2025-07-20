#if !defined(__180824B0_BEE4_4DAB_9045_3ADCA77AD0B2__)
#define __180824B0_BEE4_4DAB_9045_3ADCA77AD0B2__

class IChromium final {
  friend class Browser;

private:
  IChromium();
  virtual ~IChromium();
  void Release() const;
private:
  bool Open();
  void Close();

private:
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};

/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 31 May 2025 04:27:39 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__180824B0_BEE4_4DAB_9045_3ADCA77AD0B2__