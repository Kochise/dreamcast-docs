#ifndef _GUN_H_
#define _GUN_H_

#include <shinobi.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define GUN_A            0  /* Gun Controller A                            */
#define GUN_B            1  /* Gun Controller B                            */
#define GUN_C            2  /* Gun Controller C                            */
#define GUN_D            3  /* Gun Controller D                            */

#define GUN_VGA          0  /* VGA                                         */
#define GUN_NTSC_640x480 1  /* NTSC 640x480                                */
#define GUN_NTSC_320x240 2  /* NTSC 320x240                                */

#define GUN_RAPID_OFF    0  /* 連射モードOFF                               */
#define GUN_RAPID_ON     1  /* トリガが引かれている間連射                  */
#define GUN_RAPID_AUTO   2  /* トリガが引かれていなくても連射              */

/******** ガン情報構造体 ***************************************************/
/******** Gun information structure ****************************************/
typedef struct {
	Sint32 IsGun;           /* ガンが接続されているかどうか                */
	                        /* Is gun connected ?                          */
	Sint32 OnScreen;        /* ガンが画面内を向いているか                  */
	                        /* Does the muzzle point to the inside of      */
	                        /* a screen ?                                  */
	Sint32 x, y;            /* ガン座標                                    */
	                        /* Gun position                                */
	Sint32 rawX, rawY;      /* ガン座標(生データ)                          */
	                        /* Gun position(raw data)                      */
	Sint32 trigger;         /* トリガ情報                                  */
	                        /* Is the trigger pressed ?                    */
} GUNINFO;

/******** ガン座標補正用パラメータ *****************************************/
/******** Gun position adjust parameter.                                   */
typedef struct {
	Sint32 min;             /* 座標最小値                                  */
	                        /* Minimum position                            */
	Sint32 cen;             /* 座標中央値                                  */
	                        /* Center position                             */
	Sint32 max;             /* 座標最大値                                  */
	                        /* Maximum position                            */
} GUNADJ;


void GunInit(Sint32 tvmode, Sint32 gunmode);
void GunSetPort(Sint32 gunmode);
void GunMain(void);
void GunExit(void);
const GUNINFO* GunGetInfo(Uint32 port);
void GunSetRapid(Sint32 gunno, Sint32 flag);
void GunAdjust(Sint32 gunno, const GUNADJ* adjx, const GUNADJ* adjy,
									const GUNADJ* scrx, const GUNADJ* scry);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _GUN_H_ */
