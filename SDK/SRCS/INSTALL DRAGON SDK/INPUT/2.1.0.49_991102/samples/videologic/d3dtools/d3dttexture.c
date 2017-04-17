/*****************************************************************************
  Name : D3DTTexture.c
  Date : November 1998
  Platform : ANSI compatible
 
  * Description : 
  This file is part of the TOOLS library (D3DTools.lib) used
  with the SDK demos for PowerVR series 2.

  Set of functions used in texturing.
  (The image data has to be a 24-bit bitmap loaded as a resource).  

  Copyright : 1999 by Imagination Technologies Limited. All rights reserved.
******************************************************************************/
#include <stdio.h>
#include <math.h>
#include <d3d.h>
#include "D3DTTexture.h"

#define WCE_ZERO_MEMORY(a,b) memset(a,0,b);
#define WCE_DEBUG(x) OutputDebugString((unsigned short *)x);

/***********
** Pragma **
***********/
/* Disable conversion warning (e.g. float to float loss of data) */
#pragma warning(disable : 4244)  

/*********************
** Internal typedef **
*********************/
typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
} PixelMap;

/*********************
** Global variables **
*********************/
D3DTTextureFormatType		D3DTTextureFormat[30];
static int					nTextureFormat=-1;

/*************************************
** Prototypes of internal functions **
*************************************/
static BOOL				CopyBitmapToYUVSurface(DWORD *pTarget, BITMAP *pBm);
static BOOL				CopyBitmapToSurface(LPDIRECTDRAWSURFACE4 lpDDS, HBITMAP hBitmap, HBITMAP hBitmapTrans);
static BOOL				CreateAllMipmapLevels(LPDIRECTDRAWSURFACE4 lpDDSTexture, int nMipmapType);
static BOOL				CreateFourierMipmapLevels(LPDIRECTDRAW4 lpDD4, LPDIRECT3DDEVICE3 lpDev3, BITMAP *pBm, BITMAP *pBmTrans, LPDIRECTDRAWSURFACE4 lpDDSSystemMemorySurface, int nOrder);
static void				DitherBitmap(int XDim, int YDim, DDPIXELFORMAT *lpddPixelFormat, unsigned char *pBitmapData, unsigned char *pTranslucentBitmapData);
static BOOL				CreateNextMipmapLevel2x2(LPDIRECTDRAWSURFACE4 lpDDSTextureSurface);
static BOOL				CreateNextMipmapLevel4x4(LPDIRECTDRAWSURFACE4 lpDDSTextureSurface);
static void				ComputeTransparentPixels(BITMAP *pBm, BITMAP *pBmTrans);
static void				MirrorExpandBitmap(float **Red, float **Green, float **Blue, float **Alpha, HBITMAP hBitmap, HBITMAP hTranslucentBitmap);
static void				ApplyLowPassFilter(float **data, float *speq, DWORD dwSize, float fCutOff, int nOrder);
static float			**AllocateSquareMatrix(long nSize);
static void				FreeSquareMatrix(float **ppMatrix, long nSize);
static float			*AllocateVector(long nSize);
static void				FreeVector(float *pVector, long nSize);
static void				RealFFT2D(float **data, float *speq, unsigned long nn2, unsigned long nn3, int isign);
static int				fround(float fValue);
static HRESULT WINAPI	EnumTextureFormatsCallback(LPDDPIXELFORMAT lpddPixelFormat, LPVOID lpContext);
static BOOL				PaletteFromBitmap(LPDIRECTDRAW4 lpDD4, HBITMAP hBitmap, LPDIRECTDRAWPALETTE *lplpDDPPalette);
static void				GetPixelFormatInfo(DDPIXELFORMAT *pPixelFormat, BYTE *pRedBits, BYTE *pGreenBits, BYTE *pBlueBits, BYTE *pAlphaBits, BYTE *pLeftR,	BYTE *pLeftG, BYTE *pLeftB,	BYTE *pLeftA, BYTE *pRightR, BYTE *pRightG, BYTE *pRightB, BYTE *pRightA);
__inline void			GetColumn(PixelMap *lpPixel, int *pRed, int *pGreen, int *pBlue, DWORD dwSourceWidth);
__inline void			GetColumnWithoutTop(PixelMap *lpPixel, int *pRed, int *pGreen, int *pBlue, DWORD dwSourceWidth);
__inline void			GetColumnWithoutBottom(PixelMap *lpPixel, int *pRed, int *pGreen, int *pBlue, DWORD dwSourceWidth);
__inline void			GetColumnAlpha(PixelMap *lpPixel, int *pRed, int *pGreen, int *pBlue, int *pAlpha, DWORD dwSourceWidth);
__inline void			GetColumnAlphaWithoutTop(PixelMap *lpPixel, int *pRed, int *pGreen, int *pBlue, int *pAlpha, DWORD dwSourceWidth);
__inline void			GetColumnAlphaWithoutBottom(PixelMap *lpPixel, int *pRed, int *pGreen, int *pBlue, int *pAlpha, DWORD dwSourceWidth);

void					GetResourceBitmap(BITMAP *bm, LPCWSTR lpName);
int						GetDIBColorTable(HBITMAP hBitmap, RGBQUAD *adw);

void					ConvertHighmapToBumpmap(BITMAP *bm, unsigned short *pTarget);


/*******************************************************************************
 * VQ FUNCTIONS 
 *******************************************************************************/
#define VQ_TEXTURE              0x00000300
#define VQ_MIPMAP               0x00000400
#define VQ_RGBA_5551            0x00000300
#define VQ_RGBA_5650            0x00000301
#define VQ_RGBA_4444            0x00000302

/*******************************************************************************
 * Function Name  : D3DTTextureLoadVQ
 * Inputs		  : 
 * Global Used    : 
 * Description    : This function loads a VQ texture already compressed on video 
 *                  memory. To create a VQ file, use any of the tools suplied in
 *                  the SDK.
 *******************************************************************************/
BOOL D3DTTextureLoadVQ(LPDIRECT3DDEVICE3 lpDev3, LPDIRECTDRAW4 lpDD4, TCHAR *ResourceVQ, 
							 LPDIRECTDRAWSURFACE4 *lplpDDSTextureSurface, LPDIRECT3DTEXTURE2 *lplpD3DTexture2)
{
HRESULT					hres;
LPDIRECTDRAWSURFACE4	lpDDS=NULL;
DDSURFACEDESC2			ddsd;
DDPIXELFORMAT			PixelFormat;
WORD					x, y;
DWORD					i = 0, dwMemoryUsedByTexture=0, dwDataSize, dwFormat;
LPDWORD					lpdwSource, lpdwTarget;
unsigned short			pszString[300];
unsigned char			*VQRowData;
HGLOBAL					hGlobal;
HRSRC					hResource;

  /* Read VQ row data from resource */
	hResource = FindResource(GetModuleHandle(NULL), ResourceVQ, RT_RCDATA);
    if (!hResource) 
    {
       WCE_DEBUG(L"D3DTTextureLoadVQ: failed to find the VQ resource.\n");
       return 0;
    }

	hGlobal = LoadResource(GetModuleHandle(NULL), hResource);
    if (!hGlobal) 
    {
        WCE_DEBUG(L"D3DTTextureLoadVQ: failed to load the VQ resource.\n");
        return 0;
    }

	VQRowData = (LPBYTE)LockResource(hGlobal);
    if (!VQRowData) 
    {
        WCE_DEBUG(L"D3DTTextureLoadVQ: failed to lock the VQ resource.\n");
        return 0;
    }
   
	/* Look for the header in the first 500 bytes.
	 * If it doesn't exist, it is not a PVR format.
	 */
	while (i++<500)
	{
		if ( *(VQRowData+0) == 'P' && *(VQRowData+1) == 'V' && *(VQRowData+2) == 'R' &&	 *(VQRowData+3) == 'T')
		{
			break;
		}
		VQRowData++;
	}

	/* Is the tag correct? */
	if (i==500)
	{
		WCE_DEBUG(L"Failed to recognise the resource file as a PVR file\n");
        return 0;
	}
	

    /* Get the size of the image data */
	dwDataSize = (DWORD)*(((LPDWORD)VQRowData) + 1);
    dwDataSize -= 8;
	dwDataSize /= 4;

	/* Get the pixel format of the image */
    dwFormat = *(((LPDWORD)VQRowData) + 2);

    /* Get the dimensions of the image */
	x = (WORD)*(((LPWORD)VQRowData) + 6);
	y = (WORD)*(((LPWORD)VQRowData) + 7);
   
 
	/* VQ Mipmapped not supported in Dragon v2.0 */
    if (dwFormat & VQ_MIPMAP) 
    {
        WCE_DEBUG(L"D3DTTextureLoadVQ: VQ mipmapped not supported.\n");
        return 0;
    }
	
	/* Debug output */
	wsprintf(pszString,  TEXT("Loading VQ texture : %u*%u  %d %d %d\n"), x, y, dwFormat, dwDataSize, i);
	WCE_DEBUG(pszString);

	/* Security : discard any size above 1024 pixels */
	if (x>1024 || y>1024)
	{
		WCE_DEBUG(L"Texture size too large\n");
		return 0;
	}

	/* Initialise PixelFormat structure */
	memset(&PixelFormat, 0, sizeof(DDPIXELFORMAT));
	PixelFormat.dwSize	  = sizeof(DDPIXELFORMAT);
	PixelFormat.dwFlags	  = DDPF_RGB | DDPF_COMPRESSED;

	switch (dwFormat)
	{
	default:
	case VQ_RGBA_5650:
        PixelFormat.dwRGBBitCount = 16;
        PixelFormat.dwRBitMask = 0x0000F800;
        PixelFormat.dwGBitMask = 0x000007E0;
        PixelFormat.dwBBitMask = 0x0000001F;
		break;

	case VQ_RGBA_4444:
        PixelFormat.dwFlags |= DDPF_ALPHAPIXELS;
        PixelFormat.dwRGBBitCount = 16;
        PixelFormat.dwRBitMask = 0x00000F00;
        PixelFormat.dwGBitMask = 0x000000F0;
        PixelFormat.dwBBitMask = 0x0000000F;
        PixelFormat.dwRGBAlphaBitMask = 0x0000F000;
		break;

	case VQ_RGBA_5551:
        PixelFormat.dwFlags |= DDPF_ALPHAPIXELS;
        PixelFormat.dwRGBBitCount = 16;
        PixelFormat.dwRBitMask	= 0x00007C00;
		PixelFormat.dwGBitMask	= 0x000003E0;
		PixelFormat.dwBBitMask	= 0x0000001F;
		PixelFormat.dwRGBAlphaBitMask	= 0x00008000;
		break;
     }
 
	/* Create texture surface */
 	memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
    ddsd.dwSize=sizeof(DDSURFACEDESC2);
	ddsd.dwFlags=DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    ddsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE |  DDSCAPS_VIDEOMEMORY;
    ddsd.dwHeight=x;
    ddsd.dwWidth=y;
	ddsd.ddpfPixelFormat=PixelFormat;

	hres=lpDD4->lpVtbl->CreateSurface(lpDD4, &ddsd, &lpDDS, NULL);
	if (hres!=DD_OK) 
	{
		WCE_DEBUG(TEXT("Failed to create VQ surface\n"));
		return 0;
	}

    /* Initialise surface */
	memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
    ddsd.dwSize=sizeof(DDSURFACEDESC2);
	
	/* Lock texture surface to fill it */
    hres=lpDDS->lpVtbl->Lock(lpDDS, NULL, &ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT | DDLOCK_COMPRESSED, NULL); 
    if (hres!=DD_OK) 
	{
		WCE_DEBUG(TEXT("Failed to lock texture surface\n"));
		return 0;
	}
	/* Copy the image data into the surface. */
   	lpdwSource = (LPDWORD)(((LPDWORD)VQRowData) + 4);
	lpdwTarget = (LPDWORD)ddsd.lpSurface;

	for (i = 0; i<dwDataSize; i++) 
	{
        lpdwTarget[i] = lpdwSource[i];
    }

    /* Unlock texture surface because we're done filling it */
	hres=lpDDS->lpVtbl->Unlock(lpDDS, NULL);
	if (hres!=DD_OK)
	{
		WCE_DEBUG(TEXT("Unlock failed in LoadTexture\n"));
		return 0;
	}
  
	lplpDDSTextureSurface = &lpDDS;

	hres=(*lplpDDSTextureSurface)->lpVtbl->QueryInterface(*(lplpDDSTextureSurface), &IID_IDirect3DTexture2,(LPVOID*)lplpD3DTexture2);
	
	if (hres!=DD_OK) 
	{
		WCE_DEBUG(TEXT("QueryInterface failed\n"));
		return 0;
	}


	WCE_DEBUG(TEXT("VQ Load OK!\n\n"));
	
	/* Return OK */
    return TRUE;
}
/*******************************************************************************
 * YUV FUNCTIONS 
 *******************************************************************************/
/*******************************************************************************
 * Function Name  : D3DTTextureLoadYUV
 * Inputs		  : 
 * Global Used    : 
 * Description    : Converts a 24bit Bitmat to a YUV format and load it on video memory.
 *******************************************************************************/
BOOL D3DTTextureLoadYUV(LPDIRECT3DDEVICE3 lpDev3, LPDIRECTDRAW4 lpDD4, LPCWSTR lpName, 
							 LPDIRECTDRAWSURFACE4 *lplpDDSTextureSurface, LPDIRECT3DTEXTURE2 *lplpD3DTexture2)
{
	HRESULT					hres;
	LPDIRECTDRAWSURFACE4	lpSrcTextureSurf=NULL;
	LPDIRECTDRAWSURFACE4	lpDDS=NULL;
	LPDIRECT3DTEXTURE2		lpSrcTexture=NULL;
	DDSURFACEDESC2			ddsd;
	DDPIXELFORMAT			PixelFormat;
	BITMAP					bm;
	DWORD					x, y;
	DWORD					dwMemoryUsedByTexture=0;
	unsigned short			pszString[300];

	
	/* Load texture*/
	GetResourceBitmap(&bm,lpName);

	/* Get width and height of bitmap */
	x=bm.bmWidth;
	y=bm.bmWidth;

	/* Debug output */
	wsprintf(pszString,  TEXT("\nLoading YUV texture : %s (%u*%u)\n"), lpName, x, y);
	WCE_DEBUG(pszString);

	/* Security : discard any size above 1024 pixels */
	if (x>1024 || y>1024)
	{
		WCE_DEBUG(L"Texture size too large\n");
		return 0;
	}

	/* Initialise PixelFormat structure */
	memset(&PixelFormat, 0, sizeof(DDPIXELFORMAT));
	PixelFormat.dwSize	  = sizeof(DDPIXELFORMAT);
	PixelFormat.dwFlags	  = DDPF_YUV  | DDPF_FOURCC;
	PixelFormat.dwFourCC  = MAKEFOURCC('U', 'Y', 'V', 'Y');
	PixelFormat.dwYUVBitCount = 16;
	
	/* Create texture surface */
    memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
    ddsd.dwSize=sizeof(DDSURFACEDESC2);
    ddsd.dwFlags=DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    ddsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE | DDSCAPS_VIDEOMEMORY;
    ddsd.dwHeight=x;
    ddsd.dwWidth=y;
	ddsd.ddpfPixelFormat=PixelFormat;

	hres=lpDD4->lpVtbl->CreateSurface(lpDD4, &ddsd, &lpDDS, NULL);
	if (hres!=DD_OK) 
	{
		WCE_DEBUG(TEXT("Failed to create YUV surface\n"));
		return 0;
	}

	/* Lock texture surface to fill it */
    hres=lpDDS->lpVtbl->Lock(lpDDS, NULL, &ddsd, DDLOCK_WAIT , NULL); 
    if (hres!=DD_OK) 
	{
		WCE_DEBUG(TEXT("Failed to lock texture surface\n"));
		return 0;
	}

	/* Copy the image data into the surface. */
   	CopyBitmapToYUVSurface((DWORD *)ddsd.lpSurface , &bm);

    /* Unlock texture surface because we're done filling it */
	hres=lpDDS->lpVtbl->Unlock(lpDDS, NULL);
	if (hres!=DD_OK)
	{
		WCE_DEBUG(TEXT("Unlock failed in LoadTexture\n"));
		return 0;
	}	

    lplpDDSTextureSurface = &lpDDS;

	hres=(*lplpDDSTextureSurface)->lpVtbl->QueryInterface(*(lplpDDSTextureSurface), &IID_IDirect3DTexture2,(LPVOID*)lplpD3DTexture2);
	
	if (hres!=DD_OK) 
	{
		WCE_DEBUG(TEXT("QueryInterface failed\n"));
		return 0;
	}

	WCE_DEBUG(TEXT("YUV Load OK!\n\n"));
	
	/* Return OK */
    return TRUE;
}
/*******************************************************************************
 * Function Name  : CopyBitmapToYUVSurface
 * Inputs		  : *pBm
 * Input/Output   : lpDDS
 * Returns		  : TRUE or FALSE
 * Global Used    : None
 * Description    : Function that copy a bitmap to a DirectDraw YUV surface.
 *					The YUV format is stored in the FOURCC code of the texture
 *					surface.
 *
 *******************************************************************************/
BOOL CopyBitmapToYUVSurface(DWORD *pTarget, BITMAP *pBm)
{
   	DWORD				dwWidth, dwHeight;
	DWORD				i, j;
	DWORD				*lp32b;
	BYTE				*lpSrcPointer;
	BYTE				R, B, G;
	DWORD				Y0, Y1, U, V;


	/* Get width and height of bitmap */
	dwWidth=pBm->bmWidth;
	dwHeight=pBm->bmHeight;

	/* Loop through y values from top to bottom */
	for (i=0; i<dwHeight; i++)
	{
		
			/* Compute source and destination pointers */
			lpSrcPointer = (BYTE *)pBm->bmBits + i*(3*dwWidth);
			lp32b =		   (DWORD *)pTarget + i*(dwWidth/2);


			/* Look through x values from left to right */
			for (j=0; j<dwWidth; j+=2)
			{
				/* Get RGB of first pixel */
				R = *lpSrcPointer++;
				G = *lpSrcPointer++;
				B = *lpSrcPointer++;

				/* Compute Y0 and U for first pixel */
				Y0= (DWORD)(0.29f*R + 0.57f*G + 0.14f*B);
				U= (DWORD)(128.0f - 0.14f*R - 0.29f*G + 0.43f*B);

				/* Get RGB of second pixel */
				R = *lpSrcPointer++;
				G = *lpSrcPointer++;
				B = *lpSrcPointer++;

				/* Compute Y1 and V for second pixel */
				Y1= (DWORD)(0.29f*R + 0.57f*G + 0.14f*B);
				V= (DWORD)(128.0f + 0.36f*R - 0.29f*G - 0.07f*B);

				/* Write on the video surface the values corresponding to the YUV FOURCC code */
				*lp32b++  = ((Y0<<24)| (U<<16) | (Y1<<8) | V);
			}

	}


	/* No problem occured */
	return TRUE;
}
/*******************************************************************************
 * BUMPMAP FUNCTIONS 
 *******************************************************************************/
/*******************************************************************************
 * Function Name  : D3DTTextureLoadBumpmap
 * Inputs		  : 
 * Global Used    : 
 * Description    : Loads a highmap and converts it to a bumpmap format.
 *******************************************************************************/
BOOL D3DTTextureLoadBumpmap(LPDIRECT3DDEVICE3 lpDev3, LPDIRECTDRAW4 lpDD4, LPCWSTR lpName, 
							 LPDIRECTDRAWSURFACE4 *lplpDDSTextureSurface, LPDIRECT3DTEXTURE2 *lplpD3DTexture2)
{
	HRESULT					hres;
	LPDIRECTDRAWSURFACE4		lpSrcTextureSurf=NULL;
	LPDIRECTDRAWSURFACE4		lpDDS=NULL;
	LPDIRECT3DTEXTURE2		lpSrcTexture=NULL;
	DDSURFACEDESC2			ddsd;
	DDPIXELFORMAT			PixelFormat;
	BITMAP					bm;
	DWORD					x, y;
	DWORD					dwMemoryUsedByTexture=0;
	unsigned short			pszString[300];

	
	/* Load texture*/
	GetResourceBitmap(&bm,lpName);

	/* Get width and height of bitmap */
	x=bm.bmWidth;
	y=bm.bmWidth;

	/* Debug output */
	wsprintf(pszString,  TEXT("Loading Bumpmap texture : %s (%u*%u)\n"), lpName, x, y);
	WCE_DEBUG(pszString);

	/* Security : discard any size above 1024 pixels */
	if (x>1024 || y>1024)
	{
		WCE_DEBUG(L"Texture size too large\n");
		return 0;
	}

	/* Initialise PixelFormat structure */
	memset(&PixelFormat, 0, sizeof(DDPIXELFORMAT));
	PixelFormat.dwSize	  = sizeof(DDPIXELFORMAT);
	PixelFormat.dwFlags	  = DDPF_FOURCC;
	PixelFormat.dwFourCC  = MAKEFOURCC('P','N','B','M');
 
	/* Create texture surface */
    memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
    ddsd.dwSize=sizeof(DDSURFACEDESC2);
    ddsd.dwFlags=DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    ddsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE | DDSCAPS_SYSTEMMEMORY;
    ddsd.dwHeight=x;
    ddsd.dwWidth=y;
	ddsd.ddpfPixelFormat=PixelFormat;

	hres=lpDD4->lpVtbl->CreateSurface(lpDD4, &ddsd, &lpDDS, NULL);
	if (hres!=DD_OK) 
	{
		WCE_DEBUG(TEXT("Failed to create Bumpmap surface\n"));
		return 0;
	}
	
    /* Initialise surface */
	memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
    ddsd.dwSize=sizeof(DDSURFACEDESC2);
	
	/* Lock texture surface to fill it */
    hres=lpDDS->lpVtbl->Lock(lpDDS, NULL, &ddsd, DDLOCK_WAIT, NULL); 
    if (hres!=DD_OK) 
	{
		WCE_DEBUG(TEXT("Failed to lock texture surface\n"));
		return 0;
	}

	/* Convert and write data */
	ConvertHighmapToBumpmap	(&bm, (unsigned short *)ddsd.lpSurface);

    /* Unlock texture surface because we're done filling it */
	hres=lpDDS->lpVtbl->Unlock(lpDDS, NULL);
	if (hres!=DD_OK)
	{
		WCE_DEBUG(TEXT("Unlock failed in LoadTexture\n"));
		return 0;
	}
    
	lpSrcTextureSurf=lpDDS;

	/* QueryInterface for a Direct3DTexture2 interface */
	hres=lpSrcTextureSurf->lpVtbl->QueryInterface(lpSrcTextureSurf, &IID_IDirect3DTexture2,(LPVOID*)&lpSrcTexture);
	if (hres!=DD_OK) 
	{
		WCE_DEBUG(TEXT("QueryInterface failed\n"));
		return 0;
	}

	/* Get surface description */
	hres=lpSrcTextureSurf->lpVtbl->GetSurfaceDesc(lpSrcTextureSurf, &ddsd);
	if (hres!=DD_OK) 
	{
		WCE_DEBUG(TEXT("GetSurfaceDesc failed\n"));
		return 0;
	}
    
    /* Create texture surface */
	memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
    ddsd.dwSize=sizeof(DDSURFACEDESC2);
    ddsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE | DDSCAPS_ALLOCONLOAD |DDSCAPS_VIDEOMEMORY;
    ddsd.dwHeight=x;
    ddsd.dwWidth=y;
	ddsd.ddpfPixelFormat=PixelFormat;
	ddsd.dwFlags=DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    hres=lpDD4->lpVtbl->CreateSurface(lpDD4, &ddsd, (LPDIRECTDRAWSURFACE4 *)lplpDDSTextureSurface, NULL);
	if (hres!=DD_OK) 
	{
		WCE_DEBUG(TEXT("CreateSurface failed\n"));
		return 0;
	}

	/* QueryInterface for a Direct3DTexture2 interface */
	hres=(*lplpDDSTextureSurface)->lpVtbl->QueryInterface((*lplpDDSTextureSurface), &IID_IDirect3DTexture2,(LPVOID*)lplpD3DTexture2);
    if (hres!=DD_OK) 
	{
		WCE_DEBUG(TEXT("QueryInterface failed\n"));
		return 0;
	}

	/* Load texture into memory */
	hres=(*lplpD3DTexture2)->lpVtbl->Load((*lplpD3DTexture2), lpSrcTexture);
	if (hres!=DD_OK)
	{
		WCE_DEBUG(TEXT("Load failed\n"));
		return 0;
	}
      
	/* Release surfaces and memory */
	RELEASE(lpSrcTexture);
    RELEASE(lpSrcTextureSurf);


	WCE_DEBUG(TEXT("Bumpmap Load OK!\n"));
	
	/* Return OK */
    return TRUE;
}

/*******************************************************************************
 * Function Name  : ConvertHighmapToBitmap
 * Inputs		  : 
 * Global Used    : 
 * Description    : 
 * Note			  :	This code comes from Microsoft (with some small changes)
 *******************************************************************************/
void ConvertHighmapToBumpmap(BITMAP *bm, unsigned short *pTarget )
{
unsigned char *pSource;
int rows, cols;
int u,v,u1,v1, u2, v2;			
unsigned char h, hv1, hv2, hu1, hu2, h10, h01;
float dH01,dH10;		// (h-h01) and (h-h10) scaled
unsigned char R,S;		

	pSource = (unsigned char *)bm->bmBits;
	rows	= (int)bm->bmHeight;
	cols	= (int)bm->bmWidth * 3; /* 24 bits Bitmap only */
	
	for(v=0; v<rows; v++)
	{
		v1=(v-1);
		if (v==0) v1 = rows-1; // wrap around	

		v2=(v+1);
		if (v2==rows) v2 = 0; // wrap around

		for(u=0; u<cols; u+=3)
		{
			u1=(u-3);
			if (u==0) u1 = cols-3; // wrap around	

			u2=(u+3);
			if (u==cols) u2 = 0; // wrap around

			// Read the height map
			h   =  pSource[v*cols  + u];
			hv1 =  pSource[v1*cols + u];
			hv2 =  pSource[v2*cols + u];
			hu1 =  pSource[v*cols + u1];
			hu2 =  pSource[v*cols + u2];

			h10 = hu2;
			h01 = hv2;

			// Check for special case first
			if(( hv2 == hv1 ) && ( hu1 == hu2 ))
			{
				// height map is flat here
				*pTarget++ = (unsigned short)0xFF00;	// S=90 degrees
			}

			else
			{
				// Derive the delta heights
				dH10 = ((float)h - (float)hu2)/32.0f;
				dH01 = ((float)h - (float)hv2)/32.0f; 
				// R = atan(dH01/dH10)...
				R = (unsigned char)(int)
					((float)atan2(dH01,dH10)
					*128.0f/3.14159f);	// -pi..0..+pi -> 0x80..0x00..0x7f
				S = (unsigned char)(int)
					((float)atan2(1.0f,(float)sqrt(dH01*dH01+dH10*dH10))
					*255.0f*2.0f/3.14159f);		// 0..+pi/2 -> 0..0xff
				*pTarget++ = (((unsigned short)S)<<8) | ((unsigned short)R);
			}
		}
	}
}
/*******************************************************************************
 * STANDARD FUNCTIONS 
 *******************************************************************************/
/*******************************************************************************
 * Function Name  : D3DTTextureLoadMipmapBMP
 * Returns		  : TRUE or FALSE
 * Inputs		  : lpDD4, lpDev3, *lpNames[], *lpTranslucentNames[], 
 *					*lpddPixelFormat, bUseD3DTextureManagement
 * Outputs		  : *lplpDDSTextureSurface, *lplpD3DTexture2
 * Global Used    : None
 * Description    : Texture loading function which load a range of BMP 
 *					resources or files to create a texture surface into video
 *					memory.
 *					Each BMP must be square and half the size of the previous 
 *					one in the list.
 *					If any of the lower mipmap levels BMP names are NULL, then
 *					the corresponding level is auto-generated using the previous
 *					mipmap level (except for palettised textures).
 *					This function supports RGB and OS/2 BMP formats. RLE encoded 
 *					format is NOT supported.
 *					This function is a shortcut if you don't want to keep a 
 *					SYSTEM MEMORY surface for your textures. It calls
 *					D3DTTextureReadBMP() and D3DTTextureUpload().
 *******************************************************************************/
BOOL D3DTTextureLoadMipmapBMP(LPDIRECTDRAW4 lpDD4, LPDIRECT3DDEVICE3 lpDev3,
							  TCHAR *lpNames[], TCHAR *lpTranslucentNames[],
							  DDPIXELFORMAT *lpddPixelFormat, BOOL bUseD3DTextureManagement,
							  LPDIRECTDRAWSURFACE4 *lplpDDSTextureSurface, LPDIRECT3DTEXTURE2 *lplpD3DTexture2)
{
	LPDIRECTDRAWSURFACE4	lpDDSSystemMemorySurface=NULL;
			
	/* First get SYSTEM MEMORY surface */
	if (!D3DTTextureReadMipmapBMP(lpDD4, lpDev3, 
								  lpNames, lpTranslucentNames, 
								  lpddPixelFormat,
								  &lpDDSSystemMemorySurface))
	{
		WCE_DEBUG(L"D3DTTextureLoadMipmapBMP : Failed in D3DTTextureReadMipmapBMP\n");
		RELEASE(lpDDSSystemMemorySurface);
		return FALSE;
	}

	/* Then load texture into texture memory */
	if (!D3DTTextureUpload(lpDD4, lpDev3, lpDDSSystemMemorySurface, bUseD3DTextureManagement,
						   lplpDDSTextureSurface, lplpD3DTexture2))
	{
		WCE_DEBUG(L"D3DTTextureLoadMipmapBMP : Failed in D3DTTextureUpload\n");
		RELEASE(lpDDSSystemMemorySurface);
		return FALSE;
	}

	/* Release system memory surface as we don't need it anymore */
	RELEASE(lpDDSSystemMemorySurface);

	/* No problem occured */
	return TRUE;
}


/*******************************************************************************
 * Function Name  : D3DTTextureLoadBMP
 * Returns		  : TRUE or FALSE
 * Inputs		  : lpDD4, lpDev3, *lpName, *lpTranslucentName, bDither, 
 *					eAutoMipmap, *lpddPixelFormat
 * Outputs		  : *lplpDDSTextureSurface, *lplpD3DTexture2
 * Global Used    : None
 * Description    : Texture loading function which loads BMP textures.
 *					The BMP file can either be loaded from the resource or as
 *					a file. 
 *					RGB and OS/2 formats are supported. RLE encoded format 
 *					is NOT supported by this function.
 *					This function is a shortcut if you don't want to keep a 
 *					SYSTEM MEMORY surface for your textures. It calls
 *					D3DTTextureReadBMP() and D3DTTextureUpload().
 *******************************************************************************/
BOOL D3DTTextureLoadBMP(LPDIRECTDRAW4 lpDD4, LPDIRECT3DDEVICE3 lpDev3, 
						TCHAR *lpName, TCHAR *lpTranslucentName, 
						BOOL bDither, eD3DTAutoMipmapType eAutoMipmap,
						DDPIXELFORMAT *lpddPixelFormat,
						BOOL bUseD3DTextureManagement,
						LPDIRECTDRAWSURFACE4 *lplpDDSTextureSurface, LPDIRECT3DTEXTURE2 *lplpD3DTexture2)
{
	LPDIRECTDRAWSURFACE4	lpDDSSystemMemorySurface=NULL;
			
	/* First get SYSTEM MEMORY surface */
	if (!D3DTTextureReadBMP(lpDD4, lpDev3, 
							lpName, lpTranslucentName, 
							bDither, eAutoMipmap,
							lpddPixelFormat,
							&lpDDSSystemMemorySurface))
	{
		WCE_DEBUG(L"D3DTTextureLoadBMP : Failed in D3DTTextureReadBMP\n");
		RELEASE(lpDDSSystemMemorySurface);
		return FALSE;
	}

	/* Then load texture into texture memory */
	if (!D3DTTextureUpload(lpDD4, lpDev3, lpDDSSystemMemorySurface, bUseD3DTextureManagement, 
						   lplpDDSTextureSurface, lplpD3DTexture2))
	{
		WCE_DEBUG(L"D3DTTextureLoadBMP : Failed in D3DTTextureUpload\n");
		RELEASE(lpDDSSystemMemorySurface);
		return FALSE;
	}

	/* Release system memory surface as we don't need it anymore */
	RELEASE(lpDDSSystemMemorySurface);

	/* No problem occured */
	return TRUE;
}
		

/*******************************************************************************
 * Function Name  : D3DTTextureReadMipmapBMP
 * Returns		  : TRUE or FALSE
 * Inputs		  : lpDD4, lpDev3, *lpNames[], *lpTranslucentNames[], *lpddPixelFormat
 * Output		  : *lplpDDSSystemMemorySurface
 * Global Used    : None
 * Description    : Texture loading function which load a range of BMP 
 *					resources or files to create a mipmapped intermediate 
 *					texture map (i.e in system memory).
 *					Each BMP must be square and half the size of the previous 
 *					one in the list.
 *					If any of the lower mipmap levels BMP names are NULL, then
 *					the corresponding level is auto-generated using the previous
 *					mipmap level (except for palettised textures).
 *					- lpDD4 is the DirectDraw4 interface.
 *					- lpDev3 is the Direct3DDevice3 interface.
 *					- *lpName[] are the names of all BMP files corresponding to
 *					  mipmap levels. If using resource, then the resource IDs must 
 *					  be strings, i.e. between speech marks. (e.g. "MyBMP")
 *					- *lpTranslucentName[] are the names of all BMP files giving
 *					  the corresponding mipmap level alpha channel information 
 *					  using the red channel. If this is NULL, then texture is opaque
 *					  and no alpha information will be stored. Same remark as *lpName[]
 *					  concerning resource ID.
 *					- *lpddPixelFormat is the texture format used for this texture.
 *					  Obviously an ALPHA format must be used to load alpha textures.
 *					  If the BMP file is 8-bit palettised, then the texture format
 *					  must also be 8-bit palettised.
 *					- *lplpDDSSystemMemorySurface is a pointer pointing to the address
 *					  of the resulting SYSTEM MEMORY texture.
 *					This function supports RGB and OS/2 BMP formats. RLE encoded 
 *					format is NOT supported.
 *
 *******************************************************************************/
BOOL D3DTTextureReadMipmapBMP(LPDIRECTDRAW4 lpDD4, LPDIRECT3DDEVICE3 lpDev3,
							  TCHAR *lpNames[], TCHAR *lpTranslucentNames[],
							  DDPIXELFORMAT *lpddPixelFormat, LPDIRECTDRAWSURFACE4 *lplpDDSSystemMemorySurface)
{
	HRESULT					hres;
	LPDIRECTDRAWSURFACE4	lpSrcTextureSurf=NULL;
	LPDIRECTDRAWSURFACE4	lpDDSCurrentMemorySurface=NULL;
	LPDIRECT3DTEXTURE2		lpSrcTexture=NULL;
	DDSURFACEDESC2			ddsd;
	D3DDEVICEDESC			ddHAL, ddHEL, *lpD3DDeviceDesc;
	DDSCAPS2				ddsCaps;
	HBITMAP					Bitmap;
	BITMAP					bm, bmTrans;
	DWORD					x, y;
	BYTE					r, g, b, a;
	DWORD					dwMemoryUsedByTexture=0;
	int						i;
	TCHAR					pszString[300];
	int						Level, NumLevels;
	BOOL					bPalettisedTexture=FALSE;
	BOOL					bTranslucent=FALSE;
	BOOL					bSupportAlphaTexturing=FALSE;
	BOOL					bSupportNonSquareTextures=FALSE;
	BOOL					bSupportMipmapping=FALSE;
	// Following line necessary ?
	IDirectDrawPalette		ddPalette;
	LPDIRECTDRAWPALETTE		lpDDPPalette=&ddPalette;
	
	/* Check that parameters are valid */
	if (!lpDD4 || !lpDev3 || !lpNames || !lpddPixelFormat || !lplpDDSSystemMemorySurface)
	{
		WCE_DEBUG(L"D3DTTextureReadMipmapBMP : Bad parameters.\n");
		return FALSE;
	}

	/* Are we using a translucent texture format ? */
	if (lpddPixelFormat->dwFlags & DDPF_ALPHAPIXELS)
	{
		WCE_DEBUG(L"D3DTTextureReadMipmapBMP : Translucent texture format used\n");
		bTranslucent=TRUE;
	}

	/* If a translucent file name has been submitted, and 
	   the texture format is opaque then return from function */
	if (lpTranslucentNames && !bTranslucent)
	{
		WCE_DEBUG(L"D3DTTextureReadMipmapBMP : Select a translucent format for a translucent texture!\n");
		return FALSE;
	}

	/* If a translucent format is used, make sure that a translucent
	   file name has been submitted */
	if (!lpTranslucentNames && bTranslucent)
	{
		WCE_DEBUG(L"D3DTTextureReadMipmapBMP : Translucent format requires a translucent file name\n");
		return FALSE;
	}

	/* Is texture a palettised texture ? */
	if ( (lpddPixelFormat->dwRGBBitCount<=8) && (lpddPixelFormat->dwFlags & DDPF_PALETTEINDEXED8) )
	{
		WCE_DEBUG(L"D3DTTextureReadMipmapBMP : Palettised texture format used\n");
		bPalettisedTexture=TRUE;
	}

	/* Check that translucency is not set for a palettised texture */
	if (bPalettisedTexture && lpTranslucentNames)
	{
		WCE_DEBUG(L"D3DTTextureReadMipmapBMP : Palettised texture can not be translucent.\n");
		return FALSE;
	}


	/* Initialise D3DDEVICEDESC structures */
	WCE_ZERO_MEMORY(&ddHAL, sizeof(D3DDEVICEDESC));
	WCE_ZERO_MEMORY(&ddHEL, sizeof(D3DDEVICEDESC));
	ddHAL.dwSize=sizeof(D3DDEVICEDESC);
	ddHEL.dwSize=sizeof(D3DDEVICEDESC);
	lpDev3->lpVtbl->GetCaps(lpDev3, &ddHAL, &ddHEL);
	
	/* If the device color model is 0, then software device : use HEL otherwise use HAL */
	if (!ddHAL.dcmColorModel) lpD3DDeviceDesc=&ddHEL;
		else lpD3DDeviceDesc=&ddHAL;
	
	/* Get device caps */
	if (lpD3DDeviceDesc->dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_ALPHA)				bSupportAlphaTexturing=TRUE;
	if (!(lpD3DDeviceDesc->dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_SQUAREONLY))		bSupportNonSquareTextures=TRUE;
	if (lpD3DDeviceDesc->dpcTriCaps.dwTextureFilterCaps & D3DPTFILTERCAPS_MIPNEAREST)	bSupportMipmapping=TRUE;
	
	/* Check that device supports mipmapping */
	if (!bSupportMipmapping)
	{
		WCE_DEBUG(L"D3DTTextureReadMipmapBMP : 3D Device does not support mipmapping.\n");
		return FALSE;
	}

	/* Check that device supports alpha texturing */
	if (!bSupportAlphaTexturing && lpTranslucentNames)
	{
		WCE_DEBUG(L"D3DTTextureReadMipmapBMP : 3D Device does not support ALPHA textures.\n");
		return FALSE;
	}


	/* Load texture into BITMAP : first try to load from resource */
	GetResourceBitmap(&bm, lpNames[0]);
	
	/* If translucent, then also read the file lpTranslucentName */
	if (lpTranslucentNames)
	{
		GetResourceBitmap(&bmTrans, lpTranslucentNames[0]);
	}

	
	/* If translucent texture has also been loaded, check that both 
	   widths and heights are equal and that the bit depth is the same */
	if (lpTranslucentNames)
	{
		if (bm.bmWidth!=bmTrans.bmWidth || bm.bmHeight!=bmTrans.bmHeight || bm.bmBitsPixel!=bmTrans.bmBitsPixel)
		{
			/* Bitmap and translucent bitmap have different types */
			WCE_DEBUG(L"D3DTTextureReadMipmapBMP : Bitmap and translucent bitmap have different types.\n");
			lplpDDSSystemMemorySurface=NULL;
			return FALSE;
		}
	}

	/* Is texture requested as 8-bit palettised ? */
	if (bPalettisedTexture)
	{
		/* Yes, check that the bitmap loaded is a 8-bit bitmap */
		if (bm.bmBitsPixel!=8)
		{
			WCE_DEBUG(L"D3DTTextureReadMipmapBMP : A 8-bit palettised bitmap must be used to create a 8-bit palettised texture\n");
			return FALSE;
		}
	}
	else
	{
		/* Texture is not requested as palettised, so check that a normal 24-bits bitmap has been loaded */
		if (bm.bmBitsPixel!=24)
		{
			WCE_DEBUG(L"D3DTTextureReadMipmapBMP : The bmp file must be in 24 bits format for an RGBA texture type\n");
			return FALSE;
		}
	}


	/* Get width and height of bitmap */
	x=bm.bmWidth;
	y=bm.bmHeight;

	/* Check that width and height are equal for devices that only support SQUARE textures */
	if (!bSupportNonSquareTextures)
	{
		if (bm.bmWidth!=bm.bmHeight)
		{
			WCE_DEBUG(L"D3DTTextureReadMipmapBMP : Device does not support non-square textures\n");
			return FALSE;
		}
		if (lpTranslucentNames)
		{
			if (bmTrans.bmWidth!=bmTrans.bmHeight)
			{	
				WCE_DEBUG(L"D3DTTextureReadMipmapBMP : Device does not support non-square textures\n");
				return FALSE;
			}
		}
	}


	/* For normal textures (non-palettised), compute the number of bits
	   for each channel Red, Green, Blue and Alpha (if translucent) */
	if (!bPalettisedTexture)
	{
		GetPixelFormatInfo(lpddPixelFormat, &r, &g, &b, &a,
											NULL, NULL, NULL, NULL,
											NULL, NULL, NULL, NULL);
	}


	/* Calculate memory used by texture */
	dwMemoryUsedByTexture=x*y*lpddPixelFormat->dwRGBBitCount/8;
	
	/* Debug info about texture */
	wsprintf(pszString, TEXT("ReadMipmapBMPTexture : Loading %s texture : %s (%u*%u)\n"), 
						bTranslucent ? TEXT("translucent") : TEXT(""), lpNames[0], x, y);
	WCE_DEBUG(pszString);
	if (!bPalettisedTexture)
	{
		wsprintf(pszString, TEXT("D3DTTextureReadMipmapBMP : Texture format = %d%d%d%d (%d Bytes)\n\n"), r, g, b, a, dwMemoryUsedByTexture);
	}
	else
	{
		wsprintf(pszString, TEXT("D3DTTextureReadMipmapBMP : Texture format = 8-bit palettised (%d Bytes)\n\n"), dwMemoryUsedByTexture);
	}
	WCE_DEBUG(pszString);

	
	/* Set the fields of the DirectDraw Surface Description */
    WCE_ZERO_MEMORY(&ddsd, sizeof(DDSURFACEDESC2));
    ddsd.dwSize=sizeof(DDSURFACEDESC2);
    ddsd.dwFlags=DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PIXELFORMAT;
    ddsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE | DDSCAPS_SYSTEMMEMORY | DDSCAPS_MIPMAP | DDSCAPS_COMPLEX;
    ddsd.dwWidth=x;
	ddsd.dwHeight=y;
	ddsd.ddpfPixelFormat=*lpddPixelFormat;

	/* Create surface */
	hres=lpDD4->lpVtbl->CreateSurface(lpDD4, &ddsd, (LPDIRECTDRAWSURFACE4 *)lplpDDSSystemMemorySurface, NULL);
	if (hres!=DD_OK) 
	{
		WCE_DEBUG(L"D3DTTextureReadMipmapBMP : Failed to create system memory surface\n");
		return FALSE;
	}

	 
	/* If texture is palettised, create a palette for the texture */
    if (bPalettisedTexture)
    {
        /* Create palette from bitmap */
		if (!PaletteFromBitmap(lpDD4, Bitmap, &lpDDPPalette))
		{
			WCE_DEBUG(L"D3DTTextureReadMipmapBMP : PaletteFromBitmap failed\n");
		}
        
        /* Attach the palette to the Surface and the texture */
		hres=(*lplpDDSSystemMemorySurface)->lpVtbl->SetPalette((*lplpDDSSystemMemorySurface), lpDDPPalette);
		if (hres!=DD_OK)
		{
			WCE_DEBUG(L"D3DTTextureReadMipmapBMP : SetPalette failed\n");
			RELEASE(*lplpDDSSystemMemorySurface);
			return FALSE;
		}
    }

	/* Copy bitmap to surface */
	if (!CopyBitmapToSurface((*lplpDDSSystemMemorySurface), &bm, lpTranslucentNames ? &bmTrans : NULL))
	{
		WCE_DEBUG(L"D3DTTextureReadMipmapBMP : Failed to copy bitmap to texture surface\n");
		RELEASE(*lplpDDSSystemMemorySurface);
		return FALSE;
	}

	
	/* Find how many mipmap levels are to be loaded */
	for (NumLevels=1, i=x; i>1; i>>=1) NumLevels++;
				
	/* Debug info */
	wsprintf(pszString, TEXT("D3DTTextureReadMipmapBMP : Mipmap levels = %d\n"), NumLevels-1);
	WCE_DEBUG(pszString);
		
	/* Now that the highest level is loaded, load the rest */
	lpDDSCurrentMemorySurface=(*lplpDDSSystemMemorySurface);

	/* Load all levels */
	for (Level=1; Level<NumLevels; Level++) 
	{
		BOOL bGenerate=FALSE;
		
		/* If a mipmap name is NULL, then generate next mipmap level */
		if (!lpNames[Level])
		{
			/* Cannot automipmap palettised textures */
			if (bPalettisedTexture)
			{
				WCE_DEBUG(L"D3DTTextureReadMipmapBMP : Cannot generate palettised mipmap level\n");
				return FALSE;
			}

			/* OK, generate next level */
			if (!CreateNextMipmapLevel2x2(lpDDSCurrentMemorySurface))
			{
				WCE_DEBUG(L"D3DTTextureReadMipmapBMP : Failed to generate next mipmap level.\n");
			}
			else
			{
				wsprintf(pszString, TEXT("Generating mipmap level %d\n"), Level);
				WCE_DEBUG(pszString);
			}
			bGenerate=TRUE;
		}
		else
		{
			/* Debug info */
			wsprintf(pszString, TEXT("D3DTTextureReadMipmapBMP : Mipmap name : %s %s\n"), lpNames[Level], bTranslucent ? "(translucent)" : "");
			WCE_DEBUG(pszString);
			
			/* Load the bitmap from a resource or file */
			/* First try resource */
			GetResourceBitmap(&bm, lpNames[Level]);
			
			if (bTranslucent)
			{
				/* Load the translucent bitmap from a resource or file */
				/* First try resource */
				GetResourceBitmap(&bmTrans, lpTranslucentNames[Level]);
			
			}
		}

		/* Go to the next mipmap level */
		WCE_ZERO_MEMORY(&ddsCaps, sizeof(DDSCAPS2));
		ddsCaps.dwCaps=DDSCAPS_TEXTURE | DDSCAPS_MIPMAP;
		hres=lpDDSCurrentMemorySurface->lpVtbl->GetAttachedSurface(lpDDSCurrentMemorySurface, &ddsCaps, &lpDDSCurrentMemorySurface);
		if (hres!=DD_OK)
		{
			WCE_DEBUG(L"D3DTTextureReadMipmapBMP : Failed to get next mipmap level\n");
			wsprintf(pszString, TEXT("Current Level = %d (%s)\n"), Level, lpNames[Level]);
			WCE_DEBUG(pszString);
			RELEASE(*lplpDDSSystemMemorySurface);
			return FALSE;
		}

		/* if mipmap level was not generated, then copy bitmap into our surface */
		if (!bGenerate)
		{
		
			/* Copy the bitmap to our memory surface */
			if (!CopyBitmapToSurface(lpDDSCurrentMemorySurface, &bm, bTranslucent ? &bmTrans : NULL))
			{
				wsprintf(pszString, TEXT("D3DTTextureReadMipmapBMP : Copy failed for mipmap %d (%s)\n"), Level, lpNames[Level]);
				WCE_DEBUG(pszString);
				RELEASE(*lplpDDSSystemMemorySurface);
				return FALSE;
			}

		}
	}

	/* No problem occured */
	return TRUE;
}


/*******************************************************************************
 * Function Name  : D3DTTextureReadBMP
 * Inputs		  : lpDD4, lpDev3, 
 *					*lpName, *lpTranslucentName, bDither, eAutoMipmap, *lpddPixelFormat.
 * Output		  : *lplpDDSSystemMemorySurface
 * Returns		  : TRUE or FALSE
 * Global Used    : None
 * Description    : Reads a BMP file and creates a SYSTEM MEMORY texture surface 
 *					containing the data for this BMP file.
 *					The BMP file can either be loaded from the resource or as
 *					a file (if loaded from a resource, the resource ID must be
 *					a string, not a number i.e. use "MYNAME" with speech mark)
 *					If lpTranslucentName is set, then this file (or resource)
 *					will be read with the RED channel defining the ALPHA channel.
 *					RGB and OS/2 BMP formats are supported. RLE encoded format 
 *					is NOT supported by this function.
 *					- lpDD4 is the DirectDraw4 interface.
 *					- lpDev3 is the Direct3DDevice3 interface.
 *					- lpName is the name of the file (or resource)
 *					- lpTranslucentName is the translucent bitmap name (if required).
 *					- bDither indicates if the BMP file is to be dithered or not.
 *					- eAutoMipmap is the type of mipmap required for that texture. For
 *					  a list of these values, see D3DTools.h.
 *					- *lpddPixelFormat is the texture format used for this texture.
 *					  Obviously an ALPHA format must be used to load alpha textures.
 *					  If the BMP file is 8-bit palettised, then the texture format
 *					  must also be 8-bit palettised.
 *					- *lplpDDSSystemMemorySurface is a pointer pointing to the address
 *					  of the resulting SYSTEM MEMORY texture.
 *
 *					NOTE :
 *					The only palettised format supported by this function is 8-bit
 *					palettised.
 *					Automipmapped 8-bit palettised textures are not supported by this
 *					function as it would require a palette re-arranging.
 *******************************************************************************/
BOOL D3DTTextureReadBMP(LPDIRECTDRAW4 lpDD4, LPDIRECT3DDEVICE3 lpDev3, 
						TCHAR *lpName, TCHAR *lpTranslucentName,
						BOOL bDither, eD3DTAutoMipmapType eAutoMipmap,
						DDPIXELFORMAT *lpddPixelFormat,
						LPDIRECTDRAWSURFACE4 *lplpDDSSystemMemorySurface)
{
	HRESULT					hres;
	LPDIRECTDRAWSURFACE4	lpSrcTextureSurf=NULL;
	LPDIRECTDRAWSURFACE4	lpDDSCurrentMemorySurface=NULL;
	LPDIRECT3DTEXTURE2		lpSrcTexture=NULL;
	DDSURFACEDESC2			ddsd;
	D3DDEVICEDESC			ddHAL, ddHEL, *lpD3DDeviceDesc;
	HBITMAP					hBitmap;
	BITMAP					bm, bmTrans;
	DWORD					x, y;
	BYTE					r, g, b, a;
	DWORD					dwMemoryUsedByTexture=0;
	int						NumLevels=1;
	BOOL					bPalettisedTexture=FALSE;
	BOOL					bTranslucent=FALSE;
	BOOL					bSupportAlphaTexturing=FALSE;
	BOOL					bSupportNonSquareTextures=FALSE;
	BOOL					bSupportMipmapping=FALSE;
	// Following line necessary ?
	IDirectDrawPalette		ddPalette;
	LPDIRECTDRAWPALETTE		lpDDPPalette=&ddPalette;
	TCHAR 					pszString[300];
	
	/* Perform various checking */

	/* Check that parameters are valid */
	if (!lpDD4 || !lpddPixelFormat || !lpName || !lplpDDSSystemMemorySurface ||
		eAutoMipmap<0 || eAutoMipmap>13)
	{
		WCE_DEBUG(L"D3DTTextureReadBMP : Bad parameters\n");
		return FALSE;
	}

	/* Are we using a translucent texture format ? */
	if (lpddPixelFormat->dwFlags & DDPF_ALPHAPIXELS)
	{
		bTranslucent=TRUE;
	}

	/* If a translucent file name has been submitted, and 
	   the texture format is opaque then return from function */
	if (lpTranslucentName && !bTranslucent)
	{
		WCE_DEBUG(L"D3DTTextureReadBMP : Select a translucent format for a translucent texture!\n");
		return FALSE;
	}

	/* If a translucent format is used, make sure that a translucent
	   file name has been submitted */
	if (!lpTranslucentName && bTranslucent)
	{
		WCE_DEBUG(L"D3DTTextureReadBMP : Translucent format requires a translucent file name\n");
		return FALSE;
	}

	/* Is texture a palettised texture ? */
	if ( (lpddPixelFormat->dwRGBBitCount<=8) && (lpddPixelFormat->dwFlags & DDPF_PALETTEINDEXED8) )
	{
		WCE_DEBUG(L"D3DTTextureReadBMP : Palettised texture format used\n");
		bPalettisedTexture=TRUE;
	}

	/* Check that translucency is not set for a palettised texture */
	if (bPalettisedTexture && lpTranslucentName)
	{
		WCE_DEBUG(L"D3DTTextureReadBMP : Palettised texture can not be translucent.\n");
		return FALSE;
	}

	/* Check that automipmapping is not requested for palettised textures */
	if (bPalettisedTexture && eAutoMipmap)
	{
		WCE_DEBUG(L"D3DTTextureReadBMP : Auto-mipmapped palettised textures are not supported.\n");
		return FALSE;
	}


	/* Initialise D3DDEVICEDESC structures */
	WCE_ZERO_MEMORY(&ddHAL, sizeof(D3DDEVICEDESC));
	WCE_ZERO_MEMORY(&ddHEL, sizeof(D3DDEVICEDESC));
	ddHAL.dwSize=sizeof(D3DDEVICEDESC);
	ddHEL.dwSize=sizeof(D3DDEVICEDESC);
	lpDev3->lpVtbl->GetCaps(lpDev3, &ddHAL, &ddHEL);
	
	/* If the device color model is 0, then software device : use HEL otherwise use HAL */
	if (!ddHAL.dcmColorModel) lpD3DDeviceDesc=&ddHEL;
		else lpD3DDeviceDesc=&ddHAL;
	
	/* Get device caps */
	if (lpD3DDeviceDesc->dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_ALPHA)				bSupportAlphaTexturing=TRUE;
	if (!(lpD3DDeviceDesc->dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_SQUAREONLY))		bSupportNonSquareTextures=TRUE;
	if (lpD3DDeviceDesc->dpcTriCaps.dwTextureFilterCaps & D3DPTFILTERCAPS_MIPNEAREST)	bSupportMipmapping=TRUE;
	
	/* If auto-mipmapping has been requested then check that device can support mipmapping */
	if (eAutoMipmap && !bSupportMipmapping)
	{
		WCE_DEBUG(L"D3DTTextureReadBMP : 3D Device does not support mipmapping : mipmapping turned OFF\n");
		eAutoMipmap=0;
	}


	/* Load texture into BITMAP : first try to load from resource */
	GetResourceBitmap(&bm, lpName);
	
	/* If translucent, then also read the file lpTranslucentName */
	if (lpTranslucentName)
	{
		/* Load translucent texture : first try to load from resource */
		GetResourceBitmap(&bmTrans, lpTranslucentName);
		
	}



	/* If translucent texture has also been loaded, check that both 
	   widths and heights are equal and that the bit depth is the same */
	if (lpTranslucentName)
	{
		if (bm.bmWidth!=bmTrans.bmWidth || bm.bmHeight!=bmTrans.bmHeight || bm.bmBitsPixel!=bmTrans.bmBitsPixel)
		{
			/* Bitmap and translucent bitmap have different types */
			WCE_DEBUG(L"D3DTTextureReadBMP : Bitmap and translucent bitmap have different types.\n");
			lplpDDSSystemMemorySurface=NULL;
			return FALSE;
		}
	}

	/* Is texture requested as 8-bit palettised ? */
	if (bPalettisedTexture)
	{
		/* Yes, check that the bitmap loaded is a 8-bit bitmap */
		if (bm.bmBitsPixel!=8)
		{
			WCE_DEBUG(L"D3DTTextureReadBMP : A 8-bit palettised bitmap must be used to create a 8-bit palettised texture\n");
			return FALSE;
		}
	}
	else
	{
		/* Texture is not requested as palettised, so check that a normal 24-bits bitmap has been loaded */
		if (bm.bmBitsPixel!=24)
		{
			WCE_DEBUG(L"D3DTTextureReadBMP : The bmp file must be in 24 bits format for an RGBA texture type\n");
			return FALSE;
		}
	}


	/* Get width and height of bitmap */
	x=bm.bmWidth;
	y=bm.bmHeight;

	/* Check that width and height are equal for devices that only support SQUARE textures */
	if (!bSupportNonSquareTextures)
	{
		if (bm.bmWidth!=bm.bmHeight)
		{
			WCE_DEBUG(L"D3DTTextureReadBMP : Device does not support non-square textures\n");
	
			return FALSE;
		}
		if (lpTranslucentName)
		{
			if (bmTrans.bmWidth!=bmTrans.bmHeight)
			{	
				WCE_DEBUG(L"D3DTTextureReadBMP : Device does not support non-square textures\n");
				return FALSE;
			}
		}
	}


	/* For normal textures (non-palettised), get the number of bits
	   for each channel Red, Green, Blue and Alpha (if translucent) */
	if (!bPalettisedTexture)
	{
		GetPixelFormatInfo(lpddPixelFormat, &r, &g, &b, &a,
											NULL, NULL, NULL, NULL, 
											NULL, NULL, NULL, NULL);
	}

	
	/* Dithering */
	if (bDither && !bPalettisedTexture)// && !bConvertFromPal)
	{
		if (lpddPixelFormat->dwRGBBitCount>16)
		{
			WCE_DEBUG(L"D3DTTextureReadBMP : No need to dither 24 or 32 bits textures\n");
		}
		else
		{
			WCE_DEBUG(L"D3DTTextureReadBMP : Dithering texture\n");
			DitherBitmap(x, y, lpddPixelFormat, bm.bmBits, lpTranslucentName ? bmTrans.bmBits : NULL);
		}
	}
	
	/* Calculate memory used by texture */
	dwMemoryUsedByTexture=x*y*lpddPixelFormat->dwRGBBitCount/8;
	

	/* Debug info about texture */
	wsprintf(pszString, TEXT("\nD3DTTextureReadBMP : Loading %s texture : %s (%u*%u)\n"), 
						bTranslucent ? TEXT("translucent") : TEXT(""), lpName, x, y);
	WCE_DEBUG(pszString);
	if (!bPalettisedTexture)
	{
		wsprintf(pszString, TEXT("D3DTTextureReadBMP : Texture format = %d%d%d%d (%d Bytes)\n"), r, g, b, a, dwMemoryUsedByTexture);
	}
	else
	{
		wsprintf(pszString, TEXT("D3DTTextureReadBMP : Texture format = 8-bit palettised (%d Bytes)\n"), dwMemoryUsedByTexture);
	}
	WCE_DEBUG(pszString);


	/* If texture is translucent, compute transparent pixel colors.
	   This is needed to avoid "color bleeding" when bilinearing or
	   mipmapping a transparent texture */
	if (lpTranslucentName)
	{
		WCE_DEBUG(L"D3DTTextureReadBMP : Computing transparent pixels...\n");
		/* We remove this function for Dragon */ 
		//ComputeTransparentPixels(&bm, &bmTrans);
	}

	
	/* Set the fields of the DirectDraw Surface Description */
    WCE_ZERO_MEMORY(&ddsd, sizeof(DDSURFACEDESC2));
    ddsd.dwSize=sizeof(DDSURFACEDESC2);
    ddsd.dwFlags=DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    ddsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE | DDSCAPS_SYSTEMMEMORY;
    if (eAutoMipmap)
	{
		ddsd.ddsCaps.dwCaps|=DDSCAPS_MIPMAP | DDSCAPS_COMPLEX;
	}
	ddsd.dwWidth=x;
	ddsd.dwHeight=y;
	ddsd.ddpfPixelFormat=*lpddPixelFormat;

	/* Create surface */
	hres=lpDD4->lpVtbl->CreateSurface(lpDD4, &ddsd, (LPDIRECTDRAWSURFACE4 *)lplpDDSSystemMemorySurface, NULL);
	if (hres!=DD_OK) 
	{
		WCE_DEBUG(L"D3DTTextureReadBMP : Failed to create system memory surface\n");
	return FALSE;
	}

	 
	/* If texture is palettised, create a palette for the texture */
    if (bPalettisedTexture)
    {
        /* Create palette from bitmap */
		if (!PaletteFromBitmap(lpDD4, hBitmap, &lpDDPPalette))
		{
			WCE_DEBUG(L"D3DTTextureReadBMP : PaletteFromBitmap failed\n");
		}
        
        /* Attach the palette to the Surface and the texture */
		hres=(*lplpDDSSystemMemorySurface)->lpVtbl->SetPalette((*lplpDDSSystemMemorySurface), lpDDPPalette);
		if (hres!=DD_OK)
		{
			WCE_DEBUG(L"D3DTTextureReadBMP : SetPalette failed\n");
			RELEASE(*lplpDDSSystemMemorySurface);
			return FALSE;
		}
    }


	/* Copy bitmap to surface */
	if (!CopyBitmapToSurface((*lplpDDSSystemMemorySurface), &bm, lpTranslucentName ? &bmTrans : NULL))
	{
		WCE_DEBUG(L"D3DTTextureReadBMP : Failed to copy bitmap to texture surface\n");
		RELEASE(*lplpDDSSystemMemorySurface);
		return FALSE;
	}

	/* Auto-mipmapping has been requested, so create all mipmap levels */
	if (eAutoMipmap)
	{
		/* With box filters, each mipmap level is computed from the previous one */
		if (eAutoMipmap<3)
		{
			/* Create all mipmap levels for this texture */
			if (!CreateAllMipmapLevels((*lplpDDSSystemMemorySurface), eAutoMipmap))
			{
				WCE_DEBUG(L"D3DTTextureReadBMP : CreateAllMipmapLevels() failed.\n");
				RELEASE(*lplpDDSSystemMemorySurface);
				return FALSE;
			}
		}
		else
		{
			/* Mipmap levels computed with the Fourier method require the full bitmap data */
			if (!CreateFourierMipmapLevels(lpDD4, lpDev3, 
										   &bm, lpTranslucentName ? &bmTrans : NULL,
										   (*lplpDDSSystemMemorySurface), (eAutoMipmap-3)*2))
			{
				WCE_DEBUG(L"D3DTTextureReadBMP : CreateFourierMipmapLevels() failed.\n");
				RELEASE(*lplpDDSSystemMemorySurface);
				return FALSE;
			}
		}
	}

	
	/* No problem occured */
	return TRUE;
}
	

/*******************************************************************************
 * Function Name  : D3DTTextureReadTransparentBMP
 * Inputs		  : lpDD4, lpDev3, 
 *					*lpName, eAutoMipmap, dwTransparentColor, *lpddPixelFormat
 * Output		  : *lplpDDSSystemMemorySurface
 * Returns		  : TRUE or FALSE
 * Global Used    : None
 * Description    : Reads a BMP file and creates a SYSTEM MEMORY texture surface 
 *					containing the data for this BMP file.
 *					The BMP file can either be loaded from the resource or as
 *					a file (if loaded from a resource, the resource ID must be
 *					a string, not a number i.e. use "MYNAME" with speech mark)
 *					A color, defined as "transparent", will indicate which pixels
 *					are completely transparent in the image.
 *					RGB and OS/2 BMP formats are supported. RLE encoded format 
 *					is NOT supported by this function.
 *					- lpDD4 is the DirectDraw4 interface.
 *					- lpDev3 is the Direct3DDevice3 interface.
 *					- lpName is the name of the file (or resource)
 *					- eAutoMipmap is the type of mipmap required for that texture. The
 *					  values are : AutoMipmap_None, AutoMipmap_2by2 and AutoMipmap_4by4.
 *					- dwTransparentColor is the color used for transparency. The D3D
 *					  macro RGB_MAKE should be used to specify this parameter.
 *					- *lpddPixelFormat is the texture format used for this texture.
 *					  Must be an alpha format.
 *					- *lplpDDSSystemMemorySurface is a pointer pointing to the address
 *					  of the resulting SYSTEM MEMORY texture.
 *
 *******************************************************************************/
BOOL D3DTTextureReadTransparentBMP(LPDIRECTDRAW4 lpDD4, LPDIRECT3DDEVICE3 lpDev3, 
								   TCHAR *lpName,
								   eD3DTAutoMipmapType eAutoMipmap,
								   D3DCOLOR dwTransparentColor,
								   DDPIXELFORMAT *lpddPixelFormat,
								   LPDIRECTDRAWSURFACE4 *lplpDDSSystemMemorySurface)
{
	HRESULT					hres;
	DDSURFACEDESC2			ddsd;
	D3DDEVICEDESC			ddHAL, ddHEL, *lpD3DDeviceDesc;
	BITMAP					bm, bmTrans;
	DWORD					dwMemoryUsedByTexture=0;
	BYTE					*pReadByte, *pWriteByte;
	BYTE					R, G, B;
	BYTE					r, g, b, a;
	BOOL					bSupportAlphaTexturing=FALSE;
	BOOL					bSupportNonSquareTextures=FALSE;
	BOOL					bSupportMipmapping=FALSE;
	int						x, y;
	int						i, j;
	TCHAR					pszString[300];
	
	/* Perform various checking */

	/* Check that parameters are valid */
	if (!lpDD4 || !lpddPixelFormat || !lpName || !lplpDDSSystemMemorySurface ||
		eAutoMipmap<0 || eAutoMipmap>13)
	{
		WCE_DEBUG(L"D3DTTextureReadTransparentBMP : Bad parameters\n");
		return FALSE;
	}

	/* Are we using a translucent texture format as required ? */
	if (!(lpddPixelFormat->dwFlags & DDPF_ALPHAPIXELS))
	{
		WCE_DEBUG(L"D3DTTextureReadTransparentBMP : A translucent texture format must be used\n");
		return FALSE;
	}


	/* Initialise D3DDEVICEDESC structures */
	WCE_ZERO_MEMORY(&ddHAL, sizeof(D3DDEVICEDESC));
	WCE_ZERO_MEMORY(&ddHEL, sizeof(D3DDEVICEDESC));
	ddHAL.dwSize=sizeof(D3DDEVICEDESC);
	ddHEL.dwSize=sizeof(D3DDEVICEDESC);
	lpDev3->lpVtbl->GetCaps(lpDev3, &ddHAL, &ddHEL);
	
	/* If the device color model is 0, then software device : use HEL otherwise use HAL */
	if (!ddHAL.dcmColorModel) lpD3DDeviceDesc=&ddHEL;
		else lpD3DDeviceDesc=&ddHAL;
	
	/* Get device caps */
	if (lpD3DDeviceDesc->dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_ALPHA)				bSupportAlphaTexturing=TRUE;
	if (!(lpD3DDeviceDesc->dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_SQUAREONLY))		bSupportNonSquareTextures=TRUE;
	if (lpD3DDeviceDesc->dpcTriCaps.dwTextureFilterCaps & D3DPTFILTERCAPS_MIPNEAREST)	bSupportMipmapping=TRUE;
	
	/* If auto-mipmapping has been requested then check that device can support mipmapping */
	if (eAutoMipmap && !bSupportMipmapping)
	{
		WCE_DEBUG(L"D3DTTextureReadTransparentBMP : 3D Device does not support mipmapping : mipmapping turned OFF\n");
		eAutoMipmap=0;
	}


	/* Load texture into BITMAP : first try to load from resource */
	GetResourceBitmap(&bm, lpName);

		
	/* Check that a normal 24-bits bitmap has been loaded */
	if (bm.bmBitsPixel!=24)
	{
		WCE_DEBUG(L"D3DTTextureReadTransparentBMP : The bmp file must be in 24 bits format for an RGBA texture type\n");
		return FALSE;
	}


	/* Get width and height of bitmap */
	x=bm.bmWidth;
	y=bm.bmHeight;

	/* Check that width and height are equal for devices that only support SQUARE textures */
	if (!bSupportNonSquareTextures)
	{
		if (bm.bmWidth!=bm.bmHeight)
		{
			WCE_DEBUG(L"D3DTTextureReadTransparentBMP : Device does not support non-square textures\n");
			return FALSE;
		}
	}

	/* Create a bitmap structure containing the alpha information for the texture */
	bmTrans.bmType=bm.bmType;
	bmTrans.bmWidth=bm.bmWidth;
	bmTrans.bmHeight=bm.bmHeight;
	bmTrans.bmWidthBytes=bm.bmWidthBytes;
	bmTrans.bmPlanes=bm.bmPlanes;
	bmTrans.bmBitsPixel=bm.bmBitsPixel;
	bmTrans.bmBits=(BYTE *)malloc(bm.bmHeight * bm.bmWidthBytes);

	/* Copy translucent information into bmTrans */
	/* Loop through y values from bottom to top */
	for (i=y; i!=0; i--)
	{
		/* Get pointersfor current line */
		pReadByte=(BYTE *)bm.bmBits+(i-1)*bm.bmWidthBytes+(x*3-1);
		pWriteByte=(BYTE *)bmTrans.bmBits+(i-1)*bmTrans.bmWidthBytes+(x*3-1);		

		/* Look through x values from right to left */
		for (j=0; j<x; j++)
		{ 
			/* Get R, G, B values (always 8-bit each, as the bitmap is 24-bit) */
			R = *pReadByte--;
			G = *pReadByte--;
			B = *pReadByte--;
																
			/* Is pixel the transparent color ? */
			if (RGB_MAKE(R, G, B)!=dwTransparentColor)
			{
				/* Yes, so mark the pixel as completely opaque */
				*pWriteByte=255;
			}

			/* Decrement pointer */
			pWriteByte-=3;
		}
	}

	/* For normal textures (non-palettised), get the number of bits
	   for each channel Red, Green, Blue and Alpha (if translucent) */
	GetPixelFormatInfo(lpddPixelFormat, &r, &g, &b, &a,
										NULL, NULL, NULL, NULL, 
										NULL, NULL, NULL, NULL);


	/* Calculate memory used by texture */
	dwMemoryUsedByTexture=x*y*lpddPixelFormat->dwRGBBitCount/8;
	

	/* Debug info about texture */
	wsprintf(pszString, TEXT("D3DTTextureReadTransparentBMP : Loading texture : %s (%u*%u)\n"), lpName, x, y);
	WCE_DEBUG(pszString);
	wsprintf(pszString, TEXT("D3DTTextureReadTransparentBMP : Texture format = %d%d%d%d (%d Bytes)\n"), r, g, b, a, dwMemoryUsedByTexture);
	WCE_DEBUG(pszString);
	
	/* Set the fields of the DirectDraw Surface Description */
    WCE_ZERO_MEMORY(&ddsd, sizeof(DDSURFACEDESC2));
    ddsd.dwSize=sizeof(DDSURFACEDESC2);
    ddsd.dwFlags=DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    ddsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE | DDSCAPS_SYSTEMMEMORY;
    if (eAutoMipmap)
	{
		ddsd.ddsCaps.dwCaps|=DDSCAPS_MIPMAP | DDSCAPS_COMPLEX;
	}
	ddsd.dwWidth=x;
	ddsd.dwHeight=y;
	ddsd.ddpfPixelFormat=*lpddPixelFormat;

	/* Create surface */
	hres=lpDD4->lpVtbl->CreateSurface(lpDD4, &ddsd, (LPDIRECTDRAWSURFACE4 *)lplpDDSSystemMemorySurface, NULL);
	if (hres!=DD_OK) 
	{
		WCE_DEBUG(L"D3DTTextureReadTransparentBMP : Failed to create system memory surface\n");
		return FALSE;
	}

	/* Copy first level mipmap (main image) into texture surface */
	if (!CopyBitmapToSurface(*lplpDDSSystemMemorySurface, &bm, &bmTrans))
	{
		WCE_DEBUG(L"D3DTTextureReadTransparentBMP : Failed to copy first level mipmap into texture surface\n");
		free(bmTrans.bmBits);
		RELEASE(*lplpDDSSystemMemorySurface);
		
		return FALSE;
	}


	/* Auto-mipmapping has been requested, so create all mipmap levels */
	if (eAutoMipmap)
	{
		/* With box filters, each mipmap level is computed from the previous one */
		if (eAutoMipmap<3)
		{
			/* Create all mipmap levels for this texture */
			if (!CreateAllMipmapLevels((*lplpDDSSystemMemorySurface), eAutoMipmap))
			{
				WCE_DEBUG(L"D3DTTextureReadBMP : CreateAllMipmapLevels() failed.\n");
				free(bmTrans.bmBits);
				RELEASE(*lplpDDSSystemMemorySurface);
			return FALSE;
			}
		}
		else
		{
			/* Mipmap levels computed with the Fourier method require the full bitmap data */
			if (!CreateFourierMipmapLevels(lpDD4, lpDev3, 
										   &bm, &bmTrans,
										   (*lplpDDSSystemMemorySurface), (eAutoMipmap-3)*2))
			{
				WCE_DEBUG(L"D3DTTextureReadBMP : CreateFourierMipmapLevels() failed.\n");
				free(bmTrans.bmBits);
				RELEASE(*lplpDDSSystemMemorySurface);
				return FALSE;
			}
		}
	}

	/* Free memory */
	free(bmTrans.bmBits);

	/* No problem occured */
	return TRUE;
}


/*******************************************************************************
 * Function Name  : D3DTTextureUpload
 * Returns		  : TRUE or FALSE
 * Inputs		  : lpDD4, lpDev3, lpDDSSystemMemorySurface, bUseD3DTextureManagement
 * Output		  : *lplpDDSTextureSurface, *lplpD3DTexture2
 * Global Used    : None
 * Description    : Upload a texture from system memory to texture memory (Video
 *					memory, but can also be in system memory for software devices)
 *******************************************************************************/
BOOL D3DTTextureUpload(LPDIRECTDRAW4 lpDD4, LPDIRECT3DDEVICE3 lpDev3,
					   LPDIRECTDRAWSURFACE4 lpDDSSystemMemorySurface, BOOL bUseD3DTextureManagement,
					   LPDIRECTDRAWSURFACE4 *lplpDDSTextureSurface, LPDIRECT3DTEXTURE2 *lplpD3DTexture2)
{
	HRESULT					hres;
	LPDIRECTDRAWSURFACE4	lpSrcTextureSurface=NULL;
	LPDIRECT3DTEXTURE2		lpSrcTexture2;
	DDSURFACEDESC2			ddsd;
	D3DDEVICEDESC			ddHAL, ddHEL;
	DDPIXELFORMAT			ddPixelFormat;
	DDSCAPS2			    ddsCaps;
	DWORD					dwMemoryUsedByTexture, dwFreeTextureMemory;
	DWORD					x, y;
	BOOL					bHardware3DDevice, bMipmap=FALSE, bPalettisedTexture=FALSE;
	// The following line should not be necessary (to test)
	IDirectDrawPalette		DDPPalette;
	LPDIRECTDRAWPALETTE		lpDDPPalette=&DDPPalette;
	TCHAR					pszString[200];

	/* Check parameters */
	if (!lpDD4 || !lpDev3 || !lpDDSSystemMemorySurface)
	{
		WCE_DEBUG(L"D3DTTextureUpload : Bad parameters\n");
		(*lplpDDSTextureSurface)=NULL;
		(*lplpD3DTexture2)=NULL;
		return FALSE;
	}

	/* Determine if 3D device is hardware or not */	
	WCE_ZERO_MEMORY(&ddHAL, sizeof(D3DDEVICEDESC));
	WCE_ZERO_MEMORY(&ddHEL, sizeof(D3DDEVICEDESC));
	ddHAL.dwSize=sizeof(D3DDEVICEDESC);
	ddHEL.dwSize=sizeof(D3DDEVICEDESC);
	lpDev3->lpVtbl->GetCaps(lpDev3, &ddHAL, &ddHEL);
	
	/* If the device color model is 0, then software device */
	if (!ddHAL.dcmColorModel)
	{
		memcpy(&ddHAL, &ddHEL, sizeof(D3DDEVICEDESC));
		bHardware3DDevice=FALSE;
	}
	else
	{
		bHardware3DDevice=TRUE;
	}

	/* Check if device support texturing */
	if (bHardware3DDevice && !HWDEVICE_TEXTUREINVIDEOMEMORY)
	{
		if (!(ddHAL.dwDevCaps & (D3DDEVCAPS_TEXTUREVIDEOMEMORY | D3DDEVCAPS_TEXTURESYSTEMMEMORY)))
		{
			WCE_DEBUG(L"D3D device does not support texturing\n");
			(*lplpDDSTextureSurface)=NULL;
			(*lplpD3DTexture2)=NULL;
			return FALSE;
		}
	}

	/* Source texture surface */
	lpSrcTextureSurface=lpDDSSystemMemorySurface;

	/* QueryInterface for a Direct3DTexture2 interface */
	hres=lpSrcTextureSurface->lpVtbl->QueryInterface(lpSrcTextureSurface, &IID_IDirect3DTexture2,(LPVOID *)&lpSrcTexture2);
	if (hres!=DD_OK) 
	{
		WCE_DEBUG(L"D3DTTextureUpload : QueryInterface for Texture2 interface failed\n");
		(*lplpDDSTextureSurface)=NULL;
		(*lplpD3DTexture2)=NULL;
		return FALSE;
	}


	/* Get surface description */
	WCE_ZERO_MEMORY(&ddsd, sizeof(DDSURFACEDESC2));
	ddsd.dwSize=sizeof(DDSURFACEDESC2);
	hres=lpSrcTextureSurface->lpVtbl->GetSurfaceDesc(lpSrcTextureSurface, &ddsd);
	if (hres!=DD_OK) 
	{
		WCE_DEBUG(L"D3DTTextureUpload : GetSurfaceDesc failed\n");
		RELEASE(lpSrcTexture2);
		(*lplpDDSTextureSurface)=NULL;
		(*lplpD3DTexture2)=NULL;
		return FALSE;
	}

	/* Get width and height of source surface */
	x=ddsd.dwWidth;
	y=ddsd.dwHeight;
	
	/* Copy pixel format */

	memcpy(&ddPixelFormat, &ddsd.ddpfPixelFormat, sizeof(DDPIXELFORMAT));

	/* Check is surface is a mipmapped surface */
	if (ddsd.ddsCaps.dwCaps & DDSCAPS_MIPMAP)
	{
		WCE_DEBUG(L"D3DTTextureUpload : Texture is mipmapped\n");
		bMipmap=TRUE;
	}

	/* Is texture a palettised texture ? */
	if ( (ddPixelFormat.dwRGBBitCount<=8) && (ddPixelFormat.dwFlags & DDPF_PALETTEINDEXED8) )
	{
		bPalettisedTexture=TRUE;
	}

	
	/* Calculate memory used by texture */
	dwMemoryUsedByTexture=x*y*ddPixelFormat.dwRGBBitCount/8;
	
	/* Check amount of free texture memory */
	WCE_ZERO_MEMORY(&ddsCaps, sizeof(DDSCAPS2));
	ddsCaps.dwCaps=DDSCAPS_TEXTURE;
	hres=lpDD4->lpVtbl->GetAvailableVidMem(lpDD4, &ddsCaps, NULL, &dwFreeTextureMemory);
	if (hres!=DD_OK)
	{
		WCE_DEBUG(L"D3DTTextureUpload : GetAvailableVidMem failed\n");
	}
	
	/* Check that there is sufficient texture memory to store this texture */
	if (dwFreeTextureMemory<dwMemoryUsedByTexture)
	{
		wsprintf(pszString, TEXT("D3DTTextureUpload : Not enough memory to store texture.\nFree texture memory=%d  Texture=%d\n"),
				dwFreeTextureMemory, dwMemoryUsedByTexture);
		WCE_DEBUG(pszString);
	}
    
    /* Set the field of surface structure */
	WCE_ZERO_MEMORY(&ddsd, sizeof(DDSURFACEDESC2));
    ddsd.dwSize=sizeof(DDSURFACEDESC2);
    ddsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE | DDSCAPS_ALLOCONLOAD;
	
		/* If this macro is set and 3D device is hardware, then
		   load texture in VIDEO memory */
		if (HWDEVICE_TEXTUREINVIDEOMEMORY && bHardware3DDevice)
		{
			ddsd.ddsCaps.dwCaps|=DDSCAPS_VIDEOMEMORY;
		}
		else
		{
			/* If device does not support video texture memory, use system memory */
			if (!(ddHAL.dwDevCaps & D3DDEVCAPS_TEXTUREVIDEOMEMORY))
			{
				ddsd.ddsCaps.dwCaps|=DDSCAPS_SYSTEMMEMORY;
			}
			else
			{
				ddsd.ddsCaps.dwCaps|=DDSCAPS_VIDEOMEMORY;
			}
		}


	/* If texture is mipmapped, add the MIPMAP and COMPLEX flags */
	if (bMipmap)
	{
		ddsd.ddsCaps.dwCaps|=DDSCAPS_MIPMAP | DDSCAPS_COMPLEX;
	}
    ddsd.dwWidth=x;
	ddsd.dwHeight=y;
    ddsd.ddpfPixelFormat=ddPixelFormat;
	ddsd.dwFlags=DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
	
	/* Create surface */
	hres=lpDD4->lpVtbl->CreateSurface(lpDD4, &ddsd, (LPDIRECTDRAWSURFACE4 *)lplpDDSTextureSurface, NULL);
	if (hres!=DD_OK) 
	{
		WCE_DEBUG(L"D3DTTextureUpload : CreateSurface failed\n");
		RELEASE(lpSrcTexture2);
		(*lplpDDSTextureSurface)=NULL;
		(*lplpD3DTexture2)=NULL;
		return FALSE;
	}


	/* If texture is palettised, attach the palette to texture */
	if (bPalettisedTexture)
    {
		/* Copy palette */
		hres=lpSrcTextureSurface->lpVtbl->GetPalette(lpSrcTextureSurface, &lpDDPPalette);
		if (hres!=DD_OK)
		{
			WCE_DEBUG(L"D3DTTextureUpload : GetPalette failed\n");
			RELEASE(*lplpDDSTextureSurface);
			RELEASE(lpSrcTexture2);
			(*lplpD3DTexture2)=NULL;
			return FALSE;
		}
		
		/* Attach palette to surface */
		hres=(*lplpDDSTextureSurface)->lpVtbl->SetPalette((*lplpDDSTextureSurface), lpDDPPalette);
		if (hres!=DD_OK)
		{
			WCE_DEBUG(L"D3DTTextureUpload : SetPalette failed\n");
			RELEASE(*lplpDDSTextureSurface);
			RELEASE(lpSrcTexture2);
			(*lplpD3DTexture2)=NULL;
			return FALSE;
		}
    }
	
	/* QueryInterface for a Direct3DTexture2 interface */
	hres=(*lplpDDSTextureSurface)->lpVtbl->QueryInterface((*lplpDDSTextureSurface), 
												&IID_IDirect3DTexture2, (LPVOID *)lplpD3DTexture2);
    if (hres!=DD_OK) 
	{
		WCE_DEBUG(L"D3DTTextureUpload : QueryInterface for Direct3DTexture2 failed\n");
		RELEASE(*lplpDDSTextureSurface);
		RELEASE(lpSrcTexture2);
		(*lplpD3DTexture2)=NULL;
		return FALSE;
	}
	
	/* Load texture into memory */
	hres=(*lplpD3DTexture2)->lpVtbl->Load((*lplpD3DTexture2), lpSrcTexture2);
	if (hres!=DD_OK)
	{
		WCE_DEBUG(L"D3DTTextureUpload : Load failed\n");
		RELEASE(*lplpD3DTexture2);
		RELEASE(*lplpDDSTextureSurface);
		RELEASE(lpSrcTexture2);
		return FALSE;
	}

	/* Release source texture interface */
	RELEASE(lpSrcTexture2);
    	
	/* Debug information */
	WCE_ZERO_MEMORY(&ddsCaps, sizeof(DDSCAPS2));
	ddsCaps.dwCaps=DDSCAPS_TEXTURE;
	hres=lpDD4->lpVtbl->GetAvailableVidMem(lpDD4, &ddsCaps, NULL, &dwFreeTextureMemory);
	if (hres!=DD_OK)
	{
		WCE_DEBUG(L"D3DTTextureUpload : GetAvailableVidMem failed\n");
	}
	wsprintf(pszString, TEXT("Free Texture memory = %u\n"), dwFreeTextureMemory);
	WCE_DEBUG(pszString);

	/* No problem occured */
    return (TRUE);
}


/*****************************************************************************
 * Function Name  : D3DTTextureBestOpaqueFormat
 * Inputs		  : b16BitsTexture
 * Returns		  : Pointer to DDPIXELFORMAT in texture formats list.
 * Description    : Returns "best" opaque format for opaque texturing.
 *					If no corresponding format is found, function returns
 *					NULL.
 *					If b16BitsTexture is set, then texture format chosen
 *					will be a 16 bits format (if available)
 *
 *****************************************************************************/
DDPIXELFORMAT *D3DTTextureBestOpaqueFormat(BOOL b16BitsTexture)
{
	int		i;
	int		r=0, g=0, b=0, a=0, tr, tg, tb, ta;
	int		nBestOpaqueFormat=-1;
	
	/* Test if texture formats have been enumerated */
	if (nTextureFormat==-1)
	{
		WCE_DEBUG(L"D3DTTextureBestOpaqueFormat : Texture formats have not been enumerated yet.\nPlease call D3DTTextureListFormats().\n");
		return NULL;
	}

	/* Parse all enumerated texture format to pick best opaque format */
	for (i=0; i<nTextureFormat; i++)
	{
		/* If texture format is a RGB format */
		if (D3DTTextureFormat[i].ddPixelFormat.dwFlags & DDPF_RGB)
		{
			/* Get number of bits available for each channel R, G, B, A */
			tr=D3DTTextureFormat[i].r;
			tg=D3DTTextureFormat[i].g;
			tb=D3DTTextureFormat[i].b;
			ta=D3DTTextureFormat[i].a;
						
			/* Select best opaque format */
			if (ta==0)
			{
				/* Check if current texture format channels are larger than the previous choice */
				if (tr+tg+tb>r+g+b)
				{
					/* If 16 bits textures have to be used, use them */
					if (b16BitsTexture)
					{
						if (tr+tg+tb<=16)
						{
							nBestOpaqueFormat=i;
							r=tr;
							g=tg;
							b=tb;
							a=0;
						}
					}
					else
					{
						/* Otherwise just pick the best format (with the most bits per colour channel) */
						nBestOpaqueFormat=i;
						r=tr;
						g=tg;
						b=tb;
						a=0;
					}
				}
			}
		}
	}

	/* Test if a format has been found */
	if (nBestOpaqueFormat==-1)
	{
		WCE_DEBUG(L"D3DTTextureBestOpaqueFormat : No opaque format has been found\n");
		return NULL;
	}
			
	/* Return best opaque format */
	return (&D3DTTextureFormat[nBestOpaqueFormat].ddPixelFormat);
}



/*****************************************************************************
 * Function Name  : D3DTTextureBestTranslucentFormat
 * Inputs		  : lpDev3
 * Returns		  : Pointer to DDPIXELFORMAT in texture formats list.
 * Description    : Returns "best" translucent format for alpha texturing.
 *					If no corresponding format is found, function returns NULL.
 *					If b16BitsTexture is set, then texture format chosen
 *					will be a 16 bits format (if available)
 *
 *****************************************************************************/
DDPIXELFORMAT *D3DTTextureBestTranslucentFormat(BOOL b16BitsTexture)
{
	int		i;
	int		r=0, g=0, b=0, a=0, tr, tg, tb, ta;
	int		nBestTranslucentFormat=-1;

	/* Test if texture formats have been enumerated */
	if (nTextureFormat==-1)
	{
		WCE_DEBUG(L"D3DTTextureBestTranslucentFormat : Texture formats have not been enumerated yet.\nPlease call D3DTTextureListFormats().\n");
		return NULL;
	}

	/* Parse all enumerated texture format to pick best opaque format */
	for (i=0; i<nTextureFormat; i++)
	{
		/* If texture format is a RGB format */
		if (D3DTTextureFormat[i].ddPixelFormat.dwFlags & DDPF_RGB)
		{
			/* Get number of bits available for each channel R,G,B,A */
			tr=D3DTTextureFormat[i].r;
			tg=D3DTTextureFormat[i].g;
			tb=D3DTTextureFormat[i].b;
			ta=D3DTTextureFormat[i].a;
			
			/* Check if current alpha channel is larger than the previous choice */
			if (ta>a)
			{
				/* If 16 bits textures have to be used, use them */
				if (b16BitsTexture)
				{
					if (tr+tg+tb+ta<=16)
					{
						nBestTranslucentFormat=i;
						r=tr;
						g=tg;
						b=tb;
						a=ta;
					}
				}
				else
				{
					/* Otherwise just pick the best format (with the most bits in the alpha channel) */
					nBestTranslucentFormat=i;
					r=tr;
					g=tg;
					b=tb;
					a=ta;
				}
			}
		}
	}

	/* Test if a format has been found */
	if (nBestTranslucentFormat==-1)
	{
		WCE_DEBUG(L"D3DTTextureBestTranslucentFormat : No translucent format has been found\n");
		return NULL;
	}
			
	/* Return best opaque format */
	return (&D3DTTextureFormat[nBestTranslucentFormat].ddPixelFormat);
}


/*****************************************************************************
 * Function Name  : D3DTTexturePalettised8BitFormat
 * Inputs		  : None
 * Returns		  : Pointer to DDPIXELFORMAT in texture formats list.
 * Description    : Returns 8-bit palettised format IF AVAILABLE in the
 *					list of supported formats.
 *					If no corresponding format is found, function returns NULL.
 *****************************************************************************/
DDPIXELFORMAT *D3DTTexturePalettised8BitFormat()
{
	int		i;
	int		nBestPalettisedFormat=-1;

	/* Test if texture formats have been enumerated */
	if (nTextureFormat==-1)
	{
		WCE_DEBUG(L"D3DTTexturePalettised8BitFormat : Texture formats have not been enumerated yet.\nPlease call D3DTTextureListFormats().\n");
		return NULL;
	}

	/* Parse all enumerated texture format to pick best opaque format */
	for (i=0; i<nTextureFormat; i++)
	{
		if (D3DTTextureFormat[i].ddPixelFormat.dwFlags & DDPF_PALETTEINDEXED8)
		{
			nBestPalettisedFormat=i;
		}
	}

	/* Test if a format has been found */
	if (nBestPalettisedFormat==-1)
	{
		WCE_DEBUG(L"D3DTTexturePalettised8BitFormat : No palettised format has been found\n");
		return NULL;
	}
			
	/* Return best opaque format */
	return (&D3DTTextureFormat[nBestPalettisedFormat].ddPixelFormat);
}


/*****************************************************************************
 * Function Name  : D3DTTextureListFormats
 * Inputs		  : lpDev3
 * Returns		  : TRUE or FALSE
 * Description    : List all available texture formats for the current D3D
 *				    driver by calling the texture format enumeration callback.
 *****************************************************************************/
BOOL D3DTTextureListFormats(LPDIRECT3DDEVICE3 lpDev3)
{
	HRESULT hres;
	int		i;
	    
	/* Set number of texture format to 0 */
	nTextureFormat=0;

	/* Set array of texture formats to 0 */
	for (i=0; i<30; i++)
	{
		D3DTTextureFormat[i].b8BitsPalettised=0;
		D3DTTextureFormat[i].r=0;
		D3DTTextureFormat[i].g=0;
		D3DTTextureFormat[i].b=0;
		D3DTTextureFormat[i].a=0;
		WCE_ZERO_MEMORY(&D3DTTextureFormat[i].ddPixelFormat, sizeof(DDPIXELFORMAT));
	}
	
	/* Call texture format enumeration function */
	hres=lpDev3->lpVtbl->EnumTextureFormats(lpDev3, EnumTextureFormatsCallback, NULL);
    if (hres!=DD_OK) 
	{
        WCE_DEBUG(L"D3DTTextureListTextureFormats : Enumeration of texture formats failed.");
		nTextureFormat=-1;
        return FALSE;
    }

	/* No problem occured */
	return TRUE;
}


/*******************************************************************************
 * Function Name  : D3DTTextureRestoreSurface
 * Input		  : lpDev3, lpDDSSystemMemorySurface
 * Input/Output	  : *lplpDDSTextureSurface, *lplpD3DTexture2
 * Global Used    : None
 * Description    : Test if a texture surface is lost and restore it in 
 *					that case.
 *******************************************************************************/
void D3DTTextureRestoreSurface(LPDIRECT3DDEVICE3 lpDev3,
							   LPDIRECTDRAWSURFACE4 lpDDSSystemMemorySurface, 
							   LPDIRECTDRAWSURFACE4 *lplpDDSTextureSurface, LPDIRECT3DTEXTURE2 *lplpD3DTexture2)
{
	LPDIRECTDRAW4	lpLocalDD4;
	DDSCAPS2		ddsCaps;
	BOOL			bUseD3DTextureManagement=FALSE;

	/* Check if surface is valid */
	if (!lpDDSSystemMemorySurface)
	{
		WCE_DEBUG(L"D3DTTextureRestoreSurface : Surface is NULL\n");
		return;
	}

	/* Get lpLocalDD4 from DirectDrawSurface */
	lpDDSSystemMemorySurface->lpVtbl->GetDDInterface(lpDDSSystemMemorySurface, &lpLocalDD4);

	/* Was texture created with the D3D texture management flag ? */
	WCE_ZERO_MEMORY(&ddsCaps, sizeof(ddsCaps));
	lpDDSSystemMemorySurface->lpVtbl->GetCaps(lpDDSSystemMemorySurface, &ddsCaps);
	bUseD3DTextureManagement=FALSE;
	
	/* If texture surface exists, check whether it's lost or not */
	if ((*lplpDDSTextureSurface))
	{
		if ((*lplpDDSTextureSurface)->lpVtbl->IsLost((*lplpDDSTextureSurface))==DDERR_SURFACELOST)
		{
			/* Surface exists, so release it to recreate it afterwards */
			RELEASE((*lplpDDSTextureSurface));
			RELEASE((*lplpD3DTexture2));

			if (!D3DTTextureUpload(lpLocalDD4, lpDev3, 
								   (LPDIRECTDRAWSURFACE4)lpDDSSystemMemorySurface, bUseD3DTextureManagement,
								   lplpDDSTextureSurface, lplpD3DTexture2))
			{
				WCE_DEBUG(L"D3DTTextureRestoreSurface : D3DTTextureUpload failed\n");
			}
			else
			{
				WCE_DEBUG(L"D3DTTextureRestoreSurface : Texture restored\n");
			}
		}
	}

	/* All textures have been restored, release our copy of DirectDraw4 and return */
	RELEASE(lpLocalDD4);
}


/*****************************************************
******************************************************
***************** INTERNAL FUNCTIONS *****************
******************************************************
*****************************************************/


/*******************************************************************************
 * Function Name  : CopyBitmapToSurface
 * Inputs		  : *pBm, *pBmTrans
 * Input/Output   : lpDDS
 * Returns		  : TRUE or FALSE
 * Global Used    : None
 * Description    : Function that copy a bitmap to a DirectDraw surface.
 *					lpDDS is the adress of a DirectDrawSurface4 ALREADY CREATED.
 *					This function will just copy the image from *pBm to this
 *					surface (only using the lpSurface field of the surface
 *					description). Therefore, the surface description must exist
 *					prior to calling this function.
 *					If pBmTrans is non-NULL, then the RED channel contained in 
 *					this bitmap will be used to create the alpha 
 *					channel of the DirectDraw surface.
 *******************************************************************************/
BOOL CopyBitmapToSurface(LPDIRECTDRAWSURFACE4 lpDDS, BITMAP *pBm, BITMAP *pBmTrans)
{
	HRESULT			hres;
	DDSURFACEDESC2	ddsd;
	DWORD			x, y;
	BYTE			R, G, B, A;
	BYTE			r, g, b, a;
	BYTE			LeftR, LeftG, LeftB, LeftA; 
	BYTE			RightR, RightG, RightB, RightA;
	unsigned		Cont = 0;
	char			*pLineBuffer, *pLineBufferTrans;
	unsigned char	*lp8b;
	unsigned short	*lp16b;
	unsigned int	*lp32b;
	int				i, j, Mode;
	
	/* Get width and height of bitmap */
	x=pBm->bmWidth;
	y=pBm->bmHeight;

	/* Get surface description */
	memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
    ddsd.dwSize=sizeof(DDSURFACEDESC2);
	lpDDS->lpVtbl->GetSurfaceDesc(lpDDS, &ddsd);

	/* Check if bitmap and surface dimensions are equal */
	if (ddsd.dwWidth!=x || ddsd.dwHeight!=y)
	{
		WCE_DEBUG(L"CopyBitmapToSurface : Bitmap and surface dimensions do not match. Aborting copy.\n");
		return FALSE;
	}

	/* Special copy for 8-bit palettised textures */
	if ( (ddsd.ddpfPixelFormat.dwRGBBitCount<=8) && (ddsd.ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED8))
	{
		/* Lock texture surface to fill it */
		hres=lpDDS->lpVtbl->Lock(lpDDS, NULL, &ddsd, 0, NULL); 
		if (hres!=DD_OK) 
		{
			WCE_DEBUG(L"CopyBitmapToSurface : Failed to lock texture surface\n");
			return FALSE;
		}
		
		/* Copy bitmap to surface */
		memcpy((unsigned char *)ddsd.lpSurface, (unsigned char *)pBm->bmBits, x*y);
	
		/* Unlock texture surface because we're done filling it */
		hres=lpDDS->lpVtbl->Unlock(lpDDS, NULL);
		if (hres!=DD_OK)
		{
			WCE_DEBUG(L"CopyBitmapToSurface : Unlock failed in LoadTexture\n");
			return FALSE;
		}
		
		/* No problem occured */
		return TRUE;
	}

	/* Get pixel format information */
	GetPixelFormatInfo(&ddsd.ddpfPixelFormat, &r, &g, &b, &a,
											  &LeftR, &LeftG, &LeftB, &LeftA,
											  &RightR, &RightG, &RightB, &RightA);


	/* Allocate memory so that we can read data */
	pLineBuffer=(char *)malloc(pBm->bmWidthBytes*sizeof(char));
	pLineBufferTrans=(char *)malloc(pBm->bmWidthBytes*sizeof(char));


	/* Copy process start */

	/* Compute mode used (8, 16 or 32 bits surface) */
	Mode=ddsd.ddpfPixelFormat.dwRGBBitCount + (pBmTrans ? 1 : 0);
	
	/* Lock texture surface to fill it */
    hres=lpDDS->lpVtbl->Lock(lpDDS, NULL, &ddsd, 0, NULL); 
    if (hres!=DD_OK) 
	{
		WCE_DEBUG(L"CopyBitmapToSurface : Failed to lock texture surface\n");
		return FALSE;
	}
	
	/* Loop through y values from bottom to top */
	for (i=y; i!=0; i--)
	{
		/* Calculate pointers corresponding to surface format (8, 16 or 32 bits) */
		lp8b  = (unsigned char *) (((char *)ddsd.lpSurface) + x*i-1);
		lp16b = (unsigned short *)(((char *)ddsd.lpSurface) + x*i*2-2);
		lp32b = (unsigned int *)  (((char *)ddsd.lpSurface) + x*i*4-4);

		/* Copy the current line from the bitmap to pLineBuffer */
		memcpy(pLineBuffer, ((unsigned char *)pBm->bmBits+(i-1)*pBm->bmWidthBytes), pBm->bmWidthBytes);
		if (pBmTrans)
		{
			/* Copy the current line from the transparent bitmap to pLineBufferTrans */
			memcpy(pLineBufferTrans, ((unsigned char *)pBmTrans->bmBits+(i-1)*pBmTrans->bmWidthBytes), pBmTrans->bmWidthBytes);
		}

        /* Has been changed to x*3-1 because last value is NOT x*3, it's x*3-1 */
		Cont=x*3-1;
		
		/* Look through x values from right to left */
		for (j=0; (DWORD)j<x; j++)
		{ 
			/* Get R, G, B values (always 8-bit each, as the bitmap is 24-bit) */
			R = *(pLineBuffer+Cont--);
			G = *(pLineBuffer+Cont--);
			B = *(pLineBuffer+Cont--);
														
			/* Which surface format ? */
			switch (Mode)
			{
			case 8: 
				/* 8 Bits Opaque */
				*(lp8b--) = (R>>RightR)<<LeftR | (G>>RightG)<<LeftG | (B>>RightB)<<LeftB ;
				break;

			case 9: 
				/* 8 Bits Translucent */
				A = *(pLineBufferTrans+Cont+3);
				*(lp8b--) = (R>>RightR)<<LeftR | (G>>RightG)<<LeftG | (B>>RightB)<<LeftB | (A>>RightA)<<LeftA;
				break;

			case 16:
				/* 16 Bits Opaque */
				*(lp16b--) = (R>>RightR)<<LeftR | (G>>RightG)<<LeftG | (B>>RightB)<<LeftB ;
				break;

			case 17:
				/* 16 Bits Translucent */
				A = *(pLineBufferTrans+Cont+3);
				*(lp16b--) = (R>>RightR)<<LeftR | (G>>RightG)<<LeftG | (B>>RightB)<<LeftB | (A>>RightA)<<LeftA;
				break;

			case 32:
				/* 32 Bits Opaque */
				*(lp32b--) = (R>>RightR)<<LeftR | (G>>RightG)<<LeftG | (B>>RightB)<<LeftB ;
				break;

			case 33:
				/* 32 Bits Translucent */
				A = *(pLineBufferTrans+Cont+3);
				*(lp32b--) = (R>>RightR)<<LeftR | (G>>RightG)<<LeftG | (B>>RightB)<<LeftB | (A>>RightA)<<LeftA;
				break;

			default:
				/* Unknow pixel format : free memory and abort */
				lpDDS->lpVtbl->Unlock(lpDDS, NULL);
				free(pLineBuffer);
				free(pLineBufferTrans);
				WCE_DEBUG(L"CopyBitmapToSurface : Unknown pixel format\n");
                return FALSE;
			}
		}
	}
	
    /* Unlock texture surface because we're done filling it */
	hres=lpDDS->lpVtbl->Unlock(lpDDS, NULL);
	if (hres!=DD_OK)
	{
		WCE_DEBUG(L"CopyBitmapToSurface : Unlock failed in LoadTexture\n");
		free(pLineBuffer);
		free(pLineBufferTrans);
		return FALSE;
	}

	/* Free memory */
	free(pLineBuffer);
	free(pLineBufferTrans);

	/* No problem occured */
	return TRUE;
}


/*****************************************************************************
 * Function Name  : CreateAllMipmapLevels
 * Inputs		  : lpDDSTexture, nMipmapType
 * Returns		  : TRUE or FALSE
 * Description    : Create all mipmap levels for a texture.
 *					The texture surface must have been created with the
 *					DDSCAPS_TEXTURE, DDSCAPS_MIPMAP, and DDSCAPS_COMPLEX caps.
 *					Width and Height must have been specified at surface
 *					creation.
 *					Texture must be square and a power of 2.
 *
 *****************************************************************************/
BOOL CreateAllMipmapLevels(LPDIRECTDRAWSURFACE4 lpDDSTexture, int nMipmapType)
{
	HRESULT					hres;
	LPDIRECTDRAWSURFACE4	lpDDSCurrentMemorySurface;
	DDSURFACEDESC2			ddsd;
	DDSCAPS2				ddsCaps;
	DWORD					dwTextureWidth, dwTextureHeight;
	int						nNumberOfMipmapLevels, i;
	TCHAR					pszString[200];

	/* Initialise DDSURFACEDESC2 structure */
	WCE_ZERO_MEMORY(&ddsd, sizeof(DDSURFACEDESC2));
	ddsd.dwSize=sizeof(DDSURFACEDESC2);

	/* Get surface description */
	hres=lpDDSTexture->lpVtbl->GetSurfaceDesc(lpDDSTexture, &ddsd);
	if (hres!=DD_OK)
	{
		WCE_DEBUG(L"CreateAllMipmapLevels : GetSurfaceDesc failed.\n");
		return FALSE;
	}

	/* Check if the texture width and height have been specified */
	if (!(ddsd.dwFlags & DDSD_WIDTH) || !(ddsd.dwFlags & DDSD_HEIGHT))
	{
		WCE_DEBUG(L"CreateAllMipmapLevels : Texture size must be specified.\n");
		return FALSE;
	}

	/* Check if the texture is square */
	if (ddsd.dwWidth!=ddsd.dwHeight)
	{
		WCE_DEBUG(L"CreateAllMipmapLevels : Mipmapping require SQUARE textures.\n");
		return FALSE;
	}

	/* Get texture dimensions */
	dwTextureWidth=ddsd.dwWidth;
	dwTextureHeight=ddsd.dwHeight;

	/* Find out how many mipmap levels have to be created.
	   It depends on the texture size. At the same time,
	   check that texture size is a power of 2 */
	switch(dwTextureWidth)
	{
		case 2048 :	nNumberOfMipmapLevels=11; break;
		case 1024 :	nNumberOfMipmapLevels=10; break;
		case 512 :	nNumberOfMipmapLevels=9; break;
		case 256:	nNumberOfMipmapLevels=8; break;
		case 128:	nNumberOfMipmapLevels=7; break;
		case 64:	nNumberOfMipmapLevels=6; break;
		case 32:	nNumberOfMipmapLevels=5; break;
		case 16:	nNumberOfMipmapLevels=4; break;
		case 8:		nNumberOfMipmapLevels=3; break;
		case 4:		nNumberOfMipmapLevels=2; break;
		case 2:		nNumberOfMipmapLevels=1; break;
		case 1:		WCE_DEBUG(L"CreateAllMipmapLevels : No mipmap level needed for a texture size of 1\n");
					return FALSE; break;
		default :	WCE_DEBUG(L"CreateAllMipmapLevels : Texture size is not a power of 2\n");
					return FALSE;
	}

	/* Current texture surface is top-level mipmap */
	lpDDSCurrentMemorySurface=lpDDSTexture;
	
	/* Create all mipmap levels */
	for (i=1; i<=nNumberOfMipmapLevels; i++)
	{
		if (nMipmapType==D3DTAutoMipmap_2by2)
		{
			/* Create next mipmap level using 2x2 mipmapping */
			if (!CreateNextMipmapLevel2x2(lpDDSCurrentMemorySurface))
			{
				WCE_DEBUG(L"CreateAllMipmapLevels : CreateNextMipmapLevel2x2() failed.\n");
				return FALSE;
			}
		}
		else
		{
			/* Create next mipmap level using 4x4 mipmapping*/
			if (!CreateNextMipmapLevel4x4(lpDDSCurrentMemorySurface))
			{
				WCE_DEBUG(L"CreateAllMipmapLevels : CreateNextMipmapLevel4x4() failed.\n");
				return FALSE;
			}
		}

		/* Get next mipmap */
		WCE_ZERO_MEMORY(&ddsCaps, sizeof(DDSCAPS2));
		ddsCaps.dwCaps=DDSCAPS_TEXTURE | DDSCAPS_MIPMAP ;
		hres=lpDDSCurrentMemorySurface->lpVtbl->GetAttachedSurface(lpDDSCurrentMemorySurface, &ddsCaps, &lpDDSCurrentMemorySurface);
		if (hres!=DD_OK)
		{
			wsprintf(pszString, TEXT("CreateAllMipmapLevels : Failed to get mipmap level %d.\n"), i);
			WCE_DEBUG(pszString);
			return FALSE;
		}
	}

	/* No problem occured */
	return TRUE;
}


/*******************************************************************************
 * Function Name  : CreateFourierMipmapLevels
 * Input		  : lpDD4, lpDev3, *pBm, *pBmTrans, int nOrder
 * Input/Output	  : lpDDSSystemMemorySurface
 * Returns		  : TRUE or FALSE
 * Global Used    : None
 * Description    : Create all mipmap levels of an image pointed to by pBm
 *					and store them in texture surfaces attached to the passed
 *					texture surface.
 *					The texture surface must have been created with the
 *					DDSCAPS_TEXTURE, DDSCAPS_MIPMAP, and DDSCAPS_COMPLEX caps.
 *					Width and Height must have been specified at surface
 *					creation.
 *					Texture must be square and a power of 2.
 *******************************************************************************/
BOOL CreateFourierMipmapLevels(LPDIRECTDRAW4 lpDD4, LPDIRECT3DDEVICE3 lpDev3, 
							   BITMAP *pBm, BITMAP *pBmTrans,
							   LPDIRECTDRAWSURFACE4 lpDDSSystemMemorySurface, 
							   int nOrder)
{
	HRESULT					hres;
	LPDIRECTDRAWSURFACE4	lpDDSCurrentMemorySurface;
	DDSURFACEDESC2			ddsd;
	DDSCAPS2				ddsCaps;
	DWORD					dwMirrorSize, dwTextureSize, dwMipmapSize;
	DWORD					dwOffsetRE, dwOffsetIM;
	DWORD					i, ii1, j;
	BYTE					r, g, b, a;
	BYTE					R, G, B, A;
	BYTE					LeftR, LeftG, LeftB, LeftA; 
	BYTE					RightR, RightG, RightB, RightA;
	BYTE					*lp8b;
	WORD					*lp16b;
	DWORD					*lp32b;
	int						nNumberOfMipmapLevels, nMipmap, nMode;
	float					fScaleFactor, fRedChannel, fGreenChannel, fBlueChannel, fAlphaChannel=-1.0f;
	float					**dataRed, **dataGreen, **dataBlue, **dataAlpha=NULL;
	float					*speqRed, *speqGreen, *speqBlue, *speqAlpha;
	float					**MipmapdataRed, **MipmapdataGreen, **MipmapdataBlue, **MipmapdataAlpha;
	float					*MipmapspeqRed, *MipmapspeqGreen, *MipmapspeqBlue, *MipmapspeqAlpha;
	TCHAR					pszString[200];

	/*********************
	** Check parameters **
	*********************/
	if (!lpDDSSystemMemorySurface || !pBm || !lpDD4 || !lpDev3)
	{
		WCE_DEBUG(L"CreateFourierMipmapLevels : Invalid parameters.\n");
		return FALSE;
	}
	
	/****************************
	** Get surface description **
	****************************/
	/* Initialise DDSURFACEDESC2 structure */
	WCE_ZERO_MEMORY(&ddsd, sizeof(DDSURFACEDESC2));
	ddsd.dwSize=sizeof(DDSURFACEDESC2);

	/* Get surface description */
	hres=lpDDSSystemMemorySurface->lpVtbl->GetSurfaceDesc(lpDDSSystemMemorySurface, &ddsd);
	if (hres!=DD_OK)
	{
		WCE_DEBUG(L"CreateFourierMipmapLevels : GetSurfaceDesc() failed.\n");
		return FALSE;
	}

	/*******************
	** Various checks **
	*******************/
	/* Check if the texture width and height have been specified */
	if (!(ddsd.dwFlags & DDSD_WIDTH) || !(ddsd.dwFlags & DDSD_HEIGHT))
	{
		WCE_DEBUG(L"CreateFourierMipmapLevels : Texture size must be specified.\n");
		return FALSE;
	}

	/* Check if the texture is square */
	if (ddsd.dwWidth!=ddsd.dwHeight)
	{
		WCE_DEBUG(L"CreateFourierMipmapLevels : Mipmapping require SQUARE textures.\n");
		return FALSE;
	}

	/* Get texture size and its wrap-around equivalent */
	dwTextureSize=ddsd.dwWidth;
	dwMirrorSize=2*dwTextureSize;

	/* Check texture dimensions */
	if (dwTextureSize>2048)
	{
		WCE_DEBUG(L"CreateFourierMipmapLevels : Texture size too large.\n");
		return FALSE;
	}

	/* Find out how many mipmap levels have to be created.
	   It depends on the texture size. At the same time,
	   check that texture size is a power of 2 */
	switch(dwTextureSize)
	{
		case 2048 :	nNumberOfMipmapLevels=11; break;
		case 1024 :	nNumberOfMipmapLevels=10; break;
		case 512 :	nNumberOfMipmapLevels=9; break;
		case 256:	nNumberOfMipmapLevels=8; break;
		case 128:	nNumberOfMipmapLevels=7; break;
		case 64:	nNumberOfMipmapLevels=6; break;
		case 32:	nNumberOfMipmapLevels=5; break;
		case 16:	nNumberOfMipmapLevels=4; break;
		case 8:		nNumberOfMipmapLevels=3; break;
		case 4:		nNumberOfMipmapLevels=2; break;
		case 2:		nNumberOfMipmapLevels=1; break;
		case 1:		WCE_DEBUG(L"CreateFourierMipmapLevels : No mipmap level needed for a texture size of 1\n");
					return FALSE; break;
		default :	WCE_DEBUG(L"CreateFourierMipmapLevels : Texture size is not a power of 2\n");
					return FALSE;
	}

	/*************************
	** Texture pixel format **
	*************************/
	/* Get information about pixel format */
	GetPixelFormatInfo(&ddsd.ddpfPixelFormat, &r, &g, &b, &a,
											  &LeftR, &LeftG, &LeftB, &LeftA,
											  &RightR, &RightG, &RightB, &RightA);

	/* Compute mode used (8, 16 or 32 bits surface) */
	nMode=ddsd.ddpfPixelFormat.dwRGBBitCount + (pBmTrans ? 1 : 0);


	/***************************************************
	** Allocate memory each channel's frequency space **
	***************************************************/
	dataRed=AllocateSquareMatrix(dwMirrorSize);
	speqRed=AllocateVector(2*dwMirrorSize);
	dataGreen=AllocateSquareMatrix(dwMirrorSize);
	speqGreen=AllocateVector(2*dwMirrorSize);
	dataBlue=AllocateSquareMatrix(dwMirrorSize);
	speqBlue=AllocateVector(2*dwMirrorSize);
	if (pBmTrans)
	{
		dataAlpha=AllocateSquareMatrix(dwMirrorSize);
		speqAlpha=AllocateVector(2*dwMirrorSize);
	}

	/* Debug info */
	WCE_DEBUG(L"Generating mipmap level : 0");
		
	/****************************
	** Expand data into mirror **
	****************************/
	MirrorExpandBitmap(dataRed, dataGreen, dataBlue, pBmTrans ? dataAlpha : NULL, 
					   pBm, pBmTrans);

	/* Progress indicator */
	WCE_DEBUG(L".");
	
	
	/***************************
	** Fast Fourier Transform **
	***************************/
	/* Apply FFT to get frequency space of each color channel */
	RealFFT2D(dataRed,		speqRed,	dwMirrorSize, dwMirrorSize, 1);
	RealFFT2D(dataGreen,	speqGreen,	dwMirrorSize, dwMirrorSize, 1);
	RealFFT2D(dataBlue,		speqBlue,	dwMirrorSize, dwMirrorSize, 1);
	if (pBmTrans)
	{
		RealFFT2D(dataAlpha, speqAlpha,	dwMirrorSize, dwMirrorSize, 1);
	}

	/* Progress indicator */
	WCE_DEBUG(L".");
	
		
	/*******************************
	** Initialise mipmap creation **
	*******************************/
	/* Current texture surface is top-level mipmap */
	lpDDSCurrentMemorySurface=lpDDSSystemMemorySurface;

	/* Mipmap initial size */
	dwMipmapSize=dwTextureSize;

	/* Compute amount to multiply output of inverse Fourier with */
	fScaleFactor=1.0f/(dwMirrorSize*dwMirrorSize/2);

	/*************************
	** Mipmap creation loop **
	*************************/
	for (nMipmap=1; nMipmap<=nNumberOfMipmapLevels; nMipmap++)
	{
		/* Compute new mipmap level size (half of previous size) */
		dwMipmapSize>>=1;
		
		/* Debug info */
		wsprintf(pszString, TEXT("%d"), nMipmap);
		WCE_DEBUG(pszString);

		/****************************
		** Get next mipmap surface **
		*****************************/
		WCE_ZERO_MEMORY(&ddsCaps, sizeof(DDSCAPS2));
		ddsCaps.dwCaps=DDSCAPS_TEXTURE | DDSCAPS_MIPMAP;
		hres=lpDDSCurrentMemorySurface->lpVtbl->GetAttachedSurface(lpDDSCurrentMemorySurface, &ddsCaps, &lpDDSCurrentMemorySurface);
		if (hres!=DD_OK)
		{
			wsprintf(pszString, TEXT("CreateFourierMipmapLevels : Failed to get mipmap level %d.\n"), nMipmap);
			WCE_DEBUG(pszString);
			FreeVector(speqBlue, 2*dwMirrorSize);
			FreeSquareMatrix(dataBlue, dwMirrorSize);
			FreeVector(speqGreen, 2*dwMirrorSize);
			FreeSquareMatrix(dataGreen, dwMirrorSize);
			FreeVector(speqRed, 2*dwMirrorSize);
			FreeSquareMatrix(dataRed, dwMirrorSize);
			return FALSE;
		}

		/*************************************************
		** Allocate memory for mipmap spectrum and data **
		*************************************************/
		MipmapdataRed=AllocateSquareMatrix(2*dwMipmapSize);
		MipmapspeqRed=AllocateVector(2*(2*dwMipmapSize));
		MipmapdataGreen=AllocateSquareMatrix(2*dwMipmapSize);
		MipmapspeqGreen=AllocateVector(2*(2*dwMipmapSize));
		MipmapdataBlue=AllocateSquareMatrix(2*dwMipmapSize);
		MipmapspeqBlue=AllocateVector(2*(2*dwMipmapSize));
		if (pBmTrans)
		{
			MipmapdataAlpha=AllocateSquareMatrix(2*dwMipmapSize);
			MipmapspeqAlpha=AllocateVector(2*(2*dwMipmapSize));
		}
	
			
		/************************************************
		** Copy lower frequencies into mipmap spectrum **
		************************************************/
		/* For each row */
		for (i=1; i<=dwMipmapSize; i++)
		{
			/* For each column of each row */
			for (j=1; j<=dwMipmapSize; j++)
			{
				/* Compute real and imaginary part offsets */
				dwOffsetRE=(j<<1)-1;
				dwOffsetIM=j<<1;
				
				/* Copy frequencies */
				MipmapdataRed[i][dwOffsetRE] =	dataRed[i][dwOffsetRE];
				MipmapdataRed[i][dwOffsetIM] =	dataRed[i][dwOffsetIM];
				MipmapdataGreen[i][dwOffsetRE]= dataGreen[i][dwOffsetRE];
				MipmapdataGreen[i][dwOffsetIM]=	dataGreen[i][dwOffsetIM];
				MipmapdataBlue[i][dwOffsetRE] =	dataBlue[i][dwOffsetRE];
				MipmapdataBlue[i][dwOffsetIM]=	dataBlue[i][dwOffsetIM];
				if (pBmTrans)
				{
					MipmapdataAlpha[i][dwOffsetRE] = dataAlpha[i][dwOffsetRE];
					MipmapdataAlpha[i][dwOffsetIM] = dataAlpha[i][dwOffsetIM];
				}
			}
			/* Last value of j(dwMipmapSize+1) is in speq */
			MipmapspeqRed[(i<<1)-1]=	speqRed[(i<<1)-1];
			MipmapspeqRed[(i<<1)]=		speqRed[(i<<1)];
			MipmapspeqGreen[(i<<1)-1]=	speqGreen[(i<<1)-1];
			MipmapspeqGreen[(i<<1)]=	speqGreen[(i<<1)];
			MipmapspeqBlue[(i<<1)-1]=	speqBlue[(i<<1)-1];
			MipmapspeqBlue[(i<<1)]=		speqBlue[(i<<1)];
			if (pBmTrans)
			{
				MipmapspeqAlpha[(i<<1)-1]=	speqAlpha[(i<<1)-1];
				MipmapspeqAlpha[(i<<1)]=	speqAlpha[(i<<1)];
			}
		}
		/* For each row */
		for (i=dwMipmapSize+1, ii1=dwMirrorSize-dwMipmapSize+1; i<=2*dwMipmapSize; i++, ii1++)
		{
			/* For each column of each row */
			for (j=1; j<=dwMipmapSize; j++)
			{
				/* Compute real and imaginary part offsets */
				dwOffsetRE=(j<<1)-1;
				dwOffsetIM=(j<<1);

				/* Copy frequencies */
				MipmapdataRed[i][dwOffsetRE] =	dataRed[ii1][dwOffsetRE];
				MipmapdataRed[i][dwOffsetIM]=	dataRed[ii1][dwOffsetIM];
				MipmapdataGreen[i][dwOffsetRE]= dataGreen[ii1][dwOffsetRE];
				MipmapdataGreen[i][dwOffsetIM]=	dataGreen[ii1][dwOffsetIM];
				MipmapdataBlue[i][dwOffsetRE] =	dataBlue[ii1][dwOffsetRE];
				MipmapdataBlue[i][dwOffsetIM]=	dataBlue[ii1][dwOffsetIM];
				if (pBmTrans)
				{
					MipmapdataAlpha[i][dwOffsetRE]=	dataAlpha[ii1][dwOffsetRE];
					MipmapdataAlpha[i][dwOffsetIM]=	dataAlpha[ii1][dwOffsetIM];
				}
			}
			/* Last value of j(dwMipmapSize+1) is in speq */
			MipmapspeqRed[(i<<1)-1]=	speqRed[(ii1<<1)-1];
			MipmapspeqRed[(i<<1)]=		speqRed[(ii1<<1)];
			MipmapspeqGreen[(i<<1)-1]=	speqGreen[(ii1<<1)-1];
			MipmapspeqGreen[(i<<1)]=	speqGreen[(ii1<<1)];
			MipmapspeqBlue[(i<<1)-1]=	speqBlue[(ii1<<1)-1];
			MipmapspeqBlue[(i<<1)]=		speqBlue[(ii1<<1)];
			if (pBmTrans)
			{
				MipmapspeqAlpha[(i<<1)-1]=	speqAlpha[(ii1<<1)-1];
				MipmapspeqAlpha[(i<<1)]=	speqAlpha[(ii1<<1)];
			}
		}

		/* Progress indicator */
		WCE_DEBUG(L".");

		/********************************************************************
		** Apply a butterworth low-pass filter to new range of frequencies **
		********************************************************************/
		if (nOrder)
		{
			ApplyLowPassFilter(MipmapdataRed,	MipmapspeqRed,		2*dwMipmapSize, 0.5f, nOrder);
			ApplyLowPassFilter(MipmapdataGreen, MipmapspeqGreen,	2*dwMipmapSize, 0.5f, nOrder);
			ApplyLowPassFilter(MipmapdataBlue,	MipmapspeqBlue,		2*dwMipmapSize, 0.5f, nOrder);
			if (pBmTrans)
			{
				ApplyLowPassFilter(MipmapdataAlpha,	MipmapspeqAlpha, 2*dwMipmapSize, 0.5f, nOrder);
			}
		}

		/* Progress indicator */
		WCE_DEBUG(L".");
		
		/****************
		** Inverse FFT **
		****************/
		RealFFT2D(MipmapdataRed,	MipmapspeqRed,		2*dwMipmapSize, 2*dwMipmapSize, -1);
		RealFFT2D(MipmapdataGreen,	MipmapspeqGreen,	2*dwMipmapSize, 2*dwMipmapSize, -1);
		RealFFT2D(MipmapdataBlue,	MipmapspeqBlue,		2*dwMipmapSize, 2*dwMipmapSize, -1);
		if (pBmTrans)
		{
			RealFFT2D(MipmapdataAlpha,	MipmapspeqAlpha, 2*dwMipmapSize, 2*dwMipmapSize, -1);
		}

		/* Progress indicator */
		WCE_DEBUG(L".");
		
		
		/****************************
		** Mipmap surface creation **
		****************************/
		/* Initialise ddsd */
		WCE_ZERO_MEMORY(&ddsd, sizeof(ddsd));
		ddsd.dwSize=sizeof(ddsd);
		
		/* Lock texture surface to fill it */
		hres=lpDDSCurrentMemorySurface->lpVtbl->Lock(lpDDSCurrentMemorySurface, NULL, &ddsd, 0, NULL); 
		if (hres!=DD_OK) 
		{
			WCE_DEBUG(L"CreateFourierMipmapLevels : Failed to lock texture surface\n");
			if (pBmTrans)
			{
				FreeVector(MipmapspeqAlpha, 2*(2*dwMipmapSize));
				FreeSquareMatrix(MipmapdataAlpha, 2*dwMipmapSize);
			}
			FreeVector(MipmapspeqBlue, 2*(2*dwMipmapSize));
			FreeSquareMatrix(MipmapdataBlue, 2*dwMipmapSize);
			FreeVector(MipmapspeqGreen, 2*(2*dwMipmapSize));
			FreeSquareMatrix(MipmapdataGreen, 2*dwMipmapSize);
			FreeVector(MipmapspeqRed, 2*(2*dwMipmapSize));
			FreeSquareMatrix(MipmapdataRed, 2*dwMipmapSize);
			if (pBmTrans)
			{
				FreeVector(speqAlpha, 2*dwMirrorSize);
				FreeSquareMatrix(dataAlpha, dwMirrorSize);
			}
			FreeVector(speqBlue, 2*dwMirrorSize);
			FreeSquareMatrix(dataBlue, dwMirrorSize);
			FreeVector(speqGreen, 2*dwMirrorSize);
			FreeSquareMatrix(dataGreen, dwMirrorSize);
			FreeVector(speqRed, 2*dwMirrorSize);
			FreeSquareMatrix(dataRed, dwMirrorSize);
			return FALSE;
		}

		/* Loop through y values from bottom to top */
		for (i=dwMipmapSize; i>0; i--)
		{
			/* Calculate pointers corresponding to surface format (8, 16 or 32 bits) */
			lp8b  = (unsigned char *) (((unsigned char *)ddsd.lpSurface) + dwMipmapSize*i-1);
			lp16b = (unsigned short *)(((unsigned char *)ddsd.lpSurface) + dwMipmapSize*i*2-2);
			lp32b = (unsigned int *)  (((unsigned char *)ddsd.lpSurface) + dwMipmapSize*i*4-4);

			/* Look through x values from right to left */
			for (j=1; j<=(int)dwMipmapSize; j++)
			{ 
				/* Get R, G, B values (always 8-bit each, as the bitmap is 24-bit) */
				fRedChannel=	MipmapdataRed[(dwMipmapSize>>1) + i][(dwMipmapSize>>1) + j]*fScaleFactor;
				fGreenChannel=	MipmapdataGreen[(dwMipmapSize>>1) + i][(dwMipmapSize>>1) + j]*fScaleFactor;
				fBlueChannel=	MipmapdataBlue[(dwMipmapSize>>1) + i][(dwMipmapSize>>1) + j]*fScaleFactor;
				if (pBmTrans)
				{
					fAlphaChannel=MipmapdataAlpha[(dwMipmapSize>>1) + i][(dwMipmapSize>>1) + j]*fScaleFactor;
				}

				/* Write each color channel float value into a byte (0-255) */
				if (fRedChannel<0.0f) R=0;
					else if (fRedChannel>255.0f) R=255;
						else R=fround(fRedChannel);
				if (fGreenChannel<0.0f) G=0;
					else if (fGreenChannel>255.0f) G=255;
						else G=fround(fGreenChannel);
				if (fBlueChannel<0.0f) B=0;
					else if (fBlueChannel>255.0f) B=255;
						else B=fround(fBlueChannel);
				if (fAlphaChannel<0.0f) A=0;
					else if (fAlphaChannel>255.0f) A=255;
						else A=fround(fAlphaChannel);

				/* Which surface format ? */
				switch (nMode)
				{
				case 8:		/* 8 Bits Opaque */
							*(lp8b--) = (R>>RightR)<<LeftR | (G>>RightG)<<LeftG | (B>>RightB)<<LeftB; break;
				case 9:		/* 8 Bits Translucent */
							*(lp8b--) = (R>>RightR)<<LeftR | (G>>RightG)<<LeftG | (B>>RightB)<<LeftB | (A>>RightA)<<LeftA; break;
				
				case 16:	/* 16 Bits Opaque */
							*(lp16b--) = (R>>RightR)<<LeftR | (G>>RightG)<<LeftG | (B>>RightB)<<LeftB; break;
				case 17:	/* 16 Bits Translucent */
							*(lp16b--) = (R>>RightR)<<LeftR | (G>>RightG)<<LeftG | (B>>RightB)<<LeftB | (A>>RightA)<<LeftA; break;
				
				case 32:	/* 32 Bits Opaque */
							*(lp32b--) = (R>>RightR)<<LeftR | (G>>RightG)<<LeftG | (B>>RightB)<<LeftB; break;
				case 33:	/* 32 Bits Translucent */
							*(lp32b--) = (R>>RightR)<<LeftR | (G>>RightG)<<LeftG | (B>>RightB)<<LeftB | (A>>RightA)<<LeftA;	break;
				
				default:	/* Unknow pixel format : free memory and abort */
							lpDDSCurrentMemorySurface->lpVtbl->Unlock(lpDDSCurrentMemorySurface, NULL);
							WCE_DEBUG(L"CreateFourierMipmapLevels : Unknown pixel format\n");
							if (pBmTrans)
							{
								FreeVector(MipmapspeqAlpha, 2*(2*dwMipmapSize));
								FreeSquareMatrix(MipmapdataAlpha, 2*dwMipmapSize);
							}
							FreeVector(MipmapspeqBlue, 2*(2*dwMipmapSize));
							FreeSquareMatrix(MipmapdataBlue, 2*dwMipmapSize);
							FreeVector(MipmapspeqGreen, 2*(2*dwMipmapSize));
							FreeSquareMatrix(MipmapdataGreen, 2*dwMipmapSize);
							FreeVector(MipmapspeqRed, 2*(2*dwMipmapSize));
							FreeSquareMatrix(MipmapdataRed, 2*dwMipmapSize);
							if (pBmTrans)
							{
								FreeVector(speqAlpha, 2*dwMirrorSize);
								FreeSquareMatrix(dataAlpha, dwMirrorSize);
							}
							FreeVector(speqBlue, 2*dwMirrorSize);
							FreeSquareMatrix(dataBlue, dwMirrorSize);
							FreeVector(speqGreen, 2*dwMirrorSize);
							FreeSquareMatrix(dataGreen, dwMirrorSize);
							FreeVector(speqRed, 2*dwMirrorSize);
							FreeSquareMatrix(dataRed, dwMirrorSize);
							return FALSE;
				}
			}
		}

		/* Unlock surface */
		lpDDSCurrentMemorySurface->lpVtbl->Unlock(lpDDSCurrentMemorySurface, NULL);

		/* Last progress indicator */
		WCE_DEBUG(L".");

		/***********************
		** Free mipmap memory **
		***********************/
		if (pBmTrans)
		{
			FreeVector(MipmapspeqAlpha, 2*(2*dwMipmapSize));
			FreeSquareMatrix(MipmapdataAlpha, 2*dwMipmapSize);
		}
		FreeVector(MipmapspeqBlue, 2*(2*dwMipmapSize));
		FreeSquareMatrix(MipmapdataBlue, 2*dwMipmapSize);
		FreeVector(MipmapspeqGreen, 2*(2*dwMipmapSize));
		FreeSquareMatrix(MipmapdataGreen, 2*dwMipmapSize);
		FreeVector(MipmapspeqRed, 2*(2*dwMipmapSize));
		FreeSquareMatrix(MipmapdataRed, 2*dwMipmapSize);
	}

	/* Carriage return */
	WCE_DEBUG(L"\n");

	/***************************************
	** Free memory used for spectrum data **
	***************************************/
	if (pBmTrans)
	{
		FreeVector(speqAlpha, 2*dwMirrorSize);
		FreeSquareMatrix(dataAlpha, dwMirrorSize);
	}
	FreeVector(speqBlue, 2*dwMirrorSize);
	FreeSquareMatrix(dataBlue, dwMirrorSize);
	FreeVector(speqGreen, 2*dwMirrorSize);
	FreeSquareMatrix(dataGreen, dwMirrorSize);
	FreeVector(speqRed, 2*dwMirrorSize);
	FreeSquareMatrix(dataRed, dwMirrorSize);
	
	/* No problem occured */
	return TRUE;
}


/*******************************************************************************
 * Function Name  : DitherBitmap
 * Returns		  : Nothing
 * Inputs		  : XDim, YDim, MapType
 * Inputs/Outputs : *pBitmapData, *pTranslucentBitmapData
 * Global Used    : None
 * Description    : Performs Floyd Steinberg Dithering.
 *				    Multi-pass dither may be required for the edges of textures.
 *				    There is room for optimization here.
 *					This functions is pretty much the same as the one used
 *					in SGL1.
 *					Because PMX handles channels conversions in a different way
 *					that PCX, the "error values" computed in this function would
 *					need updating to match the current HW specifications.
 *
 *******************************************************************************/
void DitherBitmap(int XDim, int YDim, DDPIXELFORMAT *lpddPixelFormat,
			      unsigned char *pBitmapData, unsigned char *pTranslucentBitmapData)
{
	unsigned char	*pPixel, *pTranslucentPixel;
	int				*pBErr;
	int				LeftErr[4], BelowLeftErr[4];
	int				BelowErr[1024][4];
	int				Red,Green,Blue,Alpha;
	int				Err38ths;
	int				x, y;
	BYTE			r, g, b, a;

#define CLAMP(x,min,max)  (((x) < (min)) ? (min) : (((x) > (max)) ? (max) : (x)))
	
	/* if this map is too small to dither, skip it */
	if(XDim==1 || YDim==1) return;

	/* Find how many bits per channel */
	GetPixelFormatInfo(lpddPixelFormat, &r, &g, &b, &a,
										NULL, NULL, NULL, NULL,
										NULL, NULL, NULL, NULL);

	/* Check that we are going to dither a valid format */
	if (!( (r==5 && g==5 && b==5) || (r==5 && g==6 && b==5) || (r==4 && g==4 && b==4 && a==4) ))
	{
		WCE_DEBUG(L"DitherBitmap : Texture format not supported\n");
		return;
	}
	
	/* Initialize the error values passed onto the pixels below */
	pBErr=BelowErr[0];
	for(x=XDim; x!=0; x--)
	{
		pBErr[0] = 0;
		pBErr[1] = 0;
		pBErr[2] = 0;
		pBErr[3] = 0;

		pBErr += 4;
	}

	/* Initialise the error passed from the pixel to the left, and the one below. */
	LeftErr[0] = 0;
	LeftErr[1] = 0;
	LeftErr[2] = 0;
	LeftErr[3] = 0;
	BelowLeftErr[0] = 0;
	BelowLeftErr[1] = 0;
	BelowLeftErr[2] = 0;
	BelowLeftErr[3] = 0;

	/* Set pointer to the first pixel */
	pPixel=pBitmapData;
	if (pTranslucentBitmapData) pTranslucentPixel=pTranslucentBitmapData;
	
	/* Step through the rows and columns */
	for(y=YDim; y!=0; y--)
	{
		/* Reset the pointer to the errors passed to the row below */
		pBErr=BelowErr[0];

		/* Step through this row */
		for(x=XDim; x!=0; x--)
		{
			/* Add the passed on errors to this pixel.
			   These are the errors supplied from the row above, and the pixel to the left.
			   Clamp the result to the legal range. */
			Red     = *pPixel	  + pBErr[0] + LeftErr[0];
			Red		= CLAMP(Red, 0, 255);
			*pPixel++ = Red;

			Green   = *pPixel + pBErr[1] + LeftErr[1];
			Green	= CLAMP(Green, 0, 255); 
			*pPixel++ = Green;

			Blue    = *pPixel + pBErr[2] + LeftErr[2];
			Blue	= CLAMP(Blue, 0, 255); 
			*pPixel++ = Blue;

			if (pTranslucentBitmapData)
			{
				Alpha = *pTranslucentPixel + pBErr[3] + LeftErr[3];
				Alpha = CLAMP(Alpha, 0, 255); 
				*pTranslucentPixel=Alpha;
				pTranslucentPixel+=3;
			}
						
			/* Compute the error when dithering */
			if (g==6)	/* 565 texture format */
			{
				Red   = (Red - ((Red & 0xf8) | 4));
				Green = (Green - ((Green & 0xfc) | 2));
				Blue  = (Blue - ((Blue & 0xf8) | 4));
				Alpha = 0;
			}
			if (g==5)	/* 555 or 1555 texture format */
			{
				Red   = (Red - ((Red & 0xf8) | 4));
				Green = (Green - ((Green & 0xf8) | 4));
				Blue  = (Blue - ((Blue & 0xf8) | 4));
				Alpha = 0;	/* Because no dithering is necessary on 1-bit data */
			}
			if (g==4)	/* 4444 texture format */
			{
				Red   = (Red - ((Red & 0xfc) | 2));
				Green = (Green - ((Green & 0xfc) | 2));
				Blue  = (Blue - ((Blue & 0xfc) | 2));
				Alpha = (Alpha - ((Alpha & 0xfc) | 2));
			}
		
			/* Distribute the error.
			   3/8ths goes to the pixel to the left and to the one below.
			   For the one below, remember to add on the bit to its left.
			   Also distribute 1/4 of the error to the "below right" pixel  */
			/* Red */
			Err38ths = ((3*Red) + 4)>> 3;
			LeftErr[0] = Err38ths;
			pBErr[0]   = BelowLeftErr[0] + Err38ths;
			BelowLeftErr[0] = Red - (Err38ths << 1);

			/* Green */
			Err38ths = ((3*Green) + 4) >> 3;
			LeftErr[1] = Err38ths;
			pBErr[1]   = BelowLeftErr[1] + Err38ths;
			BelowLeftErr[1] = Green  - (Err38ths << 1);

			/* Blue */
			Err38ths = ((3*Blue) + 4) >> 3;
			LeftErr[2] = Err38ths;
			pBErr[2]   = BelowLeftErr[2] + Err38ths;
			BelowLeftErr[2] = Blue  - (Err38ths << 1);

			/* Alpha */
			Err38ths = ((3*Alpha)+4) >> 3;
			LeftErr[3] = Err38ths;
			pBErr[3]   = BelowLeftErr[3] + Err38ths;
			BelowLeftErr[3] = Alpha  - (Err38ths << 1);

			/* Move to the next pixel along */
			pBErr += 4;
		}
	}
}


/*****************************************************************************
 * Function Name  : CreateNextMipmapLevel2x2
 * Inputs		  : lpDDSTextureSurface
 * Returns		  : TRUE or FALSE
 * Description    : Create next mipmap level from lpDDSTextureSurface.
 *					The next mipmap is computed using a 2x2 algorithm.
 *					Four pixels in the source surface define one pixel
 *					in the destination surface.
 *					For alpha textures, the four pixels channels are weighted
 *					with their opacity values (Alpha).
 *
 *****************************************************************************/
BOOL CreateNextMipmapLevel2x2(LPDIRECTDRAWSURFACE4 lpDDSTextureSurface)
{
	HRESULT					hres;
	LPDIRECTDRAWSURFACE4	lpDDSSourceSurface, lpDDSDestinationSurface;
	DDSURFACEDESC2			ddsdSrc, ddsdDest;
	DDSCAPS2				ddsCaps;
	PixelMap				Pixel1, Pixel2, Pixel3, Pixel4;
	PixelMap				*lpTmpMap, *lpPixel;
	DWORD					*lp32b, *lpSrc32b;
	unsigned char			*lp8b, *lpSrc8b;
	unsigned short			*lp16b, *lpSrc16b;
	int						*pOutputColor;
	int						dwSourceWidth, dwSourceHeight, dwDestWidth, dwDestHeight;
	DWORD					dwSurfaceDepth;
	DWORD					dwRedMask, dwGreenMask, dwBlueMask, dwAlphaMask;
	int						lSrcPitch, lDestPitch;
	BYTE					r, g, b, a;
	BYTE					RedShift, GreenShift, BlueShift, AlphaShift;
	int						a1, a2, a3, a4, Alpha;
	int						i, j, k;
	float					fInvA;
	TCHAR					pszString[200];
		
	/* Get source surface pointer */
	lpDDSSourceSurface=lpDDSTextureSurface;

	/* Initialise DDSURFACEDESC2 structure */
	WCE_ZERO_MEMORY(&ddsdSrc, sizeof(DDSURFACEDESC2));
	ddsdSrc.dwSize=sizeof(DDSURFACEDESC2);

	/* Get surface description */
	hres=lpDDSSourceSurface->lpVtbl->GetSurfaceDesc(lpDDSSourceSurface, &ddsdSrc);
	if (hres!=DD_OK)
	{
		WCE_DEBUG(L"CreateNextMipmapLevel2x2 : GetSurfaceDesc failed.\n");
		return FALSE;
	}

	/* Get surface info */
	dwSourceWidth=ddsdSrc.dwWidth;
	dwSourceHeight=ddsdSrc.dwHeight;
	lSrcPitch=ddsdSrc.lPitch;
	dwSurfaceDepth=ddsdSrc.ddpfPixelFormat.dwRGBBitCount;
	
	/* Check if surface depth is 8, 16 or 32 bits */
	if (dwSurfaceDepth!=8 && dwSurfaceDepth!=16 && dwSurfaceDepth!=32)
	{
		wsprintf(pszString, TEXT("CreateNextMipmapLevel2x2 : Surface Depth of %d not supported.\n"), dwSurfaceDepth);
		WCE_DEBUG(pszString);
		return FALSE;
	}
	
	/* Get number of bits per color channel in surface */
	GetPixelFormatInfo(&ddsdSrc.ddpfPixelFormat, &r, &g, &b, &a,
												 &RedShift, &GreenShift, &BlueShift, &AlphaShift,
												 NULL, NULL, NULL, NULL);

	/* Get masks */
	dwRedMask=ddsdSrc.ddpfPixelFormat.dwRBitMask; 
	dwGreenMask=ddsdSrc.ddpfPixelFormat.dwGBitMask; 
	dwBlueMask=ddsdSrc.ddpfPixelFormat.dwBBitMask; 
	dwAlphaMask=ddsdSrc.ddpfPixelFormat.dwRGBAlphaBitMask; 


	/* Get memory for pointer that will receive 2 lines of source surface */
	lpTmpMap=(PixelMap *)malloc(2*dwSourceWidth*sizeof(PixelMap));
	if (!lpTmpMap)
	{
		WCE_DEBUG(L"CreateNextMipmapLevel2x2 : Not enough memory to allocate lpTmpMap\n");
		return FALSE;
	}

	/* Get memory for pointer that will receive the output line */
	pOutputColor=(int *)malloc((dwSourceWidth>>1)*sizeof(int));
	if (!pOutputColor)
	{
		WCE_DEBUG(L"CreateNextMipmapLevel2x2 : Not enough memory to allocate pOutputColor\n");
		free(lpTmpMap);
		return FALSE;
	}


	/* Get destination mipmap */
	WCE_ZERO_MEMORY(&ddsCaps, sizeof(DDSCAPS2));
	ddsCaps.dwCaps=DDSCAPS_TEXTURE | DDSCAPS_MIPMAP;
	hres=lpDDSSourceSurface->lpVtbl->GetAttachedSurface(lpDDSSourceSurface, &ddsCaps, &lpDDSDestinationSurface);
	if (hres!=DD_OK)
	{
		WCE_DEBUG(L"CreateNextMipmapLevel2x2 : Failed to get attached surface\n");
		free(pOutputColor);
		free(lpTmpMap);
		return FALSE;
	}

	/* If translucent, then add 1 to surface depth as an ID */
	if (a)
	{
		dwSurfaceDepth+=1;
	}
	
	/* Reinitialise DDSURFACEDESC2 structure */
	WCE_ZERO_MEMORY(&ddsdSrc, sizeof(DDSURFACEDESC2));
	ddsdSrc.dwSize=sizeof(DDSURFACEDESC2);

	/* Lock texture surface to read it */
	hres=lpDDSSourceSurface->lpVtbl->Lock(lpDDSSourceSurface, NULL, &ddsdSrc, DDLOCK_READONLY, NULL); 
    if (hres!=DD_OK) 
	{
		WCE_DEBUG(L"CreateNextMipmapLevel2x2 : Failed to lock texture surface\n");
		return FALSE;
	}

	/* Reinitialise DDSURFACEDESC2 structure */
	WCE_ZERO_MEMORY(&ddsdDest, sizeof(DDSURFACEDESC2));
	ddsdDest.dwSize=sizeof(DDSURFACEDESC2);

	/* Lock destination surface to fill it */
    hres=lpDDSDestinationSurface->lpVtbl->Lock(lpDDSDestinationSurface, NULL, &ddsdDest, 0, NULL); 
    if (hres!=DD_OK) 
	{
		WCE_DEBUG(L"CreateNextMipmapLevel2x2 : Failed to lock texture surface\n");
		free(pOutputColor);
		free(lpTmpMap);
		return FALSE;
	}

	/* Get surface info */
	dwDestWidth=ddsdDest.dwWidth;
	dwDestHeight=ddsdDest.dwHeight;
	lDestPitch=ddsdDest.lPitch;

	/* Pitch must be in pointer size unit, not in bytes */
	switch(dwSurfaceDepth)
	{
	case 8 :	
	case 9 :	break;
	case 16 :
	case 17 :	lSrcPitch>>=1;
				lDestPitch>>=1;
				break;
	case 32 :
	case 33 :	lSrcPitch>>=2;
				lDestPitch>>=2;
				break;
	}

	
	/* Copy loop starts here */

	/* For each line of destination surface */
	for (i=0; i<dwDestWidth; i++)
	{
		/* Get pointer to destination line */
		lpPixel=(PixelMap *)(lpTmpMap);
		
		/* Copy the 2 current source lines into PixelMap */

		/* Copy source surface into intermediate map where 1 byte = 1 color channel */
		switch(dwSurfaceDepth)
		{
		case 8 :		for (j=0; j<2; j++)
						{
							/* Get 8 bits pointer to read the four source surface line */
							lpSrc8b=(unsigned char *)( (unsigned char *)ddsdSrc.lpSurface + ((i<<1)+j)*lSrcPitch );
			
							for (k=0; k<dwSourceWidth; k++)
							{
								lpPixel->r=(unsigned char)(( (*lpSrc8b) & dwRedMask	  ) >> RedShift);
								lpPixel->g=(unsigned char)(( (*lpSrc8b) & dwGreenMask ) >> GreenShift);
								lpPixel->b=(unsigned char)(( (*lpSrc8b) & dwBlueMask  ) >> BlueShift);
								lpSrc8b++;
								lpPixel++;
							}
						}
						break;

		case 9 :		for (j=0; j<2; j++)
						{
							/* Get 8 bits pointer to read the four source surface line */
							lpSrc8b=(unsigned char *)( (unsigned char *)ddsdSrc.lpSurface + ((i<<1)+j)*lSrcPitch );
			
							for (k=0; k<dwSourceWidth; k++)
							{
								lpPixel->r=(unsigned char)(( (*lpSrc8b) & dwRedMask	  ) >> RedShift);
								lpPixel->g=(unsigned char)(( (*lpSrc8b) & dwGreenMask ) >> GreenShift);
								lpPixel->b=(unsigned char)(( (*lpSrc8b) & dwBlueMask  ) >> BlueShift);
								lpPixel->a=(unsigned char)(( (*lpSrc8b) & dwAlphaMask ) >> AlphaShift);
								lpSrc8b++;
								lpPixel++;
							}
						}
						break;

		case 16 :		for (j=0; j<2; j++)
						{
							/* Get 16 bits pointer to read the four source surface line */
							lpSrc16b=(unsigned short *)( (unsigned short *)ddsdSrc.lpSurface + ((i<<1)+j)*lSrcPitch );
			
							for (k=0; k<dwSourceWidth; k++)
							{
								lpPixel->r=(unsigned char)(( (*lpSrc16b) & dwRedMask   ) >> RedShift);
								lpPixel->g=(unsigned char)(( (*lpSrc16b) & dwGreenMask ) >> GreenShift);
								lpPixel->b=(unsigned char)(( (*lpSrc16b) & dwBlueMask  ) >> BlueShift);
								lpSrc16b++;
								lpPixel++;
							}
						}
						break;

		case 17 :		for (j=0; j<2; j++)
						{
							/* Get 16 bits pointer to read the four source surface line */
							lpSrc16b=(unsigned short *)( (unsigned short *)ddsdSrc.lpSurface + ((i<<1)+j)*lSrcPitch );
			
							for (k=0; k<dwSourceWidth; k++)
							{
								lpPixel->r=(unsigned char)(( (*lpSrc16b) & dwRedMask   ) >> RedShift);
								lpPixel->g=(unsigned char)(( (*lpSrc16b) & dwGreenMask ) >> GreenShift);
								lpPixel->b=(unsigned char)(( (*lpSrc16b) & dwBlueMask  ) >> BlueShift);
								lpPixel->a=(unsigned char)(( (*lpSrc16b) & dwAlphaMask ) >> AlphaShift);;
								lpSrc16b++;
								lpPixel++;
							}
						}
						break;

		case 32 :		for (j=0; j<2; j++)
						{
							/* Get 32 bits pointer to read the four source surface line */
							lpSrc32b=(unsigned int *)( (unsigned int *)ddsdSrc.lpSurface + ((i<<1)+j)*lSrcPitch );
			
							for (k=0; k<dwSourceWidth; k++)
							{
								lpPixel->r=(unsigned char)(( (*lpSrc32b) & dwRedMask   ) >> RedShift);
								lpPixel->g=(unsigned char)(( (*lpSrc32b) & dwGreenMask ) >> GreenShift);
								lpPixel->b=(unsigned char)(( (*lpSrc32b) & dwBlueMask  ) >> BlueShift);
								lpSrc32b++;
								lpPixel++;
							}
						}
						break;

		case 33 :		for (j=0; j<2; j++)
						{
							/* Get 32 bits pointer to read the four source surface line */
							lpSrc32b=(unsigned int *)( (unsigned int *)ddsdSrc.lpSurface + ((i<<1)+j)*lSrcPitch );
			
							for (k=0; k<dwSourceWidth; k++)
							{
								lpPixel->r=(unsigned char)(( (*lpSrc32b) & dwRedMask   ) >> RedShift);
								lpPixel->g=(unsigned char)(( (*lpSrc32b) & dwGreenMask ) >> GreenShift);
								lpPixel->b=(unsigned char)(( (*lpSrc32b) & dwBlueMask  ) >> BlueShift);
								lpPixel->a=(unsigned char)(( (*lpSrc32b) & dwAlphaMask ) >> AlphaShift);
								lpSrc32b++;
								lpPixel++;
							}
						}
						break;
		}

		/* Translucent mipmapping is a special case : treat it separaretly */
		if (a)
		{
			/* Translucent mipmapping */
				
			/* Get pointer that points to the four current source surface lines */
			lpPixel=(PixelMap *)(lpTmpMap);

			for (j=0; j<dwDestWidth; j++)
			{
				/* Read the four pixels of source surface that will define
				   one pixel of destination surface */
				Pixel1=*(lpPixel);
				Pixel2=*(lpPixel+1);
				Pixel3=*(lpPixel+dwSourceWidth+1);
				Pixel4=*(lpPixel+dwSourceWidth);

				/* Compute Alpha, Red, Green, Blue channel of these four pixels */
				a1=Pixel1.a;
				a2=Pixel2.a;
				a3=Pixel3.a;
				a4=Pixel4.a;

				/* Total alpha value */
				Alpha = a1 + a2 + a3 + a4;
				
				/* That's to avoid a division by zero exception in the middle of 
 				   a Lock()/Unlock() pair ! */
				if (!Alpha)
				{
					r = (Pixel1.r + Pixel2.r + Pixel3.r + Pixel4.r)>>2;
					g = (Pixel1.g + Pixel2.g + Pixel3.g + Pixel4.g)>>2;
					b = (Pixel1.b + Pixel2.b + Pixel3.b + Pixel4.b)>>2;
				}
				else
				{
					fInvA=1.0f/Alpha;
					r = (int)( (Pixel1.r*a1 + Pixel2.r*a2 + Pixel3.r*a3 + Pixel4.r*a4) * fInvA );
					g = (int)( (Pixel1.g*a1 + Pixel2.g*a2 + Pixel3.g*a3 + Pixel4.g*a4) * fInvA );
					b = (int)( (Pixel1.b*a1 + Pixel2.b*a2 + Pixel3.b*a3 + Pixel4.b*a4) * fInvA );
					Alpha>>=2;
				}
				
				/* Write resulting pixel in destination line */
				pOutputColor[j] = (r<<RedShift) | (g<<GreenShift) | (b<<BlueShift) | (Alpha<<AlphaShift);
	
				/* Go to next pack of pixels in source surface */
				lpPixel+=2;
			}
		}
		else
		{
			/* Opaque mipmapping */

			/* Get pointer that points to the four current source surface lines */
			lpPixel=(PixelMap *)(lpTmpMap);

			for (j=0; j<dwDestWidth; j++)
			{
				/* Read the four pixels of source surface that will define
				   one pixel of destination surface */
				Pixel1=*(lpPixel);
				Pixel2=*(lpPixel+1);
				Pixel3=*(lpPixel+dwSourceWidth+1);
				Pixel4=*(lpPixel+dwSourceWidth);

				/* Get average color channels of four pixels */
				r = (Pixel1.r + Pixel2.r + Pixel3.r + Pixel4.r)>>2;
				g = (Pixel1.g + Pixel2.g + Pixel3.g + Pixel4.g)>>2;
				b = (Pixel1.b + Pixel2.b + Pixel3.b + Pixel4.b)>>2;
				
				/* Write resulting pixel in destination line */
				pOutputColor[j] = (r<<RedShift) | (g<<GreenShift) | (b<<BlueShift);
	
				/* Go to next pack of pixels in source surface */
				lpPixel+=2;
			}
		}
		
		/* Copy current line to destination surface */
		switch(dwSurfaceDepth)
		{
		case 8 :	
		case 9 :	lp8b = (unsigned char *)( (unsigned char *)ddsdDest.lpSurface + i*lDestPitch);
					for (k=0; k<dwDestWidth; k++)
					{
						*lp8b++=pOutputColor[k];
					}
					break;
		case 16 :
		case 17:	lp16b = (unsigned short *)( (unsigned short *)ddsdDest.lpSurface + i*lDestPitch);
					for (k=0; k<dwDestWidth; k++)
					{
						*lp16b++=pOutputColor[k];
					}
					break;
		case 32 :
		case 33 :	lp32b = (unsigned int *)( (unsigned int *)ddsdDest.lpSurface + i*lDestPitch);
					for (k=0; k<dwDestWidth; k++)
					{
						*lp32b++=pOutputColor[k];
					}
					break;
		}
	}

	/* Unlock destination surface now that the copy is done */
	hres=lpDDSDestinationSurface->lpVtbl->Unlock(lpDDSDestinationSurface, NULL);
	if (hres!=DD_OK) 
	{
		WCE_DEBUG(L"CreateNextMipmapLevel2x2 : Failed to unlock destination texture surface\n");
		free(pOutputColor);
		free(lpTmpMap);
		return FALSE;
	}

	/* Unlock source surface now that the copy is done */
	hres=lpDDSSourceSurface->lpVtbl->Unlock(lpDDSSourceSurface, NULL);
	if (hres!=DD_OK) 
	{
		WCE_DEBUG(L"CreateNextMipmapLevel2x2 : Failed to unlock source texture surface\n");
		free(pOutputColor);
		free(lpTmpMap);
		return FALSE;
	}

	/* Free memory */
	free(pOutputColor);
	free(lpTmpMap);

	/* No problem occured */
	return TRUE;
}


/* Turn off optimization for that function because VC5.0 causes problems */
#pragma optimize( "", off )

/*****************************************************************************
 * Function Name  : CreateNextMipmapLevel4x4
 * Inputs		  : lpDDSTextureSurface
 * Returns		  : TRUE or FALSE
 * Description    : Create next mipmap level from lpDDSTextureSurface.
 *					The next mipmap is computed using a 4x4 algorith.
 *					
 *					The filter used looks like :
 *
 *						     COLUMN
 *						  W   X   Y   Z
 *						-----------------
 *					A	| 1 | 2 | 2 | 1 |
 *						-----------------
 *					B	| 2 | 4 | 4 | 2 |
 *		ROW				-----------------
 *					C	| 2 | 4 | 4 | 2 |
 *						-----------------
 *					D	| 1 | 2 | 2 | 1 |
 *						-----------------
 *
 *		Basically 16 pixels are used in a weighted sum to produce a single
 *		pixel. The pixels with the "4" weights are the ones originally
 *		used to produce the half-size polygons.
 *
 *
 *		When doing the next 1/2 size pixel to the right, Columns Y and Z must
 *		be re-used as columns W & X. The weightings are chosen so that the X &
 *		Y weightings are 2x the W & Z ones. This allows us to sum up Y and Z
 *		columns using the weightings (1,2,2,1) and then optionally multiply by
 *		2 to generate the (2,4,4,2) columns.
 *
 *		IE in summary, each column only needs to be computed once as we generate
 *		a row of pixels of the 1/2 size map. 
 *
 *****************************************************************************/
BOOL CreateNextMipmapLevel4x4(LPDIRECTDRAWSURFACE4 lpDDSTextureSurface)
{
	HRESULT					hres;
	DDSURFACEDESC2			ddsdSrc, ddsdDest;
	DDSCAPS2				ddsCaps;
	LPDIRECTDRAWSURFACE4	lpDDSSourceSurface, lpDDSDestinationSurface;
	int						dwSourceWidth, dwSourceHeight;
	int						dwDestWidth, dwDestHeight;
	DWORD					dwSurfaceDepth;
	int						lSrcPitch, lDestPitch;
	int						i, j, k;
	BYTE					r, g, b, a;
	int						a1, a2, a3, a4;
	unsigned char			*lp8b, *lpSrc8b;
	unsigned short			*lp16b, *lpSrc16b;
	DWORD					*lp32b, *lpSrc32b;
	DWORD					dwRedMask, dwGreenMask, dwBlueMask, dwAlphaMask;
	char					RedShift, GreenShift, BlueShift, AlphaShift;
	PixelMap				*lpTmpMap;
	PixelMap				*lpPixel;
	int						Red, Green, Blue, Alpha;
	float					fInvA;
	float					fInv25=1.0f/25.0f;
	float					fInv30=1.0f/30.0f;
	float					fInv36=1.0f/36.0f;
	int						RedColumn[4], GreenColumn[4], BlueColumn[4], AlphaColumn[4];
	int						*pOutputColor;
	int						nLinesToCopy, nCopyStart;
	TCHAR					pszString[200];
	
	/* Get source surface pointer */
	lpDDSSourceSurface=lpDDSTextureSurface;

	/* Initialise DDSURFACEDESC2 structure */
	WCE_ZERO_MEMORY(&ddsdSrc, sizeof(DDSURFACEDESC2));
	ddsdSrc.dwSize=sizeof(DDSURFACEDESC2);

	/* Get surface description */
	hres=lpDDSSourceSurface->lpVtbl->GetSurfaceDesc(lpDDSSourceSurface, &ddsdSrc);
	if (hres!=DD_OK)
	{
		WCE_DEBUG(L"CreateNextMipmapLevel4x4 : GetSurfaceDesc failed.\n");
		return FALSE;
	}

	/* Get surface info */
	dwSourceWidth=ddsdSrc.dwWidth;
	dwSourceHeight=ddsdSrc.dwHeight;
	lSrcPitch=ddsdSrc.lPitch;
	dwSurfaceDepth=ddsdSrc.ddpfPixelFormat.dwRGBBitCount;
	
	/* Check if surface depth is 8, 16 or 32 bits */
	if (dwSurfaceDepth!=8 && dwSurfaceDepth!=16 && dwSurfaceDepth!=32)
	{
		wsprintf(pszString, TEXT("CreateNextMipmapLevel4x4 : Surface Depth of %d not supported.\n"), dwSurfaceDepth);
		WCE_DEBUG(pszString);
		return FALSE;
	}
	
	/* Get number of bits per color channel in surface */
	GetPixelFormatInfo(&ddsdSrc.ddpfPixelFormat, &r, &g, &b, &a,
												 &RedShift, &GreenShift, &BlueShift, &AlphaShift,
												 NULL, NULL, NULL, NULL);

	/* Get masks */
	dwRedMask=ddsdSrc.ddpfPixelFormat.dwRBitMask; 
	dwGreenMask=ddsdSrc.ddpfPixelFormat.dwGBitMask; 
	dwBlueMask=ddsdSrc.ddpfPixelFormat.dwBBitMask; 
	dwAlphaMask=ddsdSrc.ddpfPixelFormat.dwRGBAlphaBitMask; 


	/* Get memory for pointer that will receive 4 lines of source surface */
	lpTmpMap=(PixelMap *)malloc(4*dwSourceWidth*sizeof(PixelMap));
	if (!lpTmpMap)
	{
		WCE_DEBUG(L"CreateNextMipmapLevel4x4 : Not enough memory to allocate lpTmpMap\n");
		return FALSE;
	}

	/* Get memory for pointer that will receive the output line */
	pOutputColor=(int *)malloc((dwSourceWidth/2)*sizeof(int));
	if (!pOutputColor)
	{
		WCE_DEBUG(L"CreateNextMipmapLevel4x4 : Not enough memory to allocate pOutputColor\n");
		free(lpTmpMap);
		return FALSE;
	}


	/* Get destination mipmap */
	WCE_ZERO_MEMORY(&ddsCaps, sizeof(DDSCAPS2));
	ddsCaps.dwCaps=DDSCAPS_TEXTURE | DDSCAPS_MIPMAP;
	hres=lpDDSSourceSurface->lpVtbl->GetAttachedSurface(lpDDSSourceSurface, &ddsCaps, &lpDDSDestinationSurface);
	if (hres!=DD_OK)
	{
		WCE_DEBUG(L"CreateNextMipmapLevel4x4 : Failed to get attached surface\n");
		free(pOutputColor);
		free(lpTmpMap);
		return FALSE;
	}

	/* If translucent, then add 1 to surface depth as an ID */
	if (a)
	{
		dwSurfaceDepth+=1;
	}
	
	/* Reinitialise source DDSURFACEDESC2 structure */
	WCE_ZERO_MEMORY(&ddsdSrc, sizeof(DDSURFACEDESC2));
	ddsdSrc.dwSize=sizeof(DDSURFACEDESC2);

	/* Lock texture surface to read it */
	hres=lpDDSSourceSurface->lpVtbl->Lock(lpDDSSourceSurface, NULL, &ddsdSrc, DDLOCK_READONLY, NULL); 
    if (hres!=DD_OK) 
	{
		WCE_DEBUG(L"CreateNextMipmapLevel4x4 : Failed to lock texture surface\n");
		free(pOutputColor);
		free(lpTmpMap);
		return FALSE;
	}

	/* Reinitialise destination DDSURFACEDESC2 structure */
	WCE_ZERO_MEMORY(&ddsdDest, sizeof(DDSURFACEDESC2));
	ddsdDest.dwSize=sizeof(DDSURFACEDESC2);

	/* Lock destination surface to fill it */
    hres=lpDDSDestinationSurface->lpVtbl->Lock(lpDDSDestinationSurface, NULL, &ddsdDest, 0, NULL); 
    if (hres!=DD_OK) 
	{
		WCE_DEBUG(L"CreateNextMipmapLevel4x4 : Failed to lock texture surface\n");
		free(pOutputColor);
		free(lpTmpMap);
		return FALSE;
	}

	/* Get surface info */
	dwDestWidth=ddsdDest.dwWidth;
	dwDestHeight=ddsdDest.dwHeight;
	lDestPitch=ddsdDest.lPitch;

	/* Pitch must be in pointer size unit, not in bytes */
	switch(dwSurfaceDepth)
	{
	case 8 :	
	case 9 :	break;
	case 16 :
	case 17 :	lSrcPitch>>=1;
				lDestPitch>>=1;
				break;
	case 32 :
	case 33 :	lSrcPitch>>=2;
				lDestPitch>>=2;
				break;
	}


	/* Special case for a 2-pixel size mipmap : do 2 by 2 mipmapping */
	if (dwSourceWidth==2)
	{
		/* Get pointer that points to each source surface line */
		lpPixel=(PixelMap *)(lpTmpMap);

		/* Copy 2x2 surface to PixelMap */
		switch(dwSurfaceDepth)
		{
		case 8 :
		case 9 :		for (j=0; j<2; j++)
						{
							/* Get 8 bits pointer to read the four source surface line */
							lpSrc8b=(unsigned char *)( (unsigned char *)ddsdSrc.lpSurface + j*lSrcPitch);
			
							for (k=0; k<2; k++)
							{
								lpPixel->r=(unsigned char)(( (*lpSrc8b) & dwRedMask   ) >> RedShift);
								lpPixel->g=(unsigned char)(( (*lpSrc8b) & dwGreenMask ) >> GreenShift);
								lpPixel->b=(unsigned char)(( (*lpSrc8b) & dwBlueMask  ) >> BlueShift);
								lpPixel->a=(unsigned char)(( (*lpSrc8b) & dwAlphaMask ) >> AlphaShift);
								lpSrc8b++;
								lpPixel++;
							}
						}
						break;
		case 16 :
		case 17 :		for (j=0; j<2; j++)
						{
							/* Get 16 bits pointer to read the four source surface line */
							lpSrc16b=(unsigned short *)( (unsigned short *)ddsdSrc.lpSurface + j*lSrcPitch);
			
							for (k=0; k<2; k++)
							{
								lpPixel->r=(unsigned char)(( (*lpSrc16b) & dwRedMask   ) >> RedShift);
								lpPixel->g=(unsigned char)(( (*lpSrc16b) & dwGreenMask ) >> GreenShift);
								lpPixel->b=(unsigned char)(( (*lpSrc16b) & dwBlueMask  ) >> BlueShift);
								lpPixel->a=(unsigned char)(( (*lpSrc16b) & dwAlphaMask ) >> AlphaShift);
								lpSrc16b++;
								lpPixel++;
							}
						}
						break;
		case 32 :
		case 33 :		for (j=0; j<2; j++)
						{
							/* Get 32 bits pointer to read the four source surface line */
							lpSrc32b=(unsigned int *)( (unsigned int *)ddsdSrc.lpSurface + j*lSrcPitch);
			
							for (k=0; k<2; k++)
							{
								lpPixel->r=(unsigned char)(( (*lpSrc32b) & dwRedMask   ) >> RedShift);
								lpPixel->g=(unsigned char)(( (*lpSrc32b) & dwGreenMask ) >> GreenShift);
								lpPixel->b=(unsigned char)(( (*lpSrc32b) & dwBlueMask  ) >> BlueShift);
								lpPixel->a=(unsigned char)(( (*lpSrc32b) & dwAlphaMask ) >> AlphaShift);
								lpSrc32b++;
								lpPixel++;
							}
						}
						break;
		}
		
		/* Translucent texture */
	    if (a)
		{
			/* Get pointer that points to each source surface line */
			lpPixel=(PixelMap *)(lpTmpMap);

			/* Get four pixels alpha channel */
			a1=lpPixel->a;
			a2=(lpPixel+1)->a;
			a3=(lpPixel+dwSourceWidth+1)->a;
			a4=(lpPixel+dwSourceWidth)->a;
			
			/* Total alpha */
			Alpha=a1+a2+a3+a4;

			/* That's to avoid a division by zero in the middle of a Lock()/Unlock() pair ! */
			if (Alpha)
			{
				fInvA=1.0f/Alpha;
				Red=a1*(lpPixel->r) + a2*((lpPixel+1)->r) + a3*((lpPixel+dwSourceWidth+1)->r) + a4*((lpPixel+dwSourceWidth)->r);
				Red=(int)(Red*fInvA);
				Green=a1*(lpPixel->g) + a2*((lpPixel+1)->g) + a3*((lpPixel+dwSourceWidth+1)->g) + a4*((lpPixel+dwSourceWidth)->g);
				Green=(int)(Green*fInvA);
				Blue=a1*(lpPixel->b) + a2*((lpPixel+1)->b) + a3*((lpPixel+dwSourceWidth+1)->b) + a4*((lpPixel+dwSourceWidth)->b);
				Blue=(int)(Blue*fInvA);
			}
			else
			{
				Red=lpPixel->r + (lpPixel+1)->r + (lpPixel+dwSourceWidth+1)->r + (lpPixel+dwSourceWidth)->r;
				Green=lpPixel->g + (lpPixel+1)->g + (lpPixel+dwSourceWidth+1)->g + (lpPixel+dwSourceWidth)->g;
				Blue=lpPixel->b + (lpPixel+1)->b + (lpPixel+dwSourceWidth+1)->b + (lpPixel+dwSourceWidth)->b;
			}
			Red>>=2;
			Green>>=2;
			Blue>>=2;
			Alpha>>=2;
		}
		else
		{
			/* Opaque texture */
			
			/* Get pointer that points to each source surface line */
			lpPixel=(PixelMap *)(lpTmpMap);

			/* Get 3 color channels R, G, B */
			Red=lpPixel->r + (lpPixel+1)->r + (lpPixel+dwSourceWidth+1)->r + (lpPixel+dwSourceWidth)->r;
			Red>>=2;
			Green=lpPixel->g + (lpPixel+1)->g + (lpPixel+dwSourceWidth+1)->g + (lpPixel+dwSourceWidth)->g;
			Green>>=2;
			Blue=lpPixel->b + (lpPixel+1)->b + (lpPixel+dwSourceWidth+1)->b + (lpPixel+dwSourceWidth)->b;
			Blue>>=2;
			Alpha=0;
		}

		/* Copy current line to destination surface */
		switch(dwSurfaceDepth)
		{
		case 8 :
		case 9 :	lp8b = (unsigned char *)( (unsigned char *)ddsdDest.lpSurface );
					*lp8b=(Red<<RedShift) | (Green<<GreenShift) | (Blue<<BlueShift) | (Alpha<<AlphaShift); 
					break;
		case 16 :	
		case 17 :	lp16b = (unsigned short *)( (unsigned short *)ddsdDest.lpSurface );
					*lp16b=(Red<<RedShift) | (Green<<GreenShift) | (Blue<<BlueShift) | (Alpha<<AlphaShift); 
					break;
		case 32 :
		case 33:	lp32b = (unsigned int *)( (unsigned int *)ddsdDest.lpSurface ); 
					*lp32b=(Red<<RedShift) | (Green<<GreenShift) | (Blue<<BlueShift) | (Alpha<<AlphaShift); 
					break;
		}
		
		/* Unlock surfaces and exit */
		goto Unlock;
	}

	
	/* Copy loop starts here */

	/* For each line of source surface */
	for (i=0; i<dwDestWidth; i++)
	{
		/* Copy start at this position */
		nCopyStart=(i<<1)-1;

		/* Normally four lines to copy */
		nLinesToCopy=4;

		/* Get pointer to destination line */
		lpPixel=(PixelMap *)(lpTmpMap);

		/* If top edge, then opy 3 lines only and change lpPixel address so it doesn't include
		   the first line */
		if (i==0)
		{
			nCopyStart=0;
			nLinesToCopy=3;
			lpPixel=(PixelMap *)(lpTmpMap+dwSourceWidth);
		}
		
		/* If bottom edge, then only copy 3 lines */
		if (i==dwDestWidth-1)
		{
			nLinesToCopy=3;
		}

		
		/* First copy the 4 current source lines that will create 1 output line */
		

		/* Copy source surface into intermediate map where 1 byte = 1 color channel */
		switch(dwSurfaceDepth)
		{
		case 8 :		for (j=0; j<nLinesToCopy; j++)
						{
							/* Get 8 bits pointer to read the four source surface line */
							lpSrc8b=(unsigned char *)( (unsigned char *)ddsdSrc.lpSurface + (j+nCopyStart)*lSrcPitch );
			
							for (k=0; k<dwSourceWidth; k++)
							{
								lpPixel->r=(unsigned char)(( (*lpSrc8b) & dwRedMask	  ) >> RedShift);
								lpPixel->g=(unsigned char)(( (*lpSrc8b) & dwGreenMask ) >> GreenShift);
								lpPixel->b=(unsigned char)(( (*lpSrc8b) & dwBlueMask  ) >> BlueShift);
								lpSrc8b++;
								lpPixel++;
							}
						}
						break;

		case 9 :		for (j=0; j<nLinesToCopy; j++)
						{
							/* Get 8 bits pointer to read the four source surface line */
							lpSrc8b=(unsigned char *)( (unsigned char *)ddsdSrc.lpSurface + (j+nCopyStart)*lSrcPitch );
			
							for (k=0; k<dwSourceWidth; k++)
							{
								lpPixel->r=(unsigned char)(( (*lpSrc8b) & dwRedMask	  ) >> RedShift);
								lpPixel->g=(unsigned char)(( (*lpSrc8b) & dwGreenMask ) >> GreenShift);
								lpPixel->b=(unsigned char)(( (*lpSrc8b) & dwBlueMask  ) >> BlueShift);
								lpPixel->a=(unsigned char)(( (*lpSrc8b) & dwAlphaMask ) >> AlphaShift);
								lpSrc8b++;
								lpPixel++;
							}
						}
						break;

		case 16 :		for (j=0; j<nLinesToCopy; j++)
						{
							/* Get 16 bits pointer to read the four source surface line */
							lpSrc16b=(unsigned short *)( (unsigned short *)ddsdSrc.lpSurface + (j+nCopyStart)*lSrcPitch );
			
							for (k=0; k<dwSourceWidth; k++)
							{
								lpPixel->r=(unsigned char)(( (*lpSrc16b) & dwRedMask   ) >> RedShift);
								lpPixel->g=(unsigned char)(( (*lpSrc16b) & dwGreenMask ) >> GreenShift);
								lpPixel->b=(unsigned char)(( (*lpSrc16b) & dwBlueMask  ) >> BlueShift);
								lpSrc16b++;
								lpPixel++;
							}
						}
						break;

		case 17 :		for (j=0; j<nLinesToCopy; j++)
						{
							/* Get 16 bits pointer to read the four source surface line */
							lpSrc16b=(unsigned short *)( (unsigned short *)ddsdSrc.lpSurface + (j+nCopyStart)*lSrcPitch );
			
							for (k=0; k<dwSourceWidth; k++)
							{
								lpPixel->r=(unsigned char)(( (*lpSrc16b) & dwRedMask   ) >> RedShift);
								lpPixel->g=(unsigned char)(( (*lpSrc16b) & dwGreenMask ) >> GreenShift);
								lpPixel->b=(unsigned char)(( (*lpSrc16b) & dwBlueMask  ) >> BlueShift);
								lpPixel->a=(unsigned char)(( (*lpSrc16b) & dwAlphaMask ) >> AlphaShift);;
								lpSrc16b++;
								lpPixel++;
							}
						}
						break;

		case 32 :		for (j=0; j<nLinesToCopy; j++)
						{
							/* Get 32 bits pointer to read the four source surface line */
							lpSrc32b=(unsigned int *)( (unsigned int *)ddsdSrc.lpSurface + (j+nCopyStart)*lSrcPitch );
			
							for (k=0; k<dwSourceWidth; k++)
							{
								lpPixel->r=(unsigned char)(( (*lpSrc32b) & dwRedMask   ) >> RedShift);
								lpPixel->g=(unsigned char)(( (*lpSrc32b) & dwGreenMask ) >> GreenShift);
								lpPixel->b=(unsigned char)(( (*lpSrc32b) & dwBlueMask  ) >> BlueShift);
								lpSrc32b++;
								lpPixel++;
							}
						}
						break;

		case 33 :		for (j=0; j<nLinesToCopy; j++)
						{
							/* Get 32 bits pointer to read the four source surface line */
							lpSrc32b=(unsigned int *)( (unsigned int *)ddsdSrc.lpSurface + (j+nCopyStart)*lSrcPitch );
			
							for (k=0; k<dwSourceWidth; k++)
							{
								lpPixel->r=(unsigned char)(( (*lpSrc32b) & dwRedMask   ) >> RedShift);
								lpPixel->g=(unsigned char)(( (*lpSrc32b) & dwGreenMask ) >> GreenShift);
								lpPixel->b=(unsigned char)(( (*lpSrc32b) & dwBlueMask  ) >> BlueShift);
								lpPixel->a=(unsigned char)(( (*lpSrc32b) & dwAlphaMask ) >> AlphaShift);
								lpSrc32b++;
								lpPixel++;
							}
						}
						break;
		}
	

		/* Translucent mipmapping is a special case : treat it separaretly */
		if (a)
		{
			/* Translucent mipmapping */
				
			/* Do first line */
			if (i==0)
			{
				/* Get pointer that points to the four current source surface lines */
				lpPixel=(PixelMap *)(lpTmpMap+dwSourceWidth);
	
				/* Do first pixel in line (no column 0) */
				GetColumnAlphaWithoutTop(lpPixel,   &RedColumn[1], &GreenColumn[1], &BlueColumn[1], &AlphaColumn[1], dwSourceWidth);
				GetColumnAlphaWithoutTop(lpPixel+1, &RedColumn[2], &GreenColumn[2], &BlueColumn[2], &AlphaColumn[2], dwSourceWidth);
				GetColumnAlphaWithoutTop(lpPixel+2, &RedColumn[3], &GreenColumn[3], &BlueColumn[3], &AlphaColumn[3], dwSourceWidth);
	
				/* Compute average color channels (total weight is 25 in that case) */
				Red=(int)(((RedColumn[1]<<1)+(RedColumn[2]<<1)+RedColumn[3])*fInv25);
				Green=(int)(((GreenColumn[1]<<1)+(GreenColumn[2]<<1)+GreenColumn[3])*fInv25);
				Blue=(int)(((BlueColumn[1]<<1)+(BlueColumn[2]<<1)+BlueColumn[3])*fInv25);
				Alpha=(int)(((AlphaColumn[1]<<1)+(AlphaColumn[2]<<1)+AlphaColumn[3])*fInv25);

				/* Write new pixel in Output line */
				pOutputColor[0] = (Red<<RedShift) | (Green<<GreenShift) | (Blue<<BlueShift) | (Alpha<<AlphaShift);
				lpPixel+=2;
				
				/* Do each pixel of first line */
				for (j=1; j<(int)dwDestWidth-1; j++)
				{
					/* Get four columns */
					RedColumn[0]=RedColumn[2]; GreenColumn[0]=GreenColumn[2]; BlueColumn[0]=BlueColumn[2]; AlphaColumn[0]=AlphaColumn[2]; 
					RedColumn[1]=RedColumn[3]; GreenColumn[1]=GreenColumn[3]; BlueColumn[1]=BlueColumn[3]; AlphaColumn[1]=AlphaColumn[3];
					GetColumnAlphaWithoutTop(lpPixel+1, &RedColumn[2], &GreenColumn[2], &BlueColumn[2], &AlphaColumn[2], dwSourceWidth);
					GetColumnAlphaWithoutTop(lpPixel+2, &RedColumn[3], &GreenColumn[3], &BlueColumn[3], &AlphaColumn[3], dwSourceWidth);
	
					/* Compute average color channels (total weight is 30 in that case) */
					Red=(int)((RedColumn[0]+(RedColumn[1]<<1)+(RedColumn[2]<<1)+RedColumn[3])*fInv30);
					Green=(int)((GreenColumn[0]+(GreenColumn[1]<<1)+(GreenColumn[2]<<1)+GreenColumn[3])*fInv30);
					Blue=(int)((BlueColumn[0]+(BlueColumn[1]<<1)+(BlueColumn[2]<<1)+BlueColumn[3])*fInv30);
					Alpha=(int)((AlphaColumn[0]+(AlphaColumn[1]<<1)+(AlphaColumn[2]<<1)+AlphaColumn[3])*fInv30);

					/* Write new pixel in Output line */
					pOutputColor[j]=(Red<<RedShift) | (Green<<GreenShift) | (Blue<<BlueShift) | (Alpha<<AlphaShift);
					lpPixel+=2;
				}
				
				/* Do last pixel in line (no column 3) */
				RedColumn[0]=RedColumn[2]; GreenColumn[0]=GreenColumn[2]; BlueColumn[0]=BlueColumn[2]; AlphaColumn[0]=AlphaColumn[2]; 
				RedColumn[1]=RedColumn[3]; GreenColumn[1]=GreenColumn[3]; BlueColumn[1]=BlueColumn[3]; AlphaColumn[1]=AlphaColumn[3];
				GetColumnAlphaWithoutTop(lpPixel+1, &RedColumn[2], &GreenColumn[2], &BlueColumn[2], &AlphaColumn[2], dwSourceWidth);
		
				/* Compute average color channels (total weight is 25 in that case) */
				Red=(int)((RedColumn[0]+(RedColumn[1]<<1)+(RedColumn[2]<<1))*fInv25);
				Green=(int)((GreenColumn[0]+(GreenColumn[1]<<1)+(GreenColumn[2]<<1))*fInv25);
				Blue=(int)((BlueColumn[0]+(BlueColumn[1]<<1)+(BlueColumn[2]<<1))*fInv25);
				Alpha=(int)((AlphaColumn[0]+(AlphaColumn[1]<<1)+(AlphaColumn[2]<<1))*fInv25);
	
				/* Write new pixel in Output line */
				pOutputColor[dwDestWidth-1]=(Red<<RedShift) | (Green<<GreenShift) | (Blue<<BlueShift) | (Alpha<<AlphaShift);
			}
			else
			/* Do last line */
			if (i==dwDestWidth-1)
			{
				/* Get 16 bits pointer tha points to each source surface line */
				lpPixel=(PixelMap *)(lpTmpMap+dwSourceWidth);
	
				/* Do first pixel in line (no column 0) */
				GetColumnAlphaWithoutBottom(lpPixel,   &RedColumn[1], &GreenColumn[1], &BlueColumn[1], &AlphaColumn[1], dwSourceWidth);
				GetColumnAlphaWithoutBottom(lpPixel+1, &RedColumn[2], &GreenColumn[2], &BlueColumn[2], &AlphaColumn[2], dwSourceWidth);
				GetColumnAlphaWithoutBottom(lpPixel+2, &RedColumn[3], &GreenColumn[3], &BlueColumn[3], &AlphaColumn[3], dwSourceWidth);
		
				/* Compute average color channels (total weight is 25 in that case) */
				Red=(int)(((RedColumn[1]<<1)+(RedColumn[2]<<1)+RedColumn[3])*fInv25);
				Green=(int)(((GreenColumn[1]<<1)+(GreenColumn[2]<<1)+GreenColumn[3])*fInv25);
				Blue=(int)(((BlueColumn[1]<<1)+(BlueColumn[2]<<1)+BlueColumn[3])*fInv25);
				Alpha=(int)(((AlphaColumn[1]<<1)+(AlphaColumn[2]<<1)+AlphaColumn[3])*fInv25);
	
				/* Write new pixel in Output line */
				pOutputColor[0]=(Red<<RedShift) | (Green<<GreenShift) | (Blue<<BlueShift) | (Alpha<<AlphaShift);
				lpPixel+=2;
					
				/* Do each pixel of last line */
				for (j=1; j<(int)dwDestWidth-1;j++)
				{
					/* Get four columns */
					RedColumn[0]=RedColumn[2]; GreenColumn[0]=GreenColumn[2]; BlueColumn[0]=BlueColumn[2]; AlphaColumn[0]=AlphaColumn[2]; 
					RedColumn[1]=RedColumn[3]; GreenColumn[1]=GreenColumn[3]; BlueColumn[1]=BlueColumn[3]; AlphaColumn[1]=AlphaColumn[3];
					GetColumnAlphaWithoutBottom(lpPixel+1, &RedColumn[2], &GreenColumn[2], &BlueColumn[2], &AlphaColumn[2], dwSourceWidth);
					GetColumnAlphaWithoutBottom(lpPixel+2, &RedColumn[3], &GreenColumn[3], &BlueColumn[3], &AlphaColumn[3], dwSourceWidth);
	
					/* Compute average color channels (total weight is 30 in that case) */
					Red=(int)((RedColumn[0]+(RedColumn[1]<<1)+(RedColumn[2]<<1)+RedColumn[3])*fInv30);
					Green=(int)((GreenColumn[0]+(GreenColumn[1]<<1)+(GreenColumn[2]<<1)+GreenColumn[3])*fInv30);
					Blue=(int)((BlueColumn[0]+(BlueColumn[1]<<1)+(BlueColumn[2]<<1)+BlueColumn[3])*fInv30);
					Alpha=(int)((AlphaColumn[0]+(AlphaColumn[1]<<1)+(AlphaColumn[2]<<1)+AlphaColumn[3])*fInv30);
		
					/* Write new pixel */
					pOutputColor[j]=(Red<<RedShift) | (Green<<GreenShift) | (Blue<<BlueShift) | (Alpha<<AlphaShift);
					lpPixel+=2;
				}
	
				/* Do last pixel in line (no column 3) */
				RedColumn[0]=RedColumn[2]; GreenColumn[0]=GreenColumn[2]; BlueColumn[0]=BlueColumn[2]; AlphaColumn[0]=AlphaColumn[2]; 
				RedColumn[1]=RedColumn[3]; GreenColumn[1]=GreenColumn[3]; BlueColumn[1]=BlueColumn[3]; AlphaColumn[1]=AlphaColumn[3];
				GetColumnAlphaWithoutBottom(lpPixel+1, &RedColumn[2], &GreenColumn[2], &BlueColumn[2], &AlphaColumn[2], dwSourceWidth);
	
				/* Compute average color channels (total weight is 25) */
				Red=(int)((RedColumn[0]+(RedColumn[1]<<1)+(RedColumn[2]<<1))*fInv25);
				Green=(int)((GreenColumn[0]+(GreenColumn[1]<<1)+(GreenColumn[2]<<1))*fInv25);
				Blue=(int)((BlueColumn[0]+(BlueColumn[1]<<1)+(BlueColumn[2]<<1))*fInv25);
				Alpha=(int)((AlphaColumn[0]+(AlphaColumn[1]<<1)+(AlphaColumn[2]<<1))*fInv25);
	
				/* Write new pixel */
				pOutputColor[dwDestWidth-1]=(Red<<RedShift) | (Green<<GreenShift) | (Blue<<BlueShift) | (Alpha<<AlphaShift);
			}
			else
			{
				/* Do middle lines */
	
				/* Get 16 bits pointer to read each source surface line */
				lpPixel=(PixelMap *)(lpTmpMap + dwSourceWidth);
				
				/* Do first pixel in line (no column 0) */
				GetColumnAlpha(lpPixel,   &RedColumn[1], &GreenColumn[1], &BlueColumn[1], &AlphaColumn[1], dwSourceWidth);
				GetColumnAlpha(lpPixel+1, &RedColumn[2], &GreenColumn[2], &BlueColumn[2], &AlphaColumn[2], dwSourceWidth);
				GetColumnAlpha(lpPixel+2, &RedColumn[3], &GreenColumn[3], &BlueColumn[3], &AlphaColumn[3], dwSourceWidth);
		
				/* Compute average color channels (total weight is 30 in that case) */
				Red=(int)(((RedColumn[1]<<1)+(RedColumn[2]<<1)+RedColumn[3])*fInv30);
				Green=(int)(((GreenColumn[1]<<1)+(GreenColumn[2]<<1)+GreenColumn[3])*fInv30);
				Blue=(int)(((BlueColumn[1]<<1)+(BlueColumn[2]<<1)+BlueColumn[3])*fInv30);
				Alpha=(int)(((AlphaColumn[1]<<1)+(AlphaColumn[2]<<1)+AlphaColumn[3])*fInv30);
	
				/* Write new pixel in Output line */
				pOutputColor[0]=(Red<<RedShift) | (Green<<GreenShift) | (Blue<<BlueShift) | (Alpha<<AlphaShift);
				lpPixel+=2;
											
				/* Do each pixel of each line */
				for (j=1; j<(int)dwDestWidth-1;j++)
				{
					/* Get four columns */
					RedColumn[0]=RedColumn[2]; GreenColumn[0]=GreenColumn[2]; BlueColumn[0]=BlueColumn[2]; AlphaColumn[0]=AlphaColumn[2]; 
					RedColumn[1]=RedColumn[3]; GreenColumn[1]=GreenColumn[3]; BlueColumn[1]=BlueColumn[3]; AlphaColumn[1]=AlphaColumn[3];
					GetColumnAlpha(lpPixel+1, &RedColumn[2], &GreenColumn[2], &BlueColumn[2], &AlphaColumn[2], dwSourceWidth);
					GetColumnAlpha(lpPixel+2, &RedColumn[3], &GreenColumn[3], &BlueColumn[3], &AlphaColumn[3], dwSourceWidth);
	
					/* Compute average color channels (total weight is 36) */
					Red=(int)((RedColumn[0]+(RedColumn[1]<<1)+(RedColumn[2]<<1)+RedColumn[3])*fInv36);
					Green=(int)((GreenColumn[0]+(GreenColumn[1]<<1)+(GreenColumn[2]<<1)+GreenColumn[3])*fInv36);
					Blue=(int)((BlueColumn[0]+(BlueColumn[1]<<1)+(BlueColumn[2]<<1)+BlueColumn[3])*fInv36);
					Alpha=(int)((AlphaColumn[0]+(AlphaColumn[1]<<1)+(AlphaColumn[2]<<1)+AlphaColumn[3])*fInv36);

					/* Write new pixel in Output line */
					pOutputColor[j]=(Red<<RedShift) | (Green<<GreenShift) | (Blue<<BlueShift) | (Alpha<<AlphaShift);
					lpPixel+=2;
				}
				
				/* Do last pixel in line (no column 3) */
				RedColumn[0]=RedColumn[2]; GreenColumn[0]=GreenColumn[2]; BlueColumn[0]=BlueColumn[2]; AlphaColumn[0]=AlphaColumn[2]; 
				RedColumn[1]=RedColumn[3]; GreenColumn[1]=GreenColumn[3]; BlueColumn[1]=BlueColumn[3]; AlphaColumn[1]=AlphaColumn[3];
				GetColumnAlpha(lpPixel+1, &RedColumn[2], &GreenColumn[2], &BlueColumn[2], &AlphaColumn[2], dwSourceWidth);
		
				/* Compute average color channels (total weight is 30) */
				Red=(int)((RedColumn[0]+(RedColumn[1]<<1)+(RedColumn[2]<<1))*fInv30);
				Green=(int)((GreenColumn[0]+(GreenColumn[1]<<1)+(GreenColumn[2]<<1))*fInv30);
				Blue=(int)((BlueColumn[0]+(BlueColumn[1]<<1)+(BlueColumn[2]<<1))*fInv30);
				Alpha=(int)((AlphaColumn[0]+(AlphaColumn[1]<<1)+(AlphaColumn[2]<<1))*fInv30);
		
				/* Write new pixel */
				pOutputColor[dwDestWidth-1]=(Red<<RedShift) | (Green<<GreenShift) | (Blue<<BlueShift) | (Alpha<<AlphaShift);
			}
		}
		else
		{
			/* Opaque mipmapping */
		
			/* Do first line */
			if (i==0)
			{
				/* Get pointer that points to each source surface line */
				lpPixel=(PixelMap *)(lpTmpMap+dwSourceWidth);
	
				/* Do first pixel in line (no column 0) */
				GetColumnWithoutTop(lpPixel,   &RedColumn[1], &GreenColumn[1], &BlueColumn[1], dwSourceWidth);
				GetColumnWithoutTop(lpPixel+1, &RedColumn[2], &GreenColumn[2], &BlueColumn[2], dwSourceWidth);
				GetColumnWithoutTop(lpPixel+2, &RedColumn[3], &GreenColumn[3], &BlueColumn[3], dwSourceWidth);
		
				/* Compute average color channels (total weight is 25 in that case) */
				Red=(int)(((RedColumn[1]<<1)+(RedColumn[2]<<1)+RedColumn[3])*fInv25);
				Green=(int)(((GreenColumn[1]<<1)+2*GreenColumn[2]+GreenColumn[3])*fInv25);
				Blue=(int)(((BlueColumn[1]<<1)+(BlueColumn[2]<<1)+BlueColumn[3])*fInv25);
	
				/* Write new pixel in Output line */
				pOutputColor[0] = (Red<<RedShift) | (Green<<GreenShift) | (Blue<<BlueShift);
				lpPixel+=2;
					
				/* Do each pixel of first line */
				for (j=1; j<(int)dwDestWidth-1; j++)
				{
					/* Get four columns */
					RedColumn[0]=RedColumn[2]; GreenColumn[0]=GreenColumn[2]; BlueColumn[0]=BlueColumn[2];
					RedColumn[1]=RedColumn[3]; GreenColumn[1]=GreenColumn[3]; BlueColumn[1]=BlueColumn[3];
					GetColumnWithoutTop(lpPixel+1, &RedColumn[2], &GreenColumn[2], &BlueColumn[2], dwSourceWidth);
					GetColumnWithoutTop(lpPixel+2, &RedColumn[3], &GreenColumn[3], &BlueColumn[3], dwSourceWidth);
	
					/* Compute average color channels (total weight is 30 in that case) */
					Red=(int)((RedColumn[0]+2*RedColumn[1]+2*RedColumn[2]+RedColumn[3])*fInv30);
					Green=(int)((GreenColumn[0]+2*GreenColumn[1]+2*GreenColumn[2]+GreenColumn[3])*fInv30);
					Blue=(int)((BlueColumn[0]+2*BlueColumn[1]+2*BlueColumn[2]+BlueColumn[3])*fInv30);
	
					/* Write new pixel in Output line */
					pOutputColor[j]=(Red<<RedShift) | (Green<<GreenShift) | (Blue<<BlueShift);
					lpPixel+=2;
				}
					
				/* Do last pixel in line (no column 3) */
				RedColumn[0]=RedColumn[2]; GreenColumn[0]=GreenColumn[2]; BlueColumn[0]=BlueColumn[2];
				RedColumn[1]=RedColumn[3]; GreenColumn[1]=GreenColumn[3]; BlueColumn[1]=BlueColumn[3];
				GetColumnWithoutTop(lpPixel+1, &RedColumn[2], &GreenColumn[2], &BlueColumn[2], dwSourceWidth);
		
				/* Compute average color channels (total weight is 25 in that case) */
				Red=(int)((RedColumn[0]+(RedColumn[1]<<1)+(RedColumn[2]<<1))*fInv25);
				Green=(int)((GreenColumn[0]+(GreenColumn[1]<<1)+(GreenColumn[2]<<1))*fInv25);
				Blue=(int)((BlueColumn[0]+(BlueColumn[1]<<1)+(BlueColumn[2]<<1))*fInv25);
	
				/* Write new pixel in Output line */
				pOutputColor[dwDestWidth-1]=(Red<<RedShift) | (Green<<GreenShift) | (Blue<<BlueShift);
			}
			else
			if (i==dwDestWidth-1)
			{
				/* Do last line */
		
				/* Get 16 bits pointer tha points to each source surface line */
				lpPixel=(PixelMap *)(lpTmpMap+dwSourceWidth);
	
				/* Do first pixel in line (no column 0) */
				GetColumnWithoutBottom(lpPixel,   &RedColumn[1], &GreenColumn[1], &BlueColumn[1], dwSourceWidth);
				GetColumnWithoutBottom(lpPixel+1, &RedColumn[2], &GreenColumn[2], &BlueColumn[2], dwSourceWidth);
				GetColumnWithoutBottom(lpPixel+2, &RedColumn[3], &GreenColumn[3], &BlueColumn[3], dwSourceWidth);
	
				/* Compute average color channels (total weight is 25 in that case) */
				Red=(int)(((RedColumn[1]<<1)+(RedColumn[2]<<1)+RedColumn[3])*fInv25);
				Green=(int)(((GreenColumn[1]<<1)+(GreenColumn[2]<<1)+GreenColumn[3])*fInv25);
				Blue=(int)(((BlueColumn[1]<<1)+(BlueColumn[2]<<1)+BlueColumn[3])*fInv25);
	
				/* Write new pixel in Output line */
				pOutputColor[0]=(Red<<RedShift) | (Green<<GreenShift) | (Blue<<BlueShift);
				lpPixel+=2;
					
				/* Do each pixel of last line */
				for (j=1; j<(int)dwDestWidth-1;j++)
				{
					/* Get four columns */
					RedColumn[0]=RedColumn[2]; GreenColumn[0]=GreenColumn[2]; BlueColumn[0]=BlueColumn[2];
					RedColumn[1]=RedColumn[3]; GreenColumn[1]=GreenColumn[3]; BlueColumn[1]=BlueColumn[3];
					GetColumnWithoutBottom(lpPixel+1, &RedColumn[2], &GreenColumn[2], &BlueColumn[2], dwSourceWidth);
					GetColumnWithoutBottom(lpPixel+2, &RedColumn[3], &GreenColumn[3], &BlueColumn[3], dwSourceWidth);
		
					/* Compute average color channels (total weight is 30 in that case) */
					Red=(int)((RedColumn[0]+(RedColumn[1]<<1)+(RedColumn[2]<<1)+RedColumn[3])*fInv30);
					Green=(int)((GreenColumn[0]+(GreenColumn[1]<<1)+(GreenColumn[2]<<1)+GreenColumn[3])*fInv30);
					Blue=(int)((BlueColumn[0]+(BlueColumn[1]<<1)+(BlueColumn[2]<<1)+BlueColumn[3])*fInv30);
		
					/* Write new pixel */
					pOutputColor[j]=(Red<<RedShift) | (Green<<GreenShift) | (Blue<<BlueShift);
					lpPixel+=2;
				}
	
				/* Do last pixel in line (no column 3) */
				RedColumn[0]=RedColumn[2]; GreenColumn[0]=GreenColumn[2]; BlueColumn[0]=BlueColumn[2];
				RedColumn[1]=RedColumn[3]; GreenColumn[1]=GreenColumn[3]; BlueColumn[1]=BlueColumn[3];
				GetColumnWithoutBottom(lpPixel+1, &RedColumn[2], &GreenColumn[2], &BlueColumn[2], dwSourceWidth);
	
				/* Compute average color channels (total weight is 25) */
				Red=(int)((RedColumn[0]+(RedColumn[1]<<1)+(RedColumn[2]<<1))*fInv25);
				Green=(int)((GreenColumn[0]+(GreenColumn[1]<<1)+(GreenColumn[2]<<1))*fInv25);
				Blue=(int)((BlueColumn[0]+(BlueColumn[1]<<1)+(BlueColumn[2]<<1))*fInv25);
	
				/* Write new pixel */
				pOutputColor[dwDestWidth-1]=(Red<<RedShift) | (Green<<GreenShift) | (Blue<<BlueShift);
			}
			else
			{
				/* Do middle lines */
					
				/* Get 16 bits pointer to read each source surface line */
				lpPixel=(PixelMap *)(lpTmpMap + dwSourceWidth);
			
				/* Do first pixel in line (no column 0) */
				GetColumn(lpPixel,   &RedColumn[1], &GreenColumn[1], &BlueColumn[1], dwSourceWidth);
				GetColumn(lpPixel+1, &RedColumn[2], &GreenColumn[2], &BlueColumn[2], dwSourceWidth);
				GetColumn(lpPixel+2, &RedColumn[3], &GreenColumn[3], &BlueColumn[3], dwSourceWidth);
	
				/* Compute average color channels (total weight is 30 in that case) */
				Red=(int)(((RedColumn[1]<<1)+(RedColumn[2]<<1)+RedColumn[3])*fInv30);
				Green=(int)(((GreenColumn[1]<<1)+(GreenColumn[2]<<1)+GreenColumn[3])*fInv30);
				Blue=(int)(((BlueColumn[1]<<1)+(BlueColumn[2]<<1)+BlueColumn[3])*fInv30);
	
				/* Write new pixel in Output line */
				pOutputColor[0]=(Red<<RedShift) | (Green<<GreenShift) | (Blue<<BlueShift);
				lpPixel+=2;
											
				/* Do each pixel of each line */
				for (j=1; j<(int)dwDestWidth-1;j++)
				{
					/* Get four columns */
					RedColumn[0]=RedColumn[2]; GreenColumn[0]=GreenColumn[2]; BlueColumn[0]=BlueColumn[2];
					RedColumn[1]=RedColumn[3]; GreenColumn[1]=GreenColumn[3]; BlueColumn[1]=BlueColumn[3];
					GetColumn(lpPixel+1, &RedColumn[2], &GreenColumn[2], &BlueColumn[2], dwSourceWidth);
					GetColumn(lpPixel+2, &RedColumn[3], &GreenColumn[3], &BlueColumn[3], dwSourceWidth);
	
					/* Compute average color channels (total weight is 36) */
					Red=(int)((RedColumn[0]+(RedColumn[1]<<1)+(RedColumn[2]<<1)+RedColumn[3])*fInv36);
					Green=(int)((GreenColumn[0]+(GreenColumn[1]<<1)+(GreenColumn[2]<<1)+GreenColumn[3])*fInv36);
					Blue=(int)((BlueColumn[0]+(BlueColumn[1]<<1)+(BlueColumn[2]<<1)+BlueColumn[3])*fInv36);
	
					/* Write new pixel in Output line */
					pOutputColor[j]=(Red<<RedShift) | (Green<<GreenShift) | (Blue<<BlueShift);
					lpPixel+=2;
				}
				
				/* Do last pixel in line (no column 3) */
				RedColumn[0]=RedColumn[2]; GreenColumn[0]=GreenColumn[2]; BlueColumn[0]=BlueColumn[2];
				RedColumn[1]=RedColumn[3]; GreenColumn[1]=GreenColumn[3]; BlueColumn[1]=BlueColumn[3];
				GetColumn(lpPixel+1, &RedColumn[2], &GreenColumn[2], &BlueColumn[2], dwSourceWidth);
	
				/* Compute average color channels (total weight is 30) */
				Red=(int)((RedColumn[0]+(RedColumn[1]<<1)+(RedColumn[2]<<1))*fInv30);
				Green=(int)((GreenColumn[0]+(GreenColumn[1]<<1)+(GreenColumn[2]<<1))*fInv30);
				Blue=(int)((BlueColumn[0]+(BlueColumn[1]<<1)+(BlueColumn[2]<<1))*fInv30);
	
				/* Write new pixel */
				pOutputColor[dwDestWidth-1]=(Red<<RedShift) | (Green<<GreenShift) | (Blue<<BlueShift);
			}
		}
		
		/* Copy current line to destination surface */
		switch(dwSurfaceDepth)
		{
		case 8 :
		case 9 :	lp8b = (unsigned char *)( (unsigned char *)ddsdDest.lpSurface + i*lDestPitch );
					for (k=0; k<dwDestWidth; k++)
					{
						*lp8b++=pOutputColor[k];
					}
					break;
		case 16 :	
		case 17:	lp16b = (unsigned short *)( (unsigned short *)ddsdDest.lpSurface + i*lDestPitch );
					for (k=0; k<dwDestWidth; k++)
					{
						*lp16b++=pOutputColor[k];
					}
					break;
		case 32 :	
		case 33 :	lp32b = (unsigned int *)( (unsigned int *)ddsdDest.lpSurface + i*lDestPitch );
					for (k=0; k<dwDestWidth; k++)
					{
						*lp32b++=pOutputColor[k];
					}
					break;
		}
	}
		
Unlock:
	
	/* Unlock destination surface now that the copy is done */
	hres=lpDDSDestinationSurface->lpVtbl->Unlock(lpDDSDestinationSurface, NULL);
	if (hres!=DD_OK) 
	{
		WCE_DEBUG(L"CreateNextMipmapLevel4x4 : Failed to unlock texture surface\n");
		free(pOutputColor);
		free(lpTmpMap);
		return FALSE;
	}

	/* Unlock source surface now that the copy is done */
	hres=lpDDSSourceSurface->lpVtbl->Unlock(lpDDSSourceSurface, NULL);
	if (hres!=DD_OK) 
	{
		WCE_DEBUG(L"CreateNextMipmapLevel4x4 : Failed to unlock texture surface\n");
		free(pOutputColor);
		free(lpTmpMap);
		return FALSE;
	}
	
	/* Free memory */
	free(pOutputColor);
	free(lpTmpMap);

	/* No problem occured */
	return TRUE;
}

/* Turn optimizations back on */
#pragma optimize( "", on )


/*******************************************************************************
 * Function Name  : ComputeTransparentPixels
 * Input		  : *pBm
 * Input/Output	  : *pBmTrans
 * Returns		  : Nothing
 * Global Used    : None
 * Description    : Compute RGB values of completely transparent pixels in the
 *					image.
 *					Although transparent pixels (Alpha=0) are of course not 
 *					displayed in a non-filtered normal texture, using a mipmapped
 *					texture or applying a bilinear filter to it will cause the
 *					RGB colors of transparent pixels to be displayed ("Color 
 *					bleeding"). Since these	values are very often not filled 
 *					(i.e with an alpha of 0, one might think that they will never 
 *					be exposed), it is necessary to compute them using the RGB 
 *					values of adjacent pixels.
 *					NOTE : If bilinear filtering is not to be used, and the texture
 *					is not mipmapped, then obviously this function doesn't need to
 *					be called.
 *******************************************************************************/
void ComputeTransparentPixels(BITMAP *pBm, BITMAP *pBmTrans)
{
	DWORD	RTotal=0, GTotal=0, BTotal=0;
	BYTE	*pByte, *pByteTrans;
	BYTE	R, G, B;
	BOOL	*pPixelProcessed, bAtLeastOne=FALSE;
	int		i, j, x, y, nDivider=0;

	/* Check that bitmaps share the same dimensions */
	if (pBm->bmWidth!=pBmTrans->bmWidth || pBm->bmHeight!=pBmTrans->bmHeight)
	{
		WCE_DEBUG(L"ComputeTransparentPixels : Bitmap do not share same dimensions\n");
		return;
	}

	/* Get x and y */
	x=pBm->bmWidth;
	y=pBm->bmHeight;

	/* Allocate array of processed pixels */
	pPixelProcessed=(BOOL *)malloc(x*y*sizeof(BOOL));

	/* Initialise array */
	for (i=y; i!=0; i--)
	{
		pByteTrans=((BYTE *)pBmTrans->bmBits+(i-1)*pBmTrans->bmWidthBytes+x*3-1);
		
		for (j=0; j<x; j++)
		{
			/* If alpha is non-zero, pixel is processed */
			if (*pByteTrans)
			{
				pPixelProcessed[(i-1)*x + j]=TRUE;
				bAtLeastOne=TRUE;
			}
			pByteTrans-=3;
		}
	}

	/* Check that translucent image is valid */
	if (!bAtLeastOne)
	{
		WCE_DEBUG(L"ComputeTransparentPixels : Image is completely transparent! Aborting...\n");
		return;
	}

	/* Set variable */
	bAtLeastOne=TRUE;

	/* Do multiple passes so that every pixel in the image is processed */
	while (bAtLeastOne)
	{
		/* Assume that no pixel is transparent in the beginning of the loop */
		bAtLeastOne=FALSE;

		/* Loop through y values from bottom to top */
		for (i=y; i!=0; i--)
		{
			/* Set pointers */
			pByte=((BYTE *)pBm->bmBits+(i-1)*pBm->bmWidthBytes+x*3-1);
				
			/* Look through x values from right to left */
			for (j=0; j<x; j++)
			{ 
				/* Is pixel already processed or not ? */
				if (!pPixelProcessed[(i-1)*x + j])
				{
					/* RGB color needs to be set correctly to avoid "color bleeding" */
					nDivider=0;
					RTotal=0; GTotal=0; BTotal=0;

					/* Get right pixels RGB */
					if (j>0)
					{
						/* Middle right */
						if (pPixelProcessed[(i-1)*x + j - 1])
						{
							RTotal+=*(pByte + 3);
							GTotal+=*(pByte + 2);
							BTotal+=*(pByte + 1);
							nDivider++;
						}

						if (i>1)
						{
							/* Top right */
							if (pPixelProcessed[(i-1-1)*x + j - 1])
							{
								RTotal+=*(pByte - pBm->bmWidthBytes + 3);
								GTotal+=*(pByte - pBm->bmWidthBytes + 2);
								BTotal+=*(pByte - pBm->bmWidthBytes + 1);
								nDivider++;
							}
						}

						if (i<y)
						{
							/* Bottom right */
							if (pPixelProcessed[(i-1+1)*x + j - 1])
							{
								RTotal+=*(pByte + pBm->bmWidthBytes + 3);
								GTotal+=*(pByte + pBm->bmWidthBytes + 2);
								BTotal+=*(pByte + pBm->bmWidthBytes + 1);
								nDivider++;
							}
						}
					}

					/* Get left pixels RGB */
					if (j<(x-1))
					{
						/* Middle left */
						if (pPixelProcessed[(i-1)*x + j + 1])
						{
							RTotal+=*(pByte - 3);
							GTotal+=*(pByte - 4);
							BTotal+=*(pByte - 5);
							nDivider++;
						}

						if (i>1)
						{
							/* Top left */
							if (pPixelProcessed[(i-1-1)*x + j + 1])
							{
								RTotal+=*(pByte - pBm->bmWidthBytes - 3);
								GTotal+=*(pByte - pBm->bmWidthBytes - 4);
								BTotal+=*(pByte - pBm->bmWidthBytes - 5);
								nDivider++;
							}
						}

						if (i<y)
						{
							/* Bottom left */
							if (pPixelProcessed[(i-1+1)*x + j + 1])
							{
								RTotal+=*(pByte + pBm->bmWidthBytes - 3);
								GTotal+=*(pByte + pBm->bmWidthBytes - 4);
								BTotal+=*(pByte + pBm->bmWidthBytes - 5);
								nDivider++;
							}
						}
					}

					/* Get bottom pixel RGB */
					if (i<y)
					{
						if (pPixelProcessed[(i-1+1)*x + j])
						{
							RTotal+=*(pByte + pBm->bmWidthBytes);
							GTotal+=*(pByte + pBm->bmWidthBytes - 1);
							BTotal+=*(pByte + pBm->bmWidthBytes - 2);
							nDivider++;
						}
					}

					/* Get top pixel RGB */
					if (i>1)
					{
						if (pPixelProcessed[(i-1-1)*x + j])
						{
							RTotal+=*(pByte - pBm->bmWidthBytes);
							GTotal+=*(pByte - pBm->bmWidthBytes - 1);
							BTotal+=*(pByte - pBm->bmWidthBytes - 2);
							nDivider++;
						}
					}

					/* We now have the neighbour pixels, so average the red, green
					   and blue value for transparent pixel */
					if (nDivider)		/* To avoid division by zero */
					{
						float fOneOverDivider=1.0f/nDivider;

						/* Average color channels of neighbouring texels */
						R=(BYTE)(RTotal*fOneOverDivider);
						G=(BYTE)(GTotal*fOneOverDivider);
						B=(BYTE)(BTotal*fOneOverDivider);

						/* Write resulting color */
						*pByte=R;
						*(pByte-1)=G;
						*(pByte-2)=B;

						/* Pixel has been processed */
						pPixelProcessed[(i-1)*x + j]=TRUE;
					}

					/* This pixel was completely transparent */
					bAtLeastOne=TRUE;
				}

				/* Decrement pointers */
				pByte-=3;
			}
		}
	}
}



/*******************************************************************************
 * Function Name  : MirrorExpandBitmap
 * Input		  : *pBm, *pBmTrans
 * Output		  : **Red, **Green, **Blue, **Alpha
 * Returns		  : TRUE or FALSE
 * Global Used    : None
 * Description    : Expand a bitmap into a wrap-around format. Each channel data
 *					is stored in the corresponding array (**Red, **Green, **Blue,
 *					**Alpha).
 *					if hTranslucentBitmap exists then the ALPHA channel is expanded
 *					as well.
 *					Texture must be square and a power of 2.
 *******************************************************************************/
void MirrorExpandBitmap(float **Red, float **Green, float **Blue, float **Alpha, 
						BITMAP *pBm, BITMAP *pBmTrans)
{
	DWORD	dwSize, dwTextureSize, dwHalfTextureSize;
	DWORD	i, j;
	DWORD	y;
	BYTE	*lpByte, *lpByteTrans, R, G, B, A;

	/* Get dimensions */
	dwTextureSize=pBm->bmWidth;
	dwSize=2*dwTextureSize;
	dwHalfTextureSize=dwTextureSize/2;


	/**************************
	** Read data from bitmap **
	**************************/
	if (pBmTrans)
	{
		/* Translucent case */

		/* Loop through y values from bottom to top */
		for (i=1; i<=dwTextureSize; i++)
		{
			lpByte=((unsigned char *)pBm->bmBits+(i-1)*pBm->bmWidthBytes+dwTextureSize*3-1);
			lpByteTrans=((unsigned char *)pBmTrans->bmBits+(i-1)*pBm->bmWidthBytes+dwTextureSize*3-1);
			
			/* Look through x values from right to left */
			for (j=1; j<=(int)dwTextureSize; j++)
			{ 
				/* Get R, G, B values (always 8-bit each, as the bitmap is 24-bit) */
				R = *lpByte--;
				G = *lpByte--;
				B = *lpByte--;
				A = *lpByteTrans;
				lpByteTrans-=3;

				// Central data
				Red[(i + dwHalfTextureSize)][dwHalfTextureSize + j]=R;
				Green[(i + dwHalfTextureSize)][dwHalfTextureSize + j]=G;
				Blue[(i + dwHalfTextureSize)][dwHalfTextureSize + j]=B;
				Alpha[(i + dwHalfTextureSize)][dwHalfTextureSize + j]=A;
				

				// Separate texture in two halves in x
				if (j<=dwHalfTextureSize)
				{
					// Left central data
					Red[(i + dwHalfTextureSize)][dwHalfTextureSize - j + 1]=R;
					Green[(i + dwHalfTextureSize)][dwHalfTextureSize - j + 1]=G;
					Blue[(i + dwHalfTextureSize)][dwHalfTextureSize - j + 1]=B;
					Alpha[(i + dwHalfTextureSize)][dwHalfTextureSize - j + 1]=A;
				}
				else
				{
					// Right central data
					Red[(i + dwHalfTextureSize)][dwSize + dwHalfTextureSize - j + 1]=R;
					Green[(i + dwHalfTextureSize)][dwSize + dwHalfTextureSize - j + 1]=G;
					Blue[(i + dwHalfTextureSize)][dwSize + dwHalfTextureSize - j + 1]=B;
					Alpha[(i + dwHalfTextureSize)][dwSize + dwHalfTextureSize - j + 1]=A;
				}
				
				// Separate texture in two halves in y
				if (i<=dwHalfTextureSize)
				{
					// Compute y offset
					y=(dwHalfTextureSize - i + 1);
					
					// Top central data
					Red[y][dwHalfTextureSize + j]=R;
					Green[y][dwHalfTextureSize + j]=G;
					Blue[y][dwHalfTextureSize + j]=B;
					Alpha[y][dwHalfTextureSize + j]=A;

					if (j<=dwHalfTextureSize)
					{
						// Corner
						Red[y][dwHalfTextureSize - j + 1]=R;
						Green[y][dwHalfTextureSize - j + 1]=G;
						Blue[y][dwHalfTextureSize - j + 1]=B;
						Alpha[y][dwHalfTextureSize - j + 1]=A;
					}
					else
					{
						// Corner
						Red[y][dwSize + dwHalfTextureSize - j + 1]=R;
						Green[y][dwSize + dwHalfTextureSize - j + 1]=G;
						Blue[y][dwSize + dwHalfTextureSize - j + 1]=B;
						Alpha[y][dwSize + dwHalfTextureSize - j + 1]=A;
					}
				}
				else
				{
					// Compute y offset
					y=(dwSize + dwHalfTextureSize - i + 1);
					
					// Bottom central data
					Red[y][dwHalfTextureSize + j]=R;
					Green[y][dwHalfTextureSize + j]=G;
					Blue[y][dwHalfTextureSize + j]=B;
					Alpha[y][dwHalfTextureSize + j]=A;
					
					if (j<=dwHalfTextureSize)
					{
						// Corner
						Red[y][dwHalfTextureSize - j + 1]=R;
						Green[y][dwHalfTextureSize - j + 1]=G;
						Blue[y][dwHalfTextureSize - j + 1]=B;
						Alpha[y][dwHalfTextureSize - j + 1]=A;
					}
					else
					{
						// Corner
						Red[y][dwSize + dwHalfTextureSize - j + 1]=R;
						Green[y][dwSize + dwHalfTextureSize - j + 1]=G;
						Blue[y][dwSize + dwHalfTextureSize - j + 1]=B;
						Alpha[y][dwSize + dwHalfTextureSize - j + 1]=B;
					}
				}
			}
		}
	}
	else
	{
		/* Opaque case */

		/* Loop through y values from bottom to top */
		for (i=1; i<=dwTextureSize; i++)
		{
			lpByte=((unsigned char *)pBm->bmBits+(i-1)*pBm->bmWidthBytes+dwTextureSize*3-1);
			
			/* Look through x values from right to left */
			for (j=1; j<=(int)dwTextureSize; j++)
			{ 
				/* Get R, G, B values (always 8-bit each, as the bitmap is 24-bit) */
				R = *lpByte--;
				G = *lpByte--;
				B = *lpByte--;

				// Central data
				Red[(i + dwHalfTextureSize)][dwHalfTextureSize + j]=R;
				Green[(i + dwHalfTextureSize)][dwHalfTextureSize + j]=G;
				Blue[(i + dwHalfTextureSize)][dwHalfTextureSize + j]=B;
				

				// Separate texture in two halves in x
				if (j<=dwHalfTextureSize)
				{
					// Left central data
					Red[(i + dwHalfTextureSize)][dwHalfTextureSize - j + 1]=R;
					Green[(i + dwHalfTextureSize)][dwHalfTextureSize - j + 1]=G;
					Blue[(i + dwHalfTextureSize)][dwHalfTextureSize - j + 1]=B;
				}
				else
				{
					// Right central data
					Red[(i + dwHalfTextureSize)][dwSize + dwHalfTextureSize - j + 1]=R;
					Green[(i + dwHalfTextureSize)][dwSize + dwHalfTextureSize - j + 1]=G;
					Blue[(i + dwHalfTextureSize)][dwSize + dwHalfTextureSize - j + 1]=B;
				}
				
				// Separate texture in two halves in y
				if (i<=dwHalfTextureSize)
				{
					// Compute y offset
					y=(dwHalfTextureSize - i + 1);
					
					// Top central data
					Red[y][dwHalfTextureSize + j]=R;
					Green[y][dwHalfTextureSize + j]=G;
					Blue[y][dwHalfTextureSize + j]=B;

					if (j<=dwHalfTextureSize)
					{
						// Corner
						Red[y][dwHalfTextureSize - j + 1]=R;
						Green[y][dwHalfTextureSize - j + 1]=G;
						Blue[y][dwHalfTextureSize - j + 1]=B;
					}
					else
					{
						// Corner
						Red[y][dwSize + dwHalfTextureSize - j + 1]=R;
						Green[y][dwSize + dwHalfTextureSize - j + 1]=G;
						Blue[y][dwSize + dwHalfTextureSize - j + 1]=B;
					}
				}
				else
				{
					// Compute y offset
					y=(dwSize + dwHalfTextureSize - i + 1);
					
					// Bottom central data
					Red[y][dwHalfTextureSize + j]=R;
					Green[y][dwHalfTextureSize + j]=G;
					Blue[y][dwHalfTextureSize + j]=B;
					
					if (j<=dwHalfTextureSize)
					{
						// Corner
						Red[y][dwHalfTextureSize - j + 1]=R;
						Green[y][dwHalfTextureSize - j + 1]=G;
						Blue[y][dwHalfTextureSize - j + 1]=B;
					}
					else
					{
						// Corner
						Red[y][dwSize + dwHalfTextureSize - j + 1]=R;
						Green[y][dwSize + dwHalfTextureSize - j + 1]=G;
						Blue[y][dwSize + dwHalfTextureSize - j + 1]=B;
					}
				}
			}
		}
	}
}


/*******************************************************************************
 * Function Name  : ApplyLowPassFilter
 * Input		  : dwSize, fCutOff, nOrder
 * Input/Output   : **dataRed, **dataGreen, **dataBlue, 
 *					*speqRed, *speqGreen, *speqBlue
 * Returns		  : Nothing
 * Global Used    : None
 * Description    : Apply a low-pass filter to a frequency spectrum.
 *					- dwSize is the length of each dimension of the passed data.
 *					- fCutOff is the cut-off frequency after which frequencies
 *					will be attenuated. Must be positive and between 0.0 and 0.5.
 *					- nOrder is the order of the filter. The higher nOrder 
 *					is, the	sharper the slope of the filter will be. Too much 
 *					attenuation	of higher frequencies can cause "ringing" artefacts 
 *					on some	images. nOrder should be an even number between 2 and 20.
 *					Filter used is of the form : 
 *							
 *						F =	1.0 - ( (f1*f1+f2*f2)**(nOrder/2) ) / (fCutOff**nOrder)
 *
 *******************************************************************************/
void ApplyLowPassFilter(float **data, float *speq, DWORD dwSize, float fCutOff, int nOrder)
{
	DWORD	i, j;
	DWORD	dwOffsetRE, dwOffsetIM;
	float	f, f1, f2;
	float	fFilter;
	float	fOneOverDenominator;
	int		nHalfOrder;

		
	/* Check if parameters are valid */
	if (fCutOff<=0.0f || !data || !speq)
	{
		WCE_DEBUG(L"ApplyLowPassFilter : Wrong parameters\n");
		return;
	}

	/* If order is smaller than 2, then do not perform any filtering and return */
	if (nOrder<2)
	{
		return;
	}

	/* Prevent user to use a too large value for nPower */
	if (nOrder>20)
	{
		nOrder=20;
	}

	/* Compute nHalfOrder (used with (f1*f1+f2*f2) since this term is already a power of 2) */
	nHalfOrder=nOrder/2;

	/* Compute fDenominator */
	fOneOverDenominator=1.0f/(float)pow(fCutOff, nOrder);

	/* For each row of spectrum */
	for (i=1; i<=dwSize; i++)
	{
		/* Compute frequency at this row */
		if (i<=((dwSize/2)+1))
		{
			f1=(i-1)/(float)dwSize;
		}
		else
		{
			f1=(dwSize-i+1)/(float)dwSize;
		}

		/* For each column of each row */
		for (j=1; j<=(dwSize/2); j++)
		{
			/* Compute real and imaginary offsets */
			dwOffsetRE=(j<<1)-1;
			dwOffsetIM=j<<1;
			
			/* Compute frequency at this column */
			f2=(j-1)/(float)dwSize;

			/* Compute filter, function of both frequencies */
			f=f1*f1+f2*f2;
			fFilter=1.0f - fOneOverDenominator * (float)pow(f, nHalfOrder);
			if (fFilter<0.0f) fFilter=0.0f;
			
			/* Multiply real and imaginary parts with filter */
			data[i][dwOffsetRE]*=fFilter;	
			data[i][dwOffsetIM]*=fFilter;
		}

		/* j = (dwSize/2)+1 is in speq */
		speq[(i<<1)-1]*=fFilter;
		speq[i<<1]*=fFilter;
	}
}


/*******************************************************************************
 * Function Name  : AllocateSquareMatrix
 * Input		  : nSize
 * Global Used    : None
 * Returns		  : **float
 * Description    : Allocate a square matrix M[1..nSize][1..nSize]
 *******************************************************************************/
float **AllocateSquareMatrix(long nSize)
{
	long	i;
	float	**ppMatrix;

	ppMatrix=(float **)malloc(((nSize+1)*sizeof(float *)));
	ppMatrix[1]=(float *)malloc(((nSize*nSize+1)*sizeof(float)));
	
	for (i=2; i<=nSize; i++)
	{
		ppMatrix[i]=ppMatrix[i-1]+nSize;
	}

	return ppMatrix;
}

/*******************************************************************************
 * Function Name  : FreeSquareMatrix
 * Input		  : **m, nSize
 * Global Used    : None
 * Returns		  : Nothing
 * Description    : Frees a matrix allocated with AllocateSquareMatrix().
 *******************************************************************************/
void FreeSquareMatrix(float **ppMatrix, long nSize)
{
	free((char  *)ppMatrix[1]);
	free((char  *)ppMatrix);
}


/*******************************************************************************
 * Function Name  : AllocateVector
 * Input		  : nSize
 * Global Used    : None
 * Returns		  : *float
 * Description    : Allocate a vector V[1..nSize].
 *******************************************************************************/
float *AllocateVector(long nSize)
{
	float	*pVector;

	pVector=(float *)malloc((nSize+1)*sizeof(float));
	
	return pVector;
}

/*******************************************************************************
 * Function Name  : FreeVector
 * Input		  : *v, nSize
 * Global Used    : None
 * Returns		  : Nothing
 * Description    : Frees a vector allocated with AllocateVector().
 *******************************************************************************/
void FreeVector(float *pVector, long nSize)
{
	free((char  *)pVector);
}


/*******************************************************************************
 * Function Name  : DFT2D
 * Input		  : data[], nn2, nn3, isign
 * Global Used    : None
 * Description    : For isign==1, replaces data by its two-dimensional discrete 
 *					Fourier	transform.
 *					For isign==-1, data is replaced by its inverse transform 
 *					scaled by the product of the lengths of the two dimensions.
 *******************************************************************************/
void DFT2D(float data[], unsigned long nn2, unsigned long nn3, int isign)
{
#define SWAPVALUE(a, b)	tempr=(a); (a)=(b); (b)=tempr
	int idim;
	unsigned long	i1, i2, i3, i2rev, i3rev, ip1, ip2, ip3, ifp1, ifp2;
	unsigned long	ibit, k1, k2, n, nprev, nrem, ntot;
	float			tempi, tempr;
	float			theta, wi, wpi, wpr, wr, wtemp;
	unsigned long	nn[3];

	nn[1]=nn2;
	nn[2]=nn3;

	for (ntot=1, idim=1; idim<=2; idim++)
	{
		ntot*=nn[idim];
	}
	nprev=1;

	for(idim=2; idim>=1; idim--)
	{
		n=nn[idim];
		nrem=ntot/(n*nprev);
		ip1=nprev<<1;
		ip2=ip1*n;
		ip3=ip2*nrem;
		i2rev=1;
		for (i2=1; i2<=ip2; i2+=ip1)
		{
			if (i2<i2rev)
			{
				for (i1=i2; i1<=i2+ip1-2; i1+=2)
				{
					for (i3=i1; i3<=ip3; i3+=ip2)
					{
						i3rev=i2rev+i3-i2;
						SWAPVALUE(data[i3], data[i3rev]);
						SWAPVALUE(data[i3+1], data[i3rev+1]);
					}
				}
			}
			ibit=ip2>>1;
			while (ibit>=ip1 && i2rev>ibit)
			{
				i2rev-=ibit;
				ibit>>=1;
			}
			i2rev+=ibit;
		}

		ifp1=ip1;
		while (ifp1<ip2)
		{
			ifp2=ifp1<<1;
			theta=isign*6.283185307f/(ifp2/ip1);
			wtemp=sin(0.5f*theta);
			wpr=-2.0f*wtemp*wtemp;
			wpi=sin(theta);
			wr=1.0f;
			wi=0.0f;
			for (i3=1; i3<=ifp1; i3+=ip1)
			{
				for (i1=i3; i1<=i3+ip1-2; i1+=2)
				{
					for (i2=i1; i2<=ip3; i2+=ifp2)
					{
						k1=i2;
						k2=k1+ifp1;
						tempr=(float)wr*data[k2]-(float)wi*data[k2+1];
						tempi=(float)wr*data[k2+1]+(float)wi*data[k2];
						data[k2]=data[k1]-tempr;
						data[k2+1]=data[k1+1]-tempi;
						data[k1]+=tempr;
						data[k1+1]+=tempi;
					}
				}
				wr=(wtemp=wr)*wpr-wi*wpi+wr;
				wi=wi*wpr+wtemp*wpi+wi;
			}
			ifp1=ifp2;
		}
		nprev*=n;
	}
}


/*******************************************************************************
 * Function Name  : RealFFT2D
 * Input		  : *speq (for isign==-1), nn2, nn3, isign
 * Input/Output   : **data
 * Output		  : *speq (for isign==1)
 * Global Used    : None
 * Description    : For isign==1, this function performs the Fourier transform 
 *					of a real 2D array. The resulting spectrum is returned as 
 *					two COMPLEX arrays.
 *					If isign==-1, the INVERSE Fourier transform is performed
 *					on the two COMPLEX arrays and the resulting REAL data is
 *					returned in **data, scaled by nn2*nn3/2.
 *******************************************************************************/
void RealFFT2D(float **data, float *speq, unsigned long nn2, unsigned long nn3, int isign)
{
	unsigned long	i2, i3, j2, j3, nn[3], ii3;
	float			theta, wi, wpi, wpr, wr, wtemp;
	float			c1, c2, h1r, h1i, h2r, h2i;
	
	if (1+&data[nn2][nn3]-&data[1][1] != (float)nn2*nn3)
	{
		WCE_DEBUG(L"RealFFT2D : Data array size does not match parameters\n");
		return;
	}
	
	c1=0.5f;
	c2=-0.5f*isign;
	theta=isign*(6.283185307f/nn3);
	wtemp=sin(0.5f*theta);
	wpr=-2.0f*wtemp*wtemp;
	wpi=sin(theta);
	nn[1]=nn2;
	nn[2]=nn3>>1;

	if (isign==1)
	{
		DFT2D(&data[1][1]-1, nn[1], nn[2], isign);
		for (i2=1, j2=0; i2<=nn2; i2++)
		{
			speq[++j2]=data[i2][1];
			speq[++j2]=data[i2][2];
		}
	}

	wr=1.0f;
	wi=0.0f;

	for (ii3=1, i3=1; i3<=(nn3>>2)+1; i3++, ii3+=2)
	{
		for (i2=1; i2<=nn2; i2++)
		{
			if (i3==1)
			{
				j2=(i2!=1 ? ((nn2-i2)<<1)+3 : 1);
				h1r=c1*(data[i2][1]+speq[j2]);
				h1i=c1*(data[i2][2]-speq[j2+1]);
				h2i=c2*(data[i2][1]-speq[j2]);
				h2r=-c2*(data[i2][2]+speq[j2+1]);
				data[i2][1]=h1r+h2r;
				data[i2][2]=h1i+h2i;
				speq[j2]=h1r-h2r;
				speq[j2+1]=h2i-h1i;
			}
			else
			{
				j2=(i2!=1 ? nn2-i2+2 : 1);
				j3=nn3+3-(i3<<1);
				h1r=c1*(data[i2][ii3]+data[j2][j3]);
				h1i=c1*(data[i2][ii3+1]-data[j2][j3+1]);
				h2i=c2*(data[i2][ii3]-data[j2][j3]);
				h2r=-c2*(data[i2][ii3+1]+data[j2][j3+1]);
				data[i2][ii3]=h1r+wr*h2r-wi*h2i;
				data[i2][ii3+1]=h1i+wr*h2i+wi*h2r;
				data[j2][j3]=h1r-wr*h2r+wi*h2i;
				data[j2][j3+1]=-h1i+wr*h2i+wi*h2r;
			}
		}
		wr=(wtemp=wr)*wpr-wi*wpi+wr;
		wi=wi*wpr+wtemp*wpi+wi;
	}
	
	if (isign==-1)
	{
		DFT2D(&data[1][1]-1, nn[1], nn[2], isign);
	}
}


/*******************************************************************************
 * Function Name  : fround
 * Input		  : fValue
 * Returns		  : int
 * Global Used    : None
 * Description    : Returns the closest integer value to the float input.
 *******************************************************************************/
int fround(float fValue)
{
	/* Positive case */
	if (fValue>=0)
	{
		if ((fValue-(float)floor(fValue))>0.5f)
		{
			return ((int)fValue+1);
		}
		else
		{
			return ((int)(fValue));
		}	
	}
	else
	{
		/* Negative case */
		if ((fValue-(float)floor(fValue))>0.5f)
		{
			return ((int)fValue);
		}
		else
		{
			return ((int)(fValue-1));
		}
	}
}

/*****************************************************************************
 * Function Name  : EnumTextureFormatsCallback
 * Description    : Callback function which enumerates all available texture
 *				    formats for the current D3D driver.
 *					
 *****************************************************************************/
HRESULT WINAPI EnumTextureFormatsCallback(LPDDPIXELFORMAT lpddPixelFormat, LPVOID lpContext)
{
	DWORD	m;
	int		r=0, g=0, b=0, a=0, i;
	int		*lpStartFormat=(int *)lpContext;
	TCHAR	pszString[100];
  
    /* We don't want 1 or 2 bit palettised textures for now */
	if (lpddPixelFormat->dwFlags & (DDPF_PALETTEINDEXED1 | DDPF_PALETTEINDEXED2))
	{
        return DDENUMRET_OK;
	}

	/* We don't want 1, 2, or 4 bit color indexed to an 8-bit palette */
	if (lpddPixelFormat->dwFlags & DDPF_PALETTEINDEXEDTO8)
	{
        return DDENUMRET_OK;
	}

	/* We don't want compressed texture formats for now */
	if (lpddPixelFormat->dwFlags & DDPF_COMPRESSED)
	{
        return DDENUMRET_OK;
	}

	/* Luminance formats */
	if (lpddPixelFormat->dwFlags & DDPF_LUMINANCE)
	{
        D3DTTextureFormat[nTextureFormat].bLuminanceFormat=TRUE;
	}
	
	/* BumpMap formats */
	if (lpddPixelFormat->dwFlags & (DDPF_BUMPLUMINANCE | DDPF_BUMPDUDV))
	{
        D3DTTextureFormat[nTextureFormat].bBumpMapFormat=TRUE;
	}

	/* We don't want unknown FOURCC texture formats */
	if (lpddPixelFormat->dwFlags & DDPF_FOURCC)
	{
        switch(lpddPixelFormat->dwFourCC)
		{
			case MAKEFOURCC('Y', 'U', 'Y', '2') :
			case MAKEFOURCC('U', 'Y', 'V', 'Y') : D3DTTextureFormat[nTextureFormat].bYUVFormat=TRUE; break;
			case MAKEFOURCC('D', 'X', 'T', '1') :
			case MAKEFOURCC('D', 'X', 'T', '2') :
			case MAKEFOURCC('D', 'X', 'T', '3') :
			case MAKEFOURCC('D', 'X', 'T', '4') :
			case MAKEFOURCC('D', 'X', 'T', '5') : D3DTTextureFormat[nTextureFormat].bDXTFormat=TRUE; break;
			default :	/* Unknown FOURCC, don't enumerate this format */
						return DDENUMRET_OK;
		}
	}
		
	/* Copy current pixel format to texture format */
	memcpy(&D3DTTextureFormat[nTextureFormat].ddPixelFormat, lpddPixelFormat, sizeof(DDPIXELFORMAT));
    
    /* If not palettised, calculate the number of bits available for each channel R,G,B,A */
	if (lpddPixelFormat->dwFlags & DDPF_PALETTEINDEXED8)
	{
		D3DTTextureFormat[nTextureFormat].b8BitsPalettised=TRUE;
	}
	else if (lpddPixelFormat->dwFlags & DDPF_PALETTEINDEXED4)
	{
		D3DTTextureFormat[nTextureFormat].b4BitsPalettised=TRUE;
	}
	else
	{
		m=lpddPixelFormat->dwRBitMask; 
		for (i=0; i<32; i++)
		{
			if ((1<<i) & m)
			{
				r++;
			}
		}
		m=lpddPixelFormat->dwGBitMask; 
		for (i=0; i<32; i++) 
		{
			if ((1<<i) & m) 
			{
				g++;
			}
		}
		m=lpddPixelFormat->dwBBitMask; 
		for (i=0; i<32; i++) 
		{
			if ((1<<i) & m) 
			{
				b++;
			}
		}
		if (lpddPixelFormat->dwFlags & DDPF_ALPHAPIXELS) 
		{
	  		m = lpddPixelFormat->dwRGBAlphaBitMask; 
			for (i=0; i<32; i++) 
			{
				if (m & (1<<i)) 
				{
					a++;
				}
			}
		}

		/* Now fill texture format structure with each channel bits */
		D3DTTextureFormat[nTextureFormat].r=r;
		D3DTTextureFormat[nTextureFormat].g=g;
		D3DTTextureFormat[nTextureFormat].b=b;
		D3DTTextureFormat[nTextureFormat].a=a;
	}

	/* Indicate this format is valid */
	D3DTTextureFormat[nTextureFormat].bValidFormat=TRUE;

    /* Increase total number of texture format */
	if (nTextureFormat>=29)
	{
		OutputDebugString(L"Maximum number of texture formats reached (30)\n");
	}
	else
	{
		nTextureFormat++;
	}
	
	/* Debug output */
	if (lpddPixelFormat->dwFlags & DDPF_PALETTEINDEXED8)
	{
		wsprintf (pszString, L"Enumerated texture Format : 8-bit Palettised\n");
	}
	else if (lpddPixelFormat->dwFlags & (DDPF_BUMPLUMINANCE | DDPF_BUMPDUDV))
	{
		wsprintf (pszString, L"Enumerated texture Format : BumpMap\n");
	}
	else if (lpddPixelFormat->dwFlags & DDPF_LUMINANCE)
	{
		wsprintf (pszString, L"Enumerated texture Format : Luminance\n");
	}
	else if (lpddPixelFormat->dwFlags & DDPF_FOURCC)
	{
		switch (lpddPixelFormat->dwFourCC)
		{
		case MAKEFOURCC('U', 'Y', 'V', 'Y') : wsprintf (pszString, L"Enumerated texture Format : FOURCC UYVY YUV format\n"); break;
		case MAKEFOURCC('Y', 'U', 'Y', '2') : wsprintf (pszString, L"Enumerated texture Format : FOURCC YUY2 YUV format\n"); break;
		case MAKEFOURCC('D', 'X', 'T', '1') : wsprintf (pszString, L"Enumerated texture Format : FOURCC DXT1 compressed format\n"); break;
		case MAKEFOURCC('D', 'X', 'T', '2') : wsprintf (pszString, L"Enumerated texture Format : FOURCC DXT2 compressed format\n"); break;
		case MAKEFOURCC('D', 'X', 'T', '3') : wsprintf (pszString, L"Enumerated texture Format : FOURCC DXT3 compressed format\n"); break;
		case MAKEFOURCC('D', 'X', 'T', '4') : wsprintf (pszString, L"Enumerated texture Format : FOURCC DXT4 compressed format\n"); break;
		case MAKEFOURCC('D', 'X', 'T', '5') : wsprintf (pszString, L"Enumerated texture Format : FOURCC DXT5 compressed format\n"); break;
		}
	}
	else
	{
		if (a)
		{
			wsprintf (pszString, L"Enumerated texture Format : %d%d%d%d\n", r, g, b, a);
		}
		else
		{
			wsprintf (pszString, L"Enumerated texture Format : %d%d%d\n", r, g, b);
		}
	}
	OutputDebugString(pszString);

	/* Enumeration OK */
	return DDENUMRET_OK;
}


/*****************************************************************************
 * Function Name  : PaletteFromBitmap
 * Inputs		  : lpDD4, hBitmap
 * Output		  : lpDDPPalette
 * Description    : Create a palette for bitmap hBitmap.
 *					
 *****************************************************************************/
BOOL PaletteFromBitmap(LPDIRECTDRAW4 lpDD4, HBITMAP hBitmap, LPDIRECTDRAWPALETTE *lplpDDPPalette)
{
    HRESULT				hres;
	HDC					BitmapDC;
    DWORD				adw[256];
    int					nColors, i;
	
    /* Get the color table from the DIBSection */
    BitmapDC=CreateCompatibleDC(NULL);
	if (BitmapDC==NULL)
	{
		WCE_DEBUG(L"CreateCompatibleDC failed\n");
		return FALSE;
	}
    
	/* Get bitmap description */
	if (SelectObject(BitmapDC, hBitmap)==NULL)
	{
		WCE_DEBUG(L"SelectObject failed\n");
		return FALSE;
	}

    /* Get Color table */
	nColors=GetDIBColorTable(hBitmap, (RGBQUAD *)adw);
    if (!nColors)
	{
		WCE_DEBUG(L"GetDIBColorTable failed\n");
		DeleteDC(BitmapDC);
		return FALSE;
	}
	
	/* Delete Bitmap Device Context, as we don't need it anymore */
	if (DeleteDC(BitmapDC)==0)
	{
		WCE_DEBUG(L"DeleteDC failed\n");
	}

	/* Don't support 4-bit palettes for now */
	if (nColors<16)
	{
		WCE_DEBUG(L"Only supports 256 colors palettes\n");
		return FALSE;
	}

	/* Convert BGR to RGB */
    for (i=0; i<nColors; i++)
	{
		/* Process each color index */
		adw[i] = RGB_MAKE(GetRValue(adw[i]),GetGValue(adw[i]),GetBValue(adw[i]));
	}

    /* Create a DirectDraw palette for the texture. */
    hres=lpDD4->lpVtbl->CreatePalette(lpDD4, DDPCAPS_8BIT | DDPCAPS_ALLOW256, (PALETTEENTRY *)adw, lplpDDPPalette, NULL);
	if (hres!=DD_OK)
	{
		WCE_DEBUG(L"CreatePalette failed\n");
		return FALSE;
	}
    
	/* No problem occured */
	return TRUE;
}


/*****************************************************************************
 * Function Name  : GetPixelFormatInfo
 * Inputs		  : *pPixelFormat
 * Output		  : *pRedBits, *pGreenBits, *pBlueBits, *pAlphaBits,
 *					*pLeftR, *pLeftG, *pLeftB, *pLeftA, 
 *					*pRightR, *pRightG, *pRightB, *pRightA.
 * Description    : Returns information on pixel formats :
 *					- Number of bits for each channel.
 *					- Left shifting value of each channel.
 *					- Right shifting value of each channel.
 *					If any of the output pointers is NULL, then the
 *					corresponding pointed values will not be returned.
 *****************************************************************************/
void GetPixelFormatInfo(DDPIXELFORMAT *pPixelFormat,
						BYTE *pRedBits, BYTE *pGreenBits, BYTE *pBlueBits, BYTE *pAlphaBits,
						BYTE *pLeftR,	BYTE *pLeftG,	  BYTE *pLeftB,	   BYTE *pLeftA, 
						BYTE *pRightR,	BYTE *pRightG,	  BYTE *pRightB,   BYTE *pRightA)
{
	DWORD	i, m;
	BYTE	r=0, g=0, b=0, a=0;

	/* Check that a valid pointer was passed */
	if (!pPixelFormat)
	{
		WCE_DEBUG(L"GetPixelFormatInfo : PixelFormat pointer is NULL\n");
		return;
	}

	/* Calculate the number of bits available for each channel R, G, B, A */
	m=pPixelFormat->dwRBitMask; 
	for (i=0; i<32; i++)
	{
		if ((1<<i) & m) r++;
	}
    m=pPixelFormat->dwGBitMask; 
	for (i=0; i<32; i++) 
	{
		if ((1<<i) & m) g++;
	}
	m=pPixelFormat->dwBBitMask; 
	for (i=0; i<32; i++) 
	{
		if ((1<<i) & m) b++;
	}

	/* Find right shifting values */
	if (pRightR) *pRightR=8 - r;
	if (pRightG) *pRightG=8 - g;
	if (pRightB) *pRightB=8 - b;

    /* Find left shifting values */
	for (i=0; (pPixelFormat->dwRBitMask & (1<<i))==0 ; i++); 
	if (pLeftR) *pLeftR = i; 

    for (i=0; (pPixelFormat->dwGBitMask & (1<<i))==0 ; i++); 
	if (pLeftG) *pLeftG = i;
    
	for (i=0; (pPixelFormat->dwBBitMask & (1<<i))==0 ; i++); 
	if (pLeftB) *pLeftB = i;

	/* If format is translucent, perform the same operations for the alpha channel */
	if (pPixelFormat->dwFlags & DDPF_ALPHAPIXELS)
	{
        m=pPixelFormat->dwRGBAlphaBitMask; 
		for (i=0; i<32; i++) 
		{
			if ((1<<i) & m) a++;
		}
		if (pRightA) *pRightA=8 - a;
		for (i=0; (pPixelFormat->dwRGBAlphaBitMask & (1<<i))==0 ; i++); 
		if (pLeftA) *pLeftA=i;
	}
	else
	{
		/* Set the alpha values to 0 for an opaque format */
		if (pRightA) *pRightA=0;
		if (pLeftA) *pLeftA=0;
	}

	/* Write results into pointers */
	if (pRedBits)	*pRedBits=r;
	if (pGreenBits) *pGreenBits=g;
	if (pBlueBits)	*pBlueBits=b;
	if (pAlphaBits) *pAlphaBits=a;
}


/*****************************************************************************
 * Function Name  : GetColumnXXXXXXXXXX
 * Inputs		  : lpPixel, dwSourceWidth
 * Output		  : *pRed, *pGreen, *pBlue, *pAlpha
 * Description    : These inline functions are used in the automipmapping 
 *					function named CreateNextMipmapLevel4x4(...).
 *					They are used to generate the weighted color channels of
 *					each column in the mipmap. 
 *					Each color channel (Red, Green, Blue, Alpha) returned 
 *					by these functions has a weight of 6 (for GetColumn and 
 *					GetColumnAlpha) or 5 (for GetColumnWithout... and 
 *					GetColumnAlphaWithout...)
 *					
 *****************************************************************************/
__inline void GetColumn(PixelMap *lpPixel, int *pRed, int *pGreen, int *pBlue, DWORD dwSourceWidth)
{
	PixelMap Pixel1, Pixel2, Pixel3, Pixel4;
	
	/* Get four pixels of column */
	Pixel1=*(lpPixel-dwSourceWidth);
	Pixel2=*(lpPixel);
	Pixel3=*(lpPixel+dwSourceWidth);
	Pixel4=*(lpPixel+(dwSourceWidth<<1));

	/* Compute each weighted color channel in column */
	(*pRed)=	Pixel1.r + (Pixel2.r<<1) + (Pixel3.r<<1) + Pixel4.r;
	(*pGreen)=	Pixel1.g + (Pixel2.g<<1) + (Pixel3.g<<1) + Pixel4.g;
	(*pBlue)=	Pixel1.b + (Pixel2.b<<1) + (Pixel3.b<<1) + Pixel4.b;
}

__inline void GetColumnWithoutTop(PixelMap *lpPixel, int *pRed, int *pGreen, int *pBlue, DWORD dwSourceWidth)
{
	PixelMap Pixel2, Pixel3, Pixel4;
	
	/* Get three last pixels of column */
	Pixel2=*(lpPixel);
	Pixel3=*(lpPixel+dwSourceWidth);
	Pixel4=*(lpPixel+(dwSourceWidth<<1));

	/* Compute each weighted color channel in column */
	(*pRed)=	(Pixel2.r<<1) + (Pixel3.r<<1) + Pixel4.r;
	(*pGreen)=	(Pixel2.g<<1) + (Pixel3.g<<1) + Pixel4.g;
	(*pBlue)=	(Pixel2.b<<1) + (Pixel3.b<<1) + Pixel4.b;
}

__inline void GetColumnWithoutBottom(PixelMap *lpPixel, int *pRed, int *pGreen, int *pBlue, DWORD dwSourceWidth)
{
	PixelMap Pixel1, Pixel2, Pixel3;
	
	/* Get three first pixels of column */
	Pixel1=*(lpPixel-dwSourceWidth);
	Pixel2=*(lpPixel);
	Pixel3=*(lpPixel+dwSourceWidth);
	
	/* Compute each weighted color channel in column */
	(*pRed)=	Pixel1.r + (Pixel2.r<<1) + (Pixel3.r<<1);
	(*pGreen)=	Pixel1.g + (Pixel2.g<<1) + (Pixel3.g<<1);
	(*pBlue)=	Pixel1.b + (Pixel2.b<<1) + (Pixel3.b<<1);
}

__inline void GetColumnAlpha(PixelMap *lpPixel, int *pRed, int *pGreen, int *pBlue, int *pAlpha, DWORD dwSourceWidth)
{
	PixelMap	Pixel1, Pixel2, Pixel3, Pixel4;
	int			a1, a2, a3, a4;
	float		fInvA;
	
	/* Get four pixels of column */
	Pixel1=*(lpPixel-dwSourceWidth);
	Pixel2=*(lpPixel);
	Pixel3=*(lpPixel+dwSourceWidth);
	Pixel4=*(lpPixel+(dwSourceWidth<<1));

	/* Get alpha values of each pixels */
	a1=Pixel1.a;
	a2=Pixel2.a;
	a3=Pixel3.a;
	a4=Pixel4.a;

	/* Compute weighted alpha channel */
	(*pAlpha)=a1+(a2<<1)+(a3<<1)+a4;

	/* If alpha exists (non-zero), then compute averaged alpha to
	   determine each color channel of destination pixel */
	if (*pAlpha)
	{
		/* Compute inverse of average of all alpha values */
		fInvA=4.0f/(a1+a2+a3+a4);
		(*pRed)=	(int)(((a1*Pixel1.r) + (a2*Pixel2.r<<1) + (a3*Pixel3.r<<1) + (a4*Pixel4.r))*fInvA);
		(*pGreen)=	(int)(((a1*Pixel1.g) + (a2*Pixel2.g<<1) + (a3*Pixel3.g<<1) + (a4*Pixel4.g))*fInvA);
		(*pBlue)=	(int)(((a1*Pixel1.b) + (a2*Pixel2.b<<1) + (a3*Pixel3.b<<1) + (a4*Pixel4.b))*fInvA);
	}
	else
	{
		(*pRed)=	Pixel1.r + (Pixel2.r<<1) + (Pixel3.r<<1) + Pixel4.r;
		(*pGreen)=	Pixel1.g + (Pixel2.g<<1) + (Pixel3.g<<1) + Pixel4.g;
		(*pBlue)=	Pixel1.b + (Pixel2.b<<1) + (Pixel3.b<<1) + Pixel4.b;
	}
}

__inline void GetColumnAlphaWithoutTop(PixelMap *lpPixel, int *pRed, int *pGreen, int *pBlue, int *pAlpha, DWORD dwSourceWidth)
{
	PixelMap		Pixel2,Pixel3, Pixel4;
	int				a2, a3, a4;
	float			fInvA;
	
	/* Get three last pixels of column */
	Pixel2=*(lpPixel);
	Pixel3=*(lpPixel+dwSourceWidth);
	Pixel4=*(lpPixel+(dwSourceWidth<<1));

	/* Get alpha values of each pixels */
	a2=Pixel2.a;
	a3=Pixel3.a;
	a4=Pixel4.a;

	/* Compute weighted alpha channel */
	(*pAlpha)=(a2<<1)+(a3<<1)+a4;

	/* If alpha exists (non-zero), then compute averaged alpha to
	   determine each color channel of destination pixel */
	if (*pAlpha)
	{
		/* Compute inverse of average of all alpha values */
		fInvA=3.0f/(a2+a3+a4);
		(*pRed)=	(int)(((a2*Pixel2.r<<1) + (a3*Pixel3.r<<1) + (a4*Pixel4.r))*fInvA);
		(*pGreen)=	(int)(((a2*Pixel2.g<<1) + (a3*Pixel3.g<<1) + (a4*Pixel4.g))*fInvA);
		(*pBlue)=	(int)(((a2*Pixel2.b<<1) + (a3*Pixel3.b<<1) + (a4*Pixel4.b))*fInvA);
	}
	else
	{
		(*pRed)=	(Pixel2.r<<1) + (Pixel3.r<<1) + Pixel4.r;
		(*pGreen)=	(Pixel2.g<<1) + (Pixel3.g<<1) + Pixel4.g;
		(*pBlue)=	(Pixel2.b<<1) + (Pixel3.b<<1) + Pixel4.b;
	}
}

__inline void GetColumnAlphaWithoutBottom(PixelMap *lpPixel, int *pRed, int *pGreen, int *pBlue, int *pAlpha, DWORD dwSourceWidth)
{
	PixelMap	Pixel1, Pixel2, Pixel3;
	int			a1, a2, a3;
	float		fInvA;
	
	/* Get three first pixels of column */
	Pixel1=*(lpPixel-dwSourceWidth);
	Pixel2=*(lpPixel);
	Pixel3=*(lpPixel+dwSourceWidth);

	/* Get alpha values of each pixels */
	a1=Pixel1.a;
	a2=Pixel2.a;
	a3=Pixel3.a;

	/* Compute weighted alpha channel */
	(*pAlpha)=a1+(a2<<1)+(a3<<1);

	/* If alpha exists (non-zero), then compute averaged alpha to
	   determine each color channel of destination pixel */
	if (*pAlpha)
	{
		/* Compute inverse of average of all alpha values */
		fInvA=3.0f/(a1+a2+a3);
		(*pRed)=	(int)(((a1*Pixel1.r) + (a2*Pixel2.r<<1) + (a3*Pixel3.r<<1))*fInvA);
		(*pGreen)=	(int)(((a1*Pixel1.g) + (a2*Pixel2.g<<1) + (a3*Pixel3.g<<1))*fInvA);
		(*pBlue)=	(int)(((a1*Pixel1.b) + (a2*Pixel2.b<<1) + (a3*Pixel3.b<<1))*fInvA);
	}
	else
	{
		(*pRed)=	Pixel1.r + (Pixel2.r<<1) + (Pixel3.r<<1);
		(*pGreen)=	Pixel1.g + (Pixel2.g<<1) + (Pixel3.g<<1);
		(*pBlue)=	Pixel1.b + (Pixel2.b<<1) + (Pixel3.b<<1);
	}
}
/*******************************************************************************
 * Function Name  : GetResourceBitmap
 * Inputs		  : 
 * Global Used    : 
 * Description    : This function has been done to replace LoadImage()+GetObject()
 *					that are not fully implemented yet in DRAGON.
 *******************************************************************************/
void GetResourceBitmap(BITMAP *bm, LPCWSTR lpName)
{
HRSRC hrcBMP;
HGLOBAL hgBMP;
LPBITMAPINFOHEADER lpbi;
BYTE	*prgb;

	hrcBMP = FindResource(GetModuleHandle(NULL), lpName, RT_BITMAP);

	hgBMP = LoadResource(GetModuleHandle(NULL),hrcBMP);

	lpbi = (LPBITMAPINFOHEADER)LockResource(hgBMP);

	prgb = (BYTE *) ((LPBYTE)lpbi + lpbi->biSize);

	// Output to our BITMAP structure.
	bm->bmType			= (int)0;
    bm->bmWidth			= (int)lpbi->biWidth;    
	bm->bmHeight		= (int)lpbi->biHeight;
    bm->bmWidthBytes	= (int)(lpbi->biWidth) * (lpbi->biBitCount/8);    
	bm->bmPlanes		= (BYTE)lpbi->biPlanes;    
	bm->bmBitsPixel		= (BYTE)lpbi->biBitCount;
 	bm->bmBits		    = (void *)(prgb);
}
/*******************************************************************************
 * Function Name  : GetResourceBitmap
 * Inputs		  : 
 * Global Used    : 
 * Description    : This function has been done to replace LoadImage()+GetObject()
 *					that are not fully implemented yet in DRAGON.
 *******************************************************************************/
int GetDIBColorTable(HBITMAP hBitmap, RGBQUAD *adw)
{
HGLOBAL hgBMP;
LPBITMAPINFOHEADER lpbi;
int CTSize;

	hgBMP = LoadResource(GetModuleHandle(NULL), hBitmap);

	lpbi = (LPBITMAPINFOHEADER)LockResource(hgBMP);

	adw = (RGBQUAD *) ((LPBYTE)lpbi + lpbi->biSize);

	if(lpbi->biBitCount>8) CTSize = 0;
	else if (lpbi->biClrUsed ==0) CTSize = 1 << lpbi->biBitCount;
	else    CTSize = lpbi->biClrUsed;

	return CTSize;
}


