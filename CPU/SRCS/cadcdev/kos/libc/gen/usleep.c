/* KallistiOS ##version##

   usleep.c
   Copyright (C)2001,2004 Dan Potter

   $Id: usleep.c,v 1.1 2002/02/09 06:15:42 bardtx Exp $
*/

#include <kos/thread.h>

/* usleep() */
void usleep(unsigned long usec) {
	thd_sleep (usec / 1000);
}

