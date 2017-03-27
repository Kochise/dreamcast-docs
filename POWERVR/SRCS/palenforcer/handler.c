/* handler.c - prevent the changing of the vertical frequency */

#include "types.h"

void break_handler(void);

void
break_handler()
{

	register uint32 val = *(uint32 *)0xa05f80d8;
	register uint32 val2 = (val>>16) & 0x03ff;

	/* acknowledge break */
	*(uint32 *)0xff200020 |= (1<<14) | (1<<15);

	if ((val2 > 500) && (val2 < 550))  {
		/* NTSC, interlace */
		val = (624<<16) | 863;	/* set PAL, interlace */
	}
	else if ((val2 > 210) && (val2 < 300)) {
		/* NTSC, non-interlace */
		val = (312<<16) | 863;	/* set PAL, non-interlace */
	} else {
		goto alldone;
	}

	*(uint32 *)0xff200008 = 0;
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	*(uint32 *)0xa05f80d8 = val;
	*(uint32 *)0xff200008 = (2<<4) | (2<<2);

alldone:
	__asm__("rte");
	__asm__("nop");

}
