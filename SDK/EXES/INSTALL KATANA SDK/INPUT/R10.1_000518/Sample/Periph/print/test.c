/*
    Ninja Sample

    COPYRIGHT (C) SEGA ENTERSRISES,LTD.

    Print Sample

    1999.4.21
*/

#include <shinobi.h>

Uint32 gFrameCount;

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
	njSetBackColor(0x00000000, 0x00000000, 0x000000FF);
}



Sint32 njUserMain(void)
{
	njPrintC(NJM_LOCATION(4,  2), "PRINT SAMPLE");
	njPrintH(NJM_LOCATION(20,  2), gFrameCount, 8);
	njPrintPeripheralInfo(NJM_LOCATION( 2,  4), NJD_PORT_A0);
	njPrintPeripheralInfo(NJM_LOCATION(22,  4), NJD_PORT_B0);
	njPrintPeripheralInfo(NJM_LOCATION( 2, 17), NJD_PORT_C0);
	njPrintPeripheralInfo(NJM_LOCATION(22, 17), NJD_PORT_D0);

	gFrameCount++;
	return NJD_USER_CONTINUE;
}

void njUserExit(void)
{
	sbExitSystem();
	syBtExit();
}

