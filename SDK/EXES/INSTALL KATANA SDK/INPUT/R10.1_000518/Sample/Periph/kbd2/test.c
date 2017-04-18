/*
    Ninja Sample

    COPYRIGHT (C) SEGA ENTERSRISES,LTD.

    Keyboard Sample #2

    1999.5.27
*/

#include <shinobi.h>
#include <nindows.h>

#include "keyboard.h"
#include "dbgcons.h"


#define TEXT_W   36           /* コンソールの横幅 Console width  */
#define TEXT_H   16           /* コンソールの行数 Console height */
#define KBD_PORT PDD_PORT_D0  /* キーボードポート Keyboard port  */

/*-------------------------------------------------------------------------*/
Uint32 gFrameCount;
HKBD hKbd;
char TextBuf[TEXT_W * TEXT_H];

void DispKeyboardInfo(Sint32 x, Sint32 y, Uint32 port, Uint16 data);

/*===============================================================*/
/* 各種文字列の定義                                              */
/* Character strings.                                            */
/*===============================================================*/

const char* PortName[] = {
	"A", "A-1", "A-2", "A-3", "A-4", "A-5",
	"B", "B-1", "B-2", "B-3", "B-4", "B-5",
	"C", "C-1", "C-2", "C-3", "C-4", "C-5",
	"D", "D-1", "D-2", "D-3", "D-4", "D-5",
};

const char* LangName[] = {
	"---", "JPN", "US ", "UK ", "GER", "FRA", "ITA",
	"SPA", "SWE", "SWI", "NET", "POR", "LTN", "CAN",
	"RUS", "CHI", "KOR",
};

const char* TypeName[] = {
	"---", " 89", " 92", "101", "102", "104", "105", "106",
	"109", " 87", " 88",
};


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
    njInitVertexBuffer( 10000, 0, -1, 0, 0);
    njInitPrint(NULL, 0, 0);
    njPrintSize(14);
	njSetBackColor(0x00004040, 0x00004040, 0x00004040);

	KbdInit();
	hKbd = KbdCreate(KBD_PORT);

	njSetVSyncFunction(KbdServer);

	ConInit(2, 10, TEXT_W, TEXT_H, TextBuf);
}



/*===============================================================*/
/* アプリケーションのメインループ                                */
/* Main loop of application.                                     */
/*===============================================================*/

static Uint16 orgdata = 0;

Sint32 njUserMain(void)
{
	Uint16 data;
	Sint32 x, y;

	njPrintC(NJM_LOCATION(2, 2), "KEYBOARD SAMPLE #2");
	njPrintH(NJM_LOCATION(30, 2), gFrameCount++, 8);

	if (KbdIsHit(hKbd)) {
		ConGetPos(&x, &y);

		orgdata = KbdGetChar(hKbd);
		data = orgdata & 0xff;

		/* Ctrl+Alt+Del */
		if ((orgdata & (KC_CTRL | KC_ALT)) == (KC_CTRL | KC_ALT)) {
			if (data == 0x7f) {
				return NJD_USER_EXIT;
			}
		}

		if (data < 0x7f) {
			switch (data) {
				case 0x1c:	/* Left */
					ConLocate(x - 1, y);
					break;
				case 0x1d:	/* Right */
					ConLocate(x + 1, y);
					break;
				case 0x1e:	/* Up */
					ConLocate(x, y - 1);
					break;
				case 0x1f:	/* Down */
					ConLocate(x, y + 1);
					break;
				case 0x1b:	/* ESC */
					ConCls();
					break;
				default:
					ConPrintf("%c", data);
					break;
			}
		}
	}

	gFrameCount++;

	ConDispCursor();
	ConMain();

	DispKeyboardInfo(4, 5, KBD_PORT, orgdata);

	return NJD_USER_CONTINUE;
}


/*===============================================================*/
/* アプリケーションの終了                                        */
/* Finalize application                                          */
/*===============================================================*/

void njUserExit(void)
{
	ConExit();
	KbdExit();
	sbExitSystem();
	syBtExit();
}



/*===============================================================*/
/* キーボード情報を表示                                          */
/* Display information of the keyboard                           */
/*===============================================================*/

void DispKeyboardInfo(Sint32 x, Sint32 y, Uint32 port, Uint16 data)
{
	const PDS_KEYBOARD* kbd;
	Uint8* dt;

	kbd = pdKbdGetData(port);

	if (kbd != NULL) {
		dt = kbd->key;
		njPrint(NJM_LOCATION(x, y), "PORT:%s", PortName[port]);
		njPrint(NJM_LOCATION(x + 2, y + 1),
					"RAW DATA=%02X/%02X %02X %02X %02X %02X %02X",
					kbd->ctrl, dt[0], dt[1], dt[2], dt[3], dt[4], dt[5]);
		njPrint(NJM_LOCATION(x + 2, y + 2), "KEY CODE=%04X", data);
		if (kbd->info->lang <= PDD_KBDLANG_KOREA) {
			njPrint(NJM_LOCATION(x + 2, y + 3),
					"LANGUAGE=%s", LangName[kbd->info->lang]);
		}
		if (kbd->info->type <= PDD_KBDTYPE_88) {
			njPrint(NJM_LOCATION(x + 16, y + 3),
					"TYPE=%s KEYS", TypeName[kbd->info->type]);
		}
	} else {
		njPrint(NJM_LOCATION(x, y),
					"CONNECT A KEYBOARD TO PORT %s", PortName[port]);
	}
}


