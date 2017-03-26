/* KallistiOS ##version##

   msegbuf.c
   Copyright (C)2002 Nick Kochakian

   Distributed under the terms of the KOS license.
*/

/*
    Segmented FIFO Buffer
*/

#include <stdio.h>
#include <stdlib.h>
#include "msegbuf.h"

CVSID("$Id: msegbuf.c,v 1.1 2003/05/23 02:04:42 bardtx Exp $");

int modemSegBufferQuickReorder(MODEM_SEG_BUFFER *segBuffer);
int modemSegBufferFullReorder(MODEM_SEG_BUFFER *segBuffer);

MODEM_SEG_BUFFER *modemSegBufferCreate(unsigned short numSegments,
                                       unsigned short segmentSize)
{
    MODEM_SEG_BUFFER *segBuffer = NULL;
    MODEM_SEGMENT    *segment   = NULL;
    int              i;

    assert(numSegments > 0);
    assert(segmentSize > 0);

    segBuffer = (MODEM_SEG_BUFFER *)malloc(sizeof(MODEM_SEG_BUFFER));
    assert(segBuffer != NULL);

    segBuffer->numSegments = numSegments;
    segBuffer->segmentSize = segmentSize;

    segBuffer->current.segment   = 0;
    segBuffer->current.segRead   = 0;
    segBuffer->current.freeSpace = segBuffer->numSegments *
                                   segBuffer->segmentSize;

    segBuffer->segment = (MODEM_SEGMENT **)malloc(numSegments *
                                                  sizeof(unsigned long));
    assert(segBuffer->segment != NULL);

    for (i=0; i<(int)numSegments; i++)
    {
        segment = (MODEM_SEGMENT *)malloc(sizeof(MODEM_SEGMENT));
        assert(segment != NULL);

        segment->data = (unsigned char *)malloc(segmentSize);
        assert(segment->data != NULL);

        segment->dataStart = 0;
        segment->dataEnd   = 0;

        segBuffer->segment[i] = segment;
    }

    return segBuffer;
}

void modemSegBufferDestroy(MODEM_SEG_BUFFER *segBuffer)
{
     int i;

     if (segBuffer != NULL)
     {
        if (segBuffer->segment != NULL)
        {
           for (i=0; i<(int)segBuffer->numSegments; i++)
           {
               if (segBuffer->segment[i] != NULL)
               {
                  if (segBuffer->segment[i]->data != NULL)
                  {
                     free(segBuffer->segment[i]->data);
                     segBuffer->segment[i]->data = NULL;
                  }

                  free(segBuffer->segment[i]);
                  segBuffer->segment[i] = NULL;
               }
           }

           free(segBuffer->segment);
           segBuffer->segment = NULL;
        }

        free(segBuffer);
     }
}

/* Returns the number of bytes that were actually saved. Returns 0
   when an error occurs. */
int modemSegBufferWriteData(MODEM_SEG_BUFFER *segBuffer,
                            unsigned char *data,
                            unsigned short dataLength)
{
    int           offset = 0;
    int           hasSpace;
    MODEM_SEGMENT *segment;

    while (offset < dataLength)
    {
          segment = segBuffer->segment[segBuffer->current.segment];
          if (segment->dataEnd >= segBuffer->segmentSize)
          {
             /* This segment is out of space! Check to see if there
                are any segments left. */
             if (segBuffer->current.segment + 1 <
                 segBuffer->numSegments)
                segBuffer->current.segment++;
                else
                {
                  hasSpace = 0;
                  if (!modemSegBufferQuickReorder(segBuffer))
                  {
                     if (modemSegBufferFullReorder(segBuffer))
                        hasSpace = 1;
                  } else
                     hasSpace = 1;

                  if (!hasSpace)
                  {
                     segBuffer->current.freeSpace -= offset;
                     return offset;
                  }
                }
          } else
          {
             /* Copy data into the segment */
             while (offset < dataLength &&
                    segment->dataEnd < segBuffer->segmentSize)
             {
                   segment->data[segment->dataEnd] = data[offset];

                   offset++;
                   segment->dataEnd++;
             }
          }
    }

    segBuffer->current.freeSpace -= offset;
    return offset;
}

int modemSegBufferReadData(MODEM_SEG_BUFFER *segBuffer,
                           unsigned char *data,
                           unsigned short bytesToRead)
{
    MODEM_SEGMENT *segment;
    int           offset = 0;

    while (offset < bytesToRead)
    {
          segment = segBuffer->segment[segBuffer->current.segRead];
          if (segment->dataStart==segment->dataEnd)
          {
             /* There's no more data left in this segment, reset
                the data start and end positions and try to read
                from the next one. */
             segment->dataStart = segment->dataEnd = 0;

             if (segBuffer->current.segRead + 1 <
                 segBuffer->numSegments)
                segBuffer->current.segRead++;
                else
                {
                  /* The read position is in an empty segment, which
                     is also the last segment. Reset the read and
                     write positions. */
                  segBuffer->current.segment = 0;
                  segBuffer->current.segRead = 0;

                  segBuffer->current.freeSpace += offset;
                  return offset; /* There's no more data left! */
                }
          } else
          {
             while (offset < bytesToRead &&
                    segment->dataStart < segment->dataEnd)
             {
                   data[offset] = segment->data[segment->dataStart];
                   offset++;
                   segment->dataStart++;
             }
          }
    }

    /* If the read position is in an empty segment, move it to the
       next segment. */
    if (segBuffer->segment[segBuffer->current.segRead]->dataStart==
        segBuffer->segment[segBuffer->current.segRead]->dataEnd)
    {
       /* Reset the segment's data start and end positions */
       segBuffer->segment[segBuffer->current.segRead]->dataStart = 0;
       segBuffer->segment[segBuffer->current.segRead]->dataEnd   = 0;

       /* Otherwise if it's in the last segment, then reset the read
          and write positions */
       if (segBuffer->current.segRead >= segBuffer->numSegments - 1)
       {
          segBuffer->current.segRead = 0;
          segBuffer->current.segment = 0;
       } else
          segBuffer->current.segRead++;
    }

    segBuffer->current.freeSpace += offset;
    return offset;
}

/* Returns non zero if the segments could be quickly reordered or
   zero if a quick reordering wasn't possible. */
int modemSegBufferQuickReorder(MODEM_SEG_BUFFER *segBuffer)
{
    int           emptySegments = 1;
    int           startIndex, endIndex;
    int           i;
    int           flag     = 0;
    MODEM_SEGMENT *segTemp = NULL;

    /* If the read position is in the first segment and the first
       segment is empty, then that means that the entire buffer
       is empty, so reordering is not neccessary. */
    if (!segBuffer->current.segRead &&
        segBuffer->segment[0]->dataStart==
        segBuffer->segment[0]->dataEnd)
       return 1;

    startIndex = 0;
    endIndex   = segBuffer->numSegments;

    while (emptySegments && startIndex != endIndex)
    {
          /* Find an empty segment */
          emptySegments = 0;
          for (i=startIndex; i<endIndex && !emptySegments; i++)
          {
              if (segBuffer->segment[i]->dataStart==
                  segBuffer->segment[i]->dataEnd)
              {
                 segTemp       = segBuffer->segment[i];
                 startIndex    = i;
                 emptySegments = 1;

                 /* Adjust the segment write location */
                 if (segBuffer->current.segment==i)
                    segBuffer->current.segment = endIndex - 1;
                 /* The read position can't be in an empty segment! */
                 #ifdef _DEBUG
                 assert(segBuffer->current.segRead != i);
                 #endif
              }
          }

          if (emptySegments)
          {
             /* Push the segments down, and put the stored segment
                at the end of the segment list */
             for (i=startIndex; i<endIndex - 1; i++)
                 segBuffer->segment[i] = segBuffer->segment[i + 1];

             /* Adjust the segment read/write locations */
             if (segBuffer->current.segment >= startIndex &&
                 segBuffer->current.segment < endIndex)
                segBuffer->current.segment--;
             if (segBuffer->current.segRead >= startIndex &&
                 segBuffer->current.segRead < endIndex)
                segBuffer->current.segRead--;

             segBuffer->segment[endIndex - 1] = segTemp;
             endIndex--;
             flag = 1;
          }
    }

    return flag;
}

/* Fully reorders the segments so that any unused space will be
   accessable the next time a write is attempted. It's assumed that
   the quick reorder has failed and this is being called because of
   that. */
int modemSegBufferFullReorder(MODEM_SEG_BUFFER *segBuffer)
{
    int           i;
    int           flag         = 0;
    int           firstSegment = -1;
    int           curSegment   = 0;
    MODEM_SEGMENT *segWrite;
    MODEM_SEGMENT *segRead;
    int           readOffset;
    int           writeOffset;

    /* Find the first non empty segment */
    for (i=0; i<segBuffer->numSegments && firstSegment < 0; i++)
    {
        if (segBuffer->segment[i]->dataEnd > 0)
           firstSegment = i;
    }

    if (firstSegment < 0)
       return 1; /* Every segment is empty */
       else if (firstSegment==0 &&
                segBuffer->segment[0]->dataStart==0)
               return 0; /* This buffer either cannot be reordered or
                            does not need to be reordered */

    curSegment  = firstSegment;
    i           = 0;
    segRead     = segBuffer->segment[curSegment];
    segWrite    = segBuffer->segment[0];
    readOffset  = segRead->dataStart;
    writeOffset = 0;
    while (!flag)
    {
          while (writeOffset < segBuffer->segmentSize &&
                 readOffset < segRead->dataEnd)
          {
                segWrite->data[writeOffset] =
                segRead->data[readOffset];

                writeOffset++;
                readOffset++;
          }

          /* Done reading this segment. Move to the next one. Stop
             if the end has been reached or the next segment is
             empty. */
          if (readOffset >= segRead->dataEnd)
          {
             /* Setting these values doesn't affect the reordering
                process even if the read and write segments are the
                same */
             segRead->dataStart = segRead->dataEnd = 0;

             if (curSegment + 1 >= segBuffer->numSegments)
                flag = 1;
                else
                {
                  curSegment++;
                  segRead = segBuffer->segment[curSegment];

                  /* This is an empty segment */
                  if (!segRead->dataEnd)
                     flag = 1;
                     else
                     readOffset = segRead->dataStart;
                }
          }

          if (flag ||
              (!flag && writeOffset >= segBuffer->segmentSize))
          {
             /* Set the data starting and ending locations of the
                write segment to their correct positions */
             segWrite->dataStart = 0;
             segWrite->dataEnd   = writeOffset;
          }

          if (!flag)
          {
             /* Done writing to this segment. Move to the next one.
                The fact that flag is not set means that moving to the
                next segment will not go outside the array of segment
                pointers. */
             if (writeOffset >= segBuffer->segmentSize)
             {
                i++;
                writeOffset = 0;
                segWrite    = segBuffer->segment[i];
             }
          }
    }

    /* Set the segment read and write positions based on the reordered
       data */
    segBuffer->current.segRead = 0;
    segBuffer->current.segment = i;

    return 1;
}
