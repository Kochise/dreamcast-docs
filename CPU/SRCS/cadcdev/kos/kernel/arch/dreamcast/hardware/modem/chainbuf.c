/* KallistiOS ##version##

   chainbuf.c
   Copyright (C)2004 Nick Kochakian

   Distributed under the terms of the KOS license.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "chainbuf.h"

/* Allocates a new chain buffer of length bytes. Length must be
   greater than or equal to 1 */
CHAIN_BUFFER *createChainBuffer(int length)
{
    CHAIN_BUFFER *buffer;

    assert(length >= 1);

    /* A byte is lost in storage because of the way the counters
       work, but trying to correct that problem could additionally
       take up to 4 bytes of memory in addition to the extra byte
       that is being allocated here, so it doesn't seem worth it */
    length++;

    buffer = (CHAIN_BUFFER *)malloc(sizeof(CHAIN_BUFFER));
    assert(buffer);

    memset(buffer, 0, sizeof(CHAIN_BUFFER));

    buffer->length = length;
    buffer->data   = (unsigned char *)malloc(buffer->length);

    assert(buffer->data);

    return buffer;
}

void destroyChainBuffer(CHAIN_BUFFER *buffer)
{
     if (buffer)
     {
        if (buffer->data)
        {
           free(buffer->data);
           buffer->data = NULL;
        }

        free(buffer);
     }
}

void clearChainBuffer(CHAIN_BUFFER *buffer)
{
     if (buffer)
     {
        buffer->start = 0;
        buffer->end   = 0;
        buffer->flags = 0;
     }
}

int getBufferEndOffset(CHAIN_BUFFER *buffer)
{
    return (buffer->end < buffer->start) ?
                (buffer->end + buffer->length) :
                buffer->end;
}

/* Gets the length of the data actually stored does NOT return the
   length member */
int getChainBufferLength(CHAIN_BUFFER *buffer)
{
    if (!buffer)
       return 0;

    return getBufferEndOffset(buffer) - buffer->start;
}

/* Gets the number of bytes that are unused */
int getChainBufferFreeSpace(CHAIN_BUFFER *buffer)
{
    if (!buffer)
       return 0;

    return (buffer->length - 1) - getChainBufferLength(buffer);
}

/* Returns a non-zero value if the chain buffer contains any data */
int chainBufferContainsData(CHAIN_BUFFER *buffer)
{
    if (!buffer)
       return 0;

    return (buffer->flags & CHAIN_BUFFER_CONTAINS_DATA_FLAG) ? 1 : 0;
}

/* To do: Block copying to possibly speed things up.
   Returns a non zero value if the buffer has overflowed */
int writeToChainBuffer(CHAIN_BUFFER *buffer, unsigned char *data,
                       int length)
{
    int notEqual;
    int i;

    assert(length >= 0);

    if (!buffer)
       return 0;

    for (i=0; i<length; i++)
    {
        notEqual = buffer->end != buffer->start;

        buffer->data[buffer->end] = data[i];
        buffer->end = (buffer->end + 1) % buffer->length;

        if (buffer->end==buffer->start && notEqual)
        {
           /* Overflow */
           buffer->start = (buffer->start + 1) % buffer->length;
           buffer->flags |= CHAIN_BUFFER_OVERFLOW_FLAG;
        }
    }

    if (length > 0)
       buffer->flags |= CHAIN_BUFFER_CONTAINS_DATA_FLAG;

    return (buffer->flags & CHAIN_BUFFER_OVERFLOW_FLAG) ? 1 : 0;
}

/* Reads the chain buffer and stores whatever it can into the
   specified destination. Length specifys how many bytes you would
   like to read. The actual number of bytes read is returned.
   The overflow flag is cleared if one or more bytes were actually
   read. */
int readFromChainBuffer(CHAIN_BUFFER *buffer, void *data,
                        int length)
{
    int offset;
    int bytesRead;

    assert(length >= 0);

    if (!buffer)
       return 0;

    if (length > getChainBufferLength(buffer))
       length = getChainBufferLength(buffer);

    bytesRead = length;

    offset = buffer->start;
    while (length > 0)
    {
          *(unsigned char *)data = buffer->data[offset];

          offset = (offset + 1) % buffer->length;
          data = ((unsigned char *)data) + 1;
          length--;
    }

    buffer->start = offset;

    if (bytesRead > 0)
    {
       buffer->flags &= ~CHAIN_BUFFER_OVERFLOW_FLAG;
       if (getChainBufferLength(buffer) <= 0)
          buffer->flags &= ~CHAIN_BUFFER_CONTAINS_DATA_FLAG;
    }

    return bytesRead;
}

/* Returns a non zero value if the buffer has had an overflow */
int chainBufferOverflow(CHAIN_BUFFER *buffer)
{
    if (!buffer)
       return 0;

    return (buffer->flags & CHAIN_BUFFER_OVERFLOW_FLAG) ? 1 : 0;
}
