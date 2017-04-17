/*****************************************************************************
  Name :	D3DSiberian
  Author:	Carlos Sarria
  Date :	Jan 1999 (Updated Aug 99)
  
  Description: This demo shows how to use puchthrough in DRAGON.

  Copyright : 1999 by VideoLogic Limited. All rights reserved.
******************************************************************************/

/****************************************************************************
 ** INCLUDES                                                               **
 ****************************************************************************/
#include <windowsx.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <d3d.h>

#define WCE_DEBUG(x) OutputDebugString(x);

// D3D Shell includes
#include "D3DShell.h"	// D3D Shell include

// D3D Tools include
#include "D3DTools.h"	// D3D Tools include

// 3D Model
#include "D3DSiberian.h"

/****************************************************************************
 ** DEFINES                                                                **
 ****************************************************************************/

#define USE_D3DVERTEX    0
#define USE_D3DLVERTEX   1
#define USE_D3DTLVERTEX  2

#ifndef PI
#define PI 3.14159f
#endif

#ifndef RELEASE
#define RELEASE(x)	if (x) { x->lpVtbl->Release(x); x=NULL; }
#endif

/* A structure which holds the object's data */

typedef struct _OBJECT
{
	int			nNumberOfVertices;		/* Number of Vertices */
	int			nNumberOfTriangles;		/* Number of Triangles */
	int			nNumberOfStrips;
	float		fCentreX;
	float		fCentreY;
	float		fCentreZ;				/* Object centre */
	float		*pVertices;				/* Vertices coordinates */
	float		*pNormals;				/* Normals coordinates */
	WORD		*pTriangleList;			/* Triangle list */
	WORD		*pStrips;				/* Strips list */
	WORD		*pStripLength;			/* Number of polygons per strip */
	D3DVERTEX   *pD3DVertices;			/* No tranformed vertices (DX makes all transformations and lighting) */
	D3DLVERTEX  *pLVertices;			/* No tranformed vertices (DX makes transformations only) */
	D3DTLVERTEX	*pTLVertices;			/* Transformed vertices */
} OBJECT, *LPOBJECT;

typedef struct _TEXTURE
{
	LPDIRECTDRAWSURFACE4	lpDDSTextureSurface;
	LPDIRECT3DTEXTURE2		lpD3DTexture;
} TEXTURE;


/****************************************************************************
 ** GLOBALS                                                                **
 ****************************************************************************/


int					dwCurrentWidth, dwCurrentHeight;
float				fFrontClippingPlane = 1.0f;
D3DVECTOR CameraPosition		= { 0.0f, 0.0f, -100.0f};
D3DVECTOR CameraPointing			= { 0.0f, 0.0f, 100.0f};
D3DVECTOR			LightVector			= { 1.0f, -1.0f, 1.0f};
float				fCameraRoll			= 0.0f;
HRESULT				hres;

D3DMATRIX			WorldMatrix;

TEXTURE			    D3DTexture[256];

OBJECT				D3DObject[NUM_MESHES];

int 				nFrame=0;

BOOL				bPause = FALSE;

DWORD				dwDisplayWins = TRUE;

DWORD				InfoWin, TWin[10], dwCurrentWin=0, nMode = 0;

unsigned			nTrees	= 170;
unsigned			Type	= 0;
unsigned			Cont	= 0;
unsigned			nPT		= 0;
unsigned			bStart	= FALSE;
float				Ang		= 0;
float				Distance = 0;

LPDIRECT3D3			lpGlobD3D3;

/* DX tranformations */
D3DLIGHT2			light;        // Structure defining the light
LPDIRECT3DLIGHT		lpD3DLight;   // Object pointer for the light

TCHAR				*sMode[] = {L"PUNCHTROUGH",L"OPAQUE",L"TRANSLUCENT"};

/****************************************************************************
 ** PROTOTYPES                                                             **
 ****************************************************************************/
void TransformObject		(LPDIRECT3DDEVICE3 lpDev3, D3DMATRIX *pWorldMatrix, LPOBJECT pObject, BOOL bTrans, BOOL bShaded, int nMode);
void RenderObjectTriangles  (LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DTEXTURE2	lpTexture, LPOBJECT pObject, int nMode);

void CreateWindows				(void);
void CreateObjectFromHeaderFile	(OBJECT *pObject, int nObject);

void CreateLight				(LPDIRECT3D3 lpD3D3, LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DVIEWPORT3 lpView3);
void Background					(LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DTEXTURE2 TextureID);

BOOL PadControl					(void);

void LoadPunchthrough (LPDIRECTDRAW4 lpDD4, LPDIRECT3DDEVICE3 lpDev3, TCHAR *ResourceName, TEXTURE *pTexture);

void ReorderTriangles (int nNumStrips, WORD *pFaces, WORD *pStrips, WORD *pStripLengths);
/****************************************************************************
** InitApplication() is called by D3DShell to enable user to initialise	   **
** his/her application													   **
****************************************************************************/
void InitApplication(HINSTANCE hInstance, HWND hWindow, TCHAR *pszCommandLine)
{
	/* For the Dreamcast controller */
	InitDirectInput(hWindow, hInstance);
					
	/* Creation of all the information windows */
	CreateWindows();

	D3DTPrint3DWindowOutput (InfoWin, TEXT(" (A/F5) Polygon type: PUNCHTROUGH \n"));

}


/****************************************************************************
** QuitApplication() is called by D3D Shell to enable user to release      **
** any memory before quitting the program.								   **
****************************************************************************/
void QuitApplication()
{
	/* freeing memory */
	D3DTPrint3DDeleteAllWindows();

	ReleaseDirectInput();
}

/*******************************************************************************
 * Function Name  : UserWindowProc
 * Returns        : TRUE if no error occured
 * Global Used    : None
 * Description    : Application's window messages handler
 *					When processing keystrokes, DO NOT process ESCAPE key 
 *					(VK_ESCAPE), as it is already used by the FrontEnd.
 *					
 *******************************************************************************/
void UserWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:	switch(wParam)
						{
							case VK_F1:
								dwCurrentWin--;
								if (dwCurrentWin==-1) dwCurrentWin = 2;
								break;

							case VK_F2:
								dwCurrentWin++;
								if (dwCurrentWin==3) dwCurrentWin = 0;
								break;

							case VK_F5:
								nMode++; if (nMode==3) nMode=0;
								D3DTPrint3DWindowOutput (InfoWin, TEXT(" (A/F5) Polygon type: %s \n"), sMode[nMode]);
								break;

							case VK_SPACE:
								bPause = !bPause;
								break;

							case VK_UP:
								break;

							case VK_DOWN:
								break;

							case VK_LEFT:
								break;

							case VK_RIGHT:
								break;
								
				
							case VK_F3: 
								/* Minimise all windows */
								dwDisplayWins = !dwDisplayWins;
								break;

						}
						break;
	}
}
/*******************************************************************************
 * Function Name  : PadControl
 * Returns        : FALSE to finish the application.
 * Global Used    : 
 * Description    : Dreamcast joystick control.
 *******************************************************************************/
BOOL PadControl (void)
{	
static	int	Delay = 0;

	UpdateJoystick();

	Delay++;

	/* START */
	if (IsSTARTKey())
	{
		if (Delay>2)
		{
			bPause = !bPause;
		}
		Delay = 0;
	}

	/* UP */
	if (IsUPKey()|| GetAnalogY()<64)
	{
		if (Delay>2)
		{
			dwDisplayWins = ! dwDisplayWins;
		}
			Delay = 0;
	}

	/* DOWN */
	if (IsDOWNKey() || GetAnalogY()>192)
	{
		if (Delay>2)
		{
			dwDisplayWins = ! dwDisplayWins;
		}
			Delay = 0;
	}

	/* LEFT */
	if (IsLEFTKey() || GetAnalogX()<64)
	{
		if (Delay>2)
		{
			dwCurrentWin--;
			if (dwCurrentWin==-1) dwCurrentWin = 2;
		}
			Delay = 0;
	}

	/* RIGHT */
	if (IsRIGHTKey() || GetAnalogX()>192)
	{
		if (Delay>2)
		{
			dwCurrentWin++;
			if (dwCurrentWin==3) dwCurrentWin = 0;
		}
		Delay = 0;
	}


	/* A button */
	if (IsAKey())
	{
		if (Delay>2)
		{
			nMode++; if (nMode==3) nMode=0;
			D3DTPrint3DWindowOutput (InfoWin, TEXT(" (A/F5) Polygon type: %s \n"), sMode[nMode]);
		}
		Delay = 0;
	}
	
	/* B button */
	if (IsBKey())
	{
	}
		
	/* X button */
	if (IsXKey())
	{
		return FALSE;
	}

	/* Y button */
	if (IsYKey())
	{
	}

	/* LEFT finger button */
	if (IsLFKey())
	{
	}

	/* RIGHT finger button */
	if (IsRFKey())
	{
	}

	return TRUE;
}
/*******************************************************************************
 * Function Name  : RenderScene
 * Returns        : TRUE if no error occured
 * Global Used    : None
 * Description    : Application's rendering function
 *					
 *******************************************************************************/
BOOL RenderScene (LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DVIEWPORT3 lpView3)
{
D3DMATRIX		Matrx;
int				j;
unsigned		TreeCont = 21, BiCont=0;
float			Radius;
static unsigned	PathCont = 0;

	if (PadControl()==FALSE) return FALSE; /* Finish the application */

	if (bPause==FALSE)
	{
		Ang += PI/80.0f;
		Distance += PI/60.0f;
	}

	Radius = 500 + 350 * (float)sin ((double)Distance);

	CameraPosition.x = (float)cos(Ang) * Radius;
	CameraPosition.y = 400;
	CameraPosition.z = (float)sin(Ang) * Radius;

	CameraPointing.x = *(Mesh[M_LOGO].pVertex+0);
	CameraPointing.y = *(Mesh[M_LOGO].pVertex+1);
	CameraPointing.z = *(Mesh[M_LOGO].pVertex+2);

	/* Begin Scene */
	lpDev3->lpVtbl->BeginScene(lpDev3);
	

	/* Drawing the trees (there are 3 different models) */
	for (j=0; j<(int)nTrees; j++)
	{
      	
	  D3DTMatrixReset(&Matrx);

	  /* Reads one of the ground vertices and places a tree there */
	  D3DTMatrixTranslate (&Matrx,	*(Mesh[M_SNOW].pVertex+TreeCont*3+0), 
								*(Mesh[M_SNOW].pVertex+TreeCont*3+1)+50, 
								*(Mesh[M_SNOW].pVertex+3*TreeCont+2)
						);

	  TreeCont+=8;
	 
	  if(j%4==0) Type = (BiCont++&1)?2:0;
	  if(j%4==1) Type = 2;
	  if(j%4 >1) Type = 1;

	  
	  /* Leaves render states */
	  switch (nMode)
	  {
		case 0: /* Punchthrough*/
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHATESTENABLE, TRUE);
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHAREF, 255);
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA );
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
				break;
		case 1: /* Opaque */
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHATESTENABLE, FALSE);
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE );
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);
				break;
		case 2: /* Translucent */
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHATESTENABLE, FALSE);
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA );
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
				break;
	  }
	  
	 
      switch (Type)
	  {
		case 0:
			/* First tree leaves */
			TransformObject(lpDev3, &Matrx, &D3DObject[M_B2_TRANS], TRUE, FALSE, USE_D3DLVERTEX);
			RenderObjectTriangles (lpDev3, D3DTexture[M_B2_TRANS].lpD3DTexture, &D3DObject[M_B2_TRANS], USE_D3DLVERTEX);
			break;

		case 1:
			/* Second tree leaves */
			TransformObject(lpDev3, &Matrx, &D3DObject[M_B1_TRANS], TRUE, FALSE, USE_D3DLVERTEX);
			RenderObjectTriangles (lpDev3, D3DTexture[M_B1_TRANS].lpD3DTexture, &D3DObject[M_B1_TRANS], USE_D3DLVERTEX);
			break;
	
		case 2:
			/* Third tree leaves */
			TransformObject(lpDev3, &Matrx, &D3DObject[M_B4_TRANS], TRUE, FALSE, USE_D3DLVERTEX);
			RenderObjectTriangles (lpDev3, D3DTexture[M_B4_TRANS].lpD3DTexture, &D3DObject[M_B4_TRANS], USE_D3DLVERTEX);
			break;
		}

		 /* Trunks render states */
	    lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
		lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHATESTENABLE, FALSE);
		
	    switch (Type)
		{
		case 0:
			/* First tree trunk */
			TransformObject(lpDev3, &Matrx, &D3DObject[M_B2_TRUNK], TRUE, FALSE, USE_D3DLVERTEX);
			RenderObjectTriangles (lpDev3, D3DTexture[M_B2_TRUNK].lpD3DTexture, &D3DObject[M_B2_TRUNK], USE_D3DLVERTEX);
		break;

		case 1:
			/* Second tree trunk*/
			TransformObject(lpDev3, &Matrx, &D3DObject[M_B1_BARK], TRUE, FALSE, USE_D3DLVERTEX);
			RenderObjectTriangles (lpDev3, D3DTexture[M_B1_BARK].lpD3DTexture, &D3DObject[M_B1_BARK], USE_D3DLVERTEX);
		break;


		case 2:
			/* Third tree trunk*/
			TransformObject(lpDev3, &Matrx, &D3DObject[M_B4_BARK], TRUE, FALSE, USE_D3DLVERTEX);
			RenderObjectTriangles (lpDev3, D3DTexture[M_B4_BARK].lpD3DTexture, &D3DObject[M_B4_BARK], USE_D3DLVERTEX);
		break;
		}

	}

   /* Drawing the ground */
   D3DTMatrixReset(&Matrx);
   TransformObject(lpDev3, &Matrx, &D3DObject[M_SNOW], TRUE, FALSE, USE_D3DLVERTEX);
   RenderObjectTriangles (lpDev3, D3DTexture[M_SNOW].lpD3DTexture, &D3DObject[M_SNOW], USE_D3DLVERTEX);

   /* Drawing the logo */
   D3DTMatrixReset(&Matrx);
   TransformObject(lpDev3, &Matrx, &D3DObject[M_LOGO], TRUE, FALSE, USE_D3DLVERTEX);
   RenderObjectTriangles (lpDev3, D3DTexture[M_LOGO].lpD3DTexture, &D3DObject[M_LOGO], USE_D3DLVERTEX);

 	
   	/* 
	 * D3DTPrint3DDisplayAllWindows must be called just before EndScene.
	 */
	 if(dwDisplayWins)
	 {
		D3DTPrint3DDisplayWindow(TWin[dwCurrentWin]);
		D3DTPrint3DDisplayWindow(InfoWin);

	 }

	 D3DShellDCLogo (0x00);

	if (bPause==TRUE) D3DTPrint3D (80.0f, 3.0f, 1.0f, (unsigned)0xFFFFFFFFF, TEXT("PAUSE"));

	/* Drawing the background */
	Background (lpDev3, D3DTexture[20].lpD3DTexture);

	/* End Scene */
    lpDev3->lpVtbl->EndScene(lpDev3);
 

	if (bPause==FALSE) nFrame++;

	/* No problem occured */
	return TRUE;


}
/*******************************************************************************
 * Function Name  : InitView
 * Inputs		  : lpDD4, lpD3D3, lpDev3, lpView3, dwWidth, dwHeight
 * Returns        : TRUE on success
 * Global Used    : None
 * Description    : Application's viewport initialisation function
 *					Create execute buffers, materials, etc...
 *******************************************************************************/
BOOL InitView(LPDIRECTDRAW4 lpDD4, LPDIRECT3D3 lpD3D3, LPDIRECT3DDEVICE3 lpDev3,
              LPDIRECT3DVIEWPORT3 lpView3, DWORD dwWidth, DWORD dwHeight)
{
register i;

	lpGlobD3D3 = lpD3D3;

    /* This fuction must be always in InitView  */    
	D3DTPrint3DSetTextures(lpDev3, lpDD4, dwWidth, dwHeight);
		
	 /* Update viewport size variables */
	dwCurrentWidth=dwWidth;
	dwCurrentHeight=dwHeight;
		
	/* Assign the background colour to be black.
	   This is needed to assign a colour to the viewport */
	D3DTMiscSetBackgroundColor(lpD3D3, lpDev3, lpView3, RGB_MAKE(0, 0, 0));

	/* Load Textures */
	D3DShellLoadBMP(TEXT("BMP_SNOW"),	FALSE, &D3DTexture[M_SNOW].lpD3DTexture);
	D3DShellLoadBMP(TEXT("BMP_VIDEOL"), FALSE, &D3DTexture[M_LOGO].lpD3DTexture);

	LoadPunchthrough (lpDD4, lpDev3, TEXT("BMP_PINE4"),		&D3DTexture[M_B4_TRANS]);
	LoadPunchthrough (lpDD4, lpDev3, TEXT("BMP_BRANCH2"),	&D3DTexture[M_B2_TRANS]);
	LoadPunchthrough (lpDD4, lpDev3, TEXT("BMP_BUSH"),		&D3DTexture[M_B1_TRANS]);
	
	D3DShellLoadBMP(TEXT("BMP_BARK"),	FALSE, &D3DTexture[M_B1_BARK].lpD3DTexture);

	D3DTexture[M_B4_BARK].lpD3DTexture = D3DTexture[M_B1_BARK].lpD3DTexture;
	D3DTexture[M_B2_TRUNK].lpD3DTexture = D3DTexture[M_B1_BARK].lpD3DTexture;
	D3DTexture[M_B3_TRUNK].lpD3DTexture = D3DTexture[M_B1_BARK].lpD3DTexture;	
	
	D3DShellLoadBMP(TEXT("BMP_BACK"),	FALSE, &D3DTexture[20].lpD3DTexture);
	
	/* Create directional light */
	CreateLight (lpD3D3, lpDev3, lpView3);

	/* General Render States */
	lpDev3->lpVtbl->SetTextureStageState (lpDev3, 0, D3DTSS_MINFILTER ,		D3DTFN_LINEAR);	
	lpDev3->lpVtbl->SetTextureStageState (lpDev3, 0, D3DTSS_MAGFILTER ,		D3DTFG_LINEAR);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DITHERENABLE,		TRUE);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ZENABLE,			TRUE);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_CULLMODE,			D3DCULL_NONE);

	/* Initialise Meshes */
	for (i=0; i<NUM_MESHES; i++)
	{
		 ReorderTriangles (Mesh[i].nNumStrips, Mesh[i].pFaces, Mesh[i].pStrips, Mesh[i].pStripLength);
		 CreateObjectFromHeaderFile(&D3DObject[i], i);
	}


	/* No problen occured */
	return TRUE;
}


/*******************************************************************************
 * Function Name  : ReleaseView
 * Input		  : lpView3
 * Returns        : Nothing
 * Global Used    : None
 * Description    : Application's rendering function
 *					D3DShell passes the viewport variable to this function 
 *					so you can delete any lights you created previously 
 *******************************************************************************/
void ReleaseView(LPDIRECT3DVIEWPORT3 lpView3)
{
register i;
	
	/* This fuction must be always in ReleaseView  */    
	D3DTPrint3DReleaseTextures();

	/* Free memory used by objects */
	for (i=0; i<NUM_MESHES; i++)
	{
		free(D3DObject[i].pD3DVertices);
		free(D3DObject[i].pLVertices);
		free(D3DObject[i].pTLVertices);
	}

	/* Release light */
	RELEASE(lpD3DLight);

	/* Relesease textures created with D3DTools */
	RELEASE(D3DTexture[M_B4_TRANS].lpDDSTextureSurface);
	RELEASE(D3DTexture[M_B4_TRANS].lpD3DTexture);

	RELEASE(D3DTexture[M_B2_TRANS].lpDDSTextureSurface);
	RELEASE(D3DTexture[M_B2_TRANS].lpD3DTexture);

	RELEASE(D3DTexture[M_B1_TRANS].lpDDSTextureSurface);
	RELEASE(D3DTexture[M_B1_TRANS].lpD3DTexture);


    /* (textures created with the D3DShell function 
	 *	D3DShellLoadBMP are automatically released) 
	 */
}

/*******************************************************************************
 * Function Name  : CreateObjectFromHeaderFile
 * Input/Output	  : *pObject
 * Global Used    : None
 * Description    : Function to initialise object from a .h file
 *******************************************************************************/
void CreateObjectFromHeaderFile (OBJECT *pObj, int nObject)
{
int			i;
float		*pUV;

	/* Get model info */
	pObj->nNumberOfVertices		= Mesh[nObject].nNumVertex;
	pObj->nNumberOfTriangles	= Mesh[nObject].nNumFaces;
	pObj->nNumberOfStrips		= Mesh[nObject].nNumStrips;
	pObj->fCentreX				= Mesh[nObject].fCenter[0];
	pObj->fCentreY				= Mesh[nObject].fCenter[1];
	pObj->fCentreZ				= Mesh[nObject].fCenter[2];

	/* Vertices */
	pObj->pVertices=(float *)Mesh[nObject].pVertex;
	
	/* Normals */
	pObj->pNormals=(float *)Mesh[nObject].pNormals;
	
	/* Get triangle list data */
	pObj->pTriangleList=(WORD *)Mesh[nObject].pFaces;

	/* Get strips data */
	pObj->pStrips = (WORD *)Mesh[nObject].pStrips;
	pObj->pStripLength = (WORD *)Mesh[nObject].pStripLength;

	/* UVs */
	pUV = Mesh[nObject].pUV;


	/* TL Vertices */
	pObj->pTLVertices = (D3DTLVERTEX *) malloc (pObj->nNumberOfVertices * sizeof(D3DTLVERTEX));

	/* D3DVertices */
	pObj->pD3DVertices = (D3DVERTEX *) malloc (pObj->nNumberOfVertices * sizeof(D3DVERTEX));
	
	/* L Vertices */
	pObj->pLVertices = (D3DLVERTEX *) malloc (pObj->nNumberOfVertices * sizeof(D3DLVERTEX));


	/* Get vertex data */
	for (i=0;i<pObj->nNumberOfVertices;i++)
	{
		/* UV values */
		(pObj->pLVertices + i)->tu = (pObj->pD3DVertices + i)->tu = (pObj->pTLVertices + i)->tu= *(pUV+i*2+0);
		(pObj->pLVertices + i)->tv = (pObj->pD3DVertices + i)->tv = (pObj->pTLVertices + i)->tv= *(pUV+i*2+1);
		
		/* Duffuse color = white  Specular color = black */
		(pObj->pLVertices + i)->color    = (pObj->pTLVertices + i)->color    = RGBA_MAKE(255, 255, 255, 255);		
		(pObj->pLVertices + i)->specular = (pObj->pTLVertices + i)->specular = RGBA_MAKE(0, 0, 0, 0);			

		/* Fill Vertices */
		(pObj->pLVertices + i)->x = (pObj->pD3DVertices + i)->x = *(pObj->pVertices+i*3+0);
		(pObj->pLVertices + i)->y = (pObj->pD3DVertices + i)->y = *(pObj->pVertices+i*3+1);
		(pObj->pLVertices + i)->z = (pObj->pD3DVertices + i)->z = *(pObj->pVertices+i*3+2);

		(pObj->pD3DVertices + i)->nx = *(pObj->pNormals+i*3+0);
		(pObj->pD3DVertices + i)->ny = *(pObj->pNormals+i*3+1);
		(pObj->pD3DVertices + i)->nz = *(pObj->pNormals+i*3+2);

	}


}
/*******************************************************************************
 * Function Name  : TransformObject
 * Input		  : 
 * Returns        : 
 * Global Used    : 
 * Description    : For D3DVERTEX and D3DLVERTEX transformations are not 
 *                  performed until DrawIndexPrimitive() is called.
 *******************************************************************************/
void TransformObject (LPDIRECT3DDEVICE3 lpDev3, D3DMATRIX *pWorldMatrix, LPOBJECT pObject, BOOL bTrans, BOOL bShaded, int nMode)
{
D3DMATRIX View, Projection;

	if ((nMode==USE_D3DTLVERTEX  || nMode==USE_D3DLVERTEX) & bShaded) 
	{
		D3DTLightSmoothShade(pWorldMatrix,	pObject->nNumberOfVertices, 
									pObject->pNormals, 
									(nMode==USE_D3DTLVERTEX) ? pObject->pTLVertices : (D3DTLVERTEX *)pObject->pLVertices ,	
									&LightVector, RGBA_MAKE(255, 255, 255, 255));

	}

	if ((nMode==USE_D3DTLVERTEX) & bTrans ) 
	{
		D3DTTransTransformProjectZSlamPerspective(pWorldMatrix, 
									pObject->nNumberOfVertices, 
									pObject->pVertices, 
									pObject->pTLVertices,
									dwCurrentWidth, dwCurrentHeight,
									&CameraPosition, &CameraPointing, fCameraRoll,
									fFrontClippingPlane, 250000.0f, 50.0f*PI/180.0f, 0.0f);

	}

	if (nMode==USE_D3DVERTEX || nMode==USE_D3DLVERTEX)
	{
		D3DTTransCalculateVPMatrix(&View, &Projection,
								&CameraPosition, &CameraPointing, fCameraRoll,
								fFrontClippingPlane, 250000.0f, 50.0f*PI/180.0f, 0.0);
	

		lpDev3->lpVtbl->SetTransform(lpDev3, D3DTRANSFORMSTATE_WORLD,      pWorldMatrix);
		lpDev3->lpVtbl->SetTransform(lpDev3, D3DTRANSFORMSTATE_VIEW,       &View);
		lpDev3->lpVtbl->SetTransform(lpDev3, D3DTRANSFORMSTATE_PROJECTION, &Projection);
	}

}
/*******************************************************************************
 * Function Name  : RenderObjectTriangles
 * Input		  : 
 * Returns        : 
 * Global Used    : 
 * Description    : 
 *******************************************************************************/
void RenderObjectTriangles (LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DTEXTURE2 hTexture, LPOBJECT pObject, int nMode)
{

	lpDev3->lpVtbl->SetTexture(lpDev3, 0, hTexture);

	switch(nMode)
	{
	case USE_D3DVERTEX:	lpDev3->lpVtbl->DrawIndexedPrimitive(lpDev3, D3DPT_TRIANGLELIST,  
											D3DFVF_VERTEX,
											pObject->pD3DVertices, 
											pObject->nNumberOfVertices,
											pObject->pTriangleList,
											pObject->nNumberOfTriangles * 3,
											D3DDP_DONOTUPDATEEXTENTS);
							break;

	case USE_D3DLVERTEX:	lpDev3->lpVtbl->DrawIndexedPrimitive(lpDev3, D3DPT_TRIANGLELIST,  
											D3DFVF_LVERTEX,
											pObject->pLVertices, 
											pObject->nNumberOfVertices,
											pObject->pTriangleList,
											pObject->nNumberOfTriangles * 3,
											D3DDP_DONOTUPDATEEXTENTS);
							break;

	case USE_D3DTLVERTEX:	lpDev3->lpVtbl->DrawIndexedPrimitive(lpDev3, D3DPT_TRIANGLELIST,  
											D3DFVF_TLVERTEX,
											pObject->pTLVertices, 
											pObject->nNumberOfVertices,
											pObject->pTriangleList,
											pObject->nNumberOfTriangles * 3,
											D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);
							break;
	}


}
/*******************************************************************************
 * Function Name  : CreateWindows
 * Input		  : 
 * Returns        : 
 * Global Used    : 
 * Description    : Creation of all information windows.
 *******************************************************************************/
void CreateWindows (void)
{
	/* Info Window */
	InfoWin = D3DTPrint3DCreateWindow (50, 1);
	
	D3DTPrint3DSetWindow		(InfoWin, 0xFFA00000, 0xFFFFFFFF, 0.5f, 1.0f, 93.0f, 50.0f, 10.0f);
	D3DTPrint3DSetWindowFlags	(InfoWin, PRINT3D_ADJUST_SIZE_ALWAYS | PRINT3D_DEACTIVATE_TITLE );


	/* Text Windows */
	/* Window 0 */
	TWin[0] = D3DTPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, L"SIBERIAN Punchthrough ", NULL);


	/* Window 1 */
	TWin[1] = D3DTPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, L"SIBERIAN Punchthrough (1 of 2)", TEXT("\
Puchtrough is a special type of 'cut-out' polygon where the texture pixels are treated as either full translucent or full opaque.\n\n\
These polygons can be handled by the graphics processor more efficiently than 'autosorted' translucent polygons.\n\n"));



	/* Window 2 */
	TWin[2] = D3DTPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, L"SIBERIAN Punchthrough (2 of 2)",TEXT("\
Thanks to the 'Deferred Texturing' architecture of the PowerVR graphics chips, punchthrough polygons give a much higher \
fill-rate than the standard translucency.\n\n"));


}
/*******************************************************************************
 * Function Name  : CreateLight
 * Input		  : 
 * Returns        : 
 * Global Used    : 
 * Description    : 
 *******************************************************************************/
void CreateLight (LPDIRECT3D3 lpD3D3, LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DVIEWPORT3 lpView3)
{
D3DMATERIALHANDLE	hObjectMat=0;
LPDIRECT3DMATERIAL3 lpObjectMat=NULL;
D3DMATERIAL			ObjectMat;

	/* Create blank material */
	lpD3D3->lpVtbl->CreateMaterial(lpD3D3, &lpObjectMat, NULL);

	memset(&ObjectMat, 0, sizeof(D3DMATERIAL));
    ObjectMat.dwSize		= sizeof(D3DMATERIAL);
    ObjectMat.diffuse.r		= (D3DVALUE)1.0;
    ObjectMat.diffuse.g		= (D3DVALUE)1.0;
    ObjectMat.diffuse.b		= (D3DVALUE)1.0;
    ObjectMat.ambient.r		= (D3DVALUE)0.0;
    ObjectMat.ambient.g		= (D3DVALUE)0.0;
    ObjectMat.ambient.b		= (D3DVALUE)0.0;
    ObjectMat.specular.r	= (D3DVALUE)0.0;
    ObjectMat.specular.g	= (D3DVALUE)0.0;
    ObjectMat.specular.b	= (D3DVALUE)0.0;
    ObjectMat.power			= (float)1.0;
    lpObjectMat->lpVtbl->SetMaterial(lpObjectMat, &ObjectMat);
    lpObjectMat->lpVtbl->GetHandle(lpObjectMat, lpDev3, &hObjectMat);

	/* Create the light */
	memset(&light, 0, sizeof(D3DLIGHT2));
	light.dwSize			= sizeof(D3DLIGHT2);       
	light.dltType			= D3DLIGHT_DIRECTIONAL;
	light.dcvColor.r		= 1.0f;
	light.dcvColor.g		= 1.0f;
	light.dcvColor.b		= 1.0f;
	light.dcvColor.a		= 1.0f;
	light.dvDirection.x		= LightVector.x;
	light.dvDirection.y		= LightVector.y;
	light.dvDirection.z		= LightVector.z;
	light.dvAttenuation0	= (float)0.0;
    light.dvAttenuation1	= (float)0.0;
    light.dvAttenuation2	= (float)0.0;
	light.dwFlags			= D3DLIGHT_ACTIVE;

	lpD3D3->lpVtbl->CreateLight(lpD3D3, &lpD3DLight, NULL);
	lpD3DLight->lpVtbl->SetLight(lpD3DLight, (D3DLIGHT *)&light);
	lpView3->lpVtbl->AddLight(lpView3, lpD3DLight);

	/* Light states */
	lpDev3->lpVtbl->SetLightState(lpDev3, D3DLIGHTSTATE_MATERIAL, hObjectMat);
    lpDev3->lpVtbl->SetLightState(lpDev3, D3DLIGHTSTATE_AMBIENT, RGBA_MAKE(0, 0, 0, 255));
   
}

/*******************************************************************************
 * Function Name  : Background
 * Input		  : 
 * Returns        : 
 * Global Used    : 
 * Description    : 
 *******************************************************************************/
void Background (LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DTEXTURE2 TextureID)
{
D3DTLVERTEX Plane[4];
WORD pFaces[] = {0,1,2, 0,2,3};

     Plane[0].sx		= 0.0f;
	 Plane[0].sy		= 0.0f;
	 Plane[0].rhw		= 0.0001f;
	 Plane[0].sz		= 1.0f - 0.0001f;
	 Plane[0].color     = RGBA_MAKE (255, 255, 255, 255);
	 Plane[0].tu		= 0.0f;
     Plane[0].tv		= 1.0f;

	 Plane[1].sx		= (float)dwCurrentWidth;
	 Plane[1].sy		= 0.0f;
	 Plane[1].rhw		= 0.0001f;
	 Plane[1].sz		= 1.0f - 0.0001f;
	 Plane[1].color     = RGBA_MAKE (255, 255, 255, 255);
	 Plane[1].tu		= 1.0f;
     Plane[1].tv		= 1.0f;

	 Plane[2].sx		= (float)dwCurrentWidth;
	 Plane[2].sy		= (float)dwCurrentHeight;
	 Plane[2].rhw		= 0.0001f;
	 Plane[2].sz		= 1.0f - 0.0001f;
	 Plane[2].color     = RGBA_MAKE (255, 255, 255, 255);
	 Plane[2].tu		= 1.0f;
     Plane[2].tv		= 0.0f;

	 Plane[3].sx		= 0.0f;
	 Plane[3].sy		= (float)dwCurrentHeight;
	 Plane[3].rhw		= 0.0001f;
	 Plane[3].sz		= 1.0f - 0.0001f;
	 Plane[3].color     = RGBA_MAKE (255, 255, 255, 255);
	 Plane[3].tu		= 0.0f;
     Plane[3].tv		= 0.0f;

	 lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
	 lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND,  D3DBLEND_ONE);
     lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);

	 lpDev3->lpVtbl->SetTexture(lpDev3, 0, TextureID);

	 lpDev3->lpVtbl->DrawIndexedPrimitive(lpDev3, D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, 
										  Plane, 4,  pFaces, 6, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

}
/******************************************************************************
 *  Function Name   : LoadPunchthrough     
 *  Inputs          : 
 *  Outputs         :   
 *  Returns         :  
 *  Globals Used    : 
 *  Description     : This little function loads a 1555 texture that will be used 
 *                    as PUNCHTHROUGH polygons.
 ******************************************************************************/
void LoadPunchthrough (LPDIRECTDRAW4 lpDD4, LPDIRECT3DDEVICE3 lpDev3, TCHAR *ResourceName, TEXTURE *pTexture)
{
DDPIXELFORMAT PixelFormat;
TCHAR TransName[500];
	
	wsprintf ((unsigned short *)TransName, TEXT("t%s"), ResourceName);

	/* 1555 */
	memset(&PixelFormat, 0, sizeof(DDPIXELFORMAT));
	PixelFormat.dwSize				= sizeof(DDPIXELFORMAT);
	PixelFormat.dwFlags				= DDPF_RGB | DDPF_ALPHAPIXELS;
	PixelFormat.dwRGBBitCount		= 16;
	PixelFormat.dwRGBAlphaBitMask	= 0x00008000;
	PixelFormat.dwRBitMask			= 0x00007C00;
	PixelFormat.dwGBitMask			= 0x000003E0;
	PixelFormat.dwBBitMask			= 0x0000001F;

	/* MipMapped Punchtrough */
	D3DTTextureLoadBMP(lpDD4, lpDev3, ResourceName, TransName, FALSE, D3DTAutoMipmap_2by2,
						 &PixelFormat, TRUE, &pTexture->lpDDSTextureSurface, &pTexture->lpD3DTexture);

}
/*******************************************************************************
 *  Function Name   : ReorderTriangles
 *  Inputs          : 
 *  Returns         :       
 *  Globals Used    : 
 *  Description     : Reordering of the triangle list. Dragon drivers will convert
 *                    a set of ordered triangles to strips on the fly.
 ******************************************************************************/
void ReorderTriangles (int nNumStrips, WORD *pFaces, WORD *pStrips, WORD *pStripLengths)
{
register i, j;
int nPolysInStrip = 0, StripCounter = 0, FacesCounter = 0;
WORD a,b,c, d;

	for (i=0; i<nNumStrips; i++)
	{
		nPolysInStrip = (int)*(pStripLengths+i);

		a = *(pStrips + StripCounter++);
		b = *(pStrips + StripCounter++);
		c = *(pStrips + StripCounter++);

		*(pFaces + FacesCounter++) = a;
		*(pFaces + FacesCounter++) = b;
		*(pFaces + FacesCounter++) = c;

		for (j=0; j<nPolysInStrip-1; j++)
		{
			d = *(pStrips + StripCounter++);

			if ((j&1)==0)
			{
				a = b;
				b = d;
				c = c;
			}
			else
			{
				a = c;
				b = b;
				c = d;
			}

			*(pFaces + FacesCounter++) = a;
			*(pFaces + FacesCounter++) = b;
			*(pFaces + FacesCounter++) = c;
		}
	}

}
