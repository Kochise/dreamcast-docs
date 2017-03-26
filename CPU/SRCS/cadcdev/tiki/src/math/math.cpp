/*
   Tiki

   math.cpp

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/tikimath.h"

#if TIKI_PLAT != TIKI_DC

using namespace Tiki::Math;

float Tiki::Math::F_PI = (float)M_PI;

float Math::fsqrt(float f) {
	return (float)sqrt(f);
}

float Math::frsqrt(float f) {
	return 1.0f / (float)sqrt(f);
}

float Math::fsin(float f) {
	return (float)sin(f);
}

float Math::fcos(float f) {
	return (float)cos(f);
}

float Math::ftan(float f) {
	return (float)tan(f);
}

float Math::fabs(float f) {
	return f < 0.0f ? -f : f;
}

#endif
