/*
 *  Shinobi Library
 *  Copyright (c) 1998 SEGA
 *
 *  Library : Configuration Library
 *  Module  : Library Interface Header
 *  File    : sg_cfg.h
 *  Date    : 1998-11-27
 *  Author  : T.S. (SEGA, SYSTEM_R&D)
 *  Version : 1.01
 *
 */


#ifndef _SG_CFG_H_

#define _SG_CFG_H_


/***** macros *****/

#define SYD_BT_CFG_OK   ( 0)
#define SYD_BT_CFG_ERR  (-1)

#define SYD_BT_CFGINI     (0x00)
#define SYD_BT_CFGWRT_AT  (0x01)
#define SYD_BT_CFGWRT_SM  (0x02)
#define SYD_BT_CFGWRT_LG  (0x04)
#define SYD_BT_CFGWRT_GM  (0x08)
#define SYD_BT_CFGWRT_TM  (0x10)

#define SYD_BT_CFG_WORKSIZE  (0x4000)


/***** structures *****/


/***** prototype *****/

Sint32 syBtCfgSet(Sint32 permit, void *work);


#endif /* _SG_CFG_H_ */

/* eof */
