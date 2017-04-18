/*----------------------------------------------------------------
   Name   : Imagine.c  (ARC1 demo)
   Author : Carlos Sarria
   Date   : September 1997

   Copyright : 1997 by VideoLogic Limited. All rights reserved.
   Modified  : 01, July, 1998 by Takeshi Muto / NEC Software,Ltd. for KAMUI
			   04, February, 1999, by Hiroshi Nakayama for KAMUI2
			   16, February, 1999, by Takeshi Muto for Shinobi
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
#include	"vltex.h"				/* for vl sample texture							*/

#include	"kmtools.h"
#include	"kmSpace.h"  /* This is the file with 3D data */

/****************************************************************************/
/**	Valuables for KAMUI *****************************************************/
/****************************************************************************/
	KMSTATUS			status;					/* return status of KAMUI API */
	KMVERSIONINFO		VersionInfo;			/* KAMUI Version information */
	KMSURFACEDESC		PrimarySurfaceDesc;		/* Primary frame buffer */
	KMSURFACEDESC		BackSurfaceDesc;		/* Back-buffer frame buffer */
	KMVERTEXBUFFDESC	VertexBufferDesc;		/* Vertex-buffer */
	KMSTRIPCONTEXT		StripContext01[2];		/* Strip context for disc */
	KMSTRIPHEAD			StripHead01[2];			/* Strip Head for disc*/
	KMSTRIPCONTEXT		StripContext02[2];		/* Strip context for body */
	KMSTRIPHEAD			StripHead02[2];			/* Strip Head for body */
												/* [0]:TYPE01
												   [1]:TYPE03 */

	PKMSURFACEDESC		pFB[2];
	KMDWORD				FBarea[24576 + 19456];
								/* FBstruct 4096 Entry (= 4096 * 24 / 4) */
								/* VQstruct 1024 Entry (= 1024 * 76 / 4) */
	KMDWORD				DUMPAREA[10000];
	KMSYSTEMCONFIGSTRUCT	SystemConfig;
	PKMDWORD			dwDataPtr;

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

float	drx = 0.0f;	/* object rotation step by X axis */
float	dry = 0.002f;	/* object rotation step by Y axis */
float	drz = 0.05f;	/* object rotation step by Z axis */
float	rx = 0.0f;		/* object rotation angle by X axis */
float	ry = 0.0f;		/* object rotation angle by Y axis */
float	rz = 0.0f;		/* object rotation angle by Z axis */
float	PosZ = 0.0f;	/* object position Z */

float   Frame = 0;
KMSURFACEDESC	TexOpaq;
extern TRANSFORM  T[NUM_MESHES];
static float X_Axe[3] = { 1, 0, 0 }, Y_Axe[3] = { 0, 1, 0 }, Z_Axe[3] = { 0, 0, 1 };

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
void ReadMaple (void);

extern float LightDir[3];
/* Textures */
extern unsigned char *spa_space;

/* Peripheral */
PDS_PERIPHERAL *per;

/*-------------------------------------------------------------------------------------*/
/*                                       MAIN                                          */
/*-------------------------------------------------------------------------------------*/
int Kamui_Init (void)
{
int Control = 0, Device, Val = 0;

	txt_ClearScreen();	/* Clear text screen */
	PRINTOUT(("** KMSPACE(KAMUI2&Shinobi) : Refrection mapping **\n"));

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
	dwDataPtr = (PKMDWORD)(((KMDWORD)syMalloc(0x240000) & 0x0FFFFFFFUL) | 0xA0000000);
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
	SystemConfig.nVertexBufferSize		=	0x120000*2;	/* 1MB */
	SystemConfig.nPassDepth			=	1;
	SystemConfig.Pass[0].dwRegionArrayFlag = KM_PASSINFO_AUTOSORT;
	SystemConfig.Pass[0].fBufferSize[0] =  89.0f;
	SystemConfig.Pass[0].fBufferSize[1] =   0.0f;
	SystemConfig.Pass[0].fBufferSize[2] =  11.0f;
	SystemConfig.Pass[0].fBufferSize[3] =   0.0f;
	SystemConfig.Pass[0].fBufferSize[4] =   0.0f;
	kmSetSystemConfiguration(&SystemConfig);


	/*-----------------------------------------------------------------------------------*/
	/* Initialize DisplayString routine */
	txt_InitDisplayString();

	/*----------------------------------------------------------------------------------- */
	/* some initializes */
	SetTextures   ();

	InitContext (StripContext01, StripHead01,Info, &TexOpaq);
	InitContext (StripContext02, StripHead02,Info, &TexOpaq);

	kmChangeStripBlendingMode(&StripHead02[0],KM_IMAGE_PARAM1,KM_SRCALPHA,KM_INVSRCALPHA);
	kmChangeStripListType(&StripHead02[0],KM_TRANS_POLYGON);
	kmChangeStripUseAlpha(&StripHead02[0],KM_IMAGE_PARAM1,KM_TRUE);
	kmChangeStripBlendingMode(&StripHead02[1],KM_IMAGE_PARAM1,KM_SRCALPHA,KM_INVSRCALPHA);
	kmChangeStripListType(&StripHead02[1],KM_TRANS_POLYGON);
	kmChangeStripTextureShadingMode(&StripHead02[1],KM_IMAGE_PARAM1,KM_MODULATE_ALPHA);
	kmChangeStripUseAlpha(&StripHead02[1],KM_IMAGE_PARAM1,KM_TRUE);
	SetBackground (&TexOpaq);
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

	/* This function creates an array of structures with 3D data */
	CreateMeshesArray ();
	InitMeshes (NUM_MESHES, (CASTMESHES *) Mesh);

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
	nTextureType = KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&TexOpaq,				/* OUT	PKMSURFACEDESC	pSurfaceDesc */
		256,					/*	IN	KMINT32			nWidth  */
		256,					/*	IN	KMINT32			nHeight  */
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType */
	);
	Check_Status(status, "kmCreateTextureSurface #1");
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
	pTexture01 = (unsigned long *)&spa_space;
	status = kmLoadTexture(&TexOpaq,			/* PKMSURFACEDESC pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))			/* PKMDWORD pTexture */
							);
	Check_Status(status, "kmLoadTexture #1");
}
/*-------------------------------------------------------------------------------------*/
void NextFrame (void)
{
register i;

	/* シ－ンの初期化 */
	InitScene ();
	for (i=0;i<NUM_MESHES; i++){ResetMatrix (i);}

	for (i=0;i<NUM_MESHES; i++)
	{
		rx += drx;
		ry += dry;
		rz += drz;
		Translate (i, 0.0f, 0.0f, PosZ);
		Rotate   (i, Y_Axe, ry);
		Rotate   (i, X_Axe, rx);
		Rotate   (i, Z_Axe, rz);

		SetSmoothShading (i, (i==1)?C_GREEN: C_RED);
		if (i==1)
		{
			/*	Info.VertexAlpha = FALSE; */
			/*	SetContext (Info); */
			/*	SetVertices (i,  TexOpaq, FX_OPTIC);	*/
			SetVertices (i, StripHead01, FX_OPTIC, Info.Textured);
		}
		else
		{
			/* Info.VertexAlpha = TRUE; */
			/*	SetContext (Info); */
			/*	SetVertices (i,  TexOpaq, FX_OPTIC);	*/
			SetVertices (i, StripHead02, FX_OPTIC, Info.Textured);
		}

	}

	/* シ－ンの終了 */
	EndScene();

	/* フレ－ム数更新 */
	Frame++;
}
/*-------------------------------------------------------------------------------------*/

void DisplayInformation (void)
{
char *Flag[2]   = { "FALSE", "TRUE" };

	txt_SetCursor(0,16);

	PRINTOUT(( "Pad Control\n"));
	PRINTOUT(( " A : Bilinear    %s\n",   Flag[Info.Bilinear]));
	PRINTOUT(( " B : Gouraud     %s\n",   Flag[Info.Gouraud]));
	PRINTOUT(( " X : Textured    %s\n",   Flag[Info.Textured]));
    PRINTOUT(( " Y : HighLight   %s",   Flag[Info.Highlight]));

	Timer ();			/* 評価用タイマ初期化 */
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
		drx = 0.0f;
		dry = 0.0f;
		drz = 0.0f;
/*		PosZ = 0.0f; */
	}

	/* UP cross key */
	if ( per->on & PDD_DGT_KU )
	{
		if(drz > -0.1f) drz -= 0.0002f;
	}
	/* DOWN cross key */
	if ( per->on & PDD_DGT_KD )
	{
		if(drz <  0.1f) drz += 0.0002f;
	}
	/* Left cross key */
	if ( per->on & PDD_DGT_KL )
	{
		if(dry <  0.1f) dry += 0.0002f;
	}
	/* Right cross key */
	if ( per->on & PDD_DGT_KR )
	{
		if(dry > -0.1f) dry -= 0.0002f;
	}

		/* Medama X */
		ry += (float)(per->x1) / 2000.0f;

		/* Medama Y */
		rx += (float)(per->y1) / 2000.0f;

		/* Slider Right */
		PosZ += (float)(per->r) / 100.0f;

		/* Slider Left */
		PosZ -= (float)(per->l) / 100.0f;

	/* A button */
	if ( per->press & PDD_DGT_TA )
	{
		Info.Bilinear = (Info.Bilinear) ? FALSE:TRUE;
		SetContext (StripHead01, Info, &TexOpaq);
		SetContext (StripHead02, Info, &TexOpaq);
		DisplayInformation ();
	}

	/* B button */
	if ( per->press & PDD_DGT_TB )
	{
				Info.Gouraud = (Info.Gouraud) ? FALSE:TRUE;
				SetContext (StripHead01, Info, &TexOpaq);
				SetContext (StripHead02, Info, &TexOpaq);
				DisplayInformation ();
	}

	/* X button */
	if ( per->press & PDD_DGT_TX )
	{
		Info.Textured = (Info.Textured) ? FALSE:TRUE;
		SetContext (StripHead01, Info, &TexOpaq);
		SetContext (StripHead02, Info, &TexOpaq);
		DisplayInformation ();
	}

	/* Y button */
	if ( per->press & PDD_DGT_TY )
	{
		Info.Highlight = (Info.Highlight) ? FALSE:TRUE;
		SetContext (StripHead01, Info, &TexOpaq);
		SetContext (StripHead02, Info, &TexOpaq);
		DisplayInformation ();
	}

}

/*--------------------------- End of File --------------------------------*/