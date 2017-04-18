/*----------------------------------------------------------------
   Name   : kmree.c
   Author : Carlos Sarria
   Date   : September 1997 (updated Jan98)

   Copyright : 1998 by VideoLogic Limited. All rights reserved.
   Modified  :	June     17. 1998 by Takeshi Muto / NEC Software,Ltd. for KAMUI
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
#include	<Shinobi.h>
#include	<sg_sytmr.h>	/* System timer */

#pragma warning (disable : 4244) /* Disables float to double conversion warning */
#pragma warning (disable : 4056)
#define _STRICT_UNION_
#define _CLX2_
#define _CLX_

#include	"kamui2.h"				/* for Kamui Call */
#include	"dispstr.h"				/* for DisplayString */
#include    "kmttool.h"
#include 	"kmtree.h"  			/* This is the file with 3D data */

/****************************************************************************/
/**	Valuables for KAMUI *****************************************************/
/****************************************************************************/
	KMSTATUS			status;					/* return status of KAMUI API */
	KMVERSIONINFO		VersionInfo;			/* KAMUI Version information */
	KMSURFACEDESC		PrimarySurfaceDesc;		/* Primary frame buffer */
	KMSURFACEDESC		BackSurfaceDesc;		/* Back-buffer frame buffer */
	KMVERTEXBUFFDESC	VertexBufferDesc;		/* Vertex-buffer */
	KMVERTEXCONTEXT		VertexContext01;		/* Vertex context */
	KMVERTEXCONTEXT		VertexContext02;		/* Vertex context */

	KMSTRIPCONTEXT		StripContext01[2];		/* Strip context for bark */
	KMSTRIPHEAD			StripHead01[2];			/* Strip Head for bark */
	KMSTRIPCONTEXT		StripContext02[2];		/* Strip context for leaf */
	KMSTRIPHEAD			StripHead02[2];			/* Strip Head for leaf */
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

float		Frame = 0;
float		PosZ = 30.0f;
float		Ry = 0.0f;
int			GeometryFlag = 1;
static float X_Axe[3] = { 1, 0, 0 }, Y_Axe[3] = { 0, 1, 0 }, Z_Axe[3] = { 0, 0, 1 };

KMSURFACEDESC	TexBark, TexLeaves, TexForest;

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
	FALSE,       /* Highlight     */
};

int NumLeaf = 2, Translucent = FALSE;
int StripLengths[3600];
static unsigned	TotalPolys = 0;

/* Prototypes */

static void SetTextures			(void);
void NextFrame			(void);
static void DisplayInformation	(void);
static void InitContext (PKMSTRIPCONTEXT pStripContext,PKMSTRIPHEAD	pStripHead,INFO CInfo,PKMSURFACEDESC pTexture);
static void SetContext (PKMSTRIPHEAD pStripHead, INFO CInfo, PKMSURFACEDESC pTexture);
static void Draw(void);
void ReadMaple (void);

/* Peripheral */
PDS_PERIPHERAL *per;

/* Textures */
extern unsigned char tr1_bark;
extern unsigned char tr1_leaf;
extern unsigned char tr1_forest;

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
int	i;

	txt_ClearScreen();	/* Clear text screen */
	PRINTOUT(("** KMTREE(KAMUI2&Shinobi) : many polygons **\n"));

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
								FALSE,				/* bDither */
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
	dwDataPtr = (PKMDWORD)(((KMDWORD)syMalloc(0x340000) & 0x0FFFFFFFUL) | 0xA0000000);
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
	SystemConfig.nVertexBufferSize		=	0x1a0000*2;	/* 1MB */
	SystemConfig.nPassDepth			=	1;
	SystemConfig.Pass[0].dwRegionArrayFlag = KM_PASSINFO_AUTOSORT;
	SystemConfig.Pass[0].fBufferSize[0] =  91.0f;
	SystemConfig.Pass[0].fBufferSize[1] =   0.0f;
	SystemConfig.Pass[0].fBufferSize[2] =   9.0f;
	SystemConfig.Pass[0].fBufferSize[3] =   0.0f;
	SystemConfig.Pass[0].fBufferSize[4] =   0.0f;
	kmSetSystemConfiguration(&SystemConfig);


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
	InitContext (StripContext01, StripHead01,Info, &TexBark);
	InitContext (StripContext02, StripHead02,Info, &TexLeaves);
	SetBackground (&TexForest);				/* textured background */
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

	/* This function creates an array of structures with 3D data (It is in Tree.h)*/
	CreateMeshesArray ();
	InitMeshes (NUM_MESHES, (CASTMESHES *) Mesh);

	/*
	 * The model of the leaves is a collection of 3520 two polygons strips.
	 * The length for each strip must be set to 2.
	 */
	for (i=0; i<3520; i++) StripLengths[i] = 2;

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
		&TexBark,				/* OUT	PKMSURFACEDESC	pSurfaceDesc */
		32,						/*	IN	KMINT32			nWidth  */
		32,						/*	IN	KMINT32			nHeight  */
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType */
	);
	Check_Status(status, "kmCreateTextureSurface #1");
	/*----------------------------------------------------------------------------------- */
	/* Create texture surface */
	nTextureType = KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&TexLeaves,				/* OUT	PKMSURFACEDESC	pSurfaceDesc */
		32,						/*	IN	KMINT32			nWidth  */
		32,						/*	IN	KMINT32			nHeight  */
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType */
	);
	Check_Status(status, "kmCreateTextureSurface #2");
	/*----------------------------------------------------------------------------------- */
	/* Create texture surface */
	nTextureType = KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565;	/* Set texture type */
	status = kmCreateTextureSurface(
		&TexForest,				/* OUT	PKMSURFACEDESC	pSurfaceDesc */
		256,					/*	IN	KMINT32			nWidth  */
		256,					/*	IN	KMINT32			nHeight  */
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType */
	);
	Check_Status(status, "kmCreateTextureSurface #3");
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
	pTexture01 = (unsigned long *)&tr1_bark;
	status = kmLoadTexture(&TexBark,			/* PKMSURFACEDESC pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))			/* PKMDWORD pTexture */
							);
	Check_Status(status, "kmLoadTexture #1");
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
	pTexture01 = (unsigned long *)&tr1_leaf;
	status = kmLoadTexture(&TexLeaves,			/* PKMSURFACEDESC pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))			/* PKMDWORD pTexture */
							);
	Check_Status(status, "kmLoadTexture #2");
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
	pTexture01 = (unsigned long *)&tr1_forest;
	status = kmLoadTexture(&TexForest,			/* PKMSURFACEDESC pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))			/* PKMDWORD pTexture */
							);
	Check_Status(status, "kmLoadTexture #3");
}
/*-------------------------------------------------------------------------------------*/
void NextFrame (void)
{
register i;

	InitScene ();							/* シ－ン開始 */
	if (GeometryFlag == 1) /* The scene is calculated just once. */
	{
		GeometryFlag = 0;

		for (i=0;i<NUM_MESHES; i++){ResetMatrix (i);}

		for (i=0;i<NUM_MESHES; i++)
		{
			Translate (i, 0, 0, PosZ);
			Rotate (i, Y_Axe, Ry);
			SetVertices (i);
		}
		Draw();								/* 描画 */
	}
	else
	{/* The set of PVRtriangles is sent for render in each frame. */
		Draw();								/* 描画 */
	}
	Frame++;									/* フレ－ム数更新 */
}

/*-------------------------------------------------------------------------------------*/

void DisplayInformation (void)
{
char *Flag[2]   = { "FALSE", "TRUE" };

	txt_SetCursor(0,17);

	PRINTOUT(( " A : Bilinear    %s\n", Flag[Info.Bilinear]));
	PRINTOUT(( " B : Gouraud     %s\n", Flag[Info.Gouraud]));
	PRINTOUT(( " X : Textured    %s\n", Flag[Info.Textured]));

    PRINTOUT(( " Y : Start again"));
}

/*----------------------------------------------------------------------*/
/*  Function Name   : InitContext                                       */
/*  Inputs          : pStripContext , pStripHead , CInfo , pTexture		*/
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     :                                                   */
/*----------------------------------------------------------------------*/

void InitContext (PKMSTRIPCONTEXT pStripContext,
				  PKMSTRIPHEAD	pStripHead,
				  INFO CInfo,
				  PKMSURFACEDESC pTexture)
{
	/*-------------------------------------------------------------------------------- */
	/* Initialize Strip Context */
	/*-------------------------------------------------------------------------------- */
	/* VertexType01用KMSTRIPHEADの構築	*/
	memset( pStripContext, 0, sizeof(KMSTRIPCONTEXT));			/* Crear Context */
	InitStripContext01(pStripContext,pStripHead);				/* Initialize context */
	/* VertexType03用KMSTRIPHEADの構築	*/
	memset( pStripContext+1, 0, sizeof(KMSTRIPCONTEXT));		/* Crear Context */
	InitStripContext03(pStripContext+1,pStripHead+1,pTexture);	/* Initialize context */

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
		kmChangeStripGouraud(pStripHead,KM_TRUE);	/* for VERTEX TYPE01 */
		kmChangeStripGouraud(pStripHead+1,KM_TRUE);	/* for VERTEX TYPE03 */
	}
	else
	{
		/* Set shading mode */
		kmChangeStripGouraud(pStripHead,KM_FALSE);	/* for VERTEX TYPE01 */
		kmChangeStripGouraud(pStripHead+1,KM_FALSE);/* for VERTEX TYPE03 */
	}
	kmChangeStripFlipUV(pStripHead+1,KM_IMAGE_PARAM1,KM_FLIP_UV);
}

/*----------------------------------------------------------------------*/
/*  Function Name   : SetContext                                        */
/*  Inputs          : CInfo                                             */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     :                                                   */
/*----------------------------------------------------------------------*/

void SetContext (PKMSTRIPHEAD pStripHead, INFO CInfo, PKMSURFACEDESC pTexture)
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
		kmChangeStripGouraud(pStripHead,KM_TRUE);	/* for VERTEX TYPE01 */
		kmChangeStripGouraud(pStripHead+1,KM_TRUE);	/* for VERTEX TYPE03 */
	}
	else
	{
		/* Set shading mode */
		kmChangeStripGouraud(pStripHead,KM_FALSE);	/* for VERTEX TYPE01 */
		kmChangeStripGouraud(pStripHead+1,KM_FALSE);/* for VERTEX TYPE03 */
	}

	kmChangeStripFlipUV(pStripHead+1,KM_IMAGE_PARAM1,KM_FLIP_UV);
}

/*----------------------------------------------------------------------*/
/*  Function Name   : Draw												*/
/*  Inputs          :                                                   */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    : CMesh  PVRVert			                        */
/*  Description     : The scene is rendered without any additional      */
/*                    calculation.                                      */
/*----------------------------------------------------------------------*/
void Draw(void)
{
extern PVRVERTEX		*PVRVert[256];
extern CASTMESHES		CMesh[256];

	kmtri_triangles (	&VertexBufferDesc,				/* PKMVERTEXBUFFDESC	pBufferDesc, */
						StripHead01,					/* PKMSTRIPHEAD			pStripHead, */
						CMesh[0].NumFaces,				/* int  nNumFaces, */
						(int(*)[3])CMesh[0].Faces,		/* int  pFaces[][3], */
						PVRVert[0],						/* PPVRVERTEX  pVertices */
						Info.Textured					/* int	bTexture */
						);

	kmtri_tstrips (		&VertexBufferDesc,				/* PKMVERTEXBUFFDESC	pBufferDesc, */
						StripHead02,					/* PKMSTRIPHEAD			pStripHead, */
						NumLeaf,						/* int  nNumFaces, */
						StripLengths,					/* int  *StripLengths, */
						PVRVert[1],						/* PPVRVERTEX  pVertices */
						Info.Textured					/* int	bTexture */
						);

	txt_SetCursor(0,2);
	PRINTOUT(("Number of leaves     : %8d\n",NumLeaf));
	PRINTOUT(("Max number of leaves : %8d\n",CMesh[1].NumFaces));
	PRINTOUT(("Number of polygons   : %8d\n",(NumLeaf + CMesh[0].NumFaces)));

	if (NumLeaf < CMesh[1].NumFaces)
	{
		NumLeaf += 2;
	}
	else
	{
		NumLeaf = 2;
	}

	TotalPolys = CMesh[0].NumFaces + NumLeaf;

	EndScene();											/* シ－ン終了 */
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

	/* UP cross key */
	if ( per->on & PDD_DGT_KU )
	{
		PosZ += 1.0f;
		GeometryFlag = 1;
/*		DoGeometry (0.0f, 0.0f, PosZ, 0.0f, Ry, 0.0f); */
	}
	/* DOWN cross key */
	if ( per->on & PDD_DGT_KD )
	{
		PosZ -= 1.0f;
		GeometryFlag = 1;
	}
	/* Left cross key */
	if ( per->on & PDD_DGT_KL )
	{
		Ry += 0.01f;
		GeometryFlag = 1;
	}
	/* Right cross key */
	if ( per->on & PDD_DGT_KR )
	{
		Ry -= 0.01f;
		GeometryFlag = 1;
	}

	/* A button */
	if ( per->press & PDD_DGT_TA )
	{
		Info.Bilinear = (Info.Bilinear) ? FALSE:TRUE;
		SetContext (StripHead01, Info, &TexBark);
		SetContext (StripHead02, Info, &TexLeaves);
		DisplayInformation ();
	}

	/* B button */
	if ( per->press & PDD_DGT_TB )
	{
		Info.Gouraud = (Info.Gouraud) ? FALSE:TRUE;
		SetContext (StripHead01, Info, &TexBark);
		SetContext (StripHead02, Info, &TexLeaves);
		DisplayInformation ();
	}

	/* X button */
	if ( per->press & PDD_DGT_TX )
	{
		Info.Textured = (Info.Textured) ? FALSE:TRUE;
		SetContext (StripHead01, Info, &TexBark);
		SetContext (StripHead02, Info, &TexLeaves);
		DisplayInformation ();
	}

	/* Y button */
	if ( per->press & PDD_DGT_TY )
	{
		NumLeaf = 2;
	}
}

/*--------------------------- End of File --------------------------------*/