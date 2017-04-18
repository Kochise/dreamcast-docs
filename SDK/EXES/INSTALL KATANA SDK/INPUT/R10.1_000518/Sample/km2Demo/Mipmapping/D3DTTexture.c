/*****************************************************************************
  Name : D3DTTexture.c
  Date : November 1998
  Platform : ANSI compatible
 
  * Description : 
  This file is part of the TOOLS library (D3DTools.lib) used
  with the SDK demos for PowerVR series 2.

  Set of functions used in texturing.
  

  Copyright : 1998 by VideoLogic Limited. All rights reserved.
******************************************************************************/
#include <stdio.h>
#include <math.h>
#include <d3d.h>
#include "D3DTTexture.h"


/***********
** Pragma **
***********/
/* Disable conversion warning (e.g. double to float loss of data) */
#pragma warning(disable : 4244)  

/************
** Defines **
************/
#define FREE(x)	if (x) { free(x); x=NULL; }

//#undef RELEASE
//#define RELEASE(x)		if (x) { sprintf(pszTmp, "%s released. Ref count=%d\n", #x, (x)->lpVtbl->Release(x)); OutputDebugString(pszTmp); (x)=NULL; }

/*********************
** Internal typedef **
*********************/
typedef struct
{
	unsigned char Blue;
	unsigned char Green;
	unsigned char Red;
	unsigned char Alpha;
} PixelMap;

typedef enum TextureTypeTAG { 
	RGBA = 1, 
	PAL4, 
	PAL8, 
	LUMA, 
	BUMPMAP, 
	FOURCC_YUV, 
	FOURCC_DXT 
} TextureType;

/*********************
** Global variables **
*********************/
D3DTTextureFormatType		D3DTTextureFormat[30];
static int					nTextureFormat=-1;

// temp
char						pszTmp[300];

/*************************************
** Prototypes of internal functions **
*************************************/
static BOOL				GetPaletteFromBitmapHandle(HBITMAP hBitmap, PALETTEENTRY *pPaletteEntries);
static BOOL				CopyPALBitmapToRGBBitmap(BITMAP *pBm, PALETTEENTRY *pPaletteEntries, BITMAP *pBmOut);
static BOOL				CopyBitmapToRGBASurface(LPDIRECTDRAWSURFACE4 lpDDS, BITMAP *pBm, BITMAP *pBmTrans);
static BOOL				CopyBitmapToPALSurface(LPDIRECTDRAWSURFACE4 lpDDS, BITMAP *pBm, PALETTEENTRY *pPaletteEntries);
static BOOL				CopyBitmapToLuminanceSurface(LPDIRECTDRAWSURFACE4 lpDDS, BITMAP *pBm, BITMAP *pBmTrans);
static BOOL				CopyBitmapToYUVSurface(LPDIRECTDRAWSURFACE4 lpDDS, BITMAP *pBm);
static BOOL				CopyBitmapToDXTSurface(LPDIRECTDRAW4 lpDD4, LPDIRECTDRAWSURFACE4 lpDDS, BITMAP *pBm, BITMAP *pBmTrans);
static BOOL				CopyBitmapToBumpMapSurface(LPDIRECTDRAWSURFACE4 lpDDS, BITMAP *pBm);
static BOOL				CreateFourierMipmapLevels(LPDIRECTDRAW4 lpDD4, LPDIRECT3DDEVICE3 lpDev3, BITMAP *pBm, BITMAP *pBmTrans, LPDIRECTDRAWSURFACE4 lpDDSSystemMemorySurface, int nOrder);
static void				DitherBitmap(int XDim, int YDim, DDPIXELFORMAT *lpddPixelFormat, unsigned char *pBitmapData, unsigned char *pTranslucentBitmapData);
static BOOL				CreateNextMipmapLevel2x2(BITMAP *pBm, BITMAP *pBmTrans, BITMAP *pBmOut, BITMAP *pBmTransOut);
static BOOL				CreateNextMipmapLevel4x4(BITMAP *pBm, BITMAP *pBmTrans, BITMAP *pBmOut, BITMAP *pBmTransOut);
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
static BOOL				PaletteFromBitmap(LPDIRECTDRAW4 lpDD4, HBITMAP hBitmap, PALETTEENTRY *pPaletteEntries);
static void				GetPixelFormatInfo(DDPIXELFORMAT *pPixelFormat, BYTE *pRedBits, BYTE *pGreenBits, BYTE *pBlueBits, BYTE *pAlphaBits, BYTE *pLeftR,	BYTE *pLeftG, BYTE *pLeftB,	BYTE *pLeftA, BYTE *pRightR, BYTE *pRightG, BYTE *pRightB, BYTE *pRightA);
static BYTE				GetClosestIndex(int Red, int Green, int Blue, int nNumber, PALETTEENTRY *pPalette);
static BOOL				SaveBitmapOntoDisk(BITMAP *pBm, char *pszFileName);
static void				DisplayInfoAboutSurface(LPDIRECTDRAWSURFACE4 lpDDS);


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
							  char *lpNames[], char *lpTranslucentNames[],
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
		OutputDebugString("D3DTTextureLoadMipmapBMP : Failed in D3DTTextureReadMipmapBMP\n");
		return FALSE;
	}

	/* Then load texture into texture memory */
	if (!D3DTTextureUpload(lpDD4, lpDev3, lpDDSSystemMemorySurface, bUseD3DTextureManagement,
						   lplpDDSTextureSurface, lplpD3DTexture2))
	{
		OutputDebugString("D3DTTextureLoadMipmapBMP : Failed in D3DTTextureUpload\n");
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
						char *lpName, char *lpTranslucentName, 
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
		OutputDebugString("D3DTTextureLoadBMP : Failed in D3DTTextureReadBMP\n");
		RELEASE(lpDDSSystemMemorySurface);
		return FALSE;
	}

	/* Then load texture into texture memory */
	if (!D3DTTextureUpload(lpDD4, lpDev3, lpDDSSystemMemorySurface, bUseD3DTextureManagement, 
						   lplpDDSTextureSurface, lplpD3DTexture2))
	{
		OutputDebugString("D3DTTextureLoadBMP : Failed in D3DTTextureUpload\n");
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
 *					Each BMP must be half the size of the previous 
 *					one in the list.
 *					If any of the lower mipmap levels BMP names are NULL, then
 *					the corresponding level is auto-generated using the previous
 *					mipmap level.
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
 *					  If the BMP file is 4 or 8-bit palettised, then the texture format
 *					  must also be 4 or 8-bit palettised.
 *					- *lplpDDSSystemMemorySurface is a pointer pointing to the address
 *					  of the resulting SYSTEM MEMORY texture.
 *					This function supports RGB and OS/2 BMP formats. RLE encoded 
 *					format is NOT supported.
 *
 *******************************************************************************/
BOOL D3DTTextureReadMipmapBMP(LPDIRECTDRAW4 lpDD4, LPDIRECT3DDEVICE3 lpDev3,
							  char *lpNames[], char *lpTranslucentNames[],
							  DDPIXELFORMAT *lpddPixelFormat, LPDIRECTDRAWSURFACE4 *lplpDDSSystemMemorySurface)
{
	HRESULT					hres;
	LPDIRECTDRAWSURFACE4	lpSrcTextureSurf=NULL;
	LPDIRECTDRAWSURFACE4	lpDDSCurrentMemorySurface=NULL;
	LPDIRECT3DTEXTURE2		lpSrcTexture=NULL;
	LPDIRECTDRAWPALETTE		lpDDPPalette=NULL;
	PALETTEENTRY			PaletteEntries[256];
	DDSURFACEDESC2			ddsd;
	D3DDEVICEDESC			ddHAL, ddHEL, *lpD3DDeviceDesc;
	TextureType				eTextureFormat=RGBA;
	DDSCAPS2				ddsCaps;
	HBITMAP					hBitmap, hBitmapTrans;
	BITMAP					bm[16], bmTrans[16], TmpBitmap;
	DWORD					dwMemoryUsedByTexture=0, dwNumberOfMipmapLevels=0, i, j;
	BYTE					r, g, b, a;
	BOOL					bTranslucent=FALSE;
	BOOL					bCopyOK=FALSE;
	BOOL					bSupportAlphaTexturing=FALSE;
	BOOL					bSupportNonSquareTextures=FALSE;
	BOOL					bSupportMipmapping=FALSE;
	char					pszString[256];
	
	/* Check that parameters are valid */
	if (!lpDD4 || !lpDev3 || !lpNames || !lpddPixelFormat || !lplpDDSSystemMemorySurface)
	{
		OutputDebugString("D3DTTextureReadMipmapBMP : Bad parameters.\n");
		return FALSE;
	}

	/* Are we using a translucent texture format ? */
	if (lpddPixelFormat->dwFlags & DDPF_ALPHAPIXELS)
	{
		OutputDebugString("D3DTTextureReadMipmapBMP : Translucent texture format used\n");
		bTranslucent=TRUE;
	}

	/* Are we using special FOURCC codes for the texture format ? */
	if (lpddPixelFormat->dwFlags & DDPF_FOURCC)
	{
		switch(lpddPixelFormat->dwFourCC)
		{
			case MAKEFOURCC('Y', 'U', 'Y', '2') :
			case MAKEFOURCC('U', 'Y', 'V', 'Y') : eTextureFormat=FOURCC_YUV; break;
			case MAKEFOURCC('D', 'X', 'T', '5') :
			case MAKEFOURCC('D', 'X', 'T', '4') : 
			case MAKEFOURCC('D', 'X', 'T', '3') :
			case MAKEFOURCC('D', 'X', 'T', '2') : bTranslucent=TRUE;
			case MAKEFOURCC('D', 'X', 'T', '1') : eTextureFormat=FOURCC_DXT; break;
			default :	OutputDebugString("D3DTTextureReadMipmapBMP : Unknown FOURCC code\n");
						return FALSE;
		}
	}

	/* Is texture a bump map format ? */
	if (lpddPixelFormat->dwFlags & (DDPF_BUMPDUDV | DDPF_BUMPLUMINANCE))
	{
		eTextureFormat=BUMPMAP;
	}

	/* Is texture a luminance format ? */
	if (lpddPixelFormat->dwFlags & DDPF_LUMINANCE)
	{
		eTextureFormat=LUMA;
	}

	/* Is texture a 4 or 8 bits palettised texture ? */
	if (lpddPixelFormat->dwFlags & DDPF_PALETTEINDEXED4)
	{
		eTextureFormat=PAL4;
	}
	if (lpddPixelFormat->dwFlags & DDPF_PALETTEINDEXED8)
	{
		eTextureFormat=PAL8;
	}

	/* Check that no translucent texture is to be loaded with YUV or BumpMap format */
	if ( (eTextureFormat==FOURCC_YUV || eTextureFormat==BUMPMAP) 
		 && (bTranslucent || lpTranslucentNames) )
	{
		OutputDebugString("D3DTTextureReadMipmapBMP : Can't load translucent texture with YUV or bumpmap format!\n");
		return FALSE;
	}

	/* If a translucent file name has been submitted, and 
	   the texture format is opaque then return from function */
	if (lpTranslucentNames && !bTranslucent && eTextureFormat!=FOURCC_DXT)
	{
		OutputDebugString("D3DTTextureReadMipmapBMP : Select a translucent format for a translucent texture!\n");
		return FALSE;
	}

	/* If a translucent format is used with no translucent information, warn the user */
	if (!lpTranslucentNames && bTranslucent)
	{
		OutputDebugString("D3DTTextureReadMipmapBMP : Alpha format used but no alpha information (no translucent bitmap)\n");
	}

	/* Check that translucency is not set for a palettised texture */
	if ( (eTextureFormat==PAL4 || eTextureFormat==PAL8) && lpTranslucentNames)
	{
		OutputDebugString("D3DTTextureReadMipmapBMP : Palettised texture can not be translucent.\n");
		return FALSE;
	}


	/* Initialise D3DDEVICEDESC structures */
	ZeroMemory(&ddHAL, sizeof(D3DDEVICEDESC));
	ZeroMemory(&ddHEL, sizeof(D3DDEVICEDESC));
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
		OutputDebugString("D3DTTextureReadMipmapBMP : 3D Device does not support mipmapping.\n");
		return FALSE;
	}

	/* Check that device supports alpha texturing */
	if (!bSupportAlphaTexturing && lpTranslucentNames)
	{
		OutputDebugString("D3DTTextureReadMipmapBMP : 3D Device does not support ALPHA textures.\n");
		return FALSE;
	}

	/* Load texture into BITMAP : first try to load from resource */
	hBitmap=(HBITMAP)LoadImage(GetModuleHandle(NULL), lpNames[0], IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
    if (hBitmap==NULL)
	{
		/* Load from file */
		hBitmap=(HBITMAP)LoadImage(NULL, lpNames[0], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (hBitmap==NULL)
		{
			sprintf(pszString, "D3DTTextureReadMipmapBMP : File %s not found\n", lpNames[0]);
			OutputDebugString(pszString);
			return FALSE;
		}
	}

	/* If translucent, then also read the first file of lpTranslucentNames */
	if (lpTranslucentNames)
	{
		/* Load translucent texture : first try to load from resource */
		hBitmapTrans=(HBITMAP)LoadImage(GetModuleHandle(NULL), lpTranslucentNames[0], IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
		if (hBitmapTrans==NULL)
		{
			/* Load from file */
			hBitmapTrans=(HBITMAP)LoadImage(NULL, lpTranslucentNames[0], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			if (hBitmapTrans==NULL)
			{
				sprintf(pszString, "D3DTTextureReadMipmapBMP : File %s not found\n", lpTranslucentNames[0]);
				OutputDebugString(pszString);
				DeleteObject(hBitmap);
				return FALSE;
			}
		}
	}

	/* Get bitmap description */
    GetObject(hBitmap, sizeof(BITMAP), &TmpBitmap);
	
	/* Find out how many mipmap levels have to be created.
	   It depends on the texture size. At the same time,
	   check that texture size is a power of 2 */
	switch(min(TmpBitmap.bmWidth, TmpBitmap.bmHeight))
	{
		case 2048 :	dwNumberOfMipmapLevels=11; break;
		case 1024 :	dwNumberOfMipmapLevels=10; break;
		case 512 :	dwNumberOfMipmapLevels=9; break;
		case 256:	dwNumberOfMipmapLevels=8; break;
		case 128:	dwNumberOfMipmapLevels=7; break;
		case 64:	dwNumberOfMipmapLevels=6; break;
		case 32:	dwNumberOfMipmapLevels=5; break;
		case 16:	dwNumberOfMipmapLevels=4; break;
		case 8:		dwNumberOfMipmapLevels=3; break;
		case 4:		dwNumberOfMipmapLevels=2; break;
		case 2:		dwNumberOfMipmapLevels=1; break;
		case 1:		dwNumberOfMipmapLevels=0; break;
		default :	OutputDebugString("D3DTTextureReadMipmapBMP  : Texture size is not a power of 2\n");
					DeleteObject(hBitmap);
					return FALSE;
	}

	/* Initialise first bitmap level */
	memcpy(&bm[0], &TmpBitmap, sizeof(BITMAP));
	bm[0].bmBits=(unsigned char *)malloc(bm[0].bmHeight * bm[0].bmWidthBytes);
	memcpy(bm[0].bmBits, TmpBitmap.bmBits, bm[0].bmHeight * bm[0].bmWidthBytes);


	/* Create a palette if necessary */
	/* If texture is palettised, create a palette for the texture */
    if (eTextureFormat==PAL4 || eTextureFormat==PAL8)
    {
        /* Create palette from bitmap */
		if (!PaletteFromBitmap(lpDD4, hBitmap, PaletteEntries))
		{
			OutputDebugString("D3DTTextureReadMipmapBMP : PaletteFromBitmap failed\n");
		}

		/* Create a DirectDraw palette for the texture. */
		if (eTextureFormat==PAL4)
		{
			hres=lpDD4->lpVtbl->CreatePalette(lpDD4, DDPCAPS_4BIT, PaletteEntries, &lpDDPPalette, NULL);
		}
		else
		{
			hres=lpDD4->lpVtbl->CreatePalette(lpDD4, DDPCAPS_8BIT | DDPCAPS_ALLOW256, PaletteEntries, &lpDDPPalette, NULL);
		}
		if (hres!=DD_OK)
		{
			OutputDebugString("PaletteFromBitmap : CreatePalette() failed\n");
			return FALSE;
		}
	}

	/* Now destroy bitmap */
	DeleteObject(hBitmap);

	/* Translucent case */
	if (lpTranslucentNames)
	{
		GetObject(hBitmapTrans, sizeof(BITMAP), &TmpBitmap);
		memcpy(&bmTrans[0], &TmpBitmap, sizeof(BITMAP));
		bmTrans[0].bmBits=(unsigned char *)malloc(bmTrans[0].bmHeight * bmTrans[0].bmWidthBytes);
		memcpy(bmTrans[0].bmBits, TmpBitmap.bmBits, bmTrans[0].bmHeight * bmTrans[0].bmWidthBytes);
		DeleteObject(lpTranslucentNames);
	}


	/* Is texture requested as 4 bits palettised ? */
	if (eTextureFormat==PAL4)
	{
		/* Yes, check that the bitmap loaded is a 4-bit bitmap */
		if (bm[0].bmBitsPixel!=4)
		{
			OutputDebugString("D3DTTextureReadMipmapBMP : A 4-bit palettised bitmap must be used to create a 4-bit palettised texture\n");
			if (lpTranslucentNames) FREE(bmTrans[0].bmBits);
			FREE(bm[0].bmBits);
			return FALSE;
		}
	}
	/* Is texture requested as 8 bits palettised ? */
	else if (eTextureFormat==PAL8)
	{
		/* Yes, check that the bitmap loaded is an 8-bit bitmap */
		if (bm[0].bmBitsPixel!=8)
		{
			OutputDebugString("D3DTTextureReadMipmapBMP : A 8-bit palettised bitmap must be used to create an 8-bit palettised texture\n");
			if (lpTranslucentNames) FREE(bmTrans[0].bmBits);
			FREE(bm[0].bmBits);
			return FALSE;
		}
	}
	else
	{
		/* Texture is not requested as palettised, so check that a 
		   normal 24-bits bitmap has been loaded */
		if (bm[0].bmBitsPixel!=24)
		{
			OutputDebugString("D3DTTextureReadMipmapBMP : The bmp file must be in 24 bits format for an RGBA texture type\n");
			if (lpTranslucentNames) FREE(bmTrans[0].bmBits);
			FREE(bm[0].bmBits);
			return FALSE;
		}
	}

	/* If translucent texture has also been loaded, check that both 
	   widths and heights are equal and that the bit depth is the same */
	if (lpTranslucentNames)
	{
		if (bm[0].bmWidth!=bmTrans[0].bmWidth || bm[0].bmHeight!=bmTrans[0].bmHeight || bm[0].bmBitsPixel!=bmTrans[0].bmBitsPixel)
		{
			/* Bitmap and translucent bitmap have different types */
			OutputDebugString("D3DTTextureReadMipmapBMP : Bitmap and translucent bitmap have different types.\n");
			if (lpTranslucentNames) FREE(bmTrans[0].bmBits);
			FREE(bm[0].bmBits);
			return FALSE;
		}
	}

	/* Check that width and height are equal for devices that only support SQUARE textures */
	if (!bSupportNonSquareTextures)
	{
		if (bm[0].bmWidth!=bm[0].bmHeight)
		{
			OutputDebugString("D3DTTextureReadMipmapBMP : Device does not support non-square textures\n");
			if (lpTranslucentNames) FREE(bmTrans[0].bmBits);
			FREE(bm[0].bmBits);
			return FALSE;
		}
		if (lpTranslucentNames)
		{
			if (bmTrans[0].bmWidth!=bmTrans[0].bmHeight)
			{	
				OutputDebugString("D3DTTextureReadMipmapBMP : Device does not support non-square textures\n");
				FREE(bmTrans[0].bmBits);
				FREE(bm[0].bmBits);
				return FALSE;
			}
		}
	}

	/* Allocate memory for bitmap array that contain all mipmap levels */
	for (i=1; i<=dwNumberOfMipmapLevels; i++)
	{
		bm[i].bmType =		bm[i-1].bmType;
		bm[i].bmWidth =		max(1, bm[i-1].bmWidth/2);
		bm[i].bmHeight =	max(1, bm[i-1].bmHeight/2);
		bm[i].bmWidthBytes= (bm[i].bmWidth * bm[0].bmBitsPixel) / 8;
		if (bm[i].bmWidthBytes % 4) bm[i].bmWidthBytes += 4 - (bm[i].bmWidthBytes % 4);
		bm[i].bmPlanes=		bm[i-1].bmPlanes;
		bm[i].bmBitsPixel =	bm[i-1].bmBitsPixel;
		bm[i].bmBits = (unsigned char *)malloc(bm[i].bmHeight * bm[i].bmWidthBytes);
		if (!bm[i].bmBits)
		{
			OutputDebugString("D3DTTextureReadMipmapBMP : Not enough memory to allocate bitmap\n");
			for (j=0; j<dwNumberOfMipmapLevels; j++)
			{
				FREE(bm[j].bmBits);
			}
			return FALSE;
		}

		if (lpTranslucentNames)
		{
			bmTrans[i].bmType =			bmTrans[i-1].bmType;
			bmTrans[i].bmWidth =		max(1, bmTrans[i-1].bmWidth/2);
			bmTrans[i].bmHeight =		max(1, bmTrans[i-1].bmHeight/2);
			bmTrans[i].bmWidthBytes =	(bmTrans[i].bmWidth * bmTrans[0].bmBitsPixel) / 8;
			if (bmTrans[i].bmWidthBytes % 4) bmTrans[i].bmWidthBytes += 4 - (bmTrans[i].bmWidthBytes % 4);
			bmTrans[i].bmPlanes=		bmTrans[i-1].bmPlanes;
			bmTrans[i].bmBitsPixel =	bmTrans[i-1].bmBitsPixel;
			bmTrans[i].bmBits = (unsigned char *)malloc(bmTrans[i].bmHeight * bmTrans[i].bmWidthBytes);
			if (!bmTrans[i].bmBits)
			{
				OutputDebugString("D3DTTextureReadMipmapBMP : Not enough memory to allocate bitmap\n");
				for (j=0; j<dwNumberOfMipmapLevels; j++)
				{
					if (lpTranslucentNames) FREE(bmTrans[j].bmBits);
					FREE(bm[j].bmBits);
				}
				return FALSE;
			}
		}
	}
	

	/* For normal textures (non-palettised), compute the number of bits
	   for each channel Red, Green, Blue and Alpha (if translucent) */
	if (eTextureFormat==RGBA)
	{
		GetPixelFormatInfo(lpddPixelFormat, &r, &g, &b, &a,
											NULL, NULL, NULL, NULL,
											NULL, NULL, NULL, NULL);
	}

	/* Calculate memory used by texture */
	for (i=0; i<dwNumberOfMipmapLevels; i++)
	{
		dwMemoryUsedByTexture+=(bm[i].bmWidth*bm[i].bmHeight*lpddPixelFormat->dwRGBBitCount)/8;
	}
	
	/* Debug info about texture */
	sprintf(pszString, "\nD3DTTextureReadMipmapBMP : Loading %s texture : %s (%u*%u) %.2f KBytes\n", 
						bTranslucent ? "translucent" : "", lpNames[0], bm[0].bmWidth, bm[0].bmHeight, dwMemoryUsedByTexture/1024.0f);
	OutputDebugString(pszString);
	switch(eTextureFormat)
	{
	case RGBA :		sprintf(pszString, "D3DTTextureReadMipmapBMP : Texture format = %d%d%d%d\n", r, g, b, a); break;
	case PAL4 :		sprintf(pszString, "D3DTTextureReadMipmapBMP : Texture format = 4-bit palettised\n"); break;
	case PAL8 :		sprintf(pszString, "D3DTTextureReadMipmapBMP : Texture format = 8-bit palettised\n"); break;
	case LUMA :		sprintf(pszString, "D3DTTextureReadMipmapBMP : Texture format = Luminance format\n"); break;
	case BUMPMAP :	sprintf(pszString, "D3DTTextureReadMipmapBMP : Texture format = BumpMap format\n"); break;
	case FOURCC_YUV:	switch(lpddPixelFormat->dwFourCC)
						{
							case MAKEFOURCC('Y', 'U', 'Y', '2') : sprintf(pszString, "D3DTTextureReadMipmapBMP : Texture format = FOURCC YUY2\n"); break;
							case MAKEFOURCC('U', 'Y', 'V', 'Y') : sprintf(pszString, "D3DTTextureReadMipmapBMP : Texture format = FOURCC UYVY\n"); break;
							default : sprintf(pszString, "D3DTTextureReadMipmapBMP : Texture format = Unknown YUV FOURCC code\n");
						}
						break;
	case FOURCC_DXT:
						switch(lpddPixelFormat->dwFourCC)
						{
							case MAKEFOURCC('D', 'X', 'T', '1') : sprintf(pszString, "D3DTTextureReadMipmapBMP : Texture format = FOURCC DXT1\n"); break;
							case MAKEFOURCC('D', 'X', 'T', '2') : sprintf(pszString, "D3DTTextureReadMipmapBMP : Texture format = FOURCC DXT2\n"); break;
							case MAKEFOURCC('D', 'X', 'T', '3') : sprintf(pszString, "D3DTTextureReadMipmapBMP : Texture format = FOURCC DXT3\n"); break;
							case MAKEFOURCC('D', 'X', 'T', '4') : sprintf(pszString, "D3DTTextureReadMipmapBMP : Texture format = FOURCC DXT4\n"); break;
							case MAKEFOURCC('D', 'X', 'T', '5') : sprintf(pszString, "D3DTTextureReadMipmapBMP : Texture format = FOURCC DXT5\n"); break;
							default : sprintf(pszString, "D3DTTextureReadMipmapBMP : Texture format = Unknown DXT FOURCC code\n");
						}
						break;
	default :			sprintf(pszString, "D3DTTextureReadMipmapBMP : Texture format = Unknown\n");
	}
	OutputDebugString(pszString);

	
	/* Set the fields of the DirectDraw Surface Description */
    ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
    ddsd.dwSize=sizeof(DDSURFACEDESC2);
    ddsd.dwFlags=DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PIXELFORMAT;
    ddsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE | DDSCAPS_SYSTEMMEMORY | DDSCAPS_MIPMAP | DDSCAPS_COMPLEX;
    ddsd.dwWidth=bm[0].bmWidth;
	ddsd.dwHeight=bm[0].bmHeight;
	ddsd.ddpfPixelFormat=*lpddPixelFormat;

	/* Create surface */
	hres=lpDD4->lpVtbl->CreateSurface(lpDD4, &ddsd, lplpDDSSystemMemorySurface, NULL);
	if (hres!=DD_OK) 
	{
		OutputDebugString("D3DTTextureReadMipmapBMP : Failed to create system memory surface\n");
		for (j=0; j<=dwNumberOfMipmapLevels; j++)
		{
			if (lpTranslucentNames) FREE(bmTrans[j].bmBits);
			FREE(bm[j].bmBits);
		}
		return FALSE;
	}

	/* For palletised textures, attach palette computed earlier */
	if (eTextureFormat==PAL4 || eTextureFormat==PAL8)
	{
        /* Attach the palette to the Surface and the texture */
		hres=(*lplpDDSSystemMemorySurface)->lpVtbl->SetPalette((*lplpDDSSystemMemorySurface), lpDDPPalette);
		if (hres!=DD_OK)
		{
			OutputDebugString("D3DTTextureReadMipmapBMP : SetPalette failed\n");
			RELEASE(*lplpDDSSystemMemorySurface);
			for (j=0; j<=dwNumberOfMipmapLevels; j++)
			{
				if (lpTranslucentNames) FREE(bmTrans[j].bmBits);
				FREE(bm[j].bmBits);
			}
			return FALSE;
		}
    }
	
	
	/***************************************************
	** Load or create mipmap levels into Bitmap array **
	***************************************************/
	
	/* Loop through all mipmap levels */
	for (i=1; i<=dwNumberOfMipmapLevels; i++)
	{
		sprintf(pszString, "Loading mipmap level %d\n", i);
		OutputDebugString(pszString);
		
		/* Load next mipmap from disk or resource */
		if (lpNames[i])
		{
			/* Load bitmap files */
			hBitmap=(HBITMAP)LoadImage(GetModuleHandle(NULL), lpNames[i], IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
			if (hBitmap==NULL)
			{
				/* Load from file */
				hBitmap=(HBITMAP)LoadImage(NULL, lpNames[i], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				if (!hBitmap)
				{
					sprintf(pszString, "D3DTTextureReadMipmapBMP : File %s not found\n", lpNames[i]);
					OutputDebugString(pszString);
					RELEASE(*lplpDDSSystemMemorySurface);
					for (j=0; j<=dwNumberOfMipmapLevels; j++)
					{
						if (lpTranslucentNames) FREE(bmTrans[j].bmBits);
						FREE(bm[j].bmBits);
					}
					return FALSE;
				}
			}

			/* Load data into out bitmap */
			GetObject(hBitmap, sizeof(BITMAP), &TmpBitmap);

			/* Check that bitmap has correct parameters */
			if (TmpBitmap.bmHeight	  != bm[i].bmHeight ||
				TmpBitmap.bmWidth	  != bm[i].bmWidth ||
				TmpBitmap.bmBitsPixel != bm[i].bmBitsPixel)
			{
				sprintf(pszString, "D3DTTextureReadMipmapBMP : File %s (MipMap level %d) doesn't have correct dimensions\n", lpNames[i], i);
				OutputDebugString(pszString);
				RELEASE(*lplpDDSSystemMemorySurface);
				for (j=0; j<=dwNumberOfMipmapLevels; j++)
				{
					if (lpTranslucentNames) FREE(bmTrans[j].bmBits);
					FREE(bm[j].bmBits);
				}
				return FALSE;
			}

			/* Copy bitmap into array and delete TmpBitmap */
			memcpy(bm[i].bmBits, TmpBitmap.bmBits, bm[i].bmHeight * bm[i].bmWidthBytes);
			DeleteObject(hBitmap);

			/* If translucent, then also read the file lpTranslucentNames */
			if (lpTranslucentNames)
			{
				/* Load translucent texture : first try to load from resource */
				hBitmapTrans=(HBITMAP)LoadImage(GetModuleHandle(NULL), lpTranslucentNames[i], IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
				if (hBitmapTrans==NULL)
				{
					/* Load from file */
					hBitmapTrans=(HBITMAP)LoadImage(NULL, lpTranslucentNames[i], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					if (hBitmapTrans==NULL)
					{
						sprintf(pszString, "D3DTTextureReadMipmapBMP : File %s not found\n", lpTranslucentNames[i]);
						OutputDebugString(pszString);
						RELEASE(*lplpDDSSystemMemorySurface);
						for (j=0; j<=dwNumberOfMipmapLevels; j++)
						{
							if (lpTranslucentNames) FREE(bmTrans[j].bmBits);
							FREE(bm[j].bmBits);
						}
						return FALSE;
					}
				}

				/* Load data into out bitmap */
				GetObject(hBitmapTrans, sizeof(BITMAP), &TmpBitmap);
				
				/* Check that bitmap has correct parameters */
				if (TmpBitmap.bmHeight	  != bmTrans[i].bmHeight ||
					TmpBitmap.bmWidth	  != bmTrans[i].bmWidth ||
					TmpBitmap.bmBitsPixel != bmTrans[i].bmBitsPixel)
				{
					sprintf(pszString, "D3DTTextureReadMipmapBMP : File %s (MipMap level %d) doesn't have correct dimensions\n", lpTranslucentNames[i], i);
					OutputDebugString(pszString);
					RELEASE(*lplpDDSSystemMemorySurface);
					for (j=0; j<=dwNumberOfMipmapLevels; j++)
					{
						FREE(bmTrans[j].bmBits);
						FREE(bm[j].bmBits);
					}
					return FALSE;
				}

				/* Copy bitmap into array and delete TmpBitmap */
				memcpy(bmTrans[i].bmBits, TmpBitmap.bmBits, bmTrans[i].bmHeight * bmTrans[i].bmWidthBytes);
				DeleteObject(hBitmapTrans);
			}
		}
		else
		{
			/* Special case for palettised bitmap : might need 24 bits expanding */
			if (eTextureFormat==PAL4 || eTextureFormat==PAL8)
			{
				/* Reset current level bitmap fields */
				bm[i].bmBitsPixel=	24;
				bm[i].bmWidthBytes=	3 * bm[i].bmWidth;
				if (bm[i].bmWidthBytes % 4) bm[i].bmWidthBytes += 4 - (bm[i].bmWidthBytes % 4);
				FREE(bm[i].bmBits);
				bm[i].bmBits=(unsigned char *)malloc(bm[i].bmHeight * bm[i].bmWidthBytes);
				
				/* Expand bitmap if previous one is palettised */
				if (bm[i-1].bmBitsPixel!=24)
				{
					/* Set the field of expanded mipmap */
					TmpBitmap.bmType =		bm[i-1].bmType;
					TmpBitmap.bmWidth =		bm[i-1].bmWidth;
					TmpBitmap.bmHeight=		bm[i-1].bmHeight;
					TmpBitmap.bmWidthBytes=	3 * bm[i-1].bmWidth;
					if (TmpBitmap.bmWidthBytes % 4) TmpBitmap.bmWidthBytes += 4 - (TmpBitmap.bmWidthBytes % 4);
					TmpBitmap.bmPlanes=		bm[i-1].bmPlanes;
					TmpBitmap.bmBitsPixel =	24;
					TmpBitmap.bmBits = (unsigned char *)malloc(TmpBitmap.bmHeight * TmpBitmap.bmWidthBytes);
					if (!TmpBitmap.bmBits)
					{
						OutputDebugString("D3DTTextureReadMipmapBMP : Not enough memory to allocate expanded bitmap\n");
						for (j=0; j<=dwNumberOfMipmapLevels; j++)
						{
							FREE(bm[j].bmBits);
						}
						return FALSE;
					}
				
					/* Copy palettised bitmap to 24 bits bitmap */
					if (!CopyPALBitmapToRGBBitmap(&bm[i-1], PaletteEntries, &TmpBitmap))
					{
						OutputDebugString("D3DTTextureReadBMP : Failed to copy palettised bitmap to a 24 bits bitmap\n");
						FREE(TmpBitmap.bmBits);
						for (j=0; j<=dwNumberOfMipmapLevels; j++)
						{
							FREE(bm[j].bmBits);
						}
						return FALSE;
					}

					/* Now replace level previous level with the expanded bitmap */
					bm[i-1].bmBitsPixel=	TmpBitmap.bmBitsPixel;
					bm[i-1].bmWidthBytes=	TmpBitmap.bmWidthBytes;
					FREE(bm[i-1].bmBits);
					bm[i-1].bmBits=(unsigned char *)malloc(bm[i-1].bmHeight * bm[i-1].bmWidthBytes);

					/* Copy tmp bitmap to previous level */
					memcpy(bm[i-1].bmBits, TmpBitmap.bmBits, bm[i-1].bmHeight * bm[i-1].bmWidthBytes);
					
					/* Free tmp bitmap */
					FREE(TmpBitmap.bmBits);
				}
			}

			/* Generate next mipmap level using 2x2 box mipmapping */
			if (!CreateNextMipmapLevel2x2(&bm[i-1],  (lpTranslucentNames ? &bmTrans[i-1] : NULL),
										  &bm[i],    (lpTranslucentNames ? &bmTrans[i] : NULL)))
			{
				OutputDebugString("D3DTTextureReadMipmapBMP : CreateNextMipmapLevel2x2() failed.\n");
				RELEASE(*lplpDDSSystemMemorySurface);
				for (j=0; j<=dwNumberOfMipmapLevels; j++)
				{
					if (lpTranslucentNames) FREE(bmTrans[j].bmBits);
					FREE(bm[j].bmBits);
				}
				return FALSE;
			}
		}
	}

	/* We now have all mipmap data into our array */

	/* Initialise surface pointer */
	lpDDSCurrentMemorySurface=(*lplpDDSSystemMemorySurface);
	
	/* Copy each mipmaps into mipmap surface */
	for (i=0; i<dwNumberOfMipmapLevels; i++)
	{
		/* Copy bitmap data into texture system memory surface */
		switch(eTextureFormat)
		{
		case RGBA :			/* Copy RGB bitmap to surface */
							bCopyOK=CopyBitmapToRGBASurface(lpDDSCurrentMemorySurface, &bm[i], lpTranslucentNames ? &bmTrans[i] : NULL); break;
		case PAL4 :
		case PAL8 :			/* Copy RGB or palettised bitmap to palettised surface */
							bCopyOK=CopyBitmapToPALSurface(lpDDSCurrentMemorySurface, &bm[i], PaletteEntries); break;
		
							/* Copy RGB bitmap to Bumpmap surface */
		case BUMPMAP :		bCopyOK=CopyBitmapToBumpMapSurface(lpDDSCurrentMemorySurface, &bm[i]); break;
		
		case LUMA :			/* Copy RGB bitmap to Luminance surface */
							bCopyOK=CopyBitmapToLuminanceSurface(lpDDSCurrentMemorySurface, &bm[i], lpTranslucentNames ? &bmTrans[i] : NULL); break;
		
		case FOURCC_YUV :	/* Convert RGB bitmap to YUV format */
							bCopyOK=CopyBitmapToYUVSurface(lpDDSCurrentMemorySurface, &bm[i]);	break;
		
		case FOURCC_DXT :	/* Convert RGB bitmap to DXT format */
							bCopyOK=CopyBitmapToDXTSurface(lpDD4, lpDDSCurrentMemorySurface, &bm[i], lpTranslucentNames ? &bmTrans[i] : NULL); break;
		
		default :			/* Unknown type! How can this be ? */
							OutputDebugString("D3DTTextureReadMipmapBMP : Unknown type\n");
							bCopyOK=FALSE;
		}

		/* See if copy was done correctly */
		if (!bCopyOK)
		{
			OutputDebugString("D3DTTextureReadMipmapBMP : Failed to convert bitmap to texture surface\n");
			RELEASE(*lplpDDSSystemMemorySurface);
			for (j=0; j<=dwNumberOfMipmapLevels; j++)
			{
				if (lpTranslucentNames) FREE(bmTrans[j].bmBits);
				FREE(bm[j].bmBits);
			}
			return FALSE;
		}

		/* Get next mipmap surface */
		ZeroMemory(&ddsCaps, sizeof(DDSCAPS2));
		ddsCaps.dwCaps=DDSCAPS_TEXTURE | DDSCAPS_MIPMAP;
		hres=lpDDSCurrentMemorySurface->lpVtbl->GetAttachedSurface(lpDDSCurrentMemorySurface, &ddsCaps, &lpDDSCurrentMemorySurface);
		if (hres!=DD_OK && (i<dwNumberOfMipmapLevels))
		{
			sprintf(pszString, "D3DTTextureReadMipmapBMP : Failed to get mipmap level %d.\n", i);
			OutputDebugString(pszString);
			RELEASE(*lplpDDSSystemMemorySurface);
			for (j=0; j<=dwNumberOfMipmapLevels; j++)
			{
				if (lpTranslucentNames) FREE(bmTrans[j].bmBits);
				FREE(bm[j].bmBits);
			}
			return FALSE;
		}
	}

	/* Free bitmap array */
	for (j=0; j<=dwNumberOfMipmapLevels; j++)
	{
		if (lpTranslucentNames) FREE(bmTrans[j].bmBits);
		FREE(bm[j].bmBits);
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
 *					  If the BMP file is 4 or 8-bit palettised, then the texture format
 *					  must also be 4 or 8-bit palettised.
 *					- *lplpDDSSystemMemorySurface is a pointer pointing to the address
 *					  of the resulting SYSTEM MEMORY texture.
 *
 *******************************************************************************/
BOOL D3DTTextureReadBMP(LPDIRECTDRAW4 lpDD4, LPDIRECT3DDEVICE3 lpDev3, 
						char *lpName, char *lpTranslucentName,
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
	DDSCAPS2				ddsCaps;
	LPDIRECTDRAWPALETTE		lpDDPPalette=NULL;
	PALETTEENTRY			PaletteEntries[256];
	TextureType				eTextureFormat=RGBA;
	HBITMAP					hBitmap, hBitmapTrans;
	BITMAP					bm, bmTrans, bmExpanded;
	BITMAP					*lpbmIn=NULL, *lpbmTransIn=NULL;
	BITMAP					*lpbmOut=NULL, *lpbmTransOut=NULL;
	DWORD					dwNumberOfEntries, dwNumberOfMipmapLevels, dwMemoryUsedByTexture=0;
	BYTE					r, g, b, a, i;
	BOOL					bTranslucent=FALSE;
	BOOL					bSupportAlphaTexturing=FALSE;
	BOOL					bSupportNonSquareTextures=FALSE;
	BOOL					bSupportMipmapping=FALSE;
	BOOL					bCopyOK=FALSE;
	char					pszString[256];
	
	/* Perform various checking */

	/* Check that parameters are valid */
	if (!lpDD4 || !lpddPixelFormat || !lpName || !lplpDDSSystemMemorySurface ||
		eAutoMipmap<0 || eAutoMipmap>13)
	{
		OutputDebugString("D3DTTextureReadBMP : Bad parameters\n");
		return FALSE;
	}

	/* Are we using a translucent texture format ? */
	if (lpddPixelFormat->dwFlags & DDPF_ALPHAPIXELS)
	{
		bTranslucent=TRUE;
	}

	/* Are we using special FOURCC codes for the texture format ? */
	if (lpddPixelFormat->dwFlags & DDPF_FOURCC)
	{
		switch(lpddPixelFormat->dwFourCC)
		{
			case MAKEFOURCC('Y', 'U', 'Y', '2') :
			case MAKEFOURCC('U', 'Y', 'V', 'Y') : eTextureFormat=FOURCC_YUV; break;
			case MAKEFOURCC('D', 'X', 'T', '5') :
			case MAKEFOURCC('D', 'X', 'T', '4') : 
			case MAKEFOURCC('D', 'X', 'T', '3') :
			case MAKEFOURCC('D', 'X', 'T', '2') : bTranslucent=TRUE;
			case MAKEFOURCC('D', 'X', 'T', '1') : eTextureFormat=FOURCC_DXT; break;
			default :	OutputDebugString("D3DTTextureReadBMP : Unknown FOURCC code\n");
						return FALSE;
		}
	}

	/* Is texture a bump map format ? */
	if (lpddPixelFormat->dwFlags & (DDPF_BUMPDUDV | DDPF_BUMPLUMINANCE))
	{
		eTextureFormat=BUMPMAP;
	}

	/* Is texture a luminance format ? */
	if (lpddPixelFormat->dwFlags & DDPF_LUMINANCE)
	{
		eTextureFormat=LUMA;
	}

	/* Is texture a 4 or 8 bits palettised texture ? */
	if (lpddPixelFormat->dwFlags & DDPF_PALETTEINDEXED4)
	{
		eTextureFormat=PAL4;
	}
	if (lpddPixelFormat->dwFlags & DDPF_PALETTEINDEXED8)
	{
		eTextureFormat=PAL8;
	}

	/* If a translucent name is submitted to the function, check that a valid
	   translucent format is used */
	if (lpTranslucentName && !bTranslucent)
	{
		OutputDebugString("D3DTTextureReadBMP : Select a translucent format for a translucent texture!\n");
		return FALSE;
	}

	/* If a translucent format is used with no translucent information, warn the user */
	if (!lpTranslucentName && bTranslucent)
	{
		OutputDebugString("D3DTTextureReadBMP : WARNING! Alpha format used but no translucent bitmap submitted\n");
	}

	/* Initialise D3DDEVICEDESC structures */
	ZeroMemory(&ddHAL, sizeof(D3DDEVICEDESC));
	ZeroMemory(&ddHEL, sizeof(D3DDEVICEDESC));
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
		OutputDebugString("D3DTTextureReadBMP : 3D Device does not support mipmapping : mipmapping turned OFF\n");
		eAutoMipmap=0;
	}


	/* Load texture into BITMAP : first try to load from resource */
	hBitmap=(HBITMAP)LoadImage(GetModuleHandle(NULL), lpName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
    if (hBitmap==NULL)
	{
		/* Load from file */
		hBitmap=(HBITMAP)LoadImage(NULL, lpName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (hBitmap==NULL)
		{
			sprintf(pszString, "D3DTTextureReadBMP : File %s not found\n", lpName);
			OutputDebugString(pszString);
			return FALSE;
		}
	}
	
	/* If translucent, then also read the file lpTranslucentName */
	if (lpTranslucentName)
	{
		/* Load translucent texture : first try to load from resource */
		hBitmapTrans=(HBITMAP)LoadImage(GetModuleHandle(NULL), lpTranslucentName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
		if (hBitmapTrans==NULL)
		{
			/* Load from file */
			hBitmapTrans=(HBITMAP)LoadImage(NULL, lpTranslucentName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			if (hBitmapTrans==NULL)
			{
				sprintf(pszString, "D3DTTextureReadBMP : File %s not found\n", lpTranslucentName);
				OutputDebugString(pszString);
				DeleteObject(hBitmap);
				return FALSE;
			}
		}
	}


	/* Get bitmap description */
    GetObject(hBitmap, sizeof(bm), &bm);
	if (lpTranslucentName) GetObject(hBitmapTrans, sizeof(bmTrans), &bmTrans);
	
	/* If translucent texture has also been loaded, check that both 
	   widths and heights are equal and that the bit depth is the same */
	if (lpTranslucentName)
	{
		if (bm.bmWidth!=bmTrans.bmWidth || bm.bmHeight!=bmTrans.bmHeight || bm.bmBitsPixel!=bmTrans.bmBitsPixel)
		{
			/* Bitmap and translucent bitmap have different types */
			OutputDebugString("D3DTTextureReadBMP : Bitmap and translucent bitmap have different types.\n");
			DeleteObject(hBitmap);
			DeleteObject(hBitmapTrans);
			lplpDDSSystemMemorySurface=NULL;
			return FALSE;
		}
	}

	/* Is texture requested as 4 bits palettised ? */
	if (eTextureFormat==PAL4)
	{
		/* Yes, check that the bitmap loaded is a 4-bit bitmap */
		if (bm.bmBitsPixel!=4)
		{
			OutputDebugString("D3DTTextureReadBMP : A 4-bit palettised bitmap must be used to create a 4-bit palettised texture\n");
			DeleteObject(hBitmap);
			return FALSE;
		}
	}
	/* Is texture requested as 8 bits palettised ? */
	else if (eTextureFormat==PAL8)
	{
		/* Yes, check that the bitmap loaded is an 8-bit bitmap */
		if (bm.bmBitsPixel!=8)
		{
			OutputDebugString("D3DTTextureReadBMP : A 8-bit palettised bitmap must be used to create an 8-bit palettised texture\n");
			DeleteObject(hBitmap);
			return FALSE;
		}
	}
	else
	{
		/* Texture is not requested as palettised, so check that a 
		   normal 24-bits bitmap has been loaded */
		if (bm.bmBitsPixel!=24)
		{
			OutputDebugString("D3DTTextureReadBMP : The bmp file must be in 24 bits format for an RGBA texture type\n");
			DeleteObject(hBitmap);
			if (lpTranslucentName) DeleteObject(hBitmapTrans);
			return FALSE;
		}
	}

	/* Check that width and height are equal for devices that only support SQUARE textures */
	if (!bSupportNonSquareTextures)
	{
		if (bm.bmWidth!=bm.bmHeight)
		{
			OutputDebugString("D3DTTextureReadBMP : Device does not support non-square textures\n");
			DeleteObject(hBitmap);
			DeleteObject(hBitmapTrans);
			return FALSE;
		}
		if (lpTranslucentName)
		{
			if (bmTrans.bmWidth!=bmTrans.bmHeight)
			{	
				OutputDebugString("D3DTTextureReadBMP : Device does not support non-square textures\n");
				DeleteObject(hBitmap);
				DeleteObject(hBitmapTrans);
				return FALSE;
			}
		}
	}

	/* Check that the Fourier mipmapping method is not required 
	   for rectangular textures (not supported) */
	if (eAutoMipmap>2 && bm.bmWidth!=bm.bmHeight)
	{
		OutputDebugString("D3DTTextureReadBMP : Fourier MipMapping require SQUARE textures.\n");
		OutputDebugString("D3DTTextureReadBMP : Using 2x2 MipMapping instead.\n");
		eAutoMipmap=1;
	}


	/* For normal RGBA textures, get the number of bits
	   for each channel Red, Green, Blue and Alpha (if translucent) */
	if (eTextureFormat==RGBA)
	{
		GetPixelFormatInfo(lpddPixelFormat, &r, &g, &b, &a,
											NULL, NULL, NULL, NULL, 
											NULL, NULL, NULL, NULL);
	}

	
	/* Dithering for RGBA texture only */
	if (bDither && eTextureFormat==RGBA)
	{
		if (lpddPixelFormat->dwRGBBitCount>16)
		{
			OutputDebugString("D3DTTextureReadBMP : No need to dither 24 or 32 bits textures\n");
		}
		else
		{
			OutputDebugString("D3DTTextureReadBMP : Dithering texture\n");
			DitherBitmap(bm.bmWidth, bm.bmHeight, lpddPixelFormat, bm.bmBits, lpTranslucentName ? bmTrans.bmBits : NULL);
		}
	}
	
	/* Calculate memory used by texture */
	if (eAutoMipmap)
	{
		int		x = bm.bmWidth;
		int		y = bm.bmHeight;

		while (x && y)
		{
			dwMemoryUsedByTexture+=(x * y * lpddPixelFormat->dwRGBBitCount)/8;
			x>>=1;
			y>>=1;
		}
	}
	else
	{
		dwMemoryUsedByTexture=(bm.bmWidth * bm.bmHeight * lpddPixelFormat->dwRGBBitCount)/8;
	}
	

	/* Debug info about texture */
	sprintf(pszString, "\nD3DTTextureReadBMP : Loading %s texture : %s (%u*%u) %.2f KBytes\n", 
						bTranslucent ? "translucent" : "", lpName, bm.bmWidth, bm.bmHeight, dwMemoryUsedByTexture/1024.0f);
	OutputDebugString(pszString);
	switch(eTextureFormat)
	{
	case RGBA :		sprintf(pszString, "D3DTTextureReadBMP : Texture format = %d%d%d%d\n", r, g, b, a); break;
	case PAL4 :		sprintf(pszString, "D3DTTextureReadBMP : Texture format = 4-bit palettised\n"); break;
	case PAL8 :		sprintf(pszString, "D3DTTextureReadBMP : Texture format = 8-bit palettised\n"); break;
	case LUMA :		sprintf(pszString, "D3DTTextureReadBMP : Texture format = Luminance format\n"); break;
	case BUMPMAP :	sprintf(pszString, "D3DTTextureReadBMP : Texture format = BumpMap format\n"); break;
	case FOURCC_YUV:	switch(lpddPixelFormat->dwFourCC)
						{
							case MAKEFOURCC('Y', 'U', 'Y', '2') : sprintf(pszString, "D3DTTextureReadBMP : Texture format = FOURCC YUY2\n"); break;
							case MAKEFOURCC('U', 'Y', 'V', 'Y') : sprintf(pszString, "D3DTTextureReadBMP : Texture format = FOURCC UYVY\n"); break;
							default : sprintf(pszString, "D3DTTextureReadBMP : Texture format = Unknown YUV FOURCC code\n");
						}
						break;
	case FOURCC_DXT:
						switch(lpddPixelFormat->dwFourCC)
						{
							case MAKEFOURCC('D', 'X', 'T', '1') : sprintf(pszString, "D3DTTextureReadBMP : Texture format = FOURCC DXT1\n"); break;
							case MAKEFOURCC('D', 'X', 'T', '2') : sprintf(pszString, "D3DTTextureReadBMP : Texture format = FOURCC DXT2\n"); break;
							case MAKEFOURCC('D', 'X', 'T', '3') : sprintf(pszString, "D3DTTextureReadBMP : Texture format = FOURCC DXT3\n"); break;
							case MAKEFOURCC('D', 'X', 'T', '4') : sprintf(pszString, "D3DTTextureReadBMP : Texture format = FOURCC DXT4\n"); break;
							case MAKEFOURCC('D', 'X', 'T', '5') : sprintf(pszString, "D3DTTextureReadBMP : Texture format = FOURCC DXT5\n"); break;
							default : sprintf(pszString, "D3DTTextureReadBMP : Texture format = Unknown DXT FOURCC code\n");
						}
						break;
	default :			sprintf(pszString, "D3DTTextureReadBMP : Texture format = Unknown\n");
	}
	OutputDebugString(pszString);
	
	/* If texture is translucent, compute transparent pixel colors.
	   This is needed to avoid "color bleeding" when bilinearing or
	   mipmapping a transparent texture */
	if (lpTranslucentName)
	{
		OutputDebugString("D3DTTextureReadBMP : Computing transparent pixels...\n");
		ComputeTransparentPixels(&bm, &bmTrans);
	}

	
	/* Set the fields of the DirectDraw Surface Description */
    ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
    ddsd.dwSize=sizeof(DDSURFACEDESC2);
    ddsd.dwFlags=DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PIXELFORMAT;
    ddsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE | DDSCAPS_SYSTEMMEMORY;
	
	/* YUV textures can only be created in video memory (don't ask) */
	if (eTextureFormat==FOURCC_YUV)
	{
		ddsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE | DDSCAPS_VIDEOMEMORY;
	}

    if (eAutoMipmap)
	{
		ddsd.ddsCaps.dwCaps|=DDSCAPS_MIPMAP | DDSCAPS_COMPLEX;
	}
	ddsd.dwWidth=bm.bmWidth;
	ddsd.dwHeight=bm.bmHeight;
	ddsd.ddpfPixelFormat=*lpddPixelFormat;

	/* Create surface */
	hres=lpDD4->lpVtbl->CreateSurface(lpDD4, &ddsd, lplpDDSSystemMemorySurface, NULL);
	if (hres!=DD_OK) 
	{
		OutputDebugString("D3DTTextureReadBMP : Failed to create system memory surface\n");
		DeleteObject(hBitmap);
		if (lpTranslucentName) DeleteObject(hBitmapTrans);
		return FALSE;
	}

	/* If texture is palettised, create a palette for the texture */
    if (eTextureFormat==PAL4 || eTextureFormat==PAL8)
    {
        /* How many indices in palette ? */
		if (eTextureFormat==PAL4) dwNumberOfEntries=16;
			else dwNumberOfEntries=256;

		/* Create palette from bitmap */
		if (!PaletteFromBitmap(lpDD4, hBitmap, PaletteEntries))
		{
			OutputDebugString("D3DTTextureReadBMP : PaletteFromBitmap() failed\n");
		}

		/* Create a DirectDraw palette for the texture. */
		if (eTextureFormat==PAL4)
		{
			hres=lpDD4->lpVtbl->CreatePalette(lpDD4, DDPCAPS_4BIT, PaletteEntries, &lpDDPPalette, NULL);
		}
		else
		{
			hres=lpDD4->lpVtbl->CreatePalette(lpDD4, DDPCAPS_8BIT | DDPCAPS_ALLOW256, PaletteEntries, &lpDDPPalette, NULL);
		}
		if (hres!=DD_OK)
		{
			OutputDebugString("D3DTTextureReadBMP : CreatePalette() failed\n");
			return FALSE;
		}

        /* Attach the palette to the surface */
		hres=(*lplpDDSSystemMemorySurface)->lpVtbl->SetPalette((*lplpDDSSystemMemorySurface), lpDDPPalette);
		if (hres!=DD_OK)
		{
			OutputDebugString("D3DTTextureReadBMP : SetPalette() failed\n");
			RELEASE(*lplpDDSSystemMemorySurface);
			DeleteObject(hBitmap);
			if (lpTranslucentName) DeleteObject(hBitmapTrans);
			return FALSE;
		}
    }

	/* Copy bitmap data into texture system memory surface */
	switch(eTextureFormat)
	{
	case RGBA :			/* Copy RGB bitmap to surface */
						bCopyOK=CopyBitmapToRGBASurface((*lplpDDSSystemMemorySurface), &bm, lpTranslucentName ? &bmTrans : NULL); break;
	case PAL4 :
	case PAL8 :			/* Copy RGB bitmap to palettised surface */
						bCopyOK=CopyBitmapToPALSurface((*lplpDDSSystemMemorySurface), &bm, NULL); break;
	
	case LUMA :			/* Copy RGB bitmap to Luminance surface */
						bCopyOK=CopyBitmapToLuminanceSurface((*lplpDDSSystemMemorySurface), &bm, lpTranslucentName ? &bmTrans : NULL); break;
	
						/* Copy RGB bitmap to Bumpmap surface */
	case BUMPMAP :		bCopyOK=CopyBitmapToBumpMapSurface((*lplpDDSSystemMemorySurface), &bm); break;
	
	case FOURCC_YUV :	/* Convert RGB bitmap to YUV format */
						bCopyOK=CopyBitmapToYUVSurface((*lplpDDSSystemMemorySurface), &bm);	break;
	
	case FOURCC_DXT :	/* Convert RGB bitmap to DXT format */
						bCopyOK=CopyBitmapToDXTSurface(lpDD4, (*lplpDDSSystemMemorySurface), &bm, lpTranslucentName ? &bmTrans : NULL); break;
	
	default :			/* Unknown type! How can this be ? */
						OutputDebugString("D3DTTextureReadBMP : Unknown type\n");
						bCopyOK=FALSE;
	}

	/* See if copy was done correctly */
	if (!bCopyOK)
	{
		OutputDebugString("D3DTTextureReadBMP : Failed to convert bitmap to texture surface\n");
		RELEASE(*lplpDDSSystemMemorySurface);
		DeleteObject(hBitmap);
		if (lpTranslucentName) DeleteObject(hBitmapTrans);
		return FALSE;
	}

	/* Auto-mipmapping has been requested, so create all mipmap levels */
	if (eAutoMipmap)
	{
		/* With box filters, each mipmap level is computed from the previous one */
		if (eAutoMipmap<3)
		{
			/* Create all mipmap levels for this texture */

			/* Find out how many mipmap levels have to be created.
			   It depends on the texture size. At the same time,
			   check that texture size is a power of 2 */
			switch(min(bm.bmWidth, bm.bmHeight))
			{
				case 2048 :	dwNumberOfMipmapLevels=11; break;
				case 1024 :	dwNumberOfMipmapLevels=10; break;
				case 512 :	dwNumberOfMipmapLevels=9; break;
				case 256:	dwNumberOfMipmapLevels=8; break;
				case 128:	dwNumberOfMipmapLevels=7; break;
				case 64:	dwNumberOfMipmapLevels=6; break;
				case 32:	dwNumberOfMipmapLevels=5; break;
				case 16:	dwNumberOfMipmapLevels=4; break;
				case 8:		dwNumberOfMipmapLevels=3; break;
				case 4:		dwNumberOfMipmapLevels=2; break;
				case 2:		dwNumberOfMipmapLevels=1; break;
				case 1:		OutputDebugString("D3DTTextureReadBMP : No mipmap level needed for a texture size of 1\n");
							RELEASE(*lplpDDSSystemMemorySurface);
							DeleteObject(hBitmap);
							if (lpTranslucentName) DeleteObject(hBitmapTrans);
							return TRUE; break;
				default :	OutputDebugString("D3DTTextureReadBMP  : Texture size is not a power of 2\n");
							RELEASE(*lplpDDSSystemMemorySurface);
							DeleteObject(hBitmap);
							if (lpTranslucentName) DeleteObject(hBitmapTrans);
							return FALSE;
			}

			/* Initialise first level mipmap */
			lpbmIn=&bm;
			if (lpTranslucentName) lpbmTransIn=&bmTrans;

			/* Surface initialisation */
			lpDDSCurrentMemorySurface=(*lplpDDSSystemMemorySurface);

			/* Initialise pointer */
			bmExpanded.bmBits=NULL;

			/* Special case for palettised bitmap : expand it to 24 bit RGB bitmap */
			if (eTextureFormat==PAL4 || eTextureFormat==PAL8)
			{
				/* Create the structure for expanded bitmap */
				bmExpanded.bmType =		bm.bmType;
				bmExpanded.bmWidth =	bm.bmWidth;
				bmExpanded.bmHeight =	bm.bmHeight;
				bmExpanded.bmWidthBytes=3 * bm.bmWidth;
				if (bmExpanded.bmWidthBytes % 4) bmExpanded.bmWidthBytes += 4 - (bmExpanded.bmWidthBytes % 4);
				bmExpanded.bmPlanes =	bm.bmPlanes;
				bmExpanded.bmBitsPixel =24;
				bmExpanded.bmBits = (unsigned char *)malloc(bmExpanded.bmHeight * bmExpanded.bmWidthBytes);

				/* Copy palettised bitmap to 24 bits bitmap */
				if (!CopyPALBitmapToRGBBitmap(&bm, PaletteEntries, &bmExpanded))
				{
					OutputDebugString("D3DTTextureReadBMP : Failed to copy palettised bitmap to a 24 bits bitmap\n");
					FREE(bmExpanded.bmBits);
					RELEASE(*lplpDDSSystemMemorySurface);
					DeleteObject(hBitmap);
					return FALSE;
				}

				/* Our source pointer is now the expanded bitmap */
				lpbmIn=&bmExpanded;
			}
			

			/* Create all mipmap levels */
			for (i=1; i<=dwNumberOfMipmapLevels; i++)
			{
				/* Initialise out bitmaps */
				lpbmOut=(BITMAP *)malloc(sizeof(BITMAP));
				lpbmOut->bmType=lpbmIn->bmType;
				lpbmOut->bmWidth=max(1, lpbmIn->bmWidth/2);
				lpbmOut->bmHeight=max(1, lpbmIn->bmHeight/2);
				lpbmOut->bmWidthBytes=3 * lpbmOut->bmWidth ;
				if (lpbmOut->bmWidthBytes % 4) lpbmOut->bmWidthBytes+=4 - (lpbmOut->bmWidthBytes % 4);
				lpbmOut->bmPlanes=lpbmIn->bmPlanes;
				lpbmOut->bmBitsPixel=lpbmIn->bmBitsPixel;
				lpbmOut->bmBits=(unsigned char *)malloc(lpbmOut->bmHeight * lpbmOut->bmWidthBytes);
				if (!lpbmOut->bmBits)
				{
					OutputDebugString("D3DTTextureReadBMP : Not enough memory to allocate bitmap\n");
					RELEASE(*lplpDDSSystemMemorySurface);
					DeleteObject(hBitmap);
					if (lpTranslucentName) DeleteObject(hBitmapTrans);
					return FALSE;
				}
				if (lpTranslucentName)
				{
					lpbmTransOut=(BITMAP *)malloc(sizeof(BITMAP));
					lpbmTransOut->bmType=lpbmTransIn->bmType;
					lpbmTransOut->bmWidth=max(1, lpbmTransIn->bmWidth/2);
					lpbmTransOut->bmHeight=max(1, lpbmTransIn->bmHeight/2);
					lpbmTransOut->bmWidthBytes=3 * lpbmTransOut->bmWidth ;
					if (lpbmTransOut->bmWidthBytes % 4) lpbmTransOut->bmWidthBytes+=4 - (lpbmTransOut->bmWidthBytes % 4);
					lpbmTransOut->bmPlanes=lpbmTransIn->bmPlanes;
					lpbmTransOut->bmBitsPixel=lpbmTransIn->bmBitsPixel;
					lpbmTransOut->bmBits=(unsigned char *)malloc(lpbmTransOut->bmHeight * lpbmTransOut->bmWidthBytes);
					if (!lpbmOut->bmBits)
					{
						OutputDebugString("D3DTTextureReadBMP : Not enough memory to allocate bitmap\n");
						RELEASE(*lplpDDSSystemMemorySurface);
						DeleteObject(hBitmap);
						if (lpTranslucentName) DeleteObject(hBitmapTrans);
						return FALSE;
					}
				}
				
				if (eAutoMipmap==D3DTAutoMipmap_2by2)
				{
					/* Create next mipmap level using 2x2 box mipmapping */
					if (!CreateNextMipmapLevel2x2(lpbmIn,  (lpTranslucentName ? lpbmTransIn : NULL),
												  lpbmOut, (lpTranslucentName ? lpbmTransOut : NULL)))
					{
						OutputDebugString("D3DTTextureReadBMP : CreateNextMipmapLevel2x2() failed.\n");
						RELEASE(*lplpDDSSystemMemorySurface);
						DeleteObject(hBitmap);
						if (lpTranslucentName) DeleteObject(hBitmapTrans);
						return FALSE;
					}
				}
				else
				{
					/* Create next mipmap level using 4x4 weighted box mipmapping */
					if (!CreateNextMipmapLevel4x4(lpbmIn,  (lpTranslucentName ? lpbmTransIn : NULL),
												  lpbmOut, (lpTranslucentName ? lpbmTransOut : NULL)))
					{
						OutputDebugString("D3DTTextureReadBMP : CreateNextMipmapLevel4x4() failed.\n");
						RELEASE(*lplpDDSSystemMemorySurface);
						DeleteObject(hBitmap);
						if (lpTranslucentName) DeleteObject(hBitmapTrans);
						return FALSE;
					}
				}

				/* Get next mipmap */
				ZeroMemory(&ddsCaps, sizeof(DDSCAPS2));
				ddsCaps.dwCaps=DDSCAPS_TEXTURE | DDSCAPS_MIPMAP;
				hres=lpDDSCurrentMemorySurface->lpVtbl->GetAttachedSurface(lpDDSCurrentMemorySurface, &ddsCaps, &lpDDSCurrentMemorySurface);
				if (hres!=DD_OK)
				{
					sprintf(pszString, "D3DTTextureReadBMP : Failed to get mipmap level %d.\n", i);
					OutputDebugString(pszString);
					RELEASE(*lplpDDSSystemMemorySurface);
					DeleteObject(hBitmap);
					if (lpTranslucentName) DeleteObject(hBitmapTrans);
					return FALSE;
				}

				/* Now copy bitmap data for current mipmap level 
				   into texture system memory surface */
				switch(eTextureFormat)
				{
				case RGBA :			/* Copy RGB bitmap to surface */
									bCopyOK=CopyBitmapToRGBASurface(lpDDSCurrentMemorySurface, lpbmOut, lpTranslucentName ? lpbmTransOut : NULL); break;
				case PAL4 :
				case PAL8 :			/* Copy RGB or palettised bitmap to surface */
									bCopyOK=CopyBitmapToPALSurface(lpDDSCurrentMemorySurface, lpbmOut, 
																   (eTextureFormat==PAL4 || eTextureFormat==PAL8) ? PaletteEntries : NULL); break;
				
									/* Copy RGB bitmap to Bumpmap surface */
				case BUMPMAP :		bCopyOK=CopyBitmapToBumpMapSurface(lpDDSCurrentMemorySurface, lpbmOut); break;

				case LUMA :			/* Copy RGB bitmap to Luminance surface */
									bCopyOK=CopyBitmapToLuminanceSurface(lpDDSCurrentMemorySurface, lpbmOut, lpTranslucentName ? lpbmTransOut : NULL); break;
				
				case FOURCC_YUV :	/* Convert RGB bitmap to YUV format */
									bCopyOK=CopyBitmapToYUVSurface(lpDDSCurrentMemorySurface, lpbmOut); break;
				
				case FOURCC_DXT :	/* Convert RGB bitmap to DXT format */
									bCopyOK=CopyBitmapToDXTSurface(lpDD4, lpDDSCurrentMemorySurface, lpbmOut, lpTranslucentName ? lpbmTransOut : NULL); break;
				
				default :			/* Unknown type! How can this be ? */
									OutputDebugString("D3DTTextureReadBMP : Unknown type\n");
									bCopyOK=FALSE;
				}

				/* Next level */
				if (i!=1)
				{
					/* Free memory of previous mipmap level */
					if (lpbmIn) FREE(lpbmIn->bmBits);
					FREE(lpbmIn);
					if (lpTranslucentName)
					{
						if (lpbmTransIn) FREE(lpbmTransIn->bmBits);
						FREE(lpbmTransIn);
					}
				}

				/* Check that copy as done correctly */
				if (!bCopyOK)
				{
					sprintf(pszString, "D3DTTextureReadBMP : Failed to copy bitmap onto mipmap level %d\n", i);
					OutputDebugString(pszString);
					if (lpbmOut) FREE(lpbmOut->bmBits);
					FREE(lpbmOut);
					if (lpTranslucentName)
					{
						if (lpbmTransOut) FREE(lpbmTransOut->bmBits);
						FREE(lpbmTransOut);
					}
					RELEASE(*lplpDDSSystemMemorySurface);
					DeleteObject(hBitmap);
					if (lpTranslucentName) DeleteObject(hBitmapTrans);
					return FALSE;
				}

				/* Our new IN bitmap is the current OUT */
				lpbmIn=lpbmOut;
				if (lpTranslucentName) lpbmTransIn=lpbmTransOut;
			}

			/* Free remaining memory */
			if (lpbmOut) FREE(lpbmOut->bmBits);
			FREE(lpbmOut);
			if (lpTranslucentName)
			{
				if (lpbmTransOut) FREE(lpbmTransOut->bmBits);
				FREE(lpbmTransOut);
			}

			/* If we have created an expanded bitmap, then destroy it */
			if (eTextureFormat==PAL4 || eTextureFormat==PAL8)
			{
				FREE(bmExpanded.bmBits);
			}
		}
		else
		{
			/* Mipmap levels computed with the Fourier method require the full bitmap data */
			if (!CreateFourierMipmapLevels(lpDD4, lpDev3, 
										   &bm, lpTranslucentName ? &bmTrans : NULL,
										   (*lplpDDSSystemMemorySurface), (eAutoMipmap-3)*2))
			{
				OutputDebugString("D3DTTextureReadBMP : CreateFourierMipmapLevels() failed.\n");
				RELEASE(*lplpDDSSystemMemorySurface);
				DeleteObject(hBitmap);
				if (lpTranslucentName) DeleteObject(hBitmapTrans);
				return FALSE;
			}
		}
	}

	/* Delete bitmap(s) as we don't need them anymore (copy has been done) */
	DeleteObject(hBitmap);
	if (lpTranslucentName) DeleteObject(hBitmapTrans);

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
								   char *lpName,
								   eD3DTAutoMipmapType eAutoMipmap,
								   D3DCOLOR dwTransparentColor,
								   DDPIXELFORMAT *lpddPixelFormat,
								   LPDIRECTDRAWSURFACE4 *lplpDDSSystemMemorySurface)
{
	HRESULT					hres;
	LPDIRECTDRAWSURFACE4	lpDDSCurrentMemorySurface=NULL;
	DDSURFACEDESC2			ddsd;
	D3DDEVICEDESC			ddHAL, ddHEL, *lpD3DDeviceDesc;
	TextureType				eTextureFormat=RGBA;
	DDSCAPS2				ddsCaps;
	HBITMAP					hBitmap;
	BITMAP					bm, bmTrans;
	BITMAP					*lpbmIn=NULL, *lpbmTransIn=NULL;
	BITMAP					*lpbmOut=NULL, *lpbmTransOut=NULL;
	DWORD					dwMemoryUsedByTexture=0, dwNumberOfMipmapLevels=0;
	BYTE					*pReadByte, *pWriteByte;
	BYTE					R, G, B, r, g, b, a;
	BOOL					bSupportAlphaTexturing=FALSE;
	BOOL					bSupportNonSquareTextures=FALSE;
	BOOL					bSupportMipmapping=FALSE;
	BOOL					bCopyOK;
	int						nTranslucentDXT=0;
	int						i, j;
	char					pszString[300];
	
	/* Perform various checking */

	/* Check that parameters are valid */
	if (!lpDD4 || !lpddPixelFormat || !lpName || !lplpDDSSystemMemorySurface ||
		eAutoMipmap<0 || eAutoMipmap>13)
	{
		OutputDebugString("D3DTTextureReadTransparentBMP : Bad parameters\n");
		return FALSE;
	}

	/* Are we using special FOURCC codes for the texture format ? */
	if (lpddPixelFormat->dwFlags & DDPF_FOURCC)
	{
		switch(lpddPixelFormat->dwFourCC)
		{
			case MAKEFOURCC('D', 'X', 'T', '5') : 
			case MAKEFOURCC('D', 'X', 'T', '4') : 
			case MAKEFOURCC('D', 'X', 'T', '3') : 
			case MAKEFOURCC('D', 'X', 'T', '2') : eTextureFormat=FOURCC_DXT; break;
		}
	}

	/* Is texture a luminance format ? */
	if (lpddPixelFormat->dwFlags & DDPF_LUMINANCE)
	{
		eTextureFormat=LUMA;
	}

	/* Are we using a translucent texture format as required ? */
	if (!(lpddPixelFormat->dwFlags & DDPF_ALPHAPIXELS) && (eTextureFormat!=FOURCC_DXT))
	{
		OutputDebugString("D3DTTextureReadTransparentBMP : A translucent texture format must be used\n");
		return FALSE;
	}

	/* Initialise D3DDEVICEDESC structures */
	ZeroMemory(&ddHAL, sizeof(D3DDEVICEDESC));
	ZeroMemory(&ddHEL, sizeof(D3DDEVICEDESC));
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
		OutputDebugString("D3DTTextureReadTransparentBMP : 3D Device does not support mipmapping : mipmapping turned OFF\n");
		eAutoMipmap=0;
	}


	/* Load texture into BITMAP : first try to load from resource */
	hBitmap=(HBITMAP)LoadImage(GetModuleHandle(NULL), lpName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
    if (hBitmap==NULL)
	{
		/* Load from file */
		hBitmap=(HBITMAP)LoadImage(NULL, lpName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (hBitmap==NULL)
		{
			sprintf(pszString, "D3DTTextureReadTransparentBMP : File %s not found\n", lpName);
			OutputDebugString(pszString);
			return FALSE;
		}
	}

	/* Get bitmap description */
    GetObject(hBitmap, sizeof(bm), &bm);
	
	/* Check that a normal 24-bits bitmap has been loaded */
	if (bm.bmBitsPixel!=24)
	{
		OutputDebugString("D3DTTextureReadTransparentBMP : The bmp file must be in 24 bits format for an RGBA texture type\n");
		DeleteObject(hBitmap);
		return FALSE;
	}

	/* Check that width and height are equal for devices that only support SQUARE textures */
	if (!bSupportNonSquareTextures)
	{
		if (bm.bmWidth!=bm.bmHeight)
		{
			OutputDebugString("D3DTTextureReadTransparentBMP : Device does not support non-square textures\n");
			DeleteObject(hBitmap);
			return FALSE;
		}
	}

	/* Create a bitmap structure containing the alpha information for the texture */
	bmTrans.bmType=			bm.bmType;
	bmTrans.bmWidth=		bm.bmWidth;
	bmTrans.bmHeight=		bm.bmHeight;
	bmTrans.bmWidthBytes=	bm.bmWidthBytes;
	bmTrans.bmPlanes=		bm.bmPlanes;
	bmTrans.bmBitsPixel=	bm.bmBitsPixel;
	bmTrans.bmBits=(unsigned char *)calloc(bm.bmHeight * bm.bmWidthBytes, sizeof(BYTE));

	/* Copy translucent information into bmTrans */
	/* Loop through y values from top to bottom */
	for (i=0; i<bm.bmHeight; i++)
	{
		/* Get pointers for current line */
		pReadByte =  (BYTE *)bm.bmBits      + i * bm.bmWidthBytes;
		pWriteByte = (BYTE *)bmTrans.bmBits + i * bmTrans.bmWidthBytes + 2;		

		/* Look through x values from right to left */
		for (j=0; j<bm.bmWidth; j++)
		{ 
			/* Get R, G, B values (always 8-bit each, as the bitmap is 24-bit) */
			B = *pReadByte++;
			G = *pReadByte++;
			R = *pReadByte++;
																			
			/* Is pixel the transparent color ? */
			if (RGB_MAKE(R, G, B)!=dwTransparentColor)
			{
				/* Yes, so mark the pixel as completely opaque */
				*pWriteByte=255;
			}

			/* Increment pointer */
			pWriteByte+=3;
		}
	}

	/* Check that the Fourier mipmapping method is not required 
	   for rectangular textures (not supported) */
	if (eAutoMipmap>2 && bm.bmWidth!=bm.bmHeight)
	{
		OutputDebugString("D3DTTextureReadTransparentBMP : Fourier MipMapping require SQUARE textures.\n");
		OutputDebugString("D3DTTextureReadTransparentBMP : Using 2x2 MipMapping instead.\n");
		eAutoMipmap=1;
	}

	/* For normal textures (non-palettised), get the number of bits
	   for each channel Red, Green, Blue and Alpha (if translucent) */
	GetPixelFormatInfo(lpddPixelFormat, &r, &g, &b, &a,
										NULL, NULL, NULL, NULL, 
										NULL, NULL, NULL, NULL);


	/* Calculate memory used by texture */
	if (eAutoMipmap)
	{
		int x=bm.bmWidth;
		int y=bm.bmHeight;

		while (x && y)
		{
			dwMemoryUsedByTexture+=(x * y * lpddPixelFormat->dwRGBBitCount)/8;
			x>>=1;
			y>>=1;
		}
	}
	else
	{
		dwMemoryUsedByTexture=(bm.bmWidth * bm.bmHeight * lpddPixelFormat->dwRGBBitCount)/8;
	}
	

	/* Debug info about texture */
	sprintf(pszString, "\nD3DTTextureReadTransparentBMP : Loading %s texture : (%u*%u) %.2f KBytes\n", 
						lpName, bm.bmWidth, bm.bmHeight, dwMemoryUsedByTexture/1024.0f);
	OutputDebugString(pszString);
	switch(eTextureFormat)
	{
	case RGBA :		sprintf(pszString, "D3DTTextureReadTransparentBMP : Texture format = %d%d%d%d\n", r, g, b, a); break;
	case LUMA :		sprintf(pszString, "D3DTTextureReadTransparentBMP : Texture format = Luminance Alpha format\n"); break;
	case FOURCC_DXT:
						switch(lpddPixelFormat->dwFourCC)
						{
							case MAKEFOURCC('D', 'X', 'T', '2') : sprintf(pszString, "D3DTTextureReadTransparentBMP : Texture format = FOURCC DXT2\n"); break;
							case MAKEFOURCC('D', 'X', 'T', '3') : sprintf(pszString, "D3DTTextureReadTransparentBMP : Texture format = FOURCC DXT3\n"); break;
							case MAKEFOURCC('D', 'X', 'T', '4') : sprintf(pszString, "D3DTTextureReadTransparentBMP : Texture format = FOURCC DXT4\n"); break;
							case MAKEFOURCC('D', 'X', 'T', '5') : sprintf(pszString, "D3DTTextureReadTransparentBMP : Texture format = FOURCC DXT5\n"); break;
							default : sprintf(pszString, "D3DTTextureReadTransparentBMP : Texture format = Unknown DXT FOURCC code\n");
						}
						break;
	default :			sprintf(pszString, "D3DTTextureReadTransparentBMP : Texture format = Unknown\n");
	}
	OutputDebugString(pszString);

	/* Compute transparent pixels for texture */
	ComputeTransparentPixels(&bm, &bmTrans);

	
	/* Set the fields of the DirectDraw Surface Description */
    ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
    ddsd.dwSize=sizeof(DDSURFACEDESC2);
    ddsd.dwFlags=DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    ddsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE | DDSCAPS_SYSTEMMEMORY;
    if (eAutoMipmap)
	{
		ddsd.ddsCaps.dwCaps|=DDSCAPS_MIPMAP | DDSCAPS_COMPLEX;
	}
	ddsd.dwWidth=bm.bmWidth;
	ddsd.dwHeight=bm.bmHeight;
	ddsd.ddpfPixelFormat=*lpddPixelFormat;

	/* Create surface */
	hres=lpDD4->lpVtbl->CreateSurface(lpDD4, &ddsd, lplpDDSSystemMemorySurface, NULL);
	if (hres!=DD_OK) 
	{
		OutputDebugString("D3DTTextureReadTransparentBMP : Failed to create system memory surface\n");
		FREE(bmTrans.bmBits);
		DeleteObject(hBitmap);
		return FALSE;
	}

	/* Copy bitmap data into texture system memory surface */
	switch(eTextureFormat)
	{
	case RGBA :			/* Copy RGB bitmap to surface */
						bCopyOK=CopyBitmapToRGBASurface((*lplpDDSSystemMemorySurface), &bm, &bmTrans); break;
	
	case LUMA :			/* Copy RGB bitmap to Luminance surface */
						bCopyOK=CopyBitmapToLuminanceSurface((*lplpDDSSystemMemorySurface), &bm, &bmTrans); break;
	
	case FOURCC_DXT :	/* Convert RGB bitmap to DXT format */
						bCopyOK=CopyBitmapToDXTSurface(lpDD4, (*lplpDDSSystemMemorySurface), &bm, &bmTrans); break;
	
	default :			/* Unknown type! How can this be ? */
						OutputDebugString("D3DTTextureReadTransparentBMP : Unknown type\n");
						bCopyOK=FALSE;
	}

	/* See if copy was done correctly */
	if (!bCopyOK)
	{
		OutputDebugString("D3DTTextureReadTransparentBMP : Failed to convert bitmap to texture surface\n");
		FREE(bmTrans.bmBits);
		RELEASE(*lplpDDSSystemMemorySurface);
		DeleteObject(hBitmap);
		return FALSE;
	}


	/* Auto-mipmapping has been requested, so create all mipmap levels */
	if (eAutoMipmap)
	{
		/* With box filters, each mipmap level is computed from the previous one */
		if (eAutoMipmap<3)
		{
			/* Create all mipmap levels for this texture */

			/* Find out how many mipmap levels have to be created.
			   It depends on the texture size. At the same time,
			   check that texture size is a power of 2 */
			switch(min(bm.bmWidth, bm.bmHeight))
			{
				case 2048 :	dwNumberOfMipmapLevels=11; break;
				case 1024 :	dwNumberOfMipmapLevels=10; break;
				case 512 :	dwNumberOfMipmapLevels=9; break;
				case 256:	dwNumberOfMipmapLevels=8; break;
				case 128:	dwNumberOfMipmapLevels=7; break;
				case 64:	dwNumberOfMipmapLevels=6; break;
				case 32:	dwNumberOfMipmapLevels=5; break;
				case 16:	dwNumberOfMipmapLevels=4; break;
				case 8:		dwNumberOfMipmapLevels=3; break;
				case 4:		dwNumberOfMipmapLevels=2; break;
				case 2:		dwNumberOfMipmapLevels=1; break;
				case 1:		OutputDebugString("D3DTTextureReadTransparentBMP : No mipmap level needed for a texture size of 1\n");
							FREE(bmTrans.bmBits);
							DeleteObject(hBitmap);
							return TRUE; break;
				default :	OutputDebugString("D3DTTextureReadTransparentBMP  : Texture size is not a power of 2\n");
							FREE(bmTrans.bmBits);
							DeleteObject(hBitmap);
							return FALSE;
			}

			/* Initialise first level mipmap */
			lpbmIn=&bm;
			lpbmTransIn=&bmTrans;

			/* Surface initialisation */
			lpDDSCurrentMemorySurface=(*lplpDDSSystemMemorySurface);


			/* Create all mipmap levels */
			for (i=1; i<=(int)dwNumberOfMipmapLevels; i++)
			{
				/* Initialise out bitmaps */
				lpbmOut=(BITMAP *)malloc(sizeof(BITMAP));
				lpbmOut->bmType=lpbmIn->bmType;
				lpbmOut->bmWidth=max(1, lpbmIn->bmWidth/2);
				lpbmOut->bmHeight=max(1, lpbmIn->bmHeight/2);
				lpbmOut->bmWidthBytes=3 * lpbmOut->bmWidth ;
				if (lpbmOut->bmWidthBytes % 4) lpbmOut->bmWidthBytes+=4 - (lpbmOut->bmWidthBytes % 4);
				lpbmOut->bmPlanes=lpbmIn->bmPlanes;
				lpbmOut->bmBitsPixel=lpbmIn->bmBitsPixel;
				lpbmOut->bmBits=(unsigned char *)malloc(lpbmOut->bmHeight * lpbmOut->bmWidthBytes);
				if (!lpbmOut->bmBits)
				{
					OutputDebugString("D3DTTextureReadBMP : Not enough memory to allocate bitmap\n");
					RELEASE(*lplpDDSSystemMemorySurface);
					FREE(bmTrans.bmBits);
					DeleteObject(hBitmap);
					return FALSE;
				}
				
				lpbmTransOut=(BITMAP *)malloc(sizeof(BITMAP));
				lpbmTransOut->bmType=lpbmTransIn->bmType;
				lpbmTransOut->bmWidth=max(1, lpbmTransIn->bmWidth/2);
				lpbmTransOut->bmHeight=max(1, lpbmTransIn->bmHeight/2);
				lpbmTransOut->bmWidthBytes=3 * lpbmTransOut->bmWidth ;
				if (lpbmTransOut->bmWidthBytes % 4) lpbmTransOut->bmWidthBytes+=4 - (lpbmTransOut->bmWidthBytes % 4);
				lpbmTransOut->bmPlanes=lpbmTransIn->bmPlanes;
				lpbmTransOut->bmBitsPixel=lpbmTransIn->bmBitsPixel;
				lpbmTransOut->bmBits=(unsigned char *)malloc(lpbmTransOut->bmHeight * lpbmTransOut->bmWidthBytes);
				if (!lpbmOut->bmBits)
				{
					OutputDebugString("D3DTTextureReadBMP : Not enough memory to allocate bitmap\n");
					RELEASE(*lplpDDSSystemMemorySurface);
					FREE(bmTrans.bmBits);
					DeleteObject(hBitmap);
					return FALSE;
				}
				
				if (eAutoMipmap==D3DTAutoMipmap_2by2)
				{
					/* Create next mipmap level using 2x2 box mipmapping */
					if (!CreateNextMipmapLevel2x2(lpbmIn,  lpbmTransIn,
												  lpbmOut, lpbmTransOut))
					{
						OutputDebugString("D3DTTextureReadTransparentBMP : CreateNextMipmapLevel2x2() failed.\n");
						RELEASE(*lplpDDSSystemMemorySurface);
						FREE(bmTrans.bmBits);
						DeleteObject(hBitmap);
						return FALSE;
					}
				}
				else
				{
					/* Create next mipmap level using 4x4 weighted box mipmapping */
					if (!CreateNextMipmapLevel4x4(lpbmIn,  lpbmTransIn,
												  lpbmOut, lpbmTransOut))
					{
						OutputDebugString("D3DTTextureReadBMP : CreateNextMipmapLevel4x4() failed.\n");
						RELEASE(*lplpDDSSystemMemorySurface);
						FREE(bmTrans.bmBits);
						DeleteObject(hBitmap);
						return FALSE;
					}
				}

				/* Get next mipmap */
				ZeroMemory(&ddsCaps, sizeof(DDSCAPS2));
				ddsCaps.dwCaps=DDSCAPS_TEXTURE | DDSCAPS_MIPMAP;
				hres=lpDDSCurrentMemorySurface->lpVtbl->GetAttachedSurface(lpDDSCurrentMemorySurface, &ddsCaps, &lpDDSCurrentMemorySurface);
				if (hres!=DD_OK)
				{
					sprintf(pszString, "D3DTTextureReadBMP : Failed to get mipmap level %d.\n", i);
					OutputDebugString(pszString);
					RELEASE(*lplpDDSSystemMemorySurface);
					FREE(bmTrans.bmBits);
					DeleteObject(hBitmap);
					return FALSE;
				}

				/* Now copy bitmap data for current mipmap level 
				   into texture system memory surface */
				switch(eTextureFormat)
				{
				case RGBA :			/* Copy RGB bitmap to surface */
									bCopyOK=CopyBitmapToRGBASurface(lpDDSCurrentMemorySurface, lpbmOut, lpbmTransOut); break;

				case LUMA :			/* Copy RGB bitmap to Luminance surface */
									bCopyOK=CopyBitmapToLuminanceSurface(lpDDSCurrentMemorySurface, lpbmOut, lpbmTransOut); break;
				
				case FOURCC_DXT :	/* Convert RGB bitmap to DXT format */
									bCopyOK=CopyBitmapToDXTSurface(lpDD4, lpDDSCurrentMemorySurface, lpbmOut, lpbmTransOut); break;
				
				default :			/* Unknown type! How can this be ? */
									OutputDebugString("D3DTTextureReadTransparentBMP : Unknown type\n");
									bCopyOK=FALSE;
				}

				/* Next level */
				if (i!=1)
				{
					/* Free memory of previous mipmap level */
					if (lpbmIn) FREE(lpbmIn->bmBits);
					FREE(lpbmIn);
					if (lpbmTransIn) FREE(lpbmTransIn->bmBits);
					FREE(lpbmTransIn);
				}

				/* Check that copy as done correctly */
				if (!bCopyOK)
				{
					sprintf(pszString, "D3DTTextureReadTransparentBMP : Failed to copy bitmap onto mipmap level %d\n", i);
					OutputDebugString(pszString);
					if (lpbmOut) FREE(lpbmOut->bmBits);
					FREE(lpbmOut);
					if (lpbmTransOut) FREE(lpbmTransOut->bmBits);
					FREE(lpbmTransOut);
					RELEASE(*lplpDDSSystemMemorySurface);
					FREE(bmTrans.bmBits);
					DeleteObject(hBitmap);
					return FALSE;
				}

				/* Our new IN bitmap is the current OUT */
				lpbmIn=lpbmOut;
				lpbmTransIn=lpbmTransOut;
			}

			/* Free remaining memory */
			if (lpbmOut) FREE(lpbmOut->bmBits);
			FREE(lpbmOut);
			if (lpbmTransOut) FREE(lpbmTransOut->bmBits);
			FREE(lpbmTransOut);
		}
		else
		{
			/* Mipmap levels computed with the Fourier method require the full bitmap data */
			if (!CreateFourierMipmapLevels(lpDD4, lpDev3, 
										   &bm, &bmTrans,
										   (*lplpDDSSystemMemorySurface), (eAutoMipmap-3)*2))
			{
				OutputDebugString("D3DTTextureReadTransparentBMP : CreateFourierMipmapLevels() failed.\n");
				RELEASE(*lplpDDSSystemMemorySurface);
				FREE(bmTrans.bmBits);
				DeleteObject(hBitmap);
				return FALSE;
			}
		}
	}

	/* Free memory */
	FREE(bmTrans.bmBits);

	/* Delete bitmap(s) as we don't need them anymore (copy has been done) */
	DeleteObject(hBitmap);

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
	LPDIRECTDRAWPALETTE		lpDDPPalette=NULL;
	DDSCAPS2				ddsCaps;
	DWORD					dwMemoryUsedByTexture, dwFreeTextureMemory;
	DWORD					x, y;
	BOOL					bHardware3DDevice, bMipmap=FALSE, bPalettisedTexture=FALSE, bDXTFormat=FALSE;
	char					pszString[200];

	/* Check parameters */
	if (!lpDD4 || !lpDev3 || !lpDDSSystemMemorySurface)
	{
		OutputDebugString("D3DTTextureUpload : Bad parameters\n");
		(*lplpDDSTextureSurface)=NULL;
		(*lplpD3DTexture2)=NULL;
		return FALSE;
	}

	/* Determine if 3D device is hardware or not */	
	ZeroMemory(&ddHAL, sizeof(D3DDEVICEDESC));
	ZeroMemory(&ddHEL, sizeof(D3DDEVICEDESC));
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
			OutputDebugString("D3D device does not support texturing\n");
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
		OutputDebugString("D3DTTextureUpload : QueryInterface for Texture2 interface failed\n");
		(*lplpDDSTextureSurface)=NULL;
		(*lplpD3DTexture2)=NULL;
		return FALSE;
	}


	/* Get surface description */
	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
	ddsd.dwSize=sizeof(DDSURFACEDESC2);
	hres=lpSrcTextureSurface->lpVtbl->GetSurfaceDesc(lpSrcTextureSurface, &ddsd);
	if (hres!=DD_OK) 
	{
		OutputDebugString("D3DTTextureUpload : GetSurfaceDesc failed\n");
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
		OutputDebugString("D3DTTextureUpload : Texture is mipmapped\n");
		bMipmap=TRUE;
	}

	/* Is texture a palettised texture ? */
	if (ddPixelFormat.dwFlags & (DDPF_PALETTEINDEXED4 | DDPF_PALETTEINDEXED8))
	{
		bPalettisedTexture=TRUE;
	}

	
	/* Calculate memory used by texture */
	dwMemoryUsedByTexture=(x*y*ddPixelFormat.dwRGBBitCount)/8;
	
	/* Check amount of free texture memory */
	ZeroMemory(&ddsCaps, sizeof(DDSCAPS2));
	ddsCaps.dwCaps=DDSCAPS_TEXTURE;
	hres=lpDD4->lpVtbl->GetAvailableVidMem(lpDD4, &ddsCaps, NULL, &dwFreeTextureMemory);
	if (hres!=DD_OK)
	{
		OutputDebugString("D3DTTextureUpload : GetAvailableVidMem failed\n");
	}
	
	/* Check that there is sufficient texture memory to store this texture */
	if (dwFreeTextureMemory<dwMemoryUsedByTexture)
	{
		sprintf(pszString, "D3DTTextureUpload : Not enough memory to store texture.\nFree texture memory=%d  Texture=%d\n",
				dwFreeTextureMemory, dwMemoryUsedByTexture);
		OutputDebugString(pszString);
	}
    
    /* Set the field of surface structure */
	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
    ddsd.dwSize=sizeof(DDSURFACEDESC2);
    ddsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE | DDSCAPS_ALLOCONLOAD;
	if (bUseD3DTextureManagement)
	{
		if ( !(ddPixelFormat.dwFlags & DDPF_FOURCC) || 
			 ( (MAKEFOURCC('U', 'Y', 'V', 'Y')!=ddPixelFormat.dwFourCC) &&
			   (MAKEFOURCC('Y', 'U', 'Y', '2')!=ddPixelFormat.dwFourCC) ) )
		{
			/* Use D3D texture management : cannot set memory type in that case */
			ddsd.ddsCaps.dwCaps2=DDSCAPS2_TEXTUREMANAGE;
		}
		else
		{
			OutputDebugString("D3DTTextureUpload : Can't set TEXTUREMANAGE flag with a YUV texture.\n");
		}
	}
	else
	{
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
	hres=lpDD4->lpVtbl->CreateSurface(lpDD4, &ddsd, lplpDDSTextureSurface, NULL);
	if (hres!=DD_OK) 
	{
		OutputDebugString("D3DTTextureUpload : CreateSurface failed\n");
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
			OutputDebugString("D3DTTextureUpload : GetPalette() failed\n");
			RELEASE(*lplpDDSTextureSurface);
			RELEASE(lpSrcTexture2);
			(*lplpD3DTexture2)=NULL;
			return FALSE;
		}

		/* Decrement reference count of palette (caused by GetPalette) */
		lpDDPPalette->lpVtbl->Release(lpDDPPalette);

		/* Attach palette to surface */
		hres=(*lplpDDSTextureSurface)->lpVtbl->SetPalette((*lplpDDSTextureSurface), lpDDPPalette);
		if (hres!=DD_OK)
		{
			OutputDebugString("D3DTTextureUpload : SetPalette() failed\n");
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
		OutputDebugString("D3DTTextureUpload : QueryInterface for Direct3DTexture2 failed\n");
		RELEASE(*lplpDDSTextureSurface);
		RELEASE(lpSrcTexture2);
		(*lplpD3DTexture2)=NULL;
		return FALSE;
	}
	
	/* Are we using a FOURCC DXT compressed format ? */
	if (ddPixelFormat.dwFlags & DDPF_FOURCC)
	{
		if ( ddPixelFormat.dwFourCC==MAKEFOURCC('D', 'X', 'T', '1') ||
			 ddPixelFormat.dwFourCC==MAKEFOURCC('D', 'X', 'T', '2') ||
			 ddPixelFormat.dwFourCC==MAKEFOURCC('D', 'X', 'T', '3') ||
			 ddPixelFormat.dwFourCC==MAKEFOURCC('D', 'X', 'T', '4') ||
			 ddPixelFormat.dwFourCC==MAKEFOURCC('D', 'X', 'T', '5') )
		{
			bDXTFormat=TRUE;
		}
	}
	
	
	/* Load texture into memory */
	/* The following is a temporary trick to make the LUMINANCE, 
	   BUMPMAP, non-DXT FOURCC and PAL4 texture formats work with RGB or Ref. Rasterizer
	   Basically, since Blt() or Load() fail for these formats,
	   perform a manual copy between the two surfaces (with mipmap levels). */
	if (!bHardware3DDevice && !bDXTFormat && 
		  (ddPixelFormat.dwFlags & (DDPF_LUMINANCE | DDPF_BUMPDUDV | DDPF_PALETTEINDEXED4 | DDPF_FOURCC)) )
	{
		LPDIRECTDRAWSURFACE4	lpDDSSrc, lpDDSDest;
		DDSURFACEDESC2			ddsdSrc, ddsdDest;
		DDSCAPS2				ddsCaps;
				
		OutputDebugString("D3DTTextureUpload : Performing manual copy\n");
		
		/* Initialise surfaces */
		lpDDSSrc=lpDDSSystemMemorySurface;
		lpDDSDest=(*lplpDDSTextureSurface);
		hres=DD_OK;

		/* Look through all attached surfaces in case the texture is mipmapped */
		while (hres==DD_OK)
		{
			/* Initialise ddsdSrc and ddsdDest and ddsCaps */
			ZeroMemory(&ddsdSrc, sizeof(DDSURFACEDESC2));
			ZeroMemory(&ddsdDest, sizeof(DDSURFACEDESC2));
			ddsdSrc.dwSize=sizeof(DDSURFACEDESC2);
			ddsdDest.dwSize=sizeof(DDSURFACEDESC2);
			ZeroMemory(&ddsCaps, sizeof(ddsCaps));

			/* Lock src and dest */
			hres=lpDDSSrc->lpVtbl->Lock(lpDDSSrc, NULL, &ddsdSrc, DDLOCK_READONLY, NULL);
			if (hres!=DD_OK)
			{
				OutputDebugString("Lock failed for source surface\n");
			}
			hres=lpDDSDest->lpVtbl->Lock(lpDDSDest, NULL, &ddsdDest, DDLOCK_WRITEONLY, NULL);
			if (hres!=DD_OK)
			{
				OutputDebugString("Lock failed for destination surface\n");
			}
			
			/* Copy */
			memcpy(ddsdDest.lpSurface, ddsdSrc.lpSurface, ddsdDest.dwHeight*ddsdDest.lPitch);

			/* Unlock dest and src */
			lpDDSDest->lpVtbl->Unlock(lpDDSDest, NULL);
			lpDDSSrc->lpVtbl->Unlock(lpDDSSrc, NULL);

			/* Get next mipmap level (should there be any) */
			ddsCaps.dwCaps=DDSCAPS_TEXTURE | DDSCAPS_MIPMAP;
			hres=lpDDSSrc->lpVtbl->GetAttachedSurface(lpDDSSrc, &ddsCaps, &lpDDSSrc);
			hres|=lpDDSDest->lpVtbl->GetAttachedSurface(lpDDSDest, &ddsCaps, &lpDDSDest);
		}
	}
	else
	{
		hres=(*lplpD3DTexture2)->lpVtbl->Load((*lplpD3DTexture2), lpSrcTexture2);
		if (hres!=DD_OK)
		{
			OutputDebugString("D3DTTextureUpload : Load() failed\n");
			RELEASE(*lplpD3DTexture2);
			RELEASE(*lplpDDSTextureSurface);
			RELEASE(lpSrcTexture2);
			return FALSE;
		}
	}

	/* Release source texture interface */
	RELEASE(lpSrcTexture2);
    	
	/* Debug information */
	ZeroMemory(&ddsCaps, sizeof(DDSCAPS2));
	ddsCaps.dwCaps=DDSCAPS_TEXTURE;
	hres=lpDD4->lpVtbl->GetAvailableVidMem(lpDD4, &ddsCaps, NULL, &dwFreeTextureMemory);
	if (hres!=DD_OK)
	{
		OutputDebugString("D3DTTextureUpload : GetAvailableVidMem failed\n");
	}
	sprintf(pszString, "Free Texture memory = %u\n", dwFreeTextureMemory);
	OutputDebugString(pszString);

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
		OutputDebugString("D3DTTextureBestOpaqueFormat : Texture formats have not been enumerated yet.\nPlease call D3DTTextureListFormats().\n");
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
		OutputDebugString("D3DTTextureBestOpaqueFormat : No opaque format has been found\n");
		return NULL;
	}
			
	/* Return best opaque format */
	return (&D3DTTextureFormat[nBestOpaqueFormat].ddPixelFormat);
}



/*****************************************************************************
 * Function Name  : D3DTTextureBestTranslucentFormat
 * Inputs		  : b16BitsTexture
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
		OutputDebugString("D3DTTextureBestTranslucentFormat : Texture formats have not been enumerated yet.\nPlease call D3DTTextureListFormats().\n");
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
		OutputDebugString("D3DTTextureBestTranslucentFormat : No translucent format has been found\n");
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
		OutputDebugString("D3DTTexturePalettised8BitFormat : Texture formats have not been enumerated yet.\nPlease call D3DTTextureListFormats().\n");
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
		OutputDebugString("D3DTTexturePalettised8BitFormat : No palettised format has been found\n");
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
		D3DTTextureFormat[i].bValidFormat=FALSE;
		ZeroMemory(&D3DTTextureFormat[i].ddPixelFormat, sizeof(DDPIXELFORMAT));
		D3DTTextureFormat[i].b4BitsPalettised=0;
		D3DTTextureFormat[i].b8BitsPalettised=0;
		D3DTTextureFormat[i].bLuminanceFormat=0;
		D3DTTextureFormat[i].bYUVFormat=0;
		D3DTTextureFormat[i].bDXTFormat=0;
		D3DTTextureFormat[i].bBumpMapFormat=0;
		D3DTTextureFormat[i].r=0;
		D3DTTextureFormat[i].g=0;
		D3DTTextureFormat[i].b=0;
		D3DTTextureFormat[i].a=0;
	}
	
	/* Call texture format enumeration function */
	hres=lpDev3->lpVtbl->EnumTextureFormats(lpDev3, EnumTextureFormatsCallback, NULL);
    if (hres!=DD_OK) 
	{
        OutputDebugString("D3DTTextureListFormats : Enumeration of texture formats failed.");
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
		OutputDebugString("D3DTTextureRestoreSurface : Surface is NULL\n");
		return;
	}
	
	/* Get lpLocalDD4 from DirectDrawSurface */
	lpDDSSystemMemorySurface->lpVtbl->GetDDInterface(lpDDSSystemMemorySurface, &lpLocalDD4);

	/* Was texture created with the D3D texture management flag ? */
	ZeroMemory(&ddsCaps, sizeof(ddsCaps));
	lpDDSSystemMemorySurface->lpVtbl->GetCaps(lpDDSSystemMemorySurface, &ddsCaps);
	if (ddsCaps.dwCaps & DDSCAPS2_TEXTUREMANAGE) bUseD3DTextureManagement=TRUE;
	
	/* If texture surface exists, check whether it's lost or not */
	if ((*lplpDDSTextureSurface))
	{
		if ((*lplpDDSTextureSurface)->lpVtbl->IsLost((*lplpDDSTextureSurface))==DDERR_SURFACELOST)
		{
			/* Surface exists, so release it to recreate it afterwards */
			RELEASE((*lplpDDSTextureSurface));
			RELEASE((*lplpD3DTexture2));

			if (!D3DTTextureUpload(lpLocalDD4, lpDev3, 
								   lpDDSSystemMemorySurface, bUseD3DTextureManagement,
								   lplpDDSTextureSurface, lplpD3DTexture2))
			{
				OutputDebugString("D3DTTextureRestoreSurface : D3DTTextureUpload failed\n");
			}
			else
			{
				OutputDebugString("D3DTTextureRestoreSurface : Texture restored\n");
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
 * Function Name  : CopyPALBitmapToRGBBitmap
 * Inputs		  : hBitmap
 * Outputs		  : *pBmOut
 * Input/Output   : lpDDS
 * Returns		  : TRUE or FALSE
 * Global Used    : None
 * Description    : Function that copy a 4 or 8 bits palettised bitmap to a 
 *					24 bits RGB bitmap.
 *					*pBm must be a valid pointer to a 4 or 8 bits BITMAP.
 *					*pPaletteEntries must be a valid pointer to a array of
 *					16 (for 4 bits palettised) or 256 (for 8 bits palettised)
 *					color entries.
 *					pBmOut must be a valid pointer to a BITMAP structure with
 *					the bmBits pointer already allocated to the correct size.
 *
 *******************************************************************************/
BOOL CopyPALBitmapToRGBBitmap(BITMAP *pBm, PALETTEENTRY *pPaletteEntries, BITMAP *pBmOut)
{
	unsigned char	*lp8b, *lpSrcPointer;
	DWORD			x, y, i, j, dwIndex1, dwIndex2;
	BYTE			Byte;
		
	/* Get bitmap dimensions */
	x=pBm->bmWidth;
	y=pBm->bmHeight;
	
	/* Copy process */
	for (i=0; i<y; i++)
	{
		/* Compute source and destination pointers */
		lpSrcPointer=(unsigned char *)pBm->bmBits + i*pBm->bmWidthBytes;
		lp8b=(unsigned char *)pBmOut->bmBits + i*pBmOut->bmWidthBytes;

		/* 4 Bits palettised */
		if (pBm->bmBitsPixel==4)
		{
			/* Look through x values from left to right 
			   (x+1)/2 because x could be an odd number (one, typically) */
			for (j=0; j<((x+1)/2); j++)
			{
				/* Get current pixel index */
				Byte=*lpSrcPointer++;
				dwIndex1=Byte & 0x0F;
				dwIndex2=Byte >> 4;

				/* Write corresponding R, G, B values into 24 bits bitmap */
				*lp8b++=GetBValue(*(DWORD *)&pPaletteEntries[dwIndex2]);
				*lp8b++=GetGValue(*(DWORD *)&pPaletteEntries[dwIndex2]);
				*lp8b++=GetRValue(*(DWORD *)&pPaletteEntries[dwIndex2]);
				*lp8b++=GetBValue(*(DWORD *)&pPaletteEntries[dwIndex1]);
				*lp8b++=GetGValue(*(DWORD *)&pPaletteEntries[dwIndex1]);
				*lp8b++=GetRValue(*(DWORD *)&pPaletteEntries[dwIndex1]);
			}
		}
		else
		{
			/* 8 Bits palettised */
			for (j=0; j<x; j++)
			{
				/* Get current pixel index */
				dwIndex1=*lpSrcPointer++;
				
				/* Write corresponding R, G, B values into 24 bits bitmap */
				*lp8b++=GetBValue(*(DWORD *)&pPaletteEntries[dwIndex1]);
				*lp8b++=GetGValue(*(DWORD *)&pPaletteEntries[dwIndex1]);
				*lp8b++=GetRValue(*(DWORD *)&pPaletteEntries[dwIndex1]);
			}
		}
	}

	/* No problem occured */
	return TRUE;
}


/*******************************************************************************
 * Function Name  : CopyBitmapToRGBASurface
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
BOOL CopyBitmapToRGBASurface(LPDIRECTDRAWSURFACE4 lpDDS, BITMAP *pBm, BITMAP *pBmTrans)
{
	HRESULT			hres;
	DDSURFACEDESC2	ddsd;
	DWORD			x, y, i, j, Mode;
	BYTE			R, G, B, A;
	BYTE			r, g, b, a;
	BYTE			LeftR, LeftG, LeftB, LeftA; 
	BYTE			RightR, RightG, RightB, RightA;
	unsigned char	*lp8b, *lpSrcPointer, *lpTransSrcPointer;
	unsigned short	*lp16b;
	unsigned int	*lp32b;
	
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
		OutputDebugString("CopyBitmapToRGBASurface : Bitmap and surface dimensions do not match. Aborting copy.\n");
		return FALSE;
	}

	/* Get pixel format information */
	GetPixelFormatInfo(&ddsd.ddpfPixelFormat, &r, &g, &b, &a,
											  &LeftR, &LeftG, &LeftB, &LeftA,
											  &RightR, &RightG, &RightB, &RightA);

	/* Copy process starts here */

	/* Compute mode used (8, 16 or 32 bits surface) */
	Mode=ddsd.ddpfPixelFormat.dwRGBBitCount + (pBmTrans ? 1 : 0);
	
	/* Lock texture surface to fill it */
    hres=lpDDS->lpVtbl->Lock(lpDDS, NULL, &ddsd, 0, NULL); 
    if (hres!=DD_OK) 
	{
		OutputDebugString("CopyBitmapToRGBASurface : Failed to lock texture surface\n");
		return FALSE;
	}
	
	/* Loop through y values from top to bottom */
	for (i=0; i<y; i++)
	{
		/* Calculate pointers corresponding to surface format (8, 16 or 32 bits) */
		lp8b  = (unsigned char *) (((unsigned char *)ddsd.lpSurface) + ddsd.lPitch*i);
		lp16b = (unsigned short *)(((unsigned char *)ddsd.lpSurface) + ddsd.lPitch*i);
		lp32b = (unsigned int *)  (((unsigned char *)ddsd.lpSurface) + ddsd.lPitch*i);

		/* Compute source pointer(s) */
		lpSrcPointer=((unsigned char *)pBm->bmBits + i*pBm->bmWidthBytes);
		if (pBmTrans)
		{
			/* Points to the first RED byte value */
			lpTransSrcPointer=((unsigned char *)pBmTrans->bmBits + i*pBmTrans->bmWidthBytes + 2);
		}

		/* Look through x values from left to right */
		for (j=0; j<x; j++)
		{ 
			/* Get R, G, B values (always 8-bit each, as the bitmap is 24-bit) */
			B = *lpSrcPointer++;
			G = *lpSrcPointer++;
			R = *lpSrcPointer++;
			
			/* Which surface format ? */
			switch (Mode)
			{
			case 8: /* 8 Bits Opaque */
					*lp8b++ = (R>>RightR)<<LeftR | (G>>RightG)<<LeftG | (B>>RightB)<<LeftB ;
					break;

			case 9: /* 8 Bits Translucent */
					A = *lpTransSrcPointer;
					lpTransSrcPointer+=3;
					*lp8b++ = (R>>RightR)<<LeftR | (G>>RightG)<<LeftG | (B>>RightB)<<LeftB | (A>>RightA)<<LeftA;
					break;

			case 16:/* 16 Bits Opaque */
					*lp16b++ = (R>>RightR)<<LeftR | (G>>RightG)<<LeftG | (B>>RightB)<<LeftB ;
					break;

			case 17:/* 16 Bits Translucent */
					A = *lpTransSrcPointer;
					lpTransSrcPointer+=3;
					*lp16b++ = (R>>RightR)<<LeftR | (G>>RightG)<<LeftG | (B>>RightB)<<LeftB | (A>>RightA)<<LeftA;
					break;

			case 32:/* 32 Bits Opaque */
					*lp32b++ = (R>>RightR)<<LeftR | (G>>RightG)<<LeftG | (B>>RightB)<<LeftB ;
					break;

			case 33:/* 32 Bits Translucent */
					A = *lpTransSrcPointer;
					lpTransSrcPointer+=3;
					*lp32b++ = (R>>RightR)<<LeftR | (G>>RightG)<<LeftG | (B>>RightB)<<LeftB | (A>>RightA)<<LeftA;
					break;

			default:/* Unknow pixel format : free memory and abort */
					lpDDS->lpVtbl->Unlock(lpDDS, NULL);
					OutputDebugString("CopyBitmapToRGBASurface : Unknown pixel format\n");
					return FALSE;
			}
		}
	}
	
    /* Unlock texture surface because we're done filling it */
	hres=lpDDS->lpVtbl->Unlock(lpDDS, NULL);
	if (hres!=DD_OK)
	{
		OutputDebugString("CopyBitmapToRGBASurface : Unlock() failed\n");
		return FALSE;
	}

	/* No problem occured */
	return TRUE;
}


/*******************************************************************************
 * Function Name  : CopyBitmapToPALSurface
 * Inputs		  : *pBm
 * Input/Output   : lpDDS
 * Returns		  : TRUE or FALSE
 * Global Used    : None
 * Description    : Function that copy a bitmap to a DirectDraw palettized surface.
 *					lpDDS is the adress of a DirectDrawSurface4 ALREADY CREATED.
 *					If the source color depth is in the same format as the 
 *					surface, then a simple copy from the bitmap to the surface 
 *					will take place.
 *					If the source bitmap is 24 bits, then for each pixels the 
 *					closest color index	will be used in the palettised surface.
 *					In that case a palette must have been attached to the surface 
 *					beforehand.
 *					The surface description must exist prior to calling this function.
 *					4 and 8 bits palettised surfaces are supported.
 *					
 *******************************************************************************/
BOOL CopyBitmapToPALSurface(LPDIRECTDRAWSURFACE4 lpDDS, BITMAP *pBm, 
							PALETTEENTRY *pPaletteEntries)
{
	HRESULT				hres;
	DDSURFACEDESC2		ddsd;
	DWORD				dwNumberOfEntries, dwIndex1, dwIndex2;
	DWORD				x, y, i, j;
	BYTE				R, G, B;
	BYTE				Byte, MSBNibble, LSBNibble;
	unsigned char		*lp8b, *lpSrcPointer;
		
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
		OutputDebugString("CopyBitmapToPALSurface : Bitmap and surface dimensions do not match. Aborting copy.\n");
		return FALSE;
	}

	/* If source bitmap is 24 bits, get number of indices in palette */
	if (pBm->bmBitsPixel==24)
	{
		/* Check that a palette was passed */
		if (!pPaletteEntries)
		{
			OutputDebugString("CopyBitmapToPALSurface : A palette must be specified if the source bitmap is 24 bits\n");
			return FALSE;
		}
		
		/* Get number of entries in palette */
		if (ddsd.ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED4) dwNumberOfEntries=16;
			else dwNumberOfEntries=256;
	}


	/* Copy process starts here */

	/* Lock texture surface to fill it */
	hres=lpDDS->lpVtbl->Lock(lpDDS, NULL, &ddsd, 0, NULL); 
	if (hres!=DD_OK) 
	{
		OutputDebugString("CopyBitmapToPALSurface : Failed to lock texture surface\n");
		return FALSE;
	}

	/* If source bitmap is 24 bits color depth, use closest color index to
	   set each pixel's color */
	if (pBm->bmBitsPixel==24)
	{
		/* Loop through y values from top to bottom */
		for (i=0; i<y; i++)
		{
			/* Compute source and destination pointers */
			lpSrcPointer=((unsigned char *)pBm->bmBits + i*pBm->bmWidthBytes);
			lp8b  = (unsigned char *) (((unsigned char *)ddsd.lpSurface) + ddsd.lPitch*i);

			/* 4 bits palettised case */
			if (dwNumberOfEntries==16)
			{
				/* Look through x values from left to right */
				for (j=0; j<((x+1)/2); j++)
				{ 
					/* Get R, G, B values (always 8-bit each, as the bitmap is 24-bit) */
					B = *lpSrcPointer++;
					G = *lpSrcPointer++;
					R = *lpSrcPointer++;

					/* Compute first index */
					dwIndex1=GetClosestIndex(R, G, B, dwNumberOfEntries, pPaletteEntries);

					/* Get next R, G, B values */
					B = *lpSrcPointer++;
					G = *lpSrcPointer++;
					R = *lpSrcPointer++;

					/* Compute second index */
					dwIndex2=GetClosestIndex(R, G, B, dwNumberOfEntries, pPaletteEntries);

					/* Write resulting value (i.e two pixels) in surface */
					*lp8b++=(dwIndex1 & 0x0F) | (dwIndex2<<4);
				}
			}
			else
			{
				/* 8 Bits palettised case */
				/* Look through x values from left to right */
				for (j=0; j<x; j++)
				{ 
					/* Get R, G, B values (always 8-bit each, as the bitmap is 24-bit) */
					B = *lpSrcPointer++;
					G = *lpSrcPointer++;
					R = *lpSrcPointer++;

					/* Write closest index value into surface */
					*lp8b++=GetClosestIndex(R, G, B, dwNumberOfEntries, pPaletteEntries);
				}
			}
		}
	}
	else
	{
		/* Copy 4 bits palettised bitmap to surface : revert byte since 
		   one byte indices two palette entries */
		if (ddsd.ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED4)
		{
			/* Loop through y values from top to bottom */
			for (i=0; i<y; i++)
			{
				/* Compute source and destination pointer for each line */
				lpSrcPointer=((unsigned char *)pBm->bmBits + i*pBm->bmWidthBytes);
				lp8b = (unsigned char *) (((unsigned char *)ddsd.lpSurface) + ddsd.lPitch*i);
				
				/* Look through x values from left to right 
				   (x+1)/2 because x could be an odd number (one, typically) */
				for (j=0; j<(x+1)/2; j++)
				{
					Byte = *lpSrcPointer++;
					MSBNibble=Byte<<4;
					LSBNibble=Byte>>4;
					*lp8b++=MSBNibble | LSBNibble;
				}
			}
		}
		else
		{
			/* Copy 8 bits palettised bitmap to surface : straight memory copy */
			memcpy((unsigned char *)ddsd.lpSurface, (unsigned char *)pBm->bmBits, (x*y*ddsd.ddpfPixelFormat.dwRGBBitCount)/8);
		}
	}

	/* Unlock texture surface because we're done filling it */
	hres=lpDDS->lpVtbl->Unlock(lpDDS, NULL);
	if (hres!=DD_OK)
	{
		OutputDebugString("CopyBitmapToPALSurface : Unlock() failed.\n");
		return FALSE;
	}
	
	/* No problem occured */
	return TRUE;
}


/*******************************************************************************
 * Function Name  : CopyBitmapToLuminanceSurface
 * Inputs		  : *pBm, *pBmTrans
 * Input/Output   : lpDDS
 * Returns		  : TRUE or FALSE
 * Global Used    : None
 * Description    : Function that copy a bitmap to a Luminance DirectDraw surface.
 *					lpDDS is the adress of a DirectDrawSurface4 ALREADY CREATED.
 *					If pBmTrans is non-NULL, then the RED channel contained in 
 *					this bitmap will be used to create the alpha 
 *					channel of the DirectDraw surface.
 *					Basically a greyscale of the bitmap data will be stored
 *					into the Luminance texture surface.
 *					This function assumes that an 8 bit Luminance or 16 bits (88)
 *					Luminance-Alpha	format is used.
 *					Greyscale is computed using the formula :
 *					L = (0.299*R + 0.587*G + 0.114*B).
 *					If the image is already B&W, then of course the color channels
 *					have an equal weight.
 *
 *******************************************************************************/
BOOL CopyBitmapToLuminanceSurface(LPDIRECTDRAWSURFACE4 lpDDS, BITMAP *pBm, BITMAP *pBmTrans)
{
	HRESULT			hres;
	DDSURFACEDESC2	ddsd;
	DWORD			x, y, i, j;
	BYTE			R, G, B, A, L;
	BOOL			bColoredImage=FALSE;
	float			fR, fG, fB;
	unsigned char	*lp8b, *lpSrcPointer, *lpTransSrcPointer;
		
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
		OutputDebugString("CopyBitmapToLuminanceSurface : Bitmap and surface dimensions do not match. Aborting copy.\n");
		return FALSE;
	}

	/* Check that 8 bits Luminance format is used for opaque (L=8),
	   and 16 bits is used for translucent (LA=88) */
	if (pBmTrans && ddsd.ddpfPixelFormat.dwLuminanceBitCount!=16)
	{
		OutputDebugString("CopyBitmapToLuminanceSurface : Luminance Alpha must be coded on 16 bits. Aborting copy.\n");
		return FALSE;
	}
	if (!pBmTrans && ddsd.ddpfPixelFormat.dwLuminanceBitCount!=8)
	{
		OutputDebugString("CopyBitmapToLuminanceSurface : Luminance must be coded on 8 bits. Aborting copy.\n");
		return FALSE;
	}

	/* Determine if the image is already in black and white */
	for (i=0; (i<y && !bColoredImage); i++)
	{
		/* Compute source pointer */
		lpSrcPointer=((unsigned char *)pBm->bmBits + i*pBm->bmWidthBytes);

		for (j=0; j<x; j++)
		{
			/* Get all three color channels */
			B = *lpSrcPointer++;
			G = *lpSrcPointer++;
			R = *lpSrcPointer++;

			/* If the color channels are different, then image is NOT B&W */
			if (!(R==G && R==B)) 
			{
				bColoredImage=TRUE;
				break;
			}
		}
	}

	/* Set coefficients for a color or B&W image */
	if (bColoredImage)
	{
		fR=0.299f;
		fG=0.587f;
		fB=0.114f;
	}
	else
	{
		OutputDebugString("CopyBitmapToLuminanceSurface : black & white image used\n");
		fR=0.333f;
		fG=0.333f;
		fB=0.333f;
	}


	/* Copy process start */

	/* Lock texture surface to fill it */
    hres=lpDDS->lpVtbl->Lock(lpDDS, NULL, &ddsd, 0, NULL); 
    if (hres!=DD_OK) 
	{
		OutputDebugString("CopyBitmapToLuminanceSurface : Failed to lock texture surface\n");
		return FALSE;
	}
	
	/* Loop through y values from top to bottom */
	for (i=0; i<y; i++)
	{
		/* Calculate destination pointer */
		lp8b  = (unsigned char *) (((unsigned char *)ddsd.lpSurface) + ddsd.lPitch*i);
		
		/* Compute source pointer(s) */
		lpSrcPointer=((unsigned char *)pBm->bmBits + i*pBm->bmWidthBytes);
		if (pBmTrans)
		{
			/* Points to the first RED byte value */
			lpTransSrcPointer=((unsigned char *)pBmTrans->bmBits + i*pBmTrans->bmWidthBytes + 2);
		}

		/* Look through x values from left to right */
		for (j=0; j<x; j++)
		{ 
			/* Get R, G, B values (always 8-bit each, as the bitmap is 24-bit) */
			B = *lpSrcPointer++;
			G = *lpSrcPointer++;
			R = *lpSrcPointer++;

			/* Compute luminance (greyscale of RGB) */
			L=(BYTE)(fR*R + fG*G + fB*B);
			
			/* Write luminance into surface */
			*lp8b++ = L;
			
			/* If translucent, also write alpha value */
			if (pBmTrans)
			{
				A = *lpTransSrcPointer;
				lpTransSrcPointer += 3;
				*lp8b++ = A;
			}
		}
	}
	
    /* Unlock texture surface because we're done filling it */
	hres=lpDDS->lpVtbl->Unlock(lpDDS, NULL);
	if (hres!=DD_OK)
	{
		OutputDebugString("CopyBitmapToLuminanceSurface : Unlock() failed\n");
		return FALSE;
	}

	/* No problem occured */
	return TRUE;
}


/*******************************************************************************
 * Function Name  : CopyBitmapToYUVSurface
 * Inputs		  : *pBm
 * Input/Output   : lpDDS
 * Returns		  : TRUE or FALSE
 * Global Used    : None
 * Description    : Function that copy a bitmap to a DirectDraw YUV surface.
 *					lpDDS is the adress of a DirectDrawSurface4 ALREADY CREATED.
 *					The YUV format is stored in the FOURCC code of the texture
 *					surface.
 *
 *******************************************************************************/
BOOL CopyBitmapToYUVSurface(LPDIRECTDRAWSURFACE4 lpDDS, BITMAP *pBm)
{
    DDSURFACEDESC2		ddsd;
	HRESULT				hres;
	DWORD				dwWidth, dwHeight;
	DWORD				i, j;
	BYTE				*lp8b, *lpSrcPointer;
	BYTE				R, B, G, Y0, Y1, U, V;

	/* Get width and height of bitmap */
	dwWidth=pBm->bmWidth;
	dwHeight=pBm->bmHeight;

	/* Get surface description */
	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
    ddsd.dwSize=sizeof(DDSURFACEDESC2);
	lpDDS->lpVtbl->GetSurfaceDesc(lpDDS, &ddsd);

	/* Check if bitmap and surface dimensions are equal */
	if (ddsd.dwWidth!=dwWidth || ddsd.dwHeight!=dwHeight)
	{
		OutputDebugString("CopyBitmapToYUVSurface : Bitmap and surface dimensions do not match. Aborting copy.\n");
		return FALSE;
	}

	/* Lock texture surface to fill it */
	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
	ddsd.dwSize=sizeof(DDSURFACEDESC2);
    hres=lpDDS->lpVtbl->Lock(lpDDS, NULL, &ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);
    if (hres!=DD_OK) 
	{
		OutputDebugString("CopyBitmapToYUVSurface : Failed to lock texture surface\n");
		return FALSE;
	}

	/* Special case for 1x1 (last level mipmap) */
	if (dwWidth==1 && dwHeight==1)
	{
		/* compute source pointer */
		lpSrcPointer = (unsigned char *)pBm->bmBits;
		
		/* Get RGB of single pixel */
		B = *lpSrcPointer++;
		G = *lpSrcPointer++;
		R = *lpSrcPointer++;
		
		/* Write a single RGB 565 pixel in destination surface */
		(*(unsigned short *)ddsd.lpSurface)=  ( (unsigned short)(R & 0xF8) << 8 ) |
											  ( (unsigned short)(G & 0xFC) << 3 ) |
											  ( (unsigned short)(B & 0xF8) >> 3 );
	}
	else
	{
		/* Normal case */

		/* Loop through y values from top to bottom */
		for (i=0; i<dwHeight; i++)
		{
			/* Compute source and destination pointers */
			lpSrcPointer = (unsigned char *)pBm->bmBits +	 i*pBm->bmWidthBytes;
			lp8b =		   (unsigned char *)ddsd.lpSurface + i*(2*dwWidth);

			/* Look through x values from left to right */
			for (j=0; j<dwWidth; j+=2)
			{
				/* Get RGB of first pixel */
				B = *lpSrcPointer++;
				G = *lpSrcPointer++;
				R = *lpSrcPointer++;

				/* Compute Y0 and U for first pixel */
				Y0= (BYTE)(0.29*R + 0.57*G + 0.14*B);
				U= (BYTE)(128.0 - 0.14*R - 0.29*G + 0.43*B);

				/* Get RGB of second pixel */
				B = *lpSrcPointer++;
				G = *lpSrcPointer++;
				R = *lpSrcPointer++;

				/* Compute Y1 and V for second pixel */
				Y1= (BYTE)(0.29*R + 0.57*G + 0.14*B);
				V= (BYTE)(128.0 + 0.36*R - 0.29*G - 0.07*B);

				/* Write YUV values corresponding to FOURCC code */
				switch (ddsd.ddpfPixelFormat.dwFourCC)
				{
					case MAKEFOURCC('Y','U','Y','2'): 
						*lp8b++	  = Y0;
						*lp8b++	  = U;
						*lp8b++	  = Y1;
						*lp8b++	  = V;
						break;
					case MAKEFOURCC('U','Y','V','Y'): 
						*lp8b++	  = U;
						*lp8b++	  = Y0;
						*lp8b++	  = V;
						*lp8b++	  = Y1;
						break;
				}
			}
		}
	}
	
    /* Unlock texture surface because we're done filling it */
	hres=lpDDS->lpVtbl->Unlock(lpDDS, NULL);
	if (hres!=DD_OK)
	{
		OutputDebugString("CopyBitmapToYUVSurface  : Unlock() failed\n");
		return FALSE;
	}

	/* No problem occured */
	return TRUE;
}


/*******************************************************************************
 * Function Name  : CopyBitmapToDXTSurface
 * Inputs		  : lpDD4, *pBm, *pBmTrans
 * Input/Output   : lpDDS
 * Returns		  : TRUE or FALSE
 * Global Used    : None
 * Description    : Function that copy a bitmap to a DXT texture surface.
 *					lpDDS is the adress of a DXT DirectDrawSurface4 ALREADY CREATED.
 *					Both bitmap and surface must be a multiple of four pixels in
 *					width and height.
 *					The DXT data creation is done in two steps :
 *					1) Create a dummy texture surface that will load the contents
 *					of the bitmap into the surface using a common RGB(A) format.
 *					2) Perform a Blt() to copy the contents of the RGB(A) dummy 
 *					surface into the compressed surface. DirectDraw will perform the
 *					compression automatically. 
 *
 *******************************************************************************/
BOOL CopyBitmapToDXTSurface(LPDIRECTDRAW4 lpDD4, LPDIRECTDRAWSURFACE4 lpDDS, 
							BITMAP *pBm, BITMAP *pBmTrans)
{
	LPDIRECTDRAWSURFACE4	lpDDSUncompressed;
	DDSURFACEDESC2			ddsd;
	HRESULT					hres;
	DWORD					x, y;
		
	/* Get width and height of bitmap */
	x=pBm->bmWidth;
	y=pBm->bmHeight;

	/* First, create a dummy surface on which to load the bitmap */
	
	/* Set the fields of the DirectDraw Surface Description */
    ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
    ddsd.dwSize=sizeof(DDSURFACEDESC2);
    ddsd.dwFlags=DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PIXELFORMAT;
    ddsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE | DDSCAPS_SYSTEMMEMORY;
    ddsd.dwWidth=x;
	ddsd.dwHeight=y;
	ZeroMemory(&ddsd.ddpfPixelFormat, sizeof(DDPIXELFORMAT));
	ddsd.ddpfPixelFormat.dwSize=sizeof(DDPIXELFORMAT);
	
	if (pBmTrans)
	{
		/* Use 8888 format for temporary translucent surface */
		ddsd.ddpfPixelFormat.dwFlags=DDPF_RGB | DDPF_ALPHAPIXELS;
		ddsd.ddpfPixelFormat.dwRGBBitCount=32;
		ddsd.ddpfPixelFormat.dwRBitMask=0x00FF0000;
		ddsd.ddpfPixelFormat.dwGBitMask=0x0000FF00;
		ddsd.ddpfPixelFormat.dwBBitMask=0x000000FF;
		ddsd.ddpfPixelFormat.dwRGBAlphaBitMask=0xFF000000;
	}
	else
	{
		/* Use 888 format for temporary opaque surface */
		ddsd.ddpfPixelFormat.dwFlags=DDPF_RGB;
		ddsd.ddpfPixelFormat.dwRGBBitCount=32;
		ddsd.ddpfPixelFormat.dwRBitMask=0x00FF0000;
		ddsd.ddpfPixelFormat.dwGBitMask=0x0000FF00;
		ddsd.ddpfPixelFormat.dwBBitMask=0x000000FF;
	}

	/* Create dummy surface */
	hres=lpDD4->lpVtbl->CreateSurface(lpDD4, &ddsd, &lpDDSUncompressed, NULL);
	if (hres!=DD_OK) 
	{
		OutputDebugString("CopyBitmapToDXTSurface : Failed to create system memory surface\n");
		return FALSE;
	}

	/* Now load RGB bitmap into this surface */
	if (!CopyBitmapToRGBASurface(lpDDSUncompressed, pBm, pBmTrans))
	{
		OutputDebugString("CopyBitmapToDXTSurface : Failed to copy bitmap to system memory surface\n");
		RELEASE(lpDDSUncompressed);
		return FALSE;
	}

	/* Now Blt this uncompressed surface to the compressed DXT surface.
	   DirectDraw will automatically take care of the compression. */
	hres=lpDDS->lpVtbl->Blt(lpDDS, NULL, lpDDSUncompressed, NULL, DDBLT_WAIT, NULL);
	if (hres!=DD_OK)
	{
		OutputDebugString("CopyBitmapToDXTSurface : Blt() failed\n");
		RELEASE(lpDDSUncompressed);
		return FALSE;
	}

	/* Release dummy surface (we don't need it anymore) */
	RELEASE(lpDDSUncompressed);

	/* No problem occured */
	return TRUE;
}


/*******************************************************************************
 * Function Name  : CopyBitmapToBumpMapSurface
 * Inputs		  : *pBm
 * Input/Output   : lpDDS
 * Returns		  : TRUE or FALSE
 * Global Used    : None
 * Description    : Function that copy a bitmap to a Bump Map DirectDraw surface.
 *					lpDDS is the adress of a DirectDrawSurface4 ALREADY CREATED.
 *					This function will read the height map from the bitmap and
 *					generate the DU, DV and possibly L values for the bump map.
 *					This function was adapted from the DirectX 6.0 SDK bumpmap
 *					example.
 *					Note : weird signed/unsigned problems with iDu and iDv.
 *
 *******************************************************************************/
BOOL CopyBitmapToBumpMapSurface(LPDIRECTDRAWSURFACE4 lpDDS, BITMAP *pBm)
{
	DDSURFACEDESC2			ddsd;
	HRESULT					hres;
	DWORD					x, y, i, j, Mode;
	WORD					uL, wValue;
	unsigned char			*lp8b, *lpSrcPointer, *lpSrcPointerNL;
	int						v00, v10, v01, iDu, iDv;
		
	/* Get width and height of bitmap */
	x=pBm->bmWidth;
	y=pBm->bmHeight;

	/* Lock texture surface to fill it */
	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
	ddsd.dwSize=sizeof(DDSURFACEDESC2);
    hres=lpDDS->lpVtbl->Lock(lpDDS, NULL, &ddsd, 0, NULL); 
    if (hres!=DD_OK) 
	{
		OutputDebugString("CopyBitmapToBumpMapSurface : Failed to lock texture surface\n");
		return FALSE;
	}

	/* Compute mode used */
	Mode = ddsd.ddpfPixelFormat.dwBumpBitCount + 
		   ((ddsd.ddpfPixelFormat.dwFlags & DDPF_BUMPLUMINANCE) ? 100 : 0);

	/* Loop through y values from top to bottom */
	for (i=0; i<y; i++)
	{
		/* Calculate pointer corresponding to surface format */
		lp8b  = (unsigned char *) (((unsigned char *)ddsd.lpSurface) + ddsd.lPitch*i);
				
		/* Compute source pointers */
		lpSrcPointer = (unsigned char *)pBm->bmBits + i*pBm->bmWidthBytes;
		lpSrcPointerNL = lpSrcPointer + pBm->bmWidthBytes;

		/* Avoid going past the last line of bitmap data */
		if (i == y-1) 
		{
			lpSrcPointerNL=lpSrcPointer;
			x-=1;
		}
		
		/* Look through x values from left to right */
		for (j=0; j<x; j++)
		{ 
			/* Get current pixel, right pixel and pixel one line below */
			v00 = *lpSrcPointer;
			v01 = *(lpSrcPointer + 3);
			v10 = *(lpSrcPointerNL);
			
			/* Compute DeltaU, DeltaV bump values plus Luminance */
			iDu = v00 - v01;
			iDv = v00 - v10;
			uL  = 255;

			// This is specific to the earth bitmap,
			// to make the land masses less shiny
			// TEMP
			if( v00 > 120 )
			{
				uL = 128;
			}

			/* Write values into bumpmap surface */
			switch(Mode) 
            {
				/* Bumpmap 16 bits format with no luminance (U8V8) */
				case 16 :	*lp8b++ = (unsigned char)iDu;
							*lp8b++ = (unsigned char)iDv;
							break;

				/* Bumpmap 16 bits format with luminance (U5V5L6) */
				case 116 :	wValue=   ( (iDu >> 3) & 0x1F ) | 
								    ( ( (iDv >> 3) & 0x1F ) << 5 ) | 
									( ( (uL  >> 2) & 0x3F ) << 10 );
							*(WORD *)lp8b = wValue;
							lp8b+=2;
							break;

				/* Bumpmap 24 bits format with luminance (U8V8L8) */
				case 124 :	*lp8b++ = (unsigned char)iDu;
							*lp8b++ = (unsigned char)iDv;
							*lp8b++ = (unsigned char)uL;
							break;

				default :	/* Unknown bump map format : unlock surface and exit */
							OutputDebugString("CopyBitmapToBumpMapSurface : Unknown bump map format\n");
							lpDDS->lpVtbl->Unlock(lpDDS, NULL);
							return FALSE;
            }

            /* Next pixel */
			lpSrcPointer+=3;	
			lpSrcPointerNL+=3;
        }
    }
	
	/* Unlock texture surface because we're done filling it */
	hres=lpDDS->lpVtbl->Unlock(lpDDS, NULL);
	if (hres!=DD_OK)
	{
		OutputDebugString("CopyBitmapToBumpMapSurface  : Unlock() failed\n");
		return FALSE;
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
	char					pszString[200];

	/*********************
	** Check parameters **
	*********************/
	if (!lpDDSSystemMemorySurface || !pBm || !lpDD4 || !lpDev3)
	{
		OutputDebugString("CreateFourierMipmapLevels : Invalid parameters.\n");
		return FALSE;
	}
	
	/****************************
	** Get surface description **
	****************************/
	/* Initialise DDSURFACEDESC2 structure */
	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
	ddsd.dwSize=sizeof(DDSURFACEDESC2);

	/* Get surface description */
	hres=lpDDSSystemMemorySurface->lpVtbl->GetSurfaceDesc(lpDDSSystemMemorySurface, &ddsd);
	if (hres!=DD_OK)
	{
		OutputDebugString("CreateFourierMipmapLevels : GetSurfaceDesc() failed.\n");
		return FALSE;
	}

	/*******************
	** Various checks **
	*******************/
	/* Check if the texture width and height have been specified */
	if (!(ddsd.dwFlags & DDSD_WIDTH) || !(ddsd.dwFlags & DDSD_HEIGHT))
	{
		OutputDebugString("CreateFourierMipmapLevels : Texture size must be specified.\n");
		return FALSE;
	}

	/* Check if the texture is square */
	if (ddsd.dwWidth!=ddsd.dwHeight)
	{
		OutputDebugString("CreateFourierMipmapLevels : Mipmapping require SQUARE textures.\n");
		return FALSE;
	}

	/* Get texture size and its wrap-around equivalent */
	dwTextureSize=ddsd.dwWidth;
	dwMirrorSize=2*dwTextureSize;

	/* Check texture dimensions */
	if (dwTextureSize>2048)
	{
		OutputDebugString("CreateFourierMipmapLevels : Texture size too large.\n");
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
		case 1:		OutputDebugString("CreateFourierMipmapLevels : No mipmap level needed for a texture size of 1\n");
					return FALSE; break;
		default :	OutputDebugString("CreateFourierMipmapLevels : Texture size is not a power of 2\n");
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
	OutputDebugString("Generating mipmap level : 0");
		
	/****************************
	** Expand data into mirror **
	****************************/
	MirrorExpandBitmap(dataRed, dataGreen, dataBlue, pBmTrans ? dataAlpha : NULL, 
					   pBm, pBmTrans);

	/* Progress indicator */
	OutputDebugString(".");
	
	
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
	OutputDebugString(".");
	
		
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
		sprintf(pszString, "%d", nMipmap);
		OutputDebugString(pszString);

		/****************************
		** Get next mipmap surface **
		*****************************/
		ZeroMemory(&ddsCaps, sizeof(DDSCAPS2));
		ddsCaps.dwCaps=DDSCAPS_TEXTURE | DDSCAPS_MIPMAP;
		hres=lpDDSCurrentMemorySurface->lpVtbl->GetAttachedSurface(lpDDSCurrentMemorySurface, &ddsCaps, &lpDDSCurrentMemorySurface);
		if (hres!=DD_OK)
		{
			sprintf(pszString, "CreateFourierMipmapLevels : Failed to get mipmap level %d.\n", nMipmap);
			OutputDebugString(pszString);
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
		OutputDebugString(".");

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
		OutputDebugString(".");
		
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
		OutputDebugString(".");
		
		
		/****************************
		** Mipmap surface creation **
		****************************/
		/* Initialise ddsd */
		ZeroMemory(&ddsd, sizeof(ddsd));
		ddsd.dwSize=sizeof(ddsd);
		
		/* Lock texture surface to fill it */
		hres=lpDDSCurrentMemorySurface->lpVtbl->Lock(lpDDSCurrentMemorySurface, NULL, &ddsd, 0, NULL); 
		if (hres!=DD_OK) 
		{
			OutputDebugString("CreateFourierMipmapLevels : Failed to lock texture surface\n");
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
				if (fGreenChannel<0.0) G=0;
					else if (fGreenChannel>255.0) G=255;
						else G=fround(fGreenChannel);
				if (fBlueChannel<0.0) B=0;
					else if (fBlueChannel>255.0) B=255;
						else B=fround(fBlueChannel);
				if (fAlphaChannel<0.0) A=0;
					else if (fAlphaChannel>255.0) A=255;
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
							OutputDebugString("CreateFourierMipmapLevels : Unknown pixel format\n");
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
		OutputDebugString(".");

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
	OutputDebugString("\n");

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
		OutputDebugString("DitherBitmap : Texture format not supported\n");
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
				*pTranslucentPixel==Alpha;
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
 * Inputs		  : *pBm, *pBmTrans, *pBmOut, *pBmTransOut
 * Returns		  : TRUE or FALSE
 * Description    : Create next mipmap level from *pBm and *pBmTrans.
 *					The next mipmap is computed using a 2x2 algorithm.
 *					Four pixels in the source surface define one pixel
 *					in the destination surface.
 *					For translucent images, the four pixels color channels 
 *					are weighted with their alpha values.
 *
 *****************************************************************************/
BOOL CreateNextMipmapLevel2x2(BITMAP *pBm, BITMAP *pBmTrans, 
							  BITMAP *pBmOut, BITMAP *pBmTransOut)
{
	PixelMap				Pixel1, Pixel2, Pixel3, Pixel4;
	DWORD					dwTotalAlpha;
	unsigned char			*lpSrcPointer, *lpSrcPointerNL, *lp8b;
	unsigned char			*lpSrcPointerTrans, *lp8bTrans;
	unsigned char			r, g, b;
	float					fInvA;
	int						i, j;
			
	/* For each line of destination surface */
	for (i=0; i<pBmOut->bmHeight; i++)
	{
		/* Compute source and destination pointers */
		lpSrcPointer=(unsigned char *)pBm->bmBits + i*2*pBm->bmWidthBytes;
		lpSrcPointerNL=(unsigned char *)pBm->bmBits + i*2*pBm->bmWidthBytes + pBm->bmWidthBytes;
		lp8b=(unsigned char *)pBmOut->bmBits + i*pBmOut->bmWidthBytes;

		/* Compute source and destination pointers for translucent map */
		if (pBmTrans)
		{
			lpSrcPointerTrans=(unsigned char *)pBmTrans->bmBits + i*2*pBmTrans->bmWidthBytes;
			lp8bTrans=(unsigned char *)pBmTransOut->bmBits + i*pBmTransOut->bmWidthBytes + 2;
		}

		/* For each column of destination surface */
		for (j=0; j<pBmOut->bmWidth; j++)
		{
			/* Get block of four pixels */
			Pixel1 = *(PixelMap *)(lpSrcPointer   + 0);
			Pixel2 = *(PixelMap *)(lpSrcPointer   + 3);
			Pixel3 = *(PixelMap *)(lpSrcPointerNL + 0);

			/* Read each color channel separately because we reached the end 
			   of column at the end of line, so reading a DWORD (4 bytes) could 
			   create a GP fault on exact 4 bytes aligned bitmaps */
			if (i==(pBmOut->bmHeight-1))
			{
				Pixel4.Blue =  *(lpSrcPointerNL + 3);
				Pixel4.Green = *(lpSrcPointerNL + 4);
				Pixel4.Red =   *(lpSrcPointerNL + 5);
			}
			else
			{
				Pixel4 = *(PixelMap *)(lpSrcPointerNL + 3);
			}

			/* Translucent case */
			if (pBmTrans)
			{
				/* Also read block of four alpha value */
				Pixel1.Alpha = *(lpSrcPointerTrans + 2);
				Pixel2.Alpha = *(lpSrcPointerTrans + 5);
				Pixel3.Alpha = *(lpSrcPointerTrans + pBmTrans->bmWidthBytes + 2);
				Pixel4.Alpha = *(lpSrcPointerTrans + pBmTrans->bmWidthBytes + 5);

				/* Get total alpha channel of four pixels */
				dwTotalAlpha = (Pixel1.Alpha + Pixel2.Alpha + Pixel3.Alpha + Pixel4.Alpha);

				/* If total Alpha is 0, then only average color channels */
				if (!dwTotalAlpha)
				{
					/* Get average color channels of four pixels */
					r = (Pixel1.Red   +	Pixel2.Red   +	Pixel3.Red   +	Pixel4.Red  ) >> 2;
					g = (Pixel1.Green + Pixel2.Green +	Pixel3.Green +	Pixel4.Green) >> 2;
					b = (Pixel1.Blue  + Pixel2.Blue  +  Pixel3.Blue  +  Pixel4.Blue ) >> 2;
				}
				else
				{
					/* Use Alpha weight to compute colors channels */
					fInvA=1.0f/dwTotalAlpha;
					r = ( Pixel1.Red * Pixel1.Alpha + 
						  Pixel2.Red * Pixel2.Alpha + 
						  Pixel3.Red * Pixel3.Alpha + 
						  Pixel4.Red * Pixel4.Alpha ) * fInvA;
					g = ( Pixel1.Green * Pixel1.Alpha + 
						  Pixel2.Green * Pixel2.Alpha + 
						  Pixel3.Green * Pixel3.Alpha + 
						  Pixel4.Green * Pixel4.Alpha ) * fInvA;
					b = ( Pixel1.Blue * Pixel1.Alpha + 
						  Pixel2.Blue * Pixel2.Alpha + 
						  Pixel3.Blue * Pixel3.Alpha + 
						  Pixel4.Blue * Pixel4.Alpha ) * fInvA;
					dwTotalAlpha>>=2;
				}

				/* Write resulting alpha pixel into translucent bitmap data */
				*lp8bTrans = dwTotalAlpha;
				lp8bTrans += 3;

				/* Increase translucent source pointer */
				lpSrcPointerTrans+=6;
			}
			else
			{
				/* Get average color channels of four pixels */
				r = (Pixel1.Red   +	Pixel2.Red   +	Pixel3.Red   +	Pixel4.Red  ) >> 2;
				g = (Pixel1.Green + Pixel2.Green +	Pixel3.Green +	Pixel4.Green) >> 2;
				b = (Pixel1.Blue  + Pixel2.Blue  +  Pixel3.Blue  +  Pixel4.Blue ) >> 2;
			}

			/* Write resulting pixel into bitmap data */
			*lp8b++ = b;
			*lp8b++ = g;
			*lp8b++ = r;

			/* Increase source pointers */
			lpSrcPointer+=6;
			lpSrcPointerNL+=6;
		}
	}

	/* No problem occured */
	return TRUE;
}


/*****************************************************************************
 * Function Name  : CreateNextMipmapLevel4x4
 * Inputs		  : *pBm, *pBmTrans
 * Outputs		  : *pBmOut, *pBmTransOut
 * Returns		  : TRUE or FALSE
 * Description    : Create next mipmap level from *pBm and *pBmTrans.
 *					The next mipmap is computed using a 4x4 algorith.
 *					
 *					The filter used looks like this :
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
 *		used to produce the half-size texture.
 *
 *		Each column only needs to be computed once as we generate a row of 
 *		pixels of the 1/2 size map. 
 *
 *****************************************************************************/
BOOL CreateNextMipmapLevel4x4(BITMAP *pBm, BITMAP *pBmTrans, BITMAP *pBmOut, BITMAP *pBmTransOut)
{
	int						i, j;
	unsigned char			*lp8b, *lp8bTrans;
	unsigned char			*lpSrcPointerPL, *lpSrcPointer, *lpSrcPointerNL, *lpSrcPointerLL;
	unsigned char			*lpSrcPointerPLTrans, *lpSrcPointerTrans, *lpSrcPointerNLTrans, *lpSrcPointerLLTrans;
	PixelMap				CW[4], CX[4], CY[4], CZ[4];
	PixelMap				*ColumnW=CW, *ColumnX=CX, *ColumnY=CY, *ColumnZ=CZ;
	PixelMap				*Dummy;
	DWORD					Red, Green, Blue, Alpha;
	float					fInvAlpha;

	/* For each line of destination surface */
	for (i=0; i<pBmOut->bmHeight; i++)
	{
		/* Compute source and destination pointers */
		lpSrcPointer=(unsigned char *)pBm->bmBits + i*2*pBm->bmWidthBytes;
		lpSrcPointerNL=lpSrcPointer + pBm->bmWidthBytes;
		lp8b=(unsigned char *)pBmOut->bmBits + i*pBmOut->bmWidthBytes;

		/* If first line then previous line pointer is the same as current line pointer */
		if (i==0) lpSrcPointerPL=lpSrcPointer;
			else lpSrcPointerPL=lpSrcPointer - pBm->bmWidthBytes;

		/* If last line then last line pointer is the same as next line pointer */
		if (i==(pBmOut->bmHeight-1)) lpSrcPointerLL=lpSrcPointerNL;
			else lpSrcPointerLL=lpSrcPointerNL + pBm->bmWidthBytes;

		/* Initialise column Y and Z */
		ColumnZ[0] = *(PixelMap *)lpSrcPointerPL;
		ColumnZ[1] = *(PixelMap *)lpSrcPointer;
		ColumnZ[2] = *(PixelMap *)lpSrcPointerNL;
		ColumnZ[3] = *(PixelMap *)lpSrcPointerLL;
		memcpy(ColumnY, ColumnZ, 4*sizeof(PixelMap));

		/* Compute source and destination pointers for translucent map */
		if (pBmTrans)
		{
			lpSrcPointerTrans=(unsigned char *)pBmTrans->bmBits + i*2*pBmTrans->bmWidthBytes;
			lpSrcPointerNLTrans=lpSrcPointerTrans + pBmTrans->bmWidthBytes;
			lp8bTrans=(unsigned char *)pBmTransOut->bmBits + i*pBmTransOut->bmWidthBytes + 2;

			/* If first line then previous line pointer is the same as current line pointer */
			if (i==0) lpSrcPointerPLTrans=lpSrcPointerTrans;
				else lpSrcPointerPLTrans=lpSrcPointerTrans - pBmTrans->bmWidthBytes;

			/* If last line then last line pointer is the same as next line pointer */
			if (i==(pBmTransOut->bmHeight-1)) lpSrcPointerLLTrans=lpSrcPointerNLTrans;
				else lpSrcPointerLLTrans=lpSrcPointerNLTrans + pBmTrans->bmWidthBytes;

			/* Initialise column Y and Z */
			ColumnZ[0].Alpha=	*(lpSrcPointerPLTrans + 2); 
			ColumnZ[1].Alpha=	*(lpSrcPointerTrans   + 2); 
			ColumnZ[2].Alpha=	*(lpSrcPointerNLTrans + 2); 
			ColumnZ[3].Alpha=	*(lpSrcPointerLLTrans + 2); 
			ColumnY[0].Alpha=	ColumnZ[0].Alpha;
			ColumnY[1].Alpha=	ColumnZ[1].Alpha;
			ColumnY[2].Alpha=	ColumnZ[2].Alpha;
			ColumnY[3].Alpha=	ColumnZ[3].Alpha;
		}
		
		/* For each column of destination surface */
		for (j=0; j<pBmOut->bmWidth; j++)
		{
			/********************
			** Get all columns **
			********************/

			/* Column W and X are columns Y and Z from previous pixel */
			/* Swap pointers */
			Dummy=ColumnW; ColumnW=ColumnY; ColumnY=Dummy;
			Dummy=ColumnX; ColumnX=ColumnZ; ColumnZ=Dummy;

			/* Special case if end of column */
			if (j==(pBmOut->bmWidth-1)) 
			{
				/* Get column Y */
				ColumnY[0] = *(PixelMap *)(lpSrcPointerPL + 3);
				ColumnY[1] = *(PixelMap *)(lpSrcPointer   + 3); 
				if (i==(pBmOut->bmHeight-1))
				{
					/* Read each color channel separately because we reached the end 
					   of column at the end of line, so reading a DWORD (4 bytes) could 
					   create a GP fault on exact 4 bytes aligned bitmaps */
					ColumnY[2].Blue =	*(lpSrcPointerNL + 3);
					ColumnY[2].Green =	*(lpSrcPointerNL + 4);
					ColumnY[2].Red =	*(lpSrcPointerNL + 5);
					ColumnY[3].Blue =	*(lpSrcPointerLL + 3);
					ColumnY[3].Green =	*(lpSrcPointerLL + 4);
					ColumnY[3].Red =	*(lpSrcPointerLL + 5);
				}
				else
				{
					ColumnY[2] = *(PixelMap *)(lpSrcPointerNL + 3);
					ColumnY[3] = *(PixelMap *)(lpSrcPointerLL + 3); 
				}

				/* Column Z is equal to column Y */
				memcpy(ColumnZ, ColumnY, 4*sizeof(PixelMap));
			}
			else
			{
				/* Get column Y */
				ColumnY[0] = *(PixelMap *)(lpSrcPointerPL + 3);
				ColumnY[1] = *(PixelMap *)(lpSrcPointer   + 3); 
				ColumnY[2] = *(PixelMap *)(lpSrcPointerNL + 3); 
				ColumnY[3] = *(PixelMap *)(lpSrcPointerLL + 3);
				
				/* Get column Z */
				ColumnZ[0] = *(PixelMap *)(lpSrcPointerPL + 6);
				ColumnZ[1] = *(PixelMap *)(lpSrcPointer   + 6);
				ColumnZ[2] = *(PixelMap *)(lpSrcPointerNL + 6);
				ColumnZ[3] = *(PixelMap *)(lpSrcPointerLL + 6);
			}

			/* If translucent information, also take Alpha channel */
			if (pBmTrans)
			{
				/* Column W and X alpha information is already up to date (pointers swapping) */
								
				/* Get column Y */
				ColumnY[0].Alpha=*(lpSrcPointerPLTrans + 5); 
				ColumnY[1].Alpha=*(lpSrcPointerTrans   + 5); 
				ColumnY[2].Alpha=*(lpSrcPointerNLTrans + 5); 
				ColumnY[3].Alpha=*(lpSrcPointerLLTrans + 5);

				/* Get column Z */
				if (j==(pBmOut->bmWidth-1)) 
				{
					ColumnZ[0].Alpha=ColumnY[0].Alpha; 
					ColumnZ[1].Alpha=ColumnY[1].Alpha; 
					ColumnZ[2].Alpha=ColumnY[2].Alpha; 
					ColumnZ[3].Alpha=ColumnY[3].Alpha; 
				}
				else
				{
					ColumnZ[0].Alpha=*(lpSrcPointerPLTrans + 8); 
					ColumnZ[1].Alpha=*(lpSrcPointerTrans   + 8); 
					ColumnZ[2].Alpha=*(lpSrcPointerNLTrans + 8); 
					ColumnZ[3].Alpha=*(lpSrcPointerLLTrans + 8);
				}

				/* Compute Alpha */
				Alpha= ColumnW[0].Alpha + 2*ColumnX[0].Alpha + 2*ColumnY[0].Alpha +   ColumnZ[0].Alpha +
					 2*ColumnW[1].Alpha + 4*ColumnX[1].Alpha + 4*ColumnY[1].Alpha + 2*ColumnZ[1].Alpha +
					 2*ColumnW[2].Alpha + 4*ColumnX[2].Alpha + 4*ColumnY[2].Alpha + 2*ColumnZ[2].Alpha +
				       ColumnW[3].Alpha + 2*ColumnX[3].Alpha + 2*ColumnY[3].Alpha +   ColumnZ[3].Alpha;

				/* If alpha is 0, then do not use it in weighting operation */
				if (!Alpha)
				{
					/* Compute resulting color */
					Red=   ColumnW[0].Red + 2*ColumnX[0].Red + 2*ColumnY[0].Red +   ColumnZ[0].Red +
						 2*ColumnW[1].Red + 4*ColumnX[1].Red + 4*ColumnY[1].Red + 2*ColumnZ[1].Red +
						 2*ColumnW[2].Red + 4*ColumnX[2].Red + 4*ColumnY[2].Red + 2*ColumnZ[2].Red +
						   ColumnW[3].Red + 2*ColumnX[3].Red + 2*ColumnY[3].Red +   ColumnZ[3].Red;
					Green= ColumnW[0].Green + 2*ColumnX[0].Green + 2*ColumnY[0].Green +   ColumnZ[0].Green +
						 2*ColumnW[1].Green + 4*ColumnX[1].Green + 4*ColumnY[1].Green + 2*ColumnZ[1].Green +
						 2*ColumnW[2].Green + 4*ColumnX[2].Green + 4*ColumnY[2].Green + 2*ColumnZ[2].Green +
						   ColumnW[3].Green + 2*ColumnX[3].Green + 2*ColumnY[3].Green +   ColumnZ[3].Green;
					Blue=  ColumnW[0].Blue + 2*ColumnX[0].Blue + 2*ColumnY[0].Blue +   ColumnZ[0].Blue +
						 2*ColumnW[1].Blue + 4*ColumnX[1].Blue + 4*ColumnY[1].Blue + 2*ColumnZ[1].Blue +
						 2*ColumnW[2].Blue + 4*ColumnX[2].Blue + 4*ColumnY[2].Blue + 2*ColumnZ[2].Blue +
						   ColumnW[3].Blue + 2*ColumnX[3].Blue + 2*ColumnY[3].Blue +   ColumnZ[3].Blue;

					/* Divide each color channels by total weight */
					Red   *= (1.0f / 36.0f);
					Green *= (1.0f / 36.0f);
					Blue  *= (1.0f / 36.0f);
				}
				else
				{
					/* Compute resulting color with alpha */
					Red=   ColumnW[0].Alpha*ColumnW[0].Red + 2*ColumnX[0].Alpha*ColumnX[0].Red + 2*ColumnY[0].Alpha*ColumnY[0].Red + ColumnZ[0].Alpha*ColumnZ[0].Red +
						 2*ColumnW[1].Alpha*ColumnW[1].Red + 4*ColumnX[1].Alpha*ColumnX[1].Red + 4*ColumnY[1].Alpha*ColumnY[1].Red + 2*ColumnZ[1].Alpha*ColumnZ[1].Red +
						 2*ColumnW[2].Alpha*ColumnW[2].Red + 4*ColumnX[2].Alpha*ColumnX[2].Red + 4*ColumnY[2].Alpha*ColumnY[2].Red + 2*ColumnZ[2].Alpha*ColumnZ[2].Red +
						   ColumnW[3].Alpha*ColumnW[3].Red + 2*ColumnX[3].Alpha*ColumnX[3].Red + 2*ColumnY[3].Alpha*ColumnY[3].Red + ColumnZ[3].Alpha*ColumnZ[3].Red;
					Green= ColumnW[0].Alpha*ColumnW[0].Green + 2*ColumnX[0].Alpha*ColumnX[0].Green + 2*ColumnY[0].Alpha*ColumnY[0].Green + ColumnZ[0].Alpha*ColumnZ[0].Green +
						 2*ColumnW[1].Alpha*ColumnW[1].Green + 4*ColumnX[1].Alpha*ColumnX[1].Green + 4*ColumnY[1].Alpha*ColumnY[1].Green + 2*ColumnZ[1].Alpha*ColumnZ[1].Green +
						 2*ColumnW[2].Alpha*ColumnW[2].Green + 4*ColumnX[2].Alpha*ColumnX[2].Green + 4*ColumnY[2].Alpha*ColumnY[2].Green + 2*ColumnZ[2].Alpha*ColumnZ[2].Green +
						   ColumnW[3].Alpha*ColumnW[3].Green + 2*ColumnX[3].Alpha*ColumnX[3].Green + 2*ColumnY[3].Alpha*ColumnY[3].Green + ColumnZ[3].Alpha*ColumnZ[3].Green;
					Blue=  ColumnW[0].Alpha*ColumnW[0].Blue + 2*ColumnX[0].Alpha*ColumnX[0].Blue + 2*ColumnY[0].Alpha*ColumnY[0].Blue + ColumnZ[0].Alpha*ColumnZ[0].Blue +
						 2*ColumnW[1].Alpha*ColumnW[1].Blue + 4*ColumnX[1].Alpha*ColumnX[1].Blue + 4*ColumnY[1].Alpha*ColumnY[1].Blue + 2*ColumnZ[1].Alpha*ColumnZ[1].Blue +
						 2*ColumnW[2].Alpha*ColumnW[2].Blue + 4*ColumnX[2].Alpha*ColumnX[2].Blue + 4*ColumnY[2].Alpha*ColumnY[2].Blue + 2*ColumnZ[2].Alpha*ColumnZ[2].Blue +
						   ColumnW[3].Alpha*ColumnW[3].Blue + 2*ColumnX[3].Alpha*ColumnX[3].Blue + 2*ColumnY[3].Alpha*ColumnY[3].Blue + ColumnZ[3].Alpha*ColumnZ[3].Blue;

					/* Compute 1 over alpha */
					fInvAlpha = 1.0f / Alpha;
					
					/* Divide each color channel by total alpha weight */
					Red	  *= fInvAlpha;
					Green *= fInvAlpha;
					Blue  *= fInvAlpha;
					Alpha *= (1.0f / 36.0f);
				}
				
				/* Write alpha channel in translucent bitmap */
				*lp8bTrans=Alpha;
				lp8bTrans+=3;
				
				/* Increase translucent source pointers */
				lpSrcPointerPLTrans += 6;
				lpSrcPointerTrans   += 6;
				lpSrcPointerNLTrans += 6;
				lpSrcPointerLLTrans += 6;
			}
			else
			{
				/* Opaque case */
				/* Compute resulting color */
				Red=   ColumnW[0].Red + 2*ColumnX[0].Red + 2*ColumnY[0].Red +   ColumnZ[0].Red +
					 2*ColumnW[1].Red + 4*ColumnX[1].Red + 4*ColumnY[1].Red + 2*ColumnZ[1].Red +
					 2*ColumnW[2].Red + 4*ColumnX[2].Red + 4*ColumnY[2].Red + 2*ColumnZ[2].Red +
					   ColumnW[3].Red + 2*ColumnX[3].Red + 2*ColumnY[3].Red +   ColumnZ[3].Red;
				Green= ColumnW[0].Green + 2*ColumnX[0].Green + 2*ColumnY[0].Green +   ColumnZ[0].Green +
					 2*ColumnW[1].Green + 4*ColumnX[1].Green + 4*ColumnY[1].Green + 2*ColumnZ[1].Green +
					 2*ColumnW[2].Green + 4*ColumnX[2].Green + 4*ColumnY[2].Green + 2*ColumnZ[2].Green +
					   ColumnW[3].Green + 2*ColumnX[3].Green + 2*ColumnY[3].Green +   ColumnZ[3].Green;
				Blue=  ColumnW[0].Blue + 2*ColumnX[0].Blue + 2*ColumnY[0].Blue +   ColumnZ[0].Blue +
					 2*ColumnW[1].Blue + 4*ColumnX[1].Blue + 4*ColumnY[1].Blue + 2*ColumnZ[1].Blue +
					 2*ColumnW[2].Blue + 4*ColumnX[2].Blue + 4*ColumnY[2].Blue + 2*ColumnZ[2].Blue +
					   ColumnW[3].Blue + 2*ColumnX[3].Blue + 2*ColumnY[3].Blue +   ColumnZ[3].Blue;

				/* Divide each color channel by total weight */
				Red   *= (1.0f / 36.0f);
				Green *= (1.0f / 36.0f);
				Blue  *= (1.0f / 36.0f);
			}

			/* Write resulting color */
			*lp8b++=Blue;
			*lp8b++=Green;
			*lp8b++=Red;

			/* Increase source pointers */
			lpSrcPointerPL += 6;
			lpSrcPointer   += 6;
			lpSrcPointerNL += 6;
			lpSrcPointerLL += 6;
		}
	}

	/* No problem occured */
	return TRUE;
}


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
		OutputDebugString("ComputeTransparentPixels : Bitmap do not share same dimensions\n");
		return;
	}

	/* Get x and y */
	x=pBm->bmWidth;
	y=pBm->bmHeight;

	/* Allocate array of processed pixels */
	pPixelProcessed=(BOOL *)calloc(x*y, sizeof(BOOL));

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
		OutputDebugString("ComputeTransparentPixels : Image is completely transparent! Aborting...\n");
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

	/* Release memory */
	if (pPixelProcessed)
	{
		free(pPixelProcessed);
		pPixelProcessed=NULL;
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
		OutputDebugString("ApplyLowPassFilter : Wrong parameters\n");
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
	fOneOverDenominator=1.0/pow(fCutOff, nOrder);

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
			fFilter=1.0 - fOneOverDenominator * pow(f, nHalfOrder);
			if (fFilter<0.0) fFilter=0.0;
			
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
	double			theta, wi, wpi, wpr, wr, wtemp;
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
			theta=isign*6.28318530717959/(ifp2/ip1);
			wtemp=sin(0.5*theta);
			wpr=-2.0*wtemp*wtemp;
			wpi=sin(theta);
			wr=1.0;
			wi=0.0;
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
	double			theta, wi, wpi, wpr, wr, wtemp;
	float			c1, c2, h1r, h1i, h2r, h2i;
	
	if (1+&data[nn2][nn3]-&data[1][1] != (float)nn2*nn3)
	{
		OutputDebugString("RealFFT2D : Data array size does not match parameters\n");
		return;
	}
	
	c1=0.5;
	c2=-0.5f*isign;
	theta=isign*(6.28318530717959/nn3);
	wtemp=sin(0.5*theta);
	wpr=-2.0*wtemp*wtemp;
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

	wr=1.0;
	wi=0.0;

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
		if ((fValue-floor(fValue))>0.5f)
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
		if ((fValue-floor(fValue))>0.5f)
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
	char	pszString[100];
  
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
		OutputDebugString("Maximum number of texture formats reached (30)\n");
	}
	else
	{
		nTextureFormat++;
	}
	
	/* Debug output */
	if (lpddPixelFormat->dwFlags & DDPF_PALETTEINDEXED8)
	{
		sprintf (pszString, "Enumerated texture Format : 8-bit Palettised\n");
	}
	else if (lpddPixelFormat->dwFlags & (DDPF_BUMPLUMINANCE | DDPF_BUMPDUDV))
	{
		sprintf (pszString, "Enumerated texture Format : BumpMap\n");
	}
	else if (lpddPixelFormat->dwFlags & DDPF_LUMINANCE)
	{
		sprintf (pszString, "Enumerated texture Format : Luminance\n");
	}
	else if (lpddPixelFormat->dwFlags & DDPF_FOURCC)
	{
		switch (lpddPixelFormat->dwFourCC)
		{
		case MAKEFOURCC('U', 'Y', 'V', 'Y') : sprintf (pszString, "Enumerated texture Format : FOURCC UYVY YUV format\n"); break;
		case MAKEFOURCC('Y', 'U', 'Y', '2') : sprintf (pszString, "Enumerated texture Format : FOURCC YUY2 YUV format\n"); break;
		case MAKEFOURCC('D', 'X', 'T', '1') : sprintf (pszString, "Enumerated texture Format : FOURCC DXT1 compressed format\n"); break;
		case MAKEFOURCC('D', 'X', 'T', '2') : sprintf (pszString, "Enumerated texture Format : FOURCC DXT2 compressed format\n"); break;
		case MAKEFOURCC('D', 'X', 'T', '3') : sprintf (pszString, "Enumerated texture Format : FOURCC DXT3 compressed format\n"); break;
		case MAKEFOURCC('D', 'X', 'T', '4') : sprintf (pszString, "Enumerated texture Format : FOURCC DXT4 compressed format\n"); break;
		case MAKEFOURCC('D', 'X', 'T', '5') : sprintf (pszString, "Enumerated texture Format : FOURCC DXT5 compressed format\n"); break;
		}
	}
	else
	{
		if (a)
		{
			sprintf (pszString, "Enumerated texture Format : %d%d%d%d\n", r, g, b, a);
		}
		else
		{
			sprintf (pszString, "Enumerated texture Format : %d%d%d\n", r, g, b);
		}
	}
	OutputDebugString(pszString);

	/* Enumeration OK */
	return DDENUMRET_OK;
}


/*****************************************************************************
 * Function Name  : PaletteFromBitmap
 * Inputs		  : lpDD4, hBitmap
 * Output		  : *pPaletteEntries
 * Description    : Create a surface palette from bitmap hBitmap.
 *					
 *****************************************************************************/
BOOL PaletteFromBitmap(LPDIRECTDRAW4 lpDD4, HBITMAP hBitmap, PALETTEENTRY *pPaletteEntries)
{
	BITMAP				bm;
	HDC					BitmapDC;
    DWORD				adw[256];
    char				pszString[200];
	int					nColors, i;
	
	/* First get number of palette bits */
	GetObject(hBitmap, sizeof(bm), &bm);
		
	/* Get the color table from the DIBSection */
    BitmapDC=CreateCompatibleDC(NULL);
	if (BitmapDC==NULL)
	{
		OutputDebugString("PaletteFromBitmap : CreateCompatibleDC() failed\n");
		return FALSE;
	}
    
	/* Get bitmap description */
	if (SelectObject(BitmapDC, hBitmap)==NULL)
	{
		OutputDebugString("PaletteFromBitmap : SelectObject() failed\n");
		return FALSE;
	}

    /* Debug info */
	sprintf(pszString, "PaletteFromBitmap : Using %d bits palette\n", bm.bmBitsPixel);
	OutputDebugString(pszString);
	
	/* Get Color table */
	if (bm.bmBitsPixel==4)
	{
		nColors=GetDIBColorTable(BitmapDC, 0, 16, (RGBQUAD *)adw);
		if (nColors!=16)
		{
			OutputDebugString("PaletteFromBitmap : nColors should have been 16\n");
		}
	}
	else
	{
		nColors=GetDIBColorTable(BitmapDC, 0, 256, (RGBQUAD *)adw);
	}
	if (!nColors)
	{
		OutputDebugString("PaletteFromBitmap : GetDIBColorTable() failed\n");
		DeleteDC(BitmapDC);
		return FALSE;
	}
	
	/* Delete Bitmap Device Context, as we don't need it anymore */
	DeleteDC(BitmapDC);
	
	/* Convert BGR to RGB */
    for (i=0; i<nColors; i++)
	{
		/* Process each color index */
		pPaletteEntries[i].peRed =		GetBValue(adw[i]); 
		pPaletteEntries[i].peGreen =	GetGValue(adw[i]); 
		pPaletteEntries[i].peBlue =		GetRValue(adw[i]); 
		pPaletteEntries[i].peFlags =	0;
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
		OutputDebugString("GetPixelFormatInfo : PixelFormat pointer is NULL\n");
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
 * Function Name  : GetClosestIndex
 * Inputs		  : Red, Green, Blue, dwNumber, PaletteEntries
 * Output		  : None
 * Returns		  : Closest index
 * Description    : Parse through a 16 or 256 indices palette and return the
 *					index closest to the RGB color specified.
 *
 *****************************************************************************/
BYTE GetClosestIndex(int Red, int Green, int Blue, int nNumber, PALETTEENTRY *pPalette)
{
#define ABS(x)	( (x)<0 ? (-(x)) : (x) )
	int		i, nDelta;
	int		nBestDelta=3*255, nBestIndex=0;
	
	/* Parse though all indices */
	for (i=0; i<nNumber; i++)
	{
		/* Compute delta for this color */
		nDelta=ABS(Red-pPalette[i].peRed) + ABS(Green-pPalette[i].peGreen) + ABS(Blue-pPalette[i].peBlue);

		/* Compare current delta with best one */
		if ( nDelta < nBestDelta )
		{
			/* If delta is equal to 0, a perfect match has been found, so return index */
			if (!nDelta) return i;
			
			/* Save current best index and delta */
			nBestDelta=nDelta;
			nBestIndex=i;
		}
	}

	/* Return best index */
	return nBestIndex;
}


/*****************************************************************************
 * Function Name  : SaveBitmapOntoDisk
 * Input		  : pBm, *pszFileName
 * Returns		  : TRUE or FALSE
 * Description    : Save the bitmap structure into a .bmp file on disk.
 *					The bitmap structure MUST be a 24 bits bitmap.
 *
 *****************************************************************************/
BOOL SaveBitmapOntoDisk(BITMAP *pBm, char *pszFileName)
{
	BITMAPFILEHEADER		BitmapFileHeader;
	BITMAPINFO				BitmapInfo;
	FILE					*f;
	DWORD					BMPHeaderSize=54;
	char					pszString[256];

	/* Check that bitmap is 24 bits color depth */
	if (pBm->bmBitsPixel!=24)
	{
		OutputDebugString("SaveBitmapOntoDisk : Bitmap must be 24 bits\n");
		return FALSE;
	}

	/* Fill BITMAPFILEHEADER structure */
	BitmapFileHeader.bfType='MB';
	BitmapFileHeader.bfSize=BMPHeaderSize+(pBm->bmHeight*pBm->bmWidthBytes);
	BitmapFileHeader.bfReserved1=0;
	BitmapFileHeader.bfReserved2=0;
	BitmapFileHeader.bfOffBits=BMPHeaderSize;

	/* Fill BITMAPINFO structure */
	/* Fill BITMAPINFOHEADER structure inside BITMAPINFO structure */
	BitmapInfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	BitmapInfo.bmiHeader.biWidth=pBm->bmWidth;
	BitmapInfo.bmiHeader.biHeight=pBm->bmHeight;
	BitmapInfo.bmiHeader.biPlanes=1;
	BitmapInfo.bmiHeader.biBitCount=24;		/* Image will always be saved as 24-bit BMP */
	BitmapInfo.bmiHeader.biCompression=BI_RGB;
	BitmapInfo.bmiHeader.biSizeImage=pBm->bmHeight*pBm->bmWidthBytes;
	BitmapInfo.bmiHeader.biXPelsPerMeter=0;
	BitmapInfo.bmiHeader.biYPelsPerMeter=0;
	BitmapInfo.bmiHeader.biClrUsed=0;
	BitmapInfo.bmiHeader.biClrImportant=0;

	/* Compute file name */
	if ( !(f=fopen(pszFileName, "wb")) )
	{
		sprintf(pszString, "SaveBitmapOntoDisk : Unable to create %s.\n", pszFileName);
		OutputDebugString(pszString);
		return FALSE;
	}

	/* Write BitmapFileheader */
	if (fwrite(&BitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, f)<1)
	{
		sprintf(pszString, "SaveBitmapOntoDisk : Error in writing BITMAPFILEHEADER in %s.\n", pszFileName);
		OutputDebugString(pszString);
		fclose(f);
		DeleteFile(pszFileName);
		return FALSE;
	}

	/* Write BitmapInfoHeader */
	if (fwrite(&BitmapInfo.bmiHeader, sizeof(BITMAPINFOHEADER), 1, f)<1)
	{
		sprintf(pszString, "SaveBitmapOntoDisk : Error in writing BITMAPINFOHEADER in %s.\n", pszFileName);
		OutputDebugString(pszString);
		fclose(f);
		DeleteFile(pszFileName);
		return FALSE;
	}

	/* Write bitmap data */
	if (fwrite(pBm->bmBits, pBm->bmHeight*pBm->bmWidthBytes*sizeof(unsigned char), 1, f)<1)
	{
		sprintf(pszString, "SaveBitmapOntoDisk : Error in writing %s.\n", pszFileName);
		OutputDebugString(pszString);
		fclose(f);
		DeleteFile(pszFileName);
		return FALSE;
	}

	/* Close file */
	if (fclose(f)!=0)
	{
		sprintf(pszString, "SaveBitmapOntoDisk : Error in closing %s.\n", pszFileName);
		OutputDebugString(pszString);
	}

	/* Beep = save bitmap OK */
	MessageBeep(MB_OK);

#ifdef _DEBUG
	OutputDebugString("SaveBitmapOntoDisk : Bitmap saved successfully\n");
#endif

	/* No problem occured */
	return TRUE;
}


/*****************************************************************************
 * Function Name  : DisplayInfoAboutSurface
 * Input		  : lpDDS
 * Returns		  : Nothing
 * Description    : Display information about directdraw surface in debug
 *					output.
 *
 *****************************************************************************/
void DisplayInfoAboutSurface(LPDIRECTDRAWSURFACE4 lpDDS)
{
	DDSURFACEDESC2	ddsd;
	char			pszString[300];

	/* Get surface description */
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize=sizeof(ddsd);
	lpDDS->lpVtbl->GetSurfaceDesc(lpDDS, &ddsd);

	/* Debug info */
	sprintf(pszString, "\n\nInterface address : 0x%X\n", lpDDS);
	OutputDebugString(pszString);

	OutputDebugString("\nFlags : ");
	if (ddsd.dwFlags & DDSD_ALPHABITDEPTH)		OutputDebugString("DDSD_ALPHABITDEPTH ");
	if (ddsd.dwFlags & DDSD_BACKBUFFERCOUNT)	OutputDebugString("DDSD_BACKBUFFERCOUNT ");
	if (ddsd.dwFlags & DDSD_CAPS)				OutputDebugString("DDSD_CAPS ");
	if (ddsd.dwFlags & DDSD_CKDESTBLT)			OutputDebugString("DDSD_CKDESTBLT ");
	if (ddsd.dwFlags & DDSD_CKDESTOVERLAY)		OutputDebugString("DDSD_CKDESTOVERLAY ");
	if (ddsd.dwFlags & DDSD_CKSRCBLT)			OutputDebugString("DDSD_CKSRCBLT ");
	if (ddsd.dwFlags & DDSD_CKSRCOVERLAY)		OutputDebugString("DDSD_CKSRCOVERLAY ");
	if (ddsd.dwFlags & DDSD_HEIGHT)				OutputDebugString("DDSD_HEIGHT ");
	if (ddsd.dwFlags & DDSD_LINEARSIZE)			OutputDebugString("DDSD_LINEARSIZE ");
	if (ddsd.dwFlags & DDSD_LPSURFACE)			OutputDebugString("DDSD_LPSURFACE ");
	if (ddsd.dwFlags & DDSD_MIPMAPCOUNT)		OutputDebugString("DDSD_MIPMAPCOUNT ");
	if (ddsd.dwFlags & DDSD_PITCH)				OutputDebugString("DDSD_PITCH ");
	if (ddsd.dwFlags & DDSD_PIXELFORMAT)		OutputDebugString("DDSD_PIXELFORMAT ");
	if (ddsd.dwFlags & DDSD_REFRESHRATE)		OutputDebugString("DDSD_REFRESHRATE ");
	if (ddsd.dwFlags & DDSD_TEXTURESTAGE)		OutputDebugString("DDSD_TEXTURESTAGE ");
	if (ddsd.dwFlags & DDSD_WIDTH)				OutputDebugString("DDSD_WIDTH ");
	if (ddsd.dwFlags & DDSD_ZBUFFERBITDEPTH)	OutputDebugString("DDSD_ZBUFFERBITDEPTH ");

	if (ddsd.dwFlags & (DDSD_HEIGHT | DDSD_WIDTH))
	{
		sprintf(pszString, "\nWidth = %d   Height = %d\n", ddsd.dwWidth, ddsd.dwHeight);
		OutputDebugString(pszString);
	}

	if (ddsd.dwFlags & DDSD_LINEARSIZE)
	{
		sprintf(pszString, "Linear size = %d\n", ddsd.dwLinearSize);
	}
	else
	{
		sprintf(pszString, "lPitch = %d\n", ddsd.lPitch);
	}
	OutputDebugString(pszString);

	if (ddsd.dwFlags & DDSD_BACKBUFFERCOUNT) 
	{
		sprintf(pszString, "Back buffer count = %d\n", ddsd.dwBackBufferCount);
		OutputDebugString(pszString);
	}

	if (ddsd.dwFlags & DDSD_REFRESHRATE)
	{
		sprintf(pszString, "Refresh rate = %d\n", ddsd.dwRefreshRate);
	}
	else
	{
		sprintf(pszString, "Mipmap count = %d\n", ddsd.dwMipMapCount);
	}
	OutputDebugString(pszString);

	if (ddsd.dwFlags & DDSD_ALPHABITDEPTH)
	{
		sprintf(pszString, "Alpha bit depth = %d\n", ddsd.dwAlphaBitDepth);
		OutputDebugString(pszString);
	}

	if (ddsd.dwFlags & DDSD_LPSURFACE) 
	{
		sprintf(pszString, "Surface address : 0x%X\n", ddsd.lpSurface);
		OutputDebugString(pszString);
	}

	// no CK stuff for now

	if (ddsd.dwFlags & DDSD_PIXELFORMAT)
	{
		OutputDebugString("Pixel format : \n");
		OutputDebugString("Flags : ");
		if (ddsd.ddpfPixelFormat.dwFlags & DDPF_ALPHA)				OutputDebugString("DDPF_ALPHA ");
		if (ddsd.ddpfPixelFormat.dwFlags & DDPF_ALPHAPIXELS)		OutputDebugString("DDPF_ALPHAPIXELS ");
		if (ddsd.ddpfPixelFormat.dwFlags & DDPF_ALPHAPREMULT)		OutputDebugString("DDPF_ALPHAPREMULT ");
		if (ddsd.ddpfPixelFormat.dwFlags & DDPF_BUMPLUMINANCE)		OutputDebugString("DDPF_BUMPLUMINANCE ");
		if (ddsd.ddpfPixelFormat.dwFlags & DDPF_BUMPDUDV)			OutputDebugString("DDPF_BUMPDUDV ");
		if (ddsd.ddpfPixelFormat.dwFlags & DDPF_COMPRESSED)			OutputDebugString("DDPF_COMPRESSED ");
		if (ddsd.ddpfPixelFormat.dwFlags & DDPF_FOURCC)				OutputDebugString("DDPF_FOURCC ");
		if (ddsd.ddpfPixelFormat.dwFlags & DDPF_LUMINANCE)			OutputDebugString("DDPF_LUMINANCE ");
		if (ddsd.ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED1)	OutputDebugString("DDPF_PALETTEINDEXED1 ");
		if (ddsd.ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED2)	OutputDebugString("DDPF_PALETTEINDEXED2 ");
		if (ddsd.ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED4)	OutputDebugString("DDPF_PALETTEINDEXED4 ");
		if (ddsd.ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED8)	OutputDebugString("DDPF_PALETTEINDEXED8 ");
		if (ddsd.ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXEDTO8)	OutputDebugString("DDPF_PALETTEINDEXEDTO8 ");
		if (ddsd.ddpfPixelFormat.dwFlags & DDPF_RGB)				OutputDebugString("DDPF_RGB ");
		if (ddsd.ddpfPixelFormat.dwFlags & DDPF_RGBTOYUV)			OutputDebugString("DDPF_RGBTOYUV ");
		if (ddsd.ddpfPixelFormat.dwFlags & DDPF_STENCILBUFFER)		OutputDebugString("DDPF_STENCILBUFFER ");
		if (ddsd.ddpfPixelFormat.dwFlags & DDPF_YUV)				OutputDebugString("DDPF_YUV ");
		if (ddsd.ddpfPixelFormat.dwFlags & DDPF_ZBUFFER)			OutputDebugString("DDPF_ZBUFFER ");
		if (ddsd.ddpfPixelFormat.dwFlags & DDPF_ZPIXELS)			OutputDebugString("DDPF_ZPIXELS ");

		if (ddsd.ddpfPixelFormat.dwFlags & DDPF_FOURCC)
		{
			sprintf(pszString, "\nFOURCC %c%c%c%c", RGBA_GETBLUE(ddsd.ddpfPixelFormat.dwFourCC), RGBA_GETGREEN(ddsd.ddpfPixelFormat.dwFourCC), RGBA_GETRED(ddsd.ddpfPixelFormat.dwFourCC), RGBA_GETALPHA(ddsd.ddpfPixelFormat.dwFourCC));
			OutputDebugString(pszString);
		}

		sprintf(pszString, "\nRGB Bit count = %d\n", ddsd.ddpfPixelFormat.dwRGBBitCount);
		OutputDebugString(pszString);

		sprintf(pszString, "Masks : RED=0x%X   GREEN=0x%X   BLUE=0x%X", ddsd.ddpfPixelFormat.dwRBitMask, ddsd.ddpfPixelFormat.dwGBitMask, ddsd.ddpfPixelFormat.dwBBitMask);
		OutputDebugString(pszString);

		if (ddsd.ddpfPixelFormat.dwFlags & DDPF_ALPHAPIXELS) 
		{
			sprintf(pszString, "   ALPHA=0x%X");
			OutputDebugString(pszString);
		}

		OutputDebugString("\n");
	}

	if (ddsd.dwFlags & DDSD_CAPS)
	{
		OutputDebugString("DDSCAPS : ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_3DDEVICE)				OutputDebugString("DDSCAPS_3DDEVICE ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_ALLOCONLOAD)			OutputDebugString("DDSCAPS_ALLOCONLOAD ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_ALPHA)				OutputDebugString("DDSCAPS_ALPHA ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_BACKBUFFER)			OutputDebugString("DDSCAPS_BACKBUFFER ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_COMPLEX)				OutputDebugString("DDSCAPS_COMPLEX ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_FLIP)					OutputDebugString("DDSCAPS_FLIP ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_FRONTBUFFER)			OutputDebugString("DDSCAPS_FRONTBUFFER ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_HWCODEC)				OutputDebugString("DDSCAPS_HWCODEC ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_LIVEVIDEO)			OutputDebugString("DDSCAPS_LIVEVIDEO ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_LOCALVIDMEM)			OutputDebugString("DDSCAPS_LOCALVIDMEM ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_MIPMAP)				OutputDebugString("DDSCAPS_MIPMAP ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_MODEX)				OutputDebugString("DDSCAPS_MODEX ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_NONLOCALVIDMEM)		OutputDebugString("DDSCAPS_NONLOCALVIDMEM ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_OFFSCREENPLAIN)		OutputDebugString("DDSCAPS_OFFSCREENPLAIN ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_OPTIMIZED)			OutputDebugString("DDSCAPS_OPTIMIZED ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_OVERLAY)				OutputDebugString("DDSCAPS_OVERLAY ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_OWNDC)				OutputDebugString("DDSCAPS_OWNDC ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_PALETTE)				OutputDebugString("DDSCAPS_PALETTE ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_PRIMARYSURFACE)		OutputDebugString("DDSCAPS_PRIMARYSURFACE ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_PRIMARYSURFACELEFT)	OutputDebugString("DDSCAPS_PRIMARYSURFACELEFT ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_STANDARDVGAMODE)		OutputDebugString("DDSCAPS_STANDARDVGAMODE ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_SYSTEMMEMORY)			OutputDebugString("DDSCAPS_SYSTEMMEMORY ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_TEXTURE)				OutputDebugString("DDSCAPS_TEXTURE ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_VIDEOMEMORY)			OutputDebugString("DDSCAPS_VIDEOMEMORY ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_VIDEOPORT)			OutputDebugString("DDSCAPS_VIDEOPORT ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_VISIBLE)				OutputDebugString("DDSCAPS_VISIBLE ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_WRITEONLY)			OutputDebugString("DDSCAPS_WRITEONLY ");
		if (ddsd.ddsCaps.dwCaps & DDSCAPS_ZBUFFER)				OutputDebugString("DDSCAPS_ZBUFFER ");

		if (ddsd.ddsCaps.dwCaps2 & DDSCAPS2_HARDWAREDEINTERLACE)	OutputDebugString("DDSCAPS2_HARDWAREDEINTERLACE ");
		if (ddsd.ddsCaps.dwCaps2 & DDSCAPS2_HINTANTIALIASING)		OutputDebugString("DDSCAPS2_HINTANTIALIASING ");
		if (ddsd.ddsCaps.dwCaps2 & DDSCAPS2_HINTDYNAMIC)			OutputDebugString("DDSCAPS2_HINTDYNAMIC ");
		if (ddsd.ddsCaps.dwCaps2 & DDSCAPS2_HINTSTATIC)				OutputDebugString("DDSCAPS2_HINTSTATIC ");
		if (ddsd.ddsCaps.dwCaps2 & DDSCAPS2_OPAQUE)					OutputDebugString("DDSCAPS2_OPAQUE ");
		if (ddsd.ddsCaps.dwCaps2 & DDSCAPS2_TEXTUREMANAGE)			OutputDebugString("DDSCAPS2_TEXTUREMANAGE ");
	}

	if (ddsd.dwFlags & DDSD_TEXTURESTAGE)
	{
		sprintf(pszString, "Texture stage : %d\n", ddsd.dwTextureStage);
		OutputDebugString(pszString);
	}
}
