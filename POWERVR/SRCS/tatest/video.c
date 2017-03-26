#include "video.h"


/* Initialize the PVR subsystem to a known state */

/* These values mainly from Dans 3dtest program... */

static unsigned int three_d_params[] = {
	0x80a8, 0x15d1c951,	/* M (Unknown magic value) */
	0x80a0, 0x00000020,	/* M */
	0x8008, 0x00000000,	/* TA out of reset */
	0x8048, 0x00000009,	/* alpha config */
	0x8068, 0x02800000,	/* pixel clipping x */
	0x806c, 0x01e00000,	/* pixel clipping y */
	0x8110, 0x00093f39,	/* M */
	0x8098, 0x00800408,	/* M */
	0x804c, 0x000000a0,	/* display align (640*2)/8 */
	0x8078, 0x3f800000,	/* polygon culling (1.0f) */
	0x8084, 0x00000000,	/* M */
	0x8030, 0x00000101,	/* M */
	0x80b0, 0x007f7f7f,	/* Fog table color */
	0x80b4, 0x007f7f7f,	/* Fog vertex color */
	0x80c0, 0x00000000,	/* color clamp min */
	0x80bc, 0xffffffff,	/* color clamp max */
	0x8080, 0x00000007,	/* M */
	0x8074, 0x00000001,	/* cheap shadow */
	0x807c, 0x0027df77,	/* M */
	0x8008, 0x00000001,	/* TA reset */
	0x8008, 0x00000000,	/* TA out of reset */
	0x80e4, 0x00000000,	/* stride width */
	0x6884, 0x00000000,	/* Disable all interrupt events */
	0x6930, 0x00000000,
	0x6938, 0x00000000,
	0x6900, 0xffffffff,	/* Clear all pending int events */
	0x6908, 0xffffffff,
	0x6930, 0x002807ec,	/* Re-enable some events */
	0x6938, 0x0000000e,
	0x80b8, 0x0000ff07,	/* fog density */
	0x80b4, 0x007f7f7f,	/* fog vertex color */
	0x80b0, 0x007f7f7f,	/* fog table color */
	0x8108, 0x00000003      /* 32bit palette  */
};

static unsigned int scrn_params[] = {
	0x80e8, 0x00160000,	/* screen control */
	0x8044, 0x00800000,	/* pixel mode (vb+0x11) */
	0x805c, 0x00000000,	/* Size modulo and display lines (vb+0x17) */
	0x80d0, 0x00000100,	/* interlace flags */
	0x80d8, 0x020c0359,	/* M */
	0x80cc, 0x001501fe,	/* M */
	0x80d4, 0x007e0345,	/* horizontal border */
	0x80dc, 0x00240204,	/* vertical position */
	0x80e0, 0x07d6c63f,	/* sync control */
	0x80ec, 0x000000a4,	/* horizontal position */
	0x80f0, 0x00120012,	/* vertical border */
	0x80c8, 0x03450000,	/* set to same as border H in 80d4 */
	0x8068, 0x027f0000,	/* (X resolution - 1) << 16 */
	0x806c, 0x01df0000,	/* (Y resolution - 1) << 16 */
	0x804c, 0x000000a0,	/* display align */
	0x8118, 0x00008040,	/* M */
	0x80f4, 0x00000401,	/* anti-aliasing */
	0x8048, 0x00000009,	/* alpha config */
	0x7814, 0x00000000,	/* More interrupt control stuff (so it seems)*/
	0x7834, 0x00000000,
	0x7854, 0x00000000,
	0x7874, 0x00000000,
	0x78bc, 0x4659404f,
	0x8040, 0x00000000	/* border color */
};

static void set_regs(unsigned int *values, int cnt)
{
  volatile unsigned char *regs = (volatile unsigned char *)(void *)0xa05f0000;
  unsigned int r, v;
  
  while(cnt--) {
    r = *values++;
    v = *values++;
    *(volatile unsigned int *)(regs+r) = v;
  }
}

void init_pvr()
{
  volatile unsigned int *vbl = (volatile unsigned int *)(void *)0xa05f810c;

  set_regs(three_d_params, sizeof(three_d_params)/sizeof(three_d_params[0])/2);
  while (!(*vbl & 0x01ff));
  while (*vbl & 0x01ff);
  set_regs(scrn_params, sizeof(scrn_params)/sizeof(scrn_params[0])/2);
}


/* Set up video registers to the desired
   video mode
  
   cabletype  (0=VGA, 2=RGB, 3=Composite)
   pixel mode (0=RGB555, 1=RGB565, 3=RGB888)
   res        (0 = 320 x 240, 1 = 640 x 240, 2 = 640 x 480)  */

void init_video(int cabletype, int mode, int res)
{
  volatile unsigned int *videobase=(volatile unsigned int *)(void*)0xa05f8000;
  static int bppshifttab[]= { 1,1,0,2 };
  int shift, lines, modulo, words_per_line, vpos;
  int laceoffset=0, voffset=0;
  unsigned int videoflags, attribs;
  unsigned int hvcounter = (res<2? 0x01060359 : 0x020c0359);

  mode &= 3;
  shift = bppshifttab[mode]; 

  videobase[8/4]=0;
  videobase[0x40/4]=0;

  /* Select pixel clock and colour mode */
  mode = (mode<<2)|1;
  lines = 240;
  if(!(cabletype&2)) {

    /* VGA mode */

    if(res < 2)
      mode |= 2; /* doublescan */

    hvcounter = 0x020c0359;

    lines <<= 1;
    mode |= 0x800000; /* fast pixel clock */
  }
  videobase[0x44/4]=mode;

  /* Set video base address.  Short fields will be offset by
     640 pixels, regardless of horizontal resolution.       */
  videobase[0x50/4]=0;
  videobase[0x54/4]=640<<shift;

  /* Set screen size, modulo, and interlace flag */
  videoflags = 1<<8;
  if(res==0)
    words_per_line=(320/4)<<shift;
  else
    words_per_line=(640/4)<<shift;
  modulo = 1;

  if(!(cabletype&2))
  {
    if(res==0)
      /* VGA lores -> skip 320 pixels to keep modulo at 640 pixels */
      modulo += words_per_line;
  } else {
    if(res!=1)
      /* NTSC lores -> skip 320 pixels to keep modulo at 640 pixels */
      /* _or_ NTSC hires -> skip every other line due to interlace  */
      modulo += words_per_line;

    if(res==2)
      /* interlace mode */
      videoflags |= 1<<4;
    
    /* enable NTSC */
    videoflags |= 1<<6;
  }

  /* Write screen size and modulo */
  videobase[0x5c/4]=(((modulo<<10)+lines-1)<<10)+words_per_line-1;

  /* Enable video (lace, NTSC) */
  videobase[0xd0/4]=videoflags;

  /* Screen and border position */

  if(!(cabletype&2))
    /* VGA */
    voffset += 36;
  else
    voffset += 18;
    
  vpos=(voffset<<16)|(voffset+laceoffset);

  videobase[0xf0/4]=vpos;	/* V start              */
  videobase[0xdc/4]=vpos+lines;	/* start and end border */
  videobase[0xec/4]=0xa4;	/* Horizontal pos       */
  videobase[0xd8/4]=hvcounter;	/* HV counter           */
  videobase[0xd4/4]=0x007e0345;	/* Horizontal border    */

  /* Select horizontal pixel doubling for lowres */
  if(res==0)
    attribs=((22<<8)+1)<<8;
  else
    attribs=22<<16;
  videobase[0xe8/4]=attribs;

  /* Set up vertical blank event */
  vpos = 260;
  if(!(cabletype&2))
    vpos = 510;
  videobase[0xcc/4]=(0x21<<16)|vpos;

  /* Select RGB/CVBS */
  if(cabletype&1)
    mode = 3;
  else
    mode = 0;
  *(volatile unsigned int *)(void*)0xa0702c00 = mode << 8;

  return;
}


/* Check type of video cable connected */

int check_cable()
{
  volatile unsigned int *porta = (unsigned int *)0xff80002c;

  /* PORT8 and PORT9 is input */
  *porta = (*porta & ~0xf0000) | 0xa0000;

  /* Return PORT8 and PORT9 */
  return ((*(volatile unsigned short *)(porta+1))>>8)&3;
}

