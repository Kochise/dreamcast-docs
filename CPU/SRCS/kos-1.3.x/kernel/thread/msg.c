/* KallistiOS ##version##

   msg.c
   Copyright (C)2001,2003 Dan Potter
*/

// Defines basic message passing primitives

#include <string.h>
#include <stdlib.h>
#include <kos/process.h>
#include <sys/queue.h>
#include <kos/cond.h>
#include <kos/mutex.h>
#include <kos/msg.h>

CVSID("$Id: msg.c,v 1.3 2003/07/31 00:40:30 bardtx Exp $");

/*

The message channel system is very similar to that employed by QNX. It
implements a basic synchronous message passing system.

The basic idea is that any process can create a message channel, which is
given an entry on the VFS in /msg. This process is then expected to wait
for a message on this channel (perhaps with multiple threads). The states
then go something like this:

- One or more server threads go into recvwait state, waiting for a
  message arrival.
- A client sends a message on the channel. If server threads are already
  waiting to receive messages, the message is placed on the channel and
  the client thread is placed into the replywait state. If no server
  threads are available, the client is placed into the sendwait state.
- One server thread is woken to receive and process the message.
  The woken server thread removes the message from the channel,
  clearing it for another request. If the client thread was in the sendwait
  state, it is changed to a replywait state.
- When a server request is completed, the response is placed on the
  channel. That thread generally then goes to sleep again on recvwait.
  The client thread is woken and receives the response,
  removing it from the channel again.
- Only one message may be active "on" the channel at any given time. This
  is generally OK since we never block for long periods of time with the
  channel occupied.

*/

typedef struct msgchan {
	// List entry for the global list of message channels
	LIST_ENTRY(msgchan)	g_list;

	kprocess_t	* owner;	// Owner of this channel
	char		name[64];	// Channel name

	iovec_t		* msg;		// Message data for waiting message, or NULL
	int		msgcnt;		// Number of iov entries
	kthread_t	* msgowner;	// Owner of the message placed here

	// Message channel state
	int	waitrecv_cnt;	// Number of threads waiting on receive
	int	waitsend_cnt;	// Number of threads waiting on send
	
} chan_t;

LIST_HEAD(msgchanlist, msgchan);

/**************************************/

/* Global list of message channels */
static struct msgchanlist chan_list;

/* Message channel VFS. We use this to allow separate programs to look
   up, open, and interact with message channels. */
static void * msg_vfs_open(vfs_handler_t * vfs, const char * fn, int mode);
static void msg_vfs_close(void * hnd);
static dirent_t * msg_vfs_readdir(void * hnd);
static vfs_handler_t msgvfs = {
	{
		"/msg",
		0,
		0x00010000,
		0,
		NMMGR_TYPE_VFS,
		NMMGR_LIST_INIT
	},

	0, NULL,

	msg_vfs_open,
	msg_vfs_close,
	NULL,			// read
	NULL,			// seek
	NULL,			// tell
	NULL,			// total
	msg_vfs_readdir,	// readdir
	NULL,			// ioctl
	NULL,			// rename
	NULL,			// unlink
	NULL,			// mmap
	NULL,			// complete
	NULL,			// stat
	NULL,			// mkdir
	NULL			// rmdir
};

/* Allocate a new message channel; the channel will be assigned
   to the calling process and when that process dies, the channel
   will also die. */
msgchan_t _msg_chan_create(kprocess_t * proc, const char *name) {
	chan_t		* mc;
	int		old;
	msgchan_t	rv;

	/* Create a message channel structure */
	mc = (chan_t*)calloc(1, sizeof(chan_t));
	strncpy(mc->name, name, 63);
	mc->refcnt = 1;

	/* Add to the global list */
	old = irq_disable();
	LIST_INSERT_HEAD(&chan_list, mc, g_list);
	irq_restore(old);

	/* Open a file descriptor for it */
	rv = _fs_open_handle(proc, &msgvfs, mc);
	return rv;
}

/* Return the message channel structure by name */
static chan_t *chan_by_name(const char *name) {
	chan_t	* chan;

	LIST_FOREACH(chan, &chan_list, g_list) {
		if (!strcmp(name, chan->name))
			break;
	}
	return chan;
}

/* Free a message channel */
void sc_msg_chan_destroy(channel_t id) {
	msgchan_t	*mc;

	/* Look for the channel */
	mc = chan_by_id(id);
	if (mc == NULL) {
		RETURN(-1);
	}

	/* Remove it from the global list */
	LIST_REMOVE(mc, g_list);

	/* Do the actual destruction */
	msg_chan_destroy(mc);

	RETURN(0);
}

/* Open an existing message channel by name and return a handle. */
void sc_msg_chan_open(const char *name) {
	msgchan_t	*mc;

	/* Look for the channel */
	mc = chan_by_name(name);
	if (mc == NULL) {
		RETURN(-1);
	}

	/* XXX keeping track of processes that open the channel? */

	RETURN(mc->id);
}

/* Close an opened message channel */
void sc_msg_chan_close(channel_t id) {
	RETURN(0);
}

/* Send a message on the given channel; if the channel has no
   threads queued in a receive-blocked state, then the caller
   will be queued in a send-blocked state. If the send
   succeeds, the caller will be blocked in a reply-blocked
   state. */
void sc_msg_sendv(channel_t id, iovec_t *send, int sendcnt,
		iovec_t *recv, int recvcnt) {
	msgchan_t	*mc;
	kthread_t	*thd;
	int		rv;

	/* Look up the channel ID */
	mc = chan_by_id(id);
	if (mc == NULL)
		RETURN(-1);

	/* If no one is blocked on receive, then block this
	   thread on send */
	if (TAILQ_EMPTY(&mc->blocked_recv)) {
		thd_current->state = STATE_WAITSEND;
		thd_current->msg_send_iov = send;
		thd_current->msg_send_cnt = sendcnt;
		thd_current->msg_recv_iov = recv;
		thd_current->msg_recv_cnt = recvcnt;
		TAILQ_INSERT_TAIL(&mc->blocked_send, thd_current, thdq);
		thd_schedule();
		return;
	}

	/* Grab the top waiting thread and remove it from the queue */
	thd = TAILQ_FIRST(&mc->blocked_recv);
	TAILQ_REMOVE(&mc->blocked_recv, thd, thdq);

	/* Copy the message data */
	if (send != NULL && sendcnt > 0)
		rv = mmu_copyv(thd_current->pid, send, sendcnt,
			thd->pid, thd->msg_recv_iov, thd->msg_recv_cnt);
	else
		rv = 0;
	thd->msg_recv_iov = NULL; thd->msg_recv_cnt = 0;

	/* Reactivate the receiving thread */
	thd->state = STATE_READY;
	SET_RETURN(thd, rv);
	thd_add_to_runnable(thd);

	/* Block the sending thread in a reply state */
	thd_current->state = STATE_WAITREPLY;
	thd_current->msg_recv_iov = recv;
	thd_current->msg_recv_cnt = recvcnt;
	TAILQ_INSERT_TAIL(&mc->blocked_reply, thd_current, thdq);
	thd_schedule();
}

/* Receives a message on the given channel; if the channel has no
   threads queued in a send-blocked state, then the caller
   will be queued in a receive-blocked state. If the receive
   succeeds, a notation will be made as to which thread to send
   replies to. */
void sc_msg_recvv(channel_t id, iovec_t *data, int iovcnt) {
	msgchan_t	*mc;
	kthread_t	*thd;
	int		rv;

	/* Look up the channel ID */
	mc = chan_by_id(id);
	if (mc == NULL)
		RETURN(-1);

	/* If no one is blocked on send, then block this
	   thread on receive */
	if (TAILQ_EMPTY(&mc->blocked_send)) {
		thd_current->state = STATE_WAITRECV;
		thd_current->msg_recv_iov = data;
		thd_current->msg_recv_cnt = iovcnt;
		TAILQ_INSERT_TAIL(&mc->blocked_recv, thd_current, thdq);
		thd_schedule();
		return;
	}

	/* Grab the top waiting thread and remove it from the queue */
	thd = TAILQ_FIRST(&mc->blocked_send);
	TAILQ_REMOVE(&mc->blocked_send, thd, thdq);

	/* Copy the message data */
	if (data != NULL && iovcnt > 0)
		rv = mmu_copyv(thd->pid, thd->msg_send_iov, thd->msg_send_cnt,
			thd_current->pid, data, iovcnt);
	else
		rv = 0;
	thd->msg_send_iov = NULL; thd->msg_send_cnt = 0;

	/* Change the sending thread's state to a reply state */
	thd->state = STATE_WAITREPLY;
	TAILQ_INSERT_TAIL(&mc->blocked_reply, thd, thdq);

	/* Leave the receiving thread active */
	RETURN(rv);
}

/* Reply to a message on the given channel; if the channel has no
   threads queued in a receive-blocked state, then an error is
   returned (this should not happen normally). If the reply
   succeeds, both caller and callee will be unblocked; the
   code will be returned to the original sender, and optionally,
   a chunk of data. */
void sc_msg_replyv(channel_t id, int retval, iovec_t *data, int iovcnt) {
	msgchan_t	*mc;
	kthread_t	*thd;

	/* Look up the channel ID */
	mc = chan_by_id(id);
	if (mc == NULL) {
		RETURN(-1);
	}

	/* If no one is blocked on reply, then return an error */
	if (TAILQ_EMPTY(&mc->blocked_reply)) {
		RETURN(-1);
	}

	/* Grab the top waiting thread and remove it from the queue */
	thd = TAILQ_FIRST(&mc->blocked_reply);
	TAILQ_REMOVE(&mc->blocked_reply, thd, thdq);

	/* Copy the message data, if any */
	if (data != NULL && iovcnt > 0)
		mmu_copyv(thd_current->pid, data, iovcnt,
			thd->pid, thd->msg_recv_iov, thd->msg_recv_cnt);
	thd->msg_recv_iov = NULL; thd->msg_recv_cnt = 0;

	/* Set the return value */
	SET_RETURN(thd, retval);

	/* Change the original sender's state to ready */
	thd->state = STATE_READY;
	thd_add_to_runnable(thd);

	/* Return to the replying thread */
	RETURN(0);
}

/* Free all message channels for the given process' pid */
void msg_chan_freeall(pid_t pid) {
	msgchan_t *n1, *n2;

	n1 = LIST_FIRST(&chan_list);
	while (n1 != NULL) {
		n2 = LIST_NEXT(n1, g_list);
		if (n1->owner == pid) {
			LIST_REMOVE(n1, g_list);
			msg_chan_destroy(n1);
		}
		n1 = n2;
	}
}

/* Initialize message channel structures */
int msg_init() {
	chan_highest = 0;
	LIST_INIT(&chan_list);
	return 0;
}

/* Shut down message channel structures */
void msg_shutdown() { }
