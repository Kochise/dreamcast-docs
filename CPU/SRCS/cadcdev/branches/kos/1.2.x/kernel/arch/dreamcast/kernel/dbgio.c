/* KallistiOS ##version##

   dbgio.c
   (c)2000-2001 Dan Potter
*/

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <arch/arch.h>
#include <arch/dbgio.h>
#include <arch/spinlock.h>

CVSID("$Id: dbgio.c,v 1.4 2002/02/18 02:58:02 bardtx Exp $");

/*

This module handles very basic serial I/O using the SH4's SCIF port. FIFO
mode is used by default; you can turn this off to avoid forcing a wait
when there is no serial device attached.

Unlike in KOS 1.x, this is not designed to be used as the normal I/O, but
simply as an early debugging device in case something goes wrong in the
kernel or for debugging it.

*/

/* This redirect is here to allow you to hook the debug output in your 
   program if you want to do that. */
dbgio_printk_func dbgio_printk = dbgio_null_write;

/* Is serial enabled? This is a failsafe for making CDRs. */
static int serial_enabled = 1;

/* Default serial parameters */
static int serial_baud = DEFAULT_SERIAL_BAUD,
	serial_fifo = DEFAULT_SERIAL_FIFO;

/* Set serial parameters; this is not platform independent like I want
   it to be, but it should be generic enough to be useful. */
void dbgio_set_parameters(int baud, int fifo) {
	serial_baud = baud;
	serial_fifo = fifo;
}

/* Enable serial support */
void dbgio_enable() { serial_enabled = 1; }

/* Disable serial support */
void dbgio_disable() { serial_enabled = 0; }

/* Set another function to capture all debug output */
dbgio_printk_func dbgio_set_printk(dbgio_printk_func func) {
	dbgio_printk_func rv = dbgio_printk;
	dbgio_printk = func;
	return rv;
}

/* Initialize the SCIF port; baud_rate must be at least 9600 and
   no more than 57600. 115200 does NOT work for most PCs. */
void dbgio_init() {
	volatile uint16 *scif16 = (uint16*)0xffe80000;
	volatile uint8 *scif8 = (uint8*)0xffe80000;
	int i;
	/* int fifo = 1; */

	/* If another handler hasn't been set, then set our serial
	   write handler to capture console output. */
	if (dbgio_printk == dbgio_null_write)
		dbgio_printk = dbgio_write_str;
	
	/* Disable interrupts, transmit/receive, and use internal clock */
	scif16[8/2] = 0;
	
	/* 8N1, use P0 clock */
	scif16[0] = 0;
	
	/* If baudrate unset, set baudrate, N = P0/(32*B)-1 */
	if (scif8[4] == 0xff)
		scif8[4] = (50000000 / (32 * serial_baud)) - 1;

	/* Reset FIFOs, enable hardware flow control */	
	scif16[24/2] = 12;
	scif16[24/2] = 8;
	
	/* Disable manual pin control */
	scif16[32/2] = 0;
	
	/* Clear status */
	scif16[16/2] = 0x60;
	scif16[36/2] = 0;
	
	/* Enable transmit/receive */
	scif16[8/2] = 0x30;

	/* Start off enabled */
	serial_enabled = 1;

	/* Wait a bit for it to stabilize */
	for (i=0; i<10000; i++)
		asm("nop");
}

/* Write one char to the serial port (call serial_flush()!) */
void dbgio_write(int c) {
	volatile uint16 *ack = (uint16*)0xffe80010;
	volatile uint8 *fifo = (uint8*)0xffe8000c;
	int timeout = 100000;

	if (!serial_enabled) return;
	
	/* Wait until the transmit buffer has space */
	while (!(*ack & 0x20) && timeout > 0)
		timeout--;
	if (timeout <= 0) {
		serial_enabled = 0;
		return;
	}
	
	/* Send the char */
	*fifo = c;
	
	/* Clear status */
	*ack &= 0x9f;
}

/* Flush all FIFO'd bytes out of the serial port buffer */
void dbgio_flush() {
	volatile uint16 *ack = (uint16*)0xffe80010;
	int timeout = 100000;

	if (!serial_enabled) return;
	
	*ack &= 0xbf;

	while (!(*ack & 0x40) && timeout > 0)
		timeout--;
	if (timeout <= 0) {
		serial_enabled = 0;
		return;
	}

	*ack &= 0xbf;
}

/* Send an entire buffer */
void dbgio_write_buffer(const uint8 *data, int len) {
	while (len-- > 0)
		dbgio_write(*data++);
	dbgio_flush();
}

/* Send an entire buffer */
void dbgio_write_buffer_xlat(const uint8 *data, int len) {
	while (len-- > 0) {
		if (*data == '\n')
			dbgio_write('\r');
		dbgio_write(*data++);
	}
	dbgio_flush();
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
	volatile uint16 *status = (uint16*)0xffe8001c;
	volatile uint16 *ack = (uint16*)0xffe80010;
	volatile uint8 *fifo = (uint8*)0xffe80014;
	int c;

	if (!serial_enabled) return -1;
	
	/* Check input FIFO */
	if (!(*status & 0x1f)) return -1;
	
	/* Get the input char */
	c = *fifo;
	
	/* Ack */
	*ack &= 0x6d;

	return c;
}

/* Read an entire buffer (block) */
void dbgio_read_buffer(uint8 *data, int len) {
	int c;
	while (len-- > 0) {
		while ( (c = dbgio_read()) == -1)
			;
		*data++ = c;
	}
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

