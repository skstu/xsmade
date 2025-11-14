#include "config.h"
IDeviceFingerprint::IDeviceFingerprint() {
}
IDeviceFingerprint::~IDeviceFingerprint() {
}
bool IDeviceFingerprint::InitPlatform() {
  bool result = false;
  do {
    if (fpsdb_.platform.source.empty())
      break;
    for (const auto &it : fpsdb_.platform.source) {
      if (xscfg_.fps.platform.compare(it.second) == 0) {
        platform_key_ = it.first;
        result = true;
        break;
      }
    }
  } while (0);
  if (result) {
    xscfg_.seed = stl::Time::GoogleTimestamp();

    xs_process_id_t parent_pid = 0;
    xs_sys_process_getpid(&parent_pid);
    xscfg_.startup.startup_pid =
        static_cast<decltype(xscfg_.startup.startup_pid)>(parent_pid);
  }
  return result;
}
bool IDeviceFingerprint::SelectBrowser() {
  bool result = false;
  do {
    if (!fpsdb_.ValidPlatformKey(platform_key_))
      break;
    auto f_browser = fpsdb_.browsers.find(platform_key_);
    if (f_browser == fpsdb_.browsers.end())
      break;
    if (f_browser->second.empty())
      break;
    const bool old_enable = xscfg_.fps.userAgentMetadata.enable;
    const auto &brw =
        f_browser->second[stl::Random::GetRandomValueSeed64<size_t>(
            0, f_browser->second.size() - 1, xscfg_.seed)];
    xscfg_.fps.product = brw.product;
    xscfg_.fps.userAgent = brw.userAgent;
    xscfg_.fps.userAgentMetadata = brw.userAgentMetadata;
    xscfg_.fps.userAgentMetadata.enable = old_enable;
    isGoogleChrome_ = false;
    isMicrosoftEdge_ = false;
    if (xscfg_.fps.userAgent.find("Edg/") != std::string::npos) {
      isMicrosoftEdge_ = true;
    } else {
      isGoogleChrome_ = true;
    }
    result = true;
  } while (0);
  return result;
}
bool IDeviceFingerprint::EnableGpu() {
  bool result = false;
  do {
    if (!fpsdb_.ValidPlatformKey(platform_key_))
      break;
    for (auto it = xscfg_.startup.args.begin();
         it != xscfg_.startup.args.end();) {
      if (it->find("--disable-gpu") != std::string::npos) {
        it = xscfg_.startup.args.erase(it);
        continue;
      }
      ++it;
    }
    if (stl::Random::GetRandomBoolSeed64(xscfg_.seed)) {
      xscfg_.startup.args.emplace_back("--disable-gpu");
    }
    result = true;
  } while (0);
  return result;
}
bool IDeviceFingerprint::UseAngleSwiftshader() {
  bool result = false;
  do {
    if (!fpsdb_.ValidPlatformKey(platform_key_))
      break;
    for (auto it = xscfg_.startup.args.begin();
         it != xscfg_.startup.args.end();) {
      if (it->find("--use-angle=swiftshader") != std::string::npos) {
        it = xscfg_.startup.args.erase(it);
        continue;
      }
      ++it;
    }
    if (stl::Random::GetRandomBoolSeed64(xscfg_.seed)) {
      xscfg_.startup.args.emplace_back("--use-angle=swiftshader");
    }
    result = true;
  } while (0);
  return result;
}
bool IDeviceFingerprint::InitFpsHash() {
  bool result = false;
  do {
    if (!fpsdb_.ValidPlatformKey(platform_key_))
      break;
    //!@ canvas
    xscfg_.fps.canvas.hash.base = stl::Random::GetRandomValueSeed64<double>(
        fpsdb_.hash_canvas.base[0],
        fpsdb_.hash_canvas.base[fpsdb_.hash_canvas.base.size() - 1],
        xscfg_.seed);
    //!@ webgl
    xscfg_.fps.webgl.hash.base = stl::Random::GetRandomValueSeed64<double>(
        fpsdb_.hash_webgl.base[0],
        fpsdb_.hash_webgl.base[fpsdb_.hash_webgl.base.size() - 1], xscfg_.seed);
    //!@ audio
    xscfg_.fps.audio.hash.base = stl::Random::GetRandomValueSeed64<double>(
        fpsdb_.hash_audio.base[0],
        fpsdb_.hash_audio.base[fpsdb_.hash_audio.base.size() - 1], xscfg_.seed);
    //!@ tls
    xscfg_.fps.tlspeet.grease_seed =
        stl::Random::GetRandomValueSeed64<uint16_t>(0x1, 0xff, xscfg_.seed);
    //!@ v8
    xscfg_.fps.v8.hash.base = xscfg_.seed * 1.0;
    //!@ math
    xscfg_.fps.math.hash.base =
        stl::Random::GetRandomValueSeed64<double>(1e-6, 1e-8, xscfg_.seed);

  } while (0);
  return result;
}
const bool &IDeviceFingerprint::IsGoogleChrome() const {
  return isGoogleChrome_;
}
const bool &IDeviceFingerprint::IsMicrosoftEdge() const {
  return isMicrosoftEdge_;
}
bool IDeviceFingerprint::InitFpsUtil() {
  bool result = false;
  do {
    if (!fpsdb_.ValidPlatformKey(platform_key_))
      break;
    xscfg_.fps.do_not_track = stl::Random::GetRandomBoolSeed64(xscfg_.seed);

    auto f_hardwareConcurrency =
        fpsdb_.hardwareConcurrency.source.find(platform_key_);
    if (xscfg_.fps.hardwareConcurrency > 0 &&
        f_hardwareConcurrency != fpsdb_.hardwareConcurrency.source.end()) {
      xscfg_.fps.hardwareConcurrency =
          f_hardwareConcurrency
              ->second[stl::Random::GetRandomValueSeed64<size_t>(
                  0, f_hardwareConcurrency->second.size() - 1, xscfg_.seed)];
    }

    auto f_deviceMemory = fpsdb_.deviceMemory.source.find(platform_key_);
    if (xscfg_.fps.deviceMemory > 0 &&
        f_deviceMemory != fpsdb_.deviceMemory.source.end()) {
      xscfg_.fps.deviceMemory =
          f_deviceMemory->second[stl::Random::GetRandomValueSeed64<size_t>(
              0, f_deviceMemory->second.size() - 1, xscfg_.seed)];
    }

    if (xscfg_.fps.rtt > 0) {
      xscfg_.fps.rtt =
          stl::Random::GetRandomValueSeed64<uint32_t>(20, 300, xscfg_.seed);
    }
    xscfg_.fps.disk.quota = stl::Random::GetRandomValueSeed64<uint64_t>(
        50000000000, 2000000000000, xscfg_.seed); // 50GB~2TB
    xscfg_.fps.disk.usage = stl::Random::GetRandomValueSeed64<uint64_t>(
        5000000000, 1000000000000, xscfg_.seed); // 5GB~1TB

    result = true;
  } while (0);
  return result;
}
bool IDeviceFingerprint::InitCdmRegistry() {
  bool result = false;
  do {
    if (!fpsdb_.ValidPlatformKey(platform_key_))
      break;
    auto f_cdm = fpsdb_.cdmRegistry.find(platform_key_);
    if (f_cdm == fpsdb_.cdmRegistry.end())
      break;
    xscfg_.fps.cdmRegistry.allowlist.clear();
    for (const auto &cdm : f_cdm->second) {
      auto isEdge = cdm.key_system.find("microsoft") != std::string::npos;
      if (isMicrosoftEdge_ && isEdge) {
        xscfg_.fps.cdmRegistry.allowlist.emplace_back(cdm);
        continue;
      }
      if (isGoogleChrome_ && !isEdge) {
        xscfg_.fps.cdmRegistry.allowlist.emplace_back(cdm);
        continue;
      }
    }
    result = true;
  } while (0);
  return result;
}
bool IDeviceFingerprint::InitFont() {
  bool result = false;
  do {
    if (!fpsdb_.ValidPlatformKey(platform_key_))
      break;
    auto f_font = fpsdb_.font.find(platform_key_);
    if (f_font == fpsdb_.font.end())
      break;
    xscfg_.fps.font.allowlist.clear();
    std::vector<std::string> fonts = f_font->second.family;
    const size_t total = fonts.size();
    size_t remove_count =
        stl::Random::GetRandomValue<int>(1, static_cast<int>(total / 2) - 1);
    std::shuffle(fonts.begin(), fonts.end(), std::mt19937_64(xscfg_.seed));
    remove_count = std::min(remove_count, fonts.size());
    for (size_t i = 0; i < remove_count; ++i) {
      fonts.erase(fonts.begin());
    }
    for (const auto &fontFamily : fonts) {
      xscfg_.fps.font.allowlist.emplace(fontFamily);
    }
    result = true;
  } while (0);
  return result;
}
bool IDeviceFingerprint::InitATI() {
  bool result = false;
  do {
    if (!fpsdb_.ValidPlatformKey(platform_key_))
      break;
    const bool old_contextAttributes_enable =
        xscfg_.fps.webgl.contextAttributes.enable;
    const bool old_shaderPrecisionFormat_enable =
        xscfg_.fps.webgl.shaderPrecisionFormat.enable;
    auto f_webgl_device = fpsdb_.webgl.source.find(platform_key_);
    if (f_webgl_device == fpsdb_.webgl.source.end())
      break;
    if (f_webgl_device->second.empty())
      break;
    const auto &dev =
        f_webgl_device->second[stl::Random::GetRandomValueSeed64<size_t>(
            0, f_webgl_device->second.size() - 1, xscfg_.seed)];
    xscfg_.fps.webgl.getParameter = dev.getParameter;
    xscfg_.fps.webgl.contextAttributes = dev.contextAttributes;
    xscfg_.fps.webgl.shaderPrecisionFormat = dev.shaderPrecisionFormat;
    xscfg_.fps.webgl.contextAttributes.enable = old_contextAttributes_enable;
    xscfg_.fps.webgl.shaderPrecisionFormat.enable =
        old_shaderPrecisionFormat_enable;

    result = true;
  } while (0);
  return result;
}
bool IDeviceFingerprint::InitScreen() {
  bool result = false;
  do {
    if (!fpsdb_.ValidPlatformKey(platform_key_))
      break;
    auto f_screen = fpsdb_.screen.source.find(platform_key_);
    if (f_screen == fpsdb_.screen.source.end())
      break;
    if (f_screen->second.empty())
      break;
    const bool old_enable = xscfg_.fps.screen.enable;
    auto screen_info =
        f_screen->second[stl::Random::GetRandomValueSeed64<size_t>(
            0, f_screen->second.size() - 1, xscfg_.seed)];
    xscfg_.fps.screen = screen_info;
    xscfg_.fps.screen.enable = old_enable;

    result = true;
  } while (0);
  return result;
}
bool IDeviceFingerprint::InitVoiceAndLanguages() {
  bool result = false;
  do {
    if (!fpsdb_.ValidPlatformKey(platform_key_))
      break;
    const auto tz = xscfg_.dynFpsInfo.ipinfo.timezone;
    if (tz.empty()) {
      xscfg_.fps.languages.clear();
      xscfg_.fps.languages.emplace_back("en-US");
      xscfg_.fps.languages.emplace_back("en");
    } else {
      xscfg_.fps.languages.clear();
      xscfg_.fps.languages = fpsdb_.tzlang.GetLanguages(tz);
    }
    xscfg_.fps.voice.datas.clear();
    if (isMicrosoftEdge_) {
      for (const auto &v : fpsdb_.voice) {
        if (v.name.find("Microsoft") != std::string::npos) {
          chromium::xsiumio::IXSiumio::Fingerprint::Voice::Data data;
          data.lang = v.lang;
          data.name = v.name;
          xscfg_.fps.voice.datas.emplace_back(data);
        }
      }
    } else {
      for (const auto &v : fpsdb_.voice) {
        if (v.name.find("Microsoft") == std::string::npos) {
          chromium::xsiumio::IXSiumio::Fingerprint::Voice::Data data;
          data.lang = v.lang;
          data.name = v.name;
          xscfg_.fps.voice.datas.emplace_back(data);
        }
      }
    }
    result = true;
  } while (0);
  return result;
}