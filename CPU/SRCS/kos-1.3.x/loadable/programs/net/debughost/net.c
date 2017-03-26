/* KallistiOS ##version##

   net.c
   Copyright (C)2003 Dan Potter

   $Id: net.c,v 1.1 2003/07/15 07:55:04 bardtx Exp $
*/

#include <kos.h>
#include <signal.h>
#include <lwip/lwip.h>
#include <lwip/sockets.h>
#include "debug.h"

////////////////////////////////////////////////////////////////////////

volatile int quitflag = 0;

static struct nconnlist nconns;
static mutex_t * list_mutex;

static void nc_init() {
	TAILQ_INIT(&nconns);
	list_mutex = mutex_create();
}

static void nc_shutdown() {
	mutex_destroy(list_mutex);
}

static nconn_t * nc_create() {
	nconn_t * nc;

	nc = calloc(1, sizeof(nconn_t));
	mutex_lock(list_mutex);
	TAILQ_INSERT_TAIL(&nconns, nc, list);
	mutex_unlock(list_mutex);

	return nc;
}

void nc_destroy(nconn_t *nc) {
	mutex_lock(list_mutex);
	TAILQ_REMOVE(&nconns, nc, list);
	mutex_unlock(list_mutex);
	free(nc);
}

////////////////////////////////////////////////////////////////////////

static int sighnd(int sig, void * data) {
	quitflag = 1;
	return 0;
}

////////////////////////////////////////////////////////////////////////

int net_write_reliably(int fd, const void * buffer, int size) {
	int offs, r;
	const uint8 * b8 = (const uint8 *)buffer;

	offs = 0;
	while (size > 0) {
		r = write(fd, (void *)(b8+offs), size);
		if (r <= 0 || quitflag)
			return -1;
		size -= r;
		offs += r;
	}

	return 0;
}

int net_read_reliably(int fd, void * buffer, int size) {
	int offs, r;
	uint8 * b8 = (uint8 *)buffer;

	offs = 0;
	while (size > 0) {
		r = read(fd, b8+offs, size);
		if (r <= 0 || quitflag)
			return -1;
		size -= r;
		offs += r;
	}

	return 0;
}

// This is undoubtedly slow, but accurate and easy
int net_read_line(int fd, char * buffer, int maxsize) {
	int r, rt;
	char c;

	rt = 0;
	do {
		if (rt >= maxsize)
			break;
		r = read(fd, &c, 1);
		if (r <= 0)
			return -1;
		buffer[rt++] = c;
	} while (c != '\n');

	buffer[rt-1] = 0;
	if (buffer[rt-2] == '\r')
		buffer[rt-2] = 0;

	return rt;
}

int net_write_line(int fd, const char * line) {
	return net_write_reliably(fd, line, strlen(line));
}

////////////////////////////////////////////////////////////////////////

static void net_thread(void * param) {
	nconn_t * nc = (nconn_t *)param;

	tty_printf("Connection from %d.%d.%d.%d, port %d, socket %d\n",
		ip4_addr1((struct ip_addr *)&nc->client.sin_addr.s_addr),
		ip4_addr2((struct ip_addr *)&nc->client.sin_addr.s_addr),
		ip4_addr3((struct ip_addr *)&nc->client.sin_addr.s_addr),
		ip4_addr4((struct ip_addr *)&nc->client.sin_addr.s_addr),
		nc->client.sin_port, nc->socket);

	proto_do_connection(nc);

	close(nc->socket);

	tty_printf("Connection %d closed\n", nc->socket);
	nc_destroy(nc);
}

////////////////////////////////////////////////////////////////////////

static void net_connect(int fd, struct sockaddr_in * addr) {
	nconn_t * nc;

	nc = nc_create();
	nc->socket = fd;
	nc->client = *addr;
	nc->thd = thd_create(net_thread, nc);
}

int net_doloop() {
	int	listenfd = -1;
	struct sockaddr_in saddr;
	struct timeval timeout;
	fd_set	readset;
	fd_set	writeset;
	int	i, maxfdp1;

	signal(SIGQUIT, sighnd);
	nc_init();

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd < 0) {
		tty_printf("Socket create failed.\n");
		goto bail;
	}

	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(6300);

	if (bind(listenfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
		tty_printf("Bind to socket failed.\n");
		goto bail;
	}

	if (listen(listenfd, 10) < 0) {
		tty_printf("Listen failed.\n");
		goto bail;
	}

	timeout.tv_sec = 0;
	timeout.tv_usec = 500*1000;

	tty_printf("Listening for connections on port 6300.\n");

	while (!quitflag) {
		maxfdp1 = listenfd + 1;

		FD_ZERO(&readset);
		FD_ZERO(&writeset);
		FD_SET(listenfd, &readset);

		i = select(maxfdp1, &readset, &writeset, 0, &timeout);
		if (i == 0) continue;

		if (FD_ISSET(listenfd, &readset)) {
			struct sockaddr_in client;
			socklen_t client_size;
			int socket;

			client_size = sizeof(client);
			socket = accept(listenfd,
				(struct sockaddr *)&client,
				&client_size);
			net_connect(socket, &client);
		}
	}

bail:
	if (listenfd >= 0)
		close(listenfd);
	nc_shutdown();
	tty_printf("Exiting net loop and preparing to quit.\n");

	return 0;
}

