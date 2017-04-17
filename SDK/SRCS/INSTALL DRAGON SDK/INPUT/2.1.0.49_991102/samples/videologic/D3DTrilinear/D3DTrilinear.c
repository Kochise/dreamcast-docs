/*****************************************************************************
  Name :	D3DTrlinear
  Author:	Carlos Sarria
  Date :	Nov 1998
  
  Description: This demo shows how to use trilinear filtering.

  Copyright : 1998 by VideoLogic Limited. All rights reserved.
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


// D3D Shell includes
#include "D3DShell.h"	// D3D Shell include

// D3D Tools include
#include "D3DTools.h"	// D3D Tools include


// 3D Model
#include "D3DTrilinear.h"

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
	D3DVERTEX   *pD3DVertices;			/* No tranformed vertices (DX makes all transformations and lighting) */
	D3DLVERTEX  *pLVertices;			/* No tranformed vertices (DX makes transformations only) */
	D3DTLVERTEX	*pTLVertices;			/* Transformed vertices */
	WORD		*pStripLength;			/* Number of polygons per strip */
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

OBJECT				D3DObject[NUM_MESHES];

float				nFrame=0;

BOOL				bPause = FALSE, bShowMipmap = TRUE;

DWORD				dwDisplayWins = TRUE, nMode = 0;

DWORD				InfoWin, TWin[10], dwCurrentWin=0; /* Info windows */

float				fMipmapBias = 0.0f;
 
float				fXPos, fYPos, SphPos[2];

BOOL				bStart = FALSE;

BOOL				bShowBanners = TRUE;

LPDIRECT3D3			lpGlobD3D3;

/* DX tranformations */
D3DLIGHT2			light;        // Structure defining the light
LPDIRECT3DLIGHT		lpD3DLight;   // Object pointer for the light

/****************************************************************************
 ** PROTOTYPES                                                             **
 ****************************************************************************/
void TransformObject		(LPDIRECT3DDEVICE3 lpDev3, D3DMATRIX *pWorldMatrix, LPOBJECT pObject, BOOL bTrans, BOOL bShaded, int nMode);
void RenderObjectTriangles  (LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DTEXTURE2	lpTexture, LPOBJECT pObject, int nMode);
void CreateLight			(LPDIRECT3D3 lpD3D3, LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DVIEWPORT3 lpView3);
void CreateWindows				(void);
void CreateObjectFromHeaderFile	(OBJECT *pObject, int nObject);
BOOL PadControl					(void);

void LoadTextures				(LPDIRECTDRAW4 lpDD4, LPDIRECT3DDEVICE3 lpDev3);
void Background					(LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DTEXTURE2 TextureID);

void CalculateMovement		(int nType);

void ReorderTriangles		(int nNumStrips, WORD *pFaces, WORD *pStrips, WORD *pStripLengths);

void LegacyBlendModes		(LPDIRECT3DDEVICE3 lpDev3, DWORD nMode, BOOL bIsVertexAlpha);
/****************************************************************************
** InitApplication() is called by D3DShell to enable user to initialise	   **
** his/her application													   **
****************************************************************************/
void InitApplication(HINSTANCE hInstance, HWND hWindow, TCHAR *pszCommandLine)
{
	/* For the Dreamcast controller */
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
								if (dwCurrentWin==-1) dwCurrentWin = 2;
								break;

							case VK_RETURN:
							case VK_F2:
								dwCurrentWin++;
								if (dwCurrentWin==3) dwCurrentWin = 0;
								break;

							case VK_SPACE:
								bPause = !bPause;
								break;

							case VK_UP:
								if(fMipmapBias<2.9f) fMipmapBias += 0.1f;
								break;

							case VK_DOWN:
								if(fMipmapBias>-2.00f) fMipmapBias -= 0.1f;
								break;

							case VK_LEFT:
								nMode--; if (nMode==-1) nMode=2;
								break;

							case VK_RIGHT:
								nMode++; if (nMode==3) nMode=0;
								break;

						

							case VK_F3: 
								/* Minimise all windows */
								dwDisplayWins = !dwDisplayWins;
								break;


							case VK_F5:
								nMode++;
								if (nMode==3) nMode=0;
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
	}

	/* DOWN */
	if (IsDOWNKey() || GetAnalogY()>192)
	{

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
			nMode++;
			if (nMode==3) nMode=0;
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
BOOL RenderScene(LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DVIEWPORT3 lpView3)
{
D3DMATRIX Matrx;
register i, j;
DWORD dwFPS, dwFilterMode, dwTexMipmap;
TCHAR *Banners[] = {TEXT("MIPMAP"),TEXT("STANDARD"),TEXT("ANISOTROPIC")};

	if (PadControl()==FALSE) return FALSE; /* Finish the application */

	/* Begin Scene */
	lpDev3->lpVtbl->BeginScene(lpDev3);

	Background (lpDev3, D3DTexture[6].lpD3DTexture);
     
	for (j=0; j<2; j++)
	{   
        CalculateMovement (j);

		dwFilterMode = 1;
		if(j==0) dwFilterMode = 2 + nMode;

		if(dwFilterMode == 1 || dwFilterMode == 2) dwTexMipmap = 0;
		else									   dwTexMipmap = 3;

		for (i=0; i<NUM_MESHES;i++) 
		{
			/* 
			 * TRANSFORM 
			 */
			D3DTMatrixReset(&Matrx);

			if (i==M_SPHERE)
			{
				D3DTMatrixRotate(&Matrx, -nFrame/90.0f, -nFrame/30.0f, 0.0f);
	 			D3DTMatrixTranslate (&Matrx, 0.0f, SphPos[1] + 30.0f,  SphPos[0]);
			}
 
			if (i==M_BANNER2 || i==M_BANNER3 || i==M_BANNER1 || i==M_BANNER4) 
			{
				D3DTMatrixTranslate (&Matrx, 0.0f, SphPos[1] + 30.0f,  SphPos[0]);
			}

			/* Left */
			if (j==0)	D3DTMatrixTranslate (&Matrx, -50.0f, 0.0f, 0.0f);

			/* Right */
			if (j==1)	D3DTMatrixTranslate (&Matrx,  50.0f, 0.0f, 0.0f);
	
			TransformObject (lpDev3, &Matrx, &D3DObject[i], TRUE, FALSE, USE_D3DLVERTEX);


			/*
			 * RENDER
			 */
			 /* Mipmap Bias */
			 lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_MIPMAPLODBIAS, *((DWORD *)&fMipmapBias));
			
		
			 /* Trilinear */
			if (dwFilterMode==1)
			{
				lpDev3->lpVtbl->SetTextureStageState (lpDev3, 0, D3DTSS_MIPFILTER,		D3DTFP_LINEAR);
				lpDev3->lpVtbl->SetTextureStageState (lpDev3, 0, D3DTSS_MINFILTER ,		D3DTFN_LINEAR);	
				lpDev3->lpVtbl->SetTextureStageState (lpDev3, 0, D3DTSS_MAGFILTER ,		D3DTFG_LINEAR);
			}

			 /* Mipmap */
			if (dwFilterMode==2)
			{
				lpDev3->lpVtbl->SetTextureStageState (lpDev3, 0, D3DTSS_MIPFILTER,		D3DTFP_POINT);
				lpDev3->lpVtbl->SetTextureStageState (lpDev3, 0, D3DTSS_MINFILTER ,		D3DTFN_LINEAR);	
				lpDev3->lpVtbl->SetTextureStageState (lpDev3, 0, D3DTSS_MAGFILTER ,		D3DTFG_LINEAR);
			}

			/* No Mipmap */
			if (dwFilterMode==3) 
			{
				lpDev3->lpVtbl->SetTextureStageState (lpDev3, 0, D3DTSS_MIPFILTER,		D3DTFP_NONE);
				lpDev3->lpVtbl->SetTextureStageState (lpDev3, 0, D3DTSS_MINFILTER ,		D3DTFN_LINEAR);	
				lpDev3->lpVtbl->SetTextureStageState (lpDev3, 0, D3DTSS_MAGFILTER ,		D3DTFG_LINEAR);
			}

			/* Anisotropic */
			if (dwFilterMode==4) 
			{
				lpDev3->lpVtbl->SetTextureStageState (lpDev3, 0, D3DTSS_MINFILTER ,		D3DTFN_ANISOTROPIC);	
				lpDev3->lpVtbl->SetTextureStageState (lpDev3, 0, D3DTSS_MAGFILTER ,		D3DTFG_ANISOTROPIC);
			
			}
	
			if (i==M_SPHERE)
			{
				/* Translucent */
				LegacyBlendModes (lpDev3, D3DTBLEND_MODULATEALPHA, TRUE);
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND,  D3DBLEND_SRCALPHA );
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

				/* First backfaces to get the trans sphere sorted */
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_CULLMODE, D3DCULL_CW);
				RenderObjectTriangles (lpDev3, D3DTexture[i+dwTexMipmap].lpD3DTexture, &D3DObject[i], USE_D3DLVERTEX);

				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_CULLMODE, D3DCULL_CCW);
				RenderObjectTriangles (lpDev3, D3DTexture[i+dwTexMipmap].lpD3DTexture, &D3DObject[i], USE_D3DLVERTEX);

				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);
			}

			if (i==M_TAPE)
			{
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
				RenderObjectTriangles (lpDev3, D3DTexture[i+dwTexMipmap].lpD3DTexture, &D3DObject[i], USE_D3DLVERTEX);
			}
       
			if (bShowBanners)
			{
				/* Translucent */
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND,  D3DBLEND_SRCALPHA );
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

				
				/* Trilinear */
				if (dwFilterMode==1 && i==M_BANNER1) 
				{

					RenderObjectTriangles (lpDev3, D3DTexture[2].lpD3DTexture, &D3DObject[M_BANNER1], USE_D3DLVERTEX);
				}
	
				/* No mipmap */
				if (dwFilterMode==3 && i==M_BANNER2) 
				{
					RenderObjectTriangles (lpDev3, D3DTexture[5].lpD3DTexture, &D3DObject[M_BANNER2], USE_D3DLVERTEX);
				}

				/* Mipmap */
				if (dwFilterMode==2 && i==M_BANNER3)
				{
					RenderObjectTriangles (lpDev3, D3DTexture[2].lpD3DTexture, &D3DObject[M_BANNER3], USE_D3DLVERTEX);
				}

				/* Anisotropic */
				if (dwFilterMode==4 && i==M_BANNER4)
				{
					RenderObjectTriangles (lpDev3, D3DTexture[2].lpD3DTexture, &D3DObject[M_BANNER4], USE_D3DLVERTEX);
				}

			}

		} /* i loop */

   } /* j loop */

	 /* Restore Render states */
	 lpDev3->lpVtbl->SetTextureStageState (lpDev3, 0, D3DTSS_MIPFILTER,		D3DTFP_NONE);
	 lpDev3->lpVtbl->SetTextureStageState (lpDev3, 0, D3DTSS_MINFILTER ,	D3DTFN_LINEAR);	
	 lpDev3->lpVtbl->SetTextureStageState (lpDev3, 0, D3DTSS_MAGFILTER ,	D3DTFG_LINEAR);

   	/* 
	 * D3DTPrint3DDisplayAllWindows must be called just before EndScene.
	 */
	 if(dwDisplayWins)
	 {
		D3DTPrint3DDisplayWindow(TWin[dwCurrentWin]);
		D3DTPrint3DDisplayWindow(InfoWin);
	 }

	if (bPause==TRUE) D3DTPrint3D (80.0f, 3.0f, 1.0f, (unsigned)0xFFFFFFFFF, TEXT("PAUSE"));

	D3DShellDCLogo (0xA0);

	/* End Scene */
    lpDev3->lpVtbl->EndScene(lpDev3);
 
	D3DShellGetVariable(FRAME_RATE, &dwFPS);
	D3DTPrint3DWindowOutput (InfoWin, TEXT("(A/F5) - %s vs.TRILINEAR\n"),  Banners[nMode]);

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
	
	/* Load textures */
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

	RELEASE(lpD3DLight);

	/* Relesease textures created with D3DTools */
	for (i=0; i<6; i++)
	{
		RELEASE(D3DTexture[i].lpDDSTextureSurface);
		RELEASE(D3DTexture[i].lpD3DTexture);
	}

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
	light.dcvColor.a		= 0.0f;
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
 * Function Name  : CreateWindows
 * Input		  : 
 * Returns        : 
 * Global Used    : 
 * Description    : Information windows.
 *******************************************************************************/
void CreateWindows (void)
{
	/* Info Window */
	InfoWin = D3DTPrint3DCreateWindow (50, 1);
	
	D3DTPrint3DSetWindow		(InfoWin, 0xFFA00000, 0xFFFFFFFF, 0.5f, 1.0f, 93.0f, 50.0f, 10.0f);
	D3DTPrint3DSetWindowFlags	(InfoWin, PRINT3D_ADJUST_SIZE_ALWAYS | PRINT3D_DEACTIVATE_TITLE );

	/* Text Windows */
	/* Window 0 */
	TWin[0] = D3DTPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, L"TRILINEAR  ", NULL);
	
	/* Window 1 */
	TWin[1] = D3DTPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, L"TRILINEAR  (1 of 2)", TEXT("\
Trilinear is a special filter for mip-mapped textures.\n\n\
Every texel in a polygon is calculated as the linear interpolation between two mipmap levels.\n\n\
The texel color is a weighted blend between the color of that pixel in two adjacent mipmap levels based on the Z distance to them.\n"));

	/* Window 2 */
	TWin[2] = D3DTPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, L"TRILINEAR  (2 of 2)", TEXT("\
Trilinear filtering helps to avoid the otherwise visible boundary lines between different mipmap levels.\n\n\
However, this improvement in image quality carries a performance penalty as trilinear filtering requires an additional pass\n"));

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
DDPIXELFORMAT *PixelFormat;

	
	D3DTTextureListFormats(lpDev3);
	
	/*
     * BALL translucent texture  
     */
  	PixelFormat = D3DTTextureBestTranslucentFormat(TRUE);

	/* MipMap */
	D3DTTextureLoadBMP(lpDD4, lpDev3, TEXT("BMP_BALL"),TEXT("tBMP_BALL"), FALSE, D3DTAutoMipmap_2by2,
						 PixelFormat, TRUE, &D3DTexture[0].lpDDSTextureSurface, &D3DTexture[0].lpD3DTexture);


	/* No MipMap */
	D3DTTextureLoadBMP(lpDD4, lpDev3, TEXT("BMP_BALL"), TEXT("tBMP_BALL"), FALSE, FALSE,
						 PixelFormat, TRUE, &D3DTexture[3].lpDDSTextureSurface, &D3DTexture[3].lpD3DTexture);



	/* 
	 * TAPE opaque texture  
	 */
    PixelFormat = D3DTTextureBestOpaqueFormat(TRUE);

	/* MipMap */
	D3DTTextureLoadBMP(lpDD4, lpDev3, TEXT("BMP_TAPE"), NULL, FALSE, D3DTAutoMipmap_2by2,
						 PixelFormat, TRUE, &D3DTexture[1].lpDDSTextureSurface, &D3DTexture[1].lpD3DTexture);

	/* No MipMap */
	D3DTTextureLoadBMP(lpDD4, lpDev3, TEXT("BMP_TAPE"), NULL, FALSE, FALSE,
						 PixelFormat, TRUE, &D3DTexture[4].lpDDSTextureSurface, &D3DTexture[4].lpD3DTexture);



	
	/* 
	 * BANNER translucent texture  
	 */
	PixelFormat = D3DTTextureBestTranslucentFormat(TRUE);

	/* MipMap */
	D3DTTextureLoadBMP(lpDD4, lpDev3, TEXT("BMP_INFO"), TEXT("tBMP_INFO"), FALSE, D3DTAutoMipmap_2by2,
						 PixelFormat, TRUE, &D3DTexture[2].lpDDSTextureSurface, &D3DTexture[2].lpD3DTexture);

	/* No MipMap */
	D3DTTextureLoadBMP(lpDD4, lpDev3, TEXT("BMP_INFO"), TEXT("tBMP_INFO"), FALSE, FALSE,
						 PixelFormat, TRUE, &D3DTexture[5].lpDDSTextureSurface, &D3DTexture[5].lpD3DTexture);


	/*
     * BACK opaque texture  
     */
  	PixelFormat = D3DTTextureBestOpaqueFormat(TRUE);

	/* No MipMap */
	D3DTTextureLoadBMP(lpDD4, lpDev3, TEXT("BMP_BACK"), NULL, FALSE, FALSE,
						 PixelFormat, TRUE, &D3DTexture[6].lpDDSTextureSurface, &D3DTexture[6].lpD3DTexture);

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
/*******************************************************************************
 *  Function Name   : CalculateMovement                                                    
 *  Inputs          :                                                         
 *  Outputs         :                                                 
 *  Returns         :                                         
 *  Globals Used    :                                                                 
 *  Description     :              
 ********************************************************************************/
void CalculateMovement (int nType)
{
register i;
float fZPos, fOffset;

	fOffset = nFrame/20.0f;

	if (nType)
	{
		SphPos[0] = 400.0f * (float)sin(nFrame/100.0f) + 500.0f;
		SphPos[1] = (float)sin((SphPos[0]/100.0f + fOffset)) * 20.0f - 30.0f;
	}

	else
	{
		SphPos[0] = 320.0f * (float)sin(nFrame/100.0f) + 500.0f;
		SphPos[1] = (float)cos((SphPos[0]/100.0f + fOffset)) * 20.0f - 30.0f;
	}

	for (i=0; i<(int)Mesh[M_TAPE].nNumVertex; i++) 
	{
		fZPos = *(Mesh[M_TAPE].pVertex+ i*3 + 2); 

		if (nType)
			(D3DObject[M_TAPE].pLVertices + i)->y = (D3DObject[M_TAPE].pD3DVertices + i)->y = *(Mesh[M_TAPE].pVertex+ i*3 + 1) = (float)sin((fZPos/100.0f + fOffset)) * 20.0f - 30.0f;
		else
			(D3DObject[M_TAPE].pLVertices + i)->y = (D3DObject[M_TAPE].pD3DVertices + i)->y = *(Mesh[M_TAPE].pVertex+ i*3 + 1) = (float)cos((fZPos/100.0f + fOffset)) * 20.0f - 30.0f;
	}

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
