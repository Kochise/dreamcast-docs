/* ps2-load-ip

   printf.c
   Copyright (c)2002 Dan Potter
   License: BSD

   $Id: printf.c,v 1.3 2002/11/03 06:57:13 bardtx Exp $
*/

#include "stdio.h"
#include "stdarg.h"
#include "fb_support.h"
#include "ps2loadip.h"

/* Not re-entrant */
static char printf_buf[1024];

/* Writes a string to the GS */
void gs_printk(const char *str) {
	int i, l;

	l = strlen(str);
	for (i=0; i<l; i++)
		lcd_putc(str[i]);
}

/* Writes a string to the IP console */
void cons_printk(const char *str) {
	// XXX
}

/* GS printf */
int gs_printf(int fgattr, const char *fmt, ...) {
	va_list args;
	int r;

	va_start(args, fmt);
	r = vsprintf(printf_buf, fmt, args);
	va_end(args);

	if (fgattr != -1)
		lcd_setattrs(fgattr, LCD_DEFAULT_BG);
	gs_printk(printf_buf);
	if (fgattr != -1)
		lcd_setattrs(running ? LCD_RUN_FG : LCD_DEFAULT_FG, LCD_DEFAULT_BG);
}

int cons_printf(const char * fmt, ...) {
	va_list args;
	int r;

	va_start(args, fmt);
	r = vsprintf(printf_buf, fmt, args);
	va_end(args);

	cons_printk(printf_buf);
}

/* Where's our output going? */
int pf_output;

void printf_init() {
	pf_output = PRINTF_GS;
}

/* Generic redirectable printf */
int printf(const char *fmt, ...) {
	va_list args;
	int r;

	va_start(args, fmt);
	r = vsprintf(printf_buf, fmt, args);
	va_end(args);

	switch (pf_output) {
	case PRINTF_GS:
		gs_printk(printf_buf);
		break;
	case PRINTF_CONS:
		cons_printk(printf_buf);
		break;
	}

	return r;
}

