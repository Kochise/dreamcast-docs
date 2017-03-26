/* KallistiOS ##version##

   kos/dbglog.h
   Copyright (C)2004 Dan Potter

   $Id: stdio.h,v 1.3 2003/06/23 05:21:31 bardtx Exp $

*/

#ifndef __KOS_DBGLOG_H
#define __KOS_DBGLOG_H

#include <kos/cdefs.h>
__BEGIN_DECLS

#include <unistd.h>
#include <stdarg.h>
#include <kos/fs.h>

/* Kernel debugging printf; all output sent to this is filtered through
   a kernel log level check before actually being printed. This way, you
   can set the level of debug info you want to see (or want your users
   to see). */
void dbglog(int level, const char *fmt, ...) __printflike(2, 3);

/* Log levels for the above */
#define DBG_DEAD	0		/* The system is dead */
#define DBG_CRITICAL	1		/* A critical error message */
#define DBG_ERROR	2		/* A normal error message */
#define DBG_WARNING	3		/* Potential problem */
#define DBG_NOTICE	4		/* Normal but significant */
#define DBG_INFO	5		/* Informational messages */
#define DBG_DEBUG	6		/* User debug messages */
#define DBG_KDEBUG	7		/* Kernel debug messages */

/* Set debug level */
void dbglog_set_level(int level);

__END_DECLS

#endif	/* __KOS_DBGLOG_H */

