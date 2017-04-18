/*****************************************************************************
  Name :	D3DScanner
  Author:	Carlos Sarria
  Date :	Sept 1998 (Updated Aug 99)
  
  Description: This is a "generic modifier volume" demo.

  Copyright : 1999 by Imagination Technologies Limited. All rights reserved.
******************************************************************************/

/****************************************************************************
 ** INCLUDES                                                               **
 ****************************************************************************/
#include <windowsx.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <d3d.h>

// D3D Shell includes
#include "D3DShell.h"	// D3D Shell include

// D3D Tools include
#include "D3DTools.h"	// D3D Tools include


// 3D Model
#include "D3Dscanner.h"

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

#define ID_DINO2SKIN 11
/****************************************************************************
 ** GLOBALS                                                                **
 ****************************************************************************/

int					dwCurrentWidth, dwCurrentHeight;
float				fFrontClippingPlane = 30.0f;
D3DVECTOR			LightDirection		= { 1.0f, -1.0f, 1.0f};
D3DVECTOR			CameraPosition		= {0.0f, 0.0f, -100.0f};
D3DVECTOR			CameraPointing		= {0.0f, 0.0f, 6000.0f};
float				fCameraRoll			= 0.0f;
HRESULT				hres;

D3DMATRIX			WorldMatrix;

LPDIRECT3DTEXTURE2	lpTexture[256];

OBJECT				D3DObject[NUM_MESHES], TransDinoSkin;

int					nFrame = 0;

DWORD				dwDisplayWins = 1;
BOOL				bPause = FALSE, bUserControl = FALSE;
float				fAngleMachine = PI/2, fAngleScanner = 0.0f;

DWORD				InfoWin, TWin[10], dwCurrentWin=0; /* Info windows */

/* DX tranformations */
D3DLIGHT2			light;        // Structure defining the light
LPDIRECT3DLIGHT		lpD3DLight;   // Object pointer for the light

/****************************************************************************
 ** PROTOTYPES                                                             **
 ****************************************************************************/

void CreateObjectFromHeaderFile	(OBJECT *pObj, int nObject);
void RenderObjectTriangles		(LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DTEXTURE2 hTexture, LPOBJECT pObject, int nMode);
void TransformObject			(LPDIRECT3DDEVICE3 lpDev3, D3DMATRIX *pWorldMatrix, LPOBJECT pObject, BOOL bTrans, BOOL bShaded, int nMode);
void CreateLight				(LPDIRECT3D3 lpD3D3, LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DVIEWPORT3 lpView3);
void Background					(LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DTEXTURE2 TextureID);
void CreateWindows				(void);
void ReorderTriangles			(int nNumStrips, WORD *pFaces, WORD *pStrips, WORD *pStripLengths);
void LegacyBlendModes			(LPDIRECT3DDEVICE3 lpDev3, DWORD nMode, BOOL bIsVertexAlpha);
void SetModifiedTexStages		(LPDIRECT3DDEVICE3 lpDev3);

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
	case WM_COMMAND:	switch(GET_WM_COMMAND_ID(wParam,lParam))
						{
						}
						break;
	
	case WM_KEYDOWN:	switch(wParam)
						{
							case VK_F1:
								dwCurrentWin--;
								if (dwCurrentWin==-1) dwCurrentWin = 3;
								break;

							case VK_SPACE:
								bPause = !bPause;
								break;

							case VK_RETURN:
							case VK_F2:
								dwCurrentWin++;
								if (dwCurrentWin==4) dwCurrentWin = 0;
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
			bUserControl = !bUserControl;
		}
		Delay = 0;
	}

	/* UP */
	if (GetAnalogY()<64)
	{
		fAngleScanner -= PI/50.0f;   
	}

	/* DOWN */
	if (GetAnalogY()>256-64)
	{
		fAngleScanner += PI/50.0f; 
		
	}

	/* LEFT */
	if (GetAnalogX()<64)
	{
		fAngleMachine += PI/50.0f;
	}

	/* RIGHT */
	if (GetAnalogX()>256-64)
	{
		fAngleMachine -= PI/50.0f;
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
int i;

		if(PadControl()==FALSE) return FALSE; 

		/* Begin Scene */
	    lpDev3->lpVtbl->BeginScene(lpDev3);

		Background (lpDev3, lpTexture[10]);

		
		if (!bPause && !bUserControl) 
		{
			fAngleMachine += PI/500.0f;
			fAngleScanner += PI/100.0f;
		}
   
		for (i=0; i<NUM_MESHES;i++)
		{
	  
			D3DTMatrixReset(&WorldMatrix);

			/* Special rotation for the torus */
			if (i==M_SCANNER)
			{
				D3DTMatrixRotate	(&WorldMatrix, fAngleScanner, 0.0f, 0.0f);
				D3DTMatrixTranslate (&WorldMatrix, 0.0f, 0.0f, 100.0f * (float)(sin(fAngleScanner)));
			}

			D3DTMatrixRotate	(&WorldMatrix, 0.0f, 0.0f, -PI*0.02f);
			D3DTMatrixRotate	(&WorldMatrix, 0.0f, fAngleMachine, 0.0f);
			D3DTMatrixTranslate (&WorldMatrix, 0.0f, 0.0f, 110.0f); 
		
			/* No lighting on some objects  */
			if(i==M_BONES || i==M_SCANNER || i==M_LOGO || i==M_SURFACE01)
			{
				TransformObject(lpDev3, &WorldMatrix, &D3DObject[i], TRUE, FALSE, USE_D3DLVERTEX);

			}
			else
			{
				TransformObject(lpDev3, &WorldMatrix, &D3DObject[i], TRUE, TRUE, USE_D3DLVERTEX);
			}

			/* Torus: both standard object and modifier volume. */
			if (i==M_SCANNER)
			{
				/* As standard translucent object */
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_CULLMODE, D3DCULL_CCW );
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND,  D3DBLEND_SRCALPHA);
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
				RenderObjectTriangles (lpDev3, lpTexture[i], &D3DObject[i], USE_D3DLVERTEX);

				/* As Modifier Volume (has to be translucent) */
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_FILLMODE, D3DFILL_INCLUDE);
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_CULLMODE, D3DCULL_NONE );
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);

				RenderObjectTriangles (lpDev3, lpTexture[i], &D3DObject[i], USE_D3DLVERTEX);

				/* Revert to solid-fill mode */
				lpDev3->lpVtbl->SetRenderState(lpDev3,D3DRENDERSTATE_FILLMODE, D3DFILL_SOLID);
			}

			/* Modified object (Dinosaur with two skins) 
			 * The skins are translucent, and share the same UVs so no flexible vertex format is needed.
			 * The translucency comes fron the texture (4444 format) so DECAL is used as blend mode.
			 * (See SetModifiedTexStages() function)
			 */
			else if (i==M_DINOSKIN)
			{
				SetModifiedTexStages(lpDev3); 
			
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND,  D3DBLEND_SRCALPHA);
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

				
				lpDev3->lpVtbl->SetTexture(lpDev3, 1, lpTexture[ID_DINO2SKIN]); /* Second texture (stage 1)*/

				/* Enable Modified Volumes */
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_VOLUMEENABLE, TRUE);
				
				RenderObjectTriangles (lpDev3, lpTexture[i], &D3DObject[i], USE_D3DLVERTEX); /* First texture (stage 0) */
			
				/* Disable Modified Volumes */
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_VOLUMEENABLE, FALSE);
				LegacyBlendModes (lpDev3, D3DTBLEND_MODULATEALPHA, TRUE);
			}

			/* The rest is standard opaque without culling. */
			else
			{
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_CULLMODE,   D3DCULL_NONE );
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND,  D3DBLEND_ONE);
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);

				RenderObjectTriangles (lpDev3, lpTexture[i], &D3DObject[i], USE_D3DLVERTEX);
			}
		
		}


	/* 
	* D3DTPrint3DDisplayAllWindows must be called just before EndScene.
	*/
	if(dwDisplayWins)
	{
		D3DTPrint3DDisplayWindow(TWin[dwCurrentWin]);
	}

	D3DShellDCLogo (0x80);

	/* End Scene */
    lpDev3->lpVtbl->EndScene(lpDev3);
 
	
	if (bPause==FALSE) nFrame++;
    

	/* No problem occured */
	return TRUE;

}

/*******************************************************************************
 * Function Name  : InitView
 * Inputs		  : lpDD2, lpD3D2, lpDev3, lpView2, dwWidth, dwHeight
 * Returns        : TRUE on success
 * Global Used    : None
 * Description    : Application's viewport initialisation function
 *					Create execute buffers, materials, etc...
 *******************************************************************************/
BOOL InitView(LPDIRECTDRAW4 lpDD4, LPDIRECT3D3 lpD3D3, LPDIRECT3DDEVICE3 lpDev3,
              LPDIRECT3DVIEWPORT3 lpView3, DWORD dwWidth, DWORD dwHeight)
{
register i;

     /* This fuction must be always in InitView  */    
	 D3DTPrint3DSetTextures(lpDev3, lpDD4, dwWidth, dwHeight);

    
	 /* Update viewport size variables */
	dwCurrentWidth=dwWidth;
	dwCurrentHeight=dwHeight;
		
	/* Assign the background colour to be black.
	   This is needed to assign a colour to the viewport */
	D3DTMiscSetBackgroundColor(lpD3D3, lpDev3, lpView3, RGB_MAKE(0, 0, 0));
	
	/* Load textures */
	D3DShellLoadBMP(L"ID_BACK",		FALSE,	&lpTexture[10]);
	D3DShellLoadBMP(L"ID_BONES",	FALSE,	&lpTexture[M_BONES]);
	D3DShellLoadBMP(L"ID_DINO",		FALSE,	&lpTexture[M_DINOSKIN]);
	D3DShellLoadBMP(L"ID_SCANNER",	FALSE,	&lpTexture[M_SCANNER]);
	D3DShellLoadBMP(L"ID_SURFACE",	FALSE,	&lpTexture[M_SURFACE]);
	D3DShellLoadBMP(L"ID_VIDEOL",    FALSE,	&lpTexture[M_LOGO]);
	lpTexture[M_COLLAR]     = lpTexture[M_SURFACE];
	lpTexture[M_SURFACE01]  = lpTexture[M_SCANNER];
	D3DShellLoadBMP(L"ID_BONES",	TRUE,	&lpTexture[ID_DINO2SKIN]);

	/* General Render States */
	lpDev3->lpVtbl->SetTextureStageState (lpDev3, 0, D3DTSS_MINFILTER ,		D3DTFN_LINEAR);	
	lpDev3->lpVtbl->SetTextureStageState (lpDev3, 0, D3DTSS_MAGFILTER ,		D3DTFG_LINEAR);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DITHERENABLE,		TRUE);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ZENABLE,			TRUE);

	/* Create directional light */
	CreateLight (lpD3D3, lpDev3, lpView3);

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
 * Input		  : lpView2
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

	RELEASE(lpD3DLight);

	/* Free memory used by objects */
	for (i=0; i<NUM_MESHES; i++)
	{
		free(D3DObject[i].pTLVertices);
	}


    /* Nothing to release (textures created with the D3DShell
	   function D3DShellLoadBMP are automatically released) */
}

/*******************************************************************************
 * Function Name  : CreateObjectFromHeaderFile
 * Input/Output	  : *pObject
 * Global Used    : None
 * Description    : Function to initialise object from a .h file
 *                  The three different vertex modes are initialised only for an 
 *                  educational purpose.
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
			(pObj->pLVertices + i)->tu = (pObj->pD3DVertices + i)->tu = (pObj->pTLVertices + i)->tu= *(pUV+i*2+0);
			(pObj->pLVertices + i)->tv = (pObj->pD3DVertices + i)->tv = (pObj->pTLVertices + i)->tv= *(pUV+i*2+1);
		}
		else
		{
			(pObj->pLVertices + i)->tu = (pObj->pD3DVertices + i)->tu = (pObj->pTLVertices + i)->tu=0.0f;
			(pObj->pLVertices + i)->tv = (pObj->pD3DVertices + i)->tv = (pObj->pTLVertices + i)->tv=0.0f;
		}
		
		/* Duffuse color = white  Specular color = black */
		(pObj->pLVertices + i)->color    = (pObj->pTLVertices + i)->color    = RGBA_MAKE(255, 255, 255, 180);		
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
											D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);
							break;

	case USE_D3DLVERTEX:	lpDev3->lpVtbl->DrawIndexedPrimitive(lpDev3, D3DPT_TRIANGLELIST,  
											D3DFVF_LVERTEX,
											pObject->pLVertices, 
											pObject->nNumberOfVertices,
											pObject->pTriangleList,
											pObject->nNumberOfTriangles * 3,
											D3DDP_DONOTUPDATEEXTENTS  | D3DDP_DONOTCLIP);
							break;

	case USE_D3DTLVERTEX:	lpDev3->lpVtbl->DrawIndexedPrimitive(lpDev3, D3DPT_TRIANGLELIST,  
											D3DFVF_TLVERTEX,
											pObject->pTLVertices, 
											pObject->nNumberOfVertices,
											pObject->pTriangleList,
											pObject->nNumberOfTriangles * 3,
											D3DDP_DONOTUPDATEEXTENTS  | D3DDP_DONOTCLIP);
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
 * Function Name  : CreateWindows
 * Input		  : 
 * Returns        : 
 * Global Used    : 
 * Description    : 
 *******************************************************************************/
void CreateWindows (void)
{

	/* Text Windows */
	/* Window 0 */
	TWin[0] = D3DTPrint3DCreateDefaultWindow (1.0f, 1.0f, 150, L"D3DSCANNER - Modifier Volume  ", NULL);

	/* Window 1 */
		TWin[1] = D3DTPrint3DCreateDefaultWindow (1.0f, 1.0f, 50, L"D3DSCANNER - Modifier Volume (1 of 3)",TEXT("\
This demo demonstrates the use of PowerSGL Direct2 modifier volumes. \n\n\
(START) Rolling demo/Interactive\n (ANALOG PAD) Move scanner.\n\n"));

	/* Window 2 */
		TWin[2] = D3DTPrint3DCreateDefaultWindow (1.0f, 1.0f, 50, L"D3DSCANNER - Modifier Volume (2 of 3)",TEXT("\
Modifier volumes perform real 3D clipping allowing the attributes of any objects contained in the volumes to be changed.\n\n"));

	/* Window 3 */
		TWin[3] = D3DTPrint3DCreateDefaultWindow (1.0f, 1.0f, 50, L"D3DSCANNER - Modifier Volume (3 of 3)",TEXT("\
In this case the torus object also defines a modifier volume which is used to draw the dinosaur skin using \
two different textures.\n\n"));


}

/*******************************************************************************
 * Function Name  : ReorderTriangles
 * Input		  : 
 * Returns        : 
 * Global Used    : 
 *  Description   : Reordering of the triangle list. Dragon drivers will convert
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
/*******************************************************************************
 * Function Name  : SetModifiedTexStages
 * Input		  : 
 * Returns        : 
 * Global Used    : 
 * Description    : Decal (translucency comes from the texture)
 *******************************************************************************/
void SetModifiedTexStages (LPDIRECT3DDEVICE3 lpDev3)
{
    lpDev3->lpVtbl->SetTextureStageState(lpDev3,0, D3DTSS_COLOROP, D3DTOP_MODULATE);
    lpDev3->lpVtbl->SetTextureStageState(lpDev3,0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	lpDev3->lpVtbl->SetTextureStageState(lpDev3,0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
    lpDev3->lpVtbl->SetTextureStageState(lpDev3,0, D3DTSS_TEXCOORDINDEX, 0);

    lpDev3->lpVtbl->SetTextureStageState(lpDev3,1, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
    lpDev3->lpVtbl->SetTextureStageState(lpDev3,1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    lpDev3->lpVtbl->SetTextureStageState(lpDev3,1, D3DTSS_TEXCOORDINDEX, 0);

    lpDev3->lpVtbl->SetTextureStageState(lpDev3,2, D3DTSS_COLOROP, D3DTOP_DISABLE);

    lpDev3->lpVtbl->SetTextureStageState(lpDev3,0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
    lpDev3->lpVtbl->SetTextureStageState(lpDev3,0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
   

    lpDev3->lpVtbl->SetTextureStageState(lpDev3,1, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
    lpDev3->lpVtbl->SetTextureStageState(lpDev3,1, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
   
    lpDev3->lpVtbl->SetTextureStageState(lpDev3,2, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

	lpDev3->lpVtbl->SetTextureStageState(lpDev3,0, D3DTSS_TEXCOORDINDEX, 0);
	lpDev3->lpVtbl->SetTextureStageState(lpDev3,1, D3DTSS_TEXCOORDINDEX, 0);
}