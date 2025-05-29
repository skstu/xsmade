#if !defined(__5920F26C_AB73_45AD_A483_3FDFD7C7067B__)
#define __5920F26C_AB73_45AD_A483_3FDFD7C7067B__

class IConfigure final {
public:
  IConfigure() = default;
  ~IConfigure() = default;
  bool operator<<(const std::string &buffer) {
    bool result = false;
    do {
      if (buffer.empty())
        break;
      rapidjson::Document doc;
      if (doc.Parse(buffer.c_str(), buffer.size()).HasParseError())
        break;
      if (!doc.IsObject())
        break;
    } while (0);
    return result;
  }
};
/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 20 May 2025 02:46:27 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__5920F26C_AB73_45AD_A483_3FDFD7C7067B__