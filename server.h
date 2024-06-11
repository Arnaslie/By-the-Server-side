#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

int make_socket_internet();

int bind_socket(int sock, const struct sockaddr* addr, socklen_t size);

int enable_listen(int sock, int backlog);

int accept_connection(int sock, struct sockaddr *addr, socklen_t *addr_len);
