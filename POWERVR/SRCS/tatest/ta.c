#include "ta.h"


/* Functions to send a list (the basic command unit of the TA) to the
   command list compiler.  ta_commit_list sends a 32-byte list, and
   ta_commit_list2 sends a 64-byte list.                              */

#define QACR0 (*(volatile unsigned int *)(void *)0xff000038)
#define QACR1 (*(volatile unsigned int *)(void *)0xff00003c)

void ta_commit_list(void *src)
{
  unsigned int *s = (unsigned int *)src;
  unsigned int *d = (unsigned int *)0xe0000000;
  QACR0 = ((0xb0000000>>26)<<2)&0x1c;
  d[0] = *s++;
  d[1] = *s++;
  d[2] = *s++;
  d[3] = *s++;
  d[4] = *s++;
  d[5] = *s++;
  d[6] = *s++;
  d[7] = *s++;
  asm("pref @%0" : : "r" (d));
}

void ta_commit_list2(void *src)
{
  unsigned int *s = (unsigned int *)src;
  unsigned int *d = (unsigned int *)0xe0000000;
  QACR0 = ((0xb0000000>>26)<<2)&0x1c;
  QACR1 = ((0xb0000000>>26)<<2)&0x1c;
  d[0] = *s++;
  d[1] = *s++;
  d[2] = *s++;
  d[3] = *s++;
  d[4] = *s++;
  d[5] = *s++;
  d[6] = *s++;
  d[7] = *s++;
  asm("pref @%0" : : "r" (d));
  d[8] = *s++;
  d[9] = *s++;
  d[10] = *s++;
  d[11] = *s++;
  d[12] = *s++;
  d[13] = *s++;
  d[14] = *s++;
  d[15] = *s++;
  asm("pref @%0" : : "r" (d+8));
}


/* Send the special end of list command */

void ta_commit_end()
{
  unsigned int words[8] = { 0 };
  ta_commit_list(words);
}


/* Set up buffers and descriptors for a tilespace */

void *ta_create_tile_descriptors(void *ptr, void *buf, int w, int h)
{
  /* each tile desriptor is 6 words.  In addition, there's a 24 word header */
  /* so, there are 24+6*w*h words stored at ptr.                            */

  /* each tile uses 64 bytes of buffer space.  So buf must point to */
  /* 64*w*h bytes of data                                           */

  int x, y;
  unsigned int *vr = ptr;
  unsigned int bf = ((unsigned int)buf)&0x007fffff;
  unsigned int strbase = (((unsigned int)ptr)&0x007fffff)|0x80000000;

  for (x=0; x<18; x++)
    *vr++ = 0;
  *vr++ = 0x10000000;
  *vr++ = 0x80000000;
  *vr++ = 0x80000000;
  *vr++ = 0x80000000;
  *vr++ = 0x80000000;
  *vr++ = 0x80000000;
  for (x=0; x<w; x++) {
    for (y=0; y<h; y++) {
      *vr++ = (y << 8) | (x << 2);
      *vr++ = bf+((x+y*w)<<6);
      *vr++ = strbase;
      *vr++ = strbase;
      *vr++ = strbase;
      *vr++ = strbase;
    }
  }
  vr[-6] |= 0x80000000;

  return ((char *)ptr)+72; /* pass this value to ta_begin_render() */
}


/* Tell the command list compiler where to store the command list,
   and which tilespace to use                                      */

unsigned int ta_set_target(void *cmdlist, void *tilebuf, int w, int h)
{
  volatile unsigned int *regs = (volatile unsigned int *)0xa05f8000;
  unsigned int cmdl = ((unsigned int)cmdlist)&0x007fffff;
  unsigned int tbuf = ((unsigned int)tilebuf)&0x007fffff;

  regs[0x008/4] = 1;		/* Reset TA */
  regs[0x008/4] = 0;
  regs[0x124/4] = tbuf;
  regs[0x12c/4] = 0;
  regs[0x128/4] = cmdl;
  regs[0x130/4] = 0;
  regs[0x13c/4] = ((h-1)<<16)|(w-1);
  regs[0x164/4] = tbuf;
  regs[0x140/4] = 0x00100002;
  regs[0x144/4] = 0x80000000;	/* Confirm settings */

  return regs[0x144/4];
}


/* Wait for a previous render pass to compilete */

void ta_wait_render()
{
  volatile unsigned int *eventptr = (volatile unsigned int *)0xa05f6900;
  while(!((*eventptr) & 0x80));
  *eventptr = 0x80;
}


/* Launch a new render pass */

void ta_begin_render(void *cmdlist, void *tiles,
		     void *scrn, int modulo, int pixfmt,
		     int clipw, int cliph)
{
  volatile unsigned int *regs = (volatile unsigned int *)0xa05f8000;

  unsigned int cmdl = ((unsigned int)cmdlist)&0x007fffff;
  unsigned int tls = ((unsigned int)tiles)&0x007fffff;
  unsigned int scn = ((unsigned int)scrn)&0x007fffff;

  unsigned int *taend = (unsigned int *)(void *)(0xa5000000|regs[0x138/4]);
  int i;

  for (i=0; i<0x12; i++)
    taend[i] = 0;

  regs[0x02c/4] = tls;
  regs[0x020/4] = cmdl;
  regs[0x060/4] = scn;
  regs[0x08c/4] = 0x01000000 | ((((char *)taend)-((char *)cmdlist))<<1);
  regs[0x088/4] = 0x3e4cccc0 /* zclip */;
  regs[0x068/4] = (clipw-1)<<16;
  regs[0x06c/4] = (cliph-1)<<16;
  regs[0x04c/4] = modulo>>3;
  regs[0x048/4] = pixfmt;
  regs[0x014/4] = 0xffffffff; /* Launch! */
}

