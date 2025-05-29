#include <xs.h>
#include <stl.hpp>
#include <system.hpp>
#include <rapidjson.h>
#include <components/curlcc/export.h>
class IConfigure final {
public:
  IConfigure() = default;
  ~IConfigure() = default;

public:
  bool operator<<(const std::string &cfg) {
    bool result = false;
    return result;
  }
};
int main(int argc, char **argv) {
  std::string current_path = System::GetCurrentProcessPath();
#if _DEBUG
  std::string target_component_path =
      current_path + "/../components/libcurlcc.dll";
#else
  std::string target_component_path = current_path + "/libcurlcc.dll";
#endif
  std::string cfg_path = current_path + "/curlcc.json";
  
  IComponent *pComponentCurl = nullptr;
  do {
    if (!stl::File::Exists(target_component_path))
      break;
    pComponentCurl = curl::ICurl::Create(target_component_path.c_str());
    pComponentCurl->Start();
    int sss = 0;
  } while (0);
  curl::ICurl::Destroy(&pComponentCurl);
  return 0;
}