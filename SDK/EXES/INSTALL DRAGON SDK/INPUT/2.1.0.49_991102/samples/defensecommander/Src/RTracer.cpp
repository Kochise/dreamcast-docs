/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    RTracer.cpp

Abstract:

	Tracer rendering.   

-------------------------------------------------------------------*/

// Simulates the effect of fast moving tracer fire. The real effect is caused by 
// a motion-blurred spherical glow. We approximate this by rendering two half 
// balls and a bar in between. This is close but the correct result should have 
// softer ends. To be realistic the fire should fade in intensity when the
// bar is long but looks bad in practice so we use a constant intensity. Finally,
// the far and near depth values for the ends of the tracer are not really what
// they should be. This is because we use the center of the ball depths as the 
// far/near depths. In practise though, the effects of this are not noticeable 
// and fixing it would be hard and use even more CPU time.

#include "DC.h"
#include "DCGraphics.h"
#include "DCRender.h"
#include "DCMesh.h"
#include "DCVis.h"

#define TRACER_TEXTURE TEXT("TracerFlare")
#define TRACER_NORMAL_MESH TEXT("TracerNormal")

#define TRACER_BLUR_RADIUS (0.5f*1250.0f/35.0f)
#define TRACER_RADIUS 10.0f

static HANDLE TextureHandle;
static float Radius;
static DCVertex *V;

// Callback to get mesh radius.
static float RadiusCallback(HANDLE Data, BOOL ForRender)
{
	if (ForRender)
		return Radius;
	else
		return 0;
}

// Callback to render the mesh.
static void RenderCallback(HANDLE Data, DCVector *Loc, DCVector*Rot, RMeshCurrentState *CurrState)
{
	// See if visible.
	if (gVis.SphereNotVisible(*Loc,Radius))
		return;
	
	DCMatrix16 M;
	DCVector V1,V2;
	float NX,NY;
	
	// Walk the material list.
	if (CurrState->LastTexture!=TextureHandle)
	{
		CurrState->LastTexture=TextureHandle;
		gGraphics.SetTexture(TextureHandle);
	}
	if (!(CurrState->LastFlags & TSM_MFLAG_TEXCLAMP))
	{
		CurrState->LastFlags|=TSM_MFLAG_TEXCLAMP;
		gGraphics.TexAddressModeClamp();
	}

	// Set world matrix.
	gGraphics.SetWorldMatrix(&gRender.Frame.InvViewMatrix);

	// Calculate matrix to get points into view coordinates.
	gGraphics.MatrixIdentity();
	gGraphics.MatrixRotateZ(Rot->Z);
	gGraphics.MatrixRotateX(Rot->X);
	gGraphics.MatrixRotateY(Rot->Y);
	gGraphics.MatrixTranslate(Loc->X,Loc->Y,Loc->Z);
	gGraphics.MatrixMultiply(&gRender.Frame.ViewMatrix);
	gGraphics.MatrixGet(&M);

	// Get our start and end points of the tracer into view coordinates. 
	// Extra easy since X and Y values are 0.
#define Z1 TRACER_BLUR_RADIUS
#define Z2 -TRACER_BLUR_RADIUS
	V1=DCVector(M.m31*Z1 + M.m41,
				M.m32*Z1 + M.m42,
				M.m33*Z1 + M.m43);
	V2=DCVector(M.m31*Z2 + M.m41,
				M.m32*Z2 + M.m42,
				M.m33*Z2 + M.m43);
#undef Z1
#undef Z2

	// If either point behind front clip plane bail. Its difficult to work
	// around and the best result will be the tracer fire cut against
	// the front clipping plane.
	if (V1.Z < gRender.Frame.ZNear || V2.Z < gRender.Frame.ZNear)
		return;

	// To calculate our normal, we need projected points.
#define P gRender.Frame.ProjectionMatrix
	float X01=P.m11*V1.X + P.m21*V1.Y + P.m31*V1.Z + P.m41;
	float Y01=P.m12*V1.X + P.m22*V1.Y + P.m32*V1.Z + P.m42;
	float W01=P.m14*V1.X + P.m24*V1.Y + P.m34*V1.Z + P.m44;
	float X02=P.m11*V2.X + P.m21*V2.Y + P.m31*V2.Z + P.m41;
	float Y02=P.m12*V2.X + P.m22*V2.Y + P.m32*V2.Z + P.m42;
	float W02=P.m14*V2.X + P.m24*V2.Y + P.m34*V2.Z + P.m44;
#undef P	
	
	// Do perspective division.
	float Tmp1=1.0f/W01;
	X01*=Tmp1;
	Y01*=Tmp1;
	float Tmp2=1.0f/W02;
	X02*=Tmp2;
	Y02*=Tmp2;

	// Calculate 2D normal scaled by tracer radius so 
	// we can calculate boundaries of tracer.
	NX=X02-X01;
	NY=Y02-Y01;
	float Len2=NX*NX + NY*NY;
	if (Len2>0)
	{
		Len2=TRACER_RADIUS/FastSqrt(Len2);
		NX*=Len2;
		NY*=Len2;
	}
	else
	{
		NX=TRACER_RADIUS;
		NY=0;
	}

	// Fill in vertex structures.
	V[0].X=V1.X - NX - NY;
	V[0].Y=V1.Y - NY + NX;
	V[0].Z=V1.Z;
	V[1].X=V1.X - NX + NY;
	V[1].Y=V1.Y - NY - NX;
	V[1].Z=V1.Z;
	V[2].X=V1.X      - NY;
	V[2].Y=V1.Y      + NX;
	V[2].Z=V1.Z;
	V[3].X=V1.X      + NY;
	V[3].Y=V1.Y      - NX;
	V[3].Z=V1.Z;
	V[4].X=V2.X      - NY;
	V[4].Y=V2.Y      + NX;
	V[4].Z=V2.Z;
	V[5].X=V2.X      + NY;
	V[5].Y=V2.Y      - NX;
	V[5].Z=V2.Z;
	V[6].X=V2.X + NX - NY;
	V[6].Y=V2.Y + NY + NX;
	V[6].Z=V2.Z;
	V[7].X=V2.X + NX + NY;
	V[7].Y=V2.Y + NY - NX;
	V[7].Z=V2.Z;

	// At this point we could render something but the strip is kinked and it shows
	// at certain angles. So we adjust inner vertices to be on the same line as the
	// outer ones, while still keeping the inner bar the same length.
	// First calculate some normals representing the planes
	// from the origin through the inner vertices.
	DCVector P1=DCVector(V[2].X,V[2].Y,V[2].Z)^DCVector(V[3].X,V[3].Y,V[3].Z);
	DCVector P2=DCVector(V[4].X,V[4].Y,V[4].Z)^DCVector(V[5].X,V[5].Y,V[5].Z);

	// Now calculate along line from V[0]-V[6].
	{
		float Recip=1.0f/(V[6].X-V[0].X);
		float e=(V[6].Y-V[0].Y)*Recip;
		float f=V[0].Y - V[0].X*e;
		float g=(V[6].Z-V[0].Z)*Recip;
		float h=V[0].Z - V[0].X*g;
		float X;

		// Get X intersection with P1.
		X=-(P1.Y*f + P1.Z*h)/(P1.X + P1.Y*e + P1.Z*g);
		// Set to point of intersection with P1.
		V[2].X=X;
		V[2].Y=e*X + f;
		V[2].Z=g*X + h;

		// Get X intersection with P2.
		X=-(P2.Y*f + P2.Z*h)/(P2.X + P2.Y*e + P2.Z*g);
		// Set to point of intersection with P2.
		V[4].X=X;
		V[4].Y=e*X + f;
		V[4].Z=g*X + h;
	}
	// Now calculate along line from V[1]-V[7].
	{
		float Recip=1.0f/(V[7].X-V[1].X);
		float e=(V[7].Y-V[1].Y)*Recip;
		float f=V[1].Y - V[1].X*e;
		float g=(V[7].Z-V[1].Z)*Recip;
		float h=V[1].Z - V[1].X*g;
		float X;

		// Get X intersection with P1.
		X=-(P1.Y*f + P1.Z*h)/(P1.X + P1.Y*e + P1.Z*g);
		// Set to point of intersection with P1.
		V[3].X=X;
		V[3].Y=e*X + f;
		V[3].Z=g*X + h;

		// Get X intersection with P2.
		X=-(P2.Y*f + P2.Z*h)/(P2.X + P2.Y*e + P2.Z*g);
		// Set to point of intersection with P2.
		V[5].X=X;
		V[5].Y=e*X + f;
		V[5].Z=g*X + h;
	}

	// Render short strip.
	gGraphics.Strip(V,8);
}

// Init/shutdown.
BOOL InitTracer()
{
	// Allocate a vertex buffer.
	V=(DCVertex *)DCMalloc(sizeof(DCVertex)*8);
	if (!V)
		return FALSE;

	// Init constant stuff.
	V[0].Color=V[1].Color=V[2].Color=V[3].Color=
	V[4].Color=V[5].Color=V[6].Color=V[7].Color=0xFFFFFFFF;
	V[0].U=0; V[0].V=0.0f;
	V[1].U=1; V[1].V=0.0f;
	V[2].U=0; V[2].V=0.5f;
	V[3].U=1; V[3].V=0.5f;
	V[4].U=0; V[4].V=0.5f;
	V[5].U=1; V[5].V=0.5f;
	V[6].U=0; V[6].V=1.0f;
	V[7].U=1; V[7].V=1.0f;

	// Calculate radius.
	float Tmp=TRACER_BLUR_RADIUS + TRACER_RADIUS;
	Radius=(float)sqrt(Tmp*Tmp + TRACER_RADIUS*TRACER_RADIUS*2.0f);

	// Add texture.
	TextureHandle=gGraphics.AddTexture(ReadImageFileMipmapped,TRACER_TEXTURE,TRUE,FALSE);

	// Add user render mesh.
	AddUserRenderMesh(TRACER_NORMAL_MESH,FALSE,TRUE,RenderCallback,RadiusCallback,NULL);

	return TRUE;
}

void ShutdownTracer()
{
	// Deallocate the vertex buffer.
	DCFree( V );
}
