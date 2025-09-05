#include "config.h"
#if 0
void Startup::ConfigureNormal() {
  do {
#if _DEBUG
    const std::string project_path = Config::CreateOrGet()->GetCurrentDir() +
                                     "\\browser\\chromium\\138.0.7204.158\\";
#else
    const std::string project_path = Config::CreateOrGet()->GetCurrentDir();
#endif
    const std::string xsiumio_path =
        project_path + "\\" + chromium::xsiumio::kObjectKey + ".json";
    std::string xsiumio_buffer;
    if (!stl::File::Exists(xsiumio_path))
      break;
    xsiumio_buffer = stl::File::ReadFile(xsiumio_path);
    rapidjson::Document doc;
    if (doc.Parse(xsiumio_buffer.c_str(), xsiumio_buffer.size())
            .HasParseError())
      break;
    if (!doc.HasMember(chromium::xsiumio::kObjectKey) ||
        !doc[chromium::xsiumio::kObjectKey].IsObject())
      break;
    xsiumio << doc[chromium::xsiumio::kObjectKey];
    { //!@ develop configure
      std::string curl_proxy_string;
      GenerateDynamicProxyInfo(curl_proxy_string,
                               xsiumio.proxy.credentials_url);
      LOG_INFO("Chromium using proxy: %s",
               xsiumio.proxy.credentials_url.c_str());
      std::cout << "Chromium using proxy: " << xsiumio.proxy.credentials_url
                << std::endl;
      do {
        ConfigDynamicInfo(xsiumio.proxy_info_request_url, curl_proxy_string,
                          xsiumio);
        xsiumio.webrtcIPHandling.public_ip = xsiumio.myipyunlogincom.Ip;
        xsiumio.fps.timezone.id = xsiumio.myipyunlogincom.LocalTime;

        LOG_INFO("Public IP: %s", xsiumio.webrtcIPHandling.public_ip.c_str());
        LOG_INFO("Timezone ID: %s", xsiumio.fps.timezone.id.c_str());
        std::cout << "Public IP: " << xsiumio.webrtcIPHandling.public_ip
                  << std::endl;
        std::cout << "Timezone ID: " << xsiumio.fps.timezone.id << std::endl;

        //!@ configure xsiumio fps
        const std::vector<int> cpu_cores = {2,  4,  6,  8,  12, 16, 20,
                                            24, 28, 32, 36, 48, 64, 96};
        const std::vector<unsigned long long> mem_sizes_g = {
            2, 4, 6, 8, 12, 16, 24, 32, 48, 64, 96, 128, 192, 256};
        xsiumio.fps.hardwareConcurrency =
            cpu_cores[stl::Random::GetRandomValue<int>(0, 13)];
        xsiumio.fps.deviceMemory =
            mem_sizes_g[stl::Random::GetRandomValue<int>(0, 13)];
        xsiumio.fps.canvas.hash.random = false;
        xsiumio.fps.canvas.hash.base =
            stl::Random::GetRandomValue<double>(0.00001, 0.00999);
        xsiumio.fps.webgl.hash.random = false;
        xsiumio.fps.webgl.hash.base =
            stl::Random::GetRandomValue<double>(0.00001, 100.00001);
        xsiumio.fps.audio.hash.random = false;
        xsiumio.fps.audio.hash.base =
            stl::Random::GetRandomValue<double>(0.00001, 100.00001);
        xsiumio.fps.webgl.hash.random = false;
        xsiumio.fps.webgl.hash.base =
            stl::Random::GetRandomValue<double>(0.00001, 100.00001);
        for (auto &param : xsiumio.fps.webgl.getParameter) {
          switch (param.first) {
          case 3379:
          case 34024:
          case 34076:
          case 34047:
          case 34921:
          case 34930:
          case 35660:
          case 35661:
          case 36347:
          case 36348:
          case 36349:
          case 3410:
          case 3411:
          case 3412:
          case 3413:
          case 3414: {
            long current = strtol(param.second.c_str(), nullptr, 10);
            if (current <= 2)
              continue;
            {
              current = stl::Random::GetRandomValue<long>(
                  static_cast<long>(current / 2), current);
              param.second = std::to_string(current);
            }
          } break;
          default:
            break;
          } /// switch
        }
        xsiumio.fps.font.hash.random = false;
        xsiumio.fps.font.hash.base = 1.0f;
        std::set<std::string> font_allowlist = {"arial",
                                                "bahnschrift",
                                                "calibri",
                                                "cambria",
                                                "cambria math",
                                                "candara",
                                                "comic sans ms",
                                                "consolas",
                                                "constantia",
                                                "corbel",
                                                "courier new",
                                                "ebrima",
                                                "franklin gothic",
                                                "gabriola",
                                                "gadugi",
                                                "georgia",
                                                "impact",
                                                "javanese text",
                                                "lucida console",
                                                "lucida sans unicode",
                                                "malgun gothic",
                                                "marlett",
                                                "microsoft himalaya",
                                                "microsoft jhenghei",
                                                "microsoft jhenghei ui",
                                                "microsoft new tai lue",
                                                "microsoft phagspa",
                                                "microsoft sans serif",
                                                "microsoft tai le",
                                                "microsoft yahei",
                                                "microsoft yi baiti",
                                                "mingliu-extb",
                                                "mingliu_hkscs-extb",
                                                "mongolian baiti",
                                                "ms gothic",
                                                "ms pgothic",
                                                "ms ui gothic",
                                                "mv boli",
                                                "myanmar text",
                                                "palatino linotype",
                                                "pmingliu-extb",
                                                "segoe print",
                                                "segoe script",
                                                "segoe ui",
                                                "segoe ui emoji",
                                                "segoe ui symbol",
                                                "simsun",
                                                "simsun-extb",
                                                "sitka small",
                                                "sylfaen",
                                                "symbol",
                                                "trebuchet ms",
                                                "verdana",
                                                "webdings",
                                                "yu gothic",
                                                "Arial",
                                                "Verdana",
                                                "Tahoma",
                                                "Times New Roman",
                                                "Courier New",
                                                "Georgia",
                                                "Impact",
                                                "Comic Sans MS",
                                                "Lucida Console"};

        {
          std::uint64_t seed =
              stl::Time::TimeStamp<std::chrono::microseconds>();
          std::vector<std::string> fonts(font_allowlist.begin(),
                                         font_allowlist.end());
          std::mt19937_64 rng(seed);
          std::uniform_int_distribution<int> dist_count(5, 20);
          size_t remove_count = static_cast<size_t>(dist_count(rng));
          std::shuffle(fonts.begin(), fonts.end(), rng);
          remove_count = std::min(remove_count, fonts.size());
          for (size_t i = 0; i < remove_count; ++i) {
            font_allowlist.erase(fonts[i]);
          }
          xsiumio.fps.font.allowlist.clear();
          for (const auto &font : font_allowlist) {
            xsiumio.fps.font.allowlist.emplace(font);
          }
        }

      } while (0);
    }
  } while (0);
}
#endif