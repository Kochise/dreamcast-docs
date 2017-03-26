/* KallistiOS ##version##

   fs_socket.c
   Copyright (C) 2006 Lawrence Sebald

*/

#include <kos/mutex.h>
#include <arch/spinlock.h>
#include <kos/dbgio.h>
#include <kos/fs.h>
#include <kos/fs_socket.h>
#include <kos/net.h>

#include <errno.h>
#include <string.h>
#include <malloc.h>
#include <sys/queue.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../net/net_ipv4.h"
#include "../net/net_udp.h"

/* Define the socket list type */
LIST_HEAD(socket_list, net_socket);

static struct socket_list sockets;
static mutex_t *list_mutex;

static void fs_socket_close(void *hnd) {
    net_socket_t *sock = (net_socket_t *) hnd;

    mutex_lock(list_mutex);
    LIST_REMOVE(sock, sock_list);
    mutex_unlock(list_mutex);

    net_udp_close(hnd);

    free(sock);
}

static off_t fs_socket_tell(void *hnd) {
    errno = ESPIPE;
    return (off_t) -1;
}

/* VFS handler */
static vfs_handler_t vh = {
    /* Name handler */
    {
        "/sock",        /* Name */
        0,              /* tbfi */
        0x00010000,     /* Version 1.0 */
        0,              /* Flags */
        NMMGR_TYPE_VFS,
        NMMGR_LIST_INIT,
    },

    0, NULL,        /* No cache, privdata */

    NULL,            /* open */
    fs_socket_close, /* close */
    NULL,            /* read */
    NULL,            /* write */
    NULL,            /* seek */
    fs_socket_tell,  /* tell */
    NULL,            /* total */
    NULL,            /* readdir */
    NULL,            /* ioctl */
    NULL,            /* rename */
    NULL,            /* unlink */
    NULL,            /* mmap */
    NULL,            /* complete */
    NULL,            /* stat */
    NULL,            /* mkdir */
    NULL             /* rmdir */
};

/* Have we been initialized? */
static int initted = 0;

int fs_socket_init() {
    if(initted == 1)
        return 0;

    LIST_INIT(&sockets);

    if(nmmgr_handler_add(&vh.nmmgr) < 0)
        return -1;

    list_mutex = mutex_create();
    initted = 1;

    return 0;
}

int fs_socket_shutdown() {
    net_socket_t *c, *n;

    if(initted == 0)
        return 0;

    mutex_lock(list_mutex);
    c = LIST_FIRST(&sockets);
    while(c != NULL) {
        n = LIST_NEXT(c, sock_list);

        vh.close(c);

        free(c);
        c = n;
    }

    if(nmmgr_handler_remove(&vh.nmmgr) < 0)
        return -1;

    mutex_destroy(list_mutex);

    initted = 0;

    return 0;
}

int fs_socket_setflags(int sock, int flags) {
    net_socket_t *hnd;

    hnd = (net_socket_t *) fs_get_handle(sock);
    if(hnd == NULL) {
        errno = EBADF;
        return -1;
    }

    return net_udp_setflags(hnd, flags);
}

int socket(int domain, int type, int protocol) {
    net_socket_t *sock;
    file_t hnd;

    /* First, check the arguments for validity */
    if(domain != AF_INET) {
        errno = EAFNOSUPPORT;
        return -1;
    }

    if(type != SOCK_DGRAM) {
        errno = EPROTONOSUPPORT;
        return -1;
    }

    if(protocol != 0 && protocol != IPPROTO_UDP) {
        errno = EPROTONOSUPPORT;
        return -1;
    }

    /* Allocate the socket structure, if we have the space */
    sock = (net_socket_t *) malloc(sizeof(net_socket_t));
    if(!sock)   {
        errno = ENOMEM;
        return -1;
    }

    /* Attempt to get a handle for this socket */
    hnd = fs_open_handle(&vh, sock);
    if(hnd < 0) {
        free(sock);
        return -1;
    }

    /* We only support UDP right now, so this is ok... */
    sock->protocol = IPPROTO_UDP;

    /* Initialize protocol-specific data */
    if(net_udp_socket(sock, domain, type, protocol) == -1) {
        fs_close(hnd);
        return -1;
    }

    /* Add this socket into the list of sockets, and return */
    mutex_lock(list_mutex);
    LIST_INSERT_HEAD(&sockets, sock, sock_list);
    mutex_unlock(list_mutex);

    return hnd;
}

int accept(int sock, struct sockaddr *address, socklen_t *address_len) {
    net_socket_t *hnd;

    hnd = (net_socket_t *) fs_get_handle(sock);
    if(hnd == NULL) {
        errno = EBADF;
        return -1;
    }

    return net_udp_accept(hnd, address, address_len);
}

int bind(int sock, const struct sockaddr *address, socklen_t address_len) {
    net_socket_t *hnd;

    hnd = (net_socket_t *) fs_get_handle(sock);
    if(hnd == NULL) {
        errno = EBADF;
        return -1;
    }

    return net_udp_bind(hnd, address, address_len);
}

int connect(int sock, const struct sockaddr *address, socklen_t address_len) {
    net_socket_t *hnd;

    hnd = (net_socket_t *) fs_get_handle(sock);
    if(hnd == NULL) {
        errno = EBADF;
        return -1;
    }

    return net_udp_connect(hnd, address, address_len);
}

int listen(int sock, int backlog) {
    net_socket_t *hnd;

    hnd = (net_socket_t *) fs_get_handle(sock);
    if(hnd == NULL) {
        errno = EBADF;
        return -1;
    }

    return net_udp_listen(hnd, backlog);
}

ssize_t recv(int sock, void *buffer, size_t length, int flags) {
    net_socket_t *hnd;

    hnd = (net_socket_t *) fs_get_handle(sock);
    if(hnd == NULL) {
        errno = EBADF;
        return -1;
    }

    return net_udp_recv(hnd, buffer, length, flags);
}

ssize_t recvfrom(int sock, void *buffer, size_t length, int flags,
                 struct sockaddr *address, socklen_t *address_len) {
    net_socket_t *hnd;

    hnd = (net_socket_t *) fs_get_handle(sock);
    if(hnd == NULL) {
        errno = EBADF;
        return -1;
    }

    return net_udp_recvfrom(hnd, buffer, length, flags, address,
                            address_len);
}

ssize_t send(int sock, const void *message, size_t length, int flags) {
    net_socket_t *hnd;

    hnd = (net_socket_t *) fs_get_handle(sock);
    if(hnd == NULL) {
        errno = EBADF;
        return -1;
    }

    return net_udp_send(hnd, message, length, flags);
}

ssize_t sendto(int sock, const void *message, size_t length, int flags,
               const struct sockaddr *dest_addr, socklen_t dest_len) {
    net_socket_t *hnd;

    hnd = (net_socket_t *) fs_get_handle(sock);
    if(hnd == NULL) {
        errno = EBADF;
        return -1;
    }

    return net_udp_sendto(hnd, message, length, flags, dest_addr, dest_len);
}

int shutdown(int sock, int how) {
    net_socket_t *hnd;

    hnd = (net_socket_t *) fs_get_handle(sock);
    if(hnd == NULL) {
        errno = EBADF;
        return -1;
    }

    return net_udp_shutdownsock(hnd, how);
}
