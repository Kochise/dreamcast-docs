/*
    Ninja Sample

    COPYRIGHT (C) SEGA ENTERSRISES,LTD.

    Start Sample

    1999.4.20
*/

#include <shinobi.h>

/* GD:Maximum file number opening at the same time */
#define FILES 8

/* GD:Current directory buffer */
#define BUFFERS 1024


/* GD:Work area for GD filesystem */
extern Uint8 gdfswork;
extern Uint8 gdfscurdir;


/* Ninja:Texture memory list */
NJS_TEXMEMLIST tlist[10];


static void InitGD(void);
static void InitApplication(void);
extern void DispLoadingMessage(Sint32 x, Sint32 y);

void njUserInit(void)
{
    /* Check the cable for NTSC/PAL or VGA.. works properly for SCART. */
    switch (syCblCheck())
	{
        /* Initialize the display device and set the frame buffer based on the video mode. */
        case SYE_CBL_NTSC:  /* U.S./North America NTSC (60Hz) and Brazil PAL-M (60Hz). */
            sbInitSystem (NJD_RESOLUTION_640x480_NTSCNI, NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        case SYE_CBL_PAL:   /* Europe PAL (50Hz) and Argentina PAL-N (50Hz). */
            sbInitSystem (NJD_RESOLUTION_640x544_PALNI, NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        case SYE_CBL_VGA:   /* Standard VGA. */
            sbInitSystem (NJD_RESOLUTION_VGA, NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        default:
            syBtExit();     /* Unknown video type, return to Dreamcast BootROM. */
	}
	njSetBorderColor(0);
	njInitVertexBuffer(100000, 0, -1, 0, 0);
	njInitPrint(NULL, 0, 0);
	njPrintSize(16);
	njSetBackColor(0x00000000, 0x00000000, 0x00000000);
	njInitTexture(tlist, 10);

	/* Display the NOW LOADING message. */
	DispLoadingMessage(32, 400);

	/* Initialize GD filesystem. */
	InitGD();

	/* Initialize application */
	InitApplication();
}

static void InitGD(void)
{
	Uint8* wk;
	Uint8* dir;
	Sint32 err;
	Sint32 i;

	wk  = (Uint8*)(((Uint32)gdfswork & 0xffffffe0) + 0x20);
	dir = (Uint8*)(((Uint32)gdfscurdir & 0xffffffe0) + 0x20);

	for (i = 8; i > 0; i--) {
		err = gdFsInit(FILES, wk, BUFFERS, dir);

		if (err == GDD_ERR_TRAYOPEND ||
			err == GDD_ERR_UNITATTENT) {
			sbExitSystem();
			syBtExit();
		} else if (err == GDD_ERR_OK) {
			break;
		}
	}

	if (i == 0) {
		sbExitSystem();
		syBtExit();
	}
}

static void InitApplication(void)
{
#if 0
	/* 比較的長時間かかる初期化処理（初期テクスチャのロード等）*/
	/* は、ここで行ってください。                              */
#else
	/* このサンプルではメッセージの表示結果を確認するために    */
	/* ここで無限ループとします。                              */
	while (1)
		;
#endif
}


Sint32 njUserMain(void)
{
	njPrint(NJM_LOCATION(4, 4), "COMPLETED!");

	return NJD_USER_CONTINUE;
}

void njUserExit(void)
{
	sbExitSystem();
	syBtExit();
}

