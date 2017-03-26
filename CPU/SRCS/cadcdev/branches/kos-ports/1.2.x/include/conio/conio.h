/* KallistiOS ##version##

 conio.h

 (c)2002 Dan Potter

 Adapted from Kosh, (c)2000 Jordan DeLong

 $Id: conio.h,v 1.1 2003/02/27 03:46:29 bardtx Exp $

*/

#ifndef __CONIO_CONIO_H
#define __CONIO_CONIO_H

#include <sys/cdefs.h>
__BEGIN_DECLS

/* some defines */
#define CONIO_NUM_ROWS	18
#define CONIO_NUM_COLS	48

/* our cursor */
typedef struct { int row, col; } conio_cursor_t;
extern conio_cursor_t conio_cursor;

/* the virtual screen */
extern char conio_virtscr[CONIO_NUM_ROWS][CONIO_NUM_COLS];

#include <conio/input.h>
#include <conio/draw.h>

/* functions */
void conio_scroll();
void conio_deadvance_cursor();
void conio_advance_cursor();
void conio_gotoxy(int x, int y);
int conio_getch();
int conio_check_getch();
void conio_setch(int ch);
void conio_putch(int ch);
void conio_putstr(char *str);
int conio_printf(const char *fmt, ...);
void conio_clear();
void conio_freeze();
void conio_thaw();
void conio_set_theme(int theme);

/* Themes:
   - PLAIN is white text on a black background
   - MATRIX is green text on a black background
   - C64 is cyan text on a blue background, with a cyan border
 */
#define CONIO_THEME_PLAIN	0
#define CONIO_THEME_MATRIX	1
#define CONIO_THEME_C64		2

/* Init modes:
   - TTY can be serial or PVR console
   - Input mode can be NONE, LINE, CHAR

   The only valid combination for now is TTY_PVR and INPUT_LINE */
#define CONIO_TTY_NONE		0
#define CONIO_TTY_PVR		1
#define CONIO_TTY_SERIAL	2
#define CONIO_INPUT_NONE	0
#define CONIO_INPUT_LINE	1
#define CONIO_INPUT_CHAR	2

extern int conio_ttymode, conio_inputmode, conio_theme;

int conio_init(int ttymode, int inputmode);
int conio_shutdown();

__END_DECLS

#endif /* __CONIO_CONIO_H */
