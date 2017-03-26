/*
   Tiki

   color3.h

   Copyright (C)2003,2004 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_COLOR3_H
#define __TIKI_COLOR3_H

#include "color.h"

namespace Tiki {
namespace GL {

/// Leaner, meaner version of Color.
struct Color3 {
	/// Constructor
	Color3() { }
	Color3(float ir, float ig, float ib) {
		r = ir;
		g = ig;
		b = ib;
	}

	Color3 operator * (const Color3 & other) const {
		return Color3(r*other.r, g*other.g, b*other.b);
	}

	Color3 operator * (float factor) const {
		return Color3(r*factor, g*factor, b*factor);
	}

	Color3 operator + (const Color3 & other) const {
		return Color3(r+other.r, g+other.g, b+other.b);
	}

	Color3 & operator *= (const Color3 & other) {
		*this = *this * other;
		return *this;
	}

	Color3 & operator += (const Color3 & other) {
		*this = *this + other;
		return *this;
	}

	operator uint32() const {
		float tr, tg, tb;
		tr = (r < 0.0f) ? 0.0f : (r > 1.0f) ? 1.0f : r;
		tg = (g < 0.0f) ? 0.0f : (g > 1.0f) ? 1.0f : g;
		tb = (b < 0.0f) ? 0.0f : (b > 1.0f) ? 1.0f : b;
		return Color::pack(1.0f, tr, tg, tb);
	}

	void select() const {
		glColor4f(r, g, b, 1.0f);
	}

	float	r, g, b;
};

};
};

#endif	// __TIKI_COLOR3_H

