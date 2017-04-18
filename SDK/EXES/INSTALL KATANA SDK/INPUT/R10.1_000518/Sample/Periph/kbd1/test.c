/*
    Keyboard Sample

    COPYRIGHT (C) SEGA ENTERSRISES,LTD.

    Low Level Keyboard Sample #1

    1999.5.27
*/

#include <shinobi.h>

#define KBD_PORT PDD_PORT_D0  /* キーボードポート Keyboard port  */

Sint32 gFrameCount;


/*===============================================================*/
/* アプリケーションの初期化                                      */
/* Initialize application.                                       */
/*===============================================================*/

void njUserInit(void)
{
	gFrameCount = 0;

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
    njSetBorderColor( 0x00000000 ) ;
    njInitVertexBuffer( 1000, 0, -1, 0, 0);
    njInitPrint(NULL, 0, 0);
    njPrintSize(14);
	njSetBackColor(0x00004040, 0x00004040, 0x00004040);

	/* キーボードライブラリ初期化  */
	/* Initialize keyboard library */
	pdKbdInit();
}


/*===============================================================*/
/* アプリケーションのメインループ                                */
/* Main loop of application.                                     */
/*===============================================================*/

Sint32 njUserMain(void)
{
	const PDS_KEYBOARD* kbd;

	njPrintC(NJM_LOCATION(2, 2), "KEYBOARD SAMPLE #1");
	njPrintH(NJM_LOCATION(30, 2), gFrameCount++, 8);

	/* キーボードデータ取得       */
	/* Get data from the keyboard */
	kbd = pdKbdGetData(PDD_PORT_D0);

	if (kbd) {
		njPrint(NJM_LOCATION(2, 4),
				"CONTROL=%02X LED=%02X", kbd->ctrl, kbd->led);
		njPrint(NJM_LOCATION(2, 5),
				"DATA=%02X %02X %02X %02X %02X %02X",
				kbd->key[0], kbd->key[1], kbd->key[2],
				kbd->key[3], kbd->key[4], kbd->key[5]);
		if (kbd->ctrl & PDD_KEY_CTRL_LGUI) {
			njPrintC(NJM_LOCATION(2, 8), "LEFT GUI");
		}
		if (kbd->ctrl & PDD_KEY_CTRL_LALT) {
			njPrintC(NJM_LOCATION(2, 9), "LEFT ALT");
		}
		if (kbd->ctrl & PDD_KEY_CTRL_LSHIFT) {
			njPrintC(NJM_LOCATION(2, 10), "LEFT SHIFT");
		}
		if (kbd->ctrl & PDD_KEY_CTRL_LCTRL) {
			njPrintC(NJM_LOCATION(2, 11), "LEFT CTRL");
		}
		if (kbd->ctrl & PDD_KEY_CTRL_RGUI) {
			njPrintC(NJM_LOCATION(14, 8), "RIGHT GUI");
		}
		if (kbd->ctrl & PDD_KEY_CTRL_RALT) {
			njPrintC(NJM_LOCATION(14, 9), "RIGHT ALT");
		}
		if (kbd->ctrl & PDD_KEY_CTRL_RSHIFT) {
			njPrintC(NJM_LOCATION(14, 10), "RIGHT SHIFT");
		}
		if (kbd->ctrl & PDD_KEY_CTRL_RCTRL) {
			njPrintC(NJM_LOCATION(14, 11), "RIGHT CTRL");
		}
	} else {
		njPrintC(NJM_LOCATION(2, 6), "CONNECT KEYBOARD TO PORT D");
	}

	return NJD_USER_CONTINUE;
}



/*===============================================================*/
/* アプリケーションの終了                                        */
/* Finalize application                                          */
/*===============================================================*/

void njUserExit(void)
{
	/* キーボードライブラリ終了  */
	/* Finalize keyboard library */
	pdKbdExit();

	sbExitSystem();
	syBtExit();
}


