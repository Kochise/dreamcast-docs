/*
   Tiki

   bspline.h

   Copyright (C)2000 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/


#ifndef __TIKI_BSPLINE_H
#define __TIKI_BSPLINE_H

#include "Tiki/vector.h"

namespace Tiki {
namespace Math {

/** \file
   This module provides utility functions to generate b-spline
   curves in your program. It is used by passing in a set of
   control points to bspline_coeff, and then querying for
   individual points using bspline_get_point.
*/

class BSpline {
public:
	BSpline();
	BSpline(const Vector * pnts);
	virtual ~BSpline();
	
	/**
	   Pass it an array of points and it will calculate a set of B-spline
	   co-efficients for generating a curve. There must be at least one point
	   before the "current" one, and at least two after the "current" one (a
	   total of four points required). These values will be used in the 
	   function below.
	*/
	void	setPoints(const Vector * pnts);

	/**
	   Given a 't' (between 0.0f and 1.0f) this will generate the next point
	   values for the current set of coefficients.
	*/
	Vector	getPoint(float t);

protected:
	float	bc_x[4], bc_y[4], bc_z[4];
};

}
}

#endif	// __TIKI_BSPLINE_H
