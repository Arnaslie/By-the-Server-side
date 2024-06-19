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

char* handle_request(char* msg_buffer, char* delimiter, request_t* req, char* result_buff) {
    request_line_t req_line; 
    req->req_line = req_line;
    char* request_header_keys[16][20] = {
    "Accept", "Accept-Charset", "Accept-Encoding", "Accept-Language", "Authorization", \
    "Expect", "From", "Host", "If-Match", "If-Modified-Since", "If-None-Match", "If-Range", \
    "If-Unmodified-Since", "Max-Forwards", "Proxy-Authorization", \
    "Range", "Referer", "TE", "User-Agent"};
    char* response_header_keys[9][20] = {
        "Accept-Ranges", "Age", "ETag", "Location", "Proxy-Authenticate", \
        "Retry-After", "Server", "Vary", "WWW-Authenticate"
    };
    char* request_header_values[16][100];
    char* response_header_values[9][100];
    char* msg_copy = strdup(msg_buffer);

    char* line = parse_request(msg_buffer, delimiter, req);    
    parse_request_line(line, &(req->req_line), " ", req);
    if(strcmp(req->req_line.http_verb, "GET") == 0) {
        handle_get();
    }
    parse_headers(msg_copy, delimiter);

    free(msg_copy);
    strcpy(result_buff, "HTTP/1.0 200 OK\n");
    return result_buff;
}

char* parse_request(char* str_to_parse, char* delimiter, request_t* req) {
    char* result = strtok(str_to_parse, delimiter);
    return result;
    //TODO: Write code to parse headers, body because right now this is just stripping out the request line
}

void parse_request_line(char* req_line_buffer, request_line_t* request_line, char* delimiter, request_t* req) {
    char* result;
    result = strtok(req_line_buffer, delimiter);
    strcpy(request_line->http_verb, result);
    for(int i = 0; i < 2; i++) {
        result = strtok(NULL, delimiter);
        if(i == 0) {
            strcpy(req->req_line.http_path, result); 
        } else if (i == 1) {
            strcpy(req->req_line.http_version, result);
        }
    } 
    return;
}

void parse_headers(char* header_buffer, char* delimiter) {
    char* result = strtok(header_buffer, delimiter);
    int i = 0;
    while(result != NULL) {
        if(i % 2 == 0) {
            result = strtok(NULL, ":");
        } else {
            result = strtok(NULL, "\r\n");
        }
        i++;
    }
    return;
}

// This is GET endpoint. Only return a value if the proper verb is specificed
char* handle_get() {
    printf("///// GET \\\\\\ \n");
    return "a";
}