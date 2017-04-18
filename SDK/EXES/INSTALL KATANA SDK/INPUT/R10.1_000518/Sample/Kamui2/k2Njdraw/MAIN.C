#include <shinobi.h>
#include <kamui2.h>
#include <kmutil.h>
#include <sg_sycbl.h>
#include <sg_sytmr.h>
#include <dispstr.h>
#include "gte.h"
#include "model.h"

extern KG_OBJECT TEAPOT_OBJECT[];
extern KG_OBJECT object_F40_GTE_sh_null1_1_null1_1[];
extern KG_TEXLIST texlist_F40_GTE_sh_null1_1;

/* Read From Texture */
extern KMSURFACEDESC Texture[];

#define TEXTUREMEMORYSIZE 	(0x400000)
#define VERTEXBUFFERSIZE	(0x280000)
#define TEXTUREBUFSIZE		(256 * 256 * 2 + 2048)

/*
	Prototypes
*/
Int UserMain(void);
Int UserInit(void);
void PALExtCallbackFunc(PVOID pCallbackArguments); 

/*
	Global Params
*/

KMVERTEXBUFFDESC 		VertexBufferDesc;
KMSYSTEMCONFIGSTRUCT 	SystemConfig;
KMSURFACEDESC           PrimarySurfaceDesc;
KMSURFACEDESC           BackSurfaceDesc;

PKMVOID					pConvertedModel;

NJS_PERIPHERAL 			*per;

PKG_OBJECT				pCurrentObject;
PKGVERTEX				pVertexWork;
KMDWORD					pTexWork;
KMDWORD					frameCount = 0;
float					vx, vy, vz;
float					fbank;
void main(void)
{

#ifdef __GNUC__
	shinobi_workaround();
#endif
   /* Check the cable for NTSC/PAL or VGA...works for SCART. */
    switch (syCblCheck())
	{
        /* Initialize the display device and set the frame buffer based on the video mode. */
        case SYE_CBL_NTSC:  /* U.S./North America NTSC (60Hz) and Brazil PAL-M (60Hz). */
            sbInitSystem (KM_DSPMODE_NTSCNI640x480, KM_DSPBPP_RGB565, 1);
            break;
        case SYE_CBL_PAL:   /* Europe PAL (50Hz) and Argentina PAL-N (50Hz).*/
            sbInitSystem (KM_DSPMODE_PALNI640x480EXT, KM_DSPBPP_RGB565, 1);

			/*	Change the PAL height ratio */
			kmSetPALEXTCallback(PALExtCallbackFunc,NULL);
			kmSetDisplayMode (KM_DSPMODE_PALNI640x480EXT, KM_DSPBPP_RGB565, TRUE, FALSE);

            break;
        case SYE_CBL_VGA:   /* Standard VGA. */
            sbInitSystem (KM_DSPMODE_VGA, KM_DSPBPP_RGB565, 1);
            break;
        default:
            syBtExit();     /* Unknown video type, return to Dreamcast BootROM. */
	}

	UserInit();

	/* Render Loop */
	while(UserMain())
	{
		pdExecPeripheralServer();
	}
	sbExitSystem();
}

/*------------------------------------------------------------*/
/*  Function Name   : PALExtCallbackFunc                      */
/*  Inputs          : pCallbackArguments                      */  
/*  Outputs         : None                                    */
/*  Returns         : None                                    */
/*  Globals Used    :                                         */
/*  Description     : PAL mode callback (set the height ratio)*/ 
/*------------------------------------------------------------*/

VOID STATIC	PALExtCallbackFunc(PVOID pCallbackArguments)
{
PKMPALEXTINFO	pInfo;

	pInfo = (PKMPALEXTINFO)pCallbackArguments;
	pInfo->nPALExtMode = KM_PALEXT_HEIGHT_RATIO_1_133;	   //for PAL extended mode
	return;
}




/*
*		Init
*/
Int UserInit(void)
{
	PKMSURFACEDESC	pFB[2];
	KMWORKAREASIZE	TexWorkArea;

	pFB[0] = &PrimarySurfaceDesc;
	pFB[1] = &BackSurfaceDesc;
	SystemConfig.dwSize				=	sizeof(KMSYSTEMCONFIGSTRUCT);
	SystemConfig.flags				=	KM_CONFIGFLAG_NOWAITVSYNC | KM_CONFIGFLAG_ENABLE_CLEAR_FRAMEBUFFER; /* | KM_CONFIGFLAG_ENABLE_2V_LATENCY;  */
	SystemConfig.pBufferDesc 		= 	&VertexBufferDesc;
	SystemConfig.ppSurfaceDescArray	=	pFB;
	SystemConfig.fb.nNumOfFrameBuffer	=	2;
	SystemConfig.nNumOfVertexBank	=	2;
	SystemConfig.nPassDepth			= 	1;

	/*
		Texture Memory Settings
	*/
	SystemConfig.nTextureMemorySize = 	TEXTUREMEMORYSIZE;	/* Texture 4MB */

	TexWorkArea.dwNumberOfFameBuffes 	= SystemConfig.fb.nNumOfFrameBuffer;		/* Number of Frame buffers */
	TexWorkArea.dwNumberOfNativeBuffers	= 2;										/* Number of Native buffer */
	TexWorkArea.dwNumberOfTextures		= 1024;			/* Number of Textures (No small VQ) */
	TexWorkArea.dwNumberOf8x8SmallVQ	= 0;		/* Number of 8x8 small VQ texture */
	TexWorkArea.dwNumberOf8x8SmallVQmm	= 0;		/* Number of 8x8 small VQ mipmap texture */
	TexWorkArea.dwNumberOf16x16SmallVQ	= 0;		/* Number of 16x16 small VQ texture */
	TexWorkArea.dwNumberOf16x16SmallVQmm= 0;	/* Number of 16x16 small VQ mipmap texture */
	TexWorkArea.dwNumberOf32x32SmallVQ	= 0;		/* Number of 32x32 small VQ texture */
	TexWorkArea.dwNumberOf32x32SmallVQmm= 0;	/* Number of 32x32 small VQ mipmap texture */
	TexWorkArea.dwNumberOf64x64SmallVQ	= 0;		/* Number of 64x64 small VQ texture */
	TexWorkArea.dwNumberOf64x64SmallVQmm= 0;	/* Number of 64x64 small VQ mipmap texture */
	kmuCalculateKamuiWorkareaSize( &TexWorkArea );

	SystemConfig.nNumOfTextureStruct 	= 1024;
	SystemConfig.nNumOfSmallVQStruct 	= 0;
	SystemConfig.pTextureWork			= (PKMDWORD)syMalloc(TexWorkArea.dwKamuiWorkareaSize);

	/*
		Vertex Buffer Settings
	*/
	SystemConfig.pVertexBuffer 			= (PKMDWORD)(((KMDWORD)syMalloc(VERTEXBUFFERSIZE) & 0x0FFFFFFFUL ) | 0xA0000000UL);
										  /* Map to Cache Through Area */
	SystemConfig.nVertexBufferSize 		= VERTEXBUFFERSIZE;

	SystemConfig.Pass[0].dwRegionArrayFlag = KM_PASSINFO_AUTOSORT;
	SystemConfig.Pass[0].fBufferSize[0] =  80.0f;
	SystemConfig.Pass[0].fBufferSize[1] =   0.0f;
	SystemConfig.Pass[0].fBufferSize[2] =  20.0f;
	SystemConfig.Pass[0].fBufferSize[3] =   0.0f;
	SystemConfig.Pass[0].fBufferSize[4] =   0.0f;

	kmSetSystemConfiguration(&SystemConfig);
	txt_InitDisplayString();

	kgInitGeometry(320.0f, 240.0f, 2.0f);

	vx	= 0.0f;
	vy	= 0.0f;
	vz	= 20.0f;
	kgSetView(&ViewMatrix, vx, vy, vz, 0.0f, 0.0f, 0.0f);

	fbank = 0.0f;

	kgSetAmbientColor		(0.5f, 0.5f, 0.5f);
	kgSetParallelLightDir	(0, 0.0f, -1.0f, 0.0f);	/* No. 0 Light Dir */
	kgSetParallelLightColor	(0, 0.6f, 0.6f, 0.6f);	/* No. 0 Light Color */

	kgSetParallelLightDir	(1, 0.0f, 1.0f, 0.0f);	/* No. 1 Light Dir */
	kgSetParallelLightColor	(1, 0.0f, 0.0f, 0.0f);	/* No. 1 Light Color */

	kgSetParallelLightDir	(2, 0.0f, 1.0f, 1.0f);	/* No. 2 Light Dir */
	kgSetParallelLightColor	(2, 0.0f, 0.0f, 0.0f);	/* No. 2 Light Color */

	LoadTextureList(&texlist_F40_GTE_sh_null1_1);
	kgSetTexList(Texture);

	pCurrentObject = object_F40_GTE_sh_null1_1_null1_1;
}

/*
*		Main Loop
*/
Int UserMain(void)
{
	Uint32 time1, time2;
	KMPACKEDARGB Bordar1, Bordar2;

	Bordar1.dwPacked = 0x00FFFFFF;
	Bordar2.dwPacked = 0x00000000;

	per = pdGetPeripheral(PDD_PORT_A0);

	if( per->on )
	{
		if ( per->on & PDD_DGT_KU ) vz -= 0.2f;
		if ( per->on & PDD_DGT_KD ) vz += 0.2f;
		if ( per->on & PDD_DGT_KL ) vx -= 0.2f;
		if ( per->on & PDD_DGT_KR ) vx += 0.2f;
		if ( per->on & PDD_DGT_TY ) vy -= 0.2f;
		if ( per->on & PDD_DGT_TA ) vy += 0.2f;
		if ( per->on & PDD_DGT_TB ) pCurrentObject = object_F40_GTE_sh_null1_1_null1_1;
		if ( per->on & PDD_DGT_TX ) pCurrentObject = TEAPOT_OBJECT;
		if ( per->on & PDD_DGT_ST )
		{
			vx	= 0.0f;
			vy	= 0.0f;
			vz	= 20.0f;
		}
		kgSetView(&ViewMatrix, vx, vy, vz, 0.0f, 0.0f, 0.0f);
	}

	kmBeginScene(&SystemConfig);
	{
		kmSetBorderColor(Bordar1);

		kmBeginPass(&VertexBufferDesc);
		{
			txt_ClearScreen();		/* Clear text screen	*/
			txt_SetCursor(0,4);
			time1 = syTmrGetCount();

			kgInitMatrix(&ViewMatrix);

			kgRotateY((KMDWORD)frameCount*50);
			kgBasicDrawObject( &VertexBufferDesc, pCurrentObject );

			kgPushMatrix();

			kgRotateY((KMDWORD)frameCount*200);
			kgTranslate(8.0f, 0.0f, 0.0f);
			kgRotateZ((KMDWORD)frameCount*300);
			kgRotateY((KMDWORD)frameCount*200);
			kgRotateX((KMDWORD)frameCount*100);
			kgBasicDrawObject( &VertexBufferDesc, pCurrentObject );

			kgPopMatrix();

			kgRotateX((KMDWORD)frameCount*200);
			kgTranslate(0.0f, 8.0f, 0.0f);
			kgRotateY((KMDWORD)frameCount*200);
			kgBasicDrawObject( &VertexBufferDesc, pCurrentObject );

			time2 = syTmrGetCount();
			PRINTOUT(("CALC TIME = %d[us]", syTmrCountToMicro(syTmrDiffCount(time1, time2))));

			txt_DispScreen(&VertexBufferDesc);		/* Display screen */
		}kmEndPass(&VertexBufferDesc);
		kmRender(KM_RENDER_FLIP);

		kmSetBorderColor(Bordar2);

	}kmEndScene(&SystemConfig);

	frameCount++;
	return 1;
}
