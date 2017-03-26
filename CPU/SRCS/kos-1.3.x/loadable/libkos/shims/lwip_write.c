/* KallistiOS ##version##

   lwip_write.c
   Copyright (C)2003 Dan Potter
*/

#include <lwip/lwip.h>
#include <sys/process.h>

CVSID("$Id: lwip_write.c,v 1.1 2003/07/31 00:48:09 bardtx Exp $");

int lwip_write(int s, const void *mem, int len) {
	return _lwip_write(_local_process, s, mem, len);
}
