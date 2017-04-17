/*****************************************************************************
  Name :	D3DKnot
  Author:	Carlos Sarria
  Date :	Jan 1999 (revision Aug 1999)
  
  Description: Translucent bump-mapping.

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

#define VERTEX_BUFFER_SIZE      0x1C0000 
#define POLYGON_BUFFER_SIZE     0x020000

// D3D Shell includes
#include "D3DShell.h"

// D3D Tools include
#include "D3DTools.h"	

// 3D Model
#include "D3DKnot.h"
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
D3DVECTOR			CameraPosition		= {0.0f, 0.0f, -170.0f};
D3DVECTOR			CameraPointing		= {0.0f, 0.0f, 6000.0f};
D3DVECTOR			LightVector			= { 1.0f, -1.0f, 1.0f};
float				fCameraRoll			= 0.0f;
HRESULT				hres;

D3DMATRIX			WorldMatrix;

TEXTURE			    D3DTexture[10];

OBJECT				D3DObject[10];
float				*pBumpCoords; /* This will point to the tangent-space data */

int 				nFrame=0;

BOOL				bPause = FALSE;

DWORD				dwDisplayWins = TRUE, dwResult = 0;

DWORD				InfoWin, TWin[10], dwCurrentWin=0;

float				fAng1 = 0.0f , fAng2 = 0.0f, fAng3 = 0.0f, fZ;
float				fLAng1 = -1.0 , fLAng2 = 1.0;

float				fDistance = 200.0f;

BOOL				bStart = TRUE;
int					nTypeVertex = 0;

float				fAngleOffset = 0.0f, fLightOffset = 0.0f;

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
void ReorderTriangles			(int nNumStrips, WORD *pFaces, WORD *pStrips, WORD *pStripLengths);
BOOL PadControl					(void);
void LegacyBlendModes		(LPDIRECT3DDEVICE3 lpDev3, DWORD nMode, BOOL bIsVertexAlpha);

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
 *					(VK_ESCAPE), as it is already used by the Shell.
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
								bPause = !bPause;
								break;

							case VK_UP:
								fDistance +=50.0f;
								break;

							case VK_DOWN:
								fDistance -=50.0f;
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
			bStart = !bStart;
		}
		Delay = 0;
	}

	/* UP */
	if (GetAnalogY()<64)
	{
		/* Light rotation */
		if (IsAKey()) 
		{
			fLAng1 -= 0.05f;

			LightVector.x = (float)cos(fLAng2) * (float)cos(fLAng1);
			LightVector.y = (float)cos(fLAng2) * (float)sin(fLAng1);
			LightVector.z = (float)sin(fLAng2);
		}
		else fAng2 -= 0.05f;
	}

	/* DOWN */
	if (GetAnalogY()>256-64)
	{
		/* Light rotation */
		if (IsAKey()) 
		{
			fLAng1 += 0.05f;

			LightVector.x = (float)cos(fLAng2) * (float)cos(fLAng1);
			LightVector.y = (float)cos(fLAng2) * (float)sin(fLAng1);
			LightVector.z = (float)sin(fLAng2);
		}
		else fAng2 += 0.05f;
		
	}

	/* LEFT */
	if (GetAnalogX()<64)
	{
		/* Light rotation */
		if (IsAKey()) 
		{
			fLAng2 -= 0.05f;

			LightVector.x = (float)cos(fLAng2) * (float)cos(fLAng1);
			LightVector.y = (float)cos(fLAng2) * (float)sin(fLAng1);
			LightVector.z = (float)sin(fLAng2);
		}
		else fAng1 += 0.05f;
	}

	/* RIGHT */
	if (GetAnalogX()>256-64)
	{
		/* Light rotation */
		if (IsAKey()) 
		{
			fLAng2 += 0.05f;

			LightVector.x = (float)cos(fLAng2) * (float)cos(fLAng1);
			LightVector.y = (float)cos(fLAng2) * (float)sin(fLAng1);
			LightVector.z = (float)sin(fLAng2);
		}
		else fAng1 -= 0.05f;
		
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
			if (dwCurrentWin==-1) dwCurrentWin = 3;
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
		/* Zoom in */
		if (fDistance>-40) fDistance -= 50.0f; 
		
	}

	/* RIGHT finger button */
	if (IsRFKey())
	{
		/* Zooom out */
		if (fDistance<250) fDistance += 50.0f;
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
	if(PadControl()==FALSE) return FALSE;

	if (bPause==FALSE && bStart==TRUE)
	{
		if ((nFrame%1000) < 300) fAngleOffset++;
		else 	 fLightOffset++;

		
		fLAng1 = (float)cos(fLightOffset/60.0f) * 1.0f;
		fLAng2 = (float)sin(fLightOffset/30.0f) * 1.0f;

		fAng1 = (float)cos(fAngleOffset/200.0f) * PI*2.0f;
		fAng2 = (float)sin(fAngleOffset/200.0f) * PI*2.0f;

		LightVector.x = fLAng2;
		LightVector.y = fLAng1;
		LightVector.z = 1.0f;
	}



	/* TRANSFORMATIONS */
	D3DTMatrixReset(&WorldMatrix);

	D3DTMatrixRotate(&WorldMatrix, 0.0f, fAng1, fAng2);
	D3DTMatrixTranslate (&WorldMatrix, 0.0f, 0.0f, fDistance);
	
	/* I have repited twice the same object just for clarity */
	/* In a standard app the same data can be reused for the bumpmap layer (changing the colors only)*/
	TransformObject(lpDev3, &WorldMatrix, &D3DObject[0], TRUE, FALSE, USE_D3DLVERTEX);
	TransformObject(lpDev3, &WorldMatrix, &D3DObject[1], TRUE, FALSE, USE_D3DLVERTEX);

	/* Calculation of smooth-shading and bump-map in one go */ 
	D3DTBumpShade (&WorldMatrix, D3DObject[0].nNumberOfVertices, pBumpCoords, D3DObject[0].pNormals,
					(D3DTLVERTEX *)D3DObject[1].pLVertices, (D3DTLVERTEX *)D3DObject[0].pLVertices,	
					LightVector, BUMP_METHOD_TRANSLUCENT);
	

	/* RENDER */
	
	/* Begin Scene */
	lpDev3->lpVtbl->BeginScene(lpDev3);

	/* Bumpmap translucent */
	LegacyBlendModes (lpDev3, D3DTBLEND_MODULATEALPHA, TRUE);
	lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_ADDRESS, 0);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SPECULARENABLE,	TRUE);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND,			D3DBLEND_SRCALPHA);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND,		D3DBLEND_INVSRCALPHA);

	RenderObjectTriangles (lpDev3, D3DTexture[1].lpD3DTexture, &D3DObject[1], USE_D3DLVERTEX);
	

	/* Base texture opaque */
	LegacyBlendModes (lpDev3, D3DTBLEND_MODULATEALPHA, FALSE);
	lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_ADDRESS, D3DTADDRESS_MIRROR);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SPECULARENABLE,	FALSE);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);

	RenderObjectTriangles (lpDev3, D3DTexture[0].lpD3DTexture, &D3DObject[0], USE_D3DLVERTEX);


	/* 
	 * Text windows.
	 * D3DTPrint3DDisplayAllWindows must be called just before EndScene.
	 */
	 if(dwDisplayWins)
	 {
		D3DTPrint3DDisplayWindow(TWin[dwCurrentWin]);
		D3DTPrint3DDisplayWindow(InfoWin);
	 }

	 D3DShellDCLogo (0xFF);

	if (bPause==TRUE) D3DTPrint3D (80.0f, 3.0f, 1.0f, (unsigned)0xFFFFFFFFF, TEXT("PAUSE"));

	/* End Scene */
    lpDev3->lpVtbl->EndScene(lpDev3);
 
	if (bPause==FALSE) nFrame++;

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
	D3DShellLoadBMP(TEXT("BMP_WOOD"), FALSE, &D3DTexture[0].lpD3DTexture);
	D3DTTextureLoadBumpmap(lpDev3, lpDD4, TEXT("BMP_BVL"), &(D3DTexture[1].lpDDSTextureSurface),
												&(D3DTexture[1].lpD3DTexture));

	/* Create directional light */
	CreateLight (lpD3D3, lpDev3, lpView3);

	/* General Render States */
	lpDev3->lpVtbl->SetTextureStageState (lpDev3, 0, D3DTSS_MINFILTER ,		D3DTFN_LINEAR);	
	lpDev3->lpVtbl->SetTextureStageState (lpDev3, 0, D3DTSS_MAGFILTER ,		D3DTFG_LINEAR);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DITHERENABLE,		TRUE);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ZENABLE,			TRUE);


	/* Initialise Meshes */
	ReorderTriangles (Mesh[0].nNumStrips, Mesh[0].pFaces, Mesh[0].pStrips, Mesh[0].pStripLength);
	CreateObjectFromHeaderFile(&D3DObject[0], 0); /* Opaque model */
	CreateObjectFromHeaderFile(&D3DObject[1], 0); /* The same for bump-mapping */

	/* memory array to hold the bump-map tangent space information */
	pBumpCoords = malloc (D3DObject[0].nNumberOfVertices * sizeof(float) * 6);

	/* Local coordinate system (tangent space) per vertex  (the information is stored in pBumpCoords) */
	D3DTBumpCalculateLocalCoords (pBumpCoords, BUMP_COORDS_ANYDIRECTION,
									Mesh[0].nNumVertex, Mesh[0].pVertex, Mesh[0].pNormals, Mesh[0].pUV,
									Mesh[0].nNumFaces, Mesh[0].pFaces);
	

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

	/* This fuction must be always in ReleaseView  */    
	D3DTPrint3DReleaseTextures();

	/* Free memory used by objects */
	free(D3DObject[0].pD3DVertices);
	free(D3DObject[0].pLVertices);
	free(D3DObject[0].pTLVertices);

	free(D3DObject[1].pD3DVertices);
	free(D3DObject[1].pLVertices);
	free(D3DObject[1].pTLVertices);

	free(pBumpCoords);

	/* Release textures */
	RELEASE(D3DTexture[1].lpDDSTextureSurface);
	RELEASE(D3DTexture[1].lpD3DTexture);

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
			(pObj->pLVertices + i)->tu = (pObj->pD3DVertices + i)->tu = (pObj->pTLVertices + i)->tu= *(pUV+i*2+0) * 18.0f;
			(pObj->pLVertices + i)->tv = (pObj->pD3DVertices + i)->tv = (pObj->pTLVertices + i)->tv= *(pUV+i*2+1) * 2.0f;
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
	InfoWin = D3DTPrint3DCreateWindow (50, 4);
	
	D3DTPrint3DSetWindow		(InfoWin, 0xFFA00000, 0xFFFFFFFF, 0.5f, 1.0f, 87.0f, 45.0f, 12.0f);
	D3DTPrint3DSetWindowFlags	(InfoWin, PRINT3D_DEACTIVATE_TITLE );
	D3DTPrint3DWindowOutput		(InfoWin, TEXT("(START) Rolling demo/Interactive.\n"));
	D3DTPrint3DWindowOutput		(InfoWin, TEXT("(A+CURSOR) To move light\n"));
	D3DTPrint3DWindowOutput		(InfoWin, TEXT("(CURSOR) To move object\n"));

	/* Text Windows */
	/* Window 0 */
	TWin[0] = D3DTPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, L"KNOT Bump-mapping  ", NULL);

	/* Window 1 */
	TWin[1] = D3DTPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, L"KNOT Bump-mapping (1 of 3)", TEXT("\
The bump mapping technique is based in a 2D map that stores \
information about the roughness of a surface. \
The render engine scans this map pixel by pixel and calculates the corresponding intensity value that will \
be applied on the texture underneath, creating high-definition shading over a flat surface.\n"));

	/* Window 2 */
	TWin[2] = D3DTPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, L"KNOT Bump-mapping (2 of 3)", TEXT("\
PowerVR Series2 technology uses a special bump map format that is \
optimised for its hardware.\n\
Instead of storing coloured pixels, a couple of polar co-ordinates are stored in each pixel. These co-ordinates \
(S and R) are the elevation and azimuth of the normal vector in each point of the texture surface. \
These values are packed together in a 16-bit format where 8 bits express r and 8 bits express s.\n"));

	/* Window 3 */
	TWin[3] = D3DTPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, L"KNOT Bump-mapping (3 of 3)", TEXT("\
Once you have mapped the texture onto your object, the light source vector \
has to be expressed in a local co-ordinate system for each vertex and passed to the hardware as the specular color of that vertex.\n"));

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

/********************************************************************************
 *  Function Name   : Background                
 *  Inputs          : 
 *  Outputs         :                
 *  Returns         :               
 *  Globals Used    : 
 *  Description     : 
 ******************************************************************************/
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
 * Function Name  : ReorderTriangles
 * Inputs		  : 
 * Global Used    : 
 * Description    : 
 * Note			  :	Reordering of the triangle list. Dragon drivers will convert
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