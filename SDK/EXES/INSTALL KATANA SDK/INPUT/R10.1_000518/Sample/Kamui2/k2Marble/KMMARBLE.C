/******************************************************************************
 Name     : KMMARBLE
 Title    : KAMUI test program "Evil" from VL
 Author   : VideoLogic Carlos Sarria / NEC Software Takeshi Muto
 Created  : September 1997 by VideoLogic(Updated Jan98)
 Modified : June	 29. 1998 by Takeshi Muto		for KAMUI
			February  4. 1999 by T.Kamei 	  		for KAMUI2
			February 16. 1999 by Takeshi Muto for Shinobi
 Description :
 Copyright : 1998 by VideoLogic Limited. All rights reserved.
******************************************************************************/
#if 0
#define		_NOWAIT_VSYNC_			/* 非同期モード使用時は定義する					*/
#define		_VERTEXMACRO_L4_		/* VertexMacroLevel4使用時は定義する			*/
#endif

#define		_DISPLAY_STRING_		/* if defined then display strings on screen	*/
#define		_DISP_PERFORMANCE_		/* Display performance							*/

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
#include	"vltex.h"				/* for vl sample texture							*/

#include    "soj_tool.h"
#include	"kmMarble.h"  			/* This is the file with 3D data 					*/

#if 0
#define _KM_USE_VERTEX_MACRO_
#define _KM_USE_VERTEX_MACRO_L3_
#include	"kamuix.h"
#endif

/****************************************************************************
 *	Valuables for KAMUI
 ****************************************************************************/
	KMSTATUS			status;					/* return status of KAMUI API	*/
	KMVERSIONINFO		VersionInfo;			/* KAMUI Version information	*/
	KMSURFACEDESC		PrimarySurfaceDesc;		/* Primary frame buffer			*/
	KMSURFACEDESC		BackSurfaceDesc;		/* Back-buffer frame buffer		*/
	KMVERTEXBUFFDESC	VertexBufferDesc;		/* Vertex-buffer				*/

    KMTWOVOLUMESTRIPCONTEXT      StripContext11;
	KMSTRIPCONTEXT		StripContext17;
	KMSTRIPHEAD			StripHead11_01;
	KMSTRIPHEAD			StripHead11_02;
	KMSTRIPHEAD			StripHead17_first;
	KMSTRIPHEAD			StripHead17_normal;
	KMSTRIPHEAD			StripHead17_last;

	KMDWORD				FogDensity;				/* Fog density 					*/
	KMDWORD				FogD = 1;

	PKMSURFACEDESC		pFB[2];
	KMDWORD				FBarea[24576 + 19456];
							/* FBstruct 4096 Entry (= 4096 * 24 / 4) *
							 * VQstruct 1024 Entry (= 1024 * 76 / 4) */
	KMSYSTEMCONFIGSTRUCT	SystemConfig;
	PKMDWORD				dwDataPtr;

/* 性能測定用変数 */
	int			frame;				/* 画面フレーム							*/
	int			frame_2 = 0;		/* 画面フレーム上位						*/
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
float			Frame = 0;
KMSURFACEDESC	TexOpaq, TexShadow, TexBark;

/* Info Structure */
INFO Info =
{
	FALSE,		/* OpaqMap       */
	TRUE,       /* Textured      */
	TRUE,		/* Gouraud       */
	FALSE,      /* GlobalTrans   */
	FALSE,      /* VertexAlpha   */
	FALSE,		/* TableFog      */
	FALSE,      /* VertexFog     */
	TRUE,       /* Bilinear      */
	TRUE,       /* Highlight     */
};

/* Prototypes */
static void SetTextures			(void);
void NextFrame			(void);
static void DisplayInformation	(void);
void ReadMaple			(void);		/* Maple data read routine */

/* Peripheral */
PDS_PERIPHERAL *per;

/*-------------------------------------------------------------------------------------*
 *                                       MAIN                                          *
 *-------------------------------------------------------------------------------------*/
int Kamui_Init (void)
{
	int	Control = 0, Device, Val = 0;

	txt_ClearScreen();	/* Clear text screen */

#if defined(_VERTEXMACRO_L4_)
	PRINTOUT(("** KMMARBLE(KAMUI2&Shinobi) Use:Level4 Macro **\n"));
#else
	PRINTOUT(("** KMMARBLE(KAMUI2&Shinobi) **\n"));
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
	SystemConfig.nNumOfTextureStruct	=	4096;		/* テクスチャ管理構造体の数			*/
	SystemConfig.nNumOfSmallVQStruct	=	1024;		/* VQテクスチャ管理構造体の数		*/
	SystemConfig.pTextureWork			=	&FBarea[0];	/* テクスチャ管理構造体領域			*/
	/* for Vertex buffer */
	SystemConfig.pBufferDesc			=	&VertexBufferDesc;	/* pointer to VERTEXBUFFDESC	*/
	SystemConfig.nNumOfVertexBank		=	2;
	SystemConfig.pVertexBuffer			=	dwDataPtr;			/* pointer to Vertex buffer 	*/
	SystemConfig.nVertexBufferSize		=	0x100000*4;			/* 4MB							*/
	SystemConfig.nPassDepth				=	1;
	SystemConfig.Pass[0].dwRegionArrayFlag = KM_PASSINFO_AUTOSORT;
	SystemConfig.Pass[0].fBufferSize[0] =  40.0f;
	SystemConfig.Pass[0].fBufferSize[1] =  40.0f;
	SystemConfig.Pass[0].fBufferSize[2] =  20.0f;
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

   	/****************************
	 * VertexType11-01			*
	 ****************************/
	/* VertexType11用 */
	memset( &StripContext11, 	0, sizeof(StripContext11));
	memset( &StripHead11_01,	0, sizeof(StripHead11_01));

	InitStripContext11		( &StripContext11,&StripHead11_01,&TexOpaq,&TexShadow );
	kmChangeStripFilterMode	( &StripHead11_01, KM_IMAGE_PARAM1 , KM_BILINEAR );
	kmChangeStripFlipUV		( &StripHead11_01, KM_IMAGE_PARAM1 , KM_FLIP_UV );

   	/****************************
	 * VertexType11-02			*
	 ****************************/
	memset( &StripContext11, 	0, sizeof(StripContext11));
	memset( &StripHead11_02,	0, sizeof(StripHead11_02));

	InitStripContext11		( &StripContext11,&StripHead11_02,&TexBark,&TexShadow );
	kmChangeStripFilterMode	( &StripHead11_02, KM_IMAGE_PARAM1 , KM_BILINEAR );
	kmChangeStripFlipUV		( &StripHead11_02, KM_IMAGE_PARAM1 , KM_FLIP_UV );

	/**************************
	 * ModifierVolume-First	  *
	 **************************/
	memset( &StripContext17, 	0, sizeof(StripContext17));
	memset( &StripHead17_first,	0, sizeof(StripHead17_first));

	InitStripContext17	( &StripContext17,&StripHead17_first );
	kmChangeStripModifierInstruction( &StripHead17_first, KM_MODIFIER_INCLUDE_FIRST_POLY );

	/**************************
	 * ModifierVolume-Normal  *
	 **************************/
	memset( &StripContext17, 	0, sizeof(StripContext17));
	memset( &StripHead17_normal,0, sizeof(StripHead17_normal));

	InitStripContext17	( &StripContext17, &StripHead17_normal );
	kmChangeStripModifierInstruction( &StripHead17_normal, KM_MODIFIER_NORMAL_POLY );

	/**************************
	 * ModifierVolume-Last	  *
	 **************************/
	memset( &StripContext17, 	0, sizeof(StripContext17));
	memset( &StripHead17_last,	0, sizeof(StripHead17_last));

	InitStripContext17	( &StripContext17, &StripHead17_last );
	kmChangeStripModifierInstruction( &StripHead17_last, KM_MODIFIER_INCLUDE_LAST_POLY );

	DisplayInformation ();

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
#endif

	/* This function creates an array of structures with 3D data */
	CreateMeshesArray ();
	InitMeshes (NUM_MESHES, (CASTMESHES *) Mesh);

#if 0
	while (TRUE)
	{
		ReadMaple ();
		NextFrame ();
	}

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
	PKMDWORD			pTexture01;				/* Pointer to texture		*/
	KMTEXTURETYPE		nTextureType;			/* texture type definition	*/

	/*----------------------------------------------------------------------------------- */
	/* Create texture surface */
	nTextureType = KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&TexOpaq,				/* OUT	PKMSURFACEDESC	pSurfaceDesc	*/
		256,					/*	IN	KMINT32			nWidth			*/
		256,					/*	IN	KMINT32			nHeight			*/
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType	*/
	);
	Check_Status(status, "kmCreateTextureSurface #1");
	/*----------------------------------------------------------------------------------- */
	/* Create texture surface */
	nTextureType = KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&TexShadow,				/* OUT	PKMSURFACEDESC	pSurfaceDesc	*/
		256,					/*	IN	KMINT32			nWidth			*/
		256,					/*	IN	KMINT32			nHeight			*/
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType	*/
	);
	Check_Status(status, "kmCreateTextureSurface #2");
	/*----------------------------------------------------------------------------------- */
	/* Create texture surface */
	nTextureType = KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&TexBark,				/* OUT	PKMSURFACEDESC	pSurfaceDesc	*/
		32,						/*	IN	KMINT32			nWidth			*/
		32,						/*	IN	KMINT32			nHeight			*/
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType	*/
	);
	Check_Status(status, "kmCreateTextureSurface #3");
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
	pTexture01 = (unsigned long *)&mar_marble;
	status = kmLoadTexture(	&TexOpaq,								/* PKMSURFACEDESC	pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))		/* PKMDWORD 		pTexture	 */
							);
	Check_Status(status, "kmLoadTexture #1");
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
	pTexture01 = (unsigned long *)&mar_marble2;
	status = kmLoadTexture(	&TexShadow,								/* PKMSURFACEDESC	pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))		/* PKMDWORD			pTexture	 */
							);
	Check_Status(status, "kmLoadTexture #2");
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
	pTexture01 = (unsigned long *)&mar_bark;
	status = kmLoadTexture(	&TexBark,								/* PKMSURFACEDESC	pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))		/* PKMDWORD			pTexture	 */
							);
	Check_Status(status, "kmLoadTexture #3");

}

/*-------------------------------------------------------------------------------------*/
void NextFrame (void)
{
	register i;

	InitScene ();

	for (i=0;i<NUM_MESHES; i++){ ResetMatrix (i);}

	for (i=0;i<NUM_MESHES; i++)
	{
		if (i==SHADOW)
		{
			Shadow ();
		}
		else
		{
			SetSmoothShading (i, C_GREY);
			if((i==HEAD)||(i==BACK)||(i==BASE))
			{
				SetVertices( i, &StripHead11_01, FX_NONE );
			}
			else
			{
				SetVertices( i, &StripHead11_02, FX_NONE );
			}
		}
	}

	EndScene(&SystemConfig);

	Frame++;
}

/*-------------------------------------------------------------------------------------*/
void DisplayInformation (void)
{
	char *Flag[2]   = { "FALSE", "TRUE" };

	txt_SetCursor(0,17);
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

	/* A button */
	if ( per->press & PDD_DGT_TA )
	{
		Info.Bilinear = (Info.Bilinear) ? FALSE:TRUE;
		SetContext (&StripHead11_01, Info, &TexShadow);
		SetContext (&StripHead11_02, Info, &TexShadow);
		DisplayInformation ();
	}

	/* B button */
	if ( per->press & PDD_DGT_TB )
	{
		Info.Gouraud = (Info.Gouraud) ? FALSE:TRUE;
		SetContext (&StripHead11_01, Info, &TexShadow);
		SetContext (&StripHead11_02, Info, &TexShadow);
		DisplayInformation ();
	}

	/* X button */
	if ( per->press & PDD_DGT_TX )
	{
		Info.Textured = (Info.Textured) ? FALSE:TRUE;
		SetContext (&StripHead11_01, Info, &TexShadow);
		SetContext (&StripHead11_02, Info, &TexShadow);
		DisplayInformation ();
	}

	/* Y button */
	if ( per->press & PDD_DGT_TY )
	{
		Info.Highlight = (Info.Highlight) ? FALSE:TRUE;
		SetContext (&StripHead11_01, Info, &TexShadow);
		SetContext (&StripHead11_02, Info, &TexShadow);
		DisplayInformation ();
	}
}

/*--------------------------- End of File --------------------------------*/
