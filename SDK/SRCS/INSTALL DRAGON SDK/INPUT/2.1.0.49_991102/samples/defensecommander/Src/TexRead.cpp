/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    TexRead.cpp

Abstract:

	Functions for reading and converting texture files. 
	Uses functions in Util.cpp.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGraphics.h"

// Reads an image file and sets the mipmapped flag.
// Scales textures larger than 32x32.
BOOL ReadImageFileMipmappedScaleDown32x32(HANDLE FileName, int *Width, int *Height, DWORD *Flags, DWORD **Data)
{
	BOOL Alpha;
	if (!ReadImageFile((TCHAR *)FileName,Width,Height,&Alpha,Data))
		return FALSE;

	if (*Width==*Height && *Width>=64)
	{
		for (int y=0;y<*Height/2;y++)
		{
			DWORD *Src=*Data + y*2*(*Width);
			DWORD *Dst=*Data + y*(*Width/2);
			for (int x=0;x<*Width/2;x++,Src+=2,Dst++)
			{
				DWORD C1=( (Src[0]) & 0xFCFCFCFC) >> 2;
				DWORD C2=( (Src[1]) & 0xFCFCFCFC) >> 2;
				DWORD C3=( (Src[0 + *Width]) & 0xFCFCFCFC) >> 2;
				DWORD C4=( (Src[1 + *Width]) & 0xFCFCFCFC) >> 2;

				*Dst=C1+C2+C3+C4;
			}
		}

		*Width/=2;
		*Height/=2;
	}

	*Flags=TFLAG_MIPMAPPED | (Alpha ? TFLAG_MIPMAPPED : 0);
	return TRUE;
}



// Reads an image file and sets the mipmapped flag.
BOOL ReadImageFileMipmapped(HANDLE FileName, int *Width, int *Height, DWORD *Flags, DWORD **Data)
{
	BOOL Alpha;
	if (!ReadImageFile((TCHAR *)FileName,Width,Height,&Alpha,Data))
		return FALSE;

	*Flags=TFLAG_MIPMAPPED | (Alpha ? TFLAG_MIPMAPPED : 0);
	return TRUE;
}

// Reads an image file and does not set the mipmapped flag.
BOOL ReadImageFileNotMipmapped(HANDLE FileName, int *Width, int *Height, DWORD *Flags, DWORD **Data)
{
	BOOL Alpha;
	if (!ReadImageFile((TCHAR *)FileName,Width,Height,&Alpha,Data))
		return FALSE;

	*Flags=(Alpha ? TFLAG_MIPMAPPED : 0);
	return TRUE;
}

static void ConvertIntensityToAlpha(int X, int Y, DWORD *Data)
{
	// Convert to alpha map.
	for (int i=0,Count=X*Y;i<Count;i++)
	{
		DWORD C=Data[i];
		Data[i]=(__max((C & 0x00FF0000)>>16,__max((C & 0x0000FF00)>>8,C & 0x000000FF)) << 24) |
			       0x00FFFFFF;
	}
}

// Reads an image file and sets the mipmapped flag.
BOOL ReadImageFileIntensityToAlphaMipmapped(HANDLE FileName, int *Width, int *Height, DWORD *Flags, DWORD **Data)
{
	BOOL Alpha;
	if (!ReadImageFile((TCHAR *)FileName,Width,Height,&Alpha,Data))
		return FALSE;

	ConvertIntensityToAlpha(*Width,*Height,*Data);

	*Flags=TFLAG_MIPMAPPED | TFLAG_ALPHA;
	return TRUE;
}

// Reads an image file and does not set the mipmapped flag.
BOOL ReadImageFileIntensityToAlphaNotMipmapped(HANDLE FileName, int *Width, int *Height, DWORD *Flags, DWORD **Data)
{
	BOOL Alpha;
	if (!ReadImageFile((TCHAR *)FileName,Width,Height,&Alpha,Data))
		return FALSE;

	ConvertIntensityToAlpha(*Width,*Height,*Data);

	*Flags=TFLAG_ALPHA;
	return TRUE;
}

BOOL ReadAndCombineRGBWithAlpha(HANDLE FileName, int *Width, int *Height, DWORD **Data)
{
	DWORD *TmpData1, *TmpData2;
	int TmpWidth1, TmpHeight1, TmpWidth2, TmpHeight2;
	TCHAR TmpFileName[0x100];
	BOOL TmpAlpha;

	// Read RGB map.
	if (!ReadImageFile((TCHAR *)FileName,&TmpWidth1,&TmpHeight1,&TmpAlpha,&TmpData1))
		return FALSE;

	// Read Alpha map.
	wsprintf(TmpFileName,TEXT("%sA"),FileName);
	if (!ReadImageFile(TmpFileName,&TmpWidth2,&TmpHeight2,&TmpAlpha,&TmpData2))
	{
		DCFree(TmpData1);
		return FALSE;
	}

	if (TmpWidth1!=TmpWidth2 || TmpHeight1!=TmpHeight2)
	{
		DCFree(TmpData1);
		DCFree(TmpData2);
		return FALSE;
	}

	// Combine.
	for (int i=0,Count=TmpWidth1*TmpHeight1;i<Count;i++)
	{
		DWORD C=TmpData2[i];
		DWORD Alpha=(__max((C & 0x00FF0000)>>16,__max((C & 0x0000FF00)>>8,C & 0x000000FF)) << 24);
		DWORD Color=TmpData1[i] & 0x00FFFFFF;
		TmpData1[i]=Alpha | Color;
	}

	// Free alpha map.
	DCFree(TmpData2);

	*Width=TmpWidth1;
	*Height=TmpHeight1;
	*Data=TmpData1;

	return TRUE;
}

BOOL ReadImageFilePlusAlphaMipmapped(HANDLE FileName, int *Width, int *Height, DWORD *Flags, DWORD **Data)
{
	if (!ReadAndCombineRGBWithAlpha(FileName, Width, Height, Data))
		return FALSE;

	*Flags=TFLAG_MIPMAPPED | TFLAG_ALPHA;
	return TRUE;
}

BOOL ReadImageFilePlusAlphaNotMipmapped(HANDLE FileName, int *Width, int *Height, DWORD *Flags, DWORD **Data)
{
	if (!ReadAndCombineRGBWithAlpha(FileName, Width, Height, Data))
		return FALSE;

	*Flags=TFLAG_ALPHA;
	return TRUE;
}
