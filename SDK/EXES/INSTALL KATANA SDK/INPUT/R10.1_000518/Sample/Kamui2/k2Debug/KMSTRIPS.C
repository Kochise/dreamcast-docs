/*----------------------------------------------------------------
   Name   : Strips.c  (ARC1 demo)
   Author : Carlos Sarria
   Date   : Jan 1998

   Copyright : 1998 by VideoLogic Limited. All rights reserved.
   Modified  :	June     23. 1998 by Takeshi Muto / NEC Software,Ltd. for KAMUI
				February 04. 1999 by Hiroshi Nakayama for KAMUI2
				February 16. 1999 by Takeshi Muto for Shinobi
 -----------------------------------------------------------------*/

#define		_DISPLAY_STRING_
/* if defined then display strings on screen */

#define		_DISP_PERFORMANCE_
/* Display performance : for windows */

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

#include	"kamui2.h"				/* for Kamui Call */
#include	"dispstr.h"				/* for DisplayString */
#include    "kmstool.h"
#include	"kmstrips.h"  /* This is the file with 3D data */

/****************************************************************************/
/**	Valuables for KAMUI *****************************************************/
/****************************************************************************/
	KMSTATUS			status;					/* return status of KAMUI API */
	KMVERSIONINFO		VersionInfo;			/* KAMUI Version information */
	KMSURFACEDESC		PrimarySurfaceDesc;		/* Primary frame buffer */
	KMSURFACEDESC		BackSurfaceDesc;		/* Back-buffer frame buffer */
	KMVERTEXBUFFDESC	VertexBufferDesc;		/* Vertex-buffer */
	KMSTRIPCONTEXT		StripContext[3];		/* Strip context */
	KMSTRIPHEAD			StripHead[3];			/* Strip Head */
												/* [0]:TYPE01
												   [1]:TYPE03 その１
												   [2]:TYPE03 その２ */
	KMDWORD				FogDensity;				/* Fog density */
	KMDWORD				FogD = 1;

	PKMSURFACEDESC			pFB[2];
	KMDWORD					FBarea[24576 + 19456];
								/* FBstruct 4096 Entry (= 4096 * 24 / 4) */
								/* VQstruct 1024 Entry (= 1024 * 76 / 4) */
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
/* Globals */

int			Frame = 0;
int			nCylinders = 10;
int			nStrip = 10;
pvr_vector	X_Axle = { 1, 0, 0 }, Y_Axle = { 0, 1, 0 }, Z_Axle = { 0, 0, 1 };
KMSURFACEDESC	TexStrip,TexStrip1, TexBack;

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
	FALSE,      /* Highlight     */
	TRUE       /* Strips        */
};

/* Prototypes */

static void SetTextures			(void);
void NextFrame			(void);
static void DisplayInformation	(void);
void InitContext (PKMSTRIPCONTEXT	pStripContext,
				  PKMSTRIPHEAD		pStripHead,
				  PKMSURFACEDESC	pTextureDesc1,
				  PKMSURFACEDESC	pTextureDesc2,
				  INFO CInfo);
void SetContext (PKMSTRIPHEAD pStripHead, INFO CInfo);
void ReadMaple (void);

/* Peripheral */
PDS_PERIPHERAL *per;

/* Textures */
extern unsigned char str_backgrnd;
extern unsigned char str_strip;
extern unsigned char str_strip1;

/* Macros for kamui */
#define		GetRED(col)			((KMFLOAT) ( ((col) & 0x00ff0000) >> 16 ) / 256.0f)
#define		GetGREEN(col)		((KMFLOAT) ( ((col) & 0x0000ff00) >>  8 ) / 256.0f)
#define		GetBLUE(col)		((KMFLOAT) ( ((col) & 0x000000ff)       ) / 256.0f)
#define		GetALPHA(col)		((KMFLOAT) ( ((col) & 0xff000000) >> 24 ) / 256.0f)

/*-------------------------------------------------------------------------------------*/
/*                                       MAIN                                          */
/*-------------------------------------------------------------------------------------*/
int Kamui_Init (void)
{
int Control = 0, Device, Val = 0;

	txt_ClearScreen();	/* Clear text screen */
	PRINTOUT(("** KMSTRIPS(KAMUI2&Shinobi) **\n"));

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
	dwDataPtr = (PKMDWORD)(((KMDWORD)syMalloc(0x400000) & 0x0FFFFFFFUL) | 0xA0000000);
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
	SystemConfig.nVertexBufferSize		=	0x200000*2;	/* 2MB *2 */
	SystemConfig.nPassDepth				=	1;
	SystemConfig.Pass[0].dwRegionArrayFlag = KM_PASSINFO_AUTOSORT;
	SystemConfig.Pass[0].fBufferSize[0] =  50.0f;
	SystemConfig.Pass[0].fBufferSize[1] =   0.0f;
	SystemConfig.Pass[0].fBufferSize[2] =  50.0f;
	SystemConfig.Pass[0].fBufferSize[3] =   0.0f;
	SystemConfig.Pass[0].fBufferSize[4] =   0.0f;
	kmSetSystemConfiguration(&SystemConfig);

	/*-----------------------------------------------------------------------------------*/
	/* Initialize DisplayString routine */
	txt_InitDisplayString();

	/*----------------------------------------------------------------------------------- */
	/* some initializes */
	/* SetContext  (Info); */
	SetTextures ();
	SetBackground (&TexBack);
	InitContext (StripContext,StripHead,&TexStrip,&TexStrip1,Info);

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
#endif	/* defined(_DISP_PERFORMANCE_) */

	InitMeshes ();

#if 0
	while (TRUE)
	{
		ReadMaple ();
		NextFrame ();
	}
#endif

    return 0;
}
/*-------------------------------------------------------------------------------------*/
void SetTextures (void)
{
	PKMDWORD			pTexture01;				/* Pointer to texture */
	KMTEXTURETYPE		nTextureType;			/* texture type definition */

	/*----------------------------------------------------------------------------------- */
	/* Create texture surface */
	nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&TexBack,				/* OUT	PKMSURFACEDESC	pSurfaceDesc */
		256,					/*	IN	KMINT32			nWidth  */
		256,					/*	IN	KMINT32			nHeight  */
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType */
	);
	Check_Status(status, "kmCreateTextureSurface #1");
	/*----------------------------------------------------------------------------------- */
	/* Create texture surface */
	nTextureType = KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&TexStrip,				/* OUT	PKMSURFACEDESC	pSurfaceDesc */
		128,					/*	IN	KMINT32			nWidth  */
		128,					/*	IN	KMINT32			nHeight  */
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType */
	);
	Check_Status(status, "kmCreateTextureSurface #2");
	/*----------------------------------------------------------------------------------- */
	/* Create texture surface */
	nTextureType = KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&TexStrip1,				/* OUT	PKMSURFACEDESC	pSurfaceDesc */
		128,					/*	IN	KMINT32			nWidth  */
		128,					/*	IN	KMINT32			nHeight  */
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType */
	);
	Check_Status(status, "kmCreateTextureSurface #3");
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
	pTexture01 = (unsigned long *)&str_backgrnd;
	status = kmLoadTexture(&TexBack,			/* PKMSURFACEDESC pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))		/* PKMDWORD pTexture */
							);
	Check_Status(status, "kmLoadTexture #1");
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
	pTexture01 = (unsigned long *)&str_strip;
	status = kmLoadTexture(&TexStrip,			/* PKMSURFACEDESC pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))		/* PKMDWORD pTexture */
							);
	Check_Status(status, "kmLoadTexture #2");
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
	pTexture01 = (unsigned long *)&str_strip1;
	status = kmLoadTexture(&TexStrip1,			/* PKMSURFACEDESC pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))		/* PKMDWORD pTexture */
							);
	Check_Status(status, "kmLoadTexture #3");

}
/*-------------------------------------------------------------------------------------*/
void NextFrame (void)
{
register i,j;

    InitScene (); /* シ－ン初期化 */
	
	for (i=0; i<10; i++){ResetMatrix (i);}

	for (j=0; j<nCylinders; j++) /* 10 cylinders */
	{
		for (i=0; i<10; i++)
		{ /* 10 strips (30 faces) in each cylinder  */
			Rotate (i, Y_Axle, (PI/(255+i))*Frame);
			Rotate (i, Z_Axle, (PI/(555+i))*Frame);
		}
		SetStrips (Info, nStrip,StripHead); /* Draw 10 strips in just one call. */
	}

	EndScene(); /* シ－ン終了 */
    Frame+=1;	/* フレ－ム数更新 */
}
/*-------------------------------------------------------------------------------------*/

void DisplayInformation (void)
{
char *StrTri[] = {"TRIANGLES","STRIPS API"};
char *Flag[2]   = { "FALSE", "TRUE" };

	txt_SetCursor(0,14);

	PRINTOUT(( "A : Bilinear  %s\n", Flag[Info.Bilinear]));
	PRINTOUT(( "B : Gouraud   %s\n", Flag[Info.Gouraud]));
	PRINTOUT(( "X : Textured  %s\n", Flag[Info.Textured]));
	PRINTOUT(( "Geometry  %s\n", StrTri[Info.Strips]));
	PRINTOUT(( "Cylinders : %4d\nStrips    : %4d\nFaces     : %4d",nCylinders, nStrip, (nCylinders * nStrip * 30 ) ));

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
	static	float	nStrip2 = 10.0f;
	static	float	nCylinders2 = 10.0f;

	per = pdGetPeripheral(PDD_PORT_A0);

	/* UP cross key */
	if ( per->on & PDD_DGT_KU )
	{
		nStrip2 += 0.1f;
		if(nStrip2 > 10.0f){nStrip2 = 10.0f;}
		nStrip = (int)nStrip2;
		DisplayInformation ();
	}
	/* DOWN cross key */
	if ( per->on & PDD_DGT_KD )
	{
		nStrip2 -= 0.1f;
		if(nStrip2 < 1.0f){nStrip2 = 1.0f;}
		nStrip = (int)nStrip2;
		DisplayInformation ();
	}
	/* Left cross key */
	if ( per->on & PDD_DGT_KL )
	{
		nCylinders2 += 0.1f;
		if(nCylinders2 > 10.0f){nCylinders2 = 10.0f;}
		nCylinders = (int)nCylinders2;
		DisplayInformation ();
	}
	/* Right cross key */
	if ( per->on & PDD_DGT_KR )
	{
		nCylinders2 -= 0.1f;
		if(nCylinders2 < 1.0f){nCylinders2 = 1.0f;}
		nCylinders = (int)nCylinders2;
		DisplayInformation ();
	}

	/* A button */
	if ( per->press & PDD_DGT_TA )
	{
		Info.Bilinear = (Info.Bilinear) ? FALSE:TRUE;
		SetContext (&StripHead[0], Info);
		DisplayInformation ();
	}

	/* B button */
	if ( per->press & PDD_DGT_TB )
	{
		Info.Gouraud = (Info.Gouraud) ? FALSE:TRUE;
		SetContext (&StripHead[0], Info);
		DisplayInformation ();
	}

	/* X button */
	if ( per->press & PDD_DGT_TX )
	{
		Info.Textured = (Info.Textured) ? FALSE:TRUE;
		SetContext (&StripHead[0], Info);
		DisplayInformation ();
	}

}

/*--------------------------- End of File --------------------------------*/

