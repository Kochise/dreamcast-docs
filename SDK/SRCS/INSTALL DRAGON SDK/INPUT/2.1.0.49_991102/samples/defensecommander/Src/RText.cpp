/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    RText.cpp

Abstract:

    Text rendering.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGraphics.h"
#include "DCRText.h"
#include "DCWorld.h"

// Whether to render lowercase as smaller uppercase
#define LOWER_AS_UPPER

#define TEXT_TEXTURE_IMAGE TEXT("Font")

// These defines are used to calculate U and V values for the texture.
#define TEX_DIM_X 256
#define TEX_DIM_Y 256
#define CHAR_X 24
#define CHAR_Y 24
#define SPACING_X 1
#define SPACING_Y 1
#define BELOWLINE 3
#define LOWERCASE_SCALEDOWN 0.25f
#define DIM_X 10
#define DIM_Y 10

#define START_CHAR	33
#define END_CHAR	(START_CHAR + DIM_X*DIM_Y-1) 

static HANDLE TextTexture;

// Initialize text routines.
BOOL InitText(void)
{
	TextTexture=gGraphics.AddTexture(ReadImageFileIntensityToAlphaNotMipmapped,TEXT_TEXTURE_IMAGE,TRUE,FALSE);
	if (!TextTexture)
		return FALSE;
	return TRUE;
}

// Shutdown text routines.
void ShutdownText(void)
{
	// Nothing to do.
}

// Sets up the rendering state for rendering text.
void RenderTextBegin(void)
{
	gGraphics.ShadeModeFlat();
	gGraphics.EnableBlend();
	gGraphics.BlendMode(BLEND_SRCALPHA,BLEND_INVSRCALPHA);
	gGraphics.DisableDepthTest();
	gGraphics.DisableDepthWrite();
	gGraphics.CullDisable();
	gGraphics.SetTexture(TextTexture);
}

// Restores any "default" states.
void RenderTextEnd(void)
{
	// Nothing to do.
}

// Renders a text string.
void RenderText(TCHAR *Text, float X, float Y, float Size, DWORD Color)
{
	float FontX=Size;
	float FontY=Size;

	// Init vertices for text character.
	DCVertex V[4];
	V[0].Z=V[1].Z=V[2].Z=V[3].Z=0;
	V[0].InvW=V[1].InvW=V[2].InvW=V[3].InvW=1;
	V[0].Color=V[1].Color=V[2].Color=V[3].Color=Color;
	
	// Loop through text, rendering a character at a time.
	for (float CurrX=X;*Text!=0;Text++)
	{
		TCHAR Char=*Text;

		if (Char>=START_CHAR && Char<=END_CHAR)
		{
			// Figure out X and Y values.
			float X1=CurrX * gGraphics.ScaleX2D + gGraphics.TransX2D;
			float X2=(CurrX+FontX) * gGraphics.ScaleX2D + gGraphics.TransX2D;
			float Y1=Y * gGraphics.ScaleY2D + gGraphics.TransY2D;
			float Y2=(Y+FontY) * gGraphics.ScaleY2D + gGraphics.TransY2D;

#ifdef LOWER_AS_UPPER
			// Render lower case as shrunk uppercase.
			if (Char>=(TCHAR)'a' && Char<=(TCHAR)'z')
			{
				// Make uppercase.
				Char-=(TCHAR)'a' - (TCHAR)'A';

				// Shrink font vertically.
				Y1+=FontY * LOWERCASE_SCALEDOWN * gGraphics.ScaleY2D;
				
				// Shift font back up a bit to account for the fact that
				// the base of the characters are not at the very bottom
				// of the character cell.
				float Shift=FontY * (LOWERCASE_SCALEDOWN * (float)BELOWLINE/(float)CHAR_Y) * gGraphics.ScaleY2D;
				Y1-=Shift;
				Y2-=Shift;
			}
#endif

			// Figure out U and V positions.
			Char-=START_CHAR;
			float TexU=(Char%DIM_X)*((float)(CHAR_X+SPACING_X)/(float)TEX_DIM_X);
			float TexV=(Char/DIM_X)*((float)(CHAR_Y+SPACING_Y)/(float)TEX_DIM_Y);

			// Generate vertex data.
			V[0].X=X1;
			V[0].Y=Y1;
			V[0].U=TexU;
			V[0].V=TexV;

			V[1].X=X2;
			V[1].Y=Y1;
			V[1].U=TexU+((float)CHAR_X/(float)TEX_DIM_X);
			V[1].V=TexV;

			V[2].X=X1;
			V[2].Y=Y2;
			V[2].U=TexU;
			V[2].V=TexV+((float)CHAR_Y/(float)TEX_DIM_Y);

			V[3].X=X2;
			V[3].Y=Y2;
			V[3].U=TexU+((float)CHAR_X/(float)TEX_DIM_X);
			V[3].V=TexV+((float)CHAR_Y/(float)TEX_DIM_Y);

			gGraphics.Strip(V,4);
		}
		// Move draw position.
		if (Char==(TCHAR)'\n')
		{
			CurrX=X;
			Y+=FontY;
		}
		else
		{
			CurrX+=FontX;
		}
	}
}

// Returns the number of lines in a string.
int  GetNumLines(TCHAR *String)
{
	int Lines;

	for (Lines=1;*String!=0;String++)
	{
		if (*String==(TCHAR)'\n')
			Lines++;
	}
	return Lines;
}

// Returns the maximum line length in a string.
int  GetMaxLineLength(TCHAR *String)
{
	int LineLength,MaxLineLength;

	for (LineLength=MaxLineLength=0;*String!=0;String++)
	{
		if (*String==(TCHAR)'\n')
		{
			if (LineLength>MaxLineLength)
				MaxLineLength=LineLength;
			LineLength=0;
		}
		else
		{
			LineLength++;
		}
	}
	return __max(MaxLineLength,LineLength);
}
