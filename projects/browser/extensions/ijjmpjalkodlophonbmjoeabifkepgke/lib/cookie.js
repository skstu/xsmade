export async function getCookiesByUrl(url) {
  try {
    const cookies = await new Promise((resolve, reject) => {
      chrome.cookies.getAll({ domain: url }, (cookies) => {
        if (chrome.runtime.lastError) {
          reject(chrome.runtime.lastError);
          return;
        }
        resolve(cookies);
      });
    });

    return cookies.map((cookie) => ({
      name: cookie.name,
      value: cookie.value,
    }));
  } catch (error) {
    console.error("getCookiesByUrl error:", error);
    return { error: error.message };
  }
}

export async function getCookies() {
  try {
    const cookies = await getAllCookies();
    return cookies;
  } catch (error) {
    console.error("getCookies error:", error);
    return { error: error.message };
  }
}

export function getAllCookies() {
  return new Promise((resolve, reject) => {
    chrome.cookies.getAll({}, (cookies) => {
      if (chrome.runtime.lastError) {
        reject(chrome.runtime.lastError);
        return;
      }
      resolve(cookies);
    });
  });
}

export async function delCookies() {
  try {
    const cookies = await getAllCookies();
    let arr = [];
    for (const cookie of cookies) {
      arr.push(delCookie(cookie));
    }
    await Promise.all(arr);
    console.log("remove all cookies.");
  } catch (error) {
    console.error("remove all cookies error: ", error);
  }
}

export function delCookie(cookie) {
  return new Promise((resolve, reject) => {
    const url =
      (cookie.secure ? "https://" : "http://") + cookie.domain + cookie.path;
    chrome.cookies.remove({ url: url, name: cookie.name }, (details) => {
      if (chrome.runtime.lastError) {
        reject(chrome.runtime.lastError);
        return;
      }
      resolve(details);
    });
  });
}

export async function setCookies(cookiesJson) {
  try {
    let arr = [];
    for (const cookie of cookiesJson) {
      arr.push(setCookie(cookie));
    }
    await Promise.all(arr);
  } catch (error) {
    console.error("setCookies error:", error);
  }
}

export function setCookie(cookie) {
  const c = prepareCookie(cookie);
  return new Promise((resolve, reject) => {
    chrome.cookies.set(c, (details) => {
      if (chrome.runtime.lastError) {
        reject(chrome.runtime.lastError);
        return;
      }
      resolve(details);
    });
  });
}

export function prepareCookie(cookie) {
  return cookie;
}
