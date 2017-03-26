/*
 *  Shinobi Library
 *  Copyright (c) 1998 SEGA
 *
 *       PERIPHERAL TIMER
 *
 *  Module  : Library Header File
 *  File    : sg_pdtmr.h
 *  Create  : 1998-07-03
 *  Modify  :
 *  Version : 1.00
 *  Note    :
 */

#ifndef _SG_PDTMR_H_
#define _SG_PDTMR_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sg_xpt.h>

/*
 *  DEFINES / MACROS
 */

/******** エラーコード *****************************************************/
#define PDD_TMRERR_OK          0           /* エラーなし                   */
                                           /* No error                     */
#define PDD_TMRERR_BUSY       (-1)         /* コマンド処理中               */
                                           /* Timer is busy                */
#define PDD_TMRERR_NO_TIMER   (-2)         /* タイマが接続されていない     */
                                           /* Timer is not connected       */
#define PDD_TMRERR_INVALID    (-3)         /* 指定された時刻は無効         */
                                           /* Time is invalid              */


/*
 *  TYPEDEFS
 */

/******** 時刻構造体 *******************************************************/
typedef struct {
	Uint16 year;                /* 年 year                                 */
	Uint8 month;                /* 月 month                                */
	Uint8 day;                  /* 日 day                                  */
	Uint8 hour;                 /* 時 hour                                 */
	Uint8 minute;               /* 分 minute                               */
	Uint8 second;               /* 秒 second                               */
	Uint8 dayofweek;            /* 曜日(日 = 0,月 = 1, ... 土 = 6)         */
	                            /* 設定時は有効、取得時は無効              */
	                            /* day of week(Sun = 0, Mon=1, ... Sat =6) */
	                            /* ...                                     */
} PDS_TIME;


/******** コールバック関数 *************************************************/
/******** Callback function ************************************************/
typedef void (*PD_TIMERCALLBACK)(Sint32 stat, Uint32 param);


/*
 *  PROTOTYPES
 */

Sint32 pdTmrIsReady(Uint32 port);
Sint32 pdTmrSetTime(Uint32 port, const PDS_TIME* time,
							PD_TIMERCALLBACK func, Uint32 param);
Sint32 pdTmrGetTime(Uint32 port, PDS_TIME*,
							PD_TIMERCALLBACK func, Uint32 param);
Sint32 pdTmrAlarm(Uint32 port, Uint8* data);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SG_PDTMR_H_ */