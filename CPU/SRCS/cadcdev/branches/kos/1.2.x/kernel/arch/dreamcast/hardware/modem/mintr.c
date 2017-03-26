/* KallistiOS ##version##

   mintr.c
   Copyright (C)2002 Nick Kochakian

   Distributed under the terms of the KOS license.
*/

/* Modem interrupt handlers and interrupt setup */
/* The G2 interrupt setup code was taken from the LAN adapter code in KOS */
#include <stdlib.h>
#include <dc/asic.h>
#include <kos.h>
#include <dc/modem/modem.h>
#include "mintern.h"

CVSID("$Id: mintr.c,v 1.1 2003/05/23 02:04:42 bardtx Exp $");

void (*modemCallbackCode)(void) = NULL;

unsigned char *modemTimeoutCallbackFlag         = NULL;
void          (*modemTimeoutCallbackCode)(void) = NULL;

#define IRQ_ACK\
  /* Acknowledge the interrupt */\
  ASIC_ACK_B = 1 << 2;\
\
  if (modemRead(REGLOC(0x1F)) & 0x80)\
     modemClearBits(REGLOC(0x1F), 0x8);

/* An interrupt handler that doesn't do anything in particular */
static void modemCallbackNothing(irq_t source, irq_context_t *context)
{
     IRQ_ACK
}

/* A callback for non answering modes. This is called after a timer interrupt
   is generated after a period of one second after the answer tone is
   detected. */
void modemConnectionAnswerCallback(void)
{
     modemIntResetTimeoutTimer();
     modemIntShutdownTimeoutTimer();

     /* Establish a connection */
     modemEstablishConnection();
     modemCfg.actual.state    = MODEM_STATE_CONNECTING;
     modemCfg.actual.rlsdFlag = 0;
     modemCfg.actual.ac       = 0;
}

/* This is used for a slight delay after connection. The Dreamcast's modem
   seems to jump into a ready state faster than my computer's modem which
   can cause problems if nothing's done about it. */
int mintCounter = 0;

void mintDelayCallback(void)
{
     mintCounter++;
     if (mintCounter >= 6)
     {
        modemIntResetTimeoutTimer();
        modemIntShutdownTimeoutTimer();

        modemCfg.actual.connecting = 0;
        modemCfg.actual.connected  = 1;
        modemCfg.lockData          = 0;
     }
}

/* A handler for when a connection has been established */
void modemConnectedUpdate(void)
{
     if (!modemCfg.lockData)
     {
        /* Check to see if the RX buffer needs updating */
        if (modemRead(REGLOC(0x1)) & 0x2)
           modemDataUpdateRXBuffer();

        /* Check to see if the TX buffer needs updating.
           Checks 0Dh:1 TXFNF Transmitter FIFO Not Full.
           If the transmitter FIFO is not full, then any data that's in
           the segmented FIFO buffer should be sent to the modem. */
        if (modemRead(REGLOC(0xD)) & 0x2)
           modemDataUpdateTXBuffer();
     }
}

/* Connection handler for most non-56k modes */
void modemConnection(void)
{
     switch (modemCfg.actual.state)
     {
            case MODEM_STATE_CONNECT_WAIT:
                 /* Was the handshake signal detected? */
                 if (modemRead(REGLOC(0xB)) & 0x10)
                 {
                    /* Need to wait for one second before establishing a
                       connection */
                    modemCfg.actual.state = MODEM_STATE_ANSWER_WAIT;

                    /* Setup the timeout timer to delay for 1 second before
                       calling the callback function */
                    modemIntSetupTimeoutTimer(1, NULL,
                                              modemConnectionAnswerCallback);
                    modemIntStartTimeoutTimer();
                 }
            break;

            case MODEM_STATE_CONNECTING:
                 /* The v.32 protocols don't actually start the handshake
                    until the AC tone is detected */
                 if ((modemCfg.protocol==MODEM_PROTOCOL_V32 ||
                      modemCfg.protocol==MODEM_PROTOCOL_V32BIS) &&
                     !modemCfg.actual.ac && (modemRead(REGLOC(0xC)) & 0x40))
                 {
                    /* Turn the DATA bit on to start the handshake */
                    modemSetBits(REGLOC(0x9), 0x4);
                    modemSetBits(REGLOC(0x8), 0x1); /* Set RTS */
                    modemCfg.actual.ac = 1;
                 }

                 /* Has the connection completed yet? */
                 if (modemRead(REGLOC(0xF)) & 0x80)
                 {
                    /* Get the connection speed. This works for all modes but
                       v.34 which requires a special procedure to get the
                       connection speed. */
                    if (modemCfg.protocol != MODEM_PROTOCOL_V34)
                       modemCfg.actual.speed = modemBPSConstants[modemRead(REGLOC(0xE)) & 0x1F];
                       else
                       {
                         /* Get the v.34 connection speed */
                         modemCfg.actual.speed = 0;
                       }

                    /* Delay for 6 seconds before actually going into a
                       connected state */
                    modemCfg.actual.state = MODEM_STATE_NULL;
                    modemCallbackCode     = modemConnectedUpdate;

                    mintCounter = 0;
                    modemIntSetupTimeoutTimer(1, NULL, mintDelayCallback);
                    modemIntStartTimeoutTimer();
                 }
            break;
     }
}

static void modemCallback(irq_t source, irq_context_t *context)
{
     IRQ_ACK

     if (modemCallbackCode != NULL)
        modemCallbackCode();
}

void modemIntInit(void)
{
     atexit(modemIntShutdown);

     /* Set the default IRQ handler */
     irq_set_handler(EXC_IRQB, modemCallbackNothing);

     /* Enable G2 interrupts */
     ASIC_IRQB_B = 1 << 2;
}

void modemIntShutdown(void)
{
     /* Disable G2 interrupts */
     ASIC_IRQB_B &= ~(ASIC_EVT_EXP_8BIT & 0xFF);

     /* Set a NULL IRQ handler */
     irq_set_handler(EXC_IRQB, NULL);
}

/* Communicates with the modem's DSP to mask out some events on which a
   hardware interrupt should be generated. This also disables the default
   IRQ on completeion of a DSP read or write. */
void modemIntConfigModem(void)
{
     /* Set the default IRQ handler */
     irq_set_handler(EXC_IRQB, modemCallbackNothing);

     /* Disable memory access interrupts by setting bit 6 of memory location
        0x89 */
     dspSetBits8(MAKE_DSP_ADDR(0x89), 0x40);

     /* Enable interrupts for these events in register 0xB:
        TONEA \
        TONEB  | Tone detectors used for detecting dial tones, etc.
        TONEC /
        ATV25  - Answer tone detection
        DISDET - Disconnection detector */
     dspSetBits8(MAKE_DSP_ADDR(0x245), 0xF2);

     /* Enable interrupts for these events in register 0xF:
        RLSD - Set when the MDP has finished the connection sequence
        RI   - Ring indicator */
     dspSetBits8(MAKE_DSP_ADDR(0x241), 0x88);

     /* Enable interrupts for these events in register 0xC:
        ACDET - Indicates that a V.32 bis/V.32 AC sequence has been
                detected (0Ch:6) */
     dspSetBits8(MAKE_DSP_ADDR(0x244), 0x40);

     /* Enable interrupts for these events in register 0x1:
        RXHF - RX FIFO half full (01h:1)
        TXHF - TX FIFO half full (01h:2) */
     dspSetBits8(MAKE_DSP_ADDR(0x247), 0x6);

     /* Enable interrupts for these events in register 0xD:
        TXFNF - Transmitter FIFO not full (0Dh:1) */
     dspSetBits8(MAKE_DSP_ADDR(0x243), 0x2);

     /* Set default values for some of the variables that the interrupts
        use */
     modemCfg.actual.state = MODEM_STATE_NULL;
     modemCfg.actual.ac    = 0;

     /* Set NSIE and NEWS */
     modemSetBits(REGLOC(0x1F), 0x18);
}

/* Sets the interrupt handler and state based on the specified mode of
   operation */
void modemIntSetHandler(int protocol, int mode)
{
     modemCfg.actual.connected = 0;
     modemCallbackCode         = modemConnection;

     switch (mode)
     {
            case MODEM_MODE_REMOTE:
            break;

            case MODEM_MODE_DIRECT:
                 modemCfg.actual.state      = MODEM_STATE_CONNECT_WAIT;
                 modemCfg.actual.connecting = 1;
                 irq_set_handler(EXC_IRQB, modemCallback);
            break;

            case MODEM_MODE_ANSWER:
            break;
     }
}

void modemIntClearHandler(void)
{
     /* Set the default IRQ handler */
     irq_set_handler(EXC_IRQB, modemCallbackNothing);
}

/* Timeout timer interrupt code. It uses TMU1 and can be setup to either set
   a flag to a non zero value, call a function, or both when a timer interrupt
   is generated until it's stopped. */

static void modemIntrTimeoutCallback(irq_t source, irq_context_t *context)
{
    if (modemTimeoutCallbackFlag != NULL)
       *modemTimeoutCallbackFlag = 1;
    if (modemTimeoutCallbackCode != NULL)
       modemTimeoutCallbackCode();
}

void modemIntSetupTimeoutTimer(int bps, unsigned char *callbackFlag,
                               void (*callbackCode)(void))
{
     modemTimeoutCallbackFlag = callbackFlag;
     modemTimeoutCallbackCode = callbackCode;

     /* Setup TMU1 so it can act as a timeout indicator */
     timer_stop(TMU1);

     /* Make sure the timeout variable is reset */
     if (modemTimeoutCallbackFlag != NULL)
        *modemTimeoutCallbackFlag = 0;

     /* Modify TMU1 so that it can be used for a timeout */
     irq_set_handler(EXC_TMU1_TUNI1, modemIntrTimeoutCallback);
     timer_prime(TMU1, bps, 1);
     timer_clear(TMU1);
}

void modemIntStartTimeoutTimer(void)
{
     timer_start(TMU1);
}

void modemIntResetTimeoutTimer(void)
{
     timer_stop(TMU1);
     timer_clear(TMU1);
}

void modemIntShutdownTimeoutTimer(void)
{
     irq_set_handler(EXC_TMU1_TUNI1, NULL);
}
