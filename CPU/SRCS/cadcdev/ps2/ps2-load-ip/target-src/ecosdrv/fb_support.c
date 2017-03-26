/* ps2-load-ip

   fb_support.c

   Copyright (c)1998, 1999, 2000, 2001 Red Hat, Inc.
   Copyright (c)2001 YAEGASHI Takeshi
   Copyright (c)2002 Dan Potter
   License: GPL

   $Id: fb_support.c,v 1.3 2002/11/03 06:57:13 bardtx Exp $
*/
            

// $Id: fb_support.c,v 1.3 2002/11/03 06:57:13 bardtx Exp $
// This file is based on hal/arm/sa11x0/ipaq/current/src/lcd_support.c

#include "ecostypes.h"
#include "ee.h"
#include "gs.h"
#include "fb_support.h"

#define DMA_VIF0	0xb0008000
#define DMA_VIF1	0xb0009000
#define DMA_GIF		0xb000a000
#define DMA_fromIPU	0xb000b000
#define DMA_toIPU	0xb000b400
#define DMA_fromSPR	0xb000d000
#define DMA_toSPR	0xb000d400

#define PS2_Dn_CHCR	0x0000
#define PS2_Dn_MADR	0x0010
#define PS2_Dn_QWC	0x0020
#define PS2_Dn_TADR	0x0030
#define PS2_Dn_SADR	0x0080
#define DMAREG(base, x)	(*(volatile unsigned long *)((base)+(x)))

int
show_xpm(char *xpm[], int screen_pos);

void lcd_set_pixel(int x, int y, int r, int g, int b)
{
  static unsigned long long packet[8] __attribute__((aligned(16))) = {
    PS2_GIFTAG_SET_TOPHALF(3, 1, 0, 0, PS2_GIFTAG_FLG_PACKED, 1),
    PS2_GIFTAG_REGS_AD,
    PS2_GS_SETREG_PRIM(0, 0, 0, 0, 0, 0, 0, 0, 0),
    PS2_GS_PRIM,
    0,
    PS2_GS_RGBAQ,
    0,
    PS2_GS_XYZ2,
  };

  unsigned long long *p = KSEG1ADDR((void *)packet);

  p[4] = PS2_GS_SETREG_RGBAQ(r, g, b, 0, 0);
  p[6] = PS2_GS_SETREG_XYZ(x<<4, y<<4, 0);
  
  DMAREG(DMA_GIF, PS2_Dn_MADR) = PHYSADDR(packet);
  DMAREG(DMA_GIF, PS2_Dn_QWC) = sizeof(packet)>>4;
  DMAREG(DMA_GIF, PS2_Dn_CHCR) = 0x0101;
  while(DMAREG(DMA_GIF, PS2_Dn_CHCR) & 0x0100);
  /* void (*sp)(int,int,RGBA) = 0x80f06678;
  sp(y,x,color); */
}


void lcd_init(void)
{
  /* output enable */
  *(volatile unsigned int *)0xb2000000 = 0xffa5;

  lcd_clear();
}


#define LOGO_AT_TOP
#include "../logo/logo.xpm"
#include "font.h"

// Physical dimensions of LCD display
#define DISPLAY_WIDTH  640
#define DISPLAY_HEIGHT 480

#define LCD_WIDTH  640
#define LCD_HEIGHT 480
#define LCD_DEPTH   16

// Physical screen info
static int lcd_width  = LCD_WIDTH;
static int lcd_height = LCD_HEIGHT;

// Virtual screen info
static int curX = 0;  // Last used position
static int curY = 0;
//static int width = LCD_WIDTH / (FONT_WIDTH*NIBBLES_PER_PIXEL);
//static int height = LCD_HEIGHT / (FONT_HEIGHT*SCREEN_SCALE);

static RGBA attr_cols[16] = {
	{ 0xff, 0xff, 0xff, 0 },	// White
	{ 0x80, 0xff, 0x80, 0 },	// Light green
	{ 0x10, 0x05, 0x30, 0 },	// Dark purple
	{ 0xff, 0xff, 0x80, 0 },	// Light yellow
	{ 0x80, 0x80, 0xc0, 0 },	// Mid-bright blue
};

#define SCREEN_PAN            20
#define SCREEN_WIDTH          80
#define SCREEN_HEIGHT         (LCD_HEIGHT/FONT_HEIGHT)
#define VISIBLE_SCREEN_WIDTH  (LCD_WIDTH/FONT_WIDTH)
#define VISIBLE_SCREEN_HEIGHT (LCD_HEIGHT/FONT_HEIGHT)
static char screen[SCREEN_HEIGHT][SCREEN_WIDTH];
static uint8 attrs[SCREEN_HEIGHT][SCREEN_WIDTH];
static int screen_start = 0;
static int screen_height = SCREEN_HEIGHT;
static int screen_width = SCREEN_WIDTH;
static int screen_pan = 0;

static int cursor_enable = 1;
static int kbd_pos;
static int cur_attrs = 0x02;
static int cursor_attrs = 0x33;

void lcd_setattrs(int fg, int bg) {
	cur_attrs = ((fg & 0xf) << 4)
		| ((bg & 0xf) << 0);
}

// Clear screen
void
lcd_clear(void)
{
    int row, col;
    int pos;
    RGBA * bgp;

    lcd_height = LCD_HEIGHT;
    lcd_width = LCD_WIDTH;
    screen_start = 0;
    screen_height = SCREEN_HEIGHT;
    screen_width = SCREEN_WIDTH;
    screen_pan = 0;
    cursor_enable = 1;

    bgp = attr_cols + (cur_attrs & 0xf);

    for (row = 0;  row < lcd_height;  row++) {
        for (col = 0;  col < lcd_width;  col++) {
            lcd_set_pixel(col, row, bgp->r, bgp->g, bgp->b);
        }
    }
    for (row = 0;  row < screen_height;  row++) {
        for (col = 0;  col < screen_width;  col++) {
            screen[row][col] = ' ';
            attrs[row][col] = cur_attrs;
        }
    }

    // Note: Row 0 seems to wrap incorrectly
#ifdef LOGO_AT_TOP
    pos = 0;
#else
    pos = (LCD_HEIGHT-1);
#endif
    kbd_pos = show_xpm(logo_xpm, pos);
    curX = 0;  curY = screen_start;
    if (cursor_enable) {
        lcd_drawc(CURSOR_ON, cursor_attrs, curX-screen_pan, curY);
    }
}


// Refresh screen
void
lcd_refresh(void)
{
    int row, col;
    int pos;

    lcd_height = LCD_HEIGHT;
    lcd_width = LCD_WIDTH;
    screen_start = 0;
    screen_height = SCREEN_HEIGHT;
    screen_width = SCREEN_WIDTH;
    screen_pan = 0;
    cursor_enable = 1;

    // Note: Row 0 seems to wrap incorrectly
#ifdef LOGO_AT_TOP
    pos = 0;
#else
    pos = (LCD_HEIGHT-1);
#endif
    kbd_pos = show_xpm(logo_xpm, pos);

    for (row = screen_start;  row < screen_height;  row++) {
        for (col = 0;  col < screen_width;  col++) {
            lcd_drawc(screen[row][col], attrs[row][col], col, row);
        }
    }

    if (cursor_enable) {
        lcd_drawc(CURSOR_ON, cursor_attrs, curX-screen_pan, curY);
    }
}


// Position cursor
void
lcd_moveto(int X, int Y)
{
    if (cursor_enable) {
        lcd_drawc(screen[curY][curX], attrs[curY][curX], curX-screen_pan, curY);
    }
    if (X < 0) X = 0;
    if (X >= screen_width) X = screen_width-1;
    curX = X;
    if (Y < screen_start) Y = screen_start;
    if (Y >= screen_height) Y = screen_height-1;
    curY = Y;
    if (cursor_enable) {
        lcd_drawc(CURSOR_ON, cursor_attrs, curX-screen_pan, curY);
    }
}

// Render a character at position (X,Y) with current background/foreground
void lcd_drawc(int8 c, uint8 attr, int x, int y)
{
    uint8 bits;
    RGBA * fgp, * bgp;
    int l, p;

    fgp = attr_cols + ((attr >> 4) & 0xf);
    bgp = attr_cols + (attr & 0xf);

    if ((x < 0) || (x >= VISIBLE_SCREEN_WIDTH) || 
        (y < 0) || (y >= screen_height)) return;  
    for (l = 0;  l < FONT_HEIGHT;  l++) {
        bits = font_table[c-FIRST_CHAR][l]; 
        for (p = 0;  p < FONT_WIDTH;  p++) {
            if (bits & 0x01) {
                lcd_set_pixel(x*FONT_WIDTH + p, y*FONT_HEIGHT+l, fgp->r, fgp->g, fgp->b);
            } else {
                lcd_set_pixel(x*FONT_WIDTH + p, y*FONT_HEIGHT+l, bgp->r, bgp->g, bgp->b);
            }
            bits >>= 1;
        }
    }
}

// Draw one character at the current position
void
lcd_putc(int8 c)
{
    int need_clear = 0, row, col;

    if (cursor_enable) {
        lcd_drawc(screen[curY][curX], attrs[curY][curX], curX-screen_pan, curY);
    }
    switch (c) {
    case '\n':
        curY++;
        need_clear = 1;
        /* fallthru */
    case '\r':
        curX = 0;
        break;
    case '\b':
        curX--;
        if (curX < 0) {
            curY--;
            if (curY < 0) curY = 0;
            curX = screen_width-1;
        }
        break;
    default:
        if (((uint8)c < FIRST_CHAR) || ((uint8)c > LAST_CHAR)) c = '.';
        screen[curY][curX] = c;
        attrs[curY][curX] = cur_attrs;
        lcd_drawc(c, cur_attrs, curX-screen_pan, curY);
        curX++;
        if (curX == screen_width) {
            curY++;
            curX = 0;
            need_clear = 1;
        }
    } 
    if (curY >= screen_height) {
    	curY = screen_start;
    	need_clear = 1;
    }
    if (cursor_enable) {
        lcd_drawc(CURSOR_ON, cursor_attrs, curX-screen_pan, curY);
    }

    if (need_clear) {
        for (need_clear = 2, row=curY+1; need_clear > 0; need_clear--) {
            if (row >= screen_height)
            	row = screen_start;
            for (col=0; col<screen_width; col++) {
                screen[row][col] = ' ';
                attrs[row][col] = cur_attrs;
                lcd_drawc(' ', cur_attrs, col, row);
            }
            row++;
        }
    }
}

void
lcd_setcolor(int idx, int red, int green, int blue)
{
  attr_cols[idx].r = red;
  attr_cols[idx].g = green;
  attr_cols[idx].b = blue;
}

static int
_hexdigit(char c)
{
    if ((c >= '0') && (c <= '9')) {
        return c - '0';
    } else
    if ((c >= 'A') && (c <= 'F')) {
        return (c - 'A') + 0x0A;
    } else
    if ((c >= 'a') && (c <= 'f')) {
        return (c - 'a') + 0x0a;
    }
    else return 0;
}

static int
_hex(char *cp)
{
    return (_hexdigit(*cp)<<4) | _hexdigit(*(cp+1));
}

static RGBA parse_color(char *cp)
{
    int red, green, blue;

    while (*cp && (*cp != 'c')) cp++;
    if (cp) {
        cp += 2;
        if (*cp == '#') {
	  red = _hex(cp+1);
	  green = _hex(cp+3);
	  blue = _hex(cp+5);
	  return (RGBA){ red, green, blue, 0 };
        } else {
            // Should be "None"
	  return (RGBA){ -1, -1, -1, 0 };
        }
    } else {
      return (RGBA){ -1, -1, -1, 0 };
    }
}

static int
get_int(char **_cp)
{
    char *cp = *_cp;
    char c;
    int val = 0;
    
    while ((c = *cp++) && (c != ' ')) {
        if ((c >= '0') && (c <= '9')) {
            val = val * 10 + (c - '0');
        } else {
            return -1;
        }
    }
    *_cp = cp;
    return val;
}

int
show_xpm(char *xpm[], int screen_pos)
{
    int i, row, col, offset;
    char *cp;
    int nrows, ncols, nclrs;
    RGBA colors[256];  // Mapped by character index

    cp = xpm[0];
    if (((ncols = get_int(&cp)) < 0) ||
        ((nrows = get_int(&cp)) < 0) ||
        ((nclrs = get_int(&cp)) < 0)) {

        return 0;
    }
    // printf("%d rows, %d cols, %d colors\n", nrows, ncols, nclrs);

    for (i = 0;  i < 256;  i++) {
        colors[i] = (RGBA){ 0, 0, 0, 0 };
    }
    for (i = 0;  i < nclrs;  i++) {
        cp = xpm[i+1];
        colors[(unsigned int)*cp] = parse_color(&cp[1]);
        // printf("Color[%c] = %x\n", *cp, colors[(unsigned int)*cp]);
    }

#ifdef LOGO_AT_TOP
    offset = screen_pos;
#else
    offset = screen_pos-nrows;
#endif
    for (row = 0;  row < nrows;  row++) {            
        cp = xpm[nclrs+1+row];        
        for (col = 0;  col < ncols;  col++) {
            RGBA * clr = colors + ((unsigned int)*cp++);
            lcd_set_pixel(col, row+offset, clr->r, clr->g, clr->b);
        }
    }
#ifdef LOGO_AT_TOP
    screen_start = (nrows + (FONT_HEIGHT-1))/FONT_HEIGHT;
    return offset+nrows;
#else    
    screen_height = offset / FONT_HEIGHT;
    return offset;
#endif
}

