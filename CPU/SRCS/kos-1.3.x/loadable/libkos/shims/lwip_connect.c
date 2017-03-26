/* KallistiOS ##version##

   lwip_connect.c
   Copyright (C)2003 Dan Potter
*/

#include <lwip/lwip.h>
#include <sys/process.h>

CVSID("$Id: lwip_connect.c,v 1.1 2003/07/31 00:48:09 bardtx Exp $");

int lwip_connect(int s, struct sockaddr *name, socklen_t namelen) {
	return _lwip_connect(_local_process, s, name, namelen);
}
