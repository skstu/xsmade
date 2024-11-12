#include "sys.h"

XS_EXTERN unsigned short xs_sys_get_free_port(void) {
  unsigned short result = 0;
  do {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
      break;

    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET) {
      WSACleanup();
      break;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = 0; // 让系统选择随机端口

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR) {
      closesocket(sockfd);
      WSACleanup();
      break;
    }

    int addrlen = sizeof(addr);
    if (getsockname(sockfd, (struct sockaddr *)&addr, &addrlen) ==
        SOCKET_ERROR) {
      closesocket(sockfd);
      WSACleanup();
      break;
    }

    result = ntohs(addr.sin_port);
    closesocket(sockfd);
    WSACleanup();
  } while (0);
  return result;
}