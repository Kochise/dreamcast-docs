/* KallistiOS ##version##

   msg.c
   (c)2001 Dan Potter
*/

/* Defines basic message passing primitives */

/**************************************/

#include <string.h>

#include <kos/kmalloc.h>
#include <kos/process.h>
#include <kos/mm.h>
#include <kos/limits.h>
#include <kos/msg.h>
#include <sys/queue.h>
#include <arch/syscall.h>
#include <arch/mmu.h>

CVSID("$Id: msg.c,v 1.2 2002/01/06 01:14:48 bardtx Exp $");


typedef struct msgchan {
	/* List entry for the global list of message channels */
	LIST_ENTRY(msgchan)	g_list;

	channel_t	id;			/* Channel ID */
	pid_t		owner;			/* Process that owns this channel */
	char		name[MAX_FN_LEN];	/* Channel name */
	

	/* Threads blocked waiting to receive */
	struct ktqueue	blocked_recv;

	/* Threads blocked waiting to send */
	struct ktqueue	blocked_send;

	/* Threads blocked waiting for a reply */
	struct ktqueue	blocked_reply;
} msgchan_t;

LIST_HEAD(msgchanlist, msgchan);

/**************************************/

/* Highest message channel ID */
static channel_t chan_highest;

/* Global list of message channels */
static struct msgchanlist chan_list;

/* Allocate a new message channel; the channel will be assigned
   to the calling process and when that process dies, the channel
   will also die. */
void sc_msg_chan_create(const char *name) {
	msgchan_t	*mc;

	/* Create a message channel structure */
	mc = (msgchan_t*)kmalloc(sizeof(msgchan_t));
	mc->id = ++chan_highest;
	mc->owner = thd_current->pid;
	mmu_copyin(proc_current->pid, (uint32)name, MAX_FN_LEN, mc->name);
	mc->name[MAX_FN_LEN-1] = '\0';
	TAILQ_INIT(&mc->blocked_recv);
	TAILQ_INIT(&mc->blocked_send);
	TAILQ_INIT(&mc->blocked_reply);

	/* Add to the global list */
	LIST_INSERT_HEAD(&chan_list, mc, g_list);

	RETURN(mc->id);
}

/* Return the message channel structure by ID */
static msgchan_t *chan_by_id(channel_t id) {
	msgchan_t	*chan;

	LIST_FOREACH(chan, &chan_list, g_list) {
		if (chan->id == id)
			break;
	}
	return chan;
}

/* Return the message channel structure by name */
static msgchan_t *chan_by_name(const char *name) {
	msgchan_t	*chan;
	char		kn[MAX_FN_LEN];

	mmu_copyin(proc_current->pid, (uint32)name, MAX_FN_LEN, kn);
	LIST_FOREACH(chan, &chan_list, g_list) {
		if (!strcmp(kn, chan->name))
			break;
	}
	return chan;
}

/* Take care of destroying a message channel */
static void msg_chan_destroy(msgchan_t *mc) {
	/* XXX Do something with queued threads */

	/* Free the memory */
	kfree(mc);
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
