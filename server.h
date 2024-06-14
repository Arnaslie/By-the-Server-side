#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

typedef struct http_request {
    char function[50];
    char req_headers[100];
    char body[200];
} request_t;

typedef struct http_response {
    char response_line[200];
} response_t;

typedef struct http_request_initial_line {
    char http_verb[10];
    char http_path[20];
    char http_version[10];
} request_line_t;

int make_socket_internet();

int bind_socket(int sock, const struct sockaddr* addr, socklen_t size);

int enable_listen(int sock, int backlog);

int accept_connection(int sock, struct sockaddr *addr, socklen_t *addr_len);

int handle_request(char* request, char* delimiter, request_t* req); 

char* parse_request(char* request, char* delimiter, request_t* req);

void parse_request_line(char* request_line, char* delimiter, request_line_t* req);
