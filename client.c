#include <sys/socket.h>

int connect_socket(int sock, struct sockaddr* addr, socklen_t length) {
    int c = connect(sock, addr, length);
    return c;
}