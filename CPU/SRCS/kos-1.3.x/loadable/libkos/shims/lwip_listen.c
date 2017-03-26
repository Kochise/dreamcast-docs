/* KallistiOS ##version##

   lwip_listen.c
   Copyright (C)2003 Dan Potter
*/

#include <lwip/lwip.h>
#include <sys/process.h>

CVSID("$Id: lwip_listen.c,v 1.1 2003/07/31 00:48:09 bardtx Exp $");

int lwip_listen(int s, int backlog) {
	return _lwip_listen(_local_process, s, backlog);
}
