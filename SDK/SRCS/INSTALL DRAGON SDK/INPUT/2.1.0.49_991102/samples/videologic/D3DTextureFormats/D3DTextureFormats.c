/*****************************************************************************
  Name :	D3DTextureFormats.c
  Author:	Nicolas Thibieroz
  Date :	November 1998 (updated for WinCE Dic.1999)
  
  Description: Texture formats quality test (YUV, VQ, 4444, 1555 and 565).

  Copyright : 1999 by Imagination Technologies Limited. All rights reserved.
******************************************************************************/

/*************
** Includes **
*************/
#include <windowsx.h>
#include <stdio.h>
#include <math.h>
#include <d3d.h>
#include "D3DShell.h"	/* D3DShell include */
#include "D3DTools.h"	/* D3DTools include */


/************
** Defines **
************/
#ifndef RELEASE
#define RELEASE(x)	if (x) { (x)->lpVtbl->Release(x); (x)=NULL; }
#endif

#define SWAP(x)		if (x) { x=FALSE; } else x=TRUE

#ifndef PI
#define PI	3.14159f
#endif


/*************
** Typedefs **
*************/
typedef struct _TextureType
{
	BOOL					bSupported;
	LPDIRECTDRAWSURFACE4	lpDDSSystemMemoryTexture;
	LPDIRECTDRAWSURFACE4	lpDDSTexture;
	LPDIRECT3DTEXTURE2		lpTextureInterface;
} TextureType;


/**************
** Variables **
**************/
/* Background TLVertices */
D3DTLVERTEX	SkyTLVertices[4]={
    { 	 0.0f,	   0.0f, 0.9999f, 0.0001f, RGB_MAKE(255, 255, 255), RGBA_MAKE(0, 0, 0, 255), 0.0f, 0.0f },
	{  640.0f,	   0.0f, 0.9999f, 0.0001f, RGB_MAKE(255, 255, 255), RGBA_MAKE(0, 0, 0, 255), 1.0f, 0.0f },
	{  640.0f,	 480.0f, 0.9999f, 0.0001f, RGB_MAKE(255, 255, 255), RGBA_MAKE(0, 0, 0, 255), 1.0f, 1.0f },
	{    0.0f,	 480.0f, 0.9999f, 0.0001f, RGB_MAKE(255, 255, 255), RGBA_MAKE(0, 0, 0, 255), 0.0f, 1.0f }	};

/* Untransformed texture vertices */
float PlaneVertices[3*4]={ 
	-100.0f, 100.0f,  0.0f,
	 100.0f, 100.0f,  0.0f,
	 100.0f, -100.0f, 0.0f,
	-100.0f, -100.0f, 0.0f };

/* Transformed texture vertices */
D3DTLVERTEX	PlaneTLVertices[4]={
	{	0.0f, 0.0f, 0.1f, 10.0f, RGB_MAKE(255, 255, 255), RGBA_MAKE(0, 0, 0, 255), 0.0f, 1.0f	},
	{	0.0f, 0.0f, 0.1f, 10.0f, RGB_MAKE(255, 255, 255), RGBA_MAKE(0, 0, 0, 255), 1.0f, 1.0f	},
	{	0.0f, 0.0f, 0.1f, 10.0f, RGB_MAKE(255, 255, 255), RGBA_MAKE(0, 0, 0, 255), 1.0f, 0.0f	},
	{	0.0f, 0.0f, 0.1f, 10.0f, RGB_MAKE(255, 255, 255), RGBA_MAKE(0, 0, 0, 255), 0.0f, 0.0f	}	};

/* Texture triangle list */
WORD		PlaneTriangles[2][3]={ { 0, 1, 2 }, {2, 3, 0}  };


/* Texture variables */
TextureType			Texture565;
TextureType			Texture555;
TextureType			Texture1555;
TextureType			Texture4444;
TextureType			TextureYUV422;
TextureType			TextureVQ;
TextureType			BackgroundTexture;
TextureType			NotSupportedTexture;
int					nCurrentTexture=1;

/* Booleans values indicating what's enabled or not */
BOOL				bSkyOn=TRUE;
BOOL				bMovingCamera=FALSE;
BOOL				bWobbleOn=TRUE;
BOOL				bBilinearOn=TRUE;
BOOL				bTextOn=TRUE;
BOOL				bNewChoice=TRUE;

/* Rendering variables */
DWORD				dwCurrentWidth, dwCurrentHeight;
DWORD				dwTextureWindow[6];

/***************
** Prototypes **
***************/
BOOL PadControl (void);
void LoadTextures(LPDIRECTDRAW4 lpDD4, LPDIRECT3DDEVICE3 lpDev3);



/****************************************************************************
** InitApplication() is called by D3DShell to enable user to initialise	   **
** his/her application													   **
****************************************************************************/
void InitApplication(HINSTANCE hInstance, HWND hWindow, TCHAR *pszCommandLine)
{
	InitDirectInput(hWindow, hInstance);

	/* Create all texture windows */
	dwTextureWindow[0]=D3DTPrint3DCreateDefaultWindow(3.0f, 78.0f, 80, L"TEXTURE FORMAT : 565", 
		L"The 565 format has a larger range of greens available than \
the red or blue channels. This means it is useful when using textures that need extra colour resolution.");

	dwTextureWindow[1]=D3DTPrint3DCreateDefaultWindow(3.0f, 80.0f, 80, L"TEXTURE FORMAT : 555", 
		L"Each color channel is coded with 5 bits. This format can be used to generate perfect grey variations."); 

	dwTextureWindow[2]=D3DTPrint3DCreateDefaultWindow(3.0f, 78.0f, 80, L"TEXTURE FORMAT : 1555", 
		L"Only one bit of alpha is used to determine what is visible or not. The \
texture can be forced opaque in order to use a generic 16 bits 555 RGB format. This format \
is useful for genarating a smooth greyscale sequence without having alternate bands having \
slight amounts of too much green in them."); 

	dwTextureWindow[3]=D3DTPrint3DCreateDefaultWindow(3.0f, 78.0f, 80, L"TEXTURE FORMAT : 4444", 
		L"This is the generic 16 bits translucent format. It can be used to generate smooth \
translucent edges in a texture."); 

	dwTextureWindow[4]=D3DTPrint3DCreateDefaultWindow(3.0f, 78.0f, 80, L"TEXTURE FORMAT : YUV422", 
		L"The YUV format offers a very high image quality for real-world images like photographs, captured images, video, etc...");
		
	dwTextureWindow[5]=D3DTPrint3DCreateDefaultWindow(3.0f, 78.0f, 80, L"TEXTURE FORMAT : VQ", 
		L"Vector Quantisation (VQ) is a method of compression that finds similar sections or blocks \
of an image, creates a table of the blocks and then encodes the image using indices into that code \
book table. It performs well on high frequency images like text and also on texture surface images.");

}


/****************************************************************************
** QuitApplication() is called by D3DShell to enable user to release      **
** any memory before quitting the program.								   **
****************************************************************************/
void QuitApplication()
{
	/* Delete all 3D windows */
	D3DTPrint3DDeleteAllWindows();

	ReleaseDirectInput();

}


/*******************************************************************************
** UserWindowProc(...) is the application's window messages handler.
** From that function you can process menu inputs, keystrokes, timers, etc...
** When processing keystrokes, DO NOT process ESCAPE key 
** (VK_ESCAPE), as it is already used by D3DShell.
********************************************************************************/
void UserWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_KEYDOWN:	switch(wParam)
							{
								case VK_F3 :	SWAP(bTextOn); break;
								case VK_UP :	if (nCurrentTexture<3) nCurrentTexture+=3;
												break;
								case VK_DOWN :  if (nCurrentTexture>2) nCurrentTexture-=3;
												break;
								case VK_RIGHT :	if (nCurrentTexture<5) nCurrentTexture+=1;
												break;
								case VK_LEFT :  if (nCurrentTexture>0) nCurrentTexture-=1;
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
	}

	/* UP */
	if (GetAnalogY()<64)
	{
		if(Delay>2)
		{
			if (nCurrentTexture<3) nCurrentTexture+=3;
		}
		Delay = 0;
	}

	/* DOWN */  
	if (GetAnalogY()>256-64)
	{
		if(Delay>2)
		{
			if (nCurrentTexture>2) nCurrentTexture-=3;
		}
		Delay = 0;
	}

	/* LEFT */
	if (GetAnalogX()<64)
	{
		if(Delay>2)
		{
			if (nCurrentTexture>0) nCurrentTexture-=1;
		}
		Delay = 0;
	}

	/* RIGHT */
	if (GetAnalogX()>256-64)
	{
		if(Delay>2)
		{
			if (nCurrentTexture<5) nCurrentTexture+=1; 
		}
		Delay = 0;
	}

	/* UP X-PAD */
	if (IsUPKey())
	{
		if(Delay>2)
		{
			if (nCurrentTexture<3) nCurrentTexture+=3;
		}
		Delay = 0;
	}

	/* DOWN X-PAD*/
	if (IsDOWNKey())
	{
		if(Delay>2)
		{
			if (nCurrentTexture>2) nCurrentTexture-=3;
		}
		Delay = 0;
	}

	/* LEFT X-PAD*/
	if (IsLEFTKey())
	{
		if(Delay>2)
		{
			if (nCurrentTexture>0) nCurrentTexture-=1;
		}
		Delay = 0;
	}

	/* RIGHT X-PAD*/
	if (IsRIGHTKey())
	{
		if(Delay>2)
		{
			if (nCurrentTexture<5) nCurrentTexture+=1;   
		}
		Delay = 0;
	}


	/* A button */
	if (IsAKey())
	{
		if(Delay>2)
		{
			bMovingCamera = !bMovingCamera;
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
** RenderScene(...) is the main rendering function. It is called by D3DShell
** for every frame.
** This function should contain a single BeginScene()/EndScene() pair containing
** the rendering functions to call (DrawPrimitive, SetRenderState, etc...)
*******************************************************************************/
BOOL RenderScene(LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DVIEWPORT3 lpView3)
{
	D3DMATRIX			WorldMatrix;
	D3DVECTOR			CamFrom={ 0.0f, 0.0f, 0.0f };
	int					i;
	static D3DVECTOR	CamTo={ 0.0f, 0.0f, 1000.0f };
	static float		r;
	static int			nDelta=0;
	
	if(PadControl()==FALSE) return FALSE; 

	/* Begin Scene */
	lpDev3->lpVtbl->BeginScene(lpDev3);
	
	/* Draw sky primitive */
	if (bSkyOn)
	{
		lpDev3->lpVtbl->SetTexture(lpDev3, 0, BackgroundTexture.lpTextureInterface);
		lpDev3->lpVtbl->DrawIndexedPrimitive(lpDev3, D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, 
											 SkyTLVertices, 4, 
											 (LPWORD)PlaneTriangles, 2*3,
											 D3DDP_WAIT);
	}

	/* Display all textures */
	for (i=0; i<6; i++)
	{
		D3DTMatrixReset(&WorldMatrix);
		if (i==nCurrentTexture && bWobbleOn) D3DTMatrixRotate(&WorldMatrix, 0.2f*(float)sin((float)sin(r)), 
																0.2f*(float)sin((float)cos(r)), 0.0f);
		D3DTMatrixTranslate(&WorldMatrix, (i%3)*300.0f-300.0f, (i/3)*270.0f-70.0f, 1000.0f);
		
		/* Highlight current texture */
		if (i==nCurrentTexture)
		{
			static int		nPreviousTexture=-1;
			static float	fDestX, fDestY, fGapX, fGapY;
			int				nSteps=30;

			/* A new texture has been selected */
			if (nCurrentTexture!=nPreviousTexture) 
			{
				r=0.0f;
				nPreviousTexture=nCurrentTexture;
				
				/* Code for moving camera */
				nDelta=0;
				fDestX=(nCurrentTexture%3)*300.0f-300.0f;
				fDestY=(nCurrentTexture/3)*270.0f-70.0f;
				fGapX=fDestX-CamTo.x;
				fGapY=fDestY-CamTo.y;
			}
			
			/* Move camera destination so it can reach its final position */
			if (bMovingCamera)
			{
				if (nDelta<nSteps)
				{
					CamTo.x+=fGapX/nSteps;
					CamTo.y+=fGapY/nSteps;
					nDelta++;
				}
			}
			else
			{
				CamTo.x=0.0f;
				CamTo.y=0.0f;
				fGapX=fDestX;
				fGapY=fDestY;
				nDelta=0;
			}

			/* Make the texture "wobble" if requested */
			if (bWobbleOn)
			{
				D3DTMatrixTranslate(&WorldMatrix, 0.0f, 0.0f, -100.0f*(float)sin(r));
				r+=0.25f;
			}
			else
			{
				D3DTMatrixTranslate(&WorldMatrix, 0.0f, 0.0f, -100.0f);
			}
		}
		
		/* Transform texture */
		D3DTTransTransformProjectPerspective(&WorldMatrix,
											 4, PlaneVertices, PlaneTLVertices,
											 dwCurrentWidth, dwCurrentHeight,
											 &CamFrom, &CamTo, 0.0f,
											 1.0f, 10000.0f, 50.0f*PI/180.0f, 0.0f);

		switch(i)
		{
		case 0 :	if (!Texture565.bSupported)
						lpDev3->lpVtbl->SetTexture(lpDev3, 0, NotSupportedTexture.lpTextureInterface); 
					else
						lpDev3->lpVtbl->SetTexture(lpDev3, 0, Texture565.lpTextureInterface); 
					break;
		case 1 :	if (!Texture555.bSupported)
						lpDev3->lpVtbl->SetTexture(lpDev3, 0, NotSupportedTexture.lpTextureInterface); 
					else
						lpDev3->lpVtbl->SetTexture(lpDev3, 0, Texture555.lpTextureInterface); 
					break;
		case 2 :	if (!Texture1555.bSupported)
						lpDev3->lpVtbl->SetTexture(lpDev3, 0, NotSupportedTexture.lpTextureInterface); 
					else
					{
						lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
						lpDev3->lpVtbl->SetTexture(lpDev3, 0, Texture1555.lpTextureInterface); 
					}
					break;
		case 3 :	if (!Texture4444.bSupported)
						lpDev3->lpVtbl->SetTexture(lpDev3, 0, NotSupportedTexture.lpTextureInterface); 
					else
					{
						lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
						lpDev3->lpVtbl->SetTexture(lpDev3, 0, Texture4444.lpTextureInterface); 
					}
					break;
		case 4 :	if (!TextureYUV422.bSupported)
						lpDev3->lpVtbl->SetTexture(lpDev3, 0, NotSupportedTexture.lpTextureInterface); 
					else
						lpDev3->lpVtbl->SetTexture(lpDev3, 0, TextureYUV422.lpTextureInterface); 
					break;
		case 5 :	if (!TextureVQ.bSupported)
						lpDev3->lpVtbl->SetTexture(lpDev3, 0, NotSupportedTexture.lpTextureInterface); 
					else
					{
						lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
						lpDev3->lpVtbl->SetTexture(lpDev3, 0, TextureVQ.lpTextureInterface);
					}
					break;
		}

		/* Draw texture plane */
		lpDev3->lpVtbl->DrawIndexedPrimitive(lpDev3, D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, 
											 PlaneTLVertices, 4, 
											 (LPWORD)PlaneTriangles, 3*2,
											 D3DDP_WAIT);
		
		/* Set alpha renderstate back to FALSE */
		lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
	}

	/* Display 3D text if required */
	if (bTextOn)
	{
		/* Display current texture information window */
		D3DTPrint3DDisplayWindow(dwTextureWindow[nCurrentTexture]);
	}
		
	
	/* End Scene */
    lpDev3->lpVtbl->EndScene(lpDev3);


	/* No problem occured */
	return TRUE;
}
	

/*******************************************************************************
** InitView() is called by D3DShell each time a rendering variable is changed
** in the Shell menu (Z-Buffer On/Off, resolution change, buffering mode...)
** In this function one should initialise all variables that are dependant on
** general rendering variables (screen mode, 3D device, etc...)
*******************************************************************************/
BOOL InitView(LPDIRECTDRAW4 lpDD4, LPDIRECT3D3 lpD3D3, LPDIRECT3DDEVICE3 lpDev3,
              LPDIRECT3DVIEWPORT3 lpView3, DWORD dwWidth, DWORD dwHeight)
{
BOOL	bDither=FALSE;


	/* Update viewport dimensions */
	dwCurrentWidth=dwWidth;
	dwCurrentHeight=dwHeight;
	
	/* Init Print3D functions */
	D3DTPrint3DSetTextures(lpDev3, lpDD4, dwWidth, dwHeight);

	LoadTextures(lpDD4, lpDev3);

	/* Update Sky vertices with current viewport size */
	SkyTLVertices[0].sx=0.0f;
	SkyTLVertices[0].sy=0.0f;
	SkyTLVertices[1].sx=(float)dwWidth;
	SkyTLVertices[1].sy=0.0f;
	SkyTLVertices[2].sx=(float)dwWidth;
	SkyTLVertices[2].sy=(float)dwHeight;
	SkyTLVertices[3].sx=0.0f;
	SkyTLVertices[3].sy=(float)dwHeight;
	
	/* Default render states */
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
	lpDev3->lpVtbl->SetRenderState(lpDev3, D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
	lpDev3->lpVtbl->SetTextureStageState(lpDev3, 0, D3DTSS_MAGFILTER, D3DTFG_LINEAR);

	/* No problem occured */
	return TRUE;
}


/*******************************************************************************
** ReleaseView(...) is called by D3DShell each time a rendering variable is
** changed. It is the direct companion to InitView(...), as its purpose is to
** release or destroy any variables or processes allocated in InitView.
** NOTE : Textures created with the D3DShellLoadBMP(...) function do *NOT* need
** to be released, as it is already taken care of by D3DShell.
*******************************************************************************/
void ReleaseView(LPDIRECT3DVIEWPORT3 lpView3)
{
	/* Release all textures */

	/* Background texture */
	RELEASE(BackgroundTexture.lpDDSTexture); 
	RELEASE(BackgroundTexture.lpTextureInterface);
	RELEASE(BackgroundTexture.lpDDSSystemMemoryTexture);

	/* 8888 texture */
	RELEASE(TextureVQ.lpDDSTexture); 
	RELEASE(TextureVQ.lpTextureInterface);
	RELEASE(TextureVQ.lpDDSSystemMemoryTexture);

	/* YUV422 texture */
	RELEASE(TextureYUV422.lpDDSTexture); 
	RELEASE(TextureYUV422.lpTextureInterface);
	RELEASE(TextureYUV422.lpDDSSystemMemoryTexture);

	/* 4444 texture */
	RELEASE(Texture4444.lpDDSTexture); 
	RELEASE(Texture4444.lpTextureInterface);
	RELEASE(Texture4444.lpDDSSystemMemoryTexture);

	/* 1555 texture */
	RELEASE(Texture1555.lpDDSTexture); 
	RELEASE(Texture1555.lpTextureInterface);
	RELEASE(Texture1555.lpDDSSystemMemoryTexture);

	/* 555 texture */
	RELEASE(Texture555.lpDDSTexture); 
	RELEASE(Texture555.lpTextureInterface);
	RELEASE(Texture555.lpDDSSystemMemoryTexture);

	/* 565 texture */
	RELEASE(Texture565.lpDDSTexture); 
	RELEASE(Texture565.lpTextureInterface);
	RELEASE(Texture565.lpDDSSystemMemoryTexture);
	
	/* Release textures from Print3D */
	D3DTPrint3DReleaseTextures();
}
/*******************************************************************************
 * Function Name  : LoadTextures
 * Input		  : 
 * Returns        : 
 * Global Used    : 
 * Description    : Converts and loads different textures formats.
 *                  The conversion code is included in the D3DTools library.
 *                  (See D3DTools\D3DTTextures.c)
 *******************************************************************************/
void LoadTextures(LPDIRECTDRAW4 lpDD4, LPDIRECT3DDEVICE3 lpDev3)
{
int bDither = FALSE;
DDPIXELFORMAT PixelFormat;

	/* Initialise textures variables */
	memset(&Texture565,	0, sizeof(TextureType));
	memset(&Texture555,	0, sizeof(TextureType));
	memset(&Texture1555, 0,	sizeof(TextureType));
	memset(&Texture4444, 0, sizeof(TextureType));
	memset(&TextureYUV422, 0, sizeof(TextureType));
	memset(&TextureVQ, 0,	sizeof(TextureType));
	memset(&BackgroundTexture, 0, sizeof(TextureType));
	
	/* Enumerate all texture formats */
	D3DTTextureListFormats(lpDev3);

	
	/* First load background texture */
	if (!D3DTTextureLoadBMP(lpDD4, lpDev3, L"CLOUDS", NULL,
						    FALSE, D3DTAutoMipmap_None, D3DTTextureBestOpaqueFormat(TRUE), 
						    TRUE,
						    &BackgroundTexture.lpDDSTexture, &BackgroundTexture.lpTextureInterface))
	{
		OutputDebugString(L"Failed to load background texture\n");
	}
	
			
	/* 565 format */
	memset(&PixelFormat, 0, sizeof(DDPIXELFORMAT));
	PixelFormat.dwSize				= sizeof(DDPIXELFORMAT);
	PixelFormat.dwFlags				= DDPF_RGB;
	PixelFormat.dwRGBBitCount		= 16;
	PixelFormat.dwRBitMask			= 0x0000F800;
	PixelFormat.dwGBitMask			= 0x000007E0;
	PixelFormat.dwBBitMask			= 0x0000001F;

	Texture565.bSupported=TRUE;
	if (!D3DTTextureLoadBMP(lpDD4, lpDev3, L"LEAF5", NULL,
							    bDither, D3DTAutoMipmap_None, &PixelFormat, 
							    TRUE,
							    &Texture565.lpDDSTexture, &Texture565.lpTextureInterface))
	{
		OutputDebugString(L"Failed to load 565 texture\n");
	}

	/* 555 format (to be used as opaque) */
	memset(&PixelFormat, 0, sizeof(DDPIXELFORMAT));
	PixelFormat.dwSize				= sizeof(DDPIXELFORMAT);
	PixelFormat.dwFlags				= DDPF_RGB | DDPF_ALPHAPIXELS;
	PixelFormat.dwRGBBitCount		= 16;
	PixelFormat.dwRGBAlphaBitMask	= 0x00008000;
	PixelFormat.dwRBitMask			= 0x00007C00;
	PixelFormat.dwGBitMask			= 0x000003E0;
	PixelFormat.dwBBitMask			= 0x0000001F;

	Texture555.bSupported=TRUE;
	if (!D3DTTextureLoadBMP(lpDD4, lpDev3, L"POWERVR", L"POWERVR",
							    bDither, D3DTAutoMipmap_None, &PixelFormat, 
							    TRUE,
							    &Texture555.lpDDSTexture, &Texture555.lpTextureInterface))
	{
		OutputDebugString(L"Failed to load 555 texture\n");
	}


	/* 1555 format */
	memset(&PixelFormat, 0, sizeof(DDPIXELFORMAT));
	PixelFormat.dwSize				= sizeof(DDPIXELFORMAT);
	PixelFormat.dwFlags				= DDPF_RGB | DDPF_ALPHAPIXELS;
	PixelFormat.dwRGBBitCount		= 16;
	PixelFormat.dwRGBAlphaBitMask	= 0x00008000;
	PixelFormat.dwRBitMask			= 0x00007C00;
	PixelFormat.dwGBitMask			= 0x000003E0;
	PixelFormat.dwBBitMask			= 0x0000001F;
	
	Texture1555.bSupported=TRUE;
	if (!D3DTTextureLoadBMP(lpDD4, lpDev3, L"PUNCH", L"tPUNCH",
								    bDither, D3DTAutoMipmap_None, &PixelFormat, 
								    TRUE,
								    &Texture1555.lpDDSTexture, &Texture1555.lpTextureInterface))
	{
			OutputDebugString(L"Failed to load 1555 texture\n");
	}

	

	/* 4444 format */
	memset(&PixelFormat, 0, sizeof(DDPIXELFORMAT));
	PixelFormat.dwSize				= sizeof(DDPIXELFORMAT);
	PixelFormat.dwFlags				= DDPF_RGB | DDPF_ALPHAPIXELS;
	PixelFormat.dwRGBBitCount		= 16;
	PixelFormat.dwRGBAlphaBitMask	= 0x0000F000;
	PixelFormat.dwRBitMask			= 0x00000F00;
	PixelFormat.dwGBitMask			= 0x000000F0;
	PixelFormat.dwBBitMask			= 0x0000000F;

	Texture4444.bSupported=TRUE;
	if (!D3DTTextureLoadBMP(lpDD4, lpDev3, L"TRANSLUCENT", L"TTRANSLUCENT",
								    bDither, D3DTAutoMipmap_None, &PixelFormat, 
								    TRUE,
								    &Texture4444.lpDDSTexture, &Texture4444.lpTextureInterface))
	{
			OutputDebugString(L"Failed to load 4444 texture\n");
	}
		
	/* YUV422 format */
	TextureYUV422.bSupported=TRUE;
	D3DTTextureLoadYUV (lpDev3, lpDD4, L"LENNA", &TextureYUV422.lpDDSTexture, &TextureYUV422.lpTextureInterface);

	/* VQ format (Mimapping not supported) 
	 * The binary resource (with a PVRT header) has already been compressed.
	 */
	TextureVQ.bSupported=TRUE;
	D3DTTextureLoadVQ (lpDev3, lpDD4, L"BIN_VQ", &TextureVQ.lpDDSTexture, &TextureVQ.lpTextureInterface);

	
}
