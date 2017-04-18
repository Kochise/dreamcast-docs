/*
Ninja Sample

  COPYRIGHT (C) SEGA ENTERSRISES,LTD.

	Draw2D Sample

	  1997.12.08
*/
#include <shinobi.h>
#include <sg_sycbl.h>

/* Includes needed for Browser */
#include "sg_dpldr.h"
#include "Nt_utl.h"

/* NetworkInfo Flash Value - Required check for Network Installation */
Sint32 rc;

NJS_PERIPHERAL *per;

void   njUserInit(void)
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
	njSetBorderColor(0x00000000);
    njSetBackColor(0x00000000,0x00000000,0x000000FF);
	njInitVertexBuffer(100000, 0, 100000, 0, 0);
	njInitPrint( NULL, 0, NJD_TEXFMT_ARGB_1555 );
	njPrintSize(14);

	/* Code required to launch the Browser */
	/* Get Flash Information */
	rc = ntInfIsNetworkInfo();
}

Sint32 njUserMain(void)
{
	per = (PDS_PERIPHERAL *) njGetPeripheral(NJD_PORT_A0);

    njPrintC(NJM_LOCATION(10,4),"Dream Passport2 Sample");

	if (rc==NTD_ERR_NOINFO)
	{
        njPrintC(NJM_LOCATION(10,13),"Please sign up with Dream Passport Ver 1.01 or higher.");
	}
	else
	{
        njPrintC(NJM_LOCATION(10,12),"Press A to launch browser.");
	}

    if(per->press & NJD_DGT_TA)
	{
        /* Code required to launch the Browser */
        if (rc==!NTD_ERR_NOINFO)
        {
            SwitchToPassport(); /* maigo.bin */
        }
	}

    return NJD_USER_CONTINUE;
}

void njUserExit(void)
{
	njExitPrint();
	sbExitSystem();
}