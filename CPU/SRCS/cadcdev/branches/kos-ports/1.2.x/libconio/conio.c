/* KallistiOS ##version##

 conio.c

 (c)2002 Dan Potter

 Adapted from Kosh, (c)2000 Jordan DeLong

*/

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <kos/sem.h>
#include <dc/maple/keyboard.h>
#include <conio/conio.h>
#include <conio/draw.h>
#include <conio/input.h>
#include <arch/dbgio.h>

/* the cursor */
conio_cursor_t conio_cursor;

/* the virtual screen */
char conio_virtscr[CONIO_NUM_ROWS][CONIO_NUM_COLS];

/* Our modes */
int conio_ttymode = CONIO_TTY_NONE, conio_inputmode = CONIO_INPUT_NONE;
int conio_theme = CONIO_THEME_PLAIN;

/* freeze/thaw mutex */
static semaphore_t *ft_mutex;

/* scroll everything up a line */
void conio_scroll() {
	int i;

	switch (conio_ttymode) {
		case CONIO_TTY_PVR:
			memmove(conio_virtscr, conio_virtscr[1], (CONIO_NUM_ROWS - 1) * CONIO_NUM_COLS);
			for (i = 0; i < CONIO_NUM_COLS; i++)
				conio_virtscr[CONIO_NUM_ROWS - 1][i] = ' ';
			conio_cursor.row--;
			break;
		case CONIO_TTY_SERIAL:
			dbgio_write_buffer((const uint8 *)"\x1b[M", 3);
			break;
	}
}

/* move the cursor back, don't scroll (we can't) */
void conio_deadvance_cursor() {
	switch (conio_ttymode) {
		case CONIO_TTY_PVR:
			conio_cursor.col--;
			if (conio_cursor.col < 0) {
				if (conio_cursor.row != 0) {
					conio_cursor.col = CONIO_NUM_COLS - 1;
					conio_cursor.row--;
				} else {
					conio_cursor.col = 0;
				}
			}
			break;
		case CONIO_TTY_SERIAL:
			dbgio_write(8);
			dbgio_write(32);
			dbgio_write(8);
			break;
	}
}

/* move the cursor ahead, scroll if we need to */
void conio_advance_cursor() {
	switch (conio_ttymode) {
		case CONIO_TTY_PVR:
			conio_cursor.col++;
			if (conio_cursor.col >= CONIO_NUM_COLS) {
				conio_cursor.col = 0;
				conio_cursor.row++;
				if (conio_cursor.row >= CONIO_NUM_ROWS)
					conio_scroll();
			}
			break;
		case CONIO_TTY_SERIAL:
			dbgio_write_buffer((const uint8 *)"\x1b[1C", 4);
			break;
	}
}

/* move the cursor */
void conio_gotoxy(int x, int y) {
	switch (conio_ttymode) {
		case CONIO_TTY_PVR:
			conio_cursor.col = x;
			conio_cursor.row = y;
			break;
		case CONIO_TTY_SERIAL: {
			char tmp[256];
			sprintf(tmp, "\x1b[%d;%df", x, y);
			dbgio_write_buffer(tmp, strlen(tmp));
			break;
		}
	}
}

/* blocking call for a character */
int conio_getch() {
	int key = -1;

	switch (conio_ttymode) {
		case CONIO_TTY_PVR:
			while ((key = kbd_get_key()) == -1) { thd_pass(); }
			break;
		case CONIO_TTY_SERIAL:
			while ((key = dbgio_read()) == -1) { thd_pass(); }
			break;
	}
	return key;
}

/* Check to see if a key has been pressed */
int conio_check_getch() {
	int key = -1;

	switch (conio_ttymode) {
		case CONIO_TTY_PVR:
			key = kbd_get_key();
			break;
		case CONIO_TTY_SERIAL:
			key = dbgio_read();
			break;
	}
	return key;
}

/* set current char to ch, w/o advancing the cursor */
void conio_setch(int ch) {
	switch (conio_ttymode) {
		case CONIO_TTY_PVR:
			switch (ch) {
				case '\n':
				case '\r':
					break;
				default:
					conio_virtscr[conio_cursor.row][conio_cursor.col] = ch;
			}
			break;
		case CONIO_TTY_SERIAL:
			conio_deadvance_cursor();
			conio_putch(ch);
			break;
	}
}

/* put a character at the cursor and move the cursor */
void conio_putch(int ch) {
	switch (conio_ttymode) {
		case CONIO_TTY_PVR:
			switch (ch) {
				case '\r':
					conio_cursor.col = 0;
					break;
				case '\n':
					conio_cursor.row++;
					conio_cursor.col = 0;
					if (conio_cursor.row >= CONIO_NUM_ROWS)
						conio_scroll();
					break;
				default:
					conio_virtscr[conio_cursor.row][conio_cursor.col] = ch;
					conio_advance_cursor();
			}
			break;
		case CONIO_TTY_SERIAL:
			if (ch == '\n')
				dbgio_write('\r');
			else if (ch == '\r')
				break;
			dbgio_write(ch);
			break;
	}
}

/* put a string of characters */
void conio_putstr(char *str) {
	while (*str != '\0') {
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

	switch (conio_ttymode) {
		case CONIO_TTY_PVR:
			/* fill screen with spaces */
			for (row = 0; row < CONIO_NUM_ROWS; row++)
				for (col = 0; col < CONIO_NUM_COLS; col++)
					conio_virtscr[row][col] = ' ';
			break;
		case CONIO_TTY_SERIAL:
			dbgio_write_buffer((uint8 *)"\x1b[2J", 4);
			break;
	}
}

/* conio freeze (for sub-process taking over TA) */
void conio_freeze() {
	sem_wait(ft_mutex);
}

/* conio thaw */
void conio_thaw() {
	sem_signal(ft_mutex);
}

/* set theme */
void conio_set_theme(int theme) {
	assert( theme >= CONIO_THEME_PLAIN && theme <= CONIO_THEME_C64 );
	conio_theme = theme;
}

/* ptr to old printf */
/* static int (*oldprintf)(const char *fmt, ...) = NULL; */
static volatile int conio_entered = 0;
static volatile int conio_exit = 0;

/* the drawing/keyboard polling thread */
static void conio_thread(void *param) {
	conio_entered = 1;
	while (!conio_exit) {
		sem_wait(ft_mutex);
		conio_input_frame();
		if (conio_ttymode == CONIO_TTY_PVR)
			conio_draw_frame();
		else {
			dbgio_flush();
			thd_sleep(1000/60);	/* Simulate frame delay */
		}
		sem_signal(ft_mutex);
	}
	conio_exit = -1;
}

/* initialize the console I/O stuffs */
int conio_init(int ttymode, int inputmode) {
	conio_ttymode = ttymode;
	conio_inputmode = inputmode;

	switch (conio_ttymode) {
		case CONIO_TTY_PVR:
			conio_draw_init();
			break;
		case CONIO_TTY_SERIAL:
			break;
		default:
			assert_msg( false, "Unknown CONIO TTY mode" );
			conio_ttymode = CONIO_TTY_PVR;
			break;
	}
	assert_msg( conio_inputmode == CONIO_INPUT_LINE, "Non-Line input modes not supported yet" );

	conio_input_init();
	conio_clear();
	conio_gotoxy(0, 0);

	ft_mutex = sem_create(1);

	/* create the conio thread */
	conio_exit = 0;
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

	while (conio_exit != -1)
		;

	/* Delete the sempahore */
	sem_destroy(ft_mutex);

	if (conio_ttymode == CONIO_TTY_PVR)
		conio_draw_shutdown();
	conio_input_shutdown();

	conio_ttymode = CONIO_TTY_NONE;
	conio_inputmode = CONIO_INPUT_NONE;
	
	return 0;
}
