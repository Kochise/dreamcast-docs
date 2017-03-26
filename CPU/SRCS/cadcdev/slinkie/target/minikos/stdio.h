/* ps2-load-ip

   stdio.h
   Copyright (c)2002 Dan Potter
   License: BSD

   $Id: stdio.h,v 1.3 2002/11/03 06:57:13 bardtx Exp $
*/

#ifndef __STDIO_H
#define __STDIO_H

#include <sys/cdefs.h>
#include <stddef.h>
#include <stdarg.h>

// Generic stdio-style functions
int      vsprintf(char *, const char *, va_list);
int      sprintf(char *, const char *, ...);
int      printf(const char *, ...);

// Functions that target a specific output console
int	gs_printf(int fgattr, const char *, ...);
int	cons_printf(const char *, ...);

// Raw string output functions
void	gs_printk(const char *);
void	cons_printk(const char *);

// Select an output console
#define PRINTF_GS	0
#define PRINTF_CONS	1
extern int pf_output;
void printf_init();

#endif	/* __STDIO_H */

