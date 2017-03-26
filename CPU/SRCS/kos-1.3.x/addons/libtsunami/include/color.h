/*      
   Tsunami for KallistiOS ##version##
        
   color.h

   Copyright (C)2003 Dan Potter

   $Id: color.h,v 1.1 2003/04/24 02:57:20 bardtx Exp $
*/

#ifndef __TSUNAMI_COLOR_H
#define __TSUNAMI_COLOR_H

#include <plx/color.h>

struct Color {
	/// Constructor
	Color() {
		a = r = g = b = 1.0f;
	}
	Color(float ir, float ig, float ib) {
		a = 1.0f;
		r = ir;
		g = ig;
		b = ib;
	}
	Color(float ia, float ir, float ig, float ib) {
		a = ia;
		r = ir;
		g = ig;
		b = ib;
	}

	Color operator * (const Color & other) const {
		return Color(a*other.a, r*other.r, g*other.g, b*other.b);
	}

	Color operator + (const Color & other) const {
		return Color(a+other.a, r+other.r, g+other.g, b+other.b);
	}

	Color & operator *= (const Color & other) {
		*this = *this * other;
	}

	Color & operator += (const Color & other) {
		*this = *this + other;
	}

	operator uint32() const {
		return plx_pack_color(a, r, g, b);
	}


	float	a, r, g, b;
};

#endif	/* __TSUNAMI_COLOR_H */

