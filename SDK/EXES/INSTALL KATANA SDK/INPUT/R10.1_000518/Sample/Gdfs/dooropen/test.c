/*
	Gdfs Sample
	
	COPYRIGHT (C) SEGA ENTERSRISES,LTD.
	
	open test
	
	1999.01.18
*/

#include <shinobi.h>


static Sint32 Abort;


void errfunc(void *obj, Sint32 err)
{
	/* if the tray was opened ? */
	if (err == GDD_ERR_TRAYOPEND || err == GDD_ERR_UNITATTENT) {
		/* set the abort flag */
		Abort = 1;
	}
}


/*** main routine ***/


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
    njSetBorderColor( 0x00000000 ) ;
    njInitVertexBuffer( 100000, 0, 100000, 0, 0);
    njInitPrint(NULL, 0, 0);
    njPrintSize(14);
	
	njSetBackColor(0x00000000,0x00000000,0x000000FF);
	
	/* clear the abort flag */
	Abort = 0;
	
	/* set an error callback */
	gdFsEntryErrFuncAll(errfunc, (void *) 0);
}



Sint32 njUserMain(void)
{
	Sint32 dstat;
	
	njPrintC(NJM_LOCATION(2,2), "GDFS OPEN TEST");
	
	/* check the drive status */
	dstat = gdFsGetDrvStat();
	if (dstat == GDD_DRVSTAT_OPEN || dstat == GDD_DRVSTAT_BUSY) {
		gdFsReqDrvStat();
	}
	
	/* if the abort flag is set */
	if (Abort) return NJD_USER_EXIT;
	
	return NJD_USER_CONTINUE;
}



void njUserExit(void)
{
	njExitPrint();
	sbExitSystem();
	syBtExit();
}

/* eof */
