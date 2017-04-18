/*****************************************************************************
  Name : KMShell.h
  Date : October 1998
  Platform : ANSI compatible

  Header file to be used with KMShell.c

  Copyright : 1998 by VideoLogic Limited. All rights reserved.
******************************************************************************/
#ifndef KMSHELL_H
#define KMSHELL_H

#include <kamui2.h>		/* for Kamui calls */

/* Some defines */
/* Video output modes */
#define VIDEO_NTSC 0  /* NTSC 320x240 Noninterlaced 60Hz Supersample */
#define VIDEO_VGA  1  /* VGA  640x480 60Hz no Supersample */
#define VIDEO_PAL  2  /* NTSC 320x240 Noninterlaced 50Hz Supersample */

/* Vertex Context Modes */
#define VC_OPAQUE		0
#define VC_TRANS		1
#define VC_PUNCHTHROUGH 2
#define VC_ADDITIVE     3  /* Translucent additive blending */
#define VC_SPECULAR		4
#define VC_FOGTABLE		8
#define VC_FOGVERTEX	16
#define VC_NONTEXTURED	32
#define VC_CULLING		64
#define VC_UVFLIP		128
#define VC_DECALALPHA   256

/* Passes info */
#define PASS_NULL     0
#define PASS_AUTOSORT 1
#define PASS_PRESORT  2


/********************************************************/
/* Helper functions to build a simple Kamui application */
/********************************************************/

KMDWORD		KMShellSetVideo		(void);

KMDWORD		KMShellSetBuffers	(KMDWORD Pass1, KMDWORD Pass2, KMDWORD Pass3, KMDWORD Pass4,
						   		 KMDWORD Pass5, KMDWORD Pass6, KMDWORD Pass7, KMDWORD Pass8) ;

PKMDWORD	KMShellGetMaple		(void);

void		KMShellQuitKamui	(void);

void 		KMShellInitStripHead (PKMSTRIPHEAD	pStripHead,	KMSURFACEDESC  *pTexSurfDesc, int nMode);

void		KMShellStrips		(PKMSTRIPHEAD	pStripHead,  unsigned nNumStrips, unsigned short *pLen,	
									unsigned short *pStrips, KMVERTEX_03 *pVertices);

void		KMShellTriangles	(PKMSTRIPHEAD	pStripHead, unsigned nNumFaces, unsigned short *pFaces, 
									KMVERTEX_03	*pVertices);

void		KMShellBackground	(PKMSTRIPHEAD	pStripHead);
void KMShellBackground2 (PKMSTRIPHEAD pStripHead);

KMVERTEXBUFFDESC *KMShellGetVertexBuffer (void);

/*******************************
** User interaction functions **
*******************************/

/* These functions have to exist in the scene file (e.g. scene.c).
   They are used to interract with the Kamui Shell */

void InitAplication (void);
/*
InitAplication()
  
This function will be called by the KM Shell before anything happens, at the very
beginning of the SGLShell main() function. That's the only time this function
will be called. This function enables the user to perform any initialisation before 
the program is actually run.
*/


void QuitAplication(void);
/*
QuitAplication()

This function will be called by the KMShell just before finishing the program.
It enables the user to release any memory allocated before.
*/

BOOL RenderScene	(DWORD nCurrentPass);

/*
RenderScene()

That's the main user function in which you have to do your own rendering.
Be sure to make this function return TRUE if the rendering has gone OK.
*/

int PadControl(void);
/*
PadControl(void)

This function is the user Procedure function. 
It enables the user to control the Dreamcast PAD.
If you don't want to use this function, put nothing in it :
    
int PadControl(void)
{
	
	 Nothing !
	
}

*/

/*
	Functions to read the controller by the user
 */
BOOL IsAKey(void);
BOOL IsBKey(void);
BOOL IsXKey(void);
BOOL IsYKey(void);

BOOL IsLFKey(void);
BOOL IsRFKey(void);

BOOL IsSTARTKey(void);

BOOL IsUPKey(void);
BOOL IsDOWNKey(void);
BOOL IsLEFTKey(void);
BOOL IsRIGHTKey(void);

int  AnalogPalY(void);
int  AnalogPadX(void);

#endif
