/* KallistiOS ##version##

   kos/msg.h
   Copyright (C)2001,2003 Dan Potter

   $Id: msg.h,v 1.3 2003/07/31 00:38:00 bardtx Exp $

*/

#ifndef __KOS_MSG_H
#define __KOS_MSG_H

#include <sys/iovec.h>
#include <kos/fs.h>

/* Channel handles are just file descriptors */
typedef file_t msgchan_t;


/* Allocate a new message channel. A new file descriptor will be opened
   in the calling process' table. When all processes have closed their
   references to the channel, it will be destroyed. */
msgchan_t msg_chan_create(const char * name);

/* Non-public version */
msgchan_t _msg_chan_create(struct kprocess * owner, const char * name);

/* Send a message on the given channel; if the channel has no
   threads queued in a receive-blocked state, then the caller
   will be queued in a send-blocked state. If the send
   succeeds, the caller will be blocked in a reply-blocked
   state. */
int msg_sendv(msgchan_t id, iovec_t *send, int sendcnt, iovec_t *recv, int recvcnt);

/* Receives a message on the given channel; if the channel has no
   threads queued in a send-blocked state, then the caller
   will be queued in a receive-blocked state. If the receive
   succeeds, a notation will be made as to which thread to send
   replies to. */
int msg_recvv(channel_t id, iovec_t *data, int iovcnt);

/* Reply to a message on the given channel; if the channel has no
   threads queued in a receive-blocked state, then an error is
   returned (this should not happen normally). If the reply 
   succeeds, both caller and callee will be unblocked; the
   code will be returned to the original sender, and optionally,
   a chunk of data. */
void sc_msg_replyv(channel_t id, int retval, iovec_t *data, int iovcnt);

/* Free all message channels for the given process' pid */
void msg_chan_freeall(pid_t pid);

/* Init / Shutdown */
int msg_init();
void msg_shutdown();      

#else	/* _KERNEL */

/* Userland versions */
channel_t msg_chan_create(const char *name);
int msg_chan_destroy(channel_t id);
channel_t msg_chan_open(const char *name);
int msg_chan_close(channel_t id);
int msg_sendv(channel_t id, iovec_t *send, int sendcnt,
	iovec_t *recv, int recvcnt);
int msg_recvv(channel_t id, iovec_t *data, int iovcnt);
int msg_replyv(channel_t id, int retval, iovec_t *data, int iovcnt);

#endif	/* _KERNEL */

#endif	/* __KOS_MSG_H */



