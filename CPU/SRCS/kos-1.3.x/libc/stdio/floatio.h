/* KallistiOS ##version##

   floatio.h
   (c)2001 Vincent Penne

   $Id: floatio.h,v 1.1 2002/02/09 06:15:43 bardtx Exp $
*/

#ifndef __LIBC_FLOATIO_H
#define __LIBC_FLOATIO_H

/* More or less random values, are they safe ? */
#define MAXEXP 100
#define MAXFRACT 100

/* we haven't them yet ... */
/* static int isinf(double d) { return 0; }
static int isnan(double d) { return 0; } */

/* use a very basic dtoa function */
#define __dtoa dtoa 

#endif	/* __LIBC_FLOATIO_H */

