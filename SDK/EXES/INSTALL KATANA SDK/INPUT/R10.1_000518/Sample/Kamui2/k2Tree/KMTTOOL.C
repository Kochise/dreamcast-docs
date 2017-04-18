/*----------------------------------------------------------------------*/
/*   Name   : Tools.c   (Some tools for Arc1a)                          */
/*   Author : Carlos Sarria (Matrix code is Jim's)                      */
/*   Date   : October 1997                                              */
/*                                                                      */
/*   Copyright : 1997 by VideoLogic Limited. All rights reserved.       */
/*	 Modified  :	February 04. 1999 by Hiroshi Nakayama	for KAMUI2	*/
/*					February 16. 1999 by Takeshi Muto for Shinobi		*/
/*----------------------------------------------------------------------*/

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

#include "kmttool.h"

static float	LightDir[3] = { -1.0f, 1.0f, -1.0f };
unsigned		TotalPolys = 0;
unsigned char	VFog = 0;

PVRVERTEX		*PVRVert[256];
CASTMESHES		CMesh[256];
TRANSFORM		T[256];

/***********************************************************************/
/* Kamui Val.s *********************************************************/
/***********************************************************************/
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

extern	KMSTATUS			status;					/* return status of KAMUI API */
extern	KMVERTEXBUFFDESC	VertexBufferDesc;		/* Vertex-buffer */
extern	KMVERTEXCONTEXT		VertexContext;			/* Vertex context */
extern	KMSYSTEMCONFIGSTRUCT	SystemConfig;

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
/**	kmtri_triangles  by T.Hirata ********************************************/
/****************************************************************************/
void
kmtri_triangles ( PKMVERTEXBUFFDESC		pBufferDesc,
				  PKMSTRIPHEAD			pStripHead,
				  int  					nNumFaces,
				  int  					pFaces[][3],
				  PPVRVERTEX  			pVertices,
				  int					bTexture)
{
	KMSTATUS	status;
	int			i;
	KMVERTEX_01	Ver01;				/* for NO-TEXTURE-GOURAUD */
	KMVERTEX_03	Ver03;				/* for TEXTURE-GOURAUD */

	if(bTexture == TRUE)
	{
		kmStartStrip(pBufferDesc,pStripHead+1);
	}
	else
	{
		kmStartStrip(pBufferDesc,pStripHead);
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
			status = kmSetVertex(pBufferDesc,&Ver03,KM_VERTEXTYPE_03,sizeof(KMVERTEX_03) );
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
			status = kmSetVertex(pBufferDesc,&Ver03,KM_VERTEXTYPE_03,sizeof(KMVERTEX_03) );
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
			status = kmSetVertex(pBufferDesc,&Ver03,KM_VERTEXTYPE_03,sizeof(KMVERTEX_03) );
			Check_Status(status, "kmSetVertex");
		}
		else
		{	/* if(bTexture == TRUE) : NO-TEXTURE */
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
			status = kmSetVertex(pBufferDesc,&Ver01,KM_VERTEXTYPE_01,sizeof(KMVERTEX_01) );
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
			status = kmSetVertex(pBufferDesc,&Ver01,KM_VERTEXTYPE_01,sizeof(KMVERTEX_01) );
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
			status = kmSetVertex(pBufferDesc,&Ver01,KM_VERTEXTYPE_01,sizeof(KMVERTEX_01) );
			Check_Status(status, "kmSetVertex");
		} /* end of if(bTexture == TRUE) */
	}
	kmEndStrip(pBufferDesc);
}

/****************************************************************************/
/**	kmtri_tstrips  by T.Muto ************************************************/
/****************************************************************************/
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
	KMVERTEX_01	Ver01;				/* for NO-TEXTURE-GOURAUD */
	KMVERTEX_03	Ver03;				/* for TEXTURE-GOURAUD */

	if(bTexture == TRUE)
	{
		kmStartStrip(pBufferDesc,pStripHead+1);
	}
	else
	{
		kmStartStrip(pBufferDesc,pStripHead);
	}

	i = 0;	/* vertex counter */
	nstrip = 0;	/* strip counter */
	nface = 0;	/* face counter */
	do
	{
		/********************************/
		/* Set non-last vertex of strip */
		/********************************/
		for(j = 0; j < (StripLengths[nstrip] + 1); j++)
		{
			if(bTexture == TRUE)
			{
				Ver03.ParamControlWord		= KM_VERTEXPARAM_NORMAL;
				Ver03.fX					= pVertices[i].fX;
				Ver03.fY					= pVertices[i].fY;
#if defined(_STRICT_UNION_)
				Ver03.u.fZ					= pVertices[i].fInvW;
#else
				Ver03.fZ					= pVertices[i].fInvW;
#endif
				Ver03.fU					= pVertices[i].fUOverW;
				Ver03.fV					= pVertices[i].fVOverW;
				Ver03.uBaseRGB.dwPacked		= pVertices[i].u32Colour;
				Ver03.uOffsetRGB.dwPacked	= pVertices[i].u32Specular;
				status = kmSetVertex(pBufferDesc,&Ver03,KM_VERTEXTYPE_03,sizeof(KMVERTEX_03) );
				Check_Status(status, "kmSetVertex");
			}
			else
			{	/* if(bTexture == TRUE) : NO-TEXTURE */
				Ver01.ParamControlWord	= KM_VERTEXPARAM_NORMAL;
				Ver01.fX				= pVertices[i].fX;
				Ver01.fY				= pVertices[i].fY;
#if defined(_STRICT_UNION_)
				Ver01.u.fZ				= pVertices[i].fInvW;
#else
				Ver01.fZ				= pVertices[i].fInvW;
#endif
				Ver01.fBaseAlpha		= GetALPHA(pVertices[i].u32Colour);
				Ver01.fBaseRed			= GetRED  (pVertices[i].u32Colour);
				Ver01.fBaseGreen		= GetGREEN(pVertices[i].u32Colour);
				Ver01.fBaseBlue			= GetBLUE (pVertices[i].u32Colour);
				status = kmSetVertex(pBufferDesc,&Ver01,KM_VERTEXTYPE_01,sizeof(KMVERTEX_01) );
				Check_Status(status, "kmSetVertex");
			}		/* End of if */
			i++;	/* vertex counter up */
		}	/* End of for */

		/****************************/
		/* Set last vertex of strip */
		/****************************/
		if(bTexture == TRUE)
		{
			Ver03.ParamControlWord		= KM_VERTEXPARAM_ENDOFSTRIP;
			Ver03.fX					= pVertices[i].fX;
			Ver03.fY					= pVertices[i].fY;
#if defined(_STRICT_UNION_)
			Ver03.u.fZ					= pVertices[i].fInvW;
#else
			Ver03.fZ					= pVertices[i].fInvW;
#endif
			Ver03.fU					= pVertices[i].fUOverW;
			Ver03.fV					= pVertices[i].fVOverW;
			Ver03.uBaseRGB.dwPacked		= pVertices[i].u32Colour;
			Ver03.uOffsetRGB.dwPacked	= pVertices[i].u32Specular;
			status = kmSetVertex(pBufferDesc,&Ver03,KM_VERTEXTYPE_03,sizeof(KMVERTEX_03) );
			Check_Status(status, "kmSetVertex");
		}
		else
		{	/* if(bTexture == TRUE) : NO-TEXTURE */
			Ver01.ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;
			Ver01.fX				= pVertices[i].fX;
			Ver01.fY				= pVertices[i].fY;
#if defined(_STRICT_UNION_)
			Ver01.u.fZ				= pVertices[i].fInvW;
#else
			Ver01.fZ				= pVertices[i].fInvW;
#endif
			Ver01.fBaseAlpha		= GetALPHA(pVertices[i].u32Colour);
			Ver01.fBaseRed			= GetRED  (pVertices[i].u32Colour);
			Ver01.fBaseGreen		= GetGREEN(pVertices[i].u32Colour);
			Ver01.fBaseBlue			= GetBLUE (pVertices[i].u32Colour);
			status = kmSetVertex(pBufferDesc,&Ver01,KM_VERTEXTYPE_01,sizeof(KMVERTEX_01) );
			Check_Status(status, "kmSetVertex");
		}			/* End of if */
		i++;		/* vertex counter up */
		nface += StripLengths[nstrip];	/* face count up */
		nstrip++;	/* next strip */
	} while(nface < nNumFaces);
	kmEndStrip(pBufferDesc);
}

/***************************************
 *	VertexType01用KMSTRIPHEADの構築
 ***************************************/
void	InitStripContext01(
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

/***************************************
 *	VertexType03用KMSTRIPHEADの構築
 ***************************************/
void	InitStripContext03(
								PKMSTRIPCONTEXT pStripContext,
								PKMSTRIPHEAD	pStripHead,
								PKMSURFACEDESC	pTextureDesc
)
{
	pStripContext->nSize						 					= sizeof(KMSTRIPCONTEXT);
	pStripContext->StripControl.nListType		 					= KM_OPAQUE_POLYGON;
	pStripContext->StripControl.nUserClipMode	 					= KM_USERCLIP_DISABLE;
	pStripContext->StripControl.nShadowMode		 					= KM_NORMAL_POLYGON;
	pStripContext->StripControl.bOffset								= KM_FALSE;
	pStripContext->StripControl.bGouraud		 					= KM_TRUE;
	pStripContext->ObjectControl.nDepthCompare			 			= KM_GREATER;
	pStripContext->ObjectControl.nCullingMode			 			= KM_NOCULLING;
	pStripContext->ObjectControl.bZWriteDisable						= KM_FALSE;
	pStripContext->ObjectControl.bDCalcControl			 			= KM_FALSE;
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
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFilterMode		= KM_POINT_SAMPLE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bSuperSampleMode	= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].dwMipmapAdjust		= KM_MIPMAP_D_ADJUST_1_00;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nTextureShadingMode= KM_MODULATE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].pTextureSurfaceDesc= pTextureDesc;

	kmGenerateStripHead03( pStripHead,pStripContext );
}

/*--------------------------------------------------------------------*/
/*  Function Name   : ResetMatrix                                     */
/*  Inputs          : Object                                          */
/*  Outputs         :                                                 */
/*  Returns         :                                                 */
/*  Globals Used    :                                                 */
/*  Description     : Builds an identity matrix and stores it in T    */
/*--------------------------------------------------------------------*/
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
/*----------------------------------------------------------------------*/
/*  Function Name   :  Rotate                                           */
/*  Inputs          :  Object, Axis, Theta                              */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     :  Rotate T an angle Theta around Axis              */
/*----------------------------------------------------------------------*/
void Rotate (int Object, float Axis[3], float Theta)
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

/*----------------------------------------------------------------------*/
/*  Function Name   : Translate                                         */
/*  Inputs          : Object, Tr                                        */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     : Translate T using Tr(x,y,z) displacement.         */
/*----------------------------------------------------------------------*/
void Translate (int Object, float TrX, float TrY, float TrZ)
{
	T[Object].Matrix[0][3] += T[Object].Matrix[0][0] * TrX + T[Object].Matrix[0][1] * TrY + T[Object].Matrix[0][2] * TrZ;	
	T[Object].Matrix[1][3] += T[Object].Matrix[1][0] * TrX + T[Object].Matrix[1][1] * TrY + T[Object].Matrix[1][2] * TrZ;	
	T[Object].Matrix[2][3] += T[Object].Matrix[2][0] * TrX + T[Object].Matrix[2][1] * TrY + T[Object].Matrix[2][2] * TrZ;	

	T[Object].Inverse[0][3] -= TrX;	
	T[Object].Inverse[1][3] -= TrY;	
	T[Object].Inverse[2][3] -= TrZ;	
}
/*----------------------------------------------------------------------*/
/*  Function Name   : InitScene                                         */
/*  Inputs          :                                                   */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     : Draw a object                                     */
/*----------------------------------------------------------------------*/
void InitScene (void)
{
	/* シ－ンの開始 */
	kmBeginScene(&SystemConfig);

	/* パスの開始 */
	kmBeginPass(&VertexBufferDesc);
}
/*----------------------------------------------------------------------*/
/*  Function Name   : EndScene                                          */
/*  Inputs          :                                                   */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     : Draw a object                                     */
/*----------------------------------------------------------------------*/
void EndScene (void)
{

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
	status = kmRender(KM_RENDER_FLIP);
/*	Check_Status(status, "kmRender");*/

	/* シ－ンの終了 */
	kmEndScene(&SystemConfig);

#if defined(_DISP_PERFORMANCE_)
/* 性能計算 ------------------------------------------------------------------*/
	EndTime	= syTmrGetCount();
	/* ただいまのフレームを作成するのにかかった時間 */
	nowTime = syTmrCountToMicro( syTmrDiffCount( StartTime, EndTime ) ) / 1000.0f;
	StartTime = EndTime;

	/* 得られた値が異常であった場合は無視 */
	if((nowTime > 1000.0f)||(nowTime < 1.0f)){nowTime = 20.0f;}
	if(nowTime > maxTime){maxTime = nowTime;}		/* もっとも時間がかかった？ */
	if(nowTime < minTime){minTime = nowTime;}		/* もっとも早かった？ */

	totalTime += nowTime;							/* 累積時間 */
	aveTime = totalTime / ((double)frame + 1.0f);	/* 今までの平均時間 */

	nFPS  = 1000.0f / (double)nowTime;
	aFPS  = 1000.0f / (double)aveTime;
	MxFPS = 1000.0f / (double)minTime;
	MnFPS = 1000.0f / (double)maxTime;
#endif	/* defined(_DISP_PERFORMANCE_) */

	frame++;
	if(frame > 1000000)
	{							/* フレームのリセット */
		frame = 0;
#if defined(_DISP_PERFORMANCE_)
		totalTime = 0;
#endif	/* defined(_DISP_PERFORMANCE_) */
		frame_2++;
	}
}

/*----------------------------------------------------------------------*/
/*  Function Name   : InitMeshes                                        */
/*  Inputs          :                                                   */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     : Draw a object                                     */
/*----------------------------------------------------------------------*/
void InitMeshes (int nMeshes, CASTMESHES *pMeshes)
{
register i;
float TempVert[3];
/* SET4 / SET5 */
int mptr = 0x0c400000;

	/*(CASTMESHES *) CMesh = pMeshes; */

	/* Memory allocation for PVRVert, UV values and SmoothShading*/
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
		SetSmoothShading (i, C_NONE);
		TotalPolys += CMesh[i].NumFaces;
	}

	/*
	 *  In this case we need to swap values between vertex 0 and vertex 1 of each strip
	 *  to get the correct order.
	 */

	for (i=0; i<CMesh[1].NumVertex / 4; i++)
	{
		TempVert[0] =  *(CMesh[1].Vertex+ i*4*3 + 3);
		TempVert[1] =  *(CMesh[1].Vertex+ i*4*3 + 4);
		TempVert[2] =  *(CMesh[1].Vertex+ i*4*3 + 5);

		*(CMesh[1].Vertex+ i*4*3 + 3) =  *(CMesh[1].Vertex+ i*4*3 + 0);
		*(CMesh[1].Vertex+ i*4*3 + 4) =  *(CMesh[1].Vertex+ i*4*3 + 1);
		*(CMesh[1].Vertex+ i*4*3 + 5) =  *(CMesh[1].Vertex+ i*4*3 + 2);

		*(CMesh[1].Vertex+ i*4*3 + 0) =  *(CMesh[1].Vertex+ i*4*3 + 3);
		*(CMesh[1].Vertex+ i*4*3 + 1) =  *(CMesh[1].Vertex+ i*4*3 + 4);
		*(CMesh[1].Vertex+ i*4*3 + 2) =  *(CMesh[1].Vertex+ i*4*3 + 5);
	}
}

/*----------------------------------------------------------------------*/
/*  Function Name   : SetVertices                                       */
/*  Inputs          : nFaces, Faces, nVertex, pVertex                   */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     : Draw a object                                     */
/*----------------------------------------------------------------------*/
void SetVertices (int Object)
{
register		i, nVertex = 0;
float			fX, fY, fZ, pV[3], f1OverZ;
float			CamFocus = 600.0f;

    for (i=0; i<CMesh[Object].NumVertex; i++)
	{
		pV[0] = *(CMesh[Object].Vertex+nVertex++);
		pV[1] = *(CMesh[Object].Vertex+nVertex++);
		pV[2] = *(CMesh[Object].Vertex+nVertex++);

		fX = (pV[0] * T[Object].Matrix[0][0] + pV[1] * T[Object].Matrix[0][1] + pV[2] * T[Object].Matrix[0][2] + T[Object].Matrix[0][3]);
		fY = (pV[0] * T[Object].Matrix[1][0] + pV[1] * T[Object].Matrix[1][1] + pV[2] * T[Object].Matrix[1][2] + T[Object].Matrix[1][3]);
		fZ = (pV[0] * T[Object].Matrix[2][0] + pV[1] * T[Object].Matrix[2][1] + pV[2] * T[Object].Matrix[2][2] + T[Object].Matrix[2][3]);

		fZ += 300;

		if (fZ<0.00001f){fZ = 0.00001f;}

		f1OverZ = 1.0f / fZ;

		(PVRVert[Object]+i)->fX = f1OverZ * fX * 600 + 320;
		(PVRVert[Object]+i)->fY = -f1OverZ * fY * 600 + 240;
	    (PVRVert[Object]+i)->fInvW = f1OverZ;
	}
}

/*----------------------------------------------------------------------*/
/*  Function Name   : SetUV                                             */
/*  Inputs          : nFaces, Faces, pUV                                */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     :                                                   */
/*----------------------------------------------------------------------*/
void SetUV (int Object)
{
register i;

    for (i=0; i<CMesh[Object].NumVertex; i++)
	{
		(PVRVert[Object]+i)->fUOverW = *(CMesh[Object].UV++);
		(PVRVert[Object]+i)->fVOverW = *(CMesh[Object].UV++);
	}

}
/*----------------------------------------------------------------------*/
/*  Function Name   : SetSmoothShading                                  */
/*  Inputs          : nFaces, Faces, nVertex, pNormals                  */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     :                                                   */
/*----------------------------------------------------------------------*/
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
			case C_WHITE :
				(PVRVert[Object]+i)->u32Colour = RGBAColour(Col,Col,Col, 150);
				break;
	        case C_BLACK :
				(PVRVert[Object]+i)->u32Colour = RGBAColour(Col>>3,Col>>3,Col>>3, 128);
				break;
		    case C_GREY  :
				(PVRVert[Object]+i)->u32Colour = RGBAColour(Col>>1,Col>>1,Col>>1, 128);
				break;
			case C_RED   :
				(PVRVert[Object]+i)->u32Colour = RGBAColour(Col, 0, 0, 128);
				break;
			case C_GREEN :
				(PVRVert[Object]+i)->u32Colour = RGBAColour(0, Col, 0, 128);
				break;
			case C_BLUE  :
				(PVRVert[Object]+i)->u32Colour = RGBAColour(0, 0, Col, 128);
				break;
			case C_YELLOW:
				(PVRVert[Object]+i)->u32Colour = RGBAColour(Col, Col, 0, 128);
				break;
			case C_BROWN :
				(PVRVert[Object]+i)->u32Colour = RGBAColour(Col,Col>>1,Col>>2, 128);
				break;
			case C_PLAIN :
				(PVRVert[Object]+i)->u32Specular  = RGBAColour(0,0,0, 0);
		        (PVRVert[Object]+i)->u32Colour = RGBAColour(255,255,255, 150);
				break;
		}
	}

}
/*----------------------------------------------------------------------*/
/*  Function Name   : SetBackground                                     */
/*  Inputs          :                                                   */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     :                                                   */
/*----------------------------------------------------------------------*/
void SetBackground (PKMSURFACEDESC TextureID)
{
	KMSTATUS			status;
	KMVERTEXCONTEXT		BackVertexContext;		/* Vertex context */
	KMVERTEX_01			BV01[3];				/* for NO-TEXTURE-GOURAUD */
	KMVERTEX_03			BV03[3];				/* for TEXTURE-GOURAUD */
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
	BackVertexContext.FilterMode			=	KM_BILINEAR;
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

	if(TextureID == (PKMSURFACEDESC)NULL)
	{	/* No texture */
		BackVertexContext.ColorType				= KM_FLOATINGCOLOR;
		BackVertexContext.ShadingMode			= KM_NOTEXTUREGOURAUD;
	}
	else
	{					/* Use texture */
		BackVertexContext.ColorType				= KM_PACKEDCOLOR;
		BackVertexContext.ShadingMode			= KM_TEXTUREGOURAUD;
		BackVertexContext.pTextureSurfaceDesc	= TextureID;
	}

	status = kmProcessVertexRenderState(&BackVertexContext);
	Check_Status(status, "kmProcessVertexRenderState");
	status = kmSetBackGroundRenderState(&BackVertexContext);
	Check_Status(status, "kmSetBackGroundRenderState");

	/*----------------------------------------------------------------------------------- */
	/* set VERTEX DATA */

	if(TextureID == (PKMSURFACEDESC)NULL)
	{	/* No texture */
		/* Vertex #1 */
		BV01[0].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
		BV01[0].fX				=   0.0f;
		BV01[0].fY				= 479.0f;
#if defined(_STRICT_UNION_)
		BV01[0].u.fZ			=  0.000001f;
#else
		BV01[0].fZ				=  0.000001f;
#endif
		BV01[0].fBaseAlpha		=   0.0f;
		BV01[0].fBaseRed		=   0.55f;
		BV01[0].fBaseGreen		=   0.87f;
		BV01[0].fBaseBlue		=   0.96f;

		/* Vertex #2 */
		BV01[1].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
		BV01[1].fX				= 320.0f;
		BV01[1].fY				=   0.0f;
#if defined(_STRICT_UNION_)
		BV01[1].u.fZ			=  0.000001f;
#else
		BV01[1].fZ				=  0.000001f;
#endif
		BV01[1].fBaseAlpha		=   0.0f;
		BV01[1].fBaseRed		=   0.0f;
		BV01[1].fBaseGreen		=   0.15f;
		BV01[1].fBaseBlue		=   0.73f;

		/* Vertex #3 */
		BV01[2].ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;
		BV01[2].fX				= 639.0f;
		BV01[2].fY				= 479.0f;
#if defined(_STRICT_UNION_)
		BV01[2].u.fZ			=  0.000001f;
#else
		BV01[2].fZ				=  0.000001f;
#endif
		BV01[2].fBaseAlpha		=   0.0f;
		BV01[2].fBaseRed		=   0.55f;
		BV01[2].fBaseGreen		=   0.87f;
		BV01[2].fBaseBlue		=   0.96f;

		pBV[0] = &BV01[0];
		pBV[1] = &BV01[1];
		pBV[2] = &BV01[2];

		/* set VERTEX */
		status = kmSetBackGroundPlane(	pBV,					/* pVertex */
										KM_VERTEXTYPE_01,		/* VertexType */
										sizeof(KMVERTEX_01)		/* StructSize */
										);
		Check_Status(status, "kmSetBackGroundPlane");
	}
	else
	{		/* Use texture */
		/* Vertex #1 */
		BV03[0].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
		BV03[0].fX					=  0.0f;
		BV03[0].fY					=  0.0f;
#if defined(_STRICT_UNION_)
		BV03[0].u.fZ				=  0.000001f;
#else
		BV03[0].fZ					=  0.000001f;
#endif
		BV03[0].fU					=  0.0f + BILINEAR_CORRECTION;
		BV03[0].fV					=  1.0f - BILINEAR_CORRECTION;
		BV03[0].uBaseRGB.dwPacked	=  RGBAColour (255, 255, 255, 255);
		BV03[0].uOffsetRGB.dwPacked	=  RGBAColour (255, 255, 255, 255);

		/* Vertex #2 */
		BV03[1].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
		BV03[1].fX					= 640.0f;
		BV03[1].fY					=   0.0f;
#if defined(_STRICT_UNION_)
		BV03[1].u.fZ				=  0.000001f;
#else
		BV03[1].fZ					=  0.000001f;
#endif
		BV03[1].fU					= 1.0f - BILINEAR_CORRECTION;
		BV03[1].fV					= 1.0f - BILINEAR_CORRECTION;
		BV03[1].uBaseRGB.dwPacked	= RGBAColour (255, 255, 255, 255);
		BV03[1].uOffsetRGB.dwPacked	= RGBAColour (255, 255, 255, 255);

		/* Vertex #3 */
		BV03[2].ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;
		BV03[2].fX					= 640.0f;
		BV03[2].fY					= 480.0f;
#if defined(_STRICT_UNION_)
		BV03[2].u.fZ				=  0.000001f;
#else
		BV03[2].fZ					=  0.000001f;
#endif
		BV03[2].fU					= 1.0f - BILINEAR_CORRECTION;
		BV03[2].fV					= 0.0f + BILINEAR_CORRECTION;
		BV03[2].uBaseRGB.dwPacked	= RGBAColour (255, 255, 255, 255);
		BV03[2].uOffsetRGB.dwPacked	= RGBAColour (255, 255, 255, 255);

		pBV[0] = &BV03[0];
		pBV[1] = &BV03[1];
		pBV[2] = &BV03[2];

		/* set VERTEX */
		status = kmSetBackGroundPlane(	pBV,					/* pVertex */
										KM_VERTEXTYPE_03,		/* VertexType */
										sizeof(KMVERTEX_03)		/* StructSize */
										);
		Check_Status(status, "kmSetBackGroundPlane");
	}
	/*----------------------------------------------------------------------------------- */
}

/*---------------------- End Of File -----------------------------------*/
