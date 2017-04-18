/********************************************************************************/
/* Name     : kmDirectSeal														*/
/* Title    : KAMUI test program "DirectSeal" from VL							*/
/* Author   : VideoLogic Carlos Sarria / NEC Software Takeshi Muto				*/
/* Created  : March 1997 by VideoLogic											*/
/* Modified :	Octover  18. 1997 by Takeshi Muto for KAMUI						*/
/*				April    16. 1998 by Takeshi Muto for KAMUI SET5				*/
/*				February 16. 1999 by Hiroshi Nakayama for KAMUI2 				*/
/*				February 17. 1999 by Takeshi Muto for Shinobi					*/
/* Description :  																*/
/********************************************************************************/
#if 0
#define		_NOWAIT_VSYNC_			/* 非同期モード使用時は定義する					*/
#define		_VERTEXMACRO_L4_		/* VertexMacroLevel4使用時は定義する			*/
#endif

#define		FRAMES			(1000000)				/* rendering frame number */
#define		SPEED			(1.5f)					/* pet move speed ( 1 to n ) */

#define		SUPERSAMPLE		TRUE
/*#define		SUPERSAMPLE		FALSE*/
/* Super sample filter mode */

#define		_DISPLAY_STRING_
/* if defined then display strings on screen */

#define		_DISP_PERFORMANCE_
/* Display performance : for windows */

#include	<math.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<float.h>
#include	<Shinobi.h>
#include	<sg_sytmr.h>	/* System timer */

#pragma warning (disable : 4244) /* Disables float to double conversion warning */
#pragma warning (disable : 4056)

#include	"kamui2.h"				/* for Kamui Call */
#include	"dispstr.h"				/* for DisplayString */

#if defined(_VERTEXMACRO_L4_)
#define _KM_USE_VERTEX_MACRO_L4_
#include "kamuix.h"
#endif

#include	"vltex.h"

/*******************************************************************************/
#define PI (3.142f)

#define	RGBColour(r, g, b)	((KMUINT32) (((r) << 16) | ((g) << 8) | (b)))
#define	RGBA(r, g, b, a)	((KMUINT32) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b)))

/* Macros for kamui */
#define		GetRED(col)			((KMFLOAT) ( ((col) & 0x00ff0000) >> 16 ) / 256.0f)
#define		GetGREEN(col)		((KMFLOAT) ( ((col) & 0x0000ff00) >>  8 ) / 256.0f)
#define		GetBLUE(col)		((KMFLOAT) ( ((col) & 0x000000ff)       ) / 256.0f)
#define		GetALPHA(col)		((KMFLOAT) ( ((col) & 0xff000000) >> 24 ) / 256.0f)

/* 互換TYPE */
typedef float	km_vector[3];	/* type of pvr_vector */
typedef float	km_2d_vec[2];	/* type of pvr_2d_vec */
typedef float	km_colour[3];	/* type of pvr_colour */
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
	KMUINT32	u32Colour;			/* Material colour (D3DCOLOR format): */
	KMUINT32	u32Specular;		/* Specular colour (D3DCOLOR format): */
	float		fUOverW, fVOverW;	/* Texture coordinates: */
} PVRVERTEX, *PPVRVERTEX;

/****************************************************************************/
/**	Valuables for KAMUI *****************************************************/
/****************************************************************************/
	KMSTATUS			status;					/* return status of KAMUI API */
	KMVERSIONINFO		VersionInfo;			/* KAMUI Version information */
	KMSURFACEDESC		PrimarySurfaceDesc;		/* Primary frame buffer */
	KMSURFACEDESC		BackSurfaceDesc;		/* Back-buffer frame buffer */
	KMSURFACEDESC		SeaTex;					/* texture surface */
	KMSURFACEDESC		SealTex;				/* texture surface */
	KMSURFACEDESC		GroundTex;				/* texture surface */
	KMSURFACEDESC		SkyTex;					/* texture surface */
	KMVERTEXBUFFDESC	VertexBufferDesc;		/* Vertex-buffer */
	KMSTRIPCONTEXT		StripContextGround;		/* Strip context */
	KMSTRIPHEAD			StripHeadGround;		/* Strip head */
	KMSTRIPCONTEXT		StripContextSky;		/* Strip context */
	KMSTRIPHEAD			StripHeadSky;			/* Strip head */
	KMSTRIPCONTEXT		StripContextSea;		/* Strip context */
	KMSTRIPHEAD			StripHeadSea;			/* Strip head */
	KMSTRIPCONTEXT		StripContextSeal;		/* Strip context */
	KMSTRIPHEAD			StripHeadSeal;			/* Strip head */
	PKMSURFACEDESC			pFB[2];
	KMDWORD				FBarea[24576 + 19456];
								/* FBstruct 4096 Entry (= 4096 * 24 / 4) */
								/* VQstruct 1024 Entry (= 1024 * 76 / 4) */
	KMSYSTEMCONFIGSTRUCT	SystemConfig;
	PKMDWORD				dwDataPtr;

/* 性能測定用変数 */
	int			frame;				/* 画面フレーム */
	int			frame_2 = 0;		/* 画面フレーム上位 */
#if defined(_DISP_PERFORMANCE_)
	Uint32		StartTime = 0;
	Uint32		EndTime;
	double		nowTime;
	double		nFPS;				/* 現在の性能(Frame/Second)				*/
	double		aFPS;				/* 性能の平均値							*/
	double		MxFPS;				/* 最高性能								*/
	double		MnFPS;				/* 最低性能								*/
	double		maxTime = 0.00001;	/* 最高描画時間(msec)					*/
	double		minTime = 99999;	/* 最低描画時間(msec)					*/
	double		totalTime	= 0;	/* 累積render時間(msec)					*/
	double		aveTime;			/* 平均描画時間(msec)					*/
#endif

/*------------------------------- Global Variables -----------------------------------*/
int Spd, Poll;

km_vector PetPath [20];
float	PetTime		=  0.0f, VelH = 0.3f;
float	PetPosY		= 10.0f, dY   = 0.3f,   Radius = 50.0f,   TPet = 3.0f;
float	SeaFrame	= 10.0f, SF   = 1.0f;
float	SkyFrame	= 10.0f;

km_colour	PollCol[3] = {{0.1f,0.5f,0.7f},{0.1f,0.3f,0.5f},{0.1f,0.1f,0.1f}};
int			PollFog[3] = { 9, 10, 12};

float CamFocus = 1500.0;

/*PVRCONTEXT PVRContext; */
PVRVERTEX  SealVert  [20*10],   ShadowVert  [2*11];
int        SealFaces [20*9][4], ShadowFaces [11][4];

/* PCX : PVR-Direct fog table */
static KMUINT32 PCXFogTable[]={
	0x000000ff,	0x000000fe,	0x000000fd,	0x000000fb,	0x000000fa,	0x000000f9,	0x000000f7,	0x000000f6,
	0x000000f5,	0x000000f3,	0x000000f2,	0x000000f1,	0x000000ef,	0x000000ee,	0x000000ed,	0x000000ec,
	0x000000ea,	0x000000e9,	0x000000e8,	0x000000e6,	0x000000e5,	0x000000e4,	0x000000e3,	0x000000e2,
	0x000000e0,	0x000000df,	0x000000de,	0x000000dd,	0x000000db,	0x000000da,	0x000000d9,	0x000000d8,
	0x000000d7,	0x000000d6,	0x000000d4,	0x000000d3,	0x000000d2,	0x000000d1,	0x000000d0,	0x000000cf,
	0x000000ce,	0x000000cd,	0x000000cb,	0x000000ca,	0x000000c9,	0x000000c8,	0x000000c7,	0x000000c6,
	0x000000c5,	0x000000c4,	0x000000c3,	0x000000c2,	0x000000c1,	0x000000c0,	0x000000bf,	0x000000be,
	0x000000bd,	0x000000bc,	0x000000ba,	0x000000b9,	0x000000b8,	0x000000b7,	0x000000b6,	0x000000b6,
	0x000000b5,	0x000000b4,	0x000000b3,	0x000000b2,	0x000000b1,	0x000000b0,	0x000000af,	0x000000ae,
	0x000000ad,	0x000000ac,	0x000000ab,	0x000000aa,	0x000000a9,	0x000000a8,	0x000000a7,	0x000000a6,
	0x000000a5,	0x000000a5,	0x000000a4,	0x000000a3,	0x000000a2,	0x000000a1,	0x000000a0,	0x0000009f,
	0x0000009e,	0x0000009e,	0x0000009d,	0x0000009c,	0x0000009b,	0x0000009a,	0x00000099,	0x00000099,
	0x00000098,	0x00000097,	0x00000096,	0x00000095,	0x00000094,	0x00000094,	0x00000093,	0x00000092,
	0x00000091,	0x00000090,	0x00000090,	0x0000008f,	0x0000008e,	0x0000008d,	0x0000008d,	0x0000008c,
	0x0000008b,	0x0000008a,	0x0000008a,	0x00000089,	0x00000088,	0x00000087,	0x00000087,	0x00000086,
	0x00000085,	0x00000084,	0x00000084,	0x00000083,	0x00000082,	0x00000082,	0x00000081,	0x00000080
};

/*----------------------------  Routines Prototypes ---------------------------------*/

void SetupContext  (void),
     SetupPet      (void),
     SetupTextures (void);

void DrawGround    (void),
     DrawSky       (void),
     DrawSea       (void),
     MovePet       (void),
     DrawPet       (void);

void Perspect      (const km_vector Point3D, PVRVERTEX *Vert);

/****************************************************************************/
/**	Check KAMUI function status *********************************************/
/****************************************************************************/
void	Check_Status(KMSTATUS status, char * func)
{
	switch(status)
	{
		case KMSTATUS_SUCCESS:
			/* No message is displayed when SUCCESS */
			break;
		case KMSTATUS_INVALID_DISPLAY_MODE:
			PRINTOUT(("%s:KMSTATUS_INVALID_DISPLAY_MODE\n",func)); break;
		case KMSTATUS_INVALID_VIDEO_MODE:
			PRINTOUT(("%s:KMSTATUS_INVALID_VIDEO_MODE\n",func)); break;
		case KMSTATUS_NOT_ENOUGH_MEMORY:
			PRINTOUT(("%s:KMSTATUS_NOT_ENOUGH_MEMORY\n",func)); break;
		case KMSTATUS_INVALID_TEXTURE_TYPE:
			PRINTOUT(("%s:KMSTATUS_INVALID_TEXTURE_TYPE\n",func)); break;
		case KMSTATUS_INVALID_MIPMAPED_TEXTURE:
			PRINTOUT(("%s:KMSTATUS_INVALID_MIPMAPED_TEXTURE\n",func)); break;
		case KMSTATUS_CANT_FLIP_SURFACE:
			PRINTOUT(("%s:KMSTATUS_CANT_FLIP_SURFACE\n",func)); break;
		case KMSTATUS_INVALID_ADDRESS:
			PRINTOUT(("%s:KMSTATUS_INVALID_ADDRESS\n",func)); break;
		case KMSTATUS_HARDWARE_NOT_PRESENTED:
			PRINTOUT(("%s:KMSTATUS_HARDWARE_NOT_PRESENTED\n",func)); break;
		case KMSTATUS_INVALID_SETTING:
			PRINTOUT(("%s:KMSTATUS_INVALID_SETTING\n",func)); break;
		case KMSTATUS_INVALID_VERTEX_TYPE:
			PRINTOUT(("%s:KMSTATUS_INVALID_VERTEX_TYPE\n",func)); break;
		case KMSTATUS_NOT_IMPLEMENTED:
			PRINTOUT(("%s:KMSTATUS_NOT_IMPREMENTED\n",func)); break;
		case KMSTATUS_INVALID_PARAMETER:
			PRINTOUT(("%s:KMSTATUS_INVALID_PARAMETER\n",func)); break;
		default:
			PRINTOUT(("%s:???Undefined status : %d\n", func, status));
			break;
	}
}

/****************************************************************************/
/**	Background surface setting **********************************************/
/****************************************************************************/
void	InitBackGround(void)
{
	KMSTATUS			status;
	KMVERTEXCONTEXT		BackVertexContext;		/* Vertex context */
	KMVERTEX_00			BV[3];					/* pointer to Vertex */
	PVOID				pBV[3];					/* pointer to Vertex */

	/* Clear VertexContext */
	memset(&BackVertexContext,0,sizeof(KMVERTEXCONTEXT));

	/* Setup VertexContext */
	BackVertexContext.RenderState	= KM_DEPTHMODE  		| KM_CULLINGMODE				/* ISP/TSP IW */
									| KM_SCREENCOORDINATION	| KM_SHADINGMODE
									| KM_MODIFIER 			| KM_ZWRITEDISABLE				/* TSP CW */
									| KM_SRCBLENDINGMODE
									| KM_SRCSELECT			| KM_DSTSELECT
									| KM_FOGMODE			| KM_USESPECULAR
									| KM_USEALPHA			| KM_IGNORETEXTUREALPHA
									| KM_FLIPUV 			| KM_CLAMPUV
									| KM_FILTERMODE			| KM_SUPERSAMPLE
									| KM_MIPMAPDADJUST 		| KM_TEXTURESHADINGMODE
									| KM_PARAMTYPE 			| KM_LISTTYPE 					/* Param CW */
									| KM_COLORTYPE			| KM_USESPECULAR
									| KM_UVFORMAT;

	/* for ParameterControlWord  */
	BackVertexContext.ParamType				= KM_POLYGON;
	BackVertexContext.ListType				= KM_OPAQUE_POLYGON;
	BackVertexContext.ColorType				= KM_PACKEDCOLOR;
	BackVertexContext.bUseSpecular			= FALSE;
	BackVertexContext.UVFormat				= KM_32BITUV;

	/* for ISP/TSP InstructionWord  */
	BackVertexContext.DepthMode				= KM_GREATER;
	BackVertexContext.CullingMode			= KM_NOCULLING;
/*	BackVertexContext.ScreenCoordination	= KM_SCREEN;*/
	BackVertexContext.ShadingMode			= KM_NOTEXTUREGOURAUD;
	BackVertexContext.SelectModifier		= KM_NOMODIFIER;
	BackVertexContext.bZWriteDisable		= FALSE;			/* not effective on ARC1 */

	/* for TSP ControlWord  */
	BackVertexContext.SRCBlendingMode		= KM_ONE;
/*	BackVertexContext.DSTBlendingMode		= KM_ZERO;	// must not set this parameter on background plane */
	BackVertexContext.bSRCSel				= FALSE;			/* not effective on ARC1 */
	BackVertexContext.bDSTSel				= FALSE;			/* not effective on ARC1 */
	BackVertexContext.FogMode				= KM_FOGTABLE;		/* 11 is reserved */
	BackVertexContext.bUseSpecular			= FALSE;
	BackVertexContext.bUseAlpha				= FALSE;
	BackVertexContext.ClampUV				= KM_NOCLAMP;
	BackVertexContext.FilterMode			= KM_POINT_SAMPLE;
	BackVertexContext.bSuperSample			= SUPERSAMPLE;
	BackVertexContext.MipMapAdjust			= 0x00000004;		/* D=1.00 */
	BackVertexContext.TextureShadingMode	= KM_MODULATE;

	/* for Texture ControlBit */

	/* No effect on ARC1 */
	BackVertexContext.bColorClamp			= FALSE;
	BackVertexContext.PaletteBank			= 0;

	/* for GlobalColorData */
	BackVertexContext.fFaceColorAlpha		= 1.0f;		/* Face Color Alpha */
	BackVertexContext.fFaceColorRed			= 1.0f;		/* Face Color Red */
	BackVertexContext.fFaceColorGreen		= 1.0f;		/* Face Color Green */
	BackVertexContext.fFaceColorBlue		= 1.0f;		/* Face Color Blue */
	BackVertexContext.fOffsetColorAlpha		= 1.0f;		/* Specular Color Alpha */
	BackVertexContext.fOffsetColorRed		= 1.0f;		/* Specular Color Red */
	BackVertexContext.fOffsetColorGreen		= 1.0f;		/* Specular Color Green */
	BackVertexContext.fOffsetColorBlue		= 1.0f;		/* Specular Color Blue */

	status = kmProcessVertexRenderState(&BackVertexContext);
	Check_Status(status, "kmProcessVertexRenderState");
	status = kmSetBackGroundRenderState(&BackVertexContext);
	Check_Status(status, "kmSetBackGroundRenderState");

	/*----------------------------------------------------------------------------------- */
	/* set VERTEX DATA */

	/* Vertex #1 */
	BV[0].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
	BV[0].fX				=  2.0f;
	BV[0].fY				= 260.0f;
#if defined(_STRICT_UNION_)
	BV[0].u.fZ				=  0.0001f;
#else
	BV[0].fZ				=  0.0001f;
#endif
	BV[0].uBaseRGB.dwPacked	= RGBA(0, 0, 0, 255);

	/* Vertex #2 */
	BV[1].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
	BV[1].fX				= 150.0f;
	BV[1].fY				=  2.0f;
#if defined(_STRICT_UNION_)
	BV[1].u.fZ				=  0.0001f;
#else
	BV[1].fZ				=  0.0001f;
#endif
	BV[1].uBaseRGB.dwPacked	= RGBA(0, 0, 0, 255);

	/* Vertex #3 */
	BV[2].ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;
	BV[2].fX				= 560.0f;
	BV[2].fY				= 260.0f;
#if defined(_STRICT_UNION_)
	BV[2].u.fZ				=  0.0001f;
#else
	BV[2].fZ				=  0.0001f;
#endif
	BV[2].uBaseRGB.dwPacked	= RGBA(0, 0, 0, 255);

	pBV[0] = &BV[0];
	pBV[1] = &BV[1];
	pBV[2] = &BV[2];

	/*----------------------------------------------------------------------------------- */
	/* set VERTEX */
	status = kmSetBackGroundPlane(	pBV,					/* pVertex */
									KM_VERTEXTYPE_00,		/* VertexType */
									sizeof(KMVERTEX_00)		/* StructSize */
									);
	Check_Status(status, "kmSetBackGroundPlane");
}

/****************************************************************************/
/**	kmtri_quads  by T.Hirata ************************************************/
/****************************************************************************/
void
kmtri_quads (	KMVERTEXBUFFDESC	BufferDesc,
				PKMSTRIPHEAD		pStripHead,
				int  nNumFaces,
				int  pFaces[][4],
				PPVRVERTEX  pVertices )
{
	KMSTATUS	status;
	int			i;
	KMVERTEX_03	Ver03;

	kmStartStrip( &BufferDesc , pStripHead );			/* 頂点登録開始 */

#if defined(_VERTEXMACRO_L4_)
	kmxxGetCurrentPtr(&BufferDesc);
#endif

	for(i = 0; i < nNumFaces; i++)
	{
#if defined(_VERTEXMACRO_L4_)
			kmxxSetVertex_3(	KM_VERTEXPARAM_NORMAL,
								pVertices[pFaces[i][0]].fX,
								pVertices[pFaces[i][0]].fY,
								pVertices[pFaces[i][0]].fInvW,
								pVertices[pFaces[i][0]].fUOverW,
								pVertices[pFaces[i][0]].fVOverW,
								pVertices[pFaces[i][0]].u32Colour,
								pVertices[pFaces[i][0]].u32Specular
							);

			kmxxSetVertex_3(	KM_VERTEXPARAM_NORMAL,
								pVertices[pFaces[i][1]].fX,
								pVertices[pFaces[i][1]].fY,
								pVertices[pFaces[i][1]].fInvW,
								pVertices[pFaces[i][1]].fUOverW,
								pVertices[pFaces[i][1]].fVOverW,
								pVertices[pFaces[i][1]].u32Colour,
								pVertices[pFaces[i][1]].u32Specular
							);

			kmxxSetVertex_3(	KM_VERTEXPARAM_NORMAL,
								pVertices[pFaces[i][3]].fX,
								pVertices[pFaces[i][3]].fY,
								pVertices[pFaces[i][3]].fInvW,
								pVertices[pFaces[i][3]].fUOverW,
								pVertices[pFaces[i][3]].fVOverW,
								pVertices[pFaces[i][3]].u32Colour,
								pVertices[pFaces[i][3]].u32Specular
							);

			kmxxSetVertex_3(	KM_VERTEXPARAM_ENDOFSTRIP,
								pVertices[pFaces[i][2]].fX,
								pVertices[pFaces[i][2]].fY,
								pVertices[pFaces[i][2]].fInvW,
								pVertices[pFaces[i][2]].fUOverW,
								pVertices[pFaces[i][2]].fVOverW,
								pVertices[pFaces[i][2]].u32Colour,
								pVertices[pFaces[i][2]].u32Specular
							);
#else
			Ver03.ParamControlWord		= KM_VERTEXPARAM_NORMAL;
			Ver03.fX					= pVertices[pFaces[i][0]].fX;
			Ver03.fY					= pVertices[pFaces[i][0]].fY;
#if defined(_STRICT_UNION_)
			Ver03.u.fZ					= pVertices[pFaces[i][0]].fInvW;
#else
			Ver03.fZ					= pVertices[pFaces[i][0]].fInvW;
#endif
			Ver03.fU					= pVertices[pFaces[i][0]].fUOverW;
			Ver03.fV					= pVertices[pFaces[i][0]].fVOverW;
			Ver03.uBaseRGB.dwPacked		= pVertices[pFaces[i][0]].u32Colour;
			Ver03.uOffsetRGB.dwPacked	= pVertices[pFaces[i][0]].u32Specular;
			status = kmSetVertex(&BufferDesc,&Ver03,KM_VERTEXTYPE_03,sizeof(KMVERTEX_03) );
			Check_Status(status, "kmSetVertex");

			Ver03.ParamControlWord		= KM_VERTEXPARAM_NORMAL;
			Ver03.fX					= pVertices[pFaces[i][1]].fX;
			Ver03.fY					= pVertices[pFaces[i][1]].fY;
#if defined(_STRICT_UNION_)
			Ver03.u.fZ					= pVertices[pFaces[i][1]].fInvW;
#else
			Ver03.fZ					= pVertices[pFaces[i][1]].fInvW;
#endif
			Ver03.fU					= pVertices[pFaces[i][1]].fUOverW;
			Ver03.fV					= pVertices[pFaces[i][1]].fVOverW;
			Ver03.uBaseRGB.dwPacked		= pVertices[pFaces[i][1]].u32Colour;
			Ver03.uOffsetRGB.dwPacked	= pVertices[pFaces[i][1]].u32Specular;
			status = kmSetVertex(&BufferDesc,&Ver03,KM_VERTEXTYPE_03,sizeof(KMVERTEX_03) );
			Check_Status(status, "kmSetVertex");

			Ver03.ParamControlWord		= KM_VERTEXPARAM_NORMAL;
			Ver03.fX					= pVertices[pFaces[i][3]].fX;
			Ver03.fY					= pVertices[pFaces[i][3]].fY;
#if defined(_STRICT_UNION_)
			Ver03.u.fZ					= pVertices[pFaces[i][3]].fInvW;
#else
			Ver03.fZ					= pVertices[pFaces[i][3]].fInvW;
#endif
			Ver03.fU					= pVertices[pFaces[i][3]].fUOverW;
			Ver03.fV					= pVertices[pFaces[i][3]].fVOverW;
			Ver03.uBaseRGB.dwPacked		= pVertices[pFaces[i][3]].u32Colour;
			Ver03.uOffsetRGB.dwPacked	= pVertices[pFaces[i][3]].u32Specular;
			status = kmSetVertex(&BufferDesc,&Ver03,KM_VERTEXTYPE_03,sizeof(KMVERTEX_03) );
			Check_Status(status, "kmSetVertex");

			Ver03.ParamControlWord		= KM_VERTEXPARAM_ENDOFSTRIP;
			Ver03.fX					= pVertices[pFaces[i][2]].fX;
			Ver03.fY					= pVertices[pFaces[i][2]].fY;
#if defined(_STRICT_UNION_)
			Ver03.u.fZ					= pVertices[pFaces[i][2]].fInvW;
#else
			Ver03.fZ					= pVertices[pFaces[i][2]].fInvW;
#endif
			Ver03.fU					= pVertices[pFaces[i][2]].fUOverW;
			Ver03.fV					= pVertices[pFaces[i][2]].fVOverW;
			Ver03.uBaseRGB.dwPacked		= pVertices[pFaces[i][2]].u32Colour;
			Ver03.uOffsetRGB.dwPacked	= pVertices[pFaces[i][2]].u32Specular;
			status = kmSetVertex(&BufferDesc,&Ver03,KM_VERTEXTYPE_03,sizeof(KMVERTEX_03) );
			Check_Status(status, "kmSetVertex");
#endif
	}

#if defined(_VERTEXMACRO_L4_)
	kmxxReleaseCurrentPtr(&BufferDesc);
#endif

	kmEndStrip(&BufferDesc);		/* 頂点登録終了 */
}

/***************************************
 *	VertexType03用KMSTRIPHEADの構築
 ***************************************/
void	InitStripContext03(
							PKMSTRIPCONTEXT pStripContext,	/* Strip context */
							PKMSTRIPHEAD    pStripHead,		/* Strip header */
							PKMSURFACEDESC	pTexture		/* Texture surface */
		)
{
	pStripContext->nSize						 					= sizeof(KMSTRIPCONTEXT);
	pStripContext->StripControl.nListType							= KM_OPAQUE_POLYGON;
	pStripContext->StripControl.nUserClipMode						= KM_USERCLIP_DISABLE;
	pStripContext->StripControl.nShadowMode							= KM_NORMAL_POLYGON;
	pStripContext->StripControl.bOffset								= KM_FALSE;
	pStripContext->StripControl.bGouraud							= KM_TRUE;
	pStripContext->ObjectControl.nDepthCompare						= KM_GREATER;
	pStripContext->ObjectControl.nCullingMode						= KM_NOCULLING;
	pStripContext->ObjectControl.bZWriteDisable						= KM_FALSE;
	pStripContext->ObjectControl.bDCalcControl						= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nSRCBlendingMode	= KM_ONE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nDSTBlendingMode	= KM_ZERO;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bSRCSelect			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bDSTSelect			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFogMode			= KM_FOGTABLE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bColorClamp		= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bUseAlpha			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bIgnoreTextureAlpha= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFlipUV			= KM_NOFLIP;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nClampUV			= KM_NOCLAMP;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFilterMode		= KM_BILINEAR;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bSuperSampleMode	= SUPERSAMPLE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].dwMipmapAdjust		= KM_MIPMAP_D_ADJUST_1_00;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nTextureShadingMode= KM_MODULATE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].pTextureSurfaceDesc= pTexture;

	kmGenerateStripHead03( pStripHead,pStripContext);
}

/*-------------------------------------------------------------------------------------*/
/*  Function Name   :   SetupScene                                                     */
/*  Inputs          :   None                                                           */
/*  Outputs         :   None                                                           */
/*  Returns         :   Error message or 0                                             */
/*  Globals Used    :   Device                                                         */
/*  Description     :   This routine is used to set PVR device and setup some values.  */
/*                      This routine is called from FRONTEND.C                           */
/*-------------------------------------------------------------------------------------*/
int SetupScene (void)
{
	int				i;
	KMPACKEDARGB	fogcol;
	KMFLOAT			FogTable[128];

	/*----------------------------------------------------------------------------------- */
	/* Initialize Hardware */
#if 0
	status = kmInitDevice(KM_DREAMCAST);
	Check_Status(status, "kmInitDevice");
#endif

	kmGetVersionInfo(&VersionInfo);
#if 0
	PRINTOUT(("MajorVersion      0x0%08x\n",VersionInfo.kmMajorVersion));
	PRINTOUT(("LocalVersion      0x0%08x\n",VersionInfo.kmLocalVersion));
	PRINTOUT(("kmFrameBufferSize 0x0%08x\n",VersionInfo.kmFrameBufferSize));
#endif

#if 0
	status = kmSetDisplayMode(	KM_DSPMODE_VGA,		/* nDisplayMode */
								KM_DSPBPP_RGB565,	/* nBpp */
								TRUE,				/* bDither */
								FALSE				/* bAntiAlias */
								);
	Check_Status(status, "kmSetDisplayMode");
#endif
	/*----------------------------------------------------------------------------------- */
	/* Create frame buffer and vertex buffer */

	pFB[0] = &PrimarySurfaceDesc;
	pFB[1] = &BackSurfaceDesc;

	/* VertexBufferPointer(set5) */
#if 0
	dwDataPtr = (PKMDWORD)0xACB00000;
#else
	dwDataPtr = (PKMDWORD)(((KMDWORD)syMalloc(0x200000) & 0x0FFFFFFFUL) | 0xA0000000);
#endif

	/**********/
	/* 初期化 */
	/**********/
	pFB[0] = &PrimarySurfaceDesc;
	pFB[1] = &BackSurfaceDesc;
	/* VertexBufferPointer(set5) */
	dwDataPtr = (PKMDWORD)0xACB00000;

	SystemConfig.dwSize					=	sizeof(KMSYSTEMCONFIGSTRUCT);
#if defined(_NOWAIT_VSYNC_)
	SystemConfig.flags					=	KM_CONFIGFLAG_ENABLE_CLEAR_FRAMEBUFFER | KM_CONFIGFLAG_NOWAITVSYNC;
#else
	SystemConfig.flags					=	KM_CONFIGFLAG_ENABLE_CLEAR_FRAMEBUFFER;
#endif
	/* for Frame buffer */
	SystemConfig.ppSurfaceDescArray		=	pFB;		/* Array of SurfaceDesc	pointer     */
	SystemConfig.fb.nNumOfFrameBuffer	=	2;			/* Number Of Frame Buffer			*/
	/* for Texture Memory */
	SystemConfig.nTextureMemorySize		=	0x400000;	/* Texture 4MB */
	SystemConfig.nNumOfTextureStruct	=	4096;		/* テクスチャ管理構造体の数 */
	SystemConfig.nNumOfSmallVQStruct	=	1024;		/* VQテクスチャ管理構造体の数 */
	SystemConfig.pTextureWork			=	&FBarea[0];	/* テクスチャ管理構造体領域 */
	/* for Vertex buffer */
	SystemConfig.pBufferDesc			=	&VertexBufferDesc;	/* pointer to VERTEXBUFFDESC 		*/
	SystemConfig.nNumOfVertexBank		=	2;
	SystemConfig.pVertexBuffer			=	dwDataPtr;	/* pointer to Vertex buffer 		*/
	SystemConfig.nVertexBufferSize		=	0x100000*2;	/* 1MB *2 */
	SystemConfig.nPassDepth				=	1;
	SystemConfig.Pass[0].dwRegionArrayFlag = KM_PASSINFO_AUTOSORT;
	SystemConfig.Pass[0].fBufferSize[0] =  50.0f;
	SystemConfig.Pass[0].fBufferSize[1] =   0.0f;
	SystemConfig.Pass[0].fBufferSize[2] =  50.0f;
	SystemConfig.Pass[0].fBufferSize[3] =   0.0f;
	SystemConfig.Pass[0].fBufferSize[4] =   0.0f;
	kmSetSystemConfiguration(&SystemConfig);

	/*----------------------------------------------------------------------------------- */
	/* Fog Setting */

	/* Fog Color */
	fogcol.byte.bBlue	= 0.5 * 255;
	fogcol.byte.bGreen	= 0.3 * 255;
	fogcol.byte.bRed	= 0.1 * 255;
	status = kmSetFogTableColor(fogcol);
	Check_Status(status, "kmSetFogTableColor");

	/* Fog Density */
	status = kmSetFogDensity(0xFF09);
	Check_Status(status, "kmSetFogDensity");

	/* Fog Table */
	for(i = 0;i < 128; i++) {
/*		// Linear Fog table ---------------------------------------------- */
/*		FogTable[i] = 1.0f - ((float)i / 128.0f); */
/*		// PCX Fog table ---------------------------------------------- */
/*		FogTable[i] = (float)PCXFogTable[i] / 256.0f; */
/*		// Slope Fog table ---------------------------------------------- */
#define	FOG_MIN		(-0.8f)
		FogTable[i] = 1.0f - (float)i * ((1.0f - FOG_MIN) / 128.0f);
		if(FogTable[i] < 0.0f) FogTable[i] = 0.0f;
	}
	status = kmSetFogTable(&FogTable[0]);
	Check_Status(status, "kmSetFogTable");

	/*----------------------------------------------------------------------------------- */
	/* some initializes */

	SetupTextures ();			/* Create texture surface & Load texture file */
	SetupContext  ();			/* Initialize Vertex Context */
	SetupPet      ();			/* Initialize object vertex data */

	txt_InitDisplayString();	/* Initialize DisplayString routine */
	InitBackGround();			/* Setup background plane */

	/*-------------------------------------------------------------------------------- */
	/* 性能測定用各種変数の初期化 */

	frame		= 0;

#if defined(_DISP_PERFORMANCE_)
	totalTime	= 0;
	StartTime	= syTmrGetCount();
#endif	/* defined(_DISP_PERFORMANCE_) */

	return 0;
}
/*-------------------------------------------------------------------------------------*/
/*  Function Name   :   NextFrame                                                      */
/*  Inputs          :   None                                                           */
/*  Outputs         :   None                                                           */
/*  Returns         :   None                                                           */
/*  Globals Used    :   PVRContext                                                     */
/*  Description     :   Drawing everything and rendering.                              */
/*                      This routine is called from FRONTEND.C                         */
/*-------------------------------------------------------------------------------------*/
void NextFrame()
{
	/* シ－ンの開始	*/
	kmBeginScene(&SystemConfig);

	/* パスの開始 */
	kmBeginPass(&VertexBufferDesc);

    MovePet   ();
    DrawPet   ();
    DrawGround();
    DrawSky   ();
    DrawSea   ();

	txt_SetCursor(0,1);
#if defined(_DISP_PERFORMANCE_)
	/* Write FPS on screen -----------------------------------------------------*/
	PRINTOUT(("FRAME:%06d%06d Now:%07.3fFPS, Ave:%07.3fFPS\n",frame_2, frame,nFPS,aFPS));
#else
	PRINTOUT(("FRAME:%06d%06d\n",frame_2, frame));
#endif	/* defined(_DISP_PERFORMANCE_) */

	/*----------------------------------------------------------------------------------- */
	/* Rendering start */
#if defined(_DISPLAY_STRING_)
	txt_DispScreen(&VertexBufferDesc);		/* Display screen */
#endif
	/* パスの終了 */
	kmEndPass(&VertexBufferDesc);
	/* レンダリング */
	kmRender(KM_RENDER_FLIP);

	/* シーンの終了 */
	kmEndScene(&SystemConfig);

	/*----------------------------------------------------------------------------------- */
	/* Flip screen */

#if defined(_DISP_PERFORMANCE_)
/* 性能計算 ------------------------------------------------------------------*/
	EndTime	= syTmrGetCount();
	/* ただいまのフレームを作成するのにかかった時間 */
	nowTime = syTmrCountToMicro( syTmrDiffCount( StartTime, EndTime ) ) / 1000.0f;
	StartTime = EndTime;

												/* 得られた値が異常であった場合は無視 */
	if(nowTime > maxTime){maxTime = nowTime;}	/* もっとも時間がかかった？ */
	if(nowTime < minTime){minTime = nowTime;}	/* もっとも早かった？ */

	totalTime += nowTime;						/* 累積時間 */
	aveTime = totalTime / ((double)frame + 1.0f);/* 今までの平均時間 */

	nFPS  = 1000.0f / (double)nowTime;
	aFPS  = 1000.0f / (double)aveTime;
	MxFPS = 1000.0f / (double)minTime;
	MnFPS = 1000.0f / (double)maxTime;
#endif	/* defined(_DISP_PERFORMANCE_) */

	frame++;
	if(frame > 1000000)
	{	/* フレームのリセット */
		frame = 0;
#if defined(_DISP_PERFORMANCE_)
		totalTime = 0;
#endif	/* defined(_DISP_PERFORMANCE_) */
		frame_2++;
	}
}

/*-------------------------------------------------------------------------------------*/
/*  Function Name   :   DrawGround                                                     */
/*  Inputs          :   None                                                           */
/*  Outputs         :   None                                                           */
/*  Returns         :   None                                                           */
/*  Globals Used    :   PVRContex                                                      */
/*  Description     :   Draws ground.                                                  */
/*-------------------------------------------------------------------------------------*/
void DrawGround()
{
PVRVERTEX  Vert[4];
int Face[1][4] = {0,1,2,3}, i;
/* Four points to set a big quad. */
km_vector Pnt[4]	=  {{-5000.0f,  -5.0f, -100.0f},
                       {-5000.0f,  -5.0f, 5000.0f},
                       { 5000.0f,  -5.0f, 5000.0f},
                       { 5000.0f,  -5.0f, -100.0f}};


    for (i=0; i<4; i++)
    {
		/* Translate from 3D to PVR-Direct coord. */
		Perspect (Pnt[i], &Vert[i]);
		/* Set the colour for each vertex. */
		Vert[i].u32Colour   = RGBColour (255,255,255);
		Vert[i].u32Specular = RGBColour (255,255,255);
    }
   /* Set UV values for each textured vertex. */
   Vert[0].fUOverW = 0.0f;      Vert[0].fVOverW = 0.0f;
   Vert[1].fUOverW = 0.0f;      Vert[1].fVOverW = 80.0f;
   Vert[2].fUOverW = 400.0f;    Vert[2].fVOverW = 80.0f;
   Vert[3].fUOverW = 400.0f;    Vert[3].fVOverW = 0.0f;
   /* Set a sigle textured quad to create the ground. */
kmtri_quads (	VertexBufferDesc,		/* KMVERTEXBUFFDESC	BufferDesc, */
				&StripHeadGround,		/* PKMSTRIPHEAD		pStripHead, */
				1,						/* int  nNumFaces, */
				Face,					/* int  pFaces[][4], */
				Vert					/* PPVRVERTEX  pVertices */
				);
}
/*-------------------------------------------------------------------------------------*/
/*  Function Name   :   DrawSky                                                        */
/*  Inputs          :   None                                                           */
/*  Outputs         :   None                                                           */
/*  Returns         :   None                                                           */
/*  Globals Used    :   PVRContex                                                      */
/*  Description     :   Draws Sky. (The same as DrawGround)                            */
/*-------------------------------------------------------------------------------------*/
void DrawSky()
{
float Pos=0;
PVRVERTEX  Vert[4];
int Face[1][4] = {0,1,2,3}, i;
km_vector Pnt[4]	=   {{-5000.0f,100.0f, -100.0f},
                         {-5000.0f,100.0f, 5000.0f},
                         { 5000.0f,100.0f, 5000.0f},
                         { 5000.0f,100.0f, -100.0f}};

    for (i=0; i<4; i++)
    {
	     Perspect (Pnt[i], &Vert[i]);
		Vert[i].u32Colour   = RGBColour (255,255,255);
		Vert[i].u32Specular = RGBColour (255,255,255);
    }

   /* Here the continous fluency of the sky.     */
   /* Note that I just move texture's UV values. */
   Pos =(float)SkyFrame / 100.0f;
   Vert[0].fUOverW =  0.0;  Vert[0].fVOverW = Pos+00.0;
   Vert[1].fUOverW =  0.0;  Vert[1].fVOverW = Pos+20.0;
   Vert[2].fUOverW = 90.0;  Vert[2].fVOverW = Pos+20.0;
   Vert[3].fUOverW = 90.0;  Vert[3].fVOverW = Pos+00.0;

	kmtri_quads (	VertexBufferDesc,	/* KMVERTEXBUFFDESC	BufferDesc, */
					&StripHeadSky,		/* PKMSTRIPHEAD		pStripHead, */
					1,					/* int  nNumFaces, */
					Face,				/* int  pFaces[][4], */
					Vert				/* PPVRVERTEX  pVertices */
					);

	SkyFrame += ( 1.0f / SPEED );
	if(SkyFrame > 10000.0f){SkyFrame = 10.0f;}
}
/*-------------------------------------------------------------------------------------*/
/*  Function Name   :   DrawSea                                                        */
/*  Inputs          :   None                                                           */
/*  Outputs         :   None                                                           */
/*  Returns         :   None                                                           */
/*  Globals Used    :   PVRContex                                                      */
/*  Description     :   Draws Sea surface and its shadow.                              */
/*-------------------------------------------------------------------------------------*/
void DrawSea()
{
km_vector	Move, Scale;
PVRVERTEX	Vert[4];
int			Face[1][4] = {0,1,2,3}, i;
km_vector	Pnt[4]	=   {{-100.0f, 50.0f, -100.0f},
                         {-5000.0f,50.0f, 5000.0f},
                         { 5000.0f,50.0f, 5000.0f},
                         { 100.0f, 50.0f, -100.0f}};

/*	if (SeaFrame > 20000 || SeaFrame < 1){SF = -SF;}     */
	if (SeaFrame > 1809.5573 || SeaFrame < 1){SF = -SF;}
    /* SF is just a up-down step for SeaFrame          */
    /* to avoid a large integer part of this variable  */

	Move[0] = SeaFrame / 20.0;
	Move[2] = 0.0;

	Scale[0] = 0.9 + sin(SeaFrame/32.0)/15.0;
	Scale[2] = 0.9 + sin(SeaFrame/64.0)/15.0;

	/* Here the sea stream.                    */
	/* Note that I just move the quad's vertex */
	for (i=0; i<4; i++)
	{
		Pnt[i][0] *= Scale[0];
		Pnt[i][0] += Move[0];
		Pnt[i][2] *= Scale[2];
		Pnt[i][2] += Move[2];

		Perspect (Pnt[i], &Vert[i]);
		Vert[i].u32Colour   = RGBA(255,255,255,170);
		Vert[i].u32Specular = RGBColour (255,255,255);
	}

	Vert[0].fUOverW =  -1.0;  Vert[0].fVOverW = -1.0;
	Vert[1].fUOverW = -40.0;  Vert[1].fVOverW = 40.0;
	Vert[2].fUOverW =  80.0;  Vert[2].fVOverW = 40.0;
	Vert[3].fUOverW =   1.0;  Vert[3].fVOverW = -1.0;

	/* Sea surface (transparent quad). */
	kmtri_quads (	VertexBufferDesc,	/* KMVERTEXBUFFDESC	BufferDesc, */
					&StripHeadSea,		/* PKMSTRIPHEAD		pStripHead, */
					1,					/* int  nNumFaces, */
					Face,				/* int  pFaces[][4], */
					Vert				/* PPVRVERTEX  pVertices */
					);

	/* Sea shadow (transparent quad). */
/*   for (i=0; i<4; i++){ Pnt[i][1] = -4.99f; Perspect (Pnt[i], &Vert[i]);} */
	for (i=0; i<4; i++)
	{
		Pnt[i][1] = -4.99f;
		Perspect (Pnt[i], &Vert[i]);
		Vert[i].u32Colour   = RGBA(255,255,255,90);
		Vert[i].u32Specular = RGBColour (255,255,255);
	}

	kmtri_quads	(	VertexBufferDesc,	/* KMVERTEXBUFFDESC	BufferDesc, */
					&StripHeadSea,		/* PKMSTRIPHEAD		pStripHead, */
					1,					/* int  nNumFaces, */
					Face,				/* int  pFaces[][4], */
					Vert				/* PPVRVERTEX  pVertices */
					);

	SeaFrame += ( SF / SPEED );
}
/*-------------------------------------------------------------------------------------*/
/*  Function Name   :   MovePet                                                        */
/*  Inputs          :   None                                                           */
/*  Outputs         :   None                                                           */
/*  Returns         :   None                                                           */
/*  Globals Used    :   PetPath, PetTime, PetPosY, VelH, Radius and TPet               */
/*  Description     :   Set a 10 points path for the seal's spine.                     */
/*-------------------------------------------------------------------------------------*/
void MovePet (void)
{
register i;

    for (i=0; i<11; i++)
    {
		PetPath[10-i][1] = PetPosY + sin((PetTime+i)/3.0)*3.0;
		PetPath[10-i][0] = cos ((PetTime+i)*(TPet/(Radius))) * Radius;
		PetPath[10-i][2] = sin ((PetTime+i)*(TPet/(Radius))) * Radius + 150;
    }
 	PetTime += (1.0f / SPEED);
	PetPosY += (VelH / SPEED);
    if (PetPosY < -0.0 || PetPosY > 50.0){VelH = -VelH;}
}
/*-------------------------------------------------------------------------------------*/
/*  Function Name   :   DrawPet                                                        */
/*  Inputs          :   None                                                           */
/*  Outputs         :   None                                                           */
/*  Returns         :   None                                                           */
/*  Globals Used    :   SealVerts, ShadowVerts, Sealfaces, ShadowFaces                 */
/*  Description     :   This routine draws our seal.                                   */
/*-------------------------------------------------------------------------------------*/
void DrawPet (void)
{
 km_vector	pp, n, TempP, Shadow[10*2];
 register   i, j, pos;
 int        PperC = 10, NumL = 10;
 double     CosA, SinA, CosB, SinB, CosC, SenC;
 double     LenXYZ, LenXY, p0, p1;

 for(j = 0; j < NumL; j++ )
    {
		n[0]=PetPath[j][0] - PetPath[j+1][0];
		n[2]=PetPath[j][2] - PetPath[j+1][2];
		n[1]=PetPath[j][1] - PetPath[j+1][1];

		LenXY = sqrt(n[0]*n[0] + n[2]*n[2]);

		if (LenXY > 0.0){CosA = n[0] / LenXY; SinA = n[2] / LenXY;}
		else			{CosA = 1.0;          SinA = 0.0;         }

		LenXYZ  = sqrt (n[0]*n[0] + n[2]*n[2] + n[1]*n[1]);

		CosB = n[1]  / LenXYZ;           SinB = LenXY / LenXYZ;
		CosC = cos ((2.0*PI)/(PperC-1)); SenC = sin ((2.0*PI)/(PperC-1));

		/* This sets a point pp(0, r, 0) */
		pp[0] =  pp[2]= 0.0;  pp[1] =  sin((float)j*(PI/8.0))*3.0 + 0.2;

		/* This's the tail size */
		if (j==9) {pp[1] = 3.0;}

		for (i=0; i<PperC; i++)
		{
			/* Rotating pp around n (two consecutive spine points) */
	        p0    =  CosA * pp[0] + SinA * pp[2];
	        pp[2] = -SinA * pp[0] + CosA * pp[2];
    	    pp[0] =  p0;

			p1    =  CosB * pp[1] + SinB * pp[0];
	        pp[0] = -SinB * pp[1] + CosB * pp[0];
    	    pp[1] =  p1;

	        p0    =  CosC * pp[0] - SenC * pp[2];
    	    pp[2] =  SenC * pp[0] + CosC * pp[2];
        	pp[0] =  p0;

	        p1    =  CosB * pp[1] - SinB * pp[0];
    	    pp[0] =  SinB * pp[1] + CosB * pp[0];
        	pp[1] =  p1;

	        p0    =  CosA * pp[0] - SinA * pp[2];
    	    pp[2] =  SinA * pp[0] + CosA * pp[2];
        	pp[0] =  p0;
	        pos   = i+(j)*PperC;

	        /* Seal vertex */
	        TempP[0] = PetPath[j][0]-pp[0];
    	    TempP[1] = PetPath[j][1]-pp[1];
        	TempP[2] = PetPath[j][2]-pp[2];

			/* Flatting the tail */
			if (j==9){ TempP[1] = PetPath[j][1]; }

			/* Shadow vertex */
			if (i==2) {Shadow[j*2+0][0]=TempP[0];  Shadow[j*2+0][1]=-4.8f;  Shadow[j*2+0][2]=TempP[2];}
			if (i==7) {Shadow[j*2+1][0]=TempP[0];  Shadow[j*2+1][1]=-4.8f;  Shadow[j*2+1][2]=TempP[2];}

			Perspect (TempP, &SealVert[pos]);
		}
	}
    for (j=0;j<10;j++)
    {
    	Perspect (Shadow[j*2+0], &ShadowVert[j*2+0]);
	    Perspect (Shadow[j*2+1], &ShadowVert[j*2+1]);
    }

	/* Drawing seal mesh */
	kmtri_quads (	VertexBufferDesc,	/* KMVERTEXBUFFDESC	BufferDesc, */
					&StripHeadSeal,		/* PKMSTRIPHEAD		pStripHead, */
					10*8,				/* int  nNumFaces, */
					SealFaces,			/* int  pFaces[][4], */
					SealVert			/* PPVRVERTEX  pVertices */
					);
	/* Drawing seal's shadow mesh */
	kmtri_quads (	VertexBufferDesc,	/* KMVERTEXBUFFDESC	BufferDesc, */
					&StripHeadSeal,		/* PKSTRIPHEAD		pStripHead, */
					9,					/* int  nNumFaces, */
					ShadowFaces,		/* int  pFaces[][4], */
					ShadowVert			/* PPVRVERTEX  pVertices */
					);
}
/*-------------------------------------------------------------------------------------*/
/*  Function Name   :   SetupPet                                                       */
/*  Inputs          :   None                                                           */
/*  Outputs         :   None                                                           */
/*  Returns         :   None                                                           */
/*  Globals Used    :   SealVerts, ShadowVerts, Sealfaces, ShadowFaces                 */
/*  Description     :   Set a 10 points path for the seal's spine.                     */
/*-------------------------------------------------------------------------------------*/
void SetupPet (void)
{
unsigned char	SealSh[] = { 0, 56, 150, 255, 255, 152, 56, 0, 0, 0 };
register		i, j;
int				cont = 0;

	/* Seal vertex */
	for ( j = 0; j < 10; j++)
	{
		for ( i = 0; i < 10; i++)
		{
			/* Setting seal's smooth shadow colouring faces. */
			if ( j == 8 ){ SealSh[i] = 0;} if ( j == 9 ){ SealSh[i] = 0;}/* tail */
			SealVert[cont].u32Colour = RGBColour (SealSh[i], SealSh[i], SealSh[i]);
			SealVert[cont].u32Specular	= RGBColour (0, 0, 0);
			/* U & V values for texture. */
			SealVert[cont].fUOverW     = (float)( i + 1 ) / 9.0;
			SealVert[cont].fVOverW     = (float)( j ) / 11.0;
			cont++;
		}
	}

    cont = 0;

	/* Seal faces */
	for (j = 0; j < 10; j++)
	{
		for (i = 0; i < 9; i++)
		{
	    /* In a Quad the 3 first points must be not too much close. */
    	/* I have separated the mesh in two parts to avoid the pointed nose effect. */
		    if (j < 5 || j==8)
			{	/* front harf of object & tail    */
				SealFaces[cont][2] = i+(j)*10;      SealFaces[cont][3] = i+1+j*10;
				SealFaces[cont][0] = i+1+(j+1)*10;  SealFaces[cont][1] = i+(j+1)*10;
		    }
		    else
			{				/* rear harf of object */
				SealFaces[cont][0] = i+(j)*10;      SealFaces[cont][1] = i+1+j*10;
				SealFaces[cont][2] = i+1+(j+1)*10;  SealFaces[cont][3] = i+(j+1)*10;
		    }
		    cont++;
		}
	}

	cont = 0;

	/* Shadow vertex */
	for (j=0; j<10; j++)
	{
	    for (i=0; i<2; i++)
	    {
			ShadowVert[cont].u32Colour   = RGBColour (0,0,0);
			ShadowVert[cont].u32Specular = RGBColour (0,0,0);
			ShadowVert[cont].fUOverW     = 0.1f;
			ShadowVert[cont].fVOverW     = 0.1f;
			cont++;
		}
	}

	/* Shadow faces */
	for (j=0;j<9;j++)
	{
		ShadowFaces[j][0] = 1+j*2; ShadowFaces[j][1] = 0+j*2;
		ShadowFaces[j][2] = 2+j*2; ShadowFaces[j][3] = 3+j*2;
	}
}

/*-------------------------------------------------------------------------------------*/
/*  Function Name   :   SetupTextures                                                  */
/*  Inputs          :   None                                                           */
/*  Outputs         :   None                                                           */
/*  Returns         :   None                                                           */
/*  Globals Used    :   SeaTex, SealTex, GroundTex, SkyTex                             */
/*  Description     :   Loads all texture bitmaps.                                     */
/*-------------------------------------------------------------------------------------*/
void SetupTextures (void)
{
	PKMDWORD			pTexture01;				/* Pointer to texture */
	KMTEXTURETYPE		nTextureType;			/* texture type definition */

	/*----------------------------------------------------------------------------------- */
	/* Create texture surface */
	nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&SeaTex,				/* OUT	PKMSURFACEDESC	pSurfaceDesc */
		128,					/*	IN	KMINT32			nWidth  */
		128,					/*	IN	KMINT32			nHeight  */
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType */
	);
	Check_Status(status, "kmCreateTextureSurface(SeaTex)");

	nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&SealTex,				/* OUT	PKMSURFACEDESC	pSurfaceDesc */
		128,					/*	IN	KMINT32			nWidth  */
		128,					/*	IN	KMINT32			nHeight  */
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType */
	);
	Check_Status(status, "kmCreateTextureSurface(SealTex)");

	nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&GroundTex,				/* OUT	PKMSURFACEDESC	pSurfaceDesc */
		128,					/*	IN	KMINT32			nWidth  */
		128,					/*	IN	KMINT32			nHeight  */
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType */
	);
	Check_Status(status, "kmCreateTextureSurface(GroundTex)");

	nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&SkyTex,				/* OUT	PKMSURFACEDESC	pSurfaceDesc */
		128,					/*	IN	KMINT32			nWidth  */
		128,					/*	IN	KMINT32			nHeight  */
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType */
	);
	Check_Status(status, "kmCreateTextureSurface(SkyTex)");

	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
	pTexture01 = (unsigned long *)&sea_sea;
	status = kmLoadTexture(&SeaTex,				/* PKMSURFACEDESC pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))			/* PKMDWORD pTexture */
							);
	Check_Status(status, "kmLoadTexture(Sea.pvr)");

	pTexture01 = (unsigned long *)&sea_seal;
	status = kmLoadTexture(&SealTex,			/* PKMSURFACEDESC pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))			/* PKMDWORD pTexture */
							);
	Check_Status(status, "kmLoadTexture(Seal.pvr)");

	pTexture01 = (unsigned long *)&sea_ground;
	status = kmLoadTexture(&GroundTex,				/* PKMSURFACEDESC pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))			/* PKMDWORD pTexture */
							);
	Check_Status(status, "kmLoadTexture(Ground.pvr)");

	pTexture01 = (unsigned long *)&sea_sky;
	status = kmLoadTexture(&SkyTex,				/* PKMSURFACEDESC pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))			/* PKMDWORD pTexture */
							);
	Check_Status(status, "kmLoadTexture(Sky.pvr)");
}
/*-------------------------------------------------------------------------------------*/
/*  Function Name   :   SetupContex                                                    */
/*  Inputs          :   None                                                           */
/*  Outputs         :   None                                                           */
/*  Returns         :   None                                                           */
/*  Globals Used    :   PVRContex                                                      */
/*  Description     :   Setup PVRContex values.                                        */
/*-------------------------------------------------------------------------------------*/
void SetupContext (void)
{
	/*-------------------------------------------------------------------------------- */
	/* Initialize Vertex Context */
	/*-------------------------------------------------------------------------------- */
	/* Context for Ground */
	memset(&StripContextGround, 0, sizeof(StripContextGround));	/* Crear Context */
	memset(&StripHeadGround, 0, sizeof(StripHeadGround));		/* Crear Head */
	InitStripContext03(&StripContextGround,&StripHeadGround,&GroundTex);					/* Initialize context */

	/*-------------------------------------------------------------------------------- */
	/* Context for Sky */
	memset(&StripContextSky, 0, sizeof(StripContextSky));	/* Crear Context */
	memset(&StripHeadSky, 0, sizeof(StripHeadSky));			/* Crear Head */
	InitStripContext03(&StripContextSky,&StripHeadSky,&SkyTex);/* Initialize context */

	/*-------------------------------------------------------------------------------- */
	/* Context for Sea */
	memset(&StripContextSea, 0, sizeof(StripContextSea));	/* Crear Context */
	memset(&StripHeadSea, 0, sizeof(StripHeadSea));			/* Crear Head */
	InitStripContext03(&StripContextSea,&StripHeadSea,&SeaTex);/* Initialize context */
	kmChangeStripBlendingMode(&StripHeadSea,KM_IMAGE_PARAM1,KM_SRCALPHA,KM_INVSRCALPHA);
	kmChangeStripListType(&StripHeadSea,KM_TRANS_POLYGON);
	kmChangeStripTextureShadingMode(&StripHeadSea,KM_IMAGE_PARAM1,KM_MODULATE_ALPHA);
	kmChangeStripUseAlpha(&StripHeadSea,KM_IMAGE_PARAM1,TRUE);

	/*-------------------------------------------------------------------------------- */
	/* Context for Seal */
	memset(&StripContextSeal, 0, sizeof(StripContextSeal));	/* Crear Context */
	memset(&StripHeadSeal, 0 , sizeof(StripHeadSeal));		/* Clear Head */
	InitStripContext03(&StripContextSeal,&StripHeadSeal,&SealTex);/* Initialize context */

}

/*-------------------------------------------------------------------------------------*/
/*  Function Name   :   Perspect                                                       */
/*  Inputs          :   Point3D                                                        */
/*  Outputs         :   Vert                                                           */
/*  Returns         :   None                                                           */
/*  Globals Used    :   None                                                           */
/*  Description     :   Calculates PVR-Direct coordinates from 3D coordenates.         */
/*-------------------------------------------------------------------------------------*/
void Perspect (const km_vector Point3D, PVRVERTEX *Vert)
{
const km_vector CamPos = { 0.0f, 10.0f, 150.0f};
float x, y, z;

    x    =  Point3D[0] + CamPos[0];
    y    = -Point3D[1] + CamPos[1];
    z    = (Point3D[2] + CamPos[2]);

	Vert->fX    =  (CamFocus * x) / z + 320;
	Vert->fY    =  (CamFocus * y) / z + 240;

	/* The render uses fInvW (1/z) to set the Z-buffer */
	/* In this case I use it to set the fog effect as well */
	Vert->fInvW =  1.8f / z;
}

/****************************************************************************/
/**	main ********************************************************************/
/****************************************************************************/
int	Kamui_Init(void)
{
	txt_ClearScreen();	/* Clear text screen */
#if defined(_VERTEXMACRO_L4_)
	PRINTOUT(("** KMSEAL(KAMUI2&Shinobi) Use:Level4 Macro **\n"));
#else
	PRINTOUT(("** KMSEAL(KAMUI2&Shinobi) **\n"));
#endif

    SetupScene ();	/* Initialize */

#if 0
	while(1)
	{
		NextFrame();	/* Rendering */
	}
#endif
	return 0;
}

/*--------------------------- End of File --------------------------------*/