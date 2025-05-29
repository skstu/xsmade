/**
 * 发送 POST 请求，body 为 JSON
 * @param {string} url - 目标地址
 * @param {object} data - 要发送的 JSON 对象
 * @returns {Promise<Response>}
 */
export async function postJson(url, data) {
  return fetch(url, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify(data),
  });
}