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

int handle_request(char* request, char* delimiter, request_t* req) {
    request_line_t req_line; 
    parse_request(request, delimiter, req);
    parse_request_line(req->function, " ", &req_line);
    return 0;
}

char* parse_request(char* str_to_parse, char* delimiter, request_t* req) {
    char* result = strtok(str_to_parse, delimiter);
    strcpy(req->function, result);
    while(result != NULL) {
        printf("%s \n" , result);
        result = strtok(NULL, delimiter);
    }
    return result;
}

void parse_request_line(char* request_line, char* delimiter, request_line_t* req) {
    char* result;
    result = strtok(request_line, delimiter);
    strcpy(req->http_verb, result); 
    for(int i = 0; i < 2; i++) {
        result = strtok(NULL, delimiter);
        if(i == 0) {
            strcpy(req->http_path, result); 
        } else if (i == 1) {
            strcpy(req->http_version, result);
        }
    } 
}