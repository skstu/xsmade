#if !defined(__DBF6427B_81A7_4A73_8F2F_DED725E368A4__)
#define __DBF6427B_81A7_4A73_8F2F_DED725E368A4__

class IModel {
public:
  virtual void Release() const = 0;
  virtual bool LoadModelParts() = 0;
};
class Model final : public IModel {
public:
  Model();
  ~Model();
void Release() const override final;
protected:
  bool LoadModelParts() override final;
  
};
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 26 Jul 2025 13:07:17 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__DBF6427B_81A7_4A73_8F2F_DED725E368A4__