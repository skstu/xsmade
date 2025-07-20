#include "config.h"
#ifdef __OSWIN__
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
// int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline,
//                      int cmdshow)
int main(int argc, char *args[])
#elif defined(__OSLINUX__)
int main(int argc, char *args[])
#endif
{
  if (0 == xs_sys_process_already_exists(0))
    return 1;

#if 0
  do {
    chromium::Packet packet;
    chromium::tfRouteRes ress;
    chromium::tfRoutePak res;
    packet.made(
        {
            {1, "test1"},
            {2, "test2"},
            {3, "test3"},
            {4, "test4"},
        },
        res);

    chromium::tfRoutePak inpak;
    chromium::tfRouteRes outpak;
    packet.unmade(res, outpak);
    
    std::string buffer = stl::File::ReadFile(
        R"(C:\Users\k34ub\AppData\Roaming\ChromiumDev\chromium_ub.json)");
    rapidjson::Document doc;
    if (doc.Parse(buffer.data(), buffer.size()).HasParseError())
      break;
    const auto total = doc.Size();
    if (!doc.IsArray())
      break;
    for (size_t i = 0; i < total; ++i) {
      rapidjson::Value &item = doc[i];
      std::string line = Json::toString(item);
      line.insert(0, std::to_string(i).append(" "));
      line += "\n";
      stl::File::WriteFileAddto(
          R"(C:\Users\k34ub\AppData\Roaming\ChromiumDev\list_chromium.txt)",
          line);
    }
  } while (0);
  do { // test
    break;
    std::string input = stl::File::ReadFile(
        R"(C:\Users\k34ub\AppData\Roaming\ChromiumDev\r_out.html)");

    if (input.empty())
      break;

    const std::string script_flag = "b=mb(ub);";
    size_t f = input.find(script_flag);
    if (f == std::string::npos)
      break;

    const std::string source = stl::File::ReadFile(
        R"(C:\Users\k34ub\AppData\Roaming\ChromiumDev\source.json)");
    rapidjson::Document doc;
    std::string buffer = stl::File::ReadFile(
        R"(C:\Users\k34ub\AppData\Roaming\ChromiumDev\chromium.json)");
    if (buffer.empty())
      break;
    if (doc.Parse(buffer.data(), buffer.size()).HasParseError())
      break;
    if (!doc.IsArray())
      break;

    rapidjson::Document source_doc;
    if (source_doc.Parse(source.data(), source.size()).HasParseError())
      break;
    if (!source_doc.IsObject())
      break;

    std::map<size_t, rapidjson::Value &> source_map;

    const auto total = doc.Size();
    for (size_t i = 0; i < total; ++i) {
      const std::string id = std::to_string(i);
      if (!source_doc.HasMember(id.c_str()))
        continue;
      doc[i].CopyFrom(source_doc[id.c_str()], doc.GetAllocator());
    }

    std::string new_content("new_ub=");
    new_content.append(Json::toString(doc));
    new_content.append(";");
    new_content.append("b = mb(new_ub);");
    input.replace(f, script_flag.size(), new_content);

    stl::File::WriteFile(
        R"(C:\Users\k34ub\AppData\Roaming\ChromiumDev\patch.html)", input);

    std::string patch = Json::toString(doc);
    stl::File::WriteFile(
        R"(C:\Users\k34ub\AppData\Roaming\ChromiumDev\patch.json)", patch);
    for (size_t i = 0; i < total; ++i) {
      rapidjson::Value &item = doc[i];
      std::string line = Json::toString(item);
      line.insert(0, std::to_string(i).append(" "));
      line += "\n";
      stl::File::WriteFileAddto(
          R"(C:\Users\k34ub\AppData\Roaming\ChromiumDev\chromium_list.txt)",
          line);
    }

  } while (0);
#endif
  Config::CreateOrGet();
  Startup::GetOrCreate()->Run();
  Config::Destroy();
  return 0;
}
