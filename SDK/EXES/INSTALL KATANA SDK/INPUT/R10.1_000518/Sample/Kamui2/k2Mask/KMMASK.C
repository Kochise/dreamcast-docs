/********************************************************************************
 * Name     : KMMASK															*
 * Title    : KAMUI test program "MASK" from VL									*
 * Author   : VideoLogic Carlos Sarria / NEC Software Takeshi Muto				*
 * Created  : July 1997 by VideoLogic											*
 * Modified : Novenber  4. 1997 by Takeshi Muto for KAMUI						*
 *			  January  28. 1999 by T.Kamei for KAMUI2							*
 *            February 16. 1999 by Takeshi Muto for Shinobi						*
 * Description :																*
 * Copyright : 1997 by VideoLogic Limited. All rights reserved.					*
 ********************************************************************************/
#if 0
#define		_NOWAIT_VSYNC_			/* 非同期モード使用時は定義する					*/
#define		_VERTEXMACRO_L4_		/* VertexMacroLevel4使用時は定義する			*/
#endif

#define		_DISPLAY_STRING_						/* if defined then display strings on screen	*/
#define		_DISP_PERFORMANCE_						/* Display performance							*/

#define		SPEED			(1.0f)					/* pet move speed ( 1 to n )	*/

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

#include	"kamui2.h"				/* for Kamui Call									*/
#include	"kmutil.h"				/* for Kamui utility Call							*/
#include	"dispstr.h"				/* for DisplayString								*/
#include	"kmmask.h"				/* This is the file with 3D data					*/
#include	"vltex.h"				/* for vl sample texture							*/

#if defined(_VERTEXMACRO_L4_)
#define _KM_USE_VERTEX_MACRO_L4_
#include "kamuix.h"
#endif

#pragma warning (disable : 4244)  /* Float to Double Conversion Warning */

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
	/* 1/w for the perspective projection (should be set to 1.0/fZ; fZ is */
	/* actually ignored): */
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
	KMSURFACEDESC		Texture[10];			/* texture surface				*/
	KMVERTEXBUFFDESC	VertexBufferDesc;		/* Vertex-buffer				*/

#if 0
	KMSTRIPCONTEXT		StripContext01;
	KMSTRIPHEAD			StripHead01_RE;			/* mReflect	*/
	KMSTRIPHEAD			StripHead01_FR1;		/* mFront01	*/
	KMSTRIPHEAD			StripHead01_FR2;		/* mFront02	*/
	KMSTRIPHEAD			StripHead01_FR3;		/* mFront03	*/
	KMSTRIPHEAD			StripHead01_GR;			/* mGround	*/
#endif
	KMSTRIPCONTEXT		StripContext03;
	KMSTRIPHEAD			StripHead03_RE;			/* mReflect	*/
	KMSTRIPHEAD			StripHead03_FR1;		/* mFront01	*/
	KMSTRIPHEAD			StripHead03_FR2;		/* mFront02	*/
	KMSTRIPHEAD			StripHead03_FR3;		/* mFront03	*/
	KMSTRIPHEAD			StripHead03_GR;			/* mGround	*/

	PKMSURFACEDESC			pFB[2];
	KMDWORD					FBarea[24576 + 19456];
								/* FBstruct 4096 Entry (= 4096 * 24 / 4) *
								 * VQstruct 1024 Entry (= 1024 * 76 / 4) */
	KMSYSTEMCONFIGSTRUCT	SystemConfig;
	PKMDWORD				dwDataPtr;

	PKMDWORD			BuffTex[2];				/* Pointer to texture						*/

	unsigned char		TextureBuffer1[65552];	/* buffer for save original reflection map	*/
	unsigned char		TextureBuffer2[65552];	/* buffer for generate twiddled map			*/

	/* 性能測定用変数 */
	int			frame;				/* 画面フレーム		*/
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

#define		PI	(3.1416f)

int			Init = TRUE, frame = 0;
int			TempTex;
int			TPos = 800, NumP = 10, LH= 128, DLH = 1;
float		XAng = 0.0f, YAng =0.0f, XAng1 = 0.0f, YAng1 =0.005f,  Shad[255];
char		MCol[3][20*30*4];

PVRVERTEX  *TempVert[NUM_MESHES];
float      *TempNormals[NUM_MESHES];

void InitMeshes     	(void);
void SetupContext		(PKMSTRIPHEAD pStripHead, PKMSURFACEDESC pTexture, int bTrans);
void SetupTextures    	(void);
void DrawAll          	(void);
void Shading          	(int);
void UpdateVertex     	(int Num);
void UpdateReflection 	(int Num);
void MoveBalls        	(void);
void PutBallsOn       	(void);
void ReadMaple 			(void);

int	count = 0;

/* Peripheral */
PDS_PERIPHERAL *per;

/****************************************************************************
 *	Check KAMUI function status
 ****************************************************************************/
void	Check_Status(KMSTATUS status, char *func)
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
 *	kmtri_triangles  by T.Hirata
 ***************************************************************************/
void 
kmtri_triangles ( PKMVERTEXBUFFDESC		pBufferDesc,
				  PKMSTRIPHEAD			pStripHead,
				  int  					nNumFaces,
				  int  					pFaces[][3],
				  PPVRVERTEX  			pVertices,
				  int					bTexture)
{
	KMSTATUS		status;
	int				i;
	KMVERTEX_01		Ver01;				/* for NO-TEXTURE-GOURAUD	*/
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
			kmxxSetVertex_1(	KM_VERTEXPARAM_NORMAL,
								pVertices[pFaces[i][0]].fX,
								pVertices[pFaces[i][0]].fY,
								pVertices[pFaces[i][0]].fInvW,
								GetALPHA (pVertices[pFaces[i][0]].u32Colour),
								GetRED	 (pVertices[pFaces[i][0]].u32Colour),
								GetGREEN (pVertices[pFaces[i][0]].u32Colour),
								GetBLUE	 (pVertices[pFaces[i][0]].u32Colour)
							);

			kmxxSetVertex_1(	KM_VERTEXPARAM_NORMAL,
								pVertices[pFaces[i][1]].fX,
								pVertices[pFaces[i][1]].fY,
								pVertices[pFaces[i][1]].fInvW,
								GetALPHA (pVertices[pFaces[i][0]].u32Colour),
								GetRED	 (pVertices[pFaces[i][0]].u32Colour),
								GetGREEN (pVertices[pFaces[i][0]].u32Colour),
								GetBLUE	 (pVertices[pFaces[i][0]].u32Colour)
							);

			kmxxSetVertex_1(	KM_VERTEXPARAM_ENDOFSTRIP,
								pVertices[pFaces[i][2]].fX,
								pVertices[pFaces[i][2]].fY,
								pVertices[pFaces[i][2]].fInvW,
								GetALPHA (pVertices[pFaces[i][0]].u32Colour),
								GetRED	 (pVertices[pFaces[i][0]].u32Colour),
								GetGREEN (pVertices[pFaces[i][0]].u32Colour),
								GetBLUE	 (pVertices[pFaces[i][0]].u32Colour)
							);
#else
			Ver01.ParamControlWord	= KM_VERTEXPARAM_NORMAL;
			Ver01.fX				= pVertices[pFaces[i][0]].fX;
			Ver01.fY				= pVertices[pFaces[i][0]].fY;
			Ver01.u.fZ				= pVertices[pFaces[i][0]].fInvW;
			Ver01.fBaseAlpha		= GetALPHA(pVertices[pFaces[i][0]].u32Colour);
			Ver01.fBaseRed			= GetRED  (pVertices[pFaces[i][0]].u32Colour);
			Ver01.fBaseGreen		= GetGREEN(pVertices[pFaces[i][0]].u32Colour);
			Ver01.fBaseBlue			= GetBLUE (pVertices[pFaces[i][0]].u32Colour);
			status = kmSetVertex(pBufferDesc,&Ver01,KM_VERTEXTYPE_01,sizeof(KMVERTEX_01) );
			Check_Status(status, "kmSetVertex");

			Ver01.ParamControlWord	= KM_VERTEXPARAM_NORMAL;
			Ver01.fX				= pVertices[pFaces[i][1]].fX;
			Ver01.fY				= pVertices[pFaces[i][1]].fY;
			Ver01.u.fZ				= pVertices[pFaces[i][1]].fInvW;
			Ver01.fBaseAlpha		= GetALPHA(pVertices[pFaces[i][1]].u32Colour);
			Ver01.fBaseRed			= GetRED  (pVertices[pFaces[i][1]].u32Colour);
			Ver01.fBaseGreen		= GetGREEN(pVertices[pFaces[i][1]].u32Colour);
			Ver01.fBaseBlue			= GetBLUE (pVertices[pFaces[i][1]].u32Colour);
			status = kmSetVertex(pBufferDesc,&Ver01,KM_VERTEXTYPE_01,sizeof(KMVERTEX_01) );
			Check_Status(status, "kmSetVertex");

			Ver01.ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;
			Ver01.fX				= pVertices[pFaces[i][2]].fX;
			Ver01.fY				= pVertices[pFaces[i][2]].fY;
			Ver01.u.fZ				= pVertices[pFaces[i][2]].fInvW;
			Ver01.fBaseAlpha		= GetALPHA(pVertices[pFaces[i][2]].u32Colour);
			Ver01.fBaseRed			= GetRED  (pVertices[pFaces[i][2]].u32Colour);
			Ver01.fBaseGreen		= GetGREEN(pVertices[pFaces[i][2]].u32Colour);
			Ver01.fBaseBlue			= GetBLUE (pVertices[pFaces[i][2]].u32Colour);
			status = kmSetVertex(pBufferDesc,&Ver01,KM_VERTEXTYPE_01,sizeof(KMVERTEX_01) );
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
 *	VertexType01用KMSTRIPHEADの構築
 ***************************************/
void	InitStripContext01(
								PKMSTRIPCONTEXT pStripContext,
								PKMSTRIPHEAD	pStripHead
)
{
	pStripContext->nSize					 						= sizeof(KMSTRIPCONTEXT);
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

	kmGenerateStripHead01( pStripHead,pStripContext );
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
	pStripContext->nSize						 						= sizeof(KMSTRIPCONTEXT);
	pStripContext->StripControl.nListType		 						= KM_OPAQUE_POLYGON;
	pStripContext->StripControl.nUserClipMode	 						= KM_USERCLIP_DISABLE;
	pStripContext->StripControl.nShadowMode		 						= KM_NORMAL_POLYGON;
	pStripContext->StripControl.bOffset									= KM_FALSE;
	pStripContext->StripControl.bGouraud		 						= KM_TRUE;
	pStripContext->ObjectControl.nDepthCompare			 				= KM_GREATER;
	pStripContext->ObjectControl.nCullingMode			 				= KM_CULLSMALL;
	pStripContext->ObjectControl.bZWriteDisable							= KM_FALSE;
	pStripContext->ObjectControl.bDCalcControl			 				= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nSRCBlendingMode		= KM_ONE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nDSTBlendingMode		= KM_ZERO;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bSRCSelect				= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bDSTSelect				= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFogMode				= KM_NOFOG;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bColorClamp			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bUseAlpha				= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bIgnoreTextureAlpha		= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFlipUV				= KM_NOFLIP;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nClampUV				= KM_NOCLAMP;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFilterMode			= KM_BILINEAR;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bSuperSampleMode		= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].dwMipmapAdjust			= KM_MIPMAP_D_ADJUST_1_00;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nTextureShadingMode	= KM_MODULATE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].pTextureSurfaceDesc	= pTextureDesc;

	kmGenerateStripHead03( pStripHead,pStripContext );
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
	InitStripContext01		(&StripContextBG01,&StripHeadBG01);
	kmChangeStripCullingMode(&StripHeadBG01,KM_NOCULLING);

	/*----------------------------------------------------------------------------------- */
	/* set VERTEX DATA */

	/* Vertex #0 */
	BV01[0].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
	BV01[0].fX					=   0.0f;
	BV01[0].fY					= 479.0f;
	BV01[0].u.fZ				=   0.0001f;
	BV01[0].fBaseAlpha			=   1.0f;
	BV01[0].fBaseRed			=   0.5f;
	BV01[0].fBaseGreen			=   0.5f;
	BV01[0].fBaseBlue			=   0.0f;

	/* Vertex #1 */
	BV01[1].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
	BV01[1].fX					= 320.0f;
	BV01[1].fY					=   0.0f;
	BV01[1].u.fZ				=   0.0001f;
	BV01[1].fBaseAlpha			=   1.0f;
	BV01[1].fBaseRed			=   0.25f;
	BV01[1].fBaseGreen			=   0.05f;
	BV01[1].fBaseBlue			=   0.0f;

	/* Vertex #2 */
	BV01[2].ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;
	BV01[2].fX					= 639.0f;
	BV01[2].fY					= 479.0f;
	BV01[2].u.fZ				=   0.0001f;
	BV01[2].fBaseAlpha			=   1.0f;
	BV01[2].fBaseRed			=   0.5f;
	BV01[2].fBaseGreen			=   0.5f;
	BV01[2].fBaseBlue			=   0.0f;

	/*----------------------------------------------------------------------------------- */
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
	srand ((unsigned)10);

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
	status = kmSetDisplayMode(	KM_DSPMODE_VGA,		/* nDisplayMode	*/
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

	/* VertexBufferPointer */
#if 0
	dwDataPtr = (PKMDWORD)0xACB00000;
#else
	dwDataPtr = (PKMDWORD)(((KMDWORD)syMalloc(0x400000) & 0x0FFFFFFFUL) | 0xA0000000);
#endif

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
	SystemConfig.nTextureMemorySize		=	0x100000*2;	/* Texture 2MB						*/
	SystemConfig.nNumOfTextureStruct	=	4096;		/* テクスチャ管理構造体の数 		*/
	SystemConfig.nNumOfSmallVQStruct	=	1024;		/* VQテクスチャ管理構造体の数		*/
	SystemConfig.pTextureWork			=	&FBarea[0];	/* テクスチャ管理構造体領域			*/
	/* for Vertex buffer */
	SystemConfig.pBufferDesc			=	&VertexBufferDesc;	/* pointer to VERTEXBUFFDESC 	*/
	SystemConfig.nNumOfVertexBank		=	2;
	SystemConfig.pVertexBuffer			=	dwDataPtr;			/* pointer to Vertex buffer 	*/
	SystemConfig.nVertexBufferSize		=	0x100000*4;			/* 4MB 							*/
	SystemConfig.nPassDepth				=	1;
	SystemConfig.Pass[0].dwRegionArrayFlag = KM_PASSINFO_AUTOSORT;
	SystemConfig.Pass[0].fBufferSize[0] =  50.0f;
	SystemConfig.Pass[0].fBufferSize[1] =   0.0f;
	SystemConfig.Pass[0].fBufferSize[2] =  50.0f;
	SystemConfig.Pass[0].fBufferSize[3] =   0.0f;
	SystemConfig.Pass[0].fBufferSize[4] =   0.0f;

	status = kmSetSystemConfiguration( &SystemConfig );
	Check_Status(status, "kmSetSystemConfiguration");

	/*----------------------------------------------------------------------------------- */
	/* Set Culling Register */
	status = kmSetCullingRegister(1.0f);
	Check_Status(status, "kmSetCullingRegister");

	/*-----------------------------------------------------------------------------------*/
	/* Initialize DisplayString routine */
	txt_InitDisplayString();

	/*----------------------------------------------------------------------------------- */
	/* some initializes */
	SetupTextures (); 
	SetupContext  (&StripHead03_RE,  &Texture[0], REFLECT);	/* context for reflection	*/
	SetupContext  (&StripHead03_FR1, &Texture[1], -1);		/* context for ball1		*/
	SetupContext  (&StripHead03_FR2, &Texture[2], -1);		/* context for ball2		*/
	SetupContext  (&StripHead03_FR3, &Texture[3], -1);		/* context for ball3		*/
	SetupContext  (&StripHead03_GR,  &Texture[4], MASK);	/* context for face			*/
	InitMeshes ();

	InitBackGround();		/* Setup background plane */

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

/*-------------------------------------------------------------------------------------*
 *  Function Name   :   NextFrame                                                      *
 *  Inputs          :   None                                                           *
 *  Outputs         :   None                                                           *
 *  Returns         :   None                                                           *
 *  Globals Used    :                                                                  *
 *  Description     :   Drawing everything and rendering.                              *
 *                      This routine is called from FRONTEND.C                         *
 *-------------------------------------------------------------------------------------*/
void NextFrame()
{
	char	str[256];

	/* シーンの開始 */
	kmBeginScene(&SystemConfig);

	/* パスの開始 */
	kmBeginPass(&VertexBufferDesc);

	DrawAll ();

	txt_SetCursor(0,1);
#if defined(_DISP_PERFORMANCE_)
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
	/* レンダリング */
	kmRender(KM_RENDER_FLIP);

	/* シーンの終了 */
	kmEndScene(&SystemConfig);

	/*----------------------------------------------------------------------------------- */
#if defined(_DISP_PERFORMANCE_)
/* 性能計算 ------------------------------------------------------------------*/
	EndTime	= syTmrGetCount();
	/* ただいまのフレームを作成するのにかかった時間 */
	nowTime = syTmrCountToMicro( syTmrDiffCount( StartTime, EndTime ) ) / 1000.0f;
	StartTime = EndTime;

	/* 得られた値が異常であった場合は無視 */
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

	totalTime += nowTime;							/* 累積時間 		*/
	aveTime = totalTime / ((double)frame + 1.0f);	/* 今までの平均時間 */

	nFPS  = 1000.0f / (double)nowTime;
	aFPS  = 1000.0f / (double)aveTime;
	MxFPS = 1000.0f / (double)minTime;
	MnFPS = 1000.0f / (double)maxTime;
#endif	/* defined(_DISP_PERFORMANCE_) */

	frame++;
	if(frame > 1000000)
	{
		/* フレームのリセット */
		frame = 0;
#if defined(_DISP_PERFORMANCE_)
		totalTime = 0;
#endif
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
	Init = FALSE;
	/*----------------------------------------------------------------------------------- */
	/* Free vertex buffer */
	status = kmDiscardVertexBuffer(&VertexBufferDesc);
	Check_Status(status, "kmDiscardVertexBuffer");

	/*----------------------------------------------------------------------------------- */
	/* End display */
	status = kmStopDisplayFrameBuffer();
	Check_Status(status, "kmStopDisplayFrameBuffer");
}

/*-------------------------------------------------------------------------------------*
 *  Function Name   :  DrawAll                                                         *
 *  Inputs          :  None                                                            *
 *  Outputs         :  None                                                            *
 *  Returns         :  None                                                            *
 *  Globals Used    :  XAng, YAng, XAng1, YAng1,                                       *
 *  Description     :  Updates and draws all the meshes in the model.                  *
 *  Note            :  The definition of Mesh[i] struct is in logo.h                   *
 *-------------------------------------------------------------------------------------*/
void DrawAll()
{
	register	i;
	int			bTexture = TRUE;

    YAng += (YAng1 / SPEED);    /* Scene angles are changed every frame		*/
    XAng += (XAng1 / SPEED);    /* XAng1 and YAng1 are the speed			*/
    MoveBalls ();    
    PutBallsOn();				/* Balls are drawn on the reflection map	*/

    for (i=0; i<NUM_MESHES; i++)
	{
        if (frame==0)
		{
			UpdateVertex(i);
		} 
        else if (i==REFLECT || i==MASK)
		{
			UpdateVertex  (i);
		}

        if (i==REFLECT)
		{
			UpdateReflection (i);
		}

        if (i==MASK)
		{
			/* We do not want to shade the reflection of the mask */
			Shading (i);
		}

		/* And now... triangles  */
		switch(i)
		{
			case REFLECT:	/* REFLECT */
					kmtri_triangles (	&VertexBufferDesc,			/* PKMVERTEXBUFFDESC */
										&StripHead03_RE,			/* PKMSTRIPHEAD		 */
										Mesh[i].NumFaces,			/* int  nNumFaces	 */
										(int(*)[3])Mesh[i].Faces,	/* int  pFaces[][3]	 */
										TempVert[i],				/* PPVRVERTEX		 */
										bTexture					/* bTexture			 */
						);
					break;
			case MASK:	/* MASK */
					kmtri_triangles (	&VertexBufferDesc,			/* PKMVERTEXBUFFDESC */
										&StripHead03_GR,			/* PKMSTRIPHEAD		 */
										Mesh[i].NumFaces,			/* int  nNumFaces	 */
										(int(*)[3])Mesh[i].Faces,	/* int  pFaces[][3]	 */
										TempVert[i],				/* PPVRVERTEX		 */
										bTexture					/* bTexture			 */
						);
					break;
			default:	/* BALLS */
					switch(i % 3)
					{
						default:
						case 0:
							kmtri_triangles (	&VertexBufferDesc,			/* PKMVERTEXBUFFDESC */
												&StripHead03_FR2,			/* PKMSTRIPHEAD		 */
												Mesh[i].NumFaces,			/* int  nNumFaces	 */
												(int(*)[3])Mesh[i].Faces,	/* int  pFaces[][3]	 */
												TempVert[i],				/* PPVRVERTEX		 */
												bTexture					/* bTexture			 */
							);
							break;
						case 1:
							kmtri_triangles (	&VertexBufferDesc,			/* PKMVERTEXBUFFDESC */
												&StripHead03_FR3,			/* PKMSTRIPHEAD		 */
												Mesh[i].NumFaces,			/* int  nNumFaces	 */
												(int(*)[3])Mesh[i].Faces,	/* int  pFaces[][3]	 */
												TempVert[i],				/* PPVRVERTEX		 */
												bTexture					/* bTexture			 */
								);
							break;
						case 2:
							kmtri_triangles (	&VertexBufferDesc,			/* PKMVERTEXBUFFDESC */
												&StripHead03_FR1,			/* PKMSTRIPHEAD		 */
												Mesh[i].NumFaces,			/* int  nNumFaces	 */
												(int(*)[3])Mesh[i].Faces,	/* int  pFaces[][3]	 */
												TempVert[i],				/* PPVRVERTEX		 */
												bTexture					/* bTexture			 */
								);
							break;
					}
		}
	} 
}

/*-------------------------------------------------------------------------------------*
 *  Function Name   : SetupTextures                                                    *
 *  Inputs          : None                                                             *
 *  Outputs         : None                                                             *
 *  Returns         : None                                                             *
 *  Globals Used    : NumMaterials, Texture, MatInfo                                   *
 *  Description     : Loads BMP files getting the information from MatInfo struct      *
 *                    Creates new textures changing colours in the intermediate map.   *
 *-------------------------------------------------------------------------------------*/
void SetupTextures (void)
{
	register		i,j;
	unsigned char	Red, Green, Blue, Alfa;
	int 			cont=0;

	PKMDWORD			pTexture01;				/* Pointer to texture		*/
	KMTEXTURETYPE		nTextureType;			/* texture type definition	*/
	KMTEX_PIXEL			*pPixel;

	/*----------------------------------------------------------------------------------- */
	nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&Texture[0],							/* OUT	PKMSURFACEDESC	pSurfaceDesc	*/
		128,									/*	IN	KMINT32			nWidth			*/
		128,									/*	IN	KMINT32			nHeight			*/
		nTextureType							/*	IN	KMTEXTURETYPE	nTextureType	*/
	);
	Check_Status(status, "kmCreateTextureSurface(RGB)");

	/*----------------------------------------------------------------------------------- */
	BuffTex[0] = (unsigned long *)TextureBuffer1;	/* texture work area */
	BuffTex[1] = (unsigned long *)&mas_mreflect;
	status = kmuCreateTwiddledTexture(
			(PKMDWORD)(TextureBuffer2 + (16 / sizeof(KMDWORD))),	/*	PKMDWORD		pOutputTexture	*/
			BuffTex[1] + (16 / sizeof(KMDWORD)),					/*	PKMDWORD		pInputTexture	*/
			TRUE,													/*	KMBOOLEAN		bAutoMipMap		*/
			TRUE,													/*	KMBOOLEAN		bDither			*/
			KM_MAPSIZE_128,											/*	KMINT32			USize			*/
			nTextureType											/*	KMTEXTURETYPE	nTextureType	*/
			);
	Check_Status(status, "kmuCreateTwiddledTexture #12");

	status = kmLoadTexture(	&Texture[0],										/* PKMSURFACEDESC pSurfaceDesc	*/
							(PKMDWORD)(TextureBuffer2 + (16 / sizeof(KMDWORD)))	/* PKMDWORD pTexture			*/
							);
	Check_Status(status, "kmLoadTexture(ARGB)");

	/*----------------------------------------------------------------------------------- */
	nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&Texture[4],							/* OUT	PKMSURFACEDESC	pSurfaceDesc	*/
		256,									/*	IN	KMINT32			nWidth			*/
		256,									/*	IN	KMINT32			nHeight			*/
		nTextureType							/*	IN	KMTEXTURETYPE	nTextureType	*/
	);
	Check_Status(status, "kmCreateTextureSurface(ARGB)");

	/*----------------------------------------------------------------------------------- */
	pTexture01 = (unsigned long *)&mas_mground;
	status = kmLoadTexture(&Texture[4],									/* PKMSURFACEDESC pSurfaceDesc	*/
							pTexture01 + (16 / sizeof(KMDWORD))			/* PKMDWORD pTexture			*/
							);
	Check_Status(status, "kmLoadTexture(RGB)");

	/*----------------------------------------------------------------------------------- */
	nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_ARGB4444;	/* Set texture type */
	status = kmCreateTextureSurface(
		&Texture[1],							/* OUT	PKMSURFACEDESC	pSurfaceDesc	*/
		256,									/*	IN	KMINT32			nWidth  		*/
		256,									/*	IN	KMINT32			nHeight			*/
		nTextureType							/*	IN	KMTEXTURETYPE	nTextureType	*/
	);
	Check_Status(status, "kmCreateTextureSurface(ARGB)");

	/*----------------------------------------------------------------------------------- */
	pTexture01 = (unsigned long *)&mas_mfront01;
	status = kmLoadTexture(	&Texture[1],							/* PKMSURFACEDESC pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))		/* PKMDWORD pTexture */
							);
	Check_Status(status, "kmLoadTexture(ARGB)");

	/*----------------------------------------------------------------------------------- */
	nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_ARGB4444;	/* Set texture type */
	status = kmCreateTextureSurface(
		&Texture[2],							/* OUT	PKMSURFACEDESC	pSurfaceDesc	*/
		256,									/*	IN	KMINT32			nWidth			*/
		256,									/*	IN	KMINT32			nHeight			*/
		nTextureType							/*	IN	KMTEXTURETYPE	nTextureType	*/
	);
	Check_Status(status, "kmCreateTextureSurface(ARGB)");

	/*----------------------------------------------------------------------------------- */
	pTexture01 = (unsigned long *)&mas_mfront02;
	status = kmLoadTexture(	&Texture[2],							/* PKMSURFACEDESC pSurfaceDesc	*/
							pTexture01 + (16 / sizeof(KMDWORD))		/* PKMDWORD pTexture			*/
							);
	Check_Status(status, "kmLoadTexture(ARGB)");

	/*----------------------------------------------------------------------------------- */
	nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_ARGB4444;	/* Set texture type */
	status = kmCreateTextureSurface(
		&Texture[3],						/* OUT	PKMSURFACEDESC	pSurfaceDesc	*/
		256,								/*	IN	KMINT32			nWidth			*/
		256,								/*	IN	KMINT32			nHeight			*/
		nTextureType						/*	IN	KMTEXTURETYPE	nTextureType	*/
	);
	Check_Status(status, "kmCreateTextureSurface(ARGB)");

	/*----------------------------------------------------------------------------------- */
	pTexture01 = (unsigned long *)&mas_mfront03;
	status = kmLoadTexture(&Texture[3],								/* PKMSURFACEDESC pSurfaceDesc	*/
							pTexture01 + (16 / sizeof(KMDWORD))		/* PKMDWORD pTexture			*/
							);
	Check_Status(status, "kmLoadTexture(ARGB)");

	/*----------------------------------------------------------------------------------- */
	pTexture01 = (unsigned long *)&mas_backrfl1;
	pTexture01 += (16 / sizeof(KMDWORD));			/* PKMDWORD pTexture */
	cont = 0;
	for (j = 0; j < 20; j++)
	{
		for (i = 0; i < 20; i++)
		{
			pPixel = (KMTEX_PIXEL *)&pTexture01[i + j * 128];	/* Set pointer to the first pixel */
			Alfa  = pPixel->alpha;
			Blue  = pPixel->blue;
			Green = pPixel->green;
			Red   = pPixel->red;
			MCol[0][cont++]   = Alfa;	/* Alpha	*/
			MCol[0][cont++]   = Blue;	/* Blue		*/
			MCol[0][cont++]   = Green;	/* Green	*/
			MCol[0][cont++]   = Red;	/* Red		*/
		}
	}

	/*----------------------------------------------------------------------------------- */
	pTexture01 = (unsigned long *)&mas_backrfl2;
	pTexture01 += (16 / sizeof(KMDWORD));			/* PKMDWORD pTexture */
	cont = 0;
	for (j = 0; j < 20; j++)
	{
		for (i = 0; i < 20; i++)
		{
			pPixel = (KMTEX_PIXEL *)&pTexture01[i + j * 128];	/* Set pointer to the first pixel */
			Alfa  = pPixel->alpha;
			Blue  = pPixel->blue;
			Green = pPixel->green;
			Red   = pPixel->red;
			MCol[1][cont++]   = Alfa;	/* Alpha	*/
			MCol[1][cont++]   = Blue;	/* Blue		*/
			MCol[1][cont++]   = Green;	/* Green	*/
			MCol[1][cont++]   = Red;	/* Red		*/
		}
	}

	/*----------------------------------------------------------------------------------- */
	pTexture01 = (unsigned long *)&mas_backrfl3;
	pTexture01 += (16 / sizeof(KMDWORD));			/* PKMDWORD pTexture */
	cont = 0;
	for (j = 0; j < 20; j++)
	{
		for (i = 0; i < 20; i++)
		{
			pPixel = (KMTEX_PIXEL *)&pTexture01[i + j * 128];	/* Set pointer to the first pixel */
			Alfa  = pPixel->alpha;
			Blue  = pPixel->blue;
			Green = pPixel->green;
			Red   = pPixel->red;
			MCol[2][cont++]   = Alfa;	/* Alpha	*/
			MCol[2][cont++]   = Blue;	/* Blue		*/
			MCol[2][cont++]   = Green;	/* Green	*/
			MCol[2][cont++]   = Red;	/* Red		*/
		}
	}
}

/*-------------------------------------------------------------------------------------*
 *  Function Name   : SetupContext                                                     *
 *  Inputs          : None                                                             *
 *  Outputs         : None                                                             *
 *  Returns         : None                                                             *
 *  Globals Used    :                                                                  *
 *  Description     : Sets default values for the render context.                      *
 *-------------------------------------------------------------------------------------*/
void SetupContext (PKMSTRIPHEAD pStripHead, PKMSURFACEDESC pTexture, int bTrans)
{
	/**************************
	 * KMSTRIPHEADの構築
	 **************************/
#if 0
	memset( &StripContext01, 0, sizeof(StripContext01));
	memset( &StripHead01,	 0, sizeof(StripHead01));
	InitStripContext01(&StripContext01,pStripHead);
#endif

	memset( &StripContext03, 0, sizeof(StripContext03));
	memset( pStripHead,		 0, sizeof(pStripHead));
	InitStripContext03(&StripContext03,pStripHead,pTexture);

	kmChangeStripGouraud	( pStripHead, KM_TRUE);

	if (bTrans == REFLECT)
	{
		/* Global半透明オブジェクト */
		kmChangeStripBlendingMode		( pStripHead, KM_IMAGE_PARAM1, KM_SRCALPHA, KM_INVSRCALPHA );
		kmChangeStripListType			( pStripHead, KM_TRANS_POLYGON);
		kmChangeStripTextureShadingMode	( pStripHead, KM_IMAGE_PARAM1, KM_MODULATE_ALPHA);
		kmChangeStripUseAlpha			( pStripHead, KM_IMAGE_PARAM1, KM_TRUE);
	}
	else if (bTrans == MASK)
	{
		/* 不透明オブジェクト */
		kmChangeStripBlendingMode		( pStripHead, KM_IMAGE_PARAM1, KM_ONE, KM_ZERO );
		kmChangeStripListType			( pStripHead, KM_OPAQUE_POLYGON);
		kmChangeStripTextureShadingMode	( pStripHead, KM_IMAGE_PARAM1, KM_MODULATE);
		kmChangeStripUseAlpha			( pStripHead, KM_IMAGE_PARAM1, KM_FALSE);
	}
	else
	{
		/* Texture半透明 */
		kmChangeStripBlendingMode		( pStripHead, KM_IMAGE_PARAM1, KM_SRCALPHA, KM_INVSRCALPHA );
		kmChangeStripListType			( pStripHead, KM_TRANS_POLYGON);
		kmChangeStripTextureShadingMode	( pStripHead, KM_IMAGE_PARAM1, KM_MODULATE);
		kmChangeStripUseAlpha			( pStripHead, KM_IMAGE_PARAM1, KM_TRUE);
	}
}

/*-------------------------------------------------------------------------------------*
 *  Function Name   : InitMeshes                                                       *
 *  Inputs          : None                                                             *
 *  Outputs         : None                                                             *
 *  Returns         : None                                                             *
 *  Globals Used    : Shad, Mesh, TempVert, TempNormals                                *
 *  Description     : Sets initials values for meshes managing                         *
 *-------------------------------------------------------------------------------------*/
void InitMeshes (void)
{
	float		x, z, y, DX;
	register	i, j, k=0;
	int 		mptr = 0x0c400000;

    /* This function is in mask.h and creates an array of structures with 3D data */
    CreateMeshesArray ();
   
    /* Shad is a 255 values array whit information for smooth shading */
    for (i=0; i<120; i++){ Shad[k++] = (float)(120-i)/480.0;}
    for (i=0; i<100; i++){ Shad[k++] = (float) i/100.0;}
    for (i=0; i<35;  i++){ Shad[k++] = 1.0f;}

	for (i=0; i<NUM_MESHES; i++)
	{
#if 0
		TempVert[i] = (PVRVERTEX *)mptr; mptr += Mesh[i].NumVertex*sizeof(PVRVERTEX);
		TempNormals[i] = (float *)mptr; mptr += Mesh[i].NumVertex*sizeof(float)*3 ;
#else
		TempVert[i] = (PVRVERTEX *)(((KMDWORD)syMalloc(Mesh[i].NumVertex*sizeof(PVRVERTEX)) & 0x0FFFFFFFUL) | 0xA0000000);
		TempNormals[i] = (float *)(((KMDWORD)syMalloc(Mesh[i].NumVertex*sizeof(float)*3) & 0x0FFFFFFFUL) | 0xA0000000);
#endif
	}

	/* Setting UV values for all the meshes and calculating TempNormals for reflections */
    for (j=0; j<NUM_MESHES;j++)
	{
		for (i=0; i<Mesh[j].NumVertex; i++)
		{
        	(TempVert[j]+i)->fUOverW    =  (Mesh[j].TexMap) ? *(Mesh[j].UV+i*2+0) : 0;
            (TempVert[j]+i)->fVOverW    =  (Mesh[j].TexMap) ? *(Mesh[j].UV+i*2+1) : 0; 
            (TempVert[j]+i)->u32Colour  =  0xFFFFFF; 

			/* TempNormals are calculated with the normal and the position of each vertex */
            x =  (*(Mesh[j].Vertex+i*3+0) - Mesh[j].Center[0]);
            y =  (*(Mesh[j].Vertex+i*3+1) - Mesh[j].Center[1]);
            z =  (*(Mesh[j].Vertex+i*3+2) - Mesh[j].Center[2]);

            DX = sqrt (x*x+y*y+z*z);
                      
            *(TempNormals[j]+i*3+0) = ((*(Mesh[j].Normals+i*3+0) +x/DX)/2.0);
            *(TempNormals[j]+i*3+1) = ((*(Mesh[j].Normals+i*3+1) +y/DX)/2.0);
            *(TempNormals[j]+i*3+2) = ((*(Mesh[j].Normals+i*3+2) +z/DX)/2.0);
		}
	}
}

/*-------------------------------------------------------------------------------------*
 *  Function Name   : UpdateVertex                                                     *
 *  Inputs          : Num (the mesh in the model)                                      *
 *  Outputs         : None                                                             *
 *  Returns         : None                                                             *
 *  Globals Used    : XAng, YAng                                                       *
 *  Description     : Turns vertices around two axes.                                  *
 *-------------------------------------------------------------------------------------*/
void UpdateVertex (int Num)
{
	float	CamFocus = 1000.0;
	float	CosX, SinX, CosY, SinY, x, z, y , CamZ;
	float	Temp[3];
	int		i, j=0, k=0, l=0;

	CosX = cos(XAng); SinX = sin(XAng);
	CosY = cos(YAng); SinY = sin(YAng);
  
    for (i=0; i<Mesh[Num].NumVertex; i++)
	{
		x = *(Mesh[Num].Vertex+k++);
        y = *(Mesh[Num].Vertex+k++);
        z = *(Mesh[Num].Vertex+k++);

		/* Temp is the outcome vertex after the rotation */
        Temp[0]  = x * CosY - z * SinY;
        Temp[2]  = z * CosY + x * SinY;

        z        = Temp[2];
        Temp[1]  = y * CosX - z * SinX;
        Temp[2]  = z * CosX + y * SinX + TPos;

        if (Temp[2] <=0.0)
		{
			 Temp[2] = 0.001f;
		}

		 /* We store the vertex in TempVert */
		CamZ = 1.0/(Temp[2]);
    	(TempVert[Num]+i)->fX    =  CamFocus * CamZ * Temp[0] + 320;
        (TempVert[Num]+i)->fY    = -CamFocus * CamZ * Temp[1] + 240;
	    (TempVert[Num]+i)->fInvW =  CamZ;
	}
}

/*-------------------------------------------------------------------------------------*
 *  Function Name   : Shading                                                          *
 *  Inputs          : Num                                                              *
 *  Outputs         : None                                                             *
 *  Returns         : None                                                             *
 *  Globals Used    : Light1, MatInfo, Mesh, TempVert                                  *
 *  Description     : Shades a mesh.                                                   *
 *-------------------------------------------------------------------------------------*/
void Shading (int Num)
{
	float		CosX, SinX, CosY, SinY, x, z, y;
	float		Colour[3] = {0.2f, 0.5f, 0.9f}, TCo, Dir, LTemp[3],  Ligth1[3] = { -1, 1, -1};
	register	l=0, i, k=0, Val;
	KMUINT32	Col;

    /* We just rotate the light vector in the opposite direction instead of rotating all the normals */
    Dir = sqrt (Ligth1[0]*Ligth1[0]+Ligth1[1]*Ligth1[1]+Ligth1[2]*Ligth1[2]);
    x = Ligth1[0]/Dir; 
	y = Ligth1[1]/Dir; 
	z = Ligth1[2]/Dir;

    CosX = cos(-XAng); SinX = sin(-XAng);
    CosY = cos(-YAng); SinY = sin(-YAng);

    LTemp[1]  = y * CosX - z * SinX;
    LTemp[2]  = z * CosX + y * SinX;

    z = LTemp[2];
    LTemp[0]  = x * CosY - z * SinY;
    LTemp[2]  = z * CosY + x * SinY;

    k = Mesh[Num].Material;

    for (i=0; i<Mesh[Num].NumVertex; i++)
	{
		x = *(Mesh[Num].Normals+l++);
        y = *(Mesh[Num].Normals+l++);
        z = *(Mesh[Num].Normals+l++);

		/* Val is a value from 0 to 255 depending on the angle between a normal *
		 * and the light direction.                                             */
		Val = (int) (127.0 * fabs( LTemp[0] * x + LTemp[1] * y + LTemp[2] * z + 1.0) );
      
        TCo = Shad[Val];
        Col = (int)(255*TCo); 
  
	    /* Setting vertex colour */
        (TempVert[Num]+i)->u32Colour  = RGBColour (Col,Col,Col);
    }
}

/*-------------------------------------------------------------------------------------*
 *  Function Name   :  UpdateReflection                                                *
 *  Inputs          :   Num                                                            *
 *  Outputs         :  None                                                            *
 *  Returns         :  None                                                            *
 *  Globals Used    :  XAng, YAng, Mesh, TemVert                                       *
 *  Description     :  Changes UV values fixing their position when the mesh rotates.  *
 *                     So, it has to move all values in the opposite direction.        *
 *-------------------------------------------------------------------------------------*/
void UpdateReflection (int Num)
{ 
	int		i,  k=0;
	float	CosX, SinX, CosY, SinY, x, z, y, Temp[3];

	CosX = cos(XAng); SinX = sin(XAng);
	CosY = cos(YAng); SinY = sin(YAng);

	for (i=0; i<Mesh[Num].NumVertex; i++)
	{
    	x = *(TempNormals[Num]+k++);
        y = *(TempNormals[Num]+k++);
        z = *(TempNormals[Num]+k++);

        Temp[0]  = x * CosY - z * SinY;
        Temp[2]  = z * CosY + x * SinY;

        z        = Temp[2];
        Temp[1]  = y * CosX - z * SinX;
        Temp[2]  = z * CosX + y * SinX;


        Temp[2] = fabs(Temp[2])+0.01;

		/* Now we proyect the espherical coordinates to rectangular ones... */
        x = (PI + atan(Temp[0]/Temp[2]))/PI;
        y = (PI + atan(Temp[1]/Temp[2]))/PI;

		/* ...and we have now our new UV values */
        (TempVert[Num]+i)->fUOverW =  x+0.5;
        (TempVert[Num]+i)->fVOverW =  y+0.5; 
		/* Setting vertex colour */
		if(Num == REFLECT)
		{
			(TempVert[Num]+i)->u32Colour  = RGBA(255, 255, 255, LH);
		}
		else
		{
			(TempVert[Num]+i)->u32Colour  = RGBA(255, 255, 255, 255);
		}
	}
}

/*-------------------------------------------------------------------------------------*
 *  Function Name   :  MoveBalls                                                       *
 *  Inputs          :  None                                                            *
 *  Outputs         :  None                                                            *
 *  Returns         :  None                                                            *
 *  Globals Used    :  frame, Mesh, Balls                                              *
 *  Description     :  Moves balls and stores their position for drawing them later.   *
 *-------------------------------------------------------------------------------------*/
void MoveBalls (void)
{
	float		x, y, z;
	register	i, j;

	/* Setting initials position values */
    if (frame == 0)
	{
		for (j=BALL; j<=BALL08; j++)
		{
        	x = 200-40*j - *(Mesh[j].Vertex+0);
        	y = (50.0*(float)rand())/RAND_MAX - *(Mesh[j].Vertex+1);
        	z = -300+j*10 -*(Mesh[j].Vertex+2);  

            for (i=0;i<Mesh[j].NumVertex;i++)
			{
            	*(Mesh[j].Vertex+i*3+0) += x;
            	*(Mesh[j].Vertex+i*3+1) += y;
				*(Mesh[j].Vertex+i*3+2) += z;
             }
		}
	}
         
    /* Moving in a fancy way.  */
    for (j=BALL; j<=BALL08; j++)
	{
    	for (i=0; i<Mesh[j].NumVertex; i++)
		{
        	(TempVert[j]+i)->fY +=  20.0*sin((j*15+frame/1.9)/ 30.3);
            (TempVert[j]+i)->fX +=  5.00*cos((j*15+frame)/ 15.3);
		}
    }
}

/*-------------------------------------------------------------------------------------*
 *  Function Name   :  PutBallsOn                                                      *
 *  Inputs          :  None                                                            *
 *  Outputs         :  None                                                            *
 *  Returns         :  None                                                            *
 *  Globals Used    :  XAng, YAng, Mesh, TemVert                                       *
 *  Description     :  Refreshing reflection map every frame.                          *
 *-------------------------------------------------------------------------------------*/
void PutBallsOn (void)
{
	float		x, y;
	register	i, j, k;
	int 		cont = 0, cont2=0, Co;
	char 		Alpha;

	KMTEX_PIXEL		*pPixel;
	KMTEXTURETYPE	nTextureType;		/* texture type definition */

    /* Restore original pretty background */
    memcpy (BuffTex[0], BuffTex[1], 128 * 128 * 4);

	/* Balls are setting on the background one by one */
    for (k=BALL; k<=BALL08; k++)
	{
		Co = Mesh[k].Material-1;
        /* Balls positions */
        x = (128.0 * TempVert[k]->fX )/640.0;
        y = (128.0 * (480-TempVert[k]->fY) )/480.0;
        cont2=0;
        cont = ((int)x+(int)y*128);
        for (i=0; i<20; i++) 
	    {
        	for (j=0; j<20; j++)
			{
				Alpha = MCol[Co][cont2++];		/* Color key for translucent */
                if (Alpha == 0 || y+i>128 || x+j>128 || y+i<0 || x+j<0)
				{
					cont2 += 3;
					continue;
				}
				pPixel = (KMTEX_PIXEL *)&BuffTex[0][cont + j];	/* Set pointer to the first pixel */
				pPixel->blue	= MCol[Co][cont2++];
				pPixel->green	= MCol[Co][cont2++];
				pPixel->red		= MCol[Co][cont2++];
           }
           cont +=128;
       }
	}

    /* Updating reflection texture */
	nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565;			/* Set texture type */
	status = kmuCreateTwiddledTexture(
			(PKMDWORD)(TextureBuffer2 + (16 / sizeof(KMDWORD))),	/*	PKMDWORD		pOutputTexture	*/
			BuffTex[0] + (16 / sizeof(KMDWORD)),					/*	PKMDWORD		pInputTexture	*/
			TRUE,													/*	KMBOOLEAN		bAutoMipMap		*/
			TRUE,													/*	KMBOOLEAN		bDither			*/
			KM_MAPSIZE_128,											/*	KMINT32			USize			*/
			nTextureType											/*	KMTEXTURETYPE	nTextureType	*/
			);
	Check_Status(status, "kmuCreateTwiddledTexture #12");

	status = kmLoadTexture(&Texture[0],											/* PKMSURFACEDESC	pSurfaceDesc	*/
							(PKMDWORD)(TextureBuffer2 + (16 / sizeof(KMDWORD)))	/* PKMDWORD 		pTexture		*/
							);
	Check_Status(status, "kmLoadTexture(ARGB)");
}

/****************************************************************************
 *	main
 ****************************************************************************/
int	Kamui_Init(void)
{

	txt_ClearScreen();	/* Clear text screen */
#if defined(_VERTEXMACRO_L4_)
	PRINTOUT(("** KMMASK(KAMUI2&Shinobi) Use:Level4 Macro **\n"));
#else
	PRINTOUT(("** KMMASK(KAMUI2&Shinobi) **\n"));
#endif
    SetupScene ();			/* Initialize */

#if 0
	do {
		ReadMaple ();
		NextFrame();	/* Rendering */
		/* mask の反射の強さの変更(環境マップポリゴンの透明度) */
		if((count % 10) == 0)
		{
			/* 10 frame毎に更新 */
			LH += DLH;
			if(LH > 255)
			{
				/* 反射が最強になった？(完全不透明) */
				LH = 255; DLH = -DLH;
			}
			if(LH < 0)
			{
				/* 反射が最低になった？(完全透明) */
				LH = 0; DLH = -DLH;
			}
		}
		count++;
		if(count > 100000){ count = 0;}
	} while(1);

	Finish();			/* End of render */
	PRINTOUT(("** END KMMASK **\n"));
#endif
	return 0;
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
void ReadMaple (void)
{
	per = pdGetPeripheral(PDD_PORT_A0);

	/* START button */
	if ( per->press & PDD_DGT_ST )
	{
		XAng1 = 0.0f;
		YAng1 = 0.0f;
	}

	/* UP cross key */
	if ( per->on & PDD_DGT_KU )
	{
		LH += 10;
		if(LH > 255){ LH = 255;}
	}

	/* DOWN cross key */
	if ( per->on & PDD_DGT_KD )
	{
		LH -= 10;
		if(LH < 0){ LH = 0;}
	}

	/* Medama X */
	YAng1 += (float)(per->x1) / 12700.0f;

	/* Medama Y */
	XAng1 -= (float)(per->y1) / 12700.0f;

	/* Slider Right */
	TPos += (float)(per->r / 12.8f);

	/* Slider Left */
	TPos -= (float)(per->l / 12.8f);

	/* A button */
	if ( per->press & PDD_DGT_TA )
	{
		TPos += 10;
	}

	/* B button */
	if ( per->press & PDD_DGT_TB )
	{
		TPos -= 10;
	}

	/* X button */
	if ( per->press & PDD_DGT_TX )
	{
		LH += 10;
		if(LH > 255){ LH = 255;}
	}

	/* Y button */
	if ( per->press & PDD_DGT_TY )
	{
		LH -= 10;
		if(LH < 0){ LH = 0;}
	}
}

/*--------------------------- End of File --------------------------------*/
