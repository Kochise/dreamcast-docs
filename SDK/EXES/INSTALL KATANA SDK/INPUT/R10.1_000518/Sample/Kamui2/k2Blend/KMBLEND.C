/******************************************************************************
 Name     : KMBLEND
 Title    : KAMUI test program "Blend" from VL
 Author   : VideoLogic Carlos Sarria / NEC Software Takeshi Muto
 Created  : Jan 1998 by VideoLogic
 Modified : June     09. 1998 by Takeshi Muto for KAMUI
			January  27. 1999 by T.Kamei 	 for KAMUI2
			February 15. 1999 by Masayuki Imanishi for Shinobi
 Description :
 Copyright : 1998 by VideoLogic Limited. All rights reserved.
******************************************************************************/
#define		_DISPLAY_STRING_						/* if defined then display strings on screen	*/
#define		_DISP_PERFORMANCE_						/* Display performance							*/

#include <stdio.h>
#include <math.h>
#include <Shinobi.h>

#
#pragma warning (disable : 4244) /* Disables float to double conversion warning */
#define _STRICT_UNION_
#define _CLX2_
#define _CLX_
#include	"kamui2.h"				/* for Kamui2 Call 									*/
#include	"dispstr.h"				/* for DisplayString								*/
#include	"vltex.h"				/* for vl sample texture							*/

#if 0
#define _KM_USE_VERTEX_MACRO_
#define _KM_USE_VERTEX_MACRO_L3_
#include    "kamuix.h"
#endif

#define 	PI	(3.1416f)
#define		RGBAColour(r, g, b, a)   ((unsigned long) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b)))
#define		RGBColour(r, g, b)	((KMUINT32) (((r) << 16) | ((g) <<  8) | (b)))
#define		RGBA(r, g, b, a)	((KMUINT32) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b)))

/* Macros for kamui */
#define		GetRED(col)			((KMFLOAT) ( ((col) & 0x00ff0000) >> 16 ) / 256.0f)
#define		GetGREEN(col)		((KMFLOAT) ( ((col) & 0x0000ff00) >>  8 ) / 256.0f)
#define		GetBLUE(col)		((KMFLOAT) ( ((col) & 0x000000ff)       ) / 256.0f)
#define		GetALPHA(col)		((KMFLOAT) ( ((col) & 0xff000000) >> 24 ) / 256.0f)

typedef float		pvr_vector[3];	/* type of pvr_vector */

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
KMVERTEXBUFFDESC	VertexBufferDesc;		/* Vertex-buffer				*/
KMDWORD				FogDensity;				/* Fog density					*/
KMDWORD				FogD = 1;

KMSTRIPCONTEXT		StripContext00;
KMSTRIPCONTEXT		StripContext03;
KMSTRIPHEAD			StripHead00_Gold;
KMSTRIPHEAD			StripHead00_Trans;
KMSTRIPHEAD			StripHead03_Gold;
KMSTRIPHEAD			StripHead03_Trans;

PKMSURFACEDESC			pFB[2];
KMDWORD					FBarea[24576 + 19456];
								/* FBstruct 4096 Entry (= 4096 * 24 / 4) *
								 * VQstruct 1024 Entry (= 1024 * 76 / 4) */
KMSYSTEMCONFIGSTRUCT	SystemConfig;
PKMDWORD				dwDataPtr;

/*------------------------------- Global Variables -----------------------------------*/
/* Globals */
KMSURFACEDESC		TexOpaq, TexTrans, TexBack, TexGold;
static unsigned		Frame			= 0;
static int			BlendSrc		= 4;	/* SRCA				*/
static int			BlendDst		= 5;	/* INVSRCA			*/
static int			BlendModulate	= TRUE;	/* MODULATE			*/
static int			AlphaSource		= 0;	/* TEXTURE ALPHA	*/
static int			PosZ			= 800;

/* Info Structure */
struct
{
	int		VertexAlpha;
	int		AlphaBlend;

} Info = { TRUE, TRUE };

/* Prototypes */
void NextFrame		(void);
void ReadMaple			(void);		/* Maple data read routine */

/* Static Prototypes */
static void SetContext			(void);
static void SetTextures			(void);
static void DisplayInformation	(void);
static void SetPlane			(int Num, PKMSTRIPHEAD pStripHead );
static void SetBackground		(PKMSURFACEDESC TextureID);


/* Macros for kamui */
#define		GetRED(col)			((KMFLOAT) ( ((col) & 0x00ff0000) >> 16 ) / 256.0f)
#define		GetGREEN(col)		((KMFLOAT) ( ((col) & 0x0000ff00) >>  8 ) / 256.0f)
#define		GetBLUE(col)		((KMFLOAT) ( ((col) & 0x000000ff)       ) / 256.0f)
#define		GetALPHA(col)		((KMFLOAT) ( ((col) & 0xff000000) >> 24 ) / 256.0f)

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
	KMSTATUS	status;
	int			i;
	PPVRVERTEX	pVert;
	KMVERTEX_00		Ver00;				/* for NO-TEXTURE-GOURAUD	*/
	KMVERTEX_03		Ver03;				/* for TEXTURE-GOURAUD		*/

	kmStartStrip(pBufferDesc,pStripHead);

	for(i = 0; i < nNumFaces; i++)
	{
		if(bTexture == TRUE)
		{
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
		}
		else
		{
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
		}
	}
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

/*-------------------------------------------------------------------------------------*
 *                                       MAIN                                          *
 *-------------------------------------------------------------------------------------*/
int Kamui_Init(void)
{
	int Control = 0, Device, Val = 0;

	txt_ClearScreen();		/* Clear text screen */
	PRINTOUT(("** KMBLEND(KAMUI2) : Blending mode test **\n"));

	kmGetVersionInfo(&VersionInfo);
	PRINTOUT(("MajorVersion      0x0%08x\n",VersionInfo.kmMajorVersion));
	PRINTOUT(("LocalVersion      0x0%08x\n",VersionInfo.kmLocalVersion));
	PRINTOUT(("kmFrameBufferSize 0x0%08x\n",VersionInfo.kmFrameBufferSize));

	/*----------------------------------------------------------------------------------- */
	/* Create frame buffer and vertex buffer */
	pFB[0] = &PrimarySurfaceDesc;
	pFB[1] = &BackSurfaceDesc;

	/* VertexBufferPointer(set5) */
	dwDataPtr = (PKMDWORD)(((KMDWORD)syMalloc(0x200000) & 0x0FFFFFFFUL) | 0xA0000000);

	SystemConfig.dwSize					=	sizeof(KMSYSTEMCONFIGSTRUCT);
	SystemConfig.flags					=	KM_CONFIGFLAG_ENABLE_CLEAR_FRAMEBUFFER;
	/* for Frame buffer */
	SystemConfig.ppSurfaceDescArray		=	pFB;		/* Array of SurfaceDesc	pointer	*/
	SystemConfig.fb.nNumOfFrameBuffer	=	2;			/* Number Of Frame Buffer		*/
	/* for Texture Memory */
	SystemConfig.nTextureMemorySize		=	0x100000*2;	/* Texture 2MB					*/
	SystemConfig.nNumOfTextureStruct	=	4096;		/* テクスチャ管理構造体の数		*/
	SystemConfig.nNumOfSmallVQStruct	=	1024;		/* VQテクスチャ管理構造体の数	*/
	SystemConfig.pTextureWork			=	&FBarea[0];	/* テクスチャ管理構造体領域		*/
	/* for Vertex buffer */
	SystemConfig.pBufferDesc			=	&VertexBufferDesc;	/* pointer to VERTEXBUFFDESC	*/
	SystemConfig.nNumOfVertexBank		=	2;
	SystemConfig.pVertexBuffer			=	dwDataPtr;	/* pointer to Vertex buffer		*/
	SystemConfig.nVertexBufferSize		=	0x100000*2;	/* 2MB 							*/
	SystemConfig.nPassDepth				=	1;
	SystemConfig.Pass[0].dwRegionArrayFlag = KM_PASSINFO_AUTOSORT | KM_PASSINFO_ENABLE_Z_CLEAR;
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

	/*----------------------------------------------------------------------------------- */
	/* some initializes */
	SetTextures ();
	SetBackground (&TexBack);
	SetContext();
    DisplayInformation ();

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

	unsigned long	Pad[2];		/* maple data								*/

	txt_SetCursor(0,16);

	per = pdGetPeripheral(PDD_PORT_A0);

	/* UP cross key */
	if ( per->on & PDD_DGT_KU )
	{
		if( PosZ > 0 )
		{
			PosZ -= 10;
		}
		DisplayInformation ();
	}

	/* DOWN cross key */
	if ( per->on & PDD_DGT_KD )
	{
		PosZ += 10;
		DisplayInformation ();
	}

	if ( per->press & PDD_DGT_TA )
	{
		if ( (AlphaSource>0) && (Info.VertexAlpha == TRUE) || !(AlphaSource>0) )
		{
			BlendSrc++;
		}
		if (BlendSrc==8)
		{
			BlendSrc=0;
		}
		DisplayInformation ();
	}

		/* B button */
	if ( per->press & PDD_DGT_TB )
	{
		if ( (AlphaSource>0) && (Info.VertexAlpha == TRUE) || !(AlphaSource>0) )
		{
			BlendDst++;
		}

		if (BlendDst==8)
		{
			BlendDst=0;
		}

		DisplayInformation ();
	}

	/* X button */
	if ( per->press & PDD_DGT_TX )
	{
		AlphaSource++;
		if ( AlphaSource == 3 )
		{
			AlphaSource=0;
		}

		Info.VertexAlpha = (AlphaSource==1) ? 1:0;

		/* AlphaInfo = ZERO */
		if (AlphaSource==2)
		{
			BlendSrc=1;
			BlendDst=0;
		}
		DisplayInformation ();
	}

	/* Y button */
	if ( per->press & PDD_DGT_TY )
	{
		BlendModulate = !BlendModulate;
		DisplayInformation ();
	}
}

/*----------------------------------------------------------------------*
 *  Function Name   : SetContext                                        *
 *  Inputs          :                                                   *
 *  Outputs         :                                                   *
 *  Returns         :                                                   *
 *  Globals Used    :                                                   *
 *  Description     :                                                   *
 *----------------------------------------------------------------------*/
void SetContext (void)
{
	/**************************
	 * KMSTRIPHEADの構築
	 **************************/
#if 0
	/* VertexType00用 */
	memset( &StripContext00		, 	0, sizeof(StripContext00));
	memset( &StripHead00_Gold	,	0, sizeof(StripHead00_Gold));
	memset( &StripHead00_Trans	,	0, sizeof(StripHead00_Trans));

	InitStripContext00(&StripContext00, &StripHead00_Gold	);
	InitStripContext00(&StripContext00, &StripHead00_Trans	);
#endif

	/* VertexType03用 */
	memset( &StripContext03		, 	0, sizeof(StripContext03));
	memset( &StripHead03_Gold	,	0, sizeof(StripHead03_Gold));
	memset( &StripHead03_Trans	,	0, sizeof(StripHead03_Trans));

	InitStripContext03(&StripContext03, &StripHead03_Gold, 	&TexGold	);
	InitStripContext03(&StripContext03, &StripHead03_Trans,	&TexTrans	);
}

/*----------------------------------------------------------------------*
 *  Function Name   : SetTextures                                       *
 *  Inputs          :                                                   *
 *  Outputs         :                                                   *
 *  Returns         :                                                   *
 *  Globals Used    : TexOpaq TexTrans TexGold Texback                  *
 *  Description     : Loads BMP files                                   *
 *----------------------------------------------------------------------*/
void SetTextures (void)
{
	PKMDWORD			pTexture01;				/* Pointer to texture		*/
	KMTEXTURETYPE		nTextureType;			/* texture type definition	*/

	/*----------------------------------------------------------------------------------- */
	/* Create texture surface */
	nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&TexOpaq,				/* OUT	PKMSURFACEDESC	pSurfaceDesc	*/
		256,					/*	IN	KMINT32			nWidth			*/
		256,					/*	IN	KMINT32			nHeight			*/
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType	*/
	);
	Check_Status(status, "kmCreateTextureSurface #1");
	/*----------------------------------------------------------------------------------- */
	/* Create texture surface */
	nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_ARGB4444;	/* Set texture type */
	status = kmCreateTextureSurface(
		&TexTrans,				/* OUT	PKMSURFACEDESC	pSurfaceDesc	*/
		256,					/*	IN	KMINT32			nWidth			*/
		256,					/*	IN	KMINT32			nHeight			*/
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType	*/
	);
	Check_Status(status, "kmCreateTextureSurface #2");
	/*----------------------------------------------------------------------------------- */
	/* Create texture surface */
	nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&TexBack,				/* OUT	PKMSURFACEDESC	pSurfaceDesc	*/
		256,					/*	IN	KMINT32			nWidth			*/
		256,					/*	IN	KMINT32			nHeight			*/
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType	*/
	);
	Check_Status(status, "kmCreateTextureSurface #3");
	/*----------------------------------------------------------------------------------- */
	/* Create texture surface */
	nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&TexGold,				/* OUT	PKMSURFACEDESC	pSurfaceDesc	*/
		128,					/*	IN	KMINT32			nWidth			*/
		128,					/*	IN	KMINT32			nHeight			*/
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType	*/
	);
	Check_Status(status, "kmCreateTextureSurface #4");
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
	pTexture01 = (unsigned long *)&ble_opaq;
	status = kmLoadTexture(	&TexOpaq,							/* PKMSURFACEDESC pSurfaceDesc	*/
							pTexture01 + (16 / sizeof(KMDWORD))	/* PKMDWORD pTexture			*/
							);
	Check_Status(status, "kmLoadTexture #1");
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
	pTexture01 = (unsigned long *)&ble_trans;
	status = kmLoadTexture(	&TexTrans,							/* PKMSURFACEDESC pSurfaceDesc	*/
							pTexture01 + (16 / sizeof(KMDWORD))	/* PKMDWORD pTexture			*/
							);
	Check_Status(status, "kmLoadTexture #2");
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
	pTexture01 = (unsigned long *)&ble_back;
	status = kmLoadTexture(	&TexBack,							/* PKMSURFACEDESC pSurfaceDesc	*/
							pTexture01 + (16 / sizeof(KMDWORD))	/* PKMDWORD pTexture			*/
							);
	Check_Status(status, "kmLoadTexture #3");
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
	pTexture01 = (unsigned long *)&ble_gold;
	status = kmLoadTexture(&TexGold,							/* PKMSURFACEDESC pSurfaceDesc	*/
							pTexture01 + (16 / sizeof(KMDWORD))	/* PKMDWORD pTexture			*/
							);
	Check_Status(status, "kmLoadTexture #4");
}

/*----------------------------------------------------------------------*
 *  Function Name   : NextFrame                                         *
 *  Inputs          :                                                   *
 *  Outputs         :                                                   *
 *  Returns         :                                                   *
 *  Globals Used    :                                                   *
 *  Description     : Render a scene.                                   *
 *----------------------------------------------------------------------*/
void NextFrame (void)
{
	int tmpSrc;
	int tmpDst;

	/* シーンの開始 */
	kmBeginScene(&SystemConfig);
	/* パスの開始 */
	kmBeginPass(&VertexBufferDesc);

	SetPlane  (2, &StripHead03_Gold);

	if(AlphaSource > 0)
	{
		/* Texture Opaque */
		kmChangeStripTextureSurface		( &StripHead03_Trans,KM_IMAGE_PARAM1,&TexOpaq );

		if (Info.VertexAlpha == TRUE)
		{
			kmChangeStripListType( &StripHead03_Trans, KM_TRANS_POLYGON );
			kmChangeStripUseAlpha( &StripHead03_Trans, KM_IMAGE_PARAM1, KM_TRUE );

			if(BlendModulate == TRUE)
			{
				kmChangeStripTextureShadingMode	( &StripHead03_Trans, KM_IMAGE_PARAM1, KM_MODULATE_ALPHA );
			}
			else
			{
				kmChangeStripTextureShadingMode	( &StripHead03_Trans, KM_IMAGE_PARAM1, KM_DECAL_ALPHA );
			}
		}
		else
		{
			kmChangeStripListType( &StripHead03_Trans, KM_OPAQUE_POLYGON );
			kmChangeStripUseAlpha( &StripHead03_Trans, KM_IMAGE_PARAM1, KM_FALSE );

			if(BlendModulate == TRUE)
			{
				kmChangeStripTextureShadingMode	( &StripHead03_Trans, KM_IMAGE_PARAM1, KM_MODULATE );
			}
			else
			{
				kmChangeStripTextureShadingMode	( &StripHead03_Trans, KM_IMAGE_PARAM1, KM_DECAL );
			}
			BlendSrc = 1;
			BlendDst = 0;
		}
	}
	else
	{
		/* Texture Trans */
		kmChangeStripTextureSurface		( &StripHead03_Trans,KM_IMAGE_PARAM1,&TexTrans );

		kmChangeStripListType( &StripHead03_Trans, KM_TRANS_POLYGON );
		kmChangeStripUseAlpha( &StripHead03_Trans, KM_IMAGE_PARAM1, KM_TRUE );

		if(BlendModulate == TRUE)
		{
			kmChangeStripTextureShadingMode	( &StripHead03_Trans, KM_IMAGE_PARAM1, KM_MODULATE_ALPHA );
		}
		else
		{
			kmChangeStripTextureShadingMode	( &StripHead03_Trans, KM_IMAGE_PARAM1, KM_DECAL_ALPHA );
		}
	}

	/*********************/
	/* Set blending mode */
	/*********************/
	if((BlendSrc == 5)&&(BlendDst == 4))
	{
		/* Both INVSRCALPHA */
		kmChangeStripBlendingMode	( &StripHead03_Trans, KM_IMAGE_PARAM1, KM_BOTHINVSRCALPHA, KM_BOTHINVSRCALPHA );
	}
	else if((BlendSrc == 4)&&(BlendDst == 5))
	{
		/* Both SRCALPHA */
		kmChangeStripBlendingMode	( &StripHead03_Trans, KM_IMAGE_PARAM1, KM_BOTHSRCALPHA, KM_BOTHSRCALPHA );
	}
	else
	{
		/* SRC blending mode */
		switch(BlendSrc)
		{
			default:
			case 0 :	/* ZERO */
				tmpSrc = KM_ZERO;
				break;
			case 1 :	/* ONE */
				tmpSrc = KM_ONE;
				break;
			case 2 :	/* OTHER */
				tmpSrc = KM_DESTCOLOR;
				break;
			case 3 :	/* INVOTHER */
				tmpSrc = KM_INVDESTCOLOR;
				break;
			case 4 :	/* SRCA */
				tmpSrc = KM_SRCALPHA;
				break;
			case 5 :	/* INVSRCA */
				tmpSrc = KM_INVSRCALPHA;
				break;
			case 6 :	/* DSTA */
				tmpSrc = KM_DESTALPHA;
				break;
			case 7 :	/* INVDSTA */
				tmpSrc = KM_INVDESTALPHA;
				break;
		}

		/* DEST blending mode */
		switch(BlendDst)
		{
			default:
			case 0 :	/* ZERO */
				tmpDst = KM_ZERO;
				break;
			case 1 :	/* ONE */
				tmpDst = KM_ONE;
				break;
			case 2 :	/* OTHER */
				tmpDst = KM_SRCCOLOR;
				break;
			case 3 :	/* INVOTHER */
				tmpDst = KM_INVSRCCOLOR;
				break;
			case 4 :	/* SRCA */
				tmpDst = KM_SRCALPHA;
				break;
			case 5 :	/* INVSRCA */
				tmpDst = KM_INVSRCALPHA;
				break;
			case 6 :	/* DSTA */
				tmpDst = KM_DESTALPHA;
				break;
			case 7 :	/* INVDSTA */
				tmpDst = KM_INVDESTALPHA;
				break;
		}
		kmChangeStripBlendingMode		( &StripHead03_Trans, KM_IMAGE_PARAM1, tmpSrc, tmpDst );
	}

	SetPlane  (1, &StripHead03_Trans);

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

	/*----------------------------------------------------------------------------------- */
	Frame++;
}

/*----------------------------------------------------------------------*
 *  Function Name   : DisplayInformation                                *
 *  Inputs          :                                                   *
 *  Outputs         :                                                   *
 *  Returns         :                                                   *
 *  Globals Used    : BlendScr BlendDst AlphaSource BlendShd            *
 *  Description     : Displays some information.                        *
 *----------------------------------------------------------------------*/
void DisplayInformation (void)
{
	char *Flag[]     = { "FROM BMP" ,"FROM VERTEXALPHA" ,"ZERO"};
	char *BlendStr[] = { "ZERO" ,"ONE" ,"OTHER" ,"INVOTHER" ,"SRCA" ,"INVSCRA" ,"DSTA" ,"INVDSTA"};
	char *Shade[]    = { "DECAL" ,"MODULATE"};

	txt_SetCursor(0,17);

	PRINTOUT(( " A(F1) : Source        %s\n", BlendStr[BlendSrc]));
	PRINTOUT(( " B(F2) : Destination   %s\n", BlendStr[BlendDst]));
	PRINTOUT(( " X(F3) : Alpha Info    %s\n", Flag[AlphaSource]));
    PRINTOUT(( " Y(F4) : Blend         %s", Shade[BlendModulate]));

}

/*----------------------------------------------------------------------*
 *  Function Name   : SetPlane                                          *
 *  Inputs          :                                                   *
 *  Outputs         :                                                   *
 *  Returns         :                                                   *
 *  Globals Used    :                                                   *
 *  Description     : Draws an square a rotates it                      *
 *----------------------------------------------------------------------*/
void SetPlane (int Num, PKMSTRIPHEAD pStripHead )
{
	PVRVERTEX	Vert[4];
	int			Tri1[] = {0,1,2,3}, i;
	float		Temp, CamZ, CamF, CosA, SinA, Ang;
	pvr_vector	Pnt[4]	=   {	{-128.0f, -128.0f, 0.0f},
								{ 128.0f, -128.0f, 0.0f},
								{ 128.0f,  128.0f, 0.0f},
								{-128.0f,  128.0f, 0.0f}	};

    if (Num==2)
	{
		Ang = Frame/300.0f;
	}
	else
	{
		Ang = -(Frame/300.0f);
	}

    CosA = cos(Ang); SinA = sin (Ang);

    for (i=0; i<4; i++)
	{
    	Temp      = Pnt[i][0] * CosA - Pnt[i][1] * SinA;
        Pnt[i][1] = Pnt[i][1] * CosA + Pnt[i][0] * SinA;
		Pnt[i][0] = Temp;

	    CamZ = 1.0/ (float)(PosZ+Num);
		CamF = 800.0f * CamZ;

    	Vert[i].fX    =  CamF * Pnt[i][0] + 320 ;
        Vert[i].fY    = -CamF * Pnt[i][1] + 240 ;
		Vert[i].fInvW =  CamZ;
	}

	Vert[0].u32Colour  = RGBAColour (255,255,255, 255);
	Vert[1].u32Colour  = RGBAColour (255,255,255, 0);
	Vert[2].u32Colour  = RGBAColour (255,255,255, 0);
	Vert[3].u32Colour  = RGBAColour (255,255,255, 255);

	Vert[2].fUOverW=1.0f;   Vert[2].fVOverW=1.0f;
	Vert[3].fUOverW=0.0f;   Vert[3].fVOverW=1.0f;
	Vert[1].fUOverW=1.0f;   Vert[1].fVOverW=0.0f;
	Vert[0].fUOverW=0.0f;   Vert[0].fVOverW=0.0f;

	kmtri_quads (	&VertexBufferDesc,	/* PKMVERTEXBUFFDESC */
					pStripHead,			/* PKMSTRIPHEAD		 */
					1,					/* int  nNumFaces	 */
					(int (*)[4])Tri1,	/* int  pFaces[][3]	 */
					Vert,				/* PPVRVERTEX		 */
					TRUE				/* bTexture			 */
					);
}

/*----------------------------------------------------------------------*
 *  Function Name   : SetBackground                                     *
 *  Inputs          : TextureID                                         *
 *  Outputs         :                                                   *
 *  Returns         :                                                   *
 *  Globals Used    :                                                   *
 *  Description     : Sets the background                               *
 *----------------------------------------------------------------------*/
#define	BILINEAR_CORRECTION		(1.0f/256.0f)

void SetBackground (PKMSURFACEDESC TextureID)
{
	KMSTATUS			status;
	KMVERTEXCONTEXT		BackVertexContext;		/* Vertex context			*/
	KMVERTEX_01			BV01[3];				/* for NO-TEXTURE-GOURAUD	*/
	KMVERTEX_03			BV03[3];				/* for TEXTURE-GOURAUD		*/
	PVOID				pBV[3];					/* pointer to Vertex		*/

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
	BackVertexContext.fFaceColorAlpha		= 1.0f;		/* Face Color Alpha			*/
	BackVertexContext.fFaceColorRed			= 1.0f;		/* Face Color Red			*/
	BackVertexContext.fFaceColorGreen		= 1.0f;		/* Face Color Green			*/
	BackVertexContext.fFaceColorBlue		= 1.0f;		/* Face Color Blue			*/
	BackVertexContext.fOffsetColorAlpha		= 1.0f;		/* Specular Color Alpha		*/
	BackVertexContext.fOffsetColorRed		= 1.0f;		/* Specular Color Red		*/
	BackVertexContext.fOffsetColorGreen		= 1.0f;		/* Specular Color Green		*/
	BackVertexContext.fOffsetColorBlue		= 1.0f;		/* Specular Color Blue		*/

	if(TextureID == (PKMSURFACEDESC)NULL)
	{
		/* No texture */
		BackVertexContext.ColorType				= KM_FLOATINGCOLOR;
		BackVertexContext.ShadingMode			= KM_NOTEXTUREGOURAUD;
	}
	else
	{
		/* Use texture */
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
	{
		/* No texture */
		/* Vertex #1 */
		BV01[0].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
		BV01[0].fX				=   0.0f;
		BV01[0].fY				= 479.0f;
#if defined(_STRICT_UNION_)
		BV01[0].u.fZ			= 0.0001f;
#else
		BV01[0].fZ				= 0.0001f;
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
		BV01[1].u.fZ			= 0.0001f;
#else
		BV01[1].fZ				= 0.0001f;
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
		BV01[2].u.fZ			= 0.0001f;
#else
		BV01[2].fZ				= 0.0001f;
#endif
		BV01[2].fBaseAlpha		=   0.0f;
		BV01[2].fBaseRed		=   0.55f;
		BV01[2].fBaseGreen		=   0.87f;
		BV01[2].fBaseBlue		=   0.96f;

		pBV[0] = &BV01[0];
		pBV[1] = &BV01[1];
		pBV[2] = &BV01[2];

		/* set VERTEX */
		status = kmSetBackGroundPlane(	pBV,					/* pVertex		*/
										KM_VERTEXTYPE_01,		/* VertexType	*/
										sizeof(KMVERTEX_01)		/* StructSize	*/
										);
		Check_Status(status, "kmSetBackGroundPlane");
	}
	else
	{
		/* Use texture */
		/* Vertex #1 */
		BV03[0].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
		BV03[0].fX					=  0.0f;
		BV03[0].fY					=  0.0f;
#if defined(_STRICT_UNION_)
		BV03[0].u.fZ				= 0.0001f;
#else
		BV03[0].fZ					= 0.0001f;
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
		BV03[1].u.fZ				= 0.0001f;
#else
		BV03[1].fZ					= 0.0001f;
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
		BV03[2].u.fZ				= 0.0001f;
#else
		BV03[2].fZ					= 0.0001f;
#endif
		BV03[2].fU					= 1.0f;
		BV03[2].fV					= 0.0f;
		BV03[2].uBaseRGB.dwPacked	= RGBAColour (255, 255, 255, 255);
		BV03[2].uOffsetRGB.dwPacked	= RGBAColour (255, 255, 255, 255);

		pBV[0] = &BV03[0];
		pBV[1] = &BV03[1];
		pBV[2] = &BV03[2];

		/* set VERTEX */
		status = kmSetBackGroundPlane(	pBV,					/* pVertex		*/
										KM_VERTEXTYPE_03,		/* VertexType	*/
										sizeof(KMVERTEX_03)		/* StructSize	*/
										);
		Check_Status(status, "kmSetBackGroundPlane");
	}
}
/*--------------------------- End of File --------------------------------*/
