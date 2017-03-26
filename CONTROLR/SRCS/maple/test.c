/*
 * Maple Bus example
 *
 * Displays a list of connected units, with icons for
 * the memory cards
 *
 */

#include "maple.h"
#include "video.h"

#ifndef NULL
#define NULL ((void*)0)
#endif


/* Workaround for GCC braindamage */

void atexit() { }


/* Endianness conversion */

unsigned int read_belong(unsigned int *l)
{
  unsigned char *b = (unsigned char *)l;
  return (b[0]<<24)|(b[1]<<16)|(b[2]<<8)|b[3];
}

void write_belong(unsigned int *l, unsigned int v)
{
  unsigned char *b = (unsigned char *)l;
  b[0] = v>>24;
  b[1] = v>>16;
  b[2] = v>>8;
  b[3] = v;
}


/* Syscall to return to boot menu */

void exit_to_menu()
{
  (*(void(**)())0x8c0000e0)(1);
}


int main()
{
  int port, unit;
  int ypos = 0;

  /* Set up the screen */
  init_video(check_cable(), 0);
  clrscr(0);

  /* Initialize Maple Bus */
  maple_init();

  for(port = 0; port < 4; port++)
    for(unit = 0; unit < 6; unit++) {
      char *res;

      /* First, send a DEVINFO command to find out what device
	 is present (if any) as this unit.                     */
      do
	res = maple_docmd(port, unit, MAPLE_COMMAND_DEVINFO, 0, NULL);
      while(*res == MAPLE_RESPONSE_AGAIN);

      /* If the DEVINFO command succeeds, the response is a DEVINFO
	 reply with a maple_devinfo struct (28 words long) as data. */
      if(*res == MAPLE_RESPONSE_DEVINFO && res[3]>=28) {
	struct maple_devinfo *di = (struct maple_devinfo *)(res+4);
	char buf[36];
	int i;

	/* Display unit address and name */
	buf[0] = 'A'+port;
	buf[1] = '0'+unit;
	buf[2] = ':';
	buf[3] = ' ';
	for(i=0; i<30; i++)
	  buf[4+i] = di->product_name[i];
	buf[34] = '\0';
	draw_string(36, ypos, buf, -1);

	/* If this is a memory card, get the memory info for partition 0
	   in order to get the icon for the card.
	   (No ICONDATA_VMS support right now, sorry.)                   */
	if(read_belong(&di->func) & MAPLE_FUNC_MEMCARD) {
	  unsigned int params[2];
	  write_belong(&params[0], MAPLE_FUNC_MEMCARD);
	  write_belong(&params[1], 0<<24);
	  do
	    res = maple_docmd(port, unit, MAPLE_COMMAND_GETMINFO,
			      2, params);
	  while(*res == MAPLE_RESPONSE_AGAIN);

	  /* If GETMINFO succeeds, a data transfer response is returned */
	  if(*res == MAPLE_RESPONSE_DATATRF) {
	    int x, y;
	    int icon=res[4+18];  /* 18th byte of MINFO holds icon # */

	    /* The icon font has an offset of 0x7ef30 from the base address.
	       Each glyph is 32 x 32 pixels (= 128 bytes), and the first
	       5 are system use (hourglass animation + bad card indicator) */
	    unsigned int *icondata =
	      (unsigned int *)(get_font_address()+0x7ef30+128*(icon+5));

	    unsigned short *pixel = ((unsigned short *)0xa5000000)+640*ypos;
	    for(y=0; y<32; y++) {
	      unsigned int mask = *icondata++;
	      unsigned short *pline = pixel;
	      for(x=0; x<32; x++)
		*pline++ = ((mask&(1<<(x^7)))? 0 : 0x7fe0);
	      pixel += 640;
	    }
	  }
	}

	/* Use a rowspacing of 36 rather than 24 pixels, to leave
	   appropriate room for the icons.                        */
	ypos += 36;
      }
    }

  draw_string(0, ypos+4, "Press START to exit", 0x1f);

  /* Now wait for START to be pressed on any controller */
  for(;;) {

    for(port = 0; port < 4; port++) {
      char *res;
      unsigned int func;
      unsigned int params[1];

      /* Query controller condition (non-controller will return error) */
      write_belong(&params[0], MAPLE_FUNC_CONTROLLER);
      do
	res = maple_docmd(port, 0, MAPLE_COMMAND_GETCOND, 1, params);
      while(*res == MAPLE_RESPONSE_AGAIN);

      if(*res == MAPLE_RESPONSE_DATATRF && res[3]>=2 &&
	 read_belong((unsigned int *)(res+4)) == MAPLE_FUNC_CONTROLLER) {

	/* The START button is bit 3 in the first condition word */
	if(!((*(unsigned short *)(res+8)) & 8))
	  exit_to_menu();
      }
    }
  }
}
