/******************************************************************************
 *
 *	Author:		DjR
 *	Date:		1/10/2000
 *
 *	Purpose:	Test out simple functionality in the stack
 *
 *****************************************************************************/

#include <shinobi.h>
#include "sg_sysrt.h"
#include "netUtl.h"

static Uint32 gFrameCount;

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
	njInitVertexBuffer(10000, 0, 100000, 0, 0);
	njInitPrint(NULL, 0, 0);
	njPrintSize(12);
	njSetBackColor(0x00000000, 0x00000000, 0x000000a0);

    // NETWORK INITIALIZATION CODE
	NUDebugInit();
	NUInitTransport(NULL);
}


/*===============================================================*/
/* Main loop of application.                                     */
/*===============================================================*/

static NUSTATE	state;

Sint32 njUserMain(void)
{
	const PDS_PERIPHERAL* per;
	Uint32 controller;
	static int n;

	njPrintC(NJM_LOCATION(2, 2), "Simple Connection Test");
	njPrintH(NJM_LOCATION(30, 2), gFrameCount++, 8);
	njPrintC(NJM_LOCATION(2,6), "Press START to toggle connection");

	// Every place where application code delays, NetworkIdle should be called.
	state = NUPollTransport();

	switch (state)
	{
		case	NU_INIT:
			njPrintC(NJM_LOCATION(2,4),"STATE : Nothing going on");
			break;
		case	NU_CONNECTING:
			njPrintC(NJM_LOCATION(2,4),"STATE : Attempting to connect");
			break;
		case	NU_CONNECTED:
			njPrintC(NJM_LOCATION(2,4),"STATE : Ready to go TCP/IP!!!");
//			test_socket();
			break;
		case	NU_DISCONNECTING:
			njPrintC(NJM_LOCATION(2,4),"STATE : Disconnecting");
			break;
		case	NU_DISCONNECTED:
			njPrintC(NJM_LOCATION(2,4),"STATE : Disconnected (Goodbye)");
			break;
		case	NU_FAILED:
			njPrintC(NJM_LOCATION(2,4),"STATE : Something went wrong");
			break;

	}

	per = pdGetPeripheral(PDD_PORT_A0);

	if (per->press & NJD_DGT_ST)
	{
		if (state==NU_DISCONNECTED || state==NU_INIT)
			NUConnectTransport();

		if (state==NU_CONNECTED || state==NU_CONNECTING)
			NUDisconnectTransport();
	}

	NUDebugRefresh();

	gFrameCount++;
	return NJD_USER_CONTINUE;
}


/*===============================================================*/
/* Finalize application                                          */
/*===============================================================*/

void njUserExit(void)
{
	// Goodbye code
	NUKillTransport();

	sbExitSystem();
	syBtExit();
}