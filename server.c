#include "server.h"
#include <stdio.h>
#include <stdlib.h>

struct Server createServer(int domain, int service, int protocol,
                           u_long interface, int port, int backlog,
                           void (*launch)(struct Server *server)) {
  struct Server server;

  server.domain = domain;
  server.service = service;
  server.protocol = protocol;
  server.interface = interface;
  server.port = port;
  server.backlog = backlog;
  server.launch = launch;

  server.address.sin_family = server.domain;
  server.address.sin_port = htons(server.port);
  server.address.sin_addr.s_addr = htonl(server.interface);

  server.socket = socket(server.domain, server.service, server.protocol);

  if (server.socket == 0) {
    perror("Failed to connect to socket.\n");
    exit(1);
  }

  if (bind(server.socket, (struct sockaddr *)&server.address,
           sizeof(server.address)) < 0) {
    perror("Failed to bind socket.\n");
    exit(1);
  }

  if (listen(server.socket, server.backlog) < 0) {
    perror("Failed to start listening.\n");
    exit(1);
  }

  server.launch = launch;

  return server;
}
