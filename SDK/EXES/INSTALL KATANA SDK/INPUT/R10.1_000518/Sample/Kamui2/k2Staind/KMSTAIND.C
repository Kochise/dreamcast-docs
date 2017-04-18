/********************************************************************************/
/* Name     : STAINED															*/
/* Title    : KAMUI test program "STAINED" from VL								*/
/* Author   : VideoLogic Carlos Sarria / NEC Software Takeshi Muto				*/
/* Created  : July 1997 by VideoLogic											*/
/* Modified : 	Novenber  5. 1997 by Takeshi Muto	for KAMUI					*/
/*				February  4. 1999 by H.Nakayama	for KAMUI2						*/
/*				February 16. 1999 by Takeshi Muto for Shinobi					*/
/*																				*/
/* Description :																*/
/* Copyright : 1997 by VideoLogic Limited. All rights reserved.					*/
/********************************************************************************/

#define		SPEED			(1.0f)	/* move speed ( 1 to n ) */

#define		_DISPLAY_STRING_
/* if defined then display strings on screen */

#define		_DISP_PERFORMANCE_
/* Display performance */

#include	<math.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<float.h>
#include	<Shinobi.h>
#include	<sg_sytmr.h>	/* System timer */

#pragma warning (disable : 4244) /* Disables float to double conversion warning */
#pragma warning (disable : 4056)
#define _STRICT_UNION_
#define _CLX2_
#define _CLX_

#include	"kamui2.h"				/* for Kamui Call */
#include	"dispstr.h"				/* for DisplayString */

#include	"kmstaind.h"			/* This is the file with 3D data */

/* Textures */
#include	"vltex.h"				/* for vl sample texture */

/* Texture pixel struct */
typedef struct {
	KMUCHAR8	alpha;
	KMUCHAR8	blue;
	KMUCHAR8	green;
	KMUCHAR8	red;
} KMTEX_PIXEL;

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
	KMSURFACEDESC		Texture[10];			/* texture surface */
	KMVERTEXBUFFDESC	VertexBufferDesc;		/* Vertex-buffer */

	PKMDWORD			BuffTex;				/* Pointer to texture */

	PKMSURFACEDESC		pFB[2];
	KMDWORD				FBarea[24576 + 19456];
								/* FBstruct 4096 Entry (= 4096 * 24 / 4) */
								/* VQstruct 1024 Entry (= 1024 * 76 / 4) */
	KMDWORD				DUMPAREA[10000];
	KMSYSTEMCONFIGSTRUCT	SystemConfig;
	PKMDWORD			dwDataPtr;
/*************************/
/* for VertexParam		 */
/*************************/
KMSTRIPCONTEXT 			StripContext[2];/* Strip Context */
KMSTRIPHEAD 			StripHead[2];	/* Strip Head */
										/* [0]:TYPE00 , [1]:TYPE03 */

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

#define PI	3.1416f

int		Init = TRUE;
int		frame;
int		TPos = 280;
int		UpVert=1;
int		PosX = 10;
int		PosY = 10;
float	Shad[255], GroundSh[1000];
float	XAng  = -6.3f,  YAng  =-18.85f;
float	xd	= 0.002f;
float	yd	= 0.008f;

PVRVERTEX  *TempVert[NUM_MESHES];
KMUINT32   GroundCo[1000][3], GCo[1000][3], Logo[50][50][3];

/* Prototypes */
void SetupContext   (void);
void SetupTextures  (void);
void InitMeshes     (void);
void DrawAll        (void);
void UpdateVertex   (int Num);
void Shading        (int Num);
void GroundColour   (void);
void CalculateLight (void);
void ShadingGround  (void);
void MoveLamp       (void);
void ReadMaple (void);

/* Peripheral */
PDS_PERIPHERAL *per;

/****************************************************************************/
/**	Check KAMUI function status *********************************************/
/****************************************************************************/
void	Check_Status(KMSTATUS status, char *func)
{
	switch(status) {
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
	KMVERTEX_01			BV[3];					/* pointer to Vertex */
	PVOID				pBV[3];					/* pointer to Vertex */

	/* Clear VertexContext */
	memset(&BackVertexContext,0,sizeof(KMVERTEXCONTEXT));

	/* Setup VertexContext */
	BackVertexContext.RenderState	=
										KM_DEPTHMODE			|	KM_CULLINGMODE			/* for ISP_TSP	*/
									|	KM_ZWRITEDISABLE		|	KM_DCALCEXACT
									|	KM_SRCBLENDINGMODE		|	KM_DSTBLENDINGMODE		/* for TSP		*/
									|	KM_SRCSELECT			|	KM_DSTSELECT
									|	KM_FOGMODE				|	KM_COLORCLAMP
									|	KM_USEALPHA				|	KM_IGNORETEXTUREALPHA
									|	KM_FLIPUV				|	KM_CLAMPUV
									|	KM_FILTERMODE			|	KM_SUPERSAMPLE
									|	KM_MIPMAPDADJUST		|	KM_TEXTURESHADINGMODE
									|	KM_PARAMTYPE			|	KM_LISTTYPE				/* for ParamCW	*/
									|	KM_USERCLIPMODE			|	KM_MODIFIER
									|	KM_COLORTYPE			|	KM_SHADINGMODE
									|	KM_USESPECULAR			|	KM_UVFORMAT;

	/* for ParameterControlWord */
	BackVertexContext.ParamType				=	KM_POLYGON;
	BackVertexContext.ListType				=	KM_OPAQUE_POLYGON;
	BackVertexContext.SelectModifier		=	KM_NOMODIFIER;
	BackVertexContext.UserClipMode			=	KM_USERCLIP_DISABLE;
	BackVertexContext.ColorType				=	KM_FLOATINGCOLOR;
	BackVertexContext.ShadingMode			=	KM_NOTEXTUREGOURAUD;
	BackVertexContext.bUseSpecular			=	KM_FALSE;
	BackVertexContext.UVFormat				=	KM_32BITUV;

	/* for ISP_TSP InstructionWord */
	BackVertexContext.DepthMode				=	KM_GREATER;
	BackVertexContext.CullingMode			=	KM_NOCULLING;
	BackVertexContext.bZWriteDisable		=	KM_FALSE;
	BackVertexContext.bDCalcExact			=	KM_FALSE;

	/* for TSP ControlWord */
	BackVertexContext.SRCBlendingMode		=	KM_ONE;
	BackVertexContext.DSTBlendingMode		=	KM_ZERO;
	BackVertexContext.bSRCSel				=	KM_FALSE;
	BackVertexContext.bDSTSel				=	KM_FALSE;
	BackVertexContext.FogMode				=	KM_NOFOG;
	BackVertexContext.bColorClamp			=	KM_FALSE;
	BackVertexContext.bUseAlpha				=	KM_FALSE;
	BackVertexContext.bIgnoreTextureAlpha	=	KM_FALSE;
	BackVertexContext.FlipUV				=	KM_NOFLIP;
	BackVertexContext.ClampUV				=	KM_NOCLAMP;
	BackVertexContext.FilterMode			=	KM_POINT_SAMPLE;
	BackVertexContext.bSuperSample			=	KM_FALSE;
	BackVertexContext.MipMapAdjust			=	KM_MIPMAP_D_ADJUST_1_00;
	BackVertexContext.TextureShadingMode	=	KM_MODULATE;

	/* for Texture ControlBit */
	BackVertexContext.PaletteBank			=	0;

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
	BV[0].fX				=   0.0f;
	BV[0].fY				= 479.0f;
#if defined(_STRICT_UNION_)
	BV[0].u.fZ				=  0.0001f;
#else
	BV[0].fZ				=  0.0001f;
#endif
	BV[0].fBaseAlpha		=   0.0f;
	BV[0].fBaseRed			=   0.3f;
	BV[0].fBaseGreen		=   0.3f;
	BV[0].fBaseBlue			=   0.3f;

	/* Vertex #2 */
	BV[1].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
	BV[1].fX				= 320.0f;
	BV[1].fY				=   0.0f;
#if defined(_STRICT_UNION_)
	BV[1].u.fZ				=  0.0001f;
#else
	BV[1].fZ				=  0.0001f;
#endif
	BV[1].fBaseAlpha		=   0.0f;
	BV[1].fBaseRed			=   0.1f;
	BV[1].fBaseGreen		=   0.1f;
	BV[1].fBaseBlue			=   0.1f;

	/* Vertex #3 */
	BV[2].ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;
	BV[2].fX				= 639.0f;
	BV[2].fY				= 479.0f;
#if defined(_STRICT_UNION_)
	BV[2].u.fZ				=  0.0001f;
#else
	BV[2].fZ				=  0.0001f;
#endif
	BV[2].fBaseAlpha		=   0.0f;
	BV[2].fBaseRed			=   0.3f;
	BV[2].fBaseGreen		=   0.3f;
	BV[2].fBaseBlue			=   0.3f;

	pBV[0] = &BV[0];
	pBV[1] = &BV[1];
	pBV[2] = &BV[2];

	/*----------------------------------------------------------------------------------- */
	/* set VERTEX */
	status = kmSetBackGroundPlane(	pBV,					/* pVertex */
									KM_VERTEXTYPE_01,		/* VertexType */
									sizeof(KMVERTEX_01)		/* StructSize */
									);
	Check_Status(status, "kmSetBackGroundPlane");
}

/****************************************************************************/
/**	kmtri_triangles  by T.Hirata ********************************************/
/****************************************************************************/
void 
kmtri_triangles ( KMVERTEXBUFFDESC		BufferDesc,
				  PKMSTRIPHEAD			pStripHead,
				  int  					nNumFaces,
				  int  					pFaces[][3],
				  PPVRVERTEX  			pVertices,
				  int					bTexture)
{
	KMSTATUS	status;
	int			i;
	KMVERTEX_00	Ver00;				/* for NO-TEXTURE-GOURAUD */
	KMVERTEX_03	Ver03;				/* for TEXTURE-GOURAUD */

	if(bTexture == TRUE)
	{
		kmStartStrip( &BufferDesc , pStripHead+1 );
									/* VERTEX TYPE_03用頂点登録開始 */
	}
	else
	{
		kmStartStrip( &BufferDesc , pStripHead );
									/* VERTEX TYPE_00用頂点登録開始 */
	}

	for(i = 0; i < nNumFaces; i++)
	{

		if(bTexture == TRUE)
		{
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
		}
		else
		{	/* if(bTexture == TRUE) : NO-TEXTURE */
			Ver00.ParamControlWord	= KM_VERTEXPARAM_NORMAL;
			Ver00.fX				= pVertices[pFaces[i][0]].fX;
			Ver00.fY				= pVertices[pFaces[i][0]].fY;
#if defined(_STRICT_UNION_)
			Ver00.u.fZ				= pVertices[pFaces[i][0]].fInvW;
#else
			Ver00.fZ				= pVertices[pFaces[i][0]].fInvW;
#endif
			Ver00.uBaseRGB.dwPacked	= pVertices[pFaces[i][0]].u32Colour;
			status = kmSetVertex(&BufferDesc,&Ver00,KM_VERTEXTYPE_00,sizeof(KMVERTEX_00) );
			Check_Status(status, "kmSetVertex");

			Ver00.ParamControlWord	= KM_VERTEXPARAM_NORMAL;
			Ver00.fX				= pVertices[pFaces[i][1]].fX;
			Ver00.fY				= pVertices[pFaces[i][1]].fY;
#if defined(_STRICT_UNION_)
			Ver00.u.fZ				= pVertices[pFaces[i][1]].fInvW;
#else
			Ver00.fZ				= pVertices[pFaces[i][1]].fInvW;
#endif
			Ver00.uBaseRGB.dwPacked	= pVertices[pFaces[i][1]].u32Colour;
			status = kmSetVertex(&BufferDesc,&Ver00,KM_VERTEXTYPE_00,sizeof(KMVERTEX_00) );
			Check_Status(status, "kmSetVertex");

			Ver00.ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;
			Ver00.fX				= pVertices[pFaces[i][2]].fX;
			Ver00.fY				= pVertices[pFaces[i][2]].fY;
#if defined(_STRICT_UNION_)
			Ver00.u.fZ				= pVertices[pFaces[i][2]].fInvW;
#else
			Ver00.fZ				= pVertices[pFaces[i][2]].fInvW;
#endif
			Ver00.uBaseRGB.dwPacked	= pVertices[pFaces[i][2]].u32Colour;
			status = kmSetVertex(&BufferDesc,&Ver00,KM_VERTEXTYPE_00,sizeof(KMVERTEX_00) );
			Check_Status(status, "kmSetVertex");
		} /* end of if(bTexture == TRUE) */
	}
	kmEndStrip(&BufferDesc);		/* 頂点登録終了 */
}

/****************************************************************************/
/**	Initialize Strip Context ************************************************/
/****************************************************************************/
/***************************************
 *	VertexType00用KMSTRIPHEADの構築
 ***************************************/
void	InitStripContext00(
								PKMSTRIPCONTEXT pStripContext,
								PKMSTRIPHEAD	pStripHead
)
{
	pStripContext->nSize						 					= sizeof(KMSTRIPCONTEXT);
	pStripContext->StripControl.nListType		 					= KM_OPAQUE_POLYGON;
	pStripContext->StripControl.nUserClipMode	 					= KM_USERCLIP_DISABLE;
	pStripContext->StripControl.nShadowMode		 					= KM_NORMAL_POLYGON;
	pStripContext->StripControl.bGouraud		 					= KM_TRUE;
	pStripContext->ObjectControl.nDepthCompare			 			= KM_GREATER;
	pStripContext->ObjectControl.nCullingMode			 			= KM_CULLSMALL;
	pStripContext->ObjectControl.bZWriteDisable			 			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nSRCBlendingMode	= KM_ONE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nDSTBlendingMode	= KM_ZERO;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bSRCSelect			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bDSTSelect			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFogMode			= KM_NOFOG;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bColorClamp		= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bUseAlpha			= KM_FALSE;

	kmGenerateStripHead00( pStripHead,pStripContext );
}

/***************************************
 *	VertexType03用KMSTRIPHEADの構築
 ***************************************/
void	InitStripContext03(
							PKMSTRIPCONTEXT pStripContext,	/* Strip context pointer */
							PKMSTRIPHEAD    pStripHead		/* Strip header */
		)
{
	pStripContext->nSize						 					= sizeof(KMSTRIPCONTEXT);
	pStripContext->StripControl.nListType							= KM_OPAQUE_POLYGON;
	pStripContext->StripControl.nUserClipMode						= KM_USERCLIP_DISABLE;
	pStripContext->StripControl.nShadowMode							= KM_NORMAL_POLYGON;
	pStripContext->StripControl.bOffset								= KM_FALSE;
	pStripContext->StripControl.bGouraud							= KM_TRUE;
	pStripContext->ObjectControl.nDepthCompare						= KM_GREATER;
	pStripContext->ObjectControl.nCullingMode						= KM_CULLSMALL;
	pStripContext->ObjectControl.bZWriteDisable						= KM_FALSE;
	pStripContext->ObjectControl.bDCalcControl						= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nSRCBlendingMode	= KM_ONE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nDSTBlendingMode	= KM_ZERO;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bSRCSelect			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bDSTSelect			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFogMode			= KM_NOFOG;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bColorClamp		= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bUseAlpha			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bIgnoreTextureAlpha= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFlipUV			= KM_NOFLIP;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nClampUV			= KM_NOCLAMP;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFilterMode		= KM_BILINEAR;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bSuperSampleMode	= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].dwMipmapAdjust		= KM_MIPMAP_D_ADJUST_1_00;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nTextureShadingMode= KM_MODULATE;

	kmGenerateStripHead03( pStripHead,pStripContext);
}

/*-------------------------------------------------------------------------------------*/
/*  Function Name   :   SetupScene                                                     */
/*  Inputs          :   None                                                           */
/*  Outputs         :   None                                                           */
/*  Returns         :   Error message or 0                                             */
/*  Globals Used    :   
/*  Description     :   This routine is used to set device and setup some values.  */
/*                      This routine is called from FRONTEND.C                         */
/*-------------------------------------------------------------------------------------*/
int SetupScene (void)
{
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
								KM_DSPBPP_RGB565,	/* nBpp */
								TRUE,				/* bDither */
								FALSE				/* bAntiAlias */
								);
	Check_Status(status, "kmSetDisplayMode");
#endif

	/*----------------------------------------------------------------------------------- */
	/**********/
	/* 初期化 */
	/**********/
	pFB[0] = &PrimarySurfaceDesc;
	pFB[1] = &BackSurfaceDesc;
	/* VertexBufferPointer(set5) */
#if 0
	dwDataPtr = (PKMDWORD)0xACB00000;
#else
	dwDataPtr = (PKMDWORD)(((KMDWORD)syMalloc(0x200000) & 0x0FFFFFFFUL) | 0xA0000000);
#endif

	SystemConfig.dwSize				=	sizeof(KMSYSTEMCONFIGSTRUCT);
	SystemConfig.flags				=	KM_CONFIGFLAG_ENABLE_CLEAR_FRAMEBUFFER;
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
	/* some initializes */
	SetupTextures (); 
	SetupContext  ();
    InitMeshes ();

	txt_InitDisplayString();	/* Initialize DisplayString routine */
	InitBackGround();			/* Setup background plane */

	/*----------------------------------------------------------------------------------- */
	/* initialize maple read library */
#if 0
	vInitMaple();
#endif

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
/*  Globals Used    :                                                                  */
/*  Description     :   Drawing everything and rendering.                              */
/*                      This routine is called from FRONTEND.C                         */
/*-------------------------------------------------------------------------------------*/
void NextFrame()
{
	char		str[256];

	/* シ－ンの開始	*/
	kmBeginScene(&SystemConfig);

	/* パスの開始 */
	kmBeginPass(&VertexBufferDesc);

	DrawAll ();

	txt_SetCursor(0,1);

#if defined(_DISP_PERFORMANCE_)
	/* Write Date & Time on screen ---------------------------------------------*/
	/* Write FPS on screen -----------------------------------------------------*/
	PRINTOUT(("FRAME:%06d%06d Now:%07.3fFPS, Ave:%07.3fFPS\n",frame_2, frame,nFPS,aFPS));
#else
	PRINTOUT(("FRAME:%06d%06d\n",frame_2, frame));
#endif	/* defined(_DISP_PERFORMANCE_) */

	/*-----------------------------------------------------------------------------------*/
	/* Rendering start */
#if defined(_DISPLAY_STRING_)
	txt_DispScreen(&VertexBufferDesc);		/* Display screen */
#endif
	/* パスの終了 */
	kmEndPass(&VertexBufferDesc);
	status = kmRender(KM_RENDER_FLIP);

	/* レンダリング */
/*	status = kmRender(KM_RENDER_FLIP);
	Check_Status(status, "kmRender");*/

	/* シ－ンの終了 */
	kmEndScene(&SystemConfig);

#if defined(_DISP_PERFORMANCE_)
/* 性能計算 ------------------------------------------------------------------*/
	EndTime	= syTmrGetCount();
	/* ただいまのフレームを作成するのにかかった時間 */
	nowTime = syTmrCountToMicro( syTmrDiffCount( StartTime, EndTime ) ) / 1000.0f;
	StartTime = EndTime;

	if((nowTime > 1000.0f)||(nowTime < 1.0f)){nowTime = 20.0f;}
												/* 得られた値が異常であった場合は無視 */
	if(nowTime > maxTime){maxTime = nowTime;}	/* もっとも時間がかかった？ */
	if(nowTime < minTime){minTime = nowTime;}	/* もっとも早かった？ */

	totalTime += nowTime;							/* 累積時間 */
	aveTime = totalTime / ((double)frame + 1.0f);	/* 今までの平均時間 */

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
/*  Function Name   :   Finish                                                         */
/*  Inputs          :   None                                                           */
/*  Outputs         :   None                                                           */
/*  Returns         :   None                                                           */
/*  Globals Used    :   
/*  Description     :   Free textures and close device.                                */
/*-------------------------------------------------------------------------------------*/
void Finish()
{
  Init = FALSE;
	/*----------------------------------------------------------------------------------- */
	/* Free Texture Surface */

	/*----------------------------------------------------------------------------------- */
	/* Free vertex buffer */
	status = kmDiscardVertexBuffer(&VertexBufferDesc);
	Check_Status(status, "kmDiscardVertexBuffer");

	/*----------------------------------------------------------------------------------- */
	/* End display */
	status = kmStopDisplayFrameBuffer();
	Check_Status(status, "kmStopDisplayFrameBuffer");
}

/*-------------------------------------------------------------------------------------*/
/*  Function Name   :  DrawAll                                                         */
/*  Inputs          :  None                                                            */
/*  Outputs         :  None                                                            */
/*  Returns         :  None                                                            */
/*  Globals Used    :  XAng, YAng, XAng1, YAng1,                                       */
/*  Description     :  Updates and draws all the meshes in the model.                  */
/*  Note            :  The definition of Mesh[i] struct is in logo.h                   */
/*-------------------------------------------------------------------------------------*/
void DrawAll()
{
register i;

    MoveLamp();
    GroundColour ();  /* Calculates new colors */

    for (i=0; i<NUM_MESHES; i++){
               
		if(UpVert==1 || i==LIGHT){UpdateVertex (i);} /* Only updates vertices if the scene has changed */
        if (i==NUM_MESHES-1){UpVert=0;}

	kmChangeStripTextureSurface(&StripHead[1],KM_IMAGE_PARAM1,&Texture[Mesh[i].Material]);
        /* Drawing triangles... */
	kmtri_triangles (	VertexBufferDesc,		/* KMVERTEXBUFFDESC	BufferDesc, */
					StripHead,					/* PKMSTRIPHEAD pStripHead */
					Mesh[i].NumFaces,			/* int  nNumFaces, */
					(int(*)[3])Mesh[i].Faces,	/* int  pFaces[][3], */
					TempVert[i],				/* PPVRVERTEX  pVertices */
				   	TRUE						/* int	bTexture */
					);
    } 
}
/*-------------------------------------------------------------------------------------*/
/*  Function Name   : SetupTextures                                                    */
/*  Inputs          : None                                                             */
/*  Outputs         : None                                                             */
/*  Returns         : None                                                             */
/*  Globals Used    : NumMaterials, Texture
/*  Description     : Loads BMP files getting the information from MatInfo struct      */
/*-------------------------------------------------------------------------------------*/
void SetupTextures (void)
{
register i;
	PKMDWORD			pTexture01;				/* Pointer to texture */
	KMTEXTURETYPE		nTextureType;			/* texture type definition */

	BuffTex = (unsigned long *)&sta_stpvr2;

	for (i=0;i<NumMaterials; i++){
	/*----------------------------------------------------------------------------------- */
	/* Create texture surface */
	nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&Texture[i],			/* OUT	PKMSURFACEDESC	pSurfaceDesc */
		128,					/*	IN	KMINT32			nWidth  */
		128,					/*	IN	KMINT32			nHeight  */
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType */
	);
	Check_Status(status, "kmCreateTextureSurface(RGB)");
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
	switch(i){
	default:
	case 0:	pTexture01 = (unsigned long *)&sta_stground; break;
	case 1:	pTexture01 = (unsigned long *)&sta_stpvr; break;
	case 2:	pTexture01 = (unsigned long *)&sta_stlight; break;
	}
	status = kmLoadTexture(&Texture[i],			/* PKMSURFACEDESC pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))			/* PKMDWORD pTexture */
							);
	Check_Status(status, "kmLoadTexture(ARGB)");
	}
}
/*-------------------------------------------------------------------------------------*/
/*  Function Name   : SetupContext                                                     */
/*  Inputs          : None                                                             */
/*  Outputs         : None                                                             */
/*  Returns         : None                                                             */
/*  Globals Used    :                                                                  */
/*  Description     : Sets default values for the render context.                      */
/*-------------------------------------------------------------------------------------*/
void SetupContext (void)
{
	/*-------------------------------------------------------------------------------- */
	/* Initialize Strip Context */
	/*-------------------------------------------------------------------------------- */
	/* VERTEX TYPE_00 用 KMSTRIPHEAD 構築 */
	memset( &StripContext[0], 0, sizeof(KMSTRIPCONTEXT));/* Crear Context */
	memset( &StripHead[0], 0, sizeof(KMSTRIPHEAD));			/* Crear Strip Head */
	InitStripContext00(&StripContext[0],&StripHead[0]);	/* Initialize context */

	/* VERTEX TYPE_03 用 KMSTRIPHEAD 構築 */
	memset( &StripContext[1], 0, sizeof(KMSTRIPCONTEXT));/* Crear Strip Context */
	memset( &StripHead[1], 0, sizeof(KMSTRIPHEAD));		/* Crear Strip Head */
	InitStripContext03(&StripContext[1],&StripHead[1]);	/* Initialize context */
}

/*-------------------------------------------------------------------------------------*/
/*  Function Name   : InitMeshes                                                       */
/*  Inputs          : None                                                             */
/*  Outputs         : None                                                             */
/*  Returns         : None                                                             */
/*  Globals Used    : Shad, Mesh, TempVert, TempNormals                                */
/*  Description     : Sets initials values for meshes managing                         */
/*-------------------------------------------------------------------------------------*/
void InitMeshes (void)
{
register i,j, k=0;
int mptr = 0x0c400000;

    /* This function is in stained.h and creates an array of structures with 3D data */
    CreateMeshesArray ();

	/* Shad is a 255 values array with information for smooth shading */
    for (i=0; i<120; i++) Shad[k++] = (float)(120-i)/480.0;
    for (i=0; i<100; i++) Shad[k++] = (float) i/100.0;
    for (i=0; i<35;  i++) Shad[k++] = 1.0f;

	for (i=0; i<NUM_MESHES; i++)
	{
#if 0
		TempVert[i] = (PVRVERTEX *)mptr; mptr += Mesh[i].NumVertex*sizeof(PVRVERTEX);
#else
		TempVert[i] = (PVRVERTEX *)(((KMDWORD)syMalloc(Mesh[i].NumVertex*sizeof(PVRVERTEX)) & 0x0FFFFFFFUL) | 0xA0000000);
#endif
	}

	/* Calculate colour array */
    CalculateLight ();
   
	/* Setting UV values for all the meshes */
    for (j=0; j<NUM_MESHES;j++){
		 Shading (j);  /* setting vertices colour just once */
         for (i=0; i<Mesh[j].NumVertex; i++){
            (TempVert[j]+i)->fUOverW    =  (Mesh[j].TexMap==TRUE) ? *(Mesh[j].UV+i*2+0) : 0;
            (TempVert[j]+i)->fVOverW    =  (Mesh[j].TexMap==TRUE) ? *(Mesh[j].UV+i*2+1) : 0; 
       }
    }

}

/*-------------------------------------------------------------------------------------*/
/*  Function Name   : UpdateVertex                                                     */
/*  Inputs          : Num (the mesh in the model)                                      */
/*  Outputs         : None                                                             */
/*  Returns         : None                                                             */
/*  Globals Used    : XAng, YAng                                                       */
/*  Description     : Turns vertices around two axes.                                  */
/*-------------------------------------------------------------------------------------*/
void UpdateVertex (int Num)
{
float Temp[3];
int i, j=0, k=0, l=0;
float x, y, z, CosX, SinX, CosY, SinY, CamZ, CamFocus = 500.0f;

CosX = cos(XAng); SinX = sin(XAng);
CosY = cos(YAng); SinY = sin(YAng);

  
    for (i=0; i<Mesh[Num].NumVertex; i++){
 
         x = *(Mesh[Num].Vertex+k++)-GroupCenter[0];
         y = *(Mesh[Num].Vertex+k++)-GroupCenter[1];
         z = *(Mesh[Num].Vertex+k++)-GroupCenter[2];

         /* Temp is the outcome vertex after the rotation */
         Temp[0]  = x * CosY - z * SinY;
         Temp[2]  = z * CosY + x * SinY;

         z        = Temp[2];
         Temp[1]  = y * CosX - z * SinX;
         Temp[2]  = z * CosX + y * SinX + TPos;

         if (Temp[2] <=0.1){Temp[2] = 0.001f;}

         /* We store the vertex in TempVert */    
         CamZ = 1.0/(Temp[2]);
    	 (TempVert[Num]+i)->fX    =  CamFocus * CamZ * Temp[0] + 320;
         (TempVert[Num]+i)->fY    = -CamFocus * CamZ * Temp[1] + 240;
	     (TempVert[Num]+i)->fInvW =  CamZ;

   }
}

/*-------------------------------------------------------------------------------------*/
/*  Function Name   : Shading                                                          */
/*  Inputs          : Num                                                              */
/*  Outputs         : None                                                             */
/*  Returns         : None                                                             */
/*  Globals Used    : Light1, Mesh, TempVert                                  */
/*  Description     : Shades a mesh.                                                   */
/*-------------------------------------------------------------------------------------*/
void Shading (int Num)
{
float Light1[3] = { 0, 0.5, 1};
float TCo, Dir;
register l=0, i=0, k=0;
float Sh, LTemp[3], x, y, z;
KMUINT32 Col;

    Dir = sqrt (Light1[0]*Light1[0]+Light1[1]*Light1[1]+Light1[2]*Light1[2]);
    LTemp[0] = Light1[0]/Dir;
	LTemp[1] = Light1[1]/Dir; 
	LTemp[2] = Light1[2]/Dir;

    k = Mesh[Num].Material;

    for (i=0; i<Mesh[Num].NumVertex; i++){
      
        x = *(Mesh[Num].Normals+l++);
        y = *(Mesh[Num].Normals+l++);
        z = *(Mesh[Num].Normals+l++);

		/* Sh is a value from 0.0 to 1.0 depending on the angle between a normal */
		/* and the light direction.                                              */
        Sh = fabs( LTemp[0] * x + LTemp[1] * y + LTemp[2] * z + 1.0);

        TCo = Shad[(int)(127.0*Sh)];
        Col = 255*TCo;

        if (Num==GROUND){GroundSh[i] = TCo;}	/* Original values */
        if (Num!=WALL){Col =255;}
       
       (TempVert[Num]+i)->u32Colour  = RGBColour (Col,Col,Col);
    }

}

/*-------------------------------------------------------------------------------------*/
/*  Function Name   : GroundColour                                                     */
/*  Inputs          : None                                                             */
/*  Outputs         : None                                                             */
/*  Returns         : None                                                             */
/*  Globals Used    : GroundSh, TempVert, PosX, PosY                                   */
/*  Description     : Sets colours for lighted ground (colouring vertices).            */
/*-------------------------------------------------------------------------------------*/
void GroundColour (void)
{
KMUINT32 Col[3];
register i, j, cont = 0;
	
	for (j=0; j<31; j++)
	{ 
		for (i=0; i<31; i++)
		{
			/* Sets stained glass colours on the ground.   */
			/* PosX and PosY have been calculated already. */
			if (i > PosX  && i<PosX+10 && j<15+PosY && j> PosY)
			{
				GroundCo[i+j*31][0] = Logo[i-PosX][j-PosY][0];
				GroundCo[i+j*31][1] = Logo[i-PosX][j-PosY][1];
				GroundCo[i+j*31][2] = Logo[i-PosX][j-PosY][2];
			}
			else
			{
				/* Sets white light colour */
				if (i>PosX+18)
				{
					GroundCo[i+j*31][0] = GroundCo[i+j*31][1]= GroundCo[i+j*31][2] = 250.0;
				}
				/* Set shadow colour */
				else
				{
					GroundCo[i+j*31][0] = GroundCo[i+j*31][1]= GroundCo[i+j*31][2] = 50.0;
				}
			}
		}
	}

	/* Calculates average colour for each vertex */
	for (j=0; j<31; j++)
	{ 
		for (i=0; i<31; i++)
		{
			GCo[cont][0] = GroundCo[cont][0];
			GCo[cont][1] = GroundCo[cont][1];
			GCo[cont][2] = GroundCo[cont][2];

			if (j>0 && i>0)
			{
				GCo[cont][0] =(GroundCo[cont][0]+GroundCo[cont-1][0]+GroundCo[cont+1][0]+GroundCo[cont-31][0]+GroundCo[cont+31][0])/5;
				GCo[cont][1] =(GroundCo[cont][1]+GroundCo[cont-1][1]+GroundCo[cont+1][1]+GroundCo[cont-31][1]+GroundCo[cont+31][1])/5;
				GCo[cont][2] =(GroundCo[cont][2]+GroundCo[cont-1][2]+GroundCo[cont+1][2]+GroundCo[cont-31][2]+GroundCo[cont+31][2])/5;
			}
			Col[0] = (int)(GCo[cont][0] * GroundSh[cont]); 
			Col[1] = (int)(GCo[cont][1] * GroundSh[cont]);
			Col[2] = (int)(GCo[cont][2] * GroundSh[cont]);

			/* Sets the colour */
			(TempVert[GROUND]+cont)->u32Colour  = RGBColour (Col[0],Col[1],Col[2]);            
			cont++;
		}
	}
}
/*-------------------------------------------------------------------------------------*/
/*  Function Name   : CalculateLight                                                   */
/*  Inputs          : Nune                                                             */
/*  Outputs         : None                                                             */
/*  Returns         : None                                                             */
/*  Globals Used    : Logo                                                             */
/*  Description     : Creates a 15x10 array with PVR Logo colours.                     */
/*-------------------------------------------------------------------------------------*/
void CalculateLight (void)
{
unsigned long i, j, Pos;
	KMTEX_PIXEL			*pPixel;

	for (j=0; j<15; j++)
	{
		for (i=0; i<10; i++)
		{
			Pos = ((i*128)/10)*128 + ((j*128)/15);  
			/* BuffText[1] is the texture map of the stained glass */
			pPixel = (KMTEX_PIXEL *)&BuffTex[Pos];	/* Set pointer to the first pixel */
			Logo[i][j][0]  = pPixel->red;
			Logo[i][j][1]  = pPixel->green;
			Logo[i][j][2]  = pPixel->blue;
		}
	}
}
/*-------------------------------------------------------------------------------------*/
/*  Function Name   : MoveLamp                                                         */
/*  Inputs          : None                                                             */
/*  Outputs         : None                                                             */
/*  Returns         : None                                                             */
/*  Globals Used    : frame, Mesh, PosX, PosY                                          */
/*  Description     : Up-down movement of the lamp.                                    */
/*-------------------------------------------------------------------------------------*/
void MoveLamp (void)

{
static float TempL[20][3];
register i;
float LX = 0.0f , LY= 0.0f;

    /* Sets LTemp with the 3D vertices values just once. */
	if ( frame == 0)
	{
		for (i=0; i<Mesh[LIGHT].NumVertex; i++)
		{
			TempL[i][0] = *(Mesh[LIGHT].Vertex+i*3+0);
			TempL[i][1] = *(Mesh[LIGHT].Vertex+i*3+1)+15;
			TempL[i][2] = *(Mesh[LIGHT].Vertex+i*3+2)+40;
		}
	}

	/* Calculate light position on the ground and lamp position */
	PosX = (int)(13.0*sin(frame/20.0)+20.0);
	PosY = 7.5;

	LX = 7.5-PosY;
	LY = 15-PosX;

	/* Sets final values for 3D vertices of the lamp. */
	for (i=0; i<Mesh[LIGHT].NumVertex; i++)
	{
		*(Mesh[LIGHT].Vertex+i*3+0)  =  TempL[i][0]+LX;
		*(Mesh[LIGHT].Vertex+i*3+1)  =  TempL[i][1]+LY;
		*(Mesh[LIGHT].Vertex+i*3+2)  =  TempL[i][2];
	}
    
}
/****************************************************************************/
/**	main ********************************************************************/
/****************************************************************************/
void	Kamui_Init(void)
{
	txt_ClearScreen();	/* Clear text screen */
	PRINTOUT(("** STAINED(KAMUI2&Shinobi) **\n"));
	SetupScene ();	/* Initialize */

#if 0
	while(TRUE)
	{
		ReadMaple ();
		NextFrame();	/* Rendering */
		XAng += (xd / SPEED);
		if(XAng > -6.3f) { xd = -xd; XAng = -6.3f; }
		if(XAng < -7.5f) { xd = -xd; XAng = -7.5f; }
		YAng += (yd / SPEED);
		UpVert = 1;
	}
#endif
}

/*----------------------------------------------------------------------*/
/*  Function Name   : ReadMaple                                         */
/*  Inputs          :                                                   */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    : PosZ, BlendSrc, BlendDst, AlphaSource,            */
/*                    BlendModulate                                     */
/*  Description     : Read MAPLE status                                 */
/*----------------------------------------------------------------------*/
void ReadMaple (void)
{
	per = pdGetPeripheral(PDD_PORT_A0);

	/* START button */
	if ( per->press & PDD_DGT_ST )
	{
		xd = 0.0f;
		yd = 0.0f;
	}

	/* UP cross key */
	if ( per->on & PDD_DGT_KU )
	{
		 if(xd > -0.1f) xd -= 0.0002f;
	}
	/* DOWN cross key */
	if ( per->on & PDD_DGT_KD )
	{
		 if(xd <  0.1f) xd += 0.0002f;
	}
	/* Left cross key */
	if ( per->on & PDD_DGT_KL )
	{
		 if(yd <  0.1f) yd += 0.0002f;
	}
	/* Right cross key */
	if ( per->on & PDD_DGT_KR )
	{
		 if(yd > -0.1f) yd -= 0.0002f;
	}

	/* Medama X */
	YAng += (float)(per->x1) / 2000.0f;

	/* Medama Y */
	XAng += (float)(per->y1) / 2000.0f;
	if(XAng > -6.3f){XAng = -6.3f;}
	if(XAng < -7.5f){XAng = -7.5f;}

	/* Slider Right */
	TPos += (float)(per->r) / 100.0f;

	/* Slider Left */
	TPos -= (float)(per->l) / 100.0f;

}

/*--------------------------- End of File --------------------------------*/
