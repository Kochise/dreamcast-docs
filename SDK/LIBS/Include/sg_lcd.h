/*
 *  Shinobi Library
 *  Copyright (c) 1998 SEGA
 *
 *       LCD
 *
 *  Module  : Library Header File
 *  File    : sg_lcd.h
 *  Create  : 1998-06-24
 *  Modify  : 1998-11-25
 *  Version : 1.02
 *  Note    :
 */

#ifndef _SG_LCD_H_
#define _SG_LCD_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sg_xpt.h>


/*
 *  DEFINES / MACROS
 */

/******** エラーコード *****************************************************/
#define PDD_LCDERR_OK          0           /* エラーなし                   */
                                           /* No error                     */
#define PDD_LCDERR_BUSY       (-1)         /* コマンド処理中               */
                                           /* Busy                         */
#define PDD_LCDERR_NO_LCD     (-2)         /* 液晶が接続されていない       */
                                           /* No LCD is connected          */

/******** 液晶の向き *******************************************************/
#define PDD_LCD_DIRECTION_NORMAL   0       /* 通常                         */
                                           /* Normal                       */
#define PDD_LCD_DIRECTION_FLIP     1       /* 180度回転(逆さま)            */
                                           /*                              */
#define PDD_LCD_DIRECTION_LEFT     2       /* 左90度回転                   */
                                           /*                              */
#define PDD_LCD_DIRECTION_RIGHT    3       /* 右90度回転                   */
                                           /*                              */

/******** フラグ ***********************************************************/
#define PDD_LCD_FLAG_NOFLIP        0       /* 通常                         */
                                           /* Normal                       */
#define PDD_LCD_FLAG_HFLIP         1       /* 左右反転                     */
                                           /*                              */
#define PDD_LCD_FLAG_VFLIP         2       /* 上下反転                     */
                                           /*                              */
#define PDD_LCD_FLAG_HVFLIP        3       /* 上下左右反転                 */
                                           /*                              */


/*
 *  PROTOTYPES
 */

void pdLcdInit(void);
void pdLcdExit(void);
Sint32 pdLcdGetDirection(Uint32 port);


/*
 *  VMS ONLY LCD FUNCTIONS
 */

Sint32 pdVmsLcdWrite(Uint32 port, void* data, Uint32 flag);
Sint32 pdVmsLcdWrite1(Uint32 port, void* data);
Sint32 pdVmsLcdIsReady(Uint32 port);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SG_LCD_H_ */

