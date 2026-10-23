#ifndef NETWORK_H
#define NETWORK_H

#include "project.h"

#ifdef PLATFORM_UNIX

#    include <sys/types.h>
#    include <sys/socket.h>

#    define NET_PROT_IPV4 AF_INET
#    define NET_PROT_TCP  SOCK_STREAM
#    define NET_PROT_UDP  SOCK_DGRAM

int network_socket(
    int domain,
    int type,
    int protocol
);

void network_bind(
    int                    sockfd,
    const struct sockaddr *addr,
    socklen_t              addrlen
);

void network_listen(
    int sockfd,
    int backlog
);

int network_accept(
    int              sockfd,
    struct sockaddr *addr,
    socklen_t       *addrlen
);

void network_connect(
    int                    sockfd,
    const struct sockaddr *addr,
    socklen_t              addrlen
);

void network_inetPton(
    int         af,
    const char *src,
    void       *dst
);
#endif

#endif  // NETWORK_H
