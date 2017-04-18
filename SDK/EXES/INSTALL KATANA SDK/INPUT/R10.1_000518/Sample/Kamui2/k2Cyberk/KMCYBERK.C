/*******************************************************************************
   Name     : KMCYBERK
   Title    : KAMUI test program "CyberK" from VL
   Author   : VideoLogic Carlos Sarria / NEC Software Takeshi Muto
   Created  : April 1997 by VideoLogic
   Modified : Octover  30. 1997 by Takeshi Muto for KAMUI
              April    15. 1998 by Takeshi Muto for KAMUI
              January  26. 1999 by T.Kamei for KAMUI2
              February 16. 1999 by Takeshi Muto for Shinobi
   Description :
   Copyright : 1997 by VideoLogic Limited. All rights reserved.
********************************************************************************/
#if 0
#define		_NOWAIT_VSYNC_			/* 非同期モード使用時は定義する					*/
#define		_VERTEXMACRO_L4_		/* VertexMacroLevel4使用時は定義する			*/
#endif

#define		_DISPLAY_SKY_			/* if defined then display sky plane			*/
#define		_DISPLAY_TRANS_			/* if defined then display ground trans plane	*/
#define		_DISPLAY_STRING_		/* if defined then display strings on screen	*/
#if 1
#define		_DISP_PERFORMANCE_		/* Display performance : 						*/
#endif

#define		NMAX		(50)		/* Maximum number of cyber kangaloo				*/
#define		LAP			(7)
#define		TLP			(0.3f)
#define 	GRV			(-9.81)
#define 	HIGH		(30.0)
#define		FOG_MIN		(-0.8f)

#define		SUPERSAMPLE		KM_TRUE
#define		FILTERMODE		KM_BILINEAR
#define		FOGMODE			KM_FOGTABLE

#include	<math.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<float.h>
#include	<Shinobi.h>
#include	<sg_sytmr.h>	/* System timer */

#
#pragma warning (disable : 4244) /* Disables float to double conversion warning */
#pragma warning (disable : 4056)
#define _STRICT_UNION_
#define _CLX2_
#define _CLX_

#include	"kamui2.h"				/* for Kamui Call									*/
#include	"dispstr.h"				/* for DisplayString								*/
#include	"vltex.h"				/* for vl sample texture							*/

#if 0
#define _KM_USE_VERTEX_MACRO_L4_
#include "kamuix.h"
#endif

#define		PI			(3.1416f)
#define		RGBColour(r, g, b)	((KMUINT32) (((r) << 16) | ((g) <<  8) | (b)))
#define		RGBA(r, g, b, a)	((KMUINT32) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b)))

/* Macros for kamui */
#define		GetRED(col)			((KMFLOAT) ( ((col) & 0x00ff0000) >> 16 ) / 256.0f)
#define		GetGREEN(col)		((KMFLOAT) ( ((col) & 0x0000ff00) >>  8 ) / 256.0f)
#define		GetBLUE(col)		((KMFLOAT) ( ((col) & 0x000000ff)       ) / 256.0f)
#define		GetALPHA(col)		((KMFLOAT) ( ((col) & 0xff000000) >> 24 ) / 256.0f)

typedef		float	pvr_vector[3];	/* type of pvr_vector */

/* Peripheral */
PDS_PERIPHERAL *per;

/* ---------
 * PVRVERTEX
 * ---------
 * This structure is currently physically equivalent to Direct3D's D3DTLVERTEX
 * (so one can be cast to the other), with the exception that Direct3D's u and
 * v values must be multiplied by the 1/w value.  RAVE vertices already contain
 * u/w and v/w.
 */
typedef struct tagPVRVERTEX
{
	/* Projected screen coordinates: */
	float		fX;		/* 0 <= fX < screen width (up to 1024)					*/
	float		fY;		/* 0 <= fY < screen height (up to 1024)					*/
	float		fZ;		/* 0.01 <= fZ <= 1, where 1 is infinite distance away	*/
	/* 1/w for the perspective projection (should be set to 1.0/fZ; fZ is actually ignored): */
	float		fInvW;
	KMUINT32	u32Colour;			/* Material colour (D3DCOLOR format):	*/
	KMUINT32	u32Specular;		/* Specular colour (D3DCOLOR format):	*/
	float		fUOverW, fVOverW;	/* Texture coordinates:					*/
} PVRVERTEX, *PPVRVERTEX;

/****************************************************************************
 *	Valuables for KAMUI
 ****************************************************************************/
	KMSTATUS			status;					/* return status of KAMUI API	*/
	KMVERSIONINFO		VersionInfo;			/* KAMUI Version information	*/
	KMSURFACEDESC		PrimarySurfaceDesc;		/* Primary frame buffer			*/
	KMSURFACEDESC		BackSurfaceDesc;		/* Back-buffer frame buffer		*/
	KMSURFACEDESC		CyberKTex;				/* texture surface				*/
	KMSURFACEDESC		GroundTex;				/* texture surface				*/
	KMSURFACEDESC		SkyTex;					/* texture surface				*/
	KMVERTEXBUFFDESC	VertexBufferDesc;		/* Vertex-buffer				*/

#if 0
	KMSTRIPCONTEXT		StripContext00;
	KMSTRIPHEAD			StripHead00_Ground;
	KMSTRIPHEAD			StripHead00_Sky;
	KMSTRIPHEAD			StripHead00_CyberK;
#endif

	KMSTRIPCONTEXT		StripContext03;
	KMSTRIPHEAD			StripHead03_Ground;
	KMSTRIPHEAD			StripHead03_Sky;
	KMSTRIPHEAD			StripHead03_CyberK;

	PKMSURFACEDESC		pFB[2];
	KMDWORD				FBarea[24576 + 19456];	/*	FBstruct 4096 Entry (= 4096 * 24 / 4)
													VQstruct 1024 Entry (= 1024 * 76 / 4) */
	KMSYSTEMCONFIGSTRUCT	SystemConfig;
	PKMDWORD				dwDataPtr;

	/* 性能測定用変数 */
	int			frame;				/* 画面フレーム							*/
	int			frame_2 = 0;		/* 画面フレーム上位						*/
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
	int			NK = 10;			/* Number of cyber kangaloo				*/
	int			Movement;
	int			NumMax[NMAX];
	int			LongK[NMAX];
	int			StateK[NMAX];
	int			TimerK[NMAX];
	pvr_vector	RotVecK[NMAX];
	pvr_vector	PathK[NMAX][200];
	float		AngK[NMAX];
	float		MovAngK[NMAX];
	int			TransGround = 1;

	pvr_vector	p1[NMAX]={0.0f, 0.0f, 200.0f};
	pvr_vector	p2[NMAX]={0.0f, 0.0f, 200.0f};
	float		Sig[2] ={1.0f, -1.0f};
	float		NewAng[50];
	float		CamFocus = 600.0f;

	PVRVERTEX	PrismVect[3][20];
	PVRVERTEX	TopVect[3][10];
	PVRVERTEX	BotVect[3][20];
	PVRVERTEX	ReflectVect[3][20];
	pvr_vector	Prism3DVect [3][20];

	int PrismFaces[][4] =
	{
		{0,2,1,9},     {8,3,2,9},     {7,4,3,8},     {6,5,4,7},
        {0,1,11,10},   {1,2,12,11},   {2,3,13,12},   {3,4,14,13},   {4,5,15,14},
        {5,6,16,15},   {6,7,17,16},   {7,8,18,17},   {8,9,19,18},   {9,0,10,19},
        {10,12,11,19}, {18,13,12,19}, {17,14,13,18}, {16,15,14,17}
	};

	KMUINT32	PrismCol[NMAX][10];

/*----------------------------  Routines Prototypes ---------------------------------*/

void SetupTextures   (void),
     SetupContext    (void),
     SetupPrism      (void);

void DrawGround      (void),
     DrawSky         (void),
     CreatePath      (int),
     NewPoint        (int),
     DrawCyberK      (int, int);

void Perspect (const pvr_vector, PVRVERTEX *);

/****************************************************************************
 *	Check KAMUI function status
 ****************************************************************************/
void	Check_Status(KMSTATUS status, char * func)
{
	switch(status)
	{
		case KMSTATUS_SUCCESS:
			/* No message is displayed when SUCCESS */
			break;
		case KMSTATUS_INVALID_DISPLAY_MODE:
			PRINTOUT(("%s:KMSTATUS_INVALID_DISPLAY_MODE\n",func));
			break;
		case KMSTATUS_INVALID_VIDEO_MODE:
			PRINTOUT(("%s:KMSTATUS_INVALID_VIDEO_MODE\n",func));
			break;
		case KMSTATUS_NOT_ENOUGH_MEMORY:
			PRINTOUT(("%s:KMSTATUS_NOT_ENOUGH_MEMORY\n",func));
			break;
		case KMSTATUS_INVALID_TEXTURE_TYPE:
			PRINTOUT(("%s:KMSTATUS_INVALID_TEXTURE_TYPE\n",func));
			break;
		case KMSTATUS_INVALID_MIPMAPED_TEXTURE:
			PRINTOUT(("%s:KMSTATUS_INVALID_MIPMAPED_TEXTURE\n",func));
			break;
		case KMSTATUS_CANT_FLIP_SURFACE:
			PRINTOUT(("%s:KMSTATUS_CANT_FLIP_SURFACE\n",func));
			break;
		case KMSTATUS_INVALID_ADDRESS:
			PRINTOUT(("%s:KMSTATUS_INVALID_ADDRESS\n",func));
			break;
		case KMSTATUS_HARDWARE_NOT_PRESENTED:
			PRINTOUT(("%s:KMSTATUS_HARDWARE_NOT_PRESENTED\n",func));
			break;
		case KMSTATUS_INVALID_SETTING:
			PRINTOUT(("%s:KMSTATUS_INVALID_SETTING\n",func));
			break;
		case KMSTATUS_INVALID_VERTEX_TYPE:
			PRINTOUT(("%s:KMSTATUS_INVALID_VERTEX_TYPE\n",func));
			break;
		case KMSTATUS_NOT_IMPLEMENTED:
			PRINTOUT(("%s:KMSTATUS_NOT_IMPREMENTED\n",func));
			break;
		case KMSTATUS_INVALID_PARAMETER:
			PRINTOUT(("%s:KMSTATUS_INVALID_PARAMETER\n",func));
			break;
		default:
			PRINTOUT(("%s:???Undefined status : %d\n", func, status));
			break;
	}
}

/****************************************************************************
 *	kmtri_quads  by T.Hirata
 ***************************************************************************/
void 
kmtri_quads (	PKMVERTEXBUFFDESC	pBufferDesc,
				PKMSTRIPHEAD		pStripHead,
				int					nNumFaces,
				int					pFaces[][4],
				PPVRVERTEX			pVertices,
				int					bTexture)
{
	KMSTATUS	status;
	int			i;
	PPVRVERTEX	pVert;
	KMVERTEX_00		Ver00;				/* for NO-TEXTURE-GOURAUD	*/
	KMVERTEX_03		Ver03;				/* for TEXTURE-GOURAUD		*/

#if defined(_VERTEXMACRO_L4_)
	kmxxGetCurrentPtr(&VertexBufferDesc);
	kmxxStartStrip(pBufferDesc,pStripHead);
#else
	kmStartStrip(pBufferDesc,pStripHead);
#endif

	for(i = 0; i < nNumFaces; i++)
	{
		if(bTexture == TRUE)
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
			Ver03.u.fZ					= pVertices[pFaces[i][0]].fInvW;
			Ver03.fU					= pVertices[pFaces[i][0]].fUOverW;
			Ver03.fV					= pVertices[pFaces[i][0]].fVOverW;
			Ver03.uBaseRGB.dwPacked		= pVertices[pFaces[i][0]].u32Colour;
			Ver03.uOffsetRGB.dwPacked	= pVertices[pFaces[i][0]].u32Specular;
			status = kmSetVertex(pBufferDesc,&Ver03,KM_VERTEXTYPE_03,sizeof(KMVERTEX_03) );
			Check_Status(status, "kmSetVertex");

			Ver03.ParamControlWord		= KM_VERTEXPARAM_NORMAL;
			Ver03.fX					= pVertices[pFaces[i][1]].fX;
			Ver03.fY					= pVertices[pFaces[i][1]].fY;
			Ver03.u.fZ					= pVertices[pFaces[i][1]].fInvW;
			Ver03.fU					= pVertices[pFaces[i][1]].fUOverW;
			Ver03.fV					= pVertices[pFaces[i][1]].fVOverW;
			Ver03.uBaseRGB.dwPacked		= pVertices[pFaces[i][1]].u32Colour;
			Ver03.uOffsetRGB.dwPacked	= pVertices[pFaces[i][1]].u32Specular;
			status = kmSetVertex(pBufferDesc,&Ver03,KM_VERTEXTYPE_03,sizeof(KMVERTEX_03) );
			Check_Status(status, "kmSetVertex");

			Ver03.ParamControlWord		= KM_VERTEXPARAM_NORMAL;
			Ver03.fX					= pVertices[pFaces[i][3]].fX;
			Ver03.fY					= pVertices[pFaces[i][3]].fY;
			Ver03.u.fZ					= pVertices[pFaces[i][3]].fInvW;
			Ver03.fU					= pVertices[pFaces[i][3]].fUOverW;
			Ver03.fV					= pVertices[pFaces[i][3]].fVOverW;
			Ver03.uBaseRGB.dwPacked		= pVertices[pFaces[i][3]].u32Colour;
			Ver03.uOffsetRGB.dwPacked	= pVertices[pFaces[i][3]].u32Specular;
			status = kmSetVertex(pBufferDesc,&Ver03,KM_VERTEXTYPE_03,sizeof(KMVERTEX_03) );
			Check_Status(status, "kmSetVertex");

			Ver03.ParamControlWord		= KM_VERTEXPARAM_ENDOFSTRIP;
			Ver03.fX					= pVertices[pFaces[i][2]].fX;
			Ver03.fY					= pVertices[pFaces[i][2]].fY;
			Ver03.u.fZ					= pVertices[pFaces[i][2]].fInvW;
			Ver03.fU					= pVertices[pFaces[i][2]].fUOverW;
			Ver03.fV					= pVertices[pFaces[i][2]].fVOverW;
			Ver03.uBaseRGB.dwPacked		= pVertices[pFaces[i][2]].u32Colour;
			Ver03.uOffsetRGB.dwPacked	= pVertices[pFaces[i][2]].u32Specular;
			status = kmSetVertex(pBufferDesc,&Ver03,KM_VERTEXTYPE_03,sizeof(KMVERTEX_03) );
			Check_Status(status, "kmSetVertex");
#endif
		}
		else
		{
#if defined(_VERTEXMACRO_L4_)
			kmxxSetVertex_0(	KM_VERTEXPARAM_NORMAL,
								pVertices[pFaces[i][0]].fX,
								pVertices[pFaces[i][0]].fY,
								pVertices[pFaces[i][0]].fInvW,
								pVertices[pFaces[i][0]].u32Colour
							);

			kmxxSetVertex_0(	KM_VERTEXPARAM_NORMAL,
								pVertices[pFaces[i][1]].fX,
								pVertices[pFaces[i][1]].fY,
								pVertices[pFaces[i][1]].fInvW,
								pVertices[pFaces[i][1]].u32Colour
							);

			kmxxSetVertex_0(	KM_VERTEXPARAM_NORMAL,
								pVertices[pFaces[i][3]].fX,
								pVertices[pFaces[i][3]].fY,
								pVertices[pFaces[i][3]].fInvW,
								pVertices[pFaces[i][3]].u32Colour
							);

			kmxxSetVertex_0(	KM_VERTEXPARAM_ENDOFSTRIP,
								pVertices[pFaces[i][2]].fX,
								pVertices[pFaces[i][2]].fY,
								pVertices[pFaces[i][2]].fInvW,
								pVertices[pFaces[i][2]].u32Colour
							);

#else
			Ver00.ParamControlWord	= KM_VERTEXPARAM_NORMAL;
			Ver00.fX				= pVertices[pFaces[i][0]].fX;
			Ver00.fY				= pVertices[pFaces[i][0]].fY;
			Ver00.u.fZ				= pVertices[pFaces[i][0]].fInvW;
			Ver00.uBaseRGB.dwPacked	= pVertices[pFaces[i][0]].u32Colour;
			status = kmSetVertex(pBufferDesc,&Ver00,KM_VERTEXTYPE_00,sizeof(KMVERTEX_00) );
			Check_Status(status, "kmSetVertex");

			Ver00.ParamControlWord	= KM_VERTEXPARAM_NORMAL;
			Ver00.fX				= pVertices[pFaces[i][1]].fX;
			Ver00.fY				= pVertices[pFaces[i][1]].fY;
			Ver00.u.fZ				= pVertices[pFaces[i][1]].fInvW;
			Ver00.uBaseRGB.dwPacked	= pVertices[pFaces[i][1]].u32Colour;
			status = kmSetVertex(pBufferDesc,&Ver00,KM_VERTEXTYPE_00,sizeof(KMVERTEX_00) );
			Check_Status(status, "kmSetVertex");

			Ver00.ParamControlWord	= KM_VERTEXPARAM_NORMAL;
			Ver00.fX				= pVertices[pFaces[i][3]].fX;
			Ver00.fY				= pVertices[pFaces[i][3]].fY;
			Ver00.u.fZ				= pVertices[pFaces[i][3]].fInvW;
			Ver00.uBaseRGB.dwPacked	= pVertices[pFaces[i][3]].u32Colour;
			status = kmSetVertex(pBufferDesc,&Ver00,KM_VERTEXTYPE_00,sizeof(KMVERTEX_00) );
			Check_Status(status, "kmSetVertex");

			Ver00.ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;
			Ver00.fX				= pVertices[pFaces[i][2]].fX;
			Ver00.fY				= pVertices[pFaces[i][2]].fY;
			Ver00.u.fZ				= pVertices[pFaces[i][2]].fInvW;
			Ver00.uBaseRGB.dwPacked	= pVertices[pFaces[i][2]].u32Colour;
			status = kmSetVertex(pBufferDesc,&Ver00,KM_VERTEXTYPE_00,sizeof(KMVERTEX_00) );
			Check_Status(status, "kmSetVertex");
#endif
		}
	}

#if defined(_VERTEXMACRO_L4_)
	kmxxReleaseCurrentPtr(&VertexBufferDesc);
#endif
	kmEndStrip(&VertexBufferDesc);
}

/***************************************
 *	VertexType00用KMSTRIPHEADの構築
 ***************************************/
void	InitStripContext00(
								PKMSTRIPCONTEXT pStripContext,
								PKMSTRIPHEAD	pStripHead
)
{
	pStripContext->nSize = sizeof(KMSTRIPCONTEXT);
	pStripContext->StripControl.nListType		 					= KM_OPAQUE_POLYGON;
	pStripContext->StripControl.nUserClipMode	 					= KM_USERCLIP_DISABLE;
	pStripContext->StripControl.nShadowMode		 					= KM_NORMAL_POLYGON;
	pStripContext->StripControl.bGouraud		 					= KM_TRUE;
	pStripContext->ObjectControl.nDepthCompare			 			= KM_GREATER;
	pStripContext->ObjectControl.nCullingMode			 			= KM_NOCULLING;
	pStripContext->ObjectControl.bZWriteDisable			 			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nSRCBlendingMode	= KM_ONE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nDSTBlendingMode	= KM_ZERO;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bSRCSelect			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bDSTSelect			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFogMode			= FOGMODE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bColorClamp		= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bUseAlpha			= KM_FALSE;

	kmGenerateStripHead00( pStripHead,pStripContext );
}

/***************************************
 *	VertexType03用KMSTRIPHEADの構築
 ***************************************/
void	InitStripContext03(
								PKMSTRIPCONTEXT pStripContext,
								PKMSTRIPHEAD	pStripHead,
								PKMSURFACEDESC	pTextureDesc
)
{
	pStripContext->nSize = sizeof(KMSTRIPCONTEXT);
	pStripContext->StripControl.nListType		 						= KM_OPAQUE_POLYGON;
	pStripContext->StripControl.nUserClipMode	 						= KM_USERCLIP_DISABLE;
	pStripContext->StripControl.nShadowMode		 						= KM_NORMAL_POLYGON;
	pStripContext->StripControl.bOffset									= KM_FALSE;
	pStripContext->StripControl.bGouraud		 						= KM_TRUE;
	pStripContext->ObjectControl.nDepthCompare			 				= KM_GREATER;
	pStripContext->ObjectControl.nCullingMode			 				= KM_NOCULLING;
	pStripContext->ObjectControl.bZWriteDisable							= KM_FALSE;
	pStripContext->ObjectControl.bDCalcControl			 				= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nSRCBlendingMode		= KM_ONE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nDSTBlendingMode		= KM_ZERO;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bSRCSelect				= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bDSTSelect				= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFogMode				= FOGMODE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bColorClamp			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bUseAlpha				= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bIgnoreTextureAlpha	= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFlipUV				= KM_NOFLIP;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nClampUV				= KM_NOCLAMP;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFilterMode			= FILTERMODE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bSuperSampleMode		= SUPERSAMPLE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].dwMipmapAdjust			= KM_MIPMAP_D_ADJUST_1_00;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nTextureShadingMode	= KM_MODULATE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].pTextureSurfaceDesc	= pTextureDesc;

	kmGenerateStripHead03( pStripHead,pStripContext );
}

/***************************************
 *	VertexType01用KMSTRIPHEADの構築
 ***************************************/
void	InitStripContext01(
								PKMSTRIPCONTEXT pStripContext,
								PKMSTRIPHEAD	pStripHead
)
{
	pStripContext->nSize = sizeof(KMSTRIPCONTEXT);
	pStripContext->StripControl.nListType		 					= KM_OPAQUE_POLYGON;
	pStripContext->StripControl.nUserClipMode	 					= KM_USERCLIP_DISABLE;
	pStripContext->StripControl.nShadowMode		 					= KM_NORMAL_POLYGON;
	pStripContext->StripControl.bGouraud		 					= KM_TRUE;
	pStripContext->ObjectControl.nDepthCompare			 			= KM_GREATER;
	pStripContext->ObjectControl.nCullingMode			 			= KM_NOCULLING;
	pStripContext->ObjectControl.bZWriteDisable			 			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nSRCBlendingMode	= KM_ONE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nDSTBlendingMode	= KM_ZERO;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bSRCSelect			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bDSTSelect			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFogMode			= KM_NOFOG;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bColorClamp		= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bUseAlpha			= KM_FALSE;

	kmGenerateStripHead01( pStripHead,pStripContext );
}

/****************************************************************************
 *	Background surface setting
 ****************************************************************************/
void	InitBackGround(void)
{
	KMSTRIPCONTEXT		StripContextBG01;		/* for BG				*/
	KMSTRIPHEAD			StripHeadBG01;			/* for BG				*/
	KMVERTEX_01			BV01[3];				/* pointer to Vertex	*/

	memset( &StripContextBG01	, 0, sizeof(StripContextBG01));
	memset( &StripHeadBG01		, 0, sizeof(&StripHeadBG01));
	InitStripContext01	(&StripContextBG01,&StripHeadBG01);
	kmChangeStripFogMode(&StripHeadBG01,KM_IMAGE_PARAM1,FOGMODE);

	/*-----------------------------------------------------------------------------------*/
	/* set VERTEX DATA */
	/* Vertex #0 */
	BV01[0].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
	BV01[0].fX					=   2.0f;
	BV01[0].fY					= 260.0f;
	BV01[0].u.fZ				=   0.0001f;
	BV01[0].fBaseAlpha			=   1.0f;
	BV01[0].fBaseRed			=   0.0f;
	BV01[0].fBaseGreen			=   0.0f;
	BV01[0].fBaseBlue			=   0.5f;

	/* Vertex #1 */
	BV01[1].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
	BV01[1].fX					= 150.0f;
	BV01[1].fY					=   2.0f;
	BV01[1].u.fZ				=   0.0001f;
	BV01[1].fBaseAlpha			=   1.0f;
	BV01[1].fBaseRed			=   0.0f;
	BV01[1].fBaseGreen			=   0.0f;
	BV01[1].fBaseBlue			=   0.5f;

	/* Vertex #2 */
	BV01[2].ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;
	BV01[2].fX					= 560.0f;
	BV01[2].fY					= 260.0f;
	BV01[2].u.fZ				=   0.0001f;
	BV01[2].fBaseAlpha			=   1.0f;
	BV01[2].fBaseRed			=   0.0f;
	BV01[2].fBaseGreen			=   0.0f;
	BV01[2].fBaseBlue			=   0.5f;

	/*-----------------------------------------------------------------------------------*/
	/* Set BG Plane */
	kmSetBackGround(	&StripHeadBG01,
						KM_VERTEXTYPE_01,
						(PVOID)&BV01[0],
						(PVOID)&BV01[1],
						(PVOID)&BV01[2]	);
}

/*-------------------------------------------------------------------------------------*
 *  Function Name   :   SetupScene                                                     *
 *  Inputs          :   None                                                           *
 *  Outputs         :   None                                                           *
 *  Returns         :   Error message or 0                                             *
 *  Globals Used    :   Device                                                         *
 *  Description     :   This routine is used to set device and setup some values.      *
 *                      This routine is called from FRONTEND.C                         *
 *-------------------------------------------------------------------------------------*/
int SetupScene (void)
{
	int i;
	KMPACKEDARGB	fogcol;
	KMFLOAT			FogTable[128];

	/* Initialize Random number */
	srand ((unsigned)10);

	/*-----------------------------------------------------------------------------------*/
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
								KM_DSPBPP_RGB565,	/* nBpp			*/
								TRUE,				/* bDither		*/
								FALSE				/* bAntiAlias	*/
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
	dwDataPtr = (PKMDWORD)(((KMDWORD)syMalloc(0x300000) & 0x0FFFFFFFUL) | 0xA0000000);
#endif

	SystemConfig.dwSize						=	sizeof(KMSYSTEMCONFIGSTRUCT);
#if defined(_NOWAIT_VSYNC_)
	SystemConfig.flags						=	KM_CONFIGFLAG_ENABLE_CLEAR_FRAMEBUFFER | KM_CONFIGFLAG_NOWAITVSYNC;
#else
	SystemConfig.flags						=	KM_CONFIGFLAG_ENABLE_CLEAR_FRAMEBUFFER;
#endif
	/* for Frame buffer		*/
	SystemConfig.ppSurfaceDescArray			=	pFB;		/* Array of SurfaceDesc	pointer     	*/
	SystemConfig.fb.nNumOfFrameBuffer		=	2;			/* Number Of Frame Buffer				*/
	/* for Texture Memory	*/
	SystemConfig.nTextureMemorySize			=	0x100000;	/* Texture 1MB 							*/
	SystemConfig.nNumOfTextureStruct		=	4096;		/* テクスチャ管理構造体の数				*/
	SystemConfig.nNumOfSmallVQStruct		=	1024;		/* VQテクスチャ管理構造体の数			*/
	SystemConfig.pTextureWork				=	&FBarea[0];	/* テクスチャ管理構造体領域				*/
	/* for Vertex buffer	*/
	SystemConfig.pBufferDesc				=	&VertexBufferDesc;	/* pointer to VERTEXBUFFDESC	*/
	SystemConfig.nNumOfVertexBank			=	2;
	SystemConfig.pVertexBuffer				=	dwDataPtr;	/* pointer to Vertex buffer 			*/
	SystemConfig.nVertexBufferSize			=	0x100000*3;	/* 3MB 									*/
	SystemConfig.nPassDepth					=	1;
	SystemConfig.Pass[0].dwRegionArrayFlag 	= KM_PASSINFO_AUTOSORT;
	SystemConfig.Pass[0].fBufferSize[0] 	=  80.0f;
	SystemConfig.Pass[0].fBufferSize[1] 	=   0.0f;
	SystemConfig.Pass[0].fBufferSize[2] 	=  20.0f;
	SystemConfig.Pass[0].fBufferSize[3] 	=   0.0f;
	SystemConfig.Pass[0].fBufferSize[4] 	=   0.0f;

	status = kmSetSystemConfiguration( &SystemConfig );
	Check_Status(status, "kmSetSystemConfiguration");
	/*-----------------------------------------------------------------------------------*/
	/* Fog Setting */

	/* Fog Color */
	fogcol.byte.bBlue	= 0.6 * 255;
	fogcol.byte.bGreen	= 0.4 * 255;
	fogcol.byte.bRed	= 0.1 * 255;
	status = kmSetFogTableColor(fogcol);
	Check_Status(status, "kmSetFogTableColor");

	/* Fog Density */
	status = kmSetFogDensity(0xFF0C);
	Check_Status(status, "kmSetFogDensity");

	/* Fog Table */
	for(i = 0;i < 128; i++)
	{
		FogTable[i] = 1.0f - (float)i * ((1.0f - FOG_MIN) / 128.0f);
		if(FogTable[i] < 0.0f){ FogTable[i] = 0.0f;}
	}
	status = kmSetFogTable(&FogTable[0]);
	Check_Status(status, "kmSetFogTable");

	/*-----------------------------------------------------------------------------------*/
	/* Initialize DisplayString routine */
	txt_InitDisplayString();

	/*-----------------------------------------------------------------------------------*/
	/* some initializes */
	SetupTextures ();
	SetupPrism    ();
	SetupContext  ();

	txt_SetCursor( 0, 2 );
	PRINTOUT(("Num : %d\n",NK));

	InitBackGround();	/* Setup background plane */

	for (i=0; i<NMAX; i++)
	{
    	LongK[i]  = 60;
        StateK[i] = i & 3;
        p1[i][2]  = p2[i][2]= -170.0f;
        NewAng[i] = (float)((char)(rand()))*(50.0f / 255.0f);
        NewPoint  (i);
        CreatePath(i);
	}

	/*----------------------------------------------------------------------------------- */
	/* initialize maple read library */
#if 0
	vInitMaple();
#endif

	/*-----------------------------------------------------------------------------------*/
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
/*  Globals Used    :   MovAngK, AngK, LongK, TimerK, StateK                           */
/*  Description     :   Drawing everything and rendering.                              */
/*                      This routine is called from FRONTEND.C                         */
/*-------------------------------------------------------------------------------------*/
void NextFrame()
{
	register i;   

	/* シーンの開始 */
	kmBeginScene(&SystemConfig);

	/* パスの開始 */
	kmBeginPass(&VertexBufferDesc);

#if defined(_DISPLAY_TRANS_)
      DrawGround();
#endif

#if defined(_DISPLAY_SKY_)
      DrawSky   ();
#endif

    /* We have three diferent States: 0. Before jump (Only rotation)          *
     *                                1. In the air. (Rotion and traslation)  *
     *                                2. On the ground again (Only rotation)  */
	for (i=0; i<NK; i++)
	{
    	switch (StateK[i])
		{
            case 0: MovAngK[i]+=AngK[i]/LAP; LongK[i]+=3.3; DrawCyberK(0,i); 
                    if (TimerK[i]==LAP){TimerK[i]=-1; StateK[i]=1;}
                    break;
			case 1: MovAngK[i]-=(2.0*AngK[i])/NumMax[i]; LongK[i]=60; DrawCyberK(TimerK[i], i); 
                    if (TimerK[i]==NumMax[i]-1){TimerK[i]=-1; StateK[i]=2;}
                    break;
            case 2: MovAngK[i]+=AngK[i]/LAP; LongK[i]-=3.3; DrawCyberK(NumMax[i]-1,i); 
                    if (TimerK[i]==LAP){TimerK[i]=-1; StateK[i]=0; NewPoint(i); CreatePath(i);}
                    break;
        	default:
                    break;
        }
     	TimerK[i]++;
     }

	txt_SetCursor(0,1);

#if defined(_DISP_PERFORMANCE_)
	/* Write FPS on screen -----------------------------------------------------*/
	PRINTOUT(("FRAME : %06d%06d  Now:%07.3fFPS, Ave:%07.3fFPS\n",frame_2, frame,nFPS,aFPS));
#if 0
	PRINTOUT(("now:%07.3f, total:%07.3f, ave:%07.3f\n",nowTime,totalTime,aveTime));
#endif
#else
	PRINTOUT(("FRAME : %06d%06d\n",frame_2, frame));
#endif	/* defined(_DISP_PERFORMANCE_) */

	/*-----------------------------------------------------------------------------------*/
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
	Check_Status(status, "kmRender");

	/*-----------------------------------------------------------------------------------*/

#if defined(_DISP_PERFORMANCE_)
/* 性能計算 ------------------------------------------------------------------*/
	EndTime	= syTmrGetCount();
	/* ただいまのフレームを作成するのにかかった時間 */
	nowTime = syTmrCountToMicro( syTmrDiffCount( StartTime, EndTime ) ) / 1000.0f;
	StartTime = EndTime;

	if((nowTime > 1000.0f)||(nowTime < 1.0f))
	{
		nowTime = 20.0f;
	}

	/* もっとも時間がかかった？ */
	if(nowTime > maxTime)
	{
		maxTime = nowTime;
	}

	/* もっとも早かった？ */
	if(nowTime < minTime)
	{
		minTime = nowTime;
	}

	totalTime += nowTime;								/* 累積時間 		*/
	aveTime = totalTime / ((double)frame + 1.0f);		/* 今までの平均時間 */

	nFPS  = 1000.0f / (double)nowTime;
	aFPS  = 1000.0f / (double)aveTime;
	MxFPS = 1000.0f / (double)minTime;
	MnFPS = 1000.0f / (double)maxTime;
#endif	/* defined(_DISP_PERFORMANCE_) */

	frame++;
	Movement++;

	if (Movement == 400){	Movement = 0;}

	if(frame > 1000000)
	{
		/* フレームのリセット */
		frame = 0;
#if defined(_DISP_PERFORMANCE_)
		totalTime = 0;
#endif	/* defined(_DISP_PERFORMANCE_) */
		frame_2++;
	}
}

/*-------------------------------------------------------------------------------------*
 *  Function Name   :   Finish                                                         *
 *  Inputs          :   None                                                           *
 *  Outputs         :   None                                                           *
 *  Returns         :   None                                                           *
 *  Globals Used    :   Device                                                         *
 *  Description     :   Free textures and close device.                                *
 *                      This routine is called from FRONTEND.C                         *
 *-------------------------------------------------------------------------------------*/
void Finish()
{
	/*-----------------------------------------------------------------------------------*/
	/* Free Texture Surface */
	status = kmFreeTexture(&CyberKTex);
	Check_Status(status, "kmFreeTexture");
	status = kmFreeTexture(&GroundTex);
	Check_Status(status, "kmFreeTexture");
	status = kmFreeTexture(&SkyTex);
	Check_Status(status, "kmFreeTexture");

	/*-----------------------------------------------------------------------------------*/
	/* Free vertex buffer */
	status = kmDiscardVertexBuffer(&VertexBufferDesc);
	Check_Status(status, "kmDiscardVertexBuffer");

	/*-----------------------------------------------------------------------------------*/
	/* End display */
	status = kmStopDisplayFrameBuffer();
	Check_Status(status, "kmStopDisplayFrameBuffer");
}

/*-------------------------------------------------------------------------------------*
 *  Function Name   :   DrawGround                                                     *
 *  Inputs          :   None                                                           *
 *  Outputs         :   None                                                           *
 *  Returns         :   None                                                           *
 *  Globals Used    :                                                                  *
 *  Description     :   Draw ground.                                                   *
 *-------------------------------------------------------------------------------------*/
void DrawGround()
{
	PVRVERTEX	Vert[4];
	int			Face[1][4] = {0, 1, 2, 3};
	int			i;
	float		Pos;

	/* Four points to set a big quad. */
	pvr_vector	Pnt[4] =	{
								{-5000.0f,  -0.0f, -100.0f},
	                			{-5000.0f,  -0.0f, 8000.0f},
                     			{ 6000.0f,  -0.0f, 8000.0f},
                     			{ 6000.0f,  -5.0f, -100.0f}
							};	

    for (i=0; i<4; i++)
	{
        Perspect (Pnt[i], &Vert[i]);                     
        /* Set the colour for each vertex. */
		Vert[i].u32Colour   = RGBA(255,255,255,160);
		Vert[i].u32Specular = RGBColour (255,255,255);
	}

    /* Here the continous fluency of the ground.  *
     * Note that I just move texture's UV values. *
     * I don't move the camera.                   */
    Pos = Movement / 50.0f;
    
    /* Set UV values for each textured vertex. */
    Vert[0].fUOverW = 0.0f;		Vert[0].fVOverW = Pos + 0.0f;
    Vert[1].fUOverW = 0.0f;		Vert[1].fVOverW = Pos + 30.0f;
    Vert[2].fUOverW = 35.0f;	Vert[2].fVOverW = Pos + 20.0f;
    Vert[3].fUOverW = 35.0f;	Vert[3].fVOverW = Pos + 0.0f;

    /* Set a sigle textured and transparent quad to create the ground. */
	kmtri_quads (	&VertexBufferDesc,		/* PKMVERTEXBUFFDESC */
					&StripHead03_Ground,	/* PKMSTRIPHEAD		 */
					1,						/* int  nNumFaces	 */
					Face,					/* int  pFaces[][4]	 */
					Vert,					/* PPVRVERTEX		 */
					TRUE					/* bTexture			 */
				);
}

/*-------------------------------------------------------------------------------------*
 *  Function Name   :   DrawSky                                                        *
 *  Inputs          :   None                                                           *
 *  Outputs         :   None                                                           *
 *  Returns         :   None                                                           *
 *  Globals Used    :                                                                  *
 *  Description     :   Draw Sky. (The same as DrawGround)                             *
 *-------------------------------------------------------------------------------------*/
void DrawSky()
{
	float		Pos=0;
	PVRVERTEX	Vert[4];
	int			Face[1][4] = {0,1,2,3};
	int			i;
	pvr_vector	Pnt[4] ={
							{-4000.0f,600.0f,  -100.0f},
    	                	{-4000.0f,600.0f, 50000.0f},
    	                 	{ 8000.0f,600.0f, 50000.0f},
    	                 	{ 8000.0f,600.0f,  -100.0f}
						};

    for (i=0; i<4; i++)
	{ 
        Perspect (Pnt[i], &Vert[i]);
        Vert[i].u32Colour   = RGBColour (255,255,255);
        Vert[i].u32Specular = RGBColour (255,255,255);
    }
    
    /* Here the continous fluency of the sky.     *
     * I just move texture's UV values.           */
    Pos = Movement/400.0; 

    Vert[0].fUOverW = 0.0;  Vert[0].fVOverW = Pos-0.0;
    Vert[1].fUOverW = 0.0;  Vert[1].fVOverW = Pos+5.0;
    Vert[2].fUOverW = 10.0; Vert[2].fVOverW = Pos+5.0;
    Vert[3].fUOverW = 10.0; Vert[3].fVOverW = Pos+00.0;

	kmtri_quads (	&VertexBufferDesc,		/* PKMVERTEXBUFFDESC */
					&StripHead03_Sky,		/* PKMSTRIPHEAD		 */
					1,						/* int  nNumFaces	 */
					Face,					/* int  pFaces[][4]	 */
					Vert,					/* PPVRVERTEX		 */
					TRUE					/* bTexture			 */
				);

}

/*-------------------------------------------------------------------------------------*
 *  Function Name   :   CreatePath                                                     *
 *  Inputs          :   Num                                                            *
 *  Outputs         :   None                                                           *
 *  Returns         :   None                                                           *
 *  Globals Used    :   PathK, p1, p2, RotVect, MovAngK, AngK                          *
 *  Description     :   Calculates a parabolic path (jump) for each CyberK             *
 *-------------------------------------------------------------------------------------*/
void CreatePath (int Num)
{
	int		i = 0;
	float	dist;
	float	t = 0.0f;
	float	A;
	float	CosA, SinA, x, Vel, Lang;
	pvr_vector End1, End2;

	End1[0]=p1[Num][0];
	End1[2]=p1[Num][2];
	End2[0]=p2[Num][0];
	End2[2]=p2[Num][2];

	dist = sqrt ((End2[2]-End1[2])*(End2[2]-End1[2])+(End1[0]-End2[0])*(End1[0]-End2[0]));

	RotVecK[Num][0] = (End2[2] - End1[2]);
	RotVecK[Num][1] = 0.0f;
	RotVecK[Num][2] = (End1[0] - End2[0]);

	if (fabs(RotVecK[Num][2]) < 0.1f)
	{
		RotVecK[Num][2] *= 10.0f;
 	}

	A = -atan ( (End1[2]-End2[2])/(End1[0]-End2[0]) );
	CosA = (End1[0]<End2[0]) ?  cos(A) : -cos(A);
	SinA = (End1[0]<End2[0]) ? -sin(A) :  sin(A);

	MovAngK[Num] = 0.0f;  Lang = atan (-4 * HIGH / dist);
	AngK[Num]  = ((PI/2.0)+Lang)/1.2;
	AngK[Num]  = (End1[0]<End2[0]) ? -AngK[Num]:AngK[Num];
	Vel  = sqrt (GRV * dist / sin(2*Lang));

	while (1)
	{
		x = Vel * cos(Lang) * t;
		PathK[Num][i][1] = -Vel * sin (Lang) * t + GRV/2 * t*t;
		PathK[Num][i][0] = End1[0] + CosA*x;
		PathK[Num][i][2] = End1[2] + SinA*x;

		if (PathK[Num][i][1]<0.0 && i>1){ break;}
		t += TLP; i++;
	}

	PathK[Num][i][0] = p2[Num][0];
	PathK[Num][i][1] = p2[Num][1];
	PathK[Num][i][2] = p2[Num][2];

	NumMax[Num]=++i;
}
/*-------------------------------------------------------------------------------------*
 *  Function Name   :   NewPoint                                                       *
 *  Inputs          :   Num                                                            *
 *  Outputs         :   None                                                           *
 *  Returns         :   None                                                           *
 *  Globals Used    :   NewAng, p1, p2                                                 *
 *  Description     :   Calculates two end points for creating a new path (jump).      *
 *-------------------------------------------------------------------------------------*/
void NewPoint (int Num)
{
    NewAng[Num]+=((float)((char)(rand())) / 255.0f) * ( 2.5f - Num * (2.0f / 50.0f));

    p1[Num][0] = p2[Num][0]; p1[Num][2] = p2[Num][2];

    p2[Num][0] = 50.0f * (Num /2.0f + 1.0f) * cos(NewAng[Num] / 2.0f);
    p2[Num][2] = 50.0f * (Num /2.0f + 1.0f) * sin(NewAng[Num] / 2.0f) + 500.0f + frame * 5.0f;
}
/*-------------------------------------------------------------------------------------*
 *  Function Name   :   SetupTextures                                                  *
 *  Inputs          :   None                                                           *
 *  Outputs         :   None                                                           *
 *  Returns         :   None                                                           *
 *  Globals Used    :   SeaTex, SealTex, GroundTex, SkyTex                             *
 *  Description     :   Loads all texture bitmaps.                                     *
 *-------------------------------------------------------------------------------------*/
void SetupTextures (void)
{
	PKMDWORD			pTexture01;				/* Pointer to texture		*/
	KMTEXTURETYPE		nTextureType;			/* texture type definition	*/

	/*-----------------------------------------------------------------------------------*/
	/* Create texture surface */
	nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&CyberKTex,				/* OUT	PKMSURFACEDESC	pSurfaceDesc	*/
		128,					/*	IN	KMINT32			nWidth			*/
		128,					/*	IN	KMINT32			nHeight			*/
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType	*/
	);
	Check_Status(status, "kmCreateTextureSurface(SeaTex)");

	nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&GroundTex,				/* OUT	PKMSURFACEDESC	pSurfaceDesc	*/
		128,					/*	IN	KMINT32			nWidth			*/
		128,					/*	IN	KMINT32			nHeight			*/
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType	*/
	);
	Check_Status(status, "kmCreateTextureSurface(GroundTex)");

	nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&SkyTex,				/* OUT	PKMSURFACEDESC	pSurfaceDesc 	*/
		128,					/*	IN	KMINT32			nWidth		 	*/
		128,					/*	IN	KMINT32			nHeight			*/
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType	*/
	);
	Check_Status(status, "kmCreateTextureSurface(SkyTex)");

	/*-----------------------------------------------------------------------------------*/
	/* Load and set texture */
	pTexture01 = (unsigned long *)&cyb_cyberk;
	status = kmLoadTexture(	&CyberKTex,								/* PKMSURFACEDESC pSurfaceDesc	*/
							pTexture01 + (16 / sizeof(KMDWORD))		/* PKMDWORD pTexture			*/
							);
	Check_Status(status, "kmLoadTexture(CyberK.pvr)");

	pTexture01 = (unsigned long *)&cyb_cyground;
	status = kmLoadTexture(	&GroundTex,								/* PKMSURFACEDESC pSurfaceDesc	*/
							pTexture01 + (16 / sizeof(KMDWORD))		/* PKMDWORD pTexture			*/
							);
	Check_Status(status, "kmLoadTexture(Ground.pvr)");

	pTexture01 = (unsigned long *)&cyb_cysky;
	status = kmLoadTexture(&SkyTex,									/* PKMSURFACEDESC pSurfaceDesc	*/
							pTexture01 + (16 / sizeof(KMDWORD))		/* PKMDWORD pTexture			*/
							);
	Check_Status(status, "kmLoadTexture(Sky.pvr)");
}

/*-------------------------------------------------------------------------------------*
 *  Function Name   :   SetupContex                                                    *
 *  Inputs          :   None                                                           *
 *  Outputs         :   None                                                           *
 *  Returns         :   None                                                           *
 *  Globals Used    :                                                                  *
 *  Description     :   Setup Contex values.                                           *
 *-------------------------------------------------------------------------------------*/
void SetupContext (void)
{
	/**************************
	 * KMSTRIPHEADの構築
	 **************************/
#if 0
	/* VertexType00用 */
	memset( &StripContext00		, 	0, sizeof(StripContext00));
	memset( &StripHead00_Ground	,	0, sizeof(StripHead00_Ground));
	memset( &StripHead00_Sky	,	0, sizeof(StripHead00_Sky));
	memset( &StripHead00_CyberK	,	0, sizeof(StripHead00_CyberK));

	InitStripContext00(&StripContext00,&StripHead00_Ground);
	InitStripContext00(&StripContext00,&StripHead00_Sky);
	InitStripContext00(&StripContext00,&StripHead00_CyberK);
#endif

	/* VertexType03用 */
	memset( &StripContext03		, 	0, sizeof(StripContext03));
	memset( &StripHead03_Ground	,	0, sizeof(StripHead03_Ground));
	memset( &StripHead03_Sky	,	0, sizeof(StripHead03_Sky));
	memset( &StripHead03_CyberK	,	0, sizeof(StripHead03_CyberK));

	InitStripContext03(&StripContext03, &StripHead03_Ground, &GroundTex	);
	InitStripContext03(&StripContext03, &StripHead03_Sky,	 &SkyTex	);
	InitStripContext03(&StripContext03, &StripHead03_CyberK, &CyberKTex	);

	/*--------------------------------------------------------------------------------*/
	/* KMSTRIPHEAD for Ground */
	kmChangeStripBlendingMode		( &StripHead03_Ground, KM_IMAGE_PARAM1, KM_SRCALPHA, KM_INVSRCALPHA );
	kmChangeStripListType			( &StripHead03_Ground, KM_TRANS_POLYGON );
	kmChangeStripTextureShadingMode	( &StripHead03_Ground, KM_IMAGE_PARAM1, KM_MODULATE_ALPHA );
	kmChangeStripUseAlpha			( &StripHead03_Ground, KM_IMAGE_PARAM1, KM_TRUE );
	kmChangeStripGouraud			( &StripHead03_Ground, KM_TRUE );

	/*--------------------------------------------------------------------------------*/
	/* KMSTRIPHEAD for Sky */
	kmChangeStripGouraud			( &StripHead03_Sky, KM_TRUE );

	/*--------------------------------------------------------------------------------*/
	/* KMSTRIPHEAD for CyberK */
	kmChangeStripGouraud			( &StripHead03_Sky, KM_TRUE );
}

/*-------------------------------------------------------------------------------------*
 *  Function Name   :   Perspect                                                       *
 *  Inputs          :   Point3D                                                        *
 *  Outputs         :   Vert                                                           *
 *  Returns         :   None                                                           *
 *  Globals Used    :   None                                                           *
 *  Description     :                                                                  *
 *-------------------------------------------------------------------------------------*/
void Perspect (const pvr_vector Point3D, PVRVERTEX *Vert)
{
	const pvr_vector CamPos = { 0.0f, 40.0f, 150.0f};
	float x, y, z;

    x    =  Point3D[0] + CamPos[0];
    y    = -Point3D[1] + CamPos[1];
    z    = (Point3D[2] + CamPos[2]) ;

    Vert->fX    =  (CamFocus * x) / z + 320;
    Vert->fY    =  (CamFocus * y) / z + 240;

    /* The render uses fInvW (1/z) to set the Z-buffer 		*
     * In this case I use it to set the fog effect as well	*/
     Vert->fInvW =  1.8f / z;                   
}

/*-------------------------------------------------------------------------------------*
 *  Function Name   :   SetupPrisms                                                    *
 *  Inputs          :   None                                                           *
 *  Outputs         :   None                                                           *
 *  Returns         :   None                                                           *
 *  Globals Used    :   Prism3DVert, PrismVert                                         *
 *  Description     :   Setup prisms vertex                                            *
 *-------------------------------------------------------------------------------------*/
void SetupPrism (void)
{
	int Sh[] = {0, 150, 200, 255, 255, 200, 150, 85, 0, 0};
	int ColR, ColG, ColB, ColRSh, ColGSh, ColBSh;
	register i, j, k;
	int cont = 0;

	/* Here we set values for a default CyberK (3 prisms) */
	for (j=0; j<2; j++)
	{
		for (i=0; i<10; i++)
		{
	    	for (k=0; k<3; k++)
			{
	        	Prism3DVect[k][cont][0]			= (2.0f + (float)k * 4.0f) * cos (((float)i * PI * 2.0f) / 9.0f);
	            Prism3DVect[k][cont][1]         = (float)j * 20.0f;
	            Prism3DVect[k][cont][2]         = (2.0f + (float)k * 4.0f) * sin (((float)i * PI * 2.0f) / 9.0f);
	            PrismVect[k][cont].fUOverW      = (float)(i + 2) / 9.0f;
	            PrismVect[k][cont].fVOverW      = (float)(j) / 0.95f;
	            ReflectVect[k][cont].fUOverW    = (float)(i + 2) / 9.0f;
	            ReflectVect[k][cont].fVOverW    = (float)(j) / 0.95f;
			}
	       cont++;
		}
	}

	/* Here we set the color and the shade for each vertex */
	for (i=0; i<NMAX; i++)
	{
	    ColR = 50 + (int)(rand() & 0x00FF) * 200.0f / 255.0f;
	    ColB = 50 + (int)(rand() & 0x00FF) * 200.0f / 255.0f;
	    ColG = 50 + (int)(rand() & 0x00FF) * 200.0f / 255.0f;

    	for (j=0; j<10; j++)
		{
    	    ColRSh = (ColR * Sh[j]) / 200.0f; if (ColRSh > 255) ColRSh = 255;
    	    ColGSh = (ColG * Sh[j]) / 200.0f; if (ColGSh > 255) ColGSh = 255;
    	    ColBSh = (ColB * Sh[j]) / 200.0f; if (ColBSh > 255) ColBSh = 255;
    	    PrismCol [i][j] = RGBColour (ColRSh, ColGSh, ColBSh);
		}
	}
}

/*-------------------------------------------------------------------------------------*
 *  Function Name   :   DrawCyberK                                                     *
 *  Inputs          :   PNum                                                           *
 *  Outputs         :   None                                                           *
 *  Returns         :   None                                                           *
 *  Globals Used    :   Prism3DVert, PrismVert                                         *
 *  Description     :   Draw six prisms to build a CyberK and its reflection           *
 *-------------------------------------------------------------------------------------*/
void DrawCyberK (int Pos,int KNum)
{
	register i, j, k, cont=0, Sign = TRUE;
	float TempAng, xx, x, y, z;
	pvr_vector TempVect;
	float CosZ, SinZ, CosY, SinY, CurrentLong;

    if (PathK[KNum][Pos][2]-frame*5 < -210){ return;}

    TempAng = -atan ((RotVecK[KNum][0]/RotVecK[KNum][2]));

    if (RotVecK[KNum][0] < 0.0 || RotVecK[KNum][2] < 0.0){ Sign = FALSE;}

    CosZ = cos (MovAngK[KNum]);
    SinZ = sin (MovAngK[KNum]);
    CosY = cos (TempAng);
    SinY = sin (TempAng);
 
	for (k=0; k<3; k++)
    {
		CurrentLong =  k*((LongK[KNum])/3.0) - k*(60-LongK[KNum])/5.0;
		for (j=0; j<2; j++)
    	{
    		for (i=0; i<10; i++)
      		{
         		x =  Prism3DVect[k][cont][0];
         		y =  Prism3DVect[k][cont][1];
         		z =  Prism3DVect[k][cont][2];

         		if (Sign) { x=-x;  z=-z;}

			    /* VERTICAL TRANSLATION */
         		y += CurrentLong;
    			/* Z_AXIS ROTATION      */
 		        xx = x;
 		        x  = xx * CosZ - y  * SinZ;
 		        y  = y  * CosZ + xx * SinZ;
			    /* Y_AXIS ROTATION      */
		         xx = x;
		         x  = xx * CosY - z  * SinY;
		         z  = z  * CosY + xx * SinY;
			    /* TRANSLATION          */
		        TempVect[0] = x + PathK[KNum][Pos][0];
		        TempVect[1] = y + PathK[KNum][Pos][1];
		        TempVect[2] = z + PathK[KNum][Pos][2] - frame*5 + 100;

		        Perspect (TempVect, &PrismVect[k][cont]);

    		    TempVect[1] = -TempVect[1];
    		    Perspect (TempVect, &ReflectVect[k][cont]);

			    /* Setting smooth shading */
		        PrismVect   [k][cont].u32Colour   = PrismCol[KNum][i];
		        PrismVect   [k][cont].u32Specular = RGBColour (255, 255, 255);
		        ReflectVect [k][cont].u32Colour   = PrismCol[KNum][i];
		        ReflectVect [k][cont].u32Specular = RGBColour (255, 255, 255);;
   
  				cont++;
			}
		}
	    cont = 0;

		kmtri_quads (	&VertexBufferDesc,		/* PKMVERTEXBUFFDESC */
						&StripHead03_CyberK,	/* PKMSTRIPHEAD		 */
						14,						/* int  nNumFaces	 */
						&(PrismFaces[4]),		/* int  pFaces[][4]	 */
						PrismVect[k],			/* PPVRVERTEX		 */
						TRUE					/* bTexture			 */
					);

		kmtri_quads (	&VertexBufferDesc,		/* PKMVERTEXBUFFDESC */
						&StripHead03_CyberK,	/* PKMSTRIPHEAD		 */
						14,						/* int  nNumFaces	 */
						&(PrismFaces[4]),		/* int  pFaces[][4]	 */
						ReflectVect[k],			/* PPVRVERTEX		 */
						TRUE					/* bTexture			 */
					);

	    /* We change the colour for simulating the shade on the bottom face */ 
	    for (i=0; i<20; i++)
	    {
	        PrismVect[k][i].u32Colour     = RGBColour ( 60, 60, 60);
	        ReflectVect[k][i].u32Colour   = RGBColour ( 60, 60, 60);
	    }

		kmtri_quads (	&VertexBufferDesc,		/* PKMVERTEXBUFFDESC */
						&StripHead03_CyberK,	/* PKMSTRIPHEAD		 */
						4,						/* int  nNumFaces	 */
						&(PrismFaces[0]),		/* int  pFaces[][4]	 */
						PrismVect[k],			/* PPVRVERTEX		 */
						TRUE					/* bTexture			 */
					);

		kmtri_quads (	&VertexBufferDesc,		/* PKMVERTEXBUFFDESC */
						&StripHead03_CyberK,	/* PKMSTRIPHEAD		 */
						4,						/* int  nNumFaces	 */
						&(PrismFaces[0]),		/* int  pFaces[][4]	 */
						ReflectVect[k],			/* PPVRVERTEX		 */
						TRUE					/* bTexture			 */
					);

	}
}

/****************************************************************************
 *	main
 ****************************************************************************/
int	Kamui_Init(void)
{
	txt_ClearScreen();		/* Clear text screen	*/
#if defined(_VERTEXMACRO_L4_)
	PRINTOUT(("** KMCYBERK(KAMUI2&Shinobi) Use:Level4 Macro **\n"));
#else
	PRINTOUT(("** KMCYBERK(KAMUI2&Shinobi) **\n"));
#endif
    SetupScene ();			/* Initialize System	*/
	PRINTOUT(("\n"));
}

/*----------------------------------------------------------------------*
 *  Function Name   : ReadMaple                                         *
 *  Inputs          :                                                   *
 *  Outputs         :                                                   *
 *  Returns         :                                                   *
 *  Globals Used    : PosZ, BlendSrc, BlendDst, AlphaSource,            *
 *                    BlendModulate                                     *
 *  Description     : Read MAPLE status                                 *
 *----------------------------------------------------------------------*/
void ReadMaple(void)
{
	per = pdGetPeripheral(PDD_PORT_A0);

	/* A button */
	if ( per->press & PDD_DGT_TA )
	{
		NK++;
		if (NK > NMAX){ NK = NMAX;}
		txt_SetCursor( 0, 2 );
		PRINTOUT(("Num : %d\n",NK));
	}

	/* B button */
	if ( per->press & PDD_DGT_TB )
	{
		NK--;
		if (NK < 1){ NK = 1;}
		txt_SetCursor( 0, 2 );
		PRINTOUT(("Num : %d\n",NK));
	}

	/* X button */
	if ( per->press & PDD_DGT_TX )
	{
		if(TransGround == 1)
		{
			TransGround = 0;
			kmChangeStripBlendingMode		( &StripHead03_Ground, KM_IMAGE_PARAM1, KM_ONE, KM_ZERO );
			kmChangeStripListType			( &StripHead03_Ground, KM_OPAQUE_POLYGON);
			kmChangeStripTextureShadingMode	( &StripHead03_Ground, KM_IMAGE_PARAM1, KM_MODULATE);
			kmChangeStripUseAlpha			( &StripHead03_Ground, KM_IMAGE_PARAM1, KM_FALSE);
		}
		else
		{
			TransGround = 1;
			kmChangeStripBlendingMode		( &StripHead03_Ground, KM_IMAGE_PARAM1, KM_SRCALPHA, KM_INVSRCALPHA );
			kmChangeStripListType			( &StripHead03_Ground, KM_TRANS_POLYGON);
			kmChangeStripTextureShadingMode	( &StripHead03_Ground, KM_IMAGE_PARAM1, KM_MODULATE_ALPHA);
			kmChangeStripUseAlpha			( &StripHead03_Ground, KM_IMAGE_PARAM1, KM_TRUE);
		}
	}

}

/*--------------------------- End of File --------------------------------*/
