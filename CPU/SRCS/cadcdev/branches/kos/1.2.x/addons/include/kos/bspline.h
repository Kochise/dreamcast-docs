/* KallistiOS ##version##

   bspline.h
   (c)2000 Dan Potter

   $Id: bspline.h,v 1.1 2002/09/05 07:31:55 bardtx Exp $
*/

#ifndef __KOS_BSPLINE_H
#define __KOS_BSPLINE_H

#include <sys/cdefs.h>
__BEGIN_DECLS

/** \file
   This module provides utility functions to generate b-spline
   curves in your program. It is used by passing in a set of
   control points to bspline_coeff, and then querying for
   individual points using bspline_get_point.
*/

#include <kos/vector.h>

/**
   Pass it an array of points and it will calculate a set of B-spline
   co-efficients for generating a curve. There must be at least one point
   before the "current" one, and at least two after the "current" one (a
   total of four points required). These values will be used in the 
   function below.
*/
void bspline_coeff(const point_t *pnt);

/**
   Given a 't' (between 0.0f and 1.0f) this will generate the next point
   values for the current set of coefficients.
*/
void bspline_get_point(float t, point_t *p);

__END_DECLS

#endif	/* __KOS_BSPLINE_H */
