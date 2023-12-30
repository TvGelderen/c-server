#ifndef server_h
#define server_h

#include <sys/socket.h>
#include <netinet/in.h>

struct Server {
    int domain;
    int service;
    int protocol;
    u_long interface;
    int port;
    int backlog;

    struct sockaddr_in address;

    int socket;

    void (*launch)(struct Server *server);
};

struct Server createServer(
        int domain,
        int service,
        int protocol,
        u_long interface,
        int port,
        int backlog,
        void (*launch)(struct Server *server));

#endif
