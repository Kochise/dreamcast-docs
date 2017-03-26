/* KallistiOS ##version##

   dbgio.c
   (c)2002 Dan Potter
*/

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <arch/arch.h>
#include <arch/dbgio.h>
#include <arch/spinlock.h>

CVSID("$Id: dbgio.c,v 1.2 2002/11/03 03:40:55 bardtx Exp $");

/*

This module assumes the existance of ps2-load-ip. If ps2-load-ip
isn't present, then it just disables itself.

There's no support for non-RTE targets right now, but eventually it
should probably hook up to something like NapLink's USB client.

*/

/* This redirect is here to allow you to hook the debug output in your 
   program if you want to do that. */
dbgio_printk_func dbgio_printk = dbgio_null_write;

/* Set serial parameters; this is not platform independent like I want
   it to be, but it should be generic enough to be useful. */
void dbgio_set_parameters(int baud, int fifo) { }

/* Enable serial support */
void dbgio_enable() { }

/* Disable serial support */
void dbgio_disable() { }

/* Set another function to capture all debug output */
dbgio_printk_func dbgio_set_printk(dbgio_printk_func func) {
	dbgio_printk_func rv = dbgio_printk;
	dbgio_printk = func;
	return rv;
}

/* This should probably hook up to a ps2-load-ip module at some point */
static uint32 * ps2lip_block;
static int (*ps2lip_syscall)(int code, ...);

void dbgio_init() {
	dbgio_printk = dbgio_null_write;

	if (!ps2lip_block) {
		ps2lip_block = (uint32 *)((uint32 *)0x81fff800)[0];
		if (ps2lip_block == NULL)
			return;
		if (ps2lip_block[0] != 0xdeadbeef) {
			ps2lip_block = NULL;
			return;
		}
	}

	ps2lip_syscall = (int (*)(int, ...))ps2lip_block[2];
	
	dbgio_set_printk(dbgio_write_str);
}

void dbgio_write(int c) {
	char str[2] = { c, 0 };
	if (ps2lip_syscall != NULL)
		ps2lip_syscall(14, str);
}

/* Flush all FIFO'd bytes out of the serial port buffer */
void dbgio_flush() {
}

/* Send an entire buffer */
void dbgio_write_buffer(const uint8 *data, int len) {
	while (len-- > 0)
		dbgio_write(*data++);
}

/* Send an entire buffer */
void dbgio_write_buffer_xlat(const uint8 *data, int len) {
	while (len-- > 0) {
		if (*data == '\n')
			dbgio_write('\r');
		dbgio_write(*data++);
	}
}

/* Send a string (null-terminated) */
void dbgio_write_str(const char *str) {
	dbgio_write_buffer_xlat((const uint8*)str, strlen(str));
}

/* Null write-string function for pre-init */
void dbgio_null_write(const char *str) {
}

/* Read one char from the serial port (-1 if nothing to read) */
int dbgio_read() {
	return -1;
}

/* Read an entire buffer (block) */
void dbgio_read_buffer(uint8 *data, int len) {
}

/* Not re-entrant */
static char printf_buf[1024];
static spinlock_t lock = SPINLOCK_INITIALIZER;

int dbgio_printf(const char *fmt, ...) {
	va_list args;
	int i;

	if (!irq_inside_int())
		spinlock_lock(&lock);

	va_start(args, fmt);
	i = vsprintf(printf_buf, fmt, args);
	va_end(args);

	dbgio_printk(printf_buf);

	if (!irq_inside_int())
		spinlock_unlock(&lock);

	return i;
}

