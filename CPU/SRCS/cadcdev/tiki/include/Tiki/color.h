/*
   Tiki

   color.h

   Copyright (C)2003 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_COLOR_H
#define __TIKI_COLOR_H

#include "Tiki/glhdrs.h"

namespace Tiki {
namespace GL {

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

	Color operator * (float factor) const {
		return Color(a*factor, r*factor, g*factor, b*factor);
	}

	Color operator + (const Color & other) const {
		return Color(a+other.a, r+other.r, g+other.g, b+other.b);
	}

	Color & operator *= (const Color & other) {
		*this = *this * other;
		return *this;
	}

	Color & operator += (const Color & other) {
		*this = *this + other;
		return *this;
	}

	// These must be used in some cases because C++ is too dumb to
	// handle the precedence sensibly...
	Color mult(const Color & o) const {
		return Color(a*o.a, r*o.r, g*o.g, b*o.b);
	}
	Color mult(float f) const {
		return Color(a*f, r*f, g*f, b*f);
	}
	Color add(const Color & o) const {
		return Color(a+o.a, r+o.r, g+o.g, b+o.b);
	}
	Color sub(const Color & o) const {
		return Color(a-o.a, r-o.r, g-o.g, b-o.b);
	}

	operator uint32() const {
		float ta, tr, tg, tb;
		ta = (a < 0.0f) ? 0.0f : (a > 1.0f) ? 1.0f : a;
		tr = (r < 0.0f) ? 0.0f : (r > 1.0f) ? 1.0f : r;
		tg = (g < 0.0f) ? 0.0f : (g > 1.0f) ? 1.0f : g;
		tb = (b < 0.0f) ? 0.0f : (b > 1.0f) ? 1.0f : b;
		return pack(ta, tr, tg, tb);
	}
	
	void select() const {
#if TIKI_PLAT != TIKI_NDS
		glColor4f(r, g, b, a);
#else
		glColor3f(r, g, b);
#endif
	}

	static uint32 pack(float a, float r, float g, float b) {
		return (((int)(a * 255)) << 24) |
			(((int)(r * 255)) << 16) |
			(((int)(g * 255)) << 8) |
			(((int)(b * 255)));
	}

	float	a, r, g, b;
};

}
}

#endif	// __TIKI_COLOR_H

