/* KallistiOS ##version##

   mdata.c
   Copyright (C)2002 Nick Kochakian

   Distributed under the terms of the KOS license.
*/

#include <stdlib.h>
#include "mintern.h"

CVSID("$Id: mdata.c,v 1.1 2003/05/23 02:04:42 bardtx Exp $");

/* The number of bytes that will be written or read per function call. It's
   not recommended that you change this. */
#define MODEM_DATA_LIMIT 256

#define MODEM_DEFAULT_SEGMENTS 32
#define MODEM_DEFAULT_SEGBYTES 32

MODEM_SEG_BUFFER *rxBuffer = NULL;
MODEM_SEG_BUFFER *txBuffer = NULL;

unsigned char rxBufferInUse = 0;
unsigned char txBufferInUse = 0;

#define LOCK_RX_BUFFER   rxBufferInUse = 1;
#define UNLOCK_RX_BUFFER rxBufferInUse = 0;
#define LOCK_TX_BUFFER   txBufferInUse = 1;
#define UNLOCK_TX_BUFFER txBufferInUse = 0;

void modemDataSetupBuffers(void)
{
     /* Create segmented FIFO buffers for the incoming and outgoing data.
        These are used as backup when the modem's own FIFO buffers are
        full. The buffer sizes are 32 segments with 32 bytes per segment
        (1024 bytes total.) It should be assumed that they always return
        valid pointers, because the modemSegBufferCreate function will
        cause an assertion to happen if there's a malloc error. */

     if (rxBuffer==NULL)
     {
        rxBuffer      = modemSegBufferCreate(MODEM_DEFAULT_SEGMENTS,
                                             MODEM_DEFAULT_SEGBYTES);
        rxBufferInUse = 0;
     }

     if (txBuffer==NULL)
     {
        txBuffer      = modemSegBufferCreate(MODEM_DEFAULT_SEGMENTS,
                                             MODEM_DEFAULT_SEGBYTES);
        txBufferInUse = 0;
     }
}

void modemDataDestroyBuffers(void)
{
     if (rxBuffer != NULL)
     {
        modemSegBufferDestroy(rxBuffer);
        rxBuffer = NULL;
     }

     if (txBuffer != NULL)
     {
        modemSegBufferDestroy(txBuffer);
        txBuffer = NULL;
     }
}

/* Update the RX buffer (incoming data.) This should be called when the
   modem's RX FIFO is half full or the user is trying to read data and
   the buffer is empty */

void modemDataUpdateRXBuffer(void)
{
     int           i;
     int           maxSpace;
     unsigned char data[16];

     if (rxBufferInUse || !rxBuffer)
        return;

     LOCK_RX_BUFFER

     if (modemSegBufferGetFreeSpace(rxBuffer) > 0)
     {
        i = 0;
        maxSpace = ((modemSegBufferGetFreeSpace(rxBuffer) < 16) ?
                   modemSegBufferGetFreeSpace(rxBuffer) : 16);
        /* 1Eh:0 is RBDF. This bit will be set until the RX FIFO is emptied */
        while ((modemRead(REGLOC(0x1E)) & 0x1) && i < maxSpace)
        {
              data[i] = modemRead(REGLOC(0x0));
              modemRead(REGLOC(0xA));
              i++;
        }

        if (i > 0)
           modemSegBufferWriteData(rxBuffer, data, i);
     }

     UNLOCK_RX_BUFFER
}

/* Update the TX buffer (outgoing data.) This is called only when the modem's
   TX FIFO is empty. If there's any data in the TX buffer, it gets sent to the
   modem. */

void modemDataUpdateTXBuffer(void)
{
     unsigned char data[MODEM_DEFAULT_SEGBYTES];
     int           offset;
     int           dataSize;

     if (txBufferInUse || !txBuffer)
        return;

     LOCK_TX_BUFFER

     if (modemSegBufferGetFreeSpace(txBuffer) > 0)
     {
        /* Read a segment or however much data is left */
        dataSize = modemSegBufferReadData(txBuffer, data,
                                          MODEM_DEFAULT_SEGBYTES);
        offset   = 0;
        while ((modemRead(REGLOC(0xD)) & 0x2) && offset < dataSize)
        {
              modemWrite(REGLOC(0x10), data[offset]);
              offset++;
        }

        /* If there's data that was not sent, then put it back into the
           buffer */
        if (offset < dataSize)
           modemSegBufferWriteData(txBuffer, &data[offset],
                                   dataSize - offset);
     }

     UNLOCK_TX_BUFFER
}

int modem_read_data(unsigned char *data, int size)
{
    int rxBufferSize;
    int bytesRead = 0;

    LOCK_RX_BUFFER

    if (size > MODEM_DATA_LIMIT)
       size = MODEM_DATA_LIMIT;

    rxBufferSize = modemSegBufferGetTotalSpace(rxBuffer) -
                   modemSegBufferGetFreeSpace(rxBuffer);
    if (rxBufferSize > 0)
       bytesRead += modemSegBufferReadData(rxBuffer, data,
                             ((size < rxBufferSize) ? size : rxBufferSize));

    if (bytesRead < size)
    {
       /* Is there data in RX FIFO that's waiting to be read? */
       while ((modemRead(REGLOC(0x1E)) & 0x1) && bytesRead < size)
       {
             data[bytesRead] = modemRead(REGLOC(0x0));
             modemRead(REGLOC(0xA));
             bytesRead++;
       }
    }

    UNLOCK_RX_BUFFER

    return bytesRead;
}

int modem_write_data(unsigned char *data, int size)
{
    int offset = 0;

    /* Try to send some of the data in the TX buffer to the modem */
    if (modemSegBufferGetFreeSpace(txBuffer) > 0)
       modemDataUpdateTXBuffer();

    LOCK_TX_BUFFER

    if (modemSegBufferGetFreeSpace(txBuffer) <= 0)
    {
       /* Send data to the modem first if the TX buffer is empty */
       if (modemRead(REGLOC(0xD)) & 0x2)
       {
          /* Give the modem some data */
          while ((modemRead(REGLOC(0xD)) & 0x2) && offset < size)
          {
                modemWrite(REGLOC(0x10), data[offset]);
                offset++;
          }
       }
    }

    /* If there's remaining data, or the modem's TX FIFO buffer is full,
       put the rest of it into the segmented TX FIFO buffer */
    if (offset < size)
       offset += modemSegBufferWriteData(txBuffer, &data[offset],
                                         size - offset);

    UNLOCK_TX_BUFFER

    return offset;
}

/* If the modem has data waiting to be read a non zero value is returned,
   otherwise zero is returned. */
int modem_has_data(void)
{
    if (modemSegBufferGetFreeSpace(rxBuffer) > 0 ||
        (modemRead(REGLOC(0x1E)) & 0x1))
       return 1;

    return 0;
}
