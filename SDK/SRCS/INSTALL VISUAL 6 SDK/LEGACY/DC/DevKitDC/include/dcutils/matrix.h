/* KallistiOS 1.1.6

   matrix.h
   (c)2000 Dan Potter

   $Id: matrix.h,v 1.2 2002/01/05 07:23:32 bardtx Exp $
*/

#ifndef __MATRIX_H
#define __MATRIX_H

#include <sys/cdefs.h>
__BEGIN_DECLS

/* Matrix definition (4x4) */
typedef float matrix_t[4][4];

/* Vector/point definition */
typedef struct { float x, y, z; } vector_t;
typedef vector_t point_t;

/* Fill in an identity matrix */
/* void mat_make_identity(matrix_t *out); */

/* Copy the internal matrix out to a memory one */
void mat_store(matrix_t *out);

/* Copy a memory matrix into the internal one */
void mat_load(matrix_t *out);

/* Clear internal to an identity matrix */
void mat_identity();

/* "Apply" a matrix: multiply a matrix onto the "internal" one */
void mat_apply(matrix_t *src);

/* Transform zero or more sets of vectors using the current internal
   matrix. Each vector is three floats long. */
void mat_transform(vector_t *invecs, vector_t *outvecs, int veccnt, int vecskip);

__END_DECLS

#endif	/* __MATRIX_H */

