/* KallistiOS ##version##

   kos/include/dbgio.h
   Copyright (C)2000,2004 Dan Potter

   $Id: dbgio.h,v 1.4 2002/04/06 23:40:32 bardtx Exp $
  
*/

#ifndef __KOS_DBGIO_H
#define __KOS_DBGIO_H

#include <kos/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/// This struct represents a single dbgio interface. This should represent
/// a generic pollable console interface. We will store an ordered list of
/// these statically linked into the program and fall back from one to the
/// next until one returns true for detected(). Note that the last device in
/// this chain is the null console, which will always return true.
typedef struct dbgio_handler {
	/// Name of the dbgio handler
	const char	* name;

	/// Returns 1 if the device is available and usable, or 0 if it
	/// appears not to be.
	int	(*detected)();

	/// Init the interface with default parameters.
	int	(*init)();

	/// Shut down the interface
	int	(*shutdown)();

	/// Set polled/IRQ usage
	int	(*set_irq_usage)(int mode);

	/// Read one char from the console or -1 if there's nothing to read,
	/// or an error condition exists (check errno).
	int	(*read)();
	
	/// Write one char to the console (may need to call flush()).
	/// Returns the number of chars written or -1 on error.
	int	(*write)(int c);

	/// Flush any queued written bytes. Returns -1 on error.
	int	(*flush)();

	/// Send an entire buffer. Returns the number of chars written or
	/// -1 on error. If xlat is non-zero, then newline transformations
	/// may occur.
	int	(*write_buffer)(const uint8 *data, int len, int xlat);

	/// Read a buffer (block). Returns the number of chars read or
	/// -1 on error.
	int	(*read_buffer)(uint8 *data, int len);
} dbgio_handler_t;

// These two should be initialized in arch.
extern dbgio_handler_t * dbgio_handlers[];
extern int dbgio_handler_cnt;

// This is defined by the shared code, in case there's no valid handler.
extern dbgio_handler_t dbgio_null;

/// Manually select a new dbgio interface by name. Returns 0 on success or
/// -1 on error. Note that even if the given device isn't detected, this
/// will still let you select it.
int dbgio_dev_select(const char * name);

/// Returns the name of the currently selected device.
const char * dbgio_dev_get();

/// Initialize the dbgio console. The device selection process is as
/// described above.
int dbgio_init();

/// Set IRQ usage - we default to polled
int dbgio_set_irq_usage(int mode);
#define DBGIO_MODE_POLLED 0
#define DBGIO_MODE_IRQ 1

/// Read one char from the console or -1 if there's nothing to read,
/// or an error condition exists (check errno).
int dbgio_read();

/// Write one char to the console (may need to call flush()).
/// Returns the number of chars written or -1 on error.
int dbgio_write(int c);

/// Flush any queued written bytes. Returns -1 on error.
int dbgio_flush();

/// Send an entire buffer. Returns the number of chars written or
/// -1 on error.
int dbgio_write_buffer(const uint8 *data, int len);

/// Read a buffer (block). Returns the number of chars read or
/// -1 on error.
int dbgio_read_buffer(uint8 *data, int len);

/// Send an entire buffer. Returns the number of chars written or
/// -1 on error. Newline translations may occur.
int dbgio_write_buffer_xlat(const uint8 *data, int len);

/// Send a string (null-terminated). Returns the number of chars
/// written or -1 on error.
int dbgio_write_str(const char *str);

/// Disable debug I/O globally
void dbgio_disable();

/// Enable debug I/O globally
void dbgio_enable();

/// Printf functionality
int dbgio_printf(const char *fmt, ...) __printflike(1, 2);

__END_DECLS

#endif	// __KOS_DBGIO_H

