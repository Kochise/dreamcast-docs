/* KallistiOS ##version##

   sio.c
   Copyright (C)2004 Dan Potter
*/

#include <dc/scif.h>
#include <kos/thread.h>
#include <lwip/lwip.h>
#include "lwip/sio.h"

/*
  This implements the serial I/O interface for lwIP to use PPP for serial
  connections. This hooks straight to dbgio right now but could easily
  be swapped over to use the modem stuff.
 */

static volatile int sio_abort = 0;

sio_fd_t sio_open(u8_t foo) {
	int i;
	
	sio_abort = 0;

	// Clear out anything in the buffer already
	i = 0;
	while (scif_read() != -1)
		i++;
	if (i)
		printf("sio: cleared %d initial chars\n", i);

	return NULL;
}

void sio_send(u8_t ch, sio_fd_t foo) {
	scif_write(ch);
	scif_flush();
}

u8_t sio_recv(sio_fd_t foo) {
	int ch;

	do {
		ch = scif_read();
		if (ch == -1)
			thd_sleep(10);
	} while (ch == -1 && !sio_abort);

	sio_abort = 0;
	return ch;
}

// I *think* this is right, but sio_* seems to be totally
// undocumented like so many things in lwIP.
u32_t sio_read(sio_fd_t foo, u8_t *outbuf, u32_t bufmax) {
	int i, ch;

	for (i=0; i<bufmax && !sio_abort; i++) {
		ch = scif_read();
		if (ch == -1) {
			if (i == 0) {
				thd_sleep(10);
				i--;
				continue;
			} else
				break;
		}
		outbuf[i] = ch;
	}

	sio_abort = 0;
	return i;
}

// Ditto on the comment for sio_read.
u32_t sio_write(sio_fd_t foo, u8_t *buf, u32_t buflen) {
	int i;

	for (i=0; i<buflen && !sio_abort; i++)
		scif_write(buf[i]);
	scif_flush();

	sio_abort = 0;
	return buflen;
}

void sio_read_abort(sio_fd_t foo) {
	sio_abort = 1;
	printf("sio_read_abort called\n");
	while (sio_abort)
		thd_sleep(10);
}
