/***********************************************************************
   Name   : Tools.h   
   Author : Carlos Sarria (Matrix code is Jim's)
   Date   : October 1997

   Copyright : 1997 by VideoLogic Limited. All rights reserved.
   Modified  : 01, February, 1999 by Hiroshi Nakayama for KAMUI2
 ***********************************************************************/
#ifndef TOOLSH
#define TOOLSH

#define		_DISPLAY_STRING_
/* if defined then display strings on screen */

#define		_DISP_PERFORMANCE_
/* Display performance : for windows */

#include	"kamui2.h"				/* for Kamui Call */
#include	"dispstr.h"				/* for DisplayString */

#define	RGBColour(r, g, b)	((KMUINT32) (((r) << 16) | ((g) << 8) | (b)))
#define	RGBA(r, g, b, a)	((KMUINT32) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b)))

/* Macros for kamui */
#define		GetRED(col)			((KMFLOAT) ( ((col) & 0x00ff0000) >> 16 ) / 256.0f)
#define		GetGREEN(col)		((KMFLOAT) ( ((col) & 0x0000ff00) >>  8 ) / 256.0f)
#define		GetBLUE(col)		((KMFLOAT) ( ((col) & 0x000000ff)       ) / 256.0f)
#define		GetALPHA(col)		((KMFLOAT) ( ((col) & 0xff000000) >> 24 ) / 256.0f)

/* --------- */
/* PVRVERTEX */
/* --------- */
/* This structure is currently physically equivalent to Direct3D's D3DTLVERTEX */
/* (so one can be cast to the other), with the exception that Direct3D's u and */
/* v values must be multiplied by the 1/w value.  RAVE vertices already contain */
/* u/w and v/w. */
typedef struct tagPVRVERTEX
{
	/* Projected screen coordinates: */
	float		fX;		/* 0 <= fX < screen width (up to 1024) */
	float		fY;		/* 0 <= fY < screen height (up to 1024) */
	float		fZ;		/* 0.01 <= fZ <= 1, where 1 is infinite distance away */
	/* 1/w for the perspective projection (should be set to 1.0/fZ; fZ is */
	/* actually ignored): */
	float		fInvW;
	float		fU;		/* U */
	float		fV;		/* V */
	KMUINT32	u32Colour;			/* Material colour (D3DCOLOR format): */
	KMUINT32	u32Specular;		/* Specular colour (D3DCOLOR format): */
	float		fUOverW, fVOverW;	/* Texture coordinates: */
} PVRVERTEX, *PPVRVERTEX;
/***********************************************************************/

#define PI				     3.1415926f
#define ONEOVERTWOPI	     1.0f/(2.0f*PI)

#define Z_ZERO			     300
#define CAM_FOCUS            600.0f
#define BILINEAR_CORRECTION  1.0f/256.0f

#define RESET_TIME           0
#define DISPLAY_TIME         1
#define ACTUALIZE_TIME		 2
#define HARD_TIME            3

#define FX_NONE		0
#define FX_OPTIC	1
#define FX_PLANAR	2

#define C_NONE		0
#define C_WHITE     0
#define C_BLACK		1
#define C_RED		2
#define C_GREEN     3
#define C_BLUE		4
#define C_YELLOW	5
#define C_BROWN     6
#define C_GREY		7
#define C_PLAIN     8

#define K_ESC    27
#define K_SPC    32
#define K_F1     59
#define K_F2     60
#define K_F3     61
#define K_F4     62
#define K_F5     63
#define K_F6     64
#define K_F7     65
#define K_F8     66
#define K_F9     67
#define K_F10    68
#define K_F11    133
#define K_F12    134
#define K_UP     72
#define K_DOWN   80
#define K_LEFT   75
#define K_RIGHT  77

typedef struct tagTRANSFORM
{
	float Matrix[3][4];
	float Inverse[3][4];

} TRANSFORM;

typedef struct tagINFO
{
	int		OpaqMap;
	int		Textured;
	int		Gouraud;
	int		GlobalTrans;
	int		VertexAlpha;
	int		TableFog;
	int		VertexFog;
	int		Bilinear;
	int		Highlight;
	int		Strips;

} INFO;


 typedef struct TagCastMeshes 
 { 
	int   NumVertex; 
    int   NumFaces;
    int   TexMap;
    int   Material;
    float Center[3];
    float *Vertex;
    float *UV;
    float *Normals;
    int   *Faces;

 } CASTMESHES;


#define RGBAColour(r, g, b, a)   ((unsigned long) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b)))

/********************/
/* Kamui prototypes */
/********************/
void	Check_Status(KMSTATUS status, char *func);
void 
kmtri_triangles ( PKMVERTEXBUFFDESC		pBufferDesc,
				  PKMSTRIPHEAD			pStripHead,
				  int  					nNumFaces,
				  int  					pFaces[][3],
				  PPVRVERTEX  			pVertices,
				  int					bTexture);
void 
kmtri_quads (	KMVERTEXBUFFDESC	BufferDesc,
				KMVERTEXCONTEXT		VertexContext,
				int					nNumFaces,
				int					pFaces[][4],
				PPVRVERTEX			pVertices,
				int					bTexture);
void 
kmtri_tstrips ( KMVERTEXBUFFDESC	BufferDesc,
				KMVERTEXCONTEXT		VertexContext,
				int					nNumFaces,
				int					*StripLengths,
				PPVRVERTEX  		pVertices,
				int					bTexture);
void 
kmtri_shadow (	KMVERTEXBUFFDESC		BufferDesc,
				KMVERTEXCONTEXT			VertexContextFirst,
				KMVERTEXCONTEXT			VertexContextNormal,
				KMVERTEXCONTEXT			VertexContextLast,
				int						nNumFaces,
				int						pFaces[][3],
				PPVRVERTEX				pVertices );
void	InitVertexContext(PKMVERTEXCONTEXT pVertexContext);

/**************/
/* prototypes */
/**************/
void ResetMatrix		(int Object);
void Rotate				(int Object, float Axis[3], float Theta);
void Scale				(int Object, float SX,  float SY,  float SZ);
void Translate			(int Object, float TrX, float TrY, float TrZ);
void InitScene			(void);
void EndScene			(void);
void InitMeshes			(int nMeshes, CASTMESHES *pMeshes);
void FreeMeshes			(int nMeshes);
void SetVertices 		(int Object, PKMSTRIPHEAD pStripHead, int Effect, int bTexture);
void SetUV				(int Object);
void SetSmoothShading	(int Object, int Color);
void Timer				(void);
void Print3D			(float PosX, float PosY, float PosZ, char *Text);
void SetBackground		(PKMSURFACEDESC TextureID);
void SetContext			(PKMSTRIPHEAD pStripHead,INFO CInfo,PKMSURFACEDESC pTexture);
void InitContext 		(PKMSTRIPCONTEXT pStripContext,PKMSTRIPHEAD	pStripHead,INFO CInfo,PKMSURFACEDESC pTexture);


#endif

