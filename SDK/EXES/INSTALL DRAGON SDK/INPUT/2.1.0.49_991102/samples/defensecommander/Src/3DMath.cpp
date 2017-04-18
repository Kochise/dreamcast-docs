/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    3DMath.cpp

Abstract:

	3D math functions.

-------------------------------------------------------------------*/

#include "DC.h"

void DCVector::RotateX(float Angle)
{
	float SinA=(float)sin(Angle);
	float CosA=(float)cos(Angle);
	float TmpY,TmpZ;

	TmpY = Z*SinA + Y*CosA;
	TmpZ = Z*CosA - Y*SinA;

	Y=TmpY;
	Z=TmpZ;
}

void DCVector::RotateY(float Angle)
{
	float SinA=(float)sin(Angle);
	float CosA=(float)cos(Angle);
	float TmpX,TmpZ;

	TmpX = X*CosA - Z*SinA;
	TmpZ = X*SinA + Z*CosA;

	X=TmpX;
	Z=TmpZ;
}

void DCVector::RotateZ(float Angle)
{
	float SinA=(float)sin(Angle);
	float CosA=(float)cos(Angle);
	float TmpX,TmpY;

	TmpX = Y*SinA + X*CosA;
	TmpY = Y*CosA - X*SinA;

	X=TmpX;
	Y=TmpY;
}

void DCVector::ClampMin(float Min)
{
	X=__max(Min,X);
	Y=__max(Min,Y);
	Z=__max(Min,Z);
}

void DCVector::ClampMax(float Max)
{
	X=__min(Max,X);
	Y=__min(Max,Y);
	Z=__min(Max,Z);
}

void DCVector::CalculateViewVectors(DCVector *VecX, DCVector *VecY, DCVector *VecZ)
{
	float SinX=FastSin(X);
	float CosX=FastCos(X);
	float SinY=FastSin(Y);
	float CosY=FastCos(Y);
	float SinZ=FastSin(Z);
	float CosZ=FastCos(Z);

	VecX->X = CosY*CosZ - SinX*SinY*SinZ;
	VecX->Y = -CosX*SinZ;
	VecX->Z = SinY*CosZ + SinX*CosY*SinZ;

	VecY->X = CosY*SinZ + SinX*SinY*CosZ;
	VecY->Y = CosX*CosZ;
	VecY->Z = SinY*SinZ - SinX*CosY*CosZ;

	VecZ->X = -CosX*SinY;
	VecZ->Y = SinX;
	VecZ->Z = CosX*CosY;
}
