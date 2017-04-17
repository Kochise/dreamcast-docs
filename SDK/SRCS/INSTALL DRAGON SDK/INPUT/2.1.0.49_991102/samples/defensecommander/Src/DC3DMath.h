/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    DC3DMath.h

Abstract:

    3D math functions.

-------------------------------------------------------------------*/


#define DC_PI 3.1415927f
#define DC_TO_RADIANS(a) (a * (DC_PI/180.0f))

#define FastSqrt(a) ((float)sqrt(a))
#define FastSin(a) ((float)sin(a))
#define FastCos(a) ((float)cos(a))

class DCVector
{
public:
	float X,Y,Z;

	DCVector() {}
	DCVector(float InX, float InY, float InZ) { X=InX; Y=InY; Z=InZ; }
	
	DCVector operator+(DCVector& V) { return DCVector(X+V.X, Y+V.Y, Z+V.Z); }
	DCVector operator-(DCVector& V) { return DCVector(X-V.X, Y-V.Y, Z-V.Z); }
	DCVector operator+=(DCVector& V) { X+=V.X; Y+=V.Y; Z+=V.Z; return *this; }
	DCVector operator-=(DCVector& V) { X-=V.X; Y-=V.Y; Z-=V.Z; return *this; }
	// Scalar product.
	DCVector operator*(float S)  { return DCVector(X*S, Y*S, Z*S); }
	DCVector operator*=(float S) { X*=S; Y*=S; Z*=S; return *this; }
	DCVector operator*(DCVector& V)  { return DCVector(X*V.X, Y*V.Y, Z*V.Z); }
	DCVector operator*=(DCVector& V) { X*=V.X; Y*=V.Y; Z*=V.Z; return *this; }
	// Dot product.
	float operator|(DCVector& V) { return X*V.X + Y*V.Y + Z*V.Z; }
	// Cross product.
	DCVector operator^(DCVector& V) { return DCVector(Y*V.Z-Z*V.Y,Z*V.X-X*V.Z,X*V.Y-Y*V.X); }
	// Length.
	float FastLength(void) { return FastSqrt(X*X + Y*Y + Z*Z); };
	float Length(void) { return (float)sqrt(X*X + Y*Y + Z*Z); };;
	// Misc.
	void RotateX(float Angle);
	void RotateY(float Angle);
	void RotateZ(float Angle);
	void FastNormalize(void)
	{
		float Scale=1.0f/FastSqrt(X*X + Y*Y + Z*Z);
		X*=Scale; Y*=Scale; Z*=Scale;
	}
	void Normalize(void)
	{
		float Scale=1.0f/(float)sqrt(X*X + Y*Y + Z*Z);
		X*=Scale; Y*=Scale; Z*=Scale;
	}
	void ClampMin(float Min);
	void ClampMax(float Max);
	void CalculateViewVectors(DCVector *VecX, DCVector *VecY, DCVector *VecZ);
	float FastDist(DCVector &V) 
	{ 
		float TmpX=X-V.X;
		float TmpY=Y-V.Y;
		float TmpZ=Z-V.Z;
		return (float)FastSqrt(TmpX*TmpX + TmpY*TmpY + TmpZ*TmpZ);
	}
	float Dist(DCVector &V) 
	{ 
		float TmpX=X-V.X;
		float TmpY=Y-V.Y;
		float TmpZ=Z-V.Z;
		return (float)sqrt(TmpX*TmpX + TmpY*TmpY + TmpZ*TmpZ);
	}
	float DistSquared(DCVector &V) 
	{ 
		float TmpX=X-V.X;
		float TmpY=Y-V.Y;
		float TmpZ=Z-V.Z;
		return TmpX*TmpX + TmpY*TmpY + TmpZ*TmpZ;
	}
};

class DCPlane : public DCVector
{
public:
	float W;
	// Product.
	float operator|(DCVector& V) { return X*V.X + Y*V.Y + Z*V.Z + W; }
	float operator|(DCPlane & V) { return X*V.X + Y*V.Y + Z*V.Z + W*V.W; }
};

struct DCVertex
{
	float X,Y,Z;
	float InvW;
	DWORD Color,Specular;
	float U,V;
};

struct DCVertex2L
{
	float X,Y,Z;
	float InvW;
	DWORD Color,Specular;
	float U0,V0;
	float U1,V1;
};

struct DCVertex3L
{
	float X,Y,Z;
	float InvW;
	DWORD Color,Specular;
	float U0,V0;
	float U1,V1;
	float U2,V2;
};

struct DCMatrix16
{
    float m11, m12, m13, m14;
    float m21, m22, m23, m24; 
    float m31, m32, m33, m34; 
    float m41, m42, m43, m44; 
};
