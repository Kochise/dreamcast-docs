/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    RSky.cpp

Abstract:

    Sky rendering.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCWorld.h"
#include "DCGraphics.h"
#include "DCRender.h"

// Rendering defines.
#define SKY1_ROTATE		DC_TO_RADIANS(10.0f)
#define SKY1_SCALEU		0.1f
#define SKY1_SCALEV		SKY1_SCALEU
#define SKY1_STEPU		(0.6783f*0.5f)
#define SKY1_STEPV		-0.05f

#define SKY2_ROTATE		DC_TO_RADIANS(-10.0f)
#define SKY2_SCALEU		0.11f
#define SKY2_SCALEV		SKY2_SCALEU
#define SKY2_STEPU		(1.48777f*0.5f)
#define SKY2_STEPV		0.05f

#define MIN_SKY_VIEW_ANGLE	DC_TO_RADIANS(-35.0f)

// Texture defines.
#define SKY1_TEXTURE_IMAGE TEXT("Sky1")
#define SKY2_TEXTURE_IMAGE TEXT("Sky2")

// Strip defines.
// Number of steps must be an odd number.
#define NUM_STRIPS_HIGH			22 // 28
#define NUM_HALF_STRIPS_HIGH	(NUM_STRIPS_HIGH+1)
#define NUM_STEPS_HIGH			35 // 47
#define STRIP_LEN_HIGH			(NUM_STEPS_HIGH+3)
#define HALF_STRIP_LEN_HIGH		(STRIP_LEN_HIGH/2)

#define NUM_STRIPS_LOW			14
#define NUM_HALF_STRIPS_LOW		(NUM_STRIPS_LOW+1)
#define NUM_STEPS_LOW			23
#define STRIP_LEN_LOW			(NUM_STEPS_LOW+3)
#define HALF_STRIP_LEN_LOW		(STRIP_LEN_LOW/2)

// Special vertex type for the sky.
struct SkyVertex
{
	// Screen X and Y.
	float SX,SY;
	// Normal representing the base view direction of this vertex.
	float NX,NY,NZ;
};

// Rendering variables.
float Sky1ShiftU,Sky1ShiftV,Sky2ShiftU,Sky2ShiftV;
// Texture variables.
static HANDLE Sky1Texture,Sky2Texture;
// Strip variables.
static int NumStrips,NumHalfStrips,NumSteps,StripLen,HalfStripLen;
static float LastViewAngH,LastViewAngV;
static float HalfStripAngles[NUM_HALF_STRIPS_HIGH];
static SkyVertex *HalfStrips[NUM_HALF_STRIPS_HIGH];
static SkyVertex *VertexBuffer;

static DCVertex *VBuff;

// Initializes the sky.
BOOL InitSky(void)
{
	// Init rendering variables.
	Sky1ShiftU=Sky1ShiftV=Sky2ShiftU=Sky2ShiftV=0;

	// Add sky textures.
	Sky1Texture=gGraphics.AddTexture(ReadImageFileMipmapped,SKY1_TEXTURE_IMAGE,TRUE,FALSE);
	Sky2Texture=gGraphics.AddTexture(ReadImageFileMipmapped,SKY2_TEXTURE_IMAGE,TRUE,FALSE);
	if (!Sky1Texture || !Sky2Texture)
		return FALSE;

	// Set variables dependent on detail level.
#ifndef DREAMCAST // We don't really want a high detail sky on Dreamcast since
	              // not all the math is implemented in the CPU (atan).
	if (gHighDetail)
	{
		NumStrips=NUM_STRIPS_HIGH;
		NumHalfStrips=NUM_HALF_STRIPS_HIGH;
		NumSteps=NUM_STEPS_HIGH;
		StripLen=STRIP_LEN_HIGH;
		HalfStripLen=HALF_STRIP_LEN_HIGH;
	}
	else
#endif
	{
		NumStrips=NUM_STRIPS_LOW;
		NumHalfStrips=NUM_HALF_STRIPS_LOW;
		NumSteps=NUM_STEPS_LOW;
		StripLen=STRIP_LEN_LOW;
		HalfStripLen=HALF_STRIP_LEN_LOW;
	}
	// Init other variables.
	LastViewAngH=LastViewAngV=0;
	
	// Allocate vertex buffer and initialize pointers to it.
	VertexBuffer=(SkyVertex *)DCMalloc(HalfStripLen*NumHalfStrips*sizeof(SkyVertex));
	for (int i=0;i<NumHalfStrips;i++)
		HalfStrips[i]=&VertexBuffer[HalfStripLen*i];

	// Temp vertex buffer needs to be 32 byte aligned for best performance.
	VBuff=(DCVertex *)DCMalloc32(sizeof(DCVertex)*STRIP_LEN_HIGH);
	if (!VBuff)
		return FALSE;

	return TRUE;
}

// Shuts down the sky.
void ShutdownSky(void)
{
	DCSafeFree32(VBuff);
	DCSafeFree(VertexBuffer);
}

// Handles animation of the sky over the specified time.
// We keep the shift values between 0 and 1 otherwise 
// precision errors will eventially (or not so eventually
// on most hardware) cause jittering problems.
static void TickSky(float Time)
{
#define TICK(Shift,Step) \
{ \
	Shift+=(Step)*Time; \
	while (Shift>=1.0f) \
		Shift-=1.0f; \
	while (Shift<0) \
		Shift+=1.0f; \
}
	
	TICK(Sky1ShiftU,SKY1_STEPU*SKY1_SCALEU);
	TICK(Sky1ShiftV,SKY1_STEPV*SKY1_SCALEV);
	TICK(Sky2ShiftU,SKY2_STEPU*SKY2_SCALEU);
	TICK(Sky2ShiftV,SKY2_STEPV*SKY2_SCALEV);

#undef TICK
}

// Generate vertex normals representing view directions of vertices.
static void GenerateVertexNormals(float ViewAngH, float ViewAngV)
{
	float ResX=(float)gGraphics.GetFrameBufferResX();
	float ResY=(float)gGraphics.GetFrameBufferResY();
	float FracHStep=1.0f/(float)NumSteps;
	float FracVStep=1.0f/(float)NumStrips;
	// These assume Z=1.
	float MaxX=(float)tan(ViewAngH);
	float MaxY=(float)tan(ViewAngV);

	// Generate each of the half-strips.
	float FracV=0;
	for (int V=0;V<NumHalfStrips;V++,FracV+=FracVStep)
	{
		// Figure out vertical angle of this half-strip.
		float Y=MaxY * (1 - FracV*2);
		HalfStripAngles[V]=(float)atan(Y/1.0f);
		
		// Generate the vertices.
		float FracH=(V & 0x01) ? 0 : -FracHStep;
		for (int H=0;H<HalfStripLen;H++,FracH+=FracHStep*2)
		{
			SkyVertex *Vert=HalfStrips[V]+H;

			// Clamp fractional portion to screen edges.
			float FracHTmp=__min(1.0f,__max(0.0f,FracH));

			// Generate screen coordinates.
			Vert->SX=ResX*FracHTmp;
			Vert->SY=ResY*FracV;

			// Get X and Y values.
			float X=MaxX * (FracHTmp*2 - 1);
			float Y=MaxY * (1 - FracV*2);
		
			// Normalize and save.
			float Normalizer=1.0f/(float)sqrt(X*X + Y*Y + 1);
			Vert->NX=X*Normalizer;
			Vert->NY=Y*Normalizer;
			Vert->NZ=Normalizer;
		}
	}
}

// Renders a single pass of the sky.
static void RenderSkyPass(int HalfStripCount, float ViewAngleH, float ViewAngleV, 
						  float ShiftU, float ShiftV, float ScaleU, float ScaleV)
{
	DCVertex *VDst;
	SkyVertex *VSrc;
	int H,V;
	float NX,NY,NZ,NH;

	// Generate sines and consines necessary to do the rotations.
	float SinH=(float)sin(ViewAngleH);
	float CosH=(float)cos(ViewAngleH);
	float SinV=(float)sin(ViewAngleV);
	float CosV=(float)cos(ViewAngleV);

	// Init vertex buffer.
	for (int i=0;i<StripLen;i++)
	{
		// Make Z far so sky clears depth buffer.
		VBuff[i].Z=(float)0xFFFE/(float)0xFFFF;
		VBuff[i].Color=0xFFFFFFFF;
	}

	// Loop through strips.
	for (V=0;V<HalfStripCount;V++)
	{
		VSrc=HalfStrips[V];
		VDst=VBuff + (V & 0x01);

		// Generate vertices for this half-strip.
		for (H=HalfStripLen;H;H--,VSrc++,VDst+=2)
		{
			// Set X and Y.
			VDst->X=VSrc->SX;
			VDst->Y=VSrc->SY;

			// Calculate U and V. This code is fairly slow:
			// 2 square roots, two divides and an asin.
			// The asin could be removed if a rough approximation
			// for the arclength were used.

			// Rotate normal.
			NY			= VSrc->NZ*SinV + VSrc->NY*CosV;
			float TmpZ	= VSrc->NZ*CosV - VSrc->NY*SinV;
			NX			= VSrc->NX*CosH - TmpZ    *SinH;
			NZ			= VSrc->NX*SinH + TmpZ    *CosH;
			// Now need to make a 2D normal with horizontal and vertical components.
			// "NV" is NY.
			NH=(float)sqrt(NX*NX + NZ*NZ);

			// At this point we have an aribtrary triangle. We know 2 side 
			// lengths and the sin and cos of one of the angles. We need to
			// know the other length (distance from viewer to sky) and
			// one other angle (used to calulate arc length across sky).
			// We use the law of cosines and the law of sines to accomplish
			// this. Since our normal vector has unit lenth, the sin of angle 
			// "A" is NH and cos is -NV.
			// This calculation is from the law of cosines.
#define _a (DCW_WORLD_RADIUS+DCW_SKY_HEIGHT)
#define _b (DCW_WORLD_RADIUS)
			float SkyDist= (float)sqrt(_b*_b*(NY*NY-1) + _a*_a) - _b*NY;
			// Calulate InvW. We scale SkyDist by original NZ so we get perpendiclar
			// distance from screen, not distance from viewer.
			VDst->InvW=1.0f/(SkyDist*VSrc->NZ);
			// Calculate the other angle we need using law of sines.
			float C=(float)asin(SkyDist*NH*(1.0f/_a));
			// Calculate arc length and scale value to make it reasonable.
			float ArcLen=_a*C*(1.0f/DCW_SKY_HEIGHT);
#undef _a
#undef _b
			// Break arc length into U and V components.
			// First the arc length is divided by the horizontal vector
			// length to normalize NZ & NX.
			ArcLen/=NH;
			VDst->U=NZ*ArcLen*ScaleU + ShiftU;
			VDst->V=NX*ArcLen*ScaleV + ShiftV;
		}

		// Render strip unless the first half-strip.
		if (V!=0)
			gGraphics.Strip(VBuff,StripLen);
	}

}

// Renders the sky.
void RenderSky()
{
	// Tick the sky so it scrolls overhead.
	TickSky(gRender.Frame.FrameTime);

	// See if we need to (re)generate normals representing view directions.
	float MaxViewAngH,MaxViewAngV;
	gGraphics.GetViewMaxAngles(DCW_FOV,&MaxViewAngH,&MaxViewAngV);
	if (MaxViewAngH!=LastViewAngH || MaxViewAngV!=LastViewAngV)
	{
		LastViewAngH=MaxViewAngH;
		LastViewAngV=MaxViewAngV;
		GenerateVertexNormals(MaxViewAngH,MaxViewAngV);
	}
	
	// Get view angles in an easier to follow form.
	float ViewAngleH=gRender.Frame.ViewRot.Y;
	float ViewAngleV=gRender.Frame.ViewRot.X;
	
	// Figure out how many half strips we need to render.
	// First need to figure out the worst downward view angle.
	float LowAngle=-DC_PI;
	float ViewR=(float)sqrt(gRender.Frame.ViewLoc.X*gRender.Frame.ViewLoc.X + 
							gRender.Frame.ViewLoc.Z*gRender.Frame.ViewLoc.Z);
	if (ViewR < DCW_TERRAIN_OUTER_RADIUS*0.9f && gRender.Frame.ViewLoc.Y > 0)
		LowAngle=-(float)atan(gRender.Frame.ViewLoc.Y/(DCW_TERRAIN_OUTER_RADIUS - ViewR));
	// Clamp to bottom edge of view volume.
	if (LowAngle < (ViewAngleV-MaxViewAngV))
		LowAngle=ViewAngleV-MaxViewAngV;
	// Clamp to minimum allowed view angle.
	if (LowAngle < MIN_SKY_VIEW_ANGLE)
		LowAngle=MIN_SKY_VIEW_ANGLE;

	// Now count up the number of strips.
	int HalfStripCount;
	for (HalfStripCount=0;HalfStripCount<NumHalfStrips;HalfStripCount++)
		if (HalfStripAngles[HalfStripCount]+ViewAngleV < LowAngle)
			break;
	
	// Increment count and clear portion of depth buffer we won't draw over
	// if necessary.
	if (HalfStripCount!=NumHalfStrips)
	{
		int ResX=gGraphics.GetFrameBufferResX();
		int ResY=gGraphics.GetFrameBufferResY();
		DCRect R;

		R.X1=0;
		R.Y1=(int)((float)HalfStripCount * (float)ResY/(float)NumHalfStrips);
		R.X2=ResX;
		R.Y2=ResY;

		gGraphics.Clear(&R,FALSE,0xFF4D93FB,TRUE,1.0f);
			
		HalfStripCount++;
	}

	// Set state for first pass.
	gGraphics.SetTexture(Sky1Texture);
	gGraphics.DisableTransforms();
	gGraphics.ShadeModeFlat();
	gGraphics.DisableClipping();
	gGraphics.DisableBlend();
	gGraphics.EnableDepthTest();
	gGraphics.DepthFunc(DFUNC_ALWAYS);
	gGraphics.EnableDepthWrite();
	gGraphics.CullDisable();
	gGraphics.TexAddressModeRepeat();

	// Render first pass.
	RenderSkyPass(HalfStripCount,ViewAngleH+SKY1_ROTATE,ViewAngleV,Sky1ShiftU,Sky1ShiftV,SKY1_SCALEU,SKY1_SCALEV);

	// Set state for second pass.
	gGraphics.SetTexture(Sky2Texture);
	gGraphics.EnableBlend();
	gGraphics.BlendMode(BLEND_OTHERCOLOR,BLEND_ZERO);
	gGraphics.DepthFunc(DFUNC_EQUAL);

	// Render second pass.
	RenderSkyPass(HalfStripCount,ViewAngleH+SKY2_ROTATE,ViewAngleV,Sky2ShiftU,Sky2ShiftV,SKY2_SCALEU,SKY2_SCALEV);

	// Restore certain states to default.
	gGraphics.EnableTransforms();
	gGraphics.EnableClipping();
}
