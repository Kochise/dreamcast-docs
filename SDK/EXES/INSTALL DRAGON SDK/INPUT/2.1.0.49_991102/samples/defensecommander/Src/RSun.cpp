/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    RSun.cpp

Abstract:

    Sun rendering.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCWorld.h"
#include "DCGraphics.h"
#include "DCRender.h"

#define SUN_TEXTURE_IMAGE TEXT("SunFlare")

extern DCVector ViewVecX,ViewVecY,ViewVecZ; // In RMain.cpp.

static HANDLE SunTexture;
static DCVertex V[4];
static DCVector SunCenter;

BOOL InitSun(void)
{
	// Add the sun texture.
	SunTexture=gGraphics.AddTexture(ReadImageFileNotMipmapped,SUN_TEXTURE_IMAGE,TRUE,FALSE);

	// Figure out center point for the sun.
	DCVector Vec=DCW_SUN_DIR;
	Vec.Normalize();
	SunCenter=Vec*DCW_SUN_HEIGHT;

	// Initialize part of the vertices.
	for (int i=0;i<4;i++)
	{
		V[i].Color=0xFFFFFFFF;
		V[i].U=(i & 0x01) ? 1.0f : 0.0f;
		V[i].V=(i & 0x02) ? 1.0f : 0.0f;
	}

	return TRUE;
}

void ShutdownSun(void)
{
	// Nothing to do.
}

void RenderSun()
{
	// Set up state.
	gGraphics.ShadeModeFlat();
	gGraphics.EnableBlend();
	gGraphics.EnableDepthTest();
	gGraphics.DepthFunc(DFUNC_LESSEQUAL);
	gGraphics.DisableDepthWrite();
	gGraphics.CullDisable();
	gGraphics.SetTexture(SunTexture);

	// Set new view matrix which doesn't have any translation.	
	gGraphics.MatrixIdentity();
	gGraphics.SetWorldMatrix();
	gGraphics.MatrixRotateY(-gRender.Frame.ViewRot.Y);
	gGraphics.MatrixRotateX(-gRender.Frame.ViewRot.X);
	gGraphics.SetViewMatrix();	

	// Set rest of sun vertices.
	DCVector VecX=gRender.Frame.ViewVecX*DCW_SUN_RADIUS;
	DCVector VecY=gRender.Frame.ViewVecY*DCW_SUN_RADIUS;

	V[0].X = SunCenter.X - VecX.X - VecY.X;
	V[0].Y = SunCenter.Y - VecX.Y - VecY.Y;
	V[0].Z = SunCenter.Z - VecX.Z - VecY.Z;
	V[1].X = SunCenter.X + VecX.X - VecY.X;
	V[1].Y = SunCenter.Y + VecX.Y - VecY.Y;
	V[1].Z = SunCenter.Z + VecX.Z - VecY.Z;
	V[2].X = SunCenter.X - VecX.X + VecY.X;
	V[2].Y = SunCenter.Y - VecX.Y + VecY.Y;
	V[2].Z = SunCenter.Z - VecX.Z + VecY.Z;
	V[3].X = SunCenter.X + VecX.X + VecY.X;
	V[3].Y = SunCenter.Y + VecX.Y + VecY.Y;
	V[3].Z = SunCenter.Z + VecX.Z + VecY.Z;

	// Render sun.
	gGraphics.BlendMode(BLEND_ONE,BLEND_INVOTHERCOLOR);
	gGraphics.Strip(V,4);

	// Restore view matrix.
	gGraphics.SetViewMatrix(&gRender.Frame.ViewMatrix);
}
