/*
    Ninja Sample

    COPYRIGHT (C) SEGA ENTERSRISES,LTD.

    Gun Sample #1

    1999.5.31
*/

#include <shinobi.h>
#include "gun.h"

void DrawTarget(Sint32 x, Sint32 y, Sint32 gunno);
void DrawRect(Sint32 x, Sint32 y, Sint32 w, Sint32 h, Uint32 color);
void DispGunInfo(Sint32 x, Sint32 y, Sint32 player);

Uint32 gFrameCount;
Uint32 gTvMode;

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
    njPrintSize(14);
	njSetBackColor(0x0000c0c0, 0x0000c0c0, 0x000000c0);
	njPrintColor(0xffffffff);

	gFrameCount = 0;

	GunInit(gTvMode);
}



/*===============================================================*/
/* アプリケーションのメインループ                                */
/* Main loop of application.                                     */
/*===============================================================*/

Sint32 njUserMain(void)
{
	GUNINFO* info;

	njPrintC(NJM_LOCATION(4,  2), "LIGHT GUN SAMPLE #1");
	njPrintC(NJM_LOCATION(4,  3), "   -SINGLE SHOT-");
	njPrintH(NJM_LOCATION(30,  2), gFrameCount++, 8);

	GunMain();

	DispGunInfo( 1, 6, GUN_A);
	DispGunInfo(21, 6, GUN_B);

	return NJD_USER_CONTINUE;
}


/*===============================================================*/
/* アプリケーションの終了                                        */
/* Finalize application                                          */
/*===============================================================*/

void njUserExit(void)
{
	GunExit();
	sbExitSystem();
	syBtExit();
}



/*===============================================================*/
/* ガンの情報を表示                                              */
/* Display information of gun controller.                        */
/*===============================================================*/

void DispGunInfo(Sint32 x, Sint32 y, Sint32 player)
{
	const GUNINFO* info;

	njPrint(NJM_LOCATION(x + 4, y), "PLAYER %d", player + 1);
	if (player == GUN_A) {
		njPrintPeripheralInfo(NJM_LOCATION(x, y + 10), PDD_PORT_A0);
	} else {
		njPrintPeripheralInfo(NJM_LOCATION(x, y + 10), PDD_PORT_B0);
	}

	info = GunGetInfo(player);

	if (info->IsGun) {
		/* ガンが接続されていれば情報を表示           */
		/* If gun is connected, displays information. */
		njPrint(NJM_LOCATION(x, y + 4), "(x,y)=(%4d,%4d)",
												info->x, info->y);
		njPrint(NJM_LOCATION(x, y + 5), "raw  =(%4d,%4d)",
											info->rawX, info->rawY);
		njPrint(NJM_LOCATION(x, y + 6), "trigger  = %d", info->trigger);
		njPrint(NJM_LOCATION(x, y + 7), "OnScreen = %d", info->OnScreen);

		/* トリガが引かれたら、ガンが画面内かどうかを判定し、 */
		/* 画面に表示する                                     */
		/* If trigger was pressed, examines whether there is  */
		/* the muzzle in a screen.                            */
		if (info->trigger) {
			if (info->OnScreen) {
				DrawTarget(info->x + 320, info->y + 240, player);
				{
					PDS_VIBPARAM param;

					param.unit = 1;
					param.flag = 0;
					param.power = 7;
					param.freq = 15;
					param.inc = 0;
					pdVibMxStart(PDD_PORT_A1, &param);
				}
			}
		}
	} else {
		if (gFrameCount & 0x00000020) {
			njPrintC(NJM_LOCATION(x + 2, y + 4), "CONNECT GUN.");
		}
	}
}




/*===============================================================*/
/* 簡単なポリゴン描画ルーチン                                    */
/* Easy polygon rendering routine.                               */
/*===============================================================*/

void DrawTarget(Sint32 x, Sint32 y, Sint32 gunno)
{
	static const Uint32 color[] = {
		0xffffffff, 0xffffff00, 0xffff00ff, 0xff00ffff,
	};

	DrawRect(0, y, 640, 1, color[gunno]);
	DrawRect(x, 0, 1, 480, color[gunno]);
}

void DrawRect(Sint32 x, Sint32 y, Sint32 w, Sint32 h, Uint32 color)
{
	Sint32 i;
	NJS_POLYGON_VTX vtx[4];

	for (i = 0; i < 4; i++) {
		vtx[i].col = color;
		vtx[i].z   = 4.f;
	}

	vtx[0].x = x;
	vtx[0].y = y;
	vtx[2].x = x + w;
	vtx[2].y = y;
	vtx[3].x = x + w;
	vtx[3].y = y + h;
	vtx[1].x = x;
	vtx[1].y = y + h;

	njDrawPolygon(vtx, 4, TRUE);
}

