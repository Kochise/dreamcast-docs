/*****************************************************************************
  Name :	D3DDragonFly
  Author:	Carlos Sarria
  Date :	Sept 1998 (Updated Aug 99)
  
  Description: Render in a texture (Motion Blur effect).

  Copyright : 1999 by Imagination Technologies Limited. All rights reserved.
******************************************************************************/

/****************************************************************************
 ** INCLUDES                                                               **
 ****************************************************************************/
#include <windows.h>
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
#include "D3DDragonFly.h"

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


typedef struct Shot_struct_tag {
	int Active;
	int Time;
	float fPosX; 
	float fPosZ; 
	float fAngleY; 
	float fHeight;
} SHOT;

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

TEXTURE				lpTexture[256], lpTargetTexture;

OBJECT				D3DObject[NUM_MESHES];

int					nFrame = 0, bFire = FALSE;

DWORD				dwDisplayWins = 1;
BOOL				bPause = FALSE, bUserControl = FALSE;

DWORD				InfoWin, TWin[10], dwCurrentWin=0; /* Info windows */

float				fPosX=0.0f, fPosZ=0.0, fAngleY = 0.5f, fAngleX=0.0f, fHeight = 0.0f;
float				AnimCount = 0, Incr = 1.0f;

SHOT Shot[100];

/* DX tranformations */
D3DLIGHT2			light;        // Structure defining the light
LPDIRECT3DLIGHT		lpD3DLight;   // Object pointer for the light

LPDIRECTDRAWSURFACE4 lpFrameBufferSurface;
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
void SetAnimMatrix				(D3DMATRIX *pMatrix, int i, unsigned Count);
void DrawShots					(LPDIRECT3DDEVICE3 lpDev3);
void CreateShot					(void);

BOOL RenderSceneInTexture		(LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DVIEWPORT3 lpView3);
BOOL RenderSceneInFrameBuffer	(LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DVIEWPORT3 lpView3);

void RenderBigQuad				(LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DTEXTURE2 TextureID, float fZ);

BOOL CreateTargetTexture		(LPDIRECTDRAW4 lpDD4, DWORD nXSize, DWORD nYSize, 
									LPDIRECTDRAWSURFACE4	*lpDDSTextureSurface, LPDIRECT3DTEXTURE2 *lpD3DTexture2);

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
		fPosX=0.0f; fPosZ=0.0; fAngleY = 0.5f; fAngleX=0.0f; fHeight = 0.0f;
		
	}

	/* UP */
	if (GetAnalogY()<64)
	{
		fHeight += 10.0f;
		fAngleX= 0.1f;
	}

	/* DOWN */
	if (GetAnalogY()>256-64)
	{
		fHeight -= 10.0f;
		fAngleX = -0.1f;
		
	}

	/* LEFT */
	if (GetAnalogX()<64)
	{
		fAngleY  += 0.1f;
	}

	/* RIGHT */
	if (GetAnalogX()>256-64)
	{
		fAngleY  -= 0.1f;
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
		if (AnimCount<100) {AnimCount=100;Incr=0.5f;}
		bFire = TRUE;
		fAngleX = -0.1f;
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
		fPosX += 20.0f * (float)sin(fAngleY);
		fPosZ += 20.0f * (float)cos(fAngleY);

		fAngleX= 0.1f;
	}

	/* RIGHT finger button */
	if (IsRFKey())
	{
		fPosX -= 20.0f * (float)sin(fAngleY);
		fPosZ -= 20.0f * (float)cos(fAngleY);

		fAngleX = 0.1f;
	}

	return TRUE;
}
/*******************************************************************************
 * Function Name  : RenderScene
 * Returns        : TRUE if no error occured
 * Global Used    : None
 * Description    : Application's rendering function
 * Note           : The texture target and the backbuffer target have the same
 *                  viewport size (640x480) so it doesn't need to be changed every 
 *                  time we change our render target.
 *******************************************************************************/
BOOL RenderScene(LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DVIEWPORT3 lpView3)
{
DDSURFACEDESC2  ddsd;

	if(PadControl()==FALSE) return FALSE; 

	/* Set texture target as Render target */
	lpDev3->lpVtbl->SetRenderTarget(lpDev3, lpTargetTexture.lpDDSTextureSurface, 0);

	/* Render in a texture */
	RenderSceneInTexture(lpDev3, lpView3);

	/* Flush the scene to the texture */
	memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	lpTargetTexture.lpDDSTextureSurface->lpVtbl->Lock(lpTargetTexture.lpDDSTextureSurface, NULL, &ddsd,	DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);
	lpTargetTexture.lpDDSTextureSurface->lpVtbl->Unlock(lpTargetTexture.lpDDSTextureSurface, NULL);
	
	/* Restore the FrameBuffer as our render target */
	lpDev3->lpVtbl->SetRenderTarget(lpDev3, lpFrameBufferSurface, 0);

	/* Render in FrameBuffer */
	if (!RenderSceneInFrameBuffer(lpDev3, lpView3))	return FALSE;

	if (bPause==FALSE) nFrame++;

	/* Everything is OK */
	return TRUE;
}
/*******************************************************************************
 * Function Name  : RenderSceneInFrameBuffer
 * Returns        : TRUE if no error occured
 * Global Used    : None
 * Description    : Application's rendering function (standard FrameBuffer rendering)
 *					
 *******************************************************************************/
BOOL RenderSceneInFrameBuffer(LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DVIEWPORT3 lpView3)
{
int i;
		
		/* Slow movemement of the dragonfly up and down */
		fHeight += 0.2f * (float)sin ((float)nFrame/50.0f);

		/* Slow rectification of the dragonfly angle */
		if(fAngleX>0.0f) fAngleX -= 0.01f;
		if(fAngleX<0.0f) fAngleX += 0.01f;

		/* Begin Scene */
	    lpDev3->lpVtbl->BeginScene(lpDev3);

		Background (lpDev3,  lpTexture[10].lpD3DTexture);

		for (i=0; i<NUM_MESHES;i++) 
		{ 
			
			/* Don't transform these objects */
			if (i==M_FLASH || i==M_BACKGROUND) continue;
				

			/* Set the transformation matrix for animation. (Must be done before any tranformation) */
			SetAnimMatrix (&WorldMatrix, i,  (int)AnimCount);

			/* Special movement for legs */
			if (i>=M_LEG1 && i<=M_LEG06)
				D3DTMatrixRotate(&WorldMatrix, 0.0f, 0, PI/64 * (float)sin((float)(nFrame)/(5.0f+i*2.0f)));
			  
			/* Special movement for wings */
			if (i==M_WING1)
				D3DTMatrixRotate(&WorldMatrix, 0.0f, 0.0f, -PI/5.5f + PI/5.5f * (float)cos((float)(nFrame)/1.0f));

			if (i==M_WING2)
				D3DTMatrixRotate(&WorldMatrix, 0.0f, 0.0f,  PI/5.5f - PI/5.5f * (float)cos((float)(nFrame)/1.0f));

			/* Rotate and translate the dragonfly */
			D3DTMatrixRotate(&WorldMatrix, fAngleX, fAngleY, 0); 
				
			D3DTMatrixTranslate(&WorldMatrix, fPosX, fHeight, 400.0f + fPosZ); 
	
		
			/* Transform all the vertices */
			if (i==M_WING1 || i==M_WING2)
			{
				TransformObject(lpDev3, &WorldMatrix, &D3DObject[i], TRUE, FALSE, USE_D3DTLVERTEX);

				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND,  D3DBLEND_SRCALPHA);
				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
				RenderObjectTriangles (lpDev3, lpTexture[1].lpD3DTexture, &D3DObject[i], USE_D3DTLVERTEX);
			}
			else
			{
				TransformObject(lpDev3, &WorldMatrix, &D3DObject[i], TRUE, FALSE, USE_D3DTLVERTEX);

				/* environment map */
				D3DTMatrixScale(&WorldMatrix, 0.54f);

				/* Reduce displacement to avoid 'crazy' env-map */
				WorldMatrix._41 *= 0.005f; 
				WorldMatrix._42 *= 0.005f; 
				WorldMatrix._43  = 0.005f; 

				D3DTTransUVEnvMap (&WorldMatrix, Mesh[i].nNumVertex, Mesh[i].pNormals, 
								   (D3DTLVERTEX *)D3DObject[i].pTLVertices, 	&CameraPosition, &CameraPointing, fCameraRoll);
	

				lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
				RenderObjectTriangles (lpDev3, lpTexture[2].lpD3DTexture, &D3DObject[i], USE_D3DTLVERTEX);
			}

		}

	/* Draw all the shots in the current frame */
	DrawShots(lpDev3);   

	/*
	 * Animation frame-counter.
	 * There are two different animations, 
	 * one is the slow repose movement (from frame 0 to 100) 
	 * the other one is the 'fire' movement (from frame 100 to 150)
	 */
	if (!bFire)
	{
		AnimCount += Incr;
		if(AnimCount==0 || AnimCount==100) { Incr=-Incr;}
	}
	else
	{
		AnimCount++;
		if (AnimCount==150) {AnimCount=0; Incr=0.5f; bFire=FALSE;}
		if (AnimCount==108 || AnimCount==114 || AnimCount==120) CreateShot ();
	}

	/* Draw the texture already rendered on top  */
	LegacyBlendModes (lpDev3, D3DTBLEND_MODULATEALPHA, TRUE);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND,  D3DBLEND_ONE);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);
	RenderBigQuad (lpDev3, lpTargetTexture.lpD3DTexture, 0.99f);


	/* 
	* D3DTPrint3DDisplayAllWindows must be called just before EndScene.
	*/
	if(dwDisplayWins)
	{
		D3DTPrint3DDisplayWindow(TWin[dwCurrentWin]);
		D3DTPrint3DDisplayWindow(InfoWin);
	}

	D3DShellDCLogo (0x00);

	if (bPause==TRUE) D3DTPrint3D (80.0f, 3.0f, 1.0f, (DWORD)0xFFFFFFFFF, L"PAUSE");

	
	/* End Scene */
    lpDev3->lpVtbl->EndScene(lpDev3);
 
	
    

	/* No problem occured */
	return TRUE;

}
/*******************************************************************************
 * Function Name  : RenderSceneInTexture
 * Returns        : TRUE if no error occured
 * Global Used    : None
 * Description    : Application's rendering function (to a texture)
 * Note           : Transforming is not needed because it was done in RenderToFrameBuffer.					
 *******************************************************************************/
BOOL RenderSceneInTexture(LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DVIEWPORT3 lpView3)
{
int i;
static D3DRECT	rScreen = {0, 0, 639, 479 };
	
	/* Clear the viewport at the begining */
	if(nFrame==0)
	{
		lpView3->lpVtbl->Clear(lpView3, 1, &rScreen, D3DCLEAR_TARGET);
	}

	/* Begin Scene */
	lpDev3->lpVtbl->BeginScene(lpDev3);

	for (i=0; i<NUM_MESHES;i++) 
	{ 
		/* Don't draw these objects */
		if (i==M_FLASH || i==M_BACKGROUND || (i>=M_LEG1 && i<=M_LEG06)) continue;
				
		if (i==M_WING1 || i==M_WING2)
		{
			TransformObject(lpDev3, &WorldMatrix, &D3DObject[i], TRUE, FALSE, USE_D3DLVERTEX);
			LegacyBlendModes (lpDev3, D3DTBLEND_MODULATEALPHA, TRUE);
			lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
			lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND,  D3DBLEND_SRCALPHA);
			lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
			RenderObjectTriangles (lpDev3, lpTexture[1].lpD3DTexture, &D3DObject[i], USE_D3DTLVERTEX);
		}
		else
		{
			lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
			RenderObjectTriangles (lpDev3, lpTexture[2].lpD3DTexture, &D3DObject[i], USE_D3DTLVERTEX);
		}

	}

	/* Draw all the shots in the current frame */
	DrawShots(lpDev3);   

	/* Draw the texture rendered in the previous frame on top as a translucent poly. */
	if(nFrame>0)
	{
		LegacyBlendModes (lpDev3, D3DTBLEND_MODULATEALPHA, TRUE);
		lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
		lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND,  D3DBLEND_SRCALPHA);
		lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
		RenderBigQuad (lpDev3, lpTargetTexture.lpD3DTexture, 0.99f);
	}

	/* End Scene */
    lpDev3->lpVtbl->EndScene(lpDev3);
 
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

	 //D3DShellGetVariable(BACK_BUFFER, &lpFrameBufferSurface);
	 lpDev3->lpVtbl->GetRenderTarget(lpDev3, &lpFrameBufferSurface);
    
	 /* Update viewport size variables */
	dwCurrentWidth=dwWidth;
	dwCurrentHeight=dwHeight;
		
	/* Assign the background colour to be black.
	   This is needed to assign a colour to the viewport */
	D3DTMiscSetBackgroundColor(lpD3D3, lpDev3, lpView3, RGB_MAKE(0, 0, 0));

	/* Load textures */
	D3DShellLoadBMP(L"BMP_FLASH",	FALSE,	&lpTexture[0].lpD3DTexture);
	D3DShellLoadBMP(L"BMP_WING",	TRUE,	&lpTexture[1].lpD3DTexture);
	D3DShellLoadBMP(L"BMP_REFLECT",	FALSE,	&lpTexture[2].lpD3DTexture);
	D3DShellLoadBMP(L"BMP_BACK",	FALSE,	&lpTexture[10].lpD3DTexture);

	/* target texture for 'Render in a Texture' */
	CreateTargetTexture (lpDD4, 1024, 1024, &lpTargetTexture.lpDDSTextureSurface, &lpTargetTexture.lpD3DTexture);

	 
	/* General Render States */
	lpDev3->lpVtbl->SetTextureStageState (lpDev3, 0, D3DTSS_MINFILTER ,		D3DTFN_LINEAR);	
	lpDev3->lpVtbl->SetTextureStageState (lpDev3, 0, D3DTSS_MAGFILTER ,		D3DTFG_LINEAR);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DITHERENABLE,		TRUE);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ZENABLE,			TRUE);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_CULLMODE,			D3DCULL_NONE);

	/* Create directional light */
	CreateLight (lpD3D3, lpDev3, lpView3);

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
 * Description    : D3DShell passes the viewport variable to this function 
 *					so you can delete any lights you created previously 
 *******************************************************************************/
void ReleaseView(LPDIRECT3DVIEWPORT3 lpView3)
{
register i;
	
	/* This fuction must be always in ReleaseView  */    
	D3DTPrint3DReleaseTextures();

	RELEASE(lpD3DLight);

	RELEASE(lpTexture[20].lpDDSTextureSurface);

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
int			i, Color;
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

	 /* Default color */
	Color = 0xFFFFFFFF;
		
	/* Diffuse color from the material (if it exists) */
#ifdef STRUCT_MATERIALS_DEFINED 
		if (Mesh[nObject].nMaterial!=-1) Color = Material[Mesh[nObject].nMaterial].nMatDiffuseColor;
#endif


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
		(pObj->pLVertices + i)->color    = (pObj->pTLVertices + i)->color    = Color;		
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
	/* Info Window */
	InfoWin = D3DTPrint3DCreateWindow (50, 3);
	
	D3DTPrint3DSetWindow		(InfoWin, 0x40A00000, 0xFFFFFFFF, 0.5f, 1.0f, 86.0f, 55.0f, 12.0f);
	D3DTPrint3DSetWindowFlags	(InfoWin, PRINT3D_DEACTIVATE_TITLE );
	D3DTPrint3DWindowOutput	(InfoWin, L"(ANALOG PAD + TRIGGERS) Move Dragonfly\n");
	D3DTPrint3DWindowOutput	(InfoWin, L"(A) Fire button.\n");
	D3DTPrint3DWindowOutput	(InfoWin, L"(START) Reset.\n");
	
	
	/* Text Windows */
	/* Window 0 */
	TWin[0] = D3DTPrint3DCreateDefaultWindow (1.0f, 1.0f, 50, L"DRAGONFLY Render to a Texture   ", NULL);

 	/* Window 1 */
	TWin[1] = D3DTPrint3DCreateDefaultWindow (1.0f, 1.0f, 50, L"DRAGONFLY Render to a Texture  (1 of 3)",
L"This motion-blur effect has been created by rendering recursively to a texture.\n\n");
 
 /* Window 2 */
	TWin[2] = D3DTPrint3DCreateDefaultWindow (1.0f, 1.0f, 50, L"DRAGONFLY Render to a Texture  (2 of 3)",
L"A target texture is created which contains the motion blurred object along with the previous texture contents\
 blended into it. This results in a recursive motion blur effect as previous renders of the motion blurred\
 object are slowly fading out due to the alpha component.\n\n");

/* Window 3 */
	TWin[3] = D3DTPrint3DCreateDefaultWindow (1.0f, 1.0f, 50, L"DRAGONFLY Render to a Texture  (2 of 3)",
L"This texture containing the motion blurred object is blended into the current frame containing the rest of the\
 3D scene by additive blending.\n\n");


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
 *  Function Name   : SetAnimMatrix                                                    
 *  Inputs          :                                                            
 *  Outputs         :                                                             
 *  Returns         :                                                           
 *  Globals Used    :                                                                 
 *  Description     : To set a animation from 3DStudio MAX, feed the transformation matrix 
 *					  with the values exported by the PVRexp plug-in.
 *******************************************************************************/
void SetAnimMatrix (D3DMATRIX *pMatrix, int i, unsigned Count)
{

#ifdef STRUCT_ANIMATION_DEFINED

	/* If the frame is out of range return the identity matrix */
	if (Count<0 || Count > Animation[i].nNumFrames) 
	{
		D3DTMatrixReset (pMatrix);
		return;
	}

	/*
	 *  Every chunk has 12 floats so, for example, the data for frame 32 of the object 2 starts at
	 *  (Animation[2].pData + 32*12 + 0) and carrys on for 12 floats.
	 *  Note: M_14 = 0, M_24 = 0, M_34 = 0 and M_44 =1 are fixed values.
	 */
	Count = Count*12;

    pMatrix->_11 = *(Animation[i].pData + Count + 0);
	pMatrix->_12 = *(Animation[i].pData + Count + 1);
	pMatrix->_13 = *(Animation[i].pData + Count + 2);
	pMatrix->_14 = 0.0f;

	pMatrix->_21 = *(Animation[i].pData + Count + 3);
	pMatrix->_22 = *(Animation[i].pData + Count + 4);
	pMatrix->_23 = *(Animation[i].pData + Count + 5);
	pMatrix->_24 = 0.0f;

	pMatrix->_31 = *(Animation[i].pData + Count + 6);
	pMatrix->_32 = *(Animation[i].pData + Count + 7); 
	pMatrix->_33 = *(Animation[i].pData + Count + 8);
	pMatrix->_34 = 0.0f;

	pMatrix->_41 = *(Animation[i].pData + Count + 9); 
	pMatrix->_42 = *(Animation[i].pData + Count + 10);
	pMatrix->_43 = *(Animation[i].pData + Count + 11);
	pMatrix->_44 = 1.0f;

#else
	D3DTMatrixReset (pMatrix);
#endif

}
/*******************************************************************************
 *  Function Name   : DrawShots                                                    
 *  Inputs          :                                                            
 *  Outputs         :                                                             
 *  Returns         :                                                           
 *  Globals Used    :                                                                 
 *  Description     : If a shot is on, move and draw it.
 *******************************************************************************/
void DrawShots (LPDIRECT3DDEVICE3 lpDev3)
{
register i;
D3DMATRIX Matrix;
	
	for (i=0; i<100; i++)
	{
		/* If the shot is not active, don't draw it */
		if (Shot[i].Active==FALSE) continue;

		/* Limited time for displaying the same shot */
		Shot[i].Time++; 
		if(Shot[i].Time > 200) Shot[i].Active = FALSE;

		/* Update the position */
		Shot[i].fPosX -= 20.0f * (float)sin(Shot[i].fAngleY);
		Shot[i].fPosZ -= 20.0f * (float)cos(Shot[i].fAngleY); 
		Shot[i].fHeight -= 1.0f;

		/* Transform */
		D3DTMatrixReset (&Matrix);
		D3DTMatrixTranslate(&Matrix, Shot[i].fPosX, Shot[i].fHeight, 500.0f +Shot[i].fPosZ);

		TransformObject(lpDev3, &Matrix, &D3DObject[M_FLASH], TRUE, FALSE, USE_D3DLVERTEX);
	 
		lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
		lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND,  D3DBLEND_ONE);
		lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);

		RenderObjectTriangles (lpDev3, lpTexture[0].lpD3DTexture, &D3DObject[M_FLASH], USE_D3DLVERTEX);
	
	}
}
/*******************************************************************************
 *  Function Name   : DrawShots                                                    
 *  Inputs          :                                                            
 *  Outputs         :                                                             
 *  Returns         :                                                           
 *  Globals Used    :                                                                 
 *  Description     : This function is called just once to initialize the data.                     
 *******************************************************************************/
void CreateShot (void)
{
register i;

	for (i=0; i<100; i++)
	{ 
		/* Select the first one that is free */
		if (Shot[i].Active==TRUE) continue;

		/* Feed the structure with the current position data */
		Shot[i].Active	= TRUE;
		Shot[i].Time	= 0; 
		Shot[i].fAngleY = fAngleY;	
		Shot[i].fPosX	= fPosX - 35.0f * (float)sin(Shot[i].fAngleY);
		Shot[i].fPosZ	= fPosZ - 35.0f * (float)cos(Shot[i].fAngleY);
		Shot[i].fHeight = fHeight;

		/* done */
		break;
	}
}

/*******************************************************************************
 * Function Name  : CreateTargetTexture
 * Inputs		  : 
 * Global Used    : 
 * Description    : 
 *******************************************************************************/
BOOL CreateTargetTexture (LPDIRECTDRAW4 lpDD4, DWORD nXSize, DWORD nYSize, 
						  LPDIRECTDRAWSURFACE4	*lpDDSTextureSurface, LPDIRECT3DTEXTURE2 *lpD3DTexture2)
{
HRESULT					hres;
DDSURFACEDESC2			ddsd;
unsigned short			pszString[300];


	/* Debug output */
	wsprintf(pszString,  TEXT("Creating target texture : (%u*%u)\n"),  nXSize, nYSize);
	OutputDebugString(pszString);

	/* Security : discard any size above 1024 pixels */
	if (nXSize>1024 || nYSize>1024)
	{
		OutputDebugString(L"Texture size too large\n");
		return 0;
	}

	/* Create a texture surface in video memory using the given 
     * dimensions.  The DDSCAPS_3DDEVICE flag allows
     * the texture to be used as a rendering target.
	 */
    memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
    ddsd.dwSize         = sizeof(DDSURFACEDESC2);
    ddsd.dwFlags        = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH ;
    ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_VIDEOMEMORY | DDSCAPS_3DDEVICE;
    ddsd.dwWidth        = nYSize;
    ddsd.dwHeight       = nYSize;

    hres = lpDD4->lpVtbl->CreateSurface(lpDD4, &ddsd, lpDDSTextureSurface, NULL);

	if (hres!=DD_OK) 
	{
		OutputDebugString(TEXT("Create Surface failed\n"));
		return 0;
	}
   
	/* QueryInterface for a Direct3DTexture2 interface */
	hres=(*lpDDSTextureSurface)->lpVtbl->QueryInterface(*lpDDSTextureSurface, &IID_IDirect3DTexture2,(LPVOID*)lpD3DTexture2);

    if (hres!=DD_OK) 
	{
		OutputDebugString(TEXT("Query Direct3DTexture2 Interface failed\n"));
		return 0;
	}


	/* Note that on the desktop the rendering device could have
     * an associated z buffer.  In this case we would have
     * to also create a z buffer for the texture target.
	 */

	OutputDebugString(TEXT("Target Texture created !\n"));

	
	/* Return OK */
    return TRUE;
}
/*******************************************************************************
 * Function Name  : RenderBigQuad
 * Input		  : 
 * Returns        : 
 * Global Used    : 
 * Description    : 
 *******************************************************************************/
void RenderBigQuad (LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DTEXTURE2 TextureID, float fZ)
{
D3DTLVERTEX Plane[4];
WORD pFaces[] = {0,1,2, 0,2,3};
float fDispX = -0.2f, fDispY = -0.2f;

     Plane[0].sx		= fDispX;
	 Plane[0].sy		= fDispY;
	 Plane[0].rhw		= 1.0f - fZ;
	 Plane[0].sz		= fZ;
	 Plane[0].color     = RGBA_MAKE (255, 255, 255, 240);
	 Plane[0].tu		= 0.0f;
     Plane[0].tv		= 0.0f;

	 Plane[1].sx		= fDispX + (float)dwCurrentWidth;
	 Plane[1].sy		= fDispY;
	 Plane[1].rhw		= 1.0f - fZ;
	 Plane[1].sz		= fZ;
	 Plane[1].color     = RGBA_MAKE (255, 255, 255, 240);
	 Plane[1].tu		= 640.0f/1024.0f;
     Plane[1].tv		= 0.0f;

	 Plane[2].sx		= fDispX + (float)dwCurrentWidth;
	 Plane[2].sy		= fDispY + (float)dwCurrentHeight;
	 Plane[2].rhw		= 1.0f - fZ;
	 Plane[2].sz		= fZ;
	 Plane[2].color     = RGBA_MAKE (255, 255, 255, 240);
	 Plane[2].tu		= 640.0f/1024.0f;
     Plane[2].tv		= 480.0f/1024.0f;

	 Plane[3].sx		= fDispX;
	 Plane[3].sy		= fDispY + (float)dwCurrentHeight;
	 Plane[3].rhw		= 1.0f - fZ;
	 Plane[3].sz		= fZ;
	 Plane[3].color     = RGBA_MAKE (255, 255, 255, 240);
	 Plane[3].tu		= 0.0f;
     Plane[3].tv		= 480.0f/1024.0f;

	 lpDev3->lpVtbl->SetTexture(lpDev3, 0, TextureID);

	 lpDev3->lpVtbl->DrawIndexedPrimitive(lpDev3, D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, 
										  Plane, 4,  pFaces, 6, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

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