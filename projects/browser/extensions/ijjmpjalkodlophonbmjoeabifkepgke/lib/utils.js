import { SEARCH_RANDOM_KEYWORDS, TARGETS } from "./consts.js";

/**
 * 获取当前 User-Agent
 * @returns {string}
 */
export function getUA() {
  return navigator.userAgent;
}

/**
 * 获取当前外网 IP
 * @returns {Promise<string>}
 */
export async function getPublicIP() {
  try {
    const res = await fetch("https://api.ipify.org?format=json");
    const data = await res.json();
    return data.ip;
  } catch {
    return "";
  }
}

/**
 * 生成 curl 所需的 header 信息
 * @param {Array} cookies - cookie 对象数组
 * @param {string} ua - User-Agent
 * @param {string} ip - 外网 IP
 * @returns {Array<string>} - curl header 数组
 */
export function buildCurlHeaders(cookies, ua, ip) {
  const cookieStr = cookies.map((c) => `${c.name}=${c.value}`).join("; ");
  return [
    `Cookie: ${cookieStr}`,
    `User-Agent: ${ua}`,
    `X-Forwarded-For: ${ip}`,
    // 可根据需要添加更多头
  ];
}

function getRandomKeyword() {
  return SEARCH_RANDOM_KEYWORDS[
    Math.floor(Math.random() * SEARCH_RANDOM_KEYWORDS.length)
  ];
}

export function buildRandomUrl(target) {
  if (target.domain === ".google.com") {
    return `https://www.google.com/search?q=${getRandomKeyword()}`;
  } else if (target.domain === ".bing.com") {
    return `https://www.bing.com/search?q=${getRandomKeyword()}`;
  } else if (target.domain === ".baidu.com") {
    return `https://www.baidu.com/s?wd=${getRandomKeyword()}`;
  }
  return target.url;
}

export function isTargetSearchPage(url) {
  return TARGETS.some(
    (target) => url && url.startsWith(target.url.split("?")[0])
  );
}
