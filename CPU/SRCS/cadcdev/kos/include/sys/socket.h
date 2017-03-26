/* KallistiOS ##version##

   sys/socket.h
   Copyright (C)2006 Lawrence Sebald

*/

#ifndef __SYS_SOCKET_H
#define __SYS_SOCKET_H

#include <sys/cdefs.h>
#include <arch/types.h>

__BEGIN_DECLS

typedef uint32 socklen_t;

#ifndef __SA_FAMILY_T_DEFINED
#define __SA_FAMILY_T_DEFINED
typedef uint32 sa_family_t;
#endif

struct sockaddr {
    sa_family_t sa_family;
    char        sa_data[];
};

/* Socket types, currently only SOCK_DGRAM is available */
#define SOCK_DGRAM 1

/* Socket address families. Currently only AF_INET is available */
#define AF_INET 1

#define PF_INET AF_INET

/* Socket shutdown macros. */
#define SHUT_RD   0x00000001
#define SHUT_WR   0x00000002
#define SHUT_RDWR (SHUT_RD | SHUT_WR)

int accept(int socket, struct sockaddr *address, socklen_t *address_len);
int bind(int socket, const struct sockaddr *address, socklen_t address_len);
int connect(int socket, const struct sockaddr *address, socklen_t address_len);
int listen(int socket, int backlog);
ssize_t recv(int socket, void *buffer, size_t length, int flags);
ssize_t recvfrom(int socket, void *buffer, size_t length, int flags,
                 struct sockaddr *address, socklen_t *address_len);
ssize_t send(int socket, const void *message, size_t length, int flags);
ssize_t sendto(int socket, const void *message, size_t length, int flags,
               const struct sockaddr *dest_addr, socklen_t dest_len);
int shutdown(int socket, int how);
int socket(int domain, int type, int protocol);

__END_DECLS

#endif /* __SYS_SOCKET_H */
