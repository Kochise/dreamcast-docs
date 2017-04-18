/*
    Ninja Sample

    COPYRIGHT (C) SEGA ENTERSRISES,LTD.

    Peripheral Sample

    1999.1.28
*/

#include <shinobi.h>
#include "perchk.h"

Uint32 gFrameCount;

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
    njInitVertexBuffer( 10000, 0, 100000, 0, 0);
    njInitPrint(NULL, 0, 0);
    njPrintSize(14);
	njSetBackColor(0x00000000, 0x00000000, 0x0000a000);
}



/*===============================================================*/
/* アプリケーションのメインループ                                */
/* Main loop of application.                                     */
/*===============================================================*/

Sint32 njUserMain(void)
{
	const PDS_PERIPHERAL* per;
	Uint32 controller;

	njPrintC(NJM_LOCATION(2, 2), "PERIPHERAL SAMPLE #2");
	njPrintH(NJM_LOCATION(30, 2), gFrameCount++, 8);

	njPrintPeripheralInfo(NJM_LOCATION(4, 14), PDD_PORT_A0);

	controller = CheckController(PDD_PORT_A0);

	switch (controller) {
		case PER_NONE:
			njPrintC(NJM_LOCATION(10, 10), "---------");
			break;
		case PER_CONTROLLER:
		default:
			njPrintC(NJM_LOCATION(10, 10), "CONTROLLER");
			break;
		case PER_STICK:
			njPrintC(NJM_LOCATION(10, 10), "ARCADE STICK");
			break;
		case PER_RACING:
			njPrintC(NJM_LOCATION(10, 10), "RACING CONTROLLER");
			break;
		case PER_GUN:
			njPrintC(NJM_LOCATION(10, 10), "GUN CONTROLLER");
			break;
		case PER_KEYBOARD:
			njPrintC(NJM_LOCATION(10, 10), "KEYBOARD");
			break;
		case PER_FISHING:
			njPrintC(NJM_LOCATION(10, 10), "FISHING CONTROLLER");
			break;
	}

	gFrameCount++;
	return NJD_USER_CONTINUE;
}


/*===============================================================*/
/* アプリケーションの終了                                        */
/* Finalize application                                          */
/*===============================================================*/

void njUserExit(void)
{
	sbExitSystem();
	syBtExit();
}



