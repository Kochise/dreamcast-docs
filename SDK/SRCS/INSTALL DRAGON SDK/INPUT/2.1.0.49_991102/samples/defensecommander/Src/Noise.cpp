/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    Noise.cpp

Abstract:

    Noise/random functions. The noise used is Gradient (==Perlin) noise. 

-------------------------------------------------------------------*/

#include "DC.h"

// Defines and data for gradient noise functions.
#define TABLEENTRIES		0x100
#define TABLEENTRIESMASK	0x0FF
#define TABLESIZE			((TABLEENTRIES+1)*2)
#define BASEOFFSET			0x1000

static PointerTable[TABLESIZE];
static float GradientTable1D[TABLESIZE];
static float GradientTable2D[TABLESIZE][2];
static float GradientTable3D[TABLESIZE][3];

// Data for shaping functions.
float RecipLogPointFive;

// Data for random functions.
DWORD gFastRandSeed;

// Macros used in initialization
#define NORMALIZE2D(x,y) \
{ \
	float InvL=1.0f/(float)sqrt(x*x + y*y); \
	x*=InvL; \
	y*=InvL; \
}

#define NORMALIZE3D(x,y,z) \
{ \
	float InvL=1.0f/(float)sqrt(x*x + y*y + z*z); \
	x*=InvL; \
	y*=InvL; \
	z*=InvL; \
}

// Initialize noise and random functions.
BOOL InitNoise(void)
{
	// Init tables for gradient noise functions.
	SeedGoodRand(0x69521988);
	
	int i, j, k;

	// Init first entries in tables.
	for (i=0;i<TABLEENTRIES;i++) 
	{
		// Pointer table.
		PointerTable[i]=i;
		// 1D table.
		GradientTable1D[i]		= (float)((GoodRand() % (2*TABLEENTRIES)) - TABLEENTRIES) / TABLEENTRIES;
		// 2D table.
		GradientTable2D[i][0]	= (float)((GoodRand() % (2*TABLEENTRIES)) - TABLEENTRIES) / TABLEENTRIES;
		GradientTable2D[i][1]	= (float)((GoodRand() % (2*TABLEENTRIES)) - TABLEENTRIES) / TABLEENTRIES;
		NORMALIZE2D(GradientTable2D[i][0],GradientTable2D[i][1]);
		// 3D table.
		GradientTable3D[i][0]	= (float)((GoodRand() % (2*TABLEENTRIES)) - TABLEENTRIES) / TABLEENTRIES;
		GradientTable3D[i][1]	= (float)((GoodRand() % (2*TABLEENTRIES)) - TABLEENTRIES) / TABLEENTRIES;
		GradientTable3D[i][2]	= (float)((GoodRand() % (2*TABLEENTRIES)) - TABLEENTRIES) / TABLEENTRIES;
		NORMALIZE3D(GradientTable3D[i][0],GradientTable3D[i][1],GradientTable3D[i][2]);
	}

	// Jumble up the pointer table entries.
	while (--i) 
	{
		k = PointerTable[i];
		j = GoodRand() % TABLEENTRIES;
		PointerTable[i] = PointerTable[j];
		PointerTable[j] = k;
	}

	// Duplicate first entries into the rest of the table.
	for (i=TABLEENTRIES;i<TABLESIZE;i++)
	{
		PointerTable[i]			= PointerTable[i-TABLEENTRIES];
		GradientTable1D[i]		= GradientTable1D[i-TABLEENTRIES];
		GradientTable2D[i][0]	= GradientTable2D[i-TABLEENTRIES][0];
		GradientTable2D[i][1]	= GradientTable2D[i-TABLEENTRIES][1];
		GradientTable3D[i][0]	= GradientTable3D[i-TABLEENTRIES][0];
		GradientTable3D[i][1]	= GradientTable3D[i-TABLEENTRIES][1];
		GradientTable3D[i][2]	= GradientTable3D[i-TABLEENTRIES][2];
	}

	// Init data for shaping functions.
	RecipLogPointFive=1.0f/(float)log(0.5f);

	return TRUE;
}

void ShutdownNoise(void)
{
	// Nothing to do.
}

// Shaping functions.

// Bias meets the following:
// Bias(0.0, B) = 0.0
// Bias(0.5, B) = B
// Bias(1.0, B) = 1.0
// Bias(..., 0.5) is the identity function.
float Bias(float In, float Bias)
{
	return (float)pow(In, (float)log(Bias) * RecipLogPointFive);
}

// Gain meets the following:
// Gain(0.0,  G) = 0.0
// Gain(0.25, G) = 0.5 - G/2
// Gain(0.5,  G) = 0.5
// Gain(0.75, G) = 0.5 + G/2
// Gain(1.0,  G) = 1.0
// Gain(..., 0.5) is the identity function.
float Gain(float In, float Gain)
{
	float P = (float)log(1.0f - Gain) * RecipLogPointFive;

	if (In < 0.001f)
		return 0.0f;
	else if (In > 0.999f)
		return 1.0f;
	if (In < 0.5f)
		return (float)pow(2.0f * In, P) * 0.5f;
	else
		return 1.0f - (float)pow(2.0f * (1.0f - In), P) * 0.5f;
}

// Helper macros for gradient noise functions.
#define CURVE(t) (t*t*(3.0f-2.0f*t))

#define LERP(t,a,b) (a + t*(b-a))

#define SETUP(i,b0,b1,r0,r1)\
{ \
	float t = i + BASEOFFSET;\
	b0 = ((int)t) & TABLEENTRIESMASK;\
	b1 = (b0+1) & TABLEENTRIESMASK;\
	r0 = t - (int)t;\
	r1 = r0 - 1.0f; \
}

// Gradient noise functions.
float GNoise1(float A)
{
	int bx0,bx1;
	float rx0,rx1,sx,u,v;

	SETUP(A,bx0,bx1,rx0,rx1);

	sx=CURVE(rx0);

	u=rx0*GradientTable1D[PointerTable[bx0]];
	v=rx1*GradientTable1D[PointerTable[bx1]];

	return LERP(sx,u,v);
}

float GNoise2(float A, float B)
{
	int bx0,bx1,by0,by1,b00,b10,b01,b11;
	float rx0,rx1,ry0,ry1,*q,sx,sy,a,b,u,v;
	int i,j;

	SETUP(A,bx0,bx1,rx0,rx1);
	SETUP(B,by0,by1,ry0,ry1);

	i=PointerTable[bx0];
	j=PointerTable[bx1];

	b00=PointerTable[i+by0];
	b10=PointerTable[j+by0];
	b01=PointerTable[i+by1];
	b11=PointerTable[j+by1];

	sx=CURVE(rx0);
	sy=CURVE(ry0);

#define PRODUCT(rx,ry) (rx*q[0] + ry*q[1])

	q=GradientTable2D[b00];
	u=PRODUCT(rx0,ry0);
	q=GradientTable2D[b10];
	v=PRODUCT(rx1,ry0);
	a=LERP(sx,u,v);

	q=GradientTable2D[b01];
	u=PRODUCT(rx0,ry1);
	q=GradientTable2D[b11];
	v=PRODUCT(rx1,ry1);
	b=LERP(sx,u,v);

#undef PRODUCT

	return LERP(sy,a,b);
}

float GNoise3(float A, float B, float C)
{
	int bx0,bx1,by0,by1,bz0,bz1,b00,b10,b01,b11;
	float rx0,rx1,ry0,ry1,rz0,rz1,*q,sx,sy,sz,a,b,c,d,u,v;
	int i,j;

	SETUP(A, bx0,bx1, rx0,rx1);
	SETUP(B, by0,by1, ry0,ry1);
	SETUP(C, bz0,bz1, rz0,rz1);

	i=PointerTable[bx0];
	j=PointerTable[bx1];

	b00=PointerTable[i+by0];
	b10=PointerTable[j+by0];
	b01=PointerTable[i+by1];
	b11=PointerTable[j+by1];

	sx=CURVE(rx0);
	sy=CURVE(ry0);
	sz=CURVE(rz0);

#define PRODUCT(rx,ry,rz) (rx*q[0] + ry*q[1] + rz*q[2])

	q=GradientTable3D[b00+bz0];
	u=PRODUCT(rx0,ry0,rz0);
	q=GradientTable3D[b10+bz0];
	v=PRODUCT(rx1,ry0,rz0);
	a=LERP(sx,u,v);

	q=GradientTable3D[b01+bz0];
	u=PRODUCT(rx0,ry1,rz0);
	q=GradientTable3D[b11+bz0];
	v=PRODUCT(rx1,ry1,rz0);
	b=LERP(sx,u,v);

	c=LERP(sy,a,b);

	q=GradientTable3D[b00+bz1];
	u=PRODUCT(rx0,ry0,rz1);
	q=GradientTable3D[b10+bz1];
	v=PRODUCT(rx1,ry0,rz1);
	a=LERP(sx,u,v);

	q=GradientTable3D[b01+bz1];
	u=PRODUCT(rx0,ry1,rz1);
	q=GradientTable3D[b11+bz1];
	v=PRODUCT(rx1,ry1,rz1);
	b=LERP(sx,u,v);

	d=LERP(sy,a,b);

#undef PRODUCT

	return LERP(sz, c, d);
}
