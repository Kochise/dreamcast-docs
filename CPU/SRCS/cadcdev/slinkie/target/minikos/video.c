/* KallistiOS ##version##

   video.c

   (c)2001 Anders Clerwall (scav)
   Parts (c)2000-2001 Dan Potter
 */
 
#include <dc/video.h>
#include <string.h>
#include <stdio.h>

//-----------------------------------------------------------------------------
CVSID("$Id: video.c,v 1.11.2.2 2003/08/02 01:52:31 bardtx Exp $");
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// This table is indexed w/ DM_*
vid_mode_t vid_builtin[DM_MODE_COUNT] = {
	// NULL mode..
	// DM_INVALID = 0
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, { 0 } },

	// 640x480 VGA 60Hz
	// DM_640x480_VGA
	{
		DM_640x480,
		640, 480,
		VID_INTERLACE,
		CT_VGA,
		0,
		0x20C, 0x359,
		0xAC, 0x28,
		0x15, 0x104,
		0x7E, 0x345,
		0x24, 0x204,
		0, 1,
		{ 0 }
	},

	// 640x480 NTSC 60Hz IL
	// DM_640x480_NTSC_IL
	{
		DM_640x480,
		640, 480,
		VID_INTERLACE,
		CT_ANY,
		0,
		0x20C, 0x359,
		0xA4, 0x12,
		0x15, 0x104,
		0x7E, 0x345,
		0x24, 0x204,
		0, 1,
		{ 0 }
	},

	// END
	// DM_SENTINEL
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, { 0 } }

	// DM_MODE_COUNT
};

//-----------------------------------------------------------------------------
volatile uint32	*regs = (uint32*)0xA05F8000;
vid_mode_t	currmode = { 0 };
vid_mode_t	*vid_mode = 0;
uint16		*vram_s;
uint32	 	*vram_l;

//-----------------------------------------------------------------------------
/* Checks the attached cable type (to the A/V port). Returns
   one of the following:
     0 == VGA
     1 == (nothing)
     2 == RGB
     3 == Composite
   
   This is a direct port of Marcus' assembly function of the
   same name.
   
   [This is the old KOS function by Dan.]
*/
int vid_check_cable() {
	uint32 * porta = (uint32 *)0xff80002c;
	
	*porta = (*porta & 0xfff0ffff) | 0x000a0000;
	
	// Read port8 and port9
	return (*((uint16*)(porta + 1)) >> 8) & 3;
}

//-----------------------------------------------------------------------------
void vid_set_mode(int dm, int pm) {
	vid_mode_t mode;
	int i, ct, found;

	ct = vid_check_cable();

	// Check to see if we should use a direct mode index, a generic
	// mode check, or if it's just invalid.
	if (dm > DM_INVALID && dm < DM_SENTINEL) {
		memcpy(&mode, &vid_builtin[dm], sizeof(vid_mode_t));
	} else if (dm >= DM_GENERIC_FIRST && dm <= DM_GENERIC_LAST) {
		found = 0;
		for (i=1; i<DM_SENTINEL; i++) {
			// Is it the right generic mode?
			if (vid_builtin[i].generic != dm)
				continue;

			// Do we have the right cable type?
			if (vid_builtin[i].cable_type != CT_ANY &&
					vid_builtin[i].cable_type != ct)
				continue;

			// Ok, nothing else to check right now -- we've got our mode
			memcpy(&mode, &vid_builtin[i], sizeof(vid_mode_t));
			found = 1;
			break;
		}
		if (!found) {
			printf("vid_set_mode: invalid generic mode %04x\n", dm);
			return;
		}
	} else {
		printf("vid_set_mode: invalid mode specifier %04x\n", dm);
		return;
	}
	
	// We set this here so actual mode is bit-depth independent..
	mode.pm = pm;
		
	// This is also to be generic
	mode.cable_type = ct;
		
	// This will make a private copy of our "mode"
	vid_set_mode_ex(&mode);
}

//-----------------------------------------------------------------------------
void vid_set_mode_ex(vid_mode_t *mode) {
	static uint8 bpp[4] = { 2, 2, 0, 4 };
	uint16 ct;
	uint32 data;
	
	
	// Verify cable type for video mode.
	ct = vid_check_cable();
	if (mode->cable_type != CT_ANY) {
		if (mode->cable_type != ct) {
			// Maybe this should have the ability to be forced (thru param)
			// so you can set a mode with VGA params with RGB cable type?
			//ct=mode->cable_type;
			printf("vid_set_mode: Mode not allowed for this cable type (%i!=%i)\n", mode->cable_type, ct);
			return;
		}
	}

	// Blank screen and reset display enable (looks nicer)
	regs[0x3A] |= 8;	// Blank
	regs[0x11] &= ~1;	// Display disable

	// Clear interlace flag if VGA (this maybe should be in here?)
	if (ct == CT_VGA) {
		mode->flags &= ~VID_INTERLACE;
		if (mode->flags & VID_LINEDOUBLE)
			mode->scanlines *= 2;
	}

	printf("vid_set_mode: %ix%i%s %s\n", mode->width, mode->height,
		(mode->flags & VID_INTERLACE) ? "IL" : "",
		(mode->flags & VID_PAL) ? "PAL" : "NTSC");
	
	vid_border_color(0, 0, 0);
	
	// Pixelformat
	data = (mode->pm << 2);
	if (ct == CT_VGA) {
		data |= 1 << 23;
		if (mode->flags & VID_LINEDOUBLE)
			data |= 2;
	}
	regs[0x11] = data;
	
	// Linestride
	regs[0x13] = (mode->width * bpp[mode->pm]) / 8;

	// Display size
	data = ((mode->width * bpp[mode->pm]) / 4) - 1;
	if (ct == CT_VGA || (!(mode->flags & VID_INTERLACE))) {
		data |= (1 << 20) | ((mode->height - 1) << 10);
	} else {
		data |= (((mode->width * bpp[mode->pm] >> 2) + 1) << 20)
			| (((mode->height / 2) - 1) << 10);
	}
	regs[0x17] = data;

	// vblank irq
	if(ct == CT_VGA) {
		regs[0x33] = (mode->scanint1 << 16) | (mode->scanint2 << 1);
	} else {
		regs[0x33] = (mode->scanint1 << 16) | mode->scanint2;
	}
	
	// Interlace stuff
	data = 0x100;
	if (mode->flags & VID_INTERLACE) {
		data |= 0x10;
		if (mode->flags & VID_PAL) {
			data |= 0x80;
		} else {
			data |= 0x40;
		}
	}
	regs[0x34] = data;
	
	// Border window
	regs[0x35] = (mode->borderx1 << 16) | mode->borderx2;
	regs[0x37] = (mode->bordery1 << 16) | mode->bordery2;
	
	// Scanlines and clocks.
	regs[0x36] = (mode->scanlines << 16) | mode->clocks;
	
	// Horizontal pixel doubling
	if (mode->flags & VID_PIXELDOUBLE) {
		regs[0x3A] |= 0x100;
	} else {
		regs[0x3A] &= ~0x100;
	}
	
	// Bitmap window
	regs[0x3B] = mode->bitmapx;
	data = mode->bitmapy;
	if (mode->flags & VID_PAL) {
		data++;
	}
	data = (data << 16) | mode->bitmapy;
	regs[0x3C] = data;
	
	// Everything is ok
	memcpy(&currmode, mode, sizeof(currmode));
	vid_mode = &currmode;

	regs[0x14] = 0;
	regs[0x15] = 640*2;
	vram_s = (uint16 *)0xa5000000;	
	vram_l = (uint32 *)vram_s;

	// Set cable type
	if (mode->cable_type & 1) {
		*((vuint32*)0xa0702c00) |= 0x300;
	} else {
		*((vuint32*)0xa0702c00) &= ~0x300;
	}

	// Re-enable the display
	regs[0x3A] &= ~8;
	regs[0x11] |= 1;
}

//-----------------------------------------------------------------------------
void vid_border_color(int r, int g, int b) {
	regs[0x0040/4] = ((r & 0xFF) << 16) |
			 ((g & 0xFF) << 8) |
			 (b & 0xFF);
}

//-----------------------------------------------------------------------------
/* Clears the screen with a given color

	[This is the old KOS function by Dan.]
*/
void vid_clear(int r, int g, int b) {
	uint16 pixel16;
	int i;
	
	switch (vid_mode->pm) {
		case PM_RGB565:
			pixel16 = ((r >> 3) << 11)
				| ((g >> 2) << 5)
				| ((b >> 3) << 0);
			for (i=0; i<(vid_mode->width * vid_mode->height) * 2; i++)
				vram_s[i] = pixel16;
			break;
	}
}

//-----------------------------------------------------------------------------
void vid_init(int disp_mode, int pixel_mode) {
	// Set mode and clear vram
	vid_set_mode(disp_mode, pixel_mode);
	vid_clear(0, 0, 0);
}


uint16 vid_pixel(int r, int g, int b) {
	return (((r >> 3) & 0x1f) << 11) |
		(((g >> 2) & 0x3f) << 5) |
		(((b >> 3) & 0x1f));
}
