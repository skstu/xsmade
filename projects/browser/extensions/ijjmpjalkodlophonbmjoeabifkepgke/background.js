import { getCookiesByUrl, delCookies } from "./lib/cookie.js";
import { postJson } from "./lib/net.js";
import {
  getUA,
  getPublicIP,
  buildRandomUrl,
  isTargetSearchPage,
} from "./lib/utils.js";
import {
  HTTP_SERVER_URL,
  TARGETS,
  TARGET_DOMAINS,
  HTTP_SERVER_ERROR_URL,
  PROXY_AUTH_CONFIGS,
  EXCLUDE_URL_PREFIXES,
  PROXY_BYPASS_LIST,
} from "./lib/consts.js";
let globalIndex = 0;
let isBlockedByRiskControl = false;
let globalUA = "";
let globalIP = "";
let globalConfig = {};
let gloadCurHeads = [];
async function initGlobals() {
  globalUA = getUA();
  globalIP = await getPublicIP();
}
function setProxy(proxyList = PROXY_AUTH_CONFIGS) {
  ++globalIndex;
  if (proxyList.length - 1 == globalIndex) {
    globalIndex = 0;
  }
  const proxy = proxyList[globalIndex];
  chrome.proxy.settings.set(
    {
      value: {
        mode: "fixed_servers",
        rules: {
          singleProxy: {
            scheme: "http",
            host: proxy.host,
            port: parseInt(proxy.port, 10),
          },
          bypassList: PROXY_BYPASS_LIST,
        },
      },
      scope: "regular",
    },
    () => {
      chrome.webRequest.onAuthRequired.addListener(
        function (details, callbackFn) {
          const { host, port } = details.challenger || {};
          const config = PROXY_AUTH_CONFIGS.find(
            (item) => item.host === host && Number(item.port) === Number(port)
          );
          globalConfig = config;
          //console.log("onAuthRequired!", details, callbackFn);
          callbackFn({
            authCredentials: {
              username: config.username,
              password: config.password,
            },
          });
        },
        { urls: ["<all_urls>"] },
        ["asyncBlocking"]
      );
    }
  );
  console.log("Current Proxy Config:", proxy);
  return proxy;
}
function setRandomProxy(proxyList = PROXY_AUTH_CONFIGS) {
  const proxy = proxyList[Math.floor(Math.random() * proxyList.length)];
  chrome.proxy.settings.set(
    {
      value: {
        mode: "fixed_servers",
        rules: {
          singleProxy: {
            scheme: "http",
            host: proxy.host,
            port: parseInt(proxy.port, 10),
          },
          bypassList: PROXY_BYPASS_LIST,
        },
      },
      scope: "regular",
    },
    () => {
      chrome.webRequest.onAuthRequired.addListener(
        function (details, callbackFn) {
          const { host, port } = details.challenger || {};
          const config = PROXY_AUTH_CONFIGS.find(
            (item) => item.host === host && Number(item.port) === Number(port)
          );
          globalConfig = config;
          //console.log("onAuthRequired!", details, callbackFn);
          callbackFn({
            authCredentials: {
              username: config.username,
              password: config.password,
            },
          });
        },
        { urls: ["<all_urls>"] },
        ["asyncBlocking"]
      );
    }
  );
  console.log("Current Proxy Config:", proxy);
  return proxy;
}

async function ensureTargetTabsAndCookies() {
  for (const target of TARGETS) {
    const cookies = await getCookiesByUrl(target.domain);
    let needCookies = false;
    if (target.domain === ".google.com") {
      needCookies = !cookies.some((c) => c.name === "NID" || c.name === "AEC");
    } else {
      needCookies = cookies.length === 0;
    }
    if (needCookies) {
      chrome.tabs.query({}, (tabs) => {
        let found = false;
        for (const tab of tabs) {
          if (tab.url && tab.url.startsWith(target.url.split("?")[0])) {
            found = true;
            chrome.tabs.update(tab.id, {
              url: buildRandomUrl(target),
              active: true,
            });
            break;
          }
        }
        if (!found) {
          chrome.tabs.create({ url: buildRandomUrl(target), active: true });
        }
      });
    }
  }
}

function refreshTargetTab(target) {
  if (isBlockedByRiskControl) return;
  chrome.tabs.query({}, (tabs) => {
    let found = false;
    for (const tab of tabs) {
      if (tab.url && tab.url.startsWith(target.url.split("?")[0])) {
        found = true;
        chrome.tabs.update(tab.id, { url: buildRandomUrl(target) });
        break;
      }
    }
    if (!found) {
      chrome.tabs.create({ url: buildRandomUrl(target), active: false });
    }
  });
}

function scheduleRandomRefresh(target) {
  const randomInterval = Math.floor(Math.random() * 11 + 10) * 1000;
  setTimeout(() => {
    //globalConfig = setRandomProxy(PROXY_AUTH_CONFIGS);
    globalConfig = setProxy(PROXY_AUTH_CONFIGS);
    refreshTargetTab(target);
    scheduleRandomRefresh(target);
  }, randomInterval);
}

for (const target of TARGETS) {
  scheduleRandomRefresh(target);
}

chrome.runtime.onInstalled.addListener(async () => {
  await initGlobals();
  ensureTargetTabsAndCookies();
});

chrome.windows.onCreated.addListener(async () => {
  //ensureGoogleTabAndCookies();
});
chrome.runtime.onStartup.addListener(() => {
  initGlobals();
  ensureTargetTabsAndCookies();
});

function safeRemoveTab(tabId) {
  chrome.tabs.get(tabId, function (tab) {
    if (chrome.runtime.lastError) return; // tab 已不存在
    chrome.tabs.remove(tabId);
  });
}

chrome.tabs.onUpdated.addListener((tabId, changeInfo, tab) => {
  if (!tab.url) return;
  if (EXCLUDE_URL_PREFIXES.some((prefix) => tab.url.startsWith(prefix))) return;

  if (!isTargetSearchPage(tab.url)) {
    let domain = "";
    try {
      domain = new URL(tab.url).hostname;
    } catch (e) {
      domain = "";
    }
    postJson(HTTP_SERVER_ERROR_URL, {
      msg: "Triggering risk control",
      url: tab.url,
      domain: domain,
    });

    safeRemoveTab(tabId);
    return;
  }
  const currentDomain = TARGETS.find((target) =>
    tab.url.startsWith(target.url.split("?")[0])
  )?.domain;
  if (currentDomain) {
    chrome.tabs.query({}, (tabs) => {
      const sameDomainTabs = tabs.filter(
        (t) =>
          t.id !== tabId &&
          t.url &&
          TARGETS.some(
            (target) =>
              t.url.startsWith(target.url.split("?")[0]) &&
              target.domain === currentDomain
          )
      );
      for (const t of sameDomainTabs) {
        safeRemoveTab(t.id);
      }
    });
  }
});

chrome.cookies.onChanged.addListener(async function (changeInfo) {
  const cookie = changeInfo.cookie;
  if (
    TARGET_DOMAINS.includes(cookie.domain) &&
    !changeInfo.removed &&
    (changeInfo.cause === "explicit" || changeInfo.cause === "overwrite")
  ) {
    const allCookiesRaw = await new Promise((resolve, reject) => {
      chrome.cookies.getAll({ domain: cookie.domain }, (cookies) => {
        if (chrome.runtime.lastError) {
          reject(chrome.runtime.lastError);
          return;
        }
        resolve(cookies);
      });
    });

    const allCookies = allCookiesRaw.map((c) => {
      let expireDays = null;
      if (c.expirationDate && c.creationDate) {
        expireDays = Math.round((c.expirationDate - c.creationDate) / 86400);
      } else if (c.expirationDate) {
        expireDays = Math.round((c.expirationDate - Date.now() / 1000) / 86400);
      }
      return {
        name: c.name,
        value: c.value,
        creationDate: c.creationDate || null,
        expirationDate: c.expirationDate || null,
        expireDays: expireDays,
      };
    });

    const push_data = {
      ua: globalUA,
      proxy: globalConfig,
      domain: cookie.domain,
      cookies: allCookies,
      headers: gloadCurHeads,
    };
    postJson(HTTP_SERVER_URL, push_data);
    console.log("PushData:", push_data);
  }
});

chrome.webRequest.onBeforeSendHeaders.addListener(
  (details) => {
    //console.log("onBeforeSendHeaders:", details);
    gloadCurHeads = details.requestHeaders;
    return {};
  },
  { urls: ["<all_urls>"] },
  ["requestHeaders"]
);
