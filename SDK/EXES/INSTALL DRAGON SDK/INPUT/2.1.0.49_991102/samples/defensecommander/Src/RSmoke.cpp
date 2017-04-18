/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    RSmoke.cpp

Abstract:

	Code to procedurally generate smoke textures. 
	Doesn't actually do any rendering.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGraphics.h"

#define T_DIM 32
#define NOISE_SCALE 1.0f
#define NOISE_DIM_SCALE 2.0f
#define NOISE_FRAC_INC 0.6f
#define FINAL_SCALE 1.5f

float Fractal(float X, float Y, float Z, float FracInc)
{
	X+=100;
	Y+=200;
	Z+=300;
	float Ret=0;
	for (float f=1, Scale=1; f<T_DIM*0.5f/NOISE_DIM_SCALE; f*=2, Scale*=FracInc)
		Ret+=GNoise3(X*f,Y*f,Z*f)*Scale;				// Regular fractal.
	return Ret;
}

float Turbulence(float X, float Y, float Z, float FracInc)
{
	X+=300;
	Y+=200;
	Z+=100;
	float Ret=0;
	for (float f=1, Scale=1; f<T_DIM*0.5f/NOISE_DIM_SCALE; f*=2, Scale*=FracInc)
		Ret+=(float)fabs(GNoise3(X*f,Y*f,Z*f))*Scale;	// Turbulence.
	return Ret;
}


float EvaluateNoise(float X, float Y, float Z, int ID)
{
	X+=ID*11.0f;
	Y-=ID*13.0f;
	Z+=ID*31.0f;
	
	float Ret=Fractal(X*NOISE_DIM_SCALE,Y*NOISE_DIM_SCALE,Z*NOISE_DIM_SCALE,NOISE_FRAC_INC);
	Ret+=0.5f*Turbulence(X*NOISE_DIM_SCALE,Y*NOISE_DIM_SCALE,Z*NOISE_DIM_SCALE,NOISE_FRAC_INC);
	Ret*=1.0f/1.5f;
	Ret=Ret*0.5f+0.5f;
	Ret*=NOISE_SCALE;
	return Ret;
}

float EvaluateShapeScale(float X, float Y, int ID)
{
	// Figure out scale based on distance through a sphere at this point.
	float R2=X*X+Y*Y;

	if (R2>=1)
		return 0;
	else
		return (float)sqrt(1-R2);
}

BOOL CreateProceduralSmoke(HANDLE TextureID, int *X, int *Y, DWORD *Flags, DWORD **Data)
{
	// Try and load texture from disk.
	TCHAR Name[0x100];
	wsprintf(Name,TEXT("Smoke%02i"),(int)TextureID);
	if (!ReadImageFileNotMipmapped(Name,X,Y,Flags,Data))
	{
		// Load failed so we must create it.
		DWORD *D=(DWORD *)DCMalloc(T_DIM*T_DIM*sizeof(DWORD));
		if (!D)
			return FALSE;

		// Create the texture.
		for (int x=0;x<T_DIM;x++)
		{
			for (int y=0;y<T_DIM;y++)
			{
				float I=0;
				// Figure out normalized X and Y values.
				float NX=(x-(T_DIM-1)*0.5f)/(float)((T_DIM-1)*0.5f);
				float NY=(y-(T_DIM-1)*0.5f)/(float)((T_DIM-1)*0.5f);

				// Calculate scale value to shape smoke.
				I=EvaluateShapeScale(NX,NY,(int)TextureID);

				// Evaluate noise and subtract inverse scale.
				// This gives a half decent edge to the smoke.
				I=EvaluateNoise(NX,NY,0.0f,(int)TextureID)-(1-I);

				// Scale up final result.
				I*=FINAL_SCALE;

				// Convert intensity to color value.
				DWORD dwI=(int)__max(0,__min(255.0f,I*255.0f));
				D[y*T_DIM + x]=0xFF000000 | (dwI<<16) | (dwI<<8) | dwI;
			}
		}

		// Save newly created file so we don't have to create it again.
		WriteImageFile(Name,T_DIM,T_DIM,FALSE,D);

		// Set return data.
		*X=*Y=T_DIM;
		*Flags=0;//TFLAG_MIPMAPPED;
		*Data=D;
	}
	return TRUE;
}
