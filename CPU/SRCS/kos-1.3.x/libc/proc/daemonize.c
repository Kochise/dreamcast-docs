/* KallistiOS ##version##

   daemonize.c
   Copyright (C)2003 Dan Potter
*/

#include <unistd.h>
#include <errno.h>
#include <sys/process.h>

CVSID("$Id: daemonize.c,v 1.1 2003/07/15 07:57:20 bardtx Exp $");

int daemonize() {
	return process_daemonize(_local_process);
}
