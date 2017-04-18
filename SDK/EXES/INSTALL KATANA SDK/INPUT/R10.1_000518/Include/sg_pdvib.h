/*
 *  Shinobi Library
 *  Copyright (c) 1998 SEGA
 *
 *       PERIPHERAL VIBRATOR
 *
 *  Module  : Library Header File
 *  File    : sg_pdvib.h
 *  Create  : 1999-1-18
 *  Modify  :
 *  Version : 1.00
 *  Note    :
 */

#ifndef _SG_PDVIB_H_
#define _SG_PDVIB_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sg_xpt.h>

/*
 *  DEFINES / MACROS
 */

/******** エラーコード *****************************************************/
/******** Error code *******************************************************/
#define PDD_VIBERR_OK           0        /* エラーなし                     */
                                         /* No error                       */
#define PDD_VIBERR_BUSY        (-1)      /* コマンド処理中                 */
                                         /* Busy                           */
#define PDD_VIBERR_NO_VIBRATOR (-2)      /* 振動デバイスが接続されていない */
                                         /* No vibrator is connected       */
#define PDD_VIBERR_INVALID     (-3)      /* 指定されたパラメータは無効     */
                                         /* Invalid parameter              */

/******** デバイスの向き ***************************************************/
/******** Direction of device **********************************************/
#define PDD_VIB_DIRECTION_NORMAL   0     /* 通常                           */
                                         /* Normal                         */
#define PDD_VIB_DIRECTION_FLIP     1     /* 180度回転(逆さま)              */
                                         /*                                */
#define PDD_VIB_DIRECTION_LEFT     2     /* 左90度回転                     */
                                         /*                                */
#define PDD_VIB_DIRECTION_RIGHT    3     /* 右90度回転                     */
                                         /*                                */

/******** 振動フラグ *******************************************************/
/******** flags ************************************************************/
#define PDD_VIB_FLAG_CONTINUOUS  (1 << 0)    /* 連続振動                   */
                                             /* Continuous vibration       */
#define PDD_VIB_FLAG_EXHALATION  (1 << 3)    /* 発散指定                   */
                                             /* Exhalation vibration       */
#define PDD_VIB_FLAG_CONVERGENCE (1 << 7)    /* 収束指定                   */
                                             /* Convergence vibration      */

/******** 振動ユニット位置 *************************************************/
/******** Vibrator unit position *******************************************/
#define PDD_VIB_POS_FRONT 0              /* デバイス前部                   */
                                         /* Front of the device            */
#define PDD_VIB_POS_BACK  1              /* デバイス後部                   */
                                         /* Back of the device             */
#define PDD_VIB_POS_LEFT  2              /* デバイス左側                   */
                                         /* Left of the device             */
#define PDD_VIB_POS_RIGHT 3              /* デバイス右側                   */
                                         /* Right of the device            */

/******** 振動軸 ***********************************************************/
/******** Vibration axis ***************************************************/
#define PDD_VIB_AXIS_NONE 0              /* 軸なし                         */
                                         /* No axis                        */
#define PDD_VIB_AXIS_X    1              /* X軸                            */
                                         /* X axis                         */
#define PDD_VIB_AXIS_Y    2              /* Y軸                            */
                                         /* Y Axis                         */
#define PDD_VIB_AXIS_Z    3              /* Z軸                            */
                                         /* Z Axis                         */

/******** コールバック関数リターン値 ***************************************/
#define PDD_VIBRET_OK     0              /* 継続                           */
                                         /* Continue enumeration           */


/*
 *  TYPEDEFS
 */

/******** 振動パラメータ構造体 *********************************************/
/******** Vibration parameter structure ************************************/
typedef struct {
	Uint8 unit;                          /* ユニット番号                   */
	                                     /* Unit number                    */
	Uint8 flag;                          /* 振動フラグ                     */
	                                     /* Vibration flag                 */
	Sint8 power;                         /* 強さ                           */
	                                     /* Power                          */
	Uint8 freq;                          /* 振動周波数                     */
	                                     /* Frequency                      */
	Uint8 inc;                           /* 振動勾配周期                   */
	                                     /*                                */
	Uint8 reserved[3];                   /* 予約                           */
	                                     /* Reserved                       */
} PDS_VIBPARAM;

/******** 振動デバイス情報構造体 *******************************************/
/******** Vibration device information structure ***************************/
typedef struct {
	Uint8 units;                         /* ユニット数                     */
	                                     /* Number of units                */
	Uint8 se_units;                      /* 同時振動設定可能ユニット数     */
	                                     /* Number of ...                  */
} PDS_VIBINFO;

/******** 振動ユニット情報構造体 *******************************************/
/******** Vibration unit information structure *****************************/
typedef struct {
	Uint8 position;                      /* 振動ユニット位置               */
	                                     /* Vibration unit position        */
	Uint8 axis;                          /* 振動軸                         */
	                                     /* Vibration axis                 */
	Uint8 pow_enable;                    /* 振動強度可変フラグ             */
	                                     /* Is power variable ?            */
	Uint8 cont_enable;                   /* 連続振動フラグ                 */
	                                     /* Is continuous ?                */
	Uint8 dir_enable;                    /* 方向指定フラグ                 */
	                                     /* ...                            */
	Uint8 wave_enable;                   /* 任意振動波形フラグ             */
	                                     /* ...                            */
	Uint8 min_freq;                      /* 最小振動周波数                 */
	                                     /* Minimum frequency              */
	Uint8 max_freq;                      /* 最大振動周波数                 */
	                                     /* Maximum frequency              */
} PDS_VIBUNITINFO;

/******** コールバック関数型 ***********************************************/
/******** Callback function type *******************************************/
typedef Sint32 (*PD_VIBCALLBACK)(Sint32 stat, Uint32 param);
typedef Sint32 (*PD_VIBENUMUNITCALLBACK)(Uint32 unit, Sint32 stat,
									PDS_VIBUNITINFO* info, Uint32 param);


/*
 *  PROTOTYPES
 */

/******** maxi専用お手軽関数 ***********************************************/
/******** Easy vibration functions for Puru-puru pack **********************/
Sint32 pdVibMxIsReady(Uint32 port);
Sint32 pdVibMxSetStopTime(Uint32 port, Uint32 time);
Sint32 pdVibMxStart(Uint32 port, const PDS_VIBPARAM* param);
Sint32 pdVibMxStop(Uint32 port);


/******** 汎用振動関数 *****************************************************/
/******** Vibration functions **********************************************/
Sint32 pdVibIsReady(Uint32 port);
Sint32 pdVibGetDirection(Uint32 port);
Sint32 pdVibSetStopTime(Uint32 port, Uint8* unit, Uint8* time, Uint32 num);
Sint32 pdVibStart(Uint32 port, const PDS_VIBPARAM* param, Uint32 numunits);
Sint32 pdVibSetWave(Uint32 port, Uint32 unit, const void* wave, Uint32 num);
Sint32 pdVibGetInfo(Uint32 port, PDS_VIBINFO* info);
Sint32 pdVibEnumerateUnit(Uint32 port, PD_VIBENUMUNITCALLBACK func,
																Uint32 param);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SG_PDVIB_H_ */

