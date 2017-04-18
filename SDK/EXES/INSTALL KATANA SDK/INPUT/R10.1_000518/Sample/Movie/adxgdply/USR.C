
/*	Definition of Kamui Wait V-Sync Mode		*/
#define		USR_KAMUI_NOWAITVSYNC			//	Not wait V-Sync

/***
*			Include Files
***/

#include	<shinobi.h>
#include	<stdarg.h>
#include	<string.h>

#include	"usr.h"

#define		_STRICT_UNION_		/* for kamui2.h */
#include	"kamui2.h"			/* for Kamui2 Call */
#include	"sg_chain.h"			/* for Kamui2 Call */
#include	"dispstr.h"


/* Audio driver to use, select one */
//#define USE_MANATEE		// Uncomment to use the Manatee2 driver
//#define USE_AUDIO64AC		// Uncomment to use the Audio64 driver, AC layer
#define USE_AUDIO64AM		// Uncomment to use the Audio64 driver, AM layer

//#define USE_MIDIDA		// Uncomment to use the MidiDA driver (default is Audio64.drv)

/***
*			Video Functions
***/

///////////////////  Kamui2  ///////////////////

#define	USR_INT_PRI			(0x90)
#define	VERTEXBUFFERSIZE	(0x100000*2)	/* 2MB	*/

SYCHAIN				usrg_chid = (SYCHAIN)NULL;
KMSURFACEDESC		PrimarySurfaceDesc;		/* Primary frame buffer			*/
KMSURFACEDESC		BackSurfaceDesc;		/* Back-buffer frame buffer		*/
KMVERTEXBUFFDESC	VertexBufferDesc;		/* Vertex-buffer				*/

KMSTRIPCONTEXT		StripContext;
KMSTRIPHEAD			StripHead;

PKMSURFACEDESC		pFB[2];
KMDWORD				FBarea[24576 + 19456];
								/* FBstruct 4096 Entry (= 4096 * 24 / 4) *
								 * VQstruct 1024 Entry (= 1024 * 76 / 4) */
KMSYSTEMCONFIGSTRUCT	SystemConfig;
PKMDWORD				dwDataPtr;

KMINT32				UsrRenderId[2];

/*	Initialize Video library and set display mode	*/
void *UsrInitVideo(Sint32 *mode, Sint32 *frame, Sint32 *count, Sint32 *latency)
{
	KMPACKEDARGB BorderColor;

    /* Check the cable for NTSC/PAL or VGA.. works properly for SCART. */
    switch (syCblCheck())
	{
        /* Initialize the display device and set the frame buffer based on the video mode. */
        case SYE_CBL_NTSC:  /* U.S./North America NTSC (60Hz) and Brazil PAL-M (60Hz). */
            *mode = KM_DSPMODE_NTSCNI640x480;
            break;
        case SYE_CBL_PAL:   /* Europe PAL (50Hz) and Argentina PAL-N (50Hz). */
            *mode = KM_DSPMODE_PALNI640x480;
            break;
        case SYE_CBL_VGA:   /* Standard VGA. */
            *mode = KM_DSPMODE_VGA;
            break;
        default:
            syBtExit();     /* Unknown video type, return to Dreamcast BootROM. */
	}

	*frame = KM_DSPBPP_RGB888;
	*count = 1;
	*latency = 2;
	sbInitSystem(*mode, *frame, *count);
	/*----------------------------------------------------------------- */
	/* Create frame buffer and vertex buffer */
	pFB[0] = &PrimarySurfaceDesc;
	pFB[1] = &BackSurfaceDesc;
	/* VertexBufferPointer(set5) */
	dwDataPtr =	(PKMDWORD)(
		((KMDWORD)syMalloc(VERTEXBUFFERSIZE) & 0x0FFFFFFFUL) | 0xA0000000 );
	SystemConfig.dwSize				 = sizeof(KMSYSTEMCONFIGSTRUCT);
	SystemConfig.flags				 = KM_CONFIGFLAG_ENABLE_CLEAR_FRAMEBUFFER
									 | KM_CONFIGFLAG_NOWAIT_FINISH_TEXTUREDMA
#ifdef USR_KAMUI_NOWAITVSYNC
									 | KM_CONFIGFLAG_NOWAITVSYNC
#endif
									 | KM_CONFIGFLAG_ENABLE_2V_LATENCY;
	/* for Frame buffer */
	SystemConfig.ppSurfaceDescArray	 = pFB;
	SystemConfig.fb.nNumOfFrameBuffer= 2;
	/* for Texture Memory */
	SystemConfig.nTextureMemorySize	 = 0x100000*4;
	SystemConfig.nNumOfTextureStruct = 4096;
	SystemConfig.nNumOfSmallVQStruct = 1024;
	SystemConfig.pTextureWork		 = &FBarea[0];
	/* for Vertex buffer */
	SystemConfig.pBufferDesc		 = &VertexBufferDesc;
	SystemConfig.nNumOfVertexBank	 = 2;
	SystemConfig.pVertexBuffer		 = dwDataPtr;
	SystemConfig.nVertexBufferSize	 = VERTEXBUFFERSIZE;
	SystemConfig.nPassDepth			 = 1;
	SystemConfig.Pass[0].dwRegionArrayFlag = KM_PASSINFO_AUTOSORT;
	SystemConfig.Pass[0].nDirectTransferList = KM_OPAQUE_POLYGON;
	SystemConfig.Pass[0].fBufferSize[0] =   0.0f;	/* Opaque : 80% */
	SystemConfig.Pass[0].fBufferSize[1] =   0.0f;
	SystemConfig.Pass[0].fBufferSize[2] =  100.0f;	/* Translucent : 20% */
	SystemConfig.Pass[0].fBufferSize[3] =   0.0f;
	SystemConfig.Pass[0].fBufferSize[4] =   0.0f;

	kmSetSystemConfiguration( &SystemConfig );

	/* Initialize Strip context */
	StripContext.nSize = sizeof(KMSTRIPCONTEXT);
	kmInitStripContext(KM_STRIPCONTEXT_SYS_GOURAUD|KM_OPAQUE_POLYGON,
															&StripContext);

	/* Generate Strip Head */
	kmGenerateStripHead03(&StripHead, &StripContext);
	
	BorderColor.dwPacked = 0;
	kmSetBorderColor(BorderColor);
	txt_InitDisplayString();

//	mwMngConfigUsingKmWaitVsyncCb(FALSE);

	return (void *)&VertexBufferDesc;
}

/*	Finalize Video library and SHINOBI	*/
void UsrFinishVideo(void)
{
	sbExitSystem();
}

/*	Set V-sync interrupt callback function	*/
void UsrSetVsyncFunc(void (*func)(void))
{
	if (usrg_chid != (SYCHAIN)NULL) {
		syChainDeleteHandler(usrg_chid);
	}
	usrg_chid = syChainAddHandler(
		(SY_CHAIN_EVENT) SYD_CHAIN_EVENT_IML6_VBLANK,
		(void *)func, (Uint32)USR_INT_PRI, (void *)NULL);
}

/*	Print string for debug	*/
Sint32 UsrPrintf(Sint32 lx, Sint32 ly, char *fmt,...)
{
    va_list args;
    static char buf[256];
    Sint32 ret=0, pos;

	memset(buf, 0, sizeof(buf));
    va_start(args, fmt);
    ret = vsprintf(buf, fmt, args);
    va_end(args);
	txt_SetCursor(lx, ly+1);
	txt_DispString(buf);

    return ret;
}

/*	Start Drawing	*/
void UsrBeginDraw(void)
{
	kmBeginScene(&SystemConfig);			/* シーンの開始 */
	kmBeginPass(&VertexBufferDesc);			/* パスの開始 */
	pdExecPeripheralServer();
	txt_ClearScreen();
}

/*	End Drawing	*/
void UsrEndDraw(void)
{
	txt_DispScreen(&VertexBufferDesc);
	kmEndPass(&VertexBufferDesc);			/* パスの終了 */
	UsrRenderId[1] = UsrRenderId[0];
	UsrRenderId[0] = 
		kmRender(KM_RENDER_FLIP);			/* レンダリング */
	kmEndScene(&SystemConfig);				/* シーンの終了 */
}

/*	Wait V-Blank	*/
void UsrWaitVBlank(void)
{
#ifdef USR_KAMUI_NOWAITVSYNC
	KMSTATUS	stat;

	for (;;) {
		stat = kmGetRenderStatus(UsrRenderId[1]);
		if (stat == KMSTATUS_UNDER_RENDER) {
			kmWaitVBlank();
		} else {
			return;
		}
	}
#endif
}

/* Code for Manatee2 driver.  See README.TXT for details */
#ifdef USE_MANATEE
///////////////////  Mantee  ///////////////////
#include <sg_sd.h>

/*	Initialize sound library and load sound driver	*/
void UsrInitSound(void)
{
	SDMEMBLK	memblk = NULL;
	void *snddrv;

	snddrv = UsrLoadFile("manatee.drv", NULL);
	/*	Initialize Sound library	 */
	sdLibInit(NULL, 0, 0);		/*	This api's argument is dummy now.  */
	/* 	Download and Initialize Sound driver.	 */
	/*	Create Memory block handle  */
	sdMemBlkCreate(&memblk);
	/*  Setting Memoby block handle  */
	sdMemBlkSetPrm(memblk, snddrv, 0, SDD_MEMBLK_SYNC_FUNC, NULL);
	/*	Initialize Sound driver  */
	sdDrvInit(memblk);
	sdMemBlkDestroy(memblk);
	syFree(snddrv);
	/*	Set transfer mode to DMA  	*/
	sdMemBlkSetTransferMode(SDE_MEMBLK_TRANSFER_MODE_DMA);
}

/*	Finalize sound system				*/
void UsrFinishSound(void)
{
//	sdSysFinish();
}
#endif

/* Code for Audio64 AC layer.  See README.TXT for details */
#ifdef USE_AUDIO64AC

///////////////////  Audio64 (AC level)  ///////////////////

#include <ac.h>
#include <a64thunk.h>

#include "bpacsetup.h"

/*	Initialize sound library and load sound driver	*/
void UsrInitSound(void)
{
#define	MW_MAX_CH		(8)
#define	MW_SNDRAM_SIZE	(0x4040*MW_MAX_CH)

	KTU32		port[8], i;
	volatile KTU32	*sndram=KTNULL;
#ifdef USE_MIDIDA
	if ( bpAcSetup(AC_DRIVER_MIDI, KTFALSE, KTNULL)==KTFALSE )
#else
	if ( bpAcSetup(AC_DRIVER_DA, KTFALSE, KTNULL)==KTFALSE )
#endif
		for (;;);
	// The Middleware libraries require ports and memory in order to operate.
	// You can use any contiguous block of AICA (sound) RAM and any ports you want.
	// The memory (of size MW_SNDRAM_SIZE) and the ports are returned to you when the
	// Middleware library is properly shut down.
	// This example uses the first free available memory slot and the first eight ports.
	sndram = acSystemGetFirstFreeSoundMemory();
	for (i = 0; i < MW_MAX_CH; i++)
		port[i] = i;	// Define the port numbers
	mwSetupAudio64(sndram, MW_SNDRAM_SIZE, port, MW_MAX_CH);	// Pass the information to Middleware
	acSetTransferMode(AC_TRANSFER_DMA);
}

/*	Finalize sound system				*/
void UsrFinishSound(void)
{
}
#endif

/* Code for Audio64 AM layer.  See README.TXT for details */
#ifdef USE_AUDIO64AM

///////////////////  Audio64 (AM level)  ///////////////////

#include <ac.h>
#include <a64thunk.h>
#include <am.h>

#include "bpamsetup.h"

#define	MW_MAX_CH		(8)
#define	MW_SNDRAM_SIZE	(0x4040*MW_MAX_CH)

/*	Initialize sound library and load sound driver	*/
void UsrInitSound(void)
{
	KTBOOL ret;
	AM_SOUND	amsnd[8];
	KTU32		port[8], i;
	volatile KTU32	*sndram=KTNULL;

#ifdef USE_MIDIDA
	if ( bpAmSetup(AC_DRIVER_MIDI, KTFALSE, KTNULL)==KTFALSE )
#else
	if ( bpAmSetup(AC_DRIVER_DA, KTFALSE, KTNULL)==KTFALSE )
#endif
		for (;;);
	// As above in the AC layer, the Middleware library requires a block of sound RAM and
	// ports.  However, some AM level commands are used to accomplish this.
	for (i=0; i<MW_MAX_CH; i++) {
		ret = amSoundAllocateVoiceChannel(&amsnd[i]);
		if (ret == KTFALSE) {
			for (;;);
		}
		port[i] = amsnd[i].voiceChannel;
	}
	ret = amHeapAlloc(&sndram, MW_SNDRAM_SIZE, 32, AM_FIXED_MEMORY, NULL);
	if (ret == KTFALSE) {
		for (;;);
	}
	mwSetupAudio64(sndram, MW_SNDRAM_SIZE, port, MW_MAX_CH);
	acSetTransferMode(AC_TRANSFER_DMA);
}

/*	Finalize sound system		*/
void UsrFinishSound(void)
{
}
#endif

/***
*			Utility functions
***/

/*	Check Door Status	*/
void UsrCheckDoorOpen(void){
	Sint32 dstat;

	/*	ドアオープンチェック	*/
	/*	Check door open			*/
	dstat = gdFsGetDrvStat();
	if (dstat == GDD_DRVSTAT_OPEN || dstat == GDD_DRVSTAT_BUSY) {
		gdFsReqDrvStat();
	}
}

/*	Load data to memory	*/
void *UsrLoadFile(char *fname, Sint32 *len)
{
	GDFS gdfs;
	Sint32 fsize, nsct;
	void *dat=NULL;

	if ( (gdfs=gdFsOpen(fname, NULL)) == NULL ) {
		for (;;) {
			UsrBeginDraw();
			UsrPrintf(3, 5, "can't open %s", fname);
			UsrEndDraw();
		}
	}
	gdFsGetFileSize(gdfs, &fsize);
	nsct = (fsize+2047)/2048;
	if ( (dat=syMalloc(nsct*2048)) != NULL ) {
		gdFsRead(gdfs, nsct, dat);
	}
	gdFsClose(gdfs);
	if ( len != NULL )
		*len = fsize;

	return dat;
}

/*	Convert from sampling frequency and counter to time(hour,min,sec,frame)	*/
void UsrSfcnt2time(Sint32 sf, Sint32 ncnt, Sint32 *hh, Sint32 *mm, Sint32 *ss, Sint32 *ff)
{
	register Sint32 nf = (Sint32)((Float)ncnt/(Float)sf*100.0);

	*hh = nf/(60*60*100);
	*mm = nf/(60*100) - *hh*60;
	*ss = nf/100 - *hh*60*60 - *mm*60;
	*ff = nf%100;
}
