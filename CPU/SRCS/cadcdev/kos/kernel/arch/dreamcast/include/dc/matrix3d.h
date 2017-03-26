/* KallistiOS ##version##

   matrix3d.h
   (c)2000 Dan Potter and Jordan DeLong

   $Id: matrix3d.h,v 1.1 2002/09/05 07:32:57 bardtx Exp $

*/

#ifndef __KOS_MATRIX3D_H
#define __KOS_MATRIX3D_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <dc/matrix.h>

void mat_rotate_x(float r);
void mat_rotate_y(float r);
void mat_rotate_z(float r);
void mat_rotate(float xr, float yr, float zr);
void mat_translate(float x, float y, float z);
void mat_scale(float x, float y, float z);

/**
  This sets up a perspective view frustum for basic 3D usage. The xcenter
  and ycenter parameters are dependent on your screen resolution (or however
  you want to do it); cot_fovy_2 is 1.0/tan(view_angle/2). Use 1.0 for a
  normal 90' view. znear and zfar are what they sound like. */
void mat_perspective(float xcenter, float ycenter, float cot_fovy_2,
	float znear, float zfar);

/**
  Performs a "camera" function with rotations and translations. */
void mat_lookat(const point_t * eye, const point_t * center, const vector_t * up);

__END_DECLS

#endif	/* __KOS_MATRIX3D_H */


