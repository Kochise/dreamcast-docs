/*
   Tiki

   math.h

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_MATH_H
#define __TIKI_MATH_H

#if TIKI_PLAT == TIKI_DC
#include <dc/fmath.h>
#else

namespace Tiki {
namespace Math {
	/// Do the square root in the quickest way possible.
	float fsqrt(float f);

	/// Do the inverse square root (1/sqrt) in the quickest way possible.
	float frsqrt(float f);

	/// Calculate a floating point sin as fast as possible.
	float fsin(float f);

	/// Calculate a floating point cos as fast as possible.
	float fcos(float f);

	/// Calculate tanget as fast as possible.
	float ftan(float f);

	/// Calculate absolute value as fast as possible.
	float fabs(float f);
	
	/// PI constant.
	extern float F_PI;
}
}

#endif

#endif	// __TIKI_MATH_H
