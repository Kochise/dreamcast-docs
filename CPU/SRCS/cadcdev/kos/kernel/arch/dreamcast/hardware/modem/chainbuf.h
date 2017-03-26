/* KallistiOS ##version##

   chainbuf.h
   Copyright (C)2004 Nick Kochakian

   Distributed under the terms of the KOS license.
*/

#ifndef __CHAINBUF_H
#define __CHAINBUF_H

/* Chain buffer flags */
#define CHAIN_BUFFER_OVERFLOW_FLAG      0x1
#define CHAIN_BUFFER_CONTAINS_DATA_FLAG 0x2

typedef struct
{
    int           length;     /* Number of bytes allocated to data */
    int           start, end; /* Start and end indices */
    unsigned char flags;
    unsigned char *data;
} CHAIN_BUFFER;

/* From chainbuf.c */
CHAIN_BUFFER *createChainBuffer(int length);
void         destroyChainBuffer(CHAIN_BUFFER *buffer);
void         clearChainBuffer(CHAIN_BUFFER *buffer);
int          getChainBufferLength(CHAIN_BUFFER *buffer);
int          getChainBufferFreeSpace(CHAIN_BUFFER *buffer);
int          chainBufferContainsData(CHAIN_BUFFER *buffer);
int          writeToChainBuffer(CHAIN_BUFFER *buffer, unsigned char *data,
                                int length);
int          readFromChainBuffer(CHAIN_BUFFER *buffer, void *data,
                                 int length);
int          chainBufferOverflow(CHAIN_BUFFER *buffer);

#endif
