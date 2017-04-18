/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    Vis.cpp

Abstract:

	Visbility testing. 

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCVis.h"

VisClass gVis;

void VisClass::InitForFrame(float MaxAngH, float MaxAngV, float FrontDepth, float BackDepth,
							DCVector *Loc, DCVector *Rot)
{
	float Cos,Sin;

	// Set bool variables.
	InWorldCenter=(Loc->X==0 && Loc->Z==0 && Loc->Y>0);
	LookingUp=(Rot->X > 0);

	// Init planes. Except for front, all planes initially go through origin.
	// Left and right.
	Sin=(float)sin(MaxAngH);
	Cos=(float)cos(MaxAngH);
	Left.X=-Cos;
	Left.Y=0;
	Left.Z=-Sin;
	Left.W=0;
	Right.X=Cos;
	Right.Y=0;
	Right.Z=-Sin;
	Right.W=0;
	// Top and bottom.
	Sin=(float)sin(MaxAngV);
	Cos=(float)cos(MaxAngV);
	Top.X=0;
	Top.Y=Cos;
	Top.Z=-Sin;
	Top.W=0;
	Bottom.X=0;
	Bottom.Y=-Cos;
	Bottom.Z=-Sin;
	Bottom.W=0;
	// Front.
	Front.X=0;
	Front.Y=0;
	Front.Z=-1;
	Front.W=-FrontDepth;

	// Rotate the planes vertically.
	Sin=(float)sin(Rot->X);
	Cos=(float)cos(Rot->X);
#define ROTX(PLANE,SIN,COS) \
	{ \
		float TmpY,TmpZ; \
		TmpY = PLANE.Z*SIN + PLANE.Y*COS; \
		TmpZ = PLANE.Z*COS - PLANE.Y*SIN; \
		PLANE.Y=TmpY; \
		PLANE.Z=TmpZ; \
	}
	ROTX(Left,Sin,Cos);
	ROTX(Right,Sin,Cos);
	ROTX(Top,Sin,Cos);
	ROTX(Bottom,Sin,Cos);
	ROTX(Front,Sin,Cos);
#undef ROTX

	// Rotate the planes horizontally.
	Sin=(float)sin(Rot->Y);
	Cos=(float)cos(Rot->Y);
#define ROTY(PLANE,SIN,COS) \
	{ \
		float TmpX,TmpZ; \
		TmpX = PLANE.X*COS - PLANE.Z*SIN; \
		TmpZ = PLANE.X*SIN + PLANE.Z*COS; \
		PLANE.X=TmpX; \
		PLANE.Z=TmpZ; \
	}
	ROTY(Left,Sin,Cos);
	ROTY(Right,Sin,Cos);
	ROTY(Top,Sin,Cos);
	ROTY(Bottom,Sin,Cos);
	ROTY(Front,Sin,Cos);
#undef ROTY

	// Translate the planes.
	// The translation works by adding components of translation in each direction
	// to the distance from origin (distance from origin is -W).
#define TRANS(PLANE,_X,_Y,_Z) PLANE.W-=PLANE.X*_X + PLANE.Y*_Y + PLANE.Z*_Z;
	TRANS(Left,		Loc->X,Loc->Y,Loc->Z);
	TRANS(Right,	Loc->X,Loc->Y,Loc->Z);
	TRANS(Top,		Loc->X,Loc->Y,Loc->Z);
	TRANS(Bottom,	Loc->X,Loc->Y,Loc->Z);
	TRANS(Front,	Loc->X,Loc->Y,Loc->Z);
#undef TRANS
}
