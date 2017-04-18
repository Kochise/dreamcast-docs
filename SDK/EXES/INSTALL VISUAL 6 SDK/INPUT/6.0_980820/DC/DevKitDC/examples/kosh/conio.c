/*
 * conio.c - little console i/o module.
 *
 * (C) 2000 Jordan DeLong
 */
#include <os/abi/libk.h>
#include <os/abi/fundamental.h>
#include <os/abi/thread.h>
#include <arch/spinlock.h>
#include <stdio.h>
#include <string.h>
#include "conio.h"
#include "draw.h"
#include "kosh.h"

/* the cursor */
cursor_t cursor;

/* the virtual screen */
char virtscr[NUM_ROWS][NUM_COLS];

/* freeze/thaw mutex */
spinlock_t ft_mutex;

/* scroll everything up a line */
void conio_scroll() {
	int i;

	memmove(virtscr, virtscr[1], (NUM_ROWS - 1) * NUM_COLS);
	for (i = 0; i < NUM_COLS; i++)
		virtscr[NUM_ROWS - 1][i] = ' ';
	cursor.row--;
}

/* move the cursor back, don't scroll (we can't) */
void conio_deadvance_cursor() {
	cursor.col--;
	if (cursor.col < 0) {
		if (cursor.row != 0) {
			cursor.col = NUM_COLS - 1;
			cursor.row--;
		} else {
			cursor.col = 0;
		}
	}
}

/* move the cursor ahead, scroll if we need to */
void conio_advance_cursor() {
	cursor.col++;
	if (cursor.col >= NUM_COLS) {
		cursor.col = 0;
		cursor.row++;
		if (cursor.row >= NUM_ROWS)
			conio_scroll();
	}
}

/* move the cursor */
void conio_gotoxy(int x, int y) {
	cursor.col = x;
	cursor.row = y;
}

/* blocking call for a character */
int conio_getch() {
	int key;

	while ((key = kbd_get_key()) == -1) {}
	return key;
}

/* Check to see if a key has been pressed */
int conio_check_getch() {
	int key;

	key = kbd_get_key();
	return key;
}

/* set current char to ch, w/o advancing the cursor */
void conio_setch(int ch) {
	switch (ch) {
		case '\n':
		case '\r':
			break;
		default:
			virtscr[cursor.row][cursor.col] = ch;
	}
}

/* put a character at the cursor and move the cursor */
void conio_putch(int ch) {
	switch (ch) {
		case '\r':
			cursor.col = 0;
			break;
		case '\n':
			cursor.row++;
			cursor.col = 0;
			if (cursor.row >= NUM_ROWS)
				conio_scroll();
			break;
		default:
			virtscr[cursor.row][cursor.col] = ch;
			conio_advance_cursor();
	}
}

/* put a string of characters */
void conio_putstr(char *str) {
	while (*str != '\0') {
#if 0	/* rem'd by Dan to be able to use \r to go to first of line */
		/* treat CRLF, LF, or just CR exactly the same */
		if (*str == '\r') {
			if (str[1] == '\0')
				break;
			if (*(++str) != '\n')
				conio_putch('\r');
		}
#endif
		conio_putch(*str++);
	}
}

/* a printfish function */
int conio_printf(const char *fmt, ...) {
	char buff[512];	/* buffer overflow waiting to happen.... I'll add a vsnprintf func later */
	va_list args;
	int i;

	va_start(args, fmt);
	i = vsprintf(buff, fmt, args);

	conio_putstr(buff);

	va_end(args);

	return i;
}

/* clear the screen */
void conio_clear() {
	int row, col;

	/* fill screen with spaces */
	for (row = 0; row < NUM_ROWS; row++)
		for (col = 0; col < NUM_COLS; col++)
			virtscr[row][col] = ' ';
}

/* conio freeze (for sub-process taking over TA) */
static int dirty = 0;
void conio_freeze() {
	spinlock_lock(&ft_mutex);
	dirty = 1;
}

/* conio thaw */
void conio_thaw() {
	spinlock_unlock(&ft_mutex);
}

/* register conio service */
/*
#include "abi/conio.h"
static abi_conio_t cioabi;
static void conio_svc_init() {
	memset (&cioabi, 0, sizeof(cioabi));

	cioabi.hdr.version = ABI_MAKE_VER(1, 0, 0);

	cioabi.cursor = &cursor;

	cioabi.scroll = conio_scroll;
	cioabi.deadvance_cursor = conio_deadvance_cursor;
	cioabi.advance_cursor = conio_advance_cursor;
	cioabi.gotoxy = conio_gotoxy;
	cioabi.getch = conio_getch;
	cioabi.check_getch = conio_check_getch;
	cioabi.setch = conio_setch;
	cioabi.putch = conio_putch;
	cioabi.putstr = conio_putstr;
	cioabi.printf = conio_printf;
	cioabi.clear = conio_clear;
	cioabi.freeze = conio_freeze;
	cioabi.thaw = conio_thaw;

	svcmpx->add_handler("conio", &cioabi);
} */

/* ptr to old printf */
static int (*oldprintf)(const char *fmt, ...) = NULL;
static abi_fundamental_t *fabi = NULL;
static volatile int conio_entered = 0;
static int conio_exit = 0;

/* the drawing/keyboard polling thread */
static void conio_thread(void *param) {
	conio_entered = 1;
	while (!conio_exit) {
		spinlock_lock(&ft_mutex);
		if (dirty) {
			draw_init();
			dirty = 0;
		}
		kbd_poll(maple_first_kb());
		draw_frame();
		spinlock_unlock(&ft_mutex);
		thd_pass();
	}
}

/* initialize the console I/O stuffs */
int conio_init() {
	draw_init();
	conio_clear();
	conio_gotoxy(0, 0);
	/* conio_svc_init(); */

	spinlock_init(&ft_mutex);

	/* replace fundemental printf */
	/* fabi = lib_open("fundamental");
	oldprintf = fabi->printf;
	fabi->printf = conio_printf; */

	/* create the conio thread */
	if (thd_create(conio_thread, 0) < 0)
		return -1;

	/* Wait for it to actually start */
	while (!conio_entered)
		thd_pass();
	
	return 0;
}

int conio_shutdown() {
	/* shutup our thread */
	conio_exit = 1;

	/* unregister the service */
	/* svcmpx->remove_handler("conio"); */

	/* put back the old printf */
	/* fabi->printf = oldprintf;
	lib_close(fabi); */

	return 0;
}
