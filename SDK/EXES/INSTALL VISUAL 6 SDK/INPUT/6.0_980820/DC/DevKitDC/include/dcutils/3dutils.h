/* KallistiOS 1.1.6

   3dutils.h
   (c)2000 Dan Potter and Jordan DeLong

   $Id: 3dutils.h,v 1.2 2002/01/05 07:23:32 bardtx Exp $

*/

#ifndef __3DUTILS_H
#define __3DUTILS_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <dcutils/matrix.h>

/* Sin/Cos, angles 0..1023, values (-1.0,1.0) */
extern float sintab[];
#define isin(angle) sintab[(angle) % 1024]
#define icos(angle) sintab[((angle)+256) % 1024]


/* Perspective transform constants */
#define ZNEAR		1.0f
#define ZFAR		100.0f

void td_reset();
void td_rotate_x(float r);
void td_rotate_y(float r);
void td_rotate_z(float r);
void td_rotate(float xr, float yr, float zr);
void td_translate(float x, float y, float z);
void td_scale(float x, float y, float z);
void td_project();
void td_transform_vectors(vector_t *vi, vector_t *vo, int veccnt, int skip);

__END_DECLS

#endif	/* __3DUTILS_H */


