/******************************************************************************
 Name     : Tools(KMFLIGHT)
 Title    : KAMUI test program "Tools" from VL
 Author   : VideoLogic Carlos Sarria / NEC Software Takeshi Muto
 Created  : October 1997 by VideoLogic
 Modified : February  2. 1999 by T.Kamei 	  for KAMUI2
			February 16. 1999 by Takeshi Muto for Shinobi
 Description :
 Copyright : 1997 by VideoLogic Limited. All rights reserved.
******************************************************************************/
#if 0
#define		_VERTEXMACRO_L4_		/* VertexMacroLevel4使用時は定義する			*/
#endif

#define	FOG_MIN		(-0.8f)

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


#include "kmtools.h"

#if defined(_VERTEXMACRO_L4_)
#define _KM_USE_VERTEX_MACRO_L4_
#include "kamuix.h"
#endif

static float	LightDir[3] = { -1.0f, 1.0f, -1.0f };
static unsigned	TotalPolys = 0;
static char		VFog = 0;

PVRVERTEX		*PVRVert[256];
CASTMESHES		CMesh[256];
TRANSFORM		T[256];

/****************************************************************************
 *	Valuables for KAMUI
 ****************************************************************************/
#if defined(_DISP_PERFORMANCE_)
extern	int					frame;					/* 画面フレーム							*/
extern	int					frame_2;				/* 画面フレーム上位						*/
extern	Uint32		StartTime;
extern	Uint32		EndTime;
extern	double				nFPS;					/* 現在の性能(Frame/Second)				*/
extern	double				aFPS;					/* 性能の平均値							*/
extern	double				MxFPS;					/* 最高性能								*/
extern	double				MnFPS;					/* 最低性能								*/
extern	double				nowTime;				/* 現在の描画時間(msec)					*/
extern	double				maxTime;				/* 最高描画時間(msec)					*/
extern	double				minTime;				/* 最低描画時間(msec)					*/
extern	double				totalTime;				/* 累積render時間(msec)					*/
extern	double				aveTime;				/* 平均描画時間(msec)					*/
#endif

extern	KMSTATUS				status;				/* return status of KAMUI API			*/
extern	KMVERTEXBUFFDESC		VertexBufferDesc;	/* Vertex-buffer						*/
extern  KMSTRIPCONTEXT			StripContext00;
extern  KMSTRIPHEAD				StripHead00;
extern  KMSTRIPCONTEXT			StripContext03;
extern  KMSTRIPHEAD				StripHead03;
extern 	KMSYSTEMCONFIGSTRUCT	SystemConfig;

/****************************************************************************
 *	Check KAMUI function status
 ****************************************************************************/
void	Check_Status(KMSTATUS status, char *func)
{
	switch(status) {
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
	kmEndStrip(pBufferDesc);
}

/****************************************************************************
 *	kmtri_quads  by T.Hirata
 ***************************************************************************/
void 
kmtri_quads	(	PKMVERTEXBUFFDESC	pBufferDesc,
				PKMSTRIPHEAD		pStripHead,
				int					nNumFaces,
				int					pFaces[][4],
				PPVRVERTEX			pVertices,
				int					bTexture)
{
	KMSTATUS	status;
	int			i;
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
	kmEndStrip(pBufferDesc);
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
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFogMode			= KM_FOGTABLE;
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
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFogMode				= KM_FOGTABLE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bColorClamp			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bUseAlpha				= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bIgnoreTextureAlpha	= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFlipUV				= KM_NOFLIP;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nClampUV				= KM_NOCLAMP;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFilterMode			= KM_POINT_SAMPLE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bSuperSampleMode		= KM_FALSE;
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
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFogMode			= KM_FOGTABLE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bColorClamp		= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bUseAlpha			= KM_FALSE;

	kmGenerateStripHead01( pStripHead,pStripContext );
}

/*----------------------------------------------------------------------* 
 *  Function Name   : SetBackground                                     * 
 *  Inputs          :                                                   * 
 *  Outputs         :                                                   * 
 *  Returns         :                                                   * 
 *  Globals Used    :                                                   * 
 *  Description     :                                                   * 
 *----------------------------------------------------------------------*/
void SetBackground (PKMSURFACEDESC TextureID)
{
	KMSTRIPCONTEXT		StripContextBG01;		/* for BG					*/
	KMSTRIPHEAD			StripHeadBG01;			/* for BG					*/
	KMSTRIPCONTEXT		StripContextBG03;		/* for BG					*/
	KMSTRIPHEAD			StripHeadBG03;			/* for BG					*/
	KMVERTEX_01			BV01[3];				/* for NO-TEXTURE-GOURAUD	*/
	KMVERTEX_03			BV03[3];				/* for TEXTURE-GOURAUD		*/

	if(TextureID == (PKMSURFACEDESC)NULL)
	{
		/* No Texture(VertexType01) */
		memset( &StripContextBG01	, 0, sizeof(StripContextBG01));
		memset( &StripHeadBG01		, 0, sizeof(&StripHeadBG01));
		InitStripContext01	(&StripContextBG01,&StripHeadBG01);

		/* No texture */
		/* Vertex #0 */
		BV01[0].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
		BV01[0].fX					=   0.0f;
		BV01[0].fY					= 479.0f;
		BV01[0].u.fZ				=   0.0001f;
		BV01[0].fBaseAlpha			=   0.0f;
		BV01[0].fBaseRed			=   0.55f;
		BV01[0].fBaseGreen			=   0.87f;
		BV01[0].fBaseBlue			=   0.96f;

		/* Vertex #1 */
		BV01[1].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
		BV01[1].fX					= 320.0f;
		BV01[1].fY					=   0.0f;
		BV01[1].u.fZ				=   0.0001f;
		BV01[1].fBaseAlpha			=   0.0f;
		BV01[1].fBaseRed			=   0.0f;
		BV01[1].fBaseGreen			=   0.15f;
		BV01[1].fBaseBlue			=   0.73f;

		/* Vertex #2 */
		BV01[2].ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;
		BV01[2].fX					= 639.0f;
		BV01[2].fY					= 479.0f;
		BV01[2].u.fZ				=   0.0001f;
		BV01[2].fBaseAlpha			=   0.0f;
		BV01[2].fBaseRed			=   0.55f;
		BV01[2].fBaseGreen			=   0.87f;
		BV01[2].fBaseBlue			=   0.96f;

		/* Set BG Plane */
		kmSetBackGround(	&StripHeadBG01,
							KM_VERTEXTYPE_01,
							(PVOID)&BV01[0],
							(PVOID)&BV01[1],
							(PVOID)&BV01[2]	);
	}
	else
	{	
		/* Texture(VertexType03) */
		memset( &StripContextBG03	, 0, sizeof(StripContextBG03));
		memset( &StripHeadBG03		, 0, sizeof(&StripHeadBG03));
		InitStripContext03	(&StripContextBG03,&StripHeadBG03,TextureID);

		/* Use texture */
		/* Vertex #0 */
		BV03[0].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
		BV03[0].fX					=   0.0f;
		BV03[0].fY					=   0.0f;
		BV03[0].u.fZ				=   0.0001f;
		BV03[0].fU					=   0.0f;
		BV03[0].fV					=   1.0f;
		BV03[0].uBaseRGB.dwPacked	= RGBAColour (255, 255, 255, 255);
		BV03[0].uOffsetRGB.dwPacked	= RGBAColour (255, 255, 255, 255);

		/* Vertex #1 */
		BV03[1].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
		BV03[1].fX					= 640.0f;
		BV03[1].fY					=   0.0f;
		BV03[1].u.fZ				=   0.0001f;
		BV03[1].fU					=   1.0f;
		BV03[1].fV					=   1.0f;
		BV03[1].uBaseRGB.dwPacked	= RGBAColour (255, 255, 255, 255);
		BV03[1].uOffsetRGB.dwPacked	= RGBAColour (255, 255, 255, 255);

		/* Vertex #2 */
		BV03[2].ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;
		BV03[2].fX					= 640.0f;
		BV03[2].fY					= 480.0f;
		BV03[2].u.fZ				=   0.0001f;
		BV03[2].fU					=   1.0f;
		BV03[2].fV					=   0.0f;
		BV03[2].uBaseRGB.dwPacked	= RGBAColour (255, 255, 255, 255);
		BV03[2].uOffsetRGB.dwPacked	= RGBAColour (255, 255, 255, 255);

		/* Set BG Plane */
		kmSetBackGround(	&StripHeadBG03,
							KM_VERTEXTYPE_03,
							(PVOID)&BV03[0],
							(PVOID)&BV03[1],
							(PVOID)&BV03[2]	);
	}
}

/*--------------------------------------------------------------------* 
 *  Function Name   : ResetMatrix                                     * 
 *  Inputs          : Object                                          * 
 *  Outputs         :                                                 * 
 *  Returns         :                                                 * 
 *  Globals Used    :                                                 * 
 *  Description     : Builds an identity matrix and stores it in T    * 
 *--------------------------------------------------------------------*/
void ResetMatrix (int Object)
{
	static TRANSFORM Id = 
	{ 
		{
			{1.0f, 0.0f, 0.0f, 0.0f},
		  	{0.0f, 1.0f, 0.0f, 0.0f},
		  	{0.0f, 0.0f, 1.0f, 0.0f}
		},
		{
			{1.0f, 0.0f, 0.0f, 0.0f},
		  	{0.0f, 1.0f, 0.0f, 0.0f},
		  	{0.0f, 0.0f, 1.0f, 0.0f}
		}
	};

	memcpy (&T[Object], &Id, sizeof (TRANSFORM));
}

/*----------------------------------------------------------------------* 
 *  Function Name   :  Rotate                                           * 
 *  Inputs          :  Object, Axis, Theta                              * 
 *  Outputs         :                                                   * 
 *  Returns         :                                                   * 
 *  Globals Used    :                                                   * 
 *  Description     :  Rotate T an angle Theta around Axis              * 
 *----------------------------------------------------------------------*/
void Rotate (int Object, pvr_vector Axis, float Theta)
{
	float	halfTheta;
 	float	sinHalfTheta;
 	float	cosHalfTheta;
	float	MRot[3][4], MTemp[3][4]; 
	float	W,X,Y,Z;
	float	Tm1,Tm2,Tm3,Tm4,Tm5,TmNorm;
	int		Row, Col;

	/* convert to quaternian */
	halfTheta = Theta * 0.5f;

	/*	Using double sin and cos  */ 
	cosHalfTheta = (float) cos(halfTheta);
	sinHalfTheta = (float) sin(halfTheta);

	W = cosHalfTheta;
	X = sinHalfTheta * Axis[0];
	Y = sinHalfTheta * Axis[1];
	Z = sinHalfTheta * Axis[2];

	/* convert quaternian into Matrix form */ 
	Tm1 = X * X;
	Tm2 = Y * Y;
	Tm3 = Z * Z;
	Tm4 = Tm2 + Tm3;

	TmNorm= W*W + Tm1 + Tm4;  /* Normalising term */

	if (TmNorm!=0.0f)
	{
		Tm5 = 2.0f / TmNorm; 
	}
	else
	{
		Tm5 = 0.0f;
	}

	MRot[0][0] = 1.0f - Tm5*Tm4;
	MRot[1][1] = 1.0f - Tm5*(Tm1+Tm3);    
	MRot[2][2] = 1.0f - Tm5*(Tm1+Tm2);

	Tm1 = Tm5*X;
	Tm2 = Tm5*Y;
	Tm4 = Tm5*Z*W;
	Tm5 = Tm1*Y; 

	MRot[0][1] = Tm5 - Tm4;
	MRot[1][0] = Tm5 + Tm4;

	Tm4 = Tm2*W;
	Tm5 = Tm1*Z;

	MRot[0][2] = Tm5 + Tm4;
	MRot[2][0] = Tm5 - Tm4;


	Tm4 = Tm1*W; 
	Tm5 = Tm2*Z;

	MRot[1][2] = Tm5 - Tm4;
	MRot[2][1] = Tm5 + Tm4;

	memcpy (MTemp, &T[Object].Matrix, sizeof (T[Object].Matrix));

	for(Row = 0; Row < 3; Row ++)
	{
		for(Col = 0; Col < 3; Col ++)
		{
			/*
				unroll the innermost loop to do sr bit
			*/

			T[Object].Matrix[Row][Col] = MTemp[Row][0] * MRot[0][Col] +
								  MTemp[Row][1] * MRot[1][Col] +
								  MTemp[Row][2] * MRot[2][Col];
		}
	}

	memcpy (MTemp, &T[Object].Inverse, sizeof (T[Object].Matrix));

	for(Row = 0; Row < 3; Row ++)
	{
		for(Col = 0; Col < 3; Col ++)
		{
			/*
				unroll the innermost loop to do sr bit
				inverse of a rotation is its transpose!
			*/

			T[Object].Inverse[Row][Col] = MRot[0][Row] * MTemp[0][Col] +
								   MRot[1][Row] * MTemp[1][Col] +
								   MRot[2][Row] * MTemp[2][Col];
		}
	}
}

/*----------------------------------------------------------------------* 
 *  Function Name   :  Scale                                            * 
 *  Inputs          :  Object, S                                        * 
 *  Outputs         :                                                   * 
 *  Returns         :                                                   * 
 *  Globals Used    :                                                   * 
 *  Description     :  Escale T using S values (x, y, z)                * 
 *----------------------------------------------------------------------*/
void Scale (int Object, float SX, float SY, float SZ)
{
	int i;

	float invX = 1.0f / SX;
	float invY = 1.0f / SY;
	float invZ = 1.0f / SZ;

	for(i = 0; i < 3; i ++)
	{
	 	T[Object].Matrix[i][0] *= SX;
	 	T[Object].Matrix[i][1] *= SY;
	 	T[Object].Matrix[i][2] *= SZ;

	 	T[Object].Inverse[0][i] *= invX;
	 	T[Object].Inverse[1][i] *= invY;
	 	T[Object].Inverse[2][i] *= invZ;
	}

 	T[Object].Inverse[0][3] *= invX;
 	T[Object].Inverse[1][3] *= invY;
 	T[Object].Inverse[2][3] *= invZ;
}

/*----------------------------------------------------------------------* 
 *  Function Name   : Translate                                         * 
 *  Inputs          : Object, Tr                                        * 
 *  Outputs         :                                                   * 
 *  Returns         :                                                   * 
 *  Globals Used    :                                                   * 
 *  Description     : Translate T using Tr(x,y,z) displacement.         * 
 *----------------------------------------------------------------------*/
void Translate (int Object, float TrX, float TrY, float TrZ)
{
	T[Object].Matrix[0][3] += T[Object].Matrix[0][0] * TrX + T[Object].Matrix[0][1] * TrY + T[Object].Matrix[0][2] * TrZ;	
	T[Object].Matrix[1][3] += T[Object].Matrix[1][0] * TrX + T[Object].Matrix[1][1] * TrY + T[Object].Matrix[1][2] * TrZ;	
	T[Object].Matrix[2][3] += T[Object].Matrix[2][0] * TrX + T[Object].Matrix[2][1] * TrY + T[Object].Matrix[2][2] * TrZ;	

	T[Object].Inverse[0][3] -= TrX;	
	T[Object].Inverse[1][3] -= TrY;	
	T[Object].Inverse[2][3] -= TrZ;	
}

/*----------------------------------------------------------------------* 
 *  Function Name   : InitScene                                         * 
 *  Inputs          :                                                   * 
 *  Outputs         :                                                   * 
 *  Returns         :                                                   * 
 *  Globals Used    :                                                   * 
 *  Description     : Draw a object                                     * 
 *----------------------------------------------------------------------*/
void InitScene (void)
{
	kmBeginScene(&SystemConfig);
	kmBeginPass(&VertexBufferDesc);
}

/*----------------------------------------------------------------------* 
 *  Function Name   : EndScene                                          * 
 *  Inputs          :                                                   * 
 *  Outputs         :                                                   * 
 *  Returns         :                                                   * 
 *  Globals Used    :                                                   * 
 *  Description     : Draw a object                                     * 
 *----------------------------------------------------------------------*/
void EndScene (PKMSYSTEMCONFIGSTRUCT pSyetemConfig)
{
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
	kmEndPass(&VertexBufferDesc);
	kmRender(KM_RENDER_FLIP);
	kmEndScene(pSyetemConfig);

	/*----------------------------------------------------------------------------------- */

#if defined(_DISP_PERFORMANCE_)
/* 性能計算 ------------------------------------------------------------------*/
	EndTime	= syTmrGetCount();
	/* ただいまのフレームを作成するのにかかった時間 */
	nowTime = syTmrCountToMicro( syTmrDiffCount( StartTime, EndTime ) ) / 1000.0f;
	StartTime = EndTime;

	if((nowTime > 1000.0f)||(nowTime < 1.0f)){	nowTime = 20.0f;}	/* 得られた値が異常であった場合は無視			*/
	if(nowTime > maxTime){ maxTime = nowTime;}						/* もっとも時間がかかった？ 					*/
	if(nowTime < minTime){ minTime = nowTime;}						/* もっとも早かった？							*/

	totalTime += nowTime;								/* 累積時間 		*/
	aveTime = totalTime / ((double)frame + 1.0f);		/* 今までの平均時間 */

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

/*----------------------------------------------------------------------* 
 *  Function Name   : InitMeshes                                        * 
 *  Inputs          :                                                   * 
 *  Outputs         :                                                   * 
 *  Returns         :                                                   * 
 *  Globals Used    :                                                   * 
 *  Description     : Draw a object                                     * 
 *----------------------------------------------------------------------*/
void InitMeshes (int nMeshes, CASTMESHES *pMeshes)
{
	register i;
	int mptr = 0x0c400000;

	/* Memory allocation for Vert, UV values and SmoothShading*/
    for (i=0; i<nMeshes; i++) 
	{
		memcpy ( &CMesh[i], &pMeshes[i], sizeof (CASTMESHES) );
#if 0
		PVRVert[i] = (PVRVERTEX *)mptr; mptr += CMesh[i].NumVertex*sizeof(PVRVERTEX);
#else
		PVRVert[i] = (PVRVERTEX *)(((KMDWORD)syMalloc(CMesh[i].NumVertex*sizeof(PVRVERTEX)) & 0x0FFFFFFFUL) | 0xA0000000);
#endif
		ResetMatrix (i); 
		SetUV (i);
		SetSmoothShading (i, (i==0)?C_NONE:C_PLAIN);
		TotalPolys += CMesh[i].NumFaces;
	}
}

/*----------------------------------------------------------------------* 
 *  Function Name   : FreeMeshes                                        * 
 *  Inputs          :                                                   * 
 *  Outputs         :                                                   * 
 *  Returns         :                                                   * 
 *  Globals Used    :                                                   * 
 *  Description     : Draw a object                                     * 
 *----------------------------------------------------------------------*/
void FreeMeshes (int nMeshes)
{
}

/*----------------------------------------------------------------------* 
 *  Function Name   : SetVertices                                       * 
 *  Inputs          : nFaces, Faces, nVertex, pVertex                   * 
 *  Outputs         :                                                   * 
 *  Returns         :                                                   * 
 *  Globals Used    :                                                   * 
 *  Description     : Draw a object                                     * 
 *----------------------------------------------------------------------*/
void SetVertices (int Object, PKMSTRIPHEAD pStripHead, int Effect )
{
	register	i, nVertex = 0;
	float		fX, fY, fZ, pV[3], f1OverZ;
	float		CamFocus = 600.0f;

    for (i=0; i<CMesh[Object].NumVertex; i++)
	{
		pV[0] = *(CMesh[Object].Vertex+nVertex++);
		pV[1] = *(CMesh[Object].Vertex+nVertex++);
		pV[2] = *(CMesh[Object].Vertex+nVertex++);

		fX = (pV[0] * T[Object].Matrix[0][0] + pV[1] * T[Object].Matrix[0][1] + pV[2] * T[Object].Matrix[0][2] + T[Object].Matrix[0][3]);
		fY = (pV[0] * T[Object].Matrix[1][0] + pV[1] * T[Object].Matrix[1][1] + pV[2] * T[Object].Matrix[1][2] + T[Object].Matrix[1][3]);
		fZ = (pV[0] * T[Object].Matrix[2][0] + pV[1] * T[Object].Matrix[2][1] + pV[2] * T[Object].Matrix[2][2] + T[Object].Matrix[2][3]);

		fZ += 800;

	if (fZ<0.00001f) { fZ = 0.00001f;}

	f1OverZ = 1.0f / fZ;

	(PVRVert[Object]+i)->fX = f1OverZ * fX * 600 + 320;
	(PVRVert[Object]+i)->fY = -f1OverZ * fY * 600 + 240;
    (PVRVert[Object]+i)->fInvW = f1OverZ;

	if (Effect == FX_OPTIC)
	{
		(PVRVert[Object]+i)->fUOverW = 0.5f + (fX + pV[2])/200.0f;
		(PVRVert[Object]+i)->fVOverW = 0.5f + (fY + pV[2])/200.0f;
	}

    if (Effect == FX_PLANAR)
	{
		(PVRVert[Object]+i)->fUOverW = 0.5f + fX/640.0f;
		(PVRVert[Object]+i)->fVOverW = 0.5f + fY/480.0f;
	}
	}
   
    VFog = (unsigned char) ((fZ*150.0f)/2000.0f) - 30;

	kmtri_triangles (	&VertexBufferDesc,				/* PKMVERTEXBUFFDESC */
						pStripHead,						/* PKMSTRIPHEAD		 */
						CMesh[Object].NumFaces,			/* int  nNumFaces	 */
						(int(*)[3])CMesh[Object].Faces,	/* int  pFaces[][3]	 */
						PVRVert[Object],				/* PPVRVERTEX		 */
						KM_TRUE							/* bTexture			 */
						);
}

/*----------------------------------------------------------------------* 
 *  Function Name   : SetUV                                             * 
 *  Inputs          : nFaces, Faces, pUV                                * 
 *  Outputs         :                                                   * 
 *  Returns         :                                                   * 
 *  Globals Used    :                                                   * 
 *  Description     :                                                   * 
 *----------------------------------------------------------------------*/
void SetUV (int Object)
{
	register i;

    for (i=0; i<CMesh[Object].NumVertex; i++)
	{
		(PVRVert[Object]+i)->fUOverW = *(CMesh[Object].UV++);
		(PVRVert[Object]+i)->fVOverW = *(CMesh[Object].UV++);
	}
}

/*----------------------------------------------------------------------* 
 *  Function Name   : SetSmoothShading                                  * 
 *  Inputs          : nFaces, Faces, nVertex, pNormals                  * 
 *  Outputs         :                                                   * 
 *  Returns         :                                                   * 
 *  Globals Used    :                                                   * 
 *  Description     :                                                   * 
 *----------------------------------------------------------------------*/
void SetSmoothShading (int Object, int Color)
{
	register				i, nNormal = 0;
	unsigned char			Col;
	static unsigned char	SpecVal[256] = { 0 };
	float					LightLocal[3], f1OverLength, fN[3];

   	LightLocal[0] = LightDir[0]*T[Object].Inverse[0][0] + LightDir[1]*T[Object].Inverse[0][1] + LightDir[2]*T[Object].Inverse[0][2];
	LightLocal[1] = LightDir[0]*T[Object].Inverse[1][0] + LightDir[1]*T[Object].Inverse[1][1] + LightDir[2]*T[Object].Inverse[1][2];
	LightLocal[2] = LightDir[0]*T[Object].Inverse[2][0] + LightDir[1]*T[Object].Inverse[2][1] + LightDir[2]*T[Object].Inverse[2][2];

	f1OverLength =  1.0f / (float) sqrt (LightLocal[0]*LightLocal[0] + 
										 LightLocal[1]*LightLocal[1] + 
										 LightLocal[2]*LightLocal[2]);

	LightLocal[0] *= f1OverLength;
	LightLocal[1] *= f1OverLength;
	LightLocal[2] *= f1OverLength;

	for (i=0; i<CMesh[Object].NumVertex; i++)
	{
		fN[0] = *(CMesh[Object].Normals+nNormal++);
		fN[1] = *(CMesh[Object].Normals+nNormal++);
		fN[2] = *(CMesh[Object].Normals+nNormal++);

		Col = (unsigned char) (127.0f * (fN[0]*LightLocal[0] + fN[1]*LightLocal[1] + fN[2]*LightLocal[2]+ 1.0f) );
     
		switch (Color)
		{
			case C_WHITE :  (PVRVert[Object]+i)->u32Colour = RGBAColour(Col,Col,Col, 150);
							break;
	        case C_BLACK :  (PVRVert[Object]+i)->u32Colour = RGBAColour(Col>>3,Col>>3,Col>>3, 128);
							break;
		    case C_GREY  :  (PVRVert[Object]+i)->u32Colour = RGBAColour(Col>>1,Col>>1,Col>>1, 128);
							break;
			case C_RED   :  (PVRVert[Object]+i)->u32Colour = RGBAColour(Col, 0, 0, 128);
							break;
			case C_GREEN :  (PVRVert[Object]+i)->u32Colour = RGBAColour(0, Col, 0, 128);
							break;
			case C_BLUE  :  (PVRVert[Object]+i)->u32Colour = RGBAColour(0, 0, Col, 128);
							break;
			case C_YELLOW:  (PVRVert[Object]+i)->u32Colour = RGBAColour(Col, Col, 0, 128);
							break;
			case C_BROWN :  (PVRVert[Object]+i)->u32Colour = RGBAColour(Col,Col>>1,Col>>2, 128);
							break;
			case C_PLAIN :  (PVRVert[Object]+i)->u32Specular  = RGBAColour(0,0,0, 0);
			                (PVRVert[Object]+i)->u32Colour = RGBAColour(255,255,255, 150);
							break;
		}
	}
}

/*----------------------------------------------------------------------* 
 *  Function Name   : EnviroMap                                         * 
 *  Inputs          : nFaces, Faces, pUV                                * 
 *  Outputs         :                                                   * 
 *  Returns         :                                                   * 
 *  Globals Used    :                                                   * 
 *  Description     :                                                   * 
 *----------------------------------------------------------------------*/
void EnviroMap (int nVertex, float *pVertex, PVRVERTEX *PvrVertex)
{
	register i;

    for (i=0; i<nVertex; i++)
	{
		(PvrVertex+i)->fUOverW = (PvrVertex+i)->fUOverW;/*(((float) atan2 (Vertices[k][2] - Centre[2], fX) + PI) * ONEOVERTWOPI) * fU; */
		(PvrVertex+i)->fVOverW = (PvrVertex+i)->fUOverW;/*(((float) atan2 (Vertices[k][1] - Centre[1], fX) + PI) * ONEOVERTWOPI) * fV; */
	}

}

/*----------------------------------------------------------------------* 
 *  Function Name   : SetGround                                         * 
 *  Inputs          :                                                   * 
 *  Outputs         :                                                   * 
 *  Returns         :                                                   * 
 *  Globals Used    :                                                   * 
 *  Description     : Draws the floor and moves it (just UV values).    * 
 *----------------------------------------------------------------------*/
void SetGround(PKMSTRIPHEAD pStripHead)
{
	extern	float Ang, PosX, PosY;

	/* extern int	TexGround; */
	KMSURFACEDESC	TexGround;

	PVRVERTEX	Vert[4];
	int			Face[1][4] = {0,1,2,3}, i;
	float		CosA, SinA, x;
	static		float Movement=0;
	float		Pnt[4][3] =  {{-5000.0f,  -140.0f, -100.0f},           
                    {-5000.0f,  40.0f, 8000.0f},
                    { 6000.0f,  40.0f, 8000.0f},
                    { 6000.0f,  -140.0f, -100.0f}};	


	CosA = (float)cos(Ang);
	SinA = (float)sin(Ang);

    for (i=0; i<4; i++)
	{
        Perspect (Pnt[i], &Vert[i]);                                 

        /* Set the colour for each vertex. */
        Vert[i].u32Colour   = RGBAColour (255,255,255, 255);    
        Vert[i].u32Specular = RGBAColour (255,255,255, 255);
		if (i==1||i==2)  Vert[i].u32Colour = RGBAColour (0,0,0,0);
   }

    /* Here the continous fluency of the ground.  */
    /* Note that I just move texture's UV values. */
    /* I don't move the camera.                   */
 
    /* Set UV values for each textured vertex. */
    Vert[0].fUOverW = -15.0f;  Vert[0].fVOverW = 0.0f;          
    Vert[1].fUOverW = -15.0f;  Vert[1].fVOverW =  10.0f;
    Vert[2].fUOverW =  15.0f;  Vert[2].fVOverW  = 10.0f;
    Vert[3].fUOverW =  15.0f;  Vert[3].fVOverW =  0.0f;

	PosX += (float)sin(Ang)/50.0f;
	for (i=0; i<4; i++)
	{
		x = Vert[i].fUOverW;
		Vert[i].fUOverW += PosX;
		Vert[i].fVOverW += PosY;
	}

	kmtri_quads (	&VertexBufferDesc,	/* PKMVERTEXBUFFDESC */
					pStripHead,			/* PKMSTRIPHEAD		 */
					1,					/* int  nNumFaces	 */
					Face,				/* int  pFaces[][3]	 */
					Vert,				/* PPVRVERTEX		 */
					KM_TRUE				/* bTexture			 */
					);
}

/*----------------------------------------------------------------------* 
 *  Function Name   : Perspect                                          * 
 *  Inputs          :                                                   * 
 *  Outputs         :                                                   * 
 *  Returns         :                                                   * 
 *  Globals Used    :                                                   *  
 *  Description     :                                                   * 
 *----------------------------------------------------------------------*/
void Perspect (const pvr_vector Point3D, PVRVERTEX *Vert)
{
	const pvr_vector CamPos = { 0.0, 40.0, 150.0};
	float x, y, z;

    x    =  Point3D[0] + CamPos[0];
    y    = -Point3D[1] + CamPos[1];
    z    = (Point3D[2] + CamPos[2]) ;

    Vert->fX    =  (800 * x) / z + 320;
    Vert->fY    =  (800 * y) / z + 240;

    /* The render uses fInvW (1/z) to set the Z-buffer */
    /* In this case I use it to set the fog effect as well */
     Vert->fInvW =  1.8f / z;                   
}

/*----------------------------------------------------------------------*
 *  Function Name   : Lightning                                         *
 *  Inputs          : TextureID                                         *
 *  Outputs         :                                                   *
 *  Returns         :                                                   *
 *  Globals Used    :                                                   *
 *  Description     : Especial Effect.                                  *
 *----------------------------------------------------------------------*/
void Lightning (PKMSTRIPHEAD pStripHead)
{
	extern	float PosX;
	extern	unsigned char BColor[3];
	PVRVERTEX Plane[4];
	int 	Quad[] = {0,1,2,3};
	extern	Frame;
	static	float Cont=20, PX, Size;

	if ((unsigned)(rand()%1000)<10)
	{
		PX = (float)(rand()%200)+200.0f;
		Cont=0.0f;
		Size=(rand()%200>100)?1.0f:-1.0f;
	}
	if (Cont++>10){return;}

    Plane[0].fX = 0.0f +PX;
	Plane[0].fY = 0.0f;
	Plane[0].fInvW = 1.0f/1000.0f;
	Plane[0].u32Colour =  RGBAColour(255, 255, 255, 255);
	Plane[0].fUOverW    =  0;
    Plane[0].fVOverW    =  1.0f; 
           

	Plane[1].fX = 150+PX;
	Plane[1].fY = 0.0f;
	Plane[1].fInvW = 1.0f/1000.0f;
	Plane[1].u32Colour =  RGBAColour(255, 255, 255,255);
	Plane[1].fUOverW    =  Size;
    Plane[1].fVOverW    =  1.0f; 

	Plane[2].fX = 380;
	Plane[2].fY = 340.0f;
	Plane[2].fInvW = 1.0f/1000.0f;
	Plane[2].u32Colour =  RGBAColour(255, 255, 255,255);
	Plane[2].fUOverW    =  Size;
    Plane[2].fVOverW    =  0; 

	Plane[3].fX = 250;
	Plane[3].fY = 340 ;
	Plane[3].fInvW = 1.0f/1000.0f;
	Plane[3].u32Colour = RGBAColour(255, 255, 255, 255);
	Plane[3].fUOverW    =  0;
    Plane[3].fVOverW    =  0; 

	kmtri_quads (	&VertexBufferDesc,	/* PKMVERTEXBUFFDESC */
					pStripHead,			/* PKMSTRIPHEAD		 */
					1,					/* int  nNumFaces	 */
					(int(*)[4])Quad,	/* int  pFaces[][3]	 */
					Plane,				/* PPVRVERTEX		 */
					KM_TRUE				/* bTexture			 */
					);
}

/*----------------------------------------------------------------------* 
 *  Function Name   : SetFogTable                                       * 
 *  Inputs          :                                                   * 
 *  Outputs         :                                                   * 
 *  Returns         :                                                   * 
 *  Globals Used    :                                                   * 
 *  Description     :                                                   * 
 *----------------------------------------------------------------------*/
void SetFogTable (KMDWORD FogDensity)
{
	int				i;
	KMPACKEDARGB	fogcol;
	KMFLOAT			FogTable[128];

	/* Fog Color */
	fogcol.byte.bBlue	= 0.5 * 255;
	fogcol.byte.bGreen	= 0.5 * 255;
	fogcol.byte.bRed	= 0.5 * 255;
	status = kmSetFogTableColor(fogcol);
	Check_Status(status, "kmSetFogTableColor");

	/* Fog Density */
	FogDensity = 0xFF0B;		/* FF09 - FF0D */
	status = kmSetFogDensity(FogDensity);
	Check_Status(status, "kmSetFogDensity");

	/* Fog Table */
	for(i = 0; i < 128; i++)
	{
		FogTable[i] = 1.0f - (float)i * ((1.0f - FOG_MIN) / 128.0f);
		if(FogTable[i] < 0.0f){ FogTable[i] = 0.0f;}
	}
	status = kmSetFogTable(&FogTable[0]);
	Check_Status(status, "kmSetFogTable");
}

/*----------------------------------------------------------------------* 
 *  Function Name   : SetContext                                        * 
 *  Inputs          : CInfo                                             * 
 *  Outputs         :                                                   * 
 *  Returns         :                                                   * 
 *  Globals Used    :                                                   * 
 *  Description     :                                                   * 
 *----------------------------------------------------------------------*/
void SetContext (PKMSTRIPHEAD pStripHead, INFO CInfo, PKMSURFACEDESC pTexture)
{
	if (CInfo.Bilinear)
	{
		kmChangeStripFilterMode	( pStripHead, KM_IMAGE_PARAM1, KM_BILINEAR );
	}
	else
	{
		kmChangeStripFilterMode	( pStripHead, KM_IMAGE_PARAM1, KM_POINT_SAMPLE );
	}

	if (CInfo.Textured)
	{
		if(CInfo.Gouraud)
		{
			kmChangeStripGouraud		( pStripHead, KM_TRUE );
			kmChangeStripTextureSurface	( pStripHead, KM_IMAGE_PARAM1, pTexture );
		}
		else
		{
			kmChangeStripGouraud		( pStripHead, KM_FALSE );
			kmChangeStripTextureSurface	( pStripHead, KM_IMAGE_PARAM1, pTexture );
		}
	}
	else
	{
		if(CInfo.Gouraud)
		{
			kmChangeStripGouraud( pStripHead, KM_TRUE );
		}
		else
		{
			kmChangeStripGouraud( pStripHead, KM_FALSE );
		}
	}

	kmChangeStripFlipUV( pStripHead, KM_IMAGE_PARAM1, KM_FLIP_UV );
}

/*---------------------- End Of File -----------------------------------*/
