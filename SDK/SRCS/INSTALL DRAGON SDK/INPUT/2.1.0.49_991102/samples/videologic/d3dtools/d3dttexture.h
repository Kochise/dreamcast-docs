/*****************************************************************************
  Name : D3DTTexture.h
  Date : July 1998
  Platform : ANSI compatible
 
  Description : Header file of D3DTTexture.c
				Contains structure definitions and prototypes 
				of all functions in D3DTTexture.c

  
  Copyright : 1999 by Imagination Technologies Limited. All rights reserved.
******************************************************************************/
#ifndef _D3DTTEXTURE_H_
#define _D3DTTEXTURE_H_

#ifdef __cplusplus
extern "C" {
#endif


/************
** Defines **
************/
#ifndef RELEASE
#define RELEASE(x)	if (x) { (x)->lpVtbl->Release(x); (x)=NULL; }
#endif

/* If the following macro is set, then textures will be created in video
   memory if the 3D device is hardware. The correct behaviour is of course
   to ask the Caps, but we found out that the STB Nitro 3D does not export
   the TEXTURE_VIDEOMEMORY cap eventhough textures in video memory are
   supported. Default is 0 */
#define HWDEVICE_TEXTUREINVIDEOMEMORY	1


/**********
** Enums **
**********/
typedef enum eD3DTAutoMipmapType_TAG {
	D3DTAutoMipmap_None = 0,
	D3DTAutoMipmap_2by2 = 1,
	D3DTAutoMipmap_4by4 = 2,
	D3DTAutoMipmap_Fourier = 3,
	D3DTAutoMipmap_Fourier_LP2 = 4,
	D3DTAutoMipmap_Fourier_LP4 = 5,
	D3DTAutoMipmap_Fourier_LP6 = 6,
	D3DTAutoMipmap_Fourier_LP8 = 7,
	D3DTAutoMipmap_Fourier_LP10 = 8,
	D3DTAutoMipmap_Fourier_LP12 = 9,
	D3DTAutoMipmap_Fourier_LP14 = 10,
	D3DTAutoMipmap_Fourier_LP16 = 11,
	D3DTAutoMipmap_Fourier_LP18 = 12,
	D3DTAutoMipmap_Fourier_LP20 = 13
} eD3DTAutoMipmapType;


/*************
** Typedefs **
*************/
typedef struct 
{
	BOOL					bValidFormat;
	DDPIXELFORMAT			ddPixelFormat;
	BOOL					b4BitsPalettised;
	BOOL					b8BitsPalettised;
	BOOL					bLuminanceFormat;
	BOOL					bYUVFormat;
	BOOL					bDXTFormat;
	BOOL					bBumpMapFormat;
	BYTE					r;
	BYTE					g;
	BYTE					b;
	BYTE					a;
} D3DTTextureFormatType;

/************
** Globals **
************/
extern D3DTTextureFormatType D3DTTextureFormat[30];


/***************
** Prototypes **
***************/
/* Texture functions */
BOOL			D3DTTextureListFormats(LPDIRECT3DDEVICE3 lpDev3);
DDPIXELFORMAT	*D3DTTextureBestOpaqueFormat(BOOL b16BitsTexture);
DDPIXELFORMAT	*D3DTTextureBestTranslucentFormat(BOOL b16BitsTexture);
DDPIXELFORMAT	*D3DTTexturePalettised8BitFormat();

BOOL D3DTTextureLoadVQ(LPDIRECT3DDEVICE3 lpDev2, LPDIRECTDRAW4 lpDD2, TCHAR *ResourceVQ, 
							 LPDIRECTDRAWSURFACE4 *lplpDDSTextureSurface, LPDIRECT3DTEXTURE2 *lplpD3DTexture2);

BOOL D3DTTextureLoadYUV(LPDIRECT3DDEVICE3 lpDev3, LPDIRECTDRAW4 lpDD4, LPCWSTR lpName, 
							 LPDIRECTDRAWSURFACE4 *lplpDDSTextureSurface, LPDIRECT3DTEXTURE2 *lplpD3DTexture2);

BOOL D3DTTextureLoadBumpmap(LPDIRECT3DDEVICE3 lpDev3, LPDIRECTDRAW4 lpDD2, LPCWSTR lpName, 
							 LPDIRECTDRAWSURFACE4 *lplpDDSTextureSurface, LPDIRECT3DTEXTURE2 *lplpD3DTexture2);

BOOL			D3DTTextureLoadMipmapBMP(LPDIRECTDRAW4 lpDD4, LPDIRECT3DDEVICE3 lpDev3,
										 TCHAR *lpNames[], TCHAR *lpTranslucentNames[],
										 DDPIXELFORMAT *lpddPixelFormat, BOOL bUseD3DTextureManagement,
										 LPDIRECTDRAWSURFACE4 *lplpDDSTextureSurface, LPDIRECT3DTEXTURE2 *lplpD3DTexture2);

BOOL			D3DTTextureLoadBMP(LPDIRECTDRAW4 lpDD4, LPDIRECT3DDEVICE3 lpDev3, 
								   TCHAR *lpName, TCHAR *lpTranslucentName, 
								   BOOL bDither, eD3DTAutoMipmapType eAutoMipmap,
								   DDPIXELFORMAT *lpddPixelFormat,
								   BOOL bUseD3DTextureManagement,
								   LPDIRECTDRAWSURFACE4 *lplpDDSTextureSurface, LPDIRECT3DTEXTURE2 *lplpD3DTexture2);

BOOL			D3DTTextureReadMipmapBMP(LPDIRECTDRAW4 lpDD4, LPDIRECT3DDEVICE3 lpDev3,
										 TCHAR *lpNames[], TCHAR *lpTranslucentNames[],
										 DDPIXELFORMAT *lpddPixelFormat, LPDIRECTDRAWSURFACE4 *lplpDDSSystemMemorySurface);

BOOL			D3DTTextureReadBMP(LPDIRECTDRAW4 lpDD4, LPDIRECT3DDEVICE3 lpDev3, 
								   TCHAR *lpName, TCHAR *lpTranslucentName,
								   BOOL bDither, eD3DTAutoMipmapType eAutoMipmap,
								   DDPIXELFORMAT *lpddPixelFormat,
								   LPDIRECTDRAWSURFACE4 *lplpDDSSystemMemorySurface);

BOOL			D3DTTextureReadTransparentBMP(LPDIRECTDRAW4 lpDD4, LPDIRECT3DDEVICE3 lpDev3, 
											  TCHAR *lpName,
											  eD3DTAutoMipmapType eAutoMipmap,
											  D3DCOLOR dwTransparentColor,
											  DDPIXELFORMAT *lpddPixelFormat,
											  LPDIRECTDRAWSURFACE4 *lplpDDSSystemMemorySurface);

BOOL			D3DTTextureUpload(LPDIRECTDRAW4 lpDD4, LPDIRECT3DDEVICE3 lpDev3,
								  LPDIRECTDRAWSURFACE4 lpDDSSystemMemorySurface,
								  BOOL bUseD3DTextureManagement,
								  LPDIRECTDRAWSURFACE4 *lplpDDSTextureSurface, LPDIRECT3DTEXTURE2 *lplpD3DTexture2);

void			D3DTTextureRestoreSurface(LPDIRECT3DDEVICE3 lpDev3,
										  LPDIRECTDRAWSURFACE4 lpDDSSystemMemorySurface, 
										  LPDIRECTDRAWSURFACE4 *lplpDDSTextureSurface, LPDIRECT3DTEXTURE2 *lplpD3DTexture2);



#ifdef __cplusplus
}
#endif
	

#endif

