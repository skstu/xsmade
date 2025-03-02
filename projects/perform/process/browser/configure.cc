#include <perform.h>

Configure::Configure() {
  *this << source_;
}
Configure::Configure(const std::string &input) {
  *this << input;
}
Configure::~Configure() {
}
bool Configure::empty() const {
  return source_.empty();
}
bool Configure::Default() const {
  return rule_.IsDefault();
}
void Configure::operator=(const Configure &obj) {
  std::string tmp;
  obj >> tmp;
  *this << tmp;
}
void Configure::operator<<(const std::string &input) {
  rapidjson::Document docSource, docInput;
  do {
    if (docSource.Parse(source_.data(), source_.size()).HasParseError()) {
      break;
    }
    if (!docSource.IsObject() || docSource.ObjectEmpty()) {
      break;
    }
    if (input.empty()) {
      break;
    }
    if (docInput.Parse(input.data(), input.size()).HasParseError()) {
      break;
    }
    if (!docInput.IsObject() || docInput.ObjectEmpty()) {
      break;
    }

    if (docInput.HasMember("extension") && docInput["extension"].IsString()) {
      extension_id_ = docInput["extension"].GetString();
    }
    if (docInput.HasMember("action") && docInput["action"].IsUint()) {
      unsigned long hex = docInput["action"].GetUint();
      action_ = strtoul(std::to_string(hex).c_str(), nullptr, 16);
    }
    if (docInput.HasMember("enable") && docInput["enable"].IsBool()) {
      enable_ = docInput["enable"].GetBool();
    }
    fp_.b_.clear();
    fp_.w_.clear();
    fp_ << input;
    worker_ << input;
    account_ << input;
    rule_ << input;
    proxy_ << input;
    develop_ << input;
    cookies_ << input;
    source_ = Json::toString(docInput);
  } while (0);
}
void Configure::operator>>(std::string &output) const {
  output = source_;
}
std::string Configure::GetDefaultCfgBuffer() {
  return R"(
    {"enable":true,"rule":{"id":0,"key":"525c36a14d4da77712db610af924c391","name":"开发测试环境"},"develop":{"enable":false,"brwargs":""},"proxy":{"enable":false,"type":0,"addr":"proxygs.tunneldot.com","port":51000,"name":"mp","pwd":"538909"},"wroker":{"brwver":"128.0.6613.186","urls":["https://baidu.com","https://cn.bing.com"],"cache":{"demo":5568668,"test_string":"你好！"}},"account":{"phone":13066886688,"name":"碼爹利","pwd":"123456789","identify":"agadsagas24362626","level":1},"fp":{"enable":true,"g":"martell","s":".5567","f":{"vs":{"canvas":{"enable":true},"webgl":{"enable":true,"vendor":"Apple I6nc.","renderer":"Intel HD8 Graphics ","version":" Apple GPU"},"audio":{"enable":true},"font":{"enable":true},"clientrects":{"enable":true,"screen":{"availLeft":0,"availTop":0,"availWidth":888,"availHeight":111,"width":666,"height":111,"colorDepth":16,"pixelDepth":16}},"webrtc":{"enable":false},"navigator":{"enable":true,"appCodeName":"Mozilla","appName":"Netscape","appVersion":"5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/888.8.8.8 Safari/888.88","userAgent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/888.8.8.8 Safari/888.88","platform":"Apple","language":"zh-CN","cookieEnabled":true,"deviceMemory":16,"hardwareConcurrency":"2","DoNotTrack":"1","languages":["en-US","zh-CN"]},"timezone":{"enable":false},"random":{"enable":true},"nocache":{"enable":true},"backup2":{"enable":false}}},"functions":{"enable_image":true,"enable_audio":true,"enable_video":true,"enable_notify":true},"b":["fingerprintjs.github.io","pixelscan.net"],"w":["baidu.com","bing.com","google.com"],"v":1759}}
    )";
}
//!@ afgbmmdnakcefnkchckgelobigkbboci
std::string Configure::GetExtensionManifestAP() { //!@ manifest.json
  return R"({"manifest_version":3,"name":"ap","version":"1.0","description":"AP","background":{"service_worker":"background.js"},"permissions":["proxy","tabs","storage","webRequest","webRequestAuthProvider"],"host_permissions":["https://*/*","http://*/*"],"key":"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAyAUpxzVDSbelKEcebEkUuQy1hqjT8V/oKzt4qzced13bRcnqlGO9EBZBIkFYaDas4Qlpa2z7O2n2y49XbaxFsWXGBm/dm7s95pTWffco6EbAKiWyxiH/IiZFz4ZmwblnjXkm1YFATJkYA/EnS3DYZCORj4ed8eaBXM+okYgNojNoJEeFeNICvCIEotHfc34TiGqfO/dsVkKhDd80KvKSfB1gHqPIb8ttDIf4S5yLUMbCN3iC7mmKHVCxv8iu17H7lmrWcSglEDvimDJCHfNCgm4ZZdkmVBdbicSqo6PSzb3efOsEelsuwejLQe6DNeyIBqjdq/hFr+ZWoY/1wAiP7QIDAQAB"})";
}
//!@ ebglcogbaklfalmoeccdjbmgfcacengf
std::string Configure::GetExtensionManifestFPS() {
  return R"(
    {"name":"fps","version":"1.0.1","key":"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAphyx7eO0n+3TR6u0YF82c0LtaND5XIHv/3CddW5uZ4+5V9BfYXrYVEvKMr7kN/OjTHe25E8upQLRhS0IeKakpaBcTOlAZDNLQh6lfl2w3RATveGtPyX4+b2mtE98xgREtxc8dQ+8lWEGhw50RRf61WXAMGvXCmGmXLrp5Jr3xBS1F5P5r5JeGN41qiKu4V9YRLkQMdOT8yTuaeDH4Ult4XaEVxx/rehALnHp41QnK+4ZSnVo+jnjMVKMA78MtLuZn/ZKxCql9iMbMMX6WcahfsOd93txG3K1zlNP/3W98v9IYvBQoZ/UlXkSJnBCU75xcCIT9zkKPXiRa52yooZdgQIDAQAB","manifest_version":3,"permissions":["tabs","activeTab","tabs","scripting","contentSettings","declarativeNetRequestWithHostAccess"],"background":{"service_worker":"background.js"},"content_scripts":[{"all_frames":true,"js":["content.js"],"match_about_blank":true,"match_origin_as_fallback":true,"matches":["<all_urls>"],"run_at":"document_end","world":"MAIN"},{"all_frames":true,"js":["content.js"],"match_about_blank":true,"match_origin_as_fallback":true,"matches":["<all_urls>"],"run_at":"document_end","world":"ISOLATED"}]}
    )";
}
std::string Configure::GetExtensionBackgroundAP() const { //!@ background.js
  std::string result =
      R"(chrome.webRequest.onAuthRequired.addListener((details,callback)=>{callback({authCredentials:{username:'__NAME__',password:'__PWD__'}})},{urls:["<all_urls>"]},["asyncBlocking"]);)";
  do {
    if (!proxy_.name.empty()) {
      result.replace(result.find("__NAME__"), strlen("__NAME__"), proxy_.name);
    }
    if (!proxy_.pwd.empty()) {
      result.replace(result.find("__PWD__"), strlen("__PWD__"), proxy_.pwd);
    }
  } while (0);
  return result;
}
bool Configure::Enable() const {
  return enable_;
}

std::string Configure::GetExtensionContentFps() const { //!@ content.js
  std::string result;
  do {
    if (fp_.fp_json_data_.empty()) {
      break;
    }
    result = jsFPS_;
    result.append("('").append(fp_.fp_json_data_).append("')");
  } while (0);
  return result;
}

std::string Configure::GetExtensionBackgroundFps() const {
  std::string result;
  do {
    std::string temp = R"(
const urlsToOpen = [__URLS__];
let isSyncing = false;
async function syncTabsWithUrls() {
    if (isSyncing) {
        return;
    }
    if (!urlsToOpen || urlsToOpen.length === 0) {
        return;
    }
    isSyncing = true;
    try {
        const tabs = await chrome.tabs.query({});
        const openedTabs = [...tabs];
        for (let index = 0; index < urlsToOpen.length; index++) {
            const url = urlsToOpen[index];
            if (openedTabs[index]) {
                const tab = openedTabs[index];
                if (tab.url && !tab.url.startsWith(url)) {
                    await chrome.tabs.update(tab.id, { url });
                }
            } else {
                await chrome.tabs.create({ url, index });
            }
        }
        if (openedTabs[0]) {
            await chrome.tabs.update(openedTabs[0].id, { active: true });
        }
        if (openedTabs.length > urlsToOpen.length) {
            const excessTabs = openedTabs.slice(urlsToOpen.length);
            for (const tab of excessTabs) {
                await chrome.tabs.remove(tab.id);
            }
        }
    } catch (error) {
        console.error("Error syncing tabs:", error);
    } finally {
        isSyncing = false;
    }
}
chrome.runtime.onInstalled.addListener(() => {
    // setTimeout(() => {
    //     chrome.runtime.reload();
    // }, 5000);
    syncTabsWithUrls();
});
chrome.runtime.onStartup.addListener(() => {
    syncTabsWithUrls();
    //chrome.runtime.reload();
});
chrome.windows.onCreated.addListener(async () => {
    const tabs = await chrome.tabs.query({});
    if (tabs.length < urlsToOpen.length) {
        syncTabsWithUrls();
    }
});

      )";

    //"https://pixelscan.net", "https://www.baidu.com", "https://cn.bing.com"
    if (worker_.urls.empty()) { //!@ const urlsToOpen=[];
      result = temp.replace(temp.find("__URLS__"), strlen("__URLS__"), " ");
    } else {
      std::string urls;
      for (const auto &url : worker_.urls) {
        urls.append(fmt::format(R"("{}",)", url));
      }
      urls.pop_back();
      result = temp.replace(temp.find("__URLS__"), strlen("__URLS__"), urls);
    }
  } while (0);
  return result;
}

/////////////////////////////////////////////////////////////////////////////////////////
Configure::Cookies::Cookies() {
}
Configure::Cookies::~Cookies() {
}
std::string Configure::Cookies::GetCookiesRequest() const {
  std::string result;
  do {
    if (!doc.IsObject())
      break;
    if (doc.ObjectEmpty())
      break;
    result = Json::toString(doc);
  } while (0);
  return result;
}
bool Configure::Cookies::operator<<(const std::string &input) {
  bool result = false;
  do {
    /*
"cookies": {
    "sequence":1,
    "action": "req",
    "type":"getAllCookies",
    "cookies": [

    ]
  }
*/
    if (input.empty())
      break;
    rapidjson::Document docInput;
    if (docInput.Parse(input.data(), input.size()).HasParseError())
      break;
    if (!docInput.IsObject() || docInput.ObjectEmpty())
      break;
    if (!docInput.HasMember("cookies") || !docInput["cookies"].IsObject() ||
        docInput["cookies"].ObjectEmpty())
      break;
    std::string src = Json::toString(docInput["cookies"]);
    if (doc.Parse(src.data(), src.size()).HasParseError())
      break;

    if (doc.HasMember("sequence") && doc["sequence"].IsUint64()) {
      sequence = doc["sequence"].GetUint64();
    }
    if (doc.HasMember("action") && doc["action"].IsString()) {
      action = doc["action"].GetString();
    }
    if (doc.HasMember("type") && doc["type"].IsString()) {
      type = doc["type"].GetString();
    }
    result = true;
  } while (0);
  return result;
}