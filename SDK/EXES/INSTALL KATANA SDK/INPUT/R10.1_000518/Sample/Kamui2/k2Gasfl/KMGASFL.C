/********************************************************************************
 * Name     : KMGASFL															*
 * Title    : KAMUI test program "FIRE" from VL									*
 * Author   : VideoLogic Carlos Sarria / NEC Software Takeshi Muto				*
 * Created  : July 1997 by VideoLogic											*
 * Modified : Novenber  6. 1997 by Takeshi Muto for KAMUI						*
 *            May      20. 1998 by Takeshi Muto for KAMUI(rev2)					*
 *            January  27. 1999 by T.Kamei for KAMUI2							*
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

#define		SPEED			(1.0f)					/* move speed ( 1 to n ) */

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
#include	"dispstr.h"				/* for DisplayString								*/
#include	"fire.h"  				/* This is the file with 3D data					*/
#include	"vltex.h"				/* for vl sample texture							*/

#if defined(_VERTEXMACRO_L4_)
#define _KM_USE_VERTEX_MACRO_L4_
#include "kamuix.h"
#endif

#define	RGBColour(r, g, b)	((KMUINT32) (((r) << 16) | ((g) <<  8) | (b)))
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
	KMSURFACEDESC		Texture[10];			/* texture surface				*/
	KMVERTEXBUFFDESC	VertexBufferDesc;		/* Vertex-buffer				*/

	KMSTRIPCONTEXT		StripContext00;
	KMSTRIPCONTEXT		StripContext03;
	KMSTRIPHEAD			StripHead00;
	KMSTRIPHEAD			StripHead03;

	PKMSURFACEDESC			pFB[2];
	KMDWORD					FBarea[24576 + 19456];	/*	FBstruct 4096 Entry (= 4096 * 24 / 4)
														VQstruct 1024 Entry (= 1024 * 76 / 4) */
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

#define	PI	3.1416f

static float	GlassRefect[4], Ligth1[3], Shad[255], CamFocus = 500.0;
static float	YAng, XAng;
float	XAng1 = 0.0 , YAng1 = 0.005f, LH=20.0, LHD = 0.02f;

PVRVERTEX	*TempVert[NUM_MESHES];
PVRVERTEX	Fire[4][4];

void SetupTextures		(void);
void SetupContext 		(void);
void InitMeshes    		(void);
void DrawAll       		(void);
void UpdateVertex  		(int Num);
void Shading       		(int Num);
void CreateFire    		(void);
void ReadMaple			(void);

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
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bIgnoreTextureAlpha	= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFlipUV				= KM_NOFLIP;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nClampUV				= KM_NOCLAMP;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFilterMode			= KM_BILINEAR;
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
	InitStripContext01(&StripContextBG01,&StripHeadBG01);

	/*----------------------------------------------------------------------------------- */
	/* set VERTEX DATA */

	/* Vertex #0 */
	BV01[0].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
	BV01[0].fX					=   0.0f;
	BV01[0].fY					= 479.0f;
	BV01[0].u.fZ				=   0.0001f;
	BV01[0].fBaseAlpha			=   0.0f;
	BV01[0].fBaseRed			=   0.0f;
	BV01[0].fBaseGreen			=   0.0f;
	BV01[0].fBaseBlue			=   0.0f;

	/* Vertex #1 */
	BV01[1].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
	BV01[1].fX					= 320.0f;
	BV01[1].fY					=   0.0f;
	BV01[1].u.fZ				=   0.0001f;
	BV01[1].fBaseAlpha			=   0.0f;
	BV01[1].fBaseRed			=   0.05f;
	BV01[1].fBaseGreen			=   0.05f;
	BV01[1].fBaseBlue			=   0.05f;

	/* Vertex #2 */
	BV01[2].ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;
	BV01[2].fX					= 639.0f;
	BV01[2].fY					= 479.0f;
	BV01[2].u.fZ				=   0.0001f;
	BV01[2].fBaseAlpha			=   0.0f;
	BV01[2].fBaseRed			=   0.0f;
	BV01[2].fBaseGreen			=   0.0f;
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
 *  Description     :   This routine is used to set device and setup some values.  	   *
 *                      This routine is called from FRONTEND.C                         *
 *-------------------------------------------------------------------------------------*/
int SetupScene (void)
{
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
								KM_TRUE,			/* bDither		*/
								KM_FALSE			/* bAntiAlias	*/
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

	SystemConfig.dwSize					=	sizeof(KMSYSTEMCONFIGSTRUCT);
#if defined(_NOWAIT_VSYNC_)
	SystemConfig.flags					=	KM_CONFIGFLAG_ENABLE_CLEAR_FRAMEBUFFER | KM_CONFIGFLAG_NOWAITVSYNC;
#else
	SystemConfig.flags					=	KM_CONFIGFLAG_ENABLE_CLEAR_FRAMEBUFFER;
#endif
	/* for Frame buffer */
	SystemConfig.ppSurfaceDescArray		=	pFB;		/* Array of SurfaceDesc	pointer */
	SystemConfig.fb.nNumOfFrameBuffer	=	2;			/* Number Of Frame Buffer		*/
	/* for Texture Memory */
	SystemConfig.nTextureMemorySize		=	0x100000*2;	/* Texture 2MB					*/
	SystemConfig.nNumOfTextureStruct	=	4096;		/* テクスチャ管理構造体の数		*/
	SystemConfig.nNumOfSmallVQStruct	=	1024;		/* VQテクスチャ管理構造体の数	*/
	SystemConfig.pTextureWork			=	&FBarea[0];	/* テクスチャ管理構造体領域		*/
	/* for Vertex buffer */
	SystemConfig.pBufferDesc			=	&VertexBufferDesc;	/* pointer to VERTEXBUFFDESC	*/
	SystemConfig.nNumOfVertexBank		=	2;
	SystemConfig.pVertexBuffer			=	dwDataPtr;	/* pointer to Vertex buffer	*/
	SystemConfig.nVertexBufferSize		=	0x100000*2;	/* 2MB						*/
	SystemConfig.nPassDepth				=	1;
	SystemConfig.Pass[0].dwRegionArrayFlag = KM_PASSINFO_AUTOSORT;
	SystemConfig.Pass[0].fBufferSize[0] =  50.0f;
	SystemConfig.Pass[0].fBufferSize[1] =   0.0f;
	SystemConfig.Pass[0].fBufferSize[2] =  50.0f;
	SystemConfig.Pass[0].fBufferSize[3] =   0.0f;
	SystemConfig.Pass[0].fBufferSize[4] =   0.0f;

	status = kmSetSystemConfiguration( &SystemConfig );
	Check_Status(status, "kmSetSystemConfiguration");

	/*-----------------------------------------------------------------------------------*/
	/* Initialize DisplayString routine */
	txt_InitDisplayString();

	/*-----------------------------------------------------------------------------------*/
	/* some initializes */
    SetupTextures ();
	SetupContext  ();
    InitMeshes ();

	/* Setup background plane */
	InitBackGround();

	/*-----------------------------------------------------------------------------------*/
	/* Set Culling Register */
	status = kmSetCullingRegister(1.0f);
	Check_Status(status, "kmSetCullingRegister");

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
#endif

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
#endif

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

	totalTime += nowTime;								/* 累積時間			*/
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
	register i;

	YAng += (YAng1 / SPEED);

    for (i=0; i<NUM_MESHES; i++)
	{
        UpdateVertex (i);   /* Recalculate vertices for the new position */
        Shading      (i);   /* Smooth shading							 */

		/* Updating texture parameters for each mesh of the model */
		/* Set shading mode */
		kmChangeStripGouraud			( &StripHead03, KM_TRUE );
		/* Set texture surface */
		kmChangeStripTextureSurface		( &StripHead03, KM_IMAGE_PARAM1, &Texture[Mesh[i].Material] );

        if ((i == FIRE) || (i == REFLECTION))
		{
			kmChangeStripBlendingMode		( &StripHead03, KM_IMAGE_PARAM1, KM_SRCALPHA, KM_INVSRCALPHA );
			kmChangeStripListType			( &StripHead03, KM_TRANS_POLYGON );
			kmChangeStripTextureShadingMode	( &StripHead03, KM_IMAGE_PARAM1, KM_MODULATE );
			kmChangeStripUseAlpha			( &StripHead03, KM_IMAGE_PARAM1, KM_TRUE );
		}
		else
		{
			kmChangeStripBlendingMode		( &StripHead03, KM_IMAGE_PARAM1, KM_ONE, KM_ZERO );
			kmChangeStripListType			( &StripHead03, KM_OPAQUE_POLYGON );
			kmChangeStripTextureShadingMode	( &StripHead03, KM_IMAGE_PARAM1, KM_MODULATE );
			kmChangeStripUseAlpha			( &StripHead03, KM_IMAGE_PARAM1, KM_FALSE );
		}

		/* Draws everything */
		if (i==FIRE)
		{
			CreateFire();
		}
		else
		{
			kmtri_triangles (	&VertexBufferDesc,			/* PKMVERTEXBUFFDESC */
								&StripHead03,				/* PKMSTRIPHEAD		 */
								Mesh[i].NumFaces,			/* int  nNumFaces	 */
								(int(*)[3])Mesh[i].Faces,	/* int  pFaces[][3]	 */
								TempVert[i],				/* PPVRVERTEX		 */
								TRUE						/* bTexture			 */
							);
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
 *-------------------------------------------------------------------------------------*/
void SetupTextures (void)
{
	register		i;
	PKMDWORD		pTexture01;				/* Pointer to texture		*/
	KMTEXTURETYPE	nTextureType;			/* texture type definition	*/

	for (i=0;i<NumMaterials; i++)
	{
		if (i==MFIRE)
		{
			/* Translucent texture */
			/*----------------------------------------------------------------------------------- */
			/* Create texture surface */
			nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_ARGB4444;	/* Set texture type */
			status = kmCreateTextureSurface(
				&Texture[i],			/* OUT	PKMSURFACEDESC	pSurfaceDesc	*/
				128,					/*	IN	KMINT32			nWidth			*/
				128,					/*	IN	KMINT32			nHeight			*/
				nTextureType			/*	IN	KMTEXTURETYPE	nTextureType	*/
			);
			Check_Status(status, "kmCreateTextureSurface(ARGB)");
			/*----------------------------------------------------------------------------------- */
			/* Load and set texture */
			pTexture01 = (unsigned long *)&gas_gsfire;
			status = kmLoadTexture(&Texture[i],								/* PKMSURFACEDESC pSurfaceDesc	*/
									pTexture01 + (16 / sizeof(KMDWORD))		/* PKMDWORD pTexture			*/
									);
			Check_Status(status, "kmLoadTexture(ARGB)");
		}
		else
		{
			/* Opaque texture */
			/*----------------------------------------------------------------------------------- */
			/* Create texture surface */
			nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565;	/* Set texture type */
			status = kmCreateTextureSurface(
				&Texture[i],			/* OUT	PKMSURFACEDESC	pSurfaceDesc	*/
				128,					/*	IN	KMINT32			nWidth			*/
				128,					/*	IN	KMINT32			nHeight			*/
				nTextureType			/*	IN	KMTEXTURETYPE	nTextureType	*/
			);
			Check_Status(status, "kmCreateTextureSurface(RGB)");
			/*----------------------------------------------------------------------------------- */
			/* Load and set texture */
			switch(i)
			{
				default:
				case 0:	pTexture01 = (unsigned long *)&gas_gsface;
						break;
				case 1:	pTexture01 = (unsigned long *)&gas_gsglass;
						break;
				case 2:	pTexture01 = (unsigned long *)&gas_gstorso;
						break;
				case 3:	pTexture01 = (unsigned long *)&gas_gsfirer;
						break;
				case 4:	pTexture01 = (unsigned long *)&gas_gsfire;
						break;
			}
			status = kmLoadTexture(&Texture[i],								/* PKMSURFACEDESC pSurfaceDesc	*/
									pTexture01 + (16 / sizeof(KMDWORD))		/* PKMDWORD pTexture			*/
									);
			Check_Status(status, "kmLoadTexture(ARGB)");
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
void SetupContext (void)
{
	/**************************
	 * KMSTRIPHEADの構築
	 **************************/
	memset( &StripContext03, 0, sizeof(StripContext03));
	memset( &StripHead03,	 0, sizeof(StripHead03));

	InitStripContext03(&StripContext03,&StripHead03,&Texture[0]);
}

/*-------------------------------------------------------------------------------------*
 *  Function Name   : InitMeshes                                                       *
 *  Inputs          : None                                                             *
 *  Outputs         : None                                                             *
 *  Returns         : None                                                             *
 *  Globals Used    : Shad, Mesh, TempVert, GlassReflect                               *
 *  Description     : Sets initials values for meshes managing                         *
 *-------------------------------------------------------------------------------------*/
void InitMeshes (void)
{
	float		Col;
	register	i,j,k =0;
	int			mptr = 0x0c400000;

    /* This function is in logo.h and creates an array of structures with 3D data */
    CreateMeshesArray ();

    /* Shad is a 255 values array with information for smooth shading */
    for (i=0; i<120; i++) { Col = (float)(120-i)/4; Shad[k++] = 0;}
    for (i=0; i<100; i++) { Col = (float)(i*255)/100; Shad[k++] = (float) i/100.0;}
    for (i=0; i<35;  i++) { Shad[k++] = 1.0f;}

	for (i=0; i<NUM_MESHES; i++)
	{
#if 0
		TempVert[i] = (PVRVERTEX *)mptr; mptr += Mesh[i].NumVertex*sizeof(PVRVERTEX);
#else
		TempVert[i] = (PVRVERTEX *)(((KMDWORD)syMalloc(Mesh[i].NumVertex*sizeof(PVRVERTEX)) & 0x0FFFFFFFUL) | 0xA0000000);
#endif
	}

	/* Setting UV values for all the meshes*/
	for (j=0; j<NUM_MESHES;j++)
	{
    	for (i=0; i<Mesh[j].NumVertex; i++)
		{
        	(TempVert[j]+i)->fUOverW    =  (Mesh[j].TexMap) ? *(Mesh[j].UV+i*2+0) : 0;
            (TempVert[j]+i)->fVOverW    =  (Mesh[j].TexMap) ? *(Mesh[j].UV+i*2+1) : 0;
        }
    }

	/* Reference position for glasses reflection */
	for (i=0;i<4;i++)
	{
		GlassRefect[i] = *(Mesh[REFLECTION].Vertex+i*3+2);
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
	float	Temp[3];
	int		i, j=0, k=0, l=0;
	float	x, y, z, CosX, SinX, CosY, SinY, CamZ;

	CosX = cos(XAng); SinX = sin(XAng);
	CosY = cos(YAng); SinY = sin(YAng);

    for (i=0; i<Mesh[Num].NumVertex; i++)
	{
		 x = *(Mesh[Num].Vertex+k++)-GroupCenter[0];
         y = *(Mesh[Num].Vertex+k++)-GroupCenter[1];
         z = *(Mesh[Num].Vertex+k++)-GroupCenter[2];

		 /* Temp is the outcome vertex after the rotation */
         Temp[0] = x * CosY - z * SinY;
         Temp[2] = z * CosY + x * SinY;

         z       = Temp[2];
         Temp[1] = y * CosX - z * SinX;
         Temp[2] = z * CosX + y * SinX + 800;

         if (Temp[2] <=0.0){ Temp[2] = 0.001f;}

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
 *  Globals Used    : Light1, Mesh, TempVert                                           *
 *  Description     : Shades a mesh.                                                   *
 *-------------------------------------------------------------------------------------*/
void Shading (int Num)
{
	float		TempCo, TCo, Dir;
	float		Sh, LTemp[3], sl, x,y,z;
	register	l=0, i;
	unsigned	k=0;
	KMUINT32	Col;

    /* We move the position for simulating a dinamic light */
    if (Num != FIRER)
	{
		 Ligth1[0] = 1;
		 Ligth1[2] = 0.2 + 0.1*sin(frame/1.5);
		 Ligth1[1] = 0;
	}
    else
	{
		Ligth1[0] = 0;
		Ligth1[1] = 1;
		Ligth1[2] = 0;
	}

    if (Num == FIRE){ return;}

    /* We just rotate the light vector in the opposite direction instead of rotating all the normals */
    Dir = sqrt (Ligth1[0]*Ligth1[0]+Ligth1[1]*Ligth1[1]+Ligth1[2]*Ligth1[2]);
    LTemp[0] = Ligth1[0]/Dir;
	LTemp[1] = Ligth1[1]/Dir;
	LTemp[2] = Ligth1[2]/Dir;

    k = Mesh[Num].Material;

    sl = LH/60.0;

    TempCo = 255.0 * sl;

    if (Num == REFLECTION)
	{
       if (LH<20) sl = 20.0f/60.0f;
       TempCo = 255.0*sl;
    }

    for (i=0; i<Mesh[Num].NumVertex; i++)
	{
		x = *(Mesh[Num].Normals+l++);
        y = *(Mesh[Num].Normals+l++);
        z = *(Mesh[Num].Normals+l++);

		/* Sh is a value from 0.0 to 1.0 depending on the angle between a normal *
		 * and the light direction.                                              */
        Sh = fabs( LTemp[0] * x + LTemp[1] * y + LTemp[2] * z + 1.0);

        TCo = Shad[(int)(127.0*Sh)];

        Col = (int)(TempCo*TCo);

        /* Setting vertex colour */
        (TempVert[Num]+i)->u32Colour  = RGBColour (Col, Col, Col);
    }
}

/*-------------------------------------------------------------------------------------*
 *  Function Name   : CreateFire                                                       *
 *  Inputs          : None                                                             *
 *  Outputs         : None                                                             *
 *  Returns         : None                                                             *
 *  Globals Used    : TempVert, LH                                                     *
 *  Description     : Creates fire poligons and shows the front face always.           *
 *-------------------------------------------------------------------------------------*/
void CreateFire (void)
{
	register	i,j, k;
	float		Ax, Ay, Bx, By, Bz, Sh, Ch, h, w;
	float		UVFire[][2] = {	{ 1.000000f, 1.000000f },   { 0.000000f, 1.000000f },
	        		            { 0.000000f, 0.000000f },   { 1.000000f, 0.000000f } };
	int 		FFire []	= {0, 1, 2, 3};

    for (k=0; k<1; k++)
	{
		for (j=0; j<4; j++)
		{
        	Ax = (TempVert[FIRE]+j+4)->fX;
            Ay = (TempVert[FIRE]+j+4)->fY;

            Bx = (TempVert[FIRE]+j+0)->fX;
            By = (TempVert[FIRE]+j+0)->fY;
            Bz = (TempVert[FIRE]+j+0)->fInvW;

	        /* Growing up and down the flames (LH is the value)*/
            Sh = LH*(By-Ay)/5.0;
            Ch = 200.0*Bz*LH;
            /* Moving vertices a little bit to simulating dinamic light */
            h =  Sh + (Sh/8.0) * sin((j/2+k*2+frame)/1.0);
            w =  Ch + (Ch/4.0) * cos((k*4+frame)/1.0);

			/* Building 4 poligons (4 flames) */
           	for (i=0; i<4; i++)
		   	{
            	Fire[j][i].fUOverW    =  UVFire[i][0];
            	Fire[j][i].fVOverW    =  UVFire[i][1];
            	Fire[j][i].u32Colour  =  0xFFFFFF;
            	Fire[j][i].fUOverW    =  UVFire[i][0];
            	Fire[j][i].fVOverW    =  UVFire[i][1];
            	Fire[j][i].fInvW      =  (TempVert[FIRE]+j)->fInvW;
			}

            Fire[j][0].fX =  Ax - w;
            Fire[j][0].fY =  Ay - h;
            Fire[j][1].fX =  Ax + w;
            Fire[j][1].fY =  Ay - h;
            Fire[j][2].fX =  Bx + w;
            Fire[j][2].fY =  By;
			Fire[j][3].fX =  Bx -w;
			Fire[j][3].fY =  By;

          /* Drawing quads... */
			kmtri_quads (	&VertexBufferDesc,		/* PKMVERTEXBUFFDESC */
							&StripHead03,			/* PKMSTRIPHEAD		 */
							1,						/* int  nNumFaces	 */
							&FFire,					/* int  pFaces[][3]	 */
							Fire[j],				/* PPVRVERTEX		 */
							TRUE					/* bTexture			 */
						);
		}
	}

	/* Updating the reflection on the glasses */
    for (i=0;i<4;i++)
    {
	  *(Mesh[REFLECTION].Vertex+i*3+2) = GlassRefect[i]-(float)cos((double)YAng)*40.0;
	}

    (TempVert[REFLECTION]+0)->fVOverW = *(Mesh[REFLECTION].UV+0+1)- (LH-30)/550;
    (TempVert[REFLECTION]+1)->fVOverW = *(Mesh[REFLECTION].UV+2+1)- (LH-30)/550;
    (TempVert[REFLECTION]+2)->fVOverW = *(Mesh[REFLECTION].UV+4+1)+ 0.01*sin((j*8.0+frame)/1.5)-(LH-30)/1520;
    (TempVert[REFLECTION]+3)->fVOverW = *(Mesh[REFLECTION].UV+6+1)+ 0.01*sin((j*8.0+frame)/1.5)-(LH-30)/1520;
}

/****************************************************************************
 *	main
 ****************************************************************************/
int	Kamui_Init(void)
{

	txt_ClearScreen();	/* Clear text screen	*/

#if defined(_VERTEXMACRO_L4_)
	PRINTOUT(("** KMGASFL(KAMUI2&Shinobi) Use:Level4 Macro **\n"));
#else
	PRINTOUT(("** KMGASFL(KAMUI2&Shinobi) **\n"));
#endif

	SetupScene ();		/* Initialize			*/

#if 0
	do {
		ReadMaple ();
		NextFrame();	/* Rendering			*/
		LH += (LHD / SPEED);
		if(LH > 60.0f) { LHD = -LHD; LH = 60.0f; }
		if(LH <  5.0f) { LHD = -LHD; LH =  5.0f; }
	} while(1);

	Finish();		/* End of render */
	PRINTOUT(("** END Gas flame **\n"));
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
			YAng1 = 0.0f;
	}

	/* UP cross key */
	if ( per->on & PDD_DGT_KU )
	{
		LH += 0.5f;
		if(LH > 60.0f){ LH = 60.0f;}
	}

	/* DOWN cross key */
	if ( per->on & PDD_DGT_KD )
	{
		LH -= 0.5f;
		if(LH < 5.0f){ LH = 5.0f;}
	}

	/* Left cross key */
	if ( per->on & PDD_DGT_KL )
	{
			YAng1 -= 0.001f;
	}

	/* Right cross key */
	if ( per->on & PDD_DGT_KR )
	{
		YAng1 += 0.001f;
	}
}

/*--------------------------- End of File --------------------------------*/
