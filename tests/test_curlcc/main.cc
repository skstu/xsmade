#include <xs.h>
#include <stl.hpp>
#include <system.hpp>
#include <rapidjson.h>
#include <components/curlcc/export.h>
#ifdef __OSWIN__
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR __cmdline__,
                     int cmdshow)
#else
int main(int argc, char **argv)
#endif
{
  if (0 == xs_sys_process_already_exists(0))
    return 1;
  if (!__cmdline__)
    return 0;
  stl::tfCommandLines cmdline =
      stl::CmdLine::ParserCommandLines(__cmdline__, true);

  std::string current_path = System::GetCurrentProcessPath();
#if _DEBUG
  std::string target_component_path =
      current_path + "/../components/libcurlcc.dll";
#else
  std::string target_component_path = current_path + "/libcurlcc.dll";
#endif
  IComponent *pComponentCurl = nullptr;
  do {
    if (!stl::File::Exists(target_component_path))
      break;
    pComponentCurl = curl::ICurl::Create(target_component_path.c_str());
    auto pCurl = dynamic_cast<curl::ICurl *>(pComponentCurl);
    if (!pCurl)
      break;
    for (const auto &line : cmdline) {
      if (line.first.compare("proxy-string") == 0 && !line.second.empty()) {
        pCurl->GetConfig()->SetCurlProxyString(line.second.c_str());
      }
      if (line.first.compare("urls") == 0 && !line.second.empty()) {
        std::vector<std::string> urls =
            stl::Common::StringSplit(line.second, ",");
        for (const auto &url : urls) {
          pCurl->GetConfig()->AppendCurlRequestUrl(url.c_str());
        }
      }
      if (line.first.compare("response-file") == 0 && !line.second.empty()) {
        pCurl->GetConfig()->SetCurlResponseFilename(line.second.c_str());
      }
    }

    pCurl->Start();
    pCurl->Perform(nullptr);
  } while (0);
  curl::ICurl::Destroy(&pComponentCurl);
  return 0;
}