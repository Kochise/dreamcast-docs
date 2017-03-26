/* KallistiOS ##version##

   sockets.c
   Copyright (C)2003,2004 Dan Potter
*/

#include <kos/mutex.h>
#include <kos/cond.h>
#include <kos/genwait.h>
#include <errno.h>
#include <lwip/lwip.h>
#include <lwip/sockets.h>

/////////////////////////////////////////////////////////////////////////////
// Socket descriptors; we will eventually merge these with the VFS.

typedef struct sockfd {
	int	inuse;		// Are we using it?

	// Connection info
	int			type;		// Socket type (stream, dgram)
	struct sockaddr_in	name;		// Bound name
	struct tcp_pcb		* tcppcb;	// Used if SOCK_STREAM
	struct udp_pcb		* udppcb;	// Used if SOCK_DGRAM

	// Sync variables
	mutex_t		* mutex;	// For the condvars
	condvar_t	* connect;	// A connection was received on a listen()
	condvar_t	* recv_avail;	// Received data is available
	condvar_t	* send_avail;	// Send buffer space is available

	// Counters
	int		conncnt;	// Number of connections waiting
	int		recv;		// Bytes of data received
	int		send;		// Bytes of space available

	// Connection backlog. We have one slot for each potential connection.
	int		connmax;
	int		* conns;

	// Receive buffer backlog. If we get a recv_tcp, the pbuf will be
	// placed here until the app reads it. If we get another in the
	// meantime, we'll chain it.
	struct pbuf	* recv_buf;

	// If we're making an outgoing connection, we need to get back an
	// err_t for what happened.
	err_t		connerr;
} sockfd_t;

#define SOCKFD_CNT 32
static sockfd_t fds[SOCKFD_CNT] = { {0} };
static mutex_t * fd_mutex;

// We'll genwait on this for select
static int select_wait = 0;

// Forward-declare this
extern vfs_handler_t socketvfs;

// Allocate a new socket
static int sock_open() {
	int i;
	
	mutex_lock(fd_mutex);

	for (i=0; i<SOCKFD_CNT; i++)
		if (!fds[i].inuse) break;

	if (i >= SOCKFD_CNT)
		i = -1;
	else {
		// Clean it out and set it as in-use
		memset(fds+i, 0, sizeof(sockfd_t));
		fds[i].inuse = 1;
	}

	mutex_unlock(fd_mutex);

	// Setup some basic stuff
	fds[i].mutex = mutex_create();
	fds[i].connect = cond_create();
	fds[i].recv_avail = cond_create();
	fds[i].send_avail = cond_create();

	fds[i].connmax = 0;
	fds[i].conncnt = -1;
	fds[i].recv = -1;
	fds[i].send = -1;
	
	return i;
}

// Destroy an existing socket
static void sock_close(int fd) {
	if (!fds[fd].inuse) {
		dbglog(DBG_ERROR, "sock_close: socket %d not in use!\n", fd);
		return;
	}

	// Destroy all the sync objects
	cond_destroy(fds[fd].connect);
	cond_destroy(fds[fd].recv_avail);
	cond_destroy(fds[fd].send_avail);
	mutex_destroy(fds[fd].mutex);

	fds[fd].inuse = 0;
}

// Verify a socket #
static int sock_verify(int fd) {
	if (fd < 0 || fd >= SOCKFD_CNT) {
		errno = EBADF;
		return -1;
	}
	if (!fds[fd].inuse) {
		errno = EBADF;
		return -1;
	}

	return 0;
}

// Convert a VFS fd to a socket #
static int sock_for_fd(int fd) {
	int s;

	// Verify that it's actually one of ours
	if (fs_get_handler(fd) != &socketvfs) {
		errno = EBADF;
		return -1;
	}

	// Get the socket #
	s = (int)fs_get_handle(fd); s--;
	if (s < 0) {
		errno = EBADF;
		return -1;
	}

	// Verify it
	if (sock_verify(s) < 0)
		return -1;
	else
		return s;
}

/////////////////////////////////////////////////////////////////////////////
// TCP callbacks

static err_t peerclosed_tcp(int s, struct tcp_pcb *pcb) {
	sockfd_t	* fd;

	// Get the socket struct and lock
	if (sock_verify(s) < 0) {
		if (tcp_close(pcb) != ERR_OK)
			tcp_abort(pcb);
	} else {
		fd = fds + s;

		// Get access.
		mutex_lock(fd->mutex);

		// Make sure no more reads/writes go through.
		fd->recv = fd->send = -1;

		// Wake up anyone who was waiting
		cond_broadcast(fd->recv_avail);
		cond_broadcast(fd->send_avail);

		mutex_unlock(fd->mutex);

		genwait_wake_all(&select_wait);
	}

	return ERR_OK;
}

// This works for both UDP and TCP.
static err_t recv_data(int s, struct pbuf * p) {
	sockfd_t	* fd;

	// Get our socket.
	if (sock_verify(s) < 0)
		return ERR_CONN;
	fd = fds + s;

	// Get access.
	mutex_lock(fd->mutex);

	// Do we already have some data chained up in pbufs?
	if (fd->recv_buf) {
		pbuf_chain(fd->recv_buf, p);
		pbuf_free(p);
	} else
		fd->recv_buf = p;

	// Set a new receive count
	fd->recv = fd->recv_buf->tot_len;

	// Here would be the place we'd want to implement TCP_NODELAY (or the lack
	// thereof) but for now we'll just send it all through...
	cond_signal(fd->recv_avail);

	// Note that we DON'T ACK the data until after a client has received
	// it using recv(). Otherwise the peer could send and send and send...

	mutex_unlock(fd->mutex);

	genwait_wake_all(&select_wait);

	return ERR_OK;
}

static err_t recv_tcp(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err) {
	// printf("kti: recv_tcp for %d called (pcb %p, pbuf %p, len %lu, err %d)\n", (int)arg, pcb, p, p->tot_len, err);
	if (p)
		return recv_data((int)arg, p);
	else
		return peerclosed_tcp((int)arg, pcb);
}

static err_t sent_tcp(void *arg, struct tcp_pcb *pcb, u32_t len) {
	int		s, rdy;
	sockfd_t	* fd;

	// printf("kti: sent_tcp for %d called (len %lu)\n", (int)arg, len);

	// Get the socket struct and lock
	s = (int)arg;
	if (sock_verify(s) < 0)
		return ERR_CONN;
	fd = fds + s;

	// Get access.
	mutex_lock(fd->mutex);

	// Add more buffer space available.
	fd->send += len;

	// Notify anyone waiting, if we have sufficient space (avoid silly
	// packet syndrome).
	rdy = fd->send >= 256;
	if (rdy)
		cond_signal(fd->send_avail);

	mutex_unlock(fd->mutex);

	if (rdy)
		genwait_wake_all(&select_wait);

	return ERR_OK;
}

static err_t poll_tcp(void *arg, struct tcp_pcb *pcb) {
	// printf("kti: poll_tcp for %d called\n", (int)arg);
	return ERR_OK;
}

static void err_tcp(void *arg, err_t err) {
	// printf("kti: err_tcp for %d called (err %d)\n", (int)arg, err);
}

static err_t accept_tcp(void *arg, struct tcp_pcb *pcb, err_t err) {
	int		s, i, ns;
	sockfd_t	* fd, * nsd;
	err_t		rv = ERR_OK;

	// printf("kti: accept_tcp for %d called (err %d)\n", (int)arg, err);

	// Dunno what to do here if not...
	assert( err == ERR_OK );

	// Get the socket struct and lock
	s = (int)arg;
	if (sock_verify(s) < 0)
		return ERR_CONN;
	fd = fds + s;

	// Get access.
	mutex_lock(fd->mutex);

	// Do we have enough space?
	if (fd->conncnt >= fd->connmax) {
		rv = ERR_MEM;
		goto out;
	}

	// Add the connection
	for (i=0; i<fd->connmax; i++)
		if (fd->conns[i] < 0)
			break;
	if (i >= fd->connmax) {
		assert( 0 );
		rv = ERR_MEM;
		goto out;
	}

	// Create a new socket FD for the connection.
	ns = sock_open();
	if (ns < 0) {
		rv = ERR_MEM;
		goto out;
	}

	// Assign stuff. We've already got our sync objects, we just
	// need to get things into it. To make sure nothing weird happens
	// here, we'll lock first.
	nsd = fds + ns;
	mutex_lock(nsd->mutex);

	nsd->tcppcb = pcb;

	// Init our counters
	nsd->recv = 0;
	nsd->send = tcp_sndbuf(nsd->tcppcb);

	// Setup callbacks
	tcp_arg(nsd->tcppcb, (void *)ns);
	tcp_recv(nsd->tcppcb, recv_tcp);
	tcp_sent(nsd->tcppcb, sent_tcp);
	tcp_poll(nsd->tcppcb, poll_tcp, 4);	// 4 == 4 TCP timer intervals
	tcp_err(nsd->tcppcb, err_tcp);

	// Copy over the peer address
	nsd->name.sin_len = sizeof(struct sockaddr_in);
	nsd->name.sin_family = AF_INET;
	nsd->name.sin_port = htons(nsd->tcppcb->remote_port);
	nsd->name.sin_addr.s_addr = nsd->tcppcb->remote_ip.addr;

	mutex_unlock(nsd->mutex);


	fd->conns[i] = ns;
	fd->conncnt++;

	// Signal any thread waiting on accept()
	cond_signal(fd->connect);

out:
	mutex_unlock(fd->mutex);
	if (rv == ERR_OK)
		genwait_wake_all(&select_wait);
	return rv;
}

static err_t connect_tcp(void * arg, struct tcp_pcb * pcb, err_t err) {
	int		s;
	sockfd_t	* fd;
	err_t		rv = ERR_OK;

	// printf("kti: connect_tcp for %d called (err %d)\n", (int)arg, err);

	// Get the socket struct and lock
	s = (int)arg;
	if (sock_verify(s) < 0)
		return ERR_CONN;
	fd = fds + s;

	// Get access.
	mutex_lock(fd->mutex);

	// Set the result error code
	fd->connerr = err;

	// Signal to proceed
	cond_signal(fd->connect);

	mutex_unlock(fd->mutex);

	return rv;
}

/////////////////////////////////////////////////////////////////////////////
// UDP callbacks

static void recv_udp(void *arg, struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, u16_t port) {
	// printf("kti: recv_udp for %d called\n", (int)arg);

	// This perhaps still needs work... depends on how lwIP implements
	// UDP routing internally. Could cause problems with having multiple UDP
	// connections if it does it wrong though.
	recv_data((int)arg, p);
}
         
/////////////////////////////////////////////////////////////////////////////
// Socket API

int lwip_socket(int domain, int type, int protocol) {
	int s, fd;

	// We only support basic internet protocols
	if (domain != AF_INET || protocol != 0 || (type != SOCK_STREAM && type != SOCK_DGRAM)) {
		errno = EPROTONOSUPPORT;
		return -1;
	}

	// Allocate a new socket for it
	s = sock_open();
	if (s < 0) {
		errno = ENFILE;
		return -1;
	}
	fds[s].type = type;

	// Make a VFS socket for it
	fd = fs_open_handle(&socketvfs, (void *)(s+1));
	if (fd < 0) {
		sock_close(s);
	}

	return fd;
}

// This function is called by both lwip_close and the fs_close handler. It
// expects a socket #, not a VFS fd.
static int close_common(int s) {
	// Make sure we have access
	mutex_lock(fds[s].mutex);

	// Close off any lwIP hooks
	if (fds[s].tcppcb) {
		struct tcp_pcb * pcb = fds[s].tcppcb;

		tcp_arg(pcb, NULL);

		if (pcb->state == LISTEN) {
			tcp_accept(pcb, NULL);
			tcp_close(pcb);
		} else {
			tcp_sent(pcb, NULL);
			tcp_recv(pcb, NULL);
			tcp_poll(pcb, NULL, 0);
			tcp_err(pcb, NULL);
			if (tcp_close(pcb) != ERR_OK) {
				tcp_abort(pcb);
			}
		}
	}
	if (fds[s].udppcb) {
		fds[s].udppcb->recv_arg = NULL;
		udp_remove(fds[s].udppcb);
	}

	// Free unanswered backlog connections as well
	if (fds[s].conns) {
		int i;
		for (i=0; i<fds[s].connmax; i++) {
			if (fds[s].conns[i] >= 0)
				close_common(fds[s].conns[i]);
		}
		free(fds[s].conns);
	}

	// Close the socket
	sock_close(s);

	return 0;
}

static void lwip_vfs_close(void * hnd) {
	close_common(((int)hnd) - 1);
}

int lwip_close(int s) {
	fs_close(s);
	return 0;
}

int lwip_connect(int s, struct sockaddr *name, socklen_t namelen) {
	sockfd_t	* fd;
	struct ip_addr	ip;
	int		port, rv = 0;

	s = sock_for_fd(s);
	if (s < 0) {
		errno = EBADF;
		return -1;
	}
	fd = fds + s;

	// Make sure it's an internet address we understand.
	if (namelen != sizeof(struct sockaddr_in)) {
		errno = ENAMETOOLONG;
		return -1;
	}

	// Get access
	mutex_lock(fd->mutex);

	// Copy it over
	memcpy(&fd->name, name, namelen);

	// Convert this to an lwIP-happy format
	ip.addr = ((struct sockaddr_in *)name)->sin_addr.s_addr;
	port = ((struct sockaddr_in *)name)->sin_port;

	// Are we TCP or UDP?
	switch (fd->type) {
	case SOCK_STREAM:
		// This might have gotten made already, bind is valid on
		// outgoing sockets too.
		if (!fd->tcppcb)
			fd->tcppcb = tcp_new();
		tcp_arg(fd->tcppcb, (void *)s);
		tcp_recv(fd->tcppcb, recv_tcp);
		tcp_sent(fd->tcppcb, sent_tcp);
		tcp_poll(fd->tcppcb, poll_tcp, 4);	// 4 == 4 TCP timer intervals
		tcp_err(fd->tcppcb, err_tcp);
		if (tcp_connect(fd->tcppcb, &ip, ntohs(port), connect_tcp) != ERR_OK) {
			if (tcp_close(fd->tcppcb) != ERR_OK)
				tcp_abort(fd->tcppcb);
			fd->tcppcb = NULL;
			errno = EINVAL;
			rv = -1; goto out;
		}
		break;
	case SOCK_DGRAM:
		// This might have gotten made already, bind is valid on
		// outgoing sockets too.
		if (!fd->udppcb)
			fd->udppcb = udp_new();
		udp_recv(fd->udppcb, recv_udp, (void *)s);
		udp_connect(fd->udppcb, &ip, ntohs(port));
		break;
	default:
		assert( 0 );
		errno = EINVAL;
		rv = -1; goto out;
	}

	// If we are doing a TCP connect, we need to wait for the results
	// of the operation.
	if (fd->type == SOCK_STREAM) {
		// Wait for the result
		fd->connerr = 10;
		while (fd->connerr > 0) {
			cond_wait(fd->connect, fd->mutex);
		}

		// Convert error codes
		switch (fd->connerr) {
		case ERR_OK: break;
		
		case ERR_MEM:
		case ERR_BUF:
		case ERR_VAL:
		case ERR_ARG:
		case ERR_IF:
			errno = EINVAL;
			rv = -1;
			goto out;

		case ERR_ABRT:
		case ERR_RST:
		case ERR_CLSD:
		case ERR_CONN:
			errno = ECONNREFUSED;
			rv = -1;
			goto out;

		case ERR_RTE:
			errno = ENETUNREACH;
			rv = -1;
			goto out;

		case ERR_USE:
			errno = EADDRINUSE;
			rv = -1;
			goto out;
		}

		if (fd->connerr == ERR_OK) {
			// Init our counters
			fd->recv = 0;
			fd->send = tcp_sndbuf(fd->tcppcb);
		}
	}

out:
	mutex_unlock(fd->mutex);
	return rv;
}

int lwip_bind(int s, struct sockaddr *name, socklen_t namelen) {
	sockfd_t	* fd;
	struct ip_addr	ip;
	int		port, rv = 0;

	s = sock_for_fd(s);
	if (s < 0) {
		errno = EBADF;
		return -1;
	}
	fd = fds + s;

	// Make sure it's an internet address we understand.
	if (namelen != sizeof(struct sockaddr_in)) {
		errno = ENAMETOOLONG;
		return -1;
	}

	// Get access
	mutex_lock(fd->mutex);

	// Copy it over
	memcpy(&fd->name, name, namelen);

	// Convert this to an lwIP-happy format
	ip.addr = ((struct sockaddr_in *)name)->sin_addr.s_addr;
	port = ((struct sockaddr_in *)name)->sin_port;

	// Are we TCP or UDP?
	switch (fd->type) {
	case SOCK_STREAM:
		fd->tcppcb = tcp_new();
		tcp_arg(fd->tcppcb, (void *)s);
		tcp_recv(fd->tcppcb, recv_tcp);
		tcp_sent(fd->tcppcb, sent_tcp);
		tcp_poll(fd->tcppcb, poll_tcp, 4);	// 4 == 4 TCP timer intervals
		tcp_err(fd->tcppcb, err_tcp);
		if (tcp_bind(fd->tcppcb, &ip, ntohs(port)) != ERR_OK) {
			if (tcp_close(fd->tcppcb) != ERR_OK)
				tcp_abort(fd->tcppcb);
			fd->tcppcb = NULL;
			errno = EINVAL;
			rv = -1; goto out;
		}
		break;
	case SOCK_DGRAM:
		fd->udppcb = udp_new();
		udp_recv(fd->udppcb, recv_udp, (void *)s);
		udp_bind(fd->udppcb, &ip, ntohs(port));
		break;
	default:
		assert( 0 );
		errno = EINVAL;
		rv = -1; goto out;
	}

out:
	mutex_unlock(fd->mutex);
	return rv;
}

int lwip_listen(int s, int backlog) {
	struct tcp_pcb	* npcb;
	sockfd_t	* fd;
	int		rv = 0, i;

	s = sock_for_fd(s);
	if (s < 0) {
		errno = EBADF;
		return -1;
	}
	fd = fds + s;

	// Get access
	mutex_lock(fd->mutex);

	// Is it the right type?
	if (fd->type != SOCK_STREAM) {
		errno = EOPNOTSUPP;
		rv = -1; goto out;
	}

	// Verify that someone has called bind() on this socket.
	if (!fd->tcppcb) {
		// XXX Is this the right error?
		errno = EOPNOTSUPP;
		rv = -1; goto out;
	}

	// Make sure we're not already listening.
	if (fd->conns) {
		errno = EINVAL;
		rv = -1; goto out;
	}

	// Setup a listen block. We get a new one back here.
	npcb = tcp_listen(fd->tcppcb);
	if (!npcb) {
		errno = EADDRINUSE;
		rv = -1; goto out;
	}

	// Set the new pcb
	fd->tcppcb = npcb;

	// Init the connection count
	fd->conncnt = 0;
	fd->connmax = backlog;
	fd->conns = malloc(backlog * sizeof(int));
	for (i=0; i<backlog; i++)
		fd->conns[i] = -1;

	// Setup our accept callback
	tcp_accept(fd->tcppcb, accept_tcp);

out:
	mutex_unlock(fd->mutex);
	return rv;
}

int lwip_accept(int s, struct sockaddr *addr, socklen_t *addrlen) {
	sockfd_t	* fd;
	int		rv = 0, i, ns;

	s = sock_for_fd(s);
	if (s < 0) {
		errno = EBADF;
		return -1;
	}
	fd = fds + s;

	// Make sure it's an internet address we understand.
	if (addrlen && *addrlen != sizeof(struct sockaddr_in)) {
		errno = ENAMETOOLONG;
		return -1;
	}

	// Get access
	mutex_lock(fd->mutex);

	// Is it the right type?
	if (fd->type != SOCK_STREAM) {
		errno = EINVAL;
		rv = -1; goto out;
	}

	// Loop until we've got one
	while (fd->conncnt <= 0) {
		// Make sure we're listen()'ing
		if (fd->conncnt < 0) {
			///
			rv = -1; goto out;
		}

		// Wait for a connection
		// printf("lwip_accept(%d): waiting\n", s);
		cond_wait(fd->connect, fd->mutex);
	}

	// Ok, we've got a connection. Find the first available one
	// in the list and we'll take it.
	for (i=0; i<fd->connmax; i++) {
		if (fd->conns[i] >= 0) break;
	}
	if (i >= fd->connmax) {
		// This shouldn't happen...
		assert( 0 );
		errno = EAGAIN;
		goto out;
	}

	ns = fd->conns[i];
	fd->conns[i] = -1; fd->conncnt--;

	// Copy out the peer address as well
	if (addr)
		memcpy(addr, &fds[ns].name, sizeof(struct sockaddr_in));
	if (addrlen)
		*addrlen = sizeof(struct sockaddr_in);

	// Ok, everything should be ready to go! Just need to make a VFS
	// fd for this socket.
	rv = fs_open_handle(&socketvfs, (void *)(ns + 1));
	if (rv < 0) {
		close_common(ns);
	}

out:
	mutex_unlock(fd->mutex);
	return rv;
}

static int recv_common(int s, void * mem, int len, unsigned int flags, int istcp) {
	sockfd_t	* fd;
	int		rv = 0, amt, totalrcv;
	uint8		* buf;
	struct pbuf	* p;

	if (flags != 0) {
		errno = EINVAL;
		return -1;
	}

	if (len <= 0) {
		errno = EINVAL;
		return -1;
	}

	fd = fds + s;

	// printf("lwip_recv(%d): want %d bytes\n", s, len);

	// Get access
	mutex_lock(fd->mutex);

	// Is there data available now?
	while (fd->recv <= 0) {
		// Make sure we're capable of reading
		if (fd->recv < 0) {
			rv = 0; goto out;
		}

		// Wait for more data to be available
		//printf("cond_wait for more data\n");
		cond_wait(fd->recv_avail, fd->mutex);
		//printf("woken\n");
	}

	// Ok, some data should be available now
	assert( fd->recv_buf );
	if (!fd->recv_buf) {
		///
		rv = -1; goto out;
	}

	// Pull data out into the client buffer
	buf = (uint8 *)mem;
	totalrcv = 0;
	for (p = fd->recv_buf; p && len > 0; ) {
		// How much to pull from this pbuf?
		if (p->len > len)
			amt = len;
		else
			amt = p->len;

		//printf("  pbuf: %d avail, want %d\n", p->len, amt);

		// Do it.
		memcpy(buf, p->payload, amt);
		buf += amt;
		totalrcv += amt;
		len -= amt;

		// Did we take the whole thing?
		if (amt == p->len) {
			// Yes. Dechain it and move forwards.
			fd->recv_buf = p->next;
			if (fd->recv_buf)
				pbuf_ref(fd->recv_buf);
			pbuf_free(p);
			p = fd->recv_buf;
		} else {
			// Nope. Just adjust the "header".
			pbuf_header(p, -amt);
			p = NULL;
		}
	}

	// ACK the amount we actually read out
	//printf("lwip_read(%d): ACK'ing %d bytes\n", s, totalrcv);
	rv = totalrcv;
	if (istcp)
		tcp_recved(fd->tcppcb, rv);
	fd->recv -= rv;
	//printf("returning\n");

out:
	mutex_unlock(fd->mutex);	
	return rv;
}

static int send_common(int s, const void *mem, int size, unsigned int flags) {
	sockfd_t	* fd;
	int		rv = 0;
	err_t		err;

	if (flags != 0) {
		errno = EINVAL;
		return -1;
	}

	fd = fds + s;

	// Get access
	mutex_lock(fd->mutex);

	// Is there space available now?
	while (fd->send <= 0) {
		// Make sure we're capable of writing
		if (fd->send < 0) {
			// Probably EOF.
			rv = 0; goto out;
		}

		cond_wait(fd->send_avail, fd->mutex);
	}

	// Send as much as we can.
	if (size > fd->send)
		size = fd->send;

	// Do it
	err = tcp_write(fd->tcppcb, (void *)mem, size, 1);
	switch (err) {
	case ERR_OK:
		break;

	case ERR_MEM:
		errno = ENOMEM;
		rv = -1; goto out;

	case ERR_ABRT:
	case ERR_RST:
	case ERR_CLSD:
	case ERR_CONN:
	case ERR_RTE:
	case ERR_IF:
		fd->send = -1;
		rv = 0; goto out;
	}

	// Decrease the available space counter
	rv = size;
	fd->send -= size;

out:
	mutex_unlock(fd->mutex);
	return rv;
}

int lwip_recv(int s, void *mem, int len, unsigned int flags) {
	s = sock_for_fd(s);
	if (s < 0) {
		errno = EBADF;
		return -1;
	}

	return recv_common(s, mem, len, flags, 1);
}

int lwip_send(int s, const void *mem, int size, unsigned int flags) {
	s = sock_for_fd(s);
	if (s < 0) {
		errno = EBADF;
		return -1;
	}

	return send_common(s, mem, size, flags);
}

int lwip_read(int s, void *mem, int len) {
	return lwip_recv(s, mem, len, 0);
}

int lwip_write(int s, const void *mem, int len) {
	return lwip_send(s, mem, len, 0);
}

static ssize_t lwip_vfs_read(void * hnd, void * buffer, size_t cnt) {
	int s = ((int)hnd) - 1;
	return recv_common(s, buffer, cnt, 0, 1);
}

static ssize_t lwip_vfs_write(void * hnd, const void * buffer, size_t cnt) {
	int s = ((int)hnd) - 1;
	return send_common(s, buffer, cnt, 0);
}

static int select_poll(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset) {
	int i, cnt, s;
	fd_set nr, nw;

	FD_ZERO(&nr);
	FD_ZERO(&nw);

	// Go through and look for FDs we need to service.
	cnt = 0;
	for (i=0; i<maxfdp1; i++) {
		if (readset && FD_ISSET(i, readset)) {
			// Convert to a socket #
			s = sock_for_fd(i);
			if (s < 0) continue;
		
			// Don't screw with things that are locked
			if (mutex_is_locked(fds[s].mutex))
				continue;

			// If it's a listen socket, look for used connections.
			if (fds[s].conns) {
				if (fds[s].conncnt > 0) {
					FD_SET(i, &nr);
					cnt++;
				}
			} else {
				// Any data available? Or socket dead?
				if (fds[s].recv != 0) {
					FD_SET(i, &nr);
					cnt++;
				}
			}
		}

		if (writeset && FD_ISSET(i, writeset)) {
			// Convert to a socket #
			s = sock_for_fd(i);
			if (s < 0) continue;
		
			// Don't screw with things that are locked
			if (mutex_is_locked(fds[s].mutex))
				continue;

			// Any buffer space available? Or socket dead?
			if (fds[s].send != 0) {
				FD_SET(i, &nw);
				cnt++;
			}
		}
	}

	if (cnt > 0) {
		if (readset)
			memcpy(readset, &nr, sizeof(fd_set));
		if (writeset)
			memcpy(writeset, &nw, sizeof(fd_set));
	}

	return cnt;
}

int lwip_select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset,
	struct timeval *timeout)
{
	int rv = -1, old, tmo;

	// This is a fairly quick operation for us, and we don't want the
	// results to change out from under us. So unlike the BSD design,
	// we'll actually disable ints temporarily here.
	old = irq_disable();

	// Figure out the timeout in milliseconds
	if (!timeout)
		tmo = -1;
	else {
		tmo = timeout->tv_sec*1000 + timeout->tv_usec/1000;
	}

	// Until we have something...
	do {
		// Poll everything
		rv = select_poll(maxfdp1, readset, writeset, exceptset);

		if (rv == 0) {
			// Zero timeout -- report immediately
			if (tmo == 0)
				break;
			else if (!timeout)
				genwait_wait(&select_wait, "lwip_select", 0, NULL);
			else
				genwait_wait(&select_wait, "lwip_select", tmo, NULL);
		}
	} while (rv == 0);

	// In case of a timeout, zero the sets.
	if (!rv) {
		if (readset)
			FD_ZERO(readset);
		if (writeset)
			FD_ZERO(writeset);
	}

	// Restore stuff
	irq_restore(old);

	return rv;
}




int lwip_shutdown(int s, int how) {
	errno = ENOSYS;
	return -1;
}

int lwip_getpeername (int s, struct sockaddr *name, socklen_t *namelen) {
	errno = ENOSYS;
	return -1;
}

int lwip_getsockname (int s, struct sockaddr *name, socklen_t *namelen) {
	errno = ENOSYS;
	return -1;
}

int lwip_getsockopt (int s, int level, int optname, void *optval, socklen_t *optlen) {
	errno = ENOSYS;
	return -1;
}

int lwip_setsockopt (int s, int level, int optname, const void *optval, socklen_t optlen) {
	errno = ENOSYS;
	return -1;
}

// This is a super hacky implementation of recvfrom (and below, sendto).
// It assumes that send/recv are used on TCP only and recvfrom/sendto are
// used on UDP only. This really needs to be fixed eventually.
int lwip_recvfrom(int s, void *mem, int len, unsigned int flags,
	struct sockaddr *from, socklen_t *fromlen)
{
	s = sock_for_fd(s);
	if (s < 0) {
		errno = EBADF;
		return -1;
	}

	// XXX from / fromlen aren't filled in.

	return recv_common(s, mem, len, flags, 0);
}
	
int lwip_sendto(int s, const void *dataptr, int size, unsigned int flags, 
	struct sockaddr *to, socklen_t tolen)
{
	sockfd_t	* fd;
	struct ip_addr	ip;
	struct pbuf	* pbuf = NULL;
	int		port, rv = 0;
	err_t		err;

	if (flags != 0) {
		errno = EINVAL;
		return -1;
	}

	s = sock_for_fd(s);
	if (s < 0) {
		errno = EBADF;
		return -1;
	}
	fd = fds + s;

	// Get access
	mutex_lock(fd->mutex);

	// Make sure we're doing UDP here... we don't support sendto for TCP.
	if (fd->tcppcb) {
		errno = EINVAL;
		rv = -1; goto out;
	}

	// We might not have a udppcb still, if we just did socket().
	if (!fd->udppcb)
		fd->udppcb = udp_new();

	// Convert the address to an lwIP-happy format
	ip.addr = ((struct sockaddr_in *)to)->sin_addr.s_addr;
	port = ((struct sockaddr_in *)to)->sin_port;

	// Make sure we have the recv callback setup.
	fd->recv = 0;
	udp_recv(fd->udppcb, recv_udp, (void *)s);

	// Connect this to the specified destination.
	if ((err = udp_connect(fd->udppcb, &ip, ntohs(port))) != ERR_OK) {
		printf("connect: err is %d\n", err);
		// XXX Imprecise
		errno = ENOMEM;
		rv = -1; goto out;
	}

	// Make a pbuf for the data we want to send.
	pbuf = pbuf_alloc(PBUF_RAW, size, PBUF_POOL);
	if (pbuf == NULL) {
		printf("couldn't alloc pbuf of size %d\n", size);
		errno = ENOMEM;
		rv = -1; goto out;
	}
	{
		struct pbuf *q;
		const uint8 * src = (const uint8 *)dataptr;
		int i;
		for (q=pbuf; q; q=q->next) {
			//printf("putting %d bytes into pbuf @ %p\n",
			//	q->len, q);
			for (i=0; i<q->len; i++)
				((u8_t *)q->payload)[i] = *(src++);
		}
	}
	//memcpy(pbuf->payload, dataptr, size);

	// Send the data on the socket.
	if ((err = udp_send(fd->udppcb, pbuf)) != ERR_OK) {
		printf("send: err is %d\n", err);
		// XXX Imprecise
		errno = ENOMEM;
		rv = -1; goto out;
	}

	// Let go of the pbuf before returning.
	pbuf_free(pbuf); pbuf = NULL;

out:
	if (pbuf)
		pbuf_free(pbuf);
	mutex_unlock(fd->mutex);	
	return rv;
}
	
int lwip_ioctl(int s, long cmd, void *argp) {
	errno = ENOSYS;
	return -1;
}

char * lwip_strerr(err_t err) {
	return strerror(err);
}

/////////////////////////////////////////////////////////////////////////////
// Administrative details

vfs_handler_t socketvfs = {
	{
		{ 0 },
		0,
		0x00010000,
		0,
		NMMGR_TYPE_VFS,
		NMMGR_LIST_INIT
	},

	0, NULL,

	NULL,
	lwip_vfs_close,
	lwip_vfs_read,
	lwip_vfs_write
};

void tcp_timer_needed() {
	// Do nothing... they always get a timer! Bwahaha!
}

int kti_init() {
	fd_mutex = mutex_create();
	return 0;
}
