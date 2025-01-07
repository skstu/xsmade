#include <xs.h>
#include <system.hpp>
#include <fmt/format.h>
#include <httplib.h>

int main(int argc, char **argv) {
  httplib::Server *server = new httplib::Server();

  server->Post("/close",
               [](const httplib::Request &req, httplib::Response &res) {
                 std::string repRes = R"({"status":"ok"})";

                 std::string body = req.body;
                 std::cout << "body: " << body << std::endl;
                 res.status = 200;
                 res.set_content(repRes.empty() ? "{}" : repRes,
                                 "application/json; charset=utf-8");
               });

  server->Post("/browser/cookies",
               [](const httplib::Request &req, httplib::Response &res) {
                 std::string repRes = R"({"status":"ok"})";

                //  std::string body = req.body;
                //  std::cout << "body: " << body << std::endl;
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
  server->listen("127.0.0.1", 65534);
  SK_DELETE_PTR(server);
  return 0;
}
