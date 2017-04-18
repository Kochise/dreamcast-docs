/********************************************************************
 *  Shinobi Library
 *  Copyright (c) 1998-1999 SEGA
 *
 *  Library : BootRom Service & System ID Data Check Library
 *  Module  : Library Interface Header
 *  File    : sg_sybt.h
 *  Update  : 1999-05-21  Ver.1.14
 *  Date    : 1999-01-21  Ver.1.01
 *
 ********************************************************************/

#ifndef _SG_SYBT_H_
#define _SG_SYBT_H_

/********************************************************************/
/*  インクルードファイル                                            */
/*   inlcude files                                                  */
/********************************************************************/
#include    <sg_xpt.h>                      /*                      */
#include    <shinobi.h>                     /*                      */

/********************************************************************/
/*  定数定義                                                        */
/*  constants                                                       */
/********************************************************************/
#define SYD_BT_OK                (1)          /*                    */
#define SYD_BT_NG                (0)          /*                    */

/********************************************************************/
/*  型定義                                                          */
/*  structure/union/enum                                            */
/********************************************************************/
struct tag_SYS_BT_SYSTEMID{                   /*                    */
    Sint32 nNo ;                              /*                    */
    Sint32 nAll ;                             /*                    */
    Sint8  szProduct[16];                     /*                    */
} ;                                           /*                    */
typedef struct tag_SYS_BT_SYSTEMID SYS_BT_SYSTEMID ;

/********************************************************************/
/*  関数定義                                                        */
/*  functions                                                       */
/********************************************************************/
#ifdef __cplusplus
extern "C"{                                 /* for C++ Interface    */
#endif  /* __cplusplus */

extern Void   syBtExit     ( Void );
extern Sint32 syBtCheckDisc( Void );

extern Sint32 syBtGetBootSystemID   ( SYS_BT_SYSTEMID* ) ;
extern Sint32 syBtGetCurrentSystemID( SYS_BT_SYSTEMID* ) ;

#ifdef __cplusplus
}                                           /* for C++ Interface    */
#endif /* __cplusplus  */
#endif /* _SG_SYBT_H_ */
/****************************************** End of sg_sycfg.h *******/
