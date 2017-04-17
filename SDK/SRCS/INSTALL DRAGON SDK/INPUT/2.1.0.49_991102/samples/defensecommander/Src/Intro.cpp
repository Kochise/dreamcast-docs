/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    Intro.cpp

Abstract:

    Displays intro screen.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGraphics.h"

#define INTRO_SCREEN_IMAGE_PC TEXT("IntroPC")
#define INTRO_SCREEN_IMAGE_CE TEXT("IntroCE")

static _inline void GetValues(int Src,int Max,
							  int &Index1,int &Index2,
							  int &Scale1,int &Scale2)
{
	// First index is just integer portion of fixed point value.
	Index1=Src>>16;

	// Clamp index 1.
	if (Index1<0) Index1=0;
	if (Index1>=Max) Index1=Max-1;

	int Fraction=Src & 0x0000FFFF;
	if (Fraction < 0x00008000)
	{
		// Take pixels to the left/top.
		Index2=Index1-1;
		if (Index2 < 0) Index2=0;
		Scale1=0x00008000 + Fraction;
		Scale2=0x00008000 - Fraction;
	}
	else
	{
		// Take pixels to the right/bottom.
		Index2=Index1+1;
		if (Index2 >= Max) Index2=Max-1;
		Scale1=0x00018000 - Fraction;
		Scale2=Fraction - 0x00008000;
	}
}

void DisplaySplashBitmap(TCHAR *FileName,BOOL Front)
{
	// Read image file.
	DWORD *Image;
	int X,Y,Alpha;
	if (!ReadImageFile(FileName,&X,&Y,&Alpha,&Image))
		return;

	// Lock frame buffer.
	void *Address;
	int Stride;
	if (!gGraphics.LockFrameBuffer(&Address,&Stride,Front))
	{
		DCFree(Image);
		return;
	}

	// Stretch-blit image into frame buffer using our own (slow) bilinear routine.
	// Most of the math for getting source pixels is in fixed point.
	int DestX=gGraphics.GetFrameBufferResX();
	int DestY=gGraphics.GetFrameBufferResY();
	int XStep=(X<<16)/DestX;
	int YStep=(Y<<16)/DestY;
	int BitDepth=gGraphics.GetFrameBufferBitDepth();

	for (int YCount=0,SrcYOffset=YStep/2;YCount<DestY;YCount++,SrcYOffset+=YStep)
	{
		void *TmpAddress=((BYTE *)Address)+(DestY-YCount-1)*Stride;

		for (int XCount=0,SrcXOffset=XStep/2;XCount<DestX;XCount++,SrcXOffset+=XStep)
		{
			// Get X&Y related values, depending on fractional source values.
			int XIndex1,XIndex2,XScale1,XScale2;
			int YIndex1,YIndex2,YScale1,YScale2;
			GetValues(SrcXOffset,X,XIndex1,XIndex2,XScale1,XScale2);
			GetValues(SrcYOffset,Y,YIndex1,YIndex2,YScale1,YScale2);
			// Calculate combined scale values.
			int Scale1=((XScale1>>1)*(YScale1>>1))>>14;
			int Scale2=((XScale2>>1)*(YScale1>>1))>>14;
			int Scale3=((XScale1>>1)*(YScale2>>1))>>14;
			int Scale4=((XScale2>>1)*(YScale2>>1))>>14;

			// Calculate RGB value from 4 source pixels.
			int R,G,B;
			BYTE *Src;

			// Source pixel 1.
			Src=(BYTE *)(Image + XIndex1 + YIndex1*X);
			B=Src[0]*Scale1;
			G=Src[1]*Scale1;
			R=Src[2]*Scale1;

			// Source pixel 2.
			Src=(BYTE *)(Image + XIndex2 + YIndex1*X);
			B+=Src[0]*Scale2;
			G+=Src[1]*Scale2;
			R+=Src[2]*Scale2;

			// Source pixel 3.
			Src=(BYTE *)(Image + XIndex1 + YIndex2*X);
			B+=Src[0]*Scale3;
			G+=Src[1]*Scale3;
			R+=Src[2]*Scale3;

			// Source pixel 4.
			Src=(BYTE *)(Image + XIndex2 + YIndex2*X);
			B+=Src[0]*Scale4;
			G+=Src[1]*Scale4;
			R+=Src[2]*Scale4;

			// Adjust final RGB values.
			R=R>>16;
			G=G>>16;
			B=B>>16;

			// Now have final RGB value for this screen pixel, so
			// write into frame buffer using different code for each 
			// possible bit depth.
			switch (BitDepth)
			{
				case 15:
					*((WORD *)TmpAddress)=((R & 0xF8) << 7) | ((G & 0xF8) << 2) | ((B & 0xF8) >> 3);
					TmpAddress=((BYTE *)TmpAddress)+2;
					break;
				case 16:
					*((WORD *)TmpAddress)=((R & 0xF8) << 8) | ((G & 0xFC) << 3) | ((B & 0xF8) >> 3);
					TmpAddress=((BYTE *)TmpAddress)+2;
					break;
				case 24:
					((BYTE *)TmpAddress)[0]=B;
					((BYTE *)TmpAddress)[1]=G;
					((BYTE *)TmpAddress)[2]=R;
					TmpAddress=((BYTE *)TmpAddress)+3;
					break;
				case 32:
					((BYTE *)TmpAddress)[0]=B;
					((BYTE *)TmpAddress)[1]=G;
					((BYTE *)TmpAddress)[2]=R;
					((BYTE *)TmpAddress)[3]=0xFF;
					TmpAddress=((BYTE *)TmpAddress)+4;
					break;
			}
		}
	}

	// Unlock frame buffer.
	gGraphics.UnlockFrameBuffer(Front);

	// Free memory allocated for image.
	DCFree(Image);

	// Flip frame buffer so we can see the result.
	if (!Front)
		gGraphics.Flip();
}

// Displays the intro screen which will be visible while the game loads.
void DisplayIntroScreen(void)
{
#ifdef DREAMCAST	
	DisplaySplashBitmap(INTRO_SCREEN_IMAGE_CE,FALSE);
#else
	DisplaySplashBitmap(INTRO_SCREEN_IMAGE_PC,FALSE);
#endif
}
