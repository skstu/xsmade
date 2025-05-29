#include <xs.h>
#include <stl.hpp>
#include <system.hpp>
#include <3rdparty/cpp-httplib/httplib.h>

const std::string testData = R"(
{
  "ua": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/136.0.0.0 Safari/537.36",
  "proxy": {},
  "domain": ".google.com",
  "cookies": [
    {
      "name": "SNID",
      "value": "ABablnegJSDSzoWsonMf3GSnZ4NWfY6hObFzbpKmCOI6D62Bccucs2-utp40fFPgQoH2uSTfpngLEnGdPdodPPA4TiiNRKHqlT8",
      "creationDate": null,
      "expirationDate": 1764211088.007903,
      "expireDays": 183
    },
    {
      "name": "OTZ",
      "value": "8101600_24_24__24_",
      "creationDate": null,
      "expirationDate": 1750992010,
      "expireDays": 30
    },
    {
      "name": "AEC",
      "value": "AVh_V2jIWFGHIZggUglcd16mH-Yb9Q-jrjo-mQUPwJ1p3PnAUz5dlmCGoIw",
      "creationDate": null,
      "expirationDate": 1762823546.284752,
      "expireDays": 167
    },
    {
      "name": "DV",
      "value": "Ey39Ux_z3FYfMMNiN6YW-gbk7bBPcRk",
      "creationDate": null,
      "expirationDate": 1748404287,
      "expireDays": 0
    },
    {
      "name": "NID",
      "value": "524=q0b9upsnEjqAodHVlWIinZWRHaEevqZoeEdvNbWOOU9mKZdkVjTHOb2Nit1jaAFgUe20l0XUfiDyLWflk0IJBfIrfULJxV5BkfFNS_PLuiuy5Q0LOJcN216kzi5JCG-lE1A4wNUD51lzIRK4X-RZsLXMfYDQR8gGj9BoOaY-4pXn46QgI2ZT2ij0BDInHnNA2HItgIlrlC49KQoWiVb6MHIhsW6jGpW4zYEZ4OeakbwNSwNvLdclY7AeNrJo0JIA1xJZ",
      "creationDate": null,
      "expirationDate": 1764211087.859317,
      "expireDays": 183
    }
  ],
  "gloadCurHeads": [
    {
      "name": "sec-ch-ua-platform",
      "value": "\"Windows\""
    },
    {
      "name": "User-Agent",
      "value": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/136.0.0.0 Safari/537.36"
    },
    {
      "name": "sec-ch-ua",
      "value": "\"Chromium\";v=\"136\", \"Google Chrome\";v=\"136\", \"Not.A/Brand\";v=\"99\""
    },
    {
      "name": "Content-Type",
      "value": "text/plain;charset=UTF-8"
    },
    {
      "name": "sec-ch-ua-mobile",
      "value": "?0"
    },
    {
      "name": "Accept",
      "value": "*/*"
    }
  ]
}
)";
int main(int argc, char **argv) {
  httplib::Client cli("https://search.yunlogin.com", 80);
  auto res = cli.Post("/api/v1/user/gen_cookie", testData,
                      "application/json; charset=utf-8");
  if (res) {
    std::cout << "Status: " << res->status << ", Body: " << res->body
              << std::endl;
  } else {
    std::cout << "Request failed" << std::endl;
  }

  httplib::Server *server = new httplib::Server();
  server->Post("/api/v1/user/error", [](const httplib::Request &req,
                                        httplib::Response &res) {
    // 获取当前时间
    auto now = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                  now.time_since_epoch()) %
              1000;
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
                 localtime_r(&t, &tm);
#endif
    std::cout << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << '.'
              << std::setfill('0') << std::setw(3) << ms.count()
              << " body: " << req.body << std::endl;

    std::string repRes = R"({"status":"ok"})";
    res.status = 200;
    res.set_content(repRes.empty() ? "{}" : repRes,
                    "application/json; charset=utf-8");
  });
  server->Post("/api/v1/user/gen_cookie", [](const httplib::Request &req,
                                             httplib::Response &res) {
    // 获取当前时间
    auto now = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                  now.time_since_epoch()) %
              1000;
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
                 localtime_r(&t, &tm);
#endif
    std::cout << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << '.'
              << std::setfill('0') << std::setw(3) << ms.count()
              << " body: " << req.body << std::endl;

    std::string repRes = R"({"status":"ok"})";
    res.status = 200;
    res.set_content(repRes.empty() ? "{}" : repRes,
                    "application/json; charset=utf-8");
  });

#if 0
  std::string input;
  do {
    input.clear();
    std::getline(std::cin, input);
    if (input == "q" || std::cin.eof()) {
      break;
    }
  } while (1);
#endif
  server->listen("0.0.0.0", 10888);
  SK_DELETE_PTR(server);
  return 0;
}
