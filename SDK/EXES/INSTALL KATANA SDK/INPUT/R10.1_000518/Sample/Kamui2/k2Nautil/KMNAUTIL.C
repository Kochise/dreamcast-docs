/******************************************************************************
 Name     : KMNAUTIL
 Title    : KAMUI test program "Nautilus" from VL
 Author   : VideoLogic Carlos Sarria / NEC Software Takeshi Muto
 Created  : September 1997 by VideoLogic(Updated Jan98)
 Modified : June	 15. 1997 by Takeshi Muto for KAMUI
			February  2. 1999 by T.Kamei 	  for KAMUI2
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
#include    "kmntool.h"
#include	"Esphere.h"				/* This is the file with 3D data					*/

/****************************************************************************
 *	Valuables for KAMUI
 ****************************************************************************/
	KMSTATUS			status;					/* return status of KAMUI API */
	KMVERSIONINFO		VersionInfo;			/* KAMUI Version information */
	KMSURFACEDESC		PrimarySurfaceDesc;		/* Primary frame buffer */
	KMSURFACEDESC		BackSurfaceDesc;		/* Back-buffer frame buffer */
	KMVERTEXBUFFDESC	VertexBufferDesc;		/* Vertex-buffer */

	KMSTRIPCONTEXT		StripContext00;
	KMSTRIPHEAD			StripHead00;
	KMSTRIPCONTEXT		StripContext01;
	KMSTRIPHEAD			StripHead01;
	KMSTRIPCONTEXT		StripContext03;
	KMSTRIPHEAD			StripHead03;

	PKMSURFACEDESC			pFB[2];
	KMDWORD					FBarea[24576 + 19456];
									/* FBstruct 4096 Entry (= 4096 * 24 / 4) *
									 * VQstruct 1024 Entry (= 1024 * 76 / 4) */
	KMSYSTEMCONFIGSTRUCT	SystemConfig;
	PKMDWORD				dwDataPtr;

/* 性能測定用変数 */
	int			frame;				/* 画面フレーム							*/
	int			frame_2 = 0;		/* 画面フレーム上位 					*/
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
KMSURFACEDESC   TexOpaq, TexReflect;

static pvr_vector X_Axis = { 1, 0,0}, Y_Axis = { 0,1, 0}, Z_Axis = { 0,0, 1};

/* Info Structure */
INFO Info =
{
	FALSE,		/* OpaqMap       */
	TRUE,       /* Textured      */
	TRUE,		/* Gouraud       */
	FALSE,      /* GlobalTrans   */
	FALSE,      /* VertexAlpha   */
	TRUE,		/* TableFog      */
	FALSE,      /* VertexFog     */
	TRUE,       /* Bilinear      */
	TRUE,       /* Highlight     */
};

/* Prototypes */
static void SetTextures			(void);
void NextFrame			(void);
static void DisplayInformation	(void);
void ReadMaple (void);

void	InitContext (INFO CInfo);
void	SetContext (INFO CInfo);

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
	PRINTOUT(("** KMNAUTIL(KAMUI2&Shinobi) Use:Level4 Macro **\n"));
#else
	PRINTOUT(("** KMNAUTIL(KAMUI2&Shinobi) **\n"));
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
								KM_DSPBPP_RGB565,	/* nBpp */
								KM_FALSE,				/* bDither */
								KM_FALSE				/* bAntiAlias */
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
	SystemConfig.ppSurfaceDescArray		=	pFB;		/* Array of SurfaceDesc	pointer     	*/
	SystemConfig.fb.nNumOfFrameBuffer	=	2;			/* Number Of Frame Buffer				*/
	/* for Texture Memory */
	SystemConfig.nTextureMemorySize		=	0x100000*2;	/* Texture 2MB							*/
	SystemConfig.nNumOfTextureStruct	=	4096;		/* テクスチャ管理構造体の数				*/
	SystemConfig.nNumOfSmallVQStruct	=	1024;		/* VQテクスチャ管理構造体の数			*/
	SystemConfig.pTextureWork			=	&FBarea[0];	/* テクスチャ管理構造体領域				*/
	/* for Vertex buffer */
	SystemConfig.pBufferDesc			=	&VertexBufferDesc;	/* pointer to VERTEXBUFFDESC	*/
	SystemConfig.nNumOfVertexBank		=	2;
	SystemConfig.pVertexBuffer			=	dwDataPtr;	/* pointer to Vertex buffer 			*/
	SystemConfig.nVertexBufferSize		=	0x200000*2;	/* 4MB 									*/
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
	InitContext (Info);

	InitBackground2 (&TexReflect);

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

	SetFogTable (0xFF0E, 0.5f, 0.5f, 1.0f );

#if 0
   	while (TRUE)
	{
		ReadMaple ();
		NextFrame ();
	}

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
		&TexReflect,			/* OUT	PKMSURFACEDESC	pSurfaceDesc	*/
		128,					/*	IN	KMINT32			nWidth			*/
		128,					/*	IN	KMINT32			nHeight			*/
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType	*/
	);
	Check_Status(status, "kmCreateTextureSurface #2");
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
	pTexture01 = (unsigned long *)&nau_imagine;
	status = kmLoadTexture(	&TexOpaq,									/* PKMSURFACEDESC pSurfaceDesc	*/
							pTexture01 + (16 / sizeof(KMDWORD))			/* PKMDWORD pTexture			*/
							);
	Check_Status(status, "kmLoadTexture #1");
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
	pTexture01 = (unsigned long *)&nau_reflect;
	status = kmLoadTexture(&TexReflect,									/* PKMSURFACEDESC pSurfaceDesc	*/
							pTexture01 + (16 / sizeof(KMDWORD))			/* PKMDWORD pTexture			*/
							);
	Check_Status(status, "kmLoadTexture #2");
}

/*-------------------------------------------------------------------------------------*/
void NextFrame (void)
{
	register i;

	InitScene ();

	ResetMatrix (SPHERE01);

	/* Trasnforming, Shading and Rendering 18 balls */
	for (i=0; i<18; i++)
	{
		Rotate    (SPHERE01, Z_Axis, (Frame)/222.0);
		Rotate    (SPHERE01, Y_Axis, (Frame+i)/36.0);
		Rotate    (SPHERE01, X_Axis, (Frame+i)/86.0);
     	Translate (SPHERE01, sin((Frame+i)/60.0f)*100.0f, 0, 0);

		SetSmoothShading (SPHERE01, C_NONE);

		if(Info.Textured)
		{
			SetVertices (SPHERE01, &StripHead03, FX_NONE);
		}
		else
		{
			SetVertices (SPHERE01, &StripHead00, FX_NONE);
		}
	}

	SetBackground2 (&VertexBufferDesc);
	EndScene(&SystemConfig);

	Frame++;
}
/*-------------------------------------------------------------------------------------*/

void DisplayInformation (void)
{
	char *Flag[2]   = { "FALSE", "TRUE" };

	txt_SetCursor(0,17);

	PRINTOUT(( " A : Bilinear    %s\n", Flag[Info.Bilinear]));
	PRINTOUT(( " B : Gouraud     %s\n", Flag[Info.Gouraud]));
	PRINTOUT(( " X : Textured    %s\n", Flag[Info.Textured]));
    PRINTOUT(( " Y : Translucnet %s", Flag[Info.Highlight]));
}

/*----------------------------------------------------------------------*
 *  Function Name   : InitContext                                       *
 *  Inputs          : CInfo                                             *
 *  Outputs         :                                                   *
 *  Returns         :                                                   *
 *  Globals Used    :                                                   *
 *  Description     :                                                   *
 *----------------------------------------------------------------------*/
void InitContext (INFO CInfo)
{
	/**************************
	 * KMSTRIPHEADの構築
	 **************************/

	/***************************************
	 *	VertexType00用KMSTRIPHEADの初期化
	 ***************************************/
	memset( &StripContext00, 0, sizeof(StripContext00));
	memset( &StripHead00,	 0, sizeof(StripHead00));
	InitStripContext00(&StripContext00,&StripHead00);

	kmChangeStripBlendingMode		( &StripHead00, KM_IMAGE_PARAM1, KM_SRCALPHA, KM_INVSRCALPHA );
	kmChangeStripListType			( &StripHead00, KM_TRANS_POLYGON );
	kmChangeStripUseAlpha			( &StripHead00, KM_IMAGE_PARAM1, KM_TRUE );

	/***************************************
	 *	VertexType01用KMSTRIPHEADの初期化
	 ***************************************/
	memset( &StripContext01, 0, sizeof(StripContext01));
	memset( &StripHead01,	 0, sizeof(StripHead01));
	InitStripContext01(&StripContext00,&StripHead01);

	kmChangeStripBlendingMode		( &StripHead01, KM_IMAGE_PARAM1, KM_SRCALPHA, KM_INVSRCALPHA );
	kmChangeStripListType			( &StripHead01, KM_TRANS_POLYGON );
	kmChangeStripUseAlpha			( &StripHead01, KM_IMAGE_PARAM1, KM_TRUE );

	/***************************************
	 *	VertexType03用KMSTRIPHEADの初期化
	 ***************************************/
	memset( &StripContext03, 0, sizeof(StripContext03));
	memset( &StripHead03,	 0, sizeof(StripHead03));
	InitStripContext03(&StripContext03,&StripHead03,&TexOpaq);

	if (CInfo.Bilinear)
	{
		kmChangeStripFilterMode	( &StripHead03, KM_IMAGE_PARAM1, KM_BILINEAR );
	}
	else
	{
		kmChangeStripFilterMode	( &StripHead03, KM_IMAGE_PARAM1, KM_POINT_SAMPLE );
	}

	kmChangeStripFlipUV				( &StripHead03, KM_IMAGE_PARAM1, KM_FLIP_UV );
	kmChangeStripBlendingMode		( &StripHead03, KM_IMAGE_PARAM1, KM_SRCALPHA, KM_INVSRCALPHA );
	kmChangeStripListType			( &StripHead03, KM_TRANS_POLYGON );
	kmChangeStripTextureShadingMode	( &StripHead03, KM_IMAGE_PARAM1, KM_MODULATE_ALPHA );
	kmChangeStripUseAlpha			( &StripHead03, KM_IMAGE_PARAM1, KM_TRUE );

}

/*----------------------------------------------------------------------*
 *  Function Name   : SetContext                                        *
 *  Inputs          : CInfo                                             *
 *  Outputs         :                                                   *
 *  Returns         :                                                   *
 *  Globals Used    :                                                   *
 *  Description     :                                                   *
 *----------------------------------------------------------------------*/
void SetContext (INFO CInfo)
{
	if (CInfo.Bilinear)
	{
			kmChangeStripFilterMode	( &StripHead03, KM_IMAGE_PARAM1, KM_BILINEAR );
	}
	else
	{
			kmChangeStripFilterMode	( &StripHead03, KM_IMAGE_PARAM1, KM_POINT_SAMPLE );
	}

	if (CInfo.Textured)
	{
		if(CInfo.Gouraud)
		{
			/* Set shading mode */
			kmChangeStripGouraud		( &StripHead03, KM_TRUE );
			/* Set texture surface */
			kmChangeStripTextureSurface	( &StripHead03,KM_IMAGE_PARAM1,&TexOpaq );
		}
		else
		{
			/* Set shading mode */
			kmChangeStripGouraud		( &StripHead03, KM_FALSE );
			/* Set texture surface */
			kmChangeStripTextureSurface	( &StripHead03,KM_IMAGE_PARAM1,&TexOpaq );
		}
	}
	else
	{
		if(CInfo.Gouraud)
		{
			/* Set shading mode */
			kmChangeStripGouraud	( &StripHead00, KM_TRUE );
		}
		else
		{
			/* Set shading mode */
			kmChangeStripGouraud	( &StripHead00, KM_FALSE );
		}
	}

	if(Info.Textured)
	{
		if(CInfo.Highlight)
		{
			/* Set translucent */
			kmChangeStripBlendingMode		( &StripHead03, KM_IMAGE_PARAM1, KM_SRCALPHA, KM_INVSRCALPHA );
			kmChangeStripListType			( &StripHead03, KM_TRANS_POLYGON );
			kmChangeStripTextureShadingMode	( &StripHead03, KM_IMAGE_PARAM1, KM_MODULATE_ALPHA );
			kmChangeStripUseAlpha			( &StripHead03, KM_IMAGE_PARAM1, KM_TRUE );
		}
		else
		{
			kmChangeStripBlendingMode		( &StripHead03, KM_IMAGE_PARAM1, KM_ONE, KM_ZERO );
			kmChangeStripListType			( &StripHead03, KM_OPAQUE_POLYGON );
			kmChangeStripTextureShadingMode	( &StripHead03, KM_IMAGE_PARAM1, KM_MODULATE );
			kmChangeStripUseAlpha			( &StripHead03, KM_IMAGE_PARAM1, KM_FALSE );
		}
	}
	else
	{
		if(CInfo.Highlight)
		{
			/* Set translucent */
			kmChangeStripBlendingMode		( &StripHead00, KM_IMAGE_PARAM1, KM_SRCALPHA, KM_INVSRCALPHA );
			kmChangeStripListType			( &StripHead00, KM_TRANS_POLYGON );
			kmChangeStripTextureShadingMode	( &StripHead00, KM_IMAGE_PARAM1, KM_MODULATE_ALPHA );
			kmChangeStripUseAlpha			( &StripHead00, KM_IMAGE_PARAM1, KM_TRUE );
		}
		else
		{
			kmChangeStripBlendingMode		( &StripHead00, KM_IMAGE_PARAM1, KM_ONE, KM_ZERO );
			kmChangeStripListType			( &StripHead00, KM_OPAQUE_POLYGON );
			kmChangeStripTextureShadingMode	( &StripHead00, KM_IMAGE_PARAM1, KM_MODULATE );
			kmChangeStripUseAlpha			( &StripHead00, KM_IMAGE_PARAM1, KM_FALSE );
		}
	}

	/* Set texture surface */
	kmChangeStripTextureSurface		( &StripHead03,KM_IMAGE_PARAM1,&TexOpaq );
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
		SetContext (Info);
		DisplayInformation ();
	}

	/* B button */
	if ( per->press & PDD_DGT_TB )
	{
		Info.Gouraud = (Info.Gouraud) ? FALSE:TRUE;
		SetContext (Info);
		DisplayInformation ();
	}

	/* X button */
	if ( per->press & PDD_DGT_TX )
	{
		Info.Textured = (Info.Textured) ? FALSE:TRUE;
		SetContext (Info);
		DisplayInformation ();
	}

	/* Y button */
	if ( per->press & PDD_DGT_TY )
	{
		Info.Highlight = (Info.Highlight) ? FALSE:TRUE;
		SetContext (Info);
		DisplayInformation ();
	}
}

/*--------------------------- End of File --------------------------------*/
