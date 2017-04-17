/*****************************************************************************
  Name : D3DTools.h
  Date : 1999
  Platform : ANSI compatible
 
  $Revision: 1.24 $

  Description : Header file of D3DTools.lib.
				Contains structure definitions and prototypes 
				of all functions in D3DTools.c

  
  This header should be created at building time (using a makefile or direct
  creation).
  
  Copyright : 1999 by Imagination Technologies Limited. All rights reserved.
******************************************************************************/
#ifndef _D3DTOOLS_H_
#define _D3DTOOLS_H_

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

#define FONT_SYSTEM -1.0f
#define FONT_ARIAL   1.0f

/* dwFlags for D3DTPrint3DSetWindowFlags */
enum {
	PRINT3D_ACTIVATE_WIN		=	0x01,
	PRINT3D_DEACTIVATE_WIN		=	0x02,
	PRINT3D_ACTIVATE_TITLE		=	0x04,
	PRINT3D_DEACTIVATE_TITLE	=	0x08,
	PRINT3D_FULL_OPAQUE			=	0x10,
	PRINT3D_FULL_TRANS			=	0x20,
	PRINT3D_ADJUST_SIZE_ALWAYS	=	0x40,
	PRINT3D_NO_BORDER			=	0x80,
} PRINT3D_FLAGS;

/***********************************/
/*  BUMPMAP DEFINES                */
/***********************************/
/* These are creation methods for the bumpmap local coordinate system used by 
 * KMBumpCalculateLocalCoords() 
 *
 * The first one (BUMP_COORDS_UPRIGHT) only works fine when the texture has been aplied uniformly
 * and looking upwards. It has been added here just because is a easy and common way of calculating
 * the local coordinate system for bump-mapping. We don't recomend using it.
 * 
 * The second one (BUMP_COORDS_ANYDIRECTION) works always for any model. 
 *
 * The last one (BUMP_COORDS_ANYDIRECTION_AVERAGE) is the same but average results to 'smooth' critical vertices.
 * It is very slow, and is not really needed in most cases.
 */
#define BUMP_COORDS_UPRIGHT 0
#define BUMP_COORDS_ANYDIRECTION 1
#define BUMP_COORDS_ANYDIRECTION_AVERAGE 2

/* These are different methods to calculate bumpmap angles (specular color) on the fly. 
 * They are used by KMBumpShade().
 *
 * Blend modes:
 * BUMP_METHOD_STANDARD
 * BUMP: Opaque -> Blend mode: DECAL_ALPHA 
 * BASE: Light-map -> Blend mode: MODULATE_ALPHA, Blend Operation: DESTCOLOR/ZERO
 *
 * BUMP_METHOD_TRANSLUCENT
 * BUMP: Translucent -> Blend mode: MODULATE_ALPHA, Blend Operation: SRCALPHA/INVSRCALPHA 
 * BASE: Opaque -> Blend mode: MODULATE_ALPHA
 *
 * BUMP_METHOD_HIGHLIGHT
 * BUMP: Opaque -> Blend mode: DECAL_ALPHA	
 * BASE: Additive -> Blend mode: MODULATE_ALPHA, Blend Operation: ONE/ONE */ 

#define BUMP_METHOD_STANDARD    0
#define BUMP_METHOD_TRANSLUCENT 1
#define BUMP_METHOD_HIGHLIGHT   2


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
typedef struct D3DTBOUNDINGBOXTAG
{
	D3DVECTOR	Point[8];
} D3DTBOUNDINGBOX, *LPD3DTBOUNDINGBOX;

typedef struct 
{
	DDPIXELFORMAT			ddPixelFormat;
	BOOL					b8BitsPalettised;
	BYTE					r;
	BYTE					g;
	BYTE					b;
	BYTE					a;
} D3DTTextureFormatType;

/************
** Globals **
************/
/* This is the only global variable from the Tools library.
   It corresponds to an array of texture formats available
   for the selected D3D device. See above for the texture
   format structure definition.
   Of course, this array will get updated if you change
   of 3D device. */
extern D3DTTextureFormatType D3DTTextureFormat[30];


/***************
** Prototypes **
***************/

/**********************
** From D3DTMatrix.h **
**********************/
void	D3DTMatrixReset(D3DMATRIX *pMatrix);
void	D3DTMatrixMultiply(D3DMATRIX *pResultMatrix, const D3DMATRIX *pMatrixA, const D3DMATRIX *pMatrixB);
void	D3DTMatrixTranslate(D3DMATRIX *pMatrix, const float fX, const float fY, const float fZ);
void	D3DTMatrixScale(D3DMATRIX *pMatrix, const float fFactor);
void	D3DTMatrixRotate(D3DMATRIX *pMatrix, const float fXAngle, const float fYAngle, const float fZAngle);
void	D3DTMatrixInverse(D3DMATRIX *pMatrix);
void	D3DTMatrixCopy(D3DMATRIX *pDstMatrix, const D3DMATRIX *pSrcMatrix);
float	D3DTMatrixDotProduct(const D3DVECTOR *pVectorA, const D3DVECTOR *pVectorB);
void	D3DTMatrixCrossProduct(D3DVECTOR *pResultVector, const D3DVECTOR *pVectorA, const D3DVECTOR *pVectorB);
void	D3DTMatrixNormalize(D3DVECTOR *pVector);


/*********************
** From D3DTTrans.h **
*********************/
void	D3DTTransComputeBoundingBox(const int nNumberOfVertices, const float *pVertex, D3DTBOUNDINGBOX *pBoundingBox);
void	D3DTTransTransformBoundingBox(const D3DMATRIX *pWorldMatrix, const D3DTBOUNDINGBOX *pBoundingBox, 
									  D3DTBOUNDINGBOX *pTBoundingBox);
BOOL	D3DTTransIsBoundingBoxVisible(const D3DMATRIX *pWorldMatrix, const D3DTBOUNDINGBOX *pBoundingBox, 
									  const int nViewportWidth, const int nViewportHeight,
									  const D3DVECTOR *pCamFrom, const D3DVECTOR *pCamTo, const float fRoll,
									  const float D, const float F, 
									  const float fViewAngleHoriz, const float fViewAngleVert,
									  BOOL *pNeedsZClipping);
void	D3DTTransTransform(const D3DMATRIX *pWorldMatrix, 
						   const int nNumberOfVertices, const float *pVertex, float *pTransformedVertex);
void	D3DTTransTransformProject(const D3DMATRIX *pWorldMatrix, 
								  const int nNumberOfVertices, const float *pVertex, D3DTLVERTEX *pTLVertex,
								  const int nViewportWidth, const int nViewportHeight,
								  const D3DVECTOR *pCamFrom, const D3DVECTOR *pCamTo, const float fRoll,
								  const float D, const float F, 
								  const float fViewAngleHoriz, const float fViewAngleVert);
void	D3DTTransPerspective(const int nNumberOfVertices, D3DTLVERTEX *pTLVertex,
							 const int nViewportWidth, const int nViewportHeight,
							 const float D, const float F);
void	D3DTTransTransformProjectPerspective(const D3DMATRIX *pWorldMatrix, 
											 const int nNumberOfVertices, const float *pVertex, D3DTLVERTEX *pTLVertex,
											 const int nViewportWidth, const int nViewportHeight,
											 const D3DVECTOR *pCamFrom, const D3DVECTOR *pCamTo, const float fRoll,
											 const float D, const float F, 
											 const float fViewAngleHoriz, const float fViewAngleVert);
void	D3DTTransTransformProjectZSlamPerspective(const D3DMATRIX *pWorldMatrix, 
												  const int nNumberOfVertices, const float *pVertex, D3DTLVERTEX *pTLVertex,
												  const int nViewportWidth, const int nViewportHeight,
												  const D3DVECTOR *pCamFrom, const D3DVECTOR *pCamTo, const float fRoll,
												  const float D, const float F, 
												  const float fViewAngleHoriz, const float fViewAngleVert);
void	D3DTTransZClipProjectedVertices(const int nNumberOfVertices, D3DTLVERTEX *pTLVertex,
										const int nNumberOfTriangles, WORD *pTriangleList, int *pNumberOfVisibleTriangles);
void	D3DTTransUVEnvMap(const D3DMATRIX *pWorldMatrix,
						  const int nNumberOfVertices, const float *pNormals, D3DTLVERTEX *pTLVertex,
						  const D3DVECTOR *pCamFrom, const D3DVECTOR *pCamTo, const float fRoll);

void D3DTTransCalculateVPMatrix(D3DMATRIX *pViewMatrix, D3DMATRIX *pProjMatrix,
											   const D3DVECTOR *pCamFrom, const D3DVECTOR *pCamTo, const float fRoll,
											   const float D, const float F, 
											   const float fViewAngleHoriz, const float fViewAngleVert);


/*********************
** From D3DTLight.h **
*********************/
void	D3DTLightSmoothShade(const D3DMATRIX *pWorldMatrix, 
							 const int nNumberOfVertices, const float *pNormals, D3DTLVERTEX *pTLVertex, 
							 const D3DVECTOR *pLightVector, const D3DCOLOR dwLightColor);
void	D3DTLightSpecular(const D3DMATRIX *pWorldMatrix,
						  const int nNumberOfVertices, const float *pNormals, const float *pVertex, D3DTLVERTEX *pTLVertex,
						  const D3DVECTOR *pLightVector, const D3DVECTOR *pCamWorldPos,
						  const D3DCOLOR cDiffuse, const D3DCOLOR cSpecular,
						  const float fSpecularPower);


/********************
** From D3DTMisc.h **
********************/
BOOL	D3DTMiscIsPVR2DirectDraw();
void	D3DTMiscDisplayMatrixInDebug(const D3DMATRIX *pMatrix);
void	D3DTMiscDisplayVectorInDebug(const D3DVECTOR *pVector);
void	D3DTMiscSetBackgroundColor(LPDIRECT3D3 lpD3D3, LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DVIEWPORT3 lpView3, D3DCOLOR dwColor);


/***********************
** From D3DTTexture.h **
***********************/
/* Texture functions */
BOOL			D3DTTextureListFormats(LPDIRECT3DDEVICE3 lpDev3);
DDPIXELFORMAT	*D3DTTextureBestOpaqueFormat(BOOL b16BitsTexture);
DDPIXELFORMAT	*D3DTTextureBestTranslucentFormat(BOOL b16BitsTexture);
DDPIXELFORMAT	*D3DTTexturePalettised8BitFormat();

/* For VQ only */
BOOL D3DTTextureLoadVQ(LPDIRECT3DDEVICE3 lpDev2, LPDIRECTDRAW4 lpDD2, TCHAR *ResourceVQ, 
							 LPDIRECTDRAWSURFACE4 *lplpDDSTextureSurface, LPDIRECT3DTEXTURE2 *lplpD3DTexture2);

/* For YUV only */
BOOL D3DTTextureLoadYUV(LPDIRECT3DDEVICE3 lpDev3, LPDIRECTDRAW4 lpDD4, LPCWSTR lpName, 
							 LPDIRECTDRAWSURFACE4 *lplpDDSTextureSurface, LPDIRECT3DTEXTURE2 *lplpD3DTexture2);
/* For bumpmapping only */
BOOL			D3DTTextureLoadBumpmap(LPDIRECT3DDEVICE3 lpDev2, LPDIRECTDRAW4 lpDD2, LPCWSTR lpName, 
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

/***********************
** From D3DTPrint3D.h **
***********************/
/* Always in InitView */
BOOL D3DTPrint3DSetTextures(LPDIRECT3DDEVICE3 lpDev3, LPDIRECTDRAW4 lpDD4, DWORD dwScreenX, DWORD dwScreenY);

/* Always in ReleaseView */
void  D3DTPrint3DReleaseTextures (void);

/* Screen Output */
void D3DTPrint3D (float XPos, float YPos, float fScale,  int Colour, const TCHAR *Format, ...);

/* Create a window with default values (return a handle to the window)*/
DWORD D3DTPrint3DCreateWindow	(DWORD dwBufferSizeX, DWORD dwBufferSizeY);

/* Free memory allocated with CreateWindow */
void D3DTPrint3DDeleteWindow(DWORD dwWin);

/* Free memory allocated with CreateWindow for all the windows*/
void D3DTPrint3DDeleteAllWindows(void);

/* Display the window (must be between BeginScene-EndScene)*/
void D3DTPrint3DDisplayWindow (DWORD dwWin);

/* Display All (must be between BeginScene-EndScene)*/
void D3DTPrint3DDisplayAllWindows(void);

/* Feed the text buffer */
void D3DTPrint3DWindowOutput	(DWORD dwWin, const TCHAR *Format, ...);

/* Clean the text buffer */
void D3DTPrint3DClearWindowBuffer(DWORD dwWin);

/* User values for the window.
 * Windows position and size are referred to a virtual screen of 100x100,
 * (0,0) is the top-left corner and (100,100) the bottom-right corner.
 * These values are the same for all resolutions.
 */
void  D3DTPrint3DSetWindow		(DWORD dwWin, DWORD dwBackgroundColor, DWORD dwFontColor, float fFontSize, 
								float fPosX, float fPosY, float fSizeX, float fSizeY);

/* User values for the title */
void D3DTPrint3DSetTitle	(DWORD dwWin, DWORD dwBackgroundColor, float fFontSize, 
								DWORD dwFontColorLeft, TCHAR *sTitleLeft, 
								DWORD dwFontColorRigth, TCHAR *sTitleRight);
/* Setting flags */
void D3DTPrint3DSetWindowFlags (DWORD dwWin, DWORD dwFlags);

/* Cursor position for the next OutputWindow */
void D3DTPrint3DSetWindowBufferPointer(DWORD dwWin, DWORD dwXPos, DWORD dwYPos);

/* Calculates window size to display everything.
 * (dwMode 0 = Both, dwMode 1 = X only,  dwMode 2 = Y only) 
 */
void D3DTPrint3DAdjustWindowSize(DWORD dwWin, DWORD dwMode);

/* This window on the top of everything */
void D3DTPrint3DSetTopMostWindow(DWORD dwWin);

/* Window position */
void D3DTPrint3DSetWindowPos(DWORD dwWin, float fPosX, float fPosY);

/* Window size */
void D3DTPrint3DSetWindowSize(DWORD dwWin, float fSizeX, float fSizeY);

/* Easy way... */
DWORD D3DTPrint3DCreateDefaultWindow (float fPosX, float fPosY, int nXSize_LettersPerLine, TCHAR *sTitle, TCHAR *sBody);

/*********************
** From D3DTSound.h **
*********************/
BOOL	D3DTSoundInit		(const HWND hWnd);
BOOL	D3DTSoundShutdown	();

BOOL	D3DTSoundLoad		(unsigned short *szFilename, int *nID);
BOOL	D3DTSoundPlay		(const int nID, const BOOL bLooped);
int		D3DTSoundStop		(const int nID, const BOOL bReset);

/**************************
** From D3DTController.h **
***************************/
BOOL InitDirectInput(HWND hWnd, HINSTANCE hInstance);
void ReleaseDirectInput(void);

BOOL UpdateJoystick(void);

BOOL IsAKey(void);
BOOL IsBKey(void);
BOOL IsXKey(void);
BOOL IsYKey(void);

BOOL IsLFKey(void);
BOOL IsRFKey(void);

BOOL IsSTARTKey(void);
BOOL IsUPKey(void);
BOOL IsDOWNKey(void);
BOOL IsLEFTKey(void);
BOOL IsRIGHTKey(void);

LONG GetAnalogX(void);
LONG GetAnalogY(void);

/********************/
/* BUMPMAP ROUTINES */
/********************/
/*
 *  Calculates Bump-map angles and smooth shading 
 *  Notes:
 *  Set the parameter *pTLVertexObject to NULL if you only want to calculate Bumpmap.
 *  This method uses the local coordinate systems calculated by 
 *  KMBumpCalculateLocalCoords().
 *	Call this funtion every frame to get a correct phong bumpmapping.
 */
void D3DTBumpShade(D3DMATRIX *pMatrix, 
				 unsigned nNumberOfVertices, float *pBumpCoords, float *pNormals,
				 D3DTLVERTEX *pTLVertexBump, D3DTLVERTEX *pTLVertexObject,
				 D3DVECTOR LightVector, int nMethod);

/*
 *  Calculates Bump-map angles only (tricky way).
 *  Notes:
 *  This method is fast and cheap, but the look is not very correct.
 *  This method is not supported by Naomi2.
 *  It doesn't need local co-ordinate systems, but only works with 
 *  upright textures.
 *	If the light is very close to X=0 Y=0 the bumpmap jumps very quickly.
 */
void D3DTCheapBumpShade(D3DMATRIX *pMatrix,  unsigned nNumberOfVertices, D3DTLVERTEX *pTLVertexBump, D3DVECTOR LightVector, int nMethod);


/*
 *  Calculates the local coordinate systems for KMBumpShade() and for Naomi2 hardware.
 *	Note: This function has to be called once at the begining of the application.
 *  The array pBumpCoords has to be allocated by the user. Its size is:
 *   NumberOfVertices * 6 * sizeof(float)
 */
void D3DTBumpCalculateLocalCoords (float *pBumpCoords, int CreationMode,
								 unsigned nNumberOfVertices, float *ptVertex,float *ptNormals, float *ptUV, 
							     unsigned nNumFaces, unsigned short *ptFaces);

#ifdef __cplusplus
}
#endif

#endif
