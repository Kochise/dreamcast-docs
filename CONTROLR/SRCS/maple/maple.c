
/*
 * Simple Maple Bus implementation
 *
 * NOTE: The functions here are designed for simplicity, not
 *       efficiency.  For good performance, requests should be
 *       parallelized (each DMA burst can contain one message to
 *       each device), and interrupts should be used to detect
 *       DMA completion rather than the busy-polling shown here.
 */

#include "maple.h"

#define MAPLE(x) (*(volatile unsigned long *)(0xa05f6c00+(x)))


/*
 * Initialize the Maple Bus to reasonable defaults.
 * No end-DMA interrupts are registered.
 */
void maple_init()
{
  /* Reset hardware */
  MAPLE(0x8c) = 0x6155404f;
  MAPLE(0x10) = 0;
  /* Select 2Mbps bitrate, and a timeout of 50000 */
  MAPLE(0x80) = (50000<<16)|0;
  /* Enable bus */
  MAPLE(0x14) = 1;
}


/*
 * Wait for Maple DMA to finish
 */
void maple_wait_dma()
{
  while(MAPLE(0x18) & 1)
    ;
}


/* Since we're only going to do one request at a time in this
   simple design, the buffer need only to be large enough to
   hold one maximal request frame (1024 bytes), one maximal
   response frame (1024 bytes), and the two control longwords
   for the single transfer.  In addition, DMA addresses need
   to be aligned to a 32 byte boundary, so we add some padding
   to account for extra aligning.                              */

static unsigned char dmabuffer[ 1024 + 1024 + 4 + 4 + 32 ];


/*
 * Send a command to a device and wait for the response.
 *
 * port    - controller port (0-3)
 * unit    - unit number on port (0 = main unit, 1-5 = sub units)
 * cmd     - command number
 * datalen - number of longwords of parameter data
 * data    - parameter data (NB: big endian!)
 *
 */
void *maple_docmd(int port, int unit, int cmd, int datalen, void *data)
{
  unsigned long *sendbuf, *recvbuf;
  int to, from;

  port &= 3;

  /* Compute sender and recipient address */
  from = port << 6;
  to = (port << 6) | (unit>0? ((1<<(unit-1))&0x1f) : 0x20);

  /* Max data length = 255 longs = 1020 bytes */
  if(datalen > 255)
    datalen = 255;
  else if(datalen < 0)
    datalen = 0;

  /* Allocate a 1024 byte receieve buffer at the beginning of
     dmabuffer, with proper alignment.  Also mark the buffer as
     uncacheable.                                               */
  recvbuf =
    (unsigned long *) (((((unsigned long)dmabuffer)+31) & ~31) | 0xa0000000);

  /* Place the send buffer right after the receive buffer.  This
     automatically gives proper alignment and uncacheability.    */
  sendbuf =
    (unsigned long *) (((unsigned char *)recvbuf) + 1024);

  /* Make sure no DMA operation is currently in progress */
  maple_wait_dma();

  /* Set hardware DMA pointer to beginning of send buffer */
  MAPLE(0x04) = ((unsigned long)sendbuf) & 0xfffffff;

  /* Setup DMA data.  Each message consists of two control words followed
     by the request frame.  The first control word determines the port,
     the length of the request transmission, and a flag bit marking the
     last message in the burst.  The second control word specifies the
     address where the response frame will be stored.  If no response is
     received within the timeout period, -1 will be written to this address. */

  /* Here we know only one frame should be send and received, so
     the final message control bit will always be set...          */
  *sendbuf++ = datalen | (port << 16) | 0x80000000;

  /* Write address to receive buffer where the response frame should be put */
  *sendbuf++ = ((unsigned long)recvbuf) & 0xfffffff;

  /* Create the frame header.  The fields are assembled "backwards"
     because of the Maple Bus big-endianness.                       */
  *sendbuf++ = (cmd & 0xff) | (to << 8) | (from << 16) | (datalen << 24);

  /* Copy parameter data, if any */
  if(datalen > 0) {
    unsigned long *param = data;
    int i;
    for(i=0; i<datalen; i++)
      *sendbuf++ = *param++;
  }

  /* Frame is finished, and DMA list is terminated with the flag bit.
     Time to activate the DMA channel.                                */
  MAPLE(0x18) = 1;

  /* Wait for the complete cycle to finish, so that the response
     buffer is valid.                                            */
  maple_wait_dma();

  /* Return a pointer to the response frame */
  return recvbuf;
}
