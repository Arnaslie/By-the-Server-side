#include <stdio.h>
#include <sys/un.h>
#include <stddef.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include "server.h"
#include "client.h"

int make_socket_local(const char* filename) {
    struct sockaddr_un name;
    int sock;
    size_t size;
    
    // create the socket
    sock = socket(PF_LOCAL, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        exit (EXIT_FAILURE);
    }

    // bind the socket
    name.sun_family = AF_LOCAL;
    strncpy(name.sun_path, filename, sizeof(name.sun_path));
    name.sun_path[sizeof(name.sun_path) - 1] = '\0';

    size = SUN_LEN(&name);
    if (bind(sock, (struct sockaddr *) &name, size) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    return sock;

}

int make_socket_internet() {
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        exit (EXIT_FAILURE);
    }
    return sock;
}

int bind_socket(int sock, const struct sockaddr* addr, socklen_t size) {
    // bind the socket to an address
    int _bind = bind(sock, addr, size);
    if (_bind < 0) {
        perror("bind");
        exit (EXIT_FAILURE);
        }
    return _bind;
    }

int enable_listen(int sock, int backlog) {
    int listen_ret_val = listen(sock, backlog);
    if (listen_ret_val < 0) {
        perror("listen");
        exit (EXIT_FAILURE);
    }
    return listen_ret_val;
}

int accept_connection(int sock, struct sockaddr *addr, socklen_t *addr_len) {
    int acc_val = accept(sock, addr, addr_len);
    if (acc_val < 0) {
        perror("accept");
        exit (EXIT_FAILURE);
    }
    return acc_val;
}

int connect_to_socket(int sock) {

    return 0;
}