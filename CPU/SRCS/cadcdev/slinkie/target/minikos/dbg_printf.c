/* ps2-load-ip

   sprintf.c
   Copyright (C)2002 Dan Potter
   License: BSD

   $Id: sprintf.c,v 1.1 2002/10/30 05:34:13 bardtx Exp $
*/

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <dc/scif.h>

int printf(const char *fmt, ...) {
	char buf[1024];
	va_list args;
	int i;

	va_start(args, fmt);
	i = vsprintf(buf, fmt, args);
	va_end(args);

	scif_write_buffer(buf, strlen(buf), 1);

	return i;
}
