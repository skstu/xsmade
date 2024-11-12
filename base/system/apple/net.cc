#include "sys.h"

XS_EXTERN unsigned short xs_sys_get_free_port(void) {
#if 0


bool Win::Tcpip::getFreePort(unsigned short& outPort) {
    bool result = false;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        return false;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = 0;  // 让系统选择随机端口

    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        close(sockfd);
        return false;
    }

    socklen_t addrlen = sizeof(addr);
    if (getsockname(sockfd, (struct sockaddr*)&addr, &addrlen) == -1) {
        close(sockfd);
        return false;
    }

    outPort = ntohs(addr.sin_port);
    close(sockfd);
    return true;
}

#endif
  return 0;
}