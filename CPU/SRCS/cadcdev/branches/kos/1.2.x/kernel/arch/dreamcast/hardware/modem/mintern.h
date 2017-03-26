/* KallistiOS ##version##

   mintern.h
   Copyright (C)2002 Nick Kochakian

   Distributed under the terms of the KOS license.

   $Id: mintern.h,v 1.1 2003/05/23 02:04:42 bardtx Exp $
*/
         

#ifndef __MINTERN_H
#define __MINTERN_H

#include <arch/irq.h>
#include <dc/g2bus.h>
#include "msegbuf.h"

#ifndef REGLOC
  #define REGLOC(x) (0xA0600400 + (x) * 4)
#endif

#ifndef G2_8BP_RST
  #define G2_8BP_RST 0xA0600480
#endif

#define modemWrite(a, d)     g2_write_8(a, d)
#define modemRead(a)         g2_read_8(a)
#define modemSetBits(a, d)   g2_write_8(a, g2_read_8(a) | (d))
#define modemClearBits(a, d) g2_write_8(a, g2_read_8(a) & ~(d))

/* DSP memory access macros */
#define dspSetBits8(DSPAddr, bits) dspWrite8(DSPAddr, dspRead8(DSPAddr) | (bits))
#define dspClearBits8(DSPAddr, bits) dspWrite8(DSPAddr, dspRead8(DSPAddr) & ~(bits))

#define MODEM_STATE_NULL         0 /* Not doing anything specific */
#define MODEM_STATE_CONNECT_WAIT 1 /* Waiting for a handshake signal */
#define MODEM_STATE_ANSWER_WAIT  2 /* Waiting mode after the answer tone is
                                      detected (not used in answer mode) */
#define MODEM_STATE_CONNECTING   3 /* Connecting to a remote computer */
#define MODEM_STATE_DELAY        4 /* A slight delay after connecting */

typedef struct
{
  unsigned char inited;
  unsigned char state;    /* Mode constant */
  unsigned char protocol; /* Data transmission protocol */
  unsigned char speed;    /* Data transmission speed */

  unsigned char lockData;

  struct
  {
    unsigned long speed; /* Actual connection speed */
    int           state; /* State constant used by the interrupt handlers */
    unsigned char connecting;
    unsigned char connected;
    unsigned char rlsdFlag;
    unsigned char ac;
  } actual;
} MODEM_CFG;

extern MODEM_CFG modemCfg;
extern unsigned long modemBPSConstants[31];
extern int __isLessThan(int x, int y);

//From mintr.c:
void modemIntInit(void);
void modemIntShutdown(void);
void modemIntConfigModem(void);
void modemIntSetHandler(int protocol, int mode);
void modemIntClearHandler(void);
void modemIntSetupTimeoutTimer(int bps, unsigned char *callbackFlag,
                               void (*callbackCode)(void));
void modemIntStartTimeoutTimer(void);
void modemIntResetTimeoutTimer(void);
void modemIntShutdownTimeoutTimer(void);

//From modem.c:
void           modem_reset(void);
void           modemEstablishConnection(void);
int            dspWrite8(unsigned char meaddl, unsigned char meaddh,
                         unsigned char medal);
int            dspWrite16(unsigned char meaddl, unsigned char meaddh,
                          unsigned short medal);
int            dspWrite16x2(unsigned char meaddl1, unsigned char meaddh1,
                            unsigned char meaddl2, unsigned char meaddh2,
                            unsigned short medal);
unsigned char  dspRead8(unsigned char meaddl, unsigned char meaddh);
unsigned short dspRead16(unsigned char meaddl, unsigned char meaddh);
unsigned short dspRead16x2(unsigned char meaddl1, unsigned char meaddh1,
                           unsigned char meaddl2, unsigned char meaddh2);

//From mdata.c:
void modemDataSetupBuffers(void);
void modemDataDestroyBuffers(void);
void modemDataUpdateRXBuffer(void);
void modemDataUpdateTXBuffer(void);

#endif
