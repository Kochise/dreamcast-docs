/********************************************************************
 *  Shinobi Library
 *  Copyright (c) 1998-1999 SEGA
 *
 *  Library : High layer Configuration Library
 *  Module  : Library Interface Header
 *  File    : sg_sycfg.h
 *  Date    : 1999-03-31
 *  Version : 1.14
 *
 ********************************************************************/

#ifndef _SG_SYCFG_H_
#define _SG_SYCFG_H_

/********************************************************************/
/*  インクルードファイル                                            */
/*  include files                                                   */
/********************************************************************/
#include    <sg_xpt.h>                      /*                      */
#include    <shinobi.h>                     /*                      */
/********************************************************************/
/*  定数定義                                                        */
/*  constants                                                       */
/********************************************************************/
#define SYD_CFG_STEREO  (0x00)              /* ステレオ設定         */
#define SYD_CFG_MONO    (0x01)              /* モノラル設定         */
#define SYD_CFG_OK      (0)                 /* 正常終了             *//* Ver1.10 */
#define SYD_CFG_NG      (-1)                /* 異常終了             *//* Ver1.10 */

                                            /* Ver1.10              */
/*** カントリーコード ***/
/*** country code     ***/
#define SYD_CFG_JAPAN    (0x30)             /* 日本                 */
#define SYD_CFG_AMERICA  (0x31)             /* アメリカ・ブラジル...*/
#define SYD_CFG_EUROPE   (0x32)             /* 欧州                 */

/*** 言語設定 ***/
/*** language ***/
#define SYD_CFG_JAPANESE   (0x0)            /* 日本語               */
#define SYD_CFG_ENGLISH    (0x1)            /* 英語                 */
#define SYD_CFG_GERMAN     (0x2)            /* ドイツ語             */
#define SYD_CFG_FRENCH     (0x3)            /* フランス語           */
#define SYD_CFG_SPANISH    (0x4)            /* スペイン語           */
#define SYD_CFG_ITALIAN    (0x5)            /* イタリア語           */

#define SYD_CFG_D_JAPANESE (0x30)           /* 日本語               */
#define SYD_CFG_D_ENGLISH  (0x31)           /* 英語                 */
#define SYD_CFG_D_GERMAN   (0x32)           /* ドイツ語             */
#define SYD_CFG_D_FRENCH   (0x33)           /* フランス語           */
#define SYD_CFG_D_SPANISH  (0x34)           /* スペイン語           */
#define SYD_CFG_D_ITALIAN  (0x35)           /* イタリア語           */

/*** 放送形式 ***/
/*** bloadcast type ***/
#define SYD_CFG_NTSC     (0x30)             /* NTSC                 */
#define SYD_CFG_PAL      (0x31)             /* PAL                  */
#define SYD_CFG_PAL_M    (0x32)             /* PAL-M                */
#define SYD_CFG_PAL_N    (0x33)             /* PAL-N                */


/*** 個体識別番号 ***/
/*** individual id ***/
#define SYD_CFG_IID_SIZE (6)				/* 個体識別子データ長   */
											/* individual id data size */

#define SYD_CFG_IID_OK		(1)				/* IID取得OK            *//* Ver1.11 */
#define SYD_CFG_IID_CHKERR	(2)				/* チェックサムエラー   *//* Ver1.11 */
#define SYD_CFG_IID_NG  	(0)				/* IID取得NG            *//* Ver1.11 */

/********************************************************************/
/*  型定義                                                          */
/*  structure/union/enum                                            */
/********************************************************************/

/********************************************************************/
/*  広域変数定義                                                    */
/*  global valiables                                                */
/********************************************************************/

/********************************************************************/
/*  関数定義                                                        */
/*  functions                                                       */
/********************************************************************/
#ifdef __cplusplus
extern "C"{                                 /* for C++ Interface    */
#endif  /* __cplusplus */

Sint32 syCfgInit( Void* ) ;                 /* ライブラリ初期化処理 */
Sint32 syCfgExit( Void  ) ;                 /* ライブラリ終了処理   */
Sint32 syCfgSetSoundMode( Sint32  ) ;       /* 音声設定の更新       */
Sint32 syCfgGetSoundMode( Sint32* ) ;       /* 音声設定の参照       */
                                            /* Ver1.02              */
Sint32 syCfgGetCountryCode  ( Sint32* ) ;   /* カントリーコード取得 */
Sint32 syCfgGetLanguage     ( Sint32* ) ;   /* 言語設定取得         */
Sint32 syCfgGetDefaultLanguage( Sint32* ) ; /* デフォルト言語設定取得*//* Ver1.14*/
Sint32 syCfgGetBroadcastType( Sint32* ) ;   /* 放送形式取得         */

Sint32 syCfgGetIndividualID( Sint8* ) ;     /* 固体識別番号         */

#ifdef __cplusplus
}                                           /* for C++ Interface    */
#endif /* __cplusplus  */
#endif /* _SG_SYCFG_H_ */
/****************************************** End of sg_sycfg.h *******/
