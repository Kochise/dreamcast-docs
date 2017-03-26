/* ps2-load-ip

   fb_support.h

   Copyright (c)2002 Dan Potter
   License: BSD

   $Id: fb_support.h,v 1.2 2002/11/03 06:57:13 bardtx Exp $
*/

#ifndef __FB_SUPPORT_H
#define __FB_SUPPORT_H

#include "types.h"

typedef struct { int r, g, b, a; } RGBA;

#define LCD_DEFAULT_FG	0
#define LCD_RUN_FG	1
#define LCD_DEFAULT_BG	2
#define LCD_CURSOR_FG	3
#define LCD_SYSMSG_FG	4
#define LCD_LOADMSG_FG	3

void lcd_init(void);
void lcd_set_pixel(int x, int y, int r, int g, int b);
void lcd_clear(void);
void lcd_moveto(int x, int y);
void lcd_putc(int8 c);
void lcd_setcolor(int idx, int red, int green, int blue);
void lcd_setattrs(int fg, int bg);
void lcd_drawc(int8 c, uint8 attrs, int x, int y);
void lcd_refresh();

#endif	/* __FB_SUPPORT_H */

