/*****************************************************************************
  Name :	D3DWheel
  Author:	Carlos Sarria
  Date :	May 1999 (Updated Aug 99)
  
  Description: This demo shows a 'realistic' use of bump-mapping.
				(see D3DTools\D3DTBump.c)

  Copyright : 1999 by VideoLogic Limited. All rights reserved.
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
#include <floatmathlib.h>

#define WCE_DEBUG(x) OutputDebugString(x);

// D3D Shell includes
#include "D3DShell.h"	// D3D Shell include

// D3D Tools include
#include "D3DTools.h"	// D3D Tools include

// 3D Model
#include "D3DWheel.h"

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
D3DVECTOR			CameraPosition		= {0.0f, 100.0f, -100.0f};
D3DVECTOR			CameraPointing		= {0.0f, 0.0f, 0.0f};
D3DVECTOR			LightDirection		= { 1.0f, -1.0f, 1.0f};
float				fCameraRoll			= 0.0f;
HRESULT				hres;

D3DMATRIX			WorldMatrix;

TEXTURE			    D3DTexture[NUM_MESHES];

OBJECT				D3DObject[NUM_MESHES];
float				*pBumpCoords[NUM_MESHES]; /* This will point to the tangent-space data */

int 				nFrame=0;
DWORD				dwCurrentWin= 0, dwDisplayWins = TRUE, InfoWin, TWin[10];

/* Wheel angles */
float fAng1 = 0.0f , fAng2 = -1.2f, fAng3 = 0.0f;

/* Camera distance */
float fDist = 75.0f;

/* Light angle */
float fLAng2 = -11.0f;

/* Wheel movement */
float fDistX, fDistY, fWheelCount=0, fSpeed = 1.0f, fSincro = 0.040f;

LPDIRECT3D3			lpGlobD3D3;

/* DX tranformations */
D3DLIGHT2			light;        // Structure defining the light
LPDIRECT3DLIGHT		lpD3DLight;   // Object pointer for the light
	
DWORD dwVertexBufferSize;
DWORD dwPolygonBufferSize;
/****************************************************************************
 ** PROTOTYPES                                                             **
 ****************************************************************************/
void TransformObject		(LPDIRECT3DDEVICE3 lpDev3, D3DMATRIX *pWorldMatrix, LPOBJECT pObject, BOOL bTrans, BOOL bShaded, int nMode);
void RenderObjectTriangles  (LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DTEXTURE2	lpTexture, LPOBJECT pObject, int nMode);

void CreateWindows				(void);
void CreateObjectFromHeaderFile	(OBJECT *pObject, int nObject);
void DestroyObject				(OBJECT *pObject);

void CreateLight				(LPDIRECT3D3 lpD3D3, LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DVIEWPORT3 lpView3);
void Background					(LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DTEXTURE2 TextureID);

BOOL SetDisplayValue			(LPCWSTR szName, DWORD dwValue, LPDWORD pdwOldValue);

void ReorderTriangles			(int nNumStrips, WORD *pFaces, WORD *pStrips, WORD *pStripLengths);

BOOL PadControl					(void);

void LoadTextures				(LPDIRECTDRAW4 lpDD4, LPDIRECT3DDEVICE3 lpDev3);

void CalculateGround			(void);

void LegacyBlendModes			(LPDIRECT3DDEVICE3 lpDev3, DWORD nMode, BOOL bIsVertexAlpha);
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
								if (dwCurrentWin==-1) dwCurrentWin = 1;
								break;

							case VK_RETURN:
								break;

							case VK_F2:
								dwCurrentWin++;
								if (dwCurrentWin==2) dwCurrentWin = 0;
								break;

							case VK_SPACE:
								break;

							case VK_UP:
								break;

							case VK_DOWN:
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
		if (Delay>10)
		{
			/* Reset values */
			fAng1 = 0.0f ; fAng2 = -1.2f; 
			fDist = 75.0f;
			fLAng2 = -11.0f;
			LightDirection.x = (float)cos(fLAng2);
			LightDirection.y = -0.5f;
			LightDirection.z = (float)sin (fLAng2);
		}
		Delay = 0;
	}

	/* UP */
	if (GetAnalogX()<64)
	{
	}

	/* DOWN */
	if (GetAnalogY()>256-64)
	{
	}

	/* LEFT */
	if (GetAnalogX()<64)
	{
		/* Light rotation */
		if (IsAKey()) 
		{
			LightDirection.x = (float)cos(fLAng2);
			LightDirection.y = -0.5f;
			LightDirection.z = (float)sin (fLAng2);
			fLAng2 -= 0.02f;
		}
		/* Wheel rotation */
		else  fAng2  += 0.05f;
	}

	/* RIGHT */
	if (GetAnalogX()>256-64)
	{
		/* Light rotation */
		if (IsAKey()) 
		{
			LightDirection.x = (float)cos(fLAng2);
			LightDirection.y = -0.5f;
			LightDirection.z = (float)sin (fLAng2);
			fLAng2 += 0.02f;
		}
		/* Wheel rotation */
		else   fAng2  -= 0.05f;
	}

	/* UP X-PAD*/
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
			if (dwCurrentWin==-1) dwCurrentWin = 1;
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
			if (dwCurrentWin==2) dwCurrentWin = 0;
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
		/* Zoom in */
		if (fDist>-40) fDist -= 10.0f;
	}
		
	/* X button */
	if (IsXKey())
	{
		return FALSE;
	}

	/* Y button */
	if (IsYKey())
	{
		/* Zooom out */
		if (fDist<250) fDist += 10.0f;
	}

	/* LEFT finger button */
	if (IsLFKey())
	{
		/* Wheel forward displacement */
		fAng1 += fSpeed * 0.1f;   
		fWheelCount+=0.2f;

		/* Ground displacement */
		fDistX += (float)sin(fAng2) * fSpeed * fSincro;
		fDistY += (float)cos(fAng2) * fSpeed * fSincro;

		if (fDistX> 10.0f) fDistX -= 10.0f;
		if (fDistY> 10.0f) fDistY -= 10.0f;

		CalculateGround ();
	}

	/* RIGHT finger button */
	if (IsRFKey())
	{
		/* Wheel backward displacement */
		fAng1 -= fSpeed * 0.1f;  
		fWheelCount-=0.2f;

		/* Ground displacement */
		fDistX -= (float)sin(fAng2) * fSpeed * fSincro;
		fDistY -= (float)cos(fAng2) * fSpeed * fSincro;

		if (fDistX< -10.0f) fDistX += 10.0f;
		if (fDistY< -10.0f) fDistY += 10.0f;
		
		CalculateGround ();
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
register i;
float BumpIntensity = 0.5f, BumpAmbient = 0.5f;

	if(PadControl()==FALSE) return FALSE;

	/* Wheel booble */
	fAng3 = (float)sin(fWheelCount) * 0.05f;

	/* Begin Scene */
	lpDev3->lpVtbl->BeginScene(lpDev3);

	for(i=0; i<NUM_MESHES; i++)
	{
	
		D3DTMatrixReset	(&WorldMatrix);

		/* Rotation */
		if(i!=M_GROUND && i!=M_GROUNDBUMP && i!=M_SUPPORT)	D3DTMatrixRotate   (&WorldMatrix,  fAng1, fAng2, fAng3);
		else if (i == M_SUPPORT) D3DTMatrixRotate   (&WorldMatrix,  0.0f, fAng2, 0.0f);

		/* Translation (Zoom) */
		D3DTMatrixTranslate (&WorldMatrix, 0.0f, -fDist, fDist);  
	
		if(i==M_RIM || i==M_SUPPORT)
		{
			TransformObject(lpDev3, &WorldMatrix, &D3DObject[i], TRUE, TRUE, USE_D3DTLVERTEX);
		}
		else TransformObject(lpDev3, &WorldMatrix, &D3DObject[i], TRUE, FALSE, USE_D3DTLVERTEX);
	
		/* Environment map */
		if (i==M_PLATES || i==M_RIM || i==M_SUPPORT)
		{
			/* Reduce displacement to avoid 'crazy' env-map and add a horizontal displacement*/
			WorldMatrix._41 = (fDistX+fDistY) * 0.2f; 
			WorldMatrix._42 = 0.00f; 
			WorldMatrix._43 = -5.00f;

			D3DTTransUVEnvMap (&WorldMatrix, D3DObject[i].nNumberOfVertices, D3DObject[i].pNormals, 
											 D3DObject[i].pTLVertices, &CameraPosition, &CameraPointing,
											fCameraRoll);
		}

		/* Calculation of smooth-shading and bump-map in one go */ 

		if (i==M_TIREBUMP)
		{
			D3DTBumpShade (&WorldMatrix, D3DObject[M_TIREBUMP].nNumberOfVertices, pBumpCoords[M_TIREBUMP], 
							D3DObject[M_TIREBUMP].pNormals,	D3DObject[M_TIREBUMP].pTLVertices, 
							D3DObject[M_TIRE].pTLVertices,	LightDirection, BUMP_METHOD_TRANSLUCENT);
		}
	
		if (i==M_PLATESBUMP)
		{
			D3DTBumpShade (&WorldMatrix, D3DObject[M_PLATESBUMP].nNumberOfVertices, pBumpCoords[M_PLATESBUMP], 
							D3DObject[M_PLATESBUMP].pNormals, D3DObject[M_PLATESBUMP].pTLVertices, 
							D3DObject[M_PLATES].pTLVertices, LightDirection, BUMP_METHOD_HIGHLIGHT);
		}

		if (i==M_GROUNDBUMP)
		{
			D3DTBumpShade (&WorldMatrix, D3DObject[M_GROUNDBUMP].nNumberOfVertices, pBumpCoords[M_GROUNDBUMP], 
							D3DObject[M_GROUNDBUMP].pNormals, D3DObject[M_GROUNDBUMP].pTLVertices, 
							NULL, LightDirection, BUMP_METHOD_STANDARD);
		}



		/* RENDER */
		/* Bumpmap */
		if (i==M_TIREBUMP || i==M_PLATESBUMP || i==M_GROUNDBUMP)
		{
			switch (i)
			{
				case M_TIREBUMP: /* Translucent  */
					LegacyBlendModes (lpDev3, D3DTBLEND_MODULATEALPHA, TRUE);
					lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SPECULARENABLE,	TRUE);
					lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
					lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
					lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
					break;

				case M_PLATESBUMP: /* Highlights */
				case M_GROUNDBUMP: /* Standard */
					LegacyBlendModes (lpDev3, D3DTBLEND_DECALALPHA, FALSE);
					lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SPECULARENABLE,	TRUE);
					lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
					lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
					lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);
					break;

			}
		RenderObjectTriangles (lpDev3, D3DTexture[i].lpD3DTexture, &D3DObject[i], USE_D3DTLVERTEX);
		}
	
		/* Base texture  */
		else if (i==M_TIRE || i==M_PLATES || i==M_GROUND)
		{
			switch (i)
			{
				case M_TIRE: /* Translucent  */
					LegacyBlendModes (lpDev3, D3DTBLEND_MODULATEALPHA, FALSE);
					lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SPECULARENABLE,	FALSE);
					lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
					lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
					lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);
					break;

				case M_GROUND: /* Standard */
					LegacyBlendModes (lpDev3, D3DTBLEND_MODULATEALPHA, TRUE);
					lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SPECULARENABLE,	FALSE);
					lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
					lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND, D3DBLEND_DESTCOLOR);
					lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);
					break;
				case M_PLATES: /* Highlight */
					LegacyBlendModes (lpDev3, D3DTBLEND_MODULATEALPHA, TRUE);
					lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SPECULARENABLE,	FALSE);
					lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
					lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
					lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);
					break;
			}

		RenderObjectTriangles (lpDev3, D3DTexture[i].lpD3DTexture, &D3DObject[i], USE_D3DTLVERTEX);
		}

		/* Rest of the word */
		else 
		{
			LegacyBlendModes (lpDev3, D3DTBLEND_MODULATEALPHA, FALSE);
			lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SPECULARENABLE,	FALSE);
			lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
		
			RenderObjectTriangles (lpDev3, D3DTexture[i].lpD3DTexture, &D3DObject[i], USE_D3DTLVERTEX);
		}
	} /* end of meshes loop */

	/* 
	 * Text windows.
	 * D3DTPrint3DDisplayAllWindows must be called just before EndScene.
	 */
	 if(dwDisplayWins)
	 {
		D3DTPrint3DDisplayWindow(TWin[dwCurrentWin]);
		D3DTPrint3DDisplayWindow(InfoWin);
	 }

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
	LoadTextures (lpDD4, lpDev3);

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

	/* Ground UVs */
	CalculateGround ();

	/* Light direction */
	LightDirection.x = (float)cos(fLAng2);
	LightDirection.y = -0.5f;
	LightDirection.z = (float)sin (fLAng2);

	/* memory array to hold the bump-map tangent space information */
	pBumpCoords[M_TIREBUMP] = malloc (D3DObject[M_TIREBUMP].nNumberOfVertices * sizeof(float) * 6);
	pBumpCoords[M_PLATESBUMP] = malloc (D3DObject[M_PLATESBUMP].nNumberOfVertices * sizeof(float) * 6);
	pBumpCoords[M_GROUNDBUMP] = malloc (D3DObject[M_GROUNDBUMP].nNumberOfVertices * sizeof(float) * 6);

	/* Local coordinate system (tangent space) per vertex  (the information is stored in pBumpCoords) */
	D3DTBumpCalculateLocalCoords (pBumpCoords[M_TIREBUMP], BUMP_COORDS_ANYDIRECTION,
									Mesh[M_TIREBUMP].nNumVertex, Mesh[M_TIREBUMP].pVertex, 
									Mesh[M_TIREBUMP].pNormals,   Mesh[M_TIREBUMP].pUV,
									Mesh[M_TIREBUMP].nNumFaces,  Mesh[M_TIREBUMP].pFaces);

	D3DTBumpCalculateLocalCoords (pBumpCoords[M_PLATESBUMP], BUMP_COORDS_ANYDIRECTION,
									Mesh[M_PLATESBUMP].nNumVertex, Mesh[M_PLATESBUMP].pVertex, 
									Mesh[M_PLATESBUMP].pNormals,   Mesh[M_PLATESBUMP].pUV,
									Mesh[M_PLATESBUMP].nNumFaces,  Mesh[M_PLATESBUMP].pFaces);

	D3DTBumpCalculateLocalCoords (pBumpCoords[M_GROUNDBUMP], BUMP_COORDS_ANYDIRECTION,
									Mesh[M_GROUNDBUMP].nNumVertex, Mesh[M_GROUNDBUMP].pVertex, 
									Mesh[M_GROUNDBUMP].pNormals,   Mesh[M_GROUNDBUMP].pUV,
									Mesh[M_GROUNDBUMP].nNumFaces,  Mesh[M_GROUNDBUMP].pFaces);


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
	for (i=0; i<NUM_MESHES ; i++)
	{
		free(D3DObject[i].pD3DVertices);
		free(D3DObject[i].pLVertices);
		free(D3DObject[i].pTLVertices);
	}

	free(pBumpCoords[M_TIREBUMP]);
	free(pBumpCoords[M_PLATESBUMP]);
	free(pBumpCoords[M_GROUNDBUMP]);

	/* Release textures allocated with D3DTools */
	RELEASE(D3DTexture[M_TIREBUMP].lpDDSTextureSurface);
	RELEASE(D3DTexture[M_TIREBUMP].lpD3DTexture);

	RELEASE(D3DTexture[M_PLATESBUMP].lpDDSTextureSurface);
	RELEASE(D3DTexture[M_PLATESBUMP].lpD3DTexture);

	RELEASE(D3DTexture[M_GROUNDBUMP].lpDDSTextureSurface);
	RELEASE(D3DTexture[M_GROUNDBUMP].lpD3DTexture);

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
			if(nObject==M_TIREBUMP || nObject==M_TIRE)
			{
				(pObj->pLVertices + i)->tu = (pObj->pD3DVertices + i)->tu = (pObj->pTLVertices + i)->tu= *(pUV+i*2+0) * 8.0f;
			}
			else
			{
				(pObj->pLVertices + i)->tu = (pObj->pD3DVertices + i)->tu = (pObj->pTLVertices + i)->tu= *(pUV+i*2+0);
			}
			(pObj->pLVertices + i)->tv = (pObj->pD3DVertices + i)->tv = (pObj->pTLVertices + i)->tv= *(pUV+i*2+1);
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
	D3DTPrint3DWindowOutput		(InfoWin, TEXT("(CURSOR, TRIGGERS) Move Wheel\n"));
	D3DTPrint3DWindowOutput		(InfoWin, TEXT("(A+CURSOR) Move Light\n"));
	D3DTPrint3DWindowOutput		(InfoWin, TEXT("(B,Y) Zoom"));

	/* Text Windows */
	/* Window 0 */
	TWin[0] = D3DTPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, L"WHEEL Bump-mapping  ", NULL);

	/* Window 1 */
	TWin[1] = D3DTPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, L"WHEEL Bump-mapping (1 of 1) ",TEXT("\
The bump-mapping technique is based in a 2D map that stores information about the roughness of a surface. \n\n\
The render engine scans this map pixel by pixel and calculates the corresponding intensity value that will \
be applied on the texture underneath, creating high-definition shading over a flat surface. \n\
This demos uses three different bump-mapping methods: standard for the ground, translucent for the tire and highlight for the logo on the wheel.\n\n"));

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
 * Function Name  : LoadTextures
 * Input		  : 
 * Returns        : 
 * Global Used    : 
 * Description    : 
 *******************************************************************************/
void LoadTextures (LPDIRECTDRAW4 lpDD4, LPDIRECT3DDEVICE3 lpDev3)
{
	/* OPAQUE MATERIALS */
	/* Environment map */
	D3DShellLoadBMP(TEXT("BMP_REFLECT"), FALSE, &D3DTexture[M_RIM].lpD3DTexture );
	D3DTexture[M_PLATES].lpD3DTexture = D3DTexture[M_RIM].lpD3DTexture;
	D3DTexture[M_SUPPORT].lpD3DTexture = D3DTexture[M_RIM].lpD3DTexture;

	/* Base texture for the wheel */
	D3DShellLoadBMP(TEXT("BMP_TIRE"), FALSE, &D3DTexture[M_TIRE].lpD3DTexture);

	/* Base texture for the ground */
	D3DShellLoadBMP(TEXT("BMP_GROUND"), FALSE, &D3DTexture[M_GROUND].lpD3DTexture);


	/* BUMP MATERIALS */
	/* Tire */
	D3DTTextureLoadBumpmap(lpDev3, lpDD4, TEXT("BMP_TIREBUMP"), &(D3DTexture[M_TIREBUMP].lpDDSTextureSurface),
												&(D3DTexture[M_TIREBUMP].lpD3DTexture));
	/* Logo */
	D3DTTextureLoadBumpmap(lpDev3, lpDD4, TEXT("BMP_LOGOBUMP"), &(D3DTexture[M_PLATESBUMP].lpDDSTextureSurface),
										&(D3DTexture[M_PLATESBUMP].lpD3DTexture));
	/* Ground */
	D3DTTextureLoadBumpmap(lpDev3, lpDD4, TEXT("BMP_GROUNDBUMP"), &(D3DTexture[M_GROUNDBUMP].lpDDSTextureSurface),
												&(D3DTexture[M_GROUNDBUMP].lpD3DTexture));

}
/*******************************************************************************
 * Function Name  : ReorderTriangles
 * Input		  : 
 * Returns        : 
 * Global Used    : 
 * Description    :  Reordering of the triangle list. Dragon drivers will convert
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
 * Function Name  : CalculateGround
 * Input		  : 
 * Returns        : 
 * Global Used    : 
 * Description    : Moves UVs of the ground to simulate that the ground is moving.
 *******************************************************************************/                                                             
 void CalculateGround (void)
{
	(D3DObject[M_GROUNDBUMP].pTLVertices+0)->tu = (D3DObject[M_GROUND].pTLVertices+0)->tu = 15.0f + fDistX; 
	(D3DObject[M_GROUNDBUMP].pTLVertices+0)->tv = (D3DObject[M_GROUND].pTLVertices+0)->tv = 15.0f + fDistY; 

	(D3DObject[M_GROUNDBUMP].pTLVertices+1)->tu = (D3DObject[M_GROUND].pTLVertices+1)->tu = 15.0f + fDistX; 
	(D3DObject[M_GROUNDBUMP].pTLVertices+1)->tv = (D3DObject[M_GROUND].pTLVertices+1)->tv =  0.0f + fDistY; 

	(D3DObject[M_GROUNDBUMP].pTLVertices+2)->tu = (D3DObject[M_GROUND].pTLVertices+2)->tu =  0.0f + fDistX; 
	(D3DObject[M_GROUNDBUMP].pTLVertices+2)->tv = (D3DObject[M_GROUND].pTLVertices+2)->tv =  0.0f + fDistY; 

	(D3DObject[M_GROUNDBUMP].pTLVertices+3)->tu = (D3DObject[M_GROUND].pTLVertices+3)->tu =  0.0f + fDistX; 
	(D3DObject[M_GROUNDBUMP].pTLVertices+3)->tv = (D3DObject[M_GROUND].pTLVertices+3)->tv = 15.0f + fDistY; 
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
