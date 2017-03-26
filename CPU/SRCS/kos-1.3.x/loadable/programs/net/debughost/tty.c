/* KallistiOS ##version##

   tty.c
   Copyright (C)2003 Dan Potter

   $Id: tty.c,v 1.1 2003/07/15 07:55:04 bardtx Exp $
*/

#include <kos.h>
#include <assert.h>
#include <stdarg.h>
#include <kos/img.h>
#include <jpeg/jpeg.h>
#include "debug.h"

/* This is modeled after the code I added to ps2-load-ip for its
   console, but is no where near as extensive (nor is anything
   copied from the old eCos code). */

// Our attribute colors
typedef struct {
	int r, g, b;
} rgb_t;

static rgb_t attr_cols[16] = {
	{ 0xc0, 0xc0, 0xc0 },		// White
	{ 0x80, 0xc0, 0x80 },		// Light green
	{ 0x10, 0x05, 0x30 },		// Dark purple
	{ 0xc0, 0xc0, 0x80 },		// Light yellow
	{ 0x80, 0x80, 0xc0 }		// Mid-bright blue
};

// Our screen
#define SCR_W	80
#define SCR_H	30
#define SCR_START (480 - 30*14)
static char screen[SCR_H][SCR_W];
static uint8 attrs[SCR_H][SCR_W];
static int curfg = TTY_DEFAULT_FG, curbg = TTY_DEFAULT_BG;
static int curx = 0, cury = 0;
static int frozen = 0;
static mutex_t * mutex;

// Our font
static uint8 * font = NULL;

// Our logo
static kos_img_t * logo = NULL;

static void tty_draw_logo() {
	int	y;
	uint16	* ld;

	assert( logo );
	assert( (KOS_IMG_FMT_I(logo->fmt) & KOS_IMG_FMT_MASK) == KOS_IMG_FMT_RGB565 );

	ld = (uint16 *)logo->data;

	for (y=0; y<logo->h; y++) {
		memcpy4(vram_s + y*640, ld + y*logo->w, logo->w*2);
	}
}

void tty_freeze() {
	mutex_lock(mutex);
	frozen = 1;
	mutex_unlock(mutex);
}

void tty_thaw() {
	int repaint = 0;
	
	mutex_lock(mutex);
	if (frozen)
		repaint = 1;
	frozen = 0;
	mutex_unlock(mutex);

	if (repaint) {
		vid_init(DEFAULT_VID_MODE, DEFAULT_PIXEL_MODE);
		tty_refresh();
	}
}

void tty_clear() {
	int x, y;

	mutex_lock(mutex);
	for (y=0; y<SCR_H; y++)
		for (x=0; x<SCR_W; x++) {
			screen[y][x] = ' ';
			attrs[y][x] = (curfg << 4) | curbg;
		}
	curx = cury = 0;
	mutex_unlock(mutex);
	tty_refresh();
}

static void tty_draw_char(int cx, int cy, int ch, int attr) {
	uint8	b;
	int	x, y;
	rgb_t	* col;
	uint16	fcc, bcc, * out;

	cx *= 8;
	cy = cy*14 + SCR_START;

	// Look up colors
	col = attr_cols + (attr >> 4);
	fcc = ((col->r >> 3) << 11) |
		((col->g >> 2) << 5) |
		((col->b >> 3) << 0);
	col = attr_cols + (attr & 0xf);
	bcc = ((col->r >> 3) << 11) |
		((col->g >> 2) << 5) |
		((col->b >> 3) << 0);

	out = vram_s + 640 * cy + cx;
	for (y=0; y<14; y++) {
		b = font[ch*14 + y + 6];
		for (x=0; x<8; x++) {
			if (b & (0x80 >> x))
				*out = fcc;
			else
				*out = bcc;
			out++;
		}
		out += 640 - 8;
	}
}

static void tty_draw_curs() {
	int	x, y;
	rgb_t	* col;
	uint16	cc, * out;

	col = attr_cols + curfg;
	cc = ((col->r >> 3) << 11) |
		((col->g >> 2) << 5) |
		((col->b >> 3) << 0);

	out = vram_s + 640 * (cury*14 + SCR_START) + curx*8;
	for (y=0; y<14; y++) {
		for (x=0; x<8; x++)
			out[x] = cc;
		out += 640;
	}
}

void tty_refresh() {
	int x, y;

	mutex_lock(mutex);
	if (!frozen) {
		// Start off with a base background
		vid_clear(attr_cols[TTY_DEFAULT_BG].r, attr_cols[TTY_DEFAULT_BG].g, attr_cols[TTY_DEFAULT_BG].b);

		// Redraw the logo
		tty_draw_logo();

		// Redraw the actual text area
		for (y=0; y<SCR_H; y++)
			for (x=0; x<SCR_W; x++) {
				tty_draw_char(x, y, screen[y][x], attrs[y][x]);
			}

		// Redraw the cursor
		tty_draw_curs();
	}

	mutex_unlock(mutex);
}

void tty_setcol(int f, int b) {
	mutex_lock(mutex);
	
	curfg = f;
	curbg = b;

	if (!frozen)
		tty_draw_curs();

	mutex_unlock(mutex);
}

static void tty_nexty() {
	int x, y, yc;

	curx = 0; cury++;
	if (cury >= SCR_H)
		cury = 0;

	for (y=cury, yc=4; yc >0; yc--,y = (y + 1) % SCR_H) {
		for (x=0; x<SCR_W; x++) {
			screen[y][x] = ' ';
			attrs[y][x] = (TTY_DEFAULT_FG << 4) | TTY_DEFAULT_BG;
			if (!frozen)
				tty_draw_char(x, y, screen[y][x], attrs[y][x]);
		}
	}
}

void tty_print(const char * str, int r) {
	int c;

	mutex_lock(mutex);
	
	for (c=0; c<r; c++) {
		if (str[c] == '\r') { curx = 0; continue; }
		if (str[c] == '\n') { tty_nexty(); continue; }

		screen[cury][curx] = str[c];
		attrs[cury][curx] = (curfg << 4) | curbg;
		if (!frozen)
			tty_draw_char(curx, cury, screen[cury][curx], attrs[cury][curx]);
		curx++; if (curx >= SCR_W) { curx=0; tty_nexty(); }
	}

	if (!frozen)
		tty_draw_curs();

	mutex_unlock(mutex);
}

static char pfbuf[1024];
void tty_printf(const char * fmt, ...) {
	va_list args;
	int r;

	va_start(args, fmt);
	r = vsprintf(pfbuf, fmt, args);
	va_end(args);

	tty_print(pfbuf, r);
}

int tty_init() {
	file_t	f;
	int	sz;

	// Load up our font
	f = fs_open("cp850-8x14.psf", O_RDONLY);
	if (f < 0) {
		perror("can't open font");
		return -1;
	}

	sz = fs_total(f);
	// fs_seek(f, 0, SEEK_SET);
	font = malloc(sz);
	fs_read(f, font, sz);
	fs_close(f);

	// Load up our logo graphic
	logo = calloc(1, sizeof(kos_img_t));
	if (jpeg_to_img("/debugrd/logo.jpg", 1, logo) < 0) {
		perror("can't open logo");
		free(font);
		return -1;
	}

	mutex = mutex_create();

	// Re-init the screen buffers and display
	tty_clear();

	tty_setcol(TTY_GREEN, TTY_DEFAULT_BG);
	tty_printf("%s\n", VERSION_STRING);
	tty_setcol(TTY_DEFAULT_FG, TTY_DEFAULT_BG);

	return 0;
}

void tty_shutdown() {
	mutex_destroy(mutex);
}
