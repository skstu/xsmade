#include "config.h"

ModelLevel3::ModelLevel3() {
}
ModelLevel3::~ModelLevel3() {
}
void ModelLevel3::Release() const {
  delete this;
}
const char *ModelLevel3::GetModelIdentify() const {
  return "Model-Level-3";
}
bool ModelLevel3::GetModel(chromium::xsiumio::IXSiumio &model) const {
  bool result = false;
  std::lock_guard<std::mutex> lck(*mtx_);
  const auto *fpsdb = Startup::GetOrCreate()->GetFpsdb();
  do {
    if (!fpsdb)
      break;
    model.timestamp = stl::Time::TimeStamp<std::chrono::microseconds>();
    model.identify = model.timestamp;
    std::mt19937_64 model_rng(model.timestamp);
    model.fps.rtt = stl::Random::GetRandomValue<uint32_t>(100, 500);
    model.fps.disk.quota =
        stl::Random::GetRandomValue<uint64_t>(1000000000, 5000000000);
    model.fps.disk.usage =
        stl::Random::GetRandomValue<uint64_t>(100000000, 500000000);

    model.fps.canvas.hash.random = false;
    model.fps.canvas.hash.base =
        fpsdb->hash_canvas.base[stl::Random::GetRandomValue<size_t>(
            0, fpsdb->hash_canvas.base.size() - 1)];
    model.fps.webgl.hash.random = false;
    model.fps.webgl.hash.base =
        fpsdb->hash_webgl.base[stl::Random::GetRandomValue<size_t>(
            0, fpsdb->hash_webgl.base.size() - 1)];
    model.fps.audio.hash.random = false;
    model.fps.audio.hash.base =
        fpsdb->hash_audio.base[stl::Random::GetRandomValue<size_t>(
            0, fpsdb->hash_audio.base.size() - 1)];

    const int platform_key = 0;
    // stl::Random::GetRandomValue<size_t>(0, fpsdb->platform.source.size() -
    // 1);
    model.fps.platform = "Win32";
    //*stl::Common::GetMapValueByKey(fpsdb->platform.source, platform_key);

    auto f_hardwareConcurrency =
        fpsdb->hardwareConcurrency.source.find(platform_key);
    if (f_hardwareConcurrency != fpsdb->hardwareConcurrency.source.end()) {
      model.fps.hardwareConcurrency =
          f_hardwareConcurrency->second[stl::Random::GetRandomValue<size_t>(
              0, f_hardwareConcurrency->second.size() - 1)];
    }

    auto f_deviceMemory = fpsdb->deviceMemory.source.find(platform_key);
    if (f_deviceMemory != fpsdb->deviceMemory.source.end()) {
      model.fps.deviceMemory =
          f_deviceMemory->second[stl::Random::GetRandomValue<size_t>(
              0, f_deviceMemory->second.size() - 1)];
    }

    auto f_userAgent = fpsdb->userAgent.source.find(platform_key);
    if (f_userAgent != fpsdb->userAgent.source.end()) {
      model.fps.userAgent =
          f_userAgent->second[stl::Random::GetRandomValue<size_t>(
              0, f_userAgent->second.size() - 1)];
    }

    auto f_userAgentMetadata =
        fpsdb->userAgentMetadata.source.find(platform_key);
    if (f_userAgentMetadata != fpsdb->userAgentMetadata.source.end()) {
      auto &v = f_userAgentMetadata->second[stl::Random::GetRandomValue<size_t>(
          0, f_userAgentMetadata->second.size() - 1)];
      model.fps.userAgentMetadata.model = v.model;
      model.fps.userAgentMetadata.brand_full_version_list.clear();
      for (const auto &brand : v.brand_full_version_list) {
        chromium::xsiumio::IXSiumio::Fingerprint::UserAgentMetadata::
            Brand_full_version brand_full_version;
        brand_full_version.brand = brand.brand;
        brand_full_version.version = brand.version;
        model.fps.userAgentMetadata.brand_full_version_list.push_back(
            brand_full_version);
      }
      model.fps.userAgentMetadata.brand_version_list.clear();
      for (const auto &brand : v.brand_version_list) {
        chromium::xsiumio::IXSiumio::Fingerprint::UserAgentMetadata::
            Brand_version brand_version;
        brand_version.brand = brand.brand;
        brand_version.version = brand.version;
        model.fps.userAgentMetadata.brand_version_list.push_back(brand_version);
      }
      model.fps.userAgentMetadata.full_version = v.full_version;
      model.fps.userAgentMetadata.platform = v.platform;
      model.fps.userAgentMetadata.platform_version = v.platform_version;
      model.fps.userAgentMetadata.architecture = v.architecture;
      model.fps.userAgentMetadata.mobile = v.mobile;
      model.fps.userAgentMetadata.bitness = v.bitness;
      model.fps.userAgentMetadata.wow64 = v.wow64;
      model.fps.userAgentMetadata.form_factors.clear();
      for (const auto &form_factor : v.form_factors) {
        model.fps.userAgentMetadata.form_factors.emplace_back(form_factor);
      }
    }

    const std::vector<std::string> powerPreferences = {
        "default", "high-performance", "low-power"};
    model.fps.webgl.contextAttributes.powerPreference =
        powerPreferences[stl::Random::GetRandomValue<size_t>(
            0, powerPreferences.size() - 1)];
    model.fps.webgl.contextAttributes.xrCompatible =
        stl::Random::GetRandomBool();
    model.fps.webgl.contextAttributes.enable = stl::Random::GetRandomBool();
    model.fps.webgl.contextAttributes.alpha = stl::Random::GetRandomBool();
    model.fps.webgl.contextAttributes.antialias = stl::Random::GetRandomBool();
    model.fps.webgl.contextAttributes.depth = stl::Random::GetRandomBool();
    model.fps.webgl.contextAttributes.desynchronized =
        stl::Random::GetRandomBool();
    model.fps.webgl.contextAttributes.failIfMajorPerformanceCaveat =
        stl::Random::GetRandomBool();
    model.fps.webgl.contextAttributes.premultipliedAlpha =
        stl::Random::GetRandomBool();
    model.fps.webgl.contextAttributes.preserveDrawingBuffer =
        stl::Random::GetRandomBool();
    model.fps.webgl.contextAttributes.stencil = stl::Random::GetRandomBool();
    model.fps.webgl.contextAttributes.xrCompatible =
        stl::Random::GetRandomBool();

    model.fps.webgl.shaderPrecisionFormat.enable = stl::Random::GetRandomBool();
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF0.rangeMin =
        stl::Random::GetRandomValue<int32_t>(-100, 100);
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF0.rangeMax =
        stl::Random::GetRandomValue<int32_t>(100, 200);
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF0.precision =
        stl::Random::GetRandomValue<int32_t>(0, 10);
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF1.rangeMin =
        stl::Random::GetRandomValue<int32_t>(-100, 100);
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF1.rangeMax =
        stl::Random::GetRandomValue<int32_t>(100, 200);
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF1.precision =
        stl::Random::GetRandomValue<int32_t>(0, 10);
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF2.rangeMin =
        stl::Random::GetRandomValue<int32_t>(-100, 100);
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF2.rangeMax =
        stl::Random::GetRandomValue<int32_t>(100, 200);
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF2.precision =
        stl::Random::GetRandomValue<int32_t>(0, 10);
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF3.rangeMin =
        stl::Random::GetRandomValue<int32_t>(-100, 100);
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF3.rangeMax =
        stl::Random::GetRandomValue<int32_t>(100, 200);
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF3.precision =
        stl::Random::GetRandomValue<int32_t>(0, 10);
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF4.rangeMin =
        stl::Random::GetRandomValue<int32_t>(-100, 100);
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF4.rangeMax =
        stl::Random::GetRandomValue<int32_t>(100, 200);
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF4.precision =
        stl::Random::GetRandomValue<int32_t>(0, 10);
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF5.rangeMin =
        stl::Random::GetRandomValue<int32_t>(-100, 100);
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF5.rangeMax =
        stl::Random::GetRandomValue<int32_t>(100, 200);
    model.fps.webgl.shaderPrecisionFormat._8B30._8DF5.precision =
        stl::Random::GetRandomValue<int32_t>(0, 10);

    model.fps.webgl.shaderPrecisionFormat._8B31._8DF0.rangeMin =
        stl::Random::GetRandomValue<int32_t>(-100, 100);
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF0.rangeMax =
        stl::Random::GetRandomValue<int32_t>(100, 200);
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF0.precision =
        stl::Random::GetRandomValue<int32_t>(0, 10);
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF1.rangeMin =
        stl::Random::GetRandomValue<int32_t>(-100, 100);
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF1.rangeMax =
        stl::Random::GetRandomValue<int32_t>(100, 200);
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF1.precision =
        stl::Random::GetRandomValue<int32_t>(0, 10);
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF2.rangeMin =
        stl::Random::GetRandomValue<int32_t>(-100, 100);
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF2.rangeMax =
        stl::Random::GetRandomValue<int32_t>(100, 200);
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF2.precision =
        stl::Random::GetRandomValue<int32_t>(0, 10);
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF3.rangeMin =
        stl::Random::GetRandomValue<int32_t>(-100, 100);
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF3.rangeMax =
        stl::Random::GetRandomValue<int32_t>(100, 200);
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF3.precision =
        stl::Random::GetRandomValue<int32_t>(0, 10);
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF4.rangeMin =
        stl::Random::GetRandomValue<int32_t>(-100, 100);
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF4.rangeMax =
        stl::Random::GetRandomValue<int32_t>(100, 200);
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF4.precision =
        stl::Random::GetRandomValue<int32_t>(0, 10);
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF5.rangeMin =
        stl::Random::GetRandomValue<int32_t>(-100, 100);
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF5.rangeMax =
        stl::Random::GetRandomValue<int32_t>(100, 200);
    model.fps.webgl.shaderPrecisionFormat._8B31._8DF5.precision =
        stl::Random::GetRandomValue<int32_t>(0, 10);

    for (auto &it : model.fps.webgl.getParameter) {
      switch (it.first) {
      case 3379: {
        auto f_3379 = fpsdb->webgl.getParameter._3379_.find(platform_key);
        if (f_3379 == fpsdb->webgl.getParameter._3379_.end())
          break;
        it.second =
            std::to_string(f_3379->second[stl::Random::GetRandomValue<size_t>(
                0, f_3379->second.size() - 1)]);
      } break;
      case 3386: {
        auto f_3386 = fpsdb->webgl.getParameter._3386_.find(platform_key);
        if (f_3386 == fpsdb->webgl.getParameter._3386_.end())
          break;
        it.second =
            std::to_string(f_3386->second[stl::Random::GetRandomValue<size_t>(
                0, f_3386->second.size() - 1)]);
      } break;
      case 3410: {
        auto f_3410 = fpsdb->webgl.getParameter._3410_.find(platform_key);
        if (f_3410 == fpsdb->webgl.getParameter._3410_.end())
          break;
        it.second =
            std::to_string(f_3410->second[stl::Random::GetRandomValue<size_t>(
                0, f_3410->second.size() - 1)]);
      } break;
      case 3411: {
        auto f_3411 = fpsdb->webgl.getParameter._3411_.find(platform_key);
        if (f_3411 == fpsdb->webgl.getParameter._3411_.end())
          break;
        it.second =
            std::to_string(f_3411->second[stl::Random::GetRandomValue<size_t>(
                0, f_3411->second.size() - 1)]);
      } break;
      case 3412: {
        auto f_3412 = fpsdb->webgl.getParameter._3412_.find(platform_key);
        if (f_3412 == fpsdb->webgl.getParameter._3412_.end())
          break;
        it.second =
            std::to_string(f_3412->second[stl::Random::GetRandomValue<size_t>(
                0, f_3412->second.size() - 1)]);
      } break;
      case 3413: {
        auto f_3413 = fpsdb->webgl.getParameter._3413_.find(platform_key);
        if (f_3413 == fpsdb->webgl.getParameter._3413_.end())
          break;
        it.second =
            std::to_string(f_3413->second[stl::Random::GetRandomValue<size_t>(
                0, f_3413->second.size() - 1)]);
      } break;
      case 3414: {
        auto f_3414 = fpsdb->webgl.getParameter._3414_.find(platform_key);
        if (f_3414 == fpsdb->webgl.getParameter._3414_.end())
          break;
        it.second =
            std::to_string(f_3414->second[stl::Random::GetRandomValue<size_t>(
                0, f_3414->second.size() - 1)]);
      } break;
      case 3415: {
        auto f_3415 = fpsdb->webgl.getParameter._3415_.find(platform_key);
        if (f_3415 == fpsdb->webgl.getParameter._3415_.end())
          break;
        it.second =
            std::to_string(f_3415->second[stl::Random::GetRandomValue<size_t>(
                0, f_3415->second.size() - 1)]);
      } break;
      case 34024: {
        auto f_34024 = fpsdb->webgl.getParameter._34024_.find(platform_key);
        if (f_34024 == fpsdb->webgl.getParameter._34024_.end())
          break;
        it.second =
            std::to_string(f_34024->second[stl::Random::GetRandomValue<size_t>(
                0, f_34024->second.size() - 1)]);
      } break;
      case 34047: {
        auto f_34047 = fpsdb->webgl.getParameter._34047_.find(platform_key);
        if (f_34047 == fpsdb->webgl.getParameter._34047_.end())
          break;
        it.second =
            std::to_string(f_34047->second[stl::Random::GetRandomValue<size_t>(
                0, f_34047->second.size() - 1)]);
      } break;
      case 34076: {
        auto f_34076 = fpsdb->webgl.getParameter._34076_.find(platform_key);
        if (f_34076 == fpsdb->webgl.getParameter._34076_.end())
          break;
        it.second =
            std::to_string(f_34076->second[stl::Random::GetRandomValue<size_t>(
                0, f_34076->second.size() - 1)]);
      } break;
      case 34921: {
        auto f_34921 = fpsdb->webgl.getParameter._34921_.find(platform_key);
        if (f_34921 == fpsdb->webgl.getParameter._34921_.end())
          break;
        it.second =
            std::to_string(f_34921->second[stl::Random::GetRandomValue<size_t>(
                0, f_34921->second.size() - 1)]);
      } break;
      case 34930: {
        auto f_34930 = fpsdb->webgl.getParameter._34930_.find(platform_key);
        if (f_34930 == fpsdb->webgl.getParameter._34930_.end())
          break;
        it.second =
            std::to_string(f_34930->second[stl::Random::GetRandomValue<size_t>(
                0, f_34930->second.size() - 1)]);
      } break;
      case 35660: {
        auto f_35660 = fpsdb->webgl.getParameter._35660_.find(platform_key);
        if (f_35660 == fpsdb->webgl.getParameter._35660_.end())
          break;
        it.second =
            std::to_string(f_35660->second[stl::Random::GetRandomValue<size_t>(
                0, f_35660->second.size() - 1)]);
      } break;
      case 35661: {
        auto f_35661 = fpsdb->webgl.getParameter._35661_.find(platform_key);
        if (f_35661 == fpsdb->webgl.getParameter._35661_.end())
          break;
        it.second =
            std::to_string(f_35661->second[stl::Random::GetRandomValue<size_t>(
                0, f_35661->second.size() - 1)]);
      } break;
      case 36347: {
        auto f_36347 = fpsdb->webgl.getParameter._36347_.find(platform_key);
        if (f_36347 == fpsdb->webgl.getParameter._36347_.end())
          break;
        it.second =
            std::to_string(f_36347->second[stl::Random::GetRandomValue<size_t>(
                0, f_36347->second.size() - 1)]);
      } break;
      case 36348: {
        auto f_36348 = fpsdb->webgl.getParameter._36348_.find(platform_key);
        if (f_36348 == fpsdb->webgl.getParameter._36348_.end())
          break;
        it.second =
            std::to_string(f_36348->second[stl::Random::GetRandomValue<size_t>(
                0, f_36348->second.size() - 1)]);
      } break;
      case 36349: {
        auto f_36349 = fpsdb->webgl.getParameter._36349_.find(platform_key);
        if (f_36349 == fpsdb->webgl.getParameter._36349_.end())
          break;
        it.second =
            std::to_string(f_36349->second[stl::Random::GetRandomValue<size_t>(
                0, f_36349->second.size() - 1)]);
      } break;
      case 33901: {
        auto f_33901 = fpsdb->webgl.getParameter._33901_.find(platform_key);
        if (f_33901 == fpsdb->webgl.getParameter._33901_.end())
          break;
        it.second = f_33901->second[stl::Random::GetRandomValue<size_t>(
            0, f_33901->second.size() - 1)];
      } break;
      case 37445: {
        auto f_devices = fpsdb->webgl.getParameter._devices_.find(platform_key);
        if (f_devices == fpsdb->webgl.getParameter._devices_.end())
          break;
        it.second = f_devices
                        ->second[stl::Random::GetRandomValue<size_t>(
                            0, f_devices->second.size() - 1)]
                        ._37445_;
      } break;
      case 37446: {
        auto f_devices = fpsdb->webgl.getParameter._devices_.find(platform_key);
        if (f_devices == fpsdb->webgl.getParameter._devices_.end())
          break;
        it.second = f_devices
                        ->second[stl::Random::GetRandomValue<size_t>(
                            0, f_devices->second.size() - 1)]
                        ._37446_;
      } break;
      case 7936: {
        auto f_devices = fpsdb->webgl.getParameter._devices_.find(platform_key);
        if (f_devices == fpsdb->webgl.getParameter._devices_.end())
          break;
        it.second = f_devices
                        ->second[stl::Random::GetRandomValue<size_t>(
                            0, f_devices->second.size() - 1)]
                        ._7936_;
      } break;
      case 7937: {
        auto f_devices = fpsdb->webgl.getParameter._devices_.find(platform_key);
        if (f_devices == fpsdb->webgl.getParameter._devices_.end())
          break;
        it.second = f_devices
                        ->second[stl::Random::GetRandomValue<size_t>(
                            0, f_devices->second.size() - 1)]
                        ._7937_;
      } break;
      default:
        break;
      }
    }

    auto f_screen = fpsdb->screen.source.find(platform_key);
    if (f_screen != fpsdb->screen.source.end()) {
      auto screen_info = f_screen->second[stl::Random::GetRandomValue<size_t>(
          0, f_screen->second.size() - 1)];

      model.fps.screen.devicePixelRatio = screen_info.devicePixelRatio <= 0
                                              ? 1.0
                                              : screen_info.devicePixelRatio;
      model.fps.screen.width = screen_info.width;
      model.fps.screen.height = screen_info.height;
      model.fps.screen.colorDepth = screen_info.colorDepth;
      model.fps.screen.pixelDepth = screen_info.pixelDepth;
      model.fps.screen.availLeft = screen_info.availLeft;
      model.fps.screen.availTop = screen_info.availTop;
      model.fps.screen.availHeight =
          screen_info.availHeight * model.fps.screen.devicePixelRatio;
      model.fps.screen.availWidth =
          screen_info.availWidth * model.fps.screen.devicePixelRatio;
    }

    auto f_font = fpsdb->font.find(platform_key);
    if (f_font != fpsdb->font.end()) {
      model.fps.font.allowlist.clear();

      std::vector<std::string> fonts = f_font->second.family;
      const size_t total = fonts.size();
      size_t remove_count =
          stl::Random::GetRandomValue<int>(1, static_cast<int>(total / 2) - 1);
      std::shuffle(fonts.begin(), fonts.end(), model_rng);
      remove_count = std::min(remove_count, fonts.size());
      for (size_t i = 0; i < remove_count; ++i) {
        fonts.erase(fonts.begin());
      }
      for (const auto &fontFamily : fonts) {
        model.fps.font.allowlist.emplace(fontFamily);
      }
    }

    { //!@ Voice
      auto voice = fpsdb->voice;
      std::shuffle(voice.begin(), voice.end(), model_rng);
      size_t get_count = 12 /*stl::Random::GetRandomValue<int>(
           static_cast<int>(voice.size() / 2), voice.size() - 1)*/
          ;
      model.fps.voice.datas.clear();
      for (size_t i = 0; i < get_count; ++i) {
        if (i >= voice.size())
          break;
        chromium::xsiumio::IXSiumio::Fingerprint::Voice::Data data;
        data.lang = voice[i].lang;
        data.name = voice[i].name;
        model.fps.voice.datas.emplace_back(data);
      }
    }

#if _DEBUG
    rapidjson::Document doc(rapidjson::Type::kObjectType);
    model >> doc;
    std::string json = Json::toString(doc);
    stl::File::WriteFile(Config::CreateOrGet()->GetCurrentDir() + "/model.json",
                         json);
#endif
    result = true;
  } while (0);
  return result;
}
