#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

typedef struct http_request_initial_line {
    char http_verb[10];
    char http_path[20];
    char http_version[10];
} request_line_t;

typedef struct http_request {
    request_line_t req_line;
    char req_headers[100];
    char body[200];
} request_t;

typedef struct http_response {
    char response_line[200];
} response_t;

typedef enum {
    GET = 0b0000,
    HEAD = 0b0001,
    POST = 0b0010,
    PUT = 0b0011,
    DELETE = 0b0100,
    CONNECT = 0b0101,
    OPTIONS = 0b0110,
    TRACE = 0b0111,
    PATCH = 0b1000
} verbs_enum;

int make_socket_internet();

int bind_socket(int sock, const struct sockaddr* addr, socklen_t size);

int enable_listen(int sock, int backlog);

int accept_connection(int sock, struct sockaddr *addr, socklen_t *addr_len);

char* handle_request(char* buffer, char* delimiter, request_t* req, char* result_buff); 

char* parse_request(char* msg_buffer, char* delimiter, request_t* req);

void parse_request_line(char* req_line_buffer, request_line_t* request_line, char* delimiter, request_t* req);

void parse_headers(char* header_buffer, char* delimiter, char* header_values[16][100]);

char* handle_get();