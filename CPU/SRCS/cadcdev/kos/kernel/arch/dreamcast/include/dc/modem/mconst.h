/* KallistiOS ##version##

   mconst.h
   Copyright (C)2002, 2004 Nick Kochakian

   Distributed under the terms of the KOS license.

   $Id: mconst.h,v 1.1 2003/05/23 02:05:02 bardtx Exp $
*/

/* Modem constants are defined here. Automatically included by modem.h */
#ifndef __MODEM_MCONST_H
#define __MODEM_MCONST_H

/* Each speed constant contains information about the data rate in bps and the
   protocol that's being used. The first 4 bits identify the the speed that's
   being used, and the last 4 bits identify the protocol.

   And don't try to create your own custom speeds from these, you'll cause
   something very bad to happen. Only use the MODEM_SPEED_* constants defined
   in modem.h! */

/* Speeds */
#define MODEM_SPEED_AUTO  0x0
#define MODEM_SPEED_1200  0x0
#define MODEM_SPEED_2400  0x1
#define MODEM_SPEED_4800  0x2
#define MODEM_SPEED_7200  0x3
#define MODEM_SPEED_9600  0x4
#define MODEM_SPEED_12000 0x5
#define MODEM_SPEED_14400 0x6
#define MODEM_SPEED_16800 0x7
#define MODEM_SPEED_19200 0x8
#define MODEM_SPEED_21600 0x9
#define MODEM_SPEED_24000 0xA
#define MODEM_SPEED_26400 0xB
#define MODEM_SPEED_28000 0xC
#define MODEM_SPEED_31200 0xD
#define MODEM_SPEED_33600 0xE

/* Protocols */
#define MODEM_PROTOCOL_V17    0x0
#define MODEM_PROTOCOL_V22    0x1
#define MODEM_PROTOCOL_V22BIS 0x2
#define MODEM_PROTOCOL_V32    0x3
#define MODEM_PROTOCOL_V32BIS 0x4
#define MODEM_PROTOCOL_V34    0x5
#define MODEM_PROTOCOL_V8     0x6

#define MODEM_SPEED_GET_PROTOCOL(x) ((modem_speed_t)(x) >> 4)
#define MODEM_SPEED_GET_SPEED(x)    ((modem_speed_t)(x) & 0xF)
#define MODEM_MAKE_SPEED(p, s)      ((modem_speed_t)((((p) & 0xF) << 4) | ((s) & 0xF)))

typedef unsigned char modem_speed_t;

#endif
