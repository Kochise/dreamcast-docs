/*
    Ninja Sample

    COPYRIGHT (C) SEGA ENTERSRISES,LTD.

    Peripheral Sample

    1999.1.28
*/

#include <shinobi.h>

Uint32 gFrameCount;
Sint32 index;

void DisplayPeripheralInfo(Sint32 x, Sint32 y, Uint32 port);

/*===============================================================*/
/* ポート番号を格納した配列                                      */
/* Array of control port number.                                 */
/*===============================================================*/

const Sint32 PortNo[] = {
	PDD_PORT_A0, PDD_PORT_A1, PDD_PORT_A2,
	PDD_PORT_B0, PDD_PORT_B1, PDD_PORT_B2,
	PDD_PORT_C0, PDD_PORT_C1, PDD_PORT_C2,
	PDD_PORT_D0, PDD_PORT_D1, PDD_PORT_D2,
};


/*===============================================================*/
/* 各種文字列の定義                                              */
/* Character strings.                                            */
/*===============================================================*/

const char* PortName[] = {
	"A-0", "A-1", "A-2",
	"B-0", "B-1", "B-2",
	"C-0", "C-1", "C-2",
	"D-0", "D-1", "D-2",
};

const char* TypeName[] = {
	"CONTROLLER", "STORAGE", "LCD", "TIMER",
	"SOUNDINPUT", "?", "KEYBOARD", "LIGHT-GUN",
	"VIBRATION", "?", "?", "?",
	"?", "?", "?", "?",
};

const char* AreaName[] = {
	"USA", "JAPAN", "ASIA", "EUROPE",
	"RSVD1", "RSVD2", "RSVD3", "RSVD4",
};

const char* DirName[] = {
	"TOP", "BOTTOM", "LEFT", "RIGHT",
};


/*===============================================================*/
/* アプリケーションの初期化                                      */
/* Initialize application.                                       */
/*===============================================================*/

void njUserInit(void)
{
	gFrameCount = 0;
	index = 0;

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
	const PDS_PERIPHERALINFO* info;
	const PDS_PERIPHERAL* per;

	njPrintC(NJM_LOCATION(2, 2), "PERIPHERAL SAMPLE #1");
	njPrintH(NJM_LOCATION(30, 2), gFrameCount++, 8);

	per = pdGetPeripheral(PDD_PORT_A0);

	/* コントローラが接続されているかどうかの判別 */
	/* Is controller connected to port-A ?        */
	if (!(per->info->type & PDD_DEVTYPE_CONTROLLER)) {
		if (gFrameCount & 0x00000020) {
			njPrintC(NJM_LOCATION(1, 26),
				"PLEASE CONNECT A CONTROLLER TO PORT A.");
		}
	} else {
		njPrintC(NJM_LOCATION(1, 26),
				"PRESS <- -> KEY TO SELECT PERIPHERAL.");
	}

	if (per->press & NJD_DGT_KR) index++;
	if (per->press & NJD_DGT_KL) index--;
	if (index < 0) index = 11;
	if (index > 11) index = 0;

	DisplayPeripheralInfo(1, 4, PortNo[index]);

	switch (PortNo[index]) {
		case NJD_PORT_A0:
		case NJD_PORT_B0:
		case NJD_PORT_C0:
		case NJD_PORT_D0:
			njPrintPeripheralInfo(NJM_LOCATION(1, 13), PortNo[index]);
			break;
		default:
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
}



/*===============================================================*/
/* ペリフェラルの固有情報を表示                                  */
/* Display information of peripheral.                            */
/*===============================================================*/

void DisplayPeripheralInfo(Sint32 x, Sint32 y, Uint32 port)
{
	Sint32 i, bit, xx;
	const PDS_PERIPHERALINFO* info;

	info = pdGetPeripheralInfo(port);

	njPrint(NJM_LOCATION(x, y++), "PORT NO.:%s",      PortName[index]);
	njPrint(NJM_LOCATION(x, y),   "TYPE    :[%08X]",  info->type);

	xx = x + 20;
	for (i = 0, bit = 1; i < 16; i++, bit <<= 1) {
		if (info->type & bit) {
			njPrint(NJM_LOCATION(xx, y), "%s", TypeName[i]);
			xx += strlen(TypeName[i]) + 1;
		}
	}
	y++;
	njPrint(NJM_LOCATION(x, y++), "NAME    :%s",      info->product_name);
	njPrint(NJM_LOCATION(x, y++), "LICENSE :%s",      info->license);
	njPrint(NJM_LOCATION(x, y),   "AREA    :[%02X]",  info->area_code);

	xx = x + 15;
	for (i = 0, bit = 1; i < 4; i++, bit <<= 1) {
		if (info->area_code & bit) {
			njPrint(NJM_LOCATION(xx, y), "%s", AreaName[i]);
			xx += strlen(AreaName[i]) + 1;
		}
	}

	y++;
	njPrint(NJM_LOCATION(x, y), "CONNECT :[%d %d]", info->connector_dir[0],
                                                    info->connector_dir[1]);
	njPrint(NJM_LOCATION(x + 15, y++), "%s %s",
					DirName[info->connector_dir[0]],
					DirName[info->connector_dir[1]]);

	njPrint(NJM_LOCATION(x, y++), "STANDBY :%dmA", info->stdby_pow / 10);
	njPrint(NJM_LOCATION(x, y++), "MAX POW :%dmA", info->max_pow / 10);
}

