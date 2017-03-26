/* KallistiOS ##version##
   
   kos/vector.h
   (c)2002 Dan Potter

   $Id: vector.h,v 1.1 2002/09/05 07:31:55 bardtx Exp $

*/

#ifndef __KOS_VECTOR_H
#define __KOS_VECTOR_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/**
   KOS Platform independent 4-part vector data types. These are used by
   the matrix routines in the DC, and by bsplines in misc. */

/* Matrix definition (4x4) */
typedef float matrix_t[4][4];

/* Vector definition */
typedef struct vectorstr { float x, y, z, w; } vector_t;

/* Points are just vectors */
typedef vector_t point_t;

__END_DECLS

#endif	/* __KOS_VECTOR_H */

