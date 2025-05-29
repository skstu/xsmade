// chrome.webRequest.onAuthRequired.addListener(
//   function (details, callbackFn) {
//     const { host, port } = details.challenger || {};
//     const config = PROXY_AUTH_CONFIGS.find(
//       (item) => item.host === host && Number(item.port) === Number(port)
//     );
//     globalConfig = config;
//     console.log("onAuthRequired!", details, callbackFn);
//     callbackFn({
//       authCredentials: { username: config.username, password: config.password },
//     });
//   },
//   { urls: ["<all_urls>"] },
//   ["asyncBlocking"]
// );

// chrome.cookies.set({
//   url: "https://www.google.com/",
//   name: "NID",
//   value: "random_value", // 可用旧值或随机值
//   domain: ".google.com",
//   path: "/",
// });
// 只移除 NID 的 cookie
// for (const c of allCookiesRaw) {
//   if (c.name === "NID") {
//     chrome.cookies.remove({
//       url: `https://${cookie.domain.startsWith('.') ? cookie.domain.slice(1) : cookie.domain}/`,
//       name: "NID"
//     }, (details) => {
//       console.log("Removed NID cookie:", details);
//     });
//   }
// }
// delCookies()
//   .then(() => {
//     console.log("All cookies removed after update.");
//   })
//   .catch((error) => {
//     console.error("Error removing cookies:", error);
//   });

// isBlockedByRiskControl = true; // 阻塞自动刷新
// // 不自动关闭 tab，等待人工干预
// chrome.tabs.update(tabId, { active: true }); // 激活该 tab
// chrome.notifications.create({
//   type: "basic",
//   iconUrl: "icon.png",
//   title: "风控提示",
//   message: `检测到 ${domain} 风控，请人工处理。`,
// });

// 检测是否为目标搜索页，人工过盾后自动恢复
// if (isBlockedByRiskControl && isTargetSearchPage(tab.url)) {
//   isBlockedByRiskControl = false;
//   console.log("已检测到人工过盾，恢复自动刷新");
//   // 可选：弹窗提示
//   chrome.notifications.create({
//     type: "basic",
//     iconUrl: "icon.png",
//     title: "恢复提示",
//     message: "已检测到页面恢复为搜索页，自动刷新已恢复。",
//   });
//   return;
// }
