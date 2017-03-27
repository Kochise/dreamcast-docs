/* main.c - main routines */

#include "types.h"

#define BARA	*(volatile uint32 *)0xff200000
#define BAMRA	*(volatile uint8 *)0xff200004
#define BBRA	*(volatile uint16 *)0xff200008
#define BASRA	*(volatile uint8 *)0xff000014
#define BARB	*(volatile uint32 *)0xff20000c
#define BAMRB	*(volatile uint8 *)0xff200010
#define BBRB	*(volatile uint16 *)0xff200014
#define BASRB	*(volatile uint8 *)0xff000018
#define BDRB	*(volatile uint32 *)0xff200018
#define BDRMB	*(volatile uint32 *)0xff20001c
#define BRCR	*(volatile uint16 *)0xff200020

#define HANDLER_ADDR	0x8c004000
#define HANDLER_SIZE	124

#define IMAGE_SIZE	(640*3)*512
#define IMAGE2_SIZE	(640*4)*512

/* prototypes */
sint32 enable_gdrom(void);
sint32 exec_cmd(uint32, void *);
void install_handler(void *, uint32);
void init_dbr(void);
void patch_c000(void);
void patch_regioncode(void);
void show_image(void);
void hide_image(void);
void reboot(void);
void wait_gdrom(void);
sint32 get_status(void);

extern void break_handler(void);
extern void __exit(sint32);

static const char id[] =
	"PAL-enforcer $Id: main.c,v 1.0 2001/06/30 02:51:32 ejstans Exp $";

extern void *image;

void
exit(status)
	sint32 status;
{
	__exit(status);
}

sint32
main()
{
	enable_gdrom();
	install_handler((void *)break_handler, HANDLER_SIZE);
	init_dbr();
	patch_c000();
	patch_regioncode();
	show_image();
	wait_gdrom();
	hide_image();
	reboot();
	return (0);
}

sint32
enable_gdrom()
{

	uint32 i;
	volatile uint32 *p = (volatile uint32 *)0xa0000000;
	void (*p2)(uint32, uint32, uint32, uint32) = (void *)*(uint32 *)0x8c0000bc;

	*((volatile uint32 *)0xa05f74e4) = 0x001fffff;

	/* do the checksum on bootrom */
	for (i = 0; i < 0x00200000/4; i++) {
		(void)*(p++);
	}

	/* gdrom online again...reinit */
	(*p2)(0, 0, 0, 3);

	/* slight delay */
	for (i = 0; i < 1000000; i++);

	/* try to run INIT command */
	for (i = 0; i < 10; i++) {
		if (exec_cmd(24, NULL) == 0) {
			return (0);
		}
	}

	return (-1);

}

sint32
exec_cmd(cmd, param)
	uint32 cmd;
	void *param;
{

	sint32 (*p)(uint32, void *, uint32, uint32) = (void *)*(uint32 *)0x8c0000bc;
	sint32 status[4];
	sint32 gdhn;
	sint32 i = 0;

	gdhn = (*p)(cmd, param, 0, 0);

	do {
		(*p)(0, NULL, 0, 2);
	} while ((i = (*p)(gdhn, status, 0, 1)) == 1);

	if (i != 2) {
		return (-1);
	}

	return (0);

}

void
install_handler(handler, size)
	void *handler;
	uint32 size;
{
	uint32 i;
	uint8 *d = (uint8 *)HANDLER_ADDR;
	uint8 *s = (uint8 *)handler;

	for (i = 0; i < size; i++) {
		*(d++) = *(s++);
	}

	/* should flush cache here to be 100% correct but not really needed */

}

void
init_dbr()
{

	/* set DBR here */
	__asm__("ldc	%0,dbr" :: "r" (HANDLER_ADDR) );

	/* set BARA to the address we want to break on */
	BARA = 0xa05f80d8;	/* sync_load register */

	/* set BAMRA to include all bits in BARA and ignore ASID */
	BAMRA = 0x00;

	/* set BBRA to break on write, no size comparison */
	BBRA = (2<<4) | (2<<2);

	/* set BRCR to use the User Debug Function */
	BRCR = 1;

}

void
patch_c000()
{

	uint16 *d = (uint16 *)0x8c00c000;

	*(d++) = 0x000b;
	*(d++) = 0x0009;

	/* should flush cache here */

}

void
patch_regioncode()
{

	uint16 *d = (uint16 *)0x8c000506;

	/* skipping region checking code...
	   I only have a japanese bootROM v1.004 handy so this is
	   only known to work on this particular version... */
	*(d++) = 0x890a;

}

void
show_image()
{

	uint32 *d = (uint32 *)0xa5000000;
	uint32 *s = (uint32 *)&image;
	uint32 i;

	/* disable display */
	*(volatile uint32 *)0xa05f8044 &= ~((3<<2) | 1);

	/* upload image to framebuffer */
	for (i = 0; i < IMAGE_SIZE/4; i++) {
		*(d++) = *(s++);
	}

	/* set videoregs */
	*(uint32 *)0xa05f8040 = 0x000000000;
	*(uint32 *)0xa05f8048 = (4<<0);
	*(uint32 *)0xa05f8050 = 0x00000000;
	*(uint32 *)0xa05f8054 = 0x00000000 + (640*3);
	*(uint32 *)0xa05f805c = ((((640*3)/4)+1)<<20) | (((512/2)-1)<<10)
		| (((640*3)/4) - 1);
	*(uint32 *)0xa05f80d0 = (*(volatile uint32 *)0xa05f80d0 & ~(3<<6))
		| (1<<6); 
	*(uint32 *)0xa05f80d4 = (116<<16) | 843;
	*(uint32 *)0xa05f80d8 = (624<<16) | (863);
	*(uint32 *)0xa05f80dc = (44<<16) | 620;
	*(uint32 *)0xa05f80e0 = (0x1f<<22) | (362<<12) | (5<<8) | (0x3f);
	*(uint32 *)0xa05f80ec = 174;
	*(uint32 *)0xa05f80f0 = (18<<16) | 18;

	/* re-enable display (and set RGB888-mode) */
	*(uint32 *)0xa05f8044 |= ((2<<2) | 1);

}

void
hide_image()
{

	uint32 *d = (uint32 *)0xa5000000;
	uint32 i;

	/* disable display */
	*(volatile uint32 *)0xa05f8044 &= ~((3<<2) | 1);

	/* blank out image from framebuffer */
	for (i = 0; i < IMAGE2_SIZE/4; i++) {
		*(d++) = 0xc0c0c0c0;
	}

	/* dont bother with enabling display since bootROM will do it */

}

void
wait_gdrom()
{
	/* wait for lid to open */
	while (get_status() != 6);

	/* wait for lid to close (and a proper disc inserted) */
	while (get_status() != 1);
}

sint32
get_status()
{

	sint32 (*p)(void *, uint32, uint32, uint32) = (void *)*(uint32 *)0x8c0000bc;
	uint32 buf[4];

	(*p)(buf, 0, 0, 4);

	return (buf[0]);

}

void
reboot()
{
	void (*p)(sint32) = (void *)*(uint32 *)0x8c0000e0;
	(*p)(-3);
}
