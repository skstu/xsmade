#include "config.h"
#ifdef __OSWIN__
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
// int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR __cmdline__,
//                      int cmdshow)
int main(int argc, char *args[])
#elif defined(__OSLINUX__)
int main(int argc, char *args[])
#endif
{
  if (0 == xs_sys_process_already_exists(0))
    return 1;

  // do {
  //   std::map<std::string, std::string> files, dirs;
  //   stl::Directory::Enum(
  //       R"(C:\Users\k34ub\Desktop\AdsModes\138.0.7204.158\model_parts)",
  //       dirs, files, false);
  //   std::set<double> canvas, audio, webgl;
  //   for (auto &f : files) {
  //     do {
  //       auto fb = stl::File::ReadFile(f.second);
  //       if (fb.empty())
  //         break;
  //       rapidjson::Document doc;
  //       if (doc.Parse(fb.c_str(), fb.size()).HasParseError())
  //         break;
  //       if (!doc.IsObject())
  //         break;
  //       if (!doc.HasMember("xsiumio") || !doc["xsiumio"].IsObject())
  //         break;
  //       canvas.emplace(doc["xsiumio"]["fingerprint"]["canvas"]["hash"]["base"]
  //                          .GetDouble());
  //       webgl.emplace(
  //           doc["xsiumio"]["fingerprint"]["webgl"]["hash"]["base"].GetDouble());
  //       audio.emplace(
  //           doc["xsiumio"]["fingerprint"]["audio"]["hash"]["base"].GetDouble());
  //     } while (0);
  //   }

  //   double max_canvas(0.0), min_canvas(0.0), max_webgl(0.0), min_webgl(0.0),
  //       max_audio(0.0), min_audio(0.0);
  //   std::string canvas_output, webgl_output, audio_output;
  //   for (const auto &v : canvas) {
  //     if (v > max_canvas)
  //       max_canvas = v;
  //     if (v < min_canvas || !min_canvas)
  //       min_canvas = v;
  //     canvas_output.append(stl::Common::DoubleToString(v)).append(",");
  //   }
  //   canvas_output.append("\n")
  //       .append(stl::Common::DoubleToString(min_canvas))
  //       .append("\n")
  //       .append(stl::Common::DoubleToString(max_canvas));

  //   for (const auto &v : webgl) {
  //     if (v > max_webgl)
  //       max_webgl = v;
  //     if (v < min_webgl || !min_webgl)
  //       min_webgl = v;
  //     webgl_output.append(stl::Common::DoubleToString(v)).append(",");
  //   }
  //   webgl_output.append("\n")
  //       .append(stl::Common::DoubleToString(min_webgl))
  //       .append("\n")
  //       .append(stl::Common::DoubleToString(max_webgl));

  //   for (const auto &v : audio) {
  //     if (v > max_audio)
  //       max_audio = v;
  //     if (v < min_audio || !min_audio)
  //       min_audio = v;
  //     audio_output.append(stl::Common::DoubleToString(v)).append(",");
  //   }
  //   audio_output.append("\n")
  //       .append(stl::Common::DoubleToString(min_audio))
  //       .append("\n")
  //       .append(stl::Common::DoubleToString(max_audio));

  //   stl::File::WriteFile(R"(C:\Users\k34ub\Desktop\AdsModes\canvas.txt)",
  //                        canvas_output);
  //   stl::File::WriteFile(R"(C:\Users\k34ub\Desktop\AdsModes\audio.txt)",
  //                        audio_output);
  //   stl::File::WriteFile(R"(C:\Users\k34ub\Desktop\AdsModes\webgl.txt)",
  //                        webgl_output);
  //   auto sss = 0;
  // } while (0);

  char *__cmdline__ = nullptr;
  size_t __cmdline_size__ = 0;
  xs_sys_get_commandline(&__cmdline__, &__cmdline_size__);
  if (!__cmdline__)
    return 0;
  stl::tfCommandLines cmdline = stl::CmdLine::ParserCommandLines(
      std::string(__cmdline__, __cmdline_size__), false);
  xs_sys_free((void **)&__cmdline__);

  auto f_mode = cmdline.find("--mode");
  Config::CreateOrGet();
  if (f_mode == cmdline.end()) {
    Startup::GetOrCreate()->Run();
  } else if (f_mode->second == "model_level_0") {
    Startup::GetOrCreate(RunMode::kModelLevel0)->Run();
  } else if (f_mode->second == "model_level_1") {
    Startup::GetOrCreate(RunMode::kModelLevel1)->Run();
  } else if (f_mode->second == "model_level_2") {
    Startup::GetOrCreate(RunMode::kModelLevel2)->Run();
  } else if (f_mode->second == "model_level_3") {
    Startup::GetOrCreate(RunMode::kModelLevel3)->Run();
  } else if (f_mode->second == "production" || f_mode->second == "release") {
    Startup::GetOrCreate(RunMode::kProductionModel)->Run();
  } else {
    Startup::GetOrCreate()->Run();
  }
  Config::Destroy();
  return 0;
}
