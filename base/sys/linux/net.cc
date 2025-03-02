#include "sys.h"

XS_EXTERN unsigned short xs_sys_get_free_port(void) {
  unsigned short result = 0;
  int sockfd = -1;
  do {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
      break;
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = 0; // 让系统选择随机端口

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
      break;

    socklen_t addrlen = sizeof(addr);
    if (getsockname(sockfd, (struct sockaddr *)&addr, &addrlen) == -1)
      break;

    result = ntohs(addr.sin_port);
  } while (0);
  if (sockfd != -1)
    close(sockfd);
  return result;
}