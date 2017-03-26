/* KallistiOS ##version##

   modem.c
   Copyright (C)2002 Nick Kochakian

   Distributed under the terms of the KOS license.
*/

#include <kos.h>
#include <dc/g2bus.h>
#include <stdlib.h>
#include <dc/modem/modem.h>
#include "mintern.h"

CVSID("$Id: modem.c,v 1.1 2003/05/23 02:04:42 bardtx Exp $");

/* These timeout values are not exact! */
#define MODEM_215MS_TIMEOUT 8

void modemQuickReset(void); /* Does a hard reset on the modem but doesn't
                               configure anything */
void modemConfigurationReset(void); /* Configures the modem. It's assumed that
                                       the modem has already been reset. */

MODEM_CFG modemCfg = { 0, MODEM_MODE_NULL, 0, 0, 1,
                       { 0, MODEM_STATE_NULL, 0, 0 } };

/* Converts a protocol/speed constant to a value that can be used with the
   CONF register to configure the modem. A value of zero is equal to an
   undefined speed. */
static unsigned char modemSpeedConfig[8][15] = {
    /* V.17 protocol */
    /* 1200  2400  4800  7200  9600  12000 14400 16800 19200 21600 */
    {  0,    0,    0,    0xB8, 0xB4, 0xB2, 0xB1, 0,    0,    0,

    /* 24000 26400 28000 31200 33600 */
       0,    0,    0,    0,    0  },

    /* V.22 protocol */
    /* 1200  2400  4800  7200  9600  12000 14400 16800 19200 21600 */
    {  0x52, 0,    0,    0,    0,    0,    0,    0,    0,    0,

    /* 24000 26400 28000 31200 33600 */
       0,    0,    0,    0,    0  },

    /* V.22 bis protocol */
    /* 1200  2400  4800  7200  9600  12000 14400 16800 19200 21600 */
    {  0x82, 0x84, 0,    0,    0,    0,    0,    0,    0,    0,

    /* 24000 26400 28000 31200 33600 */
       0,    0,    0,    0,    0  },

    /* V.32 protocol */
    /* 1200  2400  4800  7200  9600  12000 14400 16800 19200 21600 */
    {  0,    0,    0x71, 0,    0x75, 0,    0,    0,    0,    0,

    /* 24000 26400 28000 31200 33600 */
       0,    0,    0,    0,    0  },

    /* V.32 bis protocol */
    /* 1200  2400  4800  7200  9600  12000 14400 16800 19200 21600 */
    {  0,    0,    0,    0x78, 0,    0x72, 0x76, 0,    0,    0,

    /* 24000 26400 28000 31200 33600 */
       0,    0,    0,    0,    0  },

    /* V.34 protocol */
    /* Auto  2400  4800  7200  9600  12000 14400 16800 19200 21600 */
    {  0,    0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9,

    /* 24000 26400 28000 31200 33600 */
       0xCA, 0xCB, 0xCC, 0xCD, 0xCE }
};

/* Converts the value found in the SPEED register (0Eh:4-0) to a numerical
   value in bits per second (bps.) */
unsigned long modemBPSConstants[31] = {
    300,   600,   1200,  2400,  4800,  9600,  12000, 14400, 7200,  16800,
    19200, 21600, 24000, 26400, 28800, 31200, 33600, 0,     0,     0,
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    0
};

/* Cleardown configuration code table, which is different for each protocol */
static unsigned char modemCleardownCodes[] =
    /* v.17 v.22 v.22bis v.32  v.32bis v.34 */
    {  0,   0,   0,      0x70, 0x70,   0xC0 };

unsigned char modemTimeout = 0;

/* Need this for the timeout loops, otherwise the program never breaks out
   of them for some reason. */
int __isLessThan(int x, int y)
{
    return (x < y) ? 1 : 0;
}

void modemTimeoutIncCallback(void)
{
     modemTimeout++;
}

/* Verifys if the controller data returned as a result of a reset is valid
   or not. Returns zero if the results are invalid other a non zero number
   is returned. */
static __inline int verifyControllerData(unsigned short *ctrlInfo)
{
       /* RAM1 and RAM2 Checksums */
       if ((ctrlInfo[0]==0xEA3C || ctrlInfo[0]==0x451) &&
           (ctrlInfo[1]==0x5536 || ctrlInfo[1]==0x49A5))
       {
          /* ROM1 and ROM2 Checksums */
          if (ctrlInfo[2]==0x5F4C &&
              (ctrlInfo[3]==0x3835 || ctrlInfo[3]==0x3836))
          {
             /* Timer/ROM/RAM */
             if (ctrlInfo[4]==0x801 || ctrlInfo[4]==0xDE00)
             {
                /* Part Number and Revision Level */
                if ((ctrlInfo[5]==0x3730 || ctrlInfo[5]==0x3731) &&
                    ctrlInfo[6]==0x4241)
                   return 1;
             }
          }
       }

       return 0;
}

/* Does the same thing as verifyControllerData but checks to see if the DSP
   values from the DSP self test are valid. */
static __inline int verifyDSPData(unsigned short *dspInfo)
{
       /* EC Checksum */
       if (dspInfo[0]==0xF083 || dspInfo[0]==0xA577)
       {
          /* Multiplier Checksum */
          if (dspInfo[1]==0x46EE)
          {
             /* RAM and ROM Checksums */
             if ((dspInfo[2]==0xFA || dspInfo[2]==0xB482) &&
                 (dspInfo[3]==0xA09 || dspInfo[3]==0x3836))
             {
                /* Part Number and Revision Level */
                if ((dspInfo[4]==0x3730 || dspInfo[4]==0x3631) &&
                    dspInfo[5]==0x2041)
                   return 1;
             }
          }
       }

       return 0;
}

/* Initiates a modem self test and determines if a modem is present or not.
   This only needs to be called ONCE during the modemInit function. */
int modemSelfTest(void)
{
    int            i;
    unsigned short ctrlInfo[7];
    unsigned short dspInfo[6];

    #define readValue16(ah, al) ((modemRead(ah) << 8) | (modemRead(al)))

    /*
       Data is read in this order. Expected values are also listed.
       The modem that this was tested on got all of the expected values that
       appear first.

       Controller info
       ---------------
       RAM1 Checksum  = 0xEA3C or 0x451
       RAM2 Checksum  = 0x5536 or 0x49A5
       ROM1 Checksum  = 0x5F4C
       ROM2 Checksum  = 0x3835 or 0x3836
       Timer/ROM/RAM  = 0x801 or 0xDE00
       Part Number    = 0x3730 or 0x3731
       Revision Level = 0x4241

       DSP info
       --------
       EC Checksum         = 0xF083 or 0xA577
       Multiplier Checksum = 0x46EE
       RAM Checksum        = 0xFA or 0xB482
       ROM Checksum        = 0xA09 or 0x3836
       Part Number         = 0x3730 or 0x3631
       Revision Level      = 0x2041

       For detection, it should be safe to assume that if either the
       controller test data or the DSP test data match there's a modem
       present. If both do not match, or more likely a timeout occurs, then
       there's no modem present.
    */

    modemIntSetupTimeoutTimer(MODEM_215MS_TIMEOUT, &modemTimeout, NULL);

    /* Soft reset */
    modemSetBits(REGLOC(0x1A), 0x80);
    modemSetBits(REGLOC(0x1F), 0x1);

    /* It seems to work better if the registers are read two times rather
       than waiting for the two RAM checksums to appear as the manual
       suggests. */

    for (i=0; i<2; i++)
    {
        /* Controller info */
        ctrlInfo[0] = readValue16(REGLOC(0x1D), REGLOC(0x1C));
        ctrlInfo[1] = readValue16(REGLOC(0x1B), REGLOC(0x1A));
        ctrlInfo[2] = readValue16(REGLOC(0x19), REGLOC(0x18));
        ctrlInfo[3] = readValue16(REGLOC(0x17), REGLOC(0x16));
        ctrlInfo[4] = readValue16(REGLOC(0x15), REGLOC(0x14));
        ctrlInfo[5] = readValue16(REGLOC(0x13), REGLOC(0x12));
        ctrlInfo[6] = readValue16(REGLOC(0x11), REGLOC(0x0));

        /* This resets bit 3 in register 0x1E */
        modemRead(REGLOC(0x10));

        modemIntStartTimeoutTimer(); /* Start the timeout counter */
        while (!(modemRead(REGLOC(0x1E)) & 0x8) && !modemTimeout);
        modemIntResetTimeoutTimer(); /* Stop the timeout counter before an
                                        interrupt is generated if it hasn't
                                        done so already */

        if (modemTimeout)
        {
           /* Too late */
           modemIntShutdownTimeoutTimer();
           return 0;
        }
    }

    /* Now for the DSP self test */

    /* DSP info */
    dspInfo[0] = readValue16(REGLOC(0x1B), REGLOC(0x1A));
    dspInfo[1] = readValue16(REGLOC(0x19), REGLOC(0x18));
    dspInfo[2] = readValue16(REGLOC(0x17), REGLOC(0x16));
    dspInfo[3] = readValue16(REGLOC(0x15), REGLOC(0x14));
    dspInfo[4] = readValue16(REGLOC(0x13), REGLOC(0x12));
    dspInfo[5] = readValue16(REGLOC(0x11), REGLOC(0x0));

    /* Wait for a bit */
    modemIntStartTimeoutTimer(); /* Start the timeout counter. It should have been
                                    reset at this point so it starts counting
                                    from zero not where it was stopped
                                    last. */
    while ((modemRead(REGLOC(0x1F)) & 0x1) && !modemTimeout);
    modemIntResetTimeoutTimer();
    timer_spin_sleep(10); /* Wait for 10ms before accessing the MDP again */

    modemIntShutdownTimeoutTimer();

    if (modemTimeout)
    {
       /* No modem, I guess. It timed out, so that might mean something. */
       return 0;
    }

    if (verifyControllerData(ctrlInfo) || verifyDSPData(dspInfo))
       return 1; /* Modem detected */

    /* No modem detected */
    return 0;
}

int modem_init(void)
{
    if (modemCfg.inited)
       return 1;

    modemQuickReset();

    if (!modemSelfTest())
       return 0;

    atexit(modem_shutdown);

    modemDataSetupBuffers();

    modemIntInit();
    modem_reset();

    modemCfg.inited = 1;

    return 1;
}

void modem_shutdown(void)
{
     if (!modemCfg.inited)
        return;

     modemQuickReset();
     modemDataDestroyBuffers();

     modemCfg.inited = 0;
}

void modemQuickReset(void)
{
     /* This zeroes out all of the modem's registers */
     modemWrite(G2_8BP_RST, 0);

     timer_spin_sleep(25); /* A slight delay just to be safe */

     /* This sets the modem's registers to their default settings */
     modemWrite(G2_8BP_RST, 1);

     /* Wait for a little while so the modem has time to reset itself
        completely */
     timer_spin_sleep(150);
}

void modemConfigurationReset(void)
{
     /* Reset the configuration */
     modemCfg.state             = MODEM_MODE_NULL;
     modemCfg.actual.connecting = 0;
     modemCfg.actual.connected  = 0;
     modemCfg.lockData          = 1;

     /* Configure modem interrupt events */
     modemIntConfigModem();
}

void modem_reset(void)
{
     modemQuickReset();
     modemConfigurationReset();
}

/* Changes modes of operation for the modem */
int modem_set_mode(int mode, mspeed_t speed)
{
    if (mode != MODEM_MODE_REMOTE && mode != MODEM_MODE_DIRECT &&
        mode != MODEM_MODE_ANSWER)
       return 0;

    modem_reset();

    /* Disable the tone detectors (TONEA, TONEB, and TONEC) by default */
    modemClearBits(REGLOC(0x2), 0x80);

    if (mode != MODEM_MODE_DIRECT)
    {
       /* The other two modes need to start off with RA (Relay A) not active.
          Make sure it's disabled. */
       if (modemRead(REGLOC(0x7)) & 0x2)
          modemClearBits(REGLOC(0x7), 0x2);
    }

    modemClearBits(REGLOC(0x13), 0xC);
    modemClearBits(REGLOC(0x8), 0x1); /* Disable RTS */

    /* Disable the HDLC data transmission protocol */
    modemClearBits(REGLOC(0x6), 0x10);

    /* Enable the transmitter FIFO */
    modemSetBits(REGLOC(0x4), 0x10);

    /* Set the character size to 8 bits */
    modemSetBits(REGLOC(0x6), 0x3);

    /* Disable parity */
    modemClearBits(REGLOC(0x6), 0x8);

    /* Use one stop bit */
    modemClearBits(REGLOC(0x6), 0x4);

    /* Set the ASYN (ASYNC) bit */
    modemSetBits(REGLOC(0x8), 0x80);

    /* Turn Transmitter Parallel Data Mode on */
    modemSetBits(REGLOC(0x8), 0x40);

    switch (mode)
    {
           case MODEM_MODE_REMOTE:
                /* Put the modem into dialing mode, don't open the line */
                /* Disable the DATA bit so that the hardware interrupts will
                   work as expected. It also doesn't hurt to clear the DTR
                   bit. */
                modemClearBits(REGLOC(0x9), 0x5);

                /* Set the dialing mode */
                modemWrite(REGLOC(0x12), 0x81);

                /* Notify the modem that the configuration has changed */
                modemSetBits(REGLOC(0x1F), 0x1);
           break;

           case MODEM_MODE_DIRECT:
                modemClearBits(REGLOC(0x9), 0x5);
                modemWrite(REGLOC(0x12), 0x81);
                modemSetBits(REGLOC(0x9), 0x10); /* Originate mode */
                modemSetBits(REGLOC(0x1F), 0x1);
                modemSetBits(REGLOC(0x7), 0x2); /* Start listening to the
                                                   line */
           break;

           case MODEM_MODE_ANSWER:
                modemSetBits(REGLOC(0x1F), 0x1);
           break;
    }

    modemCfg.state    = (unsigned char)mode;
    modemCfg.protocol = MODEM_SPEED_GET_PROTOCOL(speed);
    modemCfg.speed    = MODEM_SPEED_GET_SPEED(speed);

    modemIntSetHandler(modemCfg.protocol, mode);

    return 1;
}

void modem_disconnect(void)
{
     if (!modemCfg.actual.connected)
        return;

     /* Any disconnection attempt will abort and forcefully terminate the
        connection if nothing happens after 5 seconds of starting to attempt
        a disconnection */

     modemTimeout = 0;

     modemIntSetupTimeoutTimer(1, NULL, modemTimeoutIncCallback);
     modemIntStartTimeoutTimer();

     /* 0Bh:1 is DISDET
        09h:2 is DATA
        09h:0 is DTR */

     switch (modemCfg.protocol)
     {
            case MODEM_PROTOCOL_V32:
            case MODEM_PROTOCOL_V32BIS:
                 /* In v.32 mode, the remote modem will detect a cleardown
                    sequence and both modems will drop the carrier at the
                    end */
                 modemWrite(REGLOC(0x12),
                            modemCleardownCodes[MODEM_PROTOCOL_V32]);
                 modemSetBits(REGLOC(0x15), 0x4); /* Set RREN */

                 /* Wait for a disconnection or a timeout */
                 while (__isLessThan(modemTimeout, 5) &&
                        (modemRead(REGLOC(0xF)) & 0x80));

                 modemClearBits(REGLOC(0x9), 0x5); /* Reset DTR and DATA */
                 modemSetBits(REGLOC(0x1F), 0x1);  /* Set NEWC */
            break;

            case MODEM_PROTOCOL_V34:
                 /* In v.34 mode, the MDP sets ABCODE to 0x96 when it detects
                    a cleardown sequence */
                 modemWrite(REGLOC(0x12),
                            modemCleardownCodes[MODEM_PROTOCOL_V34]);
                 modemSetBits(REGLOC(0x15), 0x4); /* Set RREN */

                 while (__isLessThan(modemTimeout, 5) &&
                        (modemRead(REGLOC(0xF)) & 0x80) &&
                        modemRead(REGLOC(0x14)) != 0x96);

                 modemClearBits(REGLOC(0x9), 0x5); /* Reset DTR and DATA */
                 modemSetBits(REGLOC(0x1F), 0x1);  /* Set NEWC */
            break;

            default:
              modemClearBits(REGLOC(0x9), 0x5); /* Reset DTR and DATA */
              /* Wait for 2 seconds just because */
              while (__isLessThan(modemTimeout, 2));
            break;
     }

     modemIntResetTimeoutTimer();
     modemIntShutdownTimeoutTimer();

     /* Close the line */
     modemClearBits(REGLOC(0x7), 0x2);

     /* Set the default interrupt handler */
     modemIntClearHandler();

     /* The modem's not connected anymore */
     modemCfg.actual.connecting = modemCfg.actual.connected = 0;

     /* Not doing anything either */
     modemCfg.state = MODEM_STATE_NULL;
}

/* For internal use only */
void modemEstablishConnection(void)
{
     unsigned char mSpeedConfig = 0;

     if (modemCfg.protocol != MODEM_PROTOCOL_V34)
     {
        mSpeedConfig = modemSpeedConfig[modemCfg.protocol][modemCfg.speed];
        assert(mSpeedConfig != 0);
     } else
        mSpeedConfig = 0xAA; /* Establish a connection using a v.8
                                handshake */

     /* Set the connection mode first */
     modemWrite(REGLOC(0x12), mSpeedConfig);

     /* Set the new configuration */
     modemSetBits(REGLOC(0x1F), 0x1);

     /* Please leave the transmitter FIFO extension disabled. It really
        messes up interrupts if they're enabled. */
     dspClearBits8(MAKE_DSP_ADDR(0x702), 0x1);

     /* Note that in all modes of operation RTS will be turned on as soon
        as DTR is set. This is allowed according to the hardware documents,
        and it makes life easier. */

     /* Set the DTR bit to establish a connection */
     if (modemCfg.protocol != MODEM_PROTOCOL_V32 &&
         modemCfg.protocol != MODEM_PROTOCOL_V32BIS)
     {
        modemSetBits(REGLOC(0x9), 0x1 | 0x4); /* Set DTR and DATA */
        modemSetBits(REGLOC(0x8), 0x1);       /* Set RTS */
     } else
     {
        /* V.32/V.32 bis protocol has special requirements */
        modemSetBits(REGLOC(0x9), 0x1); /* Set DTR but not DATA */
        /* Wait until DATA is set before setting RTS just to be safe */
     }
}

int dspWrite8(unsigned char meaddl, unsigned char meaddh,
              unsigned char medal)
{
    unsigned char data;

    /* Set the MEMW bit. Tell the DSP that data will be written. */
    modemSetBits(REGLOC(0x1D), 0x20);

    /* Read register 0x1D, and then modify its data so that the last 5 bits
       of the memory access address are set properly, then write it back. */
    data = modemRead(REGLOC(0x1D)) & ~0x4F; /* Clear bit 6 and bits 0-3 */

    /* Set bit 6 and bits 0-3 based on the value of meaddh */
    data |= ((meaddh & 0x10) << 2) | (meaddh & 0xF);

    /* Write data back to register 0x1D */
    modemWrite(REGLOC(0x1D), data);

    /* Write the first 8 bits of the DSP RAM address */
    modemWrite(REGLOC(0x1C), meaddl);

    /* Write the data that will be written to the specified address into
       MEDAL */
    modemWrite(REGLOC(0x18), medal);

    /* Set MEMACC. This tells the DSP that the data is ready to be written */
    modemSetBits(REGLOC(0x1D), 0x80);

    /* Put some sort of timeout here instead */
    while (modemRead(REGLOC(0x1D)) & 0x80);

    /* Clear MEMW now because only 8 bits of data is being written */
    modemClearBits(REGLOC(0x1D), 0x20);

    return 1;
}

int dspWrite16(unsigned char meaddl, unsigned char meaddh,
               unsigned short medal)
{
    unsigned char data;

    /* Set the MEMW bit. Tell the DSP that data will be written. */
    modemSetBits(REGLOC(0x1D), 0x20);

    /* Read register 0x1D, and then modify its data so that the last 5 bits
       of the memory access address are set properly, then write it back. */
    data = modemRead(REGLOC(0x1D)) & ~0x4F; /* Clear bit 6 and bits 0-3 */

    /* Set bit 6 and bits 0-3 based on the value of meaddh */
    data |= ((meaddh & 0x10) << 2) | (meaddh & 0xF);

    /* Write data back to register 0x1D */
    modemWrite(REGLOC(0x1D), data);

    /* Write the first 8 bits of the DSP RAM address */
    modemWrite(REGLOC(0x1C), meaddl);

    /* Write the first 8-bits of data into MEDAL */
    modemWrite(REGLOC(0x18), medal & 0xFF);

    /* Write the last 8-bits of data into MEDAM */
    modemWrite(REGLOC(0x19), medal >> 8);

    /* Set MEMACC. This tells the DSP that the data is ready to be written */
    modemSetBits(REGLOC(0x1D), 0x80);

    /* Wait for the write to complete */
    while (modemRead(REGLOC(0x1D)) & 0x80);

    /* Clear MEMW to tell the MDP that no more data is to be written */
    modemClearBits(REGLOC(0x1D), 0x20);

    return 1;
}

int dspWrite16x2(unsigned char meaddl1, unsigned char meaddh1,
                 unsigned char meaddl2, unsigned char meaddh2,
                 unsigned short medal)
{
    unsigned char data;

    /************************************
     * Write the first byte into memory *
     ************************************/

    /* Set the MEMW bit. Tell the DSP that data will be written. */
    modemSetBits(REGLOC(0x1D), 0x20);

    /* Read register 0x1D, and then modify its data so that the last 5 bits
       of the memory access address are set properly, then write it back. */
    data = modemRead(REGLOC(0x1D)) & ~0x4F; /* Clear bit 6 and bits 0-3 */

    /* Set bit 6 and bits 0-3 based on the value of meaddh1 */
    data |= ((meaddh1 & 0x10) << 2) | (meaddh1 & 0xF);

    /* Write data back to register 0x1D */
    modemWrite(REGLOC(0x1D), data);

    /* Write the first 8 bits of the DSP RAM address */
    modemWrite(REGLOC(0x1C), meaddl1);

    /* Write the data that will be written to the specified address into
       MEDAL */
    modemWrite(REGLOC(0x18), medal & 0xFF);

    /* Set MEMACC. This tells the DSP that the data is ready to be written */
    modemSetBits(REGLOC(0x1D), 0x80);

    /* Put some sort of timeout here instead */
    while (modemRead(REGLOC(0x1D)) & 0x80);

    /*************************************
     * Write the second byte into memory *
     *************************************/

    /* Set the MEMW bit. Tell the DSP that data will be written. */
    modemSetBits(REGLOC(0x1D), 0x20);

    /* Read register 0x1D, and then modify its data so that the last 5 bits
       of the memory access address are set properly, then write it back. */
    data = modemRead(REGLOC(0x1D)) & ~0x4F; /* Clear bit 6 and bits 0-3 */

    /* Set bit 6 and bits 0-3 based on the value of meaddh2 */
    data |= ((meaddh2 & 0x10) << 2) | (meaddh2 & 0xF);

    /* Write data back to register 0x1D */
    modemWrite(REGLOC(0x1D), data);

    /* Write the first 8 bits of the DSP RAM address */
    modemWrite(REGLOC(0x1C), meaddl2);

    /* Write the data that will be written to the specified address into
       MEDAL */
    modemWrite(REGLOC(0x18), medal >> 8);

    /* Set MEMACC. This tells the DSP that the data is ready to be written */
    modemSetBits(REGLOC(0x1D), 0x80);

    while (modemRead(REGLOC(0x1D)) & 0x80);

    /* Clear MEMW because the 2 bytes of data have been written */
    modemClearBits(REGLOC(0x1D), 0x20);

    return 1;
}

unsigned char dspRead8(unsigned char meaddl, unsigned char meaddh)
{
    unsigned char data;

    /* Clear the MEMW bit since data is being read instead of written */
    modemClearBits(REGLOC(0x1D), 0x20);

    /* Read register 0x1D, and then modify its data so that the last 5 bits
       of the memory access address are set properly, then write it back. */
    data = modemRead(REGLOC(0x1D)) & ~0x4F; /* Clear bit 6 and bits 0-3 */

    /* Set bit 6 and bits 0-3 based on the value of meaddh */
    data |= ((meaddh & 0x10) << 2) | (meaddh & 0xF);

    /* Write data back to register 0x1D */
    modemWrite(REGLOC(0x1D), data);

    /* Write the first 8 bits of the memory address in MEADDL */
    modemWrite(REGLOC(0x1C), meaddl);

    /* Set the MEACC bit so that the DSP reads the specified address */
    modemSetBits(REGLOC(0x1D), 0x80);

    /* Wait for the MEACC bit to be cleared */
    /* Put a timeout or something here instead */
    while (modemRead(REGLOC(0x1D)) & 0x80);

    /* Return the data that's in the MEDAL register */
    return modemRead(REGLOC(0x18));
}

/* Does a 16-bit read from a single address using method 4. This is the same
   as dspRead8, but is doesn't ignore the MEDAM register. */
unsigned short dspRead16(unsigned char meaddl, unsigned char meaddh)
{
    unsigned short value;

    value = (unsigned short)dspRead8(meaddl, meaddh);

    /* Read the MEDAM register, it contains the last 8 bits of the word */
    value |= ((unsigned short)modemRead(REGLOC(0x19))) << 8;

    return value;
}

/* Does two 8-bit reads from two different locations in DSP RAM and combines
   the two values into one 16-bit value. The first address is the low byte of
   the word and the second address is the high byte of the word. */
unsigned short dspRead16x2(unsigned char meaddl1, unsigned char meaddh1,
                           unsigned char meaddl2, unsigned char meaddh2)
{
    unsigned short value;

    value = (unsigned short)dspRead8(meaddl1, meaddh1);
    value |= ((unsigned short)dspRead8(meaddl2, meaddh2)) << 8;

    return value;
}

/* Status functions */
int modem_is_connecting(void)
{
    return modemCfg.actual.connecting;
}

int modem_is_connected(void)
{
    return modemCfg.actual.connected;
}

unsigned long modem_get_connection_rate(void)
{
    return modemCfg.actual.speed;
}
