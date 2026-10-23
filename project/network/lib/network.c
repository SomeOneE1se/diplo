#include "network.h"

#ifdef PLATFORM_UNIX

#    include <sys/types.h>
#    include <sys/socket.h>
#    include <unistd.h>
#    include <arpa/inet.h>

/**
 * @brief network_socket
 * @param domain
 * @param type
 * @param protocol
 * @return
 */
int network_socket(
    int domain,
    int type,
    int protocol
)
{
    int res = socket(domain, type, protocol);
    if (res == -1)
    {
        LOG_INFO("! socket failed");
    }
    return res;
}

/**
 * @brief network_bind
 * @param sockfd
 * @param addr
 * @param addrlen
 */
void network_bind(
    int                    sockfd,
    const struct sockaddr *addr,
    socklen_t              addrlen
)
{
    int res = bind(sockfd, addr, addrlen);
    if (res == -1)
    {
        LOG_INFO("! bind failed");
    }
}

/**
 * @brief network_listen
 * @param sockfd
 * @param backlog
 */
void network_listen(
    int sockfd,
    int backlog
)
{
    int res = listen(sockfd, backlog);
    if (res == -1)
    {
        LOG_INFO("! listen failed");
    }
}

/**
 * @brief network_accept
 * @param sockfd
 * @param addr
 * @param addrlen
 * @return
 */
int network_accept(
    int              sockfd,
    struct sockaddr *addr,
    socklen_t       *addrlen
)
{
    int res = accept(sockfd, addr, addrlen);
    if (res == -1)
    {
        LOG_INFO("! accept failed");
    }
    return res;
}

/**
 * @brief network_connect
 * @param sockfd
 * @param addr
 * @param addrlen
 */
void network_connect(
    int                    sockfd,
    const struct sockaddr *addr,
    socklen_t              addrlen
)
{
    int res = connect(sockfd, addr, addrlen);
    if (res == -1)
    {
        LOG_INFO("! connect failed");
    }
}

/**
 * @brief network_inetPton
 * @param af
 * @param src
 * @param dst
 */
void network_inetPton(
    int         af,
    const char *src,
    void       *dst
)
{
    int res = inet_pton(af, src, dst);
    if (res == 0)
    {
        LOG_INFO(
            "!  inet_pton failed: src does not contain a character"
            " string representing a valid network address in the specified"
            " address family\n"
        );
    }
    if (res == -1)
    {
        LOG_INFO("!  inet_pton failed");
    }
}

#endif
