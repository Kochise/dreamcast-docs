/* KallistiOS ##version##

   lwip_ioctl.c
   Copyright (C)2003 Dan Potter
*/

#include <lwip/lwip.h>
#include <sys/process.h>

CVSID("$Id: lwip_ioctl.c,v 1.1 2003/07/31 00:48:09 bardtx Exp $");

int lwip_ioctl(int s, long cmd, void *argp) {
	return _lwip_ioctl(_local_process, s, cmd, argp);
}
