/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    DCVis.h

Abstract:

   Visibility testing. 

-------------------------------------------------------------------*/

class VisClass
{
	BOOL InWorldCenter;
	BOOL LookingUp;
	DCPlane Left,Right,Top,Bottom,Front;

	// For this, the 8 input points must have W set to 1.
	BOOL EightPointsOutsidePlane(DCPlane *Points,DCPlane &Plane)
	{
		return ((Plane|Points[0])>0.0f && (Plane|Points[1])>0.0f && 
				(Plane|Points[2])>0.0f && (Plane|Points[3])>0.0f && 
				(Plane|Points[4])>0.0f && (Plane|Points[5])>0.0f && 
				(Plane|Points[6])>0.0f && (Plane|Points[7])>0.0f);
	}

public:
	void InitForFrame(float MaxAngH, float MaxAngV, float FrontDepth, float BackDepth,
					  DCVector *Loc, DCVector *Rot);
	BOOL IsInWorldCenter(void)	{ return InWorldCenter; }
	BOOL IsLookingUp(void)	{ return LookingUp; }
	
	BOOL PointNotVisible(DCVector &Point)
	{
		return ((Left|Point)>0.0f || (Right|Point)>0.0f || (Top|Point)>0.0f || (Bottom|Point)>0.0f || (Front|Point)>0.0f);
	}
	BOOL SphereNotVisible(DCVector &Center, float R)
	{
		return ((Left|Center)>R || (Right|Center)>R || (Top|Center)>R || (Bottom|Center)>R || (Front|Center)>R);
	}
	BOOL PointOutsideLeft  (DCVector &Point) { return ((Left  |Point)>0.0f); }
	BOOL PointOutsideRight (DCVector &Point) { return ((Right |Point)>0.0f); }
	BOOL PointOutsideTop   (DCVector &Point) { return ((Top   |Point)>0.0f); }
	BOOL PointOutsideBottom(DCVector &Point) { return ((Bottom|Point)>0.0f); }
	BOOL PointOutsideFront (DCVector &Point) { return ((Front |Point)>0.0f); }

	BOOL PointOutsideLeft  (float X, float Y, float Z) 
		{ return ((Left.X*X + Left.Y*Y + Left.Z*Z + Left.W)>0.0f); }
	BOOL PointOutsideRight (float X, float Y, float Z) 
		{ return ((Right.X*X + Right.Y*Y + Right.Z*Z + Right.W)>0.0f); }
	BOOL PointOutsideTop   (float X, float Y, float Z) 
		{ return ((Top.X*X + Top.Y*Y + Top.Z*Z + Top.W)>0.0f); }
	BOOL PointOutsideBottom(float X, float Y, float Z) 
		{ return ((Bottom.X*X + Bottom.Y*Y + Bottom.Z*Z + Bottom.W)>0.0f); }
	BOOL PointOutsideFront (float X, float Y, float Z) 
		{ return ((Front.X*X + Front.Y*Y + Front.Z*Z + Front.W)>0.0f); }

	BOOL EightPointsOutsideLeft(DCPlane *Points) { return EightPointsOutsidePlane(Points,Left); }
	BOOL EightPointsOutsideRight(DCPlane *Points) { return EightPointsOutsidePlane(Points,Right); }
	BOOL EightPointsOutsideTop(DCPlane *Points) { return EightPointsOutsidePlane(Points,Top); }
	BOOL EightPointsOutsideBottom(DCPlane *Points) { return EightPointsOutsidePlane(Points,Bottom); }
	BOOL EightPointsOutsideFront(DCPlane *Points) { return EightPointsOutsidePlane(Points,Front); }
	BOOL EightPointsNotVisible(DCPlane *Points) 
	{
		return (EightPointsOutsidePlane(Points,Left) ||
				EightPointsOutsidePlane(Points,Right) ||
				EightPointsOutsidePlane(Points,Top) ||
				EightPointsOutsidePlane(Points,Bottom) ||
				EightPointsOutsidePlane(Points,Front));
	}
};

extern VisClass gVis;
