/*****************************************************************************
  Name : D3DTPrint3D.h			v1.0.1
  Date : July 1998
 
  Description : Header for D3DTPrint3D.c
  
  Copyright : 1999 by Imagination Technologies Limited. All rights reserved.
******************************************************************************/

#ifndef _Print3D_H_
#define _Print3D_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */
#ifndef RELEASE
#define RELEASE(x)	if (x) { (x)->lpVtbl->Release(x); (x)=NULL; }
#endif

#define FONT_SYSTEM -1.0f
#define FONT_ARIAL   1.0f

/* dwFlags for D3DTPrint3DSetWindowFlags */
enum {
	PRINT3D_ACTIVATE_WIN		=	0x01,
	PRINT3D_DEACTIVATE_WIN		=	0x02,
	PRINT3D_ACTIVATE_TITLE		=	0x04,
	PRINT3D_DEACTIVATE_TITLE	=	0x08,
	PRINT3D_FULL_OPAQUE			=	0x10,
	PRINT3D_FULL_TRANS			=	0x20,
	PRINT3D_ADJUST_SIZE_ALWAYS	=	0x40,
	PRINT3D_NO_BORDER			=	0x80,
} PRINT3D_FLAGS;

/**************/
/* Prototypes */
/**************/

/* Always in InitView */
BOOL D3DTPrint3DSetTextures(LPDIRECT3DDEVICE3 lpDev3, LPDIRECTDRAW4 lpDD4, DWORD dwScreenX, DWORD dwScreenY);

/* Always in ReleaseView */
void  D3DTPrint3DReleaseTextures (void);

/* Screen Output */
void D3DTPrint3D (float XPos, float YPos, float fScale,  int Colour, const TCHAR *Format, ...);

/* Create a window with default values (return a handle to the window)*/
DWORD D3DTPrint3DCreateWindow	(DWORD dwBufferSizeX, DWORD dwBufferSizeY);

/* Free memory allocated with CreateWindow */
void D3DTPrint3DDeleteWindow(DWORD dwWin);

/* Free memory allocated with CreateWindow for all the windows*/
void D3DTPrint3DDeleteAllWindows(void);

/* Display the window (must be between BeginScene-EndScene)*/
void D3DTPrint3DDisplayWindow (DWORD dwWin);

/* Display All (must be between BeginScene-EndScene)*/
void D3DTPrint3DDisplayAllWindows(void);

/* Feed the text buffer */
void D3DTPrint3DWindowOutput	(DWORD dwWin, const TCHAR *Format, ...);

/* Clean the text buffer */
void D3DTPrint3DClearWindowBuffer(DWORD dwWin);

/* User values for the window.
 * Windows position and size are referred to a virtual screen of 100x100,
 * (0,0) is the top-left corner and (100,100) the bottom-right corner.
 * These values are the same for all resolutions.
 */
void  D3DTPrint3DSetWindow		(DWORD dwWin, DWORD dwBackgroundColor, DWORD dwFontColor, float fFontSize, 
								float fPosX, float fPosY, float fSizeX, float fSizeY);

/* User values for the title */
void D3DTPrint3DSetTitle	(DWORD dwWin, DWORD dwBackgroundColor, float fFontSize, 
								DWORD dwFontColorLeft, TCHAR *sTitleLeft, 
								DWORD dwFontColorRigth, TCHAR *sTitleRight);
/* Setting flags */
void D3DTPrint3DSetWindowFlags (DWORD dwWin, DWORD dwFlags);

/* Cursor position for the next OutputWindow */
void D3DTPrint3DSetWindowBufferPointer(DWORD dwWin, DWORD dwXPos, DWORD dwYPos);

/* Calculates window size to display everything.
 * (dwMode 0 = Both, dwMode 1 = X only,  dwMode 2 = Y only) 
 */
void D3DTPrint3DAdjustWindowSize(DWORD dwWin, DWORD dwMode);

/* This window on the top of everything */
void D3DTPrint3DSetTopMostWindow(DWORD dwWin);

/* Window position */
void D3DTPrint3DSetWindowPos(DWORD dwWin, float fPosX, float fPosY);

/* Window size */
void D3DTPrint3DSetWindowSize(DWORD dwWin, float fSizeX, float fSizeY);

/* Easy way... */
DWORD D3DTPrint3DCreateDefaultWindow (float fPosX, float fPosY, int nXSize_LettersPerLine, TCHAR *sTitle, TCHAR *sBody);

#ifdef __cplusplus
}
#endif

#endif

