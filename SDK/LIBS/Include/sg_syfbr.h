/********************************************************************
 *  Shinobi Library
 *  Copyright (c) 1998-1999 SEGA
 *
 *  Library : fiber library (very simple thread library)
 *  Module  : Library Interface Header
 *  File    : sg_syfbr.h
 *  Date    : 1999-01-21
 *  Version : 1.11
 *  History : 98/02/06 r0.00
 *            98/05/04 r0.04 識別子の名称統一                       
 *            98/05/04 r0.05 ファイバテーブルをユーザから取得する   
 *            98/11/20 r1.10 syFbrPreInit/syFbrExit/syFbrSetIntStackの定義
 ******************************************************************/

#ifndef _SG_SYFBR_H_
#define _SG_SYFBR_H_

/********************************************************************/
/*  インクルードファイル                                            */
/*  include files                                                   */
/********************************************************************/
#include    <sg_xpt.h>                      /*                      */
#include    <sg_ov.h>                       /*                      */

/********************************************************************/
/*  定数定義                                                        */
/*  constants                                                       */
/********************************************************************/
#ifdef SYD_FBR_FIXEDTBL                       							/* not used */                        
#define SYD_FBR_MAXFIBER    	(32)         /* ファイバの上限値    */  /* not used */
#endif                                                                  /* not used */

#define SYD_FBR_MINFIBER    	(2)          /* ファイバの下限値    */

#define SYD_FBR_NULL        	(NULL)       /* ファイバハンドルエラー値*/
#define SYD_FBR_OK          	(0)          /* ファイバ関数戻り値  */
#define SYD_FBR_NG          	(-1)         /* ファイバ関数戻り値  */

#define SYD_FBR_NOTSETED        (-1)
#define SYD_FBR_THREADTOCREATE  (-1)									/* not used */
#define SYD_FBR_NOTEXISTFIBER   (-1)         /* ファイバ未生成       */
                                             /* 非ファイバハンドル値 */
#define SYD_FBR_SYSSTACKSIZE (292)           /* システムが必要とするスタック */
											 /* system data size in stack */
#define SYD_FBR_LID {   \
    0x77b9fee0,         \
    0xe397,0x11d1,      \
    0x9a,0xb0,0x00,0xa0,\
    0x24,0xd8,0x60,0x79 \
} ;

/********************************************************************/
/*  型定義                                                          */
/*  structure/union/enum                                            */
/********************************************************************/
typedef struct SyFbrS_INFO_tag{             /* ファイバ情報         */
    void*       sp ;                        /* ファイバのスタックポインタ(fiber's stack pointer) */
    void*       data ;                      /* ファイバのデータ          (fiber's data)          */
} SYS_FBR_INFO; 
typedef SYS_FBR_INFO*    SYFBR ;            /* ファイバハンドル     */
                                            /* fiber handle type    */
typedef void (*SyFbrYfunc)(void*) ;         /* ファイバ関数型       */
                                            /* fiber function type  */
#define SYD_FBR_FBRSIZE (sizeof(SYS_FBR_INFO))

/********************************************************************/
/*  広域変数定義                                                    */
/*  global valiables                                                */
/********************************************************************/
#ifdef  SYD_FBR_FIXEDTBL                    /*                      */ /* not used */
extern SYS_FBR_INFO sygFbrTbl[] ;           /* ファイバテーブル     */ /* not used */
#else                                       /*                      */ /* not used */
extern SYS_FBR_INFO* sygFbrTblPtr ;         /* ファイバテーブルポインタ*/
                                            /* pointer to fiber table  */
#endif                                      /*                      */
extern Sint32      sygFbrMaxFiber ;         /* 最大ファイバ数       */
                                            /* max number of fiber  */
extern SYFBR       sygFbrCurrent ;          /* 現在のファイバ       */
                                            /* current fiber handle */
extern const UUID sygFbrLID ;               /* ライブラリＩＤ       */ /* not used */

/********************************************************************/
/*  関数定義                                                        */
/*  functions                                                       */
/********************************************************************/

#ifdef __cplusplus
extern "C"{                                 /* for C++ Interface    */
#endif  /* __cplusplus */

#ifdef SYD_FBR_FIXEDTBL                                              
extern  Sint32  syFbrInit( void ) ;
#else                                                                
extern  Sint32  syFbrInit( void*, Sint32) ;                          
#endif                                                               

extern  Sint32  syFbrPreInit( Sint32*, int );                        /* r1.10 */
extern  Sint32  syFbrExit( Void ) ;                                  /* r1.10 */
extern  Sint32  syFbrSetIntStack( void* ) ;                          /* r1.10 */

extern  SYFBR   syFbrCreateFiber( void*,Uint32,SyFbrYfunc,void* ) ;
extern  SYFBR   syFbrConvertThreadToFiber( void* ) ;
extern  Sint32  syFbrDeleteFiber    ( SYFBR ) ;
extern  SYFBR   syFbrGetCurrentFiber( void ) ;
extern  void*   syFbrGetFiberData   ( void ) ;

extern  void*   syFbrCreateFiberMain(void*,long,SyFbrYfunc,void* ) ;
extern  void    syFbrSwitchToFiber        ( SYFBR ) ;
extern  void    syFbrSwitchToFiber2       ( SYFBR ) ;
extern  void    syFbrDelayedSwitchToFiber ( SYFBR ) ;
extern  void    syFbrDelayedSwitchToFiber2( SYFBR ) ;

extern  void*   syFbrGetSp  (SYFBR) ;
extern  void*   syFbrGetData(SYFBR) ;
extern  void    syFbrSetSp  (SYFBR,void*) ;
extern  void    syFbrSetData(SYFBR,void*) ;

extern  SYS_FBR_INFO*   syFbrGetTblPtr( int n ) ;                    
extern  Sint32  syFbrGetMaxFiber( void ) ;                           
extern  void*   syFbrGet_fib_sp ( int i) ;

#if 0
extern  void*   get_fib_data(int i) ;
extern  void    set_fib_sp  (int i, void* sp) ;
extern  void    set_fib_data(int i, void* data) ;
#endif

extern  void    syFbrDumpTable( void ) ;

#ifdef __cplusplus
}                                           /* for C++ Interface    */
#endif /* __cpulspuls  */
#endif /* __SG_FB_H__ */
/********************************************* End of fiber.h *******/
