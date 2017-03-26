/* KallistiOS ##version##

   kernel/net/net_udp.h
   Copyright (C) 2005, 2006, 2007 Lawrence Sebald

*/

#ifndef __LOCAL_NET_UDP_H
#define __LOCAL_NET_UDP_H

#include <sys/socket.h>
#include <kos/fs_socket.h>

#define packed __attribute__((packed))
typedef struct {
    uint16 src_port    packed;
    uint16 dst_port    packed;
    uint16 length      packed;
    uint16 checksum    packed;
} udp_hdr_t;
#undef packed

int net_udp_input(netif_t *src, ip_hdr_t *ih, const uint8 *data, int size);
int net_udp_send_raw(netif_t *net, uint32 src_ip, uint16 src_port,
                     uint32 dst_ip, uint16 dst_port, const uint8 *data,
                     int size);

/* Sockets */
int net_udp_accept(net_socket_t *hnd, struct sockaddr *addr,
                   socklen_t *addr_len);
int net_udp_bind(net_socket_t *hnd, const struct sockaddr *addr,
                 socklen_t addr_len);
int net_udp_connect(net_socket_t *hnd, const struct sockaddr *addr,
                    socklen_t addr_len);
int net_udp_listen(net_socket_t *hnd, int backlog);
ssize_t net_udp_recv(net_socket_t *hnd, void *buffer, size_t length, int flags);
ssize_t net_udp_recvfrom(net_socket_t *hnd, void *buffer, size_t length,
                         int flags, struct sockaddr *addr, socklen_t *addr_len);
ssize_t net_udp_send(net_socket_t *hnd, const void *message, size_t length,
                     int flags);
ssize_t net_udp_sendto(net_socket_t *hnd, const void *message, size_t length,
                       int flags, const struct sockaddr *addr,
                       socklen_t addr_len);
int net_udp_shutdownsock(net_socket_t *hnd, int how);
int net_udp_socket(net_socket_t *hnd, int domain, int type, int protocol);

void net_udp_close(net_socket_t *hnd);

int net_udp_setflags(net_socket_t *hnd, int flags);

#endif /* __LOCAL_NET_UDP_H */
