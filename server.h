#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

typedef struct http_request {
    char function[50];
    char req_headers[100];
    char body[200];
} Request;

typedef struct http_response {
    char response_line[200];
} Response;

int make_socket_internet();

int bind_socket(int sock, const struct sockaddr* addr, socklen_t size);

int enable_listen(int sock, int backlog);

int accept_connection(int sock, struct sockaddr *addr, socklen_t *addr_len);

int handle_request(char* request, char* delimiter, Request req); 

char* parse_request(char* request, char* delimiter, Request req);

char* parse_request_line(char* request_line, char* delimiter);