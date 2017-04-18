/*
    Ninja Sample

    COPYRIGHT (C) SEGA ENTERSRISES,LTD.

    Gun Sample #3

    1999.5.31
*/

#include <shinobi.h>
#include "gun.h"

void DrawTarget(Sint32 x, Sint32 y, Sint32 gunno);
void DrawRect(Sint32 x, Sint32 y, Sint32 w, Sint32 h, Uint32 color);
void DispGunInfo(Sint32 x, Sint32 y, Sint32 gunno);

void CalibGetPos(Sint32 gunno, Sint32 sx, Sint32 sy, Sint32* adjx, Sint32* adjy);
void CalibChk(Sint32 gunno);
Sint32 CalibStartCheck(void);

Uint32 gFrameCount;
Uint32 gTvMode;
Uint32 gCalibMode;
Uint32 gNowGun;         /* 現在どのGUNをキャリブレーション中か */

#define CALIB_STOP 0
#define CALIB_MIN  1
#define CALIB_MAX  2
#define CALIB_CEN  3
#define CALIB_SET  4
#define CALIB_CHK  5

static GUNADJ scrX = {-320+32, 0, 320-32};
static GUNADJ scrY = {-240+40, 0, 240-40};
static GUNADJ adjX[4], adjY[4];

static const char* PlayerName[] = {
	"PLAYER 1",
	"PLAYER 2",
	"PLAYER 3",
	"PLAYER 4",
};

static const Uint32 PortNo[] = {
	PDD_PORT_A0,
	PDD_PORT_B0,
	PDD_PORT_C0,
	PDD_PORT_D0,
};

static Uint32 GunBit[] = {
	PDD_GUNMODE_A,
	PDD_GUNMODE_B,
	PDD_GUNMODE_C,
	PDD_GUNMODE_D,
};

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
    njInitVertexBuffer( 1000, 0, -1, 0, 0);
    njInitPrint(NULL, 0, 0);
    njPrintSize(14);
	njSetBackColor(0x0000c0c0, 0x0000c0c0, 0x000000c0);
	njPrintColor(0xffffffff);

	gFrameCount = 0;
	gCalibMode = CALIB_STOP;
	gNowGun = GUN_A;

	/* ガンの初期化 */
	GunInit(gTvMode, PDD_GUNMODE_ALL);
	pdGunSetFlashColor(0x00c0c0c0);
}



/*===============================================================*/
/* アプリケーションのメインループ                                */
/* Main loop of application.                                     */
/*===============================================================*/

Sint32 njUserMain(void)
{
	GUNINFO* info;
	GUNADJ* ax;
	GUNADJ* ay;

	njPrintC(NJM_LOCATION( 4, 2), "LIGHT GUN SAMPLE #3");
	njPrintH(NJM_LOCATION(30, 2), gFrameCount++, 8);
	njPrint(NJM_LOCATION(  4, 3), "-CALIBRATION %s-", PlayerName[gNowGun]);

	/* １フレームに１度呼ぶガンのメイン関数 */
	/* Gun main function                    */
	GunMain();

	ax = &adjX[gNowGun];
	ay = &adjY[gNowGun];

	switch (gCalibMode) {
		case CALIB_STOP:
			/* ガンの接続とスタートボタンをチェック      */
			/* Check the gun connection and start button */
			CalibStartCheck();
			break;
		case CALIB_MIN:
			/* 画面左上での値を取得する */
			/* Get left-top position data */
			CalibGetPos(gNowGun, scrX.min, scrY.min, &ax->min, &ay->min);
			break;
		case CALIB_MAX:
			/* 画面右下での値を取得する */
			/* Get right-bottom position data */
			CalibGetPos(gNowGun, scrX.max, scrY.max, &ax->max, &ay->max);
			break;
		case CALIB_CEN:
			/* 画面中央での値を取得する */
			/* Get center position data */
			CalibGetPos(gNowGun, scrX.cen, scrY.cen, &ax->cen, &ay->cen);
			break;
		case CALIB_SET:
			/* 得られた値をもとにキャリブレーション情報を設定する */
			/* Set the calibration parameters                     */
			GunAdjust(gNowGun, ax, ay, &scrX, &scrY);
			/* ソフトウェアトリガモードにする */
			/* Set trigger mode as software trigger mode */
			GunSetRapid(gNowGun, GUN_RAPID_AUTO);
			/* 画面フラッシュをOFFにする */
			/* Turn off the screen flash */
			pdGunSetFlashColor(0);
			njSetBackColor(0xff808080, 0xff808080, 0xff808080);
			gCalibMode = CALIB_CHK;
			break;
		case CALIB_CHK:
			/* キャリブレーション結果を確認する       */
			/* Confirma the result of the calibration */
			CalibChk(gNowGun);
			break;
	}

	/* キャリブレーション中のガンが抜かれたら中止   */
	/* If the gun is removed, abort the calibration */
	info = GunGetInfo(gNowGun);
	if (!info->IsGun) {
		gCalibMode = CALIB_STOP;
	} else {
		DispGunInfo(2,  20, gNowGun);
	}

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

void DispGunInfo(Sint32 x, Sint32 y, Sint32 gunno)
{
	const GUNINFO* info;

	info = GunGetInfo(gunno);

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
				DrawTarget(info->x + 320, info->y + 240, gunno);
			}
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

/*===============================================================*/
/* ガンの接続とスタートボタンのチェック                          */
/*   Check the gun connection and start button                   */
/*===============================================================*/

Sint32 CalibStartCheck(void)
{
	Sint32 i;
	const PDS_PERIPHERAL* per;
	GUNINFO* info;

	if (gFrameCount & 0x00000030) {
		njPrintC(NJM_LOCATION( 7, 10), "PRESS START BUTTON TO     ");
		njPrintC(NJM_LOCATION( 7, 11), "         START CALIBRATION");
	}

	for (i = 0; i < 4; i++) {
		per = pdGetPeripheral(PortNo[i]);
		info = GunGetInfo(i);
		if ((per->press & PDD_DGT_ST) && info->IsGun) {
			GunSetPort(GunBit[i]);
			gCalibMode = CALIB_MIN;
			gNowGun = i;
			break;
		}
	}

	return 0;
}


/*===============================================================*/
/* その座標でのガン生データを取得する                            */
/*   Get raw data of the gun                                     */
/*===============================================================*/

void CalibGetPos(Sint32 gunno, Sint32 sx, Sint32 sy,
											Sint32* adjx, Sint32* adjy)
{
	Sint32 x, y;
	GUNINFO* info;


	njPrintC(NJM_LOCATION(10, 10), "SHOOT THE TARGET!");
	DrawRect(sx-16+320, sy-16+240, 32, 32, 0xffffffff);

	info = GunGetInfo(gunno);

	if (info->trigger) {
		if ((info->rawX >= 0) && (info->rawY >= 0)) {
			*adjx = info->rawX;
			*adjy = info->rawY;
			gCalibMode++;
		}
	}
}

/*===============================================================*/
/* キャリブレーション結果を確認する                              */
/*   Confirm the result of the calibration                       */
/*===============================================================*/

void CalibChk(Sint32 gunno)
{
	const PDS_PERIPHERAL* per;
	GUNADJ* ax;
	GUNADJ* ay;

	if (gFrameCount & 0x00000030) {
		njPrintC(NJM_LOCATION( 7, 10), "PRESS START BUTTON TO EXIT");
		njPrintC(NJM_LOCATION( 7, 11), "     B BUTTON TO RETRY    ");
	}

	ax = &adjX[gunno];
	ay = &adjY[gunno];

	njPrint(NJM_LOCATION(2, 14), "MIN(%d,%d) MAX(%d,%d) CEN(%d,%d)",
		ax->min, ay->min, ax->max, ay->max, ax->cen, ay->cen);

	ax = &scrX;
	ay = &scrY;
	njPrint(NJM_LOCATION(2, 15), "SCREEN(%d,%d)-(%d,%d)",
							ax->min, ay->min, ax->max, ay->max);

	per = pdGetPeripheral(PortNo[gunno]);

	/* START button to exit calibration */
	if (per->press & PDD_DGT_ST) {
		njSetBackColor(0x0000c0c0, 0x0000c0c0, 0x000000c0);
		gCalibMode = CALIB_STOP;
		GunSetRapid(gunno, GUN_RAPID_OFF);
		pdGunSetFlashColor(0x00c0c0c0);
	}

	/* B button retry calibration */
	if (per->press & PDD_DGT_TB) {
		njSetBackColor(0x0000c0c0, 0x0000c0c0, 0x000000c0);
		gCalibMode = CALIB_MIN;
		GunSetRapid(gunno, GUN_RAPID_OFF);
		pdGunSetFlashColor(0x00c0c0c0);
	}
}


