/* KallistiOS ##version##

   kernel/net/net_udp.c
   Copyright (C) 2005, 2006, 2007 Lawrence Sebald

*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <arpa/inet.h>
#include <kos/net.h>
#include <kos/mutex.h>
#include <kos/cond.h>
#include <sys/queue.h>
#include <kos/dbgio.h>
#include <kos/fs_socket.h>
#include <arch/irq.h>
#include <sys/socket.h>
#include <errno.h>
#include "net_ipv4.h"
#include "net_udp.h"

struct udp_pkt {
    TAILQ_ENTRY(udp_pkt) pkt_queue;
    struct sockaddr_in from;
    uint8 *data;
    uint16 datasize;
};

TAILQ_HEAD(udp_pkt_queue, udp_pkt);

struct udp_sock {
    LIST_ENTRY(udp_sock) sock_list;
    struct sockaddr_in local_addr;
    struct sockaddr_in remote_addr;

    int flags;

    struct udp_pkt_queue packets;
};

LIST_HEAD(udp_sock_list, udp_sock);

static struct udp_sock_list net_udp_sockets = LIST_HEAD_INITIALIZER(0);
static mutex_t *udp_mutex = NULL;
static condvar_t *udp_packets_ready = NULL;

int net_udp_accept(net_socket_t *hnd, struct sockaddr *addr,
                   socklen_t *addr_len) {
    errno = EOPNOTSUPP;
    return -1;
}

int net_udp_bind(net_socket_t *hnd, const struct sockaddr *addr,
                 socklen_t addr_len) {
    struct udp_sock *udpsock, *iter;
    struct sockaddr_in *realaddr;

    /* Verify the parameters sent in first */
    if(addr == NULL) {
        errno = EFAULT;
        return -1;
    }

    if(addr->sa_family != AF_INET) {
        errno = EAFNOSUPPORT;
        return -1;
    }

    /* Get the sockaddr_in structure, rather than the sockaddr one */
    realaddr = (struct sockaddr_in *) addr;

    if(irq_inside_int()) {
        if(mutex_trylock(udp_mutex) == -1) {
            errno = EWOULDBLOCK;
            return -1;
        }
    }
    else {
        mutex_lock(udp_mutex);
    }

    udpsock = (struct udp_sock *)hnd->data;
    if(udpsock == NULL) {
        mutex_unlock(udp_mutex);
        errno = EBADF;
        return -1;
    }

    /* See if we requested a specific port or not */
    if(realaddr->sin_port != 0) {
        /* Make sure we don't already have a socket bound to the
           port specified */

        LIST_FOREACH(iter, &net_udp_sockets, sock_list) {
            if(iter->local_addr.sin_port == realaddr->sin_port) {
                mutex_unlock(udp_mutex);
                errno = EADDRINUSE;
                return -1;
            }
        }

        udpsock->local_addr = *realaddr;
    }
    else {
        uint16 port = 1024, tmp = 0;

        /* Grab the first unused port >= 1024. This is, unfortunately, O(n^2) */
        while(tmp != port) {
            tmp = port;

            LIST_FOREACH(iter, &net_udp_sockets, sock_list) {
                if(iter->local_addr.sin_port == port) {
                    ++port;
                    break;
                }
            }
        }

        udpsock->local_addr = *realaddr;
        udpsock->local_addr.sin_port = htons(port);
    }

    mutex_unlock(udp_mutex);

    return 0;
}

int net_udp_connect(net_socket_t *hnd, const struct sockaddr *addr,
                    socklen_t addr_len) {
    struct udp_sock *udpsock;
    struct sockaddr_in *realaddr;

    if(addr == NULL) {
        errno = EFAULT;
        return -1;
    }

    if(addr->sa_family != AF_INET) {
        errno = EAFNOSUPPORT;
        return -1;
    }

    if(irq_inside_int()) {
        if(mutex_trylock(udp_mutex) == -1) {
            errno = EWOULDBLOCK;
            return -1;
        }
    }
    else {
        mutex_lock(udp_mutex);
    }

    udpsock = (struct udp_sock *)hnd->data;
    if(udpsock == NULL) {
        mutex_unlock(udp_mutex);
        errno = EBADF;
        return -1;
    }

    if(udpsock->remote_addr.sin_addr.s_addr != INADDR_ANY) {
        mutex_unlock(udp_mutex);
        errno = EISCONN;
        return -1;
    }

    realaddr = (struct sockaddr_in *) addr;
    if(realaddr->sin_port == 0 || realaddr->sin_addr.s_addr == INADDR_ANY) {
        mutex_unlock(udp_mutex);
        errno = EADDRNOTAVAIL;
        return -1;
    }

    udpsock->remote_addr.sin_addr.s_addr = realaddr->sin_addr.s_addr;
    udpsock->remote_addr.sin_port = realaddr->sin_port;

    mutex_unlock(udp_mutex);

    return 0;
}

int net_udp_listen(net_socket_t *hnd, int backlog) {
    errno = EOPNOTSUPP;
    return -1;
}

ssize_t net_udp_recv(net_socket_t *hnd, void *buffer, size_t length, int flags) {
    struct udp_sock *udpsock;
    struct udp_pkt *pkt;

    if(irq_inside_int()) {
        if(mutex_trylock(udp_mutex) == -1) {
            errno = EWOULDBLOCK;
            return -1;
        }
    }
    else {
        mutex_lock(udp_mutex);
    }

    udpsock = (struct udp_sock *)hnd->data;
    if(udpsock == NULL) {
        mutex_unlock(udp_mutex);
        errno = EBADF;
        return -1;
    }

    if(udpsock->remote_addr.sin_addr.s_addr == INADDR_ANY ||
       udpsock->remote_addr.sin_port == 0) {
        mutex_unlock(udp_mutex);
        errno = ENOTCONN;
        return -1;
    }

    if(udpsock->flags & SHUT_RD) {
        mutex_unlock(udp_mutex);
        return 0;
    }

    if(buffer == NULL) {
        mutex_unlock(udp_mutex);
        errno = EFAULT;
        return -1;
    }

    if(TAILQ_EMPTY(&udpsock->packets) && ((udpsock->flags & O_NONBLOCK) ||
                                           irq_inside_int())) {
        mutex_unlock(udp_mutex);
        errno = EWOULDBLOCK;
        return -1;
    }

    if(TAILQ_EMPTY(&udpsock->packets)) {
        cond_wait(udp_packets_ready, udp_mutex);
    }

    pkt = TAILQ_FIRST(&udpsock->packets);

    if(pkt->datasize > length) {
        memcpy(buffer, pkt->data, length);
    }
    else {
        memcpy(buffer, pkt->data, pkt->datasize);
        length = pkt->datasize;
    }

    TAILQ_REMOVE(&udpsock->packets, pkt, pkt_queue);
    free(pkt->data);
    free(pkt);

    mutex_unlock(udp_mutex);

    return length;
}

ssize_t net_udp_recvfrom(net_socket_t *hnd, void *buffer, size_t length,
                         int flags, struct sockaddr *addr,
                         socklen_t *addr_len) {
    struct udp_sock *udpsock;
    struct udp_pkt *pkt;

    if(irq_inside_int()) {
        if(mutex_trylock(udp_mutex) == -1) {
            errno = EWOULDBLOCK;
            return -1;
        }
    }
    else {
        mutex_lock(udp_mutex);
    }

    udpsock = (struct udp_sock *)hnd->data;
    if(udpsock == NULL) {
        mutex_unlock(udp_mutex);
        errno = EBADF;
        return -1;
    }

    if(udpsock->flags & SHUT_RD) {
        mutex_unlock(udp_mutex);
        return 0;
    }

    if(buffer == NULL || addr_len == NULL) {
        mutex_unlock(udp_mutex);
        errno = EFAULT;
        return -1;
    }

    if(TAILQ_EMPTY(&udpsock->packets) && ((udpsock->flags & O_NONBLOCK) ||
                                           irq_inside_int())) {
        mutex_unlock(udp_mutex);
        errno = EWOULDBLOCK;
        return -1;
    }

    while(TAILQ_EMPTY(&udpsock->packets)) {
        cond_wait(udp_packets_ready, udp_mutex);
    }

    pkt = TAILQ_FIRST(&udpsock->packets);

    if(pkt->datasize > length) {
        memcpy(buffer, pkt->data, length);
    }
    else {
        memcpy(buffer, pkt->data, pkt->datasize);
        length = pkt->datasize;
    }

    if(addr != NULL) {
        struct sockaddr_in realaddr;

        realaddr.sin_family = AF_INET;
        realaddr.sin_addr.s_addr = pkt->from.sin_addr.s_addr;
        realaddr.sin_port = pkt->from.sin_port;
        memset(realaddr.sin_zero, 0, 8);

        if(*addr_len < sizeof(struct sockaddr_in)) {
            memcpy(addr, &realaddr, *addr_len);
        }
        else {
            memcpy(addr, &realaddr, sizeof(struct sockaddr_in));
            *addr_len = sizeof(struct sockaddr_in);
        }
    }

    TAILQ_REMOVE(&udpsock->packets, pkt, pkt_queue);
    free(pkt->data);
    free(pkt);

    mutex_unlock(udp_mutex);

    return length;
}

ssize_t net_udp_send(net_socket_t *hnd, const void *message, size_t length,
                     int flags) {
    struct udp_sock *udpsock;

    if(irq_inside_int()) {
        if(mutex_trylock(udp_mutex) == -1) {
            errno = EWOULDBLOCK;
            return -1;
        }
    }
    else {
        mutex_lock(udp_mutex);
    }

    udpsock = (struct udp_sock *)hnd->data;
    if(udpsock == NULL) {
        mutex_unlock(udp_mutex);
        errno = EBADF;
        return -1;
    }

    if(udpsock->flags & SHUT_WR) {
        mutex_unlock(udp_mutex);
        errno = EPIPE;
        return -1;
    }

    if(udpsock->remote_addr.sin_addr.s_addr == INADDR_ANY ||
       udpsock->remote_addr.sin_port == 0) {
        mutex_unlock(udp_mutex);
        errno = ENOTCONN;
        return -1;
    }

    if(message == NULL) {
        mutex_unlock(udp_mutex);
        errno = EFAULT;
        return -1;
    }

    if(udpsock->local_addr.sin_port == 0) {
        uint16 port = 1024, tmp = 0;
        struct udp_sock *iter;

        /* Grab the first unused port >= 1024. This is, unfortunately, O(n^2) */
        while(tmp != port) {
            tmp = port;

            LIST_FOREACH(iter, &net_udp_sockets, sock_list) {
                if(iter->local_addr.sin_port == port) {
                    ++port;
                    break;
                }
            }
        }

        udpsock->local_addr.sin_port = htons(port);
    }

    mutex_unlock(udp_mutex);

    return net_udp_send_raw(NULL, udpsock->local_addr.sin_addr.s_addr,
                            udpsock->local_addr.sin_port,
                            udpsock->remote_addr.sin_addr.s_addr,
                            udpsock->remote_addr.sin_port, (uint8 *) message,
                            length);
}

ssize_t net_udp_sendto(net_socket_t *hnd, const void *message, size_t length,
                       int flags, const struct sockaddr *addr,
                       socklen_t addr_len) {
    struct udp_sock *udpsock;
    struct sockaddr_in *realaddr;

    if(irq_inside_int()) {
        if(mutex_trylock(udp_mutex) == -1) {
            errno = EWOULDBLOCK;
            return -1;
        }
    }
    else {
        mutex_lock(udp_mutex);
    }

    udpsock = (struct udp_sock *)hnd->data;
    if(udpsock == NULL) {
        mutex_unlock(udp_mutex);
        errno = EBADF;
        return -1;
    }

    if(udpsock->flags & SHUT_WR) {
        mutex_unlock(udp_mutex);
        errno = EPIPE;
        return -1;
    }

    if(message == NULL || addr == NULL) {
        mutex_unlock(udp_mutex);
        errno = EFAULT;
        return -1;
    }

    realaddr = (struct sockaddr_in *) addr;

    if(udpsock->local_addr.sin_port == 0) {
        uint16 port = 1024, tmp = 0;
        struct udp_sock *iter;

        /* Grab the first unused port >= 1024. This is, unfortunately, O(n^2) */
        while(tmp != port) {
            tmp = port;

            LIST_FOREACH(iter, &net_udp_sockets, sock_list) {
                if(iter->local_addr.sin_port == port) {
                    ++port;
                    break;
                }
            }
        }

        udpsock->local_addr.sin_port = htons(port);
    }

    mutex_unlock(udp_mutex);

    return net_udp_send_raw(NULL, udpsock->local_addr.sin_addr.s_addr,
                            udpsock->local_addr.sin_port,
                            realaddr->sin_addr.s_addr, realaddr->sin_port,
                            (uint8 *) message, length);
}

int net_udp_shutdownsock(net_socket_t *hnd, int how) {
    struct udp_sock *udpsock;

    if(irq_inside_int()) {
        if(mutex_trylock(udp_mutex) == -1) {
            errno = EWOULDBLOCK;
            return -1;
        }
    }
    else {
        mutex_lock(udp_mutex);
    }

    udpsock = (struct udp_sock *)hnd->data;
    if(udpsock == NULL) {
        mutex_unlock(udp_mutex);
        errno = EBADF;
        return -1;
    }

    if(how & 0xFFFFFFFC) {
        mutex_unlock(udp_mutex);
        errno = EINVAL;
    }

    udpsock->flags |= how;

    mutex_unlock(udp_mutex);

    return 0;
}

int net_udp_socket(net_socket_t *hnd, int domain, int type, int protocol) {
    struct udp_sock *udpsock;

    udpsock = (struct udp_sock *) malloc(sizeof(struct udp_sock));
    if(udpsock == NULL) {
        errno = ENOMEM;
        return -1;
    }

    udpsock->remote_addr.sin_family = AF_INET;
    udpsock->remote_addr.sin_addr.s_addr = INADDR_ANY;
    udpsock->remote_addr.sin_port = 0;

    udpsock->local_addr.sin_family = AF_INET;
    udpsock->local_addr.sin_addr.s_addr = INADDR_ANY;
    udpsock->local_addr.sin_port = 0;

    udpsock->flags = 0;

    TAILQ_INIT(&udpsock->packets);

    if(irq_inside_int()) {
        if(mutex_trylock(udp_mutex) == -1) {
            errno = EWOULDBLOCK;
            return -1;
        }
    }
    else {
        mutex_lock(udp_mutex);
    }

    LIST_INSERT_HEAD(&net_udp_sockets, udpsock, sock_list);
    mutex_unlock(udp_mutex);

    hnd->data = udpsock;

    return 0;
}

void net_udp_close(net_socket_t *hnd) {
    struct udp_sock *udpsock;
    struct udp_pkt *pkt;

    if(irq_inside_int()) {
        if(mutex_trylock(udp_mutex) == -1) {
            errno = EWOULDBLOCK;
            return;
        }
    }
    else {
        mutex_lock(udp_mutex);
    }

    udpsock = (struct udp_sock *)hnd->data;
    if(udpsock == NULL) {
        mutex_unlock(udp_mutex);
        errno = EBADF;
        return;
    }

    TAILQ_FOREACH(pkt, &udpsock->packets, pkt_queue) {
        free(pkt->data);
        TAILQ_REMOVE(&udpsock->packets, pkt, pkt_queue);
        free(pkt);
    }

    LIST_REMOVE(udpsock, sock_list);

    free(udpsock);
    mutex_unlock(udp_mutex);
}

int net_udp_setflags(net_socket_t *hnd, int flags) {
    struct udp_sock *udpsock;

    if(irq_inside_int()) {
        if(mutex_trylock(udp_mutex) == -1) {
            errno = EWOULDBLOCK;
            return -1;
        }
    }
    else {
        mutex_lock(udp_mutex);
    }

    udpsock = (struct udp_sock *) hnd->data;
    if(udpsock == NULL) {
        mutex_unlock(udp_mutex);
        errno = EBADF;
        return -1;
    }

    if(flags & (~O_NONBLOCK)) {
        mutex_unlock(udp_mutex);
        errno = EINVAL;
        return -1;
    }

    udpsock->flags |= flags;
    mutex_unlock(udp_mutex);

    return 0;
}

int net_udp_input(netif_t *src, ip_hdr_t *ip, const uint8 *data, int size) {
    uint8 buf[size + 13];
    ip_pseudo_hdr_t *ps = (ip_pseudo_hdr_t *)buf;
    uint16 checksum;
    struct udp_sock *sock;
    struct udp_pkt *pkt;

    ps->src_addr = ip->src;
    ps->dst_addr = ip->dest;
    ps->zero = 0;
    ps->proto = ip->protocol;
    memcpy(&ps->src_port, data, size);
    ps->length = htons(size);

    /* check this.... */
    if(size & 0x01) {
        ps->data[size - sizeof(udp_hdr_t)] = 0;
        checksum = ps->checksum;
        ps->checksum = 0;
        ps->checksum = net_ipv4_checksum(buf, size + 13);
    }
    else {
        checksum = ps->checksum;
        ps->checksum = 0;
        ps->checksum = net_ipv4_checksum(buf, size + 12);
    }

    if(checksum != ps->checksum) {
        dbglog(DBG_KDEBUG, "net_udp: discarding UDP packet with invalid "
                           "checksum\n"
                           "         calculated 0x%04X, sent 0x%04X\n",
               ps->checksum, checksum);
        return -1;
    }

    if(mutex_trylock(udp_mutex)) {
        dbglog(DBG_KDEBUG, "net_udp: discarding packet due to locked mutex\n");
        return -1;
    }

    LIST_FOREACH(sock, &net_udp_sockets, sock_list) {
        /* See if we have a socket matching the description provided */
        if(sock->local_addr.sin_port == ps->dst_port &&
           ((sock->remote_addr.sin_port == ps->src_port &&
             sock->remote_addr.sin_addr.s_addr == ps->src_addr) ||
            (sock->remote_addr.sin_port == 0 &&
             sock->remote_addr.sin_addr.s_addr == INADDR_ANY))) {
            pkt = (struct udp_pkt *) malloc(sizeof(struct udp_pkt));

            pkt->datasize = size - sizeof(udp_hdr_t);
            pkt->data = (uint8 *) malloc(pkt->datasize);

            pkt->from.sin_family = AF_INET;
            pkt->from.sin_addr.s_addr = ip->src;
            pkt->from.sin_port = ps->src_port;

            memcpy(pkt->data, ps->data, pkt->datasize);

            TAILQ_INSERT_TAIL(&sock->packets, pkt, pkt_queue);

            cond_broadcast(udp_packets_ready);

            mutex_unlock(udp_mutex);

            return 0;
        }
    }

    dbglog(DBG_KDEBUG, "net_udp: Discarding packet for non-opened socket\n");
    mutex_unlock(udp_mutex);

    return 0;
}

int net_udp_send_raw(netif_t *net, uint32 src_ip, uint16 src_port,
                     uint32 dst_ip, uint16 dst_port, const uint8 *data,
                     int size) {
    uint8 buf[size + 13 + sizeof(udp_hdr_t)];
    ip_pseudo_hdr_t *ps = (ip_pseudo_hdr_t *) buf;
    ip_hdr_t ip;

    if(net == NULL && net_default_dev == NULL) {
        errno = ENETDOWN;
        return -1;
    }

    if(src_ip == INADDR_ANY) {
        if(net == NULL && net_default_dev != NULL) {
            ps->src_addr = htonl(net_ipv4_address(net_default_dev->ip_addr));
        }
        else if(net != NULL) {
            ps->src_addr = htonl(net_ipv4_address(net->ip_addr));
        }
    }
    else {
        ps->src_addr = src_ip;
    }

    buf[size + 12 + sizeof(udp_hdr_t)] = 0;
    memcpy(ps->data, data, size);
    size += sizeof(udp_hdr_t);

    ps->dst_addr = dst_ip;
    ps->zero = 0;
    ps->proto = 17;
    ps->length = htons(size);
    ps->src_port = src_port;
    ps->dst_port = dst_port;
    ps->hdrlength = ps->length;
    ps->checksum = 0;

    /* Compute the UDP checksum */
    if(size & 0x01) {
        ps->checksum = net_ipv4_checksum(buf, size + 13);
    }
    else {
        ps->checksum = net_ipv4_checksum(buf, size + 12);
    }

    /* Fill in the IPv4 Header */
    ip.version_ihl = 0x45;
    ip.tos = 0;
    ip.length = htons(size + 20);
    ip.packet_id = 0;
    ip.flags_frag_offs = htons(0x4000);
    ip.ttl = 64;
    ip.protocol = 17;
    ip.checksum = 0;
    ip.src = ps->src_addr;
    ip.dest = ps->dst_addr;

    /* Compute the IPv4 checksum */
    ip.checksum = net_ipv4_checksum((uint8 *) &ip, sizeof(ip_hdr_t));

    /* send it away.... */
    if(net_ipv4_send_packet(net, &ip, buf + 12, size)) {
        /* If net_ipv4_send_packet() returns anything but 0, its an error,
           errno should be set already from it. */
        return -1;
    }
    else {
        return size - sizeof(udp_hdr_t);
    }
}

int net_udp_init() {
    udp_mutex = mutex_create();

    if(udp_mutex == NULL) {
        return -1;
    }

    udp_packets_ready = cond_create();

    if(udp_packets_ready == NULL) {
        mutex_destroy(udp_mutex);
        udp_mutex = NULL;

        return -1;
    }

    return 0;
}

void net_udp_shutdown() {
    if(udp_mutex != NULL)
        mutex_destroy(udp_mutex);

    if(udp_packets_ready != NULL)
        cond_destroy(udp_packets_ready);
}
