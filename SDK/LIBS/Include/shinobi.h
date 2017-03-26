/*
 *  Shinobi Library
 *  Copyright (c) 1998-1999 SEGA
 *
 *       Shinobi Library
 *
 *  Module  : Library Header File
 *  File    : shinobi.h
 *  Create  : 1998-03-25
 *  Modify  : 1999-04-12
 *  Version : 1.37
 *  Note    :
 */

#ifndef _SHINOBI_H_
#define _SHINOBI_H_


#include <machine.h>      /* SHC Builtin Functions                    */
#include <ninja.h>        /* Ninja Library                            */
#include <ninjapad.h>     /* Controller Library for Ninja             */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sg_pad.h>       /* Controller Library                       */
#include <sg_gd.h>        /* GD Library                               */
#include <sg_sytmr.h>     /* Timer Library                            */
#include <sg_syrtc.h>     /* Realtime Clock Library                   */
#include <sg_maloc.h>     /* Memory Management Library                */
#include <sg_sycbl.h>     /* Cable Detection Library                  */
#include <sg_sycfg.h>     /* Configuration Library                    */
#include <sg_sybt.h>      /* BOOT ROM Service Library                 */
#include <sg_btfnt.h>     /* BOOT ROM Font Library                    */
#include <sg_lcd.h>       /* LCD Library                              */
#include <sg_pdkbd.h>     /* Keyboard Library                         */
#include <sg_pdvib.h>     /* Vibration Library                        */
#include <sg_pdtmr.h>     /* Peripheral Timer Library                 */
#include <sg_bup.h>       /* Backup Library                           */
#include <sg_cache.h>     /* Cache Library                            */
#include <sg_uf.h>        /* Play history Library                     */
#include <wssip.h>        /* Sound Input  Library                     */
#include <sg_sysrt.h>     /* C++ Startup Library                      */

extern void sbInitSystem(Int mode, Int frame, Int count);
extern void sbExitSystem(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SHINOBI_H_ */

/******************************* end of file *******************************/
