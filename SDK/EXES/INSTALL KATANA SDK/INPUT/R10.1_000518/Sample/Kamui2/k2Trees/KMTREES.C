/********************************************************************************/
/* Name     : VLdemo.c															*/
/* Title    : KAMUI test program "SnowHill" from VL								*/
/* Author   : VideoLogic Carlos Sarria / NEC Software Takeshi Muto				*/
/* Created  : Janualy 1998 by VideoLogic										*/
/* Modified :	February  4. 1998 by Takeshi Muto for KAMUI						*/
/*				February 16. 1999 by Hiroshi Nakayama for KAMUI2				*/
/*				February 17. 1999 by Takeshi Muto for Shinobi					*/
/* Description :																*/
/* Copyright : 1998 by VideoLogic Limited. All rights reserved.					*/
/********************************************************************************/
#if 0
#define		_NOWAIT_VSYNC_			/* 非同期モード使用時は定義する					*/
#define		_VERTEXMACRO_L4_		/* VertexMacroLevel4使用時は定義する			*/
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include	<Shinobi.h>
#include	<sg_sytmr.h>	/* System timer */

#pragma warning (disable : 4244) /* Disables float to double conversion warning */
#pragma warning (disable : 4056)
#define _STRICT_UNION_
#define _CLX2_
#define _CLX_

#include    "kmtrtool.h"
#include	"kmtrees.h"	/* This is the file with 3D data */

#if defined(_VERTEXMACRO_L4_)
#define _KM_USE_VERTEX_MACRO_L4_
#include "kamuix.h"
#endif

/* Textures */
#include	"vltex.h"
/****************************************************************************/
/**	Valuables for KAMUI *****************************************************/
/****************************************************************************/
	KMSTATUS			status;					/* return status of KAMUI API */
	KMVERSIONINFO		VersionInfo;			/* KAMUI Version information */
	KMSURFACEDESC		PrimarySurfaceDesc;		/* Primary frame buffer */
	KMSURFACEDESC		BackSurfaceDesc;		/* Back-buffer frame buffer */
	KMVERTEXBUFFDESC	VertexBufferDesc;		/* Vertex-buffer */
	KMSTRIPCONTEXT		StripContext00[2];		/* Strip context Snow */
	KMSTRIPHEAD			StripHead00[2];			/* Strip head Snow */
												/*	[0] : for TYPE01
													[1] : for TYPE03 */
	KMSTRIPCONTEXT		StripContext01[2];		/* Strip context TTree */
	KMSTRIPHEAD			StripHead01[2];			/* Strip head TTree */
												/*	[0] : for TYPE01
													[1] : for TYPE03 */
	KMSTRIPCONTEXT		StripContext02[2];		/* Strip context Tree */
	KMSTRIPHEAD			StripHead02[2];			/* Strip head Tree */
												/*	[0] : for TYPE01
													[1] : for TYPE03 */
	KMSTRIPCONTEXT		StripContext03[2];		/* Strip context Leaf */
	KMSTRIPHEAD			StripHead03[2];			/* Strip head Leaf */
												/*	[0] : for TYPE01
													[1] : for TYPE03 */
	PKMSURFACEDESC			pFB[2];
	KMSYSTEMCONFIGSTRUCT	SystemConfig;
	PKMDWORD				dwDataPtr;
	KMDWORD				FBarea[24576 + 19456];
								/* FBstruct 4096 Entry (= 4096 * 24 / 4) */
								/* VQstruct 1024 Entry (= 1024 * 76 / 4) */

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
/* Globals */

/*int				Frame = 0; */
/*unsigned			TexSnow, TexTree, TexOpaq, TexLeaf; */
KMSURFACEDESC		TexSnow, TexTree, TexOpaq, TexLeaf;
extern TRANSFORM	T[NUM_MESHES];
static pvr_vector	X_Axle = { 1, 0,0}, Y_Axle = { 0,1, 0}, Z_Axle = { 0,0, 1};
unsigned char		BColor[3];

int					 menu = 0;
#define	MENU_MAX_F	(6.0f)
int					transmode = 2;	/* 0=Opaq. 1=Trans. 2=PunchThrough */

float				Ang, PosZ = 0.0f, PosX=0.0f, High=-100.0f;
float				DAng = 0.01f;
int					nTrees = 150;

int					Translucent = TRUE, IsBark=FALSE, Stopped=FALSE, RandTree = TRUE, Type = 0;
int					TCont[1000];

float				CosA, SinA, TrX, TrY, TrZ, MovX, MovZ;

/* Info Structure */
INFO Info =
{
	FALSE,		/* OpaqMap       */
	TRUE,		/* Textured      */
	TRUE,		/* Gouraud       */
	FALSE,      /* GlobalTrans   */
	FALSE,      /* VertexAlpha   */
	FALSE,		/* TableFog      */
	FALSE,      /* VertexFog     */
	TRUE,       /* Bilinear      */
	FALSE,      /* Highlight     */
};

/* Prototypes */

static void SetTextures			(void);
void NextFrame			(void);
static void DisplayInformation	(int menu);
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
	BackVertexContext.ColorType				= KM_FLOATINGCOLOR;
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
	BackVertexContext.FogMode				= KM_NOFOG;			/* 11 is reserved */
	BackVertexContext.bUseSpecular			= FALSE;
	BackVertexContext.bUseAlpha				= FALSE;
	BackVertexContext.ClampUV				= KM_NOCLAMP;
	BackVertexContext.FilterMode			= KM_POINT_SAMPLE;
	BackVertexContext.bSuperSample			= FALSE;
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
	BV[0].fX				=   0.0f;
	BV[0].fY				= 479.0f;
#if defined(_STRICT_UNION_)
	BV[0].u.fZ				=  0.0001f;
#else
	BV[0].fZ				=  0.0001f;
#endif
	BV[0].fBaseAlpha		=   0.0f;
	BV[0].fBaseRed			=   0.55f;
	BV[0].fBaseGreen		=   0.87f;
	BV[0].fBaseBlue			=   0.96f;

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
	BV[1].fBaseRed			=   0.0f;
	BV[1].fBaseGreen		=   0.15f;
	BV[1].fBaseBlue			=   0.73f;

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
	BV[2].fBaseRed			=   0.55f;
	BV[2].fBaseGreen		=   0.87f;
	BV[2].fBaseBlue			=   0.96f;

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
	PPVRVERTEX	pVert;
	KMVERTEX_01	Ver01;				/* for NO-TEXTURE-GOURAUD */
	KMVERTEX_03	Ver03;				/* for TEXTURE-GOURAUD */

#if 0
	if(bTexture == TRUE)
	{
		kmStartStrip( &BufferDesc , &StripHead[1] );
									/* VERTEX TYPE_03用頂点登録開始 */
	}
	else
	{
		kmStartStrip( &BufferDesc , &StripHead[0] );
									/* VERTEX TYPE_00用頂点登録開始 */
	}
#else
	kmStartStrip( &BufferDesc , pStripHead );
#endif

#if defined(_VERTEXMACRO_L4_)
	kmxxGetCurrentPtr(&BufferDesc);
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
		else
		{	/* if(bTexture == TRUE) : NO-TEXTURE */
#if defined(_VERTEXMACRO_L4_)

			pVert = &pVertices[pFaces[i][0]];
			kmxxSetVertex_1(KM_VERTEXPARAM_NORMAL,
							pVert->fX,
							pVert->fY,
							pVert->fInvW,
							GetALPHA(pVert->u32Colour),
							GetRED  (pVert->u32Colour),
							GetGREEN(pVert->u32Colour),
							GetBLUE (pVert->u32Colour)
							);

			pVert = &pVertices[pFaces[i][1]];
			kmxxSetVertex_1(KM_VERTEXPARAM_NORMAL,
							pVert->fX,
							pVert->fY,
							pVert->fInvW,
							GetALPHA(pVert->u32Colour),
							GetRED  (pVert->u32Colour),
							GetGREEN(pVert->u32Colour),
							GetBLUE (pVert->u32Colour)
							);

			pVert = &pVertices[pFaces[i][2]];
			kmxxSetVertex_1(KM_VERTEXPARAM_ENDOFSTRIP,
							pVert->fX,
							pVert->fY,
							pVert->fInvW,
							GetALPHA(pVert->u32Colour),
							GetRED  (pVert->u32Colour),
							GetGREEN(pVert->u32Colour),
							GetBLUE (pVert->u32Colour)
							);
#else
			Ver01.ParamControlWord	= KM_VERTEXPARAM_NORMAL;
			Ver01.fX				= pVertices[pFaces[i][0]].fX;
			Ver01.fY				= pVertices[pFaces[i][0]].fY;
#if defined(_STRICT_UNION_)
			Ver01.u.fZ				= pVertices[pFaces[i][0]].fInvW;
#else
			Ver01.fZ				= pVertices[pFaces[i][0]].fInvW;
#endif
			Ver01.fBaseAlpha		= GetALPHA(pVertices[pFaces[i][0]].u32Colour);
			Ver01.fBaseRed			= GetRED  (pVertices[pFaces[i][0]].u32Colour);
			Ver01.fBaseGreen		= GetGREEN(pVertices[pFaces[i][0]].u32Colour);
			Ver01.fBaseBlue			= GetBLUE (pVertices[pFaces[i][0]].u32Colour);
			status = kmSetVertex(&BufferDesc,&Ver01,KM_VERTEXTYPE_01,sizeof(KMVERTEX_01) );
			Check_Status(status, "kmSetVertex");

			Ver01.ParamControlWord	= KM_VERTEXPARAM_NORMAL;
			Ver01.fX				= pVertices[pFaces[i][1]].fX;
			Ver01.fY				= pVertices[pFaces[i][1]].fY;
#if defined(_STRICT_UNION_)
			Ver01.u.fZ				= pVertices[pFaces[i][1]].fInvW;
#else
			Ver01.fZ				= pVertices[pFaces[i][1]].fInvW;
#endif
			Ver01.fBaseAlpha		= GetALPHA(pVertices[pFaces[i][1]].u32Colour);
			Ver01.fBaseRed			= GetRED  (pVertices[pFaces[i][1]].u32Colour);
			Ver01.fBaseGreen		= GetGREEN(pVertices[pFaces[i][1]].u32Colour);
			Ver01.fBaseBlue			= GetBLUE (pVertices[pFaces[i][1]].u32Colour);
			status = kmSetVertex(&BufferDesc,&Ver01,KM_VERTEXTYPE_01,sizeof(KMVERTEX_01) );
			Check_Status(status, "kmSetVertex");

			Ver01.ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;
			Ver01.fX				= pVertices[pFaces[i][2]].fX;
			Ver01.fY				= pVertices[pFaces[i][2]].fY;
#if defined(_STRICT_UNION_)
			Ver01.u.fZ				= pVertices[pFaces[i][2]].fInvW;
#else
			Ver01.fZ				= pVertices[pFaces[i][2]].fInvW;
#endif
			Ver01.fBaseAlpha		= GetALPHA(pVertices[pFaces[i][2]].u32Colour);
			Ver01.fBaseRed			= GetRED  (pVertices[pFaces[i][2]].u32Colour);
			Ver01.fBaseGreen		= GetGREEN(pVertices[pFaces[i][2]].u32Colour);
			Ver01.fBaseBlue			= GetBLUE (pVertices[pFaces[i][2]].u32Colour);
			status = kmSetVertex(&BufferDesc,&Ver01,KM_VERTEXTYPE_01,sizeof(KMVERTEX_01) );
			Check_Status(status, "kmSetVertex");
#endif
		} /* end of if(bTexture == TRUE) */
	}
#if defined(_VERTEXMACRO_L4_)
	kmxxReleaseCurrentPtr(&BufferDesc);
#endif
	kmEndStrip(&BufferDesc);		/* 頂点登録終了 */
}

/*-------------------------------------------------------------------------------------*/
/*                                       MAIN                                          */
/*-------------------------------------------------------------------------------------*/
int Kamui_Init (void)
{
int			Control = 0;
/*int		Device; */
int			Val = 0, i;

	txt_ClearScreen();	/* Clear text screen */

#if defined(_VERTEXMACRO_L4_)
	PRINTOUT(("** KMTREES(KAMUI2&Shinobi) Use:Level4 Macro **\n"));
#else
	PRINTOUT(("** KMTREES(KAMUI2&Shinobi) **\n"));
#endif

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
	dwDataPtr = (PKMDWORD)0xAC880000;
#else
	dwDataPtr = (PKMDWORD)(((KMDWORD)syMalloc(0xD00000) & 0x0FFFFFFFUL) | 0xA0000000);
#endif

	SystemConfig.dwSize	=	sizeof(KMSYSTEMCONFIGSTRUCT);
#if defined(_NOWAIT_VSYNC_)
	SystemConfig.flags					=	KM_CONFIGFLAG_ENABLE_CLEAR_FRAMEBUFFER | KM_CONFIGFLAG_NOWAITVSYNC;
#else
	SystemConfig.flags					=	KM_CONFIGFLAG_ENABLE_CLEAR_FRAMEBUFFER;
#endif

	/* for Frame buffer */
	SystemConfig.ppSurfaceDescArray		=	pFB;		/* Array of SurfaceDesc	pointer     */
	SystemConfig.fb.nNumOfFrameBuffer	=	2;			/* Number Of Frame Buffer			*/
	/* for Texture Memory */
	SystemConfig.nTextureMemorySize		=	0x100000;	/* Texture 4MB */
	SystemConfig.nNumOfTextureStruct	=	4096;		/* テクスチャ管理構造体の数 */
	SystemConfig.nNumOfSmallVQStruct	=	1024;		/* VQテクスチャ管理構造体の数 */
	SystemConfig.pTextureWork			=	&FBarea[0];	/* テクスチャ管理構造体領域 */
	/* for Vertex buffer */
	SystemConfig.pBufferDesc			=	&VertexBufferDesc;	/* pointer to VERTEXBUFFDESC 		*/
	SystemConfig.nNumOfVertexBank		=	2;
	SystemConfig.pVertexBuffer			=	dwDataPtr;	/* pointer to Vertex buffer 		*/
	SystemConfig.nVertexBufferSize		=(262144*6*4+131072*4)*2;
														/* size of Vertex buffer : 1MB * 6 +512kb */
	SystemConfig.nPassDepth				=	1;
	SystemConfig.Pass[0].dwRegionArrayFlag = KM_PASSINFO_AUTOSORT;
	SystemConfig.Pass[0].fBufferSize[0]	=	40.0f;		/* Opaque polygon buffer size        : 35% */
	SystemConfig.Pass[0].fBufferSize[1]	=	 0.0f;		/* Opaque modifier buffer size       :  0% */
	SystemConfig.Pass[0].fBufferSize[2]	=	30.0f;		/* Trans polygon buffer size         : 30% */
	SystemConfig.Pass[0].fBufferSize[3]	=	 0.0f;		/* Trans modifier buffer size        :  0% */
	SystemConfig.Pass[0].fBufferSize[4]	=	30.0f;		/* Punchthrough polygon buffer size  : 35% */

	status = kmSetSystemConfiguration( &SystemConfig );
	Check_Status(status, "kmSetSystemConfiguration");

	/*-----------------------------------------------------------------------------------*/
	/* Initialize DisplayString routine */
	txt_InitDisplayString();

	/*----------------------------------------------------------------------------------- */
	/* some initializes */
	SetTextures ();
	InitContext (StripContext00,StripHead00,Info,0,&TexSnow);
	InitContext (StripContext01,StripHead01,Info,transmode,&TexTree);
	InitContext (StripContext02,StripHead02,Info,0,&TexOpaq);
	InitContext (StripContext03,StripHead03,Info,0,&TexLeaf);

	InitBackGround();		/* Setup background plane */
	DisplayInformation (menu);


	/*----------------------------------------------------------------------------------- */
	/* Set Culling Register */
/*	status = kmSetCullingRegister(1.0f); */
/*	Check_Status(status, "kmSetCullingRegister"); */

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

	/* This function creates an array of structures with 3D data */
	CreateMeshesArray ();
	InitMeshes (NUM_MESHES, (CASTMESHES *) Mesh);

	for(i=0; i<1000; i++) TCont[i] = rand()%8 + 1;

#if 0
   	while (TRUE)
	{
	
		ReadMaple ();
		NextFrame ();
	}

Finish:

    FreeMeshes (NUM_MESHES);

	/*----------------------------------------------------------------------------------- */
	/* Free vertex buffer */
	status = kmDiscardVertexBuffer(&VertexBufferDesc);
	Check_Status(status, "kmDiscardVertexBuffer");

	/*----------------------------------------------------------------------------------- */
	/* End display */
	status = kmStopDisplayFrameBuffer();
	Check_Status(status, "kmStopDisplayFrameBuffer");
#endif

	return 0;
}

/*-------------------------------------------------------------------------------------*/
void SetTextures (void)
{

	PKMDWORD			pTexture01;				/* Pointer to texture */
	KMTEXTURETYPE		nTextureType;			/* texture type definition */

	/*----------------------------------------------------------------------------------- */
	/* Create texture surface */
	nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&TexSnow,				/* OUT	PKMSURFACEDESC	pSurfaceDesc */
		256,					/*	IN	KMINT32			nWidth  */
		256,					/*	IN	KMINT32			nHeight  */
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType */
	);
	Check_Status(status, "kmCreateTextureSurface(RGB)");
	/*----------------------------------------------------------------------------------- */
	/* Create texture surface */
	nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_ARGB1555;	/* Set texture type */
	status = kmCreateTextureSurface(
		&TexTree,				/* OUT	PKMSURFACEDESC	pSurfaceDesc */
		256,					/*	IN	KMINT32			nWidth  */
		256,					/*	IN	KMINT32			nHeight  */
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType */
	);
	Check_Status(status, "kmCreateTextureSurface(RGB)");
	/*----------------------------------------------------------------------------------- */
	/* Create texture surface */
	nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&TexOpaq,				/* OUT	PKMSURFACEDESC	pSurfaceDesc */
		256,					/*	IN	KMINT32			nWidth  */
		256,					/*	IN	KMINT32			nHeight  */
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType */
	);
	Check_Status(status, "kmCreateTextureSurface(RGB)");
	/*----------------------------------------------------------------------------------- */
	/* Create texture surface */
	nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&TexLeaf,				/* OUT	PKMSURFACEDESC	pSurfaceDesc */
		256,					/*	IN	KMINT32			nWidth  */
		256,					/*	IN	KMINT32			nHeight  */
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType */
	);
	Check_Status(status, "kmCreateTextureSurface(RGB)");
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
#if 0
	pTexture01 =  LoadTextureFile("snow.pvr");	/* Load KAMUI texture */
#endif
	pTexture01 = (unsigned long *)&tr2_snow;
	status = kmLoadTexture(&TexSnow,			/* PKMSURFACEDESC pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))			/* PKMDWORD pTexture */
							);
	Check_Status(status, "kmLoadTexture(ARGB)");
/*	free(pTexture01);	*/
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
#if 0
	pTexture01 =  LoadTextureFile("ttree.pvr");	/* Load KAMUI texture */
#endif
	pTexture01 = (unsigned long *)&tr2_ttree;
	status = kmLoadTexture(&TexTree,			/* PKMSURFACEDESC pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))			/* PKMDWORD pTexture */
							);
	Check_Status(status, "kmLoadTexture(ARGB)");
/*	free(pTexture01);	*/
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
#if 0
	pTexture01 =  LoadTextureFile("tree.pvr");	/* Load KAMUI texture */
#endif
	pTexture01 = (unsigned long *)&tr2_tree;
	status = kmLoadTexture(&TexOpaq,			/* PKMSURFACEDESC pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))			/* PKMDWORD pTexture */
							);
	Check_Status(status, "kmLoadTexture(ARGB)");
/*	free(pTexture01);	*/
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
#if 0
	pTexture01 =  LoadTextureFile("leaf.pvr");	/* Load KAMUI texture */
#endif
	pTexture01 = (unsigned long *)&tr2_leaf;
	status = kmLoadTexture(&TexLeaf,			/* PKMSURFACEDESC pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))			/* PKMDWORD pTexture */
							);
	Check_Status(status, "kmLoadTexture(ARGB)");
/*	free(pTexture01);	*/

}
/*-------------------------------------------------------------------------------------*/
void NextFrame (void)
{

static			Movement = 0;
static float	Sun = 0, HPos ;
register		i;
/*register		j, k; */
float			Xpos[] = { -50.0f,  -50.0f,  50.0f,   50.0f,-15.0f,  -15.0f,  15.0f,   15.0f};
float			Ypos[] = { -50.0f,  50.0f,   -50.0f,  50.0f ,-50.0f,  50.0f,   -50.0f,  50.0f};
/*int				TransTemp; */
int				Cont = 1000;

	if (!Stopped) Ang += DAng;

	CosA = cos (Ang);
	SinA = sin (Ang);

	InitScene ();

	if (Translucent && !Info.Textured) Info.VertexAlpha =  TRUE;

	for (i = 0; i < nTrees; i++) {
		Cont += TCont[i];
		TrX = Vertex_Ground[Cont][0];
		TrY = High + Vertex_Ground[Cont][1] - 1.0f;
		TrZ = Vertex_Ground[Cont][2];

		MovX = PosX;
		MovZ = PosZ;

		/*	PVRContext.bCullBackfacing      = 0; */
		SetVertices ( 1, (!Translucent)? StripHead02:StripHead01, Info, FX_NONE );
		if (Type==1 || Type==2) {
			SetVertices ( 3, (!Translucent)? StripHead02:StripHead01, Info, FX_NONE );
		}
		if (Type==2) {
			SetVertices ( 2, StripHead03, Info, FX_NONE );
		}
	}

#if 0
  Info.VertexAlpha =  FALSE;
  SetContext (Info);
#endif

	/* GROUND */
	TrX = 0.0f;
	TrY = High;
	TrZ = 0.0f;
	MovX = PosX ;
	MovZ = PosZ;
	/*	PVRContext.bCullBackfacing      = 0; */
	SetVertices (0, StripHead00, Info, FX_NONE );

	/*  Timer(DISPLAY_TIME); */

	EndScene();

/*  Frame++; */
}

/*-------------------------------------------------------------------------------------*/

void DisplayInformation (int menu)
{
char *treeT[] = { "3 TRANS","6 TRANS","6 TRANS + 6 OPAQ" };
char *transT[] = { "Opaque","Translucent","Punchthrough" };
char *Flag[2]   = { "FALSE", "TRUE" };

	txt_SetCursor(0,13);
	if(menu == 0)	txt_SetColor( 1.0f, 0.5f, 0.0f );
	else			txt_SetColor( 1.0f, 1.0f, 1.0f );
	PRINTOUT(( " Bilinear      %s\n",   Flag[Info.Bilinear]));
	if(menu == 1)	txt_SetColor( 1.0f, 0.5f, 0.0f );
	else			txt_SetColor( 1.0f, 1.0f, 1.0f );
	PRINTOUT(( " Gouraud       %s\n",   Flag[Info.Gouraud]));	
	if(menu == 2)	txt_SetColor( 1.0f, 0.5f, 0.0f );
	else			txt_SetColor( 1.0f, 1.0f, 1.0f );
	PRINTOUT(( " Textured      %s\n",   Flag[Info.Textured]));	
	if(menu == 3)	txt_SetColor( 1.0f, 0.5f, 0.0f );
	else			txt_SetColor( 1.0f, 1.0f, 1.0f );
	PRINTOUT(( " Tree type     %s\n",   treeT[Type]));		
	if(menu == 4)	txt_SetColor( 1.0f, 0.5f, 0.0f );
	else			txt_SetColor( 1.0f, 1.0f, 1.0f );
	PRINTOUT(( " Trans. mode   %s\n",   transT[transmode]));
	if(menu == 5)	txt_SetColor( 1.0f, 0.5f, 0.0f );
	else			txt_SetColor( 1.0f, 1.0f, 1.0f );
	PRINTOUT(( " Random        %s\n", Flag[RandTree]));
	if(menu == 6)	txt_SetColor( 1.0f, 0.5f, 0.0f );
	else			txt_SetColor( 1.0f, 1.0f, 1.0f );
	PRINTOUT(( " Num. of trees %d\n", nTrees));
	txt_SetColor( 1.0f, 1.0f, 1.0f );
/*	PRINTOUT(( " F9 : Hardware Time (F10 to normal)\n\n")); */

/*	Timer (RESET_TIME); */
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
	static	float	menu2 = 0.0f;
	int			i;

	per = pdGetPeripheral(PDD_PORT_A0);

	/* START button */
	if ( per->press & PDD_DGT_ST )
	{
		DAng	=    0.0f;
		nTrees	=  150.0f;
		PosZ	=    0.0f;
		PosX	=    0.0f;
		High	= -100.0f;
		DisplayInformation (menu);
	}

	/* UP cross key */
	if ( per->on & PDD_DGT_KU )
	{
		menu2 -= 0.2f;
		if(menu2 < 0.0f) menu2 = MENU_MAX_F + 0.9f;
		menu = (int)menu2;
		DisplayInformation (menu);
	}
	/* DOWN cross key */
	if ( per->on & PDD_DGT_KD )
	{
		menu2 += 0.2f;
		if(menu2 > (MENU_MAX_F + 0.9f)) menu2 = 0.0f;
		menu = (int)menu2;
		DisplayInformation (menu);
	}
	/* Left cross key */
	if ( per->on & PDD_DGT_KL )
	{
		DAng += 0.001;
	}
	/* Right cross key */
	if ( per->on & PDD_DGT_KR )
	{
		DAng -= 0.001;
	}

	/* Medama X */
	PosX -= (float)(per->x1) / 100.0f;

	/* Medama Y */
	PosZ += (float)(per->y1) / 100.0f;

	/* Slider Right */
	High += (float)(per->r) / 100.0f;

	/* Slider Left */
	High -= (float)(per->l) / 100.0f;

	/* A button */
	if ( per->press & PDD_DGT_TA )
	{
		switch(menu) {
		case 0:
			Info.Bilinear = (Info.Bilinear) ? FALSE:TRUE;
			SetContext (StripHead00, Info, 0, &TexSnow);
			SetContext (StripHead01, Info, transmode, &TexTree);
			SetContext (StripHead02, Info, 0, &TexOpaq);
			SetContext (StripHead03, Info, 0, &TexLeaf);
			break;
		case 1:
			Info.Gouraud = (Info.Gouraud) ? FALSE:TRUE;
			SetContext (StripHead00, Info, 0, &TexSnow);
			SetContext (StripHead01, Info, transmode, &TexTree);
			SetContext (StripHead02, Info, 0, &TexOpaq);
			SetContext (StripHead03, Info, 0, &TexLeaf);
			break;
		case 2:
			Info.Textured = (Info.Textured) ? FALSE:TRUE;
#if 0
			SetContext (StripHead00, Info, 0, &TexSnow);
			SetContext (StripHead01, Info, transmode, &TexTree);
			SetContext (StripHead02, Info, 0, &TexOpaq);
			SetContext (StripHead03, Info, 0, &TexLeaf);
#endif
			break;
		case 3:
			Type++; if (Type == 3) Type = 0;
			break;
		case 4:
			transmode++; if(transmode == 3) transmode = 0;
			if(transmode > 0) {
				Translucent = TRUE;
				SetContext (StripHead01, Info, transmode, &TexTree);
			}
			else {
				Translucent = FALSE;
			}
#if 0
			if (Translucent && !Info.Textured) Info.VertexAlpha =  TRUE;
			else  Info.VertexAlpha =  FALSE;
#endif
			DisplayInformation (menu);
			break;
		case 5:
			RandTree = (RandTree) ? FALSE:TRUE;
			if(RandTree) 	for(i=0; i<1000; i++) TCont[i] = (rand()%8) + 1;
			else 	        for(i=0; i<1000; i++) TCont[i] = 1;
			break;
		case 6:
			if(nTrees < 1000) nTrees+=10;
			break;
		default:
			break;
		}
		DisplayInformation (menu);
	}

	/* B button */
	if ( per->press & PDD_DGT_TB )
	{
		switch(menu) {
		case 6:
			 if(nTrees > 10) nTrees-=10;
			break;
		default:
			break;
		}
		DisplayInformation (menu);
	}

	/* X button */
	if ( per->press & PDD_DGT_TX )
	{
		DAng = 0.0f;
	}
}

/*--------------------------- End of File --------------------------------*/

