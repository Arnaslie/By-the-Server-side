#include <stdio.h>
#include "server.h"
#include <sys/un.h>
#include <stddef.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>


int main(int argc, char** argv) {
    struct sockaddr_in client_side;
    int client_socket = make_socket_internet();

    client_side.sin_port = htons(5050);
    client_side.sin_family = AF_INET;
    client_side.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    int connected = connect(client_socket, (struct sockaddr*) &client_side, sizeof(client_side));
    char data_buff[100] = "GET www.api.dev.url.io HTTP/1.1\r\nHeader:Value\r\nAuthorization:Bearer\r\n\r\n";
    int bytes_sent = send(client_socket, data_buff, sizeof(data_buff), 0);
    char serv_buff[100];
    int received_bytes = recv(client_socket, serv_buff, sizeof(serv_buff), 0);
    printf("%s\n", serv_buff);
    return 0;
}