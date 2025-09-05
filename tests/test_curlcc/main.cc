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
  std::string target_component_path =
      current_path + "/components/libcurlcc.dll";
#endif
  IComponent *pComponentCurl = nullptr;
  do {
    if (!stl::File::Exists(target_component_path))
      break;
    pComponentCurl = curl::ICurl::Create(target_component_path.c_str());
    auto pCurl = dynamic_cast<curl::ICurl *>(pComponentCurl);
    if (!pCurl)
      break;

    pCurl->Start();
    std::string proxy_string, request_url;

    for (const auto &line : cmdline) {
      if (line.first.compare("proxy-string") == 0 && !line.second.empty()) {
        proxy_string = line.second;
      }
      if (line.first.compare("urls") == 0 && !line.second.empty()) {
        // std::vector<std::string> urls =
        //     stl::Common::StringSplit(line.second, ",");
        // for (const auto &url : urls) {
        //   pCurl->GetConfig()->AppendCurlRequestUrl(url.c_str());
        // }
        request_url = line.second;
      }
    }

    if (proxy_string.empty())
      break;

    auto reqArray = pCurl->CreateRequestArray();
    auto reqMyip = pCurl->CreateRequest();
    reqMyip->SetUrl(request_url.c_str());
    reqMyip->SetProxyString(proxy_string.c_str());

    reqArray->Push(reqMyip);
    curl::ICurl::IRequestArray *resArrsy = pCurl->Perform(reqArray);
    for (size_t i = 0; i < resArrsy->Total(); ++i) {
      curl::ICurl::IRequest *req = resArrsy->Next(i);
      if (!req)
        continue;
      if (req->GetResponseCode()) {
        int code = req->GetResponseCode();
        std::cout << "Request failed with code: " << code << std::endl;
        continue;
      }
      char *response = nullptr;
      size_t response_size = 0;
      req->GetResponse(&response, &response_size);
      std::cout << "Response: " << std::string(response, response_size)
                << std::endl;
      pCurl->Free((void **)&response);
      
    }
    if (resArrsy)
      resArrsy->Release();
  } while (0);
  curl::ICurl::Destroy(&pComponentCurl);
  return 0;
}