/* KallistiOS ##version##

   modem.h
   Copyright (C)2002, 2004 Nick Kochakian

   Distributed under the terms of the KOS license.

   $Id: modem.h,v 1.1 2003/05/23 02:05:02 bardtx Exp $
*/

#ifndef __DC_MODEM_MODEM_H
#define __DC_MODEM_MODEM_H

#include "mconst.h"

#define MODEM_MODE_REMOTE 0   /* Connect to a remote modem */
#define MODEM_MODE_ANSWER 1   /* Answer a call when a ring is detected */
#define MODEM_MODE_NULL   255 /* Not doing anything. Don't give this to
                                 any function! */

/* V.22 bis modes */
#define MODEM_SPEED_V22BIS_1200 MODEM_MAKE_SPEED(MODEM_PROTOCOL_V22BIS, MODEM_SPEED_1200)
#define MODEM_SPEED_V22BIS_2400 MODEM_MAKE_SPEED(MODEM_PROTOCOL_V22BIS, MODEM_SPEED_2400)

/* V.22 modes */
#define MODEM_SPEED_V22_1200 MODEM_MAKE_SPEED(MODEM_PROTOCOL_V22, MODEM_SPEED_1200)

/* V.32 modes */
#define MODEM_SPEED_V32_4800 MODEM_MAKE_SPEED(MODEM_PROTOCOL_V32, MODEM_SPEED_4800)
#define MODEM_SPEED_V32_9600 MODEM_MAKE_SPEED(MODEM_PROTOCOL_V32, MODEM_SPEED_9600)

/* V.32 bis modes */
#define MODEM_SPEED_V32BIS_7200  MODEM_MAKE_SPEED(MODEM_PROTOCOL_V32BIS, MODEM_SPEED_7200)
#define MODEM_SPEED_V32BIS_12000 MODEM_MAKE_SPEED(MODEM_PROTOCOL_V32BIS, MODEM_SPEED_12000)
#define MODEM_SPEED_V32BIS_14400 MODEM_MAKE_SPEED(MODEM_PROTOCOL_V32BIS, MODEM_SPEED_14400)

/* V.8 modes */
#define MODEM_SPEED_V8_2400  MODEM_MAKE_SPEED(MODEM_PROTOCOL_V8, MODEM_SPEED_2400)
#define MODEM_SPEED_V8_4800  MODEM_MAKE_SPEED(MODEM_PROTOCOL_V8, MODEM_SPEED_4800)
#define MODEM_SPEED_V8_7200  MODEM_MAKE_SPEED(MODEM_PROTOCOL_V8, MODEM_SPEED_7200)
#define MODEM_SPEED_V8_9600  MODEM_MAKE_SPEED(MODEM_PROTOCOL_V8, MODEM_SPEED_9600)
#define MODEM_SPEED_V8_12000 MODEM_MAKE_SPEED(MODEM_PROTOCOL_V8, MODEM_SPEED_12000)
#define MODEM_SPEED_V8_14400 MODEM_MAKE_SPEED(MODEM_PROTOCOL_V8, MODEM_SPEED_14400)
#define MODEM_SPEED_V8_16800 MODEM_MAKE_SPEED(MODEM_PROTOCOL_V8, MODEM_SPEED_16800)
#define MODEM_SPEED_V8_19200 MODEM_MAKE_SPEED(MODEM_PROTOCOL_V8, MODEM_SPEED_19200)
#define MODEM_SPEED_V8_21600 MODEM_MAKE_SPEED(MODEM_PROTOCOL_V8, MODEM_SPEED_21600)
#define MODEM_SPEED_V8_24000 MODEM_MAKE_SPEED(MODEM_PROTOCOL_V8, MODEM_SPEED_24000)
#define MODEM_SPEED_V8_26400 MODEM_MAKE_SPEED(MODEM_PROTOCOL_V8, MODEM_SPEED_26400)
#define MODEM_SPEED_V8_28000 MODEM_MAKE_SPEED(MODEM_PROTOCOL_V8, MODEM_SPEED_28000)
#define MODEM_SPEED_V8_31200 MODEM_MAKE_SPEED(MODEM_PROTOCOL_V8, MODEM_SPEED_31200)
#define MODEM_SPEED_V8_33600 MODEM_MAKE_SPEED(MODEM_PROTOCOL_V8, MODEM_SPEED_33600)
#define MODEM_SPEED_V8_AUTO  MODEM_MAKE_SPEED(MODEM_PROTOCOL_V8, MODEM_SPEED_1200)

/* Event constants */
typedef enum
{
    MODEM_EVENT_CONNECTION_FAILED = 0, /* The modem tried to establish a connection but failed */
    MODEM_EVENT_CONNECTED,             /* A connection has been established */
    MODEM_EVENT_DISCONNECTED,          /* The remote modem dropped the connection */
    MODEM_EVENT_RX_NOT_EMPTY,          /* New data has entered the previously empty receive buffer */
    MODEM_EVENT_OVERFLOW,              /* The receive buffer overflowed and was cleared */
    MODEM_EVENT_TX_EMPTY               /* The transmission buffer has been emptied */
} modemEvent_t;

typedef void (*MODEMEVENTHANDLERPROC)(modemEvent_t event);

/* From modem.c */
int           modem_init(void);
void          modem_shutdown(void);
int           modem_set_mode(int mode, modem_speed_t speed);
int           modem_wait_dialtone(int ms_timeout);
int           modem_dial(const char *digits);
void          modem_set_event_handler(MODEMEVENTHANDLERPROC eventHandler);
void          modem_disconnect(void);
int           modem_is_connecting(void);
int           modem_is_connected(void);
unsigned long modem_get_connection_rate(void);

/* From mdata.c */
int modem_read_data(unsigned char *data, int size);
int modem_write_data(unsigned char *data, int size);
int modem_has_data(void);

#endif
