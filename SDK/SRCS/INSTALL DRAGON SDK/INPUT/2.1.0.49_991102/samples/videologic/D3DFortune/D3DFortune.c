/*****************************************************************************
  Name : D3DFortune
  Author: Carlos Sarria
  Date : Nov 1998 (update Aug 99)

  Description: Fill rate test.

  Note: This a WCE HS4 (DRAGON) version for Dreamcast.

  Copyright : 1999 by Imagination Technologies Limited. All rights reserved.
******************************************************************************/

// Includes
// General includes
#include <windowsx.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <d3d.h>


// D3D Shell includes
#include "D3DShell.h"	// D3D Shell include

// D3D Tools include
#include "D3DTools.h"	// D3D Tools include

/**************************************************/
/* Defines                                        */
/**************************************************/

#define TOTAL_CARDS 52
#define NUM_CARDS   42

#define CARD_REAL_AREA   154000 

#ifndef PI
#define PI 3.14159f
#endif

#ifndef RELEASE
#define RELEASE(x)	if (x) { x->lpVtbl->Release(x); x=NULL; }
#endif

/* A structure which holds the object's data */
typedef struct Card_Tag{
	float fVertex[4*3];
	float fU[4];
	float fV[4];
	float fTU[4];
	float fTV[4];
	float fShU[4];
	float fShV[4];
	float Displ;
	int   Texture;
	D3DTLVERTEX D3DVert[4];
} CARD_TYPE;

typedef struct _TEXTURE
{
	LPDIRECTDRAWSURFACE4	lpDDSTextureSurface;
	LPDIRECT3DTEXTURE2		lpD3DTexture;
} TEXTURE;

/**************************************************/
/* Globals                                        */
/**************************************************/

int					dwCurrentWidth, dwCurrentHeight;

float				fFrontClippingPlane = 10.0f;
D3DVECTOR			CameraPosition={0.0f, 0.0f, -100.0f};
D3DVECTOR			CameraPointing={0.0f, 0.0f, 6000.0f};
float				fCameraRoll=0.0f;
unsigned short		pszTmp[300];

TEXTURE				TextureTable, TextureShadow, TextureReflect, TextureBlack, TextureCard[TOTAL_CARDS];


static int			CurrentCard = 0;
static float		PosX = 0.0f, PosY = -1300.0f, PosZ= 50.0f, AngZ,
					AngIncr = -0.3f, PosXIncr = -5.0f, PosYIncr = 20.0f;

int 				bIsPacked = FALSE;
static int			nPackCont = 0;
BOOL				bBlendCaps = TRUE;

int nCardsList[] = {33,50, 6, 7, 8,34, 5, 9,12,11,
					10,27,25,26,15,16,1,18,19,2,
					13,14,0,31,32, 30,17, 24,37,42,
					39,40,21,22,43,41,46, 3, 4,38, 
					47,49,45,20,44,48,36,23,28,29,
					35,51,52};

CARD_TYPE			Card[TOTAL_CARDS];

unsigned            nFrame=0;	

D3DVECTOR CameraTo   = { 0.0f, 0.0f, 5000.0f};
D3DVECTOR CameraFrom = { 0.0f, -700.0f, -700.0f};
D3DVECTOR LightDir   = { 1.0f, -1.0f, 1.0f};

DWORD				InfoWin, TWin[10], dwCurrentWin=0; /* Info windows */

BOOL				bPause = FALSE;
DWORD				dwDisplayWins = TRUE;	

unsigned short		Temp[1000];
HRESULT				hres;

/**************************************************/
/* Prototypes                                     */
/**************************************************/

void	InitCards			(void);
void	InitTextures 		(void);
void	CalculateFlyingCard	(int nCard);
void	DrawCard			(LPDIRECT3DDEVICE3 lpDev3, int nCard, float Dist);

long	km_rand				(void);
void	Background			(LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DTEXTURE2 TextureID);

void	CreateWindows		(void);

void	ShowLayers			(LPDIRECT3DDEVICE3 lpDev3);

float   GetFramesPerSec		(void);

BOOL	PadControl			(void);

void LegacyBlendModes (LPDIRECT3DDEVICE3 lpDev3, DWORD nMode, BOOL bIsVertexAlpha);

/****************************************************************************
** InitApplication() is called by D3DShell to enable user to initialise	   **
** his/her application													   **
****************************************************************************/
void InitApplication(HINSTANCE hInstance, HWND hWindow, TCHAR *pszCommandLine)
{
	InitDirectInput(hWindow, hInstance);
								
	CreateWindows ();
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
register i;
static unsigned  nTempCurrent;


	switch (message)
	{
	case WM_KEYDOWN:	switch(wParam)
						{
						case 'P': 
							nTempCurrent = CurrentCard;
							bIsPacked = !bIsPacked;
							if(bIsPacked)	for (i=0; i<=CurrentCard;i++)	CalculateFlyingCard (i);
							CurrentCard = nTempCurrent;

						case VK_LEFT:
						case VK_F1:
								dwCurrentWin--;
								if (dwCurrentWin==-1) dwCurrentWin = 2;
								if (dwCurrentWin==1) bIsPacked=TRUE;
								else                 bIsPacked=FALSE;
								break;

						case VK_SPACE:
								bPause = !bPause;
								break;

						case VK_RIGHT:
						case VK_RETURN:
						case VK_F2:
								dwCurrentWin++;
								if (dwCurrentWin==3) dwCurrentWin = 0;
								if (dwCurrentWin==1) bIsPacked=TRUE;
								else                 bIsPacked=FALSE;
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
			dwDisplayWins = !dwDisplayWins;
		}
		Delay = 0;
	}

	/* DOWN */
	if (IsDOWNKey() || GetAnalogY()>192)
	{
		if (Delay>2)
		{
			dwDisplayWins = !dwDisplayWins;
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
			if (dwCurrentWin==1) bIsPacked=TRUE;
			else                 bIsPacked=FALSE;
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
			if (dwCurrentWin==1) bIsPacked=TRUE;
			else                 bIsPacked=FALSE;
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
DWORD dwFPS = 0;
float Area;

	if (PadControl()==FALSE) return FALSE;

	if(dwCurrentWin==2)
	{
		ShowLayers(lpDev3);
		return TRUE;
	}

	/* Begin Scene */
	lpDev3->lpVtbl->BeginScene(lpDev3);


	Background (lpDev3, TextureTable.lpD3DTexture);

	for (i=0; i<TOTAL_CARDS;i++)
	{
		if (nCardsList[i]<CurrentCard)  DrawCard(lpDev3, nCardsList[i], 0.0f); 
		if (nCardsList[i]==CurrentCard) DrawCard(lpDev3, nCardsList[i], PosZ);
	}


    if (bPause==FALSE) CalculateFlyingCard(CurrentCard);
 	
	D3DShellGetVariable(FRAME_RATE, &dwFPS);

	/*
	 * Area for Fill-Rate.
	 * Each card is half the screen size, with three layers: one opaque and two translucent,
	 * plus the background twice (a plain one and a textured one).
	 */
	Area = 3.0f*(float)(dwCurrentWidth*dwCurrentHeight/2.05f)*CurrentCard + 
					(float)(dwCurrentWidth*dwCurrentHeight*2);

	/* 
	 * D3DTPrint3DDisplayAllWindows must be called just before EndScene.
	 */
	if(dwDisplayWins)
	{
		D3DTPrint3DDisplayWindow(TWin[dwCurrentWin]);
	}

	D3DTPrint3DDisplayWindow(InfoWin);

	D3DShellDCLogo (0x80);

	if (bPause==TRUE) D3DTPrint3D (80.0f, 3.0f, 1.0f, (DWORD)0xFFFFFFFFF, TEXT("PAUSE"));

	/* End Scene */
    lpDev3->lpVtbl->EndScene(lpDev3);
 
	D3DTPrint3DWindowOutput (InfoWin, TEXT(" %s Fill Rate = %.2f Mpps\n"), (dwCurrentWin==0)?TEXT("Approximate"):TEXT("Exact"),((float)dwFPS * (Area+640*480))/1000000);

	nFrame++;

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
	/* This fuction must be always in InitView  */    
	D3DTPrint3DSetTextures(lpDev3, lpDD4, dwWidth, dwHeight);

    InitTextures();

	InitCards();

	 /* Update viewport size variables */
	dwCurrentWidth=dwWidth;
	dwCurrentHeight=dwHeight;
		
	/* Assign the background colour to be black.
	   This is needed to assign a colour to the viewport */
	D3DTMiscSetBackgroundColor(lpD3D3, lpDev3, lpView3, RGB_MAKE(0, 0, 0));
	

	/* General Render States */
	lpDev3->lpVtbl->SetTextureStageState (lpDev3, 0, D3DTSS_MINFILTER ,		D3DTFN_LINEAR);	
	lpDev3->lpVtbl->SetTextureStageState (lpDev3, 0, D3DTSS_MAGFILTER ,		D3DTFG_LINEAR);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DITHERENABLE,		TRUE);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ZENABLE,			TRUE);

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

	/* This fuction must be always in ReleaseView  */    
	D3DTPrint3DReleaseTextures();

	/* Nothing to release (textures created with the D3DShell
	   function D3DShellLoadBMP are automatically released) */
}

/*******************************************************************************
 *  Function Name   : InitCards                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    : Shad, Mesh, TempVert, TempNormals                                  
 *  Description     : Sets initials values for meshes managing                            
 ********************************************************************************/
void InitCards (void)
{
float fCardVert[]   = {-170.0f,-262.0f, 100.0f, 170.0f,-262.0f, 100.0f, 
                       -170.0f, 262.0f, 100.0f, 170.0f, 262.0f, 100.0f};
float fCardUVOdd[]  = {0.0f,0.0f,   0.5f,0.0f, 0.0f,1.0f,   0.5f,1.0f};
float fCardUVEven[] = {0.5f,0.0f,   1.0f,0.0f, 0.5f,1.0f,   1.0f,1.0f};
register i,j;
int nCard;

	/* Memory allocation for D3DVert, UV values and SmoothShading*/
    for (i=0; i<TOTAL_CARDS; i++) 
	{
       
		for (j=0; j<4; j++)
		{
            nCard = nCardsList[i];

			Card[i].fVertex[j*3+0] = fCardVert[j*3+0];
			Card[i].fVertex[j*3+1] = fCardVert[j*3+1];
			Card[i].fVertex[j*3+2] = fCardVert[j*3+2];
						
			Card[i].fU[j] = (nCard&1) ? fCardUVEven[j*2+0]: fCardUVOdd[j*2+0];
			Card[i].fV[j] = (nCard&1) ? fCardUVEven[j*2+1]: fCardUVOdd[j*2+1];
			
			Card[i].D3DVert[j].color = 0x50FFFFFF;
			Card[i].D3DVert[j].specular = 0xFF000000;

			Card[i].D3DVert[j].tu = Card[i].fU[j];
			Card[i].D3DVert[j].tv = Card[i].fV[j];

			Card[i].Texture = nCard/2;
			Card[i].Displ = (float)(km_rand()%500-250)/10.0f;
	
		}
		
	}
	
}
/*******************************************************************************
 *  Function Name   : InitTextures                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                   
 *  Description     : Loads textures and sets vertex contexts                           
 ********************************************************************************/

#define LOAD_CARD(x)	wsprintf (Temp, TEXT("IDB_BITMAP%d"),x);\
						D3DShellLoadBMP(Temp,FALSE, &TextureCard[x-1].lpD3DTexture);

void InitTextures (void)
{

	D3DShellLoadBMP(TEXT("ID_TABLE"),   FALSE, &TextureTable.lpD3DTexture);
	D3DShellLoadBMP(TEXT("ID_SHADOW"),  FALSE, &TextureShadow.lpD3DTexture);
	D3DShellLoadBMP(TEXT("ID_REFLECT"), FALSE, &TextureReflect.lpD3DTexture);


	/* Cards Textures */
	LOAD_CARD(1);
	LOAD_CARD(2);	LOAD_CARD(3);	LOAD_CARD(4);	LOAD_CARD(5);
	LOAD_CARD(6);	LOAD_CARD(7);	LOAD_CARD(8);	LOAD_CARD(9);	LOAD_CARD(10);
	LOAD_CARD(11);	LOAD_CARD(12);	LOAD_CARD(13);	LOAD_CARD(14);	LOAD_CARD(15);
	LOAD_CARD(16);	LOAD_CARD(17);	LOAD_CARD(18);	LOAD_CARD(19);	LOAD_CARD(20);
	LOAD_CARD(21);	LOAD_CARD(22);	LOAD_CARD(23);	LOAD_CARD(24);	LOAD_CARD(25);
	LOAD_CARD(26);

}
/*********************************************************************************
 *  Function Name   : CalculateFlyingCard                                                         
 *  Inputs          :                                                               
 *  Outputs         :                                                             
 *  Returns         :                                                              
 *  Globals Used    :                                   
 *  Description     :                          
 *********************************************************************************/
void CalculateFlyingCard (int nCard)
{
register i;
D3DMATRIX Matrix;
CARD_TYPE BufferCard;
static float	PosX = 0.0f, PosY = -1600.0f, AngZ;
static float	AngIncr = -0.3f, PosXIncr = -5.0f, PosYIncr = 20.0f;

    AngZ += AngIncr;
	PosX += PosXIncr;
	PosY += PosYIncr;
	PosZ--;

	if (bIsPacked)
	{
		D3DTMatrixReset(&Matrix);
		D3DTMatrixTranslate (&Matrix, (float)(((nCard+nPackCont)&1)*350-175), -600.0f, 20.0f);
	}
	else
	{
		D3DTMatrixReset(&Matrix);
		D3DTMatrixRotate (&Matrix, 0.0f, 0.0f, AngZ);
		D3DTMatrixTranslate (&Matrix, PosX, PosY, 0.0f);
	}


	D3DTTransTransformProjectPerspective(&Matrix, 4, Card[nCard].fVertex, Card[nCard].D3DVert,
											dwCurrentWidth, dwCurrentHeight,
											&CameraFrom, &CameraTo, 0.0f,
											1.0f, 10000.0f, 3.1416f/4.0f, 0);

	for (i=0; i<4; i++)
	{
		Card[nCard].fTU[i] = (Card[nCard].D3DVert[i].sx+Card[nCard].Displ)/(640.0f-nCard);
		Card[nCard].fTV[i] = 1.0f-(Card[nCard].D3DVert[i].sy+Card[nCard].Displ)/(480.0f-nCard);

		Card[nCard].fShU[i] = (Card[nCard].D3DVert[i].sx)/640.0f;
		Card[nCard].fShV[i] = 1.0f-(Card[nCard].D3DVert[i].sy)/480.0f;
	}


	/* Start a new card */
	if (PosZ==0.0f)
	{
		PosX = 0.0f;
		PosY = -1600.0f;
		PosZ = 50.0f;
		AngIncr = -0.22f;
		PosXIncr = (float)(km_rand()%140-70)/10.0f;
		PosYIncr = 20.0f - (float)(km_rand()%100-50)/10.0f;
	
		if (nCard<NUM_CARDS) /* Add another card */
		{
			CurrentCard++;
		}
		else /* Reuse the first one */
		{
			nPackCont++;

			memcpy(&BufferCard,		&Card[0],		sizeof(CARD_TYPE));
			memcpy(&Card[0],		&Card[1],		sizeof(CARD_TYPE)*(nCard));
			memcpy(&Card[nCard],	&BufferCard,	sizeof(CARD_TYPE));

			D3DTMatrixReset		(&Matrix);
			D3DTMatrixRotate	(&Matrix, 0.0f, 0.0f, AngZ);
			D3DTMatrixTranslate	(&Matrix, PosX, PosY, 0.0f);

			D3DTTransTransformProjectPerspective(&Matrix, 4, Card[nCard].fVertex, Card[nCard].D3DVert,
											dwCurrentWidth, dwCurrentHeight, &CameraFrom, &CameraTo, 0.0f,
											1.0f, 10000.0f, 3.1416f/4.0f, 0);
		}
	}
}
/*********************************************************************************
 *  Function Name   : DrawCard                                                         
 *  Inputs          :                                                               
 *  Outputs         :                                                             
 *  Returns         :                                                              
 *  Globals Used    :                                   
 *  Description     :                          
 *********************************************************************************/
void DrawCard (LPDIRECT3DDEVICE3 lpDev3, int nCard, float Dist)
{
register i;
WORD pFaces[] = {0,2,1, 1,2,3};
 
  
    /* 
	 *  OPAQUE BASE
	 */

	for(i=0;i<4;i++) 
	{
		Card[nCard].D3DVert[i].rhw = 1.0f/(float)(500-nCard*10);
		Card[nCard].D3DVert[i].sz  = 1.0f - Card[nCard].D3DVert[i].rhw;
		Card[nCard].D3DVert[i].tu  = Card[nCard].fU[i];
		Card[nCard].D3DVert[i].tv  = Card[nCard].fV[i];
		
	}

	LegacyBlendModes (lpDev3, D3DTBLEND_MODULATEALPHA, FALSE);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND,  D3DBLEND_ONE);
    lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);

	lpDev3->lpVtbl->SetTexture(lpDev3, 0, TextureCard[Card[nCard].Texture].lpD3DTexture);

	lpDev3->lpVtbl->DrawIndexedPrimitive(lpDev3, D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX,
										  Card[nCard].D3DVert, 4,  pFaces, 6, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

	/* 
	 *  LIGHT MAP
	 */
	
	for(i=0;i<4;i++)
	{
		Card[nCard].D3DVert[i].rhw += 0.00001f;
		Card[nCard].D3DVert[i].sz  = 1.0f - Card[nCard].D3DVert[i].rhw;
		Card[nCard].D3DVert[i].tu = Card[nCard].fShU[i];
		Card[nCard].D3DVert[i].tv = Card[nCard].fShV[i];

	}

	LegacyBlendModes (lpDev3, D3DTBLEND_MODULATEALPHA, TRUE);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND,  D3DBLEND_ZERO);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_SRCCOLOR);
	
	lpDev3->lpVtbl->SetTexture(lpDev3, 0,  TextureShadow.lpD3DTexture);

	lpDev3->lpVtbl->DrawIndexedPrimitive(lpDev3, D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, 
										  Card[nCard].D3DVert, 4,  pFaces, 6, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);


    /*
	 * REFLECTION 
	 */

	for(i=0;i<4;i++)
	{
		Card[nCard].D3DVert[i].rhw += 0.00001f;
		Card[nCard].D3DVert[i].sz  = 1.0f - Card[nCard].D3DVert[i].rhw;
		Card[nCard].D3DVert[i].tu = Card[nCard].fTU[i];
		Card[nCard].D3DVert[i].tv = Card[nCard].fTV[i];

	}

	LegacyBlendModes (lpDev3, D3DTBLEND_MODULATEALPHA, TRUE);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND,  D3DBLEND_SRCALPHA );
    lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

	lpDev3->lpVtbl->SetTexture(lpDev3, 0,  TextureReflect.lpD3DTexture);

	lpDev3->lpVtbl->DrawIndexedPrimitive(lpDev3, D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, 
										  Card[nCard].D3DVert, 4,  pFaces, 6, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);
	

}
/**********************************************************************************
 *  Function Name   :  km_rand()                                                 
 *  Inputs          :                                                     
 *  Outputs         :                                                   
 *  Returns         :                                                   
 *  Globals Used    :                                                   
 *  Description     : A portable L.C.G. random number generator taken from
 *				  Numerical Recipies. It does assume the unsigned 32bit mul
 *				  does behave correctly. ie returns the bottom 32bits of a
 *				  64Bit result. With a seed of 0, the next few numbers should
 *				  be 0x3C6EF35F, 0x47502932, 0xD1CCF6E9, and 0xAAF95334.
 *				  INTERNALLY! To make it easier to use, we mask off the top
 *				  bit so that we can return it as a positive signed integer.
 *********************************************************************************/
long km_rand()
{
const long TOPBIT = 0x80000000L;
static DWORD RandomNumber=0;

	RandomNumber=1664525UL*RandomNumber + 1013904223UL;

	return(RandomNumber & ~TOPBIT);
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
/*********************************************************************************
 *  Function Name   : ShowLayers	                                    
 *  Inputs          :                                                   
 *  Outputs         :                                                   
 *  Returns         :                                                   
 *  Description     :             
 *********************************************************************************/
void ShowLayers (LPDIRECT3DDEVICE3 lpDev3)
{
D3DMATRIX Matrix;
register i;
WORD pFaces[] = {0,2,1, 1,2,3};
static float fPos;

	fPos = (float)fabs(50 * (float) sin((float)nFrame/50.0f));

	/* Begin Scene */
	lpDev3->lpVtbl->BeginScene(lpDev3);

	Background (lpDev3, TextureTable.lpD3DTexture);

	/* Opaque layer */
	D3DTMatrixReset		(&Matrix);
	D3DTMatrixRotate	(&Matrix, 0.0f, 0.0f, (float)nFrame/400.0f);
	D3DTMatrixTranslate	(&Matrix, 0, -600, 0.0f);

	D3DTTransTransformProjectPerspective(&Matrix, 4, Card[50].fVertex, Card[50].D3DVert,
											dwCurrentWidth, dwCurrentHeight, &CameraFrom, &CameraTo, 0.0f,
											10.0f, 10000.0f, PI/4.0f, 0);

	for(i=0;i<4;i++) 
	{
		Card[50].D3DVert[i].rhw = 1.0f/500.0f;
		Card[50].D3DVert[i].sz  = 1.0f - Card[50].D3DVert[i].rhw;
		Card[50].D3DVert[i].tu  = Card[50].fU[i];
		Card[50].D3DVert[i].tv  = Card[50].fV[i];
		
	}

	LegacyBlendModes (lpDev3, D3DTBLEND_MODULATEALPHA, FALSE);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);

	 lpDev3->lpVtbl->SetTexture(lpDev3, 0,  TextureCard[0].lpD3DTexture);

	lpDev3->lpVtbl->DrawIndexedPrimitive(lpDev3, D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, 
										  Card[50].D3DVert, 4,  pFaces, 6, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

	for (i=0; i<4; i++)
	{
	Card[50].fTU[i] = (Card[50].D3DVert[i].sx+Card[50].Displ)/(640.0f-50);
	Card[50].fTV[i] = 1.0f-(Card[50].D3DVert[i].sy+Card[50].Displ)/(480.0f-50);

	Card[50].fShU[i] = (Card[50].D3DVert[i].sx)/640.0f;
	Card[50].fShV[i] = 1.0f-(Card[50].D3DVert[i].sy)/480.0f;
	}


	/* 
	 * Environtment translucent layer 
	 */
		for(i=0;i<4;i++)
	{
		Card[50].D3DVert[i].sx  += fPos;
		Card[50].D3DVert[i].rhw += 0.001f;
		Card[50].D3DVert[i].sz  = 1.0f - Card[50].D3DVert[i].rhw;
		Card[50].D3DVert[i].tu = Card[50].fTU[i];
		Card[50].D3DVert[i].tv = Card[50].fTV[i];

	}

	LegacyBlendModes (lpDev3, D3DTBLEND_MODULATEALPHA, TRUE);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND,  D3DBLEND_SRCALPHA);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

	lpDev3->lpVtbl->SetTexture(lpDev3, 0,   TextureReflect.lpD3DTexture);

	lpDev3->lpVtbl->DrawIndexedPrimitive(lpDev3, D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, 
										  Card[50].D3DVert, 4,  pFaces, 6, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

	/*
	 * Shadow translucent layer 
	 */
	for(i=0;i<4;i++)
	{
		Card[50].D3DVert[i].sx  -= fPos*2;
		Card[50].D3DVert[i].rhw += 0.001f;
		Card[50].D3DVert[i].sz  = 1.0f - Card[50].D3DVert[i].rhw;
		Card[50].D3DVert[i].tu = Card[50].fShU[i];
		Card[50].D3DVert[i].tv = Card[50].fShV[i];

	}

	LegacyBlendModes (lpDev3, D3DTBLEND_MODULATEALPHA, TRUE);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND,  D3DBLEND_SRCALPHA);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

	lpDev3->lpVtbl->SetTexture(lpDev3, 0,   TextureShadow.lpD3DTexture);

	lpDev3->lpVtbl->DrawIndexedPrimitive(lpDev3, D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, 
										  Card[50].D3DVert, 4,  pFaces, 6, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

	/* 
	* D3DTPrint3DDisplayAllWindows must be called just before EndScene.
	*/
	if(dwDisplayWins)
	{
		D3DTPrint3DDisplayWindow(TWin[dwCurrentWin]);
	}

	D3DShellDCLogo (0x80);

	if (bPause==TRUE) D3DTPrint3D (80.0f, 3.0f, 1.0f, (DWORD)0xFFFFFFFFF, TEXT("PAUSE"));

	/* End Scene */
    lpDev3->lpVtbl->EndScene(lpDev3);
 

	if (bPause==FALSE) nFrame++;

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
	InfoWin = D3DTPrint3DCreateWindow (50, 1);
	
	D3DTPrint3DSetWindow		(InfoWin, 0xFFA00000, 0xFFFFFFFF, 0.5f, 1.0f, 90.0f, 50.0f, 10.0f);
	D3DTPrint3DSetWindowFlags	(InfoWin, PRINT3D_ADJUST_SIZE_ALWAYS | PRINT3D_DEACTIVATE_TITLE | PRINT3D_FULL_OPAQUE);

	/* Text Windows */
	/* Window 0 */
	TWin[0] = D3DTPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, L"FORTUNE Fill-Rate Test    ", NULL);
	
	/* Window 1 */
	TWin[1] = D3DTPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, L"FORTUNE Fill-Rate Test (1 of 2)", TEXT("\
The overall fillrate is calculated by summing up the surface area of all polygons in the scene, multiplied by the framerate.\n\n\
In this case the cards are not clipped so the fill rate is not an approximation.\n\n"));

	/* Window 2 */
	TWin[2] = D3DTPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, L"FORTUNE Fill-Rate Test (2 of 2)",TEXT("\
Every card covers an area of about half the screen (150K pixels), consists of three layers: one opaque and two translucent."));

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