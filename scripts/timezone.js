// 生成 timezones.json 并打印数量
// 保存为 generate_timezones.js 然后在项目根运行: node generate_timezones.js

const fs = require("fs");

function generate() {
  if (typeof Intl.supportedValuesOf === "function") {
    const zones = Intl.supportedValuesOf("timeZone");
    const obj = {};
    zones.forEach((z) => (obj[z] = {}));
    fs.writeFileSync("timezones.json", JSON.stringify(obj, null, 2), "utf8");
    console.log("Timezones written to timezones.json");
    console.log("Count:", zones.length);
    return;
  }

  // Fallback: use moment-timezone if Intl.supportedValuesOf not available
  try {
    const moment = require("moment-timezone");
    const zones = moment.tz.names();
    const obj = {};
    zones.forEach((z) => (obj[z] = {}));
    fs.writeFileSync("timezones.json", JSON.stringify(obj, null, 2), "utf8");
    console.log("Timezones written to timezones.json (moment-timezone)");
    console.log("Count:", zones.length);
  } catch (e) {
    console.error(
      "Intl.supportedValuesOf not available and moment-timezone not installed."
    );
    console.error("Install moment-timezone: npm install moment-timezone");
    process.exit(1);
  }
}

generate();
