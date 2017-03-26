/* 
   Tiki

   bspline.cpp
   Copyright (C)2000 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC

   For generating B-Spline curves 

   This math info is from Leendert Ammeraal's "Programming Principles in
   Computer Graphics". 
*/

#include "pch.h"
#include "Tiki/bspline.h"
#include <string.h>

using namespace Tiki::Math;

BSpline::BSpline() {
	memset(bc_x, 0, sizeof(bc_x));
	memset(bc_y, 0, sizeof(bc_y));
	memset(bc_z, 0, sizeof(bc_z));
}

BSpline::BSpline(const Vector * pnts) {
	setPoints(pnts);
}

BSpline::~BSpline() {
}

void BSpline::setPoints(const Vector * pnt) {
	float a, b, c, d;
	
	/* First calculate the X coefficients */
	a = pnt[-1].x; b = pnt[0].x; c = pnt[1].x; d = pnt[2].x;
	bc_x[3] = (-a+3*(b-c)+d) / 6.0f;
	bc_x[2] = (a-2*b+c)/2.0f;
	bc_x[1] = (c-a)/2.0f;
	bc_x[0] = (a+4*b+c)/6.0f;
	
	/* Next, the Y coefficients */
	a = pnt[-1].y; b = pnt[0].y; c = pnt[1].y; d = pnt[2].y;
	bc_y[3] = (-a+3*(b-c)+d) / 6.0f;
	bc_y[2] = (a-2*b+c)/2.0f;
	bc_y[1] = (c-a)/2.0f;
	bc_y[0] = (a+4*b+c)/6.0f;

	/* Finally, the Z coefficients */
	a = pnt[-1].z; b = pnt[0].z; c = pnt[1].z; d = pnt[2].z;
	bc_z[3] = (-a+3*(b-c)+d) / 6.0f;
	bc_z[2] = (a-2*b+c)/2.0f;
	bc_z[1] = (c-a)/2.0f;
	bc_z[0] = (a+4*b+c)/6.0f;
}

Vector BSpline::getPoint(float t) {
	return Vector(
		/* Generate X */
		((bc_x[3]*t+bc_x[2])*t+bc_x[1])*t + bc_x[0],
	
		/* Generate Y */
		((bc_y[3]*t+bc_y[2])*t+bc_y[1])*t + bc_y[0],
	
		/* Generate Z */
		((bc_z[3]*t+bc_z[2])*t+bc_z[1])*t + bc_z[0]
	);
}

   
   



