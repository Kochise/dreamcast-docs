/*
	Ninja Sample

	COPYRIGHT (C) SEGA ENTERSRISES,LTD.

	Visual Memory LCD Sample

	1999.5.31
*/

#include <shinobi.h>

extern const Uint8 cgdata[];

/*===============================================================*/
/* アプリケーションの初期化                                      */
/* Initialize application.                                       */
/*===============================================================*/

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
    njInitVertexBuffer( 100000, 0, -1, 0, 0);
    njInitPrint(NULL, 0, 0);
    njPrintSize(12);
	njSetBackColor(0x00000000, 0x00000000, 0x0000a0a0);
}


Uint32 count = 0;

/*===============================================================*/
/* 画面への表示                                                  */
/* Display LCD image to screen.                                  */
/*===============================================================*/

void DrawLcdImageToScreen(Sint32 x, Sint32 y, const Uint8* data)
{
	Sint32 i, j;

	for (i = 0; i < 32; i++) {
		for (j = 0; j < 48; j++, data++) {
			if (*data & 0x08) {
				njPrintC(NJM_LOCATION(x + j, y + i), "O");
			} else {
				njPrintC(NJM_LOCATION(x + j, y + i), " ");
			}
		}
	}
}


/*===============================================================*/
/* 液晶への表示                                                  */
/* Display LCD.                                                  */
/*===============================================================*/

void DrawLcd(void)
{
	const NJS_PERIPHERAL* per;
	static Sint32 ofs = 0;
	Sint32 ret;
	Uint32 dir, flag;

	per = njGetPeripheral(NJD_PORT_A0);

	if (per->on & NJD_DGT_KU) ofs -= 48;
	if (per->on & NJD_DGT_KD) ofs += 48;

	if (ofs < 0) ofs = 0;
	if (ofs > 48 * (256 - 32)) ofs = 48 * (256 - 32);

	/* 液晶の向きを調べる        */
	/* Get the direction of LCD. */
	dir = pdLcdGetDirection(PDD_PORT_A1);

	switch (dir) {
		case PDD_LCD_DIRECTION_NORMAL:
			njPrintC(NJM_LOCATION(34, 46), "DIRECTION:NORMAL");
			flag = PDD_LCD_FLAG_NOFLIP;
			break;
		case PDD_LCD_DIRECTION_FLIP:
			njPrintC(NJM_LOCATION(34, 46), "DIRECTION:FLIP");
			flag = PDD_LCD_FLAG_HVFLIP;
			break;
		case PDD_LCD_DIRECTION_LEFT:
			njPrintC(NJM_LOCATION(34, 46), "DIRECTION:LEFT");
			flag = PDD_LCD_FLAG_NOFLIP;
			break;
		case PDD_LCD_DIRECTION_RIGHT:
			njPrintC(NJM_LOCATION(34, 46), "DIRECTION:RIGHT");
			flag = PDD_LCD_FLAG_NOFLIP;
			break;
	}

	/* 液晶にデータを送る        */
	/* Send data to LCD.         */
	ret = pdVmsLcdWrite(PDD_PORT_A1, &cgdata[ofs], flag);

	if (ret == PDD_LCDERR_OK) {
		DrawLcdImageToScreen(2, 8, &cgdata[ofs]);
	} else {
		njPrintC(NJM_LOCATION(30, 22), "LCD ERROR");
	}
}


/*===============================================================*/
/* アプリケーションのメインループ                                */
/* Main loop of application.                                     */
/*===============================================================*/

Sint32 njUserMain(void)
{
	const PDS_PERIPHERALINFO* info;
	const NJS_PERIPHERAL* per;

	njPrintC(NJM_LOCATION(10, 4), "VISUAL MEMORY LCD SAMPLE #0");

	per = njGetPeripheral(NJD_PORT_A0);

	/* 液晶が接続されているかどうか調べる */
	/* Is Visual Memory LCD connected ?   */
	if (!pdVmsLcdIsReady(PDD_PORT_A1)) {
		if (count & 0x00000010) {
			njPrintC(NJM_LOCATION(18, 50),
				"PLEASE CONNECT VISUAL MEMORY TO PORT A-1.");
		}
	} else {
		njPrintC(NJM_LOCATION(21, 50),
				"PRESS UP-DOWN KEY TO MOVE LCD GRAPHIC.");

		DrawLcd();
	}

	count++;
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

