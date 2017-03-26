/* KallistiOS ##version##

   lwip_read.c
   Copyright (C)2003 Dan Potter
*/

#include <lwip/lwip.h>
#include <sys/process.h>

CVSID("$Id: lwip_read.c,v 1.1 2003/07/31 00:48:09 bardtx Exp $");

int lwip_read(int s, void *mem, int len) {
	return _lwip_read(_local_process, s, mem, len);
}
