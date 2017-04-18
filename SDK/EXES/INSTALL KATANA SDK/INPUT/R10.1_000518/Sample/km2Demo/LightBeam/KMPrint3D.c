/*****************************************************************************
  Name : KMPrint3D.c		v1.0
  Date : JUne 1999

  * Description : 
  This file is part of the TOOLS library used
  with the SDK demos for PowerVR series 2 (Dreamcast).
  
  Description : Displays a text string using 3D polygons.
				Can be done in two ways: using a window defined by the user
				or writing straight on the screen.

 Copyright : 1999 by VideoLogic Limited. All rights reserved.
******************************************************************************/
#include "KMTools.h"


#include "KMPrint3D.dat"		/* Print3D texture data */

#define Align32Byte(adr)        ((((long)adr) + 0x1F) & 0xFFFFFFE0)

/* DEFINES */
#define MAX_LETTERS 5000
#define MAX_WINDOWS 50
#define LINE_SEPARATION 30.0f

#define Print3D_WIN_EXIST	1
#define Print3D_WIN_ACTIVE	2
#define Print3D_WIN_TITLE	4
#define Print3D_WIN_STATIC	8
#define Print3D_FULL_OPAQUE	16
#define Print3D_FULL_TRANS	32
#define Print3D_ADJUST_SIZE	64
#define Print3D_NO_BORDER	128


typedef struct {
	KMDWORD dwFlags;

	/* Text Buffer */
	 char  *pTextBuffer;
	KMDWORD  dwBufferSizeX;
	KMDWORD  dwBufferSizeY;
	KMDWORD  dwCursorPos;

	/* Title */
	float fTitleFontSize;
	float fTextRMinPos;
	KMDWORD dwTitleFontColorL;
	KMDWORD dwTitleFontColorR;
	KMDWORD dwTitleBaseColor; 
	 char  *bTitleTextL;
	 char  *bTitleTextR;

	/* Window */
	float fWinFontSize;
	KMDWORD dwWinFontColor;
	KMDWORD dwWinBaseColor;
	float fWinPos[2];
	float fWinSize[2];
	float fZPos;
	KMDWORD dwSort;

} KMPrint3DWIN;


/*  GLOBALS  */
KMSTRIPHEAD				StripContext[10];
KMSURFACEDESC			lpTexture[10];
KMDWORD					dwCreatedWins;
KMDWORD					dwTopMost;
int					    bInitOK;


KMPrint3DWIN	GlobWin[MAX_WINDOWS];

int bTexturesReleased = TRUE;

/* VertexBufferDesc is used for all the polys in the scene */
extern KMVERTEXBUFFDESC VertexBufferDesc;


/********************/
/* LOCAL PROTOTYPES */
/********************/
int		DrawWindow				(KMDWORD dwWin, KMDWORD Color, float fZPos, float fPosX, float fPosY, 
									float fSizeX, float fSizeY);
void	LocalPrint3D			(KMDWORD dwWin, float fZPos, float XPos, float YPos, float fScale, 
									int Colour, const  char *Text);
int		LoadPrint3DTextures		(KMSURFACEDESC *TexID,  char *pSource, KMDWORD nSize, KMDWORD nMode);
float	GetLength				(float fFontSize,  char *sString);
void 	SetVertexContext		(PKMSTRIPHEAD	StripHead, KMSURFACEDESC  *pTexSurfDesc, int bTranslucent);


/*----------------------------------------------------------------------
 *  Function Name   : KMPrint3DSetTextures							 
 *  Inputs          :                                                     
 *  Outputs         :                                                   
 *  Returns         : TRUE if OK.                                       
 *  Globals Used    :                                                   
 *  Description     : Initialization and texture upload.
 *  Note			: Must be called in InitView
 *----------------------------------------------------------------------*/
int KMPrint3DSetTextures(void)
{
register	i;
int		bStatus;
 int bIsFirstCall = TRUE;

		bInitOK = FALSE;

		
		dwTopMost = 255;

		if (bTexturesReleased==FALSE)
		{
			KMPrint3DReleaseTextures();
		}

		bTexturesReleased = FALSE; 
	   

		/*
		 * This is the window background texture
		 * Type 0 because the data comes in rectangular format.
		 */

		bStatus = LoadPrint3DTextures(&lpTexture[1], ( char *)WindowBackground, 16, 1);
		if (bStatus != KMSTATUS_SUCCESS) return FALSE;
		
		SetVertexContext(&StripContext[1], &lpTexture[1], TRUE);
		
		bStatus = LoadPrint3DTextures(&lpTexture[2], ( char *)WindowPlainBackground, 16, 1);
		if (bStatus != KMSTATUS_SUCCESS) return FALSE;
		
		SetVertexContext(&StripContext[2], &lpTexture[2], TRUE);
	
		bStatus = LoadPrint3DTextures(&lpTexture[3], ( char *)WindowBackgroundOp, 16, 2);
		if (bStatus != KMSTATUS_SUCCESS) return FALSE;
		
		SetVertexContext(&StripContext[3], &lpTexture[3], FALSE);

		bStatus = LoadPrint3DTextures(&lpTexture[4], ( char *)WindowPlainBackgroundOp, 16, 2);
		if (bStatus != KMSTATUS_SUCCESS) return FALSE;
		
		SetVertexContext(&StripContext[4], &lpTexture[4], FALSE);
				
		/*
		 * This is the texture with the fonts.
		 */
		bStatus = LoadPrint3DTextures(&lpTexture[0], ( char *)KMPrint3DABC_Pixels, 256, 0);
		if (bStatus != KMSTATUS_SUCCESS) return FALSE;	
		
		SetVertexContext(&(StripContext[0]), &(lpTexture[0]), TRUE);	
		
		/* Everything is OK */
		bInitOK = TRUE;

		/* Return OK */
		return TRUE;
}

/*----------------------------------------------------------------------*
 *  Function Name   : KMPrint3DReleaseTextures						 
 *  Inputs          :                                                     
 *  Outputs         :                                                   
 *  Returns         :                                                   
 *  Globals Used    : 								
 *  Description     : Deallocate the memory allocated in KMPrint3DSetTextures.  
 *----------------------------------------------------------------------*/
void KMPrint3DReleaseTextures(void)
{
register i;
  
    /* Release texture surfaces */
	for (i=0; i<5; i++)
	{
		kmFreeTexture(&lpTexture[i]);
	}


	bTexturesReleased = TRUE;
}
/*----------------------------------------------------------------------
 *  Function Name	: KMPrint3DDeleteAllWindows
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
void KMPrint3DDeleteAllWindows(void)
{
register  i;

	for (i=0; i<MAX_WINDOWS; i++)
	{
		KMPrint3DDeleteWindow (i);
	}

}
/*----------------------------------------------------------------------
 *  Function Name	: KMPrint3DDeleteWindow
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
void KMPrint3DDeleteWindow(KMDWORD dwWin)
{
	if(GlobWin[dwWin].dwFlags & Print3D_WIN_EXIST)
	{
		syFree(GlobWin[dwWin].pTextBuffer);
		syFree(GlobWin[dwWin].bTitleTextL);
		syFree(GlobWin[dwWin].bTitleTextR);
		GlobWin[dwWin].pTextBuffer = NULL;
		GlobWin[dwWin].bTitleTextL = NULL;
		GlobWin[dwWin].bTitleTextR = NULL;
	}

	GlobWin[dwWin].dwFlags = 0;
}
/*----------------------------------------------------------------------
 *  Function Name	: KMPrint3DClearWindowBuffer
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
void KMPrint3DClearWindowBuffer(KMDWORD dwWin)
{
register  i;

	if(GlobWin[dwWin].dwFlags & Print3D_WIN_EXIST)
	{
		for (i=0; i<GlobWin[dwWin].dwBufferSizeX*GlobWin[dwWin].dwBufferSizeY; i++) 
				*(GlobWin[dwWin].pTextBuffer+i) = 0;
	}

	GlobWin[dwWin].dwCursorPos	= 0;

}
/*----------------------------------------------------------------------
 *  Function Name	: KMPrint3DSetWindowBufferPointer
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
void KMPrint3DSetWindowBufferPointer(KMDWORD dwWin, KMDWORD dwXPos, KMDWORD dwYPos)
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
 *  Function Name	: KMPrint3DSetTopMostWindow
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		: 
 *----------------------------------------------------------------------*/
void KMPrint3DSetTopMostWindow(KMDWORD dwWin)
{
	dwTopMost = dwWin;
}
/*----------------------------------------------------------------------
 *  Function Name	: KMPrint3DSetWindowPos
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
void KMPrint3DSetWindowPos(KMDWORD dwWin, float fPosX, float fPosY)
{
	GlobWin[dwWin].fWinPos[0]		= fPosX * 640.0f/100.0f;
	GlobWin[dwWin].fWinPos[1]		= fPosY * 480.0f/100.0f;
}
/*----------------------------------------------------------------------
 *  Function Name	: KMPrint3DSetWindowSize
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
void KMPrint3DSetWindowSize(KMDWORD dwWin, float fSizeX, float fSizeY)
{
	GlobWin[dwWin].fWinSize[0]		= fSizeX * 640.0f/100.0f;
	GlobWin[dwWin].fWinSize[1]		= fSizeY * 480.0f/100.0f;
}

/*----------------------------------------------------------------------
 *  Function Name	: KMPrint3DDisplayAllWindows
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
void KMPrint3DDisplayAllWindows(void)
{
register  i;

	/* The TopMost window is displayed the last one */
	for (i=0; i<MAX_WINDOWS; i++)
	{
		if((GlobWin[i].dwFlags & Print3D_WIN_EXIST) && i!=dwTopMost)
		{
			KMPrint3DDisplayWindow (i);
		}

	}

	if (GlobWin[dwTopMost].dwFlags & Print3D_WIN_EXIST)
	{
		KMPrint3DDisplayWindow (dwTopMost);
	}
}
/*----------------------------------------------------------------------
 *  Function Name	: KMPrint3DSetWindowFlags
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
void KMPrint3DSetWindowFlags (KMDWORD dwWin, KMDWORD dwFlags)
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
		KMPrint3DAdjustWindowSize(dwWin, 0);
	}

	if (dwFlags & PRINT3D_NO_BORDER)	GlobWin[dwWin].dwFlags |= Print3D_NO_BORDER;
}
/*----------------------------------------------------------------------
 *  Function Name	: KMPrint3DSetWindow
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
void KMPrint3DSetWindow (KMDWORD dwWin, KMDWORD dwWinColor, KMDWORD dwFontColor, float fFontSize, 
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
 *  Function Name	: KMPrint3DSetTitle
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
void KMPrint3DSetTitle (KMDWORD dwWin, KMDWORD dwBackgroundColor, float fFontSize, 
							KMDWORD dwFontColorLeft,  char *sTitleLeft, 
							KMDWORD dwFontColorRight,  char *sTitleRight)
{

   	if (sTitleLeft) sprintf (GlobWin[dwWin].bTitleTextL, sTitleLeft);
	if (sTitleRight) sprintf (GlobWin[dwWin].bTitleTextR, sTitleRight);

	GlobWin[dwWin].fTitleFontSize	  = fFontSize;
	GlobWin[dwWin].dwTitleFontColorL  = dwFontColorLeft;
	GlobWin[dwWin].dwTitleFontColorR  = dwFontColorRight;
	GlobWin[dwWin].dwTitleBaseColor   = dwBackgroundColor; 
	GlobWin[dwWin].fTextRMinPos       = GetLength (GlobWin[dwWin].fTitleFontSize,
													GlobWin[dwWin].bTitleTextL)	+ 10.0f;

}
/*----------------------------------------------------------------------
 *  Function Name	: KMPrint3DCreateWindow
 *  Inputs			:
 *  Outputs			:
 *  Returns			: Handle to a window.
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
KMDWORD KMPrint3DCreateWindow (KMDWORD dwBufferSizeX, KMDWORD dwBufferSizeY)
{
register  i;
static KMDWORD dwCurrentWin = 1;

	/* If the window hasn't been deleted, I delete it */
	if (GlobWin[dwCurrentWin].dwFlags & Print3D_WIN_EXIST)
	{
		KMPrint3DDeleteWindow(dwCurrentWin);
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
		/* Well... start from the begining again */
		dwCurrentWin = 1;
		KMPrint3DDeleteWindow(dwCurrentWin);
		GlobWin[dwCurrentWin].dwFlags = 0;
		GlobWin[dwCurrentWin].pTextBuffer = NULL;
		
	}

	GlobWin[dwCurrentWin].dwFlags = Print3D_WIN_TITLE  | Print3D_WIN_EXIST | Print3D_WIN_ACTIVE;

	/* Text Buffer */
	GlobWin[dwCurrentWin].dwBufferSizeX = dwBufferSizeX + 1;
	GlobWin[dwCurrentWin].dwBufferSizeY = dwBufferSizeY;
	
	GlobWin[dwCurrentWin].pTextBuffer  = ( char *)syMalloc((dwBufferSizeX+2)*(dwBufferSizeY+2)*sizeof( char));
	GlobWin[dwCurrentWin].bTitleTextL  = ( char *)syMalloc(1000*sizeof( char));
	GlobWin[dwCurrentWin].bTitleTextR  = ( char *)syMalloc(1000*sizeof( char));
	

	if (GlobWin[dwCurrentWin].pTextBuffer == NULL | 
		GlobWin[dwCurrentWin].bTitleTextL == NULL |
		GlobWin[dwCurrentWin].bTitleTextR == NULL )
	{
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
	GlobWin[dwCurrentWin].fZPos		        = ((float)dwCurrentWin * 2.0f);
	GlobWin[dwCurrentWin].dwSort		    = 0;
	GlobWin[dwCurrentWin].dwCursorPos		= 0;

	dwCurrentWin++;

	/* Returning the handle */
	return (dwCurrentWin-1);
}
/*----------------------------------------------------------------------
 *  Function Name	: KMPrint3DDisplayWindow
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
void KMPrint3DDisplayWindow (KMDWORD dwWin)
{
KMDWORD		i;
float		fTitleSize = 0.0f, fRPos, fNewPos;
KMDWORD		dwPointer = 0;
	  
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
						GlobWin[dwWin].fZPos + 255.0f,
						GlobWin[dwWin].fWinPos[0],  
						GlobWin[dwWin].fWinPos[1], 
						GlobWin[dwWin].fWinSize[0], 
						fTitleSize);
			}

			/* Left text */
			LocalPrint3D(dwWin, GlobWin[dwWin].fZPos + 256.0f,
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
			
				LocalPrint3D(dwWin, GlobWin[dwWin].fZPos + 256.0f,
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
						GlobWin[dwWin].fZPos + 255.0f,
						GlobWin[dwWin].fWinPos[0],  
						(GlobWin[dwWin].fWinPos[1] + fTitleSize), 
						GlobWin[dwWin].fWinSize[0],
						GlobWin[dwWin].fWinSize[1]);
	
			}
	
			dwPointer = 0;

			/* Text, line by line */
			for (i=0; i<GlobWin[dwWin].dwBufferSizeY; i++)
			{

				fNewPos = fTitleSize + (float)(i * GlobWin[dwWin].fWinFontSize) * LINE_SEPARATION;

				if(GlobWin[dwWin].fWinFontSize < 0.0f) fNewPos = fTitleSize + (float)(i * 12.0f);
		
				LocalPrint3D(dwWin, GlobWin[dwWin].fZPos + 256.0f,
								(GlobWin[dwWin].fWinPos[0] + 6.0f), 
								(GlobWin[dwWin].fWinPos[1] + 6.0f + fNewPos), 
								GlobWin[dwWin].fWinFontSize, GlobWin[dwWin].dwWinFontColor, 
								(GlobWin[dwWin].pTextBuffer + dwPointer));

			dwPointer += GlobWin[dwWin].dwBufferSizeX;
			}
		}

	  return;
}
/*----------------------------------------------------------------------
 *  Function Name	: KMPrint3DWindowOutput
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
void KMPrint3DWindowOutput (KMDWORD dwWin, const  char *Format, ...)
{
KMDWORD		i;
KMDWORD		dwBufferSize, dwTotalLength = 0;
KMDWORD		dwPosBx, dwPosBy, dwSpcPos;
 char		Text[10000]; /* Temporal buffer for the string */
va_list		args;
 char		bChar;

	  if (!(GlobWin[dwWin].dwFlags & Print3D_WIN_EXIST)) return;

	  dwBufferSize = (GlobWin[dwWin].dwBufferSizeX+1) * (GlobWin[dwWin].dwBufferSizeY+1);
	  
	  if (dwBufferSize>10000) dwBufferSize=10000; /* Clamping to a 100x100 buffer */
	  
      /* Reading the arguments to create our Text string */
	  va_start(args,Format);
	  vsprintf(Text, Format, args);
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

	 
	  /* Automatic adjust of the window size */
	  if (GlobWin[dwWin].dwFlags & Print3D_ADJUST_SIZE) 
	  {
		  KMPrint3DAdjustWindowSize(dwWin, 0);
	  }

	  return;
}
/*----------------------------------------------------------------------
 *  Function Name	: KMPrint3D
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		: This is our old friend KMABCTablePrint3D!!
 *----------------------------------------------------------------------*/
void KMPrint3D(float XPos, float YPos, float fScale,  int Colour, const  char *Format, ...)
{
char		Text[MAX_LETTERS+1];
va_list		args;

	  /* Reading the arguments to create our Text string */
	  va_start(args,Format);
	  vsprintf(Text, Format, args);
	  va_end(args);

	
      XPos *= 640.0f/100.0f;
	  YPos *= 480.0f/100.0f;

	  LocalPrint3D(0, 300.0f, XPos, YPos, fScale, Colour, Text);


}
/*----------------------------------------------------------------------
 *  Function Name	: KMPrint3DAdjustWindowSize
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
void KMPrint3DAdjustWindowSize(KMDWORD dwWin, KMDWORD dwMode)
{
register  i;
KMDWORD dwPointer = 0;
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
            if( GlobWin[dwWin].dwCursorPos==0 || GlobWin[dwWin].dwBufferSizeY<2 ) i = 0;
			else
			{
				/* Looking for the last line */
				for (i=GlobWin[dwWin].dwBufferSizeY-1 ; i>=0 ; i--)
				{
					if (*(GlobWin[dwWin].pTextBuffer + GlobWin[dwWin].dwBufferSizeX*i)) break;
				}
			}			 

			if (GlobWin[dwWin].fWinFontSize>0)
				GlobWin[dwWin].fWinSize[1] = (float)(i+1) * LINE_SEPARATION * GlobWin[dwWin].fWinFontSize + 16.0f;
			else
				GlobWin[dwWin].fWinSize[1] = ((float)(i+1) * 12.0f) + 16.0f;


		}
}
/*----------------------------------------------------------------------
 *  Function Name	: KMPrint3DCreateDefaultWindow
 *  Inputs			:
 *  Outputs			:
 *  Returns			:
 *  Globals Used	:
 *  Description		:
 *----------------------------------------------------------------------*/
KMDWORD KMPrint3DCreateDefaultWindow (float fPosX, float fPosY, int nXSize_LettersPerLine,  char *sTitle,  char *sBody)
{
KMDWORD dwActualWin;
KMDWORD dwFlags = PRINT3D_ADJUST_SIZE_ALWAYS;
KMDWORD dwBodyTextColor, dwBodyBackgroundColor;

	if (sTitle==NULL)
	{
		dwBodyTextColor			= (KMDWORD)0xFFFFFF30;
		dwBodyBackgroundColor	= (KMDWORD)0x902020B0;
	}
	else
	{
		dwBodyTextColor			= (KMDWORD)0xFFFFFFFF;
		dwBodyBackgroundColor	= (KMDWORD)0x902030FF;
	}
	
	if(sBody  == NULL) dwFlags |= PRINT3D_DEACTIVATE_WIN;
	if(sTitle == NULL) dwFlags |= PRINT3D_DEACTIVATE_TITLE ;

	dwActualWin = KMPrint3DCreateWindow (nXSize_LettersPerLine, (sTitle==NULL) ? 1:50);
	
	if (sTitle != NULL)
	{
		KMPrint3DSetTitle	(dwActualWin, (KMDWORD)0x902020B0, 0.6f, 
								(KMDWORD)0xFFFFFF30, sTitle, (KMDWORD)0xFFFFFF30, "\x1\x2");
	}

	KMPrint3DSetWindow	(dwActualWin, dwBodyBackgroundColor, dwBodyTextColor, 0.5f, fPosX, fPosY, 20.0f, 20.0f);

	if (sBody != NULL)
	{
		KMPrint3DWindowOutput	(dwActualWin, sBody);
	}


	KMPrint3DSetWindowFlags	(dwActualWin, dwFlags);
	

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
int DrawWindow (KMDWORD dwWin, KMDWORD Color, float fZPos, float fPosX, float fPosY, float fSizeX, float fSizeY)
{
int i,j;
KMVERTEX_03	vBox[16];
int bIsOp = FALSE;
float fU[] = { 0.0f, 0.0f, 6.0f, 6.0f, 10.0f,10.0f, 16.0f,16.0f, 10.0f, 16.0f, 10.0f, 16.0f,  6.0f, 6.0f,  0.0f,  0.0f};
float fV[] = { 0.0f, 6.0f, 0.0f, 6.0f, 0.0f, 6.0f,  0.0f, 6.0f,  10.0f, 10.0f, 16.0f, 16.0f, 16.0f, 10.0f, 16.0f, 10.0f};

unsigned nVertex, nVertCont = 0;
unsigned  pFacesData[] = { 0,1,2,3,  2,3,4,5,  4,5,6,7,   5,8,7,9,  8,10,9,11,  13,12,8,10, 
				 15,14,13,12,  1,15,3,13,  3,13,5,8};
				 
	if(!bInitOK) return; /* Hummm, something is wrong so do not draw */

	/* Full translucent, no window */
    if (!(Color & 0xFF000000)) return FALSE;
    
    /* Removing the border */
	fSizeX -= 16.0f ;
	fSizeY -= 16.0f ;

    for (i=0; i<16; i++)
	{
		vBox[i].u.fZ = fZPos;
		vBox[i].uBaseRGB.dwPacked = Color;
		vBox[i].uOffsetRGB.dwPacked = 0x00000000;
		vBox[i].fU = fU[i]/16.0f;
		vBox[i].fV = 1.0f - fV[i]/16.0f;

	}

	vBox[0].fX = (fPosX + fU[0]) ;
	vBox[0].fY = (fPosY + fV[0]) ;

	vBox[1].fX = (fPosX + fU[1]) ;
	vBox[1].fY = (fPosY + fV[1]) ;

	vBox[2].fX = (fPosX + fU[2]) ;
	vBox[2].fY = (fPosY + fV[2]) ;

	vBox[3].fX = (fPosX + fU[3]) ;
	vBox[3].fY = (fPosY + fV[3]) ;

	vBox[4].fX = (fPosX + fU[4] + fSizeX) ;
	vBox[4].fY = (fPosY + fV[4]) ;

	vBox[5].fX = (fPosX + fU[5] + fSizeX) ;
	vBox[5].fY = (fPosY + fV[5]) ;

	vBox[6].fX = (fPosX + fU[6] + fSizeX) ;
	vBox[6].fY = (fPosY + fV[6]) ;

	vBox[7].fX = (fPosX + fU[7] + fSizeX) ;
	vBox[7].fY = (fPosY + fV[7]) ;

	vBox[8].fX = (fPosX + fU[8] + fSizeX) ;
	vBox[8].fY = (fPosY + fV[8] + fSizeY) ;

	vBox[9].fX = (fPosX + fU[9] + fSizeX) ;
	vBox[9].fY = (fPosY + fV[9] + fSizeY) ;

	vBox[10].fX = (fPosX + fU[10] + fSizeX) ;
	vBox[10].fY = (fPosY + fV[10] + fSizeY) ;

	vBox[11].fX = (fPosX + fU[11] + fSizeX) ;
	vBox[11].fY = (fPosY + fV[11] + fSizeY) ;

	vBox[12].fX = (fPosX + fU[12]) ;
	vBox[12].fY = (fPosY + fV[12] + fSizeY) ;

	vBox[13].fX = (fPosX + fU[13]) ;
	vBox[13].fY = (fPosY + fV[13] + fSizeY) ;

	vBox[14].fX = (fPosX + fU[14]) ;
	vBox[14].fY = (fPosY + fV[14] + fSizeY) ;

	vBox[15].fX = (fPosX + fU[15]) ;
	vBox[15].fY = (fPosY + fV[15] + fSizeY) ;

	bIsOp = (GlobWin[dwWin].dwFlags & Print3D_FULL_OPAQUE) ? 1:0;


	if(GlobWin[dwWin].dwFlags & Print3D_NO_BORDER)
	{
		kmStartStrip(&VertexBufferDesc, &StripContext[2 + (bIsOp*2)]);
	}
	else
	{
		kmStartStrip(&VertexBufferDesc, &StripContext[1 + (bIsOp*2)]);
	}
	
	/* 9 strips of 4 vertices each */
   	for (j=0; j<9; j++)
   	{
	   /* Setting vertices */
		for(i=0; i<4; i++)
		{
				nVertex = pFacesData[nVertCont++];
				(vBox+nVertex)->ParamControlWord	= (i<3)?KM_VERTEXPARAM_NORMAL:KM_VERTEXPARAM_ENDOFSTRIP;
				
				kmSetVertex (&VertexBufferDesc, (KMVERTEX_03 *)(vBox+nVertex), KM_VERTEXTYPE_03, sizeof (KMVERTEX_03));
		}

	}

		
	return TRUE;
}

/*----------------------------------------------------------------------
 *  Function Name   : KMPrint3DPrint3D                                
 *  Inputs          : PosX PosY Size Text                                
 *  Outputs         :                                                   
 *  Returns         :                                                   
 *  Globals Used    :			                                        
 *  Description     : Displays text.                                    
 *----------------------------------------------------------------------*/
void LocalPrint3D(KMDWORD dwWin, float fZPos, float XPos, float YPos, float fScale, 
						  int Colour, const  char *Text)
{
KMVERTEX_03 pVerticesFont[4];
unsigned	i=0, j, Cont=0;
unsigned	Val;
float		XSize = 0.0f, XFixBug,	YSize, TempSize;
float		UPos,	VPos;
float		USize,	VSize;
int			StripL[] = {2};
float		fWinClipX[2],fWinClipY[2];
float		fScaleX, fScaleY, fPreXPos;

		if(!bInitOK) return; /* Something is wrong so do not draw */
			
	   (pVerticesFont+0)->uBaseRGB.dwPacked	= Colour | 0xFF000000;
	   (pVerticesFont+1)->uBaseRGB.dwPacked	= Colour | 0xFF000000;
	   (pVerticesFont+2)->uBaseRGB.dwPacked	= Colour | 0xFF000000;
	   (pVerticesFont+3)->uBaseRGB.dwPacked	= Colour | 0xFF000000;

	   (pVerticesFont+0)->uOffsetRGB.dwPacked	= 0x00000000;
	   (pVerticesFont+1)->uOffsetRGB.dwPacked	= 0x00000000;
	   (pVerticesFont+2)->uOffsetRGB.dwPacked	= 0x00000000;
	   (pVerticesFont+3)->uOffsetRGB.dwPacked	= 0x00000000;
	   
	   (pVerticesFont+0)->ParamControlWord	= KM_VERTEXPARAM_NORMAL;
	   (pVerticesFont+1)->ParamControlWord	= KM_VERTEXPARAM_NORMAL;
	   (pVerticesFont+2)->ParamControlWord	= KM_VERTEXPARAM_NORMAL;
	   (pVerticesFont+3)->ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;
	   
	 	if (fScale>0)
		{
			fScaleX = fScale * 255.0f;
			fScaleY = fScale * 28.0f;
		}
		else
		{
			fScaleX = 255.0f;
			fScaleY = 12.0f;
		}


		fPreXPos = XPos;
		
		if (dwWin<0 || dwWin >MAX_WINDOWS) return;
		if (!(GlobWin[dwWin].dwFlags & Print3D_WIN_EXIST) && dwWin) return;

		/*
		 * Calculating our margins
		 */
		if (dwWin)
		{
			fWinClipX[0] = (GlobWin[dwWin].fWinPos[0] + 6.0f) ;
			fWinClipX[1] = (GlobWin[dwWin].fWinPos[0] + GlobWin[dwWin].fWinSize[0] - 6.0f) ;

			fWinClipY[0] = (GlobWin[dwWin].fWinPos[1] + 6.0f) ;
			fWinClipY[1] = (GlobWin[dwWin].fWinPos[1] + GlobWin[dwWin].fWinSize[1]  + 9.0f) ;

			if(GlobWin[dwWin].dwFlags & Print3D_WIN_TITLE)
			{
				if (GlobWin[dwWin].fTitleFontSize>0)
				{
					fWinClipY[0] +=  GlobWin[dwWin].fTitleFontSize * 25.0f  ;
					fWinClipY[1] +=  GlobWin[dwWin].fTitleFontSize * 25.0f;
				}
				else
				{
					fWinClipY[0] +=  10.0f ;
					fWinClipY[1] +=  8.0f  ;
				}
			}
		}
	
	  
	  /* Set the header for our strips */	
	  kmStartStrip(&VertexBufferDesc, &StripContext[0]);	
		
      while (TRUE)
	  {
	   Val = (unsigned)*(Text+i++);

	   /* End of the string */
	   if (Val==0 || i>MAX_LETTERS) break;

	   /* It is SPACE so don't draw and carry on... */
	   if (Val==' ') 
	   {
		   if (fScale>0)	XPos += 10.0f/255.0f * fScaleX; 
		   else				XPos += 5.0f ; 
		   continue;
	   }

	   /* It is RETURN so jump a line */
	   if (Val==0x0A) 
	   {
		   XPos = fPreXPos - XSize; 
		   YPos += YSize; 
		   continue;
	   }

	   /* If fScale is negative then select the small set of letters (System) */
	   if (fScale < 0.0f)
	   {  
		    XPos    += XSize;
			UPos    =  KMPrint3DU_System[Val];
			VPos    =  KMPrint3DV_System[Val] - 0.0001f; /* Some cards need this little bit */
			YSize   =  fScaleY;
			XSize   =  KMPrint3DSize_System[Val] * fScaleX;
			USize	=  KMPrint3DSize_System[Val];
			VSize	=  12.0f/255.0f;
	  }
	   else /* Big set of letters (Bold) */
	   {
		    XPos    += XSize;
			UPos    =  KMPrint3DU_Bold[Val];
			VPos    =  KMPrint3DV_Bold[Val] - 1.0f/256.0f;
			YSize   =  fScaleY;
			XSize   =  KMPrint3DSize_Bold[Val] * fScaleX;
			USize	=  KMPrint3DSize_Bold[Val];
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
					USize	=  KMPrint3DSize_System[Val] * (XSize/TempSize);
				else
					USize	=  KMPrint3DSize_Bold[Val] * (XSize/TempSize);
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

	   (pVerticesFont+0)->fX	= XPos;
	   (pVerticesFont+0)->fY	= YPos;
	   (pVerticesFont+0)->u.fZ	= fZPos;
	   (pVerticesFont+0)->fU	= UPos;
	   (pVerticesFont+0)->fV	= VPos;

	   (pVerticesFont+1)->fX	= XPos+XSize;
	   (pVerticesFont+1)->fY	= YPos;
	   (pVerticesFont+1)->u.fZ	= fZPos;
	   (pVerticesFont+1)->fU	= UPos+USize;
	   (pVerticesFont+1)->fV	= VPos;
	  
	   (pVerticesFont+2)->fX	= XPos;
	   (pVerticesFont+2)->fY	= YPos+YSize;
	   (pVerticesFont+2)->u.fZ	= fZPos;
	   (pVerticesFont+2)->fU	= UPos;
	   (pVerticesFont+2)->fV	= VPos-VSize;

	   (pVerticesFont+3)->fX	= XPos+XSize;
	   (pVerticesFont+3)->fY	= YPos+YSize;
	   (pVerticesFont+3)->u.fZ	= fZPos;
	   (pVerticesFont+3)->fU	= UPos+USize;
	   (pVerticesFont+3)->fV	= VPos-VSize;

	    XSize = XFixBug;

	   /* Fix number width */
	   if (Val >='0' && Val <='9')
	   {
			if (fScale < 0.0f)	XSize = KMPrint3DSize_System['0'] * fScaleX;
			else				XSize = KMPrint3DSize_Bold['0'] * fScaleX;
	   }
	  	   
	    /* Strip of 4 vertices for each letter */
	 
	 	/* Setting vertices */
		for(j=0; j<4; j++)
		{
			kmSetVertex (&VertexBufferDesc, (KMVERTEX_03 *)(pVerticesFont+j), KM_VERTEXTYPE_03, sizeof (KMVERTEX_03));
		}

	    } /* End of while */

		
} 
/*----------------------------------------------------------------------
 *  Function Name   : GetLength                                
 *  Inputs          :                                
 *  Outputs         :                                                   
 *  Returns         :                                                   
 *  Globals Used    :			                                        
 *  Description     : calculates the size in pixels.                                    
 *----------------------------------------------------------------------*/
float GetLength (float fFontSize,  char *sString)
{
 char Val;
float fScale, fSize;

		if (fFontSize>=0) /* Arial font */
		{
			fScale = fFontSize * 255.0f;
			fSize  = 0.0f;

			while (Val = *sString++)
			{
				if (Val==' ') {fSize += 10.0f * fFontSize; continue;}
				if(Val>='0' && Val <= '9') Val = '0'; /* That's for fixing the number width */
				fSize += KMPrint3DSize_Bold[Val] * fScale ;
			}
		}
		else /* System font */
		{
			fScale = 255.0f;
			fSize  = 0.0f;

			while (Val = *sString++)
			{
				if (Val==' ') {fSize += 5.0f; continue;}
				if(Val>='0' && Val <= '9') Val = '0'; /* That's for fixing the number width */
				fSize += KMPrint3DSize_System[Val]  * fScale;
			}
		}

		return (fSize);
}
/*----------------------------------------------------------------------
 *  Function Name   : LoadPrint3DTextures	                                    
 *  Inputs          :                       							 
 *  Returns         : TRUE if succesful, FALSE otherwise.               
 *  Globals Used    :                                                   
 *  Description     : Reads texture data from *.dat and loads it in     
 *					  video memory.	                                    
 *----------------------------------------------------------------------*/
int LoadPrint3DTextures(KMSURFACEDESC *pTexID,  char *pSource, KMDWORD nSize, KMDWORD nMode)
{
register i;
unsigned ErrorCode;


	/* Create texture surface */
	if(nMode==0)
	{
		ErrorCode = kmCreateTextureSurface(pTexID, nSize, nSize, KM_TEXTURE_TWIDDLED | KM_TEXTURE_ARGB4444);
	}
	
	if(nMode==1)
	{
		ErrorCode = kmCreateTextureSurface(pTexID, nSize, nSize, KM_TEXTURE_RECTANGLE | KM_TEXTURE_ARGB4444);
	}
	else if(nMode==2)
	{
		ErrorCode = kmCreateTextureSurface(pTexID, nSize, nSize, KM_TEXTURE_RECTANGLE | KM_TEXTURE_RGB565);
	}
	if (ErrorCode != KMSTATUS_SUCCESS) return ErrorCode;


	/* Load and set texture */
	ErrorCode = kmLoadTexture(pTexID, (unsigned long *)pSource + (16 / sizeof(KMDWORD)));
	if (ErrorCode != KMSTATUS_SUCCESS) return ErrorCode;
		
	/* Everything's OK */
	return KMSTATUS_SUCCESS;;
}
/*----------------------------------------------------------------------*/
/*  Function Name   :  KMShellInitStripHead		                        */
/*  Inputs          :  StripContext, *pTexSurfDesc nMode                  */  
/*  Outputs         :  None                                             */
/*  Returns         :  None                                             */
/*  Globals Used    :  None                                             */
/*  Description     :  Sets standard render parameters.                 */
/*----------------------------------------------------------------------*/
void SetVertexContext(PKMSTRIPHEAD	StripHead, KMSURFACEDESC  *pTexSurfDesc, int bTranslucent)
{
KMSTRIPCONTEXT StripContext;
int nPoly;

	memset (&StripContext, 0, sizeof(KMSTRIPCONTEXT));

	StripContext.nSize = sizeof(KMSTRIPCONTEXT);
	
	/* Defaults */
	StripContext.StripControl.nListType		 						= KM_OPAQUE_POLYGON;
	StripContext.StripControl.nUserClipMode	 						= KM_USERCLIP_DISABLE;
	StripContext.StripControl.nShadowMode		 					= KM_NORMAL_POLYGON;
	StripContext.StripControl.bOffset								= KM_FALSE;
	StripContext.StripControl.bGouraud		 						= KM_TRUE;
	StripContext.ObjectControl.nDepthCompare			 			= KM_GREATEREQUAL;
	StripContext.ObjectControl.nCullingMode			 				= KM_NOCULLING;
	StripContext.ObjectControl.bZWriteDisable						= KM_FALSE;
	StripContext.ObjectControl.bDCalcControl			 			= KM_FALSE;
	StripContext.ImageControl[KM_IMAGE_PARAM1].nSRCBlendingMode		= KM_ONE;
	StripContext.ImageControl[KM_IMAGE_PARAM1].nDSTBlendingMode		= KM_ZERO;
	StripContext.ImageControl[KM_IMAGE_PARAM1].bSRCSelect			= KM_FALSE;
	StripContext.ImageControl[KM_IMAGE_PARAM1].bDSTSelect			= KM_FALSE;
	StripContext.ImageControl[KM_IMAGE_PARAM1].nFogMode				= KM_NOFOG;
	StripContext.ImageControl[KM_IMAGE_PARAM1].bColorClamp			= KM_FALSE;
	StripContext.ImageControl[KM_IMAGE_PARAM1].bUseAlpha			= KM_FALSE;
	StripContext.ImageControl[KM_IMAGE_PARAM1].bIgnoreTextureAlpha	= KM_FALSE;
	StripContext.ImageControl[KM_IMAGE_PARAM1].nFlipUV				= KM_NOFLIP;
	StripContext.ImageControl[KM_IMAGE_PARAM1].nClampUV				= KM_NOCLAMP;
	StripContext.ImageControl[KM_IMAGE_PARAM1].nFilterMode			= KM_BILINEAR;
	StripContext.ImageControl[KM_IMAGE_PARAM1].bSuperSampleMode		= KM_FALSE;
	StripContext.ImageControl[KM_IMAGE_PARAM1].dwMipmapAdjust		= KM_MIPMAP_D_ADJUST_1_00;
	StripContext.ImageControl[KM_IMAGE_PARAM1].nTextureShadingMode	= KM_MODULATE_ALPHA;
	StripContext.ImageControl[KM_IMAGE_PARAM1].pTextureSurfaceDesc	= pTexSurfDesc;
	
	/* Translucent Polygon */
	if (bTranslucent) 	
	{
		StripContext.StripControl.nListType 						= KM_TRANS_POLYGON;
		StripContext.ImageControl[KM_IMAGE_PARAM1].bUseAlpha 		= KM_TRUE;
		StripContext.ImageControl[KM_IMAGE_PARAM1].nSRCBlendingMode	= KM_SRCALPHA;
		StripContext.ImageControl[KM_IMAGE_PARAM1].nDSTBlendingMode	= KM_INVSRCALPHA;
	}
	
	/* Create the strip head */
	kmGenerateStripHead03(StripHead, &StripContext);
}