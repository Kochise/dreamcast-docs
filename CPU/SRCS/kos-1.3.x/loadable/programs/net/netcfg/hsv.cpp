/* 
   Network Configurator
   
   hsv.cpp

   Copyright (C)2002 Cryptic Allusion, LLC
   Donated from Feet of Fury

*/

#include "hsv.h"

static float scols[8][3] = {
	{ 1.0f, 0.0f, 0.0f },	// Red
	{ 1.0f, 0.0f, 1.0f },	// Magenta
	{ 0.0f, 0.0f, 1.0f },	// Blue
	{ 0.0f, 1.0f, 1.0f },	// Cyan
	{ 0.0f, 1.0f, 0.0f },	// Green
	{ 1.0f, 1.0f, 0.0f },	// Yellow
	{ 1.0f, 0.0f, 0.0f },	// Red
	{ 1.0f, 0.0f, 1.0f }	// Magenta
};
void hsvSpectrum(float w, float & r, float & g, float & b) {
	while (w > 1.0f)
		w -= 1.0f;
	while (w < 0.0f)
		w += 1.0f;

	// Figure out what our two endpoints are
	int w1 = (int)(w * 6);
	float i = 1.0f - ((w * 6) - w1);

	// Interpolate between
	r = scols[w1][0] * i + scols[w1+1][0] * (1.0f - i);
	g = scols[w1][1] * i + scols[w1+1][1] * (1.0f - i);
	b = scols[w1][2] * i + scols[w1+1][2] * (1.0f - i);
}

