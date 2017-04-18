/********************************************************************************/
/* Name     : kmnefert.c														*/
/* Title    : KAMUI test program "Nefertt" from VL								*/
/* Author   : VideoLogic / Takeshi Muto : NEC									*/
/* Created  : 30/01/1997  by VideoLogic											*/
/* Modified : 17/09/1997  by Takeshi Muto for KAMUI								*/
/*			May      12. 1998 by Takeshi Muto for CLX/SET5						*/
/*			February 04. 1999 by Hiroshi Nakayama for KAMUI2					*/
/*			February 16. 1999 by Takeshi Muto for Shinobi						*/
/* Description :																*/
/********************************************************************************/
#define		_DISPLAY_STRING_
/* if defined then display strings on screen */

#define		_DISP_PERFORMANCE_
/* Display performance : for windows */

#define		SPEED			(1.0f)					/* pet move speed ( 1 to n ) */

/* 「顔」のテクスチャ */
#define		TEX1_U			(128)					/* Texture width */
#define		TEX1_V			(128)					/* Texture height */
/* logo のテクスチャ */
#define		TEX2_U			(256)					/* Texture width */
#define		TEX2_V			(256)					/* Texture height */

#include	<math.h>				/* for atan */
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
#include	"transfor.h"
#include	"kmnefert.h"			/* nefertity model data */
#include	"dispstr.h"				/* for DisplayString */

/* Textures */
#include	"vltex.h"				/* for vl sample texture */

#define		PI					(3.141592654f)
#define		RGBColour(r, g, b)	((KMUINT32) (((r) << 16) | ((g) << 8) | (b)))
#define		RGBA(r, g, b, a)	((KMUINT32) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b)))
#define		ONEOVERTWOPI		(1.0f/(2.0f*PI))

typedef float	km_2d_vec[2];
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
	KMSURFACEDESC		TexSurfaceDesc1;		/* texture surface */
	KMSURFACEDESC		TexSurfaceDesc2;		/* texture surface */
	KMVERTEXBUFFDESC	VertexBufferDesc;		/* Vertex-buffer */
	PKMDWORD			pTexture01;				/* Pointer to texture */
	KMTEXTURETYPE		nTextureType;			/* texture type definition */

	KMSTRIPCONTEXT		StripContext03;			/* Strip Context TYPE03 */
	KMSTRIPHEAD			StripHead03;			/* Strip Head TYPE03 */
	KMSTRIPCONTEXT		StripContext11;			/* Strip Context TYPE11 */
	KMSTRIPHEAD			StripHead11;			/* Strip Head TYPE11 */
	KMSTRIPCONTEXT		StripContext17;			/* Strip Context TYPE17 */
	KMSTRIPHEAD			StripHead17;			/* Strip Head TYPE17 */

	PKMSURFACEDESC		pFB[2];
	KMDWORD				FBarea[24576 + 19456];
								/* FBstruct 4096 Entry (= 4096 * 24 / 4) */
								/* VQstruct 1024 Entry (= 1024 * 76 / 4) */
	KMDWORD				DUMPAREA[10000];
	KMSYSTEMCONFIGSTRUCT	SystemConfig;
	PKMDWORD			dwDataPtr;

void ReadMaple (void);

/* Peripheral */
PDS_PERIPHERAL *per;

/***************************************************************************/
/**	グローバル変数 *********************************************************/
/***************************************************************************/

static km_vector km_x_axis = {1.0f, 0.0f, 0.0f};	/* x_axis */
static km_vector km_y_axis = {0.0f, 1.0f, 0.0f};	/* y_axis */
static km_vector km_z_axis = {0.0f, 0.0f, 1.0f};	/* z_axis */

static int		PVRFaces[NUM_FACES][3];
static float	fDot[NUM_VERTICES];

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

/* モード設定フラグ */
	int		move_object		= 1;	/* 物体を自動的に回転する */
	int		tex_map_type	= 2;	/* Texture mapping type 1=Spherical 2=Cylindrical */
	int		shadow_vol_type	= 2;	/* shadow volume 1:No 2:Shadow 3:Light */
	int		disp_shadow_vol	= 0;	/* Display shadow/light volume object */
	int		polygons		= NUM_FACES;	/* 表示するポリゴンの数 */
	int		LightRed		= 100;	/* Light Color(Red) */
	int		LightGreen		= 100;	/* Light Color(Green) */
	int		LightBlue		= 100;	/* Light Color(Blue) */

/* 物体の移動に関する変数 */
	float	rx = 0.0f;	/* X軸周りの回転量(ユーザー入力) */
	float	ry = 0.0f;	/* Y軸周りの回転量(ユーザー入力) */
	float	rz = 0.0f;	/* Z軸周りの回転量(ユーザー入力) */

	float 				OxDash, OyDash, SxDash, SyDash;
	float				ZoomFactor, ZoomFactorD;
	float				CamXsize, CamXsizeD, CamYsize, CamYsizeD;
	float 				f1OverLength;
	static PVRVERTEX 	PVRVertices[NUM_VERTICES];
	static km_2d_vec	UVs[NUM_VERTICES];
	km_vector			Tra, Sca, Rot;
	float				Theta;
	TRANSFORM			T;
	km_vector			LightLocal;
	km_vector			LightDir = {0.6667f, 0.6667f, -0.6667f}; 
	float				dd = 0.05f;

/***************************************************************************/
/**	サブルーチン ***********************************************************/
/***************************************************************************/

/***************************************************************************/
/**	Sphereテクスチャマッピング *********************************************/
/***************************************************************************/
void DoSphericalTextureMapping (int nVertices, km_vector Vertices[], km_2d_vec UVs[], km_vector Centre, float fU, float fV)
{
	int k;

	for (k = 0; k < nVertices; ++k)
	{
		float fX = Vertices[k][0] - Centre[0];

		UVs[k][0] = (((float) atan2 (Vertices[k][2] - Centre[2], fX) + PI) * ONEOVERTWOPI) * fU;
		UVs[k][1] = (((float) atan2 (Vertices[k][1] - Centre[1], fX) + PI) * ONEOVERTWOPI) * fV;
	}
}

/***************************************************************************/
/**	Cylindricalテクスチャマッピング ****************************************/
/***************************************************************************/
void DoCylindricalTextureMapping (int nVertices, km_vector Vertices[], km_2d_vec UVs[], km_vector Centre, km_2d_vec CVec, float fU, float fV)
{
	int k;

	for (k = 0; k < nVertices; ++k)
	{
		float fX = Vertices[k][0] - Centre[0];
		float fY = Vertices[k][1] - Centre[1];
		float fZ = Vertices[k][2] - Centre[2];

		UVs[k][0] = (((float) atan2 (fZ, fX) + PI) * ONEOVERTWOPI) * fU;
		UVs[k][1] = fY * fV;
	}
}

/****************************************************************************/
/**	Check KAMUI function status *********************************************/
/****************************************************************************/
void	Check_Status(KMSTATUS status, char * func)
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
kmtri_triangles ( KMVERTEXBUFFDESC		BufferDesc,
				  PKMSTRIPHEAD			pStripHead,
				  int  					nNumFaces,
				  int  					pFaces[][3],
				  PPVRVERTEX  			pVertices )
{
	KMSTATUS	status;
	int			i;
	KMVERTEX_03	Ver03;

	kmStartStrip(&BufferDesc, pStripHead);
	for(i = 0; i < nNumFaces; i++)
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
	kmEndStrip(&BufferDesc);
}

/****************************************************************************/
/**	kmtri_triangles for 2 parameter : modifier volume variant ***************/
/****************************************************************************/
void 
kmtri_triangles2( KMVERTEXBUFFDESC		BufferDesc,
				  PKMSTRIPHEAD			pStripHead,
				  int  					nNumFaces,
				  int  					pFaces[][3],
				  PPVRVERTEX  			pVertices )
{
	KMSTATUS		status;
	int				i;
	KMVERTEX_11		Ver;

	/* 頂点登録開始 */
	kmStartStrip(&BufferDesc,pStripHead);
	for(i = 0; i < nNumFaces; i++)
	{

		Ver.ParamControlWord		= KM_VERTEXPARAM_NORMAL;
		Ver.fX						= pVertices[pFaces[i][0]].fX;
		Ver.fY						= pVertices[pFaces[i][0]].fY;
#if defined(_STRICT_UNION_)
		Ver.u.fZ					= pVertices[pFaces[i][0]].fInvW;
#else
		Ver.fZ						= pVertices[pFaces[i][0]].fInvW;
#endif
		Ver.fU0m					= pVertices[pFaces[i][0]].fUOverW;
		Ver.fV0m					= pVertices[pFaces[i][0]].fVOverW;
		Ver.fU1m					= pVertices[pFaces[i][0]].fUOverW;
		Ver.fV1m					= pVertices[pFaces[i][0]].fVOverW;
		Ver.uBaseRGB0m.dwPacked		= pVertices[pFaces[i][0]].u32Colour;
		Ver.uBaseRGB1m.dwPacked		= pVertices[pFaces[i][0]].u32Colour;
		Ver.uOffsetRGB0m.dwPacked	= pVertices[pFaces[i][0]].u32Specular;
		Ver.uOffsetRGB1m.dwPacked	= pVertices[pFaces[i][0]].u32Specular;

		status = kmSetVertex(&BufferDesc,&Ver,KM_VERTEXTYPE_11,sizeof(KMVERTEX_11) );
		Check_Status(status, "kmSetVertex");

		Ver.ParamControlWord		= KM_VERTEXPARAM_NORMAL;
		Ver.fX						= pVertices[pFaces[i][1]].fX;
		Ver.fY						= pVertices[pFaces[i][1]].fY;
#if defined(_STRICT_UNION_)
		Ver.u.fZ					= pVertices[pFaces[i][1]].fInvW;
#else
		Ver.fZ						= pVertices[pFaces[i][1]].fInvW;
#endif
		Ver.fU0m					= pVertices[pFaces[i][1]].fUOverW;
		Ver.fV0m					= pVertices[pFaces[i][1]].fVOverW;
		Ver.fU1m					= pVertices[pFaces[i][1]].fUOverW;
		Ver.fV1m					= pVertices[pFaces[i][1]].fVOverW;
		Ver.uBaseRGB0m.dwPacked		= pVertices[pFaces[i][1]].u32Colour;
		Ver.uBaseRGB1m.dwPacked		= pVertices[pFaces[i][1]].u32Colour;
		Ver.uOffsetRGB0m.dwPacked	= pVertices[pFaces[i][1]].u32Specular;
		Ver.uOffsetRGB1m.dwPacked	= pVertices[pFaces[i][1]].u32Specular;

		status = kmSetVertex(&BufferDesc,&Ver,KM_VERTEXTYPE_11,sizeof(KMVERTEX_11) );
		Check_Status(status, "kmSetVertex");

		Ver.ParamControlWord		= KM_VERTEXPARAM_ENDOFSTRIP;
		Ver.fX						= pVertices[pFaces[i][2]].fX;
		Ver.fY						= pVertices[pFaces[i][2]].fY;
#if defined(_STRICT_UNION_)
		Ver.u.fZ					= pVertices[pFaces[i][2]].fInvW;
#else
		Ver.fZ						= pVertices[pFaces[i][2]].fInvW;
#endif
		Ver.fU0m					= pVertices[pFaces[i][2]].fUOverW;
		Ver.fV0m					= pVertices[pFaces[i][2]].fVOverW;
		Ver.fU1m					= pVertices[pFaces[i][2]].fUOverW;
		Ver.fV1m					= pVertices[pFaces[i][2]].fVOverW;
		Ver.uBaseRGB0m.dwPacked		= pVertices[pFaces[i][2]].u32Colour;
		Ver.uBaseRGB1m.dwPacked		= pVertices[pFaces[i][2]].u32Colour;
		Ver.uOffsetRGB0m.dwPacked	= pVertices[pFaces[i][2]].u32Specular;
		Ver.uOffsetRGB1m.dwPacked	= pVertices[pFaces[i][2]].u32Specular;

		status = kmSetVertex(&BufferDesc,&Ver,KM_VERTEXTYPE_11,sizeof(KMVERTEX_11) );
		Check_Status(status, "kmSetVertex");
	}
	kmEndStrip(&BufferDesc);
}

/****************************************************************************/
/**	kmtri_shadow ************************************************************/
/****************************************************************************/
void 
kmtri_shadow (	KMVERTEXBUFFDESC		BufferDesc,
				PKMSTRIPHEAD			pStripHead,
				int						nNumFaces,
				int						pFaces[][3],
				PPVRVERTEX				pVertices )
{
	KMSTATUS	status;
	int			i;
	KMVERTEX_17	Ver;	/* Shadow Volume */

	/*---------------------------------------------------- First Polygon */
	kmChangeStripModifierInstruction(pStripHead,KM_MODIFIER_INCLUDE_FIRST_POLY);
	kmStartStrip(&BufferDesc,pStripHead);

	Ver.ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;
	Ver.fAX					= pVertices[pFaces[0][0]].fX;
	Ver.fAY					= pVertices[pFaces[0][0]].fY;
#if defined(_STRICT_UNION_)
	Ver.uA.fAZ				= pVertices[pFaces[0][0]].fInvW;
#else
	Ver.fAZ					= pVertices[pFaces[0][0]].fInvW;
#endif
	Ver.fBX					= pVertices[pFaces[0][1]].fX;
	Ver.fBY					= pVertices[pFaces[0][1]].fY;
#if defined(_STRICT_UNION_)
	Ver.uB.fBZ				= pVertices[pFaces[0][1]].fInvW;
#else
	Ver.fBZ					= pVertices[pFaces[0][1]].fInvW;
#endif
	Ver.fCX					= pVertices[pFaces[0][2]].fX;
	Ver.fCY					= pVertices[pFaces[0][2]].fY;
#if defined(_STRICT_UNION_)
	Ver.uC.fCZ				= pVertices[pFaces[0][2]].fInvW;
#else
	Ver.fCZ					= pVertices[pFaces[0][2]].fInvW;
#endif

	status = kmSetVertex(&BufferDesc,&Ver,KM_VERTEXTYPE_17,sizeof(KMVERTEX17) );
	Check_Status(status, "kmSetVertex");

	kmEndStrip(&BufferDesc);

	/*---------------------------------------------------- Normal Polygon */
	kmChangeStripModifierInstruction(pStripHead,KM_MODIFIER_NORMAL_POLY);
	kmStartStrip(&BufferDesc,pStripHead);

	for(i = 1; i < (nNumFaces - 1); i++)
	{
		Ver.ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;
		Ver.fAX					= pVertices[pFaces[i][0]].fX;
		Ver.fAY					= pVertices[pFaces[i][0]].fY;
#if defined(_STRICT_UNION_)
		Ver.uA.fAZ				= pVertices[pFaces[i][0]].fInvW;
#else
		Ver.fAZ					= pVertices[pFaces[i][0]].fInvW;
#endif
		Ver.fBX					= pVertices[pFaces[i][1]].fX;
		Ver.fBY					= pVertices[pFaces[i][1]].fY;
#if defined(_STRICT_UNION_)
		Ver.uB.fBZ				= pVertices[pFaces[i][1]].fInvW;
#else
		Ver.fBZ					= pVertices[pFaces[i][1]].fInvW;
#endif
		Ver.fCX					= pVertices[pFaces[i][2]].fX;
		Ver.fCY					= pVertices[pFaces[i][2]].fY;
#if defined(_STRICT_UNION_)
		Ver.uC.fCZ				= pVertices[pFaces[i][2]].fInvW;
#else
		Ver.fCZ					= pVertices[pFaces[i][2]].fInvW;
#endif

		status = kmSetVertex(&BufferDesc,&Ver,KM_VERTEXTYPE_17,sizeof(KMVERTEX17) );
		Check_Status(status, "kmSetVertex");
	}
	kmEndStrip(&BufferDesc);

	/*---------------------------------------------------- Last Polygon */
	kmChangeStripModifierInstruction(pStripHead,KM_MODIFIER_INCLUDE_LAST_POLY);
	kmStartStrip(&BufferDesc,pStripHead);


	Ver.ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;
	Ver.fAX					= pVertices[pFaces[(nNumFaces - 1)][0]].fX;
	Ver.fAY					= pVertices[pFaces[(nNumFaces - 1)][0]].fY;
#if defined(_STRICT_UNION_)
	Ver.uA.fAZ				= pVertices[pFaces[(nNumFaces - 1)][0]].fInvW;
#else
	Ver.fAZ					= pVertices[pFaces[(nNumFaces - 1)][0]].fInvW;
#endif
	Ver.fBX					= pVertices[pFaces[(nNumFaces - 1)][1]].fX;
	Ver.fBY					= pVertices[pFaces[(nNumFaces - 1)][1]].fY;
#if defined(_STRICT_UNION_)
	Ver.uB.fBZ				= pVertices[pFaces[(nNumFaces - 1)][1]].fInvW;
#else
	Ver.fBZ					= pVertices[pFaces[(nNumFaces - 1)][1]].fInvW;
#endif
	Ver.fCX					= pVertices[pFaces[(nNumFaces - 1)][2]].fX;
	Ver.fCY					= pVertices[pFaces[(nNumFaces - 1)][2]].fY;
#if defined(_STRICT_UNION_)
	Ver.uC.fCZ				= pVertices[pFaces[(nNumFaces - 1)][2]].fInvW;
#else
	Ver.fCZ					= pVertices[pFaces[(nNumFaces - 1)][2]].fInvW;
#endif

	status = kmSetVertex(&BufferDesc,&Ver,KM_VERTEXTYPE_17,sizeof(KMVERTEX17) );
	Check_Status(status, "kmSetVertex");
	kmEndStrip(&BufferDesc);
}


/***************************************
 *	VertexType03用KMSTRIPHEADの構築
 ***************************************/
void	InitStripContext03(
								PKMSTRIPCONTEXT	pStripContext,
								PKMSTRIPHEAD	pStripHead,
								PKMSURFACEDESC	pTextureSurface
							)
{
	memset( pStripContext, 0, sizeof(KMSTRIPCONTEXT));	/* Crear Context */
	memset( pStripHead, 0, sizeof(KMSTRIPHEAD));		/* Crear Head */

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
	pStripContext->ImageControl[KM_IMAGE_PARAM1].pTextureSurfaceDesc= pTextureSurface;
  
	kmGenerateStripHead03( pStripHead,pStripContext);
}

/***************************************
 *	VertexType11用KMSTRIPHEADの構築
 ***************************************/
void	InitStripContext11(
								PKMSTRIPCONTEXT	pStripContext,
								PKMSTRIPHEAD	pStripHead,
								PKMSURFACEDESC	pTextureSurface1,
								PKMSURFACEDESC	pTextureSurface2
							)
{
	memset( pStripContext, 0, sizeof(KMSTRIPCONTEXT));	/* Crear Context */
	memset( pStripHead, 0, sizeof(KMSTRIPHEAD));		/* Crear Head */

	pStripContext->nSize											= sizeof(KMTWOVOLUMESTRIPCONTEXT);
	pStripContext->StripControl.nListType							= KM_OPAQUE_POLYGON;
	pStripContext->StripControl.nUserClipMode						= KM_USERCLIP_DISABLE;
	pStripContext->StripControl.bOffset								= KM_FALSE;
	pStripContext->StripControl.bGouraud								= KM_TRUE;
	pStripContext->ObjectControl.nDepthCompare						= KM_GREATER;
	pStripContext->ObjectControl.nCullingMode						= KM_NOCULLING;
	pStripContext->ObjectControl.bZWriteDisable						= KM_FALSE;
	pStripContext->ObjectControl.bDCalcControl						= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nSRCBlendingMode	= KM_ONE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nDSTBlendingMode	= KM_ZERO;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bSRCSelect			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bDSTSelect			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFogMode			= KM_NOFOG;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bColorClamp			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bUseAlpha			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bIgnoreTextureAlpha	= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFlipUV				= KM_NOFLIP;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nClampUV			= KM_NOCLAMP;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFilterMode			= KM_POINT_SAMPLE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bSuperSampleMode	= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].dwMipmapAdjust		= KM_MIPMAP_D_ADJUST_1_00;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nTextureShadingMode	= KM_MODULATE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].pTextureSurfaceDesc	= pTextureSurface1;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].nSRCBlendingMode	= KM_ONE;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].nDSTBlendingMode	= KM_ZERO;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].bSRCSelect			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].bDSTSelect			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].nFogMode			= KM_NOFOG;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].bColorClamp			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].bUseAlpha			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].bIgnoreTextureAlpha	= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].nFlipUV				= KM_NOFLIP;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].nClampUV			= KM_NOCLAMP;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].nFilterMode			= KM_POINT_SAMPLE;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].bSuperSampleMode	= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].dwMipmapAdjust		= KM_MIPMAP_D_ADJUST_1_00;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].nTextureShadingMode	= KM_MODULATE;
	pStripContext->ImageControl[KM_IMAGE_PARAM2].pTextureSurfaceDesc	= pTextureSurface2;

	kmGenerateStripHead11( pStripHead,pStripContext);

}

/***************************************
 *	VertexType17用KMSTRIPHEADの構築
 ***************************************/
void	InitStripContext17(
								PKMSTRIPCONTEXT	pStripContext,
								PKMSTRIPHEAD	pStripHead
							)
{
	memset( pStripContext, 0, sizeof(KMSTRIPCONTEXT));	/* Crear Context */
	memset( pStripHead, 0, sizeof(KMSTRIPHEAD));		/* Crear Head */

	pStripContext->nSize						 						= sizeof(KMSTRIPCONTEXT);
	pStripContext->StripControl.nListType							= KM_OPAQUE_MODIFIER;
	pStripContext->StripControl.nUserClipMode						= KM_USERCLIP_DISABLE;
	pStripContext->ObjectControl.nCullingMode						= KM_NOCULLING;
	pStripContext->ObjectControl.dwModifierInstruction				= KM_MODIFIER_INCLUDE_FIRST_POLY;

	kmGenerateStripHead17( pStripHead,pStripContext);
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
	BV[0].fBaseAlpha		=   1.0f;
	BV[0].fBaseRed			=   1.0f;
	BV[0].fBaseGreen		=   1.0f;
	BV[0].fBaseBlue			=   0.0f;

	/* Vertex #2 */
	BV[1].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
	BV[1].fX				= 320.0f;
	BV[1].fY				=   0.0f;
#if defined(_STRICT_UNION_)
	BV[1].u.fZ				=  0.0001f;
#else
	BV[1].fZ				=  0.0001f;
#endif
	BV[1].fBaseAlpha		=   1.0f;
	BV[1].fBaseRed			=   0.5f;
	BV[1].fBaseGreen		=   0.1f;
	BV[1].fBaseBlue			=   0.0f;

	/* Vertex #3 */
	BV[2].ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;
	BV[2].fX				= 639.0f;
	BV[2].fY				= 479.0f;
#if defined(_STRICT_UNION_)
	BV[2].u.fZ				=  0.0001f;
#else
	BV[2].fZ				=  0.0001f;
#endif
	BV[2].fBaseAlpha		=   1.0f;
	BV[2].fBaseRed			=   1.0f;
	BV[2].fBaseGreen		=   1.0f;
	BV[2].fBaseBlue			=   0.0f;

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

/***************************************************************************/
/** シーンの初期化 : Initialize scene **************************************/
/***************************************************************************/

void	InitScene(void)
{
	int	k;
	km_vector  		MeshCentre = {0.0f, -2.0f, 4.0f};
	km_2d_vec  		MeshCVec = {0.0f, 0.0f};

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

	/**********/
	/* 初期化 */
	/**********/
	pFB[0] = &PrimarySurfaceDesc;
	pFB[1] = &BackSurfaceDesc;
	/* VertexBufferPointer(set5) */
#if 0
	dwDataPtr = (PKMDWORD)0xACB00000;
#else
	dwDataPtr = (PKMDWORD)(((KMDWORD)syMalloc(0x360000) & 0x0FFFFFFFUL) | 0xA0000000);
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
	SystemConfig.nVertexBufferSize		=	0x180000*2;	/* 1.6MB *2 */
	SystemConfig.nPassDepth				=	1;
	SystemConfig.Pass[0].dwRegionArrayFlag = KM_PASSINFO_AUTOSORT;
	SystemConfig.Pass[0].fBufferSize[0] =  33.0f;
	SystemConfig.Pass[0].fBufferSize[1] =  33.0f;
	SystemConfig.Pass[0].fBufferSize[2] =  17.0f;
	SystemConfig.Pass[0].fBufferSize[3] =  17.0f;
	SystemConfig.Pass[0].fBufferSize[4] =   0.0f;
	kmSetSystemConfiguration(&SystemConfig);

	/*-----------------------------------------------------------------------------------*/
	/* Initialize DisplayString routine */
	txt_InitDisplayString();

	/*----------------------------------------------------------------------------------- */
	/* initialize maple read library */
#if 0
	vInitMaple();
#endif

/****************************************************************************/
/**	変数の初期化 ************************************************************/
/****************************************************************************/

		Tra[0] = 0.0f;			/* Translate X */
		Tra[1] = 200.0f;		/* Translate Y */
		Tra[2] = 1600.0f;		/* Translate Z */

		Sca[0] = 60.0f;			/* Scale X */
		Sca[1] = 60.0f;			/* Scale Y */
		Sca[2] = 60.0f;			/* Scale Z */

		Rot[0] = 0.333f;		/* Rotate X */
		Rot[1] = 1.0f;			/* Rotate Y */
		Rot[2] = 0.667f;		/* Rotate Z */

		Theta = 0.35f;			/* Ｙ軸方向の現在の回転角度 */

		OxDash = 320.0f;		/* Camera X Centre */
		OyDash = 240.0f;		/* Camera Y Centre */

		ZoomFactor	= 4.0f;
		ZoomFactorD	= 0.01f;
		CamXsize	= 0.3f;
		CamXsizeD	= 0.001f;
		CamYsize	= 0.3f;
		CamYsizeD	= 0.001f;

		/*-------------------------------------------------------------------------------- */
		/* 性能測定用各種変数の初期化 */

		frame		= 0;

#if defined(_DISP_PERFORMANCE_)
	totalTime	= 0;
	StartTime	= syTmrGetCount();
#endif	/* defined(_DISP_PERFORMANCE_) */

/****************************************************************************/
/**	法線ベクトルの正規化 ****************************************************/
/****************************************************************************/
		for (k = 0; k < NUM_VERTICES; ++k)
		{
			f1OverLength =  1.0f / (float) sqrt (Normals[k][0] * Normals[k][0] + 
												 Normals[k][1] * Normals[k][1] + 
												 Normals[k][2] * Normals[k][2] );
			Normals[k][0] *= f1OverLength;
			Normals[k][1] *= f1OverLength;
			Normals[k][2] *= f1OverLength;
		}

/****************************************************************************/
/**	テクスチャマッピング ****************************************************/
/****************************************************************************/
	/*----------------------------------------------------------------------------------- */
	/* Create texture surface */
	nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&TexSurfaceDesc1,		/* OUT	PKMSURFACEDESC	pSurfaceDesc */
		TEX1_U,					/*	IN	KMINT32			nWidth  */
		TEX1_V,					/*	IN	KMINT32			nHeight  */
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType */
	);
	Check_Status(status, "kmCreateTextureSurface");

	nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&TexSurfaceDesc2,		/* OUT	PKMSURFACEDESC	pSurfaceDesc */
		TEX2_U,					/*	IN	KMINT32			nWidth  */
		TEX2_V,					/*	IN	KMINT32			nHeight  */
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType */
	);
	Check_Status(status, "kmCreateTextureSurface");

	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
	pTexture01 = (unsigned long *)&nef_rivets;
	status = kmLoadTexture(&TexSurfaceDesc1,	/* PKMSURFACEDESC pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))			/* PKMDWORD pTexture */
							);
	Check_Status(status, "kmLoadTexture");

	pTexture01 = (unsigned long *)&nef_pvrlogo;
	status = kmLoadTexture(&TexSurfaceDesc2,	/* PKMSURFACEDESC pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))			/* PKMDWORD pTexture */
							);
	Check_Status(status, "kmLoadTexture");

	switch(tex_map_type)
	{
		default:
		case 1:
			DoSphericalTextureMapping (NUM_VERTICES, Vertices, UVs, MeshCentre, 10.0f, 0.5f);
			break;
		case 2:
			DoCylindricalTextureMapping (NUM_VERTICES, Vertices, UVs, MeshCentre, MeshCVec, 10.0f, 0.5f);
			break;
		case 3:
			break;
	}

/****************************************************************************/
/**	STRIP Contextの初期化 **************************************************/
/****************************************************************************/
	/* for Normal object -----------------------------------------------------  */
	/* VertexType03用KMSTRIPHEADの構築 */
	InitStripContext03(
						&StripContext03,
						&StripHead03,
						&TexSurfaceDesc1);

	/* for 2 parameter object  -------------------------------------------  */
	/* VertexType11用KMSTRIPHEADの構築 */
	InitStripContext11(
						&StripContext11,
						&StripHead11,
						&TexSurfaceDesc1,
						&TexSurfaceDesc2);

	/* for shadow parameter -------------------------------------------  */
	/* VertexType17用KMSTRIPHEADの構築 */
	InitStripContext17(
						&StripContext17,
						&StripHead17);

/****************************************************************************/
/**	Background Plane setting ************************************************/
/****************************************************************************/
	/*----------------------------------------------------------------------------------- */
	/* set background plane */
	InitBackGround();
}

/****************************************************************************/
/**	アニメーション **********************************************************/
/****************************************************************************/
void	SceneLoop(void)
{
		int 		k;
		float		*pV;
		PVRVERTEX	*pSV;
		float		fFogRescale = 1.05f;	/* 大きいほど、霧の影響を強く受ける */
	#if TWO_PASSES
		int 		nFaces;
	#endif


	/* シ－ンの開始	*/
	kmBeginScene(&SystemConfig);

	/* パスの開始 */
	kmBeginPass(&VertexBufferDesc);


	/*---------------------------------------- Camera */
	/* Change Zoom factor */
#if 0
	ZoomFactor += ZoomFactorD;
	if((ZoomFactor < 1.0f)||(ZoomFactor > 9.0f)) ZoomFactorD = -ZoomFactorD;
	/* Change Camera X size */
	CamXsize += CamXsizeD;
	if((CamXsize < 0.01f)||(CamXsize > 0.9f)) CamXsizeD = -CamXsizeD;
#endif

	SxDash =  ZoomFactor * 0.5f * CamXsize;	/*   zoom factor * 0.5 * CamXSize */
	SyDash = -ZoomFactor * 0.5f * CamYsize;	/* - zoom factor * 0.5 * CamYSize */
	PRINTOUT(("Zoom factor : %8.4f\n", ZoomFactor));
	PRINTOUT(("Cam  X size : %8.4f\n", CamXsize));
	PRINTOUT(("Cam  Y size : %8.4f\n", CamYsize));

	/*---------------------------------------- 行列式によるアフィン変換 */
	Theta += (dd / SPEED);				/* Ｙ軸方向回転角の増加 */
	MatrixIdentity(&T);						/* 行列式の初期化 */
	MatrixTranslate(&T, Tra);				/* 平行移動 */
	MatrixScale(&T, Sca);					/* 拡大・縮小 */
	if(move_object)
	{
		MatrixRotate(&T, km_y_axis, Theta);	/* Y軸回転 */
	}
	else
	{
		MatrixRotate(&T, km_x_axis, rx);	/* X軸回転 */
		MatrixRotate(&T, km_y_axis, ry);	/* Y軸回転 */
		MatrixRotate(&T, km_z_axis, rz);	/* Z軸回転 */
	}

	/*---------------------------------------- ライトの処理 */
	LightLocal[0] = LightDir[0]*T.Inverse[0][0] + LightDir[1]*T.Inverse[0][1] + LightDir[2]*T.Inverse[0][2];
	LightLocal[1] = LightDir[0]*T.Inverse[1][0] + LightDir[1]*T.Inverse[1][1] + LightDir[2]*T.Inverse[1][2];
	LightLocal[2] = LightDir[0]*T.Inverse[2][0] + LightDir[1]*T.Inverse[2][1] + LightDir[2]*T.Inverse[2][2];
	f1OverLength =  1.0f / (float) sqrt (LightLocal[0]*LightLocal[0] + 
										 LightLocal[1]*LightLocal[1] + 
										 LightLocal[2]*LightLocal[2]);
	LightLocal[0] *= f1OverLength;
	LightLocal[1] *= f1OverLength;
	LightLocal[2] *= f1OverLength;

	pSV = PVRVertices;					/* pSV = PVRVERTEX型構造体へのポインタ */
	pV = (float *) Vertices;			/* pV  = 物体の頂点座標の構造体へのポインタ */

	/*********************************************************** 各頂点の投影変換:PVRVERTEX構造体の生成 */
	for (k = 0; k < NUM_VERTICES; ++k, pV += 3, ++pSV)
	{
		float fXws;
		float fYws;
		float fZws;
		float f1OverZ;
		float fI;
		unsigned char u8Col[3];

		/*------------------------------------------------------ 頂点座標の投影 */
		#if TWO_PASSES
			fDot[k] = 	T.Inverse[0][2] * Normals[k][0] + 
						T.Inverse[1][2] * Normals[k][1] + 
						T.Inverse[2][2] * Normals[k][2];
		#endif
		fXws = (pV[0] * T.Matrix[0][0] + pV[1] * T.Matrix[0][1] + pV[2] * T.Matrix[0][2] + T.Matrix[0][3]) * fFogRescale;
		fYws = (pV[0] * T.Matrix[1][0] + pV[1] * T.Matrix[1][1] + pV[2] * T.Matrix[1][2] + T.Matrix[1][3]) * fFogRescale;
		fZws = (pV[0] * T.Matrix[2][0] + pV[1] * T.Matrix[2][1] + pV[2] * T.Matrix[2][2] + T.Matrix[2][3]) * fFogRescale;

		fZws *= 1.0f / 2000.0f;
		f1OverZ = 1.0f / fZws;

		pSV->fX = (SxDash * fXws * f1OverZ) + OxDash;		/* 投影面上のＸ座標 */
		pSV->fY = (SyDash * fYws * f1OverZ) + OyDash;		/* 投影面上のＹ座標 */
		pSV->fZ = fZws;										/* Dummy奥行き座標 */
		pSV->fInvW = SxDash * f1OverZ;						/* 奥行き情報 */

		/*------------------------------------------------------ 頂点の色の計算 */
		fI = Normals[k][0] * LightLocal[0] + Normals[k][1] * LightLocal[1] + Normals[k][2] * LightLocal[2];
		if (fI < 0.0f)	fI = -fI;
		if (fI > 1.0f)	fI = 1.0f;
		fI *= 0.75f;
		fI += 0.25f;

		u8Col[0] = (unsigned char) (fI * (LightRed   * 0.01f) * 255.0f);
		u8Col[1] = (unsigned char) (fI * (LightGreen * 0.01f) * 255.0f);
		u8Col[2] = (unsigned char) (fI * (LightBlue  * 0.01f) * 255.0f);

		/*------------------------------------------------------- 頂点の透明度の決定 */
		{
			BYTE u8Alpha;
			float f;
			f = (float) cos ((frame * 0.1) + (fYws * 0.02)) + 1.0f;
			u8Alpha = (BYTE) (f * 127.5);
			pSV->u32Colour		= RGBA (u8Col[0], u8Col[1], u8Col[2], u8Alpha);
			pSV->u32Specular	= RGBColour (u8Alpha, u8Alpha, u8Alpha);
		}
		pSV->fUOverW = UVs[k][0]; /* * pSV->fInvW; */
		pSV->fVOverW = UVs[k][1]; /* * pSV->fInvW; */
	}	/* End of for */

	/*----------------------------------------------------------- ？？？？？？？？ */
	#if TWO_PASSES
		nFaces = 0;
		for (k = 0; k < polygons; ++k)
		{
			if ((fDot[Faces[k][0]] + fDot[Faces[k][1]] + fDot[Faces[k][2]]) <= 0.0f)
			{
				PVRFaces[nFaces][0] = Faces[k][0];
				PVRFaces[nFaces][1] = Faces[k][1];
				PVRFaces[nFaces][2] = Faces[k][2];
				nFaces++;
			}
		}

		if (nFaces)
		{
			kmtri_triangles2 (	VertexBufferDesc,	/*	KMVERTEXBUFFDESC	BufferDesc */
								&StripHead11,		/*	PKMSTRIPHEAD		pStripHead */
								nFaces,				/*	int					nNumFaces */
								PVRFaces,			/*	int					pFaces[][3] */
								PVRVertices			/*	PPVRVERTEX			pVertices */
								);
		}
		nFaces = 0;

		for (k = 0; k < polygons; ++k)
		{
			if ((fDot[Faces[k][0]] + fDot[Faces[k][1]] + fDot[Faces[k][2]]) > 0.0f)
			{
				PVRFaces[nFaces][0] = Faces[k][0];
				PVRFaces[nFaces][1] = Faces[k][1];
				PVRFaces[nFaces][2] = Faces[k][2];
				nFaces++;
			}
		}
		if (nFaces)
		{
			kmtri_triangles2 (	VertexBufferDesc,	/*	KMVERTEXBUFFDESC	BufferDesc */
								&StripHead11,		/*	PKMSTRIPHEAD		pStripHead */
								nFaces,				/*	int					nNumFaces */
								PVRFaces,			/*	int					pFaces[][3] */
								PVRVertices			/*	PPVRVERTEX			pVertices */
								);
	}
	#else
		/* 2 parameter */
		kmtri_triangles2 (	VertexBufferDesc,	/*	KMVERTEXBUFFDESC	BufferDesc */
							&StripHead11,		/*	PKMSTRIPHEAD		pStripHead */
							polygons,			/*	int					nNumFaces */
							Faces,				/*	int					pFaces[][3] */
							PVRVertices			/*	PPVRVERTEX			pVertices */
							);
	#endif

/****************************************************************************/
/**	影となる空間の設定 ******************************************************/
/****************************************************************************/
	if(shadow_vol_type > 1)
	{
		/*-------------------------------- 影となる空間を定義する頂点座標 */
		float SV[8][3] =
		{
			{-1.0f,	-1.0f,	-1.0f},		/* Vertex 0        5------6   */
			{-1.0f,	-1.0f,   1.0f},		/* Vertex 1       /      /    */
			{ 1.0f,	-1.0f,	 1.0f},		/* Vertex 2      /      / |   */
			{ 1.0f,	-1.0f,	-1.0f},		/* Vertex 3     4------7  |   */
			{-1.0f,	 1.0f,	-1.0f},		/* Vertex 4     |   1  | / 2  */
			{-1.0f,	 1.0f,	 1.0f},		/* Vertex 5     |      |/     */
			{ 1.0f,	 1.0f,	 1.0f},		/* Vertex 6     0------3      */
			{ 1.0f,	 1.0f,	-1.0f}		/* Vertex 7                   */
		};
		/*-------------------------------- 影となる空間を定義する頂点の組み合わせ */
		static int SF[12][3] =
		{
			{0, 5, 4},		/* Face  0  : Left   1 */
			{0, 1, 5},		/* Face  1  : Left   2 */
			{1, 6, 5},		/* Face  2  : Back   1 */
			{1, 2, 6},		/* Face  3  : Back   2 */
			{2, 7, 6},		/* Face  4  : Right  1 */
			{2, 3, 7},		/* Face  5  : Right  2 */
			{3, 4, 7},		/* Face  6  : Front  1 */
			{3, 0, 4},		/* Face  7  : Front  2 */
			{4, 6, 7},		/* Face  8  : Top    1 */
			{4, 5, 6},		/* Face  9  : Top    2 */
			{3, 1, 0},		/* Face 10  : Bottom 1 */
			{3, 2, 1}		/* Face 11  : Bottom 2 */
		};
		/*-------------------------------- 影となる空間に対するジオメトリ演算 */
		PVRVERTEX 	ShadowVertices[8];
		km_vector	SSca = {100.0f, 100.0f,  100.0f};	/* Scaling   : 拡大・縮小量 */
		km_vector	STra = {  0.0f,   0.0f, 1600.0f};	/* Transform : 平行移動量 */
		km_vector	SRot = {  0.5f,   0.5f,    0.5f};	/* Rotation  : 回転軸 */

		MatrixIdentity(&T);								/* 行列式の初期化 */
		MatrixTranslate(&T, STra);						/* 平行移動 */
		MatrixScale(&T, SSca);							/* 拡大・縮小 */
		MatrixRotate(&T, SRot, Theta);					/* 回転 */
		for (k = 0; k < 8; ++k)
		{
			float f1OverZ, fX, fY, fZ;
			fX = (SV[k][0] * T.Matrix[0][0] + 
				  SV[k][1] * T.Matrix[0][1] + 
				  SV[k][2] * T.Matrix[0][2] + T.Matrix[0][3]) * fFogRescale;
			fY = (SV[k][0] * T.Matrix[1][0] + 
				  SV[k][1] * T.Matrix[1][1] + 
				  SV[k][2] * T.Matrix[1][2] + T.Matrix[1][3]) * fFogRescale;
			fZ = (SV[k][0] * T.Matrix[2][0] + 
				  SV[k][1] * T.Matrix[2][1] + 
				  SV[k][2] * T.Matrix[2][2] + T.Matrix[2][3]) * fFogRescale;
			fZ *= (1.0f / 2000.0f);
			f1OverZ = 1.0f / fZ;
			ShadowVertices[k].fX = (SxDash * fX * f1OverZ) + OxDash;
			ShadowVertices[k].fY = (SyDash * fY * f1OverZ) + OyDash;
			ShadowVertices[k].fZ = fZ;
			ShadowVertices[k].fInvW = SxDash * f1OverZ;
		}

		/*----------------------------------------------------------------------------------- */
		/*------ Shadow volume のVertexの設定  */
		if(disp_shadow_vol)
		{
			kmtri_triangles (	VertexBufferDesc,	/*	KMVERTEXBUFFDESC	BufferDesc */
								&StripHead03,		/*	PKMSTRIPHEAD		pStripHead */
								12,					/*	int					nNumFaces */
								SF,					/*	int					pFaces[][3] */
								ShadowVertices		/*	PPVRVERTEX			pVertices */
								);
		}
		else
		{
			kmtri_shadow (	VertexBufferDesc,		/*	KMVERTEXBUFFDESC	BufferDesc */
							&StripHead17,			/*	PKMSTRIPHEAD		pStripHead */
							12,						/*	int					nNumFaces */
							SF,						/*	int					pFaces[][3] */
							ShadowVertices			/*	PPVRVERTEX			pVertices */
							);
		}
	} /* end of if(gen_shadow_vol) */

/****************************************************************************/
/**	画面描画 ****************************************************************/
/****************************************************************************/

	txt_SetCursor(0,1);
#if defined(_DISP_PERFORMANCE_)
	/* Write Date & Time on screen ---------------------------------------------*/
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
	status = kmRender(KM_RENDER_FLIP);
/*	status = kmRender(KM_RENDER_FLIP);
	Check_Status(status, "kmRender");*/

	/* シ－ンの終了 */
	kmEndScene(&SystemConfig);

	/*----------------------------------------------------------------------------------- */
	/* Flip screen */
/*	status = kmFlipFrameBuffer();
	Check_Status(status, "kmFlipFrameBuffer");*/

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

	totalTime += nowTime;										/* 累積時間 */
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

/****************************************************************************/
/**	main ********************************************************************/
/****************************************************************************/ 
int	Kamui_Init(void)
{
	txt_ClearScreen();	/* Clear text screen */
	PRINTOUT(("** KMNEFERT(KAMUI2&Shinobi) **\n"));
	InitScene();	/* Initialize */

#if 0
	while(1)
	{
		ReadMaple ();
		SceneLoop();	/* Rendering */
	}
#endif
	return 0;
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
		ZoomFactor = 4.0f;
		dd = 0.0f;
	}

	/* UP cross key */
	if ( per->on & PDD_DGT_KU )
	{
		ZoomFactor -= 0.05f;
		if(ZoomFactor < 0.1f) ZoomFactor = 0.1f;
	}
	/* DOWN cross key */
	if ( per->on & PDD_DGT_KD )
	{
		ZoomFactor += 0.05f;
		if(ZoomFactor > 20.0f) ZoomFactor = 20.0f;
	}
	/* Left cross key */
	if ( per->on & PDD_DGT_KL )
	{
		dd += 0.002f;
	}
	/* Right cross key */
	if ( per->on & PDD_DGT_KR )
	{
		dd -= 0.002f;
	}

}

/*--------------------------- End of File --------------------------------*/
