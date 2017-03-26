/* KallistiOS ##version##

   debug.h
   Copyright (C)2003 Dan Potter

   $Id: debug.h,v 1.2 2003/07/18 08:13:27 bardtx Exp $
*/

#ifndef __DEBUG_H
#define __DEBUG_H

#include <sys/cdefs.h>
#include <sys/queue.h>

#include <lwip/lwip.h>
#include <lwip/sockets.h>

// Our version string
#define VERSION "1.0"
#define VERSION_STRING "KOS IP Debug Host " VERSION

// Minimalist tty
int tty_init();
void tty_shutdown();
void tty_clear();
void tty_refresh();
void tty_setcol(int f, int b);
void tty_printf(const char * fmt, ...) __printflike(1, 2);
void tty_freeze();
void tty_thaw();

#define TTY_WHITE	0
#define TTY_GREEN	1
#define TTY_PURPLE	2
#define TTY_YELLOW	3
#define TTY_BLUE	4
#define TTY_DEFAULT_FG	TTY_WHITE
#define TTY_DEFAULT_BG	TTY_PURPLE

// Network meatiness
extern volatile int quitflag;

typedef struct nconn {
	TAILQ_ENTRY(nconn)	list;

	// Client->Target connection
	int			socket;
	struct sockaddr_in	client;

	// Target->Client connection for file serving
	int			fservsock;

	// Client->Target thread
	kthread_t		* thd;
} nconn_t;

TAILQ_HEAD(nconnlist, nconn);

int net_doloop();
int net_write_reliably(int fd, const void * buffer, int size);
int net_read_reliably(int fd, void * buffer, int size);
int net_read_line(int fd, char * buffer, int maxsize);
int net_write_line(int fd, const char * line);

// Protocol handling
void proto_do_connection(nconn_t * nc);

// File server
int fserv_init(nconn_t * nc);
int fserv_shutdown();

#endif	/* __DEBUG_H */
