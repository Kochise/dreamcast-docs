/*****************************************************************************
  Name : KMTools.h
  Date : May 1999
  Platform : ANSI compatible
 
  Description : Header file of Tools library for Kamui.
				Contains structure definitions and prototypes 
				of all functions in the library.
  
  Copyright : 1999 by VideoLogic Limited. All rights reserved.
******************************************************************************/
#ifndef _KMTOOLS_H_
#define _KMTOOLS_H_

#define _CLX_
#define _CLX2_
#define _STRICT_UNION_

#include <kamui2.h>		/* for Kamui calls */

#include <math.h>
#include <stdio.h>
#include <stdarg.h>


/* Override Shinobi's sMalloc()/syFree() macros */
#ifdef syMalloc
#undef syMalloc
#define syMalloc malloc
#endif

#ifdef syFree
#undef syFree
#define syFree free
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef float km_vector[3];

/************
** Defines **
************/
#ifndef PI
#define PI 3.14159f
#endif

/* Colour macros */
#define MAKE_RGB(R,G,B)		((KMDWORD)( ((R)<<16) | ((G)<<8) | (B) ))
#define MAKE_RGBA(R,G,B,A)	((KMDWORD)( ((A)<<24) | ((R)<<16) | ((G)<<8) | (B) ))
#define GET_ALPHA(Colour)	((BYTE)( (Colour & 0xFF000000)>>24 ))
#define GET_RED(Colour)		((BYTE)( (Colour & 0x00FF0000)>>16 ))
#define GET_GREEN(Colour)	((BYTE)( (Colour & 0x0000FF00)>>8 ))
#define GET_BLUE(Colour)	((BYTE)  (Colour & 0x000000FF))

#define UINT32 unsigned long
#define UINT8  unsigned char

/* MIPMAPPING METHODS To be used with KMTextureSetMimapMethod() (By default it is 2x2) */
#define MIPMAP_2x2      0
#define MIPMAP_4x4      1 
#define MIPMAP_FOURIER1 2 
#define MIPMAP_FOURIER2 3 
#define MIPMAP_FOURIER3 4 


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


/*************
** Typedefs **
*************/
/* MATRIX type */
typedef struct _MATRIX {
    float _11, _12, _13, _14;
    float _21, _22, _23, _24;
    float _31, _32, _33, _34;
    float _41, _42, _43, _44;
} MATRIX, *LPMATRIX;


/* BOUNDINGBOX type */
typedef struct BoundingBoxTAG
{
	km_vector	Point[8];
} BOUNDINGBOX, LPBOUNDINGBOX;


/***************
** Prototypes **
***************/
/* From KMMatrix.c */
void	KMMatrixReset(MATRIX *pMatrix);
void	KMMatrixMultiply(MATRIX *pResultMatrix, const MATRIX *pMatrixA, const MATRIX *pMatrixB);
void	KMMatrixTranslate(MATRIX *pMatrix, const float fX, const float fY, const float fZ);
void	KMMatrixScale(MATRIX *pMatrix, const float fFactor);
void	KMMatrixRotate(MATRIX *pMatrix, const float fXAngle, const float fYAngle, const float fZAngle);
void	KMMatrixInverse(MATRIX *pMatrix);
void	KMMatrixCopy(MATRIX *pDstMatrix, const MATRIX *pSrcMatrix);
float	KMMatrixDotProduct(const km_vector VectorA, const km_vector VectorB);
void	KMMatrixCrossProduct(km_vector ResultVector, const km_vector VectorA, const km_vector VectorB);
void	KMMatrixNormalize(km_vector Vector);

/* From KMTrans.c */
void	KMTransComputeBoundingBox(const int nNumberOfVertices, const float *pVertex, BOUNDINGBOX *pBoundingBox);
int	KMTransIsBoundingBoxVisible(const MATRIX *pWorldMatrix, const BOUNDINGBOX *pBoundingBox, 
							 const km_vector CamFrom, const km_vector CamTo, const float fRoll,
							 const float D, const float F, const float fViewAngle,
							 int *pNeedsZClipping);
void	KMTransTransformVertices(const MATRIX *pWorldMatrix, 
						  const int nNumberOfVertices, const float *pVertex, float *pTransformedVertex);
void	KMTransTransformProjectVertices(MATRIX *pWorldMatrix, 
								 int nNumberOfVertices, float *pVertex, KMVERTEX_03 *pTLVertex,
								 const km_vector CamFrom, const km_vector CamTo, const float fRoll,
								 const float D, const float F, const float fViewAngle);
void	KMTransPerspectiveVertices(const int nNumberOfVertices, KMVERTEX_03 *pTLVertex,
							const int nViewportWidth, const int nViewportHeight,
							const float D, const float F, const float fViewAngle);
int	    KMTransTransformProjectPerspective(MATRIX *pWorldMatrix, 
											int nNumberOfVertices, float *pVertex, KMVERTEX_03 *pTLVertex,
											int nViewportWidth, int nViewportHeight,
											const km_vector CamFrom, const km_vector CamTo, const float fRoll,
											const float D, const float F, const float fViewAngle);
void	KMTransZClipProjectedVertices(int nNumberOfVertices, KMVERTEX_03 *pTLVertex,
			  				   int nNumberOfTriangles, int *pTriangleList, int *pNumberOfVisibleTriangles,
							   const float D, const float F, const float fViewAngle);

/* From KMLight.c */
void KMLightSmoothShade(MATRIX *pMatrix, 
				 int nNumberOfVertices, float *pNormals, KMVERTEX_03 *pTLVertex, 
				 km_vector LightVector, KMDWORD dwLightColour, int bUseSpecular);
				 
void KMLightSpecular(const MATRIX *pWorldMatrix,
					   const int nNumberOfVertices, const float *pNormals,
					   const float *pVertex, KMVERTEX_03 *pTLVertex,
					   const km_vector pLightVector, const km_vector pCamWorldPos,
					   const KMDWORD cDiffuse, const KMDWORD cSpecular,
					   const float fSpecularPower);



/* From KMTimer.c */
double	KMTimerGetFPS (void);

/* From KMTexture.c */
void KMTextureSetMipmapMethod(DWORD dwMM_Method);

KMDWORD KMTextureConvertAndLoad(KMSURFACEDESC *pTexSurfaceDesc, unsigned char *pSource, 
		unsigned char *pTransSource, KMINT32 SizeX, KMINT32 SizeY, KMTEXTURETYPE nTextureType);


/* From KMABCTable.c */
KMDWORD KMABCTableInit (int IsTranslucent);
void	KMABCTablePrint3D (float XPos, float YPos, float fScale, int Color,char *Format, ...);
void	KMABCTableRelease (void);

/* From KMBump.c */

/*
 *  Calculates Bump-map angles and smooth shading 
 *  Notes:
 *  Set the parameter *pTLVertexObject to NULL if you only want to calculate Bumpmap.
 *  This method uses the local coordinate systems calculated by 
 *  KMBumpCalculateLocalCoords().
 *	Call this funtion every frame to get a correct phong bumpmapping.
 */
void KMBumpShade(MATRIX *pMatrix, 
				 unsigned nNumberOfVertices, float *pBumpCoords, float *pNormals,
				 KMVERTEX_03 *pTLVertexBump, KMVERTEX_03 *pTLVertexObject,
				 km_vector LightVector, int nMethod);

/*
 *  Calculates Bump-map angles only (tricky way).
 *  Notes:
 *  This method is fast and cheap, but the look is not very correct.
 *  It doesn't need local co-ordinate systems, but only works with 
 *  upright textures.
 *	If the light is very close to X=0 Y=0 the bumpmap jumps very quickly.
 */
void KMCheapBumpShade(MATRIX *pMatrix,  unsigned nNumberOfVertices, 
						KMVERTEX_03 *pTLVertexBump, km_vector LightVector, int nMethod);


/*
 *  Calculates the local coordinate systems for KMBumpShade() and for Naomi2 hardware.
 *	Note: This function has to be called once at the begining of the application.
 *  The array pBumpCoords has to be allocated by the user. Its size is:
 *   NumberOfVertices * 6 * sizeof(float)
 */
void KMBumpCalculateLocalCoords (float *pBumpCoords, int CreationMode,
								 unsigned nNumberOfVertices, float *ptVertex,float *ptNormals, float *ptUV, 
							     unsigned nNumFaces, unsigned short *ptFaces);

/* From KMMisc.c */
long		KMMiscRand					(void);
void		KMMiscSeedRand				(unsigned long Seed);


/* From KMPrint3D.c */

#define FONT_SYSTEM -1.0f
#define FONT_ARIAL   1.0f

/* dwFlags for KMPrint3DSetWindowFlags */
static enum {
	PRINT3D_ACTIVATE_WIN		=	0x01,
	PRINT3D_DEACTIVATE_WIN		=	0x02,
	PRINT3D_ACTIVATE_TITLE		=	0x04,
	PRINT3D_DEACTIVATE_TITLE	=	0x08,
	PRINT3D_FULL_OPAQUE			=	0x10,
	PRINT3D_FULL_TRANS			=	0x20,
	PRINT3D_ADJUST_SIZE_ALWAYS	=	0x40,
	PRINT3D_NO_BORDER			=	0x80,
} PRINT3D_FLAGS;

/**************/
/* Prototypes */
/**************/

/* Always in InitView */
int KMPrint3DSetTextures(void);

/* Always in ReleaseView */
void  KMPrint3DReleaseTextures (void);

/* Screen Output */
void KMPrint3D (float XPos, float YPos, float fScale,  int Colour, const char *Format, ...);

/* Creates a default window.
   If Title is NULL the main body will have just one line (for InfoWin) 
*/
KMDWORD KMPrint3DCreateDefaultWindow (float fPosX, float fPosY, int nXSize_LettersPerLine, char *sTitle, char *sBody);

/* Creates a window and returns a handle to that window */
KMDWORD KMPrint3DCreateWindow	(KMDWORD dwBufferSizeX, KMDWORD dwBufferSizeY);

/* Free memory allocated with CreateWindow */
void KMPrint3DDeleteWindow(KMDWORD dwWin);

/* Free memory allocated with CreateWindow for all the windows*/
void KMPrint3DDeleteAllWindows(void);

/* Display the window (must be between BeginScene-EndScene)*/
void KMPrint3DDisplayWindow (KMDWORD dwWin);

/* Display All (must be between BeginScene-EndScene)*/
void KMPrint3DDisplayAllWindows(void);

/* Feed the text buffer */
void KMPrint3DWindowOutput	(KMDWORD dwWin, const char *Format, ...);

/* Clean the text buffer */
void KMPrint3DClearWindowBuffer(KMDWORD dwWin);

/* User values for the window.
 * Windows position and size are referred to a virtual screen of 100x100,
 * (0,0) is the top-left corner and (100,100) the bottom-right corner.
 * These values are the same for all resolutions.
 */
void  KMPrint3DSetWindow		(KMDWORD dwWin, KMDWORD dwBackgroundColor, KMDWORD dwFontColor, float fFontSize, 
								float fPosX, float fPosY, float fSizeX, float fSizeY);

/* User values for the title */
void KMPrint3DSetTitle	(KMDWORD dwWin, KMDWORD dwBackgroundColor, float fFontSize, 
								KMDWORD dwFontColorLeft, char *sTitleLeft, 
								KMDWORD dwFontColorRigth, char *sTitleRight);
/* Setting flags */
void KMPrint3DSetWindowFlags (KMDWORD dwWin, KMDWORD dwFlags);

/* Cursor position for the next OutputWindow */
void KMPrint3DSetWindowBufferPointer(KMDWORD dwWin, KMDWORD dwXPos, KMDWORD dwYPos);

/* Calculates window size to display everything.
 * (dwMode 0 = Both, dwMode 1 = X only,  dwMode 2 = Y only) 
 */
void KMPrint3DAdjustWindowSize(KMDWORD dwWin, KMDWORD dwMode);

/* This window on the top of everything */
void KMPrint3DSetTopMostWindow(KMDWORD dwWin);

/* Window position */
void KMPrint3DSetWindowPos(KMDWORD dwWin, float fPosX, float fPosY);

/* Window size */
void KMPrint3DSetWindowSize(KMDWORD dwWin, float fSizeX, float fSizeY);


void KMTransRetroProject (MATRIX *pWorldMatrix, 
										 float Vx, float Vy, float Dy, float Result[2],
										 int nViewportWidth, int nViewportHeight,
										 const km_vector CamFrom, const km_vector CamTo, const float fRoll,
										 const float D, const float F, const float fViewAngle);
										 

#ifdef __cplusplus
}
#endif


#endif

