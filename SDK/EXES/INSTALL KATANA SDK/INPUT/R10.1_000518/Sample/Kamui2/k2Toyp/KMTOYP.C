/*----------------------------------------------------------------
   Name   : kmtoyp.c
   Author : Carlos Sarria
   Date   : September 1997 (updated Jan98)

   Copyright : 1998 by VideoLogic Limited. All rights reserved.
   Modified  :	June     08. 1998 by Takeshi Muto / NEC Software,Ltd. for KAMUI
				February 04. 1999 by Hiroshi Nakayama for KAMUI2
				February 16. 1999 by Takeshi Muto for Shinobi
 ----------------------------------------------------------------*/

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
#include    "kmptool.h"
#include	"Plane.h"  /* This is the file with 3D data */

/****************************************************************************/
/**	Valuables for KAMUI *****************************************************/
/****************************************************************************/
	KMSTATUS			status;					/* return status of KAMUI API */
	KMVERSIONINFO		VersionInfo;			/* KAMUI Version information */
	KMSURFACEDESC		PrimarySurfaceDesc;		/* Primary frame buffer */
	KMSURFACEDESC		BackSurfaceDesc;		/* Back-buffer frame buffer */
	KMVERTEXBUFFDESC	VertexBufferDesc;		/* Vertex-buffer */

	KMSTRIPCONTEXT		StripContext[2];		/* Strip context */
	KMSTRIPHEAD			StripHead[2];			/* Strip Head */
												/* [0]:TYPE01
												   [1]:TYPE03 */
	KMDWORD				FogDensity;				/* Fog density */
	KMDWORD				FogD = 1;

	PKMSURFACEDESC		pFB[2];
	KMDWORD				FBarea[24576 + 19456];
								/* FBstruct 4096 Entry (= 4096 * 24 / 4) */
								/* VQstruct 1024 Entry (= 1024 * 76 / 4) */
	KMDWORD				DUMPAREA[10000];
	KMSYSTEMCONFIGSTRUCT	SystemConfig;
	PKMDWORD			dwDataPtr;

	int					FogM = 255;
	int					FogE = 11;
	int					FogAutoChange = 1;

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

static float		Frame	= 0;
float				dSpeed	= 0.05f;
float				Speed	= 0.0f;
float				PosZ	= 800.0f;
float				Roll	= PI/8.0f;		/* Rad : (dSpeed * 450.0f)*(PI/180.0f) */
float				RRx		= 500.0f;		/* dSpeed * 10000.0f */
float				RRz		= 700.0f;		/* dSpeed * 14000.0f */

KMSURFACEDESC		TexOpaq, TexBack;

static float Axis[3] = { 0,1,0},Axis1[3] = { 0,0,1},Axis2[3] = { 1,0,0};

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
void DisplayInformation	(void);
static void BuildFogTable       (void);
void ReadMaple (void);

/* Peripheral */
PDS_PERIPHERAL *per;

/* Textures */
extern unsigned char toy_back;
extern unsigned char toy_opaq;

/* Macros for kamui */
#define		GetRED(col)			((KMFLOAT) ( ((col) & 0x00ff0000) >> 16 ) / 256.0f)
#define		GetGREEN(col)		((KMFLOAT) ( ((col) & 0x0000ff00) >>  8 ) / 256.0f)
#define		GetBLUE(col)		((KMFLOAT) ( ((col) & 0x000000ff)       ) / 256.0f)
#define		GetALPHA(col)		((KMFLOAT) ( ((col) & 0xff000000) >> 24 ) / 256.0f)

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
/**	kmtri_triangles  by T.Hirata ********************************************/
/****************************************************************************/
void
kmtri_triangles ( KMVERTEXBUFFDESC		BufferDesc,
				  KMSTRIPHEAD			StripHead[2],
				  int  					nNumFaces,
				  int  					pFaces[][3],
				  PPVRVERTEX  			pVertices,
				  int					bTexture)
{
	KMSTATUS	status;
	int			i;
	KMVERTEX_01	Ver01;				/* for NO-TEXTURE-GOURAUD */
	KMVERTEX_03	Ver03;				/* for TEXTURE-GOURAUD */

	if(bTexture == TRUE)
	{
		kmStartStrip( &BufferDesc , &StripHead[1] );
									/* VERTEX TYPE_03用頂点登録開始 */
	}
	else
	{
		kmStartStrip( &BufferDesc , &StripHead[0] );
									/* VERTEX TYPE_01用頂点登録開始 */
	}

	for(i = 0; i < nNumFaces; i++)
	{
		if(bTexture == TRUE)
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
		else
		{	/* if(bTexture == TRUE) : NO-TEXTURE */
			Ver01.ParamControlWord	= KM_VERTEXPARAM_NORMAL;
			Ver01.fX				= pVertices[pFaces[i][0]].fX;
			Ver01.fY				= pVertices[pFaces[i][0]].fY;
#if defined(_STRICT_UNION_)
			Ver01.u.fZ				= pVertices[pFaces[i][0]].fInvW;
#else
			Ver01.fZ				= pVertices[pFaces[i][0]].fInvW;
#endif
			Ver01.fBaseAlpha		= GetALPHA(pVertices[pFaces[i][0]].u32Colour);
			Ver01.fBaseRed			= GetRED  (pVertices[pFaces[i][0]].u32Colour);
			Ver01.fBaseGreen		= GetGREEN(pVertices[pFaces[i][0]].u32Colour);
			Ver01.fBaseBlue			= GetBLUE (pVertices[pFaces[i][0]].u32Colour);
			status = kmSetVertex(&BufferDesc,&Ver01,KM_VERTEXTYPE_01,sizeof(KMVERTEX_01) );
			Check_Status(status, "kmSetVertex");

			Ver01.ParamControlWord	= KM_VERTEXPARAM_NORMAL;
			Ver01.fX				= pVertices[pFaces[i][1]].fX;
			Ver01.fY				= pVertices[pFaces[i][1]].fY;
#if defined(_STRICT_UNION_)
			Ver01.u.fZ				= pVertices[pFaces[i][1]].fInvW;
#else
			Ver01.fZ				= pVertices[pFaces[i][1]].fInvW;
#endif
			Ver01.fBaseAlpha		= GetALPHA(pVertices[pFaces[i][1]].u32Colour);
			Ver01.fBaseRed			= GetRED  (pVertices[pFaces[i][1]].u32Colour);
			Ver01.fBaseGreen		= GetGREEN(pVertices[pFaces[i][1]].u32Colour);
			Ver01.fBaseBlue			= GetBLUE (pVertices[pFaces[i][1]].u32Colour);
			status = kmSetVertex(&BufferDesc,&Ver01,KM_VERTEXTYPE_01,sizeof(KMVERTEX_01) );
			Check_Status(status, "kmSetVertex");

			Ver01.ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;
			Ver01.fX				= pVertices[pFaces[i][2]].fX;
			Ver01.fY				= pVertices[pFaces[i][2]].fY;
#if defined(_STRICT_UNION_)
			Ver01.u.fZ				= pVertices[pFaces[i][2]].fInvW;
#else
			Ver01.fZ				= pVertices[pFaces[i][2]].fInvW;
#endif
			Ver01.fBaseAlpha		= GetALPHA(pVertices[pFaces[i][2]].u32Colour);
			Ver01.fBaseRed			= GetRED  (pVertices[pFaces[i][2]].u32Colour);
			Ver01.fBaseGreen		= GetGREEN(pVertices[pFaces[i][2]].u32Colour);
			Ver01.fBaseBlue			= GetBLUE (pVertices[pFaces[i][2]].u32Colour);
			status = kmSetVertex(&BufferDesc,&Ver01,KM_VERTEXTYPE_01,sizeof(KMVERTEX_01) );
			Check_Status(status, "kmSetVertex");
		} /* end of if(bTexture == TRUE) */
	}
}

/*-------------------------------------------------------------------------------------*/
/*                                       MAIN                                          */
/*-------------------------------------------------------------------------------------*/
int Kamui_Init (void)
{
int Control = 0, Device, Val = 0;

	txt_ClearScreen();	/* Clear text screen */
	PRINTOUT(("** KMTOYP(KAMUI2&Shinobi) : Fog test **\n"));

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
	SetTextures ();
	InitContext  (Info, &TexOpaq);
	SetBackground (&TexBack);
	BuildFogTable ();
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

	/* This function creates an array of structures with 3D data (it is in Plane.h)*/
	CreateMeshesArray ();
	InitMeshes (NUM_MESHES, (CASTMESHES *) Mesh);

#if 0
   	while (TRUE)
	{
		ReadMaple ();
		NextFrame ();
		/* Change fog density */
		if(((frame % 400) == 0)&&(FogAutoChange == 1))
		{
			FogDensity += FogD;	/* FF09 - FF0D */
			if(FogDensity > 0xFF0E) { FogDensity = 0xFF0D; FogD = -FogD; }
			if(FogDensity < 0xFF09) { FogDensity = 0xFF0A; FogD = -FogD; }
			status = kmSetFogDensity(FogDensity);
			Check_Status(status, "kmSetFogDensity");
			DisplayInformation ();
		}
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
		&TexOpaq,				/* OUT	PKMSURFACEDESC	pSurfaceDesc */
		256,					/*	IN	KMINT32			nWidth  */
		256,					/*	IN	KMINT32			nHeight  */
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType */
	);
	Check_Status(status, "kmCreateTextureSurface #2");
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
	pTexture01 = (unsigned long *)&toy_back;
	status = kmLoadTexture(&TexBack,			/* PKMSURFACEDESC pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))			/* PKMDWORD pTexture */
							);
	Check_Status(status, "kmLoadTexture #1");
	/*----------------------------------------------------------------------------------- */
	/* Load and set texture */
	pTexture01 = (unsigned long *)&toy_opaq;
	status = kmLoadTexture(&TexOpaq,			/* PKMSURFACEDESC pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))			/* PKMDWORD pTexture */
							);
	Check_Status(status, "kmLoadTexture #2");

}
/*-------------------------------------------------------------------------------------*/
void NextFrame (void)
{
register i;

	/* シ－ンの初期化 */
	InitScene (); 

	for (i=0;i<NUM_MESHES; i++){ResetMatrix (i);}

	Speed += dSpeed;

	/*  The plane   */
	for (i=0;i<NUM_MESHES; i++) 
	{
		Translate (i, cos(Speed) * RRx, 0, -sin(Speed) * RRz + PosZ);
		Rotate   (i, Axis, Speed);
		Rotate   (i, Axis1, Roll);

		if (i==HELIX){ Rotate   (i, Axis1, Frame);}
		SetSmoothShading (i, C_NONE);
		SetVertices (i, FX_NONE, Info);
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

	txt_SetCursor(0,15);

	PRINTOUT(( " Fog Density : %04Xh\n",  FogDensity ));

	PRINTOUT(( " A : Bilinear    %s\n", Flag[Info.Bilinear]));
	PRINTOUT(( " B : Gouraud     %s\n", Flag[Info.Gouraud]));
	PRINTOUT(( " X : Textured    %s\n", Flag[Info.Textured]));
/*	PRINTOUT(( " Y : Table Fog   %s\n", Flag[Info.VertexFog])); */

}
/*------------------------------------------------------------------------------------*/
void BuildFogTable (void)
{
	int				i;
	float			depth;
	KMPACKEDARGB	fogcol;
	KMFLOAT			FogTable[128];

	/* Fog Color */
	fogcol.byte.bBlue	= 0.5 * 255;
	fogcol.byte.bGreen	= 0.5 * 255;
	fogcol.byte.bRed	= 0.5 * 255;
	status = kmSetFogTableColor(fogcol);
	Check_Status(status, "kmSetFogTableColor");

	/* Fog Density */
	FogDensity = 0xFF0B;		/* FF09 - FF0D */
/*	status = kmSetFogDensity(0xFF09); */
	status = kmSetFogDensity(FogDensity);
	Check_Status(status, "kmSetFogDensity");

	/* Fog Table */
	for(i = 0; i < 128; i++)
	{
#define	FOG_MIN		(-0.8f)
		FogTable[i] = 1.0f - (float)i * ((1.0f - FOG_MIN) / 128.0f);
		if(FogTable[i] < 0.0f){FogTable[i] = 0.0f;}
	}
	status = kmSetFogTable(&FogTable[0]);
	Check_Status(status, "kmSetFogTable");

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
			FogM = 255;
			FogE = 11;
			FogDensity = FogM * 256 + FogE;
			status = kmSetFogDensity(FogDensity);
			Check_Status(status, "kmSetFogDensity");
			dSpeed = 0.0f;
			Roll = (dSpeed * 450.0f) * (PI/180.0f);
			RRx	= dSpeed * 10000.0f;
			RRz	= dSpeed * 14000.0f;
			DisplayInformation ();
	}

	/* UP cross key */
	if ( per->on & PDD_DGT_KU )
	{
		FogAutoChange = 0;
		FogM += 1;
		if(FogM > 255)
		{
			FogE += 1;
			if(FogE > 255)
			{
				FogE = 255;
				FogM = 255;
			}
			else
			{
				FogM = 1;
			}
		}
		FogDensity = FogM * 256 + FogE;
		DisplayInformation ();
		status = kmSetFogDensity(FogDensity);
		Check_Status(status, "kmSetFogDensity");
	}
	/* DOWN cross key */
	if ( per->on & PDD_DGT_KD )
	{
		FogAutoChange = 0;
		FogM -= 1;
		if(FogM < 1)
		{
			FogE -= 1;
			if(FogE < 1)
			{
				FogE = 1;
				FogM = 1;
			}
			else
			{
				FogM = 255;
			}
		}
		FogDensity = FogM * 256 + FogE;
		DisplayInformation ();
		status = kmSetFogDensity(FogDensity);
		Check_Status(status, "kmSetFogDensity");
	}
	/* Left cross key */
	if ( per->on & PDD_DGT_KL )
	{
		dSpeed += 0.0002;
		Roll = (dSpeed * 450.0f) * (PI/180.0f);
		RRx	= dSpeed * 10000.0f;
		RRz	= dSpeed * 14000.0f;
	}
	/* Right cross key */
	if ( per->on & PDD_DGT_KR )
	{
		dSpeed -= 0.0002;
		Roll = (dSpeed * 450.0f) * (PI/180.0f);
		RRx	= dSpeed * 10000.0f;
		RRz	= dSpeed * 14000.0f;
	}

	/* Medama X */
	Speed -= (float)(per->x1) / 2000.0f;

	/* Slider Right */
	PosZ += (float)(per->r) / 100.0f;
	if(PosZ > 2000.0f){PosZ = 2000.0f;}

	/* Slider Left */
	PosZ -= (float)(per->l) / 100.0f;

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
		Info.VertexFog = (Info.VertexFog) ? FALSE:TRUE;
		SetContext (Info);
		DisplayInformation ();
	}
}

/*--------------------------- End of File --------------------------------*/

