#include "system.h"
#include "sys.hpp"
#include "stl.hpp"
#include "base/curlcc/export.h"
int main(int argc, char **argv) {
  std::string path = stl::Path::Mormalize(System::GetCurrentProcessPath() +
                                          "/plugins/curlcc.dll");
  curl::ICurl* pCurl = curl::ICurl::Create(path.c_str());
  curl::ICurl::Destroy(&pCurl);
  return 0;
}
