/* KallistiOS ##version##

   lwip_close.c
   Copyright (C)2003 Dan Potter
*/

#include <lwip/lwip.h>
#include <sys/process.h>

CVSID("$Id: lwip_close.c,v 1.1 2003/07/31 00:48:09 bardtx Exp $");

int lwip_close(int s) {
	return _lwip_close(_local_process, s);
}
