/*
 * draw.h - drawing funcs for kosh
 *
 * (C) 2000 Jordan DeLong
 */
#ifndef _KOSH_DRAW_H
#define _KOSH_DRAW_H

#include "conio.h"

/* font size constants */
#define FONT_WIDTH 	12
#define FONT_HEIGHT 	24

/* screen size constants */
#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

/* more constants */
#define SCREEN_FIRSTCOL ( (SCREEN_WIDTH - FONT_WIDTH * NUM_COLS) / 2 )
#define SCREEN_LASTCOL  (SCREEN_WIDTH - SCREEN_FIRSTCOL)

/* color themes */
#define THEME_C64	1
#define THEME_MATRIX	2
#define THEME_PLAIN	3

/* the theme */
extern int draw_theme;

/* functions */
void draw_frame();

#endif

