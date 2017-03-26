/* KallistiOS ##version##
 *
 *  dc/video.h
 *  (c)2001 Anders Clerwall (scav)
 *
 *  $Id: video.h,v 1.6.2.1 2003/07/10 02:20:23 bardtx Exp $
 */

#ifndef __DC_VIDEO_H
#define __DC_VIDEO_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

//-----------------------------------------------------------------------------
#define CT_ANY		-1 // <-- Used ONLY internally with vid_mode
#define CT_VGA		0
#define CT_RGB		2
#define CT_COMPOSITE	3

//-----------------------------------------------------------------------------
#define PM_RGB555	0
#define PM_RGB565	1
#define PM_RGB888	3

//-----------------------------------------------------------------------------
// These are more generic modes

enum {
	DM_GENERIC_FIRST = 0x1000,
	DM_320x240 = 0x1000,
	DM_640x480,
	DM_800x608,
	DM_256x256,
	DM_768x480,
	DM_768x576,
	DM_GENERIC_LAST = DM_768x576
};

//-----------------------------------------------------------------------------
// More specific modes (and actual indeces into the mode table)

enum {
	DM_INVALID = 0,
	// Valid modes below
	DM_320x240_VGA = 1,
	DM_320x240_NTSC,
	DM_640x480_VGA,
	DM_640x480_NTSC_IL,
	DM_800x608_VGA,
	DM_640x480_PAL_IL,
	DM_256x256_PAL_IL,
	DM_768x480_NTSC_IL,
	DM_768x576_PAL_IL,
	DM_768x480_PAL_IL,
	DM_320x240_PAL,
	// The below is only for counting..
	DM_SENTINEL,
	DM_MODE_COUNT
};

//-----------------------------------------------------------------------------
#define VID_MAX_FB	4	// <-- This should be enough

//-----------------------------------------------------------------------------
// These are for the "flags" field of "vid_mode_t"
#define VID_INTERLACE		0x00000001
#define VID_LINEDOUBLE		0x00000002	// <-- For 240 scanlines on VGA cable
#define VID_PIXELDOUBLE		0x00000004	// <-- For low-res modes (320)
#define VID_PAL			0x00000008	// <-- This sets output to 50Hz PAL if not CT_VGA

//-----------------------------------------------------------------------------
struct vid_mode {
	int    generic;				// <-- Generic mode identifier (for vid_set_mode)
	uint16 width, height;			// <-- With and height of screen in pixels
	uint32 flags;				// <-- Combination of one or more VID_* flags
	
	int16 cable_type;			// <-- One of CT_*
	uint16 pm;				// <-- Pixel Mode
	
	uint16 scanlines, clocks;		// <-- Scanlines/frame and clocks per scanline.
	uint16 bitmapx, bitmapy;		// <-- Bitmap window position (bitmapy is automatically increased for PAL)
	uint16 scanint1, scanint2;		// <-- Scanline interrupt positions (scanint2 automatically doubled for VGA)
	uint16 borderx1, borderx2;		// <-- Border x start/stop
	uint16 bordery1, bordery2;		// <-- Border y start/stop
	
	uint16 fb_curr, fb_count;
	uint32 fb_base[VID_MAX_FB];
};

typedef struct vid_mode vid_mode_t;

extern vid_mode_t vid_builtin[DM_MODE_COUNT];
extern vid_mode_t *vid_mode;

//-----------------------------------------------------------------------------
extern uint16 *vram_s;
extern uint32 *vram_l;

//-----------------------------------------------------------------------------
int vid_check_cable();

void vid_set_start(uint32 base);
void vid_flip(int fb);
void vid_border_color(int r, int g, int b);
void vid_clear(int r, int g, int b);
void vid_empty();
void vid_waitvbl();
void vid_set_mode(int dm, int pm);
void vid_set_mode_ex(vid_mode_t *mode);

void vid_init(int disp_mode, int pixel_mode);
void vid_shutdown();

//-----------------------------------------------------------------------------

int vid_screen_shot(const char * destfn);

//-----------------------------------------------------------------------------

__END_DECLS

#endif	// __DC_VIDEO_H

