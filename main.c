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
#include <string.h>


char* parse_request(char* str_to_parse, char* delimiter) {
  char* result;
  result = strtok(str_to_parse, delimiter);
  while(result != NULL) {
    printf("%s \n" , result);
    result = strtok(NULL, delimiter);
  }
  return result;
}



int main() {
  printf("Hi, we'll be building a HTTP server \n");

  char * header = "HTTP-Version = HTTP/1.1\n";

  struct sockaddr_in* socket_ptr = malloc(sizeof socket_ptr);
  struct in_addr addr_t;
  uint32_t address = inet_addr("127.0.0.1");
  in_port_t port = 5050;
  addr_t.s_addr = address;
  struct sockaddr_in socket_in = {.sin_family=AF_INET, .sin_port=htons(port), .sin_addr=addr_t}; 

  
  int socket_index = make_socket_internet();

  int size = sizeof (*socket_ptr); 
  int bind_ret_val = bind_socket(socket_index, (struct sockaddr*) &socket_in, (socklen_t) size);
  int reuse_local_addr_option_value = 1;
  int opt = setsockopt(socket_index, SOL_SOCKET, SO_REUSEADDR, &reuse_local_addr_option_value, sizeof(int));

  int listening = enable_listen(socket_index, 3);
  printf("Server is listening on %s:%d \n", inet_ntoa(addr_t), port);
  char c_buff[100];
  char* delimiter = "\r\n";
  while(1) {
    int acc = accept_connection(socket_index, NULL, NULL);
    int rec = recv(acc, c_buff, sizeof(c_buff), 0);
    char* client_req = parse_request(c_buff, delimiter);
    printf("%s\n", c_buff);
    char buffer[100] = "You have to leave the space! All the time you have to leave the space! - FernanGOAT\n";
    send(acc, buffer, sizeof(buffer), 0);
    int closed = close(acc);
  }
  
  free(socket_ptr);

  return 0;
}
