/******************************************************************************
 Name     : Tools(KMMARBLE)
 Title    : KAMUI test program "Tools" from VL
 Author   : VideoLogic Carlos Sarria / NEC Software Takeshi Muto
 Created  : October 1997 by VideoLogic
 Modified : February  4. 1999 by T.Kamei 	  for KAMUI2
			February 16. 1999 by Takeshi Muto for Shinobi
 Description :
 Copyright : 1997 by VideoLogic Limited. All rights reserved.
******************************************************************************/
#if 0
#define		_VERTEXMACRO_L4_		/* VertexMacroLevel4使用時は定義する			*/
#endif

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

#include "soj_tool.h"

#if defined(_VERTEXMACRO_L4_)
#define _KM_USE_VERTEX_MACRO_L4_
#include "kamuix.h"
#endif

/* Globals */
static float	LightDir[3] = { -1.0f, 1.0f, -1.0f };
static unsigned	TotalPolys = 60;
static char		VFog = 0;

PVRVERTEX		*PVRVert[300];
PVRVERTEX		*PVRVert2[300];
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

extern	KMSTATUS			status;					/* return status of KAMUI API	*/
extern	KMVERTEXBUFFDESC	VertexBufferDesc;		/* Vertex-buffer				*/

extern	KMSYSTEMCONFIGSTRUCT	SystemConfig;
extern  KMTWOVOLUMESTRIPCONTEXT          StripContext11;
extern	KMSTRIPCONTEXT			StripContext17;
extern	KMSTRIPHEAD				StripHead11_01;
extern	KMSTRIPHEAD				StripHead11_02;
extern	KMSTRIPHEAD				StripHead17_first;
extern	KMSTRIPHEAD				StripHead17_normal;
extern	KMSTRIPHEAD				StripHead17_last;

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
	PPVRVERTEX		pVert;
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
		} /* end of if(bTexture == TRUE) */
	}

#if defined(_VERTEXMACRO_L4_)
	kmxxReleaseCurrentPtr(&VertexBufferDesc);
#endif

	kmEndStrip(pBufferDesc);
}

/****************************************************************************
 *	kmtri_triangles for 2 parameter : modifier volume variant
 ***************************************************************************/
void
kmtri_triangles2( PKMVERTEXBUFFDESC		pBufferDesc,
				  PKMSTRIPHEAD			pStripHead2Param,
				  int  					nNumFaces,
				  int  					pFaces[][3],
				  PPVRVERTEX  			pVertices )
{
	KMSTATUS		status;
	int				i;
	KMVERTEX_11		Ver11;				/* for Param2 Polygon	*/
	PPVRVERTEX		pVert00;

#if defined(_VERTEXMACRO_L4_)
	kmxxGetCurrentPtr(&VertexBufferDesc);
	kmxxStartStrip(pBufferDesc,pStripHead2Param);
#else
	kmStartStrip(pBufferDesc,pStripHead2Param);
#endif

	for(i = 0; i < nNumFaces; i++)
	{
#if defined(_VERTEXMACRO_L4_)
		kmxxSetVertex_11(	KM_VERTEXPARAM_NORMAL,
							pVertices[pFaces[i][0]].fX,
							pVertices[pFaces[i][0]].fY,
							pVertices[pFaces[i][0]].fInvW,
							pVertices[pFaces[i][0]].fUOverW,
							pVertices[pFaces[i][0]].fVOverW,
							pVertices[pFaces[i][0]].u32Colour,
							pVertices[pFaces[i][0]].u32Specular,
							pVertices[pFaces[i][0]].fUOverW,
							pVertices[pFaces[i][0]].fVOverW,
							pVertices[pFaces[i][0]].u32Colour,
							pVertices[pFaces[i][0]].u32Specular
						);

		kmxxSetVertex_11(	KM_VERTEXPARAM_NORMAL,
							pVertices[pFaces[i][1]].fX,
							pVertices[pFaces[i][1]].fY,
							pVertices[pFaces[i][1]].fInvW,
							pVertices[pFaces[i][1]].fUOverW,
							pVertices[pFaces[i][1]].fVOverW,
							pVertices[pFaces[i][1]].u32Colour,
							pVertices[pFaces[i][1]].u32Specular,
							pVertices[pFaces[i][1]].fUOverW,
							pVertices[pFaces[i][1]].fVOverW,
							pVertices[pFaces[i][1]].u32Colour,
							pVertices[pFaces[i][1]].u32Specular
						);

		kmxxSetVertex_11(	KM_VERTEXPARAM_ENDOFSTRIP,
							pVertices[pFaces[i][2]].fX,
							pVertices[pFaces[i][2]].fY,
							pVertices[pFaces[i][2]].fInvW,
							pVertices[pFaces[i][2]].fUOverW,
							pVertices[pFaces[i][2]].fVOverW,
							pVertices[pFaces[i][2]].u32Colour,
							pVertices[pFaces[i][2]].u32Specular,
							pVertices[pFaces[i][2]].fUOverW,
							pVertices[pFaces[i][2]].fVOverW,
							pVertices[pFaces[i][2]].u32Colour,
							pVertices[pFaces[i][2]].u32Specular
						);
#else
		Ver11.ParamControlWord		= KM_VERTEXPARAM_NORMAL;
		Ver11.fX					= pVertices[pFaces[i][0]].fX;
		Ver11.fY					= pVertices[pFaces[i][0]].fY;
		Ver11.u.fZ					= pVertices[pFaces[i][0]].fInvW;
		Ver11.fU0m					= pVertices[pFaces[i][0]].fUOverW;
		Ver11.fV0m					= pVertices[pFaces[i][0]].fVOverW;
		Ver11.uBaseRGB0m.dwPacked	= pVertices[pFaces[i][0]].u32Colour;
		Ver11.uOffsetRGB0m.dwPacked	= pVertices[pFaces[i][0]].u32Specular;
		Ver11.fU1m					= pVertices[pFaces[i][0]].fUOverW;
		Ver11.fV1m					= pVertices[pFaces[i][0]].fVOverW;
		Ver11.uBaseRGB1m.dwPacked	= pVertices[pFaces[i][0]].u32Colour;
		Ver11.uOffsetRGB1m.dwPacked	= pVertices[pFaces[i][0]].u32Specular;
		status = kmSetVertex(pBufferDesc,&Ver11,KM_VERTEXTYPE_11,sizeof(KMVERTEX_11) );
		Check_Status(status, "kmSetVertex");

		Ver11.ParamControlWord		= KM_VERTEXPARAM_NORMAL;
		Ver11.fX					= pVertices[pFaces[i][1]].fX;
		Ver11.fY					= pVertices[pFaces[i][1]].fY;
		Ver11.u.fZ					= pVertices[pFaces[i][1]].fInvW;
		Ver11.fU0m					= pVertices[pFaces[i][1]].fUOverW;
		Ver11.fV0m					= pVertices[pFaces[i][1]].fVOverW;
		Ver11.uBaseRGB0m.dwPacked	= pVertices[pFaces[i][1]].u32Colour;
		Ver11.uOffsetRGB0m.dwPacked	= pVertices[pFaces[i][1]].u32Specular;
		Ver11.fU1m					= pVertices[pFaces[i][1]].fUOverW;
		Ver11.fV1m					= pVertices[pFaces[i][1]].fVOverW;
		Ver11.uBaseRGB1m.dwPacked	= pVertices[pFaces[i][1]].u32Colour;
		Ver11.uOffsetRGB1m.dwPacked	= pVertices[pFaces[i][1]].u32Specular;
		status = kmSetVertex(pBufferDesc,&Ver11,KM_VERTEXTYPE_11,sizeof(KMVERTEX_11) );
		Check_Status(status, "kmSetVertex");

		Ver11.ParamControlWord		= KM_VERTEXPARAM_ENDOFSTRIP;
		Ver11.fX					= pVertices[pFaces[i][2]].fX;
		Ver11.fY					= pVertices[pFaces[i][2]].fY;
		Ver11.u.fZ					= pVertices[pFaces[i][2]].fInvW;
		Ver11.fU0m					= pVertices[pFaces[i][2]].fUOverW;
		Ver11.fV0m					= pVertices[pFaces[i][2]].fVOverW;
		Ver11.uBaseRGB0m.dwPacked	= pVertices[pFaces[i][2]].u32Colour;
		Ver11.uOffsetRGB0m.dwPacked	= pVertices[pFaces[i][2]].u32Specular;
		Ver11.fU1m					= pVertices[pFaces[i][2]].fUOverW;
		Ver11.fV1m					= pVertices[pFaces[i][2]].fVOverW;
		Ver11.uBaseRGB1m.dwPacked	= pVertices[pFaces[i][2]].u32Colour;
		Ver11.uOffsetRGB1m.dwPacked	= pVertices[pFaces[i][2]].u32Specular;
		status = kmSetVertex(pBufferDesc,&Ver11,KM_VERTEXTYPE_11,sizeof(KMVERTEX_11) );
		Check_Status(status, "kmSetVertex");
#endif
	}

#if defined(_VERTEXMACRO_L4_)
	kmxxReleaseCurrentPtr(&VertexBufferDesc);
#endif
	kmEndStrip(pBufferDesc);
}

/****************************************************************************
 *	kmtri_tstrips  by T.Muto
 ***************************************************************************/
void
kmtri_tstrips ( PKMVERTEXBUFFDESC	pBufferDesc,
				PKMSTRIPHEAD		pStripHead,
				int					nNumFaces,
				int					*StripLengths,
				PPVRVERTEX  		pVertices,
				int					bTexture)
{
	KMSTATUS	status;
	int			i, j, nstrip, nface;
	PPVRVERTEX	pVert;
	KMVERTEX_00		Ver00;				/* for NO-TEXTURE-GOURAUD	*/
	KMVERTEX_03		Ver03;				/* for TEXTURE-GOURAUD		*/

	i = 0;		/* vertex counter	*/
	nstrip = 0;	/* strip counter	*/
	nface = 0;	/* face counter		*/

	do {
#if defined(_VERTEXMACRO_L4_)
		kmxxGetCurrentPtr(&VertexBufferDesc);
		kmxxStartStrip(pBufferDesc,pStripHead);
#else
		kmStartStrip(pBufferDesc,pStripHead);
#endif
		/********************************
		 * Set non-last vertex of strip *
		 ********************************/
		for(j = 0; j < (StripLengths[nstrip] + 1); j++)
		{
			pVert = &pVertices[i];

			if(bTexture == TRUE)
			{
#if defined(_VERTEXMACRO_L4_)
				kmxxSetVertex_3(	KM_VERTEXPARAM_NORMAL,
									pVert->fX,
									pVert->fY,
									pVert->fInvW,
									pVert->fUOverW,
									pVert->fVOverW,
									pVert->u32Colour,
									pVert->u32Specular
								);
#else
				Ver03.ParamControlWord		= KM_VERTEXPARAM_NORMAL;
				Ver03.fX					= pVert->fX;
				Ver03.fY					= pVert->fY;
				Ver03.u.fZ					= pVert->fInvW;
				Ver03.fU					= pVert->fUOverW;
				Ver03.fV					= pVert->fVOverW;
				Ver03.uBaseRGB.dwPacked		= pVert->u32Colour;
				Ver03.uOffsetRGB.dwPacked	= pVert->u32Specular;
				status = kmSetVertex(pBufferDesc,&Ver03,KM_VERTEXTYPE_03,sizeof(KMVERTEX_03) );
				Check_Status(status, "kmSetVertex");
#endif
			}
			else
			{
#if defined(_VERTEXMACRO_L4_)
				kmxxSetVertex_0(	KM_VERTEXPARAM_NORMAL,
									pVert->fX,
									pVert->fY,
									pVert->fInvW,
									pVert->u32Colour
								);
#else
				Ver00.ParamControlWord	= KM_VERTEXPARAM_NORMAL;
				Ver00.fX				= pVert->fX;
				Ver00.fY				= pVert->fY;
				Ver00.u.fZ				= pVert->fInvW;
				Ver00.uBaseRGB.dwPacked	= pVert->u32Colour;
				status = kmSetVertex(pBufferDesc,&Ver00,KM_VERTEXTYPE_00,sizeof(KMVERTEX_00) );
				Check_Status(status, "kmSetVertex");
#endif
			}		/* End of if */

			i++;	/* vertex counter up */
		}	/* End of for */

		/****************************
		 * Set last vertex of strip *
		 ****************************/
		pVert = &pVertices[i];

		if(bTexture == TRUE)
		{
#if defined(_VERTEXMACRO_L4_)
				kmxxSetVertex_3(	KM_VERTEXPARAM_NORMAL,
									pVert->fX,
									pVert->fY,
									pVert->fInvW,
									pVert->fUOverW,
									pVert->fVOverW,
									pVert->u32Colour,
									pVert->u32Specular
								);
#else
			Ver03.ParamControlWord		= KM_VERTEXPARAM_ENDOFSTRIP;
			Ver03.fX					= pVert->fX;
			Ver03.fY					= pVert->fY;
			Ver03.u.fZ					= pVert->fInvW;
			Ver03.fU					= pVert->fUOverW;
			Ver03.fV					= pVert->fVOverW;
			Ver03.uBaseRGB.dwPacked		= pVert->u32Colour;
			Ver03.uOffsetRGB.dwPacked	= pVert->u32Specular;
			status = kmSetVertex(pBufferDesc,&Ver03,KM_VERTEXTYPE_03,sizeof(KMVERTEX_03) );
			Check_Status(status, "kmSetVertex");
#endif
		}
		else
		{
#if defined(_VERTEXMACRO_L4_)
			kmxxSetVertex_0(	KM_VERTEXPARAM_NORMAL,
								pVert->fX,
								pVert->fY,
								pVert->fInvW,
								pVert->u32Colour
							);
#else
			Ver00.ParamControlWord	= KM_VERTEXPARAM_NORMAL;
			Ver00.fX				= pVert->fX;
			Ver00.fY				= pVert->fY;
			Ver00.u.fZ				= pVert->fInvW;
			Ver00.uBaseRGB.dwPacked	= pVert->u32Colour;
			status = kmSetVertex(pBufferDesc,&Ver00,KM_VERTEXTYPE_00,sizeof(KMVERTEX_00) );
			Check_Status(status, "kmSetVertex");
#endif
		}	/* End of if */

#if defined(_VERTEXMACRO_L4_)
		kmxxReleaseCurrentPtr(&VertexBufferDesc);
#endif
		kmEndStrip(pBufferDesc);

		i++;							/* vertex counter up	*/
		nface += StripLengths[nstrip];	/* face count up		*/
		nstrip++;						/* next strip			*/
	} while(nface < nNumFaces);
}

/****************************************************************************
 *	kmtri_shadow
 ***************************************************************************/
void
kmtri_shadow (	PKMVERTEXBUFFDESC		pBufferDesc,
				PKMSTRIPHEAD			pStripHeadFirst,
				PKMSTRIPHEAD			pStripHeadNormal,
				PKMSTRIPHEAD			pStripHeadLast,
				int						nNumFaces,
				int						pFaces[][3],
				PPVRVERTEX				pVertices )
{
	KMSTATUS		status;
	int				i;
	KMVERTEX_17		Ver17;			/* for Modifier Volume	*/
	PPVRVERTEX		pVert00,pVert01,pVert02;

	/*---------------------------------------------------- First Polygon */
#if defined(_VERTEXMACRO_L4_)
		kmxxGetCurrentPtr(&VertexBufferDesc);
		kmxxStartStrip(pBufferDesc,pStripHeadFirst);
#else
		kmStartStrip(pBufferDesc,pStripHeadFirst);
#endif

	pVert00 = &pVertices[pFaces[0][0]];
	pVert01 = &pVertices[pFaces[0][1]];
	pVert02 = &pVertices[pFaces[0][2]];

#if defined(_VERTEXMACRO_L4_)
	kmxxSetVertex_17(	KM_VERTEXPARAM_ENDOFSTRIP,
						pVert00->fX,
						pVert00->fY,
						pVert00->fInvW,
						pVert01->fX,
						pVert01->fY,
						pVert01->fInvW,
						pVert02->fX,
						pVert02->fY,
						pVert02->fInvW
					);
#else
	Ver17.ParamControlWord		= KM_VERTEXPARAM_ENDOFSTRIP;
	Ver17.fAX					= pVert00->fX;
	Ver17.fAY					= pVert00->fY;
	Ver17.uA.fAInvW				= pVert00->fInvW;
	Ver17.fBX					= pVert01->fX;
	Ver17.fBY					= pVert01->fY;
	Ver17.uB.fBInvW				= pVert01->fInvW;
	Ver17.fCX					= pVert02->fX;
	Ver17.fCY					= pVert02->fY;
	Ver17.uC.fCInvW				= pVert02->fInvW;
	status = kmSetVertex(pBufferDesc,&Ver17,KM_VERTEXTYPE_17,sizeof(KMVERTEX_17) );
	Check_Status(status, "kmSetVertex");
#endif

#if defined(_VERTEXMACRO_L4_)
	kmxxReleaseCurrentPtr(&VertexBufferDesc);
#endif
	kmEndStrip(pBufferDesc);

	/*---------------------------------------------------- Normal Polygon */
#if defined(_VERTEXMACRO_L4_)
		kmxxGetCurrentPtr(&VertexBufferDesc);
		kmxxStartStrip(pBufferDesc,pStripHeadNormal);
#else
		kmStartStrip(pBufferDesc,pStripHeadNormal);
#endif

	for(i = 1; i < (nNumFaces - 1); i++)
	{
		pVert00 = &pVertices[pFaces[i][0]];
		pVert01 = &pVertices[pFaces[i][1]];
		pVert02 = &pVertices[pFaces[i][2]];

#if defined(_VERTEXMACRO_L4_)
	kmxxSetVertex_17(	KM_VERTEXPARAM_ENDOFSTRIP,
						pVert00->fX,
						pVert00->fY,
						pVert00->fInvW,
						pVert01->fX,
						pVert01->fY,
						pVert01->fInvW,
						pVert02->fX,
						pVert02->fY,
						pVert02->fInvW
					);
#else
		Ver17.ParamControlWord		= KM_VERTEXPARAM_ENDOFSTRIP;
		Ver17.fAX					= pVert00->fX;
		Ver17.fAY					= pVert00->fY;
		Ver17.uA.fAInvW				= pVert00->fInvW;
		Ver17.fBX					= pVert01->fX;
		Ver17.fBY					= pVert01->fY;
		Ver17.uB.fBInvW				= pVert01->fInvW;
		Ver17.fCX					= pVert02->fX;
		Ver17.fCY					= pVert02->fY;
		Ver17.uC.fCInvW				= pVert02->fInvW;
		status = kmSetVertex(pBufferDesc,&Ver17,KM_VERTEXTYPE_17,sizeof(KMVERTEX_17) );
		Check_Status(status, "kmSetVertex");
#endif
	}

#if defined(_VERTEXMACRO_L4_)
	kmxxReleaseCurrentPtr(&VertexBufferDesc);
#endif
	kmEndStrip(pBufferDesc);

	/*---------------------------------------------------- Last Polygon */
#if defined(_VERTEXMACRO_L4_)
		kmxxGetCurrentPtr(&VertexBufferDesc);
		kmxxStartStrip(pBufferDesc,pStripHeadLast);
#else
		kmStartStrip(pBufferDesc,pStripHeadLast);
#endif

	pVert00 = &pVertices[pFaces[(nNumFaces - 1)][0]];
	pVert01 = &pVertices[pFaces[(nNumFaces - 1)][1]];
	pVert02 = &pVertices[pFaces[(nNumFaces - 1)][2]];

#if defined(_VERTEXMACRO_L4_)
	kmxxSetVertex_17(	KM_VERTEXPARAM_ENDOFSTRIP,
						pVert00->fX,
						pVert00->fY,
						pVert00->fInvW,
						pVert01->fX,
						pVert01->fY,
						pVert01->fInvW,
						pVert02->fX,
						pVert02->fY,
						pVert02->fInvW
					);
#else
	Ver17.ParamControlWord		= KM_VERTEXPARAM_ENDOFSTRIP;
	Ver17.fAX					= pVert00->fX;
	Ver17.fAY					= pVert00->fY;
	Ver17.uA.fAInvW				= pVert00->fInvW;
	Ver17.fBX					= pVert01->fX;
	Ver17.fBY					= pVert01->fY;
	Ver17.uB.fBInvW				= pVert01->fInvW;
	Ver17.fCX					= pVert02->fX;
	Ver17.fCY					= pVert02->fY;
	Ver17.uC.fCInvW				= pVert02->fInvW;
	status = kmSetVertex(pBufferDesc,&Ver17,KM_VERTEXTYPE_17,sizeof(KMVERTEX_17) );
	Check_Status(status, "kmSetVertex");
#endif

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
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFogMode			= KM_NOFOG;
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
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFogMode				= KM_NOFOG;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bColorClamp			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bUseAlpha				= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bIgnoreTextureAlpha		= KM_FALSE;
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
 *	VertexType11用KMSTRIPHEADの構築
 ***************************************/
void	InitStripContext11(
                                PKMTWOVOLUMESTRIPCONTEXT pStripContext,
								PKMSTRIPHEAD	pStripHead,
								PKMSURFACEDESC	pTextureDesc1,
								PKMSURFACEDESC	pTextureDesc2
)
{
	pStripContext->nSize 												= sizeof(KMTWOVOLUMESTRIPCONTEXT);
	pStripContext->StripControl.nListType		 						= KM_OPAQUE_POLYGON;
	pStripContext->StripControl.nUserClipMode	 						= KM_USERCLIP_DISABLE;
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
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFogMode				= KM_NOFOG;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bColorClamp			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bUseAlpha				= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bIgnoreTextureAlpha		= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFlipUV				= KM_NOFLIP;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nClampUV				= KM_NOCLAMP;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFilterMode			= KM_POINT_SAMPLE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bSuperSampleMode		= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].dwMipmapAdjust			= KM_MIPMAP_D_ADJUST_1_00;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nTextureShadingMode	= KM_MODULATE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].pTextureSurfaceDesc	= pTextureDesc1;

	pStripContext->ImageControl[KM_IMAGE_PARAM2].nSRCBlendingMode		= KM_ONE;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].nDSTBlendingMode		= KM_ZERO;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].bSRCSelect				= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].bDSTSelect				= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].nFogMode				= KM_NOFOG;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].bColorClamp			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].bUseAlpha				= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].bIgnoreTextureAlpha		= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].nFlipUV				= KM_NOFLIP;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].nClampUV				= KM_NOCLAMP;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].nFilterMode			= KM_POINT_SAMPLE;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].bSuperSampleMode		= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].dwMipmapAdjust			= KM_MIPMAP_D_ADJUST_1_00;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].nTextureShadingMode	= KM_MODULATE;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].pTextureSurfaceDesc	= pTextureDesc2;

    kmGenerateStripHead11( pStripHead, (PKMSTRIPCONTEXT) pStripContext );
}

/***************************************
 *	VertexType17用KMSTRIPHEADの構築
 ***************************************/
void	InitStripContext17(
								PKMSTRIPCONTEXT pStripContext,
								PKMSTRIPHEAD	pStripHead
)
{
	pStripContext->nSize = sizeof(KMSTRIPCONTEXT);
	pStripContext->StripControl.nListType							= KM_OPAQUE_MODIFIER;
	pStripContext->StripControl.nUserClipMode						= KM_USERCLIP_DISABLE;
	pStripContext->ObjectControl.nCullingMode						= KM_NOCULLING;
	pStripContext->ObjectControl.dwModifierInstruction				= KM_MODIFIER_NORMAL_POLY;

	kmGenerateStripHead17( pStripHead,pStripContext );
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
 *  Description     : Draw a object      L                              *
 *----------------------------------------------------------------------*/
void InitScene (void)
{
	kmBeginScene(&SystemConfig);
	kmBeginPass	(&VertexBufferDesc);
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
	/* Write FPS on screen -----------------------------------------------------*/
	PRINTOUT(("FRAME:%06d%06d Now:%07.3fFPS, Ave:%07.3fFPS\n",frame_2, frame,nFPS,aFPS));
#else
	PRINTOUT(("FRAME:%06d%06d\n",frame_2, frame));
#endif

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

	totalTime += nowTime;							/* 累積時間 		*/
	aveTime = totalTime / ((double)frame + 1.0f);	/* 今までの平均時間 */

	nFPS  = 1000.0f / (double)nowTime;
	aFPS  = 1000.0f / (double)aveTime;
	MxFPS = 1000.0f / (double)minTime;
	MnFPS = 1000.0f / (double)maxTime;
#endif

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
	int		 mptr = 0x0c400000;

	/* Memory allocation for Vert, UV values and SmoothShading*/
    for (i=0; i<nMeshes; i++)
	{
        memcpy ( &CMesh[i], &pMeshes[i], sizeof (CASTMESHES) );
#if 0
		PVRVert[i] = (PVRVERTEX *) mptr; mptr += (CMesh[i].NumVertex*sizeof(PVRVERTEX));
#else
		PVRVert[i] = (PVRVERTEX *)(((KMDWORD)syMalloc(CMesh[i].NumVertex*sizeof(PVRVERTEX)) & 0x0FFFFFFFUL) | 0xA0000000);
#endif
		ResetMatrix (i);
		SetUV (i);
		SetSmoothShading (i, C_GREY);
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
 *  Inputs          : Object Texture Effect                             *
 *  Outputs         :                                                   *
 *  Returns         :                                                   *
 *  Globals Used    : CMesh Vert                                        *
 *  Description     : Calculates vertices projections and               *
 *                    sends a set of triangles for render.              *
 *----------------------------------------------------------------------*/
void SetVertices (int Object, PKMSTRIPHEAD pStripHead, int Effect )
{
	extern float	Frame;
	register		i, nVertex = 0;
	float			fX, fY, fZ, pV[3], f1OverZ;
	float			CamFocus = 600.0f;

    if (Frame>0){ goto NoTransform;}

    for (i=0; i<CMesh[Object].NumVertex; i++)
	{
		pV[0] = *(CMesh[Object].Vertex+nVertex++);
		pV[1] = *(CMesh[Object].Vertex+nVertex++);
		pV[2] = *(CMesh[Object].Vertex+nVertex++);

		fX = (pV[0] * T[Object].Matrix[0][0] + pV[1] * T[Object].Matrix[0][1] + pV[2] * T[Object].Matrix[0][2] + T[Object].Matrix[0][3]);
		fY = (pV[0] * T[Object].Matrix[1][0] + pV[1] * T[Object].Matrix[1][1] + pV[2] * T[Object].Matrix[1][2] + T[Object].Matrix[1][3]);
		fZ = (pV[0] * T[Object].Matrix[2][0] + pV[1] * T[Object].Matrix[2][1] + pV[2] * T[Object].Matrix[2][2] + T[Object].Matrix[2][3]);

		fZ += Z_ZERO;

		if (fZ<0.00001f){ fZ = 0.00001f;}

		f1OverZ = 1.0f / fZ;

		(PVRVert[Object]+i)->fX = f1OverZ * fX * 600.0f + 320;
		(PVRVert[Object]+i)->fY = -f1OverZ * fY* 600.0f + 240;
	    (PVRVert[Object]+i)->fInvW = f1OverZ;
	}

NoTransform:
	kmtri_triangles2( &VertexBufferDesc,				/* PKMVERTEXBUFFDESC	*/
					  pStripHead,						/* PKMSTRIPHEAD			*/
					  CMesh[Object].NumFaces,			/* int nNumFaces,		*/
					  (int(*)[3])CMesh[Object].Faces,	/* int pFaces[][3],		*/
					  PVRVert[Object]					/* PPVRVERTEX pVertices,*/
					  );
}

/*----------------------------------------------------------------------*
 *  Function Name   : SetShadowVol                                      *
 *  Inputs          :                                                   *
 *  Outputs         :                                                   *
 *  Returns         :                                                   *
 *  Globals Used    : CMesh Vert	                                    *
 *  Description     : Calculates vertices projections and               *
 *                    sends a set of triangles for a shadow volume.     *
 *----------------------------------------------------------------------*/
void SetShadowVol (	void )
{
	register	i, nVertex = 0;
	float		fX, fY, fZ, pV[3], f1OverZ;
	float		CamFocus = 600.0f;
	int			Object = 7;

    for (i=0; i<CMesh[Object].NumVertex; i++)
	{
		pV[0] = *(CMesh[Object].Vertex+nVertex++);
		pV[1] = *(CMesh[Object].Vertex+nVertex++);
		pV[2] = *(CMesh[Object].Vertex+nVertex++);

		fX = (pV[0] * T[Object].Matrix[0][0] + pV[1] * T[Object].Matrix[0][1] + pV[2] * T[Object].Matrix[0][2] + T[Object].Matrix[0][3]);
		fY = (pV[0] * T[Object].Matrix[1][0] + pV[1] * T[Object].Matrix[1][1] + pV[2] * T[Object].Matrix[1][2] + T[Object].Matrix[1][3]);
		fZ = (pV[0] * T[Object].Matrix[2][0] + pV[1] * T[Object].Matrix[2][1] + pV[2] * T[Object].Matrix[2][2] + T[Object].Matrix[2][3]);

		fZ += Z_ZERO;

		if (fZ<0.00001f){ fZ = 0.00001f;}

		f1OverZ = 1.0f / fZ;

		(PVRVert[Object]+i)->fX = f1OverZ * fX * 600.0f + 320;
		(PVRVert[Object]+i)->fY = -f1OverZ * fY * 600.0f + 240;
	    (PVRVert[Object]+i)->fInvW = f1OverZ;
	}

	kmtri_shadow (	&VertexBufferDesc,				/* PKMVERTEXBUFFDESC	*/
					&StripHead17_first,				/* PKMSTRIPCONTEXT		*/
					&StripHead17_normal,			/* PKMSTRIPCONTEXT		*/
					&StripHead17_last,				/* PKMSTRIPCONTEXT		*/
					CMesh[Object].NumFaces,			/* int	nNumFaces, 		*/
					(int(*)[3])CMesh[Object].Faces,	/* int	pFaces[][3],	*/
					PVRVert[Object]					/* PPVRVERTEX pVertices */
					);
}

/*----------------------------------------------------------------------*
 *  Function Name   : SetUV                                             *
 *  Inputs          : Object                                            *
 *  Outputs         :                                                   *
 *  Returns         :                                                   *
 *  Globals Used    : Vertex, CMesh                                     *
 *  Description     : Copy UV values from CMesh to Vert                 *
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
 *  Inputs          : Object, Color                                     *
 *  Outputs         :                                                   *
 *  Returns         :                                                   *
 *  Globals Used    : CMesh Vert                                        *
 *  Description     : Calculates the color for each vertex.             *
 *----------------------------------------------------------------------*/
void SetSmoothShading (int Object, int Color)
{
	extern float	Frame;
	register		i, nNormal = 0;
	unsigned char	Col,Spec;
	static unsigned char SpecVal[256] = { 0 };
	float 			LightLocal[3], f1OverLength, fN[3];

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

		Spec =(((Col>200) ? (Col-200)*2 : 0));

		/* Setting vertex colour */
		/* Specular RGB is Highlight Color, Specular A is Vertexfog */
		(PVRVert[Object]+i)->u32Specular  = RGBAColour(Spec, Spec, Spec,  VFog);

		switch (Color)
		{
			case C_WHITE :  (PVRVert[Object]+i)->u32Colour = RGBAColour(Col,Col,Col, 128);
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
		}
	}
}

/*----------------------------------------------------------------------*
 *  Function Name   : 3DPrint                                           *
 *  Inputs          : nFaces, Faces, pUV                                *
 *  Outputs         :                                                   *
 *  Returns         :                                                   *
 *  Globals Used    :                                                   *
 *  Description     :                                                   *
 *----------------------------------------------------------------------*/
void Print3D (float PosX, float PosY, float Size, char *Text)
{
}

/*----------------------------------------------------------------------*
 *  Function Name   : Shadow                                            *
 *  Inputs          :                                                   *
 *  Outputs         :                                                   *
 *  Returns         :                                                   *
 *  Globals Used    : Context                                           *
 *  Description     : Draws 7 shadow volumes.                           *
 *----------------------------------------------------------------------*/
void Shadow (void)
{
	register		i;
	extern float	Frame;
	static float	FF=0;
	float 			Yaxis[3]  = { 0.0f, 1.0f, 0.0f }, AngS;

    AngS = (float)sin(Frame/60.0f)*PI/4.2f-PI;

	LightDir[2] = (float)cos(AngS);
	LightDir[0] = (float)sin(AngS);
	LightDir[1] = 0;

	for (i=0; i<6; i++)
	{
		ResetMatrix  (7);
		Translate    (7, CMesh[i].Center[0], 0,  CMesh[i].Center[2]);
		Rotate       (7, Yaxis, PI/2 + AngS);

		SetShadowVol ();
	}
}

/*----------------------------------------------------------------------*
 *  Function Name   : InitContext                                       *
 *  Inputs          : CInfo                                             *
 *  Outputs         :                                                   *
 *  Returns         :                                                   *
 *  Globals Used    :                                                   *
 *  Description     :                                                   *
 *----------------------------------------------------------------------*/
void InitContext (PKMSTRIPHEAD pStripHead, INFO CInfo, PKMSURFACEDESC pTexture)
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
		kmChangeStripFlipUV	( pStripHead, KM_IMAGE_PARAM1, KM_FLIP_UV );
	}
	else
	{
		if(CInfo.Gouraud)
		{
			kmChangeStripGouraud		( pStripHead, KM_TRUE );
		}
		else
		{
			kmChangeStripGouraud		( pStripHead, KM_FALSE );
		}
	}
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
		kmChangeStripFilterMode	( pStripHead, KM_IMAGE_PARAM2, KM_BILINEAR );
	}
	else
	{
		kmChangeStripFilterMode	( pStripHead, KM_IMAGE_PARAM2, KM_POINT_SAMPLE );
	}

	if (CInfo.Textured)
	{
		if(CInfo.Gouraud)
		{
			kmChangeStripGouraud		( pStripHead, KM_TRUE );
			kmChangeStripTextureSurface	( pStripHead, KM_IMAGE_PARAM2, pTexture );
		}
		else
		{
			kmChangeStripGouraud		( pStripHead, KM_FALSE );
			kmChangeStripTextureSurface	( pStripHead, KM_IMAGE_PARAM2, pTexture );
		}
	}
	else
	{
		if(CInfo.Gouraud)
		{
			kmChangeStripGouraud		( pStripHead, KM_TRUE );
		}
		else
		{
			kmChangeStripGouraud		( pStripHead, KM_FALSE );
		}
	}
}

/*---------------------- End Of File -----------------------------------*/