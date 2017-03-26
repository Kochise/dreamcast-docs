/* KallistiOS ##version##

   dbgio.c
   Copyright (C)2003 Dan Potter
*/

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <arch/arch.h>
#include <arch/dbgio.h>
#include <arch/spinlock.h>
#include <ia32/ports.h>

CVSID("$Id: dbgio.c,v 1.3 2003/08/02 23:11:43 bardtx Exp $");

/*

*/

static ptr_t scrn_mem;
static int output_attr;
static int curs_x,curs_y;

void vga_set_mem(uint32 base) { scrn_mem=base; }

void vga_clear() {
	memset2((void *)scrn_mem, 0x0700, 80*50);
}

void vga_move_cursor(uint32 x, uint32 y) {
	uint32	addr = y*80+x;

	curs_x = x;
	curs_y = y;

	outb(0x3d4, 0xe);
	outb(0x3d5, addr >> 8);
	outb(0x3d4, 0xf);
	outb(0x3d5, addr & 0xff);
}

void vga_scroll(uint32 ystart, uint32 numrows) {
	memcpy((void *)(scrn_mem + (ystart) * 160),
		(void *)(scrn_mem + (ystart+1) * 160),
		(numrows-1) * 160);
	memset((void *)(scrn_mem + (ystart + numrows - 1) * 160),
		0,160);
}

void vga_print_at(uint32 x, uint32 y, uint32 f, uint32 b, const char * string) {
	char	*output = (char *)(scrn_mem + y*160 + x*2);	
	int8	attr = (b << 4) | f;

	while (*string) {
		output[0] = *string;
		output[1] = attr;
		output += 2;
		string++;
	}
}

void vga_setcolor(uint32 f, uint32 b) {
	output_attr = (b<<4) | f;
}

void vga_print(const char *string) {
	uint8	*output = (uint8 *)scrn_mem;
	uint8	attr = output_attr;
	uint32	x = curs_x, y = curs_y;

	while (*string) {
		if (*string == '\n') {
			x=0; y++;
		} else if (*string == '\r') {
			x = 0;
		} else if (*string == '\t') {
			x = (x + 7) & ~7;
			if (x >= 80) { x-=80; y++; }
		} else {
			output[(y*160+x*2)] = *string;
			output[(y*160+x*2)+1] = attr;

			x++;
			if (x >= 80) { x=0; y++; }
		}

		if (y >= 25) {
			vga_scroll(1,24);
			y=24;
		}

		string++;
	}

	vga_move_cursor(x,y);
}

void vga_wait() {
	while ((inb(0x3da) & 8))
		;
	while (!(inb(0x3da) & 8))
		;
}

void vga_get_cursor(uint32 * cx, uint32 * cy) {
	*cx = curs_x;
	*cy = curs_y;
}

int vga_init() {
	// Do some initial setup
	vga_set_mem(0xb8000);
	vga_clear();		// clear the screen
	vga_move_cursor(0,1);	// put the cursor on the second row
	vga_setcolor(7,0);

	// Print a banner so we can see what's going on
	vga_print_at(0,0,15,1," KallistiOS/ia32                                                                ");
	vga_print("Startup console output initialized.\n");

	return 0;
}

int vga_shutdown() {
        return 0;
}

///////////////////////////////////////////////////////////////////////

/* This redirect is here to allow you to hook the debug output in your 
   program if you want to do that. */
dbgio_printk_func dbgio_printk = dbgio_null_write;

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

/* Write one char to the serial port (call serial_flush()!) */
void dbgio_write(int c) {
	char foo[2] = { c, 0 };
	vga_print(foo);
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
	dbgio_write_buffer(data, len);
}

/* Send a string (null-terminated) */
void dbgio_write_str(const char *str) {
	dbgio_write_buffer((const uint8*)str, strlen(str));
}

/* Null write-string function for pre-init */
void dbgio_null_write(const char *str) {
}

///////////////////////////////////////////////////////////////////////

// Ring buffer
static uint8 buffer[32];
static int buf_head, buf_tail, buf_cnt;

// Scancode translator
static uint8 scans[256] = {
	0,
	27,
	'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 8,		// 2+
	9, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 13,	// 15+
	0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'',		// 29+
	'`', 0, 0, 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,		// 41+
	'*', 0, 32
};

// IRQ9 handler
static void kb_hnd(irq_t src, irq_context_t * cxt) {
	int sc, oc;

	// Read the input value
	sc = inb(0x60);

	// Ack the KB controller
	oc = inb(0x61);
	outb(0x61, oc | 0x80);
	outb(0x61, oc & ~0x80);
	// outb(0x20, 0x61);

	// Ignore release codes
	if (sc & 0x80)
		return;

	// Translate it to ASCII if possible
	if (scans[sc]) {
		sc = scans[sc];

		// Store it in the buffer
		buffer[buf_head] = sc;
		buf_head = (buf_head + 1) % 32;
		buf_cnt++;
	}
}

/* Read one char from the serial port (-1 if nothing to read) */
int dbgio_read() {
	int old = irq_disable();
	int rv = -1;

	if (buf_cnt > 0) {
		rv = buffer[buf_tail];
		buf_tail = (buf_tail + 1) % 32;
		buf_cnt--;
	}

	irq_restore(old);

	return rv;
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

///////////////////////////////////////////////////////////////////////

// First init, handles only output
void dbgio_init() {
	vga_init();
	dbgio_printk = vga_print;
}

// Second init, also sets up keyboard input
void dbgio_init_2() {
	int oc;

	// Clear any pending keyboard input, in case...
	inb(0x60);
	inb(0x60);
	inb(0x60);

	// Send an enable command
	while (inb(0x64) & 2)
		;
	outb(0x64,0xae);
	while (inb(0x64) & 2)
		;

	// ACK the response
	oc = inb(0x61);
	outb(0x61, oc | 0xc0);
	outb(0x61, oc & ~0xc0);

	// Reset the queues and hook interrupts
	buf_head = buf_tail = buf_cnt = 0;
	irq_set_handler(EXC_IRQ1, kb_hnd);
	outb(0x21, inb(0x21) & ~2);

	dbgio_printk("PC/AT keyboard input enabled.\n");
}


///////////////////////////////////////////////////////////////////////

/* Not re-entrant */
static char printf_buf[1024];
static spinlock_t lock = SPINLOCK_INITIALIZER;

int dbgio_printf(const char *fmt, ...) {
	va_list args;
	int i;

	/* XXX This isn't correct. We could be inside an int with IRQs
	   enabled, and we could be outside an int with IRQs disabled, which
	   would cause a deadlock here. We need an irq_is_enabled()! */
	//if (!irq_inside_int())
	//	spinlock_lock(&lock);

	va_start(args, fmt);
	i = vsprintf(printf_buf, fmt, args);
	va_end(args);

	dbgio_printk(printf_buf);

	//if (!irq_inside_int())
	//	spinlock_unlock(&lock);

	return i;
}

