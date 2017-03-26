/* KallistiOS ##version##

   kos/fs_socket.h
   Copyright (C) 2006 Lawrence Sebald

*/

#ifndef __KOS_FS_SOCKET_H
#define __KOS_FS_SOCKET_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>
#include <kos/limits.h>
#include <kos/fs.h>
#include <sys/queue.h>

typedef struct net_socket {
    /* List handle */
    LIST_ENTRY(net_socket)  sock_list;
    
    /* Protocol of this socket. This corresponds to the IP protocol number */
    int                     protocol;
    
    /* Protocol specific data */
    void                   *data;
} net_socket_t;

int fs_socket_init();
int fs_socket_shutdown();

int fs_socket_setflags(int sock, int flags);

__END_DECLS

#endif	/* __KOS_FS_SOCKET_H */

