/* KallistiOS ##version##

   lwip_socket.c
   Copyright (C)2003 Dan Potter
*/

#include <lwip/lwip.h>
#include <sys/process.h>

CVSID("$Id: lwip_socket.c,v 1.1 2003/07/31 00:48:09 bardtx Exp $");

int lwip_socket(int domain, int type, int protocol) {
	return _lwip_socket(_local_process, domain, type, protocol);
}
