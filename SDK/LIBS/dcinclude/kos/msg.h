/* KallistiOS 1.2.0

   include/kos/msg.h
   (c)2001 Dan Potter

   $Id: msg.h,v 1.2 2002/01/05 07:23:32 bardtx Exp $

*/

#ifndef __KOS_MSG_H
#define __KOS_MSG_H

#error This file hasn't been ported yet.. don't use it!

#include <arch/types.h>
#include <sys/iovec.h>
#include <sys/queue.h>

/* Message channel handle type */
typedef handle_t channel_t;

#ifdef _KERNEL

/* Allocate a new message channel; the channel will be assigned
   to the calling process and when that process dies, the channel
   will also die. */
void sc_msg_chan_create(const char *name);

/* Free a message channel */
void sc_msg_chan_destroy(channel_t id);

/* Open an existing message channel by name and return a handle. */
void sc_msg_chan_open(const char *name);

/* Close an opened message channel */
void sc_msg_chan_close(channel_t id);

/* Send a message on the given channel; if the channel has no
   threads queued in a receive-blocked state, then the caller
   will be queued in a send-blocked state. If the send
   succeeds, the caller will be blocked in a reply-blocked
   state. */
void sc_msg_sendv(channel_t id, iovec_t *send, int sendcnt,
	iovec_t *recv, int recvcnt);

/* Receives a message on the given channel; if the channel has no
   threads queued in a send-blocked state, then the caller
   will be queued in a receive-blocked state. If the receive
   succeeds, a notation will be made as to which thread to send
   replies to. */
void sc_msg_recvv(channel_t id, iovec_t *data, int iovcnt);

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



