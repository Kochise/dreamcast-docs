/* KallistiOS ##version##

   proto.c
   Copyright (C)2003 Dan Potter

   $Id: proto.c,v 1.4 2003/07/31 00:50:53 bardtx Exp $
*/

#include <kos.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/process.h>
#include "debug.h"

static int child_running = 0;
static int sigchld(int sig, void * ptr) {
	int rv;
	
	assert( child_running );

	rv = process_wait((kprocess_t *)ptr);
	child_running = 0;
	tty_thaw();
	tty_printf("Program finished, exit code %d\n", rv);

	return 0;
}

static int proto_recv_file(int fd, char * buffer) {
	char	* str, * fn, * sizes, *outbuf;
	int	size;
	uint64	ts, te;
	int	tt;
	file_t	of;

	if (child_running) {
		tty_printf("Client %d: child already running\n", fd);
		return net_write_line(fd, "Error: Child image already running\r\n");
	}

	// Parse the command
	str = buffer;
	if (strsep(&str, " ") == NULL)
		goto error;
	if ((fn = strsep(&str, " ")) == NULL)
		goto error;
	if ((sizes = strsep(&str, " ")) == NULL)
		goto error;
	size = atoi(sizes);

	tty_printf("Client %d: receiving to file '%s', size %d\n", fd, fn, size);

	// This works because /ram/ is always shorter than SendFile
	sprintf(buffer, "/ram/%s", fn);
	of = fs_open(buffer, O_RDWR | O_TRUNC);
	if (of < 0) {
		tty_printf("Client %d: can't open %s: %s\n",
			fd, buffer, strerror(errno));
		return net_write_line(fd, "Error: Can't open output file\r\n");
	}

	// Pre-allocate the buffer space with random garbage
	if (fs_write(of, (void *)proto_recv_file, size) < size) {
		tty_printf("Client %d: request too big\n", fd);
		return net_write_line(fd, "Error: Request too large\r\n");
	}

	fs_seek(of, 0, SEEK_SET);
	outbuf = fs_mmap(of);
	
	ts = timer_ms_gettime64();
	if (net_read_reliably(fd, outbuf, size) < 0) {
		tty_printf("Client %d: receive aborted\n", fd);
		return -1;
	}
	te = timer_ms_gettime64();
	tt = (int)(te - ts);

	tty_printf("Client %d: receive completed in %d.%03d seconds\n",
		fd, tt / 1000, tt % 1000);

	fs_close(of);

	return net_write_line(fd, "Ok: File received\r\n");

error:
	tty_printf("Client %d: incorrectly formed SendFile request\n", fd);
	return net_write_line(fd, "Error: Incorrectly formed command\r\n");
}

static int proto_run(int fd, char * buffer) {
	char	* str, * fn;
	kprocess_t	* p;

	// Parse the command
	str = buffer;
	if (strsep(&str, " ") == NULL)
		goto error;
	if ((fn = strsep(&str, " ")) == NULL)
		goto error;

	tty_printf("Client %d: executing file '%s'\n", fd, fn);

	if (fn[0] != '/') {
		sprintf(buffer + 1024, "/ram/%s", fn);
		fn = buffer + 1024;
	}

	// Stop any further screen updates
	tty_freeze();

	// Start the child process
	child_running = 1;
	p = process_vfork();
	if (!p) {
		tty_thaw();
		tty_printf("Client %d: vfork failed: %s\n", fd, strerror(errno));
		child_running = 0;
		return net_write_line(fd, "Error: vfork failed\r\n");
	}

	if (process_execv(fn, 1, (const char **)&fn) < 0) {
		tty_thaw();
		tty_printf("Client %d: execv failed: %s\n", fd, strerror(errno));
		child_running = 0;
		return net_write_line(fd, "Error: execv failed\r\n");
	}

	// Send a notification back to the host PC
	sprintf(buffer, "Ok: Process id is %d\r\n", process_get_pid(p));
	if (net_write_line(fd, buffer) < 0)
		return -1;

	return 0;

error:
	tty_printf("Client %d: incorrectly formed Run request\n", fd);
	return net_write_line(fd, "Error: Incorrectly formed command\r\n");
}

static int proto_fserv_start(nconn_t * nc, int port) {
	// Try to connect back to the client for a filesystem
	int			fd;
	struct sockaddr_in	saddr;
	socklen_t		slen;
	char			buffer[256];

	nc->fservsock = -1;

	// Make a new socket
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		tty_printf("Client %d: fserv socket create failed.\n", nc->socket);
		return -1;
	}

	// Connect back to the host machine if possible
	memcpy(&saddr, &nc->client, sizeof(struct sockaddr_in));
	saddr.sin_port = htons(port);
	slen = sizeof(struct sockaddr_in);
	if (connect(fd, (struct sockaddr *)&saddr, slen) < 0) {
		close(fd);
		tty_printf("Client %d: fserv socket connect failed.\n", nc->socket);
		return -1;
	}

	// Ok, looks like it worked. Go through the same handshake rigmarole.
	if (net_read_line(fd, buffer, 256) < 0) {
		close(fd);
		tty_printf("Client %d: fserv handshake failed.\n", nc->socket);
		return -1;
	}

	// Send back an Ok.
	sprintf(buffer, "%s\r\n", VERSION_STRING);
	if (net_write_line(fd, buffer) < 0) {
		close(fd);
		tty_printf("Client %d: fserv handshake failed.\n", nc->socket);
		return -1;
	}

	// We're golden. Save this FD and setup a VFS handler for it.
	nc->fservsock = fd;
	if (fserv_init(nc) < 0) {
		close(fd);
		tty_printf("Client %d: failed to setup fserv\n", nc->socket);
		return -1;
	}

	return 0;
}

static int proto_fserv_stop(nconn_t * nc) {
	// Make sure we have one
	if (nc->fservsock < 0)
		return 0;

	// Tell the fserv module to shut down
	fserv_shutdown();

	// Tell the host we're no longer interested
	net_write_line(nc->fservsock, "Quit\r\n");

	// Close the socket and return ok
	close(nc->fservsock);
	nc->fservsock = -1;

	return 0;
}

void proto_do_connection(nconn_t * nc) {
	char * buffer, * b2;
	int fservport;

	signal(SIGCHLD, sigchld);

	buffer = malloc(65536);
	
	// Do a version handshake
	if (net_write_line(nc->socket, VERSION_STRING "\r\n") < 0)
		return;

	if (net_read_line(nc->socket, buffer, 65536) < 0)
		return;

	// Are we supported?
	if (strncmp(buffer, "Ok: ", 4)) {
		return;
	}
	fservport = strtol(buffer + 4, &b2, 10);
	while (*b2 && isspace(*b2))
		b2++;

	tty_printf("Client %d identifies as '%s', fserv port %d\n",
		nc->socket, b2, fservport);

	// Connect back to setup a file server
	proto_fserv_start(nc, fservport);

	// Wait for further commands
	for ( ; ; ) {
		// Read a new command
		if (net_read_line(nc->socket, buffer, 65536) < 0)
			break;

		// Are we quitting the session?
		if (!strcmp(buffer, "Quit")) {
			tty_printf("Client %d requested disconnect\n", nc->socket);
			break;
		} else if (!strncmp(buffer, "SendFile: ", 10)) {
			if (proto_recv_file(nc->socket, buffer) < 0)
				break;
		} else if (!strncmp(buffer, "Run: ", 5)) {
			if (proto_run(nc->socket, buffer) < 0)
				break;
		} else {
			tty_printf("Client %d issued unknown command '%s'\n", nc->socket, buffer);
			if (net_write_line(nc->socket, "Error: Unknown command\r\n") < 0)
				break;
		}
	}

	// Stop the file server if necessary
	proto_fserv_stop(nc);
}
