/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    RFishEye.cpp

Abstract:

    Generates a fish eye lens view by rendering the scene from many
	different angles. Takes a while.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCWorld.h"
#include "DCGraphics.h"
#include "DCRender.h"

// In RMain.cpp
void RenderFishEyeScene(float RotX, float RotY);

#define TEXTURE_NAME TEXT("FishEye")
#define X_DIMENSION 640
#define Y_DIMENSION 480
#define MAX_Y_ANGLE DC_TO_RADIANS(16.0f/14.5f*90.0f) // A bit more than 90.
#define MAX_X_ANGLE (MAX_Y_ANGLE*(640.0f/480.0f)) 


// Gets the color value of a single environment map texel.
static DWORD GetTexel(float RotX, float RotY, float RangeAngle)
{
	// Render the scene from the specified direction.
	RenderFishEyeScene(RotX,RotY);

	// Get view angles used in screen shot.
	float MaxViewAngH,MaxViewAngV;
	gGraphics.GetViewMaxAngles(DCW_FOV,&MaxViewAngH,&MaxViewAngV);
	int X=gGraphics.GetFrameBufferResX();
	int Y=gGraphics.GetFrameBufferResY();
	float Z=0.5f*(float)Y/(float)tan(MaxViewAngV);
	int Delta=(int)(Z*(float)tan(RangeAngle));
	// Figure out region of screen to read back.
	DCRect Rect;
	Rect.X1=X/2-Delta+1;
	Rect.X2=X/2+Delta;
	Rect.Y1=Y/2-Delta+1;
	Rect.Y2=Y/2+Delta;

	// Read frame buffer back.
	DWORD *Data;
	if (!gGraphics.GetScreenShot(&Rect,&Data))
		return 0xFF000000;

	float R=0,G=0,B=0;

	// Average pixels.
	int Count=Delta*2 * Delta*2;
	for (int i=0;i<Count;i++)
	{
		DWORD Color=Data[i];
					
		R+=(float)((Color >> 16) & 0xFF);
		G+=(float)((Color >>  8) & 0xFF);
		B+=(float)((Color >>  0) & 0xFF);
	}
	// Scale values back down.
	R/=(float)Count;
	G/=(float)Count;
	B/=(float)Count;
	// Clamp to be sure.
	R=__min(255,__max(0,R));
	G=__min(255,__max(0,G));
	B=__min(255,__max(0,B));

	// Free screen shot buffer.
	DCFree(Data);

	return 0xFF000000 | ((int)R << 16) | ((int)G << 8) | (int)B;
}

// Creates the environment map texture by rendering the scene in many different directions.
void CreateFishEyeView()
{
	// Allocate space for texture.
	DWORD *Data=(DWORD *)DCMalloc(X_DIMENSION*Y_DIMENSION*sizeof(DWORD));
	if (!*Data)
		return;

	float X,Y;
	int IX,IY;

	for (Y=0.5f/(float)Y_DIMENSION,IY=0;IY<Y_DIMENSION;Y+=1.0f/(float)Y_DIMENSION,IY++)
	{
		for (X=0.5f/X_DIMENSION,IX=0;IX<X_DIMENSION;X+=1.0f/(float)X_DIMENSION,IX++)
		{
			float AX,AY,RotX,RotY;

			AX=(X-0.5f)*MAX_X_ANGLE*2;
			AY=(Y-0.5f)*MAX_Y_ANGLE*2;

			RotX=(float)sqrt(AX*AX+AY*AY);
			RotY=(float)acos(AY/RotX);
			if (AX>0)
				RotY*=-1;
			RotX=DC_PI*0.5f - RotX;

			Data[IY*X_DIMENSION + IX]=GetTexel(RotX,RotY,MAX_Y_ANGLE/(float)Y_DIMENSION);
		}
	}

	// Save view.
	WriteImageFile(TEXTURE_NAME,X_DIMENSION,Y_DIMENSION,FALSE,Data,TEXT("."));
	DCFree(Data);
}
