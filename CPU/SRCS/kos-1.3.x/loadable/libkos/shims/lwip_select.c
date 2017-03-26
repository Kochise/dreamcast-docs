/* KallistiOS ##version##

   lwip_select.c
   Copyright (C)2003 Dan Potter
*/

#include <lwip/lwip.h>
#include <sys/process.h>

CVSID("$Id: lwip_select.c,v 1.1 2003/07/31 00:48:09 bardtx Exp $");

int lwip_select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset, struct timeval *timeout) {
	return _lwip_select(_local_process, maxfdp1, readset, writeset, exceptset, timeout);
}
