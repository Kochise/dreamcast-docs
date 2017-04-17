/*****************************************************************************
  Name : D3DTPrint3D.c		v1.0
  Date : October 1998

  * Description : 
  This file is part of the TOOLS library (D3DTools.lib) used
  with the SDK demos for PowerVR series 2.
  
  Description : Displays a text string using 3D polygons.
				Can be done in two ways: using a window defined by the user
				or writing straight on the screen.

  Copyright : 1999 by Imagination Technologies Limited. All rights reserved.
******************************************************************************/

/* INCLUDES */
#include <windows.h>
#include <stdio.h>
#include <d3d.h>
#include <malloc.h>
#include <memory.h>

#include "D3DTPrint3D.h"		
#include "D3DTPrint3D.dat"		/* Print3D texture data */

/* DEFINES */
#define	WCE_DEBUG(x) OutputDebugString(x);

#define Align32Byte(adr)        ((((long)adr) + 0x1F) & 0xFFFFFFE0)

#define MAX_LETTERS 5000
#define MAX_WINDOWS 20
#define LINES_SPACING 29.0f

#define Print3D_WIN_EXIST	1
#define Print3D_WIN_ACTIVE	2
#define Print3D_WIN_TITLE	4
#define Print3D_WIN_STATIC	8
#define Print3D_FULL_OPAQUE	16
#define Print3D_FULL_TRANS	32
#define Print3D_ADJUST_SIZE	64
#define Print3D_NO_BORDER	128

typedef struct {
	DWORD dwFlags;

	/* Text Buffer */
	TCHAR  *pTextBuffer;
	DWORD  dwBufferSizeX;
	DWORD  dwBufferSizeY;
	DWORD  dwCursorPos;

	/* Title */
	float fTitleFontSize;
	float fTextRMinPos;
	DWORD dwTitleFontColorL;
	DWORD dwTitleFontColorR;
	DWORD dwTitleBaseColor;
	TCHAR  *bTitleTextL;
	TCHAR  *bTitleTextR;

	/* Window */
	float fWinFontSize;
	DWORD dwWinFontColor;
	DWORD dwWinBaseColor;
	float fWinPos[2];
	float fWinSize[2];
	float fZPos;
	DWORD dwSort;

} D3DTPrint3DWIN;

/*  GLOBALS  */
static D3DTPrint3DWIN	GlobWin[MAX_WINDOWS];

static struct {
	LPDIRECT3DTEXTURE2      lpTexture[10];
	LPDIRECTDRAWSURFACE4    lpDDTextureSurface[10];
	D3DTEXTUREHANDLE		hTexture[10];
	D3DTLVERTEX				*pVerticesFont;		
	WORD					pFacesFont[MAX_LETTERS*2*3];
	LPDIRECTDRAW4			lpDD4;
	LPDIRECT3DDEVICE3		lpDev3;
	DWORD					dwCreatedWins;
	float					fScreenScale[2];
	DWORD					dwTopMost;
	BOOL					bInitOK;
	BOOL					bZCmp;
	} Glob;

static BOOL bTexturesReleased = TRUE;

/********************/
/* LOCAL PROTOTYPES */
/********************/
static HRESULT	DrawWindow		(DWORD dwWin, DWORD Color, float fZPos, float fPosX, float fPosY, 
									float fSizeX, float fSizeY);

static void		LocalPrint3D	(DWORD dwWin, float fZPos, float XPos, float YPos, float fScale, 
									int Colour, const TCHAR *Text);

static BOOL		UpLoad4444		(DWORD TexID, unsigned char *pSource, DWORD nSize, DWORD nMode);

static float	GetLength		(float fFontSize, TCHAR *sString);

static void		RenderStates	(int nAction);


/*----------------------------------------------------------------------
 *  Function Name   : D3DTPrint3DSetTextures							 
 *  Inputs          :                                                     
 *  Outputs         :                                                   
 *  Returns         : TRUE if OK.                                       
 *  Globals Used    :                                                   
 *  Description     : Initialization and texture upload.
 *  Note			: Must be called in InitView
 *----------------------------------------------------------------------*/
BOOL D3DTPrint3DSetTextures(LPDIRECT3DDEVICE3 lpDev3, LPDIRECTDRAW4 lpDD4, DWORD dwScreenX, DWORD dwScreenY)
{
register	i;
BOOL		bStatus;
D3DDEVICEDESC	ddHAL, ddHEL, *lpD3DDeviceDesc;
static BOOL bIsFirstCall = TRUE;

		Glob.bInitOK = FALSE;

		Glob.lpDev3 = lpDev3;
		Glob.lpDD4  = lpDD4;

		Glob.fScreenScale[0] = (float)dwScreenX/640.0f;
		Glob.fScreenScale[1] = (float)dwScreenY/480.0f;

		Glob.dwTopMost = 255;

		if (bTexturesReleased==FALSE)
		{
			D3DTPrint3DReleaseTextures();
		}

		bTexturesReleased = FALSE;
	   
		/* Memory allocation for vertices */
		Glob.pVerticesFont = (D3DTLVERTEX *)malloc (MAX_LETTERS * 4 * sizeof(D3DTLVERTEX));

		if (!Glob.pVerticesFont)
		{
			WCE_DEBUG (L"\nDTPrint3DInit: Memory allocation error.");
			return FALSE;
		}

		/*
		 * This is the window background texture
		 * Type 0 because the data comes in TexTool rectangular format.
		 */

		bStatus = UpLoad4444(1, (unsigned char *)WindowBackground, 16, 0);
		if (!bStatus) return FALSE;
		
		bStatus = UpLoad4444(2, (unsigned char *)WindowPlainBackground, 16, 0);
		if (!bStatus) return FALSE;

		bStatus = UpLoad4444(3, (unsigned char *)WindowBackgroundOp, 16, 0);
		if (!bStatus) return FALSE;

		bStatus = UpLoad4444(4, (unsigned char *)WindowPlainBackgroundOp, 16, 0);
		if (!bStatus) return FALSE;

	
		/*
		 * This is the texture with the fonts.
		 * Type 1 because there is only alpha component (RGB are white).
		 */
		bStatus = UpLoad4444(0, (unsigned char *)D3DTPrint3DABC_Pixels, 256, 1);
		if (!bStatus) return FALSE;		
		
		/* Vertex indices */
		for (i=0; i<MAX_LETTERS; i++)
		{
			Glob.pFacesFont[i*6+0] = 0+i*4;
			Glob.pFacesFont[i*6+1] = 1+i*4;
			Glob.pFacesFont[i*6+2] = 3+i*4;

			Glob.pFacesFont[i*6+3] = 3+i*4;
			Glob.pFacesFont[i*6+4] = 2+i*4;
			Glob.pFacesFont[i*6+5] = 0+i*4;
		}

		/*
		 * Checking Caps for ZComp = ALWAYS
		 */
		memset(&ddHAL, 0, sizeof(D3DDEVICEDESC));
		memset(&ddHEL, 0, sizeof(D3DDEVICEDESC));

		ddHAL.dwSize=sizeof(D3DDEVICEDESC);
		ddHEL.dwSize=sizeof(D3DDEVICEDESC);

		lpDev3->lpVtbl->GetCaps(lpDev3, &ddHAL, &ddHEL);
	
		/* If the device color model is 0, then software device : use HEL otherwise use HAL */
		if (!ddHAL.dcmColorModel) lpD3DDeviceDesc=&ddHEL;
		else lpD3DDeviceDesc=&ddHAL;
	
		Glob.bZCmp = ((DWORD)(lpD3DDeviceDesc->dpcTriCaps.dwZCmpCaps) & D3DPCMPCAPS_ALWAYS) ? TRUE:FALSE;

		/* Everything is OK */
		Glob.bInitOK = TRUE;

		/* Return OK */
		return TRUE;
}

/*----------------------------------------------------------------------*
 *  Function Name   : D3DTPrint3DReleaseTextures						 
 *  Inputs          :                                                     
 *  Outputs         :                                                   
 *  Returns         :                                                   
 *  Globals Used    : 								
 *  Description     : Deallocate the memory allocated in D3DTPrint3DSetTextures.  
 *----------------------------------------------------------------------*/
void D3DTPrint3DReleaseTextures(void)
{
register i;
  
    /* Release texture surfaces */
	for (i=0; i<5; i++)
	{
		RELEASE(Glob.lpTexture[i]);
	}

	for (i=0; i<5; i++)
	{
		RELEASE(Glob.lpDDTextureSurface[i]);
	}

	
	/* Free vertices allocated in InitTextures */
	if (Glob.pVerticesFont) 
	{
		free(Glob.pVerticesFont);
		Glob.pVerticesFont=NULL;
	}

	bTexturesReleased = TRUE;
}
/*----------------------------------------------------------------------
 *  Function Name	: D3DTPrint3DDeleteAllWindows
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
void D3DTPrint3DDeleteAllWindows(void)
{
register unsigned i;

	for (i=0; i<MAX_WINDOWS; i++)
	{
		D3DTPrint3DDeleteWindow (i);
	}

}
/*----------------------------------------------------------------------
 *  Function Name	: D3DTPrint3DDeleteWindow
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
void D3DTPrint3DDeleteWindow(DWORD dwWin)
{
	if(GlobWin[dwWin].dwFlags & Print3D_WIN_EXIST)
	{
		if (GlobWin[dwWin].pTextBuffer)
		{
			free (GlobWin[dwWin].pTextBuffer);
			GlobWin[dwWin].pTextBuffer = NULL;
		}

		if (GlobWin[dwWin].bTitleTextL) free (GlobWin[dwWin].bTitleTextL);
		if (GlobWin[dwWin].bTitleTextR) free (GlobWin[dwWin].bTitleTextR);

		GlobWin[dwWin].bTitleTextL = NULL;
		GlobWin[dwWin].bTitleTextR = NULL;
	}

	GlobWin[dwWin].dwFlags = 0;
}
/*----------------------------------------------------------------------
 *  Function Name	: D3DTPrint3DClearWindowBuffer
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
void D3DTPrint3DClearWindowBuffer(DWORD dwWin)
{
register unsigned i;

	if(GlobWin[dwWin].dwFlags & Print3D_WIN_EXIST)
	{
		for (i=0; i<GlobWin[dwWin].dwBufferSizeX*GlobWin[dwWin].dwBufferSizeY; i++) 
				*(GlobWin[dwWin].pTextBuffer+i) = 0;
	}

	GlobWin[dwWin].dwCursorPos	= 0;

}
/*----------------------------------------------------------------------
 *  Function Name	: D3DTPrint3DSetWindowBufferPointer
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
void D3DTPrint3DSetWindowBufferPointer(DWORD dwWin, DWORD dwXPos, DWORD dwYPos)
{
	if(GlobWin[dwWin].dwFlags & Print3D_WIN_EXIST)
	{
		if (dwXPos <= GlobWin[dwWin].dwBufferSizeX && dwYPos <= GlobWin[dwWin].dwBufferSizeY)
		{
			GlobWin[dwWin].dwCursorPos	= dwXPos + (GlobWin[dwWin].dwBufferSizeX*dwYPos);
		}
	}


}
/*----------------------------------------------------------------------
 *  Function Name	: D3DTPrint3DSetTopMostWindow
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		: 
 *----------------------------------------------------------------------*/
void D3DTPrint3DSetTopMostWindow(DWORD dwWin)
{
	Glob.dwTopMost = dwWin;
}
/*----------------------------------------------------------------------
 *  Function Name	: D3DTPrint3DSetWindowPos
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
void D3DTPrint3DSetWindowPos(DWORD dwWin, float fPosX, float fPosY)
{
	GlobWin[dwWin].fWinPos[0]		= fPosX * 640.0f/100.0f;
	GlobWin[dwWin].fWinPos[1]		= fPosY * 480.0f/100.0f;
}
/*----------------------------------------------------------------------
 *  Function Name	: D3DTPrint3DSetWindowSize
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
void D3DTPrint3DSetWindowSize(DWORD dwWin, float fSizeX, float fSizeY)
{
	GlobWin[dwWin].fWinSize[0]		= fSizeX * 640.0f/100.0f;
	GlobWin[dwWin].fWinSize[1]		= fSizeY * 480.0f/100.0f;
}

/*----------------------------------------------------------------------
 *  Function Name	: D3DTPrint3DDisplayAllWindows
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
void D3DTPrint3DDisplayAllWindows(void)
{
register unsigned i;

	/* The TopMost window is displayed the last one */
	for (i=0; i<MAX_WINDOWS; i++)
	{
		if((GlobWin[i].dwFlags & Print3D_WIN_EXIST) && i!=Glob.dwTopMost)
		{
			D3DTPrint3DDisplayWindow (i);
		}

	}

	if (GlobWin[Glob.dwTopMost].dwFlags & Print3D_WIN_EXIST)
	{
		D3DTPrint3DDisplayWindow (Glob.dwTopMost);
	}
}
/*----------------------------------------------------------------------
 *  Function Name	: D3DTPrint3DSetWindowFlags
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
void D3DTPrint3DSetWindowFlags (DWORD dwWin, DWORD dwFlags)
{

	if (dwFlags & PRINT3D_ACTIVATE_WIN)	GlobWin[dwWin].dwFlags |= Print3D_WIN_ACTIVE;
			
	if (dwFlags & PRINT3D_DEACTIVATE_WIN)	GlobWin[dwWin].dwFlags &= ~Print3D_WIN_ACTIVE;
			
	if (dwFlags & PRINT3D_ACTIVATE_TITLE)	GlobWin[dwWin].dwFlags |= Print3D_WIN_TITLE;
			
	if (dwFlags & PRINT3D_DEACTIVATE_TITLE) GlobWin[dwWin].dwFlags &= ~Print3D_WIN_TITLE;
			
	if (dwFlags & PRINT3D_FULL_OPAQUE)	GlobWin[dwWin].dwFlags |= Print3D_FULL_OPAQUE;
		
	if (dwFlags & PRINT3D_FULL_TRANS)	GlobWin[dwWin].dwFlags |= Print3D_FULL_TRANS;

	if (dwFlags & PRINT3D_ADJUST_SIZE_ALWAYS)
	{
		GlobWin[dwWin].dwFlags |= Print3D_ADJUST_SIZE;
		D3DTPrint3DAdjustWindowSize(dwWin, 0);
	}

	if (dwFlags & PRINT3D_NO_BORDER)	GlobWin[dwWin].dwFlags |= Print3D_NO_BORDER;
}
/*----------------------------------------------------------------------
 *  Function Name	: D3DTPrint3DSetWindow
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
void D3DTPrint3DSetWindow (DWORD dwWin, DWORD dwWinColor, DWORD dwFontColor, float fFontSize, 
						    float fPosX, float fPosY, float fSizeX, float fSizeY)
{
	
	/* Window */
	GlobWin[dwWin].fWinFontSize		= fFontSize;
	GlobWin[dwWin].dwWinFontColor	= dwFontColor;
	GlobWin[dwWin].dwWinBaseColor	= dwWinColor; 
	GlobWin[dwWin].fWinPos[0]		= fPosX  * 640.0f/100.0f;
	GlobWin[dwWin].fWinPos[1]		= fPosY  * 480.0f/100.0f;
	GlobWin[dwWin].fWinSize[0]		= fSizeX * 640.0f/100.0f;
	GlobWin[dwWin].fWinSize[1]		= fSizeY * 480.0f/100.0f;

}
/*----------------------------------------------------------------------
 *  Function Name	: D3DTPrint3DSetTitle
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
void D3DTPrint3DSetTitle (DWORD dwWin, DWORD dwBackgroundColor, float fFontSize, 
							DWORD dwFontColorLeft,  TCHAR *sTitleLeft, 
							DWORD dwFontColorRight, TCHAR *sTitleRight)
{

   	if (sTitleLeft) wsprintf (GlobWin[dwWin].bTitleTextL, sTitleLeft);
	if (sTitleRight) wsprintf (GlobWin[dwWin].bTitleTextR, sTitleRight);

	GlobWin[dwWin].fTitleFontSize	  = fFontSize;
	GlobWin[dwWin].dwTitleFontColorL  = dwFontColorLeft;
	GlobWin[dwWin].dwTitleFontColorR  = dwFontColorRight;
	GlobWin[dwWin].dwTitleBaseColor   = dwBackgroundColor; 
	GlobWin[dwWin].fTextRMinPos       = GetLength (GlobWin[dwWin].fTitleFontSize,
													GlobWin[dwWin].bTitleTextL)	+ 10.0f;

}
/*----------------------------------------------------------------------
 *  Function Name	: D3DTPrint3DCreateWindow
 *  Inputs			:
 *  Outputs			:
 *  Returns			: Handle to a window.
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
DWORD D3DTPrint3DCreateWindow (DWORD dwBufferSizeX, DWORD dwBufferSizeY)
{
register unsigned i;
static DWORD dwCurrentWin = 1;

	/* If the window hasn't been deleted, I delete it */
	if (GlobWin[dwCurrentWin].dwFlags & Print3D_WIN_EXIST)
	{
		D3DTPrint3DDeleteWindow(dwCurrentWin);
	}

	if (dwCurrentWin == 1)
	{
		/* Cleaning all the flags when first win is created.*/
		for (i=0; i<MAX_WINDOWS; i++) 
		{
			GlobWin[i].dwFlags = 0;
			GlobWin[i].pTextBuffer = NULL;
		}

	}

	if (dwCurrentWin == MAX_WINDOWS)
	{
		WCE_DEBUG (L"\nD3DTPrint3DCreateWindow : MAX_WINDOWS overflow.\n");
		return 0;
	}

	GlobWin[dwCurrentWin].dwFlags = Print3D_WIN_TITLE  | Print3D_WIN_EXIST | Print3D_WIN_ACTIVE;

	/* Text Buffer */
	GlobWin[dwCurrentWin].dwBufferSizeX = dwBufferSizeX + 1;
	GlobWin[dwCurrentWin].dwBufferSizeY = dwBufferSizeY;
	
	GlobWin[dwCurrentWin].pTextBuffer  = (TCHAR *)malloc(dwBufferSizeX*(dwBufferSizeY+1)*sizeof(TCHAR));
	GlobWin[dwCurrentWin].bTitleTextL  = (TCHAR *)malloc(1000*sizeof(TCHAR));
	GlobWin[dwCurrentWin].bTitleTextR  = (TCHAR *)malloc(1000*sizeof(TCHAR));
	
	if ((GlobWin[dwCurrentWin].pTextBuffer == NULL) |
		(GlobWin[dwCurrentWin].bTitleTextL == NULL) |
		(GlobWin[dwCurrentWin].bTitleTextR == NULL) )
	{
		WCE_DEBUG (L"\nD3DTPrint3DCreateWindow : No memory enough for Text Buffer.\n");
		return 0;
	}

	/* Cleaning the Buffer */
	for (i=0; i<dwBufferSizeX*(dwBufferSizeY+1); i++) *(GlobWin[dwCurrentWin].pTextBuffer+i) = 0;

	/* NULL string for the title */
	*(GlobWin[dwCurrentWin].bTitleTextL)  = 0;
	*(GlobWin[dwCurrentWin].bTitleTextR)  = 0;

	
	/* Title */
	GlobWin[dwCurrentWin].fTitleFontSize	= 1.0f;
	GlobWin[dwCurrentWin].dwTitleFontColorL = 0xFFFFFF00;
	GlobWin[dwCurrentWin].dwTitleFontColorR = 0xFFFFFF00;
	GlobWin[dwCurrentWin].dwTitleBaseColor  = 0xFF3030FF; /* Dark Blue */

	/* Window */
	GlobWin[dwCurrentWin].fWinFontSize		= 0.5f;
	GlobWin[dwCurrentWin].dwWinFontColor	= 0xFFFFFFFF;
	GlobWin[dwCurrentWin].dwWinBaseColor	= 0xFF8080FF; /* Light Blue */
	GlobWin[dwCurrentWin].fWinPos[0]		= 0.0f;
	GlobWin[dwCurrentWin].fWinPos[1]		= 0.0f;
	GlobWin[dwCurrentWin].fWinSize[0]		= 20.0f;
	GlobWin[dwCurrentWin].fWinSize[1]		= 20.0f;
	GlobWin[dwCurrentWin].fZPos		        = 0.001f - ((float)dwCurrentWin * (0.001f/MAX_WINDOWS));
	GlobWin[dwCurrentWin].dwSort		    = 0;
	GlobWin[dwCurrentWin].dwCursorPos		= 0;

	dwCurrentWin++;

	/* Returning the handle */
	return (dwCurrentWin-1);
}
/*----------------------------------------------------------------------
 *  Function Name	: D3DTPrint3DDisplayWindow
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
void D3DTPrint3DDisplayWindow (DWORD dwWin)
{
DWORD		i;
float		fTitleSize = 0.0f, fRPos, fNewPos;
DWORD		dwPointer = 0;
	  
		/* Read and write render states */
		RenderStates(0);
	
		/* 
		 * TITLE
		 */
		if(GlobWin[dwWin].dwFlags & Print3D_WIN_TITLE)
		{
			fTitleSize = GlobWin[dwWin].fTitleFontSize * 23.5f + 16.0f;
			
			if(GlobWin[dwWin].fTitleFontSize < 0.0f) fTitleSize = 8.0f +16;
			
			/* Background */
			if (!(GlobWin[dwWin].dwFlags & Print3D_FULL_TRANS))
			{
				DrawWindow (dwWin,GlobWin[dwWin].dwTitleBaseColor,
						GlobWin[dwWin].fZPos,
						GlobWin[dwWin].fWinPos[0],  
						GlobWin[dwWin].fWinPos[1], 
						GlobWin[dwWin].fWinSize[0], 
						fTitleSize);
			}

			/* Left text */
			LocalPrint3D(dwWin, GlobWin[dwWin].fZPos - 0.0005f/MAX_WINDOWS,
								(GlobWin[dwWin].fWinPos[0] + 6.0f), 
								(GlobWin[dwWin].fWinPos[1] + 7.0f), 
								GlobWin[dwWin].fTitleFontSize, 
								GlobWin[dwWin].dwTitleFontColorL, 
								GlobWin[dwWin].bTitleTextL);

			/* Right text */
			if (GlobWin[dwWin].bTitleTextR)
			{
				fRPos = GetLength (GlobWin[dwWin].fTitleFontSize,GlobWin[dwWin].bTitleTextR);
			
				fRPos = GlobWin[dwWin].fWinSize[0]  - fRPos - 6.0f;

				if(fRPos<GlobWin[dwWin].fTextRMinPos) fRPos = GlobWin[dwWin].fTextRMinPos;

				fRPos += GlobWin[dwWin].fWinPos[0];
			
				LocalPrint3D(dwWin, GlobWin[dwWin].fZPos - 0.0005f/MAX_WINDOWS,
								fRPos, 
								GlobWin[dwWin].fWinPos[1] + 7.0f, 
								GlobWin[dwWin].fTitleFontSize,
								GlobWin[dwWin].dwTitleFontColorR, 
								GlobWin[dwWin].bTitleTextR);
			}


		}
   

		/*
		 * WINDOW
		 */
		if (GlobWin[dwWin].dwFlags & Print3D_WIN_ACTIVE)
		{
			/* Background */
			if (!(GlobWin[dwWin].dwFlags & Print3D_FULL_TRANS))
			{
				DrawWindow (dwWin,GlobWin[dwWin].dwWinBaseColor,
						GlobWin[dwWin].fZPos,
						GlobWin[dwWin].fWinPos[0],  
						(GlobWin[dwWin].fWinPos[1] + fTitleSize), 
						GlobWin[dwWin].fWinSize[0],
						GlobWin[dwWin].fWinSize[1]);
	
			}
	
			dwPointer = 0;

			/* Text, line by line */
			for (i=0; i<GlobWin[dwWin].dwBufferSizeY; i++)
			{

				fNewPos = fTitleSize + (float)(i * GlobWin[dwWin].fWinFontSize) * LINES_SPACING;

				if(GlobWin[dwWin].fWinFontSize < 0.0f) fNewPos = fTitleSize + (float)(i * 12.0f);
		
				LocalPrint3D(dwWin, GlobWin[dwWin].fZPos - 0.0005f/MAX_WINDOWS,
								(GlobWin[dwWin].fWinPos[0] + 6.0f), 
								(GlobWin[dwWin].fWinPos[1] + 6.0f + fNewPos), 
								GlobWin[dwWin].fWinFontSize, GlobWin[dwWin].dwWinFontColor, 
								(GlobWin[dwWin].pTextBuffer + dwPointer));

			dwPointer += GlobWin[dwWin].dwBufferSizeX;
			}
		}

	  /* Restore render states */
	  RenderStates(1);

	  return;
}
/*----------------------------------------------------------------------
 *  Function Name	: D3DTPrint3DWindowOutput
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
void D3DTPrint3DWindowOutput (DWORD dwWin, const TCHAR *Format, ...)
{
DWORD		i;
DWORD		dwBufferSize, dwTotalLength = 0;
DWORD		dwPosBx, dwPosBy, dwSpcPos;
TCHAR		*Text;
va_list		args;
TCHAR		bChar;

	  if (!(GlobWin[dwWin].dwFlags & Print3D_WIN_EXIST)) return;

	  dwBufferSize = (GlobWin[dwWin].dwBufferSizeX+1) * (GlobWin[dwWin].dwBufferSizeY+1);

	  /* Temporal buffer for the string */
	  Text = (TCHAR *)malloc (dwBufferSize * sizeof(TCHAR));

      /* Reading the arguments to create our Text string */
	  va_start(args,Format);
	  wvsprintf(Text, Format, args);
	  va_end(args);


	  /* Lenght */
	  while (dwTotalLength<dwBufferSize && *(Text+dwTotalLength)!=0) dwTotalLength++;

	  /* X and Y pointer position */
	  dwPosBx = GlobWin[dwWin].dwCursorPos%GlobWin[dwWin].dwBufferSizeX;
	  dwPosBy = GlobWin[dwWin].dwCursorPos/GlobWin[dwWin].dwBufferSizeX;

	  for (i=0; i<dwTotalLength; i++)
	  {
		bChar = *(Text+i);

		/* Space (for word wrap only) */
		if (bChar == ' ') 
		{
			
			/* looking for the next space (or return or end) */
			dwSpcPos = 1;
			while (1)
			{
				bChar = *(Text+i+dwSpcPos++);
				if (bChar==' ' || bChar==0x0A || bChar==0) break;
			}
			bChar = ' ';

			/* Humm, if this word is longer than the buffer don't move it  */
			/* otherwise check if it is at the end and create a return.    */
			if (dwSpcPos<GlobWin[dwWin].dwBufferSizeX && (dwPosBx+dwSpcPos)>GlobWin[dwWin].dwBufferSizeX)
			{
				*(GlobWin[dwWin].pTextBuffer + GlobWin[dwWin].dwCursorPos++) = 0;

				dwPosBx = 0;
				dwPosBy++;

				GlobWin[dwWin].dwCursorPos = dwPosBy * GlobWin[dwWin].dwBufferSizeX;

				continue;
			}
		}


		/* End of line */
		if (dwPosBx == (GlobWin[dwWin].dwBufferSizeX-1))
		{
			*(GlobWin[dwWin].pTextBuffer + GlobWin[dwWin].dwCursorPos++) = 0;
			dwPosBx = 0;
			dwPosBy++;
		}

		/* Vertical Scroll */
		if (dwPosBy >= GlobWin[dwWin].dwBufferSizeY)
		{
		
			memcpy (GlobWin[dwWin].pTextBuffer, 
					GlobWin[dwWin].pTextBuffer+GlobWin[dwWin].dwBufferSizeX,
					(GlobWin[dwWin].dwBufferSizeX-1)*GlobWin[dwWin].dwBufferSizeY);
			
			GlobWin[dwWin].dwCursorPos -= GlobWin[dwWin].dwBufferSizeX;
		
			dwPosBx = 0;
			dwPosBy--;
		}

		/* Return */
		if (bChar == 0x0A) 
		{
			*(GlobWin[dwWin].pTextBuffer + GlobWin[dwWin].dwCursorPos++) = 0;

			dwPosBx = 0;
			dwPosBy++;

			GlobWin[dwWin].dwCursorPos = dwPosBy * GlobWin[dwWin].dwBufferSizeX;

			continue;
		}

		/* Storing our character */
		if (GlobWin[dwWin].dwCursorPos<dwBufferSize)
		{
			*(GlobWin[dwWin].pTextBuffer + GlobWin[dwWin].dwCursorPos++) = bChar;
		}

		dwPosBx++;


	  }

	  free (Text);

	  /* Automatic adjust of the window size */
	  if (GlobWin[dwWin].dwFlags & Print3D_ADJUST_SIZE) 
	  {
		  D3DTPrint3DAdjustWindowSize(dwWin, 0);
	  }

	  return;
}
/*----------------------------------------------------------------------
 *  Function Name	: D3DTPrint3D
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		: This is our old friend D3DTABCTablePrint3D!!
 *----------------------------------------------------------------------*/
void D3DTPrint3D(float XPos, float YPos, float fScale,  int Colour, const TCHAR *Format, ...)
{
TCHAR		Text[MAX_LETTERS+1];
va_list		args;
		

      /* Reading the arguments to create our Text string */
	  va_start(args,Format);
	  wvsprintf(Text, Format,args);
	  va_end(args);

	  /* Read and write render states */
	  RenderStates(0);

      XPos *= 640.0f/100.0f;
	  YPos *= 480.0f/100.0f;

	  LocalPrint3D(0, 0.0f, XPos, YPos, fScale, Colour, Text);
									
	  /* Restore render states	*/
	  RenderStates(1);

}
/*----------------------------------------------------------------------
 *  Function Name	: D3DTPrint3DAdjustWindowSize
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
void D3DTPrint3DAdjustWindowSize(DWORD dwWin, DWORD dwMode)
{
register unsigned i = 1;
DWORD dwPointer = 0;
float fMax = 0.0f, fLength;

		if (dwMode==1 || dwMode==0)
		{
			/* Title horizontal Size */
			if(GlobWin[dwWin].dwFlags & Print3D_WIN_TITLE)
			{
				fMax = GetLength (GlobWin[dwWin].fTitleFontSize, GlobWin[dwWin].bTitleTextL);

				if (GlobWin[dwWin].bTitleTextR)
				{
					fMax += GetLength (GlobWin[dwWin].fTitleFontSize, GlobWin[dwWin].bTitleTextR) + 12.0f;
				}
			}

			/* Body horizontal size (line by line) */
			for (i=0; i<GlobWin[dwWin].dwBufferSizeY; i++)
			{
				fLength = GetLength (GlobWin[dwWin].fWinFontSize, (GlobWin[dwWin].pTextBuffer + dwPointer));

				if (fLength > fMax) fMax = fLength;

				dwPointer += GlobWin[dwWin].dwBufferSizeX;
			}
		
			GlobWin[dwWin].fWinSize[0] = fMax - 2.0f + 16.0f;

		}


		/* Vertical Size */
		if ((dwMode==0 || dwMode==2))
		{
			if (GlobWin[dwWin].dwCursorPos==0 || GlobWin[dwWin].dwBufferSizeY < 2) i = 0;

			else
			{
				/* Looking for the last line */
				for (i=GlobWin[dwWin].dwBufferSizeY-1; i>=0 ; i--)
				{
					if (*(GlobWin[dwWin].pTextBuffer + (unsigned) (GlobWin[dwWin].dwBufferSizeX*i))) break;
				}
			}

			if (GlobWin[dwWin].fWinFontSize>0)
				GlobWin[dwWin].fWinSize[1] = (float)(i+1) * LINES_SPACING * GlobWin[dwWin].fWinFontSize + 16.0f;
			else
				GlobWin[dwWin].fWinSize[1] = ((float)(i+1) * 12.0f) + 16.0f;


		}


}
/*----------------------------------------------------------------------
 *  Function Name	: D3DTPrint3DCreateDefaultWindow
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
DWORD D3DTPrint3DCreateDefaultWindow (float fPosX, float fPosY, int nXSize_LettersPerLine, TCHAR *sTitle, TCHAR *sBody)
{
DWORD dwActualWin;
DWORD dwFlags = PRINT3D_ADJUST_SIZE_ALWAYS;
DWORD dwBodyTextColor, dwBodyBackgroundColor;

    if(sBody == NULL && sTitle == NULL) return -1;

	if (sTitle==NULL)
	{
		dwBodyTextColor			= (DWORD)0xFFFFFF30;
		dwBodyBackgroundColor	= (DWORD)0x802020B0;
	}
	else
	{
		dwBodyTextColor			= (DWORD)0xFFFFFFFF;
		dwBodyBackgroundColor	= (DWORD)0x802030FF;
	}
	
	if(sBody  == NULL) dwFlags |= PRINT3D_DEACTIVATE_WIN;
	if(sTitle == NULL) dwFlags |= PRINT3D_DEACTIVATE_TITLE ;

	dwActualWin = D3DTPrint3DCreateWindow (nXSize_LettersPerLine, (sTitle==NULL) ? 1:50);

	D3DTPrint3DSetWindow (dwActualWin, dwBodyBackgroundColor, dwBodyTextColor, 0.5f, fPosX, fPosY, 20.0f, 20.0f);
	
	if (sTitle != NULL)
	{
		D3DTPrint3DSetTitle	(dwActualWin, (DWORD)0x802020B0, 0.6f, 
								(DWORD)0xFFFFFF30, sTitle, (DWORD)0xFFFFFF30, L"\x1\x2");
	}

	if (sBody != NULL)
	{
		D3DTPrint3DWindowOutput		(dwActualWin, sBody);
	}

	D3DTPrint3DSetWindowFlags	(dwActualWin, dwFlags);

	
	
	return dwActualWin;
}
/*************************************************************
*					 INTERNAL FUNCTIONS						 *
**************************************************************/

/*----------------------------------------------------------------------
 *  Function Name   : DrawWindow	                                    
 *  Inputs          :                       							 
 *  Returns         : TRUE if succesful, FALSE otherwise.               
 *  Globals Used    :                                                   
 *  Description     : Draw a generic rectangle (with or without border).	                                    
 *----------------------------------------------------------------------*/
HRESULT DrawWindow (DWORD dwWin, DWORD Color, float fZPos, float fPosX, float fPosY, float fSizeX, float fSizeY)
{
register i;
D3DTLVERTEX	vBox[16];
BOOL bIsOp = FALSE;
float fU[] = { 0.0f, 0.0f, 6.0f, 6.0f, 10.0f,10.0f, 16.0f,16.0f,10.0f,16.0f,10.0f,16.0f,6.0f,6.0f,0.0f,0.0f};
float fV[] = { 0.0f, 6.0f, 0.0f, 6.0f, 0.0f, 6.0f, 0.0f, 6.0f, 10.0f, 10.0f, 16.0f,16.0f, 16.0f, 10.0f, 16.0f, 10.0f};
WORD pFaces[] = { 0,2,1, 2,3,1, 2,4,3, 4,5,3, 4,6,5, 6,7,5, 5,7,8, 7,9,8, 8,9,10, 9,11,10, 8,10,12, 8,12,13, 
				 13,12,14, 13,14,15, 13,15,3, 1,3,15, 3,5,13, 5,8,13};

	/* No textures! so... no window */
	if (!Glob.bInitOK) return FALSE;

	/* Full translucent, no window */
    if (!(Color & 0xFF000000)) return FALSE;

	/* Removing the border */
	fSizeX -= 16.0f ;
	fSizeY -= 16.0f ;

    for (i=0; i<16; i++)
	{
		vBox[i].sz = 0.91f;//fZPos;
		vBox[i].rhw = 1.0f - fZPos;
		vBox[i].color = Color;
		vBox[i].specular = 0x00000000;
		vBox[i].tu = fU[i]/16.0f;
		vBox[i].tv = 1.0f - fV[i]/16.0f;

	}

	vBox[0].sx = (fPosX + fU[0]) * Glob.fScreenScale[0];
	vBox[0].sy = (fPosY + fV[0]) * Glob.fScreenScale[1];

	vBox[1].sx = (fPosX + fU[1]) * Glob.fScreenScale[0];
	vBox[1].sy = (fPosY + fV[1]) * Glob.fScreenScale[1];

	vBox[2].sx = (fPosX + fU[2]) * Glob.fScreenScale[0];
	vBox[2].sy = (fPosY + fV[2]) * Glob.fScreenScale[1];

	vBox[3].sx = (fPosX + fU[3]) * Glob.fScreenScale[0];
	vBox[3].sy = (fPosY + fV[3]) * Glob.fScreenScale[1];

	vBox[4].sx = (fPosX + fU[4] + fSizeX) * Glob.fScreenScale[0];
	vBox[4].sy = (fPosY + fV[4]) * Glob.fScreenScale[1];

	vBox[5].sx = (fPosX + fU[5] + fSizeX) * Glob.fScreenScale[0];
	vBox[5].sy = (fPosY + fV[5]) * Glob.fScreenScale[1];

	vBox[6].sx = (fPosX + fU[6] + fSizeX) * Glob.fScreenScale[0];
	vBox[6].sy = (fPosY + fV[6]) * Glob.fScreenScale[1];

	vBox[7].sx = (fPosX + fU[7] + fSizeX) * Glob.fScreenScale[0];
	vBox[7].sy = (fPosY + fV[7]) * Glob.fScreenScale[1];

	vBox[8].sx = (fPosX + fU[8] + fSizeX) * Glob.fScreenScale[0];
	vBox[8].sy = (fPosY + fV[8] + fSizeY) * Glob.fScreenScale[1];

	vBox[9].sx = (fPosX + fU[9] + fSizeX) * Glob.fScreenScale[0];
	vBox[9].sy = (fPosY + fV[9] + fSizeY) * Glob.fScreenScale[1];

	vBox[10].sx = (fPosX + fU[10] + fSizeX) * Glob.fScreenScale[0];
	vBox[10].sy = (fPosY + fV[10] + fSizeY) * Glob.fScreenScale[1];

	vBox[11].sx = (fPosX + fU[11] + fSizeX) * Glob.fScreenScale[0];
	vBox[11].sy = (fPosY + fV[11] + fSizeY) * Glob.fScreenScale[1];

	vBox[12].sx = (fPosX + fU[12]) * Glob.fScreenScale[0];
	vBox[12].sy = (fPosY + fV[12] + fSizeY) * Glob.fScreenScale[1];

	vBox[13].sx = (fPosX + fU[13]) * Glob.fScreenScale[0];
	vBox[13].sy = (fPosY + fV[13] + fSizeY) * Glob.fScreenScale[1];

	vBox[14].sx = (fPosX + fU[14]) * Glob.fScreenScale[0];
	vBox[14].sy = (fPosY + fV[14] + fSizeY) * Glob.fScreenScale[1];

	vBox[15].sx = (fPosX + fU[15]) * Glob.fScreenScale[0];
	vBox[15].sy = (fPosY + fV[15] + fSizeY) * Glob.fScreenScale[1];

	/* Set render states*/
    bIsOp = ((GlobWin[dwWin].dwFlags & Print3D_FULL_OPAQUE)) ? TRUE : FALSE;
						

	Glob.lpDev3->lpVtbl->SetRenderState(Glob.lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, !bIsOp );

	if(GlobWin[dwWin].dwFlags & Print3D_NO_BORDER)
	{
		Glob.lpDev3->lpVtbl->SetTexture(Glob.lpDev3, 0, Glob.lpTexture[2 + (bIsOp*2)]);
	}
	else
	{
		Glob.lpDev3->lpVtbl->SetTexture(Glob.lpDev3, 0, Glob.lpTexture[1 + (bIsOp*2)]);
	}

    Glob.lpDev3->lpVtbl->DrawIndexedPrimitive(Glob.lpDev3, D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, 
										  vBox, 16,  pFaces, 18*3, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);


	/* Restore render states */
	Glob.lpDev3->lpVtbl->SetRenderState(Glob.lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);


	return TRUE;
}
/*----------------------------------------------------------------------
 *  Function Name   : UpLoad4444	                                    
 *  Inputs          :                       							 
 *  Returns         : TRUE if succesful, FALSE otherwise.               
 *  Globals Used    :                                                   
 *  Description     : Reads texture data from *.dat and loads it in     
 *					  video memory.	                                    
 *----------------------------------------------------------------------*/
static BOOL UpLoad4444(DWORD dwTexID, unsigned char *pSource, 	DWORD nSize, DWORD nMode)
{
HRESULT					hres;
LPDIRECTDRAWSURFACE4    lpDDSTextureFontSurface;
LPDIRECT3DTEXTURE2		lpSrcTexture=NULL;
DDSURFACEDESC2			ddsd;
DDPIXELFORMAT			PixelFormat;
DWORD					x=256, y=256;
DWORD					r=0, g=0, b=0, a=0, m=0;
DWORD					dwMemoryUsedByTexture=0;
unsigned 			    A, B;
unsigned				ContBMP=0;
unsigned short			*lp16b;
int						i, j;
static BOOL				bInit = TRUE;
	
	if (bInit)
	{
		for (i=0; i<5; i++) Glob.lpDDTextureSurface[i] = NULL;
		bInit = FALSE;
	}
    
	/* If the surface has been created already don't do it again, just load it on video memory*/
	if (Glob.lpDDTextureSurface[dwTexID] == NULL)
	{
		/* Only square textures */
		x = nSize;
		y = nSize;

		
		/* Initialise PixelFormat structure */
		/* 4444 only */
		memset(&PixelFormat, 0, sizeof(DDPIXELFORMAT));
		PixelFormat.dwSize				= sizeof(DDPIXELFORMAT);
		PixelFormat.dwFlags				= DDPF_RGB | DDPF_ALPHAPIXELS;
		PixelFormat.dwRGBBitCount		= 16;
		PixelFormat.dwRGBAlphaBitMask	= 0x0000F000;
		PixelFormat.dwRBitMask			= 0x00000F00;
		PixelFormat.dwGBitMask			= 0x000000F0;
		PixelFormat.dwBBitMask			= 0x0000000F;
	
		/* Create texture surface */
		memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
		ddsd.dwSize			=	sizeof(DDSURFACEDESC2);
		ddsd.dwFlags		=	DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
		ddsd.ddsCaps.dwCaps	=	DDSCAPS_TEXTURE | DDSCAPS_SYSTEMMEMORY;
		ddsd.ddsCaps.dwCaps2=	0;
		ddsd.dwWidth		=	x;
		ddsd.dwHeight		=	y;
		ddsd.ddpfPixelFormat=	PixelFormat;
		hres=Glob.lpDD4->lpVtbl->CreateSurface(Glob.lpDD4, &ddsd, &Glob.lpDDTextureSurface[dwTexID], NULL);
		if (hres!=DD_OK) 
		{
			WCE_DEBUG(L"UpLoad4444 : Unable to create surface\n");
			return FALSE;
		}

		/* Initialise DDSURFACEDESC2 */
		memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
		ddsd.dwSize=sizeof(DDSURFACEDESC2);
		ddsd.dwFlags=DDLOCK_SURFACEMEMORYPTR;
		/* Lock texture surface to fill it */
		hres=Glob.lpDDTextureSurface[dwTexID]->lpVtbl->Lock(Glob.lpDDTextureSurface[dwTexID], NULL, &ddsd, 0, NULL); 
		if (hres!=DD_OK)
		{
			WCE_DEBUG(L"UpLoad4444 : Lock failed\n");
			RELEASE(Glob.lpDDTextureSurface[dwTexID]);
			return FALSE;
		}

		/* Create ABC Texture from *.dat file */
		for (i=y; i!=0; i--)
		{
			/* Calculate pointers corresponding to texture format */
			lp16b = (unsigned short *)(((char *)ddsd.lpSurface) + x*i*2-2);
	
			switch (nMode)
			{

			/* Texture from TexTool */
			case 0: 
				ContBMP = (i*nSize) * 2 - 1 + 16; /* Header of 16 */
				for (j=x; j!=0; j--) 
				{ 
					A = ((unsigned) *(pSource+ContBMP--) ^ 0x000000F0) ;
					B = ((unsigned) *(pSource+ContBMP--) & 0x000000FF);
					*(lp16b--) = (WORD) ((A<<8) | B);
				}
				break;

			/* Font (only alpha)*/
			case 1:	
				ContBMP = (i*nSize + nSize-1);
				for (j=x; j!=0; j--)
				{ 
					A = (unsigned) *(pSource+ContBMP--);
					*(lp16b--) = (WORD) ((A<<8) | 0x00000FFF);
				}
				break;
			}
		}

		/* Unlock texture surface because we're done filling it */
		hres=Glob.lpDDTextureSurface[dwTexID]->lpVtbl->Unlock(Glob.lpDDTextureSurface[dwTexID], NULL);
		if (hres!=DD_OK) return FALSE;
	}
    
	/* QueryPrint3D for a Direct3DTexture2 Print3D */
	hres=Glob.lpDDTextureSurface[dwTexID]->lpVtbl->QueryInterface(Glob.lpDDTextureSurface[dwTexID], &IID_IDirect3DTexture2,(LPVOID*)&lpSrcTexture);
	if (hres!=DD_OK) 
	{
		WCE_DEBUG(L"UpLoad4444 : QueryInterface failed\n");
		RELEASE(Glob.lpDDTextureSurface[dwTexID]);
		return FALSE;
	}

	/* Create texture surface */
	memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
    ddsd.dwSize=sizeof(DDSURFACEDESC2);
    ddsd.dwFlags=DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PIXELFORMAT;
	ddsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE | DDSCAPS_ALLOCONLOAD;
	ddsd.ddsCaps.dwCaps2 = 0;
    ddsd.dwWidth=x;
	ddsd.dwHeight=y;
    ddsd.ddpfPixelFormat=PixelFormat;
	hres=Glob.lpDD4->lpVtbl->CreateSurface(Glob.lpDD4, &ddsd, &lpDDSTextureFontSurface, NULL);
	if (hres!=DD_OK) 
	{
		WCE_DEBUG(L"UpLoad4444 : CreateSurface failed\n");
		RELEASE(lpSrcTexture);
		RELEASE(Glob.lpDDTextureSurface[dwTexID]);
		return FALSE;
	}

	/* QueryPrint3D for a Direct3DTexture2 Print3D */
	hres=lpDDSTextureFontSurface->lpVtbl->QueryInterface(lpDDSTextureFontSurface, &IID_IDirect3DTexture2,
															 (LPVOID*)&Glob.lpTexture[dwTexID]);
    if (hres!=DD_OK) 
	{
		WCE_DEBUG(L"UpLoad4444 : QueryInterface failed\n");
		RELEASE(lpDDSTextureFontSurface);
		RELEASE(lpSrcTexture);
		RELEASE(Glob.lpDDTextureSurface[dwTexID]);
		return FALSE;
	}
	
	/* Load texture into memory */
	hres=Glob.lpTexture[dwTexID]->lpVtbl->Load(Glob.lpTexture[dwTexID], lpSrcTexture);
	if (hres!=DD_OK) 
	{
		WCE_DEBUG(L"UpLoad4444 : Load failed\n");
		RELEASE(Glob.lpTexture[dwTexID]);
		RELEASE(lpDDSTextureFontSurface);
		RELEASE(lpSrcTexture);
		RELEASE(Glob.lpDDTextureSurface[dwTexID]);
		Glob.lpTexture[dwTexID] = NULL;
		return FALSE;
	}

	/* Release surfaces and memory */
	RELEASE(lpSrcTexture);
	RELEASE(lpDDSTextureFontSurface);

	/* Return status : OK */
	return TRUE;
}
/*----------------------------------------------------------------------
 *  Function Name   : D3DTPrint3DPrint3D                                
 *  Inputs          : PosX PosY Size Text                                
 *  Outputs         :                                                   
 *  Returns         :                                                   
 *  Globals Used    :			                                        
 *  Description     : Displays text.                                    
 *----------------------------------------------------------------------*/
void LocalPrint3D(DWORD dwWin, float fZPos, float XPos, float YPos, float fScale, 
						  int Colour, const TCHAR *Text)
{
unsigned	i=0, Cont=0, VertexCount=0;
unsigned	Val;
float		XSize = 0.0f, XFixBug,	YSize, TempSize;
float		UPos,	VPos;
float		USize,	VSize;
int			StripL[] = {2};
float		fWinClipX[2],fWinClipY[2];
float		fScaleX, fScaleY, fPreXPos;


		/* God, no textures! */
		if (!Glob.bInitOK) return;

		if (fScale>0)
		{
			fScaleX = Glob.fScreenScale[0] * fScale * 255.0f;
			fScaleY = Glob.fScreenScale[1] * fScale * 28.0f;
		}
		else
		{
			fScaleX = Glob.fScreenScale[0] * 255.0f;
			fScaleY = Glob.fScreenScale[1] * 12.0f;
		}


		XPos *= Glob.fScreenScale[0];
		YPos *= Glob.fScreenScale[1];

		fPreXPos = XPos;
		
		if (dwWin<0 || dwWin >MAX_WINDOWS) return;
		if (!(GlobWin[dwWin].dwFlags & Print3D_WIN_EXIST) && dwWin) return;

		/*
		 * Calculating our margins
		 */
		if (dwWin)
		{
			fWinClipX[0] = (GlobWin[dwWin].fWinPos[0] + 6.0f) * Glob.fScreenScale[0];
			fWinClipX[1] = (GlobWin[dwWin].fWinPos[0] + GlobWin[dwWin].fWinSize[0] - 6.0f) * Glob.fScreenScale[0];

			fWinClipY[0] = (GlobWin[dwWin].fWinPos[1] + 6.0f) * Glob.fScreenScale[1];
			fWinClipY[1] = (GlobWin[dwWin].fWinPos[1] + GlobWin[dwWin].fWinSize[1]  + 9.0f) * Glob.fScreenScale[1];

			if(GlobWin[dwWin].dwFlags & Print3D_WIN_TITLE)
			{
				if (GlobWin[dwWin].fTitleFontSize>0)
				{
					fWinClipY[0] +=  GlobWin[dwWin].fTitleFontSize * 25.0f  * Glob.fScreenScale[1];
					fWinClipY[1] +=  GlobWin[dwWin].fTitleFontSize * 25.0f *  Glob.fScreenScale[1];
				}
				else
				{
					fWinClipY[0] +=  10.0f * Glob.fScreenScale[1];
					fWinClipY[1] +=  8.0f  * Glob.fScreenScale[1];
				}
			}
		}
	
      while (TRUE)
	  {
	   Val = (int)*(Text+i++);

	   /* End of the string */
	   if (Val==0 || i>MAX_LETTERS) break;

	   /* It is SPACE so don't draw and carry on... */
	   if (Val==' ') 
	   {
		   if (fScale>0)	XPos += 10.0f/255.0f * fScaleX; 
		   else				XPos += 5.0f * Glob.fScreenScale[0]; 
		   continue;
	   }

	   /* It is RETURN so jump a line */
	   if (Val==0x0A) 
	   {
		   XPos = fPreXPos - XSize; 
		   YPos += (YSize * 1.1f); 
		   continue;
	   }

	   /* If fScale is negative then select the small set of letters (System) */
	   if (fScale < 0.0f)
	   {  
		    XPos    += XSize;
			UPos    =  D3DTPrint3DU_System[Val];
			VPos    =  D3DTPrint3DV_System[Val] - 0.0001f; /* Some cards need this little bit */
			YSize   =  fScaleY;
			XSize   =  D3DTPrint3DSize_System[Val] * fScaleX;
			USize	=  D3DTPrint3DSize_System[Val];
			VSize	=  12.0f/255.0f;
	  }
	   else /* Big set of letters (Bold) */
	   {
		    XPos    += XSize;
			UPos    =  D3DTPrint3DU_Bold[Val];
			VPos    =  D3DTPrint3DV_Bold[Val] - 1.0f/256.0f;
			YSize   =  fScaleY;
			XSize   =  D3DTPrint3DSize_Bold[Val]*fScaleX;
			USize	=  D3DTPrint3DSize_Bold[Val];
			VSize	=  28.0f/255.0f;	
	   }

	   /*
	    * CLIPPING
		*/
	   XFixBug = XSize;

	   if (dwWin) /* for dwWin==0 (screen) no clipping */
	   {
			/* Outside */
			if (XPos>fWinClipX[1]  ||  (YPos)>fWinClipY[1])
			{
				   continue;
			}

			/* Clip X */
			if (XPos<fWinClipX[1] && XPos+XSize > fWinClipX[1])
			{
				TempSize = XSize;

				XSize = fWinClipX[1] - XPos;

				if (fScale < 0.0f)
					USize	=  D3DTPrint3DSize_System[Val] * (XSize/TempSize);
				else
					USize	=  D3DTPrint3DSize_Bold[Val] * (XSize/TempSize);
			}

			/*
			 * Clip Y
			 */
			if (YPos<fWinClipY[1] && YPos+YSize > fWinClipY[1])
			{
				TempSize = YSize;
				YSize = fWinClipY[1] - YPos;

				if (fScale < 0.0f) 	VSize	=  (YSize/TempSize)*12.0f/255.0f;
				else
					VSize	=  (YSize/TempSize)*28.0f/255.0f;
			}
			
	   }
	   
	   
	   /* Filling vertex data */

	   (Glob.pVerticesFont+VertexCount+0)->sx	= XPos;
	   (Glob.pVerticesFont+VertexCount+0)->sy	= YPos;
	   (Glob.pVerticesFont+VertexCount+0)->sz	= fZPos;
	   (Glob.pVerticesFont+VertexCount+0)->rhw	= 1.0f - fZPos;
	   (Glob.pVerticesFont+VertexCount+0)->tu	= UPos;
	   (Glob.pVerticesFont+VertexCount+0)->tv	= VPos;

	   (Glob.pVerticesFont+VertexCount+1)->sx	= XPos+XSize;
	   (Glob.pVerticesFont+VertexCount+1)->sy	= YPos;
	   (Glob.pVerticesFont+VertexCount+1)->sz	= fZPos;
	   (Glob.pVerticesFont+VertexCount+1)->rhw	= 1.0f - fZPos;
	   (Glob.pVerticesFont+VertexCount+1)->tu	= UPos+USize;
	   (Glob.pVerticesFont+VertexCount+1)->tv	= VPos;
	  
	   (Glob.pVerticesFont+VertexCount+2)->sx	= XPos;
	   (Glob.pVerticesFont+VertexCount+2)->sy	= YPos+YSize;
	   (Glob.pVerticesFont+VertexCount+2)->sz	= fZPos;
	   (Glob.pVerticesFont+VertexCount+2)->rhw	= 1.0f - fZPos;
	   (Glob.pVerticesFont+VertexCount+2)->tu	= UPos;
	   (Glob.pVerticesFont+VertexCount+2)->tv	= VPos-VSize;

	   (Glob.pVerticesFont+VertexCount+3)->sx	= XPos+XSize;
	   (Glob.pVerticesFont+VertexCount+3)->sy	= YPos+YSize;
	   (Glob.pVerticesFont+VertexCount+3)->sz	= fZPos;
	   (Glob.pVerticesFont+VertexCount+3)->rhw	= 1.0f - fZPos;
	   (Glob.pVerticesFont+VertexCount+3)->tu	= UPos+USize;
	   (Glob.pVerticesFont+VertexCount+3)->tv	= VPos-VSize;

	   (Glob.pVerticesFont+VertexCount+0)->color	= Colour;
	   (Glob.pVerticesFont+VertexCount+1)->color	= Colour;
	   (Glob.pVerticesFont+VertexCount+2)->color	= Colour;
	   (Glob.pVerticesFont+VertexCount+3)->color	= Colour;

	   (Glob.pVerticesFont+VertexCount+0)->specular	= 0x00000000;
	   (Glob.pVerticesFont+VertexCount+1)->specular	= 0x00000000;
	   (Glob.pVerticesFont+VertexCount+2)->specular	= 0x00000000;
	   (Glob.pVerticesFont+VertexCount+3)->specular	= 0x00000000;

	   VertexCount+=4;

	   XSize = XFixBug;

	   if (Val >='0' && Val <='9')
		{
		   if (fScale < 0.0f)	XSize = D3DTPrint3DSize_System['0'] * fScaleX;
		   else					XSize = D3DTPrint3DSize_Bold['0'] * fScaleX;

		}

	  }

	   /* Set Font Texture */
	  //Glob.lpDev3->lpVtbl->SetRenderState(Glob.lpDev3, D3DRENDERSTATE_TEXTUREHANDLE, Glob.hTexture[0]);
	  Glob.lpDev3->lpVtbl->SetTexture(Glob.lpDev3, 0, Glob.lpTexture[0]);

	  /* Call DrawIndexedPrimitive */
	  if (VertexCount)
	  {
	  Glob.lpDev3->lpVtbl->DrawIndexedPrimitive(Glob.lpDev3, D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, 
												 Glob.pVerticesFont, VertexCount, 
												 Glob.pFacesFont, 3*(VertexCount>>1),
												 D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);
	  }

} 
/*----------------------------------------------------------------------
 *  Function Name   : D3DTPrint3DPrint3D                                
 *  Inputs          : PosX PosY Size Text                                
 *  Outputs         :                                                   
 *  Returns         :                                                   
 *  Globals Used    :			                                        
 *  Description     : Displays text.                                    
 *----------------------------------------------------------------------*/
float GetLength (float fFontSize, TCHAR *sString)
{
TCHAR Val;
float fScale, fSize;

		if (fFontSize>=0) /* Arial font */
		{
			fScale = fFontSize * 255.0f;
			fSize  = 0.0f;

			while (Val = *sString++)
			{
				if (Val==' ') {fSize += 10.0f * fFontSize; continue;}
				if (Val>='0' && Val<='9') Val = '0';
				fSize += D3DTPrint3DSize_Bold[Val] * fScale ;
			}
		}
		else /* System font */
		{
			fScale = 255.0f;
			fSize  = 0.0f;

			while (Val = *sString++)
			{
				if (Val==' ') {fSize += 5.0f; continue;}
				if (Val>='0' && Val<='9') Val = '0';
				fSize += D3DTPrint3DSize_System[Val]  * fScale;
			}
		}

		return (fSize);
}
/*----------------------------------------------------------------------
 *  Function Name	: RenderStates
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		: Stores, writes and restores Render States
 *----------------------------------------------------------------------*/
void RenderStates(int nAction)
{
static LPDIRECT3DTEXTURE2 TextureStage0; 
static unsigned	dwAlphaBlend, dwSrc, dwDest, dwSpecular, dwFog, dwZComp, dwZCompMode;
static unsigned	ColorOp0, ColorOp1, AlphaOp0, AlphaOp1, dwMagFilt, dwMinFilt;
static unsigned	ColorArg1, ColorArg2, AlphaArg1, AlphaArg2;
static unsigned dwRenderMagFilt, dwRenderMinFilt, dwShadeMode;

	switch (nAction)
	{
	case 0:
	  /* Get previous render states */
	  Glob.lpDev3->lpVtbl->GetTexture(Glob.lpDev3, 0, &TextureStage0);
	  if(TextureStage0) TextureStage0->lpVtbl->Release(TextureStage0); 

	  Glob.lpDev3->lpVtbl->GetTextureStageState	(Glob.lpDev3, 0, D3DTSS_COLOROP,		&ColorOp0);
	  Glob.lpDev3->lpVtbl->GetTextureStageState (Glob.lpDev3, 0, D3DTSS_ALPHAOP,		&AlphaOp0);
	  Glob.lpDev3->lpVtbl->GetTextureStageState	(Glob.lpDev3, 0, D3DTSS_COLORARG1,		&ColorArg1);
	  Glob.lpDev3->lpVtbl->GetTextureStageState	(Glob.lpDev3, 0, D3DTSS_COLORARG2,		&ColorArg2);
	  Glob.lpDev3->lpVtbl->GetTextureStageState (Glob.lpDev3, 0, D3DTSS_ALPHAARG1,		&AlphaArg1);
	  Glob.lpDev3->lpVtbl->GetTextureStageState	(Glob.lpDev3, 0, D3DTSS_ALPHAARG2,		&AlphaArg2);

	  Glob.lpDev3->lpVtbl->GetTextureStageState	(Glob.lpDev3, 0, D3DTSS_MAGFILTER,		&dwMagFilt);
	  Glob.lpDev3->lpVtbl->GetTextureStageState	(Glob.lpDev3, 0, D3DTSS_MINFILTER,		&dwMinFilt);

	  Glob.lpDev3->lpVtbl->GetRenderState(Glob.lpDev3, D3DRENDERSTATE_TEXTUREMAG,		&dwRenderMagFilt);
	  Glob.lpDev3->lpVtbl->GetRenderState(Glob.lpDev3, D3DRENDERSTATE_TEXTUREMIN,		&dwRenderMinFilt);
	  Glob.lpDev3->lpVtbl->GetRenderState(Glob.lpDev3, D3DRENDERSTATE_FOGENABLE,		&dwFog);
	  Glob.lpDev3->lpVtbl->GetRenderState(Glob.lpDev3, D3DRENDERSTATE_ZENABLE,          &dwZComp);
	  Glob.lpDev3->lpVtbl->GetRenderState(Glob.lpDev3, D3DRENDERSTATE_ZFUNC,            &dwZCompMode);

	  Glob.lpDev3->lpVtbl->GetRenderState(Glob.lpDev3, D3DRENDERSTATE_SPECULARENABLE,	&dwSpecular);
	  Glob.lpDev3->lpVtbl->GetRenderState(Glob.lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, &dwAlphaBlend);
	  Glob.lpDev3->lpVtbl->GetRenderState(Glob.lpDev3, D3DRENDERSTATE_SRCBLEND,			&dwSrc);
      Glob.lpDev3->lpVtbl->GetRenderState(Glob.lpDev3, D3DRENDERSTATE_DESTBLEND,		&dwDest);
	  Glob.lpDev3->lpVtbl->GetRenderState(Glob.lpDev3, D3DRENDERSTATE_SHADEMODE,		&dwShadeMode);


	 /* Set render states and texture stage 0 states */
	  Glob.lpDev3->lpVtbl->SetRenderState(Glob.lpDev3, D3DRENDERSTATE_ZENABLE,			TRUE);
	  Glob.lpDev3->lpVtbl->SetRenderState(Glob.lpDev3, D3DRENDERSTATE_ZFUNC,			D3DCMP_ALWAYS);

	  Glob.lpDev3->lpVtbl->SetTextureStageState	(Glob.lpDev3, 0, D3DTSS_COLOROP,		D3DTOP_MODULATE );
	  Glob.lpDev3->lpVtbl->SetTextureStageState	(Glob.lpDev3, 0, D3DTSS_ALPHAOP,		D3DTOP_MODULATE );
      Glob.lpDev3->lpVtbl->SetTextureStageState	(Glob.lpDev3, 0, D3DTSS_COLORARG1,		D3DTA_TEXTURE );
	  Glob.lpDev3->lpVtbl->SetTextureStageState	(Glob.lpDev3, 0, D3DTSS_COLORARG2,		D3DTA_DIFFUSE ); 
	  Glob.lpDev3->lpVtbl->SetTextureStageState	(Glob.lpDev3, 0, D3DTSS_ALPHAARG2,		D3DTA_TEXTURE );
  	  Glob.lpDev3->lpVtbl->SetTextureStageState	(Glob.lpDev3, 0, D3DTSS_ALPHAARG2,		D3DTA_DIFFUSE );
	  Glob.lpDev3->lpVtbl->SetTextureStageState	(Glob.lpDev3, 0, D3DTSS_MINFILTER ,		D3DTFN_LINEAR);	
	  Glob.lpDev3->lpVtbl->SetTextureStageState (Glob.lpDev3, 0, D3DTSS_MAGFILTER ,		D3DTFG_LINEAR);

	  Glob.lpDev3->lpVtbl->SetRenderState(Glob.lpDev3, D3DRENDERSTATE_FOGENABLE,		FALSE);
	  Glob.lpDev3->lpVtbl->SetRenderState(Glob.lpDev3, D3DRENDERSTATE_SPECULARENABLE,	FALSE);
	  Glob.lpDev3->lpVtbl->SetRenderState(Glob.lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
	  Glob.lpDev3->lpVtbl->SetRenderState(Glob.lpDev3, D3DRENDERSTATE_SRCBLEND,			D3DBLEND_SRCALPHA );
      Glob.lpDev3->lpVtbl->SetRenderState(Glob.lpDev3, D3DRENDERSTATE_DESTBLEND,		D3DBLEND_INVSRCALPHA);
	  Glob.lpDev3->lpVtbl->SetRenderState(Glob.lpDev3, D3DRENDERSTATE_SHADEMODE,		D3DSHADE_GOURAUD);
	  break;

	case 1:
	  /* Restore render states */
	  Glob.lpDev3->lpVtbl->SetRenderState(Glob.lpDev3, D3DRENDERSTATE_TEXTUREMAG,       dwRenderMagFilt);
	  Glob.lpDev3->lpVtbl->SetRenderState(Glob.lpDev3, D3DRENDERSTATE_TEXTUREMIN,       dwRenderMinFilt);
	  Glob.lpDev3->lpVtbl->SetRenderState(Glob.lpDev3, D3DRENDERSTATE_ZENABLE,          dwZComp);
	  Glob.lpDev3->lpVtbl->SetRenderState(Glob.lpDev3, D3DRENDERSTATE_ZFUNC,            dwZCompMode);
	  Glob.lpDev3->lpVtbl->SetRenderState(Glob.lpDev3, D3DRENDERSTATE_FOGENABLE,		dwFog);
	  Glob.lpDev3->lpVtbl->SetRenderState(Glob.lpDev3, D3DRENDERSTATE_SPECULARENABLE,	dwSpecular);
	  Glob.lpDev3->lpVtbl->SetRenderState(Glob.lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, dwAlphaBlend);
	  Glob.lpDev3->lpVtbl->SetRenderState(Glob.lpDev3, D3DRENDERSTATE_SRCBLEND,			dwSrc);
      Glob.lpDev3->lpVtbl->SetRenderState(Glob.lpDev3, D3DRENDERSTATE_DESTBLEND,		dwDest);
	  Glob.lpDev3->lpVtbl->SetRenderState(Glob.lpDev3, D3DRENDERSTATE_SHADEMODE,		dwShadeMode);

	  Glob.lpDev3->lpVtbl->SetTexture(Glob.lpDev3, 0,  TextureStage0);
	  Glob.lpDev3->lpVtbl->SetTextureStageState	(Glob.lpDev3, 0, D3DTSS_COLOROP,		ColorOp0);
	  Glob.lpDev3->lpVtbl->SetTextureStageState	(Glob.lpDev3, 0, D3DTSS_ALPHAOP,		AlphaOp0);
	  Glob.lpDev3->lpVtbl->SetTextureStageState	(Glob.lpDev3, 0, D3DTSS_COLORARG1,		ColorArg1);
	  Glob.lpDev3->lpVtbl->SetTextureStageState	(Glob.lpDev3, 0, D3DTSS_COLORARG2,		ColorArg2);
	  Glob.lpDev3->lpVtbl->SetTextureStageState (Glob.lpDev3, 0, D3DTSS_ALPHAARG1,		AlphaArg1);
	  Glob.lpDev3->lpVtbl->SetTextureStageState	(Glob.lpDev3, 0, D3DTSS_ALPHAARG2,		AlphaArg2);
	  Glob.lpDev3->lpVtbl->SetTextureStageState	(Glob.lpDev3, 0, D3DTSS_MINFILTER ,		dwMinFilt);	
	  Glob.lpDev3->lpVtbl->SetTextureStageState (Glob.lpDev3, 0, D3DTSS_MAGFILTER ,		dwMagFilt);
	  break;

	}
}
