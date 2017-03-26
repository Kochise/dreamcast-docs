/* KallistiOS ##version##

   unistd.h
   (c)2000-2001 Dan Potter

   $Id: unistd.h,v 1.2 2003/07/15 07:52:24 bardtx Exp $

*/

#ifndef __UNISTD_H
#define __UNISTD_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <stddef.h>
#include <arch/types.h>

#define true (1)
#define false (0)

void usleep(unsigned long usec);

/* Unix-like function that wraps process_daemonize */
int daemonize();

__END_DECLS

#endif	/* __UNISTD_H */

