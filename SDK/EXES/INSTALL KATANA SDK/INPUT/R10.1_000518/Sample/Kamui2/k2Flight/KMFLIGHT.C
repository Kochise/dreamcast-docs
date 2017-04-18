/******************************************************************************
 Name     : KMFLIGHT
 Title    : KAMUI test program "Batman" from VL
 Author   : VideoLogic Carlos Sarria / NEC Software Takeshi Muto
 Created  : January 1998 by VideoLogic
 Modified : Octover  30. 1997 by Takeshi Muto for KAMUI
			February  2. 1999 by T.Kamei 	 for KAMUI2
			February 16. 1999 by Takeshi Muto for Shinobi
 Description :
 Copyright : 1998 by VideoLogic Limited. All rights reserved.
******************************************************************************/
#if 0
#define		_NOWAIT_VSYNC_			/* 非同期モード使用時は定義する					*/
#define		_VERTEXMACRO_L4_		/* VertexMacroLevel4使用時は定義する			*/
#endif

#define		_DISPLAY_STRING_						/* if defined then display strings on screen	*/
#define		_DISP_PERFORMANCE_						/* Display performance							*/

#include	<math.h>
#include	<stdio.h>
#include	<stdlib.h>
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

#include	"kmtools.h"
#include 	"kmFlight.h"  			/* This is the file with 3D data 					*/

/****************************************************************************
 *	Valuables for KAMUI
 ****************************************************************************/
	KMSTATUS			status;					/* return status of KAMUI API	*/
	KMVERSIONINFO		VersionInfo;			/* KAMUI Version information	*/
	KMSURFACEDESC		PrimarySurfaceDesc;		/* Primary frame buffer			*/
	KMSURFACEDESC		BackSurfaceDesc;		/* Back-buffer frame buffer		*/
	KMVERTEXBUFFDESC	VertexBufferDesc;		/* Vertex-buffer				*/

	/*------------------------------------------------*/
	KMSTRIPCONTEXT		StripContext00;
	KMSTRIPHEAD			StripHead00_Bat;
	KMSTRIPHEAD			StripHead00_Ground;
	KMSTRIPHEAD			StripHead00_Shadow;
	KMSTRIPHEAD			StripHead00_Fire;
	KMSTRIPHEAD			StripHead00_Thorm;
	KMSTRIPCONTEXT		StripContext03;
	KMSTRIPHEAD			StripHead03_Bat;
	KMSTRIPHEAD			StripHead03_Ground;
	KMSTRIPHEAD			StripHead03_Shadow;
	KMSTRIPHEAD			StripHead03_Fire;
	KMSTRIPHEAD			StripHead03_Thorm;
	/*------------------------------------------------*/

	KMDWORD				FogDensity;				/* Fog density	*/
	KMDWORD				FogD = 1;

	PKMSURFACEDESC			pFB[2];
	KMDWORD					FBarea[24576 + 19456];
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
int				Frame = 0;
float			Ang, PosX, PosY;
KMSURFACEDESC	TexBat,  TexGround, TexShadow, TexFire,  TexThorm;
pvr_vector		X_Axle = { 1, 0,0}, Y_Axle = { 0,1, 0}, Z_Axle = { 0,0, 1};

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
static void DrawToy             (void);
void ReadMaple			(void);

/* Macros for kamui */
#define		GetRED(col)			((KMFLOAT) ( ((col) & 0x00ff0000) >> 16 ) / 256.0f)
#define		GetGREEN(col)		((KMFLOAT) ( ((col) & 0x0000ff00) >>  8 ) / 256.0f)
#define		GetBLUE(col)		((KMFLOAT) ( ((col) & 0x000000ff)       ) / 256.0f)
#define		GetALPHA(col)		((KMFLOAT) ( ((col) & 0xff000000) >> 24 ) / 256.0f)

/* Peripheral */
PDS_PERIPHERAL *per;

/*-------------------------------------------------------------------------------------*
 *                                       MAIN                                          *
 *-------------------------------------------------------------------------------------*/
int Kamui_Init (void)
{
	int Control = 0, Device, Val = 0;

	txt_ClearScreen();	/* Clear text screen */

#if defined(_VERTEXMACRO_L4_)
	PRINTOUT(("** KMFLIGHT(KAMUI2&Shinobi) Use:Level4 Macro **\n"));
#else
	PRINTOUT(("** KMFLIGHT(KAMUI2&Shinobi) **\n"));
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
	SystemConfig.pVertexBuffer			=	dwDataPtr;			/* pointer to Vertex buffer		*/
	SystemConfig.nVertexBufferSize		=	0x100000*2;			/* 2MB 							*/
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
	/* Set Culling Register */
	status = kmSetCullingRegister(1.0f);
	Check_Status(status, "kmSetCullingRegister");

	/*----------------------------------------------------------------------------------- */
	/* some initializes */
	SetTextures ();
	InitContext  (Info);
	SetFogTable (0xFF0D);
	SetBackground ((PKMSURFACEDESC)NULL);
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

	/*
	 *This function creates an array of structures with 3D data (is in Batwing.h)
	 */
	CreateMeshesArray ();

	InitMeshes (NUM_MESHES, (CASTMESHES *) Mesh);

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
		&TexBat,				/* OUT	PKMSURFACEDESC	pSurfaceDesc	*/
		128,					/*	IN	KMINT32			nWidth			*/
		128,					/*	IN	KMINT32			nHeight			*/
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType	*/
	);
	Check_Status(status, "kmCreateTextureSurface #1");
	/*----------------------------------------------------------------------------------- */
	/* Create texture surface */
	nTextureType = KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&TexGround,				/* OUT	PKMSURFACEDESC	pSurfaceDesc	*/
		64,						/*	IN	KMINT32			nWidth			*/
		64,						/*	IN	KMINT32			nHeight			*/
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType	*/
	);
	Check_Status(status, "kmCreateTextureSurface #2");
	/*----------------------------------------------------------------------------------- */
	/* Create texture surface */
	nTextureType = KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_ARGB4444;	/* Set texture type */
	status = kmCreateTextureSurface(
		&TexShadow,				/* OUT	PKMSURFACEDESC	pSurfaceDesc	*/
		128,					/*	IN	KMINT32			nWidth			*/
		128,					/*	IN	KMINT32			nHeight			*/
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType	*/
	);
	Check_Status(status, "kmCreateTextureSurface #3");
	/*----------------------------------------------------------------------------------- */
	/* Create texture surface */
	nTextureType = KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&TexFire,				/* OUT	PKMSURFACEDESC	pSurfaceDesc	*/
		128,					/*	IN	KMINT32			nWidth			*/
		128,					/*	IN	KMINT32			nHeight			*/
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType	*/
	);
	Check_Status(status, "kmCreateTextureSurface #4");
	/*----------------------------------------------------------------------------------- */
	/* Create texture surface */
	nTextureType = KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_ARGB4444;	/* Set texture type */
	status = kmCreateTextureSurface(
		&TexThorm,				/* OUT	PKMSURFACEDESC	pSurfaceDesc	*/
		128,					/*	IN	KMINT32			nWidth			*/
		128,					/*	IN	KMINT32			nHeight			*/
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType	*/
	);
	Check_Status(status, "kmCreateTextureSurface #5");
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
	pTexture01 = (unsigned long *)&fli_bat;
	status = kmLoadTexture(	&TexBat,								/* PKMSURFACEDESC	pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))		/* PKMDWORD 		pTexture	 */
							);
	Check_Status(status, "kmLoadTexture #1");
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
	pTexture01 = (unsigned long *)&fli_ground;
	status = kmLoadTexture(	&TexGround,								/* PKMSURFACEDESC	pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))		/* PKMDWORD			pTexture	 */
							);
	Check_Status(status, "kmLoadTexture #2");
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
	pTexture01 = (unsigned long *)&fli_shadow;
	status = kmLoadTexture(	&TexShadow,								/* PKMSURFACEDESC	pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))		/* PKMDWORD 		pTexture	 */
							);
	Check_Status(status, "kmLoadTexture #3");
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
	pTexture01 = (unsigned long *)&fli_fire;
	status = kmLoadTexture(	&TexFire,								/* PKMSURFACEDESC	pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))		/* PKMDWORD			pTexture	 */
							);
	Check_Status(status, "kmLoadTexture #4");
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
	pTexture01 = (unsigned long *)&fli_thorm;
	status = kmLoadTexture(&TexThorm,								/* PKMSURFACEDESC	pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))		/* PKMDWORD 		pTexture	 */
							);
	Check_Status(status, "kmLoadTexture #5");
}

/*-------------------------------------------------------------------------------------*/
void NextFrame (void)
{
	static	 Movement = 0;
	static	 float Sun = 0, HPos;
	register i;

	InitScene ();

	for (i=0;i<NUM_MESHES; i++){ ResetMatrix (i);}

	/*
	 *  Processing the spaceship
     *  (Blend modes need to be set in the second Context structure)
     */
	for (i=0;i<NUM_MESHES; i++)
	{
    	if (i==SHADOW){ continue;}

    	Translate (i, -120.0f*sin(Ang), -20*sin(Frame/500.0f)-30, -400);
		Rotate (i, X_Axle, -PI/16);
		Rotate (i, Z_Axle, -(PI/8)*sin(Ang));
		Rotate (i, Y_Axle, PI+(PI/8)*sin(Ang));

    	if (i==PLANE)
		{
			SetSmoothShading (i, C_NONE);
			if(Info.Textured)
			{
				SetVertices (i,  &StripHead03_Bat, FX_NONE);
			}
			else
			{
				SetVertices (i,  &StripHead00_Bat, FX_NONE);
			}
		}
	 	else
		{
	  		/*
	   		 * Fire: 4 polygons blended using  Source:OTHER and Destination:ONE
	   		 */
			Translate (i, -2.0f*sin(i*Frame/10.0f), -2*sin(i*Frame),0);
			if(Info.Textured)
			{
				SetVertices (i,  &StripHead03_Fire, FX_NONE);
			}
			else
			{
				SetVertices (i,  &StripHead00_Fire, FX_NONE);
			}
		}
	} /* End of for */

	/*
     * Shadow blended using Source:ZERO and Destination:INVSOURCEALPHA
     */
	Translate (SHADOW, -120.0f*sin(Ang), 0, -400);
	Rotate    (SHADOW, Y_Axle, PI+(PI/8)*sin(Ang));

	if(Info.Textured)
	{
		SetVertices (SHADOW,  &StripHead03_Shadow, FX_NONE);
	}
	else
	{
		SetVertices (SHADOW,  &StripHead00_Shadow, FX_NONE);
	}

	Ang = (PI*2) * sin(Frame/5000.0f);
	PosY+=0.05f; if (PosY>100.0f) PosY =0.0f;

	if(Info.Textured)
	{
		SetGround(&StripHead03_Ground);
		Lightning(&StripHead03_Thorm);
	}
	else
	{
		SetGround(&StripHead00_Ground);
		Lightning(&StripHead00_Thorm);
	}

	EndScene(&SystemConfig);

	Frame+=2;
}

/*-------------------------------------------------------------------------------------*/
void DisplayInformation (void)
{
	char *Flag[2]   = { "FALSE", "TRUE" };

	txt_SetCursor(0,17);

	PRINTOUT(( " A : Bilinear    %s\n", Flag[Info.Bilinear]));
	PRINTOUT(( " B : Gouraud     %s\n", Flag[Info.Gouraud]));
	PRINTOUT(( " X : Textured    %s\n", Flag[Info.Textured]));
    PRINTOUT(( " Y : HighLight   %s", Flag[Info.Highlight]));
}

/*----------------------------------------------------------------------*
 *  Function Name   : SetContext                                        *
 *  Inputs          : CInfo                                             *
 *  Outputs         :                                                   *
 *  Returns         :                                                   *
 *  Globals Used    :                                                   *
 *  Description     :                                                   *
 *----------------------------------------------------------------------*/

void InitContext (INFO CInfo)
{
	/*--------------------------------------------------------------------------------	*
	 * Initialize Vertex Context : Bat				 									*
	 *--------------------------------------------------------------------------------	*/
	/* VertexType00用 */
	memset( &StripContext00, 	0, sizeof(StripContext00));
	memset( &StripHead00_Bat,	0, sizeof(StripHead00_Bat));

	InitStripContext00			( &StripContext00,&StripHead00_Bat );
	kmChangeStripCullingMode	( &StripHead00_Bat, KM_CULLSMALL );

	/* VertexType03用 */
	memset( &StripContext03, 	0, sizeof(StripContext03));
	memset( &StripHead03_Bat,	0, sizeof(StripHead03_Bat));

	InitStripContext03( &StripContext03,&StripHead03_Bat,&TexBat );
	if (CInfo.Bilinear)
	{
		kmChangeStripFilterMode	( &StripHead03_Bat, KM_IMAGE_PARAM1, KM_BILINEAR );
	}
	kmChangeStripCullingMode	( &StripHead03_Bat, KM_CULLSMALL );

	/*--------------------------------------------------------------------------------	*
	 * Initialize Vertex Context : Ground												*
	 *--------------------------------------------------------------------------------	*/
	/* VertexType00用 */
	memset( &StripContext00,		0, sizeof(StripContext00));
	memset( &StripHead00_Ground,	0, sizeof(StripHead00_Ground));

	InitStripContext00			( &StripContext00,&StripHead00_Ground );
	kmChangeStripCullingMode	( &StripHead00_Ground, KM_CULLSMALL );

	/* VertexType03用 */
	memset( &StripContext03,		0, sizeof(StripContext03));
	memset( &StripHead03_Ground,	0, sizeof(StripHead03_Ground));

	InitStripContext03			( &StripContext03,&StripHead03_Ground,&TexGround );
	if (CInfo.Bilinear)
	{
		kmChangeStripFilterMode	( &StripHead03_Ground, KM_IMAGE_PARAM1, KM_BILINEAR );
	}
	kmChangeStripCullingMode	( &StripHead03_Ground, KM_CULLSMALL );

	/*--------------------------------------------------------------------------------	*
	 * Initialize Vertex Context : Shadow												*
	 *--------------------------------------------------------------------------------	*/
	/* VertexType00用 */
	memset( &StripContext00,		0, sizeof(StripContext00));
	memset( &StripHead00_Shadow,	0, sizeof(StripHead00_Shadow));

	InitStripContext00			( &StripContext00,&StripHead00_Shadow );
	kmChangeStripBlendingMode	( &StripHead00_Shadow, KM_IMAGE_PARAM1, KM_ZERO, KM_INVSRCALPHA );
	kmChangeStripListType		( &StripHead00_Shadow, KM_TRANS_POLYGON );

	/* VertexType03用 */
	memset( &StripContext03,		0, sizeof(StripContext03));
	memset( &StripHead03_Shadow,	0, sizeof(StripHead03_Shadow));

	InitStripContext03			( &StripContext03,&StripHead03_Shadow,&TexShadow );
	if (CInfo.Bilinear)
	{
		kmChangeStripFilterMode	( &StripHead03_Shadow, KM_IMAGE_PARAM1, KM_BILINEAR );
	}
	kmChangeStripBlendingMode	( &StripHead03_Shadow, KM_IMAGE_PARAM1, KM_ZERO, KM_INVSRCALPHA );
	kmChangeStripListType		( &StripHead03_Shadow, KM_TRANS_POLYGON );

	/*--------------------------------------------------------------------------------	*
 	 * Initialize Vertex Context : Fire													*
	 *--------------------------------------------------------------------------------	*/
	/* VertexType00用 */
	memset( &StripContext00,		0, sizeof(StripContext00));
	memset( &StripHead00_Fire,		0, sizeof(StripHead00_Fire));

	InitStripContext00			( &StripContext00,&StripHead00_Fire );
	kmChangeStripBlendingMode	( &StripHead00_Fire, KM_IMAGE_PARAM1, KM_DESTCOLOR, KM_ONE );
	kmChangeStripListType		( &StripHead00_Fire, KM_TRANS_POLYGON );

	/* VertexType03用 */
	memset( &StripContext03,		0, sizeof(StripContext03));
	memset( &StripHead03_Fire,		0, sizeof(StripHead03_Fire));

	InitStripContext03			( &StripContext03,&StripHead03_Fire,&TexFire );
	if (CInfo.Bilinear)
	{
		kmChangeStripFilterMode	( &StripHead03_Fire, KM_IMAGE_PARAM1, KM_BILINEAR );
	}
	kmChangeStripBlendingMode	( &StripHead03_Fire, KM_IMAGE_PARAM1, KM_DESTCOLOR, KM_ONE );
	kmChangeStripListType		( &StripHead03_Fire, KM_TRANS_POLYGON );

	/*--------------------------------------------------------------------------------	*
	 * Initialize Vertex Context : Thorm												*
	 *--------------------------------------------------------------------------------	*/
	/* VertexType00用 */
	memset( &StripContext00,		0, sizeof(StripContext00));
	memset( &StripHead00_Thorm,		0, sizeof(StripHead00_Thorm));

	InitStripContext00			( &StripContext00,&StripHead00_Thorm );
	kmChangeStripBlendingMode	( &StripHead00_Thorm, KM_IMAGE_PARAM1, KM_SRCALPHA, KM_INVSRCALPHA );
	kmChangeStripListType		( &StripHead00_Thorm, KM_TRANS_POLYGON );
	kmChangeStripUseAlpha		( &StripHead00_Thorm, KM_IMAGE_PARAM1, KM_TRUE );

	/* VertexType03用 */
	memset( &StripContext03,		0, sizeof(StripContext03));
	memset( &StripHead03_Thorm,		0, sizeof(StripHead03_Thorm));

	InitStripContext03			( &StripContext03,&StripHead03_Thorm,&TexThorm );
	if (CInfo.Bilinear)
	{
		kmChangeStripFilterMode	( &StripHead03_Thorm, KM_IMAGE_PARAM1, KM_BILINEAR );
	}
	kmChangeStripBlendingMode		( &StripHead03_Thorm, KM_IMAGE_PARAM1, KM_SRCALPHA, KM_INVSRCALPHA );
	kmChangeStripListType			( &StripHead03_Thorm, KM_TRANS_POLYGON );
	kmChangeStripTextureShadingMode	( &StripHead03_Thorm, KM_IMAGE_PARAM1, KM_MODULATE_ALPHA );
	kmChangeStripUseAlpha			( &StripHead03_Thorm, KM_IMAGE_PARAM1, KM_TRUE );
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
		if(Info.Textured)
		{
			SetContext (&StripHead03_Bat,		Info, &TexBat);
			SetContext (&StripHead03_Ground,	Info, &TexGround);
			SetContext (&StripHead03_Shadow,	Info, &TexShadow);
			SetContext (&StripHead03_Fire,		Info, &TexFire);
			SetContext (&StripHead03_Thorm,		Info, &TexThorm);
		}
		else
		{
			SetContext (&StripHead00_Bat,		Info, NULL);
			SetContext (&StripHead00_Ground,	Info, NULL);
			SetContext (&StripHead00_Shadow,	Info, NULL);
			SetContext (&StripHead00_Fire,		Info, NULL);
			SetContext (&StripHead00_Thorm,		Info, NULL);
		}
		DisplayInformation ();
	}

	/* B button */
	if ( per->press & PDD_DGT_TB )
	{
		Info.Gouraud = (Info.Gouraud) ? FALSE:TRUE;
		if(Info.Textured)
		{
			SetContext (&StripHead03_Bat,		Info, &TexBat);
			SetContext (&StripHead03_Ground,	Info, &TexGround);
			SetContext (&StripHead03_Shadow,	Info, &TexShadow);
			SetContext (&StripHead03_Fire,		Info, &TexFire);
			SetContext (&StripHead03_Thorm,		Info, &TexThorm);
		}
		else
		{
			SetContext (&StripHead00_Bat,		Info, NULL);
			SetContext (&StripHead00_Ground,	Info, NULL);
			SetContext (&StripHead00_Shadow,	Info, NULL);
			SetContext (&StripHead00_Fire,		Info, NULL);
			SetContext (&StripHead00_Thorm,		Info, NULL);
		}
		DisplayInformation ();
	}

	/* X button */
	if ( per->press & PDD_DGT_TX )
	{
		Info.Textured = (Info.Textured) ? FALSE:TRUE;
		if(Info.Textured)
		{
			SetContext (&StripHead03_Bat,		Info, &TexBat);
			SetContext (&StripHead03_Ground,	Info, &TexGround);
			SetContext (&StripHead03_Shadow,	Info, &TexShadow);
			SetContext (&StripHead03_Fire,		Info, &TexFire);
			SetContext (&StripHead03_Thorm,		Info, &TexThorm);
		}
		else
		{
			SetContext (&StripHead00_Bat,		Info, NULL);
			SetContext (&StripHead00_Ground,	Info, NULL);
			SetContext (&StripHead00_Shadow,	Info, NULL);
			SetContext (&StripHead00_Fire,		Info, NULL);
			SetContext (&StripHead00_Thorm,		Info, NULL);
		}
		DisplayInformation ();
	}

	/* Y button */
	if ( per->press & PDD_DGT_TY )
	{
		Info.Highlight = (Info.Highlight) ? FALSE:TRUE;
		if(Info.Textured)
		{
			SetContext (&StripHead03_Bat,		Info, &TexBat);
			SetContext (&StripHead03_Ground,	Info, &TexGround);
			SetContext (&StripHead03_Shadow,	Info, &TexShadow);
			SetContext (&StripHead03_Fire,		Info, &TexFire);
			SetContext (&StripHead03_Thorm,		Info, &TexThorm);
		}
		else
		{
			SetContext (&StripHead00_Bat,		Info, NULL);
			SetContext (&StripHead00_Ground,	Info, NULL);
			SetContext (&StripHead00_Shadow,	Info, NULL);
			SetContext (&StripHead00_Fire,		Info, NULL);
			SetContext (&StripHead00_Thorm,		Info, NULL);
		}
		DisplayInformation ();
	}
}

/*--------------------------- End of File --------------------------------*/
