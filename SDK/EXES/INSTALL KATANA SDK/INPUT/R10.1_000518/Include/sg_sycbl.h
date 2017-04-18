/*
 * sg_syCbl.h
 *
 * FUNCTION: check a video cable with a machine.
 * MODIFICATION:
 *  0.51 Modified for BootROM 0.70 by SEKI Masahiro
 *  1.10 Added API for broadcast system by SEKI Masahiro
 */
#ifndef _SG_CBL_H_
#define _SG_CBL_H_

typedef enum SYE_CBL_CABLE_TAG {
	SYE_CBL_CABLE_VGA = 0,
	SYE_CBL_CABLE_RESERVED = 1,
	SYE_CBL_CABLE_NTSC_RGB = 2,
	SYE_CBL_CABLE_PAL_RGB = 2,
	SYE_CBL_CABLE_RGB = 2,
	SYE_CBL_CABLE_NTSC = 3,
	SYE_CBL_CABLE_PAL = 3,
	SYE_CBL_CABLE_VBS = 3,
#if 1 /* 1.10 */
	SYE_CBL_CABLE_MAX
#endif
} SYE_CBL_CABLE;

#if 1 /* 1.10 */
typedef enum SYE_CBL_BROADCAST_TAG {
	SYE_CBL_BROADCAST_NTSC = 0,
	SYE_CBL_BROADCAST_PAL = 1,
	SYE_CBL_BROADCAST_PALM = 2,
	SYE_CBL_BROADCAST_PALN = 3,
	SYE_CBL_BROADCAST_MAX
} SYE_CBL_BROADCAST;
#endif

#if 1 /* 1.10 */
typedef enum SYE_CBL_TAG {
	SYE_CBL_NTSC = 0,
	SYE_CBL_VGA = 1,
	SYE_CBL_PAL = 2,
	SYE_CBL_MAX
} SYE_CBL;
#endif

SYE_CBL_CABLE syCblCheckCable( void );

#if 1 /* 1.10 */
SYE_CBL_BROADCAST syCblCheckBroadcast( void );
SYE_CBL syCblCheck( void );
#endif

#endif
