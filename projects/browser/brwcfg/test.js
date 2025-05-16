!(function (e) {
  var cfg = JSON.parse(e);

  if (!cfg.enable) return;
  function isAllowed(hostname) {
    for (const allowed of cfg.wlist) {
      const regex = new RegExp("^" + allowed.replace(/\*/g, ".*") + "$");
      if (regex.test(hostname)) {
        return true;
      }
    }
    for (const blocked of cfg.blist) {
      const regex = new RegExp("^" + blocked.replace(/\*/g, ".*") + "$");
      if (regex.test(hostname)) {
        return false;
      }
    }
    return false;
  }

  if (isAllowed(window.location.hostname)) return;

  const audioEnabled = cfg.functions.enable_audio;
  const videoEnabled = cfg.functions.enable_video;
  const imageEnabled = cfg.functions.enable_image;
  const notifyEnabled = cfg.functions.enable_notify;
  if (!audioEnabled || !videoEnabled) {
    let mediaSrc = "media-src 'none';";
    const meta = document.createElement("meta");
    meta.httpEquiv = "Content-Security-Policy";
    meta.content = `default-src 'self'; ${mediaSrc}`;
    document.head.appendChild(meta);
  }

  if (!notifyEnabled) {
    if ("Notification" in window) {
      const originalNotification = Notification;
      Notification = function () {};
    }
  }

  if (!imageEnabled) {
    let imgSrc = "img-src 'none';";
    const meta = document.createElement("meta");
    meta.httpEquiv = "Content-Security-Policy";
    meta.content = `default-src 'self'; ${imgSrc}`;
    document.head.appendChild(meta);
  }
})('{"enable":true,"functions":{"enable_image":true,"enable_audio":true,"enable_video":true,"enable_notify":true},"wlist":["www.baidu.com","www.bing.com","cn.bing.com","www.google.com","ogs.google.com","accounts.google.com"],"blist":[]}');
