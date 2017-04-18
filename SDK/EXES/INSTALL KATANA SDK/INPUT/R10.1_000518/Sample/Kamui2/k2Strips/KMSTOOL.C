/*----------------------------------------------------------------------*/
/*   Name   : Tools.c   (Some tools for Arc1a)                          */
/*   Author : Carlos Sarria (Matrix code is Jim's)                      */
/*   Date   : October 1997                                              */
/*                                                                      */
/*   Copyright : 1997 by VideoLogic Limited. All rights reserved.       */
/*   Modified  :	February 04. 1999 by Hiroshi Nakayama for KAMUI2	*/
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

#include "kmstool.h"

float			LightDir[3] = { -1.0f, 0.0f, 0.0f };
unsigned		TotalPolys = 0;
unsigned char	VFog = 0;

PVRVERTEX		*PVRVert[300];
PVRVERTEX		*PVRVert2[300];
TRANSFORM		T[256];

CASTMESHES	Strips[10];

/***********************************************************************/
/* Kamui Val.s *********************************************************/
/***********************************************************************/
extern	KMSYSTEMCONFIGSTRUCT	SystemConfig;
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
/**	kmtri_tstrips  by T.Muto ************************************************/
/****************************************************************************/
void
kmtri_tstrips ( KMVERTEXBUFFDESC	BufferDesc,
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

	i = 0;	/* vertex counter */
	nstrip = 0;	/* strip counter */
	nface = 0;	/* face counter */

	/* 頂点登録開始 */
	if(bTexture == TRUE)
	{
		kmStartStrip(&BufferDesc,pStripHead+2);
									/* 頂点登録開始 (TYPE03) */
	}
	else
	{
		kmStartStrip(&BufferDesc,pStripHead);
									/* 頂点登録開始 (TYPE01) */
	}

	do {

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
				Ver03.fU					= pVertices[i].fU;
				Ver03.fV					= pVertices[i].fV;
				Ver03.uBaseRGB.dwPacked		= pVertices[i].u32Colour;
				Ver03.uOffsetRGB.dwPacked	= pVertices[i].u32Specular;
				status = kmSetVertex(&BufferDesc,&Ver03,KM_VERTEXTYPE_03,sizeof(KMVERTEX_03) );
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
				status = kmSetVertex(&BufferDesc,&Ver01,KM_VERTEXTYPE_01,sizeof(KMVERTEX_01) );
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
			Ver03.fU					= pVertices[i].fU;
			Ver03.fV					= pVertices[i].fV;
			Ver03.uBaseRGB.dwPacked		= pVertices[i].u32Colour;
			Ver03.uOffsetRGB.dwPacked	= pVertices[i].u32Specular;
			status = kmSetVertex(&BufferDesc,&Ver03,KM_VERTEXTYPE_03,sizeof(KMVERTEX_03) );
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
			status = kmSetVertex(&BufferDesc,&Ver01,KM_VERTEXTYPE_01,sizeof(KMVERTEX_01) );
			Check_Status(status, "kmSetVertex");
		}			/* End of if */
		i++;		/* vertex counter up */
		nface += StripLengths[nstrip];	/* face count up */
		nstrip++;	/* next strip */

		/* 頂点登録の切り換え */
		if((nstrip == 5)&&(bTexture == TRUE))
		{
			kmEndStrip(&BufferDesc);/* 頂点登録終了 */
			kmStartStrip(&BufferDesc,pStripHead+1);
									/* 頂点登録開始 (TYPE03) */
		}

	} while(nface < nNumFaces);

	/* 頂点登録の終了 */
	kmEndStrip(&BufferDesc);
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
/*----------------------------------------------------------------------*/
/*  Function Name   :  Scale                                            */
/*  Inputs          :  Object, S                                        */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     :  Escale T using S values (x, y, z)                */
/*----------------------------------------------------------------------*/
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
	/* シ－ンの開始	*/
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

	/* 得られた値が異常であった場合は無視 */
	if((nowTime > 1000.0f)||(nowTime < 1.0f)){nowTime = 20.0f;}
	if(nowTime > maxTime){maxTime = nowTime;}	/* もっとも時間がかかった？ */
	if(nowTime < minTime){minTime = nowTime;}	/* もっとも早かった？ */

	totalTime += nowTime;								/* 累積時間 */
	aveTime = totalTime / ((double)frame + 1.0f);		/* 今までの平均時間 */

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

/*----------------------------------------------------------------------*/
/*  Function Name   : InitMeshes                                        */
/*  Inputs          :                                                   */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     : Draw a object                                     */
/*----------------------------------------------------------------------*/
void InitMeshes (void)
{
register i;
/* SET4 / SET5 */
int mptr = 0x0c400000;

    for (i=0; i<10; i++) 
	{
		Strips[i].NumFaces  = 32;
		Strips[i].NumVertex = Strips[i].NumFaces; 
#if 0
		Strips[i].Vertex  = (float *)mptr; mptr += (Strips[i].NumVertex*sizeof(float)*3);
#else
		Strips[i].Vertex  = (float *)(((KMDWORD)syMalloc(Strips[i].NumVertex*sizeof(float)*3) & 0x0FFFFFFFUL) | 0xA0000000);
#endif
		ResetMatrix (i); 
	}

#if 0
	Strips[0].Faces   = (int *)mptr; mptr += (32*sizeof(int)*3*10);
	PVRVert2[0] = (PVRVERTEX *)mptr; mptr += (32*2*sizeof(PVRVERTEX)*10);
#else
	Strips[0].Faces   = (int *)(((KMDWORD)syMalloc(32*sizeof(int)*3*10) & 0x0FFFFFFFUL) | 0xA0000000);
	PVRVert2[0] = (PVRVERTEX *)(((KMDWORD)syMalloc(32*2*sizeof(PVRVERTEX)*10) & 0x0FFFFFFFUL) | 0xA0000000);
#endif

	BuildStrips (0);

}
/*----------------------------------------------------------------------*/
/*  Function Name   : FreeMeshes                                        */
/*  Inputs          :                                                   */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     : Draw a object                                     */
/*----------------------------------------------------------------------*/
void FreeMeshes (void)
{

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
		BV01[0].u.fZ			=  0.0001f;
#else
		BV01[0].fZ				=  0.0001f;
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
		BV01[1].u.fZ			=  0.0001f;
#else
		BV01[1].fZ				=  0.0001f;
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
		BV01[2].u.fZ			=  0.0001f;
#else
		BV01[2].fZ				=  0.0001f;
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
		BV03[0].u.fZ				=  0.0001f;
#else
		BV03[0].fZ					=  0.0001f;
#endif
		BV03[0].fU					=  0.0f;
		BV03[0].fV					=  1.0f;
		BV03[0].uBaseRGB.dwPacked	=  RGBAColour (255, 255, 255, 255);
		BV03[0].uOffsetRGB.dwPacked	=  RGBAColour (255, 255, 255, 255);

		/* Vertex #2 */
		BV03[1].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
		BV03[1].fX					= 640.0f;
		BV03[1].fY					=   0.0f;
#if defined(_STRICT_UNION_)
		BV03[1].u.fZ				=  0.0001f;
#else
		BV03[1].fZ					=  0.0001f;
#endif
		BV03[1].fU					= 1.0f;
		BV03[1].fV					= 1.0f;
		BV03[1].uBaseRGB.dwPacked	= RGBAColour (255, 255, 255, 255);
		BV03[1].uOffsetRGB.dwPacked	= RGBAColour (255, 255, 255, 255);

		/* Vertex #3 */
		BV03[2].ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;
		BV03[2].fX					= 640.0f;
		BV03[2].fY					= 480.0f;
#if defined(_STRICT_UNION_)
		BV03[2].u.fZ				=  0.0001f;
#else
		BV03[2].fZ					=  0.0001f;
#endif
		BV03[2].fU					= 1.0f;
		BV03[2].fV					= 0.0f;
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

/*----------------------------------------------------------------------*/
/*  Function Name   : EnviroMap                                         */
/*  Inputs          : nFaces, Faces, pUV                                */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     :                                                   */
/*----------------------------------------------------------------------*/
void EnviroMap (int nVertex, float *pVertex, PVRVERTEX *PvrVertex)
{
register i;

    for (i=0; i<nVertex; i++)
	{
		(PvrVertex+i)->fUOverW = (PvrVertex+i)->fUOverW;/*(((float) atan2 (Vertices[k][2] - Centre[2], fX) + PI) * ONEOVERTWOPI) * fU; */
		(PvrVertex+i)->fVOverW = (PvrVertex+i)->fUOverW;/*(((float) atan2 (Vertices[k][1] - Centre[1], fX) + PI) * ONEOVERTWOPI) * fV; */
	}

}

/*----------------------------------------------------------------------*/
/*  Function Name   : SetStrips                                         */
/*  Inputs          : IsStrip                                           */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    : Strips, PVRVert2                                  */
/*  Description     : Draws a 3D object                                 */
/*----------------------------------------------------------------------*/
void SetStrips (INFO CInfo, int nStrip, PKMSTRIPHEAD pStripHead)
{
int Strp[]={30, 30, 30, 30, 30, 30, 30, 30, 30, 30};
int i, j, nVertex = 0, nPVR = 0, Object;
int  ObjList[10] = { 0,2,4,6,8, 1,3,5,7,9} ;
float fX, fY, fZ, pV[3], f1OverZ;
float CamFocus = 600.0f;

	for (j = 0; j < nStrip; j++)
	{

		Object = ObjList[j];

		nVertex = 0;
	    for ( i = 0; i < Strips[Object].NumVertex; i++)
		{

		    pV[0] = *(Strips[Object].Vertex+nVertex++);
			pV[1] = *(Strips[Object].Vertex+nVertex++);
			pV[2] = *(Strips[Object].Vertex+nVertex++);

			fX = (pV[0] * T[Object].Matrix[0][0] + pV[1] * T[Object].Matrix[0][1] + pV[2] * T[Object].Matrix[0][2] + T[Object].Matrix[0][3]);
			fY = (pV[0] * T[Object].Matrix[1][0] + pV[1] * T[Object].Matrix[1][1] + pV[2] * T[Object].Matrix[1][2] + T[Object].Matrix[1][3]);
			fZ = (pV[0] * T[Object].Matrix[2][0] + pV[1] * T[Object].Matrix[2][1] + pV[2] * T[Object].Matrix[2][2] + T[Object].Matrix[2][3]);

			fZ += 800;

			f1OverZ = 600.0f / fZ;

			(PVRVert2[0]+nPVR)->fX		= f1OverZ * fX + 320;
			(PVRVert2[0]+nPVR)->fY		= -f1OverZ * fY + 240;
		    (PVRVert2[0]+nPVR)->fInvW	= f1OverZ;

			(PVRVert2[0]+nPVR)->u32Colour = 0xFFFFFFFF;

		    /*
    		 * The texture name needs to be set for every vertex. 
			 * If you are using triangles, the first vertex of each polygon sets the texture for that polygon. 
			 * If you are using strips, the first vertex of the strip sets the texture for the whole strip. 
			 */

			(PVRVert2[0]+nPVR)->fU = 0.5f + (fX - fZ)/200.0f;
			(PVRVert2[0]+nPVR)->fV = 0.5f + (fY - fZ)/200.0f;

			nPVR++;
		}
	}

	/*
	 * We'll send a set of 10 strips of two alternating textures with 30 polygon each
	 */
	kmtri_tstrips (	VertexBufferDesc,	/* KMVERTEXBUFFDESC	BufferDesc, */
		pStripHead,			/* PKMSTRIPHEAD pStrip , */
		30 * nStrip,		/* int				nNumFaces, */
		Strp,				/* int				*StripLengths, */
		PVRVert2[0],		/* PPVRVERTEX  		pVertices, */
		CInfo.Textured		/* int				bTexture */
		);
}

/*----------------------------------------------------------------------*/
/*  Function Name   : BuildStrips                                       */
/*  Inputs          : nStrips                                           */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    : Strips                                            */
/*  Description     : Model 3D data.                                    */
/*----------------------------------------------------------------------*/
void BuildStrips (int nStrip)
{
register i, j, k;
unsigned nMem = 0;
float Delta;

	Delta = (PI*4.0f) / (float)Strips[nStrip].NumFaces;
    
	for (k=0; k<10; k++)
	{
		nMem = 0;
    	for (i=0; i<Strips[nStrip].NumFaces/2; i++)
		{
			for (j=0; j<2; j++)
			{
				*(Strips[k].Vertex+nMem++) = (float)cos(i*Delta) * 100.0f;
				*(Strips[k].Vertex+nMem++) = (float) (300 - k*30 +j*25);
				*(Strips[k].Vertex+nMem++) = (float)sin(i*Delta) * 100.0f;
			}
		}
	}

	nMem = 0;

	  
	for (i=0; i<Strips[nStrip].NumFaces*10; i++)
	{
		if (i%32==30 ||i%32==31){continue;}
		*(Strips[0].Faces+nMem++) = i;
		*(Strips[0].Faces+nMem++) = i+1;
		*(Strips[0].Faces+nMem++) = i+2;
	}

}

/*----------------------------------------------------------------------*/
/*  Function Name   : InitContext                                       */
/*  Inputs          : CInfo                                             */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     :                                                   */
/*----------------------------------------------------------------------*/

void InitContext (PKMSTRIPCONTEXT	pStripContext,
				  PKMSTRIPHEAD		pStripHead,
				  PKMSURFACEDESC	pTextureDesc1,
				  PKMSURFACEDESC	pTextureDesc2,
				  INFO CInfo)
{
	/* VERTEX TYPE_01 用 KMSTRIPHEAD 構築 */
	memset( pStripContext, 0, sizeof(KMSTRIPCONTEXT));	/* Crear Context */
	memset( pStripHead, 0, sizeof(KMSTRIPHEAD));		/* Crear Strip Head */
	InitStripContext01(pStripContext,pStripHead);		/* Initialize context */

	/* VERTEX TYPE_03 用 KMSTRIPHEAD 構築 その１ */
	memset( pStripContext+1, 0, sizeof(KMSTRIPCONTEXT));/* Crear Strip Context */
	memset( pStripHead+1, 0, sizeof(KMSTRIPHEAD));		/* Crear Strip Head */
	InitStripContext03(pStripContext+1,pStripHead+1,pTextureDesc1);
														/* Initialize context */

	/* VERTEX TYPE_03 用 KMSTRIPHEAD 構築 その２ */
	memset( pStripContext+2, 0, sizeof(KMSTRIPCONTEXT));/* Crear Strip Context */
	memset( pStripHead+2, 0, sizeof(KMSTRIPHEAD));		/* Crear Strip Head */
	InitStripContext03(pStripContext+2,pStripHead+2,pTextureDesc2);
														/* Initialize context */

	if (CInfo.Bilinear)
	{
		kmChangeStripFilterMode(pStripHead+1,KM_IMAGE_PARAM1,KM_BILINEAR);
		kmChangeStripFilterMode(pStripHead+2,KM_IMAGE_PARAM1,KM_BILINEAR);
	}
	else
	{
		kmChangeStripFilterMode(pStripHead+1,KM_IMAGE_PARAM1,KM_POINT_SAMPLE);
		kmChangeStripFilterMode(pStripHead+2,KM_IMAGE_PARAM1,KM_POINT_SAMPLE);
	}

	if(CInfo.Gouraud)
	{
		/* Set shading mode */
		kmChangeStripGouraud(pStripHead,KM_TRUE);
		kmChangeStripGouraud(pStripHead+1,KM_TRUE);
		kmChangeStripGouraud(pStripHead+2,KM_TRUE);
	}
	else
	{
		/* Set shading mode */
		kmChangeStripGouraud(pStripHead,KM_FALSE);
		kmChangeStripGouraud(pStripHead+1,KM_FALSE);
		kmChangeStripGouraud(pStripHead+2,KM_FALSE);
	}
	kmChangeStripFlipUV(pStripHead+1,KM_IMAGE_PARAM1,KM_FLIP_UV);
	kmChangeStripFlipUV(pStripHead+2,KM_IMAGE_PARAM1,KM_FLIP_UV);
}

/*----------------------------------------------------------------------*/
/*  Function Name   : SetContext                                        */
/*  Inputs          : CInfo                                             */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     :                                                   */
/*----------------------------------------------------------------------*/

void SetContext (PKMSTRIPHEAD pStripHead, INFO CInfo)
{
	if (CInfo.Bilinear)
	{
		kmChangeStripFilterMode(pStripHead+1,KM_IMAGE_PARAM1,KM_BILINEAR);
	}
	else
	{
		kmChangeStripFilterMode(pStripHead+1,KM_IMAGE_PARAM1,KM_POINT_SAMPLE);
	}

	if(CInfo.Gouraud)
	{
		/* Set shading mode */
		kmChangeStripGouraud(pStripHead,KM_TRUE);
		kmChangeStripGouraud(pStripHead+1,KM_TRUE);
	}
	else
	{
		/* Set shading mode */
		kmChangeStripGouraud(pStripHead,KM_FALSE);
		kmChangeStripGouraud(pStripHead+1,KM_FALSE);
	}

}

/*---------------------- End Of File -----------------------------------*/
