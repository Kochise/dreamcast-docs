/* KallistiOS ##version##

   arch/ps2/include/dbgio.h
   (c)2000 Dan Potter

   $Id: dbgio.h,v 1.1 2002/10/26 08:04:00 bardtx Exp $
  
*/

#ifndef __ARCH_DBGIO_H
#define __ARCH_DBGIO_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* Set another function to capture all debug output */
typedef void (*dbgio_printk_func)(const char *);
dbgio_printk_func dbgio_set_printk(dbgio_printk_func func);

extern dbgio_printk_func dbgio_printk;


/* Set serial parameters; this is not platform independent like I want   
   it to be, but it should be generic enough to be useful. */
void dbgio_set_parameters(int baud, int fifo);

/* Initialize the debug output */
void dbgio_init();

/* Write one char to the debug output */
void dbgio_write(int c);

/* Flush all pending output -- currently a NOP */
void dbgio_flush();

/* Send an entire buffer */
void dbgio_write_buffer(const uint8 *data, int len);

/* Read an entire buffer (block) -- currently a NOP */
void dbgio_read_buffer(uint8 *data, int len);

/* Send a string (null-terminated) */
void dbgio_write_str(const char *str);

/* Null write-string function for pre-init */
void dbgio_null_write(const char *str);

/* Read one char from the serial port (-1 if nothing to read) -- currently a NOP */
int dbgio_read();

/* Enable / Disable debug I/O globally */
void dbgio_disable();
void dbgio_enable();

/* Printf functionality */
int dbgio_printf(const char *fmt, ...) __printflike(1, 2);

__END_DECLS

#endif	/* __ARCH_DBGIO_H */

