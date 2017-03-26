/* KallistiOS ##version##

   assert.h
   (c)2002 Dan Potter

   $Id: assert.h,v 1.2 2002/09/13 04:41:57 bardtx Exp $
*/

#ifndef __ASSERT_H
#define __ASSERT_H

#include <sys/cdefs.h>
__BEGIN_DECLS

/* This is nice and simple, modeled after the BSD one like most of KOS;
   the addition here is assert_msg(), which allows you to provide an
   error message. */
#define _assert(e) assert(e)

/* __FUNCTION__ is not ANSI, it's GCC, but we depend on GCC anyway.. */
#ifdef NDEBUG
#	define assert(e) ((void)0)
#	define assert_msg(e, m) ((void)0)
#else
#	define assert(e)        ((e) ? (void)0 : __assert(__FILE__, __LINE__, #e, NULL, __FUNCTION__))
#	define assert_msg(e, m) ((e) ? (void)0 : __assert(__FILE__, __LINE__, #e, m, __FUNCTION__))
#endif

/* Defined in assert.c */
void __assert(const char *file, int line, const char *expr,
	const char *msg, const char *func);

/* Set an "assert handler" which is called whenever an assert happens.
   By default, this will print a message and call abort(). Returns the old
   handler's address. */
typedef void (*assert_handler_t)(const char * file, int line, const char * expr,
	const char * msg, const char * func);
assert_handler_t assert_set_handler(assert_handler_t hnd);

__END_DECLS

#endif	/* __ASSERT_H */

