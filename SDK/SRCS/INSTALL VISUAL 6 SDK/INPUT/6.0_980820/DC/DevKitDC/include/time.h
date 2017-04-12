/* KallistiOS 1.1.6

   time.h
   (c)2000 Dan Potter

   $Id: time.h,v 1.2 2002/01/05 07:23:32 bardtx Exp $

*/

#ifndef __TIME_H
#define __TIME_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

typedef uint32 time_t;

time_t time(time_t *t);
double difftime(time_t time1, time_t time0);

__END_DECLS

#endif	/* __TIME_H */

