/*****************************************************************************
  Name :	D3DMaterials
  Author:	Carlos Sarria
  Date :	May 1999 (Updated Aug 99)
  
  Description: This demo shows a collection of 11 bump-map surfaces.
				(see D3DTools\D3DTBump.c)

  Copyright : 1999 by Imagination Technologies Limited. All rights reserved.
******************************************************************************/

/****************************************************************************
 ** INCLUDES                                                               **
 ****************************************************************************/
#include <windowsx.h>
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <d3d.h>

#define WCE_DEBUG(x) OutputDebugString((unsigned short *)x);

// D3D Shell includes
#include "D3DShell.h"	// D3D Shell include

// D3D Tools include
#include "D3DTools.h"	// D3D Tools include

// 3D Model
#include "D3DMaterials.h"

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
D3DVECTOR			CameraPosition		= {0.0f, 0.0f, -200.0f};
D3DVECTOR			CameraPointing		= {0.0f, 0.0f, 0.0f};
D3DVECTOR			LightDirection		= { 1.0f, -1.0f, 1.0f};
float				fCameraRoll			= 0.0f;
HRESULT				hres;

D3DMATRIX			WorldMatrix;

TEXTURE			    D3DTexture[100];

OBJECT				D3DObject[NUM_MESHES];
float				*pBumpCoords[NUM_MESHES]; /* This will point to the tangent-space data */


DWORD				dwCurrentWin= 0, dwDisplayWins = TRUE, InfoWin, TWin[10];

/* Generic data */
unsigned nFrame = 0, nCurrentTexture = 0, CreationMethod = 1, CurrentObject = 2, BumpMethod = 0;

/* Object angles */
float fAng1 = 0.0f , fAng2 = 0.0f, fAng3 = 0.0f;

/* Camera distance */
float fDist = 100.0f;

/* Light angle */
float fLAng1 = -0.5f, fLAng2 = 1.0f;

float BumpIntensity = 0.5f, BumpAmbient = 0.5f;

LPDIRECT3D3			lpGlobD3D3;

/* DX tranformations */
D3DLIGHT2			light;        // Structure defining the light
LPDIRECT3DLIGHT		lpD3DLight;   // Object pointer for the light

/****************************************************************************
 ** PROTOTYPES                                                             **
 ****************************************************************************/
void TransformObject		(LPDIRECT3DDEVICE3 lpDev3, D3DMATRIX *pWorldMatrix, LPOBJECT pObject, BOOL bTrans, BOOL bShaded, int nMode);
void RenderObjectTriangles  (LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DTEXTURE2	lpTexture, LPOBJECT pObject, int nMode);

void CreateWindows				(void);
void CreateObjectFromHeaderFile	(OBJECT *pObject, int nObject);

void CreateLight				(LPDIRECT3D3 lpD3D3, LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DVIEWPORT3 lpView3);
void Background					(LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DTEXTURE2 TextureID);

void ReorderTriangles (int nNumStrips, WORD *pFaces, WORD *pStrips, WORD *pStripLengths);

BOOL PadControl (void);

void InitMaterials (LPDIRECTDRAW4 lpDD4, LPDIRECT3DDEVICE3 lpDev3);

void LegacyBlendModes (LPDIRECT3DDEVICE3 lpDev3, DWORD nMode, BOOL bIsVertexAlpha);
/****************************************************************************
** InitApplication() is called by D3DShell to enable user to initialise	   **
** his/her application													   **
****************************************************************************/
void InitApplication(HINSTANCE hInstance, HWND hWindow, TCHAR *pszCommandLine)
{
	InitDirectInput(hWindow, hInstance);

	CreateWindows();
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
								if (dwCurrentWin==-1) dwCurrentWin = 3;
								break;

							case VK_RETURN:
							case VK_F2:
								dwCurrentWin++;
								if (dwCurrentWin==4) dwCurrentWin = 0;
								break;

							case VK_SPACE:
								break;

							case VK_UP:
								break;

							case VK_DOWN:
								break;

							case VK_F6:
								nCurrentTexture++; if(nCurrentTexture==10) nCurrentTexture=0; break;
							case VK_F5:
								BumpMethod++; if(BumpMethod==3) BumpMethod=0;break;
							case VK_F7:
								CurrentObject += 2; if(CurrentObject==6) CurrentObject = 0; break;
	
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
		return FALSE;
	}

	/* UP */
	if (GetAnalogY()<64)
	{
		/* Light rotation */
		if (IsAKey()) 
		{
			LightDirection.x = (float)cos(fLAng2) * (float)cos(fLAng1);
			LightDirection.y = (float)sin(fLAng1);
			LightDirection.z = (float)sin (fLAng2) * (float)cos(fLAng1);
			fLAng1 -= 0.02f;
		}
		else fAng2 += 0.05f;   
	}

	/* DOWN */
	if (GetAnalogY()>256-64)
	{
		/* Light rotation */
		if (IsAKey()) 
		{
			LightDirection.x = (float)cos(fLAng2) * (float)cos(fLAng1);
			LightDirection.y = (float)sin(fLAng1);
			LightDirection.z = (float)sin (fLAng2) * (float)cos(fLAng1);
			fLAng1 += 0.02f;
		}
		else fAng2 -= 0.05f;  
		
	}

	/* LEFT */
	if (GetAnalogX()<64)
	{
		/* Light rotation */
		if (IsAKey()) 
		{
			LightDirection.x = (float)cos(fLAng2) * (float)cos(fLAng1);
			LightDirection.y = (float)sin(fLAng1);
			LightDirection.z = (float)sin (fLAng2) * (float)cos(fLAng1);
			fLAng2 -= 0.02f;
		}
		
		else  fAng1  += 0.05f;
	}

	/* RIGHT */
	if (GetAnalogX()>256-64)
	{
		/* Light rotation */
		if (IsAKey()) 
		{
			LightDirection.x = (float)cos(fLAng2) * (float)cos(fLAng1);
			LightDirection.y = (float)sin(fLAng1);
			LightDirection.z = (float)sin (fLAng2) * (float)cos(fLAng1);
			fLAng2 += 0.02f;
		}
		
		else   fAng1  -= 0.05f;
	}

	/* UP X-PAD */
	if (IsUPKey())
	{
		if(Delay>2)
		{
			dwDisplayWins = !dwDisplayWins;
		}
		Delay = 0;
	}

	/* DOWN X-PAD*/
	if (IsDOWNKey())
	{
		if(Delay>2)
		{
			dwDisplayWins = !dwDisplayWins;
		}
		Delay = 0;
	}

	/* LEFT X-PAD*/
	if (IsLEFTKey())
	{
		if(Delay>2)
		{
			dwDisplayWins = TRUE;
			dwCurrentWin--;
			if (dwCurrentWin==-1) dwCurrentWin = 33;
		}
		Delay = 0;
	}

	/* RIGHT X-PAD*/
	if (IsRIGHTKey())
	{
		if(Delay>2)
		{
			dwDisplayWins = TRUE;
			dwCurrentWin++;
			if (dwCurrentWin==4) dwCurrentWin = 0;
		}
		Delay = 0;
	}


	/* A button */
	if (IsAKey())
	{
	}
	
	/* B button */
	if (IsBKey())
	{
		if (Delay>2) {nCurrentTexture++; if(nCurrentTexture==10) nCurrentTexture=0;}
		Delay = 0;
	}
		
	/* X button */
	if (IsXKey())
	{
		if (Delay>2) {BumpMethod++; if(BumpMethod==3) BumpMethod=0;}
		Delay = 0;
	}

	/* Y button */
	if (IsYKey())
	{
		if (Delay>2)
		{
			CurrentObject += 2; if(CurrentObject==6) CurrentObject = 0;
		}
		Delay = 0;
	}

	/* LEFT finger button */
	if (IsLFKey())
	{
		/* Zoom in */
		if (fDist>-40) fDist -= 10.0f; 
		
	}

	/* RIGHT finger button */
	if (IsRFKey())
	{
		/* Zooom out */
		if (fDist<250) fDist += 10.0f;
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
BOOL RenderScene(LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DVIEWPORT3 lpView3)
{
DWORD BumpmapObject;
TCHAR *Textures[] =	{L"WOOL", L"GOLF",L"LIZARD1",L"LIZARD2",L"SKIN",L"FIBER",L"EGYPT",L"BRICK",L"STONES",L"GOLD"};
TCHAR *Objects[]  =	{L"STAR", L"SPHERE",L"SLAB"};
TCHAR *BMethod[]  =	{L"STANDARD", L"TRANSLUCENT", L"HIGHLIGHT"};

  	if (PadControl()==FALSE) return FALSE;

	/* Begin Scene */
	lpDev3->lpVtbl->BeginScene(lpDev3);

	Background (lpDev3, D3DTexture[20].lpD3DTexture);

	/* CurrentObject is a standard object and CurrentObject+1 is the bumpmap object on top of the standard one.
	 * For this demo, both objects are appart for clarity, but the same object can be used twice. 
	 */
	BumpmapObject = CurrentObject + 1;

	D3DTMatrixReset	    (&WorldMatrix);
	D3DTMatrixRotate    (&WorldMatrix,  0.0f, fAng1, fAng2);
	D3DTMatrixTranslate (&WorldMatrix, 0.0f, 0.0f, fDist); 

	/* Transform bumpmap */
	TransformObject(lpDev3, &WorldMatrix, &D3DObject[CurrentObject], TRUE, FALSE, USE_D3DLVERTEX);

	
	D3DTBumpShade (&WorldMatrix, D3DObject[BumpmapObject].nNumberOfVertices, pBumpCoords[BumpmapObject], 
							D3DObject[BumpmapObject].pNormals,	(D3DTLVERTEX *)D3DObject[BumpmapObject].pLVertices, 
							(D3DTLVERTEX *)D3DObject[CurrentObject].pLVertices, LightDirection, BumpMethod);


	/* Render bumpmap */
	switch (BumpMethod)
	{
		case BUMP_METHOD_STANDARD:
		case BUMP_METHOD_HIGHLIGHT:
			LegacyBlendModes (lpDev3, D3DTBLEND_DECALALPHA, FALSE);
			lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SPECULARENABLE,	TRUE);
			lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
			lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);
			break;
		case BUMP_METHOD_TRANSLUCENT:
			LegacyBlendModes (lpDev3, D3DTBLEND_MODULATEALPHA, TRUE);
			lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SPECULARENABLE,	TRUE);
			lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
			lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
			lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
			break;
	}

	RenderObjectTriangles (lpDev3, D3DTexture[nCurrentTexture].lpD3DTexture, &D3DObject[BumpmapObject], USE_D3DLVERTEX);


	/* Transform base texture */
	TransformObject(lpDev3, &WorldMatrix, &D3DObject[BumpmapObject], TRUE, FALSE, USE_D3DLVERTEX);

	/* Render base texture  */
	switch (BumpMethod)
	{
		case BUMP_METHOD_STANDARD:
			LegacyBlendModes (lpDev3, D3DTBLEND_MODULATEALPHA, TRUE);
			lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SPECULARENABLE,	FALSE);
			lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
			lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND, D3DBLEND_DESTCOLOR);
			lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);
			break;
		case BUMP_METHOD_TRANSLUCENT:
			LegacyBlendModes (lpDev3, D3DTBLEND_MODULATEALPHA, FALSE);
			lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SPECULARENABLE,	FALSE);
			lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
			lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
			lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);
			break;
		case BUMP_METHOD_HIGHLIGHT:
			LegacyBlendModes (lpDev3, D3DTBLEND_MODULATEALPHA, TRUE);
			lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SPECULARENABLE,	FALSE);
			lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
			lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
			lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);
			break;
	}


	RenderObjectTriangles (lpDev3, D3DTexture[10+nCurrentTexture].lpD3DTexture, &D3DObject[CurrentObject], USE_D3DLVERTEX);


	/* Transform the light spot */
	D3DTMatrixReset	  (&WorldMatrix);
	D3DTMatrixTranslate (&WorldMatrix, -LightDirection.x * 120.0f, -LightDirection.y * 120.0f, fDist - LightDirection.z * 120.0f);  

	TransformObject(lpDev3, &WorldMatrix, &D3DObject[M_LIGHT], TRUE, FALSE, USE_D3DVERTEX);


	/* Render spot light */
	LegacyBlendModes (lpDev3, D3DTBLEND_MODULATEALPHA, TRUE);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SPECULARENABLE,	FALSE);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);

	RenderObjectTriangles (lpDev3, D3DTexture[21].lpD3DTexture, &D3DObject[M_LIGHT], USE_D3DVERTEX);

	
	/* 
	 * Text windows.
	 * D3DTPrint3DDisplayAllWindows must be called just before EndScene.
	 */
	 if(dwDisplayWins)
	 {
		D3DTPrint3DDisplayWindow(TWin[dwCurrentWin]);
		D3DTPrint3DDisplayWindow(InfoWin);
	 }
	 
	D3DTPrint3DClearWindowBuffer (InfoWin);
	D3DTPrint3DWindowOutput		(InfoWin, TEXT("(X/F5) Bump method: %s\n"), BMethod[BumpMethod]);
	D3DTPrint3DWindowOutput		(InfoWin, TEXT("(B/F6) Texture: %s\n"), Textures[nCurrentTexture]);
	D3DTPrint3DWindowOutput		(InfoWin, TEXT("(Y/F7) Object: %s\n"), Objects[CurrentObject>>1]);

	D3DShellDCLogo (0x80);

	/* End Scene */
    lpDev3->lpVtbl->EndScene(lpDev3);
 
	nFrame++;

	/* No problem occured */
	return TRUE;
}

/*******************************************************************************
 * Function Name  : InitView
 * Inputs		  : lpDD2, lpD3D3, lpDev3, lpView3, dwWidth, dwHeight
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
	InitMaterials (lpDD4, lpDev3);

	/* Create directional light */
	CreateLight (lpD3D3, lpDev3, lpView3);

	/* General Render States */
	lpDev3->lpVtbl->SetTextureStageState (lpDev3, 0, D3DTSS_MINFILTER ,		D3DTFN_LINEAR);	
	lpDev3->lpVtbl->SetTextureStageState (lpDev3, 0, D3DTSS_MAGFILTER ,		D3DTFG_LINEAR);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DITHERENABLE,		TRUE);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ZENABLE,			TRUE);


	/* Initialise Meshes */
	for (i=0; i<NUM_MESHES; i++)
	{
		ReorderTriangles (Mesh[i].nNumStrips, Mesh[i].pFaces, Mesh[i].pStrips, Mesh[i].pStripLength);
		CreateObjectFromHeaderFile(&D3DObject[i], i); 
	}

	/* Light direction */
	LightDirection.x = (float)cos(fLAng2);
	LightDirection.y = -0.5f;
	LightDirection.z = (float)sin (fLAng2);

	/* memory array to hold the bump-map tangent space information */
	pBumpCoords[M_STARBUMP] = malloc (D3DObject[M_STARBUMP].nNumberOfVertices * sizeof(float) * 6);
	pBumpCoords[M_SPHEREBUMP] = malloc (D3DObject[M_SPHEREBUMP].nNumberOfVertices * sizeof(float) * 6);
	pBumpCoords[M_BOXBUMP] = malloc (D3DObject[M_BOXBUMP].nNumberOfVertices * sizeof(float) * 6);

	/* Local coordinate system (tangent space) per vertex  (the information is stored in pBumpCoords) */
	D3DTBumpCalculateLocalCoords (pBumpCoords[M_STARBUMP], BUMP_COORDS_ANYDIRECTION,
									Mesh[M_STARBUMP].nNumVertex, Mesh[M_STARBUMP].pVertex, 
									Mesh[M_STARBUMP].pNormals,   Mesh[M_STARBUMP].pUV,
									Mesh[M_STARBUMP].nNumFaces,  Mesh[M_STARBUMP].pFaces);

	D3DTBumpCalculateLocalCoords (pBumpCoords[M_SPHEREBUMP], BUMP_COORDS_ANYDIRECTION,
									Mesh[M_SPHEREBUMP].nNumVertex, Mesh[M_SPHEREBUMP].pVertex, 
									Mesh[M_SPHEREBUMP].pNormals,   Mesh[M_SPHEREBUMP].pUV,
									Mesh[M_SPHEREBUMP].nNumFaces,  Mesh[M_SPHEREBUMP].pFaces);

	D3DTBumpCalculateLocalCoords (pBumpCoords[M_BOXBUMP], BUMP_COORDS_ANYDIRECTION,
									Mesh[M_BOXBUMP].nNumVertex, Mesh[M_BOXBUMP].pVertex, 
									Mesh[M_BOXBUMP].pNormals,   Mesh[M_BOXBUMP].pUV,
									Mesh[M_BOXBUMP].nNumFaces,  Mesh[M_BOXBUMP].pFaces);
	/* No problen occured */
	return TRUE;
}


/*******************************************************************************
 * Function Name  : ReleaseView
 * Input		  : lpView3
 * Returns        : Nothing
 * Global Used    : None
 * Description    : D3DShell passes the viewport variable to this function 
 *					so you can delete any lights you created previously 
 *******************************************************************************/
void ReleaseView(LPDIRECT3DVIEWPORT3 lpView3)
{
register i;

	/* This fuction must be always in ReleaseView  */    
	D3DTPrint3DReleaseTextures();

	/* Free memory used by objects */
	for (i=0; i<NUM_MESHES ; i++)
	{
		free(D3DObject[i].pD3DVertices);
		free(D3DObject[i].pLVertices);
		free(D3DObject[i].pTLVertices);
	}

	free(pBumpCoords[M_STARBUMP]);
	free(pBumpCoords[M_SPHEREBUMP]);
	free(pBumpCoords[M_BOXBUMP]);

	/* Release textures allocated with D3DTools */
	for (i=0; i<10; i++)
	{
		RELEASE(D3DTexture[i].lpDDSTextureSurface);
		RELEASE(D3DTexture[i].lpD3DTexture);
	}

	/* Release light */
	RELEASE(lpD3DLight);


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
		if (pUV != NULL)
		{
			if (nObject==M_BOXBUMP || nObject==M_BOX || nObject==M_LIGHT)
			{
				(pObj->pLVertices + i)->tu = (pObj->pD3DVertices + i)->tu = (pObj->pTLVertices + i)->tu= *(pUV+i*2+0);
				(pObj->pLVertices + i)->tv = (pObj->pD3DVertices + i)->tv = (pObj->pTLVertices + i)->tv= *(pUV+i*2+1);
			}
			else
			{
				(pObj->pLVertices + i)->tu = (pObj->pD3DVertices + i)->tu = (pObj->pTLVertices + i)->tu= *(pUV+i*2+0) * 4.0f;
				(pObj->pLVertices + i)->tv = (pObj->pD3DVertices + i)->tv = (pObj->pTLVertices + i)->tv= *(pUV+i*2+1) * 4.0f;
		
			}
		}
		else
		{
			(pObj->pLVertices + i)->tu = (pObj->pD3DVertices + i)->tu = (pObj->pTLVertices + i)->tu=0.0f;
			(pObj->pLVertices + i)->tv = (pObj->pD3DVertices + i)->tv = (pObj->pTLVertices + i)->tv=0.0f;
		}
		
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
									&LightDirection, RGBA_MAKE(255, 255, 255, 255));

	}

	if ((nMode==USE_D3DTLVERTEX) & bTrans ) 
	{
		D3DTTransTransformProjectZSlamPerspective(pWorldMatrix, 
									pObject->nNumberOfVertices, 
									pObject->pVertices, 
									pObject->pTLVertices,
									dwCurrentWidth, dwCurrentHeight,
									&CameraPosition, &CameraPointing, fCameraRoll,
									fFrontClippingPlane, 250000.0f, 50.0f*PI/180.0f, 0);

	}

	if (nMode==USE_D3DVERTEX || nMode==USE_D3DLVERTEX)
	{
		D3DTTransCalculateVPMatrix(&View, &Projection,
								&CameraPosition, &CameraPointing, fCameraRoll,
								fFrontClippingPlane, 250000.0f, 50.0f*PI/180.0f, 0);
	

		lpDev3->lpVtbl->SetTransform(lpDev3, D3DTRANSFORMSTATE_WORLD,      pWorldMatrix);
		lpDev3->lpVtbl->SetTransform(lpDev3, D3DTRANSFORMSTATE_VIEW,       &View);
		lpDev3->lpVtbl->SetTransform(lpDev3, D3DTRANSFORMSTATE_PROJECTION, &Projection);
	}

}
/*******************************************************************************
 * Function Name  : RenderObject
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
											D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);
							break;

	case USE_D3DLVERTEX:	lpDev3->lpVtbl->DrawIndexedPrimitive(lpDev3, D3DPT_TRIANGLELIST,  
											D3DFVF_LVERTEX,
											pObject->pLVertices, 
											pObject->nNumberOfVertices,
											pObject->pTriangleList,
											pObject->nNumberOfTriangles * 3,
											D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);
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
 * Description    : 
 *******************************************************************************/
void CreateWindows (void)
{
	/* Info Window */
	InfoWin = D3DTPrint3DCreateWindow (50, 3);
	
	D3DTPrint3DSetWindow		(InfoWin, 0x80A00000, 0xFFFFFFFF, 0.5f, 1.0f, 87.0f, 45.0f, 12.0f);
	D3DTPrint3DSetWindowFlags	(InfoWin, PRINT3D_DEACTIVATE_TITLE );
	D3DTPrint3DWindowOutput		(InfoWin, TEXT("(X/F5) Bump method: STANDARD\n"));
	D3DTPrint3DWindowOutput		(InfoWin, TEXT("(B/F6) Texture:  WOOD\n"));
	D3DTPrint3DWindowOutput		(InfoWin, TEXT("(Y/F7) Object: SPHERE"));

	/* Text Windows */
	/* Window 0 */
	TWin[0] = D3DTPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, L"MATERIALS Bump-mapping  ", NULL);

	/* Window 1 */
	TWin[1] = D3DTPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, L"MATERIALS Bump-mapping  (1 of 3)", TEXT("\
The bump-mapping technique is based in a 2D map that stores information about the roughness of a surface.\n\n\
 The render engine scans this map pixel by pixel and calculates the corresponding intensity value that will \
 be applied on the texture underneath, creating high-definition shading over a flat surface.\n\n"));

	/* Window 2 */
	TWin[2] = D3DTPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, L"MATERIALS Bump-mapping  (2 of 3)", TEXT("\
The standard method for blending bumpmap surfaces is to make \
the bumpmap surface opaque and to blend the base texture on top using as blend factors DESTCOLOR for the source \
and ZERO for the detination. \
Another combination that works really well is when the base texture is opaque and the bump map texture is translucent \
(SRCALPHA/INVSRCALPHA) with all the vertex colours set to 0. With this method you can change the strength of the bump map \
just changing the value in the alpha channel. Values around 0xA0 are best for the majority of applications.  \
K1 and K2 have been fixed to 0 and 128 (medium intesity).\n\n")); 

		/* Window 3 */
	TWin[3] = D3DTPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, L"MATERIALS Bump-mapping  (3 of 3)",TEXT("\
To get highlights on a bumpmap surface invert the K3 value (K3 = 255 -K3) \
and set K1 and K2 to 0. Blend the base texture on top of the opaque bumpmap layer using additive blending (ONE/ONE). \
This trick gives a very nice shiny effect. \n\
There is a problem: the few polygons that are right on the perpendicular to the light direction \
changes their shading very quickly. To avoid this problem the best solution is to 'burn' that conflictive \
zone with strong highlights in the base color of the bumpmap vertices.\n\n")); 

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
	light.dvDirection.x		= LightDirection.x;
	light.dvDirection.y		= LightDirection.y;
	light.dvDirection.z		= LightDirection.z;
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
	 Plane[0].rhw		= 0.001f;
	 Plane[0].sz		= 1.0f - 0.001f;
	 Plane[0].color     = RGBA_MAKE (255, 255, 255, 255);
	 Plane[0].tu		= 0.0f;
     Plane[0].tv		= 1.0f;

	 Plane[1].sx		= (float)dwCurrentWidth;
	 Plane[1].sy		= 0.0f;
	 Plane[1].rhw		= 0.001f;
	 Plane[1].sz		= 1.0f - 0.001f;
	 Plane[1].color     = RGBA_MAKE (255, 255, 255, 255);
	 Plane[1].tu		= 1.0f;
     Plane[1].tv		= 1.0f;

	 Plane[2].sx		= (float)dwCurrentWidth;
	 Plane[2].sy		= (float)dwCurrentHeight;
	 Plane[2].rhw		= 0.001f;
	 Plane[2].sz		= 1.0f - 0.001f;
	 Plane[2].color     = RGBA_MAKE (255, 255, 255, 255);
	 Plane[2].tu		= 1.0f;
     Plane[2].tv		= 0.0f;

	 Plane[3].sx		= 0.0f;
	 Plane[3].sy		= (float)dwCurrentHeight;
	 Plane[3].rhw		= 0.001f;
	 Plane[3].sz		= 1.0f - 0.001f;
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
/*******************************************************************************
 * Function Name  : InitMaterials
 * Input		  : 
 * Returns        : 
 * Global Used    : 
 * Description    : 
 *******************************************************************************/
void InitMaterials (LPDIRECTDRAW4 lpDD4, LPDIRECT3DDEVICE3 lpDev3)
{
	/* OPAQUE MATERIALS */
	D3DShellLoadBMP(TEXT("BMP_WOOL"), FALSE, &D3DTexture[10].lpD3DTexture);

	D3DShellLoadBMP(TEXT("BMP_LIZARD1"), FALSE, &D3DTexture[12].lpD3DTexture);

	D3DShellLoadBMP(TEXT("BMP_LIZARD2"), FALSE,	&D3DTexture[13].lpD3DTexture);

	D3DShellLoadBMP(TEXT("BMP_CRACKS"), FALSE, &D3DTexture[14].lpD3DTexture);

	D3DShellLoadBMP(TEXT("BMP_FIBER"), FALSE, &D3DTexture[15].lpD3DTexture);

	D3DShellLoadBMP(TEXT("BMP_EGYPT"), FALSE, &D3DTexture[16].lpD3DTexture);

	D3DShellLoadBMP(TEXT("BMP_BRICK"), FALSE, &D3DTexture[17].lpD3DTexture);

	D3DShellLoadBMP(TEXT("BMP_STONES"), FALSE, &D3DTexture[18].lpD3DTexture);

	D3DShellLoadBMP(TEXT("BMP_GOLD"), FALSE, &D3DTexture[19].lpD3DTexture);

	D3DShellLoadBMP(TEXT("BMP_BACK"), FALSE, &D3DTexture[20].lpD3DTexture);

    D3DShellLoadBMP(TEXT("BMP_LIGHT"), FALSE, &D3DTexture[21].lpD3DTexture);

	/* BUMP MATERIALS */

	D3DTTextureLoadBumpmap(lpDev3, lpDD4, TEXT("BMP_WOOLBUMP"), &(D3DTexture[0].lpDDSTextureSurface),
												&(D3DTexture[0].lpD3DTexture));

	D3DTTextureLoadBumpmap(lpDev3, lpDD4, TEXT("BMP_GOLFBUMP"), &(D3DTexture[1].lpDDSTextureSurface),
												&(D3DTexture[1].lpD3DTexture));

	D3DTTextureLoadBumpmap(lpDev3, lpDD4, TEXT("BMP_LIZARD1BUMP"), &(D3DTexture[2].lpDDSTextureSurface),
												&(D3DTexture[2].lpD3DTexture));
	
	D3DTTextureLoadBumpmap(lpDev3, lpDD4, TEXT("BMP_LIZARD2BUMP"), &(D3DTexture[3].lpDDSTextureSurface),
											&(D3DTexture[3].lpD3DTexture));

	D3DTTextureLoadBumpmap(lpDev3, lpDD4, TEXT("BMP_CRACKSBUMP"), &(D3DTexture[4].lpDDSTextureSurface),
												&(D3DTexture[4].lpD3DTexture));

	D3DTTextureLoadBumpmap(lpDev3, lpDD4, TEXT("BMP_FIBERBUMP"), &(D3DTexture[5].lpDDSTextureSurface),
												&(D3DTexture[5].lpD3DTexture));

	D3DTTextureLoadBumpmap(lpDev3, lpDD4, TEXT("BMP_EGYPTBUMP"), &(D3DTexture[6].lpDDSTextureSurface),
												&(D3DTexture[6].lpD3DTexture));

	D3DTTextureLoadBumpmap(lpDev3, lpDD4, TEXT("BMP_BRICKBUMP"), &(D3DTexture[7].lpDDSTextureSurface),
												&(D3DTexture[7].lpD3DTexture));

	D3DTTextureLoadBumpmap(lpDev3, lpDD4, TEXT("BMP_STONESBUMP"), &(D3DTexture[8].lpDDSTextureSurface),
												&(D3DTexture[8].lpD3DTexture));

	D3DTTextureLoadBumpmap(lpDev3, lpDD4, TEXT("BMP_GOLDBUMP"), &(D3DTexture[9].lpDDSTextureSurface),
												&(D3DTexture[9].lpD3DTexture));

}
/*******************************************************************************
 * Function Name  : ReorderTriangles
 * Input		  : 
 * Returns        : 
 * Global Used    : 
 * Description    : Reordering of the triangle list. Dragon drivers will convert
 *                    a set of ordered triangles to strips on the fly.
 *******************************************************************************/
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
/*******************************************************************************
 * Function Name  : LegacyBlendModes
 * Input		  : 
 * Returns        : 
 * Global Used    : 
 * Description    : Old blend modes in the new texture-stage fashion.
 *******************************************************************************/
void LegacyBlendModes (LPDIRECT3DDEVICE3 lpDev3, DWORD nMode, BOOL bIsVertexAlpha)
{
	lpDev3->lpVtbl->SetTextureStageState	(lpDev3, 1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	lpDev3->lpVtbl->SetTextureStageState	(lpDev3, 1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

	switch (nMode)
	{
	case D3DTBLEND_ADD: 
			lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_COLOROP, D3DTOP_ADD);
			lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE); 

			lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2); 
			lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
			break;
 
	case	D3DTBLEND_COPY:
	case	D3DTBLEND_DECAL: 
			lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
			lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
 
			lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
			lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
			break;
 
	case	D3DTBLEND_DECALALPHA:
			lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_COLOROP, D3DTOP_BLENDTEXTUREALPHA);
			lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

			lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2); 
			lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
			break;
 
	case	D3DTBLEND_MODULATE: 
		lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE); 
 
		if (bIsVertexAlpha)
		{
			lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1); 
			lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		}
		else
		{ 
			lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2); 
			lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
		} 
		break;

	case	D3DTBLEND_MODULATEALPHA:
		lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE); 

		lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE); 
		break;
	}
} 
