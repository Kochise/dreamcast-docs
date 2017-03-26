/* KallistiOS ##version##

   msegbuf.h
   Copyright (C)2002 Nick Kochakian

   Distributed under the terms of the KOS license.

   $Id: msegbuf.h,v 1.1 2003/06/19 04:20:59 bardtx Exp $
*/
         

/*
    Segmented FIFO Buffer
*/

#ifndef __MSEGBUF_H
#define __MSEGBUF_H

typedef struct
{
    unsigned char  *data;
    unsigned short dataStart;
    unsigned short dataEnd;
} MODEM_SEGMENT;

typedef struct
{
    unsigned short numSegments;
    unsigned short segmentSize;

    MODEM_SEGMENT **segment;

    struct
    {
      unsigned short segment;
      unsigned short segRead;
      long           freeSpace;
    } current;
} MODEM_SEG_BUFFER;

#define modemSegBufferGetFreeSpace(x)  ((x)->current.freeSpace)
#define modemSegBufferGetTotalSpace(x) ((x)->numSegments * (x)->segmentSize)

MODEM_SEG_BUFFER *modemSegBufferCreate(unsigned short numSegments,
                                       unsigned short segmentSize);
void             modemSegBufferDestroy(MODEM_SEG_BUFFER *segBuffer);
int              modemSegBufferWriteData(MODEM_SEG_BUFFER *segBuffer,
                                         unsigned char *data,
                                         unsigned short dataLength);
int              modemSegBufferReadData(MODEM_SEG_BUFFER *segBuffer,
                                        unsigned char *data,
                                        unsigned short bytesToRead);

#endif
