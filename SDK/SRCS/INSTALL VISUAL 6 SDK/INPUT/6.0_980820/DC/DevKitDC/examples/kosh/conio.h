/*
 * conio.h - mini console i/o
 *
 * (C) 2000 Jordan DeLong
 */
#ifndef _KOSH_CONIO_H
#define _KOSH_CONIO_H

/* some defines */
#define NUM_ROWS	18
#define NUM_COLS	48

/* our cursor */
typedef struct { int row, col; } cursor_t;
extern cursor_t cursor;

/* the virtual screen */
extern char virtscr[NUM_ROWS][NUM_COLS];

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
int conio_init();
int conio_shutdown();
void conio_freeze();
void conio_thaw();

#endif
