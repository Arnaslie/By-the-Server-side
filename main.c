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
  int listening = enable_listen(socket_index, 3);
  int acc = accept_connection(socket_index, NULL, NULL);
  char buffer[100] = "You have to leave the space! All the time you have to leave the space! - FernanGOAT\n";
  send(acc, buffer, sizeof(buffer), 0);

  free(socket_ptr);

  return 0;
}
