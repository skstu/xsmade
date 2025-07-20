#if !defined(__720A157D_AD24_4705_B500_6CF4DAF81407__)
#define __720A157D_AD24_4705_B500_6CF4DAF81407__

class ExtensionsRequest final {
public:
  enum class Target : int { unknown = 0, kernel = 1 };
  enum class Method : int {
    unknown = 0,
    init = 1,
    uninit = 2,
  };
  static const std::map<Method, std::string> MethodToStringMap;
  static const std::map<Target, std::string> TargetToStringMap;
  static const std::map<std::string, Method> StringToMethodMap;
  static const std::map<std::string, Target> StringToTargetMap;
  static std::string MethodToString(Method m);
  static std::string TargetToString(Target m);
  static Method StringToMethod(const std::string &str);
  static Target StringToTarget(const std::string &str);
public:
  inline ExtensionsRequest(const ExtensionsRequest &) = delete;
  inline ExtensionsRequest &operator=(const ExtensionsRequest &) = delete;
  inline void *operator new(size_t) = delete;
  inline void operator delete(void *) = delete;
  inline ~ExtensionsRequest() = default;
  ExtensionsRequest(const std::string &id, const std::string &body);

public:
  const std::string &GetExtensionsId() const;

private:
  bool operator<<(const std::string &body);
  const std::string id_;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 03 Jun 2025 03:57:23 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__720A157D_AD24_4705_B500_6CF4DAF81407__