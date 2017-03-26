/* KallistiOS ##version##

   lwip_accept.c
   Copyright (C)2003 Dan Potter
*/

#include <lwip/lwip.h>
#include <sys/process.h>

CVSID("$Id: lwip_accept.c,v 1.1 2003/07/31 00:48:09 bardtx Exp $");

int lwip_accept(int s, struct sockaddr *addr, socklen_t *addrlen) {
	return _lwip_accept(_local_process, s, addr, addrlen);
}
