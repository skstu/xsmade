#include <xs.h>
#include <stl.hpp>
#include <system.hpp>
#include <rapidjson.h>
#include <components/cceng/export.h>
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
  std::string target_component_path = current_path + "/../components/libcceng.dll";
  IComponent *pComponentCCeng = nullptr;
  do {
    if (!stl::File::Exists(target_component_path))
      break;
    pComponentCCeng = ICCEng::Create(target_component_path.c_str());
    int err = GetLastError();
    auto pCCeng = dynamic_cast<ICCEng *>(pComponentCCeng);
    if (!pCCeng)
      break;

    pCCeng->Start();
  } while (0);
  ICCEng::Destroy(&pComponentCCeng);
  return 0;
}