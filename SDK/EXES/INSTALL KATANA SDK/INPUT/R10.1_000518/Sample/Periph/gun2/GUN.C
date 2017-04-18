/********************************************************************
 *  Shinobi Library Sample
 *  Copyright (c) 1998 SEGA
 *
 *  Library : Controller Library
 *  Module  : Gun Functions (Continuous shot sample)
 *  File    : gun.c
 *  Date    : 1999-03-03
 *  Version : 1.00
 ********************************************************************/

#include "gun.h"


/******** ガン座標補正用パラメータ *****************************************/
/******** Gun position adjust parameter.                                   */
typedef struct {
	Sint32 min;             /* 座標最小値                                  */
	                        /* Minimum position                            */
	Sint32 cen;             /* 座標中央値                                  */
	                        /* Center position                             */
	Sint32 max;             /* 座標最大値                                  */
	                        /* Maximum position                            */
} ADJPARAM;


/******** ガン用ワーク *****************************************************/
/******** Work area for gun.                                               */
typedef struct {
	Sint32 rawX, rawY;      /* ガン座標(生データ)                          */
	                        /* Gun position(raw data)                      */
	Sint32 x, y;            /* ガン座標(補正後)                            */
	                        /* Gun position(corrected)                     */
	Sint32 rawOnScreen;     /* ガンが画面内を向いているか(生データ)        */
	                        /* Does the muzzle point to the inside of      */
	                        /* a screen ? (raw data)                       */
	Sint32 OnScreen;        /* ガンが画面内を向いているか                  */
	                        /* Does the muzzle point to the inside of      */
	                        /* a screen ?                                  */
	Sint32 trigger;         /* トリガ情報                                  */
	                        /* Is the trigger pressed ?                    */
	ADJPARAM adjx, adjy;    /* ガン座標補正用パラメータ                    */
	                        /* Gun adjust parameters                       */
} GUNWORK;


static GUNWORK GunWork[4];  /* ガン用ワーク(４ポート分）                   */
                            /* Work area for gun (for 4 control ports)     */
static GUNINFO GunInfo[4];  /* ガン情報(４ポート分）                       */
                            /* Gun information (for 4 control ports)       */
static Sint32 RapidFlag[4]; /* 連射フラグ(４ポート分)                      */
                            /* Continuous shot flag(for 4 control ports)   */


/*===============================================================*/
/* 補正後のガン座標がとりうる最小、最大、中心値                  */
/* この値を変更すると、補正後のガン座標の移動範囲を変更できます。*/
/* また、NTSCの場合は画面周辺が表示されないことを考慮して、多少  */
/* 範囲を狭くしています。                                        */
/* The minumum, center and maximum value that gun coordinate     */
/* after corrected.                                              */
/* You can change a sphere of movement of gun coordinate after   */
/* corrected when change these value.                            */
/* Considers that the screen outskirts are not displayed in case */
/* NTSC and makes range narrow.                                  */
/*===============================================================*/

static const ADJPARAM ScreenAdjTblX[] = {
	/* 最小  中心  最大 */
	/* min   cen   max  */
	{ -320,    0,   320},         /* VGA                                   */
	{ -312,    0,   312},         /* NTSC 640x480                          */
	{ -156,    0,   156},         /* NTSC 320x240                          */
};

static const ADJPARAM ScreenAdjTblY[] = {
	/* 最小  中心  最大 */
	/* min   cen   max  */
	{  -240,   0,   240},         /* VGA                                   */
	{  -208,   0,   208},         /* NTSC 640x480                          */
	{  -104,   0,   104},         /* NTSC 320x240                          */
};


/*===============================================================*/
/* ガン座標生データのキャリブレーションテーブル                  */
/* この値を変更すると、銃のキャリブレーション(微調整)ができます。*/
/* ガン座標生データがこの値の時にそれぞれ最小、中心、最大を      */
/* 示します。                                                    */
/* Calibration table of raw data of gun.                         */
/* You can do a fine adjustment of a gun when change these       */
/* values.                                                       */
/*===============================================================*/
static const ADJPARAM CalibTblX[] = {
	/* 最小  中心  最大 */
	/* min  cen   max  */
	{  409,  695, 1013},          /* VGA                                   */
	{  295,  620,  891},          /* NTSC 640x480                          */
	{  295,  620,  891},          /* NTSC 320x240                          */
};

static const ADJPARAM CalibTblY[] = {
	/* 最小  中心  最大 */
	/* min  cen   max  */
	{   82,  300,  519},          /* VGA                                   */
	{   45,  152,  254},          /* NTSC 640x480                          */
	{   45,  152,  254},          /* NTSC 320x240                          */
};


static const PortNo[] = {
	PDD_PORT_A0,
	PDD_PORT_B0,
	PDD_PORT_C0,
	PDD_PORT_D0,
};

/* 前回のガン座標生データを記憶しておく変数 */
/* Variables to memorize a lat raw coordinate of a gun. */
static Sint32 LastGunPosX;
static Sint32 LastGunPosY;

/* 補正用パラメータへのポインタ。 画面モードにより切り替えます */
/* Pointers to calibration table. Chances it according to screen mode. */
static const ADJPARAM* CalibX;
static const ADJPARAM* CalibY;
static const ADJPARAM* ScreenX;
static const ADJPARAM* ScreenY;

/*-------------------------------------------------------------------------*/
static Sint32 adjust(Sint32 rawval, const ADJPARAM *raw,
			const ADJPARAM *adj, Sint32 min, Sint32 max, Sint32 *onscflg);
static Sint32 adjust_sub(Sint32 val, const ADJPARAM *raw,
													const ADJPARAM *adj);
static Sint32 callback(void);

/*-------------------------------------------------------------------------*/

/*===============================================================*/
/*      コントローラライブラリをガンモードに設定する             */
/*      Set up controller library in gun mode.                   */
/*===============================================================*/

void GunInit(Sint32 tvmode)
{
	pdGunEnter(PDD_GUNMODE_ALL);
	pdGunSetCallback(callback);
	pdGunSetFlashColor(0x00ffffff);

	memset(GunWork, 0, sizeof(GunWork));
	memset(GunInfo, 0, sizeof(GunInfo));
	memset(RapidFlag, 0, sizeof(RapidFlag));

	LastGunPosX = 0;
	LastGunPosY = 0;

	CalibX = &CalibTblX[tvmode];
	CalibY = &CalibTblY[tvmode];
	ScreenX = &ScreenAdjTblX[tvmode];
	ScreenY = &ScreenAdjTblY[tvmode];
}



/*
** ポート番号から構造体配列のインデックスに変換する
** Converts port number into an index.
*/

static Sint32 port2index(Sint32 port)
{
	switch (port) {
		case PDD_PORT_A0: return 0;
		case PDD_PORT_B0: return 1;
		case PDD_PORT_C0: return 2;
		case PDD_PORT_D0: return 3;
		default: return -1;
	}
}

/*===============================================================*/
/*      毎フレーム呼ばれるガンのメイン関数                       */
/*      Main function of a gun called every frame.               */
/*===============================================================*/

void GunMain(void)
{
	GUNWORK* gw;
	GUNINFO* gi;
	PDS_PERIPHERAL* per;
	Sint32 gunport;
	Sint32 gunx, guny;
	Sint32 i;
	Sint32 flag1, flag2;

	for (i = 0; i < 4; i++) {
		GunWork[i].trigger = FALSE;
	}

	/* ガン座標を取得したポートを調べる           */
	/* Examine the port which got gun coordinate. */
	gunport = pdGunGetLatchedPort();

	if (gunport >= 0) {
		gw = &GunWork[port2index(gunport)];

		/* ガン座標生データの取得     */
		/* Get raw coordinate of gun. */
		pdGunGetPosition(&gunx, &guny);

		if (gunx < 200) gunx += 857;

		gw->trigger= TRUE;

		/* 前回の値と全く同じならば、座標が得られなかった  */
		/* として、画面外とする。                          */
		/* If a coordinate is same as a last value at all, */
		/* could not get coordinate.                       */
		if ((LastGunPosX == gunx) && (LastGunPosY == guny)) {
			gw->rawOnScreen = FALSE;
			gw->OnScreen = FALSE;
			gw->rawX = -1;
			gw->rawY = -1;
			gw->x = 999;
			gw->y = 999;
		} else {
			gw->rawOnScreen = FALSE;
			gw->rawX = gunx;
			gw->rawY = guny;
			gw->x = adjust(gw->rawX, CalibX, ScreenX, -320, 319, &flag1);
			gw->y = adjust(gw->rawY, CalibY, ScreenY, -240, 239, &flag2);
			gw->OnScreen = (flag1 && flag2) ? TRUE : FALSE;
		}

		/* 今回の値を保存する               */
		/* Store a coordinate of this time. */
		LastGunPosX = gunx;
		LastGunPosY = guny;
	}

	gw = GunWork;
	gi = GunInfo;
	for (i = 0; i < 4; i++, gw++, gi++) {
		/* ガンが接続されているかどうかの判定 */
		/* Is gun connected ?                 */
		per = pdGetPeripheral(PortNo[i]);
		gi->IsGun = (per->info->type & PDD_DEVTYPE_LIGHTGUN) ? 1 : 0;
		/* ガンワークからガン情報構造体にコピーする                   */
		/* Copy values to gun information structure from work of gun. */
		gi->x = gw->x;
		gi->y = gw->y;
		gi->rawX = gw->rawX;
		gi->rawY = gw->rawY;
		gi->trigger = gw->trigger;
		gi->OnScreen = gw->OnScreen;
	}
}


/*===============================================================*/
/*      ガンの情報を取得する                                     */
/*      Get gun information.                                     */
/*===============================================================*/
const GUNINFO* GunGetInfo(Uint32 port)
{
	return &GunInfo[port];
}

/*===============================================================*/
/*      連射モードを設定する                                     */
/*      Set continuous shot mode.                                */
/*===============================================================*/
void GunSetRapid(Sint32 gunno, Sint32 flag)
{
	RapidFlag[gunno] = flag;
}


/*===============================================================*/
/*      コントローラライブラリを通常モードに設定する             */
/*      Set up controller library in normal mode.                */
/*===============================================================*/
void GunExit(void)
{
	pdGunLeave();
}


/*-------------------------------------------------------------------------*/


/*
** 直線補正 & MIN-MAXチェック
** Linear correction and minimum-maximum check.
*/

static Sint32 adjust(Sint32 rawval, const ADJPARAM *raw, const ADJPARAM *adj,
								Sint32 min, Sint32 max, Sint32 *onscflg)
{
	Sint32 val;

	val = adjust_sub(rawval, raw, adj);

	/* 範囲外か？                   */
	/* Is a value outside of range? */
	if (val < min) {
		*onscflg = FALSE;
		return 0;
	} else if (val > max) {
		*onscflg = FALSE;
		return 0;
	}

	*onscflg = TRUE;
	return val;
}


/*
** 直線補正(戻り値は補正後の値)
** Linear correction (Return value is a corrected value)
*/

static Sint32 adjust_sub(Sint32 val, const ADJPARAM *raw, const ADJPARAM *adj)
{
	if (((raw->max > raw->min) ? 0 : 1)^((raw->cen > val) ? 0 : 1)) {
		if (raw->max == raw->cen) {
			return 0;
		} else {
			return (val - raw->cen) * (adj->max - adj->cen) /
									(raw->max - raw->cen) + adj->cen;
		}
	} else {
		if (raw->min == raw->cen) {
			return  0;
		} else {
			return (val - raw->cen) * (adj->min - adj->cen) /
									(raw->min - raw->cen) + adj->cen;
		}
	}
}




/*-------------------------------------------------------------------------*/

/*
** ガンコールバック関数
** Gun callback function.
*/

static Sint32 callback(void)
{
	static Uint32 count = 0;
	Sint32 i;
	const PDS_PERIPHERAL* per;

	for (i = 0; i < 4; i++) {
		per = pdGetPeripheral(PortNo[i]);

		if (RapidFlag[i]) {
			/* 連射フラグがONなら、定期的にトリガ情報をセットする     */
			/* If continuous shot flag is on, sets trigger regularly. */
			if (per->on & PDD_DGT_TA) {
				if (((count >> 1) & 3) == i) {
					pdGunSetTrigger(PortNo[i]);
				}
			}
		} else {
			/* 連射フラグがOFFなら、実際のトリガでトリガ情報をセットする */
			/* If continuous shot flag is FALSE, sets trigger with       */
			/* real trigger.                                             */
			if (per->press & PDD_DGT_TA) {
				pdGunSetTrigger(PortNo[i]);
			}
		}
	}

	count++;

	return FALSE;
}

